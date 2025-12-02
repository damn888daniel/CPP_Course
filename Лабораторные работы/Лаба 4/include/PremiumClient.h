#ifndef PREMIUMCLIENT_H
#define PREMIUMCLIENT_H

#include "Client.h"

class PremiumClient : public Client {
private:
    int level;  // уровень премиум-статуса
    double discount;  // скидка (0-1)

public:
    PremiumClient();  // конструктор по умолчанию
    PremiumClient(const std::string &firstName, const std::string &lastName, const Address &address, const Date &registrationDate, int level, double discount);  // конструктор с параметрами

    void setLevel(int level);  // установить уровень
    void setDiscount(double discount);  // установить скидку
    int getLevel() const;  // получить уровень
    double getDiscount() const;  // получить скидку
    void displayInfo() const override;  // показать информацию
};

#endif
