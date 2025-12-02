// Защита от повторного подключения заголовочного файла
#ifndef BANK_H
#define BANK_H

#include <vector>  // Для использования динамических массивов
#include <memory>  // Для использования умных указателей (unique_ptr)
#include "Client.h"        // Подключаем класс Client
#include "BankAccount.h"   // Подключаем класс BankAccount

// Класс для управления банком (хранит клиентов и их счета)
class Bank {
private:
    // Вектор умных указателей на клиентов (unique_ptr автоматически освобождает память)
    std::vector<std::unique_ptr<Client>> clients;

    // Вектор банковских счетов
    std::vector<BankAccount> accounts;

    // Приватный метод для поиска клиента по ID
    // Возвращает указатель на клиента или nullptr, если не найден
    Client* findClient(int id);

    // Приватный метод для поиска счёта по номеру
    // Возвращает указатель на счёт или nullptr, если не найден
    BankAccount* findAccount(int accountNumber);

public:
    // Конструктор по умолчанию
    Bank() = default;

    // Добавить нового клиента в банк
    // client - умный указатель на объект клиента
    void addClient(std::unique_ptr<Client> client);

    // Удалить клиента по ID
    // id - идентификатор клиента
    // Возвращает true, если удаление успешно
    bool removeClient(int id);

    // Получить указатель на клиента по ID
    // id - идентификатор клиента
    // Возвращает указатель на клиента или nullptr
    Client* getClient(int id);

    // Показать информацию обо всех клиентах
    void viewClients() const;

    // Редактировать данные клиента
    // id - идентификатор клиента
    // firstName - новое имя
    // lastName - новая фамилия
    // address - новый адрес
    void editClient(int id, const std::string &firstName, const std::string &lastName, const Address &address);

    // Проверить, принадлежит ли счёт клиенту
    // clientId - ID клиента
    // accountNumber - номер счёта
    // Возвращает true, если счёт принадлежит клиенту
    bool accountBelongsToClient(int clientId, int accountNumber) const;

    // Открыть новый счёт для клиента
    // clientId - ID клиента
    // type - тип счёта (Checking или Savings)
    // initialDeposit - начальная сумма
    // openDate - дата открытия
    // Возвращает указатель на созданный счёт
    BankAccount* openAccount(int clientId, AccountType type, double initialDeposit, const Date &openDate);

    // Закрыть счёт
    // accountNumber - номер счёта для закрытия
    // Возвращает true, если закрытие успешно
    bool closeAccount(int accountNumber);

    // Получить все счета конкретного клиента
    // clientId - ID клиента
    // Возвращает вектор указателей на счета
    std::vector<BankAccount*> getClientAccounts(int clientId);

    // Показать информацию обо всех счетах
    vo2id viewAccounts() const;

    // Пополнить счёт
    // accountNumber - номер счёта
    // amount - сумма пополнения
    void deposit(int accountNumber, double amount);

    // Снять деньги со счёта
    // accountNumber - номер счёта
    // amount - сумма для снятия
    void withdraw(int accountNumber, double amount);

    // Перевести деньги между счетами
    // fromAccountNumber - номер счёта отправителя
    // toAccountNumber - номер счёта получателя
    // amount - сумма перевода
    void transfer(int fromAccountNumber, int toAccountNumber, double amount);

    // Показать общую информацию о банке (количество клиентов, счетов и т.д.)
    void printBankInfo() const;
};

#endif 
