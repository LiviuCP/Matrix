#include <QtTest>
#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;

class IntMatrixTests : public QObject
{
    Q_OBJECT

public:
    IntMatrixTests();
    ~IntMatrixTests();

private slots:
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

};

IntMatrixTests::IntMatrixTests()
{

}

IntMatrixTests::~IntMatrixTests()
{

}

void IntMatrixTests::testMatrixesAreEqual()
{
    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        IntMatrix matrix{2, 3, {5, 75, -5, 15, 833, -8333}};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }

    {
        IntMatrix firstMatrix{};
        IntMatrix secondMatrix{};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }
}

void IntMatrixTests::testMatrixesAreNotEqual()
{
    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{2, 3, {5, 125, -5, 15, 833, -8333}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{2, 2, {5, 75, 15, 833}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{3, 2, {5, 75, 15, 833, -5, -8333}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        IntMatrix firstMatrix{2, 3, {5, 75, -5, 15, 833, -8333}};
        IntMatrix secondMatrix{};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }
}

QTEST_APPLESS_MAIN(IntMatrixTests)

#include "tst_intmatrixtests.moc"
