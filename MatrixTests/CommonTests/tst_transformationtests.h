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
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestColumnCapacityOffset); \
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
                 primaryMatrix.getColumnCapacity() == expectedDestColumnCapacity && \
                 primaryMatrix.getRowCapacityOffset() == expectedDestRowCapacityOffset && \
                 primaryMatrix.getColumnCapacityOffset() == expectedDestColumnCapacityOffset, "Transposing failed, the resulting capacity (offset), dimensions and/or values are incorrect!"); \
    } \
    else \
    { \
        secondaryMatrix = initialDestMatrix; \
 \
        primaryMatrix.transpose(secondaryMatrix); \
 \
        QVERIFY2(primaryMatrix == initialSrcMatrix && \
                 primaryMatrix.getRowCapacity() == expectedSrcRowCapacity && \
                 primaryMatrix.getColumnCapacity() == expectedSrcColumnCapacity && \
                 primaryMatrix.getRowCapacityOffset() == expectedSrcRowCapacityOffset && \
                 primaryMatrix.getColumnCapacityOffset() == expectedSrcColumnCapacityOffset, "Transposing failed, the source matrix shouldn't change!"); \
 \
        QVERIFY2(secondaryMatrix == expectedDestMatrix && \
                 secondaryMatrix.getRowCapacity() == expectedDestRowCapacity && \
                 secondaryMatrix.getColumnCapacity() == expectedDestColumnCapacity && \
                 secondaryMatrix.getRowCapacityOffset() == expectedDestRowCapacityOffset && \
                 secondaryMatrix.getColumnCapacityOffset() == expectedDestColumnCapacityOffset, "Transposing failed, the resulting capacity (offset), dimensions and/or values of the transposed matrix are incorrect!"); \
    }

#define TEST_MATRIX_CAT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
    QFETCH(Matrix<matrixType>, expectedDestMatrix); \
\
    switch(mode) \
    { \
    case ConcatMode::SOURCE_TO_DESTINATION: \
        destMatrix.catByRow(srcMatrix); \
        QVERIFY(srcMatrix.isEmpty()); \
        break; \
    case ConcatMode::TO_ITSELF: \
        destMatrix.catByRow(destMatrix); \
        break; \
    default: \
        assert(false); \
        break; \
    } \
\
    if (destMatrix.getRowCapacity() != expectedRowCapacity || \
        destMatrix.getColumnCapacity() != expectedColumnCapacity || \
        destMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        destMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Vertical concatenation failed, capacity (offset) of the destination matrix is not correct!"); \
    } \
\
    QVERIFY2(destMatrix == expectedDestMatrix, "Vertical concatenation failed, destination matrix has incorrect values!");

#define TEST_MATRIX_CAT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
    QFETCH(Matrix<matrixType>, expectedDestMatrix); \
\
    switch(mode) \
    { \
    case ConcatMode::SOURCE_TO_DESTINATION: \
        destMatrix.catByColumn(srcMatrix); \
        QVERIFY(srcMatrix.isEmpty()); \
        break; \
    case ConcatMode::TO_ITSELF: \
        destMatrix.catByColumn(destMatrix); \
        break; \
    default: \
        assert(false); \
        break; \
    } \
\
    if (destMatrix.getRowCapacity() != expectedRowCapacity || \
        destMatrix.getColumnCapacity() != expectedColumnCapacity || \
        destMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        destMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Horizontal concatenation failed, capacity (offset) of the destination matrix is not correct!"); \
    } \
\
    QVERIFY2(destMatrix == expectedDestMatrix, "Horizontal concatenation failed, destination matrix has incorrect values!");

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
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestColumnCapacityOffset); \
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
    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || \
        firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity || \
        firstDestMatrix.getRowCapacityOffset() != expectedFirstDestRowCapacityOffset || \
        firstDestMatrix.getColumnCapacityOffset() != expectedFirstDestColumnCapacityOffset) \
    { \
        QFAIL("Vertical split failed, capacity (offset) of the first destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Vertical split failed, first destination matrix has incorrect values!"); \
    } \
 \
    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || \
        secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity || \
        secondDestMatrix.getRowCapacityOffset() != expectedSecondDestRowCapacityOffset || \
        secondDestMatrix.getColumnCapacityOffset() != expectedSecondDestColumnCapacityOffset) \
    { \
        QFAIL("Vertical split failed, capacity (offset) of the second destination matrix is not correct!"); \
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
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestColumnCapacityOffset); \
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
    if (firstDestMatrix.getRowCapacity() != expectedFirstDestRowCapacity || \
        firstDestMatrix.getColumnCapacity() != expectedFirstDestColumnCapacity || \
        firstDestMatrix.getRowCapacityOffset() != expectedFirstDestRowCapacityOffset || \
        firstDestMatrix.getColumnCapacityOffset() != expectedFirstDestColumnCapacityOffset) \
    { \
        QFAIL("Horizontal split failed, capacity (offset) of the first destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(firstDestMatrix == expectedFirstDestMatrix, "Horizontal split failed, first destination matrix has incorrect values!"); \
    } \
 \
    if (secondDestMatrix.getRowCapacity() != expectedSecondDestRowCapacity || \
        secondDestMatrix.getColumnCapacity() != expectedSecondDestColumnCapacity || \
        secondDestMatrix.getRowCapacityOffset() != expectedSecondDestRowCapacityOffset || \
        secondDestMatrix.getColumnCapacityOffset() != expectedSecondDestColumnCapacityOffset) \
    { \
        QFAIL("Horizontal split failed, capacity (offset) of the second destination matrix is not correct!"); \
    } \
    else \
    { \
        QVERIFY2(secondDestMatrix == expectedSecondDestMatrix, "Horizontal split failed, second destination matrix has incorrect values!"); \
    }

#endif // TST_TRANSFORMATIONTESTS_H
