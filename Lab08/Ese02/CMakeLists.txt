cmake_minimum_required(VERSION 3.27)
project(Ese02 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ese02 main.c
        graph.h
        graph.c
        st.h
        st.c)
