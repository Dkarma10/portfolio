cmake_minimum_required(VERSION 3.24)
project(randomCard)

set(CMAKE_CXX_STANDARD 23)

add_executable(randomCard main.cpp cardlib.h cardlib.cpp test.h)
