#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstDIterator = Matrix<int>::ConstDIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstDIterator = Matrix<std::string>::ConstDIterator;

Q_DECLARE_METATYPE(IntMatrixConstDIterator)
Q_DECLARE_METATYPE(StringMatrixConstDIterator)

class ConstDIteratorTests : public QObject
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

    IntMatrixConstDIterator m_PrimaryIntIterator;
    IntMatrixConstDIterator m_SecondaryIntIterator;
    StringMatrixConstDIterator m_StringIterator;
};

void ConstDIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstDIterator, iterator);
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
void ConstDIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(2, 1);

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixConstDIterator emptyIterator;

    QVERIFY2(emptyIterator.getRowNr() == -1 && emptyIterator.getColumnNr() == -1 && emptyIterator.getDiagonalNr() == 0 && emptyIterator.getDiagonalIndex() == -1, "The iterator has not been correctly created");
    QVERIFY(!emptyIterator.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstDIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(1, 2);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstDIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstDIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstDIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constDEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constDEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constDEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstDIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constDEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constDEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstDIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstDIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstDIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstDIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstDIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstDIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstDIterator, firstIterator);
    QFETCH(IntMatrixConstDIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstDIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_StringMatrix.constDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");
}

void ConstDIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstDIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constDBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 2);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == -11);
}

void ConstDIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstDIterator, leftIterator);
    QFETCH(IntMatrixConstDIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstDIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstDIterator, leftIterator);
    QFETCH(IntMatrixConstDIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstDIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstDIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  4, 6,  7,
                              1,  2, -3,  4, -5, 5,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constDBegin(1), m_PrimaryIntMatrix.constDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constDEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constDEnd(1), "The std::find algorithm does not return the expected iterator!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ConstDIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(-2) << 2 << 0 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(0) << 0 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(1) << 0 << 1 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(2, 1) << 1 << 0 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(0, 0) << 0 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(1, 2) << 0 << 1 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(-2) << 4 << 2 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(0) << 3 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(1) << 2 << 3 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(2, 1) << 4 << 3 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(0, 0) << 3 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(1, 2) << 2 << 3 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << 1 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(0, 2) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 2) << 2 << 2 << 0 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 0, true) << 1 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 0, true) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(0, 2, true) << 2 << 2 << 0 << 2;
}

void ConstDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.getConstDIterator(1, 1, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.constDBegin(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constDBegin(2, 1) << m_PrimaryIntMatrix.getConstDIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << m_PrimaryIntMatrix.getConstDIterator(-1, 0, true);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constDEnd(2) << m_PrimaryIntMatrix.constDEnd(0, 2);
}

void ConstDIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstDIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstDIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstDIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstDIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstDIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstDIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstDIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstDIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstDIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.constDBegin(1, 0) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 2) << m_PrimaryIntMatrix.constDBegin(0, 0) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator(-1, 2, true) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.getConstDIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 0, true) << m_PrimaryIntMatrix.constDEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constDEnd(1) << m_PrimaryIntMatrix.constDEnd(0, 1) << 0;
}

void ConstDIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(0, 1) << 0 << 2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constDBegin(0, 1) << 1 << 6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << -1 << 4;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << 1 << 12;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(0) << -3 << 1;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constDEnd(0) << -1 << 9;
}

void ConstDIteratorTests::testStdCount_data()
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

    QTest::addColumn<IntMatrixConstDIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstDIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constDBegin(1) << m_SecondaryIntMatrix.constDEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(0, 1) << m_PrimaryIntMatrix.getConstDIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstDIterator(1, 1, true) << m_SecondaryIntMatrix.getConstDIterator(4, 5) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstDIterator(2, 3) << m_SecondaryIntMatrix.getConstDIterator(1, 4, true) << 4 << 0;
}

void ConstDIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  5, 6,  7,
                              1,  2, -3,  4, -5, 4,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    QTest::addColumn<IntMatrixConstDIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstDIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << 5 << m_PrimaryIntMatrix.getConstDIterator(3, 4);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << -9 << m_PrimaryIntMatrix.constDEnd(1);
}

void ConstDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.getConstDIterator(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.constDEnd(1);
}

void ConstDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.getConstDIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << m_PrimaryIntMatrix.getConstDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << m_PrimaryIntMatrix.constDEnd(-1);
}

void ConstDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << -1 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << 2 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << 3 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constDBegin(-1) << 4 << m_PrimaryIntMatrix.constDEnd(1, 0);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getConstDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstDIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.constDEnd(1, 0);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constDEnd(-1) << -4 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constDEnd(-1) << -3 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constDEnd(-1) << -1 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constDEnd(-1) << 1 << m_PrimaryIntMatrix.constDEnd(1, 0);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constDBegin(0, 1) << -2 << m_SecondaryIntMatrix.constDBegin(0, 1);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constDBegin(0, 1) << -1 << m_SecondaryIntMatrix.constDBegin(0, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.constDBegin(0, 1) << 2 << m_SecondaryIntMatrix.getConstDIterator(2, 3);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constDBegin(0, 1) << 3 << m_SecondaryIntMatrix.constDEnd(0, 1);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constDBegin(0, 1) << 4 << m_SecondaryIntMatrix.constDEnd(0, 1);
}

QTEST_APPLESS_MAIN(ConstDIteratorTests)

#include "tst_constditeratortests.moc"
