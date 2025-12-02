// Подключаем необходимые библиотеки
#include <iostream>    // Для ввода-вывода (std::cout)
#include <vector>      // Для работы с динамическими массивами (std::vector)
#include <thread>      // Для работы с потоками (std::thread)
#include <random>      // Для генерации случайных чисел (std::random_device)
#include <chrono>      // Для измерения времени (std::chrono)

// Класс для обработки изображений
class ImageProcessor {
private:
    std::vector<std::vector<int>> image;  // Двумерный вектор - матрица изображения (вектор строк, где каждая строка - вектор пикселей)
    int width;   // Ширина изображения в пикселях
    int height;  // Высота изображения в пикселях

public:
    // Конструктор: создаёт изображение заданного размера и заполняет случайными значениями яркости
    // w - ширина, h - высота
    ImageProcessor(int w, int h) : width(w), height(h) {
        // Инициализируем матрицу: height строк, каждая содержит width нулей
        image.assign(height, std::vector<int>(width, 0));
        
        // Инициализируем генератор случайных чисел
        std::random_device rd;  // Источник случайности (hardware random)
        std::mt19937 gen(rd()); // Генератор Mersenne Twister с начальным значением от rd
        std::uniform_int_distribution<int> dist(0, 255);  // Равномерное распределение от 0 до 255 (значения яркости пикселя)
        
        // Заполняем матрицу случайными значениями яркости
        for (int y = 0; y < height; ++y) {      // Проходим по всем строкам (координата y)
            for (int x = 0; x < width; ++x) {   // Проходим по всем столбцам (координата x)
                image[y][x] = dist(gen);        // Генерируем случайное значение яркости от 0 до 255
            }
        }
    }

    // Метод для вычисления размытого значения одного пикселя
    // Размытие = среднее значение яркости пикселя и его соседей (окно 3x3)
    // x, y - координаты пикселя
    // src - исходное изображение (константная ссылка, чтобы не копировать)
    // Возвращает новое значение яркости для пикселя
    int blurPixel(int x, int y, const std::vector<std::vector<int>>& src) const {
        int sum = 0;    // Сумма яркостей всех соседних пикселей (включая центральный)
        int count = 0;  // Количество пикселей, участвующих в вычислении
        
        // Проходим по окну 3x3 вокруг пикселя (x, y)
        for (int dy = -1; dy <= 1; ++dy) {      // dy: -1, 0, 1 (смещение по вертикали)
            for (int dx = -1; dx <= 1; ++dx) {  // dx: -1, 0, 1 (смещение по горизонтали)
                int nx = x + dx;  // Новая координата x соседнего пикселя
                int ny = y + dy;  // Новая координата y соседнего пикселя
                
                // Проверяем, что сосед находится внутри границ изображения
                if (nx >= 0 && nx < width && ny >= 0 && ny < height) {
                    sum += src[ny][nx];  // Добавляем яркость соседнего пикселя к сумме
                    ++count;             // Увеличиваем счётчик пикселей
                }
            }
        }
        
        // Возвращаем среднее значение (сумма / количество)
        // Если count > 0, возвращаем среднее; иначе исходное значение пикселя
        return count > 0 ? sum / count : src[y][x];
    }

    // Однопоточная обработка изображения фильтром размытия
    void applyFilterSingleThread() {
        // Создаём копию исходного изображения (чтобы читать из неизменённых данных)
        std::vector<std::vector<int>> src = image;
        // Создаём матрицу для результата (копия исходной)
        std::vector<std::vector<int>> dst = image;
        
        // Проходим по всем пикселям изображения
        for (int y = 0; y < height; ++y) {      // Для каждой строки
            for (int x = 0; x < width; ++x) {   // Для каждого столбца
                // Вычисляем размытое значение и записываем в результат
                dst[y][x] = blurPixel(x, y, src);
            }
        }
        
        // Заменяем исходное изображение на обработанное
        // std::move - перемещаем данные, а не копируем (эффективнее)
        image = std::move(dst);
    }

