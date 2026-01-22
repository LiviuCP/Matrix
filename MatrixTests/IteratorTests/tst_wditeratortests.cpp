#include <QTest>

#define USE_WD_ITER_INDEX

#include "testutils.h"

Q_DECLARE_METATYPE(IntWDIter)
Q_DECLARE_METATYPE(StringWDIter)

class WDIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
    void testEmptyIterator();

    // test data
    void testIteratorCreation_data();

private:
    IntMatrix m_PrimaryIntMatrix;
    IntMatrix m_SecondaryIntMatrix;
};

void WDIteratorTests::testIteratorCreation()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    QFETCH(matrix_opt_diff_t, expectedIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getIndex() == expectedIndex,
             "The iterator has not been correctly created!");
}

void WDIteratorTests::testEmptyIterator()
{
    IntWDIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() &&
             !emptyIt.getColumnNr().has_value() &&
             !emptyIt.getIndex().has_value(),
             "The iterator has not been correctly created!");
}

/*
WDIterator indexes for 9x8 matrix:

     0  2  5  9 14 20 27 35
     1  4  8 13 19 26 34 43
     3  7 12 18 25 33 42 50
     6 11 17 24 32 41 49 56
    10 16 23 31 40 48 55 61
    15 22 30 39 47 54 60 65
    21 29 38 46 53 59 64 68
    28 37 45 52 58 63 67 70
    36 44 51 57 62 66 69 71
*/
void WDIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_opt_diff_t>("expectedIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_diff_t{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_opt_size_t{9u} << matrix_opt_size_t{8u} << matrix_opt_diff_t{72u};
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_diff_t{0u};
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_diff_t{2u};
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4) << matrix_opt_size_t{5u} << matrix_opt_size_t{4u} << matrix_opt_diff_t{47u};
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6) << matrix_opt_size_t{8u} << matrix_opt_size_t{6u} << matrix_opt_diff_t{69u};
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_opt_size_t{8u} << matrix_opt_size_t{7u} << matrix_opt_diff_t{71u};
    QTest::newRow("8: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_opt_diff_t{};
    QTest::newRow("9: end iterator") << m_SecondaryIntMatrix.wdEnd() << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_opt_diff_t{};
}

QTEST_APPLESS_MAIN(WDIteratorTests)

#include "tst_wditeratortests.moc"
