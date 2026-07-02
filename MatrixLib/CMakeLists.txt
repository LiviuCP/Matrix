project(MatrixLib LANGUAGES CXX)

if(BUILD_SHARED_MATRIX_LIB)
    add_library(${PROJECT_NAME} SHARED Utils/errorhandling.cpp)
else()
    add_library(${PROJECT_NAME} STATIC Utils/errorhandling.cpp)
endif()

target_sources(${PROJECT_NAME}
    PUBLIC
        FILE_SET matrix_modules
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
