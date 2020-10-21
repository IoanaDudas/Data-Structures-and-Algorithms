cmake_minimum_required(VERSION 3.16)
project(Assignment_3___Map)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_3___Map
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        Map.cpp
        Map.h
        MapIterator.cpp
        MapIterator.h
        ShortTest.cpp
        ShortTest.h)
