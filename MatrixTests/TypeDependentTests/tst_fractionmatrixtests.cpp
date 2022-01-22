#define ERROR_CHECKING

#include <QtTest>

#include "matrix.h"
#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

Q_DECLARE_METATYPE(FractMatrix)

class FractionMatrixTests : public QObject
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

void FractionMatrixTests::testBooleanOperator()
{
    QFETCH(FractMatrix, matrix);
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

void FractionMatrixTests::testMatrixesAreEqual()
{
    QFETCH(FractMatrix, firstMatrix);
    QFETCH(FractMatrix, secondMatrix);
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

void FractionMatrixTests::testMatrixesAreNotEqual()
{
    QFETCH(FractMatrix, firstMatrix);
    QFETCH(FractMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

void FractionMatrixTests::testBooleanOperator_data()
{
    QTest::addColumn<FractMatrix>("matrix");
    QTest::addColumn<bool>("checkTrue");

    QTest::newRow("check false") << FractMatrix{} << false;
    QTest::newRow("check false") << FractMatrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-0/4"}, Fraction{"0/-5"}, Fraction{"-0.000"}}} << false;
    QTest::newRow("check true") << FractMatrix{2, 3, {Fraction{"1/3"}, Fraction{"-1/4"}, Fraction{"2.6"}, Fraction{"-3.8"}, Fraction{"0/1"}, Fraction{"-0.1"}}} << true;
    QTest::newRow("check true") << FractMatrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-1/4"}, Fraction{"0/-5"}, Fraction{"-0.000"}}} << true;
    QTest::newRow("check true") << FractMatrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-0/4"}, Fraction{"0/-5"}, Fraction{"0.25"}}} << true;
}

void FractionMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<FractMatrix>("firstMatrix");
    QTest::addColumn<FractMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("distinct matrixes equality") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"2/4"}, Fraction{"3/4"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}} << false;
    QTest::newRow("equality to itself") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << true;
    QTest::newRow("distinct matrixes equality") << FractMatrix{} << FractMatrix{} << false;
    QTest::newRow("equality to itself") << FractMatrix{} << FractMatrix{} << true;
}

void FractionMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<FractMatrix>("firstMatrix");
    QTest::addColumn<FractMatrix>("secondMatrix");

    QTest::newRow("same size matrixes") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"2/4"}, Fraction{"10/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}};
    QTest::newRow("different columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}}};
    QTest::newRow("different rows count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{3, 3, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}, Fraction{"1/2"}, Fraction{"3/6"}, Fraction{"-5/4"}}};
    QTest::newRow("different rows/columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{3, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-4/8"}, Fraction{"-5/6"}}};
    QTest::newRow("different rows/columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{};
}

QTEST_APPLESS_MAIN(FractionMatrixTests)

#include "tst_fractionmatrixtests.moc"
