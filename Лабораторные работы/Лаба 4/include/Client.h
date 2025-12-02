// Защита от повторного подключения заголовочного файла
#ifndef CLIENT_H
#define CLIENT_H

#include <string>     // Для использования std::string
#include "Address.h"  // Подключаем структуру Address
#include "Date.h"     // Подключаем структуру Date

// Класс для представления клиента банка
class Client {
private:
    int id;                      // Уникальный идентификатор клиента
    std::string firstName;       // Имя клиента
    std::string lastName;        // Фамилия клиента
    Address address;             // Адрес проживания клиента
    Date registrationDate;       // Дата регистрации в банке
    static int clientCounter;    // Статический счётчик для автоматической генерации ID

public:
    // Конструктор по умолчанию (создаёт пустого клиента)
    Client();

    // Конструктор с параметрами (создаёт клиента с указанными данными)
    // firstName - имя
    // lastName - фамилия
    // address - адрес
    // registrationDate - дата регистрации
    Client(const std::string &firstName, const std::string &lastName, const Address &address, const Date &registrationDate);

    // Виртуальный деструктор (нужен для корректного удаления объектов через указатель на базовый класс)
    virtual ~Client();

    // Получить ID клиента
    int getId() const;

    // Получить имя клиента
    std::string getFirstName() const;

    // Получить фамилию клиента
    std::string getLastName() const;

    // Получить адрес клиента
    Address getAddress() const;

    // Получить дату регистрации клиента
    Date getRegistrationDate() const;

    // Установить новое имя клиента
    void setFirstName(const std::string &firstName);

    // Установить новую фамилию клиента
    void setLastName(const std::string &lastName);

    // Установить новый адрес клиента
    void setAddress(const Address &address);

    // Установить новую дату регистрации
    void setRegistrationDate(const Date &registrationDate);

    // Получить общее количество созданных клиентов (статический метод)
    static int getClientCount();

    // Показать информацию о клиенте (виртуальный метод для возможности переопределения)
    virtual void displayInfo() const;
};

#endif 
