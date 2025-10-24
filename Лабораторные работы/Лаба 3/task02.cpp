#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;
    string address;

public:
    Person(string n, int a, string addr) : name(n), age(a), address(addr) {}
    virtual void displayInfo() const {
        cout << "Имя: " << name << ", Возраст: " << age << ", Адрес: " << address << endl;
    }
    virtual ~Person() {}
};

class Student : public Person {
private:
    string studentId;
    double averageGrade;

public:
    // TODO: Создать конструктор
    
    Student(string n, int a, string addr, string id, double grade)
        : Person(n, a, addr), studentId(id), averageGrade(grade) {}
    
    // TODO: Переопределить displayInfo()
    
    void displayInfo() const override {
        cout << "=== Студент ===" << endl;
        Person::displayInfo();
        cout << "ID студента: " << studentId << endl;
        cout << "Средний балл: " << averageGrade << endl;
    }
    
    // TODO: Добавить методы для работы с оценками
    
    void setAverageGrade(double grade) {
        if (grade >= 0.0 && grade <= 5.0) {
            averageGrade = grade;
        }
    }
    
    double getAverageGrade() const {
        return averageGrade;
    }
    
    string getStudentId() const {
        return studentId;
    }
};

class Professor : public Person {
private:
    string department;
    double salary;
    int yearsOfExperience;

public:
    // TODO: Создать конструктор
    
    Professor(string n, int a, string addr, string dept, double sal, int years)
        : Person(n, a, addr), department(dept), salary(sal), yearsOfExperience(years) {}
    
    // TODO: Переопределить displayInfo()
    
    void displayInfo() const override {
        cout << "=== Профессор ===" << endl;
        Person::displayInfo();
        cout << "Кафедра: " << department << endl;
        cout << "Зарплата: " << salary << " руб." << endl;
        cout << "Стаж: " << yearsOfExperience << " лет" << endl;
        cout << "Надбавка за стаж: " << calculateExperienceBonus() << " руб." << endl;
    }
    
    // TODO: Добавить метод для расчета надбавки за стаж
    
    double calculateExperienceBonus() const {
        return salary * (yearsOfExperience / 5) * 0.05;
    }
};

int main() {
    Student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    Professor prof("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);
    
    student.displayInfo();
    cout << endl;
    prof.displayInfo();
    
    return 0;
}
