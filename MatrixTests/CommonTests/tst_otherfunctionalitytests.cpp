// clang-format off
#include <QTest>

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
    void testIntMatrixGetBaseArray();

    void testStringMatrixesAreEqual();
    void testStringMatrixesAreNotEqual();
    void testStringMatrixFunctionAt();
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
    mPrimaryIntMatrix = {{2, 3}, 5};

    mPrimaryIntMatrix.at(0, 0) = 10;
    mPrimaryIntMatrix.at(0, 1) = 20;
    mPrimaryIntMatrix.at(0, 2) = 30;
    mPrimaryIntMatrix.at(1, 0) = 40;
    mPrimaryIntMatrix.at(1, 1) = 50;
    mPrimaryIntMatrix.at(1, 2) = 60;

    QVERIFY2(mPrimaryIntMatrix == IntMatrix(2, 3, {10, 20, 30, 40, 50, 60}), "The write at() method does not work properly, values are not correctly written!");

    mPrimaryIntMatrix = {{10, 10}, 2};

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

void OtherFunctionalityTests::testIntMatrixGetBaseArray()
{
    mPrimaryIntMatrix = {};
    
    matrix_size_t nrOfElements;
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
    mPrimaryStringMatrix = {{2, 3}, "Five"};

    mPrimaryStringMatrix.at(0, 0) = "Ten";
    mPrimaryStringMatrix.at(0, 1) = "Twenty";
    mPrimaryStringMatrix.at(0, 2) = "Thirty";
    mPrimaryStringMatrix.at(1, 0) = "Forty";
    mPrimaryStringMatrix.at(1, 1) = "Fifty";
    mPrimaryStringMatrix.at(1, 2) = "Sixty";

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(2, 3, {"Ten", "Twenty", "Thirty", "Forty", "Fifty", "Sixty"}), "The write at() method does not work properly, values are not correctly written!");

    mPrimaryStringMatrix = {{10, 10}, "Two"};

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

void OtherFunctionalityTests::testStringMatrixGetBaseArray()
{
    mPrimaryStringMatrix = {};

    matrix_size_t nrOfElements;
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

    QTest::newRow("1: distinct matrixes equality") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << false;
    QTest::newRow("2: equality to itself") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << true;
    QTest::newRow("3: distinct matrixes equality") << IntMatrix{{8, 10}, -2} << IntMatrix{{8, 10}, -2} << false;
    QTest::newRow("4: equality to itself") << IntMatrix{{8, 10}, -2} << IntMatrix{{8, 10}, -2} << true;
    QTest::newRow("5: distinct matrixes equality") << IntMatrix{10, {-4, 8}} << IntMatrix{10, {-4, 8}} << false;
    QTest::newRow("6: equality to itself") << IntMatrix{10, {-4, 8}} << IntMatrix{10, {-4, 8}} << true;
    QTest::newRow("7: distinct matrixes equality") << IntMatrix{} << IntMatrix{} << false;
    QTest::newRow("8: equality to itself") << IntMatrix{} << IntMatrix{} << true;
}

void OtherFunctionalityTests::testIntMatrixesAreNotEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("1: same size matrixes") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};
    QTest::newRow("2: same size matrixes") << IntMatrix{10, {5, -2}} << IntMatrix{10, {5, 3}};
    QTest::newRow("3: different columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 2, {5, 75, 15, 833}};
    QTest::newRow("4: different rows count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};
    QTest::newRow("5: different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};
    QTest::newRow("6: different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{};
}

void OtherFunctionalityTests::testStringMatrixesAreEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("1: distinct matrixes equality") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << false;
    QTest::newRow("2: equality to itself") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << true;
    QTest::newRow("3: distinct matrixes equality") << StringMatrix{{8, 10}, "_abc"} << StringMatrix{{8, 10}, "_abc"} << false;
    QTest::newRow("4: equality to itself") << StringMatrix{{8, 10}, "_abc"} << StringMatrix{{8, 10}, "_abc"} << true;
    QTest::newRow("5: distinct matrixes equality") << StringMatrix(10, {"_abc", "Abc"}) << StringMatrix(10, {"_abc", "Abc"}) << false;
    QTest::newRow("6: equality to itself") << StringMatrix(10, {"_abc", "Abc"}) << StringMatrix(10, {"_abc", "Abc"}) << true;
    QTest::newRow("7: distinct matrixes equality") << StringMatrix{} << StringMatrix{} << false;
    QTest::newRow("8: equality to itself") << StringMatrix{} << StringMatrix{} << true;
}

void OtherFunctionalityTests::testStringMatrixesAreNotEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("1: same size matrixes") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};
    QTest::newRow("2: same size matrixes") << StringMatrix{10, {"_abc", "Abc"}} << StringMatrix{10, {"_abc", "abc"}};
    QTest::newRow("3: different columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 2, {"abc", "abdc", "Abc", "1abc"}};
    QTest::newRow("4: different rows count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};
    QTest::newRow("5: different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};
    QTest::newRow("6: different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{};
}

QTEST_APPLESS_MAIN(OtherFunctionalityTests)

#include "tst_otherfunctionalitytests.moc"
// clang-format on
