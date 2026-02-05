#pragma once

#define TEST_MATRIX_TRANSPOSE(matrixType)                                                                              \
    QFETCH(Matrix<matrixType>, matrix);                                                                                \
    QFETCH(Matrix<matrixType>, expectedMatrix);                                                                        \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity);                                                        \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity);                                                     \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset);                                   \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset);                                \
                                                                                                                       \
    matrix.transpose();                                                                                                \
                                                                                                                       \
    QVERIFY2(matrix == expectedMatrix && matrix.getRowCapacity() == expectedRowCapacity &&                             \
                 matrix.getColumnCapacity() == expectedColumnCapacity &&                                               \
                 matrix.getRowCapacityOffset() == expectedRowCapacityOffset &&                                         \
                 matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset,                                     \
             "Transposing failed, the resulting capacity (offset), dimensions and/or values are incorrect!");

#define TEST_MATRIX_CAT_BY_ROW(matrixType)                                                                             \
    QFETCH(Matrix<matrixType>, destMatrix);                                                                            \
    QFETCH(Matrix<matrixType>, srcMatrix);                                                                             \
    QFETCH(ConcatMode, mode);                                                                                          \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity);                                                        \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity);                                                     \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset);                                   \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset);                                \
    QFETCH(Matrix<matrixType>, expectedDestMatrix);                                                                    \
                                                                                                                       \
    switch (mode)                                                                                                      \
    {                                                                                                                  \
    case ConcatMode::SOURCE_TO_DESTINATION:                                                                            \
        destMatrix.catByRow(srcMatrix);                                                                                \
        QVERIFY(srcMatrix.isEmpty());                                                                                  \
        break;                                                                                                         \
    case ConcatMode::TO_ITSELF:                                                                                        \
        destMatrix.catByRow(destMatrix);                                                                               \
        break;                                                                                                         \
    default:                                                                                                           \
        assert(false);                                                                                                 \
        break;                                                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    if (destMatrix.getRowCapacity() != expectedRowCapacity ||                                                          \
        destMatrix.getColumnCapacity() != expectedColumnCapacity ||                                                    \
        destMatrix.getRowCapacityOffset() != expectedRowCapacityOffset ||                                              \
        destMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset)                                          \
    {                                                                                                                  \
        QFAIL("Vertical concatenation failed, capacity (offset) of the destination matrix is not correct!");           \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(destMatrix == expectedDestMatrix,                                                                         \
             "Vertical concatenation failed, destination matrix has incorrect values!");

#define TEST_MATRIX_CAT_BY_COLUMN(matrixType)                                                                          \
    QFETCH(Matrix<matrixType>, destMatrix);                                                                            \
    QFETCH(Matrix<matrixType>, srcMatrix);                                                                             \
    QFETCH(ConcatMode, mode);                                                                                          \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity);                                                        \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity);                                                     \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset);                                   \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset);                                \
    QFETCH(Matrix<matrixType>, expectedDestMatrix);                                                                    \
                                                                                                                       \
    switch (mode)                                                                                                      \
    {                                                                                                                  \
    case ConcatMode::SOURCE_TO_DESTINATION:                                                                            \
        destMatrix.catByColumn(srcMatrix);                                                                             \
        QVERIFY(srcMatrix.isEmpty());                                                                                  \
        break;                                                                                                         \
    case ConcatMode::TO_ITSELF:                                                                                        \
        destMatrix.catByColumn(destMatrix);                                                                            \
        break;                                                                                                         \
    default:                                                                                                           \
        assert(false);                                                                                                 \
        break;                                                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    if (destMatrix.getRowCapacity() != expectedRowCapacity ||                                                          \
        destMatrix.getColumnCapacity() != expectedColumnCapacity ||                                                    \
        destMatrix.getRowCapacityOffset() != expectedRowCapacityOffset ||                                              \
        destMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset)                                          \
    {                                                                                                                  \
        QFAIL("Horizontal concatenation failed, capacity (offset) of the destination matrix is not correct!");         \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(destMatrix == expectedDestMatrix,                                                                         \
             "Horizontal concatenation failed, destination matrix has incorrect values!");

#define TEST_MATRIX_SPLIT_BY_ROW(matrixType)                                                                           \
    QFETCH(Matrix<matrixType>, srcMatrix);                                                                             \
    QFETCH(Matrix<matrixType>, destMatrix);                                                                            \
    QFETCH(Matrix<matrixType>::size_type, splitPosition);                                                              \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcRowCapacity);                                                     \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcColumnCapacity);                                                  \
    QFETCH(Matrix<matrixType>::size_type, expectedDestRowCapacity);                                                    \
    QFETCH(Matrix<matrixType>::size_type, expectedDestColumnCapacity);                                                 \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcRowCapacityOffset);                                \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcColumnCapacityOffset);                             \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestRowCapacityOffset);                               \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestColumnCapacityOffset);                            \
    QFETCH(Matrix<matrixType>, expectedSrcMatrix);                                                                     \
    QFETCH(Matrix<matrixType>, expectedDestMatrix);                                                                    \
                                                                                                                       \
    srcMatrix.splitByRow(destMatrix, splitPosition);                                                                   \
                                                                                                                       \
    if (srcMatrix.getRowCapacity() != expectedSrcRowCapacity ||                                                        \
        srcMatrix.getColumnCapacity() != expectedSrcColumnCapacity ||                                                  \
        srcMatrix.getRowCapacityOffset() != expectedSrcRowCapacityOffset ||                                            \
        srcMatrix.getColumnCapacityOffset() != expectedSrcColumnCapacityOffset)                                        \
    {                                                                                                                  \
        QFAIL("Vertical split failed, capacity (offset) of the source matrix is not correct!");                        \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(srcMatrix == expectedSrcMatrix, "Vertical split failed, source matrix has incorrect values!");            \
                                                                                                                       \
    if (destMatrix.getRowCapacity() != expectedDestRowCapacity ||                                                      \
        destMatrix.getColumnCapacity() != expectedDestColumnCapacity ||                                                \
        destMatrix.getRowCapacityOffset() != expectedDestRowCapacityOffset ||                                          \
        destMatrix.getColumnCapacityOffset() != expectedDestColumnCapacityOffset)                                      \
    {                                                                                                                  \
        QFAIL("Vertical split failed, capacity (offset) of the destination matrix is not correct!");                   \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(destMatrix == expectedDestMatrix, "Vertical split failed, destination matrix has incorrect values!");

#define TEST_MATRIX_SPLIT_BY_COLUMN(matrixType)                                                                        \
    QFETCH(Matrix<matrixType>, srcMatrix);                                                                             \
    QFETCH(Matrix<matrixType>, destMatrix);                                                                            \
    QFETCH(Matrix<matrixType>::size_type, splitPosition);                                                              \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcRowCapacity);                                                     \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcColumnCapacity);                                                  \
    QFETCH(Matrix<matrixType>::size_type, expectedDestRowCapacity);                                                    \
    QFETCH(Matrix<matrixType>::size_type, expectedDestColumnCapacity);                                                 \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcRowCapacityOffset);                                \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcColumnCapacityOffset);                             \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestRowCapacityOffset);                               \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestColumnCapacityOffset);                            \
    QFETCH(Matrix<matrixType>, expectedSrcMatrix);                                                                     \
    QFETCH(Matrix<matrixType>, expectedDestMatrix);                                                                    \
                                                                                                                       \
    srcMatrix.splitByColumn(destMatrix, splitPosition);                                                                \
                                                                                                                       \
    if (srcMatrix.getRowCapacity() != expectedSrcRowCapacity ||                                                        \
        srcMatrix.getColumnCapacity() != expectedSrcColumnCapacity ||                                                  \
        srcMatrix.getRowCapacityOffset() != expectedSrcRowCapacityOffset ||                                            \
        srcMatrix.getColumnCapacityOffset() != expectedSrcColumnCapacityOffset)                                        \
    {                                                                                                                  \
        QFAIL("Horizontal split failed, capacity (offset) of the source matrix is not correct!");                      \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(srcMatrix == expectedSrcMatrix, "Horizontal split failed, source matrix has incorrect values!");          \
                                                                                                                       \
    if (destMatrix.getRowCapacity() != expectedDestRowCapacity ||                                                      \
        destMatrix.getColumnCapacity() != expectedDestColumnCapacity ||                                                \
        destMatrix.getRowCapacityOffset() != expectedDestRowCapacityOffset ||                                          \
        destMatrix.getColumnCapacityOffset() != expectedDestColumnCapacityOffset)                                      \
    {                                                                                                                  \
        QFAIL("Horizontal split failed, capacity (offset) of the destination matrix is not correct!");                 \
    }                                                                                                                  \
                                                                                                                       \
    QVERIFY2(destMatrix == expectedDestMatrix, "Horizontal split failed, destination matrix has incorrect values!");
