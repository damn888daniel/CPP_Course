#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

// Абстрактный базовый класс
class UniversityMember {
protected:
    string name;
    string id;
    string email;

public:
    UniversityMember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~UniversityMember() {}
    
    // TODO: Чисто виртуальные методы:
    // - virtual void displayInfo() const = 0;
    // - virtual void work() const = 0;
    
    //виртуальный метод для вывода информации о члене университета
    virtual void displayInfo() const = 0;
    
    //виртуальный метод для описания деятельности члена университета
    virtual void work() const = 0;
    
    virtual string getRole() const = 0;
    
    // Геттеры для получения информации
    string getName() const { return name; }
    string getId() const { return id; }
    string getEmail() const { return email; }
};

class Student : public UniversityMember {
private:
    string major;
    int year;
    double gpa;
    vector<string> courses;

public:
    // TODO: Конструктор
    
    // Конструктор класса Student с инициализацией всех полей
    Student(string n, string i, string e, string maj, int y, double g = 0.0)
        : UniversityMember(n, i, e), major(maj), year(y), gpa(g) {}
    
    // TODO: Реализовать виртуальные методы
    
    // Переопределение метода для вывода информации о студенте
    void displayInfo() const override {
        cout << "=== СТУДЕНТ ===" << endl;
        cout << "Имя: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Email: " << email << endl;
        cout << "Специальность: " << major << endl;
        cout << "Курс: " << year << endl;
        cout << "Средний балл: " << gpa << endl;
        cout << "Записанные курсы (" << courses.size() << "): ";
        for (const auto& course : courses) {
            cout << course << " ";
        }
        cout << endl;
    }
    
    // Переопределение метода для описания деятельности студента
    void work() const override {
        cout << name << " учится на курсе " << year << " по специальности " << major << endl;
    }
    
    // Переопределение метода для получения роли
    string getRole() const override {
        return "Студент";
    }
    
    // TODO: Добавить методы:
    // - enrollCourse(const string& course)
    
    // Метод для записи студента на курс
    void enrollCourse(const string& course) {
        auto it = find(courses.begin(), courses.end(), course);  // Поиск курса в списке
        if (it == courses.end()) {  // Если курс не найден
            courses.push_back(course);  // Добавление курса в список
            cout << name << " записан(а) на курс: " << course << endl;
        } else {
            cout << name << " уже записан(а) на курс: " << course << endl;
        }
    }
    
    // - dropCourse(const string& course)
    
    // Метод для отчисления студента с курса
    void dropCourse(const string& course) {
        auto it = find(courses.begin(), courses.end(), course);  // Поиск курса в списке
        if (it != courses.end()) {  // Если курс найден
            courses.erase(it);  // Удаление курса из списка
            cout << name << " отписан(а) от курса: " << course << endl;
        } else {
            cout << name << " не записан(а) на курс: " << course << endl;
        }
    }
    
    // - calculateGPA()
    
    // Метод для установки среднего балла с валидацией
    void setGPA(double newGPA) {
        if (newGPA >= 0.0 && newGPA <= 5.0) {  // Проверка корректности балла
            gpa = newGPA;
        }
    }
    
    // Геттеры для получения информации о студенте
    double getGPA() const { return gpa; }
    string getMajor() const { return major; }
    int getYear() const { return year; }
};

class Professor : public UniversityMember {
private:
    string department;
    string office;
    double salary;
    vector<string> teachingCourses;

public:
    // TODO: Конструктор
    
    // Конструктор класса Professor с инициализацией всех полей
    Professor(string n, string i, string e, string dept, string off, double sal)
        : UniversityMember(n, i, e), department(dept), office(off), salary(sal) {}
    
    // TODO: Реализовать виртуальные методы
    
    // Переопределение метода для вывода информации о профессоре
    void displayInfo() const override {
        cout << "=== ПРОФЕССОР ===" << endl;
        cout << "Имя: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Email: " << email << endl;
        cout << "Кафедра: " << department << endl;
        cout << "Кабинет: " << office << endl;
        cout << "Зарплата: " << salary << " руб." << endl;
        cout << "Преподаваемые курсы (" << teachingCourses.size() << "): ";
        for (const auto& course : teachingCourses) {
            cout << course << " ";
        }
        cout << endl;
    }
    
