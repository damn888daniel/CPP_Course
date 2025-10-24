#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Vehicle {
protected:
    string brand;
    string model;
    int year;
    double fuelLevel;

public:
    Vehicle(string b, string m, int y) : brand(b), model(m), year(y), fuelLevel(100) {}
    virtual ~Vehicle() {}
    
    virtual void startEngine() = 0;
    virtual void stopEngine() = 0;
    virtual void refuel(double amount) = 0;
    
    virtual void displayInfo() const {
        cout << brand << " " << model << " (" << year << ")" << endl;
        cout << "Уровень топлива: " << fuelLevel << "%" << endl;
    }
    
    double getFuelLevel() const { return fuelLevel; }
    void setFuelLevel(double level) { 
        if (level >= 0 && level <= 100) fuelLevel = level; 
    }
};

class Car : public Vehicle {
private:
    int doors;
    string transmission;

public:
    Car(string b, string m, int y, int d, string trans) 
        : Vehicle(b, m, y), doors(d), transmission(trans) {}
    
    void startEngine() override {
        cout << "Автомобиль " << brand << " " << model << ": Двигатель запущен. Врум-врум!" << endl;
    }
    
    void stopEngine() override {
        cout << "Автомобиль " << brand << " " << model << ": Двигатель заглушен." << endl;
    }
    
    void refuel(double amount) override {
        double newLevel = fuelLevel + amount;
        if (newLevel > 100) newLevel = 100;
        fuelLevel = newLevel;
        cout << "Заправка автомобиля. Новый уровень топлива: " << fuelLevel << "%" << endl;
    }
    
    void displayInfo() const override {
        cout << "=== Автомобиль ===" << endl;
        Vehicle::displayInfo();
        cout << "Количество дверей: " << doors << endl;
        cout << "Трансмиссия: " << transmission << endl;
    }
};

class Motorcycle : public Vehicle {
private:
    bool hasFairing;

public:
    Motorcycle(string b, string m, int y, bool fairing) 
        : Vehicle(b, m, y), hasFairing(fairing) {}
    
    void startEngine() override {
        cout << "Мотоцикл " << brand << " " << model << ": ВРУМ-ВРУМ! Двигатель ревёт!" << endl;
    }
    
    void stopEngine() override {
        cout << "Мотоцикл " << brand << " " << model << ": Двигатель выключен." << endl;
    }
    
    void refuel(double amount) override {
        double newLevel = fuelLevel + amount;
        if (newLevel > 100) newLevel = 100;
        fuelLevel = newLevel;
        cout << "Заправка мотоцикла. Новый уровень топлива: " << fuelLevel << "%" << endl;
    }
    
    void displayInfo() const override {
        cout << "=== Мотоцикл ===" << endl;
        Vehicle::displayInfo();
        cout << "Обтекатель: " << (hasFairing ? "Да" : "Нет") << endl;
    }
    
    void wheelie() {
        cout << brand << " " << model << " делает вилли!" << endl;
    }
};

int main() {
    
    vector<Vehicle*> vehicles;
    vehicles.push_back(new Car("Toyota", "Camry", 2020, 4, "Автомат"));
    vehicles.push_back(new Motorcycle("Harley-Davidson", "Street 750", 2019, false));
    vehicles.push_back(new Car("BMW", "X5", 2021, 5, "Автомат"));
    
    cout << "=== Демонстрация полиморфизма ===" << endl << endl;
    
    for (auto vehicle : vehicles) {
        vehicle->displayInfo();
        vehicle->startEngine();
        vehicle->setFuelLevel(50);
        vehicle->refuel(30);
        vehicle->stopEngine();
        cout << endl;
    }
    
    Motorcycle* bike = dynamic_cast<Motorcycle*>(vehicles[1]);
    if (bike) {
        bike->wheelie();
    }
    
    for (auto vehicle : vehicles) {
        delete vehicle;
    }
    
    return 0;
}
