cmake_minimum_required(VERSION 3.27)
project(Ese01 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ese01 main.c
        datetime.h
        datetime.c
        titoli.h
        titoli.c
        quotazioni.h
        quotazioni.c)
