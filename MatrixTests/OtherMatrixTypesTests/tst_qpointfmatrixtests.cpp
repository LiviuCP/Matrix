// clang-format off
#include <QTest>
#include <QPointF>

#include "testutils.h"

Q_DECLARE_METATYPE(QPointFMatrix)

class QPointFMatrixTests : public QObject
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

void QPointFMatrixTests::testMatrixesAreEqual()
{
    QFETCH(QPointFMatrix, firstMatrix);
    QFETCH(QPointFMatrix, secondMatrix);
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

void QPointFMatrixTests::testMatrixesAreNotEqual()
{
    QFETCH(QPointFMatrix, firstMatrix);
    QFETCH(QPointFMatrix, secondMatrix);

    QVERIFY2(firstMatrix != secondMatrix &&
            !(firstMatrix == secondMatrix), "The matrixes should not be equal!");
}

void QPointFMatrixTests::testMatrixesAreEqual_data()
{
    QTest::addColumn<QPointFMatrix>("firstMatrix");
    QTest::addColumn<QPointFMatrix>("secondMatrix");
    QTest::addColumn<bool>("checkEqualityToItself");

    QTest::newRow("1: distinct matrixes equality") << QPointFMatrix{2, 3, {QPointF(-2.500, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.810), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.020)}} << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.400, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.20), QPointF(2.455, 1.02)}} << false;
    QTest::newRow("2: equality to itself") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << true;
    QTest::newRow("3: distinct matrixes equality") << QPointFMatrix{} << QPointFMatrix{} << false;
    QTest::newRow("4: equality to itself") << QPointFMatrix{} << QPointFMatrix{} << true;
}

void QPointFMatrixTests::testMatrixesAreNotEqual_data()
{
    QTest::addColumn<QPointFMatrix>("firstMatrix");
    QTest::addColumn<QPointFMatrix>("secondMatrix");

    QTest::newRow("1: same size matrixes") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, 4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}};
    QTest::newRow("2: different columns count") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{2, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2)}};
    QTest::newRow("3: different rows count") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{3, 3, {QPointF(-2.5, 1.2),  QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02), QPointF(4.5, -20.2), QPointF(-100.1, -300.7), QPointF(20.45, 50.22)}};
    QTest::newRow("4: different rows/columns count") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{3, 2, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(-200.4, 10.81), QPointF(2.455, 1.02)}};
    QTest::newRow("5: different rows/columns count") << QPointFMatrix{2, 3, {QPointF(-2.5, 1.2), QPointF(5.1, -4.2), QPointF(-200.4, 10.81), QPointF(5.0, 4.2), QPointF(-1000.1, -200.2), QPointF(2.455, 1.02)}} << QPointFMatrix{};
}

QTEST_APPLESS_MAIN(QPointFMatrixTests)

#include "tst_qpointfmatrixtests.moc"
// clang-format on
