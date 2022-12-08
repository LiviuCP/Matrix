#include <QtTest>

#include "testutils.h"
#include "tst_swappingtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class SwappingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testSwapIntMatrixes();
    void testIntMatrixSwapItems();
    void testIntMatrixSwapRows();
    void testIntMatrixSwapColumns();
    void testIntMatrixSwapRowColumn();

    void testSwapStringMatrixes();
    void testStringMatrixSwapItems();
    void testStringMatrixSwapRows();
    void testStringMatrixSwapColumns();
    void testStringMatrixSwapRowColumn();

    // test data
    void testSwapIntMatrixes_data();
    void testIntMatrixSwapItems_data();
    void testIntMatrixSwapRows_data();
    void testIntMatrixSwapColumns_data();

    void testSwapStringMatrixes_data();
    void testStringMatrixSwapItems_data();
    void testStringMatrixSwapRows_data();
    void testStringMatrixSwapColumns_data();

private:
    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
    StringMatrix mPrimaryStringMatrix;
    StringMatrix mSecondaryStringMatrix;
};

void SwappingTests::testSwapIntMatrixes()
{
    TEST_MATRIXES_SWAP(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

void SwappingTests::testIntMatrixSwapItems()
{
    TEST_MATRIX_SWAP_ITEMS(int);
}

void SwappingTests::testIntMatrixSwapRows()
{
    TEST_MATRIX_SWAP_ROWS(int);
}

void SwappingTests::testIntMatrixSwapColumns()
{
    TEST_MATRIX_SWAP_COLUMNS(int);
}

void SwappingTests::testIntMatrixSwapRowColumn()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    mSecondaryIntMatrix = {3, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};

    mPrimaryIntMatrix.swapRowColumn(0, mSecondaryIntMatrix, 3);

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(4, 3, {16, 20, 24, 4, 5, 6, 7, 8, 9, 10, 11, 12}),
             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap!");

    QVERIFY2(mSecondaryIntMatrix == IntMatrix(3, 4, {13, 14, 15, 1, 17, 18, 19, 2, 21, 22, 23, 3}),
             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap!");
}

void SwappingTests::testSwapStringMatrixes()
{
    TEST_MATRIXES_SWAP(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void SwappingTests::testStringMatrixSwapItems()
{
    TEST_MATRIX_SWAP_ITEMS(std::string);
}

void SwappingTests::testStringMatrixSwapRows()
{
    TEST_MATRIX_SWAP_ROWS(std::string);
}

void SwappingTests::testStringMatrixSwapColumns()
{
    TEST_MATRIX_SWAP_COLUMNS(std::string);
}

void SwappingTests::testStringMatrixSwapRowColumn()
{
    mPrimaryStringMatrix = {4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    mSecondaryStringMatrix = {3, 4, {"13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24"}};

    mPrimaryStringMatrix.swapRowColumn(0, mSecondaryStringMatrix, 3);

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(4, 3, {"16", "20", "24", "4", "5", "6", "7", "8", "9", "10", "11", "12"}),
             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap!");

    QVERIFY2(mSecondaryStringMatrix == StringMatrix(3, 4, {"13", "14", "15", "1", "17", "18", "19", "2", "21", "22", "23", "3"}),
             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap!");
}

void SwappingTests::testSwapIntMatrixes_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("non-empty matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("one empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{};
    QTest::newRow("one empty matrix") << IntMatrix{} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("both matrixes empty") << IntMatrix{} << IntMatrix{};
}

void SwappingTests::testIntMatrixSwapItems_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("firstItemColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different items") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 0 << 1 << true << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}} << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}};
    QTest::newRow("same matrix, same item") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 1 << 0 << 1 << true << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 2 << 0 << false << IntMatrix{2, 3, {1, 2, 3, 4, 5, 11}} << IntMatrix{3, 2, {7, 8, 9, 10, 6, 12}};
}

void SwappingTests::testIntMatrixSwapRows_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different rows") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}} << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}};
    QTest::newRow("same matrix, same row") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 1 << true << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false << IntMatrix{2, 3, {16, 17, 18, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3}};
}

