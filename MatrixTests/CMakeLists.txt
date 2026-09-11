project(MatrixTests LANGUAGES CXX)

find_package(QT NAMES Qt5 Qt6 COMPONENTS Test REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

enable_testing()

include_directories(Shared)
include_directories(../MatrixLib/Matrix)

add_subdirectory(CommonTests)
add_subdirectory(ExceptionTests)
add_subdirectory(IteratorTests)
add_subdirectory(OtherMatrixTypesTests)
