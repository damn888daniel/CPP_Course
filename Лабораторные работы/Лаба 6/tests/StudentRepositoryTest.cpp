// Unit-тесты для StudentRepository (Задание 5)
// Для компиляции требуется Google Test framework
// Установка: sudo apt-get install libgtest-dev (Linux) или brew install googletest (macOS)

#include <gtest/gtest.h>
#include "../include/DatabaseManager.h"
#include "../include/StudentRepository.h"
#include "../include/InputValidator.h"

// Фикстура для тестов - создает чистую БД перед каждым тестом
class StudentRepositoryTest : public ::testing::Test {
protected:
    DatabaseManager* dbManager;
    StudentRepository* repo;

    // Выполняется перед каждым тестом
    void SetUp() override {
        dbManager = new DatabaseManager();
        // Используем :memory: для создания БД в памяти (быстрее и не создает файлы)
        dbManager->initialize(":memory:");
        repo = new StudentRepository(dbManager->getHandle());
    }

    // Выполняется после каждого теста
    void TearDown() override {
        delete repo;
        delete dbManager;
    }
};

// Тест 1: Добавление студента с корректными данными
TEST_F(StudentRepositoryTest, AddStudentValidData) {
    EXPECT_TRUE(repo->addStudent("Иван Иванов", "ivan@university.ru", "CS-101"));

    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value()); // Проверка что студент найден
    EXPECT_EQ(student->name, "Иван Иванов");
    EXPECT_EQ(student->email, "ivan@university.ru");
    EXPECT_EQ(student->groupName, "CS-101");
}

// Тест 2: Попытка добавления с некорректным email
TEST_F(StudentRepositoryTest, AddStudentInvalidEmail) {
    EXPECT_THROW({
        repo->addStudent("Тест Тестов", "invalid-email", "CS-101");
    }, std::invalid_argument);
}

// Тест 3: Попытка добавления с SQL-инъекцией
TEST_F(StudentRepositoryTest, AddStudentSQLInjection) {
    EXPECT_THROW({
        repo->addStudent("Robert'); DROP TABLE students;--", "test@university.ru", "CS-101");
    }, std::invalid_argument);
}

// Тест 4: Обновление данных студента
TEST_F(StudentRepositoryTest, UpdateStudent) {
    repo->addStudent("Петр Петров", "petr@university.ru", "CS-101");

    EXPECT_TRUE(repo->updateStudent(1, "Петр Иванович Петров", "petr.new@university.ru", "CS-102"));

    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value());
    EXPECT_EQ(student->name, "Петр Иванович Петров");
    EXPECT_EQ(student->email, "petr.new@university.ru");
    EXPECT_EQ(student->groupName, "CS-102");
}

// Тест 5: Удаление студента
TEST_F(StudentRepositoryTest, DeleteStudent) {
    repo->addStudent("Мария Сидорова", "maria@university.ru", "CS-101");

    EXPECT_TRUE(repo->deleteStudent(1));

    auto student = repo->getStudent(1);
    EXPECT_FALSE(student.has_value()); // Студент должен быть удален
}

// Тест 6: Получение всех студентов
TEST_F(StudentRepositoryTest, GetAllStudents) {
    repo->addStudent("Студент 1", "student1@university.ru", "CS-101");
    repo->addStudent("Студент 2", "student2@university.ru", "CS-102");
    repo->addStudent("Студент 3", "student3@university.ru", "CS-101");

    auto students = repo->getAllStudents();
    EXPECT_EQ(students.size(), 3);
}

// Тест 7: Добавление оценки
TEST_F(StudentRepositoryTest, AddGrade) {
    repo->addStudent("Анна Козлова", "anna@university.ru", "CS-101");

    EXPECT_TRUE(repo->addGrade(1, "Математика", 95));
    EXPECT_TRUE(repo->addGrade(1, "Физика", 88));
}

// Тест 8: Проверка валидации оценки
TEST_F(StudentRepositoryTest, AddGradeInvalidRange) {
    repo->addStudent("Тест Тестов", "test@university.ru", "CS-101");

    EXPECT_THROW({
        repo->addGrade(1, "Математика", 150); // Больше 100
    }, std::invalid_argument);

    EXPECT_THROW({
        repo->addGrade(1, "Физика", -10); // Меньше 0
    }, std::invalid_argument);
}

// Тест 9: Транзакция - добавление студента с оценками
TEST_F(StudentRepositoryTest, AddStudentWithGradesTransaction) {
    std::vector<Grade> grades = {
        {"Программирование", 92},
        {"Алгоритмы", 88},
        {"Базы данных", 95}
    };

    EXPECT_TRUE(repo->addStudentWithGrades("Дмитрий Смирнов", "dmitry@university.ru", "CS-101", grades));

    auto student = repo->getStudent(1);
    ASSERT_TRUE(student.has_value());
    EXPECT_EQ(student->name, "Дмитрий Смирнов");
}

// Тест 10: Поиск студентов по группе
TEST_F(StudentRepositoryTest, GetStudentsByGroup) {
    repo->addStudent("Студент 1", "s1@university.ru", "CS-101");
    repo->addStudent("Студент 2", "s2@university.ru", "CS-102");
    repo->addStudent("Студент 3", "s3@university.ru", "CS-101");
    repo->addStudent("Студент 4", "s4@university.ru", "CS-101");

    auto students = repo->getStudentsByGroup("CS-101");
    EXPECT_EQ(students.size(), 3);

    auto students2 = repo->getStudentsByGroup("CS-102");
    EXPECT_EQ(students2.size(), 1);
}

