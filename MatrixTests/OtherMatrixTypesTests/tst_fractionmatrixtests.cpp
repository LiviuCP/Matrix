// clang-format off
#define ERROR_CHECKING

#include <QTest>

#include "matrix.h"
#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

Q_DECLARE_METATYPE(FractMatrix)

class FractionMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

    // test data
    void testMatrixesAreEqual_data();
    void testMatrixesAreNotEqual_data();
};

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

void FractionMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<FractMatrix>("firstMatrix");
    QTest::addColumn<FractMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("1: distinct matrixes equality") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"2/4"}, Fraction{"3/4"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}} << false;
    QTest::newRow("2: equality to itself") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << true;
    QTest::newRow("3: distinct matrixes equality") << FractMatrix{} << FractMatrix{} << false;
    QTest::newRow("4: equality to itself") << FractMatrix{} << FractMatrix{} << true;
}

void FractionMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<FractMatrix>("firstMatrix");
    QTest::addColumn<FractMatrix>("secondMatrix");

    QTest::newRow("1: same size matrixes") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 3, {Fraction{"2/4"}, Fraction{"10/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}};
    QTest::newRow("2: different columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{2, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}}};
    QTest::newRow("3: different rows count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{3, 3, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}, Fraction{"1/2"}, Fraction{"3/6"}, Fraction{"-5/4"}}};
    QTest::newRow("4: different rows/columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{3, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-4/8"}, Fraction{"-5/6"}}};
    QTest::newRow("5: different rows/columns count") << FractMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}} << FractMatrix{};
}

QTEST_APPLESS_MAIN(FractionMatrixTests)

#include "tst_fractionmatrixtests.moc"
// clang-format on
