// Защита от повторного подключения заголовочного файла
#ifndef ADDRESS_H
#define ADDRESS_H

#include <string> // Для использования std::string

// Структура для хранения адреса клиента
struct Address {
    std::string streetAndHouse;  // Улица и номер дома (например, "Ленина 25")
    std::string city;            // Город (например, "Москва")
    std::string postalIndex;     // Почтовый индекс (например, "123456")
    std::string country;         // Страна (например, "Россия")

    // Конструктор по умолчанию (создает пустой адрес)
    Address();

    // Конструктор с параметрами (создает адрес с указанными значениями)
    // street - улица и дом
    // city - город
    // index - почтовый индекс
    // country - страна
    Address(const std::string &street, const std::string &city, const std::string &index, const std::string &country);
};

#endif 