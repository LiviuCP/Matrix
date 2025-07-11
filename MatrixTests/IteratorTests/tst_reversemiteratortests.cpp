#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntReverseMIter)
Q_DECLARE_METATYPE(StringReverseMIter)

class ReverseMIteratorTests : public QObject
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
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testAsteriskOperator();
    void testArrowOperator();
    void testSquareBracketsOperatorRead();
    void testSquareBracketsOperatorWrite();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrement();
    void testStdSort();

    // test data
    void testIteratorCreation_data();
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
    void testSquareBracketsOperatorRead_data();
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
    
    IntReverseMIter m_PrimaryIntIterator;
    IntReverseMIter m_SecondaryIntIterator;
    StringReverseMIter m_StringIterator;
};

void ReverseMIteratorTests::testIteratorCreation()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    QFETCH(matrix_diff_t, expectedDiagonalNr);
    QFETCH(matrix_opt_size_t, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ReverseMIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();
    
    IntReverseMIter emptyIterator;

    QVERIFY2(!emptyIterator.getRowNr().has_value() && !emptyIterator.getColumnNr().has_value() && emptyIterator.getDiagonalNr() == 0 && !emptyIterator.getDiagonalIndex().has_value(), "The iterator has not been correctly created");
}

void ReverseMIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseMIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 0);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ReverseMIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseMIteratorTests::testLessThanOperator()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseMIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseMIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseMIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseMIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseMIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseMIteratorTests::testOperatorPlus()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseMIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseMIteratorTests::testOperatorMinus()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseMIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseMIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseMIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseMIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseMIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseMIteratorTests::testDifferenceOperator()
{
    QFETCH(IntReverseMIter, firstIterator);
    QFETCH(IntReverseMIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseMIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.reserve(6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.reserve(4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");
}

void ReverseMIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "defed", "jkl", "mno"}};
    m_StringIterator = m_StringMatrix.reverseMBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    m_StringIterator = m_StringMatrix.getReverseMIterator(1, 0);
    m_StringIterator->assign("abcdefghij");

    QVERIFY2(*m_StringMatrix.getReverseMIterator({1, 0}) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");

    // test with row/column capacity offset
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "defed", "jkl", "mno"}};
    m_StringMatrix.reserve(4, 5);
    m_StringIterator = m_StringMatrix.reverseMBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    m_StringIterator = m_StringMatrix.getReverseMIterator(1, 0);
    m_StringIterator->assign("abcdefghij");

    QVERIFY2(*m_StringMatrix.getReverseMIterator({1, 0}) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");
}

void ReverseMIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntReverseMIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseMIteratorTests::testSquareBracketsOperatorWrite()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseMIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.reserve(6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseMIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.reserve(4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseMIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ReverseMIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseMBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 4);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseMIterator({-2, 0});

    QVERIFY(m_PrimaryIntIterator[1] == 9);
}

