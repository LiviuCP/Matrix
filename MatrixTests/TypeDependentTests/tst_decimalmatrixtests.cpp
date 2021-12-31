#include <QtTest>

#include "testutils.h"

class DecimalMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

private:
    DecMatrix mPrimaryDecMatrix;
    DecMatrix mSecondaryDecMatrix;
};

void DecimalMatrixTests::testBooleanOperator()
{
    mPrimaryDecMatrix.clear();
    QVERIFY2(!mPrimaryDecMatrix, "The boolean operator does not return the expected value!");

    mPrimaryDecMatrix = {2, 3, {0.0, 0.00, 0.000, 0.0000, 0.00000, 0.000000}};
    QVERIFY2(!mPrimaryDecMatrix, "The boolean operator does not return the expected value!");

    mPrimaryDecMatrix = {2, 3, {0.33333333, -0.25, 2.6, -3.8, 0.00, -0.1}};
    QVERIFY2(mPrimaryDecMatrix, "The boolean operator does not return the expected value!");

    mPrimaryDecMatrix = {2, 3, {0.0, 0.00, 0.000, 0.0000, -0.25, 0.000000}};
    QVERIFY2(mPrimaryDecMatrix, "The boolean operator does not return the expected value!");
}

void DecimalMatrixTests::testMatrixesAreEqual()
{
    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};

    QVERIFY2(mPrimaryDecMatrix == mSecondaryDecMatrix && !(mPrimaryDecMatrix != mSecondaryDecMatrix), "The matrixes should be equal!");

    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};

    QVERIFY2(mPrimaryDecMatrix == mPrimaryDecMatrix && !(mPrimaryDecMatrix != mPrimaryDecMatrix), "The matrix should be equal to itself");

    mPrimaryDecMatrix.clear();
    mSecondaryDecMatrix.clear();

    QVERIFY2(mPrimaryDecMatrix == mSecondaryDecMatrix && !(mPrimaryDecMatrix != mSecondaryDecMatrix), "The matrixes should be equal!");
    QVERIFY2(mPrimaryDecMatrix == mPrimaryDecMatrix && !(mPrimaryDecMatrix != mPrimaryDecMatrix), "The matrix should be equal to itself");
}

void DecimalMatrixTests::testMatrixesAreNotEqual()
{
    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix = {2, 3, {0.5, 1.25, -0.5, 1.5, 0.8333333333, -0.8333}};

    QVERIFY2(mPrimaryDecMatrix != mSecondaryDecMatrix && !(mPrimaryDecMatrix == mSecondaryDecMatrix), "The matrixes should not be equal!");

    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix = {2, 2, {0.5, 0.75, 1.5, 0.8333333333}};

    QVERIFY2(mPrimaryDecMatrix != mSecondaryDecMatrix && !(mPrimaryDecMatrix == mSecondaryDecMatrix), "The matrixes should not be equal!");

    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix = {3, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333, 0.5, 0.5, -1.25}};

    QVERIFY2(mPrimaryDecMatrix != mSecondaryDecMatrix && !(mPrimaryDecMatrix == mSecondaryDecMatrix), "The matrixes should not be equal!");

    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix = {3, 2, {0.5, 0.75, 1.5, 0.8333333333, -0.5, -0.8333}};

    QVERIFY2(mPrimaryDecMatrix != mSecondaryDecMatrix && !(mPrimaryDecMatrix == mSecondaryDecMatrix), "The matrixes should not be equal!");

    mPrimaryDecMatrix = {2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}};
    mSecondaryDecMatrix.clear();

    QVERIFY2(mPrimaryDecMatrix != mSecondaryDecMatrix && !(mPrimaryDecMatrix == mSecondaryDecMatrix), "The matrixes should not be equal!");
}

QTEST_APPLESS_MAIN(DecimalMatrixTests)

#include "tst_decimalmatrixtests.moc"
