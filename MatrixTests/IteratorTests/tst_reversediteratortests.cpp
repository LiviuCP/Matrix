#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntReverseDIter)
Q_DECLARE_METATYPE(StringReverseDIter)

class ReverseDIteratorTests : public QObject
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
    
    IntReverseDIter m_PrimaryIntIterator;
    IntReverseDIter m_SecondaryIntIterator;
    StringReverseDIter m_StringIterator;
};

void ReverseDIteratorTests::testIteratorCreation()
{
    QFETCH(IntReverseDIter, iterator);
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

void ReverseDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();
    
    IntReverseDIter emptyIterator;

    QVERIFY2(!emptyIterator.getRowNr().has_value() && !emptyIterator.getColumnNr().has_value() && emptyIterator.getDiagonalNr() == 0 && !emptyIterator.getDiagonalIndex().has_value(), "The iterator has not been correctly created");
}

void ReverseDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseDIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 2);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ReverseDIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseDIteratorTests::testLessThanOperator()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseDIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseDIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseDIteratorTests::testOperatorPlus()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseDIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorMinus()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseDIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseDIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseDIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntReverseDIter, firstIterator);
    QFETCH(IntReverseDIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator({1, 1});
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(0, 1) == 14, "The asterisk operator does not work correctly when writing the value!");
}

void ReverseDIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    m_StringIterator = m_StringMatrix.reverseDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    m_StringIterator = m_StringMatrix.getReverseDIterator(1, 2);
    m_StringIterator->assign("abcdefghij");

    QVERIFY2(*m_StringMatrix.getReverseDIterator({1, 0}) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");

    // test with row/column capacity offset
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    m_StringMatrix.resize(2, 3, 4, 5);
    m_StringIterator = m_StringMatrix.reverseDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    m_StringIterator = m_StringMatrix.getReverseDIterator(1, 2);
    m_StringIterator->assign("abcdefghij");

    QVERIFY2(*m_StringMatrix.getReverseDIterator({1, 0}) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");
}

void ReverseDIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseDIteratorTests::testSquareBracketsOperatorWrite()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseDIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseDIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseDIterator({1, 0}) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ReverseDIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 6);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator({-2, 0});

    QVERIFY(m_PrimaryIntIterator[1] == 7);
}

