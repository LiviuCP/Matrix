#ifndef TST_TRANSFORMATIONTESTS_H
#define TST_TRANSFORMATIONTESTS_H

#define TEST_MATRIX_TRANSPOSE(matrixType, primaryMatrix, secondaryMatrix) \
    QFETCH(Matrix<matrixType>, initialSrcMatrix); \
    QFETCH(Matrix<matrixType>, initialDestMatrix); \
    QFETCH(Matrix<matrixType>, expectedDestMatrix); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestColumnCapacity); \
    QFETCH(bool, isTransposedToItself); \
 \
    primaryMatrix = initialSrcMatrix; \
 \
    if (isTransposedToItself) \
    { \
        primaryMatrix.transpose(primaryMatrix); \
 \
        QVERIFY2(primaryMatrix == expectedDestMatrix && \
                 primaryMatrix.getRowCapacity() == expectedDestRowCapacity && \
                 primaryMatrix.getColumnCapacity() == expectedDestColumnCapacity, "Transposing failed, the resulting capacity, dimensions and/or values are incorrect!"); \
    } \
    else \
    { \
        secondaryMatrix = initialDestMatrix; \
 \
        primaryMatrix.transpose(secondaryMatrix); \
 \
        QVERIFY2(primaryMatrix == initialSrcMatrix && \
                 primaryMatrix.getRowCapacity() == expectedSrcRowCapacity && \
                 primaryMatrix.getColumnCapacity() == expectedSrcColumnCapacity, "Transposing failed, the source matrix shouldn't change!"); \
 \
        QVERIFY2(secondaryMatrix == expectedDestMatrix && \
                 secondaryMatrix.getRowCapacity() == expectedDestRowCapacity && \
                 secondaryMatrix.getColumnCapacity() == expectedDestColumnCapacity, "Transposing failed, the resulting capacity, dimensions and/or values of the transposed matrix are incorrect!"); \
    }

#define TEST_MATRIX_CAT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, firstSrcMatrix); \
    QFETCH(Matrix<matrixType>, secondSrcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedDestMatrix); \
\
    switch(mode) \
    { \
    case ConcatMode::ALL_DIFFERENT: \
        destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_FIRST: \
        destMatrix.catByRow(destMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_SECOND: \
        destMatrix.catByRow(firstSrcMatrix, destMatrix); \
        break; \
    case ConcatMode::DESTINATION_ALL: \
        destMatrix.catByRow(destMatrix, destMatrix); \
        break; \
    case ConcatMode::SOURCE_BOTH: \
        destMatrix.catByRow(firstSrcMatrix, firstSrcMatrix); \
        break; \
    default: \
        break; \
    } \
\
    if (destMatrix.getRowCapacity() != expectedRowCapacity || destMatrix.getColumnCapacity() != expectedColumnCapacity) \
    { \
        QFAIL("Vertical concatenation failed, capacity of the destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(destMatrix == expectedDestMatrix, "Vertical concatenation failed, destination matrix has incorrect values!"); \
    }

#define TEST_MATRIX_CAT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, firstSrcMatrix); \
    QFETCH(Matrix<matrixType>, secondSrcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedDestMatrix); \
\
    switch(mode) \
    { \
    case ConcatMode::ALL_DIFFERENT: \
        destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_FIRST: \
        destMatrix.catByColumn(destMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_SECOND: \
        destMatrix.catByColumn(firstSrcMatrix, destMatrix); \
        break; \
    case ConcatMode::DESTINATION_ALL: \
        destMatrix.catByColumn(destMatrix, destMatrix); \
        break; \
    case ConcatMode::SOURCE_BOTH: \
        destMatrix.catByColumn(firstSrcMatrix, firstSrcMatrix); \
        break; \
    default: \
        break; \
    } \
\
    if (destMatrix.getRowCapacity() != expectedRowCapacity || destMatrix.getColumnCapacity() != expectedColumnCapacity) \
    { \
        QFAIL("Horizontal concatenation failed, capacity of the destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(destMatrix == expectedDestMatrix, "Horizontal concatenation failed, destination matrix has incorrect values!"); \
    }

#define TEST_MATRIX_SPLIT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, firstDestMatrix); \
    QFETCH(Matrix<matrixType>, secondDestMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(SplitMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedFirstDestMatrix); \
    QFETCH(Matrix<matrixType>, expectedSecondDestMatrix); \
 \
    switch(mode) \
    { \
    case SplitMode::ALL_DIFFERENT: \
        srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_FIRST: \
        firstDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_SECOND: \
        secondDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    default: \
        QFAIL("exception scenario"); \
        break; \
    } \
 \
    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity) \
    { \
        QFAIL("Vertical split failed, capacity of the first destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Vertical split failed, first destination matrix has incorrect values!"); \
    } \
 \
    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity) \
    { \
        QFAIL("Vertical split failed, capacity of the second destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(secondDestMatrix == expectedSecondDestMatrix, "Vertical split failed, second destination matrix has incorrect values!"); \
    }

#define TEST_MATRIX_SPLIT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, firstDestMatrix); \
    QFETCH(Matrix<matrixType>, secondDestMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(SplitMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestColumnCapacity); \
    QFETCH(Matrix<matrixType>, expectedFirstDestMatrix); \
    QFETCH(Matrix<matrixType>, expectedSecondDestMatrix); \
 \
    switch(mode) \
    { \
    case SplitMode::ALL_DIFFERENT: \
        srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_FIRST: \
        firstDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_SECOND: \
        secondDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    default: \
        QFAIL("exception scenario"); \
        break; \
    } \
 \
    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity) \
    { \
        QFAIL("Horizontal split failed, capacity of the first destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Horizontal split failed, first destination matrix has incorrect values!"); \
    } \
 \
    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity) \
    { \
        QFAIL("Horizontal split failed, capacity of the second destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(secondDestMatrix == expectedSecondDestMatrix, "Horizontal split failed, second destination matrix has incorrect values!"); \
    }

#endif // TST_TRANSFORMATIONTESTS_H
