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
    void testIntMatrixBooleanOperator();
    void testIntMatrixesAreEqual();
    void testIntMatrixesAreNotEqual();
    void testIntMatrixFunctionAt();
    void testSquareBracketsOperator();
    void testIntMatrixGetBaseArray();

    void testStringMatrixBooleanOperator();
    void testStringMatrixesAreEqual();
    void testStringMatrixesAreNotEqual();
    void testStringMatrixFunctionAt();
    void testStringMatrixSquareBracketsOperator();
    void testStringMatrixGetBaseArray();

    // test data
    void testIntMatrixBooleanOperator_data();
    void testIntMatrixesAreEqual_data();
    void testIntMatrixesAreNotEqual_data();

    void testStringMatrixBooleanOperator_data();
    void testStringMatrixesAreEqual_data();
    void testStringMatrixesAreNotEqual_data();

private:
    IntMatrix mPrimaryIntMatrix;
    StringMatrix mPrimaryStringMatrix;
};

void OtherFunctionalityTests::testIntMatrixBooleanOperator()
{
    TEST_MATRIX_BOOLEAN_OPERATOR(int);
}

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

    // "const" at() - trivial too but tested here just to ensure it exists (it is required for reading values from const matrixes)
    const IntMatrix matrix{2, 3, {70, 80, 90, 100, 110, 120}};

    QVERIFY2(matrix.at(0, 0) == 70 &&
             matrix.at(0, 1) == 80 &&
             matrix.at(0, 2) == 90 &&
             matrix.at(1, 0) == 100 &&
             matrix.at(1, 1) == 110 &&
             matrix.at(1, 2) == 120, "The const at() method does not work correctly, read values are wrong!");
}

void OtherFunctionalityTests::testSquareBracketsOperator()
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

    // test the "const" square brackets operator too (similar to "const" at() - just to ensure it has been created)
    const IntMatrix matrix{4, 3, {10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}};

    QVERIFY2(matrix[0] == 10 &&
             matrix[1] == 20 &&
             matrix[2] == 30 &&
             matrix[3] == 40 &&
             matrix[4] == 50 &&
             matrix[5] == 60 &&
             matrix[6] == 70 &&
             matrix[7] == 80 &&
             matrix[8] == 90 &&
             matrix[9] == 100 &&
             matrix[10] == 110 &&
             matrix[11] == 120, "The const square brackets operator does not work correctly, read values are wrong!");
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

    QVERIFY(mPrimaryIntMatrix == IntMatrix{});

    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;
}

void OtherFunctionalityTests::testStringMatrixBooleanOperator()
{
    TEST_MATRIX_BOOLEAN_OPERATOR(std::string);
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
    mPrimaryStringMatrix = {2, 3, "5"};

    mPrimaryStringMatrix.at(0, 0) = "10";
    mPrimaryStringMatrix.at(0, 1) = "20";
    mPrimaryStringMatrix.at(0, 2) = "30";
    mPrimaryStringMatrix.at(1, 0) = "40";
    mPrimaryStringMatrix.at(1, 1) = "50";
    mPrimaryStringMatrix.at(1, 2) = "60";

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(2, 3, {"10", "20", "30", "40", "50", "60"}), "The write at() method does not work properly, values are not correctly written!");

    // "const" at() - trivial too but tested here just to ensure it exists (it is required for reading values from const matrixes)
    const StringMatrix matrix{2, 3, {"70", "80", "90", "100", "110", "120"}};

    QVERIFY2(matrix.at(0, 0) == "70" &&
             matrix.at(0, 1) == "80" &&
             matrix.at(0, 2) == "90" &&
             matrix.at(1, 0) == "100" &&
             matrix.at(1, 1) == "110" &&
             matrix.at(1, 2) == "120", "The const at() method does not work correctly, read values are wrong!");
}

