cmake_minimum_required(VERSION 3.27)
project(Ese03 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ese03 main.c
        personaggi.c
        personaggi.h
        inventario.h
        inventario.c)
