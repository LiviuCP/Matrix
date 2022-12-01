#ifndef TST_RESIZINGTESTS_H
#define TST_RESIZINGTESTS_H

#include "testutils.h"

#define TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, \
                                   "Resizing failed, number of rows or columns of the matrix is not correct!", \
                                   "Resizing failed, capacity of the matrix is not correct!")

#define TEST_SHRINK_TO_FIT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredNrOfRows, requiredNrOfColumns, \
                                   "Shrinking to fit failed, number of rows or columns of the matrix is not correct!", \
                                   "Shrinking to fit failed, capacity of the matrix is not correct!")

#define TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, \
                                   "Insert row failed, number of rows or columns of the matrix is not correct!", \
                                   "Insert row failed, capacity of the matrix is not correct!")

#define TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, \
                                   "Insert column failed, number of rows or columns of the matrix is not correct!", \
                                   "Insert column failed, capacity of the matrix is not correct!")

#define TEST_ERASE_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, \
                                   "Erase row failed, number of rows or columns of the matrix is not correct!", \
                                   "Erase row failed, capacity of the matrix is not correct!")

#define TEST_ERASE_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity, \
                                   "Erase column failed, number of rows or columns of the matrix is not correct!", \
                                   "Erase column failed, capacity of the matrix is not correct!")

#define TEST_CLEAR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix) \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0, 0, 0, 0, \
                                   "Clear failed, number of rows or columns of the matrix is not correct!", \
                                   "Clear failed, capacity of the matrix is not correct!")

#define TEST_MATRIX_RESIZE_AND_FILL_IN_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(matrixType, fillValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
 \
    matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, fillValue); \
 \
    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");

#define TEST_MATRIX_SHRINK_TO_FIT(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
 \
    primaryMatrix = matrix; \
    primaryMatrix.shrinkToFit(); \
 \
    TEST_SHRINK_TO_FIT_CHECK_MATRIX_SIZE_AND_CAPACITY(primaryMatrix, matrix.getNrOfRows(), matrix.getNrOfColumns()) \
 \
    QVERIFY2(primaryMatrix == matrix, "Shrinking to fit failed, the matrix does not retain its values!");

#define TEST_MATRIX_INSERT_ROW_SET_VALUE(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedRowValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, referenceMatrix); \
 \
    matrix.insertRow(insertPosition, insertedRowValue); \
 \
    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == referenceMatrix, "Insert row failed, the matrix doesn't have the right values!");

#define TEST_MATRIX_INSERT_COLUMN_SET_VALUE(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedColumnValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, referenceMatrix); \
 \
    matrix.insertColumn(insertPosition, insertedColumnValue); \
 \
    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == referenceMatrix, "Insert column failed, the matrix doesn't have the right values!");

#define TEST_MATRIX_ERASE_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, erasePosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
 \
    matrix.eraseRow(erasePosition); \
 \
    TEST_ERASE_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, expectedMatrix.getNrOfRows(), expectedMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == expectedMatrix, "Erase row failed, the matrix doesn't have the right values on the remaining rows!");

#define TEST_MATRIX_ERASE_MULTIPLE_ROWS(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, erasePosition); \
    QFETCH(Matrix<matrixType>::size_type, erasedRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
 \
    while (erasedRowsCount > 0) \
    { \
        if (erasePosition >= matrix.getNrOfRows()) \
        { \
            QFAIL("Erase row failed: invalid row number, cannot erase!"); \
        } \
\
        matrix.eraseRow(erasePosition); \
        --erasedRowsCount; \
    } \
 \
    TEST_ERASE_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, expectedMatrix.getNrOfRows(), expectedMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == expectedMatrix, "Erase row failed, the matrix doesn't have the right values on the remaining rows!");

#define TEST_MATRIX_ERASE_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, erasePosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
 \
    matrix.eraseColumn(erasePosition); \
 \
    TEST_ERASE_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, expectedMatrix.getNrOfRows(), expectedMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == expectedMatrix, "Erase column failed, the matrix doesn't have the right values on the remaining columns!");

#define TEST_MATRIX_ERASE_MULTIPLE_COLUMNS(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, erasePosition); \
    QFETCH(Matrix<matrixType>::size_type, erasedColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
 \
    while (erasedColumnsCount > 0) \
    { \
        if (erasePosition >= matrix.getNrOfRows()) \
        { \
            QFAIL("Erase column failed: invalid column number, cannot erase!"); \
        } \
\
        matrix.eraseColumn(erasePosition); \
        --erasedColumnsCount; \
    } \
 \
    TEST_ERASE_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, expectedMatrix.getNrOfRows(), expectedMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity); \
 \
    QVERIFY2(matrix == expectedMatrix, "Erase column failed, the matrix doesn't have the right values on the remaining columns!"); \

#define TEST_MATRIX_CLEAR(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
 \
    primaryMatrix = matrix; \
    primaryMatrix.clear(); \
 \
    TEST_CLEAR_CHECK_MATRIX_SIZE_AND_CAPACITY(primaryMatrix);

#endif // TST_RESIZINGTESTS_H