void OtherFunctionalityTests::testStringMatrixSquareBracketsOperator()
{
    mPrimaryStringMatrix = {4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};

    QVERIFY2(mPrimaryStringMatrix[0] == "1" &&
             mPrimaryStringMatrix[1] == "2" &&
             mPrimaryStringMatrix[2] == "3" &&
             mPrimaryStringMatrix[3] == "4" &&
             mPrimaryStringMatrix[4] == "5" &&
             mPrimaryStringMatrix[5] == "6" &&
             mPrimaryStringMatrix[6] == "7" &&
             mPrimaryStringMatrix[7] == "8" &&
             mPrimaryStringMatrix[8] == "9" &&
             mPrimaryStringMatrix[9] == "10" &&
             mPrimaryStringMatrix[10] == "11" &&
             mPrimaryStringMatrix[11] == "12", "The square brackets operator did not return the right values!");


    mPrimaryStringMatrix = {2, 3, "5"};

    mPrimaryStringMatrix[0] = "70";
    mPrimaryStringMatrix[1] = "80";
    mPrimaryStringMatrix[2] = "90";
    mPrimaryStringMatrix[3] = "100";
    mPrimaryStringMatrix[4] = "110";
    mPrimaryStringMatrix[5] = "120";

    QVERIFY2(mPrimaryStringMatrix == StringMatrix(2, 3, {"70", "80", "90", "100", "110", "120"}), "The square brackets operator did not write the right values!");

    // test the "const" square brackets operator too (similar to "const" at() - just to ensure it has been created)
    const StringMatrix matrix{4, 3, {"10", "20", "30", "40", "50", "60", "70", "80", "90", "100", "110", "120"}};

    QVERIFY2(matrix[0] == "10" &&
             matrix[1] == "20" &&
             matrix[2] == "30" &&
             matrix[3] == "40" &&
             matrix[4] == "50" &&
             matrix[5] == "60" &&
             matrix[6] == "70" &&
             matrix[7] == "80" &&
             matrix[8] == "90" &&
             matrix[9] == "100" &&
             matrix[10] == "110" &&
             matrix[11] == "120", "The const square brackets operator does not work correctly, read values are wrong!");
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

    mPrimaryStringMatrix = {2, 3, {"1", "2", "3", "4", "5", "6"}};

    baseArrayPtr = static_cast<std::string*>(mPrimaryStringMatrix.getBaseArray(nrOfElements));

    if (!baseArrayPtr || nrOfElements != 6)
    {
        QFAIL("Passing resources outside the matrix failed, either the pointer is null or the number of elements is not correct!");
    }

    QVERIFY2(baseArrayPtr[0] == "1" &&
             baseArrayPtr[1] == "2" &&
             baseArrayPtr[2] == "3" &&
             baseArrayPtr[3] == "4" &&
             baseArrayPtr[4] == "5" &&
             baseArrayPtr[5] == "6", "Passing resources outside the matrix failed, the element values are not correct!");

    QVERIFY(mPrimaryStringMatrix == StringMatrix{});

    std::destroy_n(baseArrayPtr, nrOfElements);
    std::free(baseArrayPtr);
    baseArrayPtr = nullptr;
}

void OtherFunctionalityTests::testIntMatrixBooleanOperator_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << IntMatrix{} << false;
    QTest::newRow("check false") << IntMatrix{2, 3, {0, 0, 0, 0, 0, 0}} << false;
    QTest::newRow("check true") << IntMatrix{2, 3, {3, -25, 26, -38, 0, -1}} << true;
    QTest::newRow("check true") << IntMatrix{2, 3, {0, 0, 0, 0, -25, 0}} << true;
}

void OtherFunctionalityTests::testIntMatrixesAreEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << false;
    QTest::newRow("equality to itself") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << true;
    QTest::newRow("distinct matrixes equality") << IntMatrix{} << IntMatrix{} << false;
    QTest::newRow("equality to itself") << IntMatrix{} << IntMatrix{} << true;
}

void OtherFunctionalityTests::testIntMatrixesAreNotEqual_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};
    QTest::newRow("different columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{2, 2, {5, 75, 15, 833}};
    QTest::newRow("different rows count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};
    QTest::newRow("different rows/columns count") << IntMatrix{2, 3, {5, 75, -5, 15, 833, -8333}} << IntMatrix{};
}

void OtherFunctionalityTests::testStringMatrixBooleanOperator_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << StringMatrix{} << false;
    QTest::newRow("check false") << StringMatrix{2, 3, {"", "", "", "", "", ""}} << false;
    QTest::newRow("check true") << StringMatrix{2, 3, {"abcD", "-a bcd", "-0.123", " ", "1aBc-", ".A1b2"}} << true;
    QTest::newRow("check true") << StringMatrix{2, 3, {"", " ", "", "", "", ""}} << true;
    QTest::newRow("check true") << StringMatrix{2, 3, {"", "", "", "", "abc", ""}} << true;
}

void OtherFunctionalityTests::testStringMatrixesAreEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << false;
    QTest::newRow("equality to itself") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << true;
    QTest::newRow("distinct matrixes equality") << StringMatrix{} << StringMatrix{} << false;
    QTest::newRow("equality to itself") << StringMatrix{} << StringMatrix{} << true;
}

void OtherFunctionalityTests::testStringMatrixesAreNotEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};
    QTest::newRow("different columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 2, {"abc", "abdc", "Abc", "1abc"}};
    QTest::newRow("different rows count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{};
}

QTEST_APPLESS_MAIN(OtherFunctionalityTests)

#include "tst_otherfunctionalitytests.moc"
