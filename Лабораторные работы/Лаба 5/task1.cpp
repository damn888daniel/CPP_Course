// Подключаем необходимые библиотеки
#include <iostream>    // Для ввода-вывода (std::cout)
#include <vector>      // Для работы с динамическими массивами (std::vector)
#include <thread>      // Для работы с потоками (std::thread)
#include <mutex>       // Для работы с мьютексами (std::mutex)
#include <chrono>      // Для измерения времени (std::chrono)
#include <random>      // Для генерации случайных чисел (std::random_device)

// Класс для вычисления суммы элементов вектора
class VectorSumCalculator {
private:
    std::vector<int> data;  // Вектор данных (массив целых чисел)
    std::mutex sum_mutex;   // Мьютекс для защиты общей переменной sum при многопоточности

public:
    // Конструктор: создаёт вектор указанного размера и заполняет его случайными числами
    VectorSumCalculator(size_t size) {
        data.reserve(size);  // Резервируем память для size элементов (оптимизация)

        // Инициализируем генератор случайных чисел
        std::random_device rd;  // Источник случайности (hardware random)
        std::mt19937 gen(rd()); // Генератор Mersenne Twister с начальным значением от rd
        std::uniform_int_distribution<int> dist(1, 100);  // Равномерное распределение от 1 до 100

        // Заполняем вектор случайными числами
        for (size_t i = 0; i < size; ++i) {
            data.push_back(dist(gen));  // Добавляем случайное число в вектор
        }
    }

    // Однопоточное вычисление суммы (последовательное)
    long long calculateSingleThreaded() {
        long long sum = 0;  // Переменная для накопления суммы (long long для больших чисел)

        // Проходим по всем элементам вектора
        for (int value : data) {
            sum += value;  // Добавляем каждый элемент к сумме
        }

        return sum;  // Возвращаем итоговую сумму
    }

    // Многопоточное вычисление суммы
    // num_threads - количество потоков для распараллеливания
    long long calculateMultiThreaded(int num_threads) {
        long long total_sum = 0;  // Общая сумма (защищена мьютексом)
        size_t n = data.size();   // Размер вектора

        // Вычисляем размер блока для каждого потока
        size_t chunk_size = n / num_threads;  // Базовый размер блока
        size_t remainder = n % num_threads;   // Остаток (для равномерного распределения)

        std::vector<std::thread> threads;  // Вектор для хранения потоков
        threads.reserve(num_threads);      // Резервируем память для потоков

        // Лямбда-функция: задача для каждого потока
        // Вычисляет сумму элементов вектора от start до end
        auto worker = [this, &total_sum](size_t start, size_t end) {
            long long local_sum = 0;  // Локальная сумма (у каждого потока своя)

            // Суммируем элементы в заданном диапазоне
            for (size_t i = start; i < end; ++i) {
                local_sum += data[i];
            }

            // Критическая секция: добавляем локальную сумму к общей
            {
                std::lock_guard<std::mutex> lock(sum_mutex);  // Захватываем мьютекс
                total_sum += local_sum;  // Добавляем локальную сумму к общей
            }  // Мьютекс автоматически освобождается при выходе из блока
        };

        // Создаём и запускаем потоки
        size_t current_start = 0;  // Начальная позиция для текущего потока
        for (int t = 0; t < num_threads; ++t) {
            // Вычисляем размер блока для текущего потока
            // Первые remainder потоков получают на 1 элемент больше
            size_t current_chunk = chunk_size + (t < (int)remainder ? 1 : 0);
            size_t current_end = current_start + current_chunk;  // Конечная позиция

            // Создаём поток и передаём ему функцию worker с параметрами
            threads.emplace_back(worker, current_start, current_end);

            current_start = current_end;  // Обновляем начальную позицию для следующего потока
        }

        // Ожидаем завершения всех потоков
        for (auto &th : threads) {
            th.join();  // Блокирует выполнение, пока поток не завершится
        }

        return total_sum;  // Возвращаем общую сумму
    }
};

// Главная функция программы
int main() {
    // Константы
    const size_t vector_size = 10000000;  // Размер вектора: 10 миллионов элементов
    const int num_threads = 4;            // Количество потоков для многопоточного вычисления

    // Создаём объект калькулятора и заполняем вектор случайными числами
    VectorSumCalculator calculator(vector_size);

    // === Однопоточное вычисление ===
    auto start_single = std::chrono::steady_clock::now();  // Засекаем время начала
    long long single_sum = calculator.calculateSingleThreaded();  // Вычисляем сумму
    auto end_single = std::chrono::steady_clock::now();    // Засекаем время окончания
    // Вычисляем длительность в миллисекундах
    auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);

    // === Многопоточное вычисление ===
    auto start_multi = std::chrono::steady_clock::now();   // Засекаем время начала
    long long multi_sum = calculator.calculateMultiThreaded(num_threads);  // Вычисляем сумму
    auto end_multi = std::chrono::steady_clock::now();     // Засекаем время окончания
    // Вычисляем длительность в миллисекундах
    auto duration_multi = std::chrono::duration_cast<std::chrono::milliseconds>(end_multi - start_multi);

    // Выводим результаты
    std::cout << "Однопоточная сумма: " << single_sum << std::endl;
    std::cout << "Многопоточная сумма: " << multi_sum << std::endl;
    std::cout << "Время однопоточного вычисления (мс): " << duration_single.count() << std::endl;
    std::cout << "Время многопоточного вычисления (мс): " << duration_multi.count() << std::endl;

    return 0;  
}
