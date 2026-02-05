// clang-format off
#include <QTest>

#include "tst_constructionandassignmenttests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class ConstructionAndAssignmentTests : public QObject
{
    Q_OBJECT

private slots:
    void testIntMatrixDefaultConstructor();
    void testIntMatrixVectorConstructor();
    void testIntMatrixIdenticalElementsConstructor();
    void testIntMatrixDiagonalMatrixConstructor();
    void testIntMatrixCopyConstructor();
    void testIntMatrixMoveConstructor();
    void testIntMatrixCopyAssignmentOperator();
    void testIntMatrixMoveAssignmentOperator();
    void testIntMatrixAdditionalAssignmentOperatorTests();

    void testStringMatrixDefaultConstructor();
    void testStringMatrixVectorConstructor();
    void testStringMatrixIdenticalElementsConstructor();
    void testStringMatrixDiagonalMatrixConstructor();
    void testStringMatrixCopyConstructor();
    void testStringMatrixMoveConstructor();
    void testStringMatrixCopyAssignmentOperator();
    void testStringMatrixMoveAssignmentOperator();
    void testStringMatrixAdditionalAssignmentOperatorTests();

    void testIntMatrixVectorConstructor_data();
    void testIntMatrixIdenticalElementsConstructor_data();
    void testIntMatrixDiagonalMatrixConstructor_data();
    void testIntMatrixCopyConstructor_data();
    void testIntMatrixMoveConstructor_data();
    void testIntMatrixCopyAssignmentOperator_data();
    void testIntMatrixMoveAssignmentOperator_data();

    void testStringMatrixVectorConstructor_data();
    void testStringMatrixIdenticalElementsConstructor_data();
    void testStringMatrixDiagonalMatrixConstructor_data();
    void testStringMatrixCopyConstructor_data();
    void testStringMatrixMoveConstructor_data();
    void testStringMatrixCopyAssignmentOperator_data();
    void testStringMatrixMoveAssignmentOperator_data();


private:
    // test data helper methods
    void _buildIntMatrixMoveCopyConstructorsTestingTable();
    void _buildIntMatrixMoveCopyAssignmentOperatorsTestingTable();
    void _buildStringMatrixMoveCopyConstructorsTestingTable();
    void _buildStringMatrixMoveCopyAssignmentOperatorsTestingTable();
};

void ConstructionAndAssignmentTests::testIntMatrixDefaultConstructor()
{
    IntMatrix matrix{};
    TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix);
}

// actually a copy operation here
void ConstructionAndAssignmentTests::testIntMatrixVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    const std::vector<int> c_InitListRef{initList};

    IntMatrix matrix{rowsCount, columnsCount, std::move(initList)};

    TEST_VECTOR_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(matrix, c_InitListRef, "Matrix elements have not been correctly initialized by the moved vector constructor");

    // check that the content of the vector is actually copied (int cannot be moved as it's a primitive)
    QVERIFY(initList == c_InitListRef);
}

void ConstructionAndAssignmentTests::testIntMatrixIdenticalElementsConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    IntMatrix matrix{{rowsCount, columnsCount}, elementValue};

    TEST_IDENTICAL_ELEMENTS_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(matrix, elementValue, "Matrix elements have not been correctly initialized by the identical elements constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixDiagonalMatrixConstructor()
{
    QFETCH(matrix_size_t, rowsColumnsCount);
    QFETCH(int, nonDiagonalValue);
    QFETCH(int, diagonalValue);
    QFETCH(matrix_size_t, expectedRowColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowColumnCapacityOffset);

    IntMatrix matrix{rowsColumnsCount, std::pair<int, int>{nonDiagonalValue, diagonalValue}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsColumnsCount, rowsColumnsCount, expectedRowColumnCapacity, expectedRowColumnCapacity, expectedRowColumnCapacityOffset, expectedRowColumnCapacityOffset);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(matrix, nonDiagonalValue, diagonalValue, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
}

void ConstructionAndAssignmentTests::testIntMatrixCopyConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    if (!initList.empty())
    {
        IntMatrix srcMatrix{rowsCount, columnsCount, std::move(std::vector{initList})};
        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(destMatrix, initList, "Matrix elements have not been correctly initialized by the copy constructor");
    }
    else
    {
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0, std::nullopt, std::nullopt);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixMoveConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    if (!initList.empty())
    {
        IntMatrix srcMatrix{rowsCount, columnsCount, std::move(std::vector{initList})};
        IntMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(destMatrix, initList, "Matrix elements have not been correctly initialized by the move constructor");

        QVERIFY(srcMatrix.isEmpty());
    }
    else
    {
        const IntMatrix srcMatrix{};
        IntMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0, std::nullopt, std::nullopt);
    }
}

