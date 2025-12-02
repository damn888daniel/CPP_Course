#include "PremiumClient.h"
#include <iostream>

PremiumClient::PremiumClient()
    : Client(), level(1), discount(0.0) {}

PremiumClient::PremiumClient(const std::string &firstName,
                             const std::string &lastName,
                             const Address &address,
                             const Date &registrationDate,
                             int level,
                             double discount)
    : Client(firstName, lastName, address, registrationDate),
      level(level), discount(discount) {}

void PremiumClient::setLevel(int level) {
    this->level = level;
}

void PremiumClient::setDiscount(double discount) {
    this->discount = discount;
}

int PremiumClient::getLevel() const {
    return level;
}

double PremiumClient::getDiscount() const {
    return discount;
}

void PremiumClient::displayInfo() const {
    Client::displayInfo();  // вывод базовой информации
    std::cout << "Уровень премиум: " << level << "\n";
    std::cout << "Скидка: " << discount * 100 << "%\n";
}
