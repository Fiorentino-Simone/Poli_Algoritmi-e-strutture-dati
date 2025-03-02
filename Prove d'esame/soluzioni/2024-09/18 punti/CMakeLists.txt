cmake_minimum_required(VERSION 3.27)
project(18_punti C)

set(CMAKE_C_STANDARD 11)

add_executable(18_punti main.c
        Elenco.c
        Elenco.h
        DistMatr.c
        DistMatr.h
        SEDI.c
        SEDI.h)
