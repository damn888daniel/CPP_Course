// Подключаем необходимые библиотеки
#include <iostream>  // Для ввода-вывода (std::cin, std::cout)
#include <memory>    // Для умных указателей (std::unique_ptr, std::make_unique)
#include <limits>    // Для очистки буфера ввода (std::numeric_limits)
#include "Bank.h"    // Подключаем класс Bank

// Функция для безопасного чтения целого числа
// Если пользователь вводит не число, функция запросит ввод повторно
int readInt() {
    int value;  // Переменная для хранения введённого значения
    // Цикл работает, пока ввод некорректен
    while (!(std::cin >> value)) {  // Пытаемся считать int, пока не получится
        std::cin.clear();  // Сбрасываем флаг ошибки потока
        // Очищаем буфер ввода до конца строки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Попробуйте снова: ";  // Просим ввести снова
    }
    return value;  // Возвращаем корректно введённое число
}

// Функция для безопасного чтения вещественного числа (double)
double readDouble() {
    double value;  // Переменная для хранения введённого значения
    // Цикл работает, пока ввод некорректен
    while (!(std::cin >> value)) {  // Пытаемся считать double, пока не получится
        std::cin.clear();  // Сбрасываем флаг ошибки потока
        // Очищаем буфер ввода до конца строки
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Некорректный ввод. Попробуйте снова: ";  // Просим ввести снова
    }
    return value;  // Возвращаем корректно введённое число
}

// Функция для чтения даты от пользователя
Date readDate() {
    std::cout << "Введите день: ";  // Просим ввести день
    int d = readInt();           // Читаем день
    std::cout << "Введите месяц: ";  // Просим ввести месяц
    int m = readInt();             // Читаем месяц
    std::cout << "Введите год: ";   // Просим ввести год
    int y = readInt();             // Читаем год
    return Date(d, m, y);  // Создаём и возвращаем объект Date
}

