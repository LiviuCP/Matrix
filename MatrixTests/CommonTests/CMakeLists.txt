project(CommonTests LANGUAGES CXX)

add_compile_definitions(USE_CAPACITY_OFFSET)
add_compile_definitions(USE_SMALL_DIMENSIONS)

add_executable(ConstructionAndAssignmentTests tst_constructionandassignmenttests.cpp)
add_executable(ResizingTests tst_resizingtests.cpp)
add_executable(TransformationTests tst_transformationtests.cpp)
add_executable(SwappingTests tst_swappingtests.cpp)
add_executable(OtherFunctionalityTests tst_otherfunctionalitytests.cpp)
add_executable(CombinedTests tst_combinedtests.cpp)

add_test(NAME ConstructionAndAssignmentTests COMMAND ConstructionAndAssignmentTests)
add_test(NAME ResizingTests COMMAND ResizingTests)
add_test(NAME TransformationTests COMMAND TransformationTests)
add_test(NAME SwappingTests COMMAND SwappingTests)
add_test(NAME OtherFunctionalityTests COMMAND OtherFunctionalityTests)
add_test(NAME CombinedTests COMMAND CombinedTests)

target_link_libraries(ConstructionAndAssignmentTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(ResizingTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(TransformationTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(SwappingTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(OtherFunctionalityTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)
target_link_libraries(CombinedTests PRIVATE Qt${QT_VERSION_MAJOR}::Test)

add_subdirectory(CapacityTests)
