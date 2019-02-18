#include <QtTest>
#include <QPointF>

#include "../../../MatrixLib/matrix.h"

using QPointFMatrix = Matrix<QPointF>;

class QPointFMatrixTests : public QObject
{
    Q_OBJECT

public:
    QPointFMatrixTests();
    ~QPointFMatrixTests();

private slots:
//    void testBooleanOperator(); // we need to specialize the QPointF Matrix in order to make this operator working (to be done later)
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

};

QPointFMatrixTests::QPointFMatrixTests()
{

}

QPointFMatrixTests::~QPointFMatrixTests()
{

}

//void QPointFMatrixTests::testBooleanOperator()
//{

//}

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
