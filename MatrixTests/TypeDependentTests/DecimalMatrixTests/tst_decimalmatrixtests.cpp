#include <QtTest>
#include "../../../MatrixLib/matrix.h"

using DecMatrix = Matrix<double>;

class DecimalMatrixTests : public QObject
{
    Q_OBJECT

public:
    DecimalMatrixTests();
    ~DecimalMatrixTests();

private slots:
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();
};

DecimalMatrixTests::DecimalMatrixTests()
{

}

DecimalMatrixTests::~DecimalMatrixTests()
{

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
