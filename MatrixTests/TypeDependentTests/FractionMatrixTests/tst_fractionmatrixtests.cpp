#include <QtTest>
#include "../../../MatrixLib/matrix.h"

// uncomment the below #define after the Fraction library has been correctly setup

#define FRACTION_MATRIX_TEST

class FractionMatrixTests : public QObject
{
    Q_OBJECT

public:
    FractionMatrixTests();
    ~FractionMatrixTests();

private slots:
#ifdef FRACTION_MATRIX_TEST
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();
#endif

};



FractionMatrixTests::FractionMatrixTests()
{

}

FractionMatrixTests::~FractionMatrixTests()
{

}

#ifdef FRACTION_MATRIX_TEST

#include "fraction.h"

using FractMatrix = Matrix<Fraction>;

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

#endif

QTEST_APPLESS_MAIN(FractionMatrixTests)

#include "tst_fractionmatrixtests.moc"
