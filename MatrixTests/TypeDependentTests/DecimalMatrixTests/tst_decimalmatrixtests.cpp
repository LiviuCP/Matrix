#include <QtTest>

#include "matrix.h"

using DecMatrix = Matrix<double>;

class DecimalMatrixTests : public QObject
{
    Q_OBJECT

public:
    DecimalMatrixTests();
    ~DecimalMatrixTests();

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();
};

DecimalMatrixTests::DecimalMatrixTests()
{

}

DecimalMatrixTests::~DecimalMatrixTests()
{

}

void DecimalMatrixTests::testBooleanOperator()
{
    {
        DecMatrix matrix{};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        DecMatrix matrix{2, 3, {0.0, 0.00, 0.000, 0.0000, 0.00000, 0.000000}};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        DecMatrix matrix{2, 3, {0.33333333, -0.25, 2.6, -3.8, 0.00, -0.1}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        DecMatrix matrix{2, 3, {0.0, 0.00, 0.000, 0.0000, -0.25, 0.000000}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }
}

void DecimalMatrixTests::testMatrixesAreEqual()
{
    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        DecMatrix matrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }

    {
        DecMatrix firstMatrix{};
        DecMatrix secondMatrix{};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        DecMatrix matrix{};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }
}

void DecimalMatrixTests::testMatrixesAreNotEqual()
{
    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{2, 3, {0.5, 1.25, -0.5, 1.5, 0.8333333333, -0.8333}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{2, 2, {0.5, 0.75, 1.5, 0.8333333333}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{3, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333, 0.5, 0.5, -1.25}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{3, 2, {0.5, 0.75, 1.5, 0.8333333333, -0.5, -0.8333}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        DecMatrix firstMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
        DecMatrix secondMatrix{};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }
}

QTEST_APPLESS_MAIN(DecimalMatrixTests)

#include "tst_decimalmatrixtests.moc"
