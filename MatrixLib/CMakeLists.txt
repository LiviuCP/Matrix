project(MatrixLib LANGUAGES CXX)

add_library(${PROJECT_NAME} Utils/errorhandling.cpp)

target_sources(${PROJECT_NAME}
    PUBLIC
        FILE_SET library_modules
        TYPE CXX_MODULES
        FILES
            Matrix/matrix.cpp
            Matrix/matrix_header.cpp
            Matrix/matrix_impl.cpp
            Iterators/matrix_ziterator_impl.cpp
            Iterators/matrix_niterator_impl.cpp
            Iterators/matrix_diterator_impl.cpp
            Iterators/matrix_miterator_impl.cpp
)