    // Многопоточная обработка изображения фильтром размытия
    // num_threads - количество потоков для распараллеливания
    void applyFilterMultiThread(int num_threads) {
        // Создаём копию исходного изображения
        std::vector<std::vector<int>> src = image;
        // Создаём матрицу для результата
        std::vector<std::vector<int>> dst = image;
        
        // Вектор для хранения потоков
        std::vector<std::thread> threads;
        threads.reserve(num_threads);  // Резервируем память для num_threads потоков
        
        // Вычисляем, сколько строк обрабатывает каждый поток
        int rows_per_thread = height / num_threads;  // Базовое количество строк на поток
        int remainder = height % num_threads;         // Остаток для равномерного распределения
        
        // Лямбда-функция: рабочая функция для каждого потока
        // Обрабатывает строки изображения от start_row до end_row
        // [this, &src, &dst] - захват: this для доступа к методам, src и dst по ссылке
        auto worker = [this, &src, &dst](int start_row, int end_row) {
            // Проходим по назначенным строкам
            for (int y = start_row; y < end_row; ++y) {
                // Для каждой строки проходим по всем столбцам
                for (int x = 0; x < width; ++x) {
                    // Вычисляем размытое значение пикселя
                    dst[y][x] = blurPixel(x, y, src);
                }
            }
        };
        
        // Создаём и запускаем потоки
        int current_start = 0;  // Начальная строка для текущего потока
        for (int t = 0; t < num_threads; ++t) {
            // Вычисляем количество строк для текущего потока
            // Первые remainder потоков получают +1 строку для равномерного распределения
            int block = rows_per_thread + (t < remainder ? 1 : 0);
            int current_end = current_start + block;  // Конечная строка (не включительно)
            
            // Создаём поток и передаём ему функцию worker с параметрами
            threads.emplace_back(worker, current_start, current_end);
            
            // Сдвигаем начало для следующего потока
            current_start = current_end;
        }
        
        // Ожидаем завершения всех потоков
        for (auto& th : threads) {
            th.join();  // Блокирует выполнение, пока поток не завершится
        }
        
        // Заменяем исходное изображение на обработанное
        image = std::move(dst);
    }

    // Метод для вычисления средней яркости всего изображения
    // Используется для проверки корректности обработки
    double averageBrightness() const {
        long long sum = 0;    // Сумма яркостей всех пикселей (long long для больших чисел)
        long long count = 0;  // Количество пикселей
        
        // Проходим по всем пикселям
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                sum += image[y][x];  // Добавляем яркость пикселя к сумме
                ++count;             // Увеличиваем счётчик
            }
        }
        
        // Возвращаем среднее значение (преобразуем к double для точности)
        return count > 0 ? static_cast<double>(sum) / count : 0.0;
    }
};

// Главная функция программы
int main() {
    // Константы
    const int width = 1000;       // Ширина изображения: 1000 пикселей
    const int height = 1000;      // Высота изображения: 1000 пикселей
    const int num_threads = 4;    // Количество потоков для многопоточной обработки

    // === Однопоточная обработка ===
    
    // Создаём процессор изображений с размером 1000x1000
    ImageProcessor processor(width, height);
    
    // Вычисляем среднюю яркость исходного изображения (до обработки)
    double initial_avg = processor.averageBrightness();
    
    // Засекаем время начала однопоточной обработки
    auto start_single = std::chrono::steady_clock::now();
    
    // Применяем фильтр размытия однопоточно
    processor.applyFilterSingleThread();
    
    // Засекаем время окончания обработки
    auto end_single = std::chrono::steady_clock::now();
    
    // Вычисляем длительность в миллисекундах
    auto duration_single = std::chrono::duration_cast<std::chrono::milliseconds>(end_single - start_single);
    
    // Вычисляем среднюю яркость после однопоточной обработки
    double single_avg = processor.averageBrightness();

    // === Многопоточная обработка ===
    
    // Создаём НОВЫЙ процессор с тем же размером (для честного сравнения)
    ImageProcessor processor_multi(width, height);
    
    // Засекаем время начала многопоточной обработки
    auto start_multi = std::chrono::steady_clock::now();
    
    // Применяем фильтр размытия многопоточно (4 потока)
    processor_multi.applyFilterMultiThread(num_threads);
    
    // Засекаем время окончания обработки
    auto end_multi = std::chrono::steady_clock::now();
    
    // Вычисляем длительность в миллисекундах
    auto duration_multi = std::chrono::duration_cast<std::chrono::milliseconds>(end_multi - start_multi);
    
    // Вычисляем среднюю яркость после многопоточной обработки
    double multi_avg = processor_multi.averageBrightness();

    // === Вывод результатов ===
    
    std::cout << "Исходная средняя яркость: " << initial_avg << std::endl;
    std::cout << "Средняя яркость (однопоточно): " << single_avg << std::endl;
    std::cout << "Средняя яркость (многопоточно): " << multi_avg << std::endl;
    std::cout << "Время однопоточной обработки (мс): " << duration_single.count() << std::endl;
    std::cout << "Время многопоточной обработки (мс): " << duration_multi.count() << std::endl;

    return 0;  
}
