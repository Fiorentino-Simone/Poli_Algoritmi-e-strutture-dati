cmake_minimum_required(VERSION 3.27)
project(Prim C)

set(CMAKE_C_STANDARD 11)

add_executable(Prim main.c
    graph.c
    graph.h
    st.c
    st.h
)
