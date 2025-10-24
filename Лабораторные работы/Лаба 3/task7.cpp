#include <iostream>
#include <string>
using namespace std;

class Complex {
private:
    double real;
    double imaginary;

public:
    Complex(double r = 0, double i = 0) : real(r), imaginary(i) {}
    
    double getReal() const { return real; }
    double getImaginary() const { return imaginary; }
    
    void setReal(double r) { real = r; }
    void setImaginary(double i) { imaginary = i; }
    
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imaginary + other.imaginary);
    }
    
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imaginary - other.imaginary);
    }
    
    Complex operator*(const Complex& other) const {
        double r = real * other.real - imaginary * other.imaginary;
        double i = real * other.imaginary + imaginary * other.real;
        return Complex(r, i);
    }
    
    bool operator==(const Complex& other) const {
        return (real == other.real && imaginary == other.imaginary);
    }
    
    friend ostream& operator<<(ostream& os, const Complex& c) {
        if (c.imaginary >= 0) {
            os << c.real << " + " << c.imaginary << "i";
        } else {
            os << c.real << " - " << (-c.imaginary) << "i";
        }
        return os;
    }
    
    friend istream& operator>>(istream& is, Complex& c) {
        cout << "Введите действительную часть: ";
        is >> c.real;
        cout << "Введите мнимую часть: ";
        is >> c.imaginary;
        return is;
    }
    
    void display() const {
        cout << real << " + " << imaginary << "i" << endl;
    }
};

int main() {
    
    cout << "=== Создание комплексных чисел ===" << endl;
    Complex c1(3.0, 4.0);
    Complex c2(1.0, 2.0);
    Complex c3(3.0, 4.0);
    
    cout << "c1 = " << c1 << endl;
    cout << "c2 = " << c2 << endl;
    cout << "c3 = " << c3 << endl;
    cout << endl;
    
    cout << "=== Арифметические операции ===" << endl;
    Complex sum = c1 + c2;
    cout << "c1 + c2 = " << sum << endl;
    
    Complex diff = c1 - c2;
    cout << "c1 - c2 = " << diff << endl;
    
    Complex prod = c1 * c2;
    cout << "c1 * c2 = " << prod << endl;
    cout << endl;
    
    cout << "=== Операция сравнения ===" << endl;
    if (c1 == c3) {
        cout << "c1 и c3 равны" << endl;
    } else {
        cout << "c1 и c3 не равны" << endl;
    }
    
    if (c1 == c2) {
        cout << "c1 и c2 равны" << endl;
    } else {
        cout << "c1 и c2 не равны" << endl;
    }
    cout << endl;
    
    cout << "=== Ввод комплексного числа ===" << endl;
    Complex c4;
    
    c4.setReal(5.0);
    c4.setImaginary(-3.0);
    cout << "c4 = " << c4 << endl;
    cout << endl;
    
    cout << "=== Сложные выражения ===" << endl;
    Complex result = (c1 + c2) * c4;
    cout << "(c1 + c2) * c4 = " << result << endl;
    
    return 0;
}
