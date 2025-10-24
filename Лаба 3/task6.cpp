#include <iostream>
#include <string>
using namespace std;

class BankAccount {
private:
    string accountNumber;
    string ownerName;
    double balance;
    static int totalAccounts;           // Общее количество счетов
    static double totalBankBalance;     // Общий баланс банка
    const double MIN_BALANCE = 10.0;    // Минимальный баланс

public:
    BankAccount(string accNum, string owner, double initialBalance) 
        : accountNumber(accNum), ownerName(owner), balance(initialBalance) {
        totalAccounts++;
        totalBankBalance += balance;
        cout << "Создан счет " << accountNumber << " для " << ownerName << endl;
    }
    
    ~BankAccount() {
        totalAccounts--;
        totalBankBalance -= balance;
        cout << "Счет " << accountNumber << " закрыт." << endl;
    }
    
    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            totalBankBalance += amount;
            cout << "Пополнение счета " << accountNumber << " на " << amount << " руб." << endl;
            cout << "Новый баланс: " << balance << " руб." << endl;
        } else {
            cout << "Неверная сумма пополнения." << endl;
        }
    }
    
    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Неверная сумма для снятия." << endl;
            return false;
        }
        
        if (balance - amount < MIN_BALANCE) {
            cout << "Недостаточно средств. Минимальный баланс: " << MIN_BALANCE << " руб." << endl;
            return false;
        }
        
        balance -= amount;
        totalBankBalance -= amount;
        cout << "Снятие со счета " << accountNumber << ": " << amount << " руб." << endl;
        cout << "Новый баланс: " << balance << " руб." << endl;
        return true;
    }
    
    void displayAccountInfo() const {
        cout << "=== Информация о счете ===" << endl;
        cout << "Номер счета: " << accountNumber << endl;
        cout << "Владелец: " << ownerName << endl;
        cout << "Баланс: " << balance << " руб." << endl;
        cout << "Минимальный баланс: " << MIN_BALANCE << " руб." << endl;
    }
    
    static int getTotalAccounts() {
        return totalAccounts;
    }
    
    static double getTotalBankBalance() {
        return totalBankBalance;
    }
    
    static double getAverageBalance() {
        if (totalAccounts > 0) {
            return totalBankBalance / totalAccounts;
        }
        return 0.0;
    }
};

int BankAccount::totalAccounts = 0;
double BankAccount::totalBankBalance = 0.0;

int main() {
    
    cout << "=== Создание счетов ===" << endl;
    BankAccount* acc1 = new BankAccount("001", "Иван Иванов", 5000.0);
    BankAccount* acc2 = new BankAccount("002", "Петр Петров", 10000.0);
    BankAccount* acc3 = new BankAccount("003", "Мария Сидорова", 15000.0);
    
    cout << "\n=== Статистика банка ===" << endl;
    cout << "Всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб." << endl;
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб." << endl;
    
    cout << "\n=== Операции со счетами ===" << endl;
    acc1->displayAccountInfo();
    cout << endl;
    
    acc1->deposit(2000);
    acc1->withdraw(3000);
    cout << endl;
    
    acc2->displayAccountInfo();
    cout << endl;
    
    acc2->withdraw(8000);
    cout << endl;
    
    cout << "=== Обновленная статистика банка ===" << endl;
    cout << "Всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб." << endl;
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб." << endl;
    
    cout << "\n=== Закрытие счета ===" << endl;
    delete acc2;
    
    cout << "\n=== Финальная статистика ===" << endl;
    cout << "Всего счетов: " << BankAccount::getTotalAccounts() << endl;
    cout << "Общий баланс банка: " << BankAccount::getTotalBankBalance() << " руб." << endl;
    cout << "Средний баланс: " << BankAccount::getAverageBalance() << " руб." << endl;
    
    delete acc1;
    delete acc3;
    
    return 0;
}
