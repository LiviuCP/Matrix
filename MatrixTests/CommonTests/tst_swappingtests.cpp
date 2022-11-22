#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)

class SwappingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testSwapMatrixes();
    void testSwapItems();
    void testSwapRows();
    void testSwapColumns();
    void testSwapRowColumn();

    // test data
    void testSwapMatrixes_data();
    void testSwapItems_data();
    void testSwapRows_data();
    void testSwapColumns_data();

private:
    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void SwappingTests::testSwapMatrixes()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);

    mPrimaryIntMatrix = firstMatrix;
    mSecondaryIntMatrix = secondMatrix;

    std::swap(mPrimaryIntMatrix, mSecondaryIntMatrix);

    if (mPrimaryIntMatrix.getRowCapacity() != secondMatrix.getRowCapacity() || mPrimaryIntMatrix.getColumnCapacity() != secondMatrix.getColumnCapacity())
    {
        QFAIL("Incorrect capacity of the first matrix after swap!");
    }

    if (mSecondaryIntMatrix.getRowCapacity() != firstMatrix.getRowCapacity() || mSecondaryIntMatrix.getColumnCapacity() != firstMatrix.getColumnCapacity())
    {
        QFAIL("Incorrect capacity of the second matrix after swap!");
    }

    QVERIFY2(mPrimaryIntMatrix == secondMatrix, "First matrix has incorrect element values after swap!");
    QVERIFY2(mSecondaryIntMatrix == firstMatrix, "Second matrix has incorrect element values after swap!");
}

void SwappingTests::testSwapItems()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstItemRowNr);
    QFETCH(IntMatrixSizeType, firstItemColumnNr);
    QFETCH(IntMatrixSizeType, secondItemRowNr);
    QFETCH(IntMatrixSizeType, secondItemColumnNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, firstMatrix, secondItemRowNr, secondItemColumnNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, secondMatrix, secondItemRowNr, secondItemColumnNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Items are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Items are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void SwappingTests::testSwapRows()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstRowNr);
    QFETCH(IntMatrixSizeType, secondRowNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapRows(firstRowNr, firstMatrix, secondRowNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapRows(firstRowNr, secondMatrix, secondRowNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Rows are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Rows are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void SwappingTests::testSwapColumns()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstColumnNr);
    QFETCH(IntMatrixSizeType, secondColumnNr);
    QFETCH(bool, isSwapWithinMatrix);
    QFETCH(IntMatrix, expectedFirstMatrix);
    QFETCH(IntMatrix, expectedSecondMatrix);

    if (isSwapWithinMatrix)
    {
        firstMatrix.swapColumns(firstColumnNr, firstMatrix, secondColumnNr);
        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped within same matrix!");
    }
    else
    {
        firstMatrix.swapColumns(firstColumnNr, secondMatrix, secondColumnNr);

        QVERIFY2(firstMatrix == expectedFirstMatrix, "Columns are incorrectly swapped between matrixes, first matrix does not have the desired value after swap!");
        QVERIFY2(secondMatrix == expectedSecondMatrix, "Columns are incorrectly swapped between matrixes, second matrix does not have the desired value after swap!");
    }
}

void SwappingTests::testSwapRowColumn()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    mSecondaryIntMatrix = {3, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};

    mPrimaryIntMatrix.swapRowColumn(0, mSecondaryIntMatrix, 3);

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(4, 3, {16, 20, 24, 4, 5, 6, 7, 8, 9, 10, 11, 12}),
             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap!");

    QVERIFY2(mSecondaryIntMatrix == IntMatrix(3, 4, {13, 14, 15, 1, 17, 18, 19, 2, 21, 22, 23, 3}),
             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap!");
}

void SwappingTests::testSwapMatrixes_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("non-empty matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("one empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{};
    QTest::newRow("one empty matrix") << IntMatrix{} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("both matrixes empty") << IntMatrix{} << IntMatrix{};
}

void SwappingTests::testSwapItems_data()
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

    QTest::newRow("same matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 0 << 1 << true << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}} << IntMatrix{2, 3, {1, 6, 3, 4, 5, 2}};
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 2 << 0 << false << IntMatrix{2, 3, {1, 2, 3, 4, 5, 11}} << IntMatrix{3, 2, {7, 8, 9, 10, 6, 12}};
}

void SwappingTests::testSwapRows_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}} << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}};
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false << IntMatrix{2, 3, {16, 17, 18, 4, 5, 6}} << IntMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 1, 2, 3}};
}

void SwappingTests::testSwapColumns_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");
    QTest::addColumn<IntMatrix>("expectedFirstMatrix");
    QTest::addColumn<IntMatrix>("expectedSecondMatrix");

    QTest::newRow("same matrix") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << true << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}} << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}};
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false << IntMatrix{3, 2, {10, 2, 14, 4, 18, 6}} << IntMatrix{3, 4, {7, 8, 9, 1, 11, 12, 13, 3, 15, 16, 17, 5}};
}

QTEST_APPLESS_MAIN(SwappingTests)

#include "tst_swappingtests.moc"
