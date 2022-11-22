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

include_directories(../Shared)
include_directories(../../MatrixLib/Matrix)

add_executable(ConstructionAndAssignmentTests tst_constructionandassignmenttests.cpp)
add_test(NAME ConstructionAndAssignmentTests COMMAND ConstructionAndAssignmentTests)

add_executable(ResizingTests tst_resizingtests.cpp)
add_test(NAME ResizingTests COMMAND ResizingTests)

add_executable(TransformationTests tst_transformationtests.cpp)
add_test(NAME TransformationTests COMMAND TransformationTests)

add_executable(SwappingTests tst_swappingtests.cpp)
add_test(NAME SwappingTests COMMAND SwappingTests)

add_executable(OtherFunctionalityTests tst_otherfunctionalitytests.cpp)
add_test(NAME OtherFunctionalityTests COMMAND OtherFunctionalityTests)

add_executable(CapacityTests tst_capacitytests.cpp)
add_test(NAME CapacityTests COMMAND CapacityTests)

target_link_libraries(ConstructionAndAssignmentTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(ResizingTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(TransformationTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(SwappingTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(OtherFunctionalityTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(CapacityTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

