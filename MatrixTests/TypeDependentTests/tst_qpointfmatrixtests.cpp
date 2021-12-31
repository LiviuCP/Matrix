#include <QtTest>
#include <QPointF>

#include "matrix_template_specializations.h"
#include "testutils.h"

class QPointFMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

private:
    QPointFMatrix mPrimaryQPointFMatrix;
    QPointFMatrix mSecondaryQPointFMatrix;
};

void QPointFMatrixTests::testBooleanOperator()
{
    mPrimaryQPointFMatrix.clear();
    QVERIFY2(!mPrimaryQPointFMatrix, "The boolean operator does not return the expected value!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(0.0, 0.00), QPointF(-0.0, 0.000), QPointF(0.00, 0.0), QPointF(0.0, -0.000), QPointF(0.0000, 0.00), QPointF(-0.0000, 0.00)}};
    QVERIFY2(!mPrimaryQPointFMatrix, "The boolean operator does not return the expected value!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(0.12, 10.00), QPointF(-0.5, 0.123), QPointF(1000.00, 100.1), QPointF(0.4, -0.005), QPointF(2.1234, 0.00), QPointF(-0.0001, 0.05)}};
    QVERIFY2(mPrimaryQPointFMatrix, "The boolean operator does not return the expected value!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(0.0, 0.00), QPointF(-0.0, 0.000), QPointF(0.00, 0.0), QPointF(0.3, -0.000), QPointF(0.0000, 0.00), QPointF(-0.0000, 0.00)}};
    QVERIFY2(mPrimaryQPointFMatrix, "The boolean operator does not return the expected value!");
}

void QPointFMatrixTests::testMatrixesAreEqual()
{
    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.500, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.810), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.020)}};
    mSecondaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.400, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.20), QPointF(2.455, 1.02)}};

    QVERIFY2(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix), "The matrixes should be equal!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};

    QVERIFY2(mPrimaryQPointFMatrix == mPrimaryQPointFMatrix && !(mPrimaryQPointFMatrix != mPrimaryQPointFMatrix), "The matrix should be equal to itself!");

    mPrimaryQPointFMatrix.clear();
    mSecondaryQPointFMatrix.clear();

    QVERIFY2(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix), "The matrixes should be equal!");
    QVERIFY2(mPrimaryQPointFMatrix == mPrimaryQPointFMatrix && !(mPrimaryQPointFMatrix != mPrimaryQPointFMatrix), "The matrix should be equal to itself!");
}

void QPointFMatrixTests::testMatrixesAreNotEqual()
{
    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    mSecondaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, 4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};

    QVERIFY2(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix), "The matrixes should not be equal!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    mSecondaryQPointFMatrix = {2, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2)}};

    QVERIFY2(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix), "The matrixes should not be equal!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    mSecondaryQPointFMatrix = {3, 3, {
                                   QPointF(-2.5, 1.2),  QPointF(5.1, -4.2),       QPointF(-200.4, 10.81),
                                   QPointF(5.0, 4.2),   QPointF(-1000.1, -200.2), QPointF(2.455, 1.02),
                                   QPointF(4.5, -20.2), QPointF(-100.1, -300.7),  QPointF(20.45, 50.22)
                               }};

    QVERIFY2(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix), "The matrixes should not be equal!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    mSecondaryQPointFMatrix = {3, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(-200.4, 10.81), QPointF(2.455, 1.02)}};

    QVERIFY2(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix), "The matrixes should not be equal!");

    mPrimaryQPointFMatrix = {2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    mSecondaryQPointFMatrix.clear();

    QVERIFY2(mPrimaryQPointFMatrix != mSecondaryQPointFMatrix && !(mPrimaryQPointFMatrix == mSecondaryQPointFMatrix), "The matrixes should not be equal!");
}

QTEST_APPLESS_MAIN(QPointFMatrixTests)

#include "tst_qpointfmatrixtests.moc"
