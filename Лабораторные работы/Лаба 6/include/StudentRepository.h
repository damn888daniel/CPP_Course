#ifndef STUDENT_REPOSITORY_H // Защита от повторного включения
#define STUDENT_REPOSITORY_H // Определение макроса

#include <sqlite3.h> // Библиотека SQLite
#include <string> // Строки
#include <vector> // Векторы (динамические массивы)
#include <optional> // std::optional для возможного отсутствия значения

// Структура, описывающая студента
struct Student {
    int id; // Уникальный идентификатор
    std::string name; // Имя студента
    std::string email; // Email студента
    std::string groupName; // Группа студента
};

// Структура для оценки
struct Grade {
    std::string subject; // Предмет
    int grade; // Оценка
};

// Структура для студента со средним баллом (для отчетов)
struct StudentWithAvg {
    int id; // ID студента
    std::string name; // Имя
    double avgGrade; // Средний балл
};

// Класс Репозиторий для работы с сущностями Студент в БД
class StudentRepository {
public:
    // Конструктор, принимающий подключение к БД (explicit запрещает неявное преобразование)
    explicit StudentRepository(sqlite3* database);
    
    // CRUD операции:
    // Добавить студента
    bool addStudent(const std::string& name, const std::string& email, const std::string& group);
    // Получить студента по ID (возвращает optional, т.к. студента может не быть)
    std::optional<Student> getStudent(int id);
    // Обновить данные студента
    bool updateStudent(int id, const std::string& name, const std::string& email, const std::string& group);
    // Удалить студента
    bool deleteStudent(int id);
    // Получить список всех студентов
    std::vector<Student> getAllStudents();
    
    // Операции с оценками:
    // Добавить оценку студенту
    bool addGrade(int studentId, const std::string& subject, int grade);
    // Добавить студента сразу с оценками (транзакция)
    bool addStudentWithGrades(const std::string& name, const std::string& email, const std::string& group, const std::vector<Grade>& grades);
    
    // Статистические запросы:
    // Найти всех студентов определенной группы
    std::vector<Student> getStudentsByGroup(const std::string& groupName);
    // Вычислить среднюю оценку по предмету
    double getAverageGradeBySubject(const std::string& subject);
    // Получить топ студентов по среднему баллу
    std::vector<StudentWithAvg> getTopStudents(int limit);
    
    // Оптимизация:
    // Пакетная вставка множества студентов (для быстродействия)
    bool batchInsertStudents(const std::vector<Student>& students);

private:
    sqlite3* db; // Указатель на подключение к базе данных
};

#endif // Конец защиты