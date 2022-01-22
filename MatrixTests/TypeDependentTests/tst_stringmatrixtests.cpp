#include <QtTest>

#include "matrix_template_specializations.h"
#include "testutils.h"

Q_DECLARE_METATYPE(StringMatrix)

class StringMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

    // test data
    void testBooleanOperator_data();
    void testMatrixesAreEqual_data();
    void testMatrixesAreNotEqual_data();
};

void StringMatrixTests::testBooleanOperator()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(bool, checkTrue);

    if (checkTrue)
    {
        QVERIFY2(matrix, "The boolean operator does not return the expected value (true)!");
    }
    else
    {
        QVERIFY2(!matrix, "The boolean operator does not return the expected value (false)!");
    }
}

void StringMatrixTests::testMatrixesAreEqual()
{
    QFETCH(StringMatrix, firstMatrix);
    QFETCH(StringMatrix, secondMatrix);
    QFETCH(bool, checkEqualityToItself);

    if (checkEqualityToItself)
    {
        QVERIFY2(firstMatrix == firstMatrix &&
                 !(firstMatrix != firstMatrix), "The matrix should be equal to itself!");
    }
    else
    {
        QVERIFY2(firstMatrix == secondMatrix &&
                 !(firstMatrix != secondMatrix), "The matrixes should be equal!");
    }
}

void StringMatrixTests::testMatrixesAreNotEqual()
{
    QFETCH(StringMatrix, firstMatrix);
    QFETCH(StringMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

void StringMatrixTests::testBooleanOperator_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << StringMatrix{} << false;
    QTest::newRow("check false") << StringMatrix{2, 3, {"", "", "", "", "", ""}} << false;
    QTest::newRow("check true") << StringMatrix{2, 3, {"abcD", "-a bcd", "-0.123", " ", "1aBc-", ".A1b2"}} << true;
    QTest::newRow("check true") << StringMatrix{2, 3, {"", " ", "", "", "", ""}} << true;
    QTest::newRow("check true") << StringMatrix{2, 3, {"", "", "", "", "abc", ""}} << true;
}

void StringMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << false;
    QTest::newRow("equality to itself") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << true;
    QTest::newRow("distinct matrixes equality") << StringMatrix{} << StringMatrix{} << false;
    QTest::newRow("equality to itself") << StringMatrix{} << StringMatrix{} << true;
}

void StringMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<StringMatrix>("firstMatrix");
    QTest::addColumn<StringMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};
    QTest::newRow("different columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{2, 2, {"abc", "abdc", "Abc", "1abc"}};
    QTest::newRow("different rows count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};
    QTest::newRow("different rows/columns count") << StringMatrix{2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}} << StringMatrix{};
}

QTEST_APPLESS_MAIN(StringMatrixTests)

#include "tst_stringmatrixtests.moc"