// Меню для сотрудника: доступ ко всем функциям банка
void employeePortal(Bank &bank) {
    bool running = true;  // Флаг продолжения работы меню

    while (running) {  // Цикл меню сотрудника
        std::cout << "\n=== Меню сотрудника ===\n";  // Заголовок меню
        std::cout << "1. Добавить клиента\n";               
        std::cout << "2. Показать клиентов\n";              
        std::cout << "3. Изменить клиента\n";           
        std::cout << "4. Удалить клиента\n";           
        std::cout << "5. Открыть счёт\n";               
        std::cout << "6. Показать все счета\n";         
        std::cout << "7. Показать счета клиента\n";     
        std::cout << "8. Пополнить счёт\n";             
        std::cout << "9. Снять деньги\n";               
        std::cout << "10. Перевести деньги\n";          
        std::cout << "11. Закрыть счёт\n";              
        std::cout << "12. Информация о банке\n";        
        std::cout << "0. Выйти\n";                     
        std::cout << "Выберите пункт: ";  

        int choice = readInt();  // Чтение выбора

        switch (choice) {  // Разбор выбранного пункта
            case 1: {  // Добавить клиента
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера перед getline

                std::string firstName;  // Имя клиента
                std::cout << "Введите имя: ";  // Запрос имени
                std::getline(std::cin, firstName);  // Чтение имени

                std::string lastName;  // Фамилия клиента
                std::cout << "Введите фамилию: ";  // Запрос фамилии
                std::getline(std::cin, lastName);  // Чтение фамилии

                std::string street, city, index, country;  // Адресные поля
                std::cout << "Введите улицу и дом: ";  // Запрос улицы
                std::getline(std::cin, street);  // Чтение улицы
                std::cout << "Введите город: ";  // Запрос города
                std::getline(std::cin, city);  // Чтение города
                std::cout << "Введите индекс: ";  // Запрос индекса
                std::getline(std::cin, index);  // Чтение индекса
                std::cout << "Введите страну: ";  // Запрос страны
                std::getline(std::cin, country);  // Чтение страны

                Address addr(street, city, index, country);  // Создание адреса

                std::cout << "Введите дату регистрации:\n";  // Подсказка даты
                Date regDate = readDate();  // Чтение даты регистрации

                auto client = std::make_unique<Client>(firstName, lastName, addr, regDate);  // Новый клиент
                bank.addClient(std::move(client));  // Добавление в банк
                std::cout << "Клиент успешно добавлен.\n";  // Подтверждение
                break;  // Выход из case
            }

            case 2: {  // Показать всех клиентов
                bank.viewClients();  // Вызов отображения
                break;  // Выход из case
            }

            case 3: {  // Редактировать клиента
                std::cout << "Введите ID клиента для изменения: ";  // Запрос ID
                int id = readInt();  // Чтение ID

                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // Очистка буфера

                std::string firstName, lastName;  // Новые имя/фамилия
                std::cout << "Введите новое имя: ";  // Запрос нового имени
                std::getline(std::cin, firstName);  // Чтение имени
                std::cout << "Введите новую фамилию: ";  // Запрос новой фамилии
                std::getline(std::cin, lastName);  // Чтение фамилии

                std::string street, city, index, country;  // Новый адрес
                std::cout << "Введите новую улицу и дом: ";  // Запрос улицы
                std::getline(std::cin, street);  // Чтение улицы
                std::cout << "Введите новый город: ";  // Запрос города
                std::getline(std::cin, city);  // Чтение города
                std::cout << "Введите новый индекс: ";  // Запрос индекса
                std::getline(std::cin, index);  // Чтение индекса
                std::cout << "Введите новую страну: ";  // Запрос страны
                std::getline(std::cin, country);  // Чтение страны

                Address addr(street, city, index, country);  // Новый адрес
                bank.editClient(id, firstName, lastName, addr);  // Применяем изменения
                break;  // Выход из case
            }

            case 4: {  // Удалить клиента
                std::cout << "Введите ID клиента для удаления: ";  // Запрос ID
                int id = readInt();  // Чтение ID

                if (bank.removeClient(id)) {  // Попытка удаления
                    std::cout << "Клиент удалён.\n";  // Успех
                } else {
                    std::cout << "Не удалось удалить клиента.\n";  // Ошибка
                }
                break;  // Выход из case
            }

            case 5: {  // Открыть счёт
                std::cout << "Введите ID клиента: ";  // Запрос ID клиента
                int clientId = readInt();  // Чтение ID клиента

                std::cout << "Введите тип счёта (1 - расчётный, 2 - сберегательный): ";  // Запрос типа
                int t = readInt();  // Тип счёта
                AccountType type = (t == 2) ? AccountType::Savings : AccountType::Checking;  // Выбор enum

                std::cout << "Введите начальный депозит: ";  // Запрос депозита
                double deposit = readDouble();  // Начальный баланс

                std::cout << "Введите дату открытия:\n";  // Подсказка ввода даты
                Date openDate = readDate();  // Дата открытия

                bank.openAccount(clientId, type, deposit, openDate);  // Создание счёта
                break;  // Выход из case
            }

            case 6: {  // Показать все счета
                bank.viewAccounts();  // Отображение всех счетов
                break;  // Выход из case
            }

            case 7: {  // Показать счета конкретного клиента
                std::cout << "Введите ID клиента: ";  // Запрос ID
                int clientId = readInt();  // Чтение ID

                auto accounts = bank.getClientAccounts(clientId);  // Получение счетов

                if (accounts.empty()) {  // Проверка наличия
                    std::cout << "У этого клиента нет счетов.\n";  // Сообщение об отсутствии
                } else {
                    for (auto *acc : accounts) {  // Перебор счетов
                        acc->displayInfo();  // Вывод информации
                        std::cout << "-----------------------------\n";  // Разделитель
                    }
                }
                break;  // Выход из case
            }

            case 8: {  // Пополнить счёт
                std::cout << "Введите номер счёта: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта

                std::cout << "Введите сумму пополнения: ";  // Запрос суммы
                double amount = readDouble();  // Сумма

                bank.deposit(accNum, amount);  // Пополнение
                break;  // Выход из case
            }

            case 9: {  // Снять деньги
                std::cout << "Введите номер счёта: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта

                std::cout << "Введите сумму снятия: ";  // Запрос суммы
                double amount = readDouble();  // Сумма

                bank.withdraw(accNum, amount);  // Снятие
                break;  // Выход из case
            }

            case 10: {  // Перевести деньги
                std::cout << "Введите номер счёта-отправителя: ";  // Запрос счёта отправителя
                int fromAcc = readInt();  // Счёт отправителя

                std::cout << "Введите номер счёта-получателя: ";  // Запрос счёта получателя
                int toAcc = readInt();  // Счёт получателя

                std::cout << "Введите сумму перевода: ";  // Запрос суммы
                double amount = readDouble();  // Сумма перевода

                bank.transfer(fromAcc, toAcc, amount);  // Перевод
                break;  // Выход из case
            }

            case 11: {  // Закрыть счёт
                std::cout << "Введите номер счёта для закрытия: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта

                bank.closeAccount(accNum);  // Закрытие
                break;  // Выход из case
            }

            case 12: {  // Показать информацию о банке
                bank.printBankInfo();  // Вывод статистики
                break;  // Выход из case
            }

            case 0: {  // Выход из режима сотрудника
                running = false;  // Завершаем цикл меню
                std::cout << "Выход из режима сотрудника.\n";  // Сообщение о выходе
                break;  // Выход из case
            }

            default: {  // Некорректный пункт меню
                std::cout << "Неверный пункт. Попробуйте ещё раз.\n";  // Сообщение об ошибке
                break;  // Выход из case
            }
        }
    }
}

