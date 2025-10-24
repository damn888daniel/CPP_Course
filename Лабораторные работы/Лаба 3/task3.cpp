#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Shape {
protected:
    string color;
    string name;

public:
    Shape(string n, string c) : name(n), color(c) {}
    virtual ~Shape() {}
    
    virtual double calculateArea() const = 0;
    virtual double calculatePerimeter() const = 0;
    virtual void draw() const = 0;
    
    virtual void displayInfo() const {
        cout << "Фигура: " << name << ", Цвет: " << color << endl;
    }
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(string c, double r) : Shape("Круг", c), radius(r) {}
    
    double calculateArea() const override {
        return M_PI * radius * radius;
    }
    
    double calculatePerimeter() const override {
        return 2 * M_PI * radius;
    }
    
    void draw() const override {
        cout << "Рисуем круг радиусом " << radius << endl;
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(string c, double w, double h) : Shape("Прямоугольник", c), width(w), height(h) {}
    
    double calculateArea() const override {
        return width * height;
    }
    
    double calculatePerimeter() const override {
        return 2 * (width + height);
    }
    
    void draw() const override {
        cout << "Рисуем прямоугольник " << width << "x" << height << endl;
    }
};

class Triangle : public Shape {
private:
    double sideA, sideB, sideC;

public:
    Triangle(string c, double a, double b, double cc) : Shape("Треугольник", c), sideA(a), sideB(b), sideC(cc) {}
    
    double calculateArea() const override {
        double s = (sideA + sideB + sideC) / 2.0;
        return sqrt(s * (s - sideA) * (s - sideB) * (s - sideC));
    }
    
    double calculatePerimeter() const override {
        return sideA + sideB + sideC;
    }
    
    void draw() const override {
        cout << "Рисуем треугольник со сторонами " << sideA << ", " << sideB << ", " << sideC << endl;
    }
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle("Красный", 5.0));
    shapes.push_back(new Rectangle("Синий", 4.0, 6.0));
    shapes.push_back(new Triangle("Зеленый", 3.0, 4.0, 5.0));
    
    cout << "=== Демонстрация полиморфизма ===" << endl << endl;
    
    for (auto shape : shapes) {
        shape->displayInfo();
        shape->draw();
        cout << "Площадь: " << shape->calculateArea() << endl;
        cout << "Периметр: " << shape->calculatePerimeter() << endl;
        cout << endl;
    }
    
    for (auto shape : shapes) {
        delete shape;
    }
    
    return 0;
}