// Тест 11: Вычисление средней оценки по предмету
TEST_F(StudentRepositoryTest, GetAverageGradeBySubject) {
    repo->addStudent("Студент 1", "s1@university.ru", "CS-101");
    repo->addStudent("Студент 2", "s2@university.ru", "CS-101");

    repo->addGrade(1, "Математика", 80);
    repo->addGrade(2, "Математика", 90);
    repo->addGrade(1, "Физика", 70);

    double avgMath = repo->getAverageGradeBySubject("Математика");
    EXPECT_DOUBLE_EQ(avgMath, 85.0); // (80 + 90) / 2 = 85
}

// Тест 12: Получение топа студентов
TEST_F(StudentRepositoryTest, GetTopStudents) {
    repo->addStudent("Студент A", "sa@university.ru", "CS-101");
    repo->addStudent("Студент B", "sb@university.ru", "CS-101");
    repo->addStudent("Студент C", "sc@university.ru", "CS-101");

    repo->addGrade(1, "Предмет1", 70);
    repo->addGrade(1, "Предмет2", 80); // Средний: 75

    repo->addGrade(2, "Предмет1", 90);
    repo->addGrade(2, "Предмет2", 95); // Средний: 92.5

    repo->addGrade(3, "Предмет1", 85);
    repo->addGrade(3, "Предмет2", 85); // Средний: 85

    auto topStudents = repo->getTopStudents(2);
    ASSERT_EQ(topStudents.size(), 2);

    // Проверяем что первый - это студент с наивысшим баллом
    EXPECT_EQ(topStudents[0].name, "Студент B");
    EXPECT_DOUBLE_EQ(topStudents[0].avgGrade, 92.5);

    EXPECT_EQ(topStudents[1].name, "Студент C");
    EXPECT_DOUBLE_EQ(topStudents[1].avgGrade, 85.0);
}

// Тест 13: Пакетная вставка студентов
TEST_F(StudentRepositoryTest, BatchInsertStudents) {
    std::vector<Student> students;
    for (int i = 0; i < 50; ++i) {
        Student s;
        s.name = "Студент_" + std::to_string(i);
        s.email = "student" + std::to_string(i) + "@university.ru";
        s.groupName = "CS-101";
        students.push_back(s);
    }

    EXPECT_TRUE(repo->batchInsertStudents(students));

    auto allStudents = repo->getAllStudents();
    EXPECT_EQ(allStudents.size(), 50);
}

// Тест 14: Проверка каскадного удаления (FOREIGN KEY CASCADE)
TEST_F(StudentRepositoryTest, CascadeDeleteGrades) {
    repo->addStudent("Тест Каскад", "cascade@university.ru", "CS-101");
    repo->addGrade(1, "Математика", 90);
    repo->addGrade(1, "Физика", 85);

    // Удаляем студента - оценки должны удалиться автоматически
    EXPECT_TRUE(repo->deleteStudent(1));

    // Проверяем что студент удален
    auto student = repo->getStudent(1);
    EXPECT_FALSE(student.has_value());
}

// Тесты для InputValidator

// Тест 15: Валидация email
TEST(InputValidatorTest, ValidEmail) {
    EXPECT_TRUE(InputValidator::isValidEmail("test@university.ru"));
    EXPECT_TRUE(InputValidator::isValidEmail("user.name@example.com"));
    EXPECT_FALSE(InputValidator::isValidEmail("invalid-email"));
    EXPECT_FALSE(InputValidator::isValidEmail("@university.ru"));
    EXPECT_FALSE(InputValidator::isValidEmail("test@"));
}

// Тест 16: Валидация безопасности ввода
TEST(InputValidatorTest, SafeInput) {
    EXPECT_TRUE(InputValidator::isSafeInput("Нормальное Имя"));
    EXPECT_FALSE(InputValidator::isSafeInput("Robert'); DROP TABLE students;--"));
    EXPECT_FALSE(InputValidator::isSafeInput("Test';"));
    EXPECT_FALSE(InputValidator::isSafeInput("Test--comment"));
}

// Тест 17: Валидация длины имени
TEST(InputValidatorTest, NameLength) {
    EXPECT_TRUE(InputValidator::isValidNameLength("Иван Иванов"));
    EXPECT_FALSE(InputValidator::isValidNameLength("А")); // Слишком короткое
    EXPECT_FALSE(InputValidator::isValidNameLength(std::string(101, 'a'))); // Слишком длинное (101 символ)
}

// Тест 18: Валидация оценки
TEST(InputValidatorTest, GradeRange) {
    EXPECT_TRUE(InputValidator::isValidGrade(0));
    EXPECT_TRUE(InputValidator::isValidGrade(50));
    EXPECT_TRUE(InputValidator::isValidGrade(100));
    EXPECT_FALSE(InputValidator::isValidGrade(-1));
    EXPECT_FALSE(InputValidator::isValidGrade(101));
}

// Тест 19: Валидация формата группы
TEST(InputValidatorTest, GroupNameFormat) {
    EXPECT_TRUE(InputValidator::isValidGroupName("CS-101"));
    EXPECT_TRUE(InputValidator::isValidGroupName("MATH-202"));
    EXPECT_FALSE(InputValidator::isValidGroupName("CS")); // Слишком короткое
    EXPECT_FALSE(InputValidator::isValidGroupName("CS101")); // Нет дефиса
}

// Главная функция для запуска всех тестов
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
