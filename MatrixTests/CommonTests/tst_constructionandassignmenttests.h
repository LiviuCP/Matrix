#ifndef TST_CONSTRUCTIONANDASSIGNMENTTESTS_H
#define TST_CONSTRUCTIONANDASSIGNMENTTESTS_H

#include "testutils.h"

#define TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix)                                                \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0u, 0u, 0u, 0u, std::nullopt, std::nullopt,                                 \
                                   "Default constructor initialized matrix with wrong number of rows and columns!",    \
                                   "Default constructor initialized matrix with wrong capacity!",                      \
                                   "Default constructor initialized matrix with wrong capacity offset!")

#define TEST_VECTOR_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(                                                        \
    matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                        \
    requiredRowCapacityOffset, requiredColumnCapacityOffset)                                                           \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity,                 \
                                   requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset,    \
                                   "Vector constructor initialized matrix with wrong number of rows and columns!",     \
                                   "Vector constructor initialized matrix with wrong capacity!",                       \
                                   "Vector constructor initialized matrix with wrong capacity offset!")

#define TEST_IDENTICAL_ELEMENTS_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(                                            \
    matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                        \
    requiredRowCapacityOffset, requiredColumnCapacityOffset)                                                           \
    CHECK_MATRIX_SIZE_AND_CAPACITY(                                                                                    \
        matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                    \
        requiredRowCapacityOffset, requiredColumnCapacityOffset,                                                       \
        "Identical matrix constructor initialized matrix with wrong number of rows and columns!",                      \
        "Identical matrix constructor initialized matrix with wrong capacity!",                                        \
        "Identical matrix constructor initialized matrix with wrong capacity offset!")

#define TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(                                               \
    matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                        \
    requiredRowCapacityOffset, requiredColumnCapacityOffset)                                                           \
    CHECK_MATRIX_SIZE_AND_CAPACITY(                                                                                    \
        matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                    \
        requiredRowCapacityOffset, requiredColumnCapacityOffset,                                                       \
        "Diagonal matrix constructor initialized matrix with wrong number of rows and columns!",                       \
        "Diagonal matrix constructor initialized matrix with wrong capacity!",                                         \
        "Diagonal matrix constructor initialized matrix with wrong capacity offset!")

#define TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns,            \
                                                             requiredRowCapacity, requiredColumnCapacity,              \
                                                             requiredRowCapacityOffset, requiredColumnCapacityOffset)  \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity,                 \
                                   requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset,    \
                                   "Copy constructor initialized matrix with wrong number of rows and columns!",       \
                                   "Copy constructor initialized matrix with wrong capacity!",                         \
                                   "Copy constructor initialized matrix with wrong capacity offset!")

#define TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns,            \
                                                             requiredRowCapacity, requiredColumnCapacity,              \
                                                             requiredRowCapacityOffset, requiredColumnCapacityOffset)  \
    CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity,                 \
                                   requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset,    \
                                   "Move constructor initialized matrix with wrong number of rows and columns!",       \
                                   "Move constructor initialized matrix with wrong capacity!",                         \
                                   "Move constructor initialized matrix with wrong capacity offset!")

#define TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns,             \
                                                            requiredRowCapacity, requiredColumnCapacity,               \
                                                            requiredRowCapacityOffset, requiredColumnCapacityOffset)   \
    CHECK_MATRIX_SIZE_AND_CAPACITY(                                                                                    \
        matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                    \
        requiredRowCapacityOffset, requiredColumnCapacityOffset,                                                       \
        "Copy assignment failed, number of rows or columns of the destination matrix is not correct!",                 \
        "Copy assignment failed, capacity of the destination matrix is not correct!",                                  \
        "Copy assignment failed, capacity offset of the destination matrix is not correct!")

#define TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns,             \
                                                            requiredRowCapacity, requiredColumnCapacity,               \
                                                            requiredRowCapacityOffset, requiredColumnCapacityOffset)   \
    CHECK_MATRIX_SIZE_AND_CAPACITY(                                                                                    \
        matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity, requiredColumnCapacity,                    \
        requiredRowCapacityOffset, requiredColumnCapacityOffset,                                                       \
        "Move assignment failed, number of rows or columns of the destination matrix is not correct!",                 \
        "Move assignment failed, capacity of the destination matrix is not correct!",                                  \
        "Move assignment failed, capacity offset of the destination matrix is not correct!")

