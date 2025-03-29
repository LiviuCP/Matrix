#include <QtTest>
#include <cmath>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixZIterator)
Q_DECLARE_METATYPE(StringMatrixZIterator)

class ZIteratorTests : public QObject
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
    void testAutoWithLocalCopyRead(); // "auto" syntax tested for non-const matrixes (this is where ZIterators apply)
    void testAutoWithLocalCopyWrite();
    void testAutoWithReference();
    void testConstAutoWithLocalCopy();
    void testConstAutoWithReference();
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

    IntMatrixZIterator m_PrimaryIntIterator;
    IntMatrixZIterator m_SecondaryIntIterator;
    StringMatrixZIterator m_StringIterator;
};

void ZIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixOptSizeType, expectedRowNr);
    QFETCH(IntMatrixOptSizeType, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixZIterator emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixZIterator, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ZIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ZIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixZIterator, inputIterator);
    QFETCH(IntMatrixZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixZIterator, inputIterator);
    QFETCH(IntMatrixZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 4);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 6),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 4),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 4);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 4);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixZIterator, inputIterator);
    QFETCH(IntMatrixZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixZIterator, inputIterator);
    QFETCH(IntMatrixZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 6);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 4),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 6),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 6);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(5, 6);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ZIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixZIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ZIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixZIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixZIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixZIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixZIterator, firstIterator);
    QFETCH(IntMatrixZIterator, secondIterator);
    QFETCH(IntMatrixDiffType, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ZIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ZIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {4, 3, -20};
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};
    *m_PrimaryIntMatrix.zBegin() = 1;
    *m_PrimaryIntMatrix.getZIterator(0, 1) = -2;
    *m_PrimaryIntMatrix.getZIterator(1, 2) = -6;
    *m_PrimaryIntMatrix.getZIterator(3, 1) = 11;
    *m_PrimaryIntMatrix.getZIterator(3, 2) = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    *m_PrimaryIntMatrix.zBegin() = 1;
    *m_PrimaryIntMatrix.getZIterator(0, 1) = -2;
    *m_PrimaryIntMatrix.getZIterator(1, 2) = -6;
    *m_PrimaryIntMatrix.getZIterator(3, 1) = 11;
    *m_PrimaryIntMatrix.getZIterator(3, 2) = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");
}

void ZIteratorTests::testAsteriskOperatorReadWrite()
{
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 2) == 10);

    // test with column capacity offset

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(0, 2) == 10);
}

void ZIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringMatrixZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ZIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {4, 3, "zzz"};
    m_SecondaryStringMatrix = {4, 3, {"abc", "ba","zzz","zzz","zzz","gfedcba","zzz","zzz","zzz","zzz","abcdefghijk","fedcba"}};
    m_PrimaryStringMatrix.zBegin()->assign("abc");
    m_PrimaryStringMatrix.getZIterator(0, 1)->assign("ba");
    m_PrimaryStringMatrix.getZIterator(1, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getZIterator(3, 1)->assign("abcdefghijk");
    m_PrimaryStringMatrix.getZIterator(3, 2)->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");

    // test with column capacity offset
    m_PrimaryStringMatrix = {4, 3, "zzz"};
    m_PrimaryStringMatrix.resize(4, 3, 4, 5);
    m_PrimaryStringMatrix.zBegin()->assign("abc");
    m_PrimaryStringMatrix.getZIterator(0, 1)->assign("ba");
    m_PrimaryStringMatrix.getZIterator(1, 2)->assign("gfedcba");
    m_PrimaryStringMatrix.getZIterator(3, 1)->assign("abcdefghijk");
    m_PrimaryStringMatrix.getZIterator(3, 2)->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");
}

void ZIteratorTests::testArrowOperatorReadWrite()
{
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.zBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.zBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 2) == "abcdefghi");

    // test with row/column capacity offset

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.resize(2, 3, 4, 5);
    m_StringIterator = m_PrimaryStringMatrix.zBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.resize(2, 3, 4, 5);
    m_StringIterator = m_PrimaryStringMatrix.zBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(0, 2) == "abcdefghi");
}

void ZIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ZIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[1] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[10] = 11;
    m_PrimaryIntIterator[11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(0, 1);
    m_PrimaryIntIterator[-1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[4] = -6;
    m_PrimaryIntIterator[9] = 11;
    m_PrimaryIntIterator[10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(1, 2);
    m_PrimaryIntIterator[-5] = 1;
    m_PrimaryIntIterator[-4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[5] = 11;
    m_PrimaryIntIterator[6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(3, 1);
    m_PrimaryIntIterator[-10] = 1;
    m_PrimaryIntIterator[-9] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(3, 2);
    m_PrimaryIntIterator[-11] = 1;
    m_PrimaryIntIterator[-10] = -2;
    m_PrimaryIntIterator[-6] = -6;
    m_PrimaryIntIterator[-1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntMatrix.resize(4, 3, 6, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[1] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[10] = 11;
    m_PrimaryIntIterator[11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(1, 2);
    m_PrimaryIntIterator[-5] = 1;
    m_PrimaryIntIterator[-4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[5] = 11;
    m_PrimaryIntIterator[6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    // test with column capacity offset
    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntMatrix.resize(4, 3, 4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getZIterator(3, 2);
    m_PrimaryIntIterator[-11] = 1;
    m_PrimaryIntIterator[-10] = -2;
    m_PrimaryIntIterator[-6] = -6;
    m_PrimaryIntIterator[-1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ZIteratorTests::testAutoWithLocalCopyRead()
{
    m_PrimaryIntMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

    int sum{0}, product{1};
    size_t count{0};

    for (auto element : m_PrimaryIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using auto (read) does not work correctly!");

    m_PrimaryIntMatrix.clear();

    for (auto element : m_PrimaryIntMatrix)
    {
        Q_UNUSED(element);
        ++count;
    }

    QVERIFY(count == 6);
}

void ZIteratorTests::testAutoWithLocalCopyWrite()
{
    m_PrimaryIntMatrix = {2, 3, {-1, 2, 3, 4, -5, 6}};
    m_SecondaryIntMatrix = {2, 3, {-1, 2, 3, 4, -5, 6}};

    int sum{0};
    size_t count{0};

    for (auto element : m_PrimaryIntMatrix)
    {
        element = std::abs(element);
        sum += element;
        ++count;
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix && sum == 21 && count == 6, "Iterating through the matrix elements by using auto (write) does not work correctly!");

    m_PrimaryIntMatrix.clear();

    for (auto element : m_PrimaryIntMatrix)
    {
        Q_UNUSED(element);
        ++count;
    }

    QVERIFY(count == 6);
}

void ZIteratorTests::testAutoWithReference()
{
    m_PrimaryIntMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};
    m_SecondaryIntMatrix = {2, 3, {1, 2, 3, 4, 5, 6}};

    size_t count{0};

    for (auto& element : m_PrimaryIntMatrix)
    {
        element = std::abs(element);
        ++count;
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix && count == 6, "Iterating through the matrix elements by using auto& does not work correctly!");

    m_PrimaryIntMatrix.clear();

    for (auto& element : m_PrimaryIntMatrix)
    {
        Q_UNUSED(element);
        ++count;
    }

    QVERIFY(count == 6);
}

void ZIteratorTests::testConstAutoWithLocalCopy()
{
    m_PrimaryIntMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

    int sum{0}, product{1};
    size_t count{0};

    for (const auto element : m_PrimaryIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using const auto does not work correctly!");

    m_PrimaryIntMatrix.clear();

    for (const auto element : m_PrimaryIntMatrix)
    {
        Q_UNUSED(element);
        ++count;
    }

    QVERIFY(count == 6);
}

void ZIteratorTests::testConstAutoWithReference()
{
    m_PrimaryIntMatrix = {2, 3, {-1, 2, -3, 4, -5, 6}};

    int sum{0}, product{1};
    size_t count{0};

    for (const auto& element : m_PrimaryIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using const auto& does not work correctly!");

    m_PrimaryIntMatrix.clear();

    for (const auto& element : m_PrimaryIntMatrix)
    {
        Q_UNUSED(element);
        ++count;
    }

    QVERIFY(count == 6);
}

void ZIteratorTests::testStdCount()
{
    QFETCH(IntMatrixZIterator, leftIterator);
    QFETCH(IntMatrixZIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ZIteratorTests::testStdFind()
{
    QFETCH(IntMatrixZIterator, leftIterator);
    QFETCH(IntMatrixZIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixZIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ZIteratorTests::testStdFindWithIncrementAndCount()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.zBegin(), m_PrimaryIntMatrix.zEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.zBegin(), m_PrimaryIntMatrix.zEnd(), 10) == m_PrimaryIntMatrix.zEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.zBegin();

    while(m_PrimaryIntIterator != m_PrimaryIntMatrix.zEnd())
    {
        m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.zEnd(), 9);

        if (m_PrimaryIntIterator != m_PrimaryIntMatrix.zEnd())
        {
            *m_PrimaryIntIterator = 10;
        }
    }

    QVERIFY2(std::count(m_PrimaryIntMatrix.zBegin(), m_PrimaryIntMatrix.zEnd(), 10) == 3,
             "The iterator doesn't work properly with std::find, element values haven't been correctly replaced!");
}

void ZIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                                -1, 1, 1, 3, 4,
                                 0, 5, 6, 8, 9,
                                -2, 2, 2, 8, 9,
                                -7, 2, 7, 9, 11
                            }};

    for (auto row{0}; row < m_PrimaryIntMatrix.getNrOfRows(); ++row)
    {
        std::sort(m_PrimaryIntMatrix.zRowBegin(row), m_PrimaryIntMatrix.zRowEnd(row));
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                               -7, -2, -1, 0, 1,
                                1, 2, 2, 2, 3,
                                4, 5, 6, 7, 8,
                                8, 9, 9, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.zBegin(), m_PrimaryIntMatrix.zEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                               -1, 1, 3, 1, 4,
                                5, 9, 8, -7, -2,
                                0, 2, 2, 6, 8,
                                9, 7, 2, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getZIterator(1, 3), m_PrimaryIntMatrix.getZIterator(3, 1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {4, 5, {
                             -1, 1, 3, 1, 4,
                              5, 9, 8, 0, 6,
                              2, -2, 2, 8, 9,
                             -7, 7, 2, 9, 11
                          }};

    m_SecondaryIntMatrix = {4, 5, {
                               -1, 0, 1, 1, 2,
                                3, 4, 5, 6, 8,
                                9, -2, 2, 8, 9,
                               -7, 7, 2, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.zBegin(), m_PrimaryIntMatrix.getZIterator(2, 1));

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
                                2, -7, -2, 2, 2,
                                7, 8, 9, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getZIterator(2, 1), m_PrimaryIntMatrix.zEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

void ZIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.zEnd() << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(1) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(4) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(7) << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.zRowEnd(0) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.zRowEnd(1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.zRowEnd(4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.zRowEnd(7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.zRowEnd(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getZIterator(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getZIterator(1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getZIterator(44) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getZIterator(70) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getZIterator(71) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.zBegin() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.zEnd() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
}

void ZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("firstIterator");
    QTest::addColumn<IntMatrixZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0) << m_PrimaryIntMatrix.getZIterator(0, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1) << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(44) << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(70) << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(71) << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("7: row begin iterator, random iterator") << m_PrimaryIntMatrix.zRowBegin(0) << m_PrimaryIntMatrix.getZIterator(0, 0);
    QTest::newRow("8: row begin iterator, random iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.getZIterator(1, 0);
    QTest::newRow("9: row begin iterator, random iterator") << m_PrimaryIntMatrix.zRowBegin(5) << m_PrimaryIntMatrix.getZIterator(5, 0);
    QTest::newRow("10: row begin iterator, random iterator") << m_PrimaryIntMatrix.zRowBegin(7) << m_PrimaryIntMatrix.getZIterator(7, 0);
    QTest::newRow("11: row begin iterator, random iterator") << m_PrimaryIntMatrix.zRowBegin(8) << m_PrimaryIntMatrix.getZIterator(8, 0);
    QTest::newRow("12: row end iterator, random iterator") << m_PrimaryIntMatrix.zRowEnd(0) << m_PrimaryIntMatrix.getZIterator(1, 0);
    QTest::newRow("13: row end iterator, random iterator") << m_PrimaryIntMatrix.zRowEnd(1) << m_PrimaryIntMatrix.getZIterator(2, 0);
    QTest::newRow("14: row end iterator, random iterator") << m_PrimaryIntMatrix.zRowEnd(5) << m_PrimaryIntMatrix.getZIterator(6, 0);
    QTest::newRow("15: row end iterator, random iterator") << m_PrimaryIntMatrix.zRowEnd(7) << m_PrimaryIntMatrix.getZIterator(8, 0);
    QTest::newRow("16: row end iterator, end iterator") << m_PrimaryIntMatrix.zRowEnd(8) << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.zEnd();
}

void ZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixZIterator>("iterator");

    QTest::newRow("1: begin iterator")  << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 0);
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("7: end iterator")  << m_PrimaryIntMatrix.zEnd();
}

void ZIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ZIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ZIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ZIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ZIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ZIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ZIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ZIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ZIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ZIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ZIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ZIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ZIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ZIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("firstIterator");
    QTest::addColumn<IntMatrixZIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.zEnd() << 0;
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.zEnd() << 1;
    QTest::newRow("3: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.zEnd() << 2;
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.zEnd() << 28;
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.zEnd() << 71;
    QTest::newRow("6: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zEnd() << 72;
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.getZIterator(8, 7) << -1;
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(8, 7) << 0;
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 7) << 1;
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(8, 7) << 27;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(8, 7) << 70;
    QTest::newRow("12: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(8, 7) << 71;
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.getZIterator(8, 6) << -2;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(8, 6) << -1;
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 6) << 0;
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(8, 6) << 26;
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(8, 6) << 69;
    QTest::newRow("18: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(8, 6) << 70;
    QTest::newRow("19: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.getZIterator(5, 4) << -28;
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(5, 4) << -27;
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(5, 4) << -26;
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(5, 4) << 0;
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(5, 4) << 43;
    QTest::newRow("24: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(5, 4) << 44;
    QTest::newRow("25: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.getZIterator(0, 1) << -71;
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(0, 1) << -70;
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(0, 1) << -69;
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(0, 1) << -43;
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(0, 1) << 0;
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(0, 1) << 1;
    QTest::newRow("31: end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.zBegin() << -72;
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.zBegin() << -71;
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.zBegin() << -70;
    QTest::newRow("34: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.zBegin() << -44;
    QTest::newRow("35: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.zBegin() << -1;
    QTest::newRow("36: begin iterator, begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zBegin() << 0;
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(7, 2) << m_PrimaryIntMatrix.getZIterator(5, 4) << -14;
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(7, 2) << 14;
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 2) << m_PrimaryIntMatrix.getZIterator(5, 4) << 2;
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(5, 2) << -2;
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.zEnd() << 0;
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.zBegin() << 0;
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.zBegin() << 0;
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.zEnd() << 0;
    QTest::newRow("45: empty iterator, empty iterator") << IntMatrixZIterator{} << IntMatrixZIterator{} << 0;
}

void ZIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("6: begin iterator") << m_SecondaryIntMatrix.zBegin() << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << -12;
}

void ZIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringMatrixZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.zBegin() << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getZIterator(0, 1) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getZIterator(1, 2) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getZIterator(3, 1) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryStringMatrix.getZIterator(3, 2) << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.resize(4, 3, 6, 3);

    QTest::newRow("6: begin iterator") << m_SecondaryStringMatrix.zBegin() << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getZIterator(0, 1) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getZIterator(1, 2) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getZIterator(3, 1) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryStringMatrix.getZIterator(3, 2) << 6;
}

void ZIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << 0 << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.zBegin() << 1 << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.zBegin() << 5 << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.zBegin() << 10 << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.zBegin() << 11 << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << -1 << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 0 << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 4 << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 9 << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 10 << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << -5 << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << -4 << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << 0 << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << 5 << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getZIterator(1, 2) << 6 << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << -10 << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << -9 << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << -5 << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << 0 << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 1) << 1 << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << -11 << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << -10 << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << -6 << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << -1 << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getZIterator(3, 2) << 0 << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.zBegin() << 0 << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.zBegin() << 1 << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.zBegin() << 5 << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.zBegin() << 10 << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.zBegin() << 11 << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << -1 << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << 0 << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << 4 << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << 9 << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getZIterator(0, 1) << 10 << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << -5 << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << -4 << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << 0 << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << 5 << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getZIterator(1, 2) << 6 << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << -10 << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << -9 << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << -5 << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << 0 << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 1) << 1 << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << -11 << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << -10 << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << -6 << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << -1 << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getZIterator(3, 2) << 0 << -12;
}

void ZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    QTest::addColumn<IntMatrixZIterator>("leftIterator");
    QTest::addColumn<IntMatrixZIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zEnd() << 2 << 3;
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zEnd() << -5 << 0;
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(1, 4) << 1 << 1;
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(2, 0) << 1 << 2;
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 3) << m_PrimaryIntMatrix.getZIterator(1, 4) << 1 << 1;
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 3) << m_PrimaryIntMatrix.getZIterator(2, 0) << 1 << 2;
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(2, 3) << 2 << 2;
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(2, 3) << m_PrimaryIntMatrix.zEnd() << 2 << 1;
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(2, 2) << 2 << 1;
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(2, 2) << m_PrimaryIntMatrix.zEnd() << 2 << 2;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(2) << m_PrimaryIntMatrix.getZIterator(9) << 1 << 1;
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(2) << m_PrimaryIntMatrix.getZIterator(10) << 1 << 2;
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(3) << m_PrimaryIntMatrix.getZIterator(9) << 1 << 1;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(3) << m_PrimaryIntMatrix.getZIterator(10) << 1 << 2;
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(13) << 2 << 2;
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(13) << m_PrimaryIntMatrix.zEnd() << 2 << 1;
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(12) << 2 << 1;
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(12) << m_PrimaryIntMatrix.zEnd() << 2 << 2;
    QTest::newRow("19: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << 1 << 1;
    QTest::newRow("20: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(2) << 8 << 2;
    QTest::newRow("21: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(2) << m_PrimaryIntMatrix.zRowEnd(2) << 9 << 1;
    QTest::newRow("22: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(2) << m_PrimaryIntMatrix.zRowEnd(3) << 9 << 2;
    QTest::newRow("23: begin iterator, row begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowBegin(1) << 1 << 2;
    QTest::newRow("24: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << 1 << 1;
    QTest::newRow("25: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << 1 << 3;
    QTest::newRow("26: row end iterator, end iterator") << m_PrimaryIntMatrix.zRowEnd(1) << m_PrimaryIntMatrix.zEnd() << 1 << 0;
}

void ZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    QTest::addColumn<IntMatrixZIterator>("leftIterator");
    QTest::addColumn<IntMatrixZIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zEnd() << 5 << m_PrimaryIntMatrix.zRowBegin(1);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zEnd() << 10 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("3: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << 5 << m_PrimaryIntMatrix.zRowBegin(1);
    QTest::newRow("4: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << 6 << m_PrimaryIntMatrix.getZIterator(1, 4);
    QTest::newRow("5: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << 8 << m_PrimaryIntMatrix.getZIterator(1, 2);
    QTest::newRow("6: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << -1 << m_PrimaryIntMatrix.zRowEnd(1);
    QTest::newRow("7: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << -2 << m_PrimaryIntMatrix.zRowEnd(1);
    QTest::newRow("8: row begin iterator, row end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zRowEnd(1) << 10 << m_PrimaryIntMatrix.zRowEnd(1);
    QTest::newRow("9: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << 5 << m_PrimaryIntMatrix.zRowBegin(1);
    QTest::newRow("10: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << 11 << m_PrimaryIntMatrix.getZIterator(19);
    QTest::newRow("11: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << -2 << m_PrimaryIntMatrix.getZIterator(2, 1);
    QTest::newRow("12: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << -1 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("13: row begin iterator, end iterator") << m_PrimaryIntMatrix.zRowBegin(1) << m_PrimaryIntMatrix.zEnd() << 10 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("14: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << -1 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("15: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << 6 << m_PrimaryIntMatrix.getZIterator(9);
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << 8 << m_PrimaryIntMatrix.getZIterator(1, 2);
    QTest::newRow("17: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << -2 << m_PrimaryIntMatrix.zRowEnd(1);
    QTest::newRow("18: begin iterator, row end iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zRowEnd(1) << 10 << m_PrimaryIntMatrix.zRowEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getZIterator(1, 3);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getZIterator(3, 0);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getZIterator(2, 1);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << -1 << m_PrimaryIntMatrix.getZIterator(3, 1);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getZIterator(3, 1);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.getZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getZIterator(3, 1);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.zEnd() << 0 << m_PrimaryIntMatrix.getZIterator(1, 3);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.zEnd() << 11 << m_PrimaryIntMatrix.getZIterator(19);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.zEnd() << -2 << m_PrimaryIntMatrix.getZIterator(2, 1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.zEnd() << -1 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(1, 3) << m_PrimaryIntMatrix.zEnd() << 10 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(3, 1) << -1 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getZIterator(3, 0);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getZIterator(2, 1);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getZIterator(3, 1);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getZIterator(3, 1);
}

void ZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixZIterator>("firstIterator");
    QTest::addColumn<IntMatrixZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(0, 2);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.zEnd();
}

void ZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("firstIterator");
    QTest::addColumn<IntMatrixZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(0, 2);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(0, 2);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.zBegin() << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.zEnd() << m_SecondaryIntMatrix.zBegin();
}

void ZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixZIterator>("inputIterator");
    QTest::addColumn<IntMatrixZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.getZIterator(0, 2);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(4, 6) << m_PrimaryIntMatrix.getZIterator(4, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(4, 7) << m_PrimaryIntMatrix.getZIterator(5, 0);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 0) << m_PrimaryIntMatrix.getZIterator(5, 1);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 1) << m_PrimaryIntMatrix.getZIterator(5, 2);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 4) << m_PrimaryIntMatrix.getZIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(8, 6) << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.zEnd();
}

void ZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixZIterator>("inputIterator");
    QTest::addColumn<IntMatrixZIterator>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.zEnd() << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(8, 7) << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 5) << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 2) << m_PrimaryIntMatrix.getZIterator(5, 1);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 1) << m_PrimaryIntMatrix.getZIterator(5, 0);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(5, 0) << m_PrimaryIntMatrix.getZIterator(4, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(4, 7) << m_PrimaryIntMatrix.getZIterator(4, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getZIterator(0, 2) << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getZIterator(0, 1) << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.zBegin() << m_PrimaryIntMatrix.zBegin();
}

void ZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.zBegin() << -3 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.zBegin() << -1 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("3: begin iterator, begin iterator") << m_PrimaryIntMatrix.zBegin() << 0 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("4: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << 1 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("5: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << 4 << m_PrimaryIntMatrix.getZIterator(0, 4);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << 10 << m_PrimaryIntMatrix.getZIterator(1, 2);
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << 70 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("8: begin iterator, random iterator") << m_PrimaryIntMatrix.zBegin() << 71 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("9: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << 72 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("10: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << 73 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("11: begin iterator, end iterator") << m_PrimaryIntMatrix.zBegin() << 75 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("12: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << -4 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("13: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << -2 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("14: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << -1 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 0 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 3 << m_PrimaryIntMatrix.getZIterator(0, 4);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 9 << m_PrimaryIntMatrix.getZIterator(1, 2);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 69 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 70 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("20: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 71 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("21: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 72 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("22: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << 74 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("23: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -47 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("24: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -45 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("25: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -44 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -43 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -6 << m_PrimaryIntMatrix.getZIterator(4, 6);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << -2 << m_PrimaryIntMatrix.getZIterator(5, 2);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) <<  0 << m_PrimaryIntMatrix.getZIterator(5, 4);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) <<  2 << m_PrimaryIntMatrix.getZIterator(5, 6);
    QTest::newRow("31: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 6 << m_PrimaryIntMatrix.getZIterator(6, 2);
    QTest::newRow("32: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 26 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("33: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 27 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 28 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 29 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << 31 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("37: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -73 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("38: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -71 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("39: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -70 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -69 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -24 << m_PrimaryIntMatrix.getZIterator(5, 6);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << -3 << m_PrimaryIntMatrix.getZIterator(8, 3);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << 0 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << 1 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("45: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << 2 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("46: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << 3 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("47: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << 5 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("48: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -74 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("49: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -72 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("50: random iterator, begin iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -71 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -70 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -25 << m_PrimaryIntMatrix.getZIterator(5, 6);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -4 << m_PrimaryIntMatrix.getZIterator(8, 3);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << -1 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << 0 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("56: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << 1 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("57: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << 2 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("58: random iterator, end iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << 4 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("59: end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << -75 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("60: end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << -73 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("61: end iterator, begin iterator") << m_PrimaryIntMatrix.zEnd() << -72 << m_PrimaryIntMatrix.zBegin();
    QTest::newRow("62: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << -71 << m_PrimaryIntMatrix.getZIterator(0, 1);
    QTest::newRow("63: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << -26 << m_PrimaryIntMatrix.getZIterator(5, 6);
    QTest::newRow("64: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << -5 << m_PrimaryIntMatrix.getZIterator(8, 3);
    QTest::newRow("65: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << -2 << m_PrimaryIntMatrix.getZIterator(8, 6);
    QTest::newRow("66: end iterator, random iterator") << m_PrimaryIntMatrix.zEnd() << -1 << m_PrimaryIntMatrix.getZIterator(8, 7);
    QTest::newRow("67: end iterator, end iterator") << m_PrimaryIntMatrix.zEnd() << 0 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("68: end iterator, end iterator") << m_PrimaryIntMatrix.zEnd() << 1 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("69: end iterator, end iterator") << m_PrimaryIntMatrix.zEnd() << 3 << m_PrimaryIntMatrix.zEnd();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.zBegin() << -1 << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.zBegin() << 1 << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.zEnd() << 0 << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.zEnd() << 1 << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.zEnd() << -1 << m_SecondaryIntMatrix.zEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntMatrixZIterator{} << -1 << IntMatrixZIterator{};
    QTest::newRow("76: empty iterator, empty iterator") << IntMatrixZIterator{} << 1 << IntMatrixZIterator{};
}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortests.moc"
