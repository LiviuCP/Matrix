#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntReverseZIter)
Q_DECLARE_METATYPE(StringReverseZIter)

class ReverseZIteratorTests : public QObject
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
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testAsteriskOperatorRead();
    void testAsteriskOperatorWrite();
    void testAsteriskOperatorReadWrite();
    void testArrowOperatorRead();
    void testArrowOperatorWrite();
    void testArrowOperatorReadWrite();
    void testSquareBracketsOperatorRead();
    void testSquareBracketsOperatorWrite();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrementAndCount();
    void testStdSort();

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
    void testOperatorPlus_data();
    void testOperatorMinus_data();
    void testOperatorPlusEqual_data();
    void testOperatorMinusEqual_data();
    void testDifferenceOperator_data();
    void testAsteriskOperatorRead_data();
    void testArrowOperatorRead_data();
    void testSquareBracketsOperatorRead_data();
    void testStdCount_data();
    void testStdFind_data();

private:
    // test data helper methods
    void _buildLessThanOperatorTestingTable();
    void _buildLessThanOrEqualOperatorTestingTable();
    void _buildIncrementOperatorTestingTable();
    void _buildDecrementOperatorTestingTable();
    void _buildOperatorPlusTestingTable();

    IntMatrix m_PrimaryIntMatrix;
    IntMatrix m_SecondaryIntMatrix;
    StringMatrix m_PrimaryStringMatrix;
    StringMatrix m_SecondaryStringMatrix;
    
    IntReverseZIter m_PrimaryIntIterator;
    IntReverseZIter m_SecondaryIntIterator;
    StringReverseZIter m_StringIterator;
};

void ReverseZIteratorTests::testIteratorCreation()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ReverseZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    IntReverseZIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ReverseZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntReverseZIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ReverseZIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseZIteratorTests::testLessThanOperator()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntReverseZIter, inputIterator);
    QFETCH(IntReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntReverseZIter, inputIterator);
    QFETCH(IntReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntReverseZIter, inputIterator);
    QFETCH(IntReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntReverseZIter, inputIterator);
    QFETCH(IntReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testOperatorPlus()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseZIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorMinus()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseZIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseZIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseZIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntReverseZIter, firstIterator);
    QFETCH(IntReverseZIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseZIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ReverseZIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};
    *m_PrimaryIntMatrix.getReverseZIterator(0, 0) = 1;
    *m_PrimaryIntMatrix.getReverseZIterator(0, 1) = -2;
    *m_PrimaryIntMatrix.getReverseZIterator(1, 2) = -6;
    *m_PrimaryIntMatrix.getReverseZIterator(3, 1) = 11;
    *m_PrimaryIntMatrix.reverseZBegin() = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 3);
    *m_PrimaryIntMatrix.getReverseZIterator(0, 0) = 1;
    *m_PrimaryIntMatrix.getReverseZIterator(0, 1) = -2;
    *m_PrimaryIntMatrix.getReverseZIterator(1, 2) = -6;
    *m_PrimaryIntMatrix.getReverseZIterator(3, 1) = 11;
    *m_PrimaryIntMatrix.reverseZBegin() = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");
}

void ReverseZIteratorTests::testAsteriskOperatorReadWrite()
{
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(1, 0) == 10);

    // test with column capacity offset

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(1, 0) == 10);
}

void ReverseZIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringReverseZIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ReverseZIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {{4, 3}, "zzz"};
    m_SecondaryStringMatrix = {4, 3, {"abc", "ba", "zzz", "zzz", "zzz", "gfedcba", "zzz", "zzz", "zzz", "zzz", "abcdefghijk", "fedcba"}};
    m_PrimaryStringMatrix.getReverseZIterator(0, 0)->assign("abc");
    m_PrimaryStringMatrix.getReverseZIterator(0, 1)->assign("ba");
    m_PrimaryStringMatrix.getReverseZIterator(1, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getReverseZIterator(3, 1)->assign("abcdefghijk");
    m_PrimaryStringMatrix.reverseZBegin()->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryStringMatrix = {{4, 3}, "zzz"};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_SecondaryStringMatrix = {4, 3, {"abc", "ba", "zzz", "zzz", "zzz", "gfedcba", "zzz", "zzz", "zzz", "zzz", "abcdefghijk", "fedcba"}};
    m_PrimaryStringMatrix.getReverseZIterator(0, 0)->assign("abc");
    m_PrimaryStringMatrix.getReverseZIterator(0, 1)->assign("ba");
    m_PrimaryStringMatrix.getReverseZIterator(1, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getReverseZIterator(3, 1)->assign("abcdefghijk");
    m_PrimaryStringMatrix.reverseZBegin()->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");
}

void ReverseZIteratorTests::testArrowOperatorReadWrite()
{
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_StringIterator = m_PrimaryStringMatrix.reverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.reverseZBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(1, 0) == "abcdefghi");

    // test with row/column capacity offset

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_StringIterator = m_PrimaryStringMatrix.reverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_StringIterator = m_PrimaryStringMatrix.reverseZBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(1, 0) == "abcdefghi");
}

void ReverseZIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseZIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    m_PrimaryIntIterator[1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[-4] = -6;
    m_PrimaryIntIterator[-9] = 11;
    m_PrimaryIntIterator[-10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    m_PrimaryIntIterator[10] = 1;
    m_PrimaryIntIterator[9] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[-1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntIterator[11] = 1;
    m_PrimaryIntIterator[10] = -2;
    m_PrimaryIntIterator[6] = -6;
    m_PrimaryIntIterator[1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    m_PrimaryIntIterator[11] = 1;
    m_PrimaryIntIterator[10] = -2;
    m_PrimaryIntIterator[6] = -6;
    m_PrimaryIntIterator[1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ReverseZIteratorTests::testStdCount()
{
    QFETCH(IntReverseZIter, leftIterator);
    QFETCH(IntReverseZIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseZIteratorTests::testStdFind()
{
    QFETCH(IntReverseZIter, leftIterator);
    QFETCH(IntReverseZIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntReverseZIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ReverseZIteratorTests::testStdFindWithIncrementAndCount()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.reverseZBegin(), m_PrimaryIntMatrix.reverseZEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.reverseZBegin(), m_PrimaryIntMatrix.reverseZEnd(), 10) == m_PrimaryIntMatrix.reverseZEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();

    while(m_PrimaryIntIterator != m_PrimaryIntMatrix.reverseZEnd())
    {
        m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseZEnd(), 9);

        if (m_PrimaryIntIterator != m_PrimaryIntMatrix.reverseZEnd())
        {
            *m_PrimaryIntIterator = 10;
        }
    }

    QVERIFY2(std::count(m_PrimaryIntMatrix.reverseZBegin(), m_PrimaryIntMatrix.reverseZEnd(), 10) == 3,
             "The iterator doesn't work properly with std::find, element values haven't been correctly replaced!");
}

void ReverseZIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                4, 3, 1, 1, -1,
                                9, 8, 6, 5, 0,
                                9, 8, 2, 2, -2,
                                11, 9, 7, 2, -7
                            }};

    for (auto row{0}; row < m_PrimaryIntMatrix.getNrOfRows(); ++row)
    {
        std::sort(m_PrimaryIntMatrix.reverseZRowBegin(row), m_PrimaryIntMatrix.reverseZRowEnd(row));
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                11, 9, 9, 9, 8,
                                8, 7, 6, 5, 4,
                                3, 2, 2, 2, 1,
                                1, 0, -1, -2, -7
                            }};

    std::sort(m_PrimaryIntMatrix.reverseZBegin(), m_PrimaryIntMatrix.reverseZEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                -1, 1, 3, 1, 4,
                                 5, 9, 8, 0, 9,
                                 8, 7, 6, 2, 2,
                                -2, -7, 2, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseZIterator(3, 1), m_PrimaryIntMatrix.getReverseZIterator(1, 3));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                -1, 1, 3, 1, 4,
                                 5, 9, 8, 0, 6,
                                 2, -2, 11, 9, 9,
                                 8, 7, 2, 2, -7
                            }};

    std::sort(m_PrimaryIntMatrix.reverseZBegin(), m_PrimaryIntMatrix.getReverseZIterator(2, 1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                9, 8, 6, 5, 4,
                                3, 2, 1, 1, 0,
                               -1, -2, 2, 8, 9,
                               -7, 7, 2, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseZIterator(2, 1), m_PrimaryIntMatrix.reverseZEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

void ReverseZIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_opt_size_t{8} << matrix_opt_size_t{7};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_opt_size_t{0} << matrix_opt_size_t{};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(0) << matrix_opt_size_t{0} << matrix_opt_size_t{7};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << matrix_opt_size_t{1} << matrix_opt_size_t{7};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(4) << matrix_opt_size_t{4} << matrix_opt_size_t{7};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(7) << matrix_opt_size_t{7} << matrix_opt_size_t{7};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(8) << matrix_opt_size_t{8} << matrix_opt_size_t{7};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(0) << matrix_opt_size_t{0} << matrix_opt_size_t{};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(1) << matrix_opt_size_t{0} << matrix_opt_size_t{7};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(4) << matrix_opt_size_t{3} << matrix_opt_size_t{7};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(7) << matrix_opt_size_t{6} << matrix_opt_size_t{7};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(8) << matrix_opt_size_t{7} << matrix_opt_size_t{7};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_opt_size_t{0} << matrix_opt_size_t{0};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_opt_size_t{0} << matrix_opt_size_t{1};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_opt_size_t{5} << matrix_opt_size_t{4};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_opt_size_t{8} << matrix_opt_size_t{6};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << matrix_opt_size_t{8} << matrix_opt_size_t{7};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0) << matrix_opt_size_t{0} << matrix_opt_size_t{0};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1) << matrix_opt_size_t{0} << matrix_opt_size_t{1};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(44) << matrix_opt_size_t{5} << matrix_opt_size_t{4};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(70) << matrix_opt_size_t{8} << matrix_opt_size_t{6};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(71) << matrix_opt_size_t{8} << matrix_opt_size_t{7};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.reverseZEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ReverseZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("firstIterator");
    QTest::addColumn<IntReverseZIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(44) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(70) << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(71) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("7: row begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowBegin(0) << m_PrimaryIntMatrix.getReverseZIterator(0, 7);
    QTest::newRow("8: row begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.getReverseZIterator(1, 7);
    QTest::newRow("9: row begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowBegin(5) << m_PrimaryIntMatrix.getReverseZIterator(5, 7);
    QTest::newRow("10: row begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowBegin(7) << m_PrimaryIntMatrix.getReverseZIterator(7, 7);
    QTest::newRow("11: row begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowBegin(8) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("12: row end iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("13: row end iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowEnd(1) << m_PrimaryIntMatrix.getReverseZIterator(0, 7);
    QTest::newRow("14: row end iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowEnd(5) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("15: row end iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowEnd(7) << m_PrimaryIntMatrix.getReverseZIterator(6, 7);
    QTest::newRow("16: row end iterator, random iterator") << m_PrimaryIntMatrix.reverseZRowEnd(8) << m_PrimaryIntMatrix.getReverseZIterator(7, 7);
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntReverseZIter>("iterator");

    QTest::newRow("1: end iterator")  << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("2: random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("3: random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("4: random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("5: random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("6: random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("7: begin iterator")  << m_PrimaryIntMatrix.reverseZBegin();
}

void ReverseZIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseZIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseZIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseZIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseZIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseZIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ReverseZIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ReverseZIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ReverseZIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ReverseZIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseZIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseZIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseZIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseZIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("firstIterator");
    QTest::addColumn<IntReverseZIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-1};
    QTest::newRow("3: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-27};
    QTest::newRow("4: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-70};
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-71};
    QTest::newRow("6: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-72};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-26};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-69};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-70};
    QTest::newRow("12: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-71};
    QTest::newRow("13: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{27};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{26};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-43};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-44};
    QTest::newRow("18: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-45};
    QTest::newRow("19: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{70};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{69};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{43};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-1};
    QTest::newRow("24: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-2};
    QTest::newRow("25: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{44};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{1};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{0};
    QTest::newRow("30: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-1};
    QTest::newRow("31: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{72};
    QTest::newRow("32: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{71};
    QTest::newRow("33: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{45};
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{2};
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{1};
    QTest::newRow("36: end iterator, end iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(7, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(7, 2) << matrix_diff_t{-14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << matrix_diff_t{2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntReverseZIter{} << IntReverseZIter{} << matrix_diff_t{0};
}

void ReverseZIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    
    QTest::addColumn<IntReverseZIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(6, 5);

    QTest::newRow("6: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << -12;
}

void ReverseZIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    
    QTest::addColumn<StringReverseZIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryStringMatrix.getReverseZIterator(0, 0) << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getReverseZIterator(0, 1) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getReverseZIterator(1, 2) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryStringMatrix.reverseZBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(6, 3);

    QTest::newRow("6: random iterator") << m_SecondaryStringMatrix.getReverseZIterator(0, 0) << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getReverseZIterator(0, 1) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getReverseZIterator(1, 2) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryStringMatrix.reverseZBegin() << 6;
}

void ReverseZIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    
    QTest::addColumn<IntReverseZIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{10} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{9} << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{5} << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{0} << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{-1} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{4} << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{0} << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{-5} << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{-6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{1} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{0} << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-4} << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-9} << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-10} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-11} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{10} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{9} << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{5} << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{0} << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(3, 1) << matrix_diff_t{-1} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{4} << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{0} << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{-5} << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(1, 2) << matrix_diff_t{-6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{1} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{0} << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-4} << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-9} << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-10} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-11} << -12;
}

void ReverseZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};
    
    QTest::addColumn<IntReverseZIter>("leftIterator");
    QTest::addColumn<IntReverseZIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(2, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(2, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(2, 3) << 2 << matrix_diff_t{1};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(2, 3) << m_PrimaryIntMatrix.reverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(2, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(2, 2) << m_PrimaryIntMatrix.reverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(9) << m_PrimaryIntMatrix.getReverseZIterator(2) << 1 << matrix_diff_t{2};
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(10) << m_PrimaryIntMatrix.getReverseZIterator(2) << 1 << matrix_diff_t{2};
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(9) << m_PrimaryIntMatrix.getReverseZIterator(3) << 1 << matrix_diff_t{1};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(10) << m_PrimaryIntMatrix.getReverseZIterator(3) << 1 << matrix_diff_t{1};
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(13) << 2 << matrix_diff_t{1};
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(13) << m_PrimaryIntMatrix.reverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(12) << 2 << matrix_diff_t{1};
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(12) << m_PrimaryIntMatrix.reverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("19: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << matrix_diff_t{1};
    QTest::newRow("20: row end iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(3) << m_PrimaryIntMatrix.reverseZRowEnd(0) << 8 << matrix_diff_t{2};
    QTest::newRow("21: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(3) << m_PrimaryIntMatrix.reverseZRowEnd(3) << 9 << matrix_diff_t{1};
    QTest::newRow("22: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(3) << m_PrimaryIntMatrix.reverseZRowEnd(2) << 9 << matrix_diff_t{2};
    QTest::newRow("23: row end iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(1) << m_PrimaryIntMatrix.reverseZEnd() << 1 << matrix_diff_t{2};
    QTest::newRow("24: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << matrix_diff_t{1};
    QTest::newRow("25: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(2) << m_PrimaryIntMatrix.reverseZEnd() << 1 << matrix_diff_t{3};
    QTest::newRow("26: begin iterator, row begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowBegin(2) << 1 << matrix_diff_t{0};
}

void ReverseZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};
    
    QTest::addColumn<IntReverseZIter>("leftIterator");
    QTest::addColumn<IntReverseZIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntReverseZIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 5 << m_PrimaryIntMatrix.getReverseZIterator(5);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("3: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 6 << m_PrimaryIntMatrix.reverseZRowBegin(1);
    QTest::newRow("4: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getReverseZIterator(1, 0);
    QTest::newRow("5: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 8 << m_PrimaryIntMatrix.getReverseZIterator(7);
    QTest::newRow("6: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << -1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("7: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("8: row begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("9: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 6 << m_PrimaryIntMatrix.reverseZRowBegin(1);
    QTest::newRow("10: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << -1 << m_PrimaryIntMatrix.getReverseZIterator(0);
    QTest::newRow("11: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 3 << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("12: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << -2 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("13: row begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("14: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 11 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("15: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getReverseZIterator(1, 0);
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 0 << m_PrimaryIntMatrix.getReverseZIterator(8);
    QTest::newRow("17: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("18: begin iterator, row end iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 7 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -7 << m_PrimaryIntMatrix.getReverseZIterator(3, 0);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -2 << m_PrimaryIntMatrix.getReverseZIterator(11);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -1 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 11 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 10 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 0 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << -1 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 4 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 11 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 11 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 2 << m_PrimaryIntMatrix.getReverseZIterator(3, 2);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 9 << m_PrimaryIntMatrix.getReverseZIterator(18);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
}

void ReverseZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntReverseZIter>("firstIterator");
    QTest::addColumn<IntReverseZIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("firstIterator");
    QTest::addColumn<IntReverseZIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZBegin();
}

void ReverseZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntReverseZIter>("inputIterator");
    QTest::addColumn<IntReverseZIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 5);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 5) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 1);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 0);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 0) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(4, 7) << m_PrimaryIntMatrix.getReverseZIterator(4, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntReverseZIter>("inputIterator");
    QTest::addColumn<IntReverseZIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(4, 6) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(4, 7) << m_PrimaryIntMatrix.getReverseZIterator(5, 0);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 0) << m_PrimaryIntMatrix.getReverseZIterator(5, 1);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 2);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin();
}

void ReverseZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntReverseZIter>("expectedIterator");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("3: end iterator, end iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("4: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("5: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("6: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-11} << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("8: end iterator, random iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("9: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("10: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{4} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-10} << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("20: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("21: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-72} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("22: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_diff_t{-74} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("23: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{5} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("24: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-9} << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("31: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-70} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-71} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_diff_t{-73} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{48} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{46} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{45} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{44} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{43} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{6} << m_PrimaryIntMatrix.getReverseZIterator(4, 6);
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{2} << m_PrimaryIntMatrix.getReverseZIterator(5, 2);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getReverseZIterator(6, 2);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-26} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("45: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-27} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("46: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-28} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("47: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_diff_t{-30} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("48: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{74} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("49: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{72} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("50: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{71} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{70} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{69} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{24} << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{3} << m_PrimaryIntMatrix.getReverseZIterator(8, 3);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("56: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("57: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-2} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("58: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_diff_t{-4} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("59: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("60: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("61: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("62: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("63: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("64: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{25} << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("65: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getReverseZIterator(8, 3);
    QTest::newRow("66: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("67: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("68: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("69: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.reverseZEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.reverseZEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.reverseZEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntReverseZIter{} << matrix_diff_t{-1} << IntReverseZIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntReverseZIter{} << matrix_diff_t{1} << IntReverseZIter{};
}

QTEST_APPLESS_MAIN(ReverseZIteratorTests)

#include "tst_reverseziteratortests.moc"
