cmake_minimum_required(VERSION 3.5)

project(ExceptionTests LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(../Shared)
include_directories(../../MatrixLib/Matrix)

add_executable(CommonExceptionTests tst_commonexceptiontests.cpp)
add_test(NAME CommonExceptionTests COMMAND CommonExceptionTests)

add_executable(IteratorExceptionTests tst_iteratorexceptiontests.cpp)
add_test(NAME IteratorExceptionTests COMMAND IteratorExceptionTests)

target_link_libraries(CommonExceptionTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(IteratorExceptionTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

