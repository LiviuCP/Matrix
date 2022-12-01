#ifndef TST_OTHERFUNCTIONALITYTESTS_H
#define TST_OTHERFUNCTIONALITYTESTS_H

#define TEST_MATRIX_BOOLEAN_OPERATOR(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(bool, checkTrue); \
 \
    if (checkTrue) \
    { \
        QVERIFY2(matrix, "The boolean operator does not return the expected value (true)!"); \
    } \
    else \
    { \
        QVERIFY2(!matrix, "The boolean operator does not return the expected value (false)!"); \
    }

#define TEST_MATRIXES_ARE_EQUAL(matrixType) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
    QFETCH(bool, checkEqualityToItself); \
 \
    if (checkEqualityToItself) \
    { \
        QVERIFY2(firstMatrix == firstMatrix && \
                 !(firstMatrix != firstMatrix), "The matrix should be equal to itself!"); \
    } \
    else \
    { \
        QVERIFY2(firstMatrix == secondMatrix && \
                 !(firstMatrix != secondMatrix), "The matrixes should be equal!"); \
    }

#define TEST_MATRIXES_ARE_NOT_EQUAL(matrixType) \
    QFETCH(Matrix<matrixType>, firstMatrix); \
    QFETCH(Matrix<matrixType>, secondMatrix); \
 \
    QVERIFY2(firstMatrix != secondMatrix && \
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");

#endif // TST_OTHERFUNCTIONALITYTESTS_H
