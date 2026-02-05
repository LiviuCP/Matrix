// clang-format off
#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(DecMatrix)

class DecimalMatrixTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testMatrixesAreEqual();
    void testMatrixesAreNotEqual();

    // test data
    void testMatrixesAreEqual_data();
    void testMatrixesAreNotEqual_data();
};

void DecimalMatrixTests::testMatrixesAreEqual()
{
    QFETCH(DecMatrix, firstMatrix);
    QFETCH(DecMatrix, secondMatrix);
    QFETCH(bool, checkEqualityToItself);

    if (checkEqualityToItself)
    {
        QVERIFY2(firstMatrix == firstMatrix &&
                 !(firstMatrix != firstMatrix), "The matrix should be equal to itself!");
    }
    else
    {
        QVERIFY2(firstMatrix == secondMatrix &&
                 !(firstMatrix != secondMatrix), "The matrixes should be equal!");
    }
}

void DecimalMatrixTests::testMatrixesAreNotEqual()
{
    QFETCH(DecMatrix, firstMatrix);
    QFETCH(DecMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

void DecimalMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<DecMatrix>("firstMatrix");
    QTest::addColumn<DecMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("1: distinct matrixes equality") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << false;
    QTest::newRow("2: equality to itself") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << true;
    QTest::newRow("3: distinct matrixes equality") << DecMatrix{} << DecMatrix{} << false;
    QTest::newRow("4: equality to itself") << DecMatrix{} << DecMatrix{} << true;
}

void DecimalMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<DecMatrix>("firstMatrix");
    QTest::addColumn<DecMatrix>("secondMatrix");

    QTest::newRow("1: same size matrixes") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 3, {0.5, 1.25, -0.5, 1.5, 0.8333333333, -0.8333}};
    QTest::newRow("2: different columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{2, 2, {0.5, 0.75, 1.5, 0.8333333333}};
    QTest::newRow("3: different rows count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{3, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333, 0.5, 0.5, -1.25}};
    QTest::newRow("4: different rows/columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{3, 2, {0.5, 0.75, 1.5, 0.8333333333, -0.5, -0.8333}};
    QTest::newRow("5: different rows/columns count") << DecMatrix{2, 3, {0.5, 0.75, -0.5, 1.5, 0.8333333333, -0.8333}} << DecMatrix{};
}

QTEST_APPLESS_MAIN(DecimalMatrixTests)

#include "tst_decimalmatrixtests.moc"
// clang-format on
