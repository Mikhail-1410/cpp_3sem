cmake_minimum_required(VERSION 3.28)
project(iarullin)

#if (WIN32)
if (MSVC)
    # https://docs.microsoft.com/en-us/cpp/build/reference/compiler-options-listed-by-category
    list(APPEND compiler_flags
        "/WX" "/W4" "/permissive-" "/Za" "/fsanitize=address"

        # (необязательно) для статической компоновки с библиотеками времени выполнения
        "/MT"

        # (необязательно) использование c++20
        "/std:c++20"
    )
else()
    list(APPEND compiler_flags
        "-Werror" "-Wall" "-Wextra" "-pedantic" "-fsanitize=address"
        # (необязательно) использование c++20
        "-std=c++20"
    )
    list(APPEND linker_flags
        "-fsanitize=address"
    )
endif()

add_executable(iarullin gridlab.cpp)
target_compile_options(iarullin PRIVATE ${compiler_flags})
target_link_options(iarullin PRIVATE ${linker_flags})