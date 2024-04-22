#include <QtTest>

#include "testutils.h"
#include "tst_swappingtests.h"
#include "tst_swappingtests_data.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class SwappingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testSwapIntMatrixes();
    void testIntMatrixSwapRows();
    void testIntMatrixSwapColumns();

    void testSwapStringMatrixes();
    void testStringMatrixSwapRows();
    void testStringMatrixSwapColumns();

    // test data
    void testSwapIntMatrixes_data();
    void testIntMatrixSwapRows_data();
    void testIntMatrixSwapColumns_data();

    void testSwapStringMatrixes_data();
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

void SwappingTests::testIntMatrixSwapRows()
{
    TEST_MATRIX_SWAP_ROWS(int);
}

void SwappingTests::testIntMatrixSwapColumns()
{
    TEST_MATRIX_SWAP_COLUMNS(int);
}

void SwappingTests::testSwapStringMatrixes()
{
    TEST_MATRIXES_SWAP(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void SwappingTests::testStringMatrixSwapRows()
{
    TEST_MATRIX_SWAP_ROWS(std::string);
}

void SwappingTests::testStringMatrixSwapColumns()
{
    TEST_MATRIX_SWAP_COLUMNS(std::string);
}

void SwappingTests::testSwapIntMatrixes_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("1: non-empty matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("2: one empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{};
    QTest::newRow("3: one empty matrix") << IntMatrix{} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("4: non-empty matrixes") << c_IntMatrix1_8x9 << c_IntMatrix1_9x8;
    QTest::newRow("5: non-empty matrixes") << c_IntMatrix1_9x8 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("6: non-empty matrixes") << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}} << c_IntMatrix1_8x9;
    QTest::newRow("7: one empty matrix") << IntMatrix{} << c_IntMatrix1_9x8;
    QTest::newRow("8: one empty matrix") << c_IntMatrix1_8x9 << IntMatrix{};
    QTest::newRow("9: both matrixes empty") << IntMatrix{} << IntMatrix{};
}

void SwappingTests::testIntMatrixSwapRows_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowNr");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: different rows") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}};
    QTest::newRow("2: different rows") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 0 << IntMatrix{4, 3, {7, 8, 9, 4, 5, 6, 1, 2, 3, 10, 11, 12}};
    QTest::newRow("3: same row") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 1 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("4: different rows") << c_IntMatrix1_9x8 << 2 << 7 << c_IntMatrix2_9x8;
    QTest::newRow("5: different rows") << c_IntMatrix1_9x8 << 7 << 2 << c_IntMatrix2_9x8;
    QTest::newRow("6: same row") << c_IntMatrix1_9x8 << 3 << 3 << c_IntMatrix1_9x8;
}

void SwappingTests::testIntMatrixSwapColumns_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("firstColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondColumnNr");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: different columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}};
    QTest::newRow("2: different columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 0 << IntMatrix{3, 4, {3, 2, 1, 4, 7, 6, 5, 8, 11, 10, 9, 12}};
    QTest::newRow("3: same column") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 1 << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("4: different columns") << c_IntMatrix1_8x9 << 2 << 7 << c_IntMatrix2_8x9;
    QTest::newRow("5: different columns") << c_IntMatrix1_8x9 << 7 << 2 << c_IntMatrix2_8x9;
    QTest::newRow("6: same column") << c_IntMatrix1_8x9 << 3 << 3 << c_IntMatrix1_8x9;
}

void SwappingTests::testSwapStringMatrixes_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("1: non-empty matrixes") << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}} << StringMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: one empty matrix") << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}} << StringMatrix{};
    QTest::newRow("3: one empty matrix") << StringMatrix{} << StringMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("4: non-empty matrixes") << c_StringMatrix1_8x9 << c_StringMatrix1_9x8;
    QTest::newRow("5: non-empty matrixes") << c_StringMatrix1_9x8 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("6: non-empty matrixes") << StringMatrix{3, 2, {"Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << c_StringMatrix1_8x9;
    QTest::newRow("7: one empty matrix") << StringMatrix{} << c_StringMatrix1_9x8;
    QTest::newRow("8: one empty matrix") << c_StringMatrix1_8x9 << StringMatrix{};
    QTest::newRow("9: both matrixes empty") << StringMatrix{} << StringMatrix{};
}

void SwappingTests::testStringMatrixSwapRows_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("firstRowNr");
    QTest::addColumn<StringMatrixSizeType>("secondRowNr");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: different rows") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 2 << StringMatrix{4, 3, {"Seventh", "Eighth", "Ninth", "Fourth", "Fifth", "Sixth", "First", "Second", "Third", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: different rows") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 0 << StringMatrix{4, 3, {"Seventh", "Eighth", "Ninth", "Fourth", "Fifth", "Sixth", "First", "Second", "Third", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: same row") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 1 << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("4: different rows") << c_StringMatrix1_9x8 << 2 << 7 << c_StringMatrix2_9x8;
    QTest::newRow("5: different rows") << c_StringMatrix1_9x8 << 7 << 2 << c_StringMatrix2_9x8;
    QTest::newRow("6: same row") << c_StringMatrix1_9x8 << 3 << 3 << c_StringMatrix1_9x8;
}

void SwappingTests::testStringMatrixSwapColumns_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("firstColumnNr");
    QTest::addColumn<StringMatrixSizeType>("secondColumnNr");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: different columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 2 << StringMatrix{3, 4, {"Third", "Second", "First", "Fourth", "Seventh", "Sixth", "Fifth", "Eighth", "Eleventh", "Tenth", "Ninth", "Twelfth"}};
    QTest::newRow("2: different columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 0 << StringMatrix{3, 4, {"Third", "Second", "First", "Fourth", "Seventh", "Sixth", "Fifth", "Eighth", "Eleventh", "Tenth", "Ninth", "Twelfth"}};
    QTest::newRow("3: same column") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 1 << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("4: different columns") << c_StringMatrix1_8x9 << 2 << 7 << c_StringMatrix2_8x9;
    QTest::newRow("5: different columns") << c_StringMatrix1_8x9 << 7 << 2 << c_StringMatrix2_8x9;
    QTest::newRow("6: same column") << c_StringMatrix1_8x9 << 3 << 3 << c_StringMatrix1_8x9;
}

QTEST_APPLESS_MAIN(SwappingTests)

#include "tst_swappingtests.moc"