void ReverseMIteratorTests::testStdCount()
{
    QFETCH(IntReverseMIter, leftIterator);
    QFETCH(IntReverseMIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseMIteratorTests::testStdFind()
{
    QFETCH(IntReverseMIter, leftIterator);
    QFETCH(IntReverseMIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntReverseMIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ReverseMIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  4,  4, -3,  2, 1,
                              7, 5, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.reverseMBegin(1), m_PrimaryIntMatrix.reverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(3, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseMIterator(1, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseMEnd(1), "The std::find algorithm does not return the expected iterator!");
}

void ReverseMIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4, -3,  2, 1,
                              7, 6, -5,  1, -3,  2, 1,
                              7, 6,  0,  4, -3,  2, 1,
                              7, 5, -5,  4, -3,  2, 1,
                              2, 6, -5,  4, -3,  2, 1,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                7,  6, -5,  4, -3,  5, 1,
                                7,  6, -5,  4,  2,  2, 1,
                                7,  6, -5,  1, -3,  2, 1,
                                7,  6,  0,  4, -3,  2, 1,
                                7, -1, -5,  4, -3,  2, 1,
                                -3,  6, -5,  4, -3,  2, 1,
                            }};

    std::sort(m_PrimaryIntMatrix.reverseMBegin(1), m_PrimaryIntMatrix.reverseMEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  5,  2, 1,
                              7, 6, -5, -3, -3,  2, 1,
                              7, 6,  1,  4, -3,  2, 1,
                              7, 0, -5,  4, -3,  2, 1,
                              2, 6, -5,  4, -3,  2, 1,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                7,  6, -5, 4, -3, -1, 1,
                                7,  6, -5, 4,  5,  2, 1,
                                7,  6, -5, 1, -3,  2, 1,
                                7,  6,  0, 4, -3,  2, 1,
                                7, -3, -5, 4, -3,  2, 1,
                                2,  6, -5, 4, -3,  2, 1,
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseMIterator(4, 1), m_PrimaryIntMatrix.getReverseMIterator(1, 4));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              7,  6, -5, 4, -3, -1, 1,
                              7,  6, -5, 4,  5,  2, 1,
                              7,  6, -5, 1, -3,  2, 1,
                              7,  6,  0, 4, -3,  2, 1,
                              7, -3, -5, 4, -3,  2, 1,
                              2,  6, -5, 4, -3,  2, 1,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                7, 6, -5, 4, -3, -1, 1,
                                7, 6, -5, 4,  5,  2, 1,
                                7, 6, -5, 2, -3,  2, 1,
                                7, 6,  1, 4, -3,  2, 1,
                                7, 0, -5, 4, -3,  2, 1,
                               -3, 6, -5, 4, -3,  2, 1,
                            }};

    std::sort(m_PrimaryIntMatrix.reverseMBegin(1), m_PrimaryIntMatrix.getReverseMIterator(1, 4));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5, 4, -3, -1, 1,
                              7, 6, -5, 4,  1,  2, 1,
                              7, 6, -5, 5, -3,  2, 1,
                              7, 6, -3, 4, -3,  2, 1,
                              7, 0, -5, 4, -3,  2, 1,
                              2, 6, -5, 4, -3,  2, 1,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                7,  6, -5, 4, -3, 5, 1,
                                7,  6, -5, 4,  1, 2, 1,
                                7,  6, -5, 0, -3, 2, 1,
                                7,  6, -1, 4, -3, 2, 1,
                                7, -3, -5, 4, -3, 2, 1,
                                2,  6, -5, 4, -3, 2, 1,
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseMIterator(4, 1), m_PrimaryIntMatrix.reverseMEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ReverseMIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_diff_t>("expectedDiagonalNr");
    QTest::addColumn<matrix_opt_size_t>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(-2) << matrix_opt_size_t{3u} << matrix_opt_size_t{1u} << matrix_diff_t{-2} << matrix_opt_size_t{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(0) << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(2, 1) << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(0, 2) << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.reverseMEnd(-2) << matrix_opt_size_t{1u} << matrix_opt_size_t{3u} << matrix_diff_t{-2} << matrix_opt_size_t{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.reverseMEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{3u} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.reverseMEnd(1) << matrix_opt_size_t{} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.reverseMEnd(2, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << matrix_diff_t{-1} << matrix_opt_size_t{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.reverseMEnd(0, 2) << matrix_opt_size_t{} << matrix_opt_size_t{3u} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.reverseMEnd(1, 0) << matrix_opt_size_t{} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(1, 2) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{2u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 0) << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 0}) << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseMIterator({2, 0}) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseMIterator({0, 2}) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{2u};
}

void ReverseMIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("firstIterator");
    QTest::addColumn<IntReverseMIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(1, 0) << m_PrimaryIntMatrix.getReverseMIterator({1, 0});
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << m_PrimaryIntMatrix.reverseMBegin(2, 1);
    QTest::newRow("3: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseMBegin(2, 1) << m_PrimaryIntMatrix.getReverseMIterator(3, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(3, 0) << m_PrimaryIntMatrix.getReverseMIterator({-1, 0});
    QTest::newRow("5: end iterator, end iterator") << m_PrimaryIntMatrix.reverseMEnd(2) << m_PrimaryIntMatrix.reverseMEnd(0, 0);
}

void ReverseMIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseMIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseMIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseMIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseMIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseMIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseMIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseMIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseMIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseMIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("firstIterator");
    QTest::addColumn<IntReverseMIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << m_PrimaryIntMatrix.reverseMBegin(3, 0) << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseMIterator(0, 2) << m_PrimaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{-2};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << m_PrimaryIntMatrix.getReverseMIterator({-1, 0}) << matrix_diff_t{-1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(0, 1) << m_PrimaryIntMatrix.getReverseMIterator({1, 0}) << matrix_diff_t{-1};
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 0}) << m_PrimaryIntMatrix.reverseMEnd(-1) << matrix_diff_t{3};
    QTest::newRow("6: end iterator, end iterator") << m_PrimaryIntMatrix.reverseMEnd(1) << m_PrimaryIntMatrix.reverseMEnd(1, 0) << matrix_diff_t{0};
}

void ReverseMIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(0, 1) << matrix_diff_t{0} << 4;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseMBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{-1} << 10;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{1} << 6;
    QTest::newRow("6: end iterator") << m_PrimaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-3} << 7;
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-1} << -3;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(6, 5);

    QTest::newRow("9: begin iterator") << m_SecondaryIntMatrix.reverseMBegin(0, 1) << matrix_diff_t{0} << 4;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.reverseMBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("11: random iterator") << m_SecondaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{-1} << 10;
    QTest::newRow("12: random iterator") << m_SecondaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("13: random iterator") << m_SecondaryIntMatrix.getReverseMIterator(2, 1) << matrix_diff_t{1} << 6;
    QTest::newRow("14: end iterator") << m_SecondaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-3} << 7;
    QTest::newRow("15: end iterator") << m_SecondaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.reverseMEnd(0) << matrix_diff_t{-1} << -3;
}

void ReverseMIteratorTests::testStdCount_data()
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
    
    QTest::addColumn<IntReverseMIter>("leftIterator");
    QTest::addColumn<IntReverseMIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseMBegin(1) << m_PrimaryIntMatrix.reverseMEnd(1) << -3 << matrix_diff_t{1};
    QTest::newRow("2: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseMBegin(1) << m_SecondaryIntMatrix.reverseMEnd(1) << -1 << matrix_diff_t{3};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(0, 0) << m_PrimaryIntMatrix.getReverseMIterator({1, 0}) << -3 << matrix_diff_t{0};
    QTest::newRow("4: random iterator, random iterator") << m_SecondaryIntMatrix.getReverseMIterator(4, 1) << m_SecondaryIntMatrix.getReverseMIterator({1, 4}) << 4 << matrix_diff_t{1};
    QTest::newRow("5: random iterator, random iterator") << m_SecondaryIntMatrix.getReverseMIterator(3, 2) << m_SecondaryIntMatrix.getReverseMIterator({1, 4}) << 4 << matrix_diff_t{0};
}

void ReverseMIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                          }};
    
    QTest::addColumn<IntReverseMIter>("leftIterator");
    QTest::addColumn<IntReverseMIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntReverseMIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseMBegin(1) << m_PrimaryIntMatrix.reverseMEnd(1) << 5 << m_PrimaryIntMatrix.getReverseMIterator(3, 2);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseMBegin(1) << m_PrimaryIntMatrix.reverseMEnd(1) << -9 << m_PrimaryIntMatrix.reverseMEnd(1);
}

void ReverseMIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("firstIterator");
    QTest::addColumn<IntReverseMIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseMBegin(1) << m_PrimaryIntMatrix.getReverseMIterator(0, 1);
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseMIterator(0, 1) << m_PrimaryIntMatrix.reverseMEnd(1);
}

void ReverseMIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("firstIterator");
    QTest::addColumn<IntReverseMIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << m_PrimaryIntMatrix.getReverseMIterator(3, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(3, 0) << m_PrimaryIntMatrix.getReverseMIterator(2, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator(2, 1) << m_PrimaryIntMatrix.getReverseMIterator({-1, 1});
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << m_PrimaryIntMatrix.reverseMEnd(-1);
}

void ReverseMIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseMIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntReverseMIter>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseMBegin(3, 0);
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << matrix_diff_t{2} << m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    QTest::newRow("3: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseMEnd(3, 0);
    QTest::newRow("4: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseMBegin(-1) << matrix_diff_t{4} << m_PrimaryIntMatrix.reverseMEnd(3, 0);
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{-2} << m_PrimaryIntMatrix.reverseMBegin(3, 0);
    QTest::newRow("6: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseMBegin(3, 0);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseMIterator(2, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    QTest::newRow("9: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseMEnd(3, 0);
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseMIterator({-1, 1}) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseMEnd(3, 0);
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseMEnd(-1) << matrix_diff_t{-4} << m_PrimaryIntMatrix.reverseMBegin(3, 0);
    QTest::newRow("12: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseMEnd(-1) << matrix_diff_t{-3} << m_PrimaryIntMatrix.reverseMBegin(3, 0);
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.reverseMEnd(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseMIterator(1, 2);
    QTest::newRow("14: end iterator, end iterator") << m_PrimaryIntMatrix.reverseMEnd(-1) << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseMEnd(3, 0);
    QTest::newRow("15: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{-2} << m_SecondaryIntMatrix.reverseMBegin(2, 0);
    QTest::newRow("16: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseMBegin(2, 0);
    QTest::newRow("17: begin iterator, random iterator") << m_SecondaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{2} << m_SecondaryIntMatrix.getReverseMIterator(0, 2);
    QTest::newRow("18: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{3} << m_SecondaryIntMatrix.reverseMEnd(2, 0);
    QTest::newRow("19: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseMBegin(2, 0) << matrix_diff_t{4} << m_SecondaryIntMatrix.reverseMEnd(2, 0);
}

QTEST_APPLESS_MAIN(ReverseMIteratorTests)

#include "tst_reversemiteratortests.moc"
