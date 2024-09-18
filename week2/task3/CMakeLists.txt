cmake_minimum_required(VERSION 3.10)

project(ImageGenerator)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ImageGenerator main.cpp src/utils.cpp)

target_include_directories(ImageGenerator PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(ImageGenerator PRIVATE src/utils.cpp)
