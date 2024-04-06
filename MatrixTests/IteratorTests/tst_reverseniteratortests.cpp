#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixReverseNIterator)
Q_DECLARE_METATYPE(StringMatrixReverseNIterator)

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

    IntMatrixReverseNIterator m_PrimaryIntIterator;
    IntMatrixReverseNIterator m_SecondaryIntIterator;
    StringMatrixReverseNIterator m_StringIterator;
};

void ReverseNIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ReverseNIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixReverseNIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
}

void ReverseNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixReverseNIterator, iterator);

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
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseNIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixReverseNIterator, inputIterator);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixReverseNIterator, inputIterator);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

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
    QFETCH(IntMatrixReverseNIterator, inputIterator);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixReverseNIterator, inputIterator);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

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
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixReverseNIterator, firstIterator);
    QFETCH(IntMatrixReverseNIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseNIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ReverseNIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {3, 4, -20};
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};
    *m_PrimaryIntMatrix.getReverseNIterator(0, 0) = 1;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getReverseNIterator(2, 1) = -6;
    *m_PrimaryIntMatrix.getReverseNIterator(1, 3) = 11;
    *m_PrimaryIntMatrix.reverseNBegin() = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntMatrix.resize(3, 4, 5, 4);
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
    m_PrimaryIntMatrix.resize(3, 2, 3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.resize(3, 2, 3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 1) == 10);
}

void ReverseNIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringMatrixReverseNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ReverseNIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {3, 4, "zzz"};
    m_SecondaryStringMatrix = {3, 4, {"abc", "zzz", "zzz", "zzz", "ba", "zzz", "zzz", "abcdefghijk", "zzz", "gfedcba", "zzz", "fedcba"}};
    m_PrimaryStringMatrix.getReverseNIterator(0, 0)->assign("abc");
    m_PrimaryStringMatrix.getReverseNIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getReverseNIterator(2, 1)->assign("gfedcba");
    m_PrimaryStringMatrix.getReverseNIterator(1, 3)->assign("abcdefghijk");
    m_PrimaryStringMatrix.reverseNBegin()->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryStringMatrix = {3, 4, "zzz"};
    m_PrimaryStringMatrix.resize(3, 4, 3, 6);
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
    m_PrimaryStringMatrix.resize(3, 2, 5, 4);
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.resize(3, 2, 5, 4);
    m_StringIterator = m_PrimaryStringMatrix.reverseNBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 1) == "abcdefghi");
}

void ReverseNIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseNIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    m_PrimaryIntIterator[1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[-4] = -6;
    m_PrimaryIntIterator[-9] = 11;
    m_PrimaryIntIterator[-10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    m_PrimaryIntIterator[10] = 1;
    m_PrimaryIntIterator[9] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[-1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseNBegin();
    m_PrimaryIntIterator[11] = 1;
    m_PrimaryIntIterator[10] = -2;
    m_PrimaryIntIterator[6] = -6;
    m_PrimaryIntIterator[1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntMatrix.resize(3, 4, 5, 6);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntMatrix.resize(3, 4, 5, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntMatrix.resize(3, 4, 3, 6);
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
    QFETCH(IntMatrixReverseNIterator, leftIterator);
    QFETCH(IntMatrixReverseNIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseNIteratorTests::testStdFind()
{
    QFETCH(IntMatrixReverseNIterator, leftIterator);
    QFETCH(IntMatrixReverseNIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixReverseNIterator, expectedIterator);

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

    for (int col{0}; col<m_PrimaryIntMatrix.getNrOfColumns(); ++col)
    {
        std::sort(m_PrimaryIntMatrix.reverseNColumnBegin(col), m_PrimaryIntMatrix.reverseNColumnEnd(col));
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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 7 << 8;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -1 << 0;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << 7 << 0;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << 7 << 1;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(4) << 7 << 4;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << 7 << 7;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << 7 << 8;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << -1 << 0;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 7 << 0;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(4) << 7 << 3;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << 7 << 6;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << 7 << 7;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 4 << 5;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 6 << 8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << 7 << 8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0) << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1) << 1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(44) << 4 << 5;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(70) << 6 << 8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(71) << 7 << 8;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << -1 << -1;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << -1 << -1;
}

void ReverseNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(44) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(70) << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(71) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << m_PrimaryIntMatrix.getReverseNIterator(7, 0);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.getReverseNIterator(7, 1);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(5) << m_PrimaryIntMatrix.getReverseNIterator(7, 5);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << m_PrimaryIntMatrix.getReverseNIterator(7, 7);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << m_PrimaryIntMatrix.getReverseNIterator(7, 0);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(5) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << m_PrimaryIntMatrix.getReverseNIterator(7, 6);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << m_PrimaryIntMatrix.getReverseNIterator(7, 7);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");

    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.reverseNBegin();
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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin() << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.reverseNBegin() << -1;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.reverseNBegin() << -27;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.reverseNBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNBegin() << -71;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNBegin() << -72;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -71;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -45;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -1;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 44;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 0;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -1;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 72;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.reverseNEnd() << 71;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.reverseNEnd() << 45;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.reverseNEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd() << 1;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 7) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 7) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << 2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseNIterator{} << IntMatrixReverseNIterator{} << 0;
}

void ReverseNIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(3, 4, 5, 6);

    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << 1;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << -2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << -6;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << -12;
}

void ReverseNIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};

    QTest::addColumn<StringMatrixReverseNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseNIterator(0, 0) << 3;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseNIterator(1, 0) << 2;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseNIterator(2, 1) << 7;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryStringMatrix.reverseNBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.resize(3, 4, 5, 4);

    QTest::newRow("{random iterator}") << m_SecondaryStringMatrix.getReverseNIterator(0, 0) << 3;
    QTest::newRow("{random iterator}") << m_SecondaryStringMatrix.getReverseNIterator(1, 0) << 2;
    QTest::newRow("{random iterator}") << m_SecondaryStringMatrix.getReverseNIterator(2, 1) << 7;
    QTest::newRow("{random iterator}") << m_SecondaryStringMatrix.getReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_SecondaryStringMatrix.reverseNBegin() << 6;
}

void ReverseNIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 11 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 10 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 6 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 1 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 0 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << -1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << 5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << 4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << -5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 1) << -6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 0 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -1 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -10 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -11 << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(3, 4, 3, 6);

    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 11 << 1;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 10 << -2;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 6 << -6;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 1 << 11;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 0 << -12;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 10 << 1;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 9 << -2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 5 << -6;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << 0 << 11;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 3) << -1 << -12;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << 5 << 1;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << 4 << -2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << 0 << -6;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << -5 << 11;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(2, 1) << -6 << -12;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << 1 << 1;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << 0 << -2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << -4 << -6;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << -9 << 11;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(1, 0) << -10 << -12;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << 0 << 1;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << -1 << -2;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << -5 << -6;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << -10 << 11;
    QTest::newRow("{random iterator}") << m_SecondaryIntMatrix.getReverseNIterator(0, 0) << -11 << -12;
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

    QTest::addColumn<IntMatrixReverseNIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 1) << m_PrimaryIntMatrix.getReverseNIterator(3, 0) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 2) << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 2) << m_PrimaryIntMatrix.getReverseNIterator(3, 0) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 1) << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(3, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 2) << m_PrimaryIntMatrix.reverseNEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 2) << m_PrimaryIntMatrix.reverseNEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(9) << m_PrimaryIntMatrix.getReverseNIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(10) << m_PrimaryIntMatrix.getReverseNIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(9) << m_PrimaryIntMatrix.getReverseNIterator(3) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(10) << m_PrimaryIntMatrix.getReverseNIterator(3) << 1 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(13) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(13) << m_PrimaryIntMatrix.reverseNEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(12) << m_PrimaryIntMatrix.reverseNEnd() << 2 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << 1;
    QTest::newRow("{column end iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(3) << m_PrimaryIntMatrix.reverseNColumnEnd(0) << 8 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(3) << m_PrimaryIntMatrix.reverseNColumnEnd(3) << 9 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(3) << m_PrimaryIntMatrix.reverseNColumnEnd(2) << 9 << 2;
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << m_PrimaryIntMatrix.reverseNEnd() << 1 << 2;
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << 1;
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(2) << m_PrimaryIntMatrix.reverseNEnd() << 1 << 3;
    QTest::newRow("{begin iterator, column begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnBegin(2) << 1 << 0;
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

    QTest::addColumn<IntMatrixReverseNIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixReverseNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 5 << m_PrimaryIntMatrix.getReverseNIterator(5);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 6 << m_PrimaryIntMatrix.reverseNColumnBegin(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getReverseNIterator(0, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getReverseNIterator(7);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << -1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 6 << m_PrimaryIntMatrix.reverseNColumnBegin(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << -1 << m_PrimaryIntMatrix.getReverseNIterator(0);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 3 << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << -2 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 11 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getReverseNIterator(0, 1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 0 << m_PrimaryIntMatrix.getReverseNIterator(8);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 7 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -7 << m_PrimaryIntMatrix.getReverseNIterator(0, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -2 << m_PrimaryIntMatrix.getReverseNIterator(11);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << -1 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 11 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << 10 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 0 << m_PrimaryIntMatrix.getReverseNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << -1 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 4 << m_PrimaryIntMatrix.reverseNColumnEnd(1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 11 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(3, 1) << m_PrimaryIntMatrix.reverseNEnd() << 10 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 11 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 2 << m_PrimaryIntMatrix.getReverseNIterator(2, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 9 << m_PrimaryIntMatrix.getReverseNIterator(18);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getReverseNIterator(1, 3);
}

void ReverseNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(2, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseNBegin() << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.reverseNEnd() << m_SecondaryIntMatrix.reverseNBegin();
}

void ReverseNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixReverseNIterator>("inputIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(5, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(5, 5) << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(2, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(1, 5) << m_PrimaryIntMatrix.getReverseNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(0, 5) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(7, 4) << m_PrimaryIntMatrix.getReverseNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.reverseNEnd();
}

void ReverseNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixReverseNIterator>("inputIterator");
    QTest::addColumn<IntMatrixReverseNIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.reverseNEnd() << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(6, 4) << m_PrimaryIntMatrix.getReverseNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(7, 4) << m_PrimaryIntMatrix.getReverseNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(0, 5) << m_PrimaryIntMatrix.getReverseNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(1, 5) << m_PrimaryIntMatrix.getReverseNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << m_PrimaryIntMatrix.getReverseNIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << m_PrimaryIntMatrix.getReverseNIterator(7, 8);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.reverseNBegin() << m_PrimaryIntMatrix.reverseNBegin();
}

void ReverseNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixReverseNIterator>("expectedIterator");

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << 3 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << 1 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << 0 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -1 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -2 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -5 << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -11 << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -71 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -72 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -73 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -75 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 4 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 2 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 1 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 0 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -1 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -4 << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -10 << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -70 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -71 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -72 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << -74 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 5 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 3 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 2 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 1 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 0 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -3 << m_PrimaryIntMatrix.getReverseNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -9 << m_PrimaryIntMatrix.getReverseNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -69 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -70 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -71 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << -73 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 48 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 46 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 45 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 44 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 43 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 6 << m_PrimaryIntMatrix.getReverseNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 2 << m_PrimaryIntMatrix.getReverseNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 0 << m_PrimaryIntMatrix.getReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -2 << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -6 << m_PrimaryIntMatrix.getReverseNIterator(2, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -26 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -27 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -28 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << -30 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 74 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 72 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 71 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 70 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 69 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 24 << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 3 << m_PrimaryIntMatrix.getReverseNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 0 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -1 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -2 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << -4 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 75 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 73 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 72 << m_PrimaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 71 << m_PrimaryIntMatrix.getReverseNIterator(0, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 70 << m_PrimaryIntMatrix.getReverseNIterator(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 25 << m_PrimaryIntMatrix.getReverseNIterator(6, 5);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 4 << m_PrimaryIntMatrix.getReverseNIterator(3, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 1 << m_PrimaryIntMatrix.getReverseNIterator(6, 8);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 0 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << -1 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << -3 << m_PrimaryIntMatrix.reverseNBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseNBegin() << -1 << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseNBegin() << 1 << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << 0 << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << 1 << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << -1 << m_SecondaryIntMatrix.reverseNEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseNIterator{} << -1 << IntMatrixReverseNIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseNIterator{} << 1 << IntMatrixReverseNIterator{};
}

QTEST_APPLESS_MAIN(ReverseNIteratorTests)

#include "tst_reverseniteratortests.moc"
