// clang-format off
#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntWDIter)
Q_DECLARE_METATYPE(StringWDIter)

/*
WDIterator vs. ZIterator indexes for:
- 2x3 matrix:

    0 2 4                               0 1 2
    1 3 5                               3 4 5

- 4x3 matrix:

    0 2 5                               0 1  2
    1 4 8                               3 4  5
    3 7 10                              6 7  8
    6 9 11                              9 10 11

- 4x5 matrix:

     0  2  5  9 13                      0  1  2  3  4
     1  4  8 12 16                      5  6  7  8  9
     3  7 11 15 18                      10 11 12 13 14
     6 10 14 17 19                      15 16 17 18 19

- 9x8 matrix:

     0  2  5  9 14 20 27 35             0  1  2  3  4  5  6  7
     1  4  8 13 19 26 34 43             8  9  10 11 12 13 14 15
     3  7 12 18 25 33 42 50             16 17 18 19 20 21 22 23
     6 11 17 24 32 41 49 56             24 25 26 27 28 29 30 31
    10 16 23 31 40 48 55 61             32 33 34 35 36 37 38 39
    15 22 30 39 47 54 60 65             40 41 42 43 44 45 46 47
    21 29 38 46 53 59 64 68             48 49 50 51 52 53 54 55
    28 37 45 52 58 63 67 70             56 57 58 59 60 61 62 63
    36 44 51 57 62 66 69 71             64 65 66 67 68 69 70 71
*/

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

    IntWDIter m_PrimaryIntIterator;
    IntWDIter m_SecondaryIntIterator;
    StringWDIter m_StringIterator;
};

void WDIteratorTests::testIteratorCreation()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(IntWDIter, beginIterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    QFETCH(matrix_diff_t, expectedDistance);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             std::distance(beginIterator, iterator) == expectedDistance,
             "The iterator has not been correctly created!");
}

void WDIteratorTests::testEmptyIterator()
{
    IntWDIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() &&
             !emptyIt.getColumnNr().has_value() &&
             std::distance(emptyIt, emptyIt) == 0,
             "The iterator has not been correctly created!");

    IntWDIter anotherEmptyIt;

    QVERIFY(std::distance(emptyIt, anotherEmptyIt) == 0);
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

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(8, 1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(6, 3) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(6, 3),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(8, 1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(8, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(8, 1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(6, 3) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(8, 1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2),
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

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(6, 3);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(8, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(8, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(6, 3);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(6, 3),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(6, 3);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(8, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(6, 3);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getWDIterator(7, 2),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void WDIteratorTests::testOperatorPlus()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntWDIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void WDIteratorTests::testOperatorMinus()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntWDIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void WDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntWDIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void WDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntWDIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void WDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntWDIter, firstIterator);
    QFETCH(IntWDIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void WDIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void WDIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_SecondaryIntMatrix = {4, 3, {1, -20, -6, -2, -20, -20, -20, -20, 11, -20, -20, -12}};
    *m_PrimaryIntMatrix.wdBegin() = 1;
    *m_PrimaryIntMatrix.getWDIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getWDIterator(0, 2) = -6;
    *m_PrimaryIntMatrix.getWDIterator(2, 2) = 11;
    *m_PrimaryIntMatrix.getWDIterator(3, 2) = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 3);
    *m_PrimaryIntMatrix.wdBegin() = 1;
    *m_PrimaryIntMatrix.getWDIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getWDIterator(0, 2) = -6;
    *m_PrimaryIntMatrix.getWDIterator(2, 2) = 11;
    *m_PrimaryIntMatrix.getWDIterator(3, 2) = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");
}

void WDIteratorTests::testAsteriskOperatorReadWrite()
{
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 1) == 10);

    // test with column capacity offset

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 1) == 10);
}

void WDIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringWDIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void WDIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {{4, 3}, "zzz"};
    m_SecondaryStringMatrix = {4, 3, {"abc", "zzz", "gfedcba", "ba", "zzz", "zzz", "zzz", "zzz", "abcdefghijk", "zzz", "zzz", "fedcba"}};
    m_PrimaryStringMatrix.wdBegin()->assign("abc");
    m_PrimaryStringMatrix.getWDIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getWDIterator(0, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getWDIterator(2, 2)->assign("abcdefghijk");
    m_PrimaryStringMatrix.getWDIterator(3, 2)->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryStringMatrix = {{4, 3}, "zzz"};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_PrimaryStringMatrix.wdBegin()->assign("abc");
    m_PrimaryStringMatrix.getWDIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getWDIterator(0, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getWDIterator(2, 2)->assign("abcdefghijk");
    m_PrimaryStringMatrix.getWDIterator(3, 2)->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");
}

void WDIteratorTests::testArrowOperatorReadWrite()
{
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.wdBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.wdBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 1) == "abcdefghi");

    // test with row/column capacity offset

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_StringIterator = m_PrimaryStringMatrix.wdBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_StringIterator = m_PrimaryStringMatrix.wdBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 1) == "abcdefghi");
}

void WDIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntWDIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void WDIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {4, 3, {1, -20, -6, -2, -20, -20, -20, -20, 11, -20, -20, -12}};

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[1] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[10] = 11;
    m_PrimaryIntIterator[11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(1, 0);
    m_PrimaryIntIterator[-1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[4] = -6;
    m_PrimaryIntIterator[9] = 11;
    m_PrimaryIntIterator[10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(0, 2);
    m_PrimaryIntIterator[-5] = 1;
    m_PrimaryIntIterator[-4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[5] = 11;
    m_PrimaryIntIterator[6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(2, 2);
    m_PrimaryIntIterator[-10] = 1;
    m_PrimaryIntIterator[-9] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 2);
    m_PrimaryIntIterator[-11] = 1;
    m_PrimaryIntIterator[-10] = -2;
    m_PrimaryIntIterator[-6] = -6;
    m_PrimaryIntIterator[-1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[1] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[10] = 11;
    m_PrimaryIntIterator[11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(0, 2);
    m_PrimaryIntIterator[-5] = 1;
    m_PrimaryIntIterator[-4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[5] = 11;
    m_PrimaryIntIterator[6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {{4, 3}, -20};
    m_PrimaryIntMatrix.reserve(4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getWDIterator(3, 2);
    m_PrimaryIntIterator[-11] = 1;
    m_PrimaryIntIterator[-10] = -2;
    m_PrimaryIntIterator[-6] = -6;
    m_PrimaryIntIterator[-1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void WDIteratorTests::testStdCount()
{
    QFETCH(IntWDIter, leftIterator);
    QFETCH(IntWDIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void WDIteratorTests::testStdFind()
{
    QFETCH(IntWDIter, leftIterator);
    QFETCH(IntWDIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntWDIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void WDIteratorTests::testStdFindWithIncrementAndCount()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  1, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.wdBegin(), m_PrimaryIntMatrix.wdEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.wdBegin(), m_PrimaryIntMatrix.wdEnd(), 10) == m_PrimaryIntMatrix.wdEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.wdBegin();

    while(m_PrimaryIntIterator != m_PrimaryIntMatrix.wdEnd())
    {
        m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.wdEnd(), 9);

        if (m_PrimaryIntIterator != m_PrimaryIntMatrix.wdEnd())
        {
            *m_PrimaryIntIterator = 10;
        }
    }

    QVERIFY2(std::count(m_PrimaryIntMatrix.wdBegin(), m_PrimaryIntMatrix.wdEnd(), 10) == 3,
             "The iterator doesn't work properly with std::find, element values haven't been correctly replaced!");
}


void WDIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                               -7, -1, 1, 3, 7,
                               -2,  1, 2, 6, 9,
                                0,  2, 5, 8, 9,
                                2,  4, 8, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.wdBegin(), m_PrimaryIntMatrix.wdEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                              -1, 3,  5, -2, 6,
                               1, 4, -7,  2, 7,
                               1, 8,  2,  9, 9,
                               9, 0,  8,  2, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getWDIterator(1, 2), m_PrimaryIntMatrix.getWDIterator(1, 4));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                              -1, 1,  3,  8, 8,
                               0, 2,  6,  2, 7,
                               1, 5, -2, -7, 9,
                               4, 9,  9,  2, 11
                            }};

    std::sort(m_PrimaryIntMatrix.wdBegin(), m_PrimaryIntMatrix.getWDIterator(2, 2));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 2,
                               1, 4,  0, -2, 8,
                               1, 8, -7,  7, 9,
                               9, 2,  2,  9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getWDIterator(2, 2), m_PrimaryIntMatrix.wdEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

void WDIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("iterator");
    QTest::addColumn<IntWDIter>("beginIterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_diff_t>("expectedDistance");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{0};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{9u} << matrix_opt_size_t{8u} << matrix_diff_t{72};
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 0) << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{0};
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{1};
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{8u} << matrix_opt_size_t{1u} << matrix_diff_t{44};
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{7u} << matrix_opt_size_t{7u} << matrix_diff_t{70};
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdBegin() << matrix_opt_size_t{8u} << matrix_opt_size_t{7u} << matrix_diff_t{71};
    QTest::newRow("8: begin iterator") << m_SecondaryIntMatrix.wdBegin() << m_SecondaryIntMatrix.wdBegin() << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0};
    QTest::newRow("9: end iterator") << m_SecondaryIntMatrix.wdEnd() << m_SecondaryIntMatrix.wdBegin() << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0};
}

void WDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 0) << m_PrimaryIntMatrix.getWDIterator(0, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(7, 7);
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
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7);
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

void WDIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void WDIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void WDIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void WDIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void WDIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{1};
    QTest::newRow("3: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{2};
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{28};
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{71};
    QTest::newRow("6: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{72};
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{1};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{27};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{70};
    QTest::newRow("12: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{71};
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-2};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-1};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{26};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{69};
    QTest::newRow("18: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{70};
    QTest::newRow("19: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-28};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-27};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-26};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{43};
    QTest::newRow("24: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{44};
    QTest::newRow("25: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-69};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-43};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{0};
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{1};
    QTest::newRow("31: end iterator, begin iterator") << m_PrimaryIntMatrix.wdEnd() << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-72};
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-71};
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-70};
    QTest::newRow("34: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-44};
    QTest::newRow("35: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-1};
    QTest::newRow("36: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 4) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(7, 4) << matrix_diff_t{14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 6) << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(2, 6) << matrix_diff_t{-2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.wdBegin() << m_SecondaryIntMatrix.wdEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.wdEnd() << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.wdBegin() << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.wdEnd() << m_SecondaryIntMatrix.wdEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntWDIter{} << IntWDIter{} << matrix_diff_t{0};
}

void WDIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntWDIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.wdBegin() << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << -4;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << 3;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << 9;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(6, 5);

    QTest::newRow("6: begin iterator") << m_SecondaryIntMatrix.wdBegin() << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << -4;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << 3;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << 9;
    QTest::newRow("10: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << -12;
}

void WDIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringWDIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.wdBegin() << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getWDIterator(1, 0) << 10;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getWDIterator(0, 2) << 4;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getWDIterator(2, 2) << 8;
    QTest::newRow("5: random iterator") << m_PrimaryStringMatrix.getWDIterator(3, 2) << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(6, 3);

    QTest::newRow("6: begin iterator") << m_SecondaryStringMatrix.wdBegin() << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getWDIterator(1, 0) << 10;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getWDIterator(0, 2) << 4;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getWDIterator(2, 2) << 8;
    QTest::newRow("10: random iterator") << m_SecondaryStringMatrix.getWDIterator(3, 2) << 6;
}

void WDIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntWDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{0} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{1} << -4;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{5} << 3;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{10} << 9;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{11} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-1} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{0} << -4;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{4} << 3;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{9} << 9;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{10} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{-5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{-4} << -4;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{0} << 3;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{5} << 9;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-10} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-9} << -4;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-5} << 3;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{0} << 9;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{1} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-11} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-10} << -4;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-6} << 3;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-1} << 9;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{0} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{0} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{1} << -4;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{5} << 3;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{10} << 9;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{11} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-1} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{0} << -4;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{4} << 3;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{9} << 9;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{10} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{-5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{-4} << -4;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{0} << 3;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{5} << 9;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getWDIterator(0, 2) << matrix_diff_t{6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-10} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-9} << -4;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{-5} << 3;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{0} << 9;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getWDIterator(2, 2) << matrix_diff_t{1} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-11} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-10} << -4;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-6} << 3;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{-1} << 9;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getWDIterator(3, 2) << matrix_diff_t{0} << -12;
}

void WDIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  1, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 8
                          }};

    QTest::addColumn<IntWDIter>("leftIterator");
    QTest::addColumn<IntWDIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 0) << m_PrimaryIntMatrix.getWDIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(2, 0) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 4) << 2 << matrix_diff_t{2};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 4) << m_PrimaryIntMatrix.wdEnd() << 2 << matrix_diff_t{1};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 3) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 3) << m_PrimaryIntMatrix.wdEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 1 << matrix_diff_t{1};
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(2, 3) << 8 << matrix_diff_t{2};
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(3, 1) << m_PrimaryIntMatrix.getWDIterator(2, 3) << 9 << matrix_diff_t{1};
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(3, 1) << m_PrimaryIntMatrix.wdEnd() << 9 << matrix_diff_t{2};
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << 1 << matrix_diff_t{1};
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << 1 << matrix_diff_t{3};
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(3, 1) << m_PrimaryIntMatrix.wdEnd() << 1 << matrix_diff_t{0};
}

void WDIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 3,  5,  6, 8,
                               1, 4,  0,  2, 7,
                               1, 8, -2, -7, 9,
                               9, 2,  9,  2, 11
                          }};

    QTest::addColumn<IntWDIter>("leftIterator");
    QTest::addColumn<IntWDIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntWDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdEnd() << 5 << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdEnd() << 10 << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 5 << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 6 << m_PrimaryIntMatrix.getWDIterator(0, 3);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 8 << m_PrimaryIntMatrix.getWDIterator(2, 1);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << -1 << m_PrimaryIntMatrix.getWDIterator(3, 1);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << -2 << m_PrimaryIntMatrix.getWDIterator(3, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.getWDIterator(3, 1) << 10 << m_PrimaryIntMatrix.getWDIterator(3, 1);
    QTest::newRow("9: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << 5 << m_PrimaryIntMatrix.getWDIterator(0, 2);
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << 11 << m_PrimaryIntMatrix.getWDIterator(3, 4);
    QTest::newRow("11: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << -2 << m_PrimaryIntMatrix.getWDIterator(2, 2);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << -1 << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(0, 2) << m_PrimaryIntMatrix.wdEnd() << 10 << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("14: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << -1 << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << 6 << m_PrimaryIntMatrix.getWDIterator(0, 3);
    QTest::newRow("16: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << 8 << m_PrimaryIntMatrix.getWDIterator(2, 1);
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << -2 << m_PrimaryIntMatrix.getWDIterator(3, 1);
    QTest::newRow("18: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(3, 1) << 10 << m_PrimaryIntMatrix.getWDIterator(3, 1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << 0 << m_PrimaryIntMatrix.getWDIterator(1, 2);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << -7 << m_PrimaryIntMatrix.getWDIterator(2, 3);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << -2 << m_PrimaryIntMatrix.getWDIterator(2, 2);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << -1 << m_PrimaryIntMatrix.getWDIterator(1, 4);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << 11 << m_PrimaryIntMatrix.getWDIterator(1, 4);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.getWDIterator(1, 4) << 10 << m_PrimaryIntMatrix.getWDIterator(1, 4);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.wdEnd() << 0 << m_PrimaryIntMatrix.getWDIterator(1, 2);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.wdEnd() << 11 << m_PrimaryIntMatrix.getWDIterator(3, 4);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.wdEnd() << -2 << m_PrimaryIntMatrix.getWDIterator(2, 2);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.wdEnd() << -1 << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 2) << m_PrimaryIntMatrix.wdEnd() << 10 << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 4) << -1 << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 4) << -7 << m_PrimaryIntMatrix.getWDIterator(2, 3);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 4) << -2 << m_PrimaryIntMatrix.getWDIterator(2, 2);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 4) << 11 << m_PrimaryIntMatrix.getWDIterator(1, 4);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 4) << 10 << m_PrimaryIntMatrix.getWDIterator(1, 4);
}

void WDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << m_PrimaryIntMatrix.wdEnd();
}

void WDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("firstIterator");
    QTest::addColumn<IntWDIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(0, 1);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << m_PrimaryIntMatrix.getWDIterator(8, 7);
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
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(6, 2) << m_PrimaryIntMatrix.getWDIterator(5, 3);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(5, 3) << m_PrimaryIntMatrix.getWDIterator(4, 4);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(4, 4) << m_PrimaryIntMatrix.getWDIterator(3, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(3, 5) << m_PrimaryIntMatrix.getWDIterator(2, 6);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(8, 1) << m_PrimaryIntMatrix.getWDIterator(7, 2);
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
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(7, 2) << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(2, 6) << m_PrimaryIntMatrix.getWDIterator(3, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(3, 5) << m_PrimaryIntMatrix.getWDIterator(4, 4);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(4, 4) << m_PrimaryIntMatrix.getWDIterator(5, 3);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(5, 3) << m_PrimaryIntMatrix.getWDIterator(6, 2);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getWDIterator(0, 1) << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getWDIterator(1, 0) << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.wdBegin() << m_PrimaryIntMatrix.wdBegin();
}

void WDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntWDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntWDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("3: begin iterator, begin iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("4: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("5: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getWDIterator(1, 1);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{10} << m_PrimaryIntMatrix.getWDIterator(4, 0);
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("8: begin iterator, random iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("9: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("10: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("11: begin iterator, end iterator") << m_PrimaryIntMatrix.wdBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("12: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("13: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-2} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("14: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{3} << m_PrimaryIntMatrix.getWDIterator(1, 1);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{9} << m_PrimaryIntMatrix.getWDIterator(4, 0);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{69} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{70} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("20: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{71} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("21: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{72} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("22: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(1, 0) << matrix_diff_t{74} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("23: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-47} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("24: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-45} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("25: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-44} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-43} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getWDIterator(6, 2);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getWDIterator(2, 6);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{0} << m_PrimaryIntMatrix.getWDIterator(8, 1);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) <<  matrix_diff_t{2} << m_PrimaryIntMatrix.getWDIterator(6, 3);
    QTest::newRow("31: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{6} << m_PrimaryIntMatrix.getWDIterator(2, 7);
    QTest::newRow("32: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{26} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("33: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{27} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{28} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{29} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 1) << matrix_diff_t{31} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("37: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-73} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("38: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-71} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("39: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-70} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-24} << m_PrimaryIntMatrix.getWDIterator(6, 3);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getWDIterator(7, 6);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{0} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{1} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("45: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{2} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("46: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{3} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("47: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(7, 7) << matrix_diff_t{5} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("48: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-74} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("49: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-72} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("50: random iterator, begin iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-71} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-25} << m_PrimaryIntMatrix.getWDIterator(6, 3);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getWDIterator(7, 6);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{0} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("56: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{1} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("57: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{2} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("58: random iterator, end iterator") << m_PrimaryIntMatrix.getWDIterator(8, 7) << matrix_diff_t{4} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("59: end iterator, begin iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("60: end iterator, begin iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("61: end iterator, begin iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.wdBegin();
    QTest::newRow("62: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getWDIterator(1, 0);
    QTest::newRow("63: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-26} << m_PrimaryIntMatrix.getWDIterator(6, 3);
    QTest::newRow("64: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getWDIterator(7, 6);
    QTest::newRow("65: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getWDIterator(7, 7);
    QTest::newRow("66: end iterator, random iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getWDIterator(8, 7);
    QTest::newRow("67: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("68: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("69: end iterator, end iterator") << m_PrimaryIntMatrix.wdEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.wdEnd();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.wdBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.wdEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.wdEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.wdEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.wdEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntWDIter{} << matrix_diff_t{-1} << IntWDIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntWDIter{} << matrix_diff_t{1} << IntWDIter{};
}

QTEST_APPLESS_MAIN(WDIteratorTests)

#include "tst_wditeratortests.moc"
// clang-format on