// Меню для клиента: доступ только к своим счетам
void clientPortal(Bank &bank, int clientId) {
    bool running = true;  // Флаг продолжения меню клиента

    while (running) {  // Цикл меню клиента
        std::cout << "\n=== Меню клиента (ID: " << clientId << ") ===\n";  // Заголовок меню
        std::cout << "1. Посмотреть мои счета\n";  // Пункт меню
        std::cout << "2. Открыть счёт\n";  // Пункт меню
        std::cout << "3. Пополнить счёт\n";  // Пункт меню
        std::cout << "4. Снять деньги\n";  // Пункт меню
        std::cout << "5. Перевести деньги\n";  // Пункт меню
        std::cout << "6. Закрыть счёт\n";  // Пункт меню
        std::cout << "0. Выйти\n";  // Пункт выхода
        std::cout << "Выберите пункт: ";  // Запрос выбора

        int choice = readInt();  // Чтение выбора

        switch (choice) {  // Разбор пункта
            case 1: {  // Показать счета клиента
                auto accounts = bank.getClientAccounts(clientId);  // Получение счетов
                if (accounts.empty()) {  // Проверка наличия
                    std::cout << "У вас нет счетов.\n";  // Сообщение об отсутствии
                } else {
                    for (auto *acc : accounts) {  // Перебор счетов
                        acc->displayInfo();  // Вывод информации
                        std::cout << "-----------------------------\n";  // Разделитель
                    }
                }
                break;  // Выход из case
            }

            case 2: {  // Открыть счёт
                std::cout << "Введите тип счёта (1 - расчётный, 2 - сберегательный): ";  // Запрос типа
                int t = readInt();  // Тип счёта
                AccountType type = (t == 2) ? AccountType::Savings : AccountType::Checking;  // Выбор enum

                std::cout << "Введите начальный депозит: ";  // Запрос депозита
                double deposit = readDouble();  // Сумма депозита

                std::cout << "Введите дату открытия:\n";  // Подсказка ввода даты
                Date openDate = readDate();  // Дата

                bank.openAccount(clientId, type, deposit, openDate);  // Открытие
                break;  // Выход из case
            }

            case 3: {  // Пополнить свой счёт
                std::cout << "Введите номер счёта: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта
                if (!bank.accountBelongsToClient(clientId, accNum)) {  // Проверка владения
                    std::cout << "Счёт вам не принадлежит.\n";  // Сообщение об ошибке
                    break;  // Выход из case
                }

                std::cout << "Введите сумму пополнения: ";  // Запрос суммы
                double amount = readDouble();  // Сумма
                bank.deposit(accNum, amount);  // Пополнение
                break;  // Выход из case
            }

            case 4: {  // Снять деньги
                std::cout << "Введите номер счёта: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта
                if (!bank.accountBelongsToClient(clientId, accNum)) {  // Проверка владения
                    std::cout << "Счёт вам не принадлежит.\n";  // Сообщение об ошибке
                    break;  // Выход из case
                }

                std::cout << "Введите сумму снятия: ";  // Запрос суммы
                double amount = readDouble();  // Сумма
                bank.withdraw(accNum, amount);  // Снятие
                break;  // Выход из case
            }

            case 5: {  // Перевод с собственного счёта
                std::cout << "Введите номер счёта-отправителя: ";  // Запрос счёта отправителя
                int fromAcc = readInt();  // Счёт отправителя
                if (!bank.accountBelongsToClient(clientId, fromAcc)) {  // Проверка владения
                    std::cout << "Можно переводить только со своих счетов.\n";  // Сообщение об ошибке
                    break;  // Выход из case
                }

                std::cout << "Введите номер счёта-получателя: ";  // Запрос счёта получателя
                int toAcc = readInt();  // Счёт получателя

                std::cout << "Введите сумму перевода: ";  // Запрос суммы
                double amount = readDouble();  // Сумма
                bank.transfer(fromAcc, toAcc, amount);  // Перевод
                break;  // Выход из case
            }

            case 6: {  // Закрыть свой счёт
                std::cout << "Введите номер счёта для закрытия: ";  // Запрос номера счёта
                int accNum = readInt();  // Номер счёта
                if (!bank.accountBelongsToClient(clientId, accNum)) {  // Проверка владения
                    std::cout << "Счёт вам не принадлежит.\n";  // Сообщение об ошибке
                    break;  // Выход из case
                }

                bank.closeAccount(accNum);  // Закрытие
                break;  // Выход из case
            }

            case 0: {  // Выход клиента
                running = false;  // Завершаем цикл меню
                std::cout << "Выход из ЛК клиента.\н";  // Сообщение о выходе (опечатка: должно быть \n)
                break;  // Выход из case
            }

            default: {  // Некорректный пункт
                std::cout << "Неверный пункт. Попробуйте ещё раз.\н";  // Сообщение об ошибке (опечатка \н)
                break;  // Выход из case
            }
        }
    }
}

