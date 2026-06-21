project(MatrixLib LANGUAGES CXX)

# not really required, header-only library
add_library(MatrixLib Matrix/matrix.cpp)
