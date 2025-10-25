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
    
    // Конструктор класса Student с вызовом конструктора базового класса Person
    Student(string n, int a, string addr, string id, double grade)
        : Person(n, a, addr), studentId(id), averageGrade(grade) {}
    
    // TODO: Переопределить displayInfo()
    
    // Переопределенный метод для вывода информации о студенте
    void displayInfo() const override {
        cout << "=== Студент ===" << endl;
        Person::displayInfo();  // Вызов метода базового класса для вывода общей информации
        cout << "ID студента: " << studentId << endl;  // Вывод ID студента
        cout << "Средний балл: " << averageGrade << endl;  // Вывод среднего балла
    }
    
    // TODO: Добавить методы для работы с оценками
    
    // Сеттер для установки среднего балла с валидацией (от 0.0 до 5.0)
    void setAverageGrade(double grade) {
        if (grade >= 0.0 && grade <= 5.0) {  // Проверка корректности балла
            averageGrade = grade;
        }
    }
    
    // Геттер для получения среднего балла
    double getAverageGrade() const {
        return averageGrade;
    }
    
    // Геттер для получения ID студента
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
    
    // Конструктор класса Professor с вызовом конструктора базового класса Person
    Professor(string n, int a, string addr, string dept, double sal, int years)
        : Person(n, a, addr), department(dept), salary(sal), yearsOfExperience(years) {}
    
    // TODO: Переопределить displayInfo()
    
    // Переопределенный метод для вывода информации о профессоре
    void displayInfo() const override {
        cout << "=== Профессор ===" << endl;
        Person::displayInfo();  // Вызов метода базового класса
        cout << "Кафедра: " << department << endl;  // Вывод кафедры
        cout << "Зарплата: " << salary << " руб." << endl;  // Вывод зарплаты
        cout << "Стаж: " << yearsOfExperience << " лет" << endl;  // Вывод стажа
        cout << "Надбавка за стаж: " << calculateExperienceBonus() << " руб." << endl;  // Вывод надбавки
    }
    
    // TODO: Добавить метод для расчета надбавки за стаж
    
    // Метод для расчета надбавки за стаж работы (5% от зарплаты за каждые 5 лет стажа)
    double calculateExperienceBonus() const {
        return salary * (yearsOfExperience / 5) * 0.05;  // Формула: зарплата * (стаж/5) * 5%
    }
};

int main() {
    // Тестирование иерархии классов
    Student student("Петр Петров", 20, "ул. Студенческая, 15", "S12345", 4.3);
    Professor prof("Доктор Иванов", 45, "ул. Академическая, 10", "Компьютерные науки", 50000, 15);
    
    student.displayInfo();
    cout << endl;
    prof.displayInfo();
    
    return 0;
}