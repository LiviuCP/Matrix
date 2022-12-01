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

set(FRACTION_LIB_ENABLED OFF) # set this ON once the Fractions library and include dir are setup

add_definitions(-DQT)

enable_testing()

include_directories(../Shared)
include_directories(../../MatrixLib/Matrix)

add_executable(DecimalMatrixTests tst_decimalmatrixtests.cpp)
add_executable(QPointFMatrixTests tst_qpointfmatrixtests.cpp)

add_test(NAME DecimalMatrixTests COMMAND DecimalMatrixTests)
add_test(NAME QPointFMatrixTests COMMAND QPointFMatrixTests)

target_link_libraries(DecimalMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(QPointFMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

if (${FRACTION_LIB_ENABLED})
    include_directories(../../../Fractions/FractionLib) # set the include dir path for the Fractions library
    add_executable(FractionMatrixTests tst_fractionmatrixtests.cpp)
    add_test(NAME FractionMatrixTests COMMAND FractionMatrixTests)
    target_link_libraries(FractionMatrixTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

    set(FRACTION_LIB_TYPE SHARED)

    # errors were encountered when building some libraries as shared on Windows so it has been decided to keep it static on this OS for the moment (for all other OSes it should be dynamic)
    if(WIN32)
        set(FRACTION_LIB_TYPE STATIC)
    endif()

    add_library(fractionlib ${FRACTION_LIB_TYPE} IMPORTED)
    set_target_properties(fractionlib PROPERTIES IMPORTED_LOCATION ${CMAKE_CURRENT_BINARY_DIR}/../../../Fractions/FractionLib/libFractionLib.so) # set the library path and use the required lib extension (.so for Linux, .dylib for MAC, etc)
    target_link_libraries(FractionMatrixTests PRIVATE fractionlib)
endif()
