cmake_minimum_required(VERSION 3.23)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        main.c functions.h functions.c matrix.c matrix.h matrix_math.c matrix_math.h)
