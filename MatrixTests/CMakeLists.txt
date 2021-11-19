cmake_minimum_required(VERSION 3.5)

project(MatrixTests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(CommonTests)
add_subdirectory(ExceptionTests)
add_subdirectory(IteratorTests)
add_subdirectory(TypeDependentTests)
