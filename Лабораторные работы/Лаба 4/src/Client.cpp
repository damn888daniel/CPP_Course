#include "Client.h"
#include <iostream>

int Client::clientCounter = 0;  // инициализация статического счетчика

Client::Client() : id(++clientCounter), firstName("Неизвестно"), lastName("Неизвестно"), address(), registrationDate() {}  // конструктор по умолчанию

Client::Client(const std::string &firstName, const std::string &lastName, const Address &address, const Date &registrationDate)
    : id(++clientCounter), firstName(firstName), lastName(lastName), address(address), registrationDate(registrationDate) {}  // конструктор с параметрами

Client::~Client() {}  // виртуальный деструктор

int Client::getId() const { return id; }  // получить ID
std::string Client::getFirstName() const { return firstName; }  // получить имя
std::string Client::getLastName() const { return lastName; }  // получить фамилию
Address Client::getAddress() const { return address; }  // получить адрес
Date Client::getRegistrationDate() const { return registrationDate; }  // получить дату регистрации

void Client::setFirstName(const std::string &firstName) { this->firstName = firstName; }  // установить имя
void Client::setLastName(const std::string &lastName) { this->lastName = lastName; }  // установить фамилию
void Client::setAddress(const Address &address) { this->address = address; }  // установить адрес
void Client::setRegistrationDate(const Date &registrationDate) { this->registrationDate = registrationDate; }  // установить дату

int Client::getClientCount() { return clientCounter; }  // получить количество клиентов

void Client::displayInfo() const {  // показать информацию
    std::cout << "ID клиента: " << id << "\n";  // ID клиента
    std::cout << "Имя: " << firstName << " " << lastName << "\n";  // имя и фамилия
    std::cout << "Адрес: " << address.streetAndHouse << ", " << address.city << ", " << address.postalIndex << ", " << address.country << "\n";  // адрес
    std::cout << "Дата регистрации: " << registrationDate.toString() << "\n";  // дата регистрации
}
