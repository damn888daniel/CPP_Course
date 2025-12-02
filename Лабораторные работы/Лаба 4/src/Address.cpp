#include "Address.h"

Address::Address() : streetAndHouse(""), city(""), postalIndex(""), country("") {}  // конструктор по умолчанию

Address::Address(const std::string &street, const std::string &city, const std::string &index, const std::string &country)
    : streetAndHouse(street), city(city), postalIndex(index), country(country) {}  // конструктор с параметрами