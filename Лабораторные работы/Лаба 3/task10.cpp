#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
using namespace std;

class UniversityMember {
protected:
    string name;
    string id;
    string email;

public:
    UniversityMember(string n, string i, string e) : name(n), id(i), email(e) {}
    virtual ~UniversityMember() {}
    
    virtual void displayInfo() const = 0;
    virtual void work() const = 0;
    
    virtual string getRole() const = 0;
    
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
    Student(string n, string i, string e, string maj, int y, double g = 0.0)
        : UniversityMember(n, i, e), major(maj), year(y), gpa(g) {}
    
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
    
    void work() const override {
        cout << name << " учится на курсе " << year << " по специальности " << major << endl;
    }
    
    string getRole() const override {
        return "Студент";
    }
    
    void enrollCourse(const string& course) {
        auto it = find(courses.begin(), courses.end(), course);
        if (it == courses.end()) {
            courses.push_back(course);
            cout << name << " записан(а) на курс: " << course << endl;
        } else {
            cout << name << " уже записан(а) на курс: " << course << endl;
        }
    }
    
    void dropCourse(const string& course) {
        auto it = find(courses.begin(), courses.end(), course);
        if (it != courses.end()) {
            courses.erase(it);
            cout << name << " отписан(а) от курса: " << course << endl;
        } else {
            cout << name << " не записан(а) на курс: " << course << endl;
        }
    }
    
    void setGPA(double newGPA) {
        if (newGPA >= 0.0 && newGPA <= 5.0) {
            gpa = newGPA;
        }
    }
    
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
    Professor(string n, string i, string e, string dept, string off, double sal)
        : UniversityMember(n, i, e), department(dept), office(off), salary(sal) {}
    
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
    
    void work() const override {
        cout << name << " преподает " << teachingCourses.size() 
             << " курс(ов) на кафедре " << department << endl;
    }
    
    string getRole() const override {
        return "Профессор";
    }
    
    void assignCourse(const string& course) {
        auto it = find(teachingCourses.begin(), teachingCourses.end(), course);
        if (it == teachingCourses.end()) {
            teachingCourses.push_back(course);
            cout << "Профессор " << name << " назначен на курс: " << course << endl;
        } else {
            cout << "Профессор " << name << " уже ведет курс: " << course << endl;
        }
    }
    
    void removeCourse(const string& course) {
        auto it = find(teachingCourses.begin(), teachingCourses.end(), course);
        if (it != teachingCourses.end()) {
            teachingCourses.erase(it);
            cout << "Профессор " << name << " снят с курса: " << course << endl;
        } else {
            cout << "Профессор " << name << " не ведет курс: " << course << endl;
        }
    }
    
    double calculateSalary() const {
        double bonus = teachingCourses.size() * 5000.0;
        return salary + bonus;
    }
    
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
    Course(string code, string name, int cred)
        : courseCode(code), courseName(name), credits(cred), instructor(nullptr) {}
    
    void addStudent(Student* student) {
        if (student) {
            auto it = find(enrolledStudents.begin(), enrolledStudents.end(), student);
            if (it == enrolledStudents.end()) {
                enrolledStudents.push_back(student);
                student->enrollCourse(courseCode);
                cout << "Студент " << student->getName() << " записан на курс " << courseName << endl;
            } else {
                cout << "Студент уже записан на этот курс" << endl;
            }
        }
    }
    
    void removeStudent(const string& studentId) {
        for (auto it = enrolledStudents.begin(); it != enrolledStudents.end(); ++it) {
            if ((*it)->getId() == studentId) {
                (*it)->dropCourse(courseCode);
                enrolledStudents.erase(it);
                cout << "Студент удален с курса " << courseName << endl;
                return;
            }
        }
        cout << "Студент не найден на курсе" << endl;
    }
    
    void setInstructor(Professor* prof) {
        instructor = prof;
        if (prof) {
            prof->assignCourse(courseCode);
            cout << "Преподаватель " << prof->getName() << " назначен на курс " << courseName << endl;
        }
    }
    
    void displayCourseInfo() const {
        cout << "=== КУРС ===" << endl;
        cout << "Код: " << courseCode << endl;
        cout << "Название: " << courseName << endl;
        cout << "Кредиты: " << credits << endl;
        cout << "Преподаватель: " << (instructor ? instructor->getName() : "Не назначен") << endl;
        cout << "Записано студентов: " << enrolledStudents.size() << endl;
        if (!enrolledStudents.empty()) {
            cout << "Список студентов:" << endl;
            for (const auto& student : enrolledStudents) {
                cout << "  - " << student->getName() << " (" << student->getId() << ")" << endl;
            }
        }
    }
    
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
    University(string n) : name(n) {
        totalUniversities++;
        cout << "Создан университет: " << name << endl;
    }
    
    ~University() {
        totalUniversities--;
        cout << "Университет " << name << " расформирован" << endl;
    }
    
