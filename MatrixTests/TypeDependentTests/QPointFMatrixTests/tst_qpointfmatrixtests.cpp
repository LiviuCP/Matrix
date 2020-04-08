#define ERROR_CHECKING

#include <QtTest>
#include <QPointF>

#include "../../../MatrixLib/matrix.h"
#include "../../../MatrixLib/matrix_template_specializations.h"

using QPointFMatrix = Matrix<QPointF>;

class QPointFMatrixTests : public QObject
{
    Q_OBJECT

public:
    QPointFMatrixTests();
    ~QPointFMatrixTests();

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

};

QPointFMatrixTests::QPointFMatrixTests()
{

}

QPointFMatrixTests::~QPointFMatrixTests()
{

}

void QPointFMatrixTests::testBooleanOperator()
{
    {
        QPointFMatrix matrix{};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        QPointFMatrix matrix{2, 3, {QPointF(0.0, 0.00), QPointF(-0.0, 0.000), QPointF(0.00, 0.0), QPointF(0.0, -0.000), QPointF(0.0000, 0.00), QPointF(-0.0000, 0.00)}};

        QVERIFY2(!matrix, "The boolean operator does not return the correct value");
    }

    {
        QPointFMatrix matrix{2, 3, {QPointF(0.12, 10.00), QPointF(-0.5, 0.123), QPointF(1000.00, 100.1), QPointF(0.4, -0.005), QPointF(2.1234, 0.00), QPointF(-0.0001, 0.05)}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }

    {
        QPointFMatrix matrix{2, 3, {QPointF(0.0, 0.00), QPointF(-0.0, 0.000), QPointF(0.00, 0.0), QPointF(0.3, -0.000), QPointF(0.0000, 0.00), QPointF(-0.0000, 0.00)}};

        QVERIFY2(matrix, "The boolean operator does not return the correct value");
    }
}

void QPointFMatrixTests::testMatrixesAreEqual()
{
    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.500, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.810), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.020)}};
        QPointFMatrix secondMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.400, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.20), QPointF(2.455, 1.02)}};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};

        QVERIFY2(firstMatrix == firstMatrix, "The matrix is not equal to itself");
    }

    {
        QPointFMatrix firstMatrix{};
        QPointFMatrix secondMatrix{};

        QVERIFY2(firstMatrix == secondMatrix && secondMatrix == firstMatrix, "Matrixes are not equal");
    }

    {
        QPointFMatrix matrix{};

        QVERIFY2(matrix == matrix, "The matrix is not equal to itself");
    }
}

void QPointFMatrixTests::testMatrixesAreNotEqual()
{
    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
        QPointFMatrix secondMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, 4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
        QPointFMatrix secondMatrix{2, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2)}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
        QPointFMatrix secondMatrix
                      {
                          3, 3, {
                                    QPointF(-2.5, 1.2),  QPointF(5.1, -4.2),       QPointF(-200.4, 10.81),
                                    QPointF(5.0, 4.2),   QPointF(-1000.1, -200.2), QPointF(2.455, 1.02),
                                    QPointF(4.5, -20.2), QPointF(-100.1, -300.7),  QPointF(20.45, 50.22)
                                }
                      };

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
        QPointFMatrix secondMatrix{3, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(-200.4, 10.81), QPointF(2.455, 1.02)}};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }

    {
        QPointFMatrix firstMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
        QPointFMatrix secondMatrix{};

        QVERIFY2(firstMatrix != secondMatrix && secondMatrix != firstMatrix, "Matrixes are equal");
    }
}

QTEST_APPLESS_MAIN(QPointFMatrixTests)

#include "tst_qpointfmatrixtests.moc"