void ConstructionAndAssignmentTests::testIntMatrixCopyAssignmentOperator()
{
    QFETCH(matrix_size_t, srcRowsCount);
    QFETCH(matrix_size_t, srcColumnsCount);
    QFETCH(std::vector<int>, srcInitList);
    QFETCH(matrix_size_t, destRowsCount);
    QFETCH(matrix_size_t, destColumnsCount);
    QFETCH(std::vector<int>, destInitList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(bool, isSelfAssigned);

    TEST_COPY_ASSIGNMENT_OPERATOR(int, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount, destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned);
}

void ConstructionAndAssignmentTests::testIntMatrixMoveAssignmentOperator()
{
    QFETCH(matrix_size_t, srcRowsCount);
    QFETCH(matrix_size_t, srcColumnsCount);
    QFETCH(std::vector<int>, srcInitList);
    QFETCH(matrix_size_t, destRowsCount);
    QFETCH(matrix_size_t, destColumnsCount);
    QFETCH(std::vector<int>, destInitList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(bool, isSelfAssigned);

    TEST_MOVE_ASSIGNMENT_OPERATOR(int, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount, destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned);
}

void ConstructionAndAssignmentTests::testIntMatrixAdditionalAssignmentOperatorTests()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        const IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = thirdMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16, "Copy assignment failed, the first matrix doesn't have the right values!");
    }

    {
        const IntMatrix srcMatrix{{9, 3}, -2};
        IntMatrix destMatrix{{4, 2}, 7};

        destMatrix.reserve(11, 3);
        destMatrix.resize(4, 2);
        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 9, 3, 11, 3, 1, 0);
        CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(destMatrix, -2, "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
        IntMatrix thirdMatrix{2, 2, {13, 14, 15, 16}};

        firstMatrix = secondMatrix = std::move(thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

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

        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

        QVERIFY2(firstMatrix.at(0, 0) == 13 &&
                 firstMatrix.at(0, 1) == 14 &&
                 firstMatrix.at(1, 0) == 15 &&
                 firstMatrix.at(1, 1) == 16, "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }
}

void ConstructionAndAssignmentTests::testStringMatrixDefaultConstructor()
{
    StringMatrix matrix{};
    TEST_DEFAULT_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix);
}

void ConstructionAndAssignmentTests::testStringMatrixVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<std::string>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    const std::vector<std::string> c_InitListRef{initList};

    StringMatrix matrix{rowsCount, columnsCount, std::move(initList)};

    TEST_VECTOR_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(matrix, c_InitListRef, "Matrix elements have not been correctly initialized by the moved vector constructor");

    // check that the content of the vector is actually moved
    QVERIFY(initList != c_InitListRef);
}

void ConstructionAndAssignmentTests::testStringMatrixIdenticalElementsConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::string, elementValue);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    StringMatrix matrix{{rowsCount, columnsCount}, elementValue};

    TEST_IDENTICAL_ELEMENTS_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(matrix, elementValue, "Matrix elements have not been correctly initialized by the identical elements constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixDiagonalMatrixConstructor()
{
    QFETCH(matrix_size_t, rowsColumnsCount);
    QFETCH(std::string, nonDiagonalValue);
    QFETCH(std::string, diagonalValue);
    QFETCH(matrix_size_t, expectedRowColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowColumnCapacityOffset);

    StringMatrix matrix{rowsColumnsCount, std::pair<std::string, std::string>{nonDiagonalValue, diagonalValue}};

    TEST_DIAGONAL_MATRIX_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, rowsColumnsCount, rowsColumnsCount, expectedRowColumnCapacity, expectedRowColumnCapacity, expectedRowColumnCapacityOffset, expectedRowColumnCapacityOffset);
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(matrix, nonDiagonalValue, diagonalValue, "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
}

void ConstructionAndAssignmentTests::testStringMatrixCopyConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<std::string>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    if (!initList.empty())
    {
        StringMatrix srcMatrix{rowsCount, columnsCount, std::move(std::vector{initList})};
        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(destMatrix, initList, "Matrix elements have not been correctly initialized by the copy constructor");
    }
    else
    {
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{srcMatrix};

        TEST_COPY_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0, std::nullopt, std::nullopt);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixMoveConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<std::string>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    if (!initList.empty())
    {
        StringMatrix srcMatrix{rowsCount, columnsCount, std::move(std::vector{initList})};
        StringMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, rowsCount, columnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
        CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(destMatrix, initList, "Matrix elements have not been correctly initialized by the move constructor");

        QVERIFY(srcMatrix.isEmpty());
    }
    else
    {
        const StringMatrix srcMatrix{};
        StringMatrix destMatrix{std::move(srcMatrix)};

        TEST_MOVE_CONSTRUCTOR_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 0, 0, 0, 0, std::nullopt, std::nullopt);
    }
}

