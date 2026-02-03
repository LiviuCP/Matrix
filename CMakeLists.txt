cmake_minimum_required(VERSION 3.5)

project(Matrix LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(MatrixLib)
# add_subdirectory(Example)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test QUIET)

if(QT_FOUND)
    add_subdirectory(MatrixTests)
endif()
