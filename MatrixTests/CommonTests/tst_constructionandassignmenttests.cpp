#include <QtTest>

#include "tst_constructionandassignmenttests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class ConstructionAndAssignmentTests : public QObject
{
    Q_OBJECT

private slots:
    void testIntMatrixDefaultConstructor();
    void testIntMatrixInitListConstructor();
    void testIntMatrixIdenticalMatrixConstructor();
    void testIntMatrixDiagonalMatrixConstructor();
    void testIntMatrixCopyConstructor();
    void testIntMatrixMoveConstructor();
    void testIntMatrixCopyAssignmentOperator();
    void testIntMatrixMoveAssignmentOperator();

    void testStringMatrixDefaultConstructor();
    void testStringMatrixInitListConstructor();
    void testStringMatrixIdenticalMatrixConstructor();
    void testStringMatrixDiagonalMatrixConstructor();
    void testStringMatrixCopyConstructor();
    void testStringMatrixMoveConstructor();
    void testStringMatrixCopyAssignmentOperator();
    void testStringMatrixMoveAssignmentOperator();
};

void ConstructionAndAssignmentTests::testIntMatrixDefaultConstructor()
{
    IntMatrix matrix{};
    TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix);
}

void ConstructionAndAssignmentTests::testIntMatrixInitListConstructor()
{
    IntMatrix smallMatrix{2, 3, {1, 2, 3, 4, 5, 6}};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 2, 3, 2, 3);

    QVERIFY2(smallMatrix.at(0, 0) == 1 &&
             smallMatrix.at(0, 1) == 2 &&
             smallMatrix.at(0, 2) == 3 &&
             smallMatrix.at(1, 0) == 4 &&
             smallMatrix.at(1, 1) == 5 &&
             smallMatrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the init list constructor");

    IntMatrix largeMatrix{8, 10, { -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                  -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                  -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                  -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                  -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                  -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                  -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                  -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                          }};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 8, 10, 10, 12);

    const IntMatrix& lm{largeMatrix};

    QVERIFY(lm.at(0, 0) ==  -1 && lm.at(0, 1) ==  2 && lm.at(0, 2) ==  -3 && lm.at(0, 3) ==  4 && lm.at(0, 4) ==  -5 && lm.at(0, 5) ==  6 && lm.at(0, 6) ==  -7 && lm.at(0, 7) ==  8 && lm.at(0, 8) ==  -9 && lm.at(0, 9) == 10 &&
            lm.at(1, 0) == -11 && lm.at(1, 1) == 12 && lm.at(1, 2) == -13 && lm.at(1, 3) == 14 && lm.at(1, 4) == -15 && lm.at(1, 5) == 16 && lm.at(1, 6) == -17 && lm.at(1, 7) == 18 && lm.at(1, 8) == -19 && lm.at(1, 9) == 20 &&
            lm.at(2, 0) == -21 && lm.at(2, 1) == 22 && lm.at(2, 2) == -23 && lm.at(2, 3) == 24 && lm.at(2, 4) == -25 && lm.at(2, 5) == 26 && lm.at(2, 6) == -27 && lm.at(2, 7) == 28 && lm.at(2, 8) == -29 && lm.at(2, 9) == 30 &&
            lm.at(3, 0) == -31 && lm.at(3, 1) == 32 && lm.at(3, 2) == -33 && lm.at(3, 3) == 34 && lm.at(3, 4) == -35 && lm.at(3, 5) == 36 && lm.at(3, 6) == -37 && lm.at(3, 7) == 38 && lm.at(3, 8) == -39 && lm.at(3, 9) == 40 &&
            lm.at(4, 0) == -41 && lm.at(4, 1) == 42 && lm.at(4, 2) == -43 && lm.at(4, 3) == 44 && lm.at(4, 4) == -45 && lm.at(4, 5) == 46 && lm.at(4, 6) == -47 && lm.at(4, 7) == 48 && lm.at(4, 8) == -49 && lm.at(4, 9) == 50 &&
            lm.at(5, 0) == -51 && lm.at(5, 1) == 52 && lm.at(5, 2) == -53 && lm.at(5, 3) == 54 && lm.at(5, 4) == -55 && lm.at(5, 5) == 56 && lm.at(5, 6) == -57 && lm.at(5, 7) == 58 && lm.at(5, 8) == -59 && lm.at(5, 9) == 60 &&
            lm.at(6, 0) == -61 && lm.at(6, 1) == 62 && lm.at(6, 2) == -63 && lm.at(6, 3) == 64 && lm.at(6, 4) == -65 && lm.at(6, 5) == 66 && lm.at(6, 6) == -67 && lm.at(6, 7) == 68 && lm.at(6, 8) == -69 && lm.at(6, 9) == 70 &&
            lm.at(7, 0) == -71 && lm.at(7, 1) == 72 && lm.at(7, 2) == -73 && lm.at(7, 3) == 74 && lm.at(7, 4) == -75 && lm.at(7, 5) == 76 && lm.at(7, 6) == -77 && lm.at(7, 7) == 78 && lm.at(7, 8) == -79 && lm.at(7, 9) == 80);
}

