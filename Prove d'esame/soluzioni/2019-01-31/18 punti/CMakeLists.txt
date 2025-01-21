cmake_minimum_required(VERSION 3.27)
project(18_punti C)

set(CMAKE_C_STANDARD 11)

add_executable(18_punti main.c
        Graph.h
        Graph.c
        ST.c
        ST.h)
