cmake_minimum_required(VERSION 3.21)
project(Simple_Library_Catalog_System)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Simple_Library_Catalog_System
        main.cpp
        SLS.cpp
        SLS.h
        bits-stdc++.h
        )
