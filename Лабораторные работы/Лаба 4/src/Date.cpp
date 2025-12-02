#include "Date.h"
#include <iomanip>
#include <sstream>

Date::Date() : day(1), month(1), year(1970) {}  // конструктор по умолчанию

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}  // конструктор с параметрами

std::string Date::toString() const {  // преобразование даты в строку
    std::ostringstream oss;  // создаем строковый поток
    oss << std::setw(2) << std::setfill('0') << day << "."  // день с ведущим нулем
        << std::setw(2) << std::setfill('0') << month << "."  // месяц с ведущим нулем
        << year;  // год
    return oss.str();  // возвращаем строку
}