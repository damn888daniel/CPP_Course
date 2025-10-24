#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
    int age;

public:
    Person(string n, int a) : name(n), age(a) {}
    virtual void display() const {
        cout << "Имя: " << name << ", Возраст: " << age << endl;
    }
};

class Employee {
protected:
    string position;
    double salary;

public:
    Employee(string pos, double sal) : position(pos), salary(sal) {}
    virtual void work() const {
        cout << "Выполняет работу как сотрудник" << endl;
    }
};

class Teacher : public Person, public Employee {
private:
    string subject;
    int experienceYears;

public:
    Teacher(string n, int a, string pos, double sal, string subj, int exp)
        : Person(n, a), Employee(pos, sal), subject(subj), experienceYears(exp) {}
    
    void display() const override {
        cout << "=== Учитель ===" << endl;
        Person::display();
        cout << "Должность: " << position << endl;
        cout << "Зарплата: " << salary << " руб." << endl;
        cout << "Предмет: " << subject << endl;
        cout << "Стаж: " << experienceYears << " лет" << endl;
    }
    
    void work() const override {
        cout << "Преподает предмет: " << subject << endl;
    }
    
    void conductLesson() const {
        cout << name << " проводит урок по предмету " << subject << endl;
    }
    
    void gradeStudents() const {
        cout << name << " оценивает работы студентов" << endl;
    }
    
    double calculateBonus() const {
        return salary * experienceYears * 0.02;
    }
};

class Researcher {
protected:
    string researchArea;
    int publicationsCount;

public:
    Researcher(string area, int publications) 
        : researchArea(area), publicationsCount(publications) {}
    
    void conductResearch() const {
        cout << "Проводит исследования в области: " << researchArea << endl;
    }
};

class Professor : public Teacher, public Researcher {
public:
    Professor(string n, int a, string pos, double sal, string subj, int exp, 
              string area, int publications)
        : Teacher(n, a, pos, sal, subj, exp), Researcher(area, publications) {}
    
    void display() const override {
        cout << "=== Профессор ===" << endl;
        Person::display();
        cout << "Должность: " << position << endl;
        cout << "Зарплата: " << salary << " руб." << endl;
        cout << "Предмет: " << subject << endl;
        cout << "Стаж: " << experienceYears << " лет" << endl;
        cout << "Область исследований: " << researchArea << endl;
        cout << "Количество публикаций: " << publicationsCount << endl;
    }
    
    void work() const override {
        Teacher::work();
        conductResearch();
        cout << "Публикует научные статьи" << endl;
    }
    
    void superviseDissertations() const {
        cout << name << " руководит диссертациями аспирантов" << endl;
    }
    
    double calculateTotalSalary() const {
        double bonus = calculateBonus();
        double publicationBonus = publicationsCount * 500.0;
        return salary + bonus + publicationBonus;
    }
};

int main() {
    
    cout << "=== Создание объектов ===" << endl << endl;
    
    Teacher teacher("Иван Петров", 35, "Старший преподаватель", 40000, "Математика", 10);
    teacher.display();
    cout << endl;
    teacher.work();
    teacher.conductLesson();
    teacher.gradeStudents();
    cout << "Премия: " << teacher.calculateBonus() << " руб." << endl;
    cout << endl << endl;
    
    Professor prof("Анна Смирнова", 45, "Профессор", 80000, "Физика", 20, 
                   "Квантовая механика", 35);
    prof.display();
    cout << endl;
    prof.work();
    prof.superviseDissertations();
    cout << "Общая зарплата с надбавками: " << prof.calculateTotalSalary() << " руб." << endl;
    
    return 0;
}
