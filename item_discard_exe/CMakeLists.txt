cmake_minimum_required(VERSION 3.27)
project(ds2_inventory_cleaner)

set(CMAKE_CXX_STANDARD 17)

add_executable(ds2_inventory_cleaner main.cpp
        dll_injector.h
        dll_injector.cpp
)