#define TEST_COPY_ASSIGNMENT_OPERATOR(MatrixType, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount,           \
                                      destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity,     \
                                      expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned)         \
    const bool isEmptySrcMatrix = srcInitList.empty();                                                                 \
    const bool isEmptyDestMatrix = destInitList.empty();                                                               \
                                                                                                                       \
    if (isSelfAssigned)                                                                                                \
    {                                                                                                                  \
        if (!isEmptyDestMatrix)                                                                                        \
        {                                                                                                              \
            Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};      \
            destMatrix = destMatrix;                                                                                   \
                                                                                                                       \
            TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(                                                       \
                destMatrix, destRowsCount, destColumnsCount, expectedRowCapacity, expectedColumnCapacity,              \
                expectedRowCapacityOffset, expectedColumnCapacityOffset);                                              \
            CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                 \
                destMatrix, destInitList,                                                                              \
                "Copy assignment failed, the destination matrix doesn't have the right values!");                      \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            Matrix<MatrixType> destMatrix;                                                                             \
            destMatrix = destMatrix;                                                                                   \
                                                                                                                       \
            QVERIFY(destMatrix.isEmpty());                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
    else if (!isEmptySrcMatrix && !isEmptyDestMatrix)                                                                  \
    {                                                                                                                  \
        const Matrix<MatrixType> srcMatrix{srcRowsCount, srcColumnsCount, std::move(std::vector{srcInitList})};        \
        Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};          \
                                                                                                                       \
        destMatrix = srcMatrix;                                                                                        \
                                                                                                                       \
        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, srcRowsCount, srcColumnsCount,                 \
                                                            expectedRowCapacity, expectedColumnCapacity,               \
                                                            expectedRowCapacityOffset, expectedColumnCapacityOffset);  \
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                     \
            destMatrix, srcInitList, "Copy assignment failed, the destination matrix doesn't have the right values!"); \
    }                                                                                                                  \
    else if (!isEmptySrcMatrix && isEmptyDestMatrix)                                                                   \
    {                                                                                                                  \
        const Matrix<MatrixType> srcMatrix{srcRowsCount, srcColumnsCount, std::move(std::vector{srcInitList})};        \
        Matrix<MatrixType> destMatrix;                                                                                 \
                                                                                                                       \
        destMatrix = srcMatrix;                                                                                        \
                                                                                                                       \
        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, srcRowsCount, srcColumnsCount,                 \
                                                            expectedRowCapacity, expectedColumnCapacity,               \
                                                            expectedRowCapacityOffset, expectedColumnCapacityOffset);  \
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                     \
            destMatrix, srcInitList, "Copy assignment failed, the destination matrix doesn't have the right values!"); \
    }                                                                                                                  \
    else if (isEmptySrcMatrix && !isEmptyDestMatrix)                                                                   \
    {                                                                                                                  \
        const Matrix<MatrixType> srcMatrix;                                                                            \
        Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};          \
                                                                                                                       \
        destMatrix = srcMatrix;                                                                                        \
                                                                                                                       \
        QVERIFY(destMatrix.isEmpty());                                                                                 \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        const Matrix<MatrixType> srcMatrix;                                                                            \
        Matrix<MatrixType> destMatrix;                                                                                 \
                                                                                                                       \
        destMatrix = srcMatrix;                                                                                        \
                                                                                                                       \
        QVERIFY(destMatrix.isEmpty());                                                                                 \
    }

#define TEST_MOVE_ASSIGNMENT_OPERATOR(MatrixType, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount,           \
                                      destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity,     \
                                      expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned)         \
    const bool isEmptySrcMatrix = srcInitList.empty();                                                                 \
    const bool isEmptyDestMatrix = destInitList.empty();                                                               \
                                                                                                                       \
    if (isSelfAssigned)                                                                                                \
    {                                                                                                                  \
        if (!isEmptyDestMatrix)                                                                                        \
        {                                                                                                              \
            Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};      \
            destMatrix = std::move(destMatrix);                                                                        \
                                                                                                                       \
            TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(                                                       \
                destMatrix, destRowsCount, destColumnsCount, expectedRowCapacity, expectedColumnCapacity,              \
                expectedRowCapacityOffset, expectedColumnCapacityOffset);                                              \
            CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                 \
                destMatrix, destInitList,                                                                              \
                "Move assignment failed, the destination matrix doesn't have the right values!");                      \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            Matrix<MatrixType> destMatrix;                                                                             \
            destMatrix = std::move(destMatrix);                                                                        \
                                                                                                                       \
            QVERIFY(destMatrix.isEmpty());                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
    else if (!isEmptySrcMatrix && !isEmptyDestMatrix)                                                                  \
    {                                                                                                                  \
        Matrix<MatrixType> srcMatrix{srcRowsCount, srcColumnsCount, std::move(std::vector{srcInitList})};              \
        Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};          \
                                                                                                                       \
        destMatrix = std::move(srcMatrix);                                                                             \
                                                                                                                       \
        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, srcRowsCount, srcColumnsCount,                 \
                                                            expectedRowCapacity, expectedColumnCapacity,               \
                                                            expectedRowCapacityOffset, expectedColumnCapacityOffset);  \
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                     \
            destMatrix, srcInitList, "Move assignment failed, the destination matrix doesn't have the right values!"); \
    }                                                                                                                  \
    else if (!isEmptySrcMatrix && isEmptyDestMatrix)                                                                   \
    {                                                                                                                  \
        Matrix<MatrixType> srcMatrix{srcRowsCount, srcColumnsCount, std::move(std::vector{srcInitList})};              \
        Matrix<MatrixType> destMatrix;                                                                                 \
                                                                                                                       \
        destMatrix = std::move(srcMatrix);                                                                             \
                                                                                                                       \
        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, srcRowsCount, srcColumnsCount,                 \
                                                            expectedRowCapacity, expectedColumnCapacity,               \
                                                            expectedRowCapacityOffset, expectedColumnCapacityOffset);  \
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(                                                                     \
            destMatrix, srcInitList, "Move assignment failed, the destination matrix doesn't have the right values!"); \
    }                                                                                                                  \
    else if (isEmptySrcMatrix && !isEmptyDestMatrix)                                                                   \
    {                                                                                                                  \
        Matrix<MatrixType> srcMatrix;                                                                                  \
        Matrix<MatrixType> destMatrix{destRowsCount, destColumnsCount, std::move(std::vector{destInitList})};          \
                                                                                                                       \
        destMatrix = std::move(srcMatrix);                                                                             \
                                                                                                                       \
        QVERIFY(destMatrix.isEmpty());                                                                                 \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        Matrix<MatrixType> srcMatrix;                                                                                  \
        Matrix<MatrixType> destMatrix;                                                                                 \
                                                                                                                       \
        destMatrix = std::move(srcMatrix);                                                                             \
                                                                                                                       \
        QVERIFY(destMatrix.isEmpty());                                                                                 \
    }

#endif // TST_CONSTRUCTIONANDASSIGNMENTTESTS_H
