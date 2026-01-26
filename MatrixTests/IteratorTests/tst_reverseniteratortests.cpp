#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntReverseNIter)
Q_DECLARE_METATYPE(StringReverseNIter)

class ReverseNIteratorTests : public QObject
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
    
    IntReverseNIter m_PrimaryIntIterator;
    IntReverseNIter m_SecondaryIntIterator;
    StringReverseNIter m_StringIterator;
};

void ReverseNIteratorTests::testIteratorCreation()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ReverseNIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    IntReverseNIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ReverseNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntReverseNIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ReverseNIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseNIteratorTests::testLessThanOperator()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntReverseNIter, inputIterator);
    QFETCH(IntReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntReverseNIter, inputIterator);
    QFETCH(IntReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(4, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(6, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntReverseNIter, inputIterator);
    QFETCH(IntReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntReverseNIter, inputIterator);
    QFETCH(IntReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(6, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(4, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testOperatorPlus()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseNIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorMinus()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseNIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseNIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntReverseNIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntReverseNIter, firstIterator);
    QFETCH(IntReverseNIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseNIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ReverseNIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};
    *m_PrimaryIntMatrix.getReverseNIterator(0, 0) = 1;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getReverseNIterator(2, 1) = -6;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 3) = 11;
    *m_PrimaryIntMatrix.reverseNBegin() = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntMatrix.reserve(5, 4);
    *m_PrimaryIntMatrix.getReverseNIterator(0, 0) = 1;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getReverseNIterator(2, 1) = -6;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 3) = 11;
    *m_PrimaryIntMatrix.reverseNBegin() = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");
}

void ReverseNIteratorTests::testAsteriskOperatorReadWrite()
{
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 1) == 10);

    // test with column capacity offset

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 1) == 10);
}

void ReverseNIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringReverseNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ReverseNIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {{3, 4}, "zzz"};
    m_SecondaryStringMatrix = {3, 4, {"abc", "zzz", "zzz", "zzz", "ba", "zzz", "zzz", "abcdefghijk", "zzz", "gfedcba", "zzz", "fedcba"}};
    m_PrimaryStringMatrix.getReverseNIterator(0, 0)->assign("abc");
    m_PrimaryStringMatrix.getReverseNIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getReverseNIterator(2, 1)->assign("gfedcba");
    m_PrimaryStringMatrix.getReverseNIterator(1, 3)->assign("abcdefghijk");
    m_PrimaryStringMatrix.reverseNBegin()->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryStringMatrix = {{3, 4}, "zzz"};
    m_PrimaryStringMatrix.reserve(3, 6);
    m_PrimaryStringMatrix.getReverseNIterator(0, 0)->assign("abc");
    m_PrimaryStringMatrix.getReverseNIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getReverseNIterator(2, 1)->assign("gfedcba");
    m_PrimaryStringMatrix.getReverseNIterator(1, 3)->assign("abcdefghijk");
    m_PrimaryStringMatrix.reverseNBegin()->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");
}

void ReverseNIteratorTests::testArrowOperatorReadWrite()
{
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 1) == "abcdefghi");

    // test with row/column capacity offset

    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.reserve(5, 4);
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.reserve(5, 4);
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 1) == "abcdefghi");
}

void ReverseNIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseNIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};

    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    m_PrimaryIntIterator[1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[-4] = -6;
    m_PrimaryIntIterator[-9] = 11;
    m_PrimaryIntIterator[-10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    m_PrimaryIntIterator[10] = 1;
    m_PrimaryIntIterator[9] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[-1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator[11] = 1;
    m_PrimaryIntIterator[10] = -2;
    m_PrimaryIntIterator[6] = -6;
    m_PrimaryIntIterator[1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntMatrix.reserve(5, 6);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntMatrix.reserve(5, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {{3, 4}, -20};
    m_PrimaryIntMatrix.reserve(3, 6);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator[11] = 1;
    m_PrimaryIntIterator[10] = -2;
    m_PrimaryIntIterator[6] = -6;
    m_PrimaryIntIterator[1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ReverseNIteratorTests::testStdCount()
{
    QFETCH(IntReverseNIter, leftIterator);
    QFETCH(IntReverseNIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseNIteratorTests::testStdFind()
{
    QFETCH(IntReverseNIter, leftIterator);
    QFETCH(IntReverseNIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntReverseNIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ReverseNIteratorTests::testStdFindWithIncrementAndCount()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.reverseNBegin(), m_PrimaryIntMatrix.reverseNEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.reverseNBegin(), m_PrimaryIntMatrix.reverseNEnd(), 10) == m_PrimaryIntMatrix.reverseNEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();

    while(m_PrimaryIntIterator != m_PrimaryIntMatrix.reverseNEnd())
    {
        m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.reverseNEnd(), 9);

        if (m_PrimaryIntIterator != m_PrimaryIntMatrix.reverseNEnd())
        {
            *m_PrimaryIntIterator = 10;
        }
    }

    QVERIFY2(std::count(m_PrimaryIntMatrix.reverseNBegin(), m_PrimaryIntMatrix.reverseNEnd(), 10) == 3,
             "The iterator doesn't work properly with std::find, element values haven't been correctly replaced!");
}

void ReverseNIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5,  2, -7,
                               1, 9, -2,  7,
                               3, 8,  2,  2,
                               1, 0,  8,  9,
                               4, 6,  9,  11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                 4, 9, 9, 11,
                                 3, 8, 8, 9,
                                 1, 6, 2, 7,
                                 1, 5, 2, 2,
                                -1, 0, -2, -7
                            }};

    for (auto column{0}; column < m_PrimaryIntMatrix.getNrOfColumns(); ++column)
    {
        std::sort(m_PrimaryIntMatrix.reverseNColumnBegin(column), m_PrimaryIntMatrix.reverseNColumnEnd(column));
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                11, 8, 3, 1,
                                9, 7, 2, 0,
                                9, 6, 2, -1,
                                9, 5, 2, -2,
                                8, 4, 1, -7
                            }};

    std::sort(m_PrimaryIntMatrix.reverseNBegin(), m_PrimaryIntMatrix.reverseNEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                              -1, 5, 8, -2,
                               1, 9, 7, -7,
                               3, 8, 6, 2,
                               1, 0, 2, 9,
                               4, 9, 2, 11
                          }};

    std::sort(m_PrimaryIntMatrix.getReverseNIterator(1, 3), m_PrimaryIntMatrix.getReverseNIterator(3, 1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                -1, 5, 2, 8,
                                 1, 9, -2, 7,
                                 3, 8, 11, 2,
                                 1, 0, 9, 2,
                                 4, 6, 9, -7
                            }};

    std::sort(m_PrimaryIntMatrix.reverseNBegin(), m_PrimaryIntMatrix.getReverseNIterator(1, 2));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                9, 3, -1, -7,
                                8, 2, -2, 7,
                                6, 1, 2, 2,
                                5, 1, 8, 9,
                                4, 0, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getReverseNIterator(1, 2), m_PrimaryIntMatrix.reverseNEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

void ReverseNIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("3: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("4: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{1u};
    QTest::newRow("5: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{4u};
    QTest::newRow("6: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("7: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("8: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("9: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("10: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{3u};
    QTest::newRow("11: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{6u};
    QTest::newRow("12: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("18: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("19: end iterator") << m_SecondaryIntMatrix.reverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ReverseNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("firstIterator");
    QTest::addColumn<IntReverseNIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("7: column begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << m_PrimaryIntMatrix.getReverseNIterator(7, 0);
    QTest::newRow("8: column begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.getReverseNIterator(7, 1);
    QTest::newRow("9: column begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(5) << m_PrimaryIntMatrix.getReverseNIterator(7, 5);
    QTest::newRow("10: column begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << m_PrimaryIntMatrix.getReverseNIterator(7, 7);
    QTest::newRow("11: column begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("12: column end iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("13: column end iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << m_PrimaryIntMatrix.getReverseNIterator(7, 0);
    QTest::newRow("14: column end iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(5) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("15: column end iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << m_PrimaryIntMatrix.getReverseNIterator(7, 6);
    QTest::newRow("16: column end iterator, random iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << m_PrimaryIntMatrix.getReverseNIterator(7, 7);
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntReverseNIter>("iterator");

    QTest::newRow("1: end iterator")  << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("2: random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("3: random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("4: random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("5: random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("6: random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("7: begin iterator")  << m_PrimaryIntMatrix.reverseNBegin();
}

void ReverseNIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseNIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseNIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseNIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ReverseNIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ReverseNIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ReverseNIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ReverseNIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ReverseNIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ReverseNIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseNIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseNIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseNIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ReverseNIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("firstIterator");
    QTest::addColumn<IntReverseNIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-1};
    QTest::newRow("3: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-27};
    QTest::newRow("4: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-70};
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-71};
    QTest::newRow("6: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-72};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-26};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-69};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-70};
    QTest::newRow("12: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-71};
    QTest::newRow("13: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{27};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{26};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-43};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-44};
    QTest::newRow("18: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-45};
    QTest::newRow("19: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{70};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{69};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{43};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-1};
    QTest::newRow("24: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-2};
    QTest::newRow("25: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{44};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{1};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{0};
    QTest::newRow("30: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-1};
    QTest::newRow("31: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{72};
    QTest::newRow("32: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{71};
    QTest::newRow("33: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{45};
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{2};
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{1};
    QTest::newRow("36: end iterator, end iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 7) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 7) << matrix_diff_t{-14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << matrix_diff_t{2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntReverseNIter{} << IntReverseNIter{} << matrix_diff_t{0};
}

void ReverseNIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntReverseNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(5, 6);

    QTest::newRow("6: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << -12;
}

void ReverseNIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    
    QTest::addColumn<StringReverseNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryStringMatrix.getReverseNIterator(0, 0) << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getReverseNIterator(1, 0) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getReverseNIterator(2, 1) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryStringMatrix.reverseNBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(5, 4);

    QTest::newRow("6: random iterator") << m_SecondaryStringMatrix.getReverseNIterator(0, 0) << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getReverseNIterator(1, 0) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getReverseNIterator(2, 1) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryStringMatrix.reverseNBegin() << 6;
}

void ReverseNIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntReverseNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{10} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{9} << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{5} << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{-1} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{4} << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{-5} << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{-6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{1} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-4} << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-9} << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-10} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-11} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(3, 6);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{10} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{9} << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{5} << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << matrix_diff_t{-1} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{4} << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{-5} << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << matrix_diff_t{-6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{1} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-4} << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-9} << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-10} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-11} << -12;
}

void ReverseNIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};
    
    QTest::addColumn<IntReverseNIter>("leftIterator");
    QTest::addColumn<IntReverseNIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 1) << m_PrimaryIntMatrix.getReverseNIterator(3, 0) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 2) << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 2) << m_PrimaryIntMatrix.getReverseNIterator(3, 0) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 1) << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(3, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 2) << m_PrimaryIntMatrix.reverseNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(2, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 2) << m_PrimaryIntMatrix.reverseNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << matrix_diff_t{1};
    QTest::newRow("12: column end iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(3) << m_PrimaryIntMatrix.reverseNColumnEnd(0) << 8 << matrix_diff_t{2};
    QTest::newRow("13: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(3) << m_PrimaryIntMatrix.reverseNColumnEnd(3) << 9 << matrix_diff_t{1};
    QTest::newRow("14: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(3) << m_PrimaryIntMatrix.reverseNColumnEnd(2) << 9 << matrix_diff_t{2};
    QTest::newRow("15: column end iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << m_PrimaryIntMatrix.reverseNEnd() << 1 << matrix_diff_t{2};
    QTest::newRow("16: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << matrix_diff_t{1};
    QTest::newRow("17: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(2) << m_PrimaryIntMatrix.reverseNEnd() << 1 << matrix_diff_t{3};
    QTest::newRow("18: begin iterator, column begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnBegin(2) << 1 << matrix_diff_t{0};
}

void ReverseNIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};
    
    QTest::addColumn<IntReverseNIter>("leftIterator");
    QTest::addColumn<IntReverseNIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntReverseNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 5 << m_PrimaryIntMatrix.getReverseNIterator(0, 1);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("3: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 6 << m_PrimaryIntMatrix.reverseNColumnBegin(1);
    QTest::newRow("4: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getReverseNIterator(0, 1);
    QTest::newRow("5: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("6: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << -1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("7: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("8: column begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("9: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 6 << m_PrimaryIntMatrix.reverseNColumnBegin(1);
    QTest::newRow("10: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << -1 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("11: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 3 << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("12: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << -2 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("13: column begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("14: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 11 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("15: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getReverseNIterator(0, 1);
    QTest::newRow("16: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 0 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("17: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("18: begin iterator, column end iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 7 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -7 << m_PrimaryIntMatrix.getReverseNIterator(0, 3);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -2 << m_PrimaryIntMatrix.getReverseNIterator(1, 2);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -1 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 11 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 10 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 0 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << -1 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 4 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 11 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 11 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 2 << m_PrimaryIntMatrix.getReverseNIterator(2, 3);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 9 << m_PrimaryIntMatrix.getReverseNIterator(3, 3);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
}

void ReverseNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntReverseNIter>("firstIterator");
    QTest::addColumn<IntReverseNIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("firstIterator");
    QTest::addColumn<IntReverseNIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNBegin();
}

void ReverseNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntReverseNIter>("inputIterator");
    QTest::addColumn<IntReverseNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(5, 8);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(5, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(1, 5) << m_PrimaryIntMatrix.getReverseNIterator(0, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(0, 5) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(7, 4) << m_PrimaryIntMatrix.getReverseNIterator(6, 4);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntReverseNIter>("inputIterator");
    QTest::addColumn<IntReverseNIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(6, 4) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(7, 4) << m_PrimaryIntMatrix.getReverseNIterator(0, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(0, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(1, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 5);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin();
}

void ReverseNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntReverseNIter>("expectedIterator");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("3: end iterator, end iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("4: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("5: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("6: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-11} << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("8: end iterator, random iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("9: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("10: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{4} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-10} << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("20: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("21: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-72} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("22: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_diff_t{-74} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("23: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{5} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("24: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{3} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-9} << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("31: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_diff_t{-73} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{48} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{46} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{45} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{44} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{43} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{6} << m_PrimaryIntMatrix.getReverseNIterator(6, 4);
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{2} << m_PrimaryIntMatrix.getReverseNIterator(2, 5);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getReverseNIterator(2, 6);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-26} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("45: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-27} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("46: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-28} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("47: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_diff_t{-30} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("48: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{74} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("49: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{72} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("50: random iterator, end iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{71} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{70} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{69} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{24} << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{3} << m_PrimaryIntMatrix.getReverseNIterator(3, 8);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{0} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("56: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("57: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-2} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("58: random iterator, begin iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_diff_t{-4} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("59: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("60: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("61: begin iterator, end iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("62: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("63: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("64: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{25} << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("65: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getReverseNIterator(3, 8);
    QTest::newRow("66: begin iterator, random iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("67: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("68: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("69: begin iterator, begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.reverseNEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.reverseNEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.reverseNEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntReverseNIter{} << matrix_diff_t{-1} << IntReverseNIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntReverseNIter{} << matrix_diff_t{1} << IntReverseNIter{};
}

QTEST_APPLESS_MAIN(ReverseNIteratorTests)

#include "tst_reverseniteratortests.moc"
