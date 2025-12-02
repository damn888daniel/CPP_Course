#include "Transaction.h"
#include <iostream>
#include <iomanip>
#include <sstream>

int Transaction::transactionCounter = 0;

Transaction::Transaction(int fromAccount, int toAccount, double amount, TransactionType type)
    : id(++transactionCounter), fromAccount(fromAccount), toAccount(toAccount),
      amount(amount), type(type) {
    std::time_t now = std::time(nullptr);
    std::tm *ltm = std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(ltm, "%d.%m.%Y %H:%M:%S");
    timestamp = oss.str();
}

int Transaction::getId() const {
    return id;
}

int Transaction::getFromAccount() const {
    return fromAccount;
}

int Transaction::getToAccount() const {
    return toAccount;
}

double Transaction::getAmount() const {
    return amount;
}

std::string Transaction::getTimestamp() const {
    return timestamp;
}

TransactionType Transaction::getType() const {
    return type;
}

void Transaction::displayInfo() const {
    std::cout << "ID транзакции: " << id << "\n";
    std::cout << "Тип: ";
    switch (type) {
        case TransactionType::Deposit:
            std::cout << "Пополнение";
            break;
        case TransactionType::Withdrawal:
            std::cout << "Снятие";
            break;
        case TransactionType::Transfer:
            std::cout << "Перевод";
            break;
    }
    std::cout << "\n";
    std::cout << "Со счёта: " << fromAccount << "\n";
    std::cout << "На счёт: " << toAccount << "\n";
    std::cout << "Сумма: " << amount << "\n";
    std::cout << "Дата/время: " << timestamp << "\n";
}

int Transaction::getTransactionCount() {
    return transactionCounter;
}
