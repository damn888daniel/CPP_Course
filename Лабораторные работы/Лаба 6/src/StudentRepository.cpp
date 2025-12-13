#include "StudentRepository.h" // Подключение заголовочного файла репозитория
#include "InputValidator.h" // Подключение валидатора
#include <iostream> // Ввод-вывод
#include <stdexcept> // Стандартные исключения

// Конструктор: сохраняет указатель на базу данных
StudentRepository::StudentRepository(sqlite3* database) : db(database) {}

// Метод добавления студента
bool StudentRepository::addStudent(const std::string& name, const std::string& email, const std::string& group) {
    // Валидация входных данных перед выполнением запроса
    if (!InputValidator::isValidNameLength(name)) {
        throw std::invalid_argument("Имя должно быть от 2 до 100 символов");
    }
    if (!InputValidator::isValidEmail(email)) {
        throw std::invalid_argument("Неверный формат email");
    }
    if (!InputValidator::isValidGroupName(group)) {
        throw std::invalid_argument("Неверный формат группы (требуется XX-YYY)");
    }
    if (!InputValidator::isSafeInput(name)) { // Проверка на SQL-инъекции
        throw std::invalid_argument("Обнаружена потенциальная SQL-инъекция в имени");
    }
    
    // SQL-запрос с параметрами (знаками вопроса) для безопасности
    const char* sql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt; // Указатель на подготовленное выражение
    
    // Подготовка запроса
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) { // Если ошибка подготовки
        std::cerr << "Ошибка подготовки запроса: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    
    // Привязка значений к параметрам запроса (binding)
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);  // 1-й параметр: имя
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);  // 2-й параметр: email
    sqlite3_bind_text(stmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);  // 3-й параметр: группа
    
    // Выполнение запроса (шаг)
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt); // Освобождение ресурсов выражения
    
    if (rc != SQLITE_DONE) { // Если выполнение не завершено успешно
        std::cerr << "Ошибка добавления студента: " << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    return true; // Успех
}

// Метод получения студента по ID
std::optional<Student> StudentRepository::getStudent(int id) {
    const char* sql = "SELECT id, name, email, group_name FROM students WHERE id = ?;";
    sqlite3_stmt* stmt;
    
    // Подготовка запроса
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return std::nullopt; // Возврат "пустого значения", если ошибка
    }
    
    sqlite3_bind_int(stmt, 1, id); // Привязка ID к параметру
    
    rc = sqlite3_step(stmt); // Выполнение
    if (rc == SQLITE_ROW) { // Если найдена строка
        Student student;
        // Извлечение данных из колонок результата
        student.id = sqlite3_column_int(stmt, 0); // 0-я колонка: id
        student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1)); // 1-я: name
        student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2)); // 2-я: email
        student.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3)); // 3-я: group
        sqlite3_finalize(stmt); // Очистка
        return student; // Возврат найденного студента
    }
    sqlite3_finalize(stmt); // Очистка, если не найдено
    return std::nullopt; // Студент не найден
}

// Метод обновления данных студента
bool StudentRepository::updateStudent(int id, const std::string& name, const std::string& email, const std::string& group) {
    // Валидация новых данных
    if (!InputValidator::isValidNameLength(name)) {
        throw std::invalid_argument("Имя должно быть от 2 до 100 символов");
    }
    if (!InputValidator::isValidEmail(email)) {
        throw std::invalid_argument("Неверный формат email");
    }
    if (!InputValidator::isValidGroupName(group)) {
        throw std::invalid_argument("Неверный формат группы");
    }
    
    // SQL запрос обновления
    const char* sql = "UPDATE students SET name = ?, email = ?, group_name = ? WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }
    
    // Привязка параметров
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, group.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 4, id); // ID идет последним в запросе
    
    rc = sqlite3_step(stmt); // Выполнение
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE; // Возврат true, если успешно обновлено
}

// Метод удаления студента
bool StudentRepository::deleteStudent(int id) {
    const char* sql = "DELETE FROM students WHERE id = ?;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }
    sqlite3_bind_int(stmt, 1, id); // Привязка ID
    rc = sqlite3_step(stmt); // Выполнение
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

// Метод получения списка всех студентов
std::vector<Student> StudentRepository::getAllStudents() {
    std::vector<Student> students; // Вектор для результатов
    const char* sql = "SELECT id, name, email, group_name FROM students;";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return students; // Возврат пустого списка при ошибке
    }
    
    // Цикл по всем найденным строкам
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Student student;
        student.id = sqlite3_column_int(stmt, 0);
        student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        student.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        students.push_back(student); // Добавление в вектор
    }
    sqlite3_finalize(stmt);
    return students;
}

// Метод добавления оценки
bool StudentRepository::addGrade(int studentId, const std::string& subject, int grade) {
    // Валидация оценки
    if (!InputValidator::isValidGrade(grade)) {
        throw std::invalid_argument("Оценка должна быть в диапазоне 0-100");
    }
    const char* sql = "INSERT INTO grades (student_id, subject, grade) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return false;
    }
    // Привязка параметров
    sqlite3_bind_int(stmt, 1, studentId);
    sqlite3_bind_text(stmt, 2, subject.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 3, grade);
    
    rc = sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    return rc == SQLITE_DONE;
}

