cmake_minimum_required(VERSION 3.23)
project(src C)

set(CMAKE_C_STANDARD 11)

add_executable(src
        main.c combSort.h bitonicSort.h bucketSort.h structs.h functions.h bitonicSort.c bucketSort.c combSort.c functions.c structs.c timeCounter.c timeCounter.h)

target_link_libraries(src m)
