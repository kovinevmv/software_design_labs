cmake_minimum_required(VERSION 3.10)
project(figures)

set(CMAKE_CXX_STANDARD 11)

include_directories(
        src/figures
        include/figures
        include/container
        include/exception
        ${GTEST_INCLUDE_DIRS})
        
set(PREFIX_DIR_FIGURES_SRC src/figures) 
       

set (FIGURES
        ${PREFIX_DIR_FIGURES_SRC}/point.cpp
        ${PREFIX_DIR_FIGURES_SRC}/color.cpp
        ${PREFIX_DIR_FIGURES_SRC}/shape.cpp
        ${PREFIX_DIR_FIGURES_SRC}/text.cpp
        ${PREFIX_DIR_FIGURES_SRC}/sinsquaretext.cpp
        ${PREFIX_DIR_FIGURES_SRC}/sinsquare.cpp
        ${PREFIX_DIR_FIGURES_SRC}/sinwave.cpp
        )

add_executable(main ${FIGURES} src/tests/test_figures.cpp)

find_package(GTest REQUIRED)
target_link_libraries(main ${GTEST_LIBRARIES} pthread)

