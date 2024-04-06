#ifndef TST_SWAPPINGTESTS_H
#define TST_SWAPPINGTESTS_H

#define TEST_MATRIXES_SWAP(matrixType, primaryMatrix, secondaryMatrix) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
\
    primaryMatrix = firstMatrix; \
    secondaryMatrix = secondMatrix; \
\
    std::swap(primaryMatrix, secondaryMatrix); \
\
    if (primaryMatrix.getRowCapacity() != secondMatrix.getRowCapacity() || primaryMatrix.getColumnCapacity() != secondMatrix.getColumnCapacity()) \
    { \
        QFAIL("Incorrect capacity of the first matrix after swap!"); \
    } \
\
    if (secondaryMatrix.getRowCapacity() != firstMatrix.getRowCapacity() || secondaryMatrix.getColumnCapacity() != firstMatrix.getColumnCapacity()) \
    { \
        QFAIL("Incorrect capacity of the second matrix after swap!"); \
    } \
\
    QVERIFY2(primaryMatrix == secondMatrix, "First matrix has incorrect element values after swap!"); \
    QVERIFY2(secondaryMatrix == firstMatrix, "Second matrix has incorrect element values after swap!");

#define TEST_MATRIX_SWAP_ROWS(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, firstRowNr); \
    QFETCH(Matrix<matrixType>::size_type, secondRowNr); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
\
    matrix.swapRows(firstRowNr, secondRowNr); \
    QVERIFY2(matrix == expectedMatrix, "Rows are incorrectly swapped!");

#define TEST_MATRIX_SWAP_COLUMNS(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, firstColumnNr); \
    QFETCH(Matrix<matrixType>::size_type, secondColumnNr); \
    QFETCH(Matrix<matrixType>, expectedMatrix); \
\
    matrix.swapColumns(firstColumnNr, secondColumnNr); \
    QVERIFY2(matrix == expectedMatrix, "Columns are incorrectly swapped!");

#endif // TST_SWAPPINGTESTS_H
