cmake_minimum_required(VERSION 3.23)
project(task4)

set(CMAKE_CXX_STANDARD 14)

add_executable(task4 main.cpp
        Lex.h
        lex.cpp
        syntax.cpp
        syntax.h
        )
