#define ERROR_CHECKING

#include <QtTest>

#include "matrix.h"

class FractionMatrixTests : public QObject
{
    Q_OBJECT

public:
    FractionMatrixTests();
    ~FractionMatrixTests();

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

};



FractionMatrixTests::FractionMatrixTests()
{

}

FractionMatrixTests::~FractionMatrixTests()
{

}

#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

void FractionMatrixTests::testBooleanOperator()
{
    {
        FractMatrix matrix{};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        FractMatrix matrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-0/4"}, Fraction{"0/-5"}, Fraction{"-0.000"}}};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        FractMatrix matrix{2, 3, {Fraction{"1/3"}, Fraction{"-1/4"}, Fraction{"2.6"}, Fraction{"-3.8"}, Fraction{"0/1"}, Fraction{"-0.1"}}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        FractMatrix matrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-1/4"}, Fraction{"0/-5"}, Fraction{"-0.000"}}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        FractMatrix matrix{2, 3, {Fraction{"0/1"}, Fraction{"0.00"}, Fraction{"0/3"}, Fraction{"-0/4"}, Fraction{"0/-5"}, Fraction{"0.25"}}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }
}

void FractionMatrixTests::testMatrixesAreEqual()
{
    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{2, 3, {Fraction{"2/4"}, Fraction{"3/4"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        FractMatrix matrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }

    {
        FractMatrix firstMatrix{};
        FractMatrix secondMatrix{};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        FractMatrix matrix{};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }
}

void FractionMatrixTests::testMatrixesAreNotEqual()
{
    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{2, 3, {Fraction{"2/4"}, Fraction{"10/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"}}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{2, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{3, 3, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"-4/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-5/6"},
                                        Fraction{"1/2"}, Fraction{"3/6"}, Fraction{"-5/4"}}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{3, 2, {Fraction{"2/4"}, Fraction{"6/8"}, Fraction{"1.5"}, Fraction{"10/12"}, Fraction{"-4/8"}, Fraction{"-5/6"}}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        FractMatrix firstMatrix{2, 3, {Fraction{"1/2"}, Fraction{"3/4"}, Fraction{"-1/2"}, Fraction{"3/2"}, Fraction{"5/6"}, Fraction{"-5/6"}}};
        FractMatrix secondMatrix{};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }
}

QTEST_APPLESS_MAIN(FractionMatrixTests)

#include "tst_fractionmatrixtests.moc"
