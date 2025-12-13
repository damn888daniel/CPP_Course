#include "InputValidator.h" // Подключение заголовочного файла валидатора

// Реализация проверки email
bool InputValidator::isValidEmail(const std::string& email) {
    // Простой шаблон регулярного выражения для email: слово@слово.домен
    const std::regex pattern(R"((\w+)(\.|_)?(\w*)@(\w+)(\.(\w+))+)");
    // Возвращает true, если email соответствует шаблону
    return std::regex_match(email, pattern);
}

// Реализация проверки на безопасность ввода (защита от SQL-инъекций)
bool InputValidator::isSafeInput(const std::string& input) {
    // Простая проверка: ищем опасные символы, часто используемые в инъекциях
    if (input.find('\'') != std::string::npos || // Поиск одинарной кавычки
        input.find(';') != std::string::npos || // Поиск точки с запятой (разделение команд)
        input.find("--") != std::string::npos) { // Поиск комментария SQL
        return false; // Если найдено что-то подозрительное, ввод небезопасен
    }
    return true; // Ввод безопасен
}

// Реализация проверки длины имени
bool InputValidator::isValidNameLength(const std::string& name) {
    // Имя должно быть от 2 до 100 символов
    return name.length() >= 2 && name.length() <= 100;
}

// Реализация проверки корректности оценки
bool InputValidator::isValidGrade(int grade) {
    // Оценка должна быть в диапазоне от 0 до 100
    return grade >= 0 && grade <= 100;
}

// Реализация проверки формата группы
bool InputValidator::isValidGroupName(const std::string& group) {
    // Разрешаем формат: минимум 3 символа и наличие дефиса (например, "CS-101")
    return group.length() >= 3 && group.find('-') != std::string::npos;
}