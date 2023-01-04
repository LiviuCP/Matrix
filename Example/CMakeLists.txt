cmake_minimum_required(VERSION 3.5)

project(Example LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(../MatrixLib/Matrix)

add_executable(Example examplemain.cpp utilities.cpp)
