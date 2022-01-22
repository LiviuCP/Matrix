#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(DecMatrix)

class DecimalMatrixTests : public QObject
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

void DecimalMatrixTests::testBooleanOperator()
{
    QFETCH(DecMatrix, matrix);
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

void DecimalMatrixTests::testMatrixesAreEqual()
{
    QFETCH(DecMatrix, firstMatrix);
    QFETCH(DecMatrix, secondMatrix);
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

void DecimalMatrixTests::testMatrixesAreNotEqual()
{
    QFETCH(DecMatrix, firstMatrix);
    QFETCH(DecMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

void DecimalMatrixTests::testBooleanOperator_data()
{
    QTest::addColumn<DecMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << DecMatrix{} << false;
    QTest::newRow("check false") << DecMatrix{2, 3, {0.0, 0.00, 0.000, 0.0000, 0.00000, 0.000000}} << false;
    QTest::newRow("check true") << DecMatrix{2, 3, {0.33333333, -0.25, 2.6, -3.8, 0.00, -0.1}} << true;
    QTest::newRow("check true") << DecMatrix{2, 3, {0.0, 0.00, 0.000, 0.0000, -0.25, 0.000000}} << true;
}

void DecimalMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<DecMatrix>("firstMatrix");
    QTest::addColumn<DecMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << false;
    QTest::newRow("equality to itself") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << true;
    QTest::newRow("distinct matrixes equality") << DecMatrix{} << DecMatrix{} << false;
    QTest::newRow("equality to itself") << DecMatrix{} << DecMatrix{} << true;
}

void DecimalMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<DecMatrix>("firstMatrix");
    QTest::addColumn<DecMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 1.25, -0.5, 1.5, 0.8333333333, -0.8333}};
    QTest::newRow("different columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 2, {0.5, 0.75, 1.5, 0.8333333333}};
    QTest::newRow("different rows count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{3, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333, 0.5, 0.5, -1.25}};
    QTest::newRow("different rows/columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{3, 2, {0.5, 0.75, 1.5, 0.8333333333, -0.5, -0.8333}};
    QTest::newRow("different rows/columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{};

}

QTEST_APPLESS_MAIN(DecimalMatrixTests)

#include "tst_decimalmatrixtests.moc"
