#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template<typename T>
class Stack {
private:
    vector<T> elements;
    int capacity;

public:
    Stack(int size = 10) : capacity(size) {}
    
    // TODO: Реализовать методы:
    // - void push(const T& element)
    
    // Метод для добавления элемента в стек
    void push(const T& element) {
        if (isFull()) {  // Проверка переполнения стека
            throw overflow_error("Стек переполнен!");
        }
        elements.push_back(element);  // Добавление элемента в конец вектора (вершина стека)
    }
    // Метод для извлечения элемента из стека
    T pop() {
        if (isEmpty()) {  // Проверка пустоты стека
            throw underflow_error("Стек пуст!");
        }
        T element = elements.back();  // Получение элемента с вершины стека
        elements.pop_back();          // Удаление элемента с вершины
        return element;               // Возврат извлеченного элемента
    }
    
    // - T top() const
    
    // Метод для просмотра элемента на вершине стека без удаления
    T top() const {
        if (isEmpty()) {  // Проверка пустоты стека
            throw underflow_error("Стек пуст!");
        }
        return elements.back();  // Возврат элемента с вершины без удаления
    }
    
    // - bool isEmpty() const
    
    // Метод для проверки, пуст ли стек
    bool isEmpty() const {
        return elements.empty();
    }
    
    // - bool isFull() const
    
    // Метод для проверки, заполнен ли стек до максимальной вместимости
    bool isFull() const {
        return elements.size() >= capacity;
    }
    
    // - int size() const
    
    // Метод для получения текущего размера стека
    int size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "Стек: ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

template<typename T>
class Queue {
private:
    vector<T> elements;
    int capacity;

public:
    Queue(int size = 10) : capacity(size) {}
    
    // TODO: Реализовать методы:
    // - void enqueue(const T& element)
    
    // Метод для добавления элемента в очередь
    void enqueue(const T& element) {
        if (isFull()) {  // Проверка переполнения очереди
            throw overflow_error("Очередь переполнена!");
        }
        elements.push_back(element);  // Добавление элемента в конец очереди
    }
    
    // - T dequeue()
    
    // Метод для извлечения элемента из очереди
    T dequeue() {
        if (isEmpty()) {  // Проверка пустоты очереди
            throw underflow_error("Очередь пуста!");
        }
        T element = elements.front();       // Получение первого элемента очереди
        elements.erase(elements.begin());   // Удаление первого элемента
        return element;                     // Возврат извлеченного элемента
    }
    
    // - T front() const
    
    // Метод для просмотра первого элемента очереди без удаления
    T front() const {
        if (isEmpty()) {  // Проверка пустоты очереди
            throw underflow_error("Очередь пуста!");
        }
        return elements.front();  // Возврат первого элемента без удаления
    }
    
    // - bool isEmpty() const
    
    // Метод для проверки, пуста ли очередь
    bool isEmpty() const {
        return elements.empty();
    }
    
    // - bool isFull() const
    
    // Метод для проверки, заполнена ли очередь до максимальной вместимости
    bool isFull() const {
        return elements.size() >= capacity;
    }
    
    // - int size() const
    
    // Метод для получения текущего размера очереди
    int size() const {
        return elements.size();
    }
    
    void display() const {
        cout << "Очередь: ";
        for (const auto& elem : elements) {
            cout << elem << " ";
        }
        cout << endl;
    }
};

int main() {
    // TODO: Протестировать Stack и Queue с разными типами данных:
    // - int
    // - double
    // - string
    
    cout << "=== Тестирование Stack<int> ===" << endl;
    // Создание стека для целых чисел с максимальной вместимостью 5
    Stack<int> intStack(5);
    
    // Добавление элементов в стек
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);
    intStack.push(40);
    intStack.display();
    
    cout << "Верхний элемент: " << intStack.top() << endl;  // Просмотр вершины стека
    cout << "Размер: " << intStack.size() << endl;
    
    // Извлечение элементов из стека
    cout << "Извлекаем: " << intStack.pop() << endl;
    cout << "Извлекаем: " << intStack.pop() << endl;
    intStack.display();
    cout << endl;
    
    cout << "=== Тестирование Stack<double> ===" << endl;
    // Создание стека для чисел с плавающей точкой
    Stack<double> doubleStack(5);
    
    doubleStack.push(3.14);
    doubleStack.push(2.71);
    doubleStack.push(1.41);
    doubleStack.display();
    
    cout << "Верхний элемент: " << doubleStack.top() << endl;
    cout << "Извлекаем: " << doubleStack.pop() << endl;
    doubleStack.display();
    cout << endl;
    
    cout << "=== Тестирование Stack<string> ===" << endl;
    // Создание стека для строк
    Stack<string> stringStack(5);
    
    stringStack.push("Hello");
    stringStack.push("World");
    stringStack.push("C++");
    stringStack.display();
    
    cout << "Верхний элемент: " << stringStack.top() << endl;
    cout << "Извлекаем: " << stringStack.pop() << endl;
    stringStack.display();
    cout << endl;
    
    cout << "=== Тестирование Queue<int> ===" << endl;
    // Создание очереди для целых чисел
    Queue<int> intQueue(5);
    
    // Добавление элементов в очередь
    intQueue.enqueue(100);
    intQueue.enqueue(200);
    intQueue.enqueue(300);
    intQueue.enqueue(400);
    intQueue.display();
    
    cout << "Первый элемент: " << intQueue.front() << endl;  // Просмотр первого элемента
    cout << "Размер: " << intQueue.size() << endl;
    
    // Извлечение элементов из очереди
    cout << "Извлекаем: " << intQueue.dequeue() << endl;
    cout << "Извлекаем: " << intQueue.dequeue() << endl;
    intQueue.display();
    cout << endl;
    
    cout << "=== Тестирование Queue<string> ===" << endl;
    // Создание очереди для строк
    Queue<string> stringQueue(5);
    
    stringQueue.enqueue("First");
    stringQueue.enqueue("Second");
    stringQueue.enqueue("Third");
    stringQueue.display();
    
    cout << "Первый элемент: " << stringQueue.front() << endl;
    cout << "Извлекаем: " << stringQueue.dequeue() << endl;
    stringQueue.display();
    cout << endl;
    
    cout << "=== Тестирование переполнения ===" << endl;
    try {
        Stack<int> smallStack(2);  // Стек с малой вместимостью
        smallStack.push(1);
        smallStack.push(2);
        cout << "Стек заполнен. Попытка добавить еще..." << endl;
        smallStack.push(3);  // Это вызовет исключение overflow_error
    } catch (const overflow_error& e) {
        cout << "Исключение: " << e.what() << endl;  // Обработка исключения
    }
    
    cout << endl;
    cout << "=== Тестирование извлечения из пустой структуры ===" << endl;
    try {
        Queue<int> emptyQueue(5);  // Пустая очередь
        cout << "Попытка извлечь из пустой очереди..." << endl;
        emptyQueue.dequeue();  // Это вызовет исключение underflow_error
    } catch (const underflow_error& e) {
        cout << "Исключение: " << e.what() << endl;  // Обработка исключения
    }
    
    return 0;
}