    // Переопределение метода для описания деятельности профессора
    void work() const override {
        cout << name << " преподает " << teachingCourses.size() 
             << " курс(ов) на кафедре " << department << endl;
    }
    
    // Переопределение метода для получения роли
    string getRole() const override {
        return "Профессор";
    }
    
    // TODO: Добавить методы:
    // - assignCourse(const string& course)
    
    // Метод для назначения профессора на курс
    void assignCourse(const string& course) {
        auto it = find(teachingCourses.begin(), teachingCourses.end(), course);  // Поиск курса
        if (it == teachingCourses.end()) {  // Если курс не найден в списке
            teachingCourses.push_back(course);  // Добавление курса в список преподаваемых
            cout << "Профессор " << name << " назначен на курс: " << course << endl;
        } else {
            cout << "Профессор " << name << " уже ведет курс: " << course << endl;
        }
    }
    
    // - removeCourse(const string& course)
    
    // Метод для снятия профессора с курса
    void removeCourse(const string& course) {
        auto it = find(teachingCourses.begin(), teachingCourses.end(), course);  // Поиск курса
        if (it != teachingCourses.end()) {  // Если курс найден
            teachingCourses.erase(it);  // Удаление курса из списка
            cout << "Профессор " << name << " снят с курса: " << course << endl;
        } else {
            cout << "Профессор " << name << " не ведет курс: " << course << endl;
        }
    }
    
    // - calculateSalary() const
    
    // Метод для расчета зарплаты с надбавками за ведение курсов
    double calculateSalary() const {
        double bonus = teachingCourses.size() * 5000.0;  // Надбавка 5000 руб. за каждый курс
        return salary + bonus;  // Общая зарплата с надбавками
    }
    
    // Геттеры для получения информации о профессоре
    string getDepartment() const { return department; }
    const vector<string>& getTeachingCourses() const { return teachingCourses; }
};

class Course {
private:
    string courseCode;
    string courseName;
    int credits;
    Professor* instructor;
    vector<Student*> enrolledStudents;

public:
    // TODO: Конструктор
    
    // Конструктор класса Course с инициализацией полей
    Course(string code, string name, int cred)
        : courseCode(code), courseName(name), credits(cred), instructor(nullptr) {}
    
    // TODO: Методы:
    // - addStudent(Student* student)
    
    // Метод для добавления студента на курс
    void addStudent(Student* student) {
        if (student) {  // Проверка валидности указателя
            auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);  // Поиск студента
            if (it == enrolledStudents.end()) {  // Если студент еще не записан
                enrolledStudents.push_back(student);  // Добавление студента в список
                student->enrollCourse(courseCode);    // Запись курса в список студента
                cout << "Студент " << student->getName() << " записан на курс " << courseName << endl;
            } else {
                cout << "Студент уже записан на этот курс" << endl;
            }
        }
    }
    
    // - removeStudent(const string& studentId)
    
    // Метод для удаления студента с курса по ID
    void removeStudent(const string& studentId) {
        // Поиск студента с указанным ID
        for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
            if ((*it)->getId() == studentId) {
                (*it)->dropCourse(courseCode);  // Удаление курса из списка студента
                enrolledStudents.erase(it);     // Удаление студента из списка курса
                cout << "Студент удален с курса " << courseName << endl;
                return;
            }
        }
        cout << "Студент не найден на курсе" << endl;
    }
    
    // - setInstructor(Professor* prof)
    
    // Метод для назначения преподавателя на курс
    void setInstructor(Professor* prof) {
        instructor = prof;  // Установка указателя на преподавателя
        if (prof) {  // Если преподаватель не nullptr
            prof->assignCourse(courseCode);  // Добавление курса в список преподавателя
            cout << "Преподаватель " << prof->getName() << " назначен на курс " << courseName << endl;
        }
    }
    
    // - displayCourseInfo() const
    
    // Метод для вывода полной информации о курсе
    void displayCourseInfo() const {
        cout << "=== КУРС ===" << endl;
        cout << "Код: " << courseCode << endl;
        cout << "Название: " << courseName << endl;
        cout << "Кредиты: " << credits << endl;
        cout << "Преподаватель: " << (instructor ? instructor->getName() : "Не назначен") << endl;
        cout << "Записано студентов: " << enrolledStudents.size() << endl;
        if (!enrolledStudents.empty()) {  // Если есть записанные студенты
            cout << "Список студентов:" << endl;
            for (const auto& student : enrolledStudents) {
                cout << "  - " << student->getName() << " (" << student->getId() << ")" << endl;
            }
        }
    }
    
    // Геттеры для получения информации о курсе
    string getCourseCode() const { return courseCode; }
    string getCourseName() const { return courseName; }
    int getEnrollmentCount() const { return enrolledStudents.size(); }
};

