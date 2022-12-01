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

#define TEST_MATRIX_SWAP_ITEMS(matrixType) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
    QFETCH(Matrix<matrixType>::size_type, firstItemRowNr); \
    QFETCH(Matrix<matrixType>::size_type, firstItemColumnNr); \
    QFETCH(Matrix<matrixType>::size_type, secondItemRowNr); \
    QFETCH(Matrix<matrixType>::size_type, secondItemColumnNr); \
    QFETCH(bool, isSwapWithinMatrix); \
    QFETCH(Matrix<matrixType>, expectedFirstMatrix); \
    QFETCH(Matrix<matrixType>, expectedSecondMatrix); \
\
    if (isSwapWithinMatrix) \
    { \
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, firstMatrix, secondItemRowNr, secondItemColumnNr); \
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped within same matrix!"); \
    } \
    else \
    { \
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, secondMatrix, secondItemRowNr, secondItemColumnNr); \
\
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!"); \
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Items are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!"); \
    }

#define TEST_MATRIX_SWAP_ROWS(matrixType) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
    QFETCH(Matrix<matrixType>::size_type, firstRowNr); \
    QFETCH(Matrix<matrixType>::size_type, secondRowNr); \
    QFETCH(bool, isSwapWithinMatrix); \
    QFETCH(Matrix<matrixType>, expectedFirstMatrix); \
    QFETCH(Matrix<matrixType>, expectedSecondMatrix); \
\
    if (isSwapWithinMatrix) \
    { \
        firstMatrix.swapRows(firstRowNr, firstMatrix, secondRowNr); \
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped within same matrix!"); \
    } \
    else \
    { \
        firstMatrix.swapRows(firstRowNr, secondMatrix, secondRowNr); \
\
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!"); \
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Rows are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!"); \
    }

#define TEST_MATRIX_SWAP_COLUMNS(matrixType) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
    QFETCH(Matrix<matrixType>::size_type, firstColumnNr); \
    QFETCH(Matrix<matrixType>::size_type, secondColumnNr); \
    QFETCH(bool, isSwapWithinMatrix); \
    QFETCH(Matrix<matrixType>, expectedFirstMatrix); \
    QFETCH(Matrix<matrixType>, expectedSecondMatrix); \
\
    if (isSwapWithinMatrix) \
    { \
        firstMatrix.swapColumns(firstColumnNr, firstMatrix, secondColumnNr); \
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped within same matrix!"); \
    } \
    else \
    { \
        firstMatrix.swapColumns(firstColumnNr, secondMatrix, secondColumnNr); \
\
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!"); \
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Columns are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!"); \
    }

#endif // TST_SWAPPINGTESTS_H
