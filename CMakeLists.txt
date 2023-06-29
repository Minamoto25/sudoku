cmake_minimum_required(VERSION 3.9)
project(sudoku)
add_executable(sudoku main.cpp sudoku.cpp helper.cpp getopt.cpp)

set(HEADER_FILES
        include/sudoku.h
        include/getopt.h
        include/helper.h
        )

set(SOURCE_FILES
        sudoku.cpp
        getopt.cpp
        helper.cpp
        )

add_library(sudoku_lib STATIC ${SOURCE_FILES} ${HEADER_FILES})

add_subdirectory(Google_tests)