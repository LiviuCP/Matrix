#include <QtTest>

#include "testutils.h"
#include "tst_otherfunctionalitytests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class OtherFunctionalityTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixesAreEqual();
    void testIntMatrixesAreNotEqual();
    void testIntMatrixFunctionAt();
    void testIntMatrixSquareBracketsOperator();
    void testIntMatrixGetBaseArray();

    void testStringMatrixesAreEqual();
    void testStringMatrixesAreNotEqual();
    void testStringMatrixFunctionAt();
    void testStringMatrixSquareBracketsOperator();
    void testStringMatrixGetBaseArray();

    // test data
    void testIntMatrixesAreEqual_data();
    void testIntMatrixesAreNotEqual_data();

    void testStringMatrixesAreEqual_data();
    void testStringMatrixesAreNotEqual_data();

private:
    IntMatrix mPrimaryIntMatrix;
    StringMatrix mPrimaryStringMatrix;
};

void OtherFunctionalityTests::testIntMatrixesAreEqual()
{
    TEST_MATRIXES_ARE_EQUAL(int);
}

void OtherFunctionalityTests::testIntMatrixesAreNotEqual()
{
    TEST_MATRIXES_ARE_NOT_EQUAL(int);
}

/* This test exercises the write-only and the "const" at() method
   For read-only at() operations of writable matrixes it is considered trivial (getter-like method)
   and is used in many tests for checking that other methods work correctly (see above and below)
*/
void OtherFunctionalityTests::testIntMatrixFunctionAt()
{
    mPrimaryIntMatrix = {2, 3, 5};

    mPrimaryIntMatrix.at(0, 0) = 10;
    mPrimaryIntMatrix.at(0, 1) = 20;
    mPrimaryIntMatrix.at(0, 2) = 30;
    mPrimaryIntMatrix.at(1, 0) = 40;
    mPrimaryIntMatrix.at(1, 1) = 50;
    mPrimaryIntMatrix.at(1, 2) = 60;

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(2, 3, {10, 20, 30, 40, 50, 60}), "The write at() method does not work properly, values are not correctly written!");

    mPrimaryIntMatrix = {10, 10, 2};

    for (IntMatrix::size_type rowColumnNr{0}; rowColumnNr < mPrimaryIntMatrix.getNrOfRows(); ++rowColumnNr)
    {
        mPrimaryIntMatrix.at(rowColumnNr, rowColumnNr) = -5;
    }

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(10, {2, -5}), "The write at() method does not work properly, values are not correctly written!");

    // "const" at() - trivial too but tested here just to ensure it exists (it is required for reading values from const matrixes)
    const IntMatrix firstMatrix{2, 3, {70, 80, 90, 100, 110, 120}};

    QVERIFY2(firstMatrix.at(0, 0) == 70 &&
             firstMatrix.at(0, 1) == 80 &&
             firstMatrix.at(0, 2) == 90 &&
             firstMatrix.at(1, 0) == 100 &&
             firstMatrix.at(1, 1) == 110 &&
             firstMatrix.at(1, 2) == 120, "The const at() method does not work correctly, read values are wrong!");

    const IntMatrix secondMatrix{mPrimaryIntMatrix};
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(secondMatrix, 2, -5, "The const at() method does not work correctly, read values are wrong!");
}

