cmake_minimum_required(VERSION 3.27)
project(Ese01 C)

set(CMAKE_C_STANDARD 11)

add_executable(Ese01 main.c
        graph.h
        graph.c
        st.h
        st.c)
