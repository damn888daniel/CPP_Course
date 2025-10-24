#include <iostream>
using namespace std;

int main() {
    double num1, num2;
    char operation;
    
    cout << "Простой калькулятор" << endl;
    cout << "Введите первое число: ";
    cin >> num1;
    
    cout << "Введите операцию (+, -, *, /): ";
    cin >> operation;
    
    cout << "Введите второе число: ";
    cin >> num2;
    
    if (operation == '+') {
        cout << "Результат: " << num1 + num2 << endl;
    }
    
    if (operation == '-') {
        cout << "Результат: " << num1 - num2 << endl;
    }
    
    if (operation == '*') {
        cout << "Результат: " << num1 * num2 << endl;
    }
    
    if (operation == '/') {
        if (num2 != 0) {
            cout << "Результат: " << num1 / num2 << endl;
        } else {
            cout << "Ошибка! Делить на ноль нельзя" << endl;
        }
    }
    
    return 0;
}