void ConstructionAndAssignmentTests::testIntMatrixIdenticalMatrixConstructor()
{
    IntMatrix smallMatrix{3, 2, 4};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 3, 2, 3, 2);
    CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(smallMatrix, 4, "Matrix elements have not been correctly initialized by the identical matrix constructor");

    IntMatrix largeMatrix{10, 8, -5};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 10, 8, 12, 10);
    CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(largeMatrix, -5, "Matrix elements have not been correctly initialized by the identical matrix constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixDiagonalMatrixConstructor()
{
    IntMatrix smallMatrix{3, std::pair<int, int>{2, 1}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 3, 3, 3, 3);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(smallMatrix, 2, 1, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");

    IntMatrix largeMatrix{9, std::pair<int, int>{-5, -4}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 9, 9, 11, 11);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(largeMatrix, -5, -4, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixCopyConstructor()
{
    {
        const IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the copy constructor");
    }

    {
        const IntMatrix srcMatrix{8, 10, { -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                          -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                          -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                          -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                          -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                          -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                          -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                          -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                                  }};

        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const IntMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  -1 && dest.at(0, 1) ==  2 && dest.at(0, 2) ==  -3 && dest.at(0, 3) ==  4 && dest.at(0, 4) ==  -5 && dest.at(0, 5) ==  6 && dest.at(0, 6) ==  -7 && dest.at(0, 7) ==  8 && dest.at(0, 8) ==  -9 && dest.at(0, 9) == 10 &&
                dest.at(1, 0) == -11 && dest.at(1, 1) == 12 && dest.at(1, 2) == -13 && dest.at(1, 3) == 14 && dest.at(1, 4) == -15 && dest.at(1, 5) == 16 && dest.at(1, 6) == -17 && dest.at(1, 7) == 18 && dest.at(1, 8) == -19 && dest.at(1, 9) == 20 &&
                dest.at(2, 0) == -21 && dest.at(2, 1) == 22 && dest.at(2, 2) == -23 && dest.at(2, 3) == 24 && dest.at(2, 4) == -25 && dest.at(2, 5) == 26 && dest.at(2, 6) == -27 && dest.at(2, 7) == 28 && dest.at(2, 8) == -29 && dest.at(2, 9) == 30 &&
                dest.at(3, 0) == -31 && dest.at(3, 1) == 32 && dest.at(3, 2) == -33 && dest.at(3, 3) == 34 && dest.at(3, 4) == -35 && dest.at(3, 5) == 36 && dest.at(3, 6) == -37 && dest.at(3, 7) == 38 && dest.at(3, 8) == -39 && dest.at(3, 9) == 40 &&
                dest.at(4, 0) == -41 && dest.at(4, 1) == 42 && dest.at(4, 2) == -43 && dest.at(4, 3) == 44 && dest.at(4, 4) == -45 && dest.at(4, 5) == 46 && dest.at(4, 6) == -47 && dest.at(4, 7) == 48 && dest.at(4, 8) == -49 && dest.at(4, 9) == 50 &&
                dest.at(5, 0) == -51 && dest.at(5, 1) == 52 && dest.at(5, 2) == -53 && dest.at(5, 3) == 54 && dest.at(5, 4) == -55 && dest.at(5, 5) == 56 && dest.at(5, 6) == -57 && dest.at(5, 7) == 58 && dest.at(5, 8) == -59 && dest.at(5, 9) == 60 &&
                dest.at(6, 0) == -61 && dest.at(6, 1) == 62 && dest.at(6, 2) == -63 && dest.at(6, 3) == 64 && dest.at(6, 4) == -65 && dest.at(6, 5) == 66 && dest.at(6, 6) == -67 && dest.at(6, 7) == 68 && dest.at(6, 8) == -69 && dest.at(6, 9) == 70 &&
                dest.at(7, 0) == -71 && dest.at(7, 1) == 72 && dest.at(7, 2) == -73 && dest.at(7, 3) == 74 && dest.at(7, 4) == -75 && dest.at(7, 5) == 76 && dest.at(7, 6) == -77 && dest.at(7, 7) == 78 && dest.at(7, 8) == -79 && dest.at(7, 9) == 80);
    }

    {
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixMoveConstructor()
{
    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6} };
        IntMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                     destMatrix.at(0, 1) == 2 &&
                     destMatrix.at(0, 2) == 3 &&
                     destMatrix.at(1, 0) == 4 &&
                     destMatrix.at(1, 1) == 5 &&
                     destMatrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the move constructor");

        TEST_MOVE_CONSTRUCTOR_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        IntMatrix srcMatrix{8, 10, { -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                    -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                    -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                    -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                    -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                    -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                    -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                    -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                            }};

        IntMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const IntMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  -1 && dest.at(0, 1) ==  2 && dest.at(0, 2) ==  -3 && dest.at(0, 3) ==  4 && dest.at(0, 4) ==  -5 && dest.at(0, 5) ==  6 && dest.at(0, 6) ==  -7 && dest.at(0, 7) ==  8 && dest.at(0, 8) ==  -9 && dest.at(0, 9) == 10 &&
                dest.at(1, 0) == -11 && dest.at(1, 1) == 12 && dest.at(1, 2) == -13 && dest.at(1, 3) == 14 && dest.at(1, 4) == -15 && dest.at(1, 5) == 16 && dest.at(1, 6) == -17 && dest.at(1, 7) == 18 && dest.at(1, 8) == -19 && dest.at(1, 9) == 20 &&
                dest.at(2, 0) == -21 && dest.at(2, 1) == 22 && dest.at(2, 2) == -23 && dest.at(2, 3) == 24 && dest.at(2, 4) == -25 && dest.at(2, 5) == 26 && dest.at(2, 6) == -27 && dest.at(2, 7) == 28 && dest.at(2, 8) == -29 && dest.at(2, 9) == 30 &&
                dest.at(3, 0) == -31 && dest.at(3, 1) == 32 && dest.at(3, 2) == -33 && dest.at(3, 3) == 34 && dest.at(3, 4) == -35 && dest.at(3, 5) == 36 && dest.at(3, 6) == -37 && dest.at(3, 7) == 38 && dest.at(3, 8) == -39 && dest.at(3, 9) == 40 &&
                dest.at(4, 0) == -41 && dest.at(4, 1) == 42 && dest.at(4, 2) == -43 && dest.at(4, 3) == 44 && dest.at(4, 4) == -45 && dest.at(4, 5) == 46 && dest.at(4, 6) == -47 && dest.at(4, 7) == 48 && dest.at(4, 8) == -49 && dest.at(4, 9) == 50 &&
                dest.at(5, 0) == -51 && dest.at(5, 1) == 52 && dest.at(5, 2) == -53 && dest.at(5, 3) == 54 && dest.at(5, 4) == -55 && dest.at(5, 5) == 56 && dest.at(5, 6) == -57 && dest.at(5, 7) == 58 && dest.at(5, 8) == -59 && dest.at(5, 9) == 60 &&
                dest.at(6, 0) == -61 && dest.at(6, 1) == 62 && dest.at(6, 2) == -63 && dest.at(6, 3) == 64 && dest.at(6, 4) == -65 && dest.at(6, 5) == 66 && dest.at(6, 6) == -67 && dest.at(6, 7) == 68 && dest.at(6, 8) == -69 && dest.at(6, 9) == 70 &&
                dest.at(7, 0) == -71 && dest.at(7, 1) == 72 && dest.at(7, 2) == -73 && dest.at(7, 3) == 74 && dest.at(7, 4) == -75 && dest.at(7, 5) == 76 && dest.at(7, 6) == -77 && dest.at(7, 7) == 78 && dest.at(7, 8) == -79 && dest.at(7, 9) == 80);

        TEST_MOVE_CONSTRUCTOR_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixCopyAssignmentOperator()
{
    {
        const IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }

    {
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }

    {
        const IntMatrix srcMatrix{3, 4, 7};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 3, 4, 3, 5);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, 7, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{4, 3, 9};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 4, 3, 5, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, 9, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{4, 3, 9};
        IntMatrix destMatrix{4, 2, 8};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 4, 3, 5, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, 9, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{20, 20, 11};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 20, 20, 25, 25);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, 11, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{22, 22, 12};
        IntMatrix destMatrix{2, 3, 8};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 22, 22, 27, 27);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, 12, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix = matrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6, "Same matrix copy assignment failed, the matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{};

        matrix = matrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0, 0, 0, 0);
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        const IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = thirdMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16, "Copy assignment failed, the first matrix doesn't have the right values!");
    }

    // test cases when destination matrix already has the required capacity
    {
        const IntMatrix srcMatrix{3, 5, -2};
        IntMatrix destMatrix{3, 5, 7};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 3, 5, 3, 6);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, -2, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{9, 3, -2};
        IntMatrix destMatrix{4, 2, 7};

        destMatrix.resize(4, 2, 11, 3);
        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 9, 3, 11, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, -2, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    // additional test
    {
        const IntMatrix srcMatrix{8, 10, { -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                          -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                          -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                          -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                          -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                          -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                          -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                          -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                                  }};

        IntMatrix destMatrix{3, 5, 7};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const IntMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  -1 && dest.at(0, 1) ==  2 && dest.at(0, 2) ==  -3 && dest.at(0, 3) ==  4 && dest.at(0, 4) ==  -5 && dest.at(0, 5) ==  6 && dest.at(0, 6) ==  -7 && dest.at(0, 7) ==  8 && dest.at(0, 8) ==  -9 && dest.at(0, 9) == 10 &&
                dest.at(1, 0) == -11 && dest.at(1, 1) == 12 && dest.at(1, 2) == -13 && dest.at(1, 3) == 14 && dest.at(1, 4) == -15 && dest.at(1, 5) == 16 && dest.at(1, 6) == -17 && dest.at(1, 7) == 18 && dest.at(1, 8) == -19 && dest.at(1, 9) == 20 &&
                dest.at(2, 0) == -21 && dest.at(2, 1) == 22 && dest.at(2, 2) == -23 && dest.at(2, 3) == 24 && dest.at(2, 4) == -25 && dest.at(2, 5) == 26 && dest.at(2, 6) == -27 && dest.at(2, 7) == 28 && dest.at(2, 8) == -29 && dest.at(2, 9) == 30 &&
                dest.at(3, 0) == -31 && dest.at(3, 1) == 32 && dest.at(3, 2) == -33 && dest.at(3, 3) == 34 && dest.at(3, 4) == -35 && dest.at(3, 5) == 36 && dest.at(3, 6) == -37 && dest.at(3, 7) == 38 && dest.at(3, 8) == -39 && dest.at(3, 9) == 40 &&
                dest.at(4, 0) == -41 && dest.at(4, 1) == 42 && dest.at(4, 2) == -43 && dest.at(4, 3) == 44 && dest.at(4, 4) == -45 && dest.at(4, 5) == 46 && dest.at(4, 6) == -47 && dest.at(4, 7) == 48 && dest.at(4, 8) == -49 && dest.at(4, 9) == 50 &&
                dest.at(5, 0) == -51 && dest.at(5, 1) == 52 && dest.at(5, 2) == -53 && dest.at(5, 3) == 54 && dest.at(5, 4) == -55 && dest.at(5, 5) == 56 && dest.at(5, 6) == -57 && dest.at(5, 7) == 58 && dest.at(5, 8) == -59 && dest.at(5, 9) == 60 &&
                dest.at(6, 0) == -61 && dest.at(6, 1) == 62 && dest.at(6, 2) == -63 && dest.at(6, 3) == 64 && dest.at(6, 4) == -65 && dest.at(6, 5) == 66 && dest.at(6, 6) == -67 && dest.at(6, 7) == 68 && dest.at(6, 8) == -69 && dest.at(6, 9) == 70 &&
                dest.at(7, 0) == -71 && dest.at(7, 1) == 72 && dest.at(7, 2) == -73 && dest.at(7, 3) == 74 && dest.at(7, 4) == -75 && dest.at(7, 5) == 76 && dest.at(7, 6) == -77 && dest.at(7, 7) == 78 && dest.at(7, 8) == -79 && dest.at(7, 9) == 80);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixMoveAssignmentOperator()
{
    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Move assignment failed, the destination matrix doesn't have the right values!");

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        IntMatrix srcMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == 1 &&
                 destMatrix.at(0, 1) == 2 &&
                 destMatrix.at(0, 2) == 3 &&
                 destMatrix.at(1, 0) == 4 &&
                 destMatrix.at(1, 1) == 5 &&
                 destMatrix.at(1, 2) == 6, "Move assignment failed, the destination matrix doesn't have the right values!");

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        IntMatrix srcMatrix{};
        IntMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = std::move(thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16, "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = std::move(secondMatrix = thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16, "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

        matrix = std::move(matrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

        QVERIFY2(matrix.at(0, 0) == 1 &&
                 matrix.at(0, 1) == 2 &&
                 matrix.at(0, 2) == 3 &&
                 matrix.at(1, 0) == 4 &&
                 matrix.at(1, 1) == 5 &&
                 matrix.at(1, 2) == 6, "Move assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        IntMatrix matrix;

        matrix = std::move(matrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(matrix, 0, 0, 0, 0);
    }

    // additional test
    {
        IntMatrix srcMatrix{8, 10, { -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                    -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                    -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                    -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                    -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                    -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                    -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                    -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                            }};

        IntMatrix destMatrix{3, 5, 7};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const IntMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  -1 && dest.at(0, 1) ==  2 && dest.at(0, 2) ==  -3 && dest.at(0, 3) ==  4 && dest.at(0, 4) ==  -5 && dest.at(0, 5) ==  6 && dest.at(0, 6) ==  -7 && dest.at(0, 7) ==  8 && dest.at(0, 8) ==  -9 && dest.at(0, 9) == 10 &&
                dest.at(1, 0) == -11 && dest.at(1, 1) == 12 && dest.at(1, 2) == -13 && dest.at(1, 3) == 14 && dest.at(1, 4) == -15 && dest.at(1, 5) == 16 && dest.at(1, 6) == -17 && dest.at(1, 7) == 18 && dest.at(1, 8) == -19 && dest.at(1, 9) == 20 &&
                dest.at(2, 0) == -21 && dest.at(2, 1) == 22 && dest.at(2, 2) == -23 && dest.at(2, 3) == 24 && dest.at(2, 4) == -25 && dest.at(2, 5) == 26 && dest.at(2, 6) == -27 && dest.at(2, 7) == 28 && dest.at(2, 8) == -29 && dest.at(2, 9) == 30 &&
                dest.at(3, 0) == -31 && dest.at(3, 1) == 32 && dest.at(3, 2) == -33 && dest.at(3, 3) == 34 && dest.at(3, 4) == -35 && dest.at(3, 5) == 36 && dest.at(3, 6) == -37 && dest.at(3, 7) == 38 && dest.at(3, 8) == -39 && dest.at(3, 9) == 40 &&
                dest.at(4, 0) == -41 && dest.at(4, 1) == 42 && dest.at(4, 2) == -43 && dest.at(4, 3) == 44 && dest.at(4, 4) == -45 && dest.at(4, 5) == 46 && dest.at(4, 6) == -47 && dest.at(4, 7) == 48 && dest.at(4, 8) == -49 && dest.at(4, 9) == 50 &&
                dest.at(5, 0) == -51 && dest.at(5, 1) == 52 && dest.at(5, 2) == -53 && dest.at(5, 3) == 54 && dest.at(5, 4) == -55 && dest.at(5, 5) == 56 && dest.at(5, 6) == -57 && dest.at(5, 7) == 58 && dest.at(5, 8) == -59 && dest.at(5, 9) == 60 &&
                dest.at(6, 0) == -61 && dest.at(6, 1) == 62 && dest.at(6, 2) == -63 && dest.at(6, 3) == 64 && dest.at(6, 4) == -65 && dest.at(6, 5) == 66 && dest.at(6, 6) == -67 && dest.at(6, 7) == 68 && dest.at(6, 8) == -69 && dest.at(6, 9) == 70 &&
                dest.at(7, 0) == -71 && dest.at(7, 1) == 72 && dest.at(7, 2) == -73 && dest.at(7, 3) == 74 && dest.at(7, 4) == -75 && dest.at(7, 5) == 76 && dest.at(7, 6) == -77 && dest.at(7, 7) == 78 && dest.at(7, 8) == -79 && dest.at(7, 9) == 80);

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixDefaultConstructor()
{
    StringMatrix matrix{};
    TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix);
}

void ConstructionAndAssignmentTests::testStringMatrixInitListConstructor()
{
    StringMatrix smallMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 2, 3, 2, 3);

    QVERIFY2(smallMatrix.at(0, 0) == "First" &&
             smallMatrix.at(0, 1) == "Second" &&
             smallMatrix.at(0, 2) == "Third" &&
             smallMatrix.at(1, 0) == "Fourth" &&
             smallMatrix.at(1, 1) == "Fifth" &&
             smallMatrix.at(1, 2) == "Sixth", "Matrix elements have not been correctly initialized by the init list constructor");

    StringMatrix largeMatrix{8, 10, { "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                     "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                     "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                     "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                     "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                     "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                     "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                     "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                                 }};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 8, 10, 10, 12);

    const StringMatrix& lm{largeMatrix};

    QVERIFY(lm.at(0, 0) ==  "-1a" && lm.at(0, 1) ==  "2B" && lm.at(0, 2) ==  "-3c" && lm.at(0, 3) ==  "4D" && lm.at(0, 4) ==  "-5e" && lm.at(0, 5) ==  "6F" && lm.at(0, 6) ==  "-7g" && lm.at(0, 7) ==  "8H" && lm.at(0, 8) ==  "-9i" && lm.at(0, 9) == "10J" &&
            lm.at(1, 0) == "-11a" && lm.at(1, 1) == "12B" && lm.at(1, 2) == "-13c" && lm.at(1, 3) == "14D" && lm.at(1, 4) == "-15e" && lm.at(1, 5) == "16F" && lm.at(1, 6) == "-17g" && lm.at(1, 7) == "18H" && lm.at(1, 8) == "-19i" && lm.at(1, 9) == "20J" &&
            lm.at(2, 0) == "-21a" && lm.at(2, 1) == "22B" && lm.at(2, 2) == "-23c" && lm.at(2, 3) == "24D" && lm.at(2, 4) == "-25e" && lm.at(2, 5) == "26F" && lm.at(2, 6) == "-27g" && lm.at(2, 7) == "28H" && lm.at(2, 8) == "-29i" && lm.at(2, 9) == "30J" &&
            lm.at(3, 0) == "-31a" && lm.at(3, 1) == "32B" && lm.at(3, 2) == "-33c" && lm.at(3, 3) == "34D" && lm.at(3, 4) == "-35e" && lm.at(3, 5) == "36F" && lm.at(3, 6) == "-37g" && lm.at(3, 7) == "38H" && lm.at(3, 8) == "-39i" && lm.at(3, 9) == "40J" &&
            lm.at(4, 0) == "-41a" && lm.at(4, 1) == "42B" && lm.at(4, 2) == "-43c" && lm.at(4, 3) == "44D" && lm.at(4, 4) == "-45e" && lm.at(4, 5) == "46F" && lm.at(4, 6) == "-47g" && lm.at(4, 7) == "48H" && lm.at(4, 8) == "-49i" && lm.at(4, 9) == "50J" &&
            lm.at(5, 0) == "-51a" && lm.at(5, 1) == "52B" && lm.at(5, 2) == "-53c" && lm.at(5, 3) == "54D" && lm.at(5, 4) == "-55e" && lm.at(5, 5) == "56F" && lm.at(5, 6) == "-57g" && lm.at(5, 7) == "58H" && lm.at(5, 8) == "-59i" && lm.at(5, 9) == "60J" &&
            lm.at(6, 0) == "-61a" && lm.at(6, 1) == "62B" && lm.at(6, 2) == "-63c" && lm.at(6, 3) == "64D" && lm.at(6, 4) == "-65e" && lm.at(6, 5) == "66F" && lm.at(6, 6) == "-67g" && lm.at(6, 7) == "68H" && lm.at(6, 8) == "-69i" && lm.at(6, 9) == "70J" &&
            lm.at(7, 0) == "-71a" && lm.at(7, 1) == "72B" && lm.at(7, 2) == "-73c" && lm.at(7, 3) == "74D" && lm.at(7, 4) == "-75e" && lm.at(7, 5) == "76F" && lm.at(7, 6) == "-77g" && lm.at(7, 7) == "78H" && lm.at(7, 8) == "-79i" && lm.at(7, 9) == "80J");
}