class University {
private:
    string name;
    vector<unique_ptr<UniversityMember>> members;
    vector<unique_ptr<Course>> courses;
    static int totalUniversities;

public:
    // Конструктор университета с увеличением счетчика университетов
    University(string n) : name(n) {
        totalUniversities++;  // Увеличение счетчика университетов
        cout << "Создан университет: " << name << endl;
    }
    
    // Деструктор университета с уменьшением счетчика
    ~University() {
        totalUniversities--;  // Уменьшение счетчика университетов
        cout << "Университет " << name << " расформирован" << endl;
    }
    
    // TODO: Методы для управления членами университета и курсами
    
    // Метод для добавления студента в университет
    void addStudent(unique_ptr<Student> student) {
        cout << "Добавлен студент: " << student->getName() << endl;
        members.push_back(move(student));  // Перемещение unique_ptr в вектор
    }
    
    // Метод для добавления профессора в университет
    void addProfessor(unique_ptr<Professor> professor) {
        cout << "Добавлен профессор: " << professor->getName() << endl;
        members.push_back(move(professor));  // Перемещение unique_ptr в вектор
    }
    
    // Метод для добавления курса в университет
    void addCourse(unique_ptr<Course> course) {
        cout << "Добавлен курс: " << course->getCourseName() << endl;
        courses.push_back(move(course));  // Перемещение unique_ptr в вектор
    }
    
    // Метод для поиска студента по ID
    Student* findStudent(const string& id) {
        for (auto& member : members) {
            // Проверка ID и роли члена университета
            if (member->getId() == id && member->getRole() == "Студент") {
                return dynamic_cast<Student*>(member.get());  // Приведение к типу Student
            }
        }
        return nullptr;  // Возврат nullptr если студент не найден
    }
    
    // Метод для поиска профессора по ID
    Professor* findProfessor(const string& id) {
        for (auto& member : members) {
            // Проверка ID и роли члена университета
            if (member->getId() == id && member->getRole() == "Профессор") {
                return dynamic_cast<Professor*>(member.get());  // Приведение к типу Professor
            }
        }
        return nullptr;  // Возврат nullptr если профессор не найден
    }
    
    // Метод для поиска курса по коду
    Course* findCourse(const string& code) {
        for (auto& course : courses) {
            if (course->getCourseCode() == code) {
                return course.get();  // Возврат указателя на курс
            }
        }
        return nullptr;  // Возврат nullptr если курс не найден
    }
    
    // Метод для вывода информации обо всех членах университета
    void displayAllMembers() const {
        cout << "\n=== Все члены университета " << name << " ===" << endl;
        cout << "Всего: " << members.size() << " человек" << endl << endl;
        for (const auto& member : members) {
            member->displayInfo();  // Полиморфный вызов displayInfo()
            cout << endl;
        }
    }
    
    // Метод для вывода информации обо всех курсах
    void displayAllCourses() const {
        cout << "\n=== Все курсы университета " << name << " ===" << endl;
        cout << "Всего курсов: " << courses.size() << endl << endl;
        for (const auto& course : courses) {
            course->displayCourseInfo();
            cout << endl;
        }
    }
    
    // Метод для вывода статистики университета
    void displayStatistics() const {
        int studentCount = 0, professorCount = 0;
        
        // Подсчет количества студентов и профессоров
        for (const auto& member : members) {
            if (member->getRole() == "Студент") studentCount++;
            else if (member->getRole() == "Профессор") professorCount++;
        }
        
        cout << "\n=== Статистика " << name << " ===" << endl;
        cout << "Студентов: " << studentCount << endl;
        cout << "Профессоров: " << professorCount << endl;
        cout << "Курсов: " << courses.size() << endl;
        cout << "Всего университетов: " << totalUniversities << endl;
    }
    
