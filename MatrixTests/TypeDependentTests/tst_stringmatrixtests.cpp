#include <QtTest>

#include "matrix_template_specializations.h"
#include "testutils.h"

class StringMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    void testBooleanOperator();
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

private:
    StringMatrix mPrimaryStringMatrix;
    StringMatrix mSecondaryStringMatrix;
};

void StringMatrixTests::testBooleanOperator()
{
    mPrimaryStringMatrix.clear();
    QVERIFY2(!mPrimaryStringMatrix, "The boolean operator does not return the expected value!");

    mPrimaryStringMatrix = {2, 3, {"", "", "", "", "", ""}};
    QVERIFY2(!mPrimaryStringMatrix, "The boolean operator does not return the expected value!");

    mPrimaryStringMatrix = {2, 3, {"abcD", "-a bcd", "-0.123", " ", "1aBc-", ".A1b2"}};
    QVERIFY2(mPrimaryStringMatrix, "The boolean operator does not return the expected value!");

    mPrimaryStringMatrix = {2, 3, {"", " ", "", "", "", ""}};
    QVERIFY2(mPrimaryStringMatrix, "The boolean operator does not return the expected value!");

    mPrimaryStringMatrix = {2, 3, {"", "", "", "", "abc", ""}};
    QVERIFY2(mPrimaryStringMatrix, "The boolean operator does not return the expected value!");
}

void StringMatrixTests::testMatrixesAreEqual()
{
    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};

    QVERIFY2(mPrimaryStringMatrix == mSecondaryStringMatrix && !(mPrimaryStringMatrix != mSecondaryStringMatrix), "The matrixes should be equal!");

    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};

    QVERIFY2(mPrimaryStringMatrix == mPrimaryStringMatrix && !(mPrimaryStringMatrix != mPrimaryStringMatrix), "The matrix should be equal to itself!");

    mPrimaryStringMatrix.clear();
    mSecondaryStringMatrix.clear();

    QVERIFY2(mPrimaryStringMatrix == mSecondaryStringMatrix && !(mPrimaryStringMatrix != mSecondaryStringMatrix), "The matrixes should be equal!");
    QVERIFY2(mPrimaryStringMatrix == mPrimaryStringMatrix && !(mPrimaryStringMatrix != mPrimaryStringMatrix), "The matrix should be equal to itself!");
}

void StringMatrixTests::testMatrixesAreNotEqual()
{
    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix = {2, 3, {"abc", "abde", "-abc", "Abc", "1abc", "-0.8333"}};

    QVERIFY2(mPrimaryStringMatrix != mSecondaryStringMatrix && !(mPrimaryStringMatrix == mSecondaryStringMatrix), "The matrixes should not be equal!");

    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix = {2, 2, {"abc", "abdc", "Abc", "1abc"}};

    QVERIFY2(mPrimaryStringMatrix != mSecondaryStringMatrix && !(mPrimaryStringMatrix == mSecondaryStringMatrix), "The matrixes should not be equal!");

    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix = {3, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333", "Abc", "c1D", "-A1bE2"}};

    QVERIFY2(mPrimaryStringMatrix != mSecondaryStringMatrix && !(mPrimaryStringMatrix == mSecondaryStringMatrix), "The matrixes should not be equal!");

    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix = {3, 2, {"abc", "abdc", "Abc", "1abc", "-abc", "-0.8333"}};

    QVERIFY2(mPrimaryStringMatrix != mSecondaryStringMatrix && !(mPrimaryStringMatrix == mSecondaryStringMatrix), "The matrixes should not be equal!");

    mPrimaryStringMatrix = {2, 3, {"abc", "abdc", "-abc", "Abc", "1abc", "-0.8333"}};
    mSecondaryStringMatrix.clear();

    QVERIFY2(mPrimaryStringMatrix != mSecondaryStringMatrix && !(mPrimaryStringMatrix == mSecondaryStringMatrix), "The matrixes should not be equal!");
}

QTEST_APPLESS_MAIN(StringMatrixTests)

#include "tst_stringmatrixtests.moc"
