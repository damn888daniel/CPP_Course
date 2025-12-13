#include "DatabaseManager.h" // Подключение заголовочного файла класса DatabaseManager
#include <iostream> // Подключение библиотеки ввода-вывода

// Конструктор: инициализирует указатель базы данных нулем
DatabaseManager::DatabaseManager() : db(nullptr) {}

// Деструктор: закрывает соединение с базой данных, если оно открыто
DatabaseManager::~DatabaseManager() {
    if (db) { // Если указатель на БД валиден
        sqlite3_close(db); // Закрываем соединение с SQLite
    }
}

// Инициализация базы данных: открытие файла и создание таблиц
bool DatabaseManager::initialize(const std::string& dbPath) {
    // Попытка открыть базу данных по указанному пути
    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc) { // Если возникла ошибка при открытии (код возврата не 0)
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl; // Вывод ошибки
        return false; // Возврат неудачи
    }
    
    // SQL-запрос для создания таблицы студентов, если она не существует
    const char* createStudents = 
        "CREATE TABLE IF NOT EXISTS students (" // Создать таблицу students, если нет
        "id INTEGER PRIMARY KEY AUTOINCREMENT, " // Поле id: первичный ключ, автоинкремент
        "name TEXT NOT NULL, " // Поле name: текст, обязательно для заполнения
        "email TEXT UNIQUE, " // Поле email: текст, должно быть уникальным
        "group_name TEXT);"; // Поле group_name: текст (название группы)
        
    // SQL-запрос для создания таблицы оценок, если она не существует
    const char* createGrades = 
        "CREATE TABLE IF NOT EXISTS grades (" // Создать таблицу grades, если нет
        "id INTEGER PRIMARY KEY AUTOINCREMENT, " // Поле id: первичный ключ, автоинкремент
        "student_id INTEGER, " // Поле student_id: внешний ключ на студента
        "subject TEXT, " // Поле subject: название предмета
        "grade INTEGER, " // Поле grade: оценка (целое число)
        "FOREIGN KEY(student_id) REFERENCES students(id) ON DELETE CASCADE);"; // Связь с таблицей students, удаление оценок при удалении студента

    char* errMsg = 0; // Переменная для хранения сообщения об ошибке SQL

    // Выполнение запроса создания таблицы студентов
    rc = sqlite3_exec(db, createStudents, 0, 0, &errMsg);
    if (rc != SQLITE_OK) { // Если выполнение не успешно
        std::cerr << "SQL error (students): " << errMsg << std::endl; // Вывод ошибки
        sqlite3_free(errMsg); // Освобождение памяти сообщения об ошибке
        return false; // Возврат неудачи
    }

    // Выполнение запроса создания таблицы оценок
    rc = sqlite3_exec(db, createGrades, 0, 0, &errMsg);
    if (rc != SQLITE_OK) { // Если выполнение не успешно
        std::cerr << "SQL error (grades): " << errMsg << std::endl; // Вывод ошибки
        sqlite3_free(errMsg); // Освобождение памяти сообщения об ошибке
        return false; // Возврат неудачи
    }
    
    // Базовая оптимизация настроек SQLite
    sqlite3_exec(db, "PRAGMA journal_mode = WAL;", 0, 0, 0); // Включение режима Write-Ahead Logging для производительности
    sqlite3_exec(db, "PRAGMA synchronous = NORMAL;", 0, 0, 0); // Установка режима синхронизации (меньше операций записи на диск)

    // Создание индексов для оптимизации часто используемых запросов (Задание 5)
    sqlite3_exec(db, "CREATE INDEX IF NOT EXISTS idx_students_email ON students(email);", 0, 0, 0); // Индекс для поиска по email
    sqlite3_exec(db, "CREATE INDEX IF NOT EXISTS idx_students_group ON students(group_name);", 0, 0, 0); // Индекс для поиска по группе
    sqlite3_exec(db, "CREATE INDEX IF NOT EXISTS idx_grades_subject ON grades(subject);", 0, 0, 0); // Индекс для поиска по предмету

    return true; // Инициализация прошла успешно
}

// Получение сырого указателя на базу данных SQLite
sqlite3* DatabaseManager::getHandle() const {
    return db; // Возврат указателя
}