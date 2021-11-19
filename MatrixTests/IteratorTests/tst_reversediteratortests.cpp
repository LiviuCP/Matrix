#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseDIterator = Matrix<int>::ReverseDIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseDIterator = Matrix<std::string>::ReverseDIterator;

Q_DECLARE_METATYPE(IntMatrixReverseDIterator)
Q_DECLARE_METATYPE(StringMatrixReverseDIterator)

class ReverseDIteratorTests : public QObject
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

    IntMatrixReverseDIterator m_PrimaryIntIterator;
    IntMatrixReverseDIterator m_SecondaryIntIterator;
    StringMatrixReverseDIterator m_StringIterator;
};

void ReverseDIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex &&
             iterator.isValidWithMatrix(m_PrimaryIntMatrix),
             "The iterator has not been correctly created!");
}

// additional test for checking that an iterator is only valid with the matrix with which it is created
void ReverseDIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(2, 1);

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ReverseDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixReverseDIterator emptyIterator;

    QVERIFY2(emptyIterator.getRowNr() == -1 && emptyIterator.getColumnNr() == -1 && emptyIterator.getDiagonalNr() == 0 && emptyIterator.getDiagonalIndex() == -1, "The iterator has not been correctly created");
    QVERIFY(!emptyIterator.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ReverseDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

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
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ReverseDIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ReverseDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ReverseDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);

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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(3, 2),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getReverseDIterator(2, 1),
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
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseDIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseDIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseDIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixReverseDIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ReverseDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixReverseDIterator, firstIterator);
    QFETCH(IntMatrixReverseDIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ReverseDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(1, 1, true);
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

    QVERIFY2(*m_StringMatrix.getReverseDIterator(1, 0, true) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");
}

void ReverseDIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ReverseDIteratorTests::testSquareBracketsOperatorWrite()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    m_PrimaryIntIterator[-1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getReverseDIterator(1, 0, true) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void ReverseDIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.reverseDBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 6);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getReverseDIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == 7);
}

void ReverseDIteratorTests::testStdCount()
{
    QFETCH(IntMatrixReverseDIterator, leftIterator);
    QFETCH(IntMatrixReverseDIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ReverseDIteratorTests::testStdFind()
{
    QFETCH(IntMatrixReverseDIterator, leftIterator);
    QFETCH(IntMatrixReverseDIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixReverseDIterator, expectedIterator);

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

    QTest::addColumn<IntMatrixReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(-2) << 3 << 1 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(0) << 2 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(1) << 1 << 2 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(2, 1) << 3 << 2 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(0, 0) << 2 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(1, 2) << 1 << 2 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(-2) << 1 << -1 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(0) << -1 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(1) << -1 << 0 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(2, 1) << 0 << -1 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(0, 0) << -1 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(1, 2) << -1 << 0 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(1, 0) << 1 << 0 << -1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 2) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 2) << 2 << 2 << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 0, true) << 3 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 0, true) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 2, true) << 0 << 0 << 0 << 2;
}

void ReverseDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(1, 2) << m_PrimaryIntMatrix.getReverseDIterator(1, 0, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseDBegin(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(3, 2) << m_PrimaryIntMatrix.getReverseDIterator(-1, 0, true);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseDEnd(2) << m_PrimaryIntMatrix.reverseDEnd(0, 2);
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

    QTest::addColumn<IntMatrixReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.reverseDBegin(3, 2) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 0) << m_PrimaryIntMatrix.reverseDBegin(2, 2) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(-1, 0, true) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.getReverseDIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 0, true) << m_PrimaryIntMatrix.reverseDEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseDEnd(1) << m_PrimaryIntMatrix.reverseDEnd(1, 2) << 0;
}

void ReverseDIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(0, 1) << 0 << 6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(0, 1) << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << -1 << 12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << 1 << 4;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(0) << -3 << 9;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseDEnd(0) << -1 << 1;
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

    QTest::addColumn<IntMatrixReverseDIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseDBegin(1) << m_SecondaryIntMatrix.reverseDEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.getReverseDIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getReverseDIterator(4, 5) << m_SecondaryIntMatrix.getReverseDIterator(1, 4, true) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getReverseDIterator(3, 4) << m_SecondaryIntMatrix.getReverseDIterator(1, 4, true) << 4 << 0;
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

    QTest::addColumn<IntMatrixReverseDIterator>("leftIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixReverseDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << 5 << m_PrimaryIntMatrix.getReverseDIterator(3, 4);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.reverseDEnd(1) << -9 << m_PrimaryIntMatrix.reverseDEnd(1);
}

void ReverseDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseDBegin(1) << m_PrimaryIntMatrix.getReverseDIterator(0, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseDIterator(0, 1) << m_PrimaryIntMatrix.reverseDEnd(1);
}

void ReverseDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixReverseDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << m_PrimaryIntMatrix.getReverseDIterator(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(3, 2) << m_PrimaryIntMatrix.getReverseDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << m_PrimaryIntMatrix.reverseDEnd(-1);
}

void ReverseDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixReverseDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << -1 << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << 2 << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << 3 << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.reverseDBegin(-1) << 4 << m_PrimaryIntMatrix.reverseDEnd(3, 2);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getReverseDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.reverseDEnd(3, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getReverseDIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.reverseDEnd(3, 2);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseDEnd(-1) << -4 << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.reverseDEnd(-1) << -3 << m_PrimaryIntMatrix.reverseDBegin(3, 2);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.reverseDEnd(-1) << -1 << m_PrimaryIntMatrix.getReverseDIterator(1, 0);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.reverseDEnd(-1) << 1 << m_PrimaryIntMatrix.reverseDEnd(3, 2);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << -2 << m_SecondaryIntMatrix.reverseDBegin(2, 3);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << -1 << m_SecondaryIntMatrix.reverseDBegin(2, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << 2 << m_SecondaryIntMatrix.getReverseDIterator(0, 1);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << 3 << m_SecondaryIntMatrix.reverseDEnd(2, 3);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.reverseDBegin(2, 3) << 4 << m_SecondaryIntMatrix.reverseDEnd(2, 3);
}

QTEST_APPLESS_MAIN(ReverseDIteratorTests)

#include "tst_reversediteratortests.moc"
