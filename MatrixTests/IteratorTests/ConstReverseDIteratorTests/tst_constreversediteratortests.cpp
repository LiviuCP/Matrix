#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseDIterator = Matrix<int>::ConstReverseDIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseDIterator = Matrix<std::string>::ConstReverseDIterator;

Q_DECLARE_METATYPE(IntMatrixConstReverseDIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseDIterator)

class ConstReverseDIteratorTests : public QObject
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
    void testSquareBracketsOperator();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrement();

    // test data
    void testIteratorCreation_data();
    void testIteratorsAreEqual_data();
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

    IntMatrixConstReverseDIterator m_PrimaryIntIterator;
    IntMatrixConstReverseDIterator m_SecondaryIntIterator;
    StringMatrixConstReverseDIterator m_StringIterator;
};

void ConstReverseDIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
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
void ConstReverseDIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstReverseDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixConstReverseDIterator emptyIterator;

    QVERIFY2(emptyIterator.getRowNr() == -1 && emptyIterator.getColumnNr() == -1 && emptyIterator.getDiagonalNr() == 0 && emptyIterator.getDiagonalIndex() == -1, "The iterator has not been correctly created");
    QVERIFY(!emptyIterator.isValidWithMatrix(m_PrimaryIntMatrix) && !emptyIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstReverseDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator, "The iterators should be equal!");
}

void ConstReverseDIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 2);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstReverseDIteratorTests::testIteratorsAreNotEqual()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 2);
    m_SecondaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 1, true);

    QVERIFY2(m_PrimaryIntIterator != m_SecondaryIntIterator, "The iterators should not be equal!");
}

void ConstReverseDIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator, "The first iterator should be less than the second one!");
}

void ConstReverseDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator, "The first iterator should be less than or equal to the second one!");
}

void ConstReverseDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator, "The second iterator should be greater than the first one!");
}

void ConstReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator, "The second iterator should be greater than or equal to the second one!");
}

void ConstReverseDIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseDIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseDIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseDIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseDIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseDIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, firstIterator);
    QFETCH(IntMatrixConstReverseDIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstReverseDIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    m_StringIterator = m_StringMatrix.constReverseDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseDIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstReverseDIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseDIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 6);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == 7);
}

void ConstReverseDIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstReverseDIterator, leftIterator);
    QFETCH(IntMatrixConstReverseDIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseDIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstReverseDIterator, leftIterator);
    QFETCH(IntMatrixConstReverseDIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstReverseDIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstReverseDIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  4, 6,  7,
                              1,  2, -3,  4, -5, 5,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constReverseDBegin(1), m_PrimaryIntMatrix.constReverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constReverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constReverseDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constReverseDEnd(1), "The std::find algorithm does not return the expected iterator!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ConstReverseDIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-2) << 3 << 1 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(0) << 2 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1) << 1 << 2 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(2, 1) << 3 << 2 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(0, 0) << 2 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1, 2) << 1 << 2 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(-2) << 1 << -1 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(0) << -1 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(1) << -1 << 0 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(2, 1) << 0 << -1 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(0, 0) << -1 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(1, 2) << -1 << 0 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) << 1 << 0 << -1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 2) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 2) << 2 << 2 << 0 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 0, true) << 3 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 0, true) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 2, true) << 0 << 0 << 0 << 2;
}

void ConstReverseDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(1, 2) << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseDBegin(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 0, true);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(2) << m_PrimaryIntMatrix.constReverseDEnd(0, 2);
}

void ConstReverseDIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseDIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseDIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseDIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseDIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseDIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseDIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseDIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseDIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(3, 2) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 0) << m_PrimaryIntMatrix.constReverseDBegin(2, 2) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 0, true) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 0, true) << m_PrimaryIntMatrix.constReverseDEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(1) << m_PrimaryIntMatrix.constReverseDEnd(1, 2) << 0;
}

void ConstReverseDIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << 0 << 6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << -1 << 12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << 1 << 4;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(0) << -3 << 9;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(0) << -1 << 1;
}

void ConstReverseDIteratorTests::testStdCount_data()
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

    QTest::addColumn<IntMatrixConstReverseDIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseDBegin(1) << m_SecondaryIntMatrix.constReverseDEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstReverseDIterator(4, 5) << m_SecondaryIntMatrix.getConstReverseDIterator(1, 4, true) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstReverseDIterator(3, 4) << m_SecondaryIntMatrix.getConstReverseDIterator(1, 4, true) << 4 << 0;
}

void ConstReverseDIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  5, 6,  7,
                              1,  2, -3,  4, -5, 4,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    QTest::addColumn<IntMatrixConstReverseDIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstReverseDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseDIterator(3, 4);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << -9 << m_PrimaryIntMatrix.constReverseDEnd(1);
}

void ConstReverseDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.constReverseDEnd(1);
}

void ConstReverseDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << m_PrimaryIntMatrix.constReverseDEnd(-1);
}

void ConstReverseDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstReverseDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstReverseDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << -1 << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << 2 << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << 3 << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDBegin(-1) << 4 << m_PrimaryIntMatrix.constReverseDEnd(3, 2);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseDIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.constReverseDEnd(3, 2);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseDEnd(-1) << -4 << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseDEnd(-1) << -3 << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseDEnd(-1) << -1 << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseDEnd(-1) << 1 << m_PrimaryIntMatrix.constReverseDEnd(3, 2);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << -2 << m_SecondaryIntMatrix.constReverseDBegin(2, 3);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << -1 << m_SecondaryIntMatrix.constReverseDBegin(2, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << 2 << m_SecondaryIntMatrix.getConstReverseDIterator(0, 1);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << 3 << m_SecondaryIntMatrix.constReverseDEnd(2, 3);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << 4 << m_SecondaryIntMatrix.constReverseDEnd(2, 3);
}

QTEST_APPLESS_MAIN(ConstReverseDIteratorTests)

#include "tst_constreversediteratortests.moc"