    void addStudent(unique_ptr<Student> student) {
        cout << "Добавлен студент: " << student->getName() << endl;
        members.push_back(move(student));
    }
    
    void addProfessor(unique_ptr<Professor> professor) {
        cout << "Добавлен профессор: " << professor->getName() << endl;
        members.push_back(move(professor));
    }
    
    void addCourse(unique_ptr<Course> course) {
        cout << "Добавлен курс: " << course->getCourseName() << endl;
        courses.push_back(move(course));
    }
    
    Student* findStudent(const string& id) {
        for (auto& member : members) {
            if (member->getId() == id && member->getRole() == "Студент") {
                return dynamic_cast<Student*>(member.get());
            }
        }
        return nullptr;
    }
    
    Professor* findProfessor(const string& id) {
        for (auto& member : members) {
            if (member->getId() == id && member->getRole() == "Профессор") {
                return dynamic_cast<Professor*>(member.get());
            }
        }
        return nullptr;
    }
    
    Course* findCourse(const string& code) {
        for (auto& course : courses) {
            if (course->getCourseCode() == code) {
                return course.get();
            }
        }
        return nullptr;
    }
    
    void displayAllMembers() const {
        cout << "\n=== Все члены университета " << name << " ===" << endl;
        cout << "Всего: " << members.size() << " человек" << endl << endl;
        for (const auto& member : members) {
            member->displayInfo();
            cout << endl;
        }
    }
    
    void displayAllCourses() const {
        cout << "\n=== Все курсы университета " << name << " ===" << endl;
        cout << "Всего курсов: " << courses.size() << endl << endl;
        for (const auto& course : courses) {
            course->displayCourseInfo();
            cout << endl;
        }
    }
    
    void displayStatistics() const {
        int studentCount = 0, professorCount = 0;
        
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
    
    static int getTotalUniversities() {
        return totalUniversities;
    }
    
    string getName() const { return name; }
};

int University::totalUniversities = 0;

int main() {
    
    cout << "========================================" << endl;
    cout << "СИСТЕМА УПРАВЛЕНИЯ УНИВЕРСИТЕТОМ" << endl;
    cout << "========================================" << endl << endl;
    
    University university("МГУ имени М.В. Ломоносова");
    
    cout << "\n--- Добавление студентов ---" << endl;
    university.addStudent(make_unique<Student>("Иван Петров", "S001", "ivanov@msu.ru", 
                                               "Информатика", 2, 4.5));
    university.addStudent(make_unique<Student>("Мария Сидорова", "S002", "sidorova@msu.ru", 
                                               "Математика", 3, 4.8));
    university.addStudent(make_unique<Student>("Алексей Смирнов", "S003", "smirnov@msu.ru", 
                                               "Информатика", 1, 4.2));
    
    cout << "\n--- Добавление профессоров ---" << endl;
    university.addProfessor(make_unique<Professor>("Доктор Иванов", "P001", "ivanov.prof@msu.ru",
                                                   "Компьютерные науки", "A-201", 80000));
    university.addProfessor(make_unique<Professor>("Профессор Кузнецов", "P002", "kuznetsov@msu.ru",
                                                   "Математика", "B-305", 90000));
    
    cout << "\n--- Добавление курсов ---" << endl;
    university.addCourse(make_unique<Course>("CS101", "Основы программирования", 4));
    university.addCourse(make_unique<Course>("CS201", "Алгоритмы и структуры данных", 5));
    university.addCourse(make_unique<Course>("MATH101", "Математический анализ", 6));
    
    cout << "\n--- Назначение преподавателей на курсы ---" << endl;
    Course* cs101 = university.findCourse("CS101");
    Course* cs201 = university.findCourse("CS201");
    Course* math101 = university.findCourse("MATH101");
    
    Professor* prof1 = university.findProfessor("P001");
    Professor* prof2 = university.findProfessor("P002");
    
    if (cs101 && prof1) cs101->setInstructor(prof1);
    if (cs201 && prof1) cs201->setInstructor(prof1);
    if (math101 && prof2) math101->setInstructor(prof2);
    
    cout << "\n--- Запись студентов на курсы ---" << endl;
    Student* stud1 = university.findStudent("S001");
    Student* stud2 = university.findStudent("S002");
    Student* stud3 = university.findStudent("S003");
    
    if (cs101) {
        if (stud1) cs101->addStudent(stud1);
        if (stud3) cs101->addStudent(stud3);
    }
    
    if (cs201 && stud1) cs201->addStudent(stud1);
    if (math101 && stud2) math101->addStudent(stud2);
    
    university.displayStatistics();
    university.displayAllMembers();
    university.displayAllCourses();
    
    cout << "\n--- Демонстрация работы ---" << endl;
    if (stud1) stud1->work();
    if (prof1) {
        prof1->work();
        cout << "Зарплата с надбавками: " << prof1->calculateSalary() << " руб." << endl;
    }
    
    cout << "\n--- Отчисление студента с курса ---" << endl;
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
