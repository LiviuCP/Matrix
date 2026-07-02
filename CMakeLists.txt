cmake_minimum_required(VERSION 3.28)

add_compile_definitions(USE_SMALL_DIMENSIONS)
add_compile_definitions(USE_CAPACITY_OFFSET)
add_compile_definitions(CONVERT_TO_EXCEPTIONS)

project(Matrix LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(MatrixLib)
add_subdirectory(Example)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test QUIET)

if(QT_FOUND)
    add_subdirectory(MatrixTests)
    add_subdirectory(TestUtilsLib)
endif()
