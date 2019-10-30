cmake_minimum_required(VERSION 3.10)
project(figures)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        src/figures
        include/figures
        include/container
        )
        
set(SRC_PREFIX src/figures)        

set (FIGURES
        ${SRC_PREFIX}/point.cpp
        ${SRC_PREFIX}/color.cpp
        ${SRC_PREFIX}/shape.cpp
        ${SRC_PREFIX}/text.cpp
        ${SRC_PREFIX}/sinsquaretext.cpp
        ${SRC_PREFIX}/sinsquare.cpp
        ${SRC_PREFIX}/sinwave.cpp
        )

add_executable(main ${FIGURES} src/main.cpp)