    // TODO: Статические методы
    
    // Статический метод для получения общего количества университетов
    static int getTotalUniversities() {
        return totalUniversities;
    }
    
    string getName() const { return name; }
};

// Инициализация статической переменной
int University::totalUniversities = 0;

int main() {
    // TODO: Создать университет
    // Добавить студентов, преподавателей, курсы
    // Продемонстрировать все возможности системы
    
    cout << "========================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ УНИВЕРСИТЕТОМ" << endl;
    cout << "========================================" << endl << endl;
    
    // Создание университета
    University university("МГУ имени М.В. Ломоносова");
    
    cout << "\n--- Добавление студентов ---" << endl;
    // Добавление студентов с использованием умных указателей
    university.addStudent(make_unique<Student>("Иван Петров", "S001", "ivanov@msu.ru", 
                                               "Информатика", 2, 4.5));
    university.addStudent(make_unique<Student>("Мария Сидорова", "S002", "sidorova@msu.ru", 
                                               "Математика", 3, 4.8));
    university.addStudent(make_unique<Student>("Алексей Смирнов", "S003", "smirnov@msu.ru", 
                                               "Информатика", 1, 4.2));
    
    cout << "\n--- Добавление профессоров ---" << endl;
    // Добавление профессоров с использованием умных указателей
    university.addProfessor(make_unique<Professor>("Доктор Иванов", "P001", "ivanov.prof@msu.ru",
                                                   "Компьютерные науки", "A-201", 80000));
    university.addProfessor(make_unique<Professor>("Профессор Кузнецов", "P002", "kuznetsov@msu.ru",
                                                   "Математика", "B-305", 90000));
    
    cout << "\n--- Добавление курсов ---" << endl;
    // Добавление курсов с использованием умных указателей
    university.addCourse(make_unique<Course>("CS101", "Основы программирования", 4));
    university.addCourse(make_unique<Course>("CS201", "Алгоритмы и структуры данных", 5));
    university.addCourse(make_unique<Course>("MATH101", "Математический анализ", 6));
    
    cout << "\n--- Назначение преподавателей на курсы ---" << endl;
    // Поиск курсов по кодам
    Course* cs101 = university.findCourse("CS101");
    Course* cs201 = university.findCourse("CS201");
    Course* math101 = university.findCourse("MATH101");
    
    // Поиск профессоров по ID
    Professor* prof1 = university.findProfessor("P001");
    Professor* prof2 = university.findProfessor("P002");
    
    // Назначение преподавателей на курсы
    if (cs101 && prof1) cs101->setInstructor(prof1);
    if (cs201 && prof1) cs201->setInstructor(prof1);
    if (math101 && prof2) math101->setInstructor(prof2);
    
    cout << "\n--- Запись студентов на курсы ---" << endl;
    // Поиск студентов по ID
    Student* stud1 = university.findStudent("S001");
    Student* stud2 = university.findStudent("S002");
    Student* stud3 = university.findStudent("S003");
    
    // Запись студентов на курсы
    if (cs101) {
        if (stud1) cs101->addStudent(stud1);
        if (stud3) cs101->addStudent(stud3);
    }
    
    if (cs201 && stud1) cs201->addStudent(stud1);
    if (math101 && stud2) math101->addStudent(stud2);
    
    // Вывод статистики и информации
    university.displayStatistics();
    university.displayAllMembers();
    university.displayAllCourses();
    
    cout << "\n--- Демонстрация работы ---" << endl;
    // Демонстрация полиморфного вызова методов work()
    if (stud1) stud1->work();
    if (prof1) {
        prof1->work();
        cout << "Зарплата с надбавками: " << prof1->calculateSalary() << " руб." << endl;
    }
    
    cout << "\n--- Отчисление студента с курса ---" << endl;
    // Удаление студента с курса
    if (cs101 && stud1) cs101->removeStudent("S001");
    
    if (cs101) {
        cout << "\nОбновленная информация о курсе:" << endl;
        cs101->displayCourseInfo();
    }
    
    cout << "\n========================================" << endl;
    cout << "ПРОГРАММА ЗАВЕРШЕНА" << endl;
    cout << "========================================" << endl;
    
    return 0;
}