void ReverseDIteratorTests::testStdCount()
{
    QFETCH(IntReverseDIter, leftIterator);
    QFETCH(IntReverseDIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseDIteratorTests::testStdFind()
{
    QFETCH(IntReverseDIter, leftIterator);
    QFETCH(IntReverseDIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntReverseDIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ReverseDIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  4, 6,  7,
                              1,  2, -3,  4, -5, 5,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.reverseDBegin(1), m_PrimaryIntMatrix.reverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.reverseDEnd(1), "The std::find algorithm does not return the expected iterator!");
}

void ReverseDIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6, 7,
                              1,  2, -3,  4, -5, 6, 7,
                              1,  2, -3,  1, -5, 6, 7,
                              1,  2, -3,  4,  0, 6, 7,
                              1,  2, -3,  4, -5, 5, 7,
                              1,  2, -3,  4, -5, 6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1,  5, -3,  4, -5,  6,  7,
                                1,  2,  2,  4, -5,  6,  7,
                                1,  2, -3,  1, -5,  6,  7,
                                1,  2, -3,  4,  0,  6,  7,
                                1,  2, -3,  4, -5, -1,  7,
                                1,  2, -3,  4, -5,  6, -3,
                            }};

    std::sort(m_PrimaryIntMatrix.reverseDBegin(1), m_PrimaryIntMatrix.reverseDEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5,  6, 7,
                              1,  2,  5,  4, -5,  6, 7,
                              1,  2, -3, -3, -5,  6, 7,
                              1,  2, -3,  4,  1,  6, 7,
                              1,  2, -3,  4, -5,  0, 7,
                              1,  2, -3,  4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5,  6, 7,
                                1,  2,  5,  4, -5,  6, 7,
                                1,  2, -3,  1, -5,  6, 7,
                                1,  2, -3,  4,  0,  6, 7,
                                1,  2, -3,  4, -5, -3, 7,
                                1,  2, -3,  4, -5,  6, 2,
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseDIterator(4, 5), m_PrimaryIntMatrix.getReverseDIterator(1, 2));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5,  6, 7,
                              1,  2,  5,  4, -5,  6, 7,
                              1,  2, -3,  1, -5,  6, 7,
                              1,  2, -3,  4,  0,  6, 7,
                              1,  2, -3,  4, -5, -3, 7,
                              1,  2, -3,  4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5, 6,  7,
                                1,  2,  5,  4, -5, 6,  7,
                                1,  2, -3,  2, -5, 6,  7,
                                1,  2, -3,  4,  1, 6,  7,
                                1,  2, -3,  4, -5, 0,  7,
                                1,  2, -3,  4, -5, 6, -3,
                            }};

    std::sort(m_PrimaryIntMatrix.reverseDBegin(1), m_PrimaryIntMatrix.getReverseDIterator(1, 2));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3, 4, -5,  6, 7,
                              1,  2,  1, 4, -5,  6, 7,
                              1,  2, -3, 5, -5,  6, 7,
                              1,  2, -3, 4, -3,  6, 7,
                              1,  2, -3, 4, -5,  0, 7,
                              1,  2, -3, 4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, 5, -3, 4, -5,  6, 7,
                                1, 2,  1, 4, -5,  6, 7,
                                1, 2, -3, 0, -5,  6, 7,
                                1, 2, -3, 4, -1,  6, 7,
                                1, 2, -3, 4, -5, -3, 7,
                                1, 2, -3, 4, -5,  6, 2,
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseDIterator(4, 5), m_PrimaryIntMatrix.reverseDEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ReverseDIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_diff_t>("expectedDiagonalNr");
    QTest::addColumn<matrix_opt_size_t>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(-2) << matrix_opt_size_t{3u} << matrix_opt_size_t{1u} << matrix_diff_t{-2} << matrix_opt_size_t{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(2, 1) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0, 0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(1, 2) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.reverseDEnd(-2) << matrix_opt_size_t{1u} << matrix_opt_size_t{} << matrix_diff_t{-2} << matrix_opt_size_t{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.reverseDEnd(1) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.reverseDEnd(2, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{} << matrix_diff_t{-1} << matrix_opt_size_t{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0, 0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.reverseDEnd(1, 2) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{-1} << matrix_opt_size_t{2u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 2) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 2) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 0}) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({2, 0}) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({0, 2}) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{2u};
}

void ReverseDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("firstIterator");
    QTest::addColumn<IntReverseDIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(1, 2) << m_PrimaryIntMatrix.getReverseDIterator({1, 0});
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(2, 1);
    QTest::newRow("3: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseDBegin(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(3, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(3, 2) << m_PrimaryIntMatrix.getReverseDIterator({-1, 0});
    QTest::newRow("5: end iterator, end iterator") << m_PrimaryIntMatrix.reverseDEnd(2) << m_PrimaryIntMatrix.reverseDEnd(0, 2);
}

void ReverseDIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseDIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseDIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseDIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseDIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseDIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseDIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseDIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseDIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseDIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("firstIterator");
    QTest::addColumn<IntReverseDIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(3, 2) << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 0) << m_PrimaryIntMatrix.reverseDBegin(2, 2) << matrix_diff_t{-2};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator({-1, 0}) << matrix_diff_t{-1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.getReverseDIterator({1, 0}) << matrix_diff_t{-1};
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 0}) << m_PrimaryIntMatrix.reverseDEnd(-1) << matrix_diff_t{3};
    QTest::newRow("6: end iterator, end iterator") << m_PrimaryIntMatrix.reverseDEnd(1) << m_PrimaryIntMatrix.reverseDEnd(1, 2) << matrix_diff_t{0};
}

void ReverseDIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0, 1) << matrix_diff_t{0} << 6;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{-1} << 12;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{1} << 4;
    QTest::newRow("6: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-3} << 9;
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-1} << 1;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("9: begin iterator") << m_SecondaryIntMatrix.reverseDBegin(0, 1) << matrix_diff_t{0} << 6;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.reverseDBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("11: random iterator") << m_SecondaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{-1} << 12;
    QTest::newRow("12: random iterator") << m_SecondaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("13: random iterator") << m_SecondaryIntMatrix.getReverseDIterator(2, 1) << matrix_diff_t{1} << 4;
    QTest::newRow("14: end iterator") << m_SecondaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-3} << 9;
    QTest::newRow("15: end iterator") << m_SecondaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.reverseDEnd(0) << matrix_diff_t{-1} << 1;
}

void ReverseDIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {1, 2, {2, -3}};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5, 6,  7,
                                1,  2,  4,  4, -5, 6,  7,
                                1,  2, -3, -1, -5, 6,  7,
                                1,  2, -3,  4,  5, 6,  7,
                                1,  2, -3,  4, -5, 4,  7,
                                1,  2, -3,  4, -5, 6, -1,
                            }};
    
    QTest::addColumn<IntReverseDIter>("leftIterator");
    QTest::addColumn<IntReverseDIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << -3 << matrix_diff_t{1};
    QTest::newRow("2: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseDBegin(1) << m_SecondaryIntMatrix.reverseDEnd(1) << -1 << matrix_diff_t{3};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.getReverseDIterator({1, 0}) << -3 << matrix_diff_t{0};
    QTest::newRow("4: random iterator, random iterator") << m_SecondaryIntMatrix.getReverseDIterator(4, 5) << m_SecondaryIntMatrix.getReverseDIterator({1, 4}) << 4 << matrix_diff_t{1};
    QTest::newRow("5: random iterator, random iterator") << m_SecondaryIntMatrix.getReverseDIterator(3, 4) << m_SecondaryIntMatrix.getReverseDIterator({1, 4}) << 4 << matrix_diff_t{0};
}

void ReverseDIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  5, 6,  7,
                              1,  2, -3,  4, -5, 4,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};
    
    QTest::addColumn<IntReverseDIter>("leftIterator");
    QTest::addColumn<IntReverseDIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntReverseDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << 5 << m_PrimaryIntMatrix.getReverseDIterator(3, 4);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << -9 << m_PrimaryIntMatrix.reverseDEnd(1);
}

void ReverseDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("firstIterator");
    QTest::addColumn<IntReverseDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.reverseDEnd(1);
}

void ReverseDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("firstIterator");
    QTest::addColumn<IntReverseDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.getReverseDIterator(3, 2);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(3, 2) << m_PrimaryIntMatrix.getReverseDIterator(2, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator({-1, 1});
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << m_PrimaryIntMatrix.reverseDEnd(-1);
}

void ReverseDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntReverseDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << matrix_diff_t{2} << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("3: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("4: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseDBegin(-1) << matrix_diff_t{4} << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{-2} << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("6: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseDIterator(2, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("9: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseDEnd(-1) << matrix_diff_t{-4} << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("12: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseDEnd(-1) << matrix_diff_t{-3} << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.reverseDEnd(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("14: end iterator, end iterator") << m_PrimaryIntMatrix.reverseDEnd(-1) << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("15: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << matrix_diff_t{-2} << m_SecondaryIntMatrix.reverseDBegin(2, 3);
    QTest::newRow("16: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseDBegin(2, 3);
    QTest::newRow("17: begin iterator, random iterator") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << matrix_diff_t{2} << m_SecondaryIntMatrix.getReverseDIterator(0, 1);
    QTest::newRow("18: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << matrix_diff_t{3} << m_SecondaryIntMatrix.reverseDEnd(2, 3);
    QTest::newRow("19: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << matrix_diff_t{4} << m_SecondaryIntMatrix.reverseDEnd(2, 3);
}

QTEST_APPLESS_MAIN(ReverseDIteratorTests)

#include "tst_reversediteratortests.moc"