void SwappingTests::testIntMatrixSwapColumns_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}} << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}};
    QTest::newRow("same matrix, same column") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 1 << true << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false << IntMatrix{3, 2, {10, 2, 14, 4, 18, 6}} << IntMatrix{3, 4, {7, 8, 9, 1, 11, 12, 13, 3, 15, 16, 17, 5}};
}

void SwappingTests::testSwapStringMatrixes_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("non-empty matrixes") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 2, {"7", "8", "9", "10", "11", "12"}};
    QTest::newRow("one empty matrix") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{};
    QTest::newRow("one empty matrix") << StringMatrix{} << StringMatrix{3, 2, {"7", "8", "9", "10", "11", "12"}};
    QTest::newRow("both matrixes empty") << StringMatrix{} << StringMatrix{};
}

void SwappingTests::testStringMatrixSwapItems_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<StringMatrixSizeType>("firstItemRowNr");
    QTest::addColumn<StringMatrixSizeType>("firstItemColumnNr");
    QTest::addColumn<StringMatrixSizeType>("secondItemRowNr");
    QTest::addColumn<StringMatrixSizeType>("secondItemColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<StringMatrix>("expectedFirstMatrix");
    QTest::addColumn<StringMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different items") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << 1 << 2 << 0 << 1 << true << StringMatrix{2, 3, {"1", "6", "3", "4", "5", "2"}} << StringMatrix{2, 3, {"1", "6", "3", "4", "5", "2"}};
    QTest::newRow("same matrix, same item") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << 0 << 1 << 0 << 1 << true << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("different matrixes") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 2, {"7", "8", "9", "10", "11", "12"}} << 1 << 2 << 2 << 0 << false << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "11"}} << StringMatrix{3, 2, {"7", "8", "9", "10", "6", "12"}};
}

void SwappingTests::testStringMatrixSwapRows_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<StringMatrixSizeType>("firstRowNr");
    QTest::addColumn<StringMatrixSizeType>("secondRowNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<StringMatrix>("expectedFirstMatrix");
    QTest::addColumn<StringMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different rows") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 2 << true << StringMatrix{4, 3, {"7", "8", "9", "4", "5", "6", "1", "2", "3", "10", "11", "12"}} << StringMatrix{4, 3, {"7", "8", "9", "4", "5", "6", "1", "2", "3", "10", "11", "12"}};
    QTest::newRow("same matrix, same row") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 1 << true << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("different matrixes") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{4, 3, {"7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"}} << 0 << 3 << false << StringMatrix{2, 3, {"16", "17", "18", "4", "5", "6"}} << StringMatrix{4, 3, {"7", "8", "9", "10", "11", "12", "13", "14", "15", "1", "2", "3"}};
}

void SwappingTests::testStringMatrixSwapColumns_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<StringMatrixSizeType>("firstColumnNr");
    QTest::addColumn<StringMatrixSizeType>("secondColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<StringMatrix>("expectedFirstMatrix");
    QTest::addColumn<StringMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix, different columns") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 2 << true << StringMatrix{3, 4, {"3", "2", "1", "4", "7", "6", "5", "8", "11", "10", "9", "12"}} << StringMatrix{3, 4, {"3", "2", "1", "4", "7", "6", "5", "8", "11", "10", "9", "12"}};
    QTest::newRow("same matrix, same column") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 1 << true << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("different matrixes") << StringMatrix{3, 2, {"1", "2", "3", "4", "5", "6"}} << StringMatrix{3, 4, {"7", "8", "9", "10", "11", "12", "13", "14", "15", "16", "17", "18"}} << 0 << 3 << false << StringMatrix{3, 2, {"10", "2", "14", "4", "18", "6"}} << StringMatrix{3, 4, {"7", "8", "9", "1", "11", "12", "13", "3", "15", "16", "17", "5"}};
}

QTEST_APPLESS_MAIN(SwappingTests)

#include "tst_swappingtests.moc"
