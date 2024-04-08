cmake_minimum_required(VERSION 3.27)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp
        SingleLinkedList.h)