// Сложная операция: добавление студента с оценками в одной транзакции
bool StudentRepository::addStudentWithGrades(const std::string& name, const std::string& email, const std::string& group, const std::vector<Grade>& grades) {
    char* errMsg = nullptr;
    
    // Начало транзакции
    int rc = sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка начала транзакции: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    // Попытка добавить студента
    if (!addStudent(name, email, group)) {
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); // Откат изменений при ошибке
        return false;
    }
    
    // Получение ID только что добавленного студента
    int studentId = sqlite3_last_insert_rowid(db);
    
    // Добавление всех оценок
    for (const auto& grade : grades) {
        if (!addGrade(studentId, grade.subject, grade.grade)) {
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); // Откат, если хоть одна оценка не добавилась
            return false;
        }
    }
    
    // Фиксация транзакции (сохранение всех изменений)
    rc = sqlite3_exec(db, "COMMIT;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка фиксации транзакции: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); // Откат при ошибке коммита
        return false;
    }
    return true; // Успех всей операции
}

// Поиск студентов по группе
std::vector<Student> StudentRepository::getStudentsByGroup(const std::string& groupName) {
    std::vector<Student> students;
    const char* sql = "SELECT id, name, email, group_name FROM students WHERE group_name = ?;";
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return students;
    }
    
    sqlite3_bind_text(stmt, 1, groupName.c_str(), -1, SQLITE_TRANSIENT);
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        Student student;
        student.id = sqlite3_column_int(stmt, 0);
        student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        student.email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        student.groupName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        students.push_back(student);
    }
    sqlite3_finalize(stmt);
    return students;
}

// Получение среднего балла по предмету (агрегирующая функция SQL)
double StudentRepository::getAverageGradeBySubject(const std::string& subject) {
    const char* sql = "SELECT AVG(grade) FROM grades WHERE subject = ?;"; // SQL функция AVG
    sqlite3_stmt* stmt;
    
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return 0.0;
    }
    
    sqlite3_bind_text(stmt, 1, subject.c_str(), -1, SQLITE_TRANSIENT);
    
    double average = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        average = sqlite3_column_double(stmt, 0); // Получение результата вычисления
    }
    sqlite3_finalize(stmt);
    return average;
}

// Сложный запрос с JOIN и группировкой
std::vector<StudentWithAvg> StudentRepository::getTopStudents(int limit) {
    std::vector<StudentWithAvg> topStudents;
    const char* sql =
        "SELECT s.id, s.name, AVG(g.grade) as avg_grade " // Выбрать ID, имя и средний балл
        "FROM students s "
        "JOIN grades g ON s.id = g.student_id " // Объединение таблиц
        "GROUP BY s.id " // Группировка по студенту
        "ORDER BY avg_grade DESC " // Сортировка по убыванию оценки
        "LIMIT ?;"; // Ограничение количества результатов
        
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        return topStudents;
    }
    
    sqlite3_bind_int(stmt, 1, limit); // Привязка лимита
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        StudentWithAvg student;
        student.id = sqlite3_column_int(stmt, 0);
        student.name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        student.avgGrade = sqlite3_column_double(stmt, 2); // 3-я колонка: средний балл
        topStudents.push_back(student);
    }
    sqlite3_finalize(stmt);
    return topStudents;
}

// Пакетная вставка для оптимизации
bool StudentRepository::batchInsertStudents(const std::vector<Student>& students) {
    char* errMsg = nullptr;
    
    // Все вставки выполняются в одной транзакции для скорости
    int rc = sqlite3_exec(db, "BEGIN TRANSACTION;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка начала транзакции: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    
    const char* sql = "INSERT INTO students (name, email, group_name) VALUES (?, ?, ?);";
    sqlite3_stmt* stmt;
    
    // Подготавливаем запрос один раз вне цикла
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr);
        return false;
    }
    
    // Цикл по всем студентам
    for (const auto& student : students) {
        // Привязка параметров для текущего студента
        sqlite3_bind_text(stmt, 1, student.name.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 2, student.email.c_str(), -1, SQLITE_TRANSIENT);
        sqlite3_bind_text(stmt, 3, student.groupName.c_str(), -1, SQLITE_TRANSIENT);
        
        rc = sqlite3_step(stmt); // Выполнение
        
        if (rc != SQLITE_DONE) {
            sqlite3_finalize(stmt);
            sqlite3_exec(db, "ROLLBACK;", nullptr, nullptr, nullptr); // Откат всей пачки при ошибке
            return false;
        }
        sqlite3_reset(stmt); // Сброс выражения для следующей итерации (но сохранение компиляции)
    }
    
    sqlite3_finalize(stmt);
    
    // Фиксация всей пачки
    rc = sqlite3_exec(db, "COMMIT;", nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "Ошибка фиксации: " << errMsg << std::endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}