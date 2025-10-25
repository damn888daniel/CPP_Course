#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    // TODO: Добавить приватные поля: имя, возраст, средний балл
    // и массив оценок (5 элементов)
    
    string name;            // Имя студента
    int age;                // Возраст студента
    double averageGrade;    // Средний балл студента
    int grades[5];          // Массив из 5 оценок

public:
    // TODO: Создать конструктор с параметрами
    
    // Конструктор с параметрами имени и возраста
    Student(string n, int a) : name(n), age(a), averageGrade(0.0) {
        // Инициализация всех оценок нулями
        for (int i = 0; i < 5; i++) {
            grades[i] = 0;
        }
    }
    
    // TODO: Реализовать геттеры и сеттеры с валидацией
    
    // Геттер для получения имени студента
    string getName() const { return name; }
    
    // Геттер для получения возраста студента
    int getAge() const { return age; }
    
    // Геттер для получения среднего балла
    double getAverageGrade() const { return averageGrade; }
    
    // Сеттер для установки имени студента
    void setName(string n) { name = n; }
    
    // Сеттер для установки возраста с валидацией (от 0 до 100)
    void setAge(int a) {
        if (a > 0 && a < 100) {  // Проверка корректности возраста
            age = a;
        }
    }
    
    // Сеттер для установки оценки по индексу с валидацией
    void setGrade(int index, int grade) {
        // Проверка корректности индекса и значения оценки (от 2 до 5)
        if (index >= 0 && index < 5 && grade >= 2 && grade <= 5) {
            grades[index] = grade;           // Установка оценки
            calculateAverageGrade();         // Пересчет среднего балла
        }
    }
    
    // Геттер для получения оценки по индексу
    int getGrade(int index) const {
        if (index >= 0 && index < 5) {  // Проверка корректности индекса
            return grades[index];        // Возврат оценки
        }
        return 0;  // Возврат 0 при некорректном индексе
    }
    
    // TODO: Метод для расчета среднего балла
    
    // Метод для вычисления среднего балла студента
    void calculateAverageGrade() {
        double sum = 0;  // Переменная для суммы оценок
        // Цикл для суммирования всех оценок
        for (int i = 0; i < 5; i++) {
            sum += grades[i];
        }
        averageGrade = sum / 5.0;  // Вычисление среднего арифметического
    }
    
    // TODO: Метод для вывода информации о студенте
    
    // Метод для вывода полной информации о студенте
    void displayInfo() const {
        cout << "Студент: " << name << endl;       // Вывод имени
        cout << "Возраст: " << age << endl;        // Вывод возраста
        cout << "Оценки: ";                        // Заголовок для оценок
        // Цикл для вывода всех оценок
        for (int i = 0; i < 5; i++) {
            cout << grades[i] << " ";
        }
        cout << endl;
        cout << "Средний балл: " << averageGrade << endl;  // Вывод среднего балла
    }
    
    // TODO: Метод для проверки стипендии (средний балл >= 4.5)
    
    // Метод для проверки права на стипендию
    bool hasScholarship() const {
        return averageGrade >= 4.5;  // Возврат true если средний балл >= 4.5
    }
};

int main() {
    // Тестирование класса Student
    Student student("Иван Иванов", 20);
    
    // Установка оценок
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