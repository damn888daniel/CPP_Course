#ifndef DATABASE_MANAGER_H // Защита от повторного включения заголовочного файла
#define DATABASE_MANAGER_H // Определение макроса для защиты

#include <sqlite3.h> // Подключение библиотеки SQLite3 для работы с базой данных
#include <string> // Подключение стандартной библиотеки строк

// Класс для управления подключением к базе данных
class DatabaseManager {
public:
    DatabaseManager(); // Конструктор класса
    ~DatabaseManager(); // Деструктор класса для очистки ресурсов

    // Метод инициализации базы данных (открытие и создание таблиц)
    // Принимает путь к файлу базы данных
    bool initialize(const std::string& dbPath);

    // Геттер для получения указателя на объект базы данных SQLite
    sqlite3* getHandle() const;

private:
    sqlite3* db; // Указатель на структуру базы данных SQLite
};

#endif // Конец защиты от повторного включения