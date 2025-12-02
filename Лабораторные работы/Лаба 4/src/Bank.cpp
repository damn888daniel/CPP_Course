// Подключаем заголовочный файл с объявлением класса Bank
#include "Bank.h"
#include <iostream>   // Для ввода-вывода (std::cout)
#include <algorithm>  // Для алгоритмов (std::remove_if)

// Приватный метод: ищет клиента по ID
// Возвращает указатель на клиента или nullptr, если не найден
Client* Bank::findClient(int id) {
    // Проходим по всем клиентам в векторе
    for (auto &c : clients) {
        // Если ID совпадает, возвращаем указатель на клиента
        if (c->getId() == id) {
            return c.get(); // .get() возвращает сырой указатель из unique_ptr
        }
    }
    // Клиент не найден
    return nullptr;
}

// Приватный метод: ищет счёт по номеру
// Возвращает указатель на счёт или nullptr, если не найден
BankAccount* Bank::findAccount(int accountNumber) {
    // Проходим по всем счетам в векторе
    for (auto &a : accounts) {
        // Если номер совпадает, возвращаем указатель на счёт
        if (a.getAccountNumber() == accountNumber) {
            return &a; // Возвращаем адрес элемента вектора
        }
    }
    // Счёт не найден
    return nullptr;
}

// Добавить нового клиента в банк
void Bank::addClient(std::unique_ptr<Client> client) {
    // Перемещаем умный указатель в вектор (std::move передаёт владение)
    clients.push_back(std::move(client));
}

// Удалить клиента по ID
// Возвращает true, если удаление прошло успешно
bool Bank::removeClient(int id) {
    // Проверяем, нет ли у клиента активных счетов
    for (auto &a : accounts) {
        // Если у клиента есть активный счёт, удаление невозможно
        if (a.getClientId() == id && a.isActive()) {
            std::cout << "У клиента есть активные счета, удалить нельзя.\n";
            return false;
        }
    }

    // Используем алгоритм std::remove_if для поиска клиента
    // Лямбда-функция проверяет, совпадает ли ID
    auto it = std::remove_if(clients.begin(), clients.end(),
                              [id](const std::unique_ptr<Client> &c) {
                                  return c->getId() == id;
                              });

    // Если клиент найден, удаляем его
    if (it != clients.end()) {
        clients.erase(it, clients.end()); // Удаляем элементы
        return true;
    }
    return false;
}

// Получить указатель на клиента по ID
Client* Bank::getClient(int id) {
    // Просто вызываем приватный метод поиска
    return findClient(id);
}

// Показать информацию обо всех клиентах
void Bank::viewClients() const {
    // Проверяем, есть ли клиенты
    if (clients.empty()) {
        std::cout << "Клиентов нет.\n";
    } else {
        // Проходим по всем клиентам и выводим их информацию
        for (const auto &c : clients) {
            c->displayInfo(); // Вызываем метод displayInfo() для каждого клиента
            std::cout << "-----------------------------\n";
        }
    }
}

// Редактировать данные клиента
void Bank::editClient(int id, const std::string &firstName, const std::string &lastName, const Address &address) {
    // Ищем клиента по ID
    Client *c = findClient(id);
    if (c) {
        // Если клиент найден, обновляем его данные
        c->setFirstName(firstName);
        c->setLastName(lastName);
        c->setAddress(address);
        std::cout << "Данные клиента обновлены.\n";
    } else {
        std::cout << "Клиент не найден.\n";
    }
}

// Проверить, принадлежит ли счёт клиенту
bool Bank::accountBelongsToClient(int clientId, int accountNumber) const {
    // Проходим по всем счетам
    for (const auto &a : accounts) {
        // Проверяем совпадение номера счёта и ID клиента
        if (a.getAccountNumber() == accountNumber && a.getClientId() == clientId) {
            return true; // Счёт принадлежит клиенту
        }
    }
    return false; // Счёт не принадлежит клиенту
}

