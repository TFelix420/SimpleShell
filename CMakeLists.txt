cmake_minimum_required(VERSION 3.20)
project(Shell9 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Shell9
        main.c shell.c history.c aliases.c linkedList.c)
