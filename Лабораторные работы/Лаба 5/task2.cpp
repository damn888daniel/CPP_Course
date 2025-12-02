// Подключаем необходимые библиотеки
#include <iostream>            // Для ввода-вывода (std::cout)
#include <queue>               // Для работы с очередью (std::queue)
#include <thread>              // Для работы с потоками (std::thread)
#include <mutex>               // Для работы с мьютексами (std::mutex)
#include <condition_variable>  // Для синхронизации потоков (std::condition_variable)
#include <chrono>              // Для работы со временем (std::chrono)

// Шаблонный класс потокобезопасной очереди
// T - тип элементов, которые хранятся в очереди
template<typename T>
class ThreadSafeQueue {
private:
    std::queue<T> queue;               // Внутренняя очередь (стандартная std::queue)
    std::mutex mutex;                  // Мьютекс для защиты доступа к очереди
    std::condition_variable cond;      // Условная переменная для оповещения потоков
    bool is_shutdown = false;          // Флаг завершения работы очереди

public:
    // Метод для добавления элемента в очередь (вызывается производителем)
    void push(T value) {
        {
            // Захватываем мьютекс для безопасного доступа к очереди
            std::lock_guard<std::mutex> lock(mutex);
            // Добавляем элемент в очередь (std::move для оптимизации)
            queue.push(std::move(value));
        }  // Мьютекс автоматически освобождается здесь

        // Оповещаем один ожидающий поток о том, что в очереди появился элемент
        cond.notify_one();
    }

    // Метод для извлечения элемента из очереди (вызывается потребителем)
    // value - ссылка, куда будет записан извлечённый элемент
    // Возвращает true, если элемент успешно извлечён, false - если очередь завершила работу
    bool pop(T& value) {
        // Захватываем мьютекс с возможностью временного освобождения
        std::unique_lock<std::mutex> lock(mutex);

        // Ожидаем, пока очередь не завершится (is_shutdown) или не появится элемент
        // Лямбда-функция определяет условие выхода из ожидания
        cond.wait(lock, [this]() {
            return is_shutdown || !queue.empty();  // Выходим, если есть элементы или shutdown
        });

        // Если очередь пуста и работа завершена, возвращаем false
        if (queue.empty() && is_shutdown) {
            return false;
        }

        // Извлекаем элемент из очереди
        value = std::move(queue.front());  // Берём первый элемент
        queue.pop();                       // Удаляем его из очереди

        return true;  // Успешно извлекли элемент
    }

    // Метод для завершения работы очереди
    void shutdown() {
        {
            // Захватываем мьютекс для установки флага завершения
            std::lock_guard<std::mutex> lock(mutex);
            is_shutdown = true;  // Устанавливаем флаг завершения
        }  // Мьютекс освобождается

        // Оповещаем все ожидающие потоки о завершении работы
        cond.notify_all();
    }
};

// Функция производителя: генерирует числа и добавляет их в очередь
// queue - ссылка на очередь
// count - количество чисел для генерации
void producer(ThreadSafeQueue<int>& queue, int count) {
    // Генерируем числа от 0 до count-1
    for (int i = 0; i < count; ++i) {
        queue.push(i);  // Добавляем число в очередь

        // Задержка 1 миллисекунда (имитация времени работы)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    // По завершении работы отправляем сигнал завершения
    queue.shutdown();
}

// Функция потребителя: извлекает числа из очереди и обрабатывает их
// queue - ссылка на очередь
// id - идентификатор потребителя (для отображения в консоли)
void consumer(ThreadSafeQueue<int>& queue, int id) {
    int value;  // Переменная для хранения извлечённого значения

    // Цикл работает, пока можно извлекать элементы из очереди
    while (queue.pop(value)) {
        // Выводим информацию о полученном значении
        std::cout << "[Потребитель " << id << "] получил " << value << std::endl;

        // Задержка 5 миллисекунд (имитация обработки данных)
        std::this_thread::sleep_for(std::chrono::milliseconds(5));
    }

    // Выводим сообщение о завершении работы потребителя
    std::cout << "[Потребитель " << id << "] завершил работу" << std::endl;
}

// Главная функция программы
int main() {
    // Создаём потокобезопасную очередь для целых чисел
    ThreadSafeQueue<int> queue;

    // Константы
    const int produce_count = 100;    // Количество элементов для генерации
    const int num_consumers = 3;      // Количество потребителей

    // Создаём поток-производитель
    // std::ref передаёт ссылку на очередь (чтобы не копировать)
    std::thread prod_thread(producer, std::ref(queue), produce_count);

    // Создаём вектор для хранения потоков-потребителей
    std::vector<std::thread> consumers;
    consumers.reserve(num_consumers);  // Резервируем память для 3 потоков

    // Создаём и запускаем потоки-потребители
    for (int i = 0; i < num_consumers; ++i) {
        // Создаём поток с функцией consumer и передаём ему очередь и ID
        consumers.emplace_back(consumer, std::ref(queue), i + 1);
    }

    // Ожидаем завершения потока-производителя
    prod_thread.join();

    // Ожидаем завершения всех потоков-потребителей
    for (auto& th : consumers) {
        th.join();  // Блокирует выполнение, пока поток не завершится
    }

    return 0;  
}
