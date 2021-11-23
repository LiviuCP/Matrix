#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;

class IntMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

private:
    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void IntMatrixTests::testBooleanOperator()
{
    mPrimaryIntMatrix.clear();
    QVERIFY2(!mPrimaryIntMatrix, "The boolean operator does not return the expected value!");

    mPrimaryIntMatrix = {2, 3, {0, 0, 0, 0, 0, 0}};
    QVERIFY2(!mPrimaryIntMatrix, "The boolean operator does not return the expected value!");

    mPrimaryIntMatrix = {2, 3, {3, -25, 26, -38, 0, -1}};
    QVERIFY2(mPrimaryIntMatrix, "The boolean operator does not return the expected value!");

    mPrimaryIntMatrix = {2, 3, {0, 0, 0, 0, -25, 0}};
    QVERIFY2(mPrimaryIntMatrix, "The boolean operator does not return the expected value!");
}

void IntMatrixTests::testMatrixesAreEqual()
{
    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};

    QVERIFY2(mPrimaryIntMatrix == mSecondaryIntMatrix && !(mPrimaryIntMatrix != mSecondaryIntMatrix), "The matrixes should be equal!");

    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};

    QVERIFY2(mPrimaryIntMatrix == mPrimaryIntMatrix && !(mPrimaryIntMatrix != mPrimaryIntMatrix), "The matrix should be equal to itself!");

    mPrimaryIntMatrix.clear();
    mSecondaryIntMatrix.clear();

    QVERIFY2(mPrimaryIntMatrix == mSecondaryIntMatrix && !(mPrimaryIntMatrix != mSecondaryIntMatrix), "The matrixes should be equal!");
    QVERIFY2(mPrimaryIntMatrix == mPrimaryIntMatrix && !(mPrimaryIntMatrix != mPrimaryIntMatrix), "The matrix should be equal to itself!");
}

void IntMatrixTests::testMatrixesAreNotEqual()
{
    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix = {2, 3, {5, 125, -5, 15, 833, -8333}};

    QVERIFY2(mPrimaryIntMatrix != mSecondaryIntMatrix && !(mPrimaryIntMatrix == mSecondaryIntMatrix), "The matrixes should not be equal!");

    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix = {2, 2, {5, 75, 15, 833}};

    QVERIFY2(mPrimaryIntMatrix != mSecondaryIntMatrix && !(mPrimaryIntMatrix == mSecondaryIntMatrix), "The matrixes should not be equal!");

    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix = {3, 3, {5, 75, -5, 15, 833, -8333, 5, 5, -125}};

    QVERIFY2(mPrimaryIntMatrix != mSecondaryIntMatrix && !(mPrimaryIntMatrix == mSecondaryIntMatrix), "The matrixes should not be equal!");

    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix = {3, 2, {5, 75, 15, 833, -5, -8333}};

    QVERIFY2(mPrimaryIntMatrix != mSecondaryIntMatrix && !(mPrimaryIntMatrix == mSecondaryIntMatrix), "The matrixes should not be equal!");

    mPrimaryIntMatrix = {2, 3, {5, 75, -5, 15, 833, -8333}};
    mSecondaryIntMatrix.clear();

    QVERIFY2(mPrimaryIntMatrix != mSecondaryIntMatrix && !(mPrimaryIntMatrix == mSecondaryIntMatrix), "The matrixes should not be equal!");
}

QTEST_APPLESS_MAIN(IntMatrixTests)

#include "tst_intmatrixtests.moc"
