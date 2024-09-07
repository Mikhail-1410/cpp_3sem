cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project(TrigProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

message(INFO: ${TrigProject_SOURCE_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${TrigProject_SOURCE_DIR}/bin)

include_directories(include)

add_executable(TrigProject main.cpp src/ans_handler.cpp src/my_math.cpp)
