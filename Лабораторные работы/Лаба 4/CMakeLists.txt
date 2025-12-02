# CMakeLists.txt - конфигурационный файл для CMake
# Этот файл описывает, как собирать проект банковской системы

cmake_minimum_required(VERSION 3.10) # Требуемая минимальная версия CMake
project(BankSystem LANGUAGES CXX)     # Определяем имя проекта и язык

set(CMAKE_CXX_STANDARD 17)            # Указываем стандарт C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)   # Требуем строго стандарт C++17

include_directories(include)          # Добавляем папку include в список директорий для поиска заголовков

file(GLOB SOURCES "src/*.cpp")       # Собираем список всех cpp-файлов в папке src

add_executable(bank_system ${SOURCES}) # Создаём исполняемый файл bank_system из исходников