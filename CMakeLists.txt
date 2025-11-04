cmake_minimum_required(VERSION 3.23)
project(task2)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(task2
        main.cpp
        StringList.cpp
        StringList.h)
