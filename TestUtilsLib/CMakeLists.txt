project(TestUtilsLib LANGUAGES CXX)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME}
    PUBLIC
        FILE_SET testutils_modules
        TYPE CXX_MODULES
        FILES
            testconstants.cpp)

target_link_libraries(${PROJECT_NAME} PUBLIC MatrixLib)