// Главная функция программы
int main() {
    Bank bank;  // Создаём объект банка

    bool running = true;  // Флаг работы основного меню
    while (running) {  // Цикл главного меню
        std::cout << "\n=== Банковская система ===\n";  // Заголовок
        std::cout << "1. Войти как сотрудник\n";  // Пункт меню
        std::cout << "2. Войти как клиент\n";  // Пункт меню
        std::cout << "0. Выход\n";  // Пункт меню
        std::cout << "Выберите пункт: ";  // Запрос выбора

        int choice = readInt();  // Чтение выбора

        switch (choice) {  // Разбор пункта
            case 1: {  // Режим сотрудника
                employeePortal(bank);  // Переход в меню сотрудника
                break;  // Выход из case
            }

            case 2: {  // Режим клиента
                std::cout << "Введите ID клиента: ";  // Запрос ID
                int clientId = readInt();  // Чтение ID

                Client *client = bank.getClient(clientId);  // Проверка наличия
                if (!client) {  // Если клиента нет
                    std::cout << "Клиент не найден.\n";  // Сообщаем
                    break;  // Выход из case
                }

                clientPortal(bank, clientId);  // Переход в меню клиента
                break;  // Выход из case
            }

            case 0: {  // Завершение работы программы
                running = false;  // Завершаем цикл
                std::cout << "Выход из программы. До свидания!\н";  // Сообщение о выходе (опечатка \н)
                break;  // Выход из case
            }

            default: {  // Некорректный пункт
                std::cout << "Неверный пункт. Попробуйте ещё раз.\н";  // Сообщение об ошибке (опечатка \н)
                break;  // Выход из case
            }
        }
    }

    return 0;  // Код успешного завершения программы
}