void OtherFunctionalityTests::testIntMatrixSquareBracketsOperator()
{
    mPrimaryIntMatrix = {4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    QVERIFY2(mPrimaryIntMatrix[0] == 1 &&
             mPrimaryIntMatrix[1] == 2 &&
             mPrimaryIntMatrix[2] == 3 &&
             mPrimaryIntMatrix[3] == 4 &&
             mPrimaryIntMatrix[4] == 5 &&
             mPrimaryIntMatrix[5] == 6 &&
             mPrimaryIntMatrix[6] == 7 &&
             mPrimaryIntMatrix[7] == 8 &&
             mPrimaryIntMatrix[8] == 9 &&
             mPrimaryIntMatrix[9] == 10 &&
             mPrimaryIntMatrix[10] == 11 &&
             mPrimaryIntMatrix[11] == 12, "The square brackets operator did not return the right values!");


    mPrimaryIntMatrix = {2, 3, 5};

    mPrimaryIntMatrix[0] = 70;
    mPrimaryIntMatrix[1] = 80;
    mPrimaryIntMatrix[2] = 90;
    mPrimaryIntMatrix[3] = 100;
    mPrimaryIntMatrix[4] = 110;
    mPrimaryIntMatrix[5] = 120;

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(2, 3, {70, 80, 90, 100, 110, 120}), "The square brackets operator did not write the right values!");

    mPrimaryIntMatrix = {10, 10, 2};
    const IntMatrix::size_type nrOfRowsOrColumns{mPrimaryIntMatrix.getNrOfRows()};

    for (IntMatrix::size_type rowColumnNr{0}; rowColumnNr < nrOfRowsOrColumns; ++rowColumnNr)
    {
        mPrimaryIntMatrix[rowColumnNr * nrOfRowsOrColumns + rowColumnNr] = -5;
    }

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(10, {2, -5}), "The square brackets operator did not write the right values!");

    // test the "const" square brackets operator too (similar to "const" at() - just to ensure it has been created)
    const IntMatrix firstMatrix{4, 3, {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}};

    QVERIFY2(firstMatrix[0] == 10 &&
             firstMatrix[1] == 20 &&
             firstMatrix[2] == 30 &&
             firstMatrix[3] == 40 &&
             firstMatrix[4] == 50 &&
             firstMatrix[5] == 60 &&
             firstMatrix[6] == 70 &&
             firstMatrix[7] == 80 &&
             firstMatrix[8] == 90 &&
             firstMatrix[9] == 100 &&
             firstMatrix[10] == 110 &&
             firstMatrix[11] == 120, "The const square brackets operator does not work correctly, read values are wrong!");

    const IntMatrix secondMatrix{mPrimaryIntMatrix};

    QVERIFY2(secondMatrix[0] == -5 &&
             secondMatrix[12] == 2 &&
             secondMatrix[24] == 2 &&
             secondMatrix[33] == -5 &&
             secondMatrix[48] == 2 &&
             secondMatrix[59] == 2 &&
             secondMatrix[66] == -5 &&
             secondMatrix[78] == 2 &&
             secondMatrix[88] == -5 &&
             secondMatrix[95] == 2 &&
             secondMatrix[99] == -5,  "The const square brackets operator does not work correctly, read values are wrong!");
}

void OtherFunctionalityTests::testIntMatrixGetBaseArray()
{
    mPrimaryIntMatrix = {};

    int nrOfElements;
    int* baseArrayPtr{static_cast<int*>(mPrimaryIntMatrix.getBaseArray(nrOfElements))};

    if (baseArrayPtr || nrOfElements != 0)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is not null or the number of elements is different from 0!");
    }

    mPrimaryIntMatrix = {2, 3, {1, 2, 3, 4, 5, 6}};
    baseArrayPtr = static_cast<int*>(mPrimaryIntMatrix.getBaseArray(nrOfElements));

    if (!baseArrayPtr || nrOfElements != 6)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == 1 &&
             baseArrayPtr[1] == 2 &&
             baseArrayPtr[2] == 3 &&
             baseArrayPtr[3] == 4 &&
             baseArrayPtr[4] == 5 &&
             baseArrayPtr[5] == 6, "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryIntMatrix.isEmpty());

    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;

    mPrimaryIntMatrix = {10, {2, -5}};
    baseArrayPtr = static_cast<int*>(mPrimaryIntMatrix.getBaseArray(nrOfElements));

    if (!baseArrayPtr || nrOfElements != 100)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == -5 &&
             baseArrayPtr[12] == 2 &&
             baseArrayPtr[24] == 2 &&
             baseArrayPtr[33] == -5 &&
             baseArrayPtr[48] == 2 &&
             baseArrayPtr[59] == 2 &&
             baseArrayPtr[66] == -5 &&
             baseArrayPtr[78] == 2 &&
             baseArrayPtr[88] == -5 &&
             baseArrayPtr[95] == 2 &&
             baseArrayPtr[99] == -5,  "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryIntMatrix.isEmpty());

    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;
}

void OtherFunctionalityTests::testStringMatrixesAreEqual()
{
    TEST_MATRIXES_ARE_EQUAL(std::string);
}

void OtherFunctionalityTests::testStringMatrixesAreNotEqual()
{
    TEST_MATRIXES_ARE_NOT_EQUAL(std::string);
}