void ConstructionAndAssignmentTests::testStringMatrixCopyAssignmentOperator()
{
    QFETCH(matrix_size_t, srcRowsCount);
    QFETCH(matrix_size_t, srcColumnsCount);
    QFETCH(std::vector<std::string>, srcInitList);
    QFETCH(matrix_size_t, destRowsCount);
    QFETCH(matrix_size_t, destColumnsCount);
    QFETCH(std::vector<std::string>, destInitList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(bool, isSelfAssigned);

    TEST_COPY_ASSIGNMENT_OPERATOR(std::string, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount, destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned);
}

void ConstructionAndAssignmentTests::testStringMatrixMoveAssignmentOperator()
{
    QFETCH(matrix_size_t, srcRowsCount);
    QFETCH(matrix_size_t, srcColumnsCount);
    QFETCH(std::vector<std::string>, srcInitList);
    QFETCH(matrix_size_t, destRowsCount);
    QFETCH(matrix_size_t, destColumnsCount);
    QFETCH(std::vector<std::string>, destInitList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(bool, isSelfAssigned);

    TEST_MOVE_ASSIGNMENT_OPERATOR(std::string, srcRowsCount, srcColumnsCount, srcInitList, destRowsCount, destColumnsCount, destInitList, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset, isSelfAssigned);
}

void ConstructionAndAssignmentTests::testStringMatrixAdditionalAssignmentOperatorTests()
{
    {
        StringMatrix firstMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix secondMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
        const StringMatrix thirdMatrix{2, 2, {"13th", "14th", "15th", "16th"}};

        firstMatrix = secondMatrix = thirdMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

        QVERIFY2(firstMatrix.at(0, 0) == "13th" &&
                 firstMatrix.at(0, 1) == "14th" &&
                 firstMatrix.at(1, 0) == "15th" &&
                 firstMatrix.at(1, 1) == "16th", "Copy assignment failed, the first matrix doesn't have the right values!");
    }

    {
        const StringMatrix srcMatrix{{9, 3}, "/second"};
        StringMatrix destMatrix{{4, 2}, "seventh"};

        destMatrix.reserve(11, 3);
        destMatrix.resize(4, 2);
        destMatrix = srcMatrix;

        TEST_COPY_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(destMatrix, 9, 3, 11, 3, 1, 0);
        CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(destMatrix, "/second", "Copy assignment failed, the destination matrix is not identical or doesn't have the right values!");
    }

    {
        StringMatrix firstMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
        StringMatrix secondMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
        StringMatrix thirdMatrix{2, 2, {"13th", "14th", "15th", "16th"}};

        firstMatrix = secondMatrix = std::move(thirdMatrix);

        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

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

        TEST_MOVE_ASSIGNMENT_CHECK_MATRIX_SIZE_AND_CAPACITY(firstMatrix, 2, 2, 2, 2, 0, 0);

        QVERIFY2(firstMatrix.at(0, 0) == "13th" &&
                 firstMatrix.at(0, 1) == "14th" &&
                 firstMatrix.at(1, 0) == "15th" &&
                 firstMatrix.at(1, 1) == "16th", "Copy and/or move assignment failed, the first matrix doesn't have the right values!");
    }
}

void ConstructionAndAssignmentTests::testIntMatrixVectorConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<int>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const std::vector<int> c_LargeVector{ -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
        -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
        -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
        -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
        -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
        -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
        -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
        -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
    };

    QTest::newRow("2: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_LargeVector << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testIntMatrixIdenticalElementsConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{2u} << 4 << matrix_size_t{3u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: large size matrix") << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testIntMatrixDiagonalMatrixConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<matrix_size_t>("expectedRowColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << 2 << 4 << matrix_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("2: large size matrix") << matrix_size_t{9u} << -5 << -4 << matrix_size_t{11u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testIntMatrixCopyConstructor_data()
{
    _buildIntMatrixMoveCopyConstructorsTestingTable();
}

void ConstructionAndAssignmentTests::testIntMatrixMoveConstructor_data()
{
    _buildIntMatrixMoveCopyConstructorsTestingTable();
}

void ConstructionAndAssignmentTests::testIntMatrixCopyAssignmentOperator_data()
{
    _buildIntMatrixMoveCopyAssignmentOperatorsTestingTable();
}

void ConstructionAndAssignmentTests::testIntMatrixMoveAssignmentOperator_data()
{
    _buildIntMatrixMoveCopyAssignmentOperatorsTestingTable();
}

void ConstructionAndAssignmentTests::testStringMatrixVectorConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<std::string>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const std::vector<std::string> c_LargeVector{ "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
        "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
        "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
        "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
        "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
        "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
        "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
        "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
    };

    QTest::newRow("2: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_LargeVector << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testStringMatrixIdenticalElementsConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{2u} << std::string{"Fourth"} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: large size matrix") << matrix_size_t{10u} << matrix_size_t{8u} << std::string{"_Fifth"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testStringMatrixDiagonalMatrixConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsColumnsCount");
    QTest::addColumn<std::string>("nonDiagonalValue");
    QTest::addColumn<std::string>("diagonalValue");
    QTest::addColumn<matrix_size_t>("expectedRowColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << std::string{"Second"} << std::string{"First"} << matrix_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("2: large size matrix") << matrix_size_t{9u} << std::string{"_Fifth"} << std::string{"_Fourth"} << matrix_size_t{11u} << matrix_opt_size_t{1u};
}

void ConstructionAndAssignmentTests::testStringMatrixCopyConstructor_data()
{
    _buildStringMatrixMoveCopyConstructorsTestingTable();
}

void ConstructionAndAssignmentTests::testStringMatrixMoveConstructor_data()
{
    _buildStringMatrixMoveCopyConstructorsTestingTable();
}

void ConstructionAndAssignmentTests::testStringMatrixCopyAssignmentOperator_data()
{
    _buildStringMatrixMoveCopyAssignmentOperatorsTestingTable();
}

void ConstructionAndAssignmentTests::testStringMatrixMoveAssignmentOperator_data()
{
    _buildStringMatrixMoveCopyAssignmentOperatorsTestingTable();
}

void ConstructionAndAssignmentTests::_buildIntMatrixMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<int>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const std::vector<int> c_LargeVector{ -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                         -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                         -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                         -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                         -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                         -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                         -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                         -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                                        };

    QTest::newRow("2: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_LargeVector << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("3: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstructionAndAssignmentTests::_buildIntMatrixMoveCopyAssignmentOperatorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("srcRowsCount");
    QTest::addColumn<matrix_size_t>("srcColumnsCount");
    QTest::addColumn<std::vector<int>>("srcInitList");
    QTest::addColumn<matrix_size_t>("destRowsCount");
    QTest::addColumn<matrix_size_t>("destColumnsCount");
    QTest::addColumn<std::vector<int>>("destInitList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isSelfAssigned");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{3u} << matrix_size_t{2u} << std::vector<int>{7, 8, 9, 10, 11, 12} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("2: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("3: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::vector<int>(12, 7) << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>(6, 8) << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("4: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<int>(12, 9) << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>(6, 8) << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("5: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<int>(12, 9) << matrix_size_t{4u} << matrix_size_t{2u} << std::vector<int>(8, 8) << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("6: small size matrix") << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<int>(15, -2) << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<int>(15, 7) << matrix_size_t{3u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;

    const std::vector<int> c_MediumVector{ -1,  2,  -3,  4,  -5,  6,  -7,  8,  -9, 10,
                                          -11, 12, -13, 14, -15, 16, -17, 18, -19, 20,
                                          -21, 22, -23, 24, -25, 26, -27, 28, -29, 30,
                                          -31, 32, -33, 34, -35, 36, -37, 38, -39, 40,
                                          -41, 42, -43, 44, -45, 46, -47, 48, -49, 50,
                                          -51, 52, -53, 54, -55, 56, -57, 58, -59, 60,
                                          -61, 62, -63, 64, -65, 66, -67, 68, -69, 70,
                                          -71, 72, -73, 74, -75, 76, -77, 78, -79, 80
                                         };

    QTest::newRow("7: medium size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_MediumVector << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<int>(15, 7) << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("8: large size matrix") << matrix_size_t{20u} << matrix_size_t{20u} << std::vector<int>(400, 11) << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>(6, 8) << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << false;
    QTest::newRow("9: large size matrix") << matrix_size_t{22u} << matrix_size_t{22u} << std::vector<int>(484, 12) << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>(6, 8) << matrix_size_t{27u} << matrix_size_t{27u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << false;

    QTest::newRow("10: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{3u} << matrix_size_t{2u} << std::vector<int>{7, 8, 9, 10, 11, 12} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << false;
    QTest::newRow("11: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << false;
    QTest::newRow("12: non-empty self-assigned matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5, 6} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("13: empty self-assigned matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << true;
}

void ConstructionAndAssignmentTests::_buildStringMatrixMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<std::string>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const std::vector<std::string> c_LargeVector{ "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                                 "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                                 "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                                 "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                                 "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                                 "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                                 "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                                 "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                                                };

    QTest::newRow("2: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_LargeVector << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("3: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstructionAndAssignmentTests::_buildStringMatrixMoveCopyAssignmentOperatorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("srcRowsCount");
    QTest::addColumn<matrix_size_t>("srcColumnsCount");
    QTest::addColumn<std::vector<std::string>>("srcInitList");
    QTest::addColumn<matrix_size_t>("destRowsCount");
    QTest::addColumn<matrix_size_t>("destColumnsCount");
    QTest::addColumn<std::vector<std::string>>("destInitList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isSelfAssigned");

    QTest::newRow("1: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{3u} << matrix_size_t{2u} << std::vector<std::string>{"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("2: small size matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("3: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::vector<std::string>(12, "Seventh") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>(6, "Eighth") << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("4: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<std::string>(12, "Ninth") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>(6, "Eighth") << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("5: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<std::string>(12, "Ninth") << matrix_size_t{4u} << matrix_size_t{2u} << std::vector<std::string>(8, "Eighth") << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("6: small size matrix") << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<std::string>(15, "/second") << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<std::string>(15, "Seventh") << matrix_size_t{3u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;

    const std::vector<std::string> c_MediumVector{ "-1a",  "2B",  "-3c",  "4D",  "-5e",  "6F",  "-7g",  "8H",  "-9i", "10J",
                                                  "-11a", "12B", "-13c", "14D", "-15e", "16F", "-17g", "18H", "-19i", "20J",
                                                  "-21a", "22B", "-23c", "24D", "-25e", "26F", "-27g", "28H", "-29i", "30J",
                                                  "-31a", "32B", "-33c", "34D", "-35e", "36F", "-37g", "38H", "-39i", "40J",
                                                  "-41a", "42B", "-43c", "44D", "-45e", "46F", "-47g", "48H", "-49i", "50J",
                                                  "-51a", "52B", "-53c", "54D", "-55e", "56F", "-57g", "58H", "-59i", "60J",
                                                  "-61a", "62B", "-63c", "64D", "-65e", "66F", "-67g", "68H", "-69i", "70J",
                                                  "-71a", "72B", "-73c", "74D", "-75e", "76F", "-77g", "78H", "-79i", "80J"
                                                 };

    QTest::newRow("7: medium size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << c_MediumVector << matrix_size_t{3u} << matrix_size_t{5u} << std::vector<std::string>(15, "Seventh") << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("8: large size matrix") << matrix_size_t{20u} << matrix_size_t{20u} << std::vector<std::string>(400, "Eleventh") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>(6, "Eighth") << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << false;
    QTest::newRow("9: large size matrix") << matrix_size_t{22u} << matrix_size_t{22u} << std::vector<std::string>(484, "Twelfth") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>(6, "Eighth") << matrix_size_t{27u} << matrix_size_t{27u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << false;

    QTest::newRow("10: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{3u} << matrix_size_t{2u} << std::vector<std::string>{"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << false;
    QTest::newRow("11: empty matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << false;
    QTest::newRow("12: non-empty self-assigned matrix") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<std::string>{"First", "Second", "Third", "Fourth", "Fifth", "Sixth"} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("13: empty self-assigned matrix") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<std::string>{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << true;
}

QTEST_APPLESS_MAIN(ConstructionAndAssignmentTests)

#include "tst_constructionandassignmenttests.moc"
// clang-format on
