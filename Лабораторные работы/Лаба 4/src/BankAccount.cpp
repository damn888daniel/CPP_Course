#include "BankAccount.h"
#include <iostream>

int BankAccount::accountCounter = 1000;

BankAccount::BankAccount(int clientId, AccountType type, double initialDeposit, const Date &openDate)
    : accountNumber(++accountCounter), clientId(clientId), balance(initialDeposit),
      type(type), openDate(openDate), active(true) {}

int BankAccount::getAccountNumber() const {
    return accountNumber;
}

int BankAccount::getClientId() const {
    return clientId;
}

double BankAccount::getBalance() const {
    return balance;
}

AccountType BankAccount::getType() const {
    return type;
}

Date BankAccount::getOpenDate() const {
    return openDate;
}

bool BankAccount::isActive() const {
    return active;
}

void BankAccount::deposit(double amount) {
    if (amount > 0) {
        balance += amount;
    }
}

bool BankAccount::withdraw(double amount) {
    if (amount > 0 && balance >= amount) {
        balance -= amount;
        return true;
    }
    return false;
}

bool BankAccount::transferTo(BankAccount &recipient, double amount) {
    if (this->withdraw(amount)) {
        recipient.deposit(amount);
        return true;
    }
    return false;
}

void BankAccount::deactivate() {
    active = false;
}

void BankAccount::activate() {
    active = true;
}

int BankAccount::getAccountCount() {
    return accountCounter - 1000;
}

void BankAccount::displayInfo() const {
    std::cout << "Номер счёта: " << accountNumber << "\n";
    std::cout << "ID клиента: " << clientId << "\n";
    std::cout << "Баланс: " << balance << "\n";
    std::cout << "Тип: " << (type == AccountType::Checking ? "Расчётный" : "Сберегательный") << "\n";
    std::cout << "Дата открытия: " << openDate.toString() << "\n";
    std::cout << "Статус: " << (active ? "Активен" : "Неактивен") << "\n";
}
