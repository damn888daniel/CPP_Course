// Подключаем необходимые библиотеки
#include <iostream>    // Для ввода-вывода (std::cout)
#include <future>      // Для асинхронного программирования (std::async, std::future)
#include <random>      // Для генерации случайных чисел (std::random_device)
#include <vector>      // Для работы с динамическими массивами (std::vector)
#include <chrono>      // Для измерения времени (std::chrono)
#include <exception>   // Для обработки исключений (std::exception)

// Класс для вычисления числа π методом Монте-Карло
class PiCalculator {
public:
    // Метод для вычисления приближения π на основе заданного количества точек
    // total_points - количество случайных точек для генерации
    // Возвращает приближённое значение π
    double calculatePiPortion(int total_points) {
        // Инициализируем генератор случайных чисел
        std::random_device rd;  // Источник случайности (hardware random)
        std::mt19937 gen(rd()); // Генератор Mersenne Twister с начальным значением от rd
        // Равномерное распределение вещественных чисел от 0.0 до 1.0
        std::uniform_real_distribution<double> dist(0.0, 1.0);
        
        int inside = 0;  // Счётчик точек, попавших внутрь четверти круга
        
        // Генерируем total_points случайных точек
        for (int i = 0; i < total_points; ++i) {
            double x = dist(gen);  // Случайная координата x в диапазоне [0, 1]
            double y = dist(gen);  // Случайная координата y в диапазоне [0, 1]
            
            // Проверяем, попала ли точка (x, y) в четверть круга единичного радиуса
            // Уравнение круга: x² + y² ≤ r²
            // У нас r = 1, поэтому: x² + y² ≤ 1
            if (x * x + y * y <= 1.0) {
                ++inside;  // Точка внутри круга - увеличиваем счётчик
            }
        }
        
        // Вычисляем π по формуле Монте-Карло:
        // Площадь четверти круга / Площадь квадрата = (π·r²/4) / r² = π/4
        // Отношение точек внутри круга к общему числу ≈ π/4
        // Следовательно: π ≈ 4 × (точек внутри / всего точек)
        return 4.0 * static_cast<double>(inside) / static_cast<double>(total_points);
    }

    // Параллельное вычисление π с использованием нескольких асинхронных задач
    // total_points - общее количество точек для генерации
    // num_tasks - количество параллельных задач
    // Возвращает усреднённое приближение π из всех задач
    double calculatePiParallel(int total_points, int num_tasks) {
        // Проверяем корректность параметров
        if (num_tasks <= 0) {
            // Если количество задач некорректно, выбрасываем исключение
            throw std::invalid_argument("Количество задач должно быть положительным");
        }
        
        // Вектор для хранения future-объектов (будущих результатов)
        std::vector<std::future<double>> futures;
        futures.reserve(num_tasks);  // Резервируем память для num_tasks элементов
        
        // Распределяем точки между задачами
        int points_per_task = total_points / num_tasks;  // Базовое количество точек на задачу
        int remainder = total_points % num_tasks;         // Остаток для равномерного распределения
        
        // Создаём и запускаем асинхронные задачи
        for (int i = 0; i < num_tasks; ++i) {
            // Вычисляем количество точек для текущей задачи
            // Первые remainder задач получают +1 точку
            int current_points = points_per_task + (i < remainder ? 1 : 0);
            
            // Запускаем асинхронную задачу с помощью std::async
            // std::launch::async - гарантирует выполнение в ОТДЕЛЬНОМ потоке
            // &PiCalculator::calculatePiPortion - указатель на метод класса
            // this - указатель на текущий объект (для вызова метода)
            // current_points - аргумент метода
            // Возвращает std::future<double> - объект для получения результата в будущем
            futures.emplace_back(std::async(std::launch::async, 
                                           &PiCalculator::calculatePiPortion, 
                                           this, 
                                           current_points));
        }
        
        double sum_pi = 0.0;  // Сумма всех приближений π
        
        // Собираем результаты из всех асинхронных задач
        for (auto& fut : futures) {
            try {
                // fut.get() - БЛОКИРУЕТ выполнение до готовности результата
                // Возвращает значение double, вычисленное в асинхронной задаче
                // Можно вызвать ТОЛЬКО ОДИН РАЗ для каждого future
                double portion = fut.get();
                
                // Добавляем результат к общей сумме
                sum_pi += portion;
            } catch (const std::exception& e) {
                // Если в асинхронной задаче произошло исключение,
                // fut.get() пробросит его сюда
                std::cerr << "Ошибка в асинхронной задаче: " << e.what() << std::endl;
            }
        }
        
        // Возвращаем среднее значение π из всех задач
        // Проверяем num_tasks > 0 для избежания деления на ноль
        return num_tasks > 0 ? sum_pi / static_cast<double>(num_tasks) : 0.0;
    }
};

// Главная функция программы
int main() {
    // Константы
    const int total_points = 1000000;  // Общее количество случайных точек: 1 миллион
    const int num_tasks = 8;           // Количество параллельных задач: 8
    
    // Создаём объект калькулятора π
    PiCalculator calculator;

    // === Последовательное вычисление π ===
    
    // Засекаем время начала последовательного вычисления
    auto start_single = std::chrono::steady_clock::now();
    
    // Вычисляем π последовательно (в одном потоке)
    double pi_single = calculator.calculatePiPortion(total_points);
    
    // Засекаем время окончания вычисления
    auto end_single = std::chrono::steady_clock::now();
    
    // Вычисляем длительность в миллисекундах
    auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);

    // === Параллельное вычисление π ===
    
    // Засекаем время начала параллельного вычисления
    auto start_parallel = std::chrono::steady_clock::now();
    
    // Вычисляем π параллельно (8 асинхронных задач)
    double pi_parallel = calculator.calculatePiParallel(total_points, num_tasks);
    
    // Засекаем время окончания вычисления
    auto end_parallel = std::chrono::steady_clock::now();
    
    // Вычисляем длительность в миллисекундах
    auto duration_parallel = std::chrono::duration_cast<std::chrono::milliseconds>(end_parallel - start_parallel);

    // === Вывод результатов ===
    
    std::cout << "Последовательное вычисление π: " << pi_single << std::endl;
    std::cout << "Параллельное вычисление π: " << pi_parallel << std::endl;
    std::cout << "Время последовательного вычисления (мс): " << duration_single.count() << std::endl;
    std::cout << "Время параллельного вычисления (мс): " << duration_parallel.count() << std::endl;
    
    // Примечание: истинное значение π ≈ 3.14159265359
    // Точность увеличивается с ростом количества точек

    return 0;  
}
