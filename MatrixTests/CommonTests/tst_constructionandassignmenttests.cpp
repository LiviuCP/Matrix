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
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

    QVERIFY2(matrix.at(0, 0) == 1 &&
             matrix.at(0, 1) == 2 &&
             matrix.at(0, 2) == 3 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 5 &&
             matrix.at(1, 2) == 6, "Matrix elements have not been correctly initialized by the init list constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixIdenticalMatrixConstructor()
{
    IntMatrix matrix{3, 2, 4};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 3, 2, 3, 2);

    QVERIFY2(matrix.at(0, 0) == 4 &&
             matrix.at(0, 1) == 4 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 4 &&
             matrix.at(2, 0) == 4 &&
             matrix.at(2, 1) == 4, "Matrix elements have not been correctly initialized by the identical matrix constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixDiagonalMatrixConstructor()
{
    IntMatrix matrix{3, std::pair<int, int>{2, 1}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 3, 3, 3, 3);

    QVERIFY2(matrix.at(0, 0) == 1 &&
             matrix.at(0, 1) == 2 &&
             matrix.at(0, 2) == 2 &&
             matrix.at(1, 0) == 2 &&
             matrix.at(1, 1) == 1 &&
             matrix.at(1, 2) == 2 &&
             matrix.at(2, 0) == 2 &&
             matrix.at(2, 1) == 2 &&
             matrix.at(2, 2) == 1, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
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
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixMoveConstructor()
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
}

void ConstructionAndAssignmentTests::testStringMatrixDefaultConstructor()
{
    StringMatrix matrix{};
    TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix);
}

void ConstructionAndAssignmentTests::testStringMatrixInitListConstructor()
{
    StringMatrix matrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};

    TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 2, 3, 2, 3);

    QVERIFY2(matrix.at(0, 0) == "First" &&
             matrix.at(0, 1) == "Second" &&
             matrix.at(0, 2) == "Third" &&
             matrix.at(1, 0) == "Fourth" &&
             matrix.at(1, 1) == "Fifth" &&
             matrix.at(1, 2) == "Sixth", "Matrix elements have not been correctly initialized by the init list constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixIdenticalMatrixConstructor()
{
    StringMatrix matrix{3, 2, "Fourth"};

    TEST_IDENTICAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 3, 2, 3, 2);

    QVERIFY2(matrix.at(0, 0) == "Fourth" &&
             matrix.at(0, 1) == "Fourth" &&
             matrix.at(1, 0) == "Fourth" &&
             matrix.at(1, 1) == "Fourth" &&
             matrix.at(2, 0) == "Fourth" &&
             matrix.at(2, 1) == "Fourth", "Matrix elements have not been correctly initialized by the identical matrix constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixDiagonalMatrixConstructor()
{
    StringMatrix matrix{3, std::pair<std::string, std::string>{"Second", "First"}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, 3, 3, 3, 3);

    QVERIFY2(matrix.at(0, 0) == "First" &&
             matrix.at(0, 1) == "Second" &&
             matrix.at(0, 2) == "Second" &&
             matrix.at(1, 0) == "Second" &&
             matrix.at(1, 1) == "First" &&
             matrix.at(1, 2) == "Second" &&
             matrix.at(2, 0) == "Second" &&
             matrix.at(2, 1) == "Second" &&
             matrix.at(2, 2) == "First", "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
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
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixMoveConstructor()
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
}

QTEST_APPLESS_MAIN(ConstructionAndAssignmentTests)

#include "tst_constructionandassignmenttests.moc"
