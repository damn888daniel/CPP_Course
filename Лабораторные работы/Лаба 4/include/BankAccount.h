// Защита от повторного подключения заголовочного файла
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include "Date.h" // Подключаем структуру Date

// Перечисление для типов банковских счетов
enum class AccountType {
    Checking,  // Расчётный счёт (текущий счёт для повседневных операций)
    Savings    // Сберегательный счёт (накопительный счёт)
};

// Класс для представления банковского счёта
class BankAccount {
private:
    int accountNumber;             // Уникальный номер счёта
    int clientId;                  // ID клиента-владельца этого счёта
    double balance;                // Текущий баланс счёта
    AccountType type;              // Тип счёта (Checking или Savings)
    Date openDate;                 // Дата открытия счёта
    bool active;                   // Статус счёта (true - активен, false - закрыт)
    static int accountCounter;     // Статический счётчик для автоматической генерации номеров счетов

public:
    // Конструктор для создания нового банковского счёта
    // clientId - ID владельца счёта
    // type - тип счёта (Checking или Savings)
    // initialDeposit - начальная сумма при открытии счёта
    // openDate - дата открытия счёта
    BankAccount(int clientId, AccountType type, double initialDeposit, const Date &openDate);

    // Получить номер счёта
    int getAccountNumber() const;

    // Получить ID владельца счёта
    int getClientId() const;

    // Получить текущий баланс
    double getBalance() const;

    // Получить тип счёта
    AccountType getType() const;

    // Получить дату открытия счёта
    Date getOpenDate() const;

    // Проверить, активен ли счёт
    bool isActive() const;

    // Пополнить счёт на указанную сумму
    // amount - сумма пополнения
    void deposit(double amount);

    // Снять деньги со счёта
    // amount - сумма для снятия
    // Возвращает true, если операция успешна, false - если недостаточно средств
    bool withdraw(double amount);

    // Перевести деньги на другой счёт
    // recipient - счёт получателя
    // amount - сумма перевода
    // Возвращает true, если операция успешна
    bool transferTo(BankAccount &recipient, double amount);

    // Закрыть счёт (деактивировать)
    void deactivate();

    // Активировать счёт (открыть снова)
    void activate();

    // Получить общее количество созданных счетов (статический метод)
    static int getAccountCount();

    // Показать информацию о счёте
    void displayInfo() const;
};

#endif 