// Открыть новый счёт для клиента
BankAccount* Bank::openAccount(int clientId, AccountType type, double initialDeposit, const Date &openDate) {
    // Проверяем, существует ли клиент
    Client *client = findClient(clientId);
    if (!client) {
        std::cout << "Клиент не найден.\n";
        return nullptr;
    }

    // Создаём новый счёт
    BankAccount account(clientId, type, initialDeposit, openDate);
    // Добавляем счёт в вектор
    accounts.push_back(account);
    std::cout << "Счёт успешно открыт.\n";

    // Возвращаем указатель на последний добавленный счёт
    return &accounts.back();
}

// Закрыть счёт
bool Bank::closeAccount(int accountNumber) {
    // Ищем счёт среди всех счетов
    for (auto &a : accounts) {
        if (a.getAccountNumber() == accountNumber) {
            // Проверяем, что баланс равен нулю
            if (a.getBalance() != 0.0) {
                std::cout << "Баланс счёта должен быть нулевым для закрытия.\n";
                return false;
            }
            // Проверяем, что счёт ещё активен
            if (!a.isActive()) {
                std::cout << "Счёт уже закрыт.\n";
                return false;
            }
            // Деактивируем счёт
            a.deactivate();
            std::cout << "Счёт закрыт.\n";
            return true;
        }
    }
    std::cout << "Счёт не найден.\n";
    return false;
}

// Получить все счета конкретного клиента
std::vector<BankAccount*> Bank::getClientAccounts(int clientId) {
    // Создаём вектор для результата
    std::vector<BankAccount*> results;

    // Проходим по всем счетам
    for (auto &a : accounts) {
        // Если счёт принадлежит клиенту, добавляем указатель в результат
        if (a.getClientId() == clientId) {
            results.push_back(&a);
        }
    }
    return results;
}

// Показать информацию обо всех счетах
void Bank::viewAccounts() const {
    // Проверяем, есть ли счета
    if (accounts.empty()) {
        std::cout << "Счётов нет.\n";
    } else {
        // Проходим по всем счетам и выводим информацию
        for (const auto &a : accounts) {
            a.displayInfo();
            std::cout << "-----------------------------\n";
        }
    }
}

// Пополнить счёт
void Bank::deposit(int accountNumber, double amount) {
    // Ищем счёт по номеру
    BankAccount *a = findAccount(accountNumber);
    if (a) {
        // Если счёт найден, пополняем его
        a->deposit(amount);
        std::cout << "Пополнение выполнено.\n";
    } else {
        std::cout << "Счёт не найден.\n";
    }
}

// Снять деньги со счёта
void Bank::withdraw(int accountNumber, double amount) {
    // Ищем счёт по номеру
    BankAccount *a = findAccount(accountNumber);
    if (a) {
        // Пытаемся снять деньги
        if (a->withdraw(amount)) {
            std::cout << "Снятие выполнено.\n";
        } else {
            std::cout << "Недостаточно средств.\n"; // Недостаточно средств
        }
    } else {
        std::cout << "Счёт не найден.\n";
    }
}

// Перевести деньги между счетами
void Bank::transfer(int fromAccountNumber, int toAccountNumber, double amount) {
    // Ищем оба счёта
    BankAccount *from = findAccount(fromAccountNumber);
    BankAccount *to = findAccount(toAccountNumber);

    // Проверяем, что оба счёта существуют
    if (!from || !to) {
        std::cout << "Один или оба счёта не найдены.\n";
        return;
    }

    // Проверяем, что оба счёта активны
    if (!from->isActive() || !to->isActive()) {
        std::cout << "Один из счетов не активен.\n";
        return;
    }

    // Выполняем перевод
    if (from->transferTo(*to, amount)) {
        std::cout << "Перевод выполнен.\n";
    } else {
        std::cout << "Недостаточно средств.\n"; // Недостаточно средств
    }
}

// Показать общую информацию о банке
void Bank::printBankInfo() const {
    std::cout << "Информация о банке:\n";
    // Выводим количество клиентов
    std::cout << "Всего клиентов: " << clients.size() << "\n";
    // Выводим количество счетов
    std::cout << "Всего счетов: " << accounts.size() << "\n";
}
