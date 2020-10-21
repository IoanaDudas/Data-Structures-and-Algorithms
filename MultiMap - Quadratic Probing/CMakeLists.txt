cmake_minimum_required(VERSION 3.16)
project(Assignment_5___MultiMap)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Assignment_5___MultiMap
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        MultiMap.cpp
        MultiMap.h
        MultiMapIterator.cpp
        MultiMapIterator.h
        ShortTest.cpp
        ShortTest.h)
