cmake_minimum_required(VERSION 3.5)

project(CommonTests LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(../../MatrixLib/Matrix)

add_executable(CommonTests tst_commontests.cpp)
add_test(NAME CommonTests COMMAND CommonTests)

target_link_libraries(CommonTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
