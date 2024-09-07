cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_COMPILER g++)

project(Task1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(main)

set(SOURCES src/main.cpp)

target_sources(main PRIVATE ${SOURCES})