void OtherFunctionalityTests::testStringMatrixFunctionAt()
{
    mPrimaryStringMatrix = {2, 3, "Five"};

    mPrimaryStringMatrix.at(0, 0) = "Ten";
    mPrimaryStringMatrix.at(0, 1) = "Twenty";
    mPrimaryStringMatrix.at(0, 2) = "Thirty";
    mPrimaryStringMatrix.at(1, 0) = "Forty";
    mPrimaryStringMatrix.at(1, 1) = "Fifty";
    mPrimaryStringMatrix.at(1, 2) = "Sixty";

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(2, 3, {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty"}), "The write at() method does not work properly, values are not correctly written!");

    mPrimaryStringMatrix = {10, 10, "Two"};

    for (StringMatrix::size_type rowColumnNr{0}; rowColumnNr < mPrimaryStringMatrix.getNrOfRows(); ++rowColumnNr)
    {
        mPrimaryStringMatrix.at(rowColumnNr, rowColumnNr) = "_Five";
    }

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(10, {"Two", "_Five"}), "The write at() method does not work properly, values are not correctly written!");

    // "const" at() - trivial too but tested here just to ensure it exists (it is required for reading values from const matrixes)
    const StringMatrix firstMatrix{2, 3, {"Seventy", "Eighty", "Ninety", "OneHundred", "OneHundredAndTen", "OneHundredAndTwenty"}};

    QVERIFY2(firstMatrix.at(0, 0) == "Seventy" &&
             firstMatrix.at(0, 1) == "Eighty" &&
             firstMatrix.at(0, 2) == "Ninety" &&
             firstMatrix.at(1, 0) == "OneHundred" &&
             firstMatrix.at(1, 1) == "OneHundredAndTen" &&
             firstMatrix.at(1, 2) == "OneHundredAndTwenty", "The const at() method does not work correctly, read values are wrong!");

    const StringMatrix secondMatrix{mPrimaryStringMatrix};
    CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(secondMatrix, "Two", "_Five", "The const at() method does not work correctly, read values are wrong!")
}

void OtherFunctionalityTests::testStringMatrixSquareBracketsOperator()
{
    mPrimaryStringMatrix = {4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};

    QVERIFY2(mPrimaryStringMatrix[0] == "First" &&
             mPrimaryStringMatrix[1] == "Second" &&
             mPrimaryStringMatrix[2] == "Third" &&
             mPrimaryStringMatrix[3] == "Fourth" &&
             mPrimaryStringMatrix[4] == "Fifth" &&
             mPrimaryStringMatrix[5] == "Sixth" &&
             mPrimaryStringMatrix[6] == "Seventh" &&
             mPrimaryStringMatrix[7] == "Eighth" &&
             mPrimaryStringMatrix[8] == "Ninth" &&
             mPrimaryStringMatrix[9] == "Tenth" &&
             mPrimaryStringMatrix[10] == "Eleventh" &&
             mPrimaryStringMatrix[11] == "Twelfth", "The square brackets operator did not return the right values!");


    mPrimaryStringMatrix = {2, 3, "Five"};

    mPrimaryStringMatrix[0] = "Seventy";
    mPrimaryStringMatrix[1] = "Eighty";
    mPrimaryStringMatrix[2] = "Ninety";
    mPrimaryStringMatrix[3] = "OneHundred";
    mPrimaryStringMatrix[4] = "OneHundredAndTen";
    mPrimaryStringMatrix[5] = "OneHundredAndTwenty";

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(2, 3, {"Seventy", "Eighty", "Ninety", "OneHundred", "OneHundredAndTen", "OneHundredAndTwenty"}), "The square brackets operator did not write the right values!");

    mPrimaryStringMatrix = {10, 10, "Two"};
    const StringMatrix::size_type nrOfRowsOrColumns{mPrimaryStringMatrix.getNrOfRows()};

    for (StringMatrix::size_type rowColumnNr{0}; rowColumnNr < nrOfRowsOrColumns; ++rowColumnNr)
    {
        mPrimaryStringMatrix[rowColumnNr * nrOfRowsOrColumns + rowColumnNr] = "_Five";
    }

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(10, {"Two", "_Five"}), "The square brackets operator did not write the right values!");

    // test the "const" square brackets operator too (similar to "const" at() - just to ensure it has been created)
    const StringMatrix firstMatrix{4, 3, {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety", "OneHundred", "OneHundredAndTen", "OneHundredAndTwenty"}};

    QVERIFY2(firstMatrix[0] == "Ten" &&
             firstMatrix[1] == "Twenty" &&
             firstMatrix[2] == "Thirty" &&
             firstMatrix[3] == "Forty" &&
             firstMatrix[4] == "Fifty" &&
             firstMatrix[5] == "Sixty" &&
             firstMatrix[6] == "Seventy" &&
             firstMatrix[7] == "Eighty" &&
             firstMatrix[8] == "Ninety" &&
             firstMatrix[9] == "OneHundred" &&
             firstMatrix[10] == "OneHundredAndTen" &&
             firstMatrix[11] == "OneHundredAndTwenty", "The const square brackets operator does not work correctly, read values are wrong!");

    const StringMatrix secondMatrix{mPrimaryStringMatrix};

    QVERIFY2(secondMatrix[0] == "_Five" &&
             secondMatrix[12] == "Two" &&
             secondMatrix[24] == "Two" &&
             secondMatrix[33] == "_Five" &&
             secondMatrix[48] == "Two" &&
             secondMatrix[59] == "Two" &&
             secondMatrix[66] == "_Five" &&
             secondMatrix[78] == "Two" &&
             secondMatrix[88] == "_Five" &&
             secondMatrix[95] == "Two" &&
             secondMatrix[99] == "_Five",  "The const square brackets operator does not work correctly, read values are wrong!");
}

void OtherFunctionalityTests::testStringMatrixGetBaseArray()
{
    mPrimaryStringMatrix = {};

    int nrOfElements;
    std::string* baseArrayPtr{static_cast<std::string*>(mPrimaryStringMatrix.getBaseArray(nrOfElements))};

    if (baseArrayPtr || nrOfElements != 0)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is not null or the number of elements is different from 0!");
    }

    mPrimaryStringMatrix = {2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    baseArrayPtr = static_cast<std::string*>(mPrimaryStringMatrix.getBaseArray(nrOfElements));

    if (!baseArrayPtr || nrOfElements != 6)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == "First" &&
             baseArrayPtr[1] == "Second" &&
             baseArrayPtr[2] == "Third" &&
             baseArrayPtr[3] == "Fourth" &&
             baseArrayPtr[4] == "Fifth" &&
             baseArrayPtr[5] == "Sixth", "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryStringMatrix.isEmpty());

    std::destroy_n(baseArrayPtr, nrOfElements);
    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;

    mPrimaryStringMatrix = {10, {"Two", "_Five"}};
    baseArrayPtr = static_cast<std::string*>(mPrimaryStringMatrix.getBaseArray(nrOfElements));

    if (!baseArrayPtr || nrOfElements != 100)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == "_Five" &&
             baseArrayPtr[12] == "Two" &&
             baseArrayPtr[24] == "Two" &&
             baseArrayPtr[33] == "_Five" &&
             baseArrayPtr[48] == "Two" &&
             baseArrayPtr[59] == "Two" &&
             baseArrayPtr[66] == "_Five" &&
             baseArrayPtr[78] == "Two" &&
             baseArrayPtr[88] == "_Five" &&
             baseArrayPtr[95] == "Two" &&
             baseArrayPtr[99] == "_Five",  "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryStringMatrix.isEmpty());

    std::destroy_n(baseArrayPtr, nrOfElements);
    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;
}

void OtherFunctionalityTests::testIntMatrixesAreEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << false;
    QTest::newRow("equality to itself") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{8, 10, -2} << IntMatrix{8, 10, -2} << false;
    QTest::newRow("equality to itself") << IntMatrix{8, 10, -2} << IntMatrix{8, 10, -2} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{10, {-4, 8}} << IntMatrix{10, {-4, 8}} << false;
    QTest::newRow("equality to itself") << IntMatrix{10, {-4, 8}} << IntMatrix{10, {-4, 8}} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{} << IntMatrix{} << false;
    QTest::newRow("equality to itself") << IntMatrix{} << IntMatrix{} << true;
}

