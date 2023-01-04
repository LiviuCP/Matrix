cmake_minimum_required(VERSION 3.5)

project(MatrixLib LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# not really required, header-only library
add_library(MatrixLib Matrix/matrix.cpp)