void ConstructionAndAssignmentTests::testStringMatrixIdenticalMatrixConstructor()
{
    StringMatrix smallMatrix{3, 2, "Fourth"};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 3, 2, 3, 2);
    CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(smallMatrix, "Fourth", "Matrix elements have not been correctly initialized by the identical matrix constructor");

    StringMatrix largeMatrix{10, 8, "_Fifth"};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 10, 8, 12, 10);
    CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(largeMatrix, "_Fifth", "Matrix elements have not been correctly initialized by the identical matrix constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixDiagonalMatrixConstructor()
{
    StringMatrix smallMatrix{3, std::pair<std::string, std::string>{"Second", "First"}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(smallMatrix, 3, 3, 3, 3);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(smallMatrix, "Second", "First", "Matrix elements have not been correctly initialized by the diagonal matrix constructor");

    StringMatrix largeMatrix{9, std::pair<std::string, std::string>{"_Fifth", "_Fourth"}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(largeMatrix, 9, 9, 11, 11);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(largeMatrix, "_Fifth", "_Fourth", "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixCopyConstructor()
{
    {
        const StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                 destMatrix.at(0, 1) == "Second" &&
                 destMatrix.at(0, 2) == "Third" &&
                 destMatrix.at(1, 0) == "Fourth" &&
                 destMatrix.at(1, 1) == "Fifth" &&
                 destMatrix.at(1, 2) == "Sixth", "Matrix elements have not been correctly initialized by the copy constructor");
    }

    {
        const StringMatrix srcMatrix{8, 10, { "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                             "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                             "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                             "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                             "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                             "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                             "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                             "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                                     }};

        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const StringMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  "-1a" && dest.at(0, 1) ==  "2B" && dest.at(0, 2) ==  "-3c" && dest.at(0, 3) ==  "4D" && dest.at(0, 4) ==  "-5e" && dest.at(0, 5) ==  "6F" && dest.at(0, 6) ==  "-7g" && dest.at(0, 7) ==  "8H" && dest.at(0, 8) ==  "-9i" && dest.at(0, 9) == "10J" &&
                dest.at(1, 0) == "-11a" && dest.at(1, 1) == "12B" && dest.at(1, 2) == "-13c" && dest.at(1, 3) == "14D" && dest.at(1, 4) == "-15e" && dest.at(1, 5) == "16F" && dest.at(1, 6) == "-17g" && dest.at(1, 7) == "18H" && dest.at(1, 8) == "-19i" && dest.at(1, 9) == "20J" &&
                dest.at(2, 0) == "-21a" && dest.at(2, 1) == "22B" && dest.at(2, 2) == "-23c" && dest.at(2, 3) == "24D" && dest.at(2, 4) == "-25e" && dest.at(2, 5) == "26F" && dest.at(2, 6) == "-27g" && dest.at(2, 7) == "28H" && dest.at(2, 8) == "-29i" && dest.at(2, 9) == "30J" &&
                dest.at(3, 0) == "-31a" && dest.at(3, 1) == "32B" && dest.at(3, 2) == "-33c" && dest.at(3, 3) == "34D" && dest.at(3, 4) == "-35e" && dest.at(3, 5) == "36F" && dest.at(3, 6) == "-37g" && dest.at(3, 7) == "38H" && dest.at(3, 8) == "-39i" && dest.at(3, 9) == "40J" &&
                dest.at(4, 0) == "-41a" && dest.at(4, 1) == "42B" && dest.at(4, 2) == "-43c" && dest.at(4, 3) == "44D" && dest.at(4, 4) == "-45e" && dest.at(4, 5) == "46F" && dest.at(4, 6) == "-47g" && dest.at(4, 7) == "48H" && dest.at(4, 8) == "-49i" && dest.at(4, 9) == "50J" &&
                dest.at(5, 0) == "-51a" && dest.at(5, 1) == "52B" && dest.at(5, 2) == "-53c" && dest.at(5, 3) == "54D" && dest.at(5, 4) == "-55e" && dest.at(5, 5) == "56F" && dest.at(5, 6) == "-57g" && dest.at(5, 7) == "58H" && dest.at(5, 8) == "-59i" && dest.at(5, 9) == "60J" &&
                dest.at(6, 0) == "-61a" && dest.at(6, 1) == "62B" && dest.at(6, 2) == "-63c" && dest.at(6, 3) == "64D" && dest.at(6, 4) == "-65e" && dest.at(6, 5) == "66F" && dest.at(6, 6) == "-67g" && dest.at(6, 7) == "68H" && dest.at(6, 8) == "-69i" && dest.at(6, 9) == "70J" &&
                dest.at(7, 0) == "-71a" && dest.at(7, 1) == "72B" && dest.at(7, 2) == "-73c" && dest.at(7, 3) == "74D" && dest.at(7, 4) == "-75e" && dest.at(7, 5) == "76F" && dest.at(7, 6) == "-77g" && dest.at(7, 7) == "78H" && dest.at(7, 8) == "-79i" && dest.at(7, 9) == "80J");
    }

    {
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixMoveConstructor()
{
    {
        StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} };
        StringMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                     destMatrix.at(0, 1) == "Second" &&
                     destMatrix.at(0, 2) == "Third" &&
                     destMatrix.at(1, 0) == "Fourth" &&
                     destMatrix.at(1, 1) == "Fifth" &&
                     destMatrix.at(1, 2) == "Sixth", "Matrix elements have not been correctly initialized by the move constructor");

        TEST_MOVE_CONSTRUCTOR_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        StringMatrix srcMatrix{8, 10, { "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                       "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                       "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                       "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                       "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                       "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                       "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                       "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                               }};

        StringMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const StringMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  "-1a" && dest.at(0, 1) ==  "2B" && dest.at(0, 2) ==  "-3c" && dest.at(0, 3) ==  "4D" && dest.at(0, 4) ==  "-5e" && dest.at(0, 5) ==  "6F" && dest.at(0, 6) ==  "-7g" && dest.at(0, 7) ==  "8H" && dest.at(0, 8) ==  "-9i" && dest.at(0, 9) == "10J" &&
                dest.at(1, 0) == "-11a" && dest.at(1, 1) == "12B" && dest.at(1, 2) == "-13c" && dest.at(1, 3) == "14D" && dest.at(1, 4) == "-15e" && dest.at(1, 5) == "16F" && dest.at(1, 6) == "-17g" && dest.at(1, 7) == "18H" && dest.at(1, 8) == "-19i" && dest.at(1, 9) == "20J" &&
                dest.at(2, 0) == "-21a" && dest.at(2, 1) == "22B" && dest.at(2, 2) == "-23c" && dest.at(2, 3) == "24D" && dest.at(2, 4) == "-25e" && dest.at(2, 5) == "26F" && dest.at(2, 6) == "-27g" && dest.at(2, 7) == "28H" && dest.at(2, 8) == "-29i" && dest.at(2, 9) == "30J" &&
                dest.at(3, 0) == "-31a" && dest.at(3, 1) == "32B" && dest.at(3, 2) == "-33c" && dest.at(3, 3) == "34D" && dest.at(3, 4) == "-35e" && dest.at(3, 5) == "36F" && dest.at(3, 6) == "-37g" && dest.at(3, 7) == "38H" && dest.at(3, 8) == "-39i" && dest.at(3, 9) == "40J" &&
                dest.at(4, 0) == "-41a" && dest.at(4, 1) == "42B" && dest.at(4, 2) == "-43c" && dest.at(4, 3) == "44D" && dest.at(4, 4) == "-45e" && dest.at(4, 5) == "46F" && dest.at(4, 6) == "-47g" && dest.at(4, 7) == "48H" && dest.at(4, 8) == "-49i" && dest.at(4, 9) == "50J" &&
                dest.at(5, 0) == "-51a" && dest.at(5, 1) == "52B" && dest.at(5, 2) == "-53c" && dest.at(5, 3) == "54D" && dest.at(5, 4) == "-55e" && dest.at(5, 5) == "56F" && dest.at(5, 6) == "-57g" && dest.at(5, 7) == "58H" && dest.at(5, 8) == "-59i" && dest.at(5, 9) == "60J" &&
                dest.at(6, 0) == "-61a" && dest.at(6, 1) == "62B" && dest.at(6, 2) == "-63c" && dest.at(6, 3) == "64D" && dest.at(6, 4) == "-65e" && dest.at(6, 5) == "66F" && dest.at(6, 6) == "-67g" && dest.at(6, 7) == "68H" && dest.at(6, 8) == "-69i" && dest.at(6, 9) == "70J" &&
                dest.at(7, 0) == "-71a" && dest.at(7, 1) == "72B" && dest.at(7, 2) == "-73c" && dest.at(7, 3) == "74D" && dest.at(7, 4) == "-75e" && dest.at(7, 5) == "76F" && dest.at(7, 6) == "-77g" && dest.at(7, 7) == "78H" && dest.at(7, 8) == "-79i" && dest.at(7, 9) == "80J");

        TEST_MOVE_CONSTRUCTOR_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixCopyAssignmentOperator()
{
    {
        const StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix destMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                 destMatrix.at(0, 1) == "Second" &&
                 destMatrix.at(0, 2) == "Third" &&
                 destMatrix.at(1, 0) == "Fourth" &&
                 destMatrix.at(1, 1) == "Fifth" &&
                 destMatrix.at(1, 2) == "Sixth", "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix destMatrix{};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                 destMatrix.at(0, 1) == "Second" &&
                 destMatrix.at(0, 2) == "Third" &&
                 destMatrix.at(1, 0) == "Fourth" &&
                 destMatrix.at(1, 1) == "Fifth" &&
                 destMatrix.at(1, 2) == "Sixth", "Copy assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }

    {
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }

    {
        const StringMatrix srcMatrix{3, 4, "Seventh"};
        StringMatrix destMatrix{2, 3, "Eighth"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 3, 4, 3, 5);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "Seventh", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{4, 3, "Ninth"};
        StringMatrix destMatrix{2, 3, "Eighth"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 4, 3, 5, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "Ninth", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{4, 3, "Ninth"};
        StringMatrix destMatrix{4, 2, "Eighth"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 4, 3, 5, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "Ninth", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{20, 20, "Eleventh"};
        StringMatrix destMatrix{2, 3, "Eighth"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 20, 20, 25, 25);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "Eleventh", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{22, 22, "Twelfth"};
        StringMatrix destMatrix{2, 3, "Eighth"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 22, 22, 27, 27);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "Twelfth", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        StringMatrix matrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};

        matrix = matrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

        QVERIFY2(matrix.at(0, 0) == "First" &&
                 matrix.at(0, 1) == "Second" &&
                 matrix.at(0, 2) == "Third" &&
                 matrix.at(1, 0) == "Fourth" &&
                 matrix.at(1, 1) == "Fifth" &&
                 matrix.at(1, 2) == "Sixth", "Same matrix copy assignment failed, the matrix doesn't have the right values!");
    }

    {
        StringMatrix matrix{};

        matrix = matrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 0, 0, 0, 0);
    }

    {
        StringMatrix firstMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix secondMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
        const StringMatrix thirdMatrix{2, 2, {"13th", "14th", "15th", "16th"}};

        firstMatrix = secondMatrix = thirdMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == "13th" &&
                 firstMatrix.at(0, 1) == "14th" &&
                 firstMatrix.at(1, 0) == "15th" &&
                 firstMatrix.at(1, 1) == "16th", "Copy assignment failed, the first matrix doesn't have the right values!");
    }

    // test cases when destination matrix already has the required capacity
    {
        const StringMatrix srcMatrix{3, 5, "/second"};
        StringMatrix destMatrix{3, 5, "seventh"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 3, 5, 3, 6);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "/second", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{9, 3, "/second"};
        StringMatrix destMatrix{4, 2, "seventh"};

        destMatrix.resize(4, 2, 11, 3);
        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 9, 3, 11, 3);
        CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(destMatrix, "/second", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    // additional test
    {
        const StringMatrix srcMatrix{8, 10, { "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                             "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                             "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                             "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                             "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                             "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                             "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                             "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                                     }};

        StringMatrix destMatrix{3, 5, "seventh"};

        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const StringMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  "-1a" && dest.at(0, 1) ==  "2B" && dest.at(0, 2) ==  "-3c" && dest.at(0, 3) ==  "4D" && dest.at(0, 4) ==  "-5e" && dest.at(0, 5) ==  "6F" && dest.at(0, 6) ==  "-7g" && dest.at(0, 7) ==  "8H" && dest.at(0, 8) ==  "-9i" && dest.at(0, 9) == "10J" &&
                dest.at(1, 0) == "-11a" && dest.at(1, 1) == "12B" && dest.at(1, 2) == "-13c" && dest.at(1, 3) == "14D" && dest.at(1, 4) == "-15e" && dest.at(1, 5) == "16F" && dest.at(1, 6) == "-17g" && dest.at(1, 7) == "18H" && dest.at(1, 8) == "-19i" && dest.at(1, 9) == "20J" &&
                dest.at(2, 0) == "-21a" && dest.at(2, 1) == "22B" && dest.at(2, 2) == "-23c" && dest.at(2, 3) == "24D" && dest.at(2, 4) == "-25e" && dest.at(2, 5) == "26F" && dest.at(2, 6) == "-27g" && dest.at(2, 7) == "28H" && dest.at(2, 8) == "-29i" && dest.at(2, 9) == "30J" &&
                dest.at(3, 0) == "-31a" && dest.at(3, 1) == "32B" && dest.at(3, 2) == "-33c" && dest.at(3, 3) == "34D" && dest.at(3, 4) == "-35e" && dest.at(3, 5) == "36F" && dest.at(3, 6) == "-37g" && dest.at(3, 7) == "38H" && dest.at(3, 8) == "-39i" && dest.at(3, 9) == "40J" &&
                dest.at(4, 0) == "-41a" && dest.at(4, 1) == "42B" && dest.at(4, 2) == "-43c" && dest.at(4, 3) == "44D" && dest.at(4, 4) == "-45e" && dest.at(4, 5) == "46F" && dest.at(4, 6) == "-47g" && dest.at(4, 7) == "48H" && dest.at(4, 8) == "-49i" && dest.at(4, 9) == "50J" &&
                dest.at(5, 0) == "-51a" && dest.at(5, 1) == "52B" && dest.at(5, 2) == "-53c" && dest.at(5, 3) == "54D" && dest.at(5, 4) == "-55e" && dest.at(5, 5) == "56F" && dest.at(5, 6) == "-57g" && dest.at(5, 7) == "58H" && dest.at(5, 8) == "-59i" && dest.at(5, 9) == "60J" &&
                dest.at(6, 0) == "-61a" && dest.at(6, 1) == "62B" && dest.at(6, 2) == "-63c" && dest.at(6, 3) == "64D" && dest.at(6, 4) == "-65e" && dest.at(6, 5) == "66F" && dest.at(6, 6) == "-67g" && dest.at(6, 7) == "68H" && dest.at(6, 8) == "-69i" && dest.at(6, 9) == "70J" &&
                dest.at(7, 0) == "-71a" && dest.at(7, 1) == "72B" && dest.at(7, 2) == "-73c" && dest.at(7, 3) == "74D" && dest.at(7, 4) == "-75e" && dest.at(7, 5) == "76F" && dest.at(7, 6) == "-77g" && dest.at(7, 7) == "78H" && dest.at(7, 8) == "-79i" && dest.at(7, 9) == "80J");

    }
}

void ConstructionAndAssignmentTests::testStringMatrixMoveAssignmentOperator()
{
    {
        StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix destMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                 destMatrix.at(0, 1) == "Second" &&
                 destMatrix.at(0, 2) == "Third" &&
                 destMatrix.at(1, 0) == "Fourth" &&
                 destMatrix.at(1, 1) == "Fifth" &&
                 destMatrix.at(1, 2) == "Sixth", "Move assignment failed, the destination matrix doesn't have the right values!");

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        StringMatrix srcMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 2, 3, 2, 3);

        QVERIFY2(destMatrix.at(0, 0) == "First" &&
                 destMatrix.at(0, 1) == "Second" &&
                 destMatrix.at(0, 2) == "Third" &&
                 destMatrix.at(1, 0) == "Fourth" &&
                 destMatrix.at(1, 1) == "Fifth" &&
                 destMatrix.at(1, 2) == "Sixth", "Move assignment failed, the destination matrix doesn't have the right values!");

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        StringMatrix srcMatrix{};
        StringMatrix destMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        StringMatrix srcMatrix{};
        StringMatrix destMatrix{};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }

    {
        StringMatrix firstMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix secondMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
        StringMatrix thirdMatrix{2, 2, {"13th", "14th", "15th", "16th"}};

        firstMatrix = secondMatrix = std::move(thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == "13th" &&
                 firstMatrix.at(0, 1) == "14th" &&
                 firstMatrix.at(1, 0) == "15th" &&
                 firstMatrix.at(1, 1) == "16th", "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }

    {
        StringMatrix firstMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix secondMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
        StringMatrix thirdMatrix{2, 2, {"13th", "14th", "15th", "16th"}};

        firstMatrix = std::move(secondMatrix = thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2);

        QVERIFY2(firstMatrix.at(0, 0) == "13th" &&
                 firstMatrix.at(0, 1) == "14th" &&
                 firstMatrix.at(1, 0) == "15th" &&
                 firstMatrix.at(1, 1) == "16th", "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }

    {
        StringMatrix matrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};

        matrix = std::move(matrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

        QVERIFY2(matrix.at(0, 0) == "First" &&
                 matrix.at(0, 1) == "Second" &&
                 matrix.at(0, 2) == "Third" &&
                 matrix.at(1, 0) == "Fourth" &&
                 matrix.at(1, 1) == "Fifth" &&
                 matrix.at(1, 2) == "Sixth", "Move assignment failed, the destination matrix doesn't have the right values!");
    }

    {
        StringMatrix matrix;

        matrix = std::move(matrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(matrix, 0, 0, 0, 0);
    }

    // additional test
    {
        StringMatrix srcMatrix{8, 10, {  "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                        "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                        "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                        "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                        "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                        "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                        "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                        "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                               }};

        StringMatrix destMatrix{3, 5, "seventh"};

        destMatrix = std::move(srcMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_DEST_MATRIX_SIZE_AND_CAPACITY(destMatrix, 8, 10, 10, 12);

        const StringMatrix& dest{destMatrix};

        QVERIFY(dest.at(0, 0) ==  "-1a" && dest.at(0, 1) ==  "2B" && dest.at(0, 2) ==  "-3c" && dest.at(0, 3) ==  "4D" && dest.at(0, 4) ==  "-5e" && dest.at(0, 5) ==  "6F" && dest.at(0, 6) ==  "-7g" && dest.at(0, 7) ==  "8H" && dest.at(0, 8) ==  "-9i" && dest.at(0, 9) == "10J" &&
                dest.at(1, 0) == "-11a" && dest.at(1, 1) == "12B" && dest.at(1, 2) == "-13c" && dest.at(1, 3) == "14D" && dest.at(1, 4) == "-15e" && dest.at(1, 5) == "16F" && dest.at(1, 6) == "-17g" && dest.at(1, 7) == "18H" && dest.at(1, 8) == "-19i" && dest.at(1, 9) == "20J" &&
                dest.at(2, 0) == "-21a" && dest.at(2, 1) == "22B" && dest.at(2, 2) == "-23c" && dest.at(2, 3) == "24D" && dest.at(2, 4) == "-25e" && dest.at(2, 5) == "26F" && dest.at(2, 6) == "-27g" && dest.at(2, 7) == "28H" && dest.at(2, 8) == "-29i" && dest.at(2, 9) == "30J" &&
                dest.at(3, 0) == "-31a" && dest.at(3, 1) == "32B" && dest.at(3, 2) == "-33c" && dest.at(3, 3) == "34D" && dest.at(3, 4) == "-35e" && dest.at(3, 5) == "36F" && dest.at(3, 6) == "-37g" && dest.at(3, 7) == "38H" && dest.at(3, 8) == "-39i" && dest.at(3, 9) == "40J" &&
                dest.at(4, 0) == "-41a" && dest.at(4, 1) == "42B" && dest.at(4, 2) == "-43c" && dest.at(4, 3) == "44D" && dest.at(4, 4) == "-45e" && dest.at(4, 5) == "46F" && dest.at(4, 6) == "-47g" && dest.at(4, 7) == "48H" && dest.at(4, 8) == "-49i" && dest.at(4, 9) == "50J" &&
                dest.at(5, 0) == "-51a" && dest.at(5, 1) == "52B" && dest.at(5, 2) == "-53c" && dest.at(5, 3) == "54D" && dest.at(5, 4) == "-55e" && dest.at(5, 5) == "56F" && dest.at(5, 6) == "-57g" && dest.at(5, 7) == "58H" && dest.at(5, 8) == "-59i" && dest.at(5, 9) == "60J" &&
                dest.at(6, 0) == "-61a" && dest.at(6, 1) == "62B" && dest.at(6, 2) == "-63c" && dest.at(6, 3) == "64D" && dest.at(6, 4) == "-65e" && dest.at(6, 5) == "66F" && dest.at(6, 6) == "-67g" && dest.at(6, 7) == "68H" && dest.at(6, 8) == "-69i" && dest.at(6, 9) == "70J" &&
                dest.at(7, 0) == "-71a" && dest.at(7, 1) == "72B" && dest.at(7, 2) == "-73c" && dest.at(7, 3) == "74D" && dest.at(7, 4) == "-75e" && dest.at(7, 5) == "76F" && dest.at(7, 6) == "-77g" && dest.at(7, 7) == "78H" && dest.at(7, 8) == "-79i" && dest.at(7, 9) == "80J");

        TEST_MOVE_ASSIGNMENT_CHECK_SRC_MATRIX_SIZE_AND_CAPACITY(srcMatrix);
    }
}

QTEST_APPLESS_MAIN(ConstructionAndAssignmentTests)

#include "tst_constructionandassignmenttests.moc"
