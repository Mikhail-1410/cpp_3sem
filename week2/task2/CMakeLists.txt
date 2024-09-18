# CMakeLists.txt
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(ImageGenerator)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Указание исходных файлов
add_executable(ImageGenerator main.cpp utils.cpp)

# Включение заголовочного файла
target_include_directories(ImageGenerator PUBLIC "${PROJECT_SOURCE_DIR}")
