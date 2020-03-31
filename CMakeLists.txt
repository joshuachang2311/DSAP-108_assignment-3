cmake_minimum_required(VERSION 3.15)
project(assignment_3)

set(CMAKE_CXX_STANDARD 14)

add_executable(assignment_3 main.cpp
        Customer.h Customer.cpp
        Merchandiser.h Merchandiser.cpp)