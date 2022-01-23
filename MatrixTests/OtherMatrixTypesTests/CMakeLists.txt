cmake_minimum_required(VERSION 3.5)

project(OtherMatrixTypesTests LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-DQT)

enable_testing()

include_directories(../Shared)
include_directories(../../MatrixLib/Matrix)

# uncomment Fraction tests configuration as soon as the Fractions include and library dir are setup

add_executable(DecimalMatrixTests tst_decimalmatrixtests.cpp)
add_executable(StringMatrixTests tst_stringmatrixtests.cpp)
add_executable(QPointFMatrixTests tst_qpointfmatrixtests.cpp)
#add_executable(FractionMatrixTests tst_fractionmatrixtests.cpp)

add_test(NAME DecimalMatrixTests COMMAND DecimalMatrixTests)
add_test(NAME StringMatrixTests COMMAND StringMatrixTests)
add_test(NAME QPointFMatrixTests COMMAND QPointFMatrixTests)
#add_test(NAME FractionMatrixTests COMMAND FractionMatrixTests)

target_link_libraries(DecimalMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(StringMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(QPointFMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
#target_link_libraries(FractionMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

#include_directories(../../../Fractions/FractionLib)

#add_library(fractionlib SHARED IMPORTED)
#set_target_properties(fractionlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/../../../Fractions/FractionLib/libFractionLib.so)
#target_link_libraries(FractionMatrixTests PRIVATE fractionlib)

