cmake_minimum_required(VERSION 3.27)
project(ds2_inventory_cleaner)

set(CMAKE_CXX_STANDARD 17)

add_library(discardItems SHARED dllmain.cpp
        PointerChain.h
        Signature.h
        signature.cpp
        GameManagerImp.h
        GameManagerImp.cpp
        DiscardFunction.h
        DiscardFunction.cpp
)