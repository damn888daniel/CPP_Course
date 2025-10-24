#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    // TODO: Добавить приватные поля: имя, возраст, средний балл
    // и массив оценок (5 элементов)
    
    string name;
    int age;
    double averageGrade;
    int grades[5];

public:
    // TODO: Создать конструктор с параметрами
    
    Student(string n, int a) : name(n), age(a), averageGrade(0.0) {
        for (int i = 0; i < 5; i++) {
            grades[i] = 0;
        }
    }
    
    // TODO: Реализовать геттеры и сеттеры с валидацией
    
    string getName() const { return name; }
    int getAge() const { return age; }
    double getAverageGrade() const { return averageGrade; }
    
    void setName(string n) { name = n; }
    
    void setAge(int a) {
        if (a > 0 && a < 100) {
            age = a;
        }
    }
    
    void setGrade(int index, int grade) {
        if (index >= 0 && index < 5 && grade >= 2 && grade <= 5) {
            grades[index] = grade;
            calculateAverageGrade();
        }
    }
    
    int getGrade(int index) const {
        if (index >= 0 && index < 5) {
            return grades[index];
        }
        return 0;
    }
    
    // TODO: Метод для расчета среднего балла
    
    void calculateAverageGrade() {
        double sum = 0;
        for (int i = 0; i < 5; i++) {
            sum += grades[i];
        }
        averageGrade = sum / 5.0;
    }
    
    // TODO: Метод для вывода информации о студенте
    
    void displayInfo() const {
        cout << "Студент: " << name << endl;
        cout << "Возраст: " << age << endl;
        cout << "Оценки: ";
        for (int i = 0; i < 5; i++) {
            cout << grades[i] << " ";
        }
        cout << endl;
        cout << "Средний балл: " << averageGrade << endl;
    }
    
    // TODO: Метод для проверки стипендии (средний балл >= 4.5)
    
    bool hasScholarship() const {
        return averageGrade >= 4.5;
    }
};

int main() {
    Student student("Иван Иванов", 20);
    
    student.setGrade(0, 5);
    student.setGrade(1, 4);
    student.setGrade(2, 5);
    student.setGrade(3, 3);
    student.setGrade(4, 4);
    
    student.displayInfo();
    
    if (student.hasScholarship()) {
        cout << "Студент получает стипендию" << endl;
    } else {
        cout << "Стипендия не назначена" << endl;
    }
    
    return 0;
}