void OtherFunctionalityTests::testIntMatrixesAreNotEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};
    QTest::newRow("same size matrixes") << IntMatrix{10, {5, -2}} << IntMatrix{10, {5, 3}};
    QTest::newRow("different columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 2, {5, 75, 15, 833}};
    QTest::newRow("different rows count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{};
}

void OtherFunctionalityTests::testStringMatrixesAreEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << false;
    QTest::newRow("equality to itself") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << true;
    QTest::newRow("distinct matrixes equality") << StringMatrix{8, 10, "_abc"} << StringMatrix{8, 10, "_abc"} << false;
    QTest::newRow("equality to itself") << StringMatrix{8, 10, "_abc"} << StringMatrix{8, 10, "_abc"} << true;
    QTest::newRow("distinct matrixes equality") << StringMatrix(10, {"_abc", "Abc"}) << StringMatrix(10, {"_abc", "Abc"}) << false;
    QTest::newRow("equality to itself") << StringMatrix(10, {"_abc", "Abc"}) << StringMatrix(10, {"_abc", "Abc"}) << true;
    QTest::newRow("distinct matrixes equality") << StringMatrix{} << StringMatrix{} << false;
    QTest::newRow("equality to itself") << StringMatrix{} << StringMatrix{} << true;
}

void OtherFunctionalityTests::testStringMatrixesAreNotEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};
    QTest::newRow("same size matrixes") << StringMatrix{10, {"_abc", "Abc"}} << StringMatrix{10, {"_abc", "abc"}};
    QTest::newRow("different columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 2, {"abc", "abdc", "Abc", "1abc"}};
    QTest::newRow("different rows count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{};
}

QTEST_APPLESS_MAIN(OtherFunctionalityTests)

#include "tst_otherfunctionalitytests.moc"
