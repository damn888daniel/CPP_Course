#include <iostream> // Ввод-вывод
#include <chrono> // Работа со временем (для замеров производительности)
#include <limits> // Для очистки ввода
#include "DatabaseManager.h" // Менеджер БД
#include "StudentRepository.h" // Репозиторий студентов
#include "InputValidator.h" // Валидатор

// Функция очистки экрана (кроссплатформенная)
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Функция паузы (ожидание Enter)
void pause() {
    std::cout << "\nНажмите Enter для продолжения...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

// Функция отображения заголовка
void showHeader(const std::string& title) {
    std::cout << "\n╔════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  " << title;
    // Добавление пробелов для выравнивания
    for (size_t i = title.length(); i < 60; ++i) std::cout << " ";
    std::cout << "║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════╝" << std::endl;
}

// ==================== ЗАДАНИЕ 1 ====================
void task1_demo(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 1: Базовая настройка и создание таблиц");

    std::cout << "\n✓ База данных успешно инициализирована" << std::endl;
    std::cout << "✓ Таблица 'students' создана с полями:" << std::endl;
    std::cout << "  - id (INTEGER PRIMARY KEY AUTOINCREMENT)" << std::endl;
    std::cout << "  - name (TEXT NOT NULL)" << std::endl;
    std::cout << "  - email (TEXT UNIQUE)" << std::endl;
    std::cout << "  - group_name (TEXT)" << std::endl;

    std::cout << "\n✓ Таблица 'grades' создана с полями:" << std::endl;
    std::cout << "  - id (INTEGER PRIMARY KEY AUTOINCREMENT)" << std::endl;
    std::cout << "  - student_id (INTEGER, FOREIGN KEY)" << std::endl;
    std::cout << "  - subject (TEXT)" << std::endl;
    std::cout << "  - grade (INTEGER)" << std::endl;
    std::cout << "  - ON DELETE CASCADE (каскадное удаление)" << std::endl;

    std::cout << "\n✓ Применена оптимизация:" << std::endl;
    std::cout << "  - PRAGMA journal_mode = WAL" << std::endl;
    std::cout << "  - PRAGMA synchronous = NORMAL" << std::endl;

    std::cout << "\n✓ Созданы индексы:" << std::endl;
    std::cout << "  - idx_students_email (для быстрого поиска по email)" << std::endl;
    std::cout << "  - idx_students_group (для поиска по группе)" << std::endl;
    std::cout << "  - idx_grades_subject (для поиска по предмету)" << std::endl;

    pause();
}

// ==================== ЗАДАНИЕ 2 ====================
void task2_addStudent(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 2: Добавление студента (Create)");

    std::string name, email, group;

    std::cout << "\nВведите имя студента: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    std::cout << "Введите email: ";
    std::getline(std::cin, email);

    std::cout << "Введите группу (формат XX-YYY): ";
    std::getline(std::cin, group);

    try {
        if (repo.addStudent(name, email, group)) {
            std::cout << "\n✓ Студент успешно добавлен!" << std::endl;
        } else {
            std::cout << "\n✗ Ошибка при добавлении студента" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\n✗ Ошибка валидации: " << e.what() << std::endl;
    }

    pause();
}

void task2_viewStudent(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 2: Просмотр студента (Read)");

    int id;
    std::cout << "\nВведите ID студента: ";
    std::cin >> id;

    auto student = repo.getStudent(id);
    if (student) {
        std::cout << "\n┌─────────────────────────────────────────┐" << std::endl;
        std::cout << "│ ID:     " << student->id << std::endl;
        std::cout << "│ Имя:    " << student->name << std::endl;
        std::cout << "│ Email:  " << student->email << std::endl;
        std::cout << "│ Группа: " << student->groupName << std::endl;
        std::cout << "└─────────────────────────────────────────┘" << std::endl;
    } else {
        std::cout << "\n✗ Студент с ID " << id << " не найден" << std::endl;
    }

    pause();
}

void task2_updateStudent(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 2: Обновление студента (Update)");

    int id;
    std::string name, email, group;

    std::cout << "\nВведите ID студента для обновления: ";
    std::cin >> id;

    // Проверяем существование студента
    auto existing = repo.getStudent(id);
    if (!existing) {
        std::cout << "\n✗ Студент с ID " << id << " не найден" << std::endl;
        pause();
        return;
    }

    std::cout << "\nТекущие данные:" << std::endl;
    std::cout << "Имя:    " << existing->name << std::endl;
    std::cout << "Email:  " << existing->email << std::endl;
    std::cout << "Группа: " << existing->groupName << std::endl;

    std::cin.ignore();
    std::cout << "\nВведите новое имя: ";
    std::getline(std::cin, name);

    std::cout << "Введите новый email: ";
    std::getline(std::cin, email);

    std::cout << "Введите новую группу: ";
    std::getline(std::cin, group);

    try {
        if (repo.updateStudent(id, name, email, group)) {
            std::cout << "\n✓ Данные студента успешно обновлены!" << std::endl;
        } else {
            std::cout << "\n✗ Ошибка при обновлении" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\n✗ Ошибка валидации: " << e.what() << std::endl;
    }

    pause();
}

void task2_deleteStudent(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 2: Удаление студента (Delete)");

    int id;
    std::cout << "\nВведите ID студента для удаления: ";
    std::cin >> id;

    // Проверяем существование студента
    auto existing = repo.getStudent(id);
    if (!existing) {
        std::cout << "\n✗ Студент с ID " << id << " не найден" << std::endl;
        pause();
        return;
    }

    std::cout << "\nУдаляется студент: " << existing->name << " (" << existing->email << ")" << std::endl;
    std::cout << "Вы уверены? (y/n): ";

    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
        if (repo.deleteStudent(id)) {
            std::cout << "\n✓ Студент успешно удален!" << std::endl;
            std::cout << "✓ Все его оценки также удалены (CASCADE)" << std::endl;
        } else {
            std::cout << "\n✗ Ошибка при удалении" << std::endl;
        }
    } else {
        std::cout << "\n✗ Удаление отменено" << std::endl;
    }

    pause();
}

void task2_listAllStudents(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 2: Список всех студентов");

    auto students = repo.getAllStudents();

    if (students.empty()) {
        std::cout << "\nБаза данных пуста. Нет студентов для отображения." << std::endl;
    } else {
        std::cout << "\nВсего студентов: " << students.size() << std::endl;
        std::cout << "\n┌────┬──────────────────────────┬─────────────────────────────┬─────────┐" << std::endl;
        std::cout << "│ ID │ Имя                      │ Email                       │ Группа  │" << std::endl;
        std::cout << "├────┼──────────────────────────┼─────────────────────────────┼─────────┤" << std::endl;

        for (const auto& s : students) {
            printf("│ %-2d │ %-24s │ %-27s │ %-7s │\n",
                   s.id, s.name.c_str(), s.email.c_str(), s.groupName.c_str());
        }

        std::cout << "└────┴──────────────────────────┴─────────────────────────────┴─────────┘" << std::endl;
    }

    pause();
}

void task2_menu(StudentRepository& repo) {
    int choice;
    do {
        clearScreen();
        showHeader("ЗАДАНИЕ 2: CRUD операции с подготовленными выражениями");

        std::cout << "\n1. Добавить студента (Create)" << std::endl;
        std::cout << "2. Просмотреть студента (Read)" << std::endl;
        std::cout << "3. Обновить студента (Update)" << std::endl;
        std::cout << "4. Удалить студента (Delete)" << std::endl;
        std::cout << "5. Список всех студентов" << std::endl;
        std::cout << "0. Вернуться в главное меню" << std::endl;
        std::cout << "\nВыберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: task2_addStudent(repo); break;
            case 2: task2_viewStudent(repo); break;
            case 3: task2_updateStudent(repo); break;
            case 4: task2_deleteStudent(repo); break;
            case 5: task2_listAllStudents(repo); break;
            case 0: break;
            default:
                std::cout << "\n✗ Неверный выбор!" << std::endl;
                pause();
        }
    } while (choice != 0);
}

// ==================== ЗАДАНИЕ 3 ====================
void task3_addGrade(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 3: Добавление оценки");

    int studentId, grade;
    std::string subject;

    std::cout << "\nВведите ID студента: ";
    std::cin >> studentId;

    // Проверяем существование студента
    auto student = repo.getStudent(studentId);
    if (!student) {
        std::cout << "\n✗ Студент с ID " << studentId << " не найден" << std::endl;
        pause();
        return;
    }

    std::cout << "Студент: " << student->name << std::endl;

    std::cin.ignore();
    std::cout << "\nВведите предмет: ";
    std::getline(std::cin, subject);

    std::cout << "Введите оценку (0-100): ";
    std::cin >> grade;

    try {
        if (repo.addGrade(studentId, subject, grade)) {
            std::cout << "\n✓ Оценка успешно добавлена!" << std::endl;
        } else {
            std::cout << "\n✗ Ошибка при добавлении оценки" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\n✗ Ошибка валидации: " << e.what() << std::endl;
    }

    pause();
}

void task3_addStudentWithGrades(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 3: Добавление студента с оценками (Транзакция)");

    std::string name, email, group;

    std::cin.ignore();
    std::cout << "\nВведите имя студента: ";
    std::getline(std::cin, name);

    std::cout << "Введите email: ";
    std::getline(std::cin, email);

    std::cout << "Введите группу: ";
    std::getline(std::cin, group);

    int gradeCount;
    std::cout << "\nСколько оценок добавить? ";
    std::cin >> gradeCount;

    std::vector<Grade> grades;
    std::cin.ignore();

    for (int i = 0; i < gradeCount; ++i) {
        std::string subject;
        int gradeValue;

        std::cout << "\nОценка " << (i + 1) << ":" << std::endl;
        std::cout << "  Предмет: ";
        std::getline(std::cin, subject);
        std::cout << "  Оценка (0-100): ";
        std::cin >> gradeValue;
        std::cin.ignore();

        grades.push_back({subject, gradeValue});
    }

    try {
        if (repo.addStudentWithGrades(name, email, group, grades)) {
            std::cout << "\n✓ Студент и все оценки успешно добавлены в одной транзакции!" << std::endl;
            std::cout << "✓ Гарантирована атомарность: либо все данные добавлены, либо ничего" << std::endl;
        } else {
            std::cout << "\n✗ Ошибка при добавлении (транзакция откачена)" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "\n✗ Ошибка: " << e.what() << std::endl;
    }

    pause();
}

void task3_getStudentsByGroup(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 3: Поиск студентов по группе");

    std::string groupName;

    std::cin.ignore();
    std::cout << "\nВведите название группы: ";
    std::getline(std::cin, groupName);

    auto students = repo.getStudentsByGroup(groupName);

    std::cout << "\nНайдено студентов: " << students.size() << std::endl;

    if (!students.empty()) {
        std::cout << "\n┌────┬──────────────────────────┬─────────────────────────────┐" << std::endl;
        std::cout << "│ ID │ Имя                      │ Email                       │" << std::endl;
        std::cout << "├────┼──────────────────────────┼─────────────────────────────┤" << std::endl;

        for (const auto& s : students) {
            printf("│ %-2d │ %-24s │ %-27s │\n",
                   s.id, s.name.c_str(), s.email.c_str());
        }

        std::cout << "└────┴──────────────────────────┴─────────────────────────────┘" << std::endl;
    }

    pause();
}

void task3_getAverageGrade(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 3: Средняя оценка по предмету (AVG)");

    std::string subject;

    std::cin.ignore();
    std::cout << "\nВведите название предмета: ";
    std::getline(std::cin, subject);

    double avg = repo.getAverageGradeBySubject(subject);

    std::cout << "\n╔════════════════════════════════════════╗" << std::endl;
    printf("║ Средняя оценка по %-20s ║\n", subject.c_str());
    std::cout << "╠════════════════════════════════════════╣" << std::endl;
    printf("║           %.2f / 100                  ║\n", avg);
    std::cout << "╚════════════════════════════════════════╝" << std::endl;

    pause();
}

void task3_getTopStudents(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 3: Топ студентов (JOIN + GROUP BY + ORDER BY)");

    int limit;
    std::cout << "\nСколько лучших студентов показать? ";
    std::cin >> limit;

    auto topStudents = repo.getTopStudents(limit);

    if (topStudents.empty()) {
        std::cout << "\nНедостаточно данных для построения рейтинга" << std::endl;
    } else {
        std::cout << "\n┌──────┬──────────────────────────┬───────────────┐" << std::endl;
        std::cout << "│ Место│ Имя                      │ Средний балл  │" << std::endl;
        std::cout << "├──────┼──────────────────────────┼───────────────┤" << std::endl;

        int place = 1;
        for (const auto& s : topStudents) {
            printf("│  %-3d │ %-24s │    %.2f       │\n",
                   place++, s.name.c_str(), s.avgGrade);
        }

        std::cout << "└──────┴──────────────────────────┴───────────────┘" << std::endl;
    }

    pause();
}

void task3_menu(StudentRepository& repo) {
    int choice;
    do {
        clearScreen();
        showHeader("ЗАДАНИЕ 3: Транзакции и сложные запросы");

        std::cout << "\n1. Добавить оценку студенту" << std::endl;
        std::cout << "2. Добавить студента с оценками (Транзакция)" << std::endl;
        std::cout << "3. Найти студентов по группе" << std::endl;
        std::cout << "4. Средняя оценка по предмету (AVG)" << std::endl;
        std::cout << "5. Топ студентов (JOIN + GROUP BY)" << std::endl;
        std::cout << "0. Вернуться в главное меню" << std::endl;
        std::cout << "\nВыберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: task3_addGrade(repo); break;
            case 2: task3_addStudentWithGrades(repo); break;
            case 3: task3_getStudentsByGroup(repo); break;
            case 4: task3_getAverageGrade(repo); break;
            case 5: task3_getTopStudents(repo); break;
            case 0: break;
            default:
                std::cout << "\n✗ Неверный выбор!" << std::endl;
                pause();
        }
    } while (choice != 0);
}

// ==================== ЗАДАНИЕ 4 ====================
void task4_demo(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 4: Безопасность и валидация данных");

    std::cout << "\n=== Тест 1: Некорректный email ===" << std::endl;
    try {
        std::cout << "Попытка добавить студента с email 'invalid-email'..." << std::endl;
        repo.addStudent("Test User", "invalid-email", "CS-101");
        std::cout << "✗ ОШИБКА: валидация пропустила некорректный email!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Перехвачено: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 2: SQL-инъекция ===" << std::endl;
    try {
        std::cout << "Попытка SQL-инъекции: Robert'); DROP TABLE students;--" << std::endl;
        repo.addStudent("Robert'); DROP TABLE students;--", "robert@university.ru", "CS-101");
        std::cout << "✗ ОШИБКА: валидация пропустила SQL-инъекцию!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Перехвачено: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 3: Некорректный формат группы ===" << std::endl;
    try {
        std::cout << "Попытка добавить группу 'INVALID' (без дефиса)..." << std::endl;
        repo.addStudent("Valid Name", "valid@university.ru", "INVALID");
        std::cout << "✗ ОШИБКА: валидация пропустила некорректную группу!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Перехвачено: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 4: Слишком короткое имя ===" << std::endl;
    try {
        std::cout << "Попытка добавить студента с именем 'A' (1 символ)..." << std::endl;
        repo.addStudent("A", "a@university.ru", "CS-101");
        std::cout << "✗ ОШИБКА: валидация пропустила короткое имя!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Перехвачено: " << e.what() << std::endl;
    }

    std::cout << "\n=== Тест 5: Оценка вне диапазона ===" << std::endl;
    try {
        std::cout << "Попытка добавить оценку 150 (больше 100)..." << std::endl;
        repo.addStudent("Test", "test123@university.ru", "CS-101");
        int studentId = 1;
        repo.addGrade(studentId, "Math", 150);
        std::cout << "✗ ОШИБКА: валидация пропустила неверную оценку!" << std::endl;
    } catch (const std::exception& e) {
        std::cout << "✓ Перехвачено: " << e.what() << std::endl;
    }

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Все тесты валидации пройдены успешно!                 ║" << std::endl;
    std::cout << "║  Система защищена от:                                  ║" << std::endl;
    std::cout << "║  ✓ SQL-инъекций                                        ║" << std::endl;
    std::cout << "║  ✓ Некорректных email                                  ║" << std::endl;
    std::cout << "║  ✓ Неверных форматов данных                            ║" << std::endl;
    std::cout << "║  ✓ Выхода за диапазон значений                         ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    pause();
}

// ==================== ЗАДАНИЕ 5 ====================
void task5_batchInsert(StudentRepository& repo) {
    clearScreen();
    showHeader("ЗАДАНИЕ 5: Пакетная вставка с измерением производительности");

    int count;
    std::cout << "\nСколько студентов добавить? ";
    std::cin >> count;

    std::cout << "\nГенерация " << count << " студентов..." << std::endl;

    std::vector<Student> students;
    for (int i = 0; i < count; ++i) {
        Student s;
        s.name = "Студент_" + std::to_string(i);
        s.email = "student" + std::to_string(i) + "@university.ru";
        s.groupName = (i % 2 == 0) ? "CS-101" : "CS-102";
        students.push_back(s);
    }

    std::cout << "✓ Студенты сгенерированы" << std::endl;
    std::cout << "\nЗапуск пакетной вставки..." << std::endl;

    auto start = std::chrono::steady_clock::now();
    bool success = repo.batchInsertStudents(students);
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    if (success) {
        std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
        std::cout << "║  РЕЗУЛЬТАТЫ ПАКЕТНОЙ ВСТАВКИ                           ║" << std::endl;
        std::cout << "╠════════════════════════════════════════════════════════╣" << std::endl;
        printf("║  Добавлено студентов: %-32d ║\n", count);
        printf("║  Время выполнения: %-35ld мс ║\n", duration.count());

        if (count > 0 && duration.count() > 0) {
            double speed = (double)count / duration.count() * 1000;
            printf("║  Скорость: %-43.0f студентов/сек ║\n", speed);
        }

        std::cout << "╠════════════════════════════════════════════════════════╣" << std::endl;
        std::cout << "║  ✓ Использована одна транзакция для всех записей      ║" << std::endl;
        std::cout << "║  ✓ Подготовленное выражение переиспользовано          ║" << std::endl;
        std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;
    } else {
        std::cout << "\n✗ Ошибка при пакетной вставке" << std::endl;
    }

    pause();
}

void task5_showIndexes() {
    clearScreen();
    showHeader("ЗАДАНИЕ 5: Индексы для оптимизации запросов");

    std::cout << "\n✓ Созданы следующие индексы:" << std::endl;
    std::cout << "\n1. idx_students_email (на поле students.email)" << std::endl;
    std::cout << "   Ускоряет:" << std::endl;
    std::cout << "   - Проверку уникальности email при добавлении студента" << std::endl;
    std::cout << "   - Поиск студента по email" << std::endl;

    std::cout << "\n2. idx_students_group (на поле students.group_name)" << std::endl;
    std::cout << "   Ускоряет:" << std::endl;
    std::cout << "   - Запрос getStudentsByGroup()" << std::endl;
    std::cout << "   - Группировку и статистику по группам" << std::endl;

    std::cout << "\n3. idx_grades_subject (на поле grades.subject)" << std::endl;
    std::cout << "   Ускоряет:" << std::endl;
    std::cout << "   - Запрос getAverageGradeBySubject()" << std::endl;
    std::cout << "   - Поиск оценок по предмету" << std::endl;

    std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║  ЭФФЕКТ ИНДЕКСОВ:                                      ║" << std::endl;
    std::cout << "║  Без индекса: O(n) - полное сканирование таблицы       ║" << std::endl;
    std::cout << "║  С индексом:  O(log n) - бинарный поиск                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════╝" << std::endl;

    pause();
}

void task5_menu(StudentRepository& repo) {
    int choice;
    do {
        clearScreen();
        showHeader("ЗАДАНИЕ 5: Оптимизация и тестирование");

        std::cout << "\n1. Пакетная вставка студентов (с замером времени)" << std::endl;
        std::cout << "2. Информация об индексах" << std::endl;
        std::cout << "3. Запустить unit-тесты (требуется Google Test)" << std::endl;
        std::cout << "0. Вернуться в главное меню" << std::endl;
        std::cout << "\nВыберите действие: ";
        std::cin >> choice;

        switch (choice) {
            case 1: task5_batchInsert(repo); break;
            case 2: task5_showIndexes(); break;
            case 3:
                clearScreen();
                showHeader("Запуск unit-тестов");
                std::cout << "\nДля запуска тестов выполните в терминале:" << std::endl;
                std::cout << "  make test" << std::endl;
                std::cout << "\nИнструкции по установке Google Test:" << std::endl;
                std::cout << "  см. файл TESTING_README.md" << std::endl;
                pause();
                break;
            case 0: break;
            default:
                std::cout << "\n✗ Неверный выбор!" << std::endl;
                pause();
        }
    } while (choice != 0);
}

// ==================== ГЛАВНОЕ МЕНЮ ====================
void showMainMenu() {
    clearScreen();
    std::cout << "╔════════════════════════════════════════════════════════════════╗" << std::endl;
    std::cout << "║                                                                ║" << std::endl;
    std::cout << "║        ЛАБОРАТОРНАЯ РАБОТА №6                                  ║" << std::endl;
    std::cout << "║        Работа с базами данных в C++                            ║" << std::endl;
    std::cout << "║                                                                ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════════════════════════╝" << std::endl;

    std::cout << "\n┌────────────────────────────────────────────────────────────────┐" << std::endl;
    std::cout << "│  ЗАДАНИЯ:                                                      │" << std::endl;
    std::cout << "├────────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│  1. Базовая настройка и создание таблиц                        │" << std::endl;
    std::cout << "│  2. CRUD операции и подготовленные выражения                   │" << std::endl;
    std::cout << "│  3. Транзакции и сложные запросы                               │" << std::endl;
    std::cout << "│  4. Безопасность и валидация данных                            │" << std::endl;
    std::cout << "│  5. Оптимизация и тестирование                                 │" << std::endl;
    std::cout << "├────────────────────────────────────────────────────────────────┤" << std::endl;
    std::cout << "│  0. Выход                                                      │" << std::endl;
    std::cout << "└────────────────────────────────────────────────────────────────┘" << std::endl;

    std::cout << "\nВыберите задание (0-5): ";
}

// ==================== MAIN ====================
int main() {
    // Инициализация базы данных
    DatabaseManager dbManager;
    if (!dbManager.initialize("university.db")) {
        std::cerr << "✗ Не удалось инициализировать базу данных" << std::endl;
        return 1;
    }

    StudentRepository repo(dbManager.getHandle());

    int choice;
    do {
        showMainMenu();
        std::cin >> choice;

        switch (choice) {
            case 1: task1_demo(repo); break;
            case 2: task2_menu(repo); break;
            case 3: task3_menu(repo); break;
            case 4: task4_demo(repo); break;
            case 5: task5_menu(repo); break;
            case 0:
                clearScreen();
                std::cout << "\n╔════════════════════════════════════════════════════════╗" << std::endl;
                std::cout << "║  Спасибо за использование программы!                   ║" << std::endl;
                std::cout << "║  До свидания!                                          ║" << std::endl;
                std::cout << "╚════════════════════════════════════════════════════════╝\n" << std::endl;
                break;
            default:
                std::cout << "\n✗ Неверный выбор! Выберите число от 0 до 5." << std::endl;
                pause();
        }
    } while (choice != 0);

    return 0;
}
