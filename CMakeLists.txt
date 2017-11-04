cmake_minimum_required(VERSION 3.8)
project(playground-ps)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        LICENSE
        main.cpp
        node.cpp
        node.h
        README.md)

add_executable(playground-ps ${SOURCE_FILES})