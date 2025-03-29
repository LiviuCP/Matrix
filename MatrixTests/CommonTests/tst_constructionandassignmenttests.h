#ifndef TST_CONSTRUCTIONANDASSIGNMENTTESTS_H
#define TST_CONSTRUCTIONANDASSIGNMENTTESTS_H

#include "testutils.h"

#define TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0u, 0u, 0u, 0u, std::nullopt, std::nullopt, \
                                   "Default constructor initialized matrix with wrong number of rows and columns!", \
                                   "Default constructor initialized matrix with wrong capacity!", \
                                   "Default constructor initialized matrix with wrong capacity offset!")

#define TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                                  requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Init list constructor initialized matrix with wrong number of rows and columns!", \
                                   "Init list constructor initialized matrix with wrong capacity!", \
                                   "Init list constructor initialized matrix with wrong capacity offset!")

#define TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                                         requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Identical matrix constructor initialized matrix with wrong number of rows and columns!", \
                                   "Identical matrix constructor initialized matrix with wrong capacity!", \
                                   "Identical matrix constructor initialized matrix with wrong capacity offset!")

#define TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                                        requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Diagonal matrix constructor initialized matrix with wrong number of rows and columns!", \
                                   "Diagonal matrix constructor initialized matrix with wrong capacity!", \
                                   "Diagonal matrix constructor initialized matrix with wrong capacity offset!")

#define TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                             requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Copy constructor initialized matrix with wrong number of rows and columns!", \
                                   "Copy constructor initialized matrix with wrong capacity!", \
                                   "Copy constructor initialized matrix with wrong capacity offset!")

#define TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                             requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Move constructor initialized matrix with wrong number of rows and columns!", \
                                   "Move constructor initialized matrix with wrong capacity!", \
                                   "Move constructor initialized matrix with wrong capacity offset!")

#define TEST_MOVE_CONSTRUCTOR_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(matrix) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0u, 0u, 0u, 0u, std::nullopt, std::nullopt, \
                                   "Move constructor set the wrong number of rows and columns to the source matrix!", \
                                   "Move constructor set the wrong capacity to the source matrix!", \
                                   "Move constructor set the wrong capacity offset to the source matrix!")

#define TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                            requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Copy assignment failed, number of rows or columns of the destination matrix is not correct!", \
                                   "Copy assignment failed, capacity of the destination matrix is not correct!", \
                                   "Copy assignment failed, capacity offset of the destination matrix is not correct!")

#define TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                                                 requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                   "Move assignment failed, number of rows or columns of the destination matrix is not correct!", \
                                   "Move assignment failed, capacity of the destination matrix is not correct!", \
                                   "Move assignment failed, capacity offset of the destination matrix is not correct!")

#define TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(matrix) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0u, 0u, 0u, 0u, std::nullopt, std::nullopt, \
                                   "Move assignment failed, number of rows or columns of the source matrix is not correct!", \
                                   "Move assignment failed, capacity of the source matrix is not correct!", \
                                   "Move assignment failed, capacity offset of the source matrix is not correct!")

#endif // TST_CONSTRUCTIONANDASSIGNMENTTESTS_H
