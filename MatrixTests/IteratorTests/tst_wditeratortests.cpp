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
    void testIteratorsAreEqual();
    void testIteratorEqualToItself();
    void testIteratorsAreNotEqual();
    void testLessThanOperator();
    void testLessThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testPreIncrementOperator();
    void testPostIncrementOperator();
    void testCombinedIncrementOperators();
    void testPreDecrementOperator();
    void testPostDecrementOperator();
    void testCombinedDecrementOperators();

    // test data
    void testIteratorCreation_data();
    void testIteratorsAreEqual_data();
    void testIteratorEqualToItself_data();
    void testIteratorsAreNotEqual_data();
    void testLessThanOperator_data();
    void testLessThanOrEqualToOperator_data();
    void testGreaterThanOperator_data();
    void testGreaterThanOrEqualToOperator_data();
    void testPreIncrementOperator_data();
    void testPostIncrementOperator_data();
    void testPreDecrementOperator_data();
    void testPostDecrementOperator_data();

private:
    // test data helper methods
    void _buildLessThanOperatorTestingTable();
    void _buildLessThanOrEqualOperatorTestingTable();
    void _buildIncrementOperatorTestingTable();
    void _buildDecrementOperatorTestingTable();

    IntMatrix m_PrimaryIntMatrix;
    IntMatrix m_SecondaryIntMatrix;
    IntWDIter m_PrimaryIntIterator;
    IntWDIter m_SecondaryIntIterator;
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

void WDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void WDIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntWDIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void WDIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void WDIteratorTests::testLessThanOperator()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void WDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void WDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void WDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void WDIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntWDIter, inputIterator);
    QFETCH(IntWDIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntWDIter, inputIterator);
    QFETCH(IntWDIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(5, 4);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(3, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(3, 6),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(5, 4),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(5, 4);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(3, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(5, 4);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntWDIter, inputIterator);
    QFETCH(IntWDIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntWDIter, inputIterator);
    QFETCH(IntWDIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 6);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(5, 4),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(3, 6),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 6);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 6);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(4, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
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

void WDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 0) << m_PrimaryIntMatrix.getWDIterator(0, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4) << m_PrimaryIntMatrix.getWDIterator(5, 4);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6) << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("7: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("8: begin iterator, end iterator") << m_SecondaryIntMatrix.wdBegin() << m_SecondaryIntMatrix.wdEnd();
}

void WDIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    QTest::addColumn<IntWDIter>("iterator");

    QTest::newRow("1: begin iterator")  << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 0);
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4);
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("7: end iterator")  << m_PrimaryIntMatrix.wdEnd();
}

void WDIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void WDIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void WDIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void WDIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void WDIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void WDIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void WDIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void WDIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void WDIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void WDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4) << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdEnd();
}

void WDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(5, 4);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4) << m_PrimaryIntMatrix.getWDIterator(5, 4);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(5, 4) << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6) << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 6) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.wdBegin() << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.wdEnd() << m_SecondaryIntMatrix.wdBegin();
}

void WDIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    QTest::addColumn<IntWDIter>("inputIterator");
    QTest::addColumn<IntWDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(4, 6) << m_PrimaryIntMatrix.getWDIterator(3, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(3, 7) << m_PrimaryIntMatrix.getWDIterator(8, 3);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 3) << m_PrimaryIntMatrix.getWDIterator(7, 4);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(6, 6) << m_PrimaryIntMatrix.getWDIterator(5, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(6, 7) << m_PrimaryIntMatrix.getWDIterator(8, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdEnd();
}

void WDIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    QTest::addColumn<IntWDIter>("inputIterator");
    QTest::addColumn<IntWDIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 6) << m_PrimaryIntMatrix.getWDIterator(6, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(5, 7) << m_PrimaryIntMatrix.getWDIterator(6, 6);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(7, 4) << m_PrimaryIntMatrix.getWDIterator(8, 3);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 3) << m_PrimaryIntMatrix.getWDIterator(3, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(3, 7) << m_PrimaryIntMatrix.getWDIterator(4, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin();
}

QTEST_APPLESS_MAIN(WDIteratorTests)

#include "tst_wditeratortests.moc"
