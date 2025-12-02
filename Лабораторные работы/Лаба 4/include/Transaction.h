#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>
#include <chrono>
#include <ctime>

enum class TransactionType {
    Deposit,  // пополнение
    Withdrawal,  // снятие
    Transfer  // перевод
};

class Transaction {
private:
    int id;  // ID транзакции
    int fromAccount;  // счёт отправителя
    int toAccount;  // счёт получателя
    double amount;  // сумма
    std::string timestamp;  // время операции
    TransactionType type;  // тип операции
    static int transactionCounter;  // счётчик транзакций

public:
    Transaction(int fromAccount, int toAccount, double amount, TransactionType type);
    int getId() const;
    int getFromAccount() const;
    int getToAccount() const;
    double getAmount() const;
    std::string getTimestamp() const;
    TransactionType getType() const;
    void displayInfo() const;
    static int getTransactionCount();
};

#endif
