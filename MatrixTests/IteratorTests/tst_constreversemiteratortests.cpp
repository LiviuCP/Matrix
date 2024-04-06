#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstReverseMIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseMIterator)
Q_DECLARE_METATYPE(IntMatrixReverseMIterator)

class ConstReverseMIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
    void testIteratorCreationFromNonConstIterator();
    void testEmptyIterator();
    void testIteratorsAreEqual();
    void testIteratorEqualToItself();
    void testIteratorsAreNotEqual();
    void testLessThanOperator();
    void testLessThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testAsteriskOperator();
    void testArrowOperator();
    void testSquareBracketsOperator();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrement();

    // test data
    void testIteratorCreation_data();
    void testIteratorCreationFromNonConstIterator_data();
    void testIteratorsAreEqual_data();
    void testIteratorsAreNotEqual_data();
    void testLessThanOperator_data();
    void testLessThanOrEqualToOperator_data();
    void testGreaterThanOperator_data();
    void testGreaterThanOrEqualToOperator_data();
    void testOperatorPlus_data();
    void testOperatorMinus_data();
    void testOperatorPlusEqual_data();
    void testOperatorMinusEqual_data();
    void testDifferenceOperator_data();
    void testSquareBracketsOperator_data();
    void testStdCount_data();
    void testStdFind_data();

private:
    // test data helper methods
    void _buildLessThanOperatorTestingTable();
    void _buildLessThanOrEqualOperatorTestingTable();
    void _buildOperatorPlusTestingTable();

    IntMatrix m_PrimaryIntMatrix;
    IntMatrix m_SecondaryIntMatrix;
    StringMatrix m_StringMatrix;

    IntMatrixConstReverseMIterator m_PrimaryIntIterator;
    IntMatrixConstReverseMIterator m_SecondaryIntIterator;
    StringMatrixConstReverseMIterator m_StringIterator;
};

void ConstReverseMIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstReverseMIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixReverseMIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalIndex);

    IntMatrixConstReverseMIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.getDiagonalNr() == expectedDiagonalNr &&
             constIterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstReverseMIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixConstReverseMIterator emptyIterator;

    QVERIFY2(emptyIterator.getRowNr() == -1 && emptyIterator.getColumnNr() == -1 && emptyIterator.getDiagonalNr() == 0 && emptyIterator.getDiagonalIndex() == -1, "The iterator has not been correctly created");
}

void ConstReverseMIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseMIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 0);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstReverseMIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseMIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseMIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseMIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseMIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstReverseMIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseMIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseMIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseMIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseMIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseMIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseMIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseMIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseMIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseMIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseMIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, firstIterator);
    QFETCH(IntMatrixConstReverseMIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseMIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstReverseMIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "defed", "jkl", "mno"}};
    m_StringIterator = m_StringMatrix.constReverseMBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    // test with column capacity offset
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "defed", "jkl", "mno"}};
    m_StringMatrix.resize(2, 3, 2, 5);
    m_StringIterator = m_StringMatrix.constReverseMBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseMIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstReverseMIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseMIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseMBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 4);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseMIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == 9);
}

void ConstReverseMIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstReverseMIterator, leftIterator);
    QFETCH(IntMatrixConstReverseMIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseMIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstReverseMIterator, leftIterator);
    QFETCH(IntMatrixConstReverseMIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstReverseMIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstReverseMIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  4,  4, -3,  2, 1,
                              7, 5, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constReverseMBegin(1), m_PrimaryIntMatrix.constReverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(3, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constReverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseMIterator(1, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constReverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseMEnd(1), "The std::find algorithm does not return the expected iterator!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ConstReverseMIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-2) << 3 << 1 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(0) << 2 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1) << 1 << 0 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(2, 1) << 3 << 0 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(0, 2) << 2 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1, 0) << 1 << 0 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(-2) << 1 << 3 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(0) << -1 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(1) << -1 << 2 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(2, 1) << 0 << 3 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(0, 2) << -1 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(1, 0) << -1 << 2 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(1, 2) << 1 << 2 << -1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 0) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 0) << 2 << 0 << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 0, true) << 3 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 0, true) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 2, true) << 0 << 2 << 0 << 2;
}

void ConstReverseMIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseMIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(-2) << 3 << 1 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(0) << 2 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(1) << 1 << 0 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(2, 1) << 3 << 0 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(0, 2) << 2 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseMBegin(1, 0) << 1 << 0 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(-2) << 1 << 3 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(0) << -1 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(1) << -1 << 2 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(2, 1) << 0 << 3 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(0, 2) << -1 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseMEnd(1, 0) << -1 << 2 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(1, 2) << 1 << 2 << -1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(0, 0) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(2, 0) << 2 << 0 << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(-1, 0, true) << 3 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(2, 0, true) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseMIterator(0, 2, true) << 0 << 2 << 0 << 2;
}

void ConstReverseMIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseMIterator(1, 0, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << m_PrimaryIntMatrix.constReverseMBegin(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseMBegin(2, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(3, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 0, true);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(2) << m_PrimaryIntMatrix.constReverseMEnd(0, 0);
}

void ConstReverseMIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseMIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseMIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseMIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseMIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseMIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseMIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseMIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseMIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseMIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << m_PrimaryIntMatrix.constReverseMBegin(3, 0) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 2) << m_PrimaryIntMatrix.constReverseMBegin(2, 0) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 0, true) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 0, true) << m_PrimaryIntMatrix.constReverseMEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(1) << m_PrimaryIntMatrix.constReverseMEnd(1, 0) << 0;
}

void ConstReverseMIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(0, 1) << 0 << 4;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(0, 1) << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << -1 << 10;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << 1 << 6;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(0) << -3 << 7;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(0) << -1 << -3;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.constReverseMBegin(0, 1) << 0 << 4;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.constReverseMBegin(0, 1) << 1 << 2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getConstReverseMIterator(2, 1) << -1 << 10;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getConstReverseMIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getConstReverseMIterator(2, 1) << 1 << 6;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constReverseMEnd(0) << -3 << 7;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constReverseMEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constReverseMEnd(0) << -1 << -3;
}

void ConstReverseMIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {1, 2, {-3, 2}};

    m_SecondaryIntMatrix = {6, 7, {
                                7, 6, -5,  4, -3, -1, 1,
                                7, 6, -5,  4,  4,  2, 1,
                                7, 6, -5, -1, -3,  2, 1,
                                7, 6,  5,  4, -3,  2, 1,
                                7, 4, -5,  4, -3,  2, 1,
                               -1, 6, -5,  4, -3,  2, 1,
                            }};

    QTest::addColumn<IntMatrixConstReverseMIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1) << m_PrimaryIntMatrix.constReverseMEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseMBegin(1) << m_SecondaryIntMatrix.constReverseMEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseMIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstReverseMIterator(4, 1) << m_SecondaryIntMatrix.getConstReverseMIterator(1, 4, true) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstReverseMIterator(3, 2) << m_SecondaryIntMatrix.getConstReverseMIterator(1, 4, true) << 4 << 0;
}

void ConstReverseMIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                          }};

    QTest::addColumn<IntMatrixConstReverseMIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstReverseMIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1) << m_PrimaryIntMatrix.constReverseMEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseMIterator(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1) << m_PrimaryIntMatrix.constReverseMEnd(1) << -9 << m_PrimaryIntMatrix.constReverseMEnd(1);
}

void ConstReverseMIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseMBegin(1) << m_PrimaryIntMatrix.getConstReverseMIterator(0, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(0, 1) << m_PrimaryIntMatrix.constReverseMEnd(1);
}

void ConstReverseMIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseMIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << m_PrimaryIntMatrix.getConstReverseMIterator(3, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(3, 0) << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << m_PrimaryIntMatrix.constReverseMEnd(-1);
}

void ConstReverseMIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseMIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstReverseMIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << -1 << m_PrimaryIntMatrix.constReverseMBegin(3, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << 2 << m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << 3 << m_PrimaryIntMatrix.constReverseMEnd(3, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMBegin(-1) << 4 << m_PrimaryIntMatrix.constReverseMEnd(3, 0);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.constReverseMBegin(3, 0);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.constReverseMBegin(3, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getConstReverseMIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.constReverseMEnd(3, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseMIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.constReverseMEnd(3, 0);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseMEnd(-1) << -4 << m_PrimaryIntMatrix.constReverseMBegin(3, 0);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseMEnd(-1) << -3 << m_PrimaryIntMatrix.constReverseMBegin(3, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseMEnd(-1) << -1 << m_PrimaryIntMatrix.getConstReverseMIterator(1, 2);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseMEnd(-1) << 1 << m_PrimaryIntMatrix.constReverseMEnd(3, 0);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseMBegin(2, 0) << -2 << m_SecondaryIntMatrix.constReverseMBegin(2, 0);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseMBegin(2, 0) << -1 << m_SecondaryIntMatrix.constReverseMBegin(2, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.constReverseMBegin(2, 0) << 2 << m_SecondaryIntMatrix.getConstReverseMIterator(0, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseMBegin(2, 0) << 3 << m_SecondaryIntMatrix.constReverseMEnd(2, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseMBegin(2, 0) << 4 << m_SecondaryIntMatrix.constReverseMEnd(2, 0);
}

QTEST_APPLESS_MAIN(ConstReverseMIteratorTests)

#include "tst_constreversemiteratortests.moc"
