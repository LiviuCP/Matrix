project(Example LANGUAGES CXX)

include_directories(../MatrixLib/Matrix)

add_executable(Example examplemain.cpp utilities.cpp)
target_link_libraries(Example MatrixLib)
