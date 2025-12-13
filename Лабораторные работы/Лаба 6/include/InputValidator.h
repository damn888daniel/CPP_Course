#ifndef INPUT_VALIDATOR_H // Защита от повторного включения
#define INPUT_VALIDATOR_H // Определение макроса защиты

#include <string> // Подключение библиотеки строк
#include <regex> // Подключение библиотеки регулярных выражений

// Класс для валидации (проверки) входных данных
class InputValidator {
public:
    // Статический метод проверки формата email
    static bool isValidEmail(const std::string& email);
    
    // Статический метод проверки на наличие SQL-инъекций
    static bool isSafeInput(const std::string& input);
    
    // Статический метод проверки длины имени
    static bool isValidNameLength(const std::string& name);
    
    // Статический метод проверки диапазона оценки
    static bool isValidGrade(int grade);
    
    // Статический метод проверки формата названия группы
    static bool isValidGroupName(const std::string& group);
};

#endif // Конец защиты