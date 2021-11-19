#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseZIterator = Matrix<int>::ReverseZIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseZIterator = Matrix<std::string>::ReverseZIterator;

Q_DECLARE_METATYPE(IntMatrixReverseZIterator)
Q_DECLARE_METATYPE(StringMatrixReverseZIterator)

class ReverseZIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
    void testIteratorIsValidWithOneMatrix();
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

    IntMatrixReverseZIterator m_PrimaryIntIterator;
    IntMatrixReverseZIterator m_SecondaryIntIterator;
    StringMatrixReverseZIterator m_StringIterator;
};

void ReverseZIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ReverseZIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_SecondaryIntMatrix.clear();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.reverseZBegin();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.reverseZEnd();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntMatrix.clear();
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZBegin();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseZEnd();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ReverseZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixReverseZIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
    QVERIFY(!emptyIt.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIt.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ReverseZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ReverseZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixReverseZIterator, iterator);

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
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseZIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ReverseZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixReverseZIterator, inputIterator);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixReverseZIterator, inputIterator);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixReverseZIterator, inputIterator);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixReverseZIterator, inputIterator);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 6),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 4),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ReverseZIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixReverseZIterator, firstIterator);
    QFETCH(IntMatrixReverseZIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseZIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ReverseZIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {4, 3, -20};
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};
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
}

void ReverseZIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringMatrixReverseZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ReverseZIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {4, 3, "zzz"};
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
}

void ReverseZIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseZIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {4, 3, {1, -2, -20, -20, -20, -6, -20, -20, -20, -20, 11, -12}};

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[-1] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[-10] = 11;
    m_PrimaryIntIterator[-11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    m_PrimaryIntIterator[1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[-4] = -6;
    m_PrimaryIntIterator[-9] = 11;
    m_PrimaryIntIterator[-10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    m_PrimaryIntIterator[5] = 1;
    m_PrimaryIntIterator[4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[-5] = 11;
    m_PrimaryIntIterator[-6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    m_PrimaryIntIterator[10] = 1;
    m_PrimaryIntIterator[9] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[-1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {4, 3, -20};
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
    QFETCH(IntMatrixReverseZIterator, leftIterator);
    QFETCH(IntMatrixReverseZIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseZIteratorTests::testStdFind()
{
    QFETCH(IntMatrixReverseZIterator, leftIterator);
    QFETCH(IntMatrixReverseZIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixReverseZIterator, expectedIterator);

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

    for (int row{0}; row<m_PrimaryIntMatrix.getNrOfRows(); ++row)
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
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 8 << 7 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << 0 << -1 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(0) << 0 << 7 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << 1 << 7 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(4) << 4 << 7 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(7) << 7 << 7 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(8) << 8 << 7 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(0) << 0 << -1 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(1) << 0 << 7 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(4) << 3 << 7 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(7) << 6 << 7 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(8) << 7 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << 8 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(44) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(70) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(71) << 8 << 7 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseZBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.reverseZEnd() << -1 << -1 << false << true;
}

void ReverseZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(44) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(70) << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(71) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(0) << m_PrimaryIntMatrix.getReverseZIterator(0, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.getReverseZIterator(1, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(5) << m_PrimaryIntMatrix.getReverseZIterator(5, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(7) << m_PrimaryIntMatrix.getReverseZIterator(7, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(8) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("{row end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(1) << m_PrimaryIntMatrix.getReverseZIterator(0, 7);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(5) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(7) << m_PrimaryIntMatrix.getReverseZIterator(6, 7);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(8) << m_PrimaryIntMatrix.getReverseZIterator(7, 7);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");

    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.reverseZBegin();
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
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin() << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.reverseZBegin() << -1;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.reverseZBegin() << -27;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.reverseZBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZBegin() << -71;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZBegin() << -72;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -71;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -45;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -1;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 44;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 0;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -1;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 72;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.reverseZEnd() << 71;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.reverseZEnd() << 45;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.reverseZEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd() << 1;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(7, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(7, 2) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << 2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseZIterator{} << IntMatrixReverseZIterator{} << 0;
}

void ReverseZIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << -12;
}

void ReverseZIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringMatrixReverseZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseZIterator(0, 0) << 3;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseZIterator(0, 1) << 2;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseZIterator(1, 2) << 7;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getReverseZIterator(3, 1) << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryStringMatrix.reverseZBegin() << 6;
}

void ReverseZIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 11 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 10 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 6 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 1 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 0 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << -1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << 5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << 4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << -5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 2) << -6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 0 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -1 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -10 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -11 << -12;
}

void ReverseZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    QTest::addColumn<IntMatrixReverseZIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 3) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(2, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(2, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 3) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(2, 3) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(2, 3) << m_PrimaryIntMatrix.reverseZEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(2, 2) << m_PrimaryIntMatrix.reverseZEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(9) << m_PrimaryIntMatrix.getReverseZIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(10) << m_PrimaryIntMatrix.getReverseZIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(9) << m_PrimaryIntMatrix.getReverseZIterator(3) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(10) << m_PrimaryIntMatrix.getReverseZIterator(3) << 1 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(13) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(13) << m_PrimaryIntMatrix.reverseZEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(12) << m_PrimaryIntMatrix.reverseZEnd() << 2 << 2;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << 1;
    QTest::newRow("{row end iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(3) << m_PrimaryIntMatrix.reverseZRowEnd(0) << 8 << 2;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(3) << m_PrimaryIntMatrix.reverseZRowEnd(3) << 9 << 1;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(3) << m_PrimaryIntMatrix.reverseZRowEnd(2) << 9 << 2;
    QTest::newRow("{row end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowEnd(1) << m_PrimaryIntMatrix.reverseZEnd() << 1 << 2;
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << 1;
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(2) << m_PrimaryIntMatrix.reverseZEnd() << 1 << 3;
    QTest::newRow("{begin iterator, row begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowBegin(2) << 1 << 0;
}

void ReverseZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    QTest::addColumn<IntMatrixReverseZIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixReverseZIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 5 << m_PrimaryIntMatrix.getReverseZIterator(5);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 6 << m_PrimaryIntMatrix.reverseZRowBegin(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getReverseZIterator(1, 0);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 8 << m_PrimaryIntMatrix.getReverseZIterator(7);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << -1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 6 << m_PrimaryIntMatrix.reverseZRowBegin(1);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << -1 << m_PrimaryIntMatrix.getReverseZIterator(0);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 3 << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << -2 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZRowBegin(1) << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 11 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getReverseZIterator(1, 0);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 0 << m_PrimaryIntMatrix.getReverseZIterator(8);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 7 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -7 << m_PrimaryIntMatrix.getReverseZIterator(3, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -2 << m_PrimaryIntMatrix.getReverseZIterator(11);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << -1 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 11 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << 10 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 0 << m_PrimaryIntMatrix.getReverseZIterator(1, 3);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << -1 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 4 << m_PrimaryIntMatrix.reverseZRowEnd(1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 11 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(1, 3) << m_PrimaryIntMatrix.reverseZEnd() << 10 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 11 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 2 << m_PrimaryIntMatrix.getReverseZIterator(3, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 9 << m_PrimaryIntMatrix.getReverseZIterator(18);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getReverseZIterator(3, 1);
}

void ReverseZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 2) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseZBegin() << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.reverseZEnd() << m_SecondaryIntMatrix.reverseZBegin();
}

void ReverseZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixReverseZIterator>("inputIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 5) << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 2) << m_PrimaryIntMatrix.getReverseZIterator(5, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 0) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(4, 7) << m_PrimaryIntMatrix.getReverseZIterator(4, 6);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.reverseZEnd();
}

void ReverseZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixReverseZIterator>("inputIterator");
    QTest::addColumn<IntMatrixReverseZIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.reverseZEnd() << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(4, 6) << m_PrimaryIntMatrix.getReverseZIterator(4, 7);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(4, 7) << m_PrimaryIntMatrix.getReverseZIterator(5, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 0) << m_PrimaryIntMatrix.getReverseZIterator(5, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 1) << m_PrimaryIntMatrix.getReverseZIterator(5, 2);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << m_PrimaryIntMatrix.getReverseZIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << m_PrimaryIntMatrix.getReverseZIterator(8, 7);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.reverseZBegin() << m_PrimaryIntMatrix.reverseZBegin();
}

void ReverseZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixReverseZIterator>("expectedIterator");

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << 3 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << 1 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseZEnd() << 0 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -1 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -2 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -5 << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -11 << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -71 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -72 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -73 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZEnd() << -75 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 4 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 2 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 1 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 0 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -1 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -4 << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -10 << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -70 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -71 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -72 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << -74 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 5 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 3 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 2 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 1 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 0 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -3 << m_PrimaryIntMatrix.getReverseZIterator(0, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -9 << m_PrimaryIntMatrix.getReverseZIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -69 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -70 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -71 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << -73 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 48 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 46 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 45 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 44 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 43 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 6 << m_PrimaryIntMatrix.getReverseZIterator(4, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 2 << m_PrimaryIntMatrix.getReverseZIterator(5, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 0 << m_PrimaryIntMatrix.getReverseZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -2 << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -6 << m_PrimaryIntMatrix.getReverseZIterator(6, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -26 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -27 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -28 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << -30 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 74 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 72 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 71 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 70 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 69 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 24 << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 3 << m_PrimaryIntMatrix.getReverseZIterator(8, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 0 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -1 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -2 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << -4 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 75 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 73 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 72 << m_PrimaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 71 << m_PrimaryIntMatrix.getReverseZIterator(0, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 70 << m_PrimaryIntMatrix.getReverseZIterator(0, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 25 << m_PrimaryIntMatrix.getReverseZIterator(5, 6);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 4 << m_PrimaryIntMatrix.getReverseZIterator(8, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 1 << m_PrimaryIntMatrix.getReverseZIterator(8, 6);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << 0 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << -1 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseZBegin() << -3 << m_PrimaryIntMatrix.reverseZBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseZBegin() << -1 << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseZBegin() << 1 << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseZEnd() << 0 << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseZEnd() << 1 << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.reverseZEnd() << -1 << m_SecondaryIntMatrix.reverseZEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseZIterator{} << -1 << IntMatrixReverseZIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixReverseZIterator{} << 1 << IntMatrixReverseZIterator{};
}

QTEST_APPLESS_MAIN(ReverseZIteratorTests)

#include "tst_reverseziteratortests.moc"
