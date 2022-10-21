cmake_minimum_required(VERSION 3.23)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        main.c functions.h functions.c matrix.c matrix.h levinstain.c levinstain.h time_counter.c time_counter.h)
