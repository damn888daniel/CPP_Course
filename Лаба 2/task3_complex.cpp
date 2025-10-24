#include <iostream>
using namespace std;

struct Complex {
    double real;
    double imaginary;
};

Complex add(Complex a, Complex b) {
    Complex result;
    result.real = a.real + b.real;
    result.imaginary = a.imaginary + b.imaginary;
    return result;
}

Complex subtract(Complex a, Complex b) {
    Complex result;
    result.real = a.real - b.real;
    result.imaginary = a.imaginary - b.imaginary;
    return result;
}

Complex multiply(Complex a, Complex b) {
    Complex result;
    result.real = a.real * b.real - a.imaginary * b.imaginary;
    result.imaginary = a.real * b.imaginary + a.imaginary * b.real;
    return result;
}

void print(Complex c) {
    cout << "(" << c.real;
    if (c.imaginary >= 0) {
        cout << " + " << c.imaginary << "i)";
    } else {
        cout << " - " << (-c.imaginary) << "i)";
    }
}

int main() {
    Complex num1 = {3.0, 4.0};
    Complex num2 = {1.0, -2.0};
    Complex num3 = {-2.0, 5.0};
    
    cout << "=== КАЛЬКУЛЯТОР КОМПЛЕКСНЫХ ЧИСЕЛ ===\n\n";
    
    cout << "Число 1: "; print(num1); cout << "\n";
    cout << "Число 2: "; print(num2); cout << "\n";
    cout << "Число 3: "; print(num3); cout << "\n\n";
    
    cout << "--- Сложение ---\n";
    Complex sum1 = add(num1, num2);
    print(num1); cout << " + "; print(num2); cout << " = "; print(sum1); cout << "\n";
    
    Complex sum2 = add(num1, num3);
    print(num1); cout << " + "; print(num3); cout << " = "; print(sum2); cout << "\n\n";
    
    cout << "--- Вычитание ---\n";
    Complex diff1 = subtract(num1, num2);
    print(num1); cout << " - "; print(num2); cout << " = "; print(diff1); cout << "\n";
    
    Complex diff2 = subtract(num3, num1);
    print(num3); cout << " - "; print(num1); cout << " = "; print(diff2); cout << "\n\n";
    
    cout << "--- Умножение ---\n";
    Complex product1 = multiply(num1, num2);
    print(num1); cout << " * "; print(num2); cout << " = "; print(product1); cout << "\n";
    
    Complex product2 = multiply(num2, num3);
    print(num2); cout << " * "; print(num3); cout << " = "; print(product2); cout << "\n";
    
    return 0;
}
