#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstMIterator)
Q_DECLARE_METATYPE(StringMatrixConstMIterator)
Q_DECLARE_METATYPE(IntMatrixMIterator)

class ConstMIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
    void testIteratorCreationFromNonConstIterator();
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
    void testIteratorCreationFromNonConstIterator_data();
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

    IntMatrixConstMIterator m_PrimaryIntIterator;
    IntMatrixConstMIterator m_SecondaryIntIterator;
    StringMatrixConstMIterator m_StringIterator;
};

void ConstMIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstMIterator, iterator);
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

void ConstMIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixMIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalIndex);

    IntMatrixConstMIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.getDiagonalNr() == expectedDiagonalNr &&
             constIterator.getDiagonalIndex() == expectedDiagonalIndex &&
             constIterator.isValidWithMatrix(m_PrimaryIntMatrix),
             "The iterator has not been correctly created!");
}

// additional test for checking that an iterator is only valid with the matrix with which it is created
void ConstMIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(2, 1);

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstMIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixConstMIterator emptyIterator;

    QVERIFY2(emptyIterator.getRowNr() == -1 && emptyIterator.getColumnNr() == -1 && emptyIterator.getDiagonalNr() == 0 && emptyIterator.getDiagonalIndex() == -1, "The iterator has not been correctly created");
    QVERIFY(!emptyIterator.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstMIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstMIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(1, 0);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstMIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstMIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstMIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstMIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstMIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstMIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constMEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constMEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constMEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstMIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constMEnd(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.constMEnd(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(3, 0);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstMIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstMIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstMIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstMIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstMIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstMIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstMIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstMIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstMIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstMIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstMIterator, firstIterator);
    QFETCH(IntMatrixConstMIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstMIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstMIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_StringMatrix.constMBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");
}

void ConstMIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstMIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstMIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constMBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 2);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstMIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == -11);
}

void ConstMIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstMIterator, leftIterator);
    QFETCH(IntMatrixConstMIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstMIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstMIterator, leftIterator);
    QFETCH(IntMatrixConstMIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstMIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstMIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  4,  4, -3,  2, 1,
                              7, 5, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constMBegin(1), m_PrimaryIntMatrix.constMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(1, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstMIterator(3, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.constMEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.constMEnd(1), "The std::find algorithm does not return the expected iterator!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void ConstMIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(-2) << 2 << 2 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(0) << 0 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(1) << 0 << 1 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(2, 1) << 1 << 2 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(0, 2) << 0 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(1, 0) << 0 << 1 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(-2) << 4 << 0 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(0) << 3 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(1) << 2 << -1 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(2, 1) << 4 << -1 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(0, 2) << 3 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(1, 0) << 2 << -1 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 2) << 1 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(0, 0) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 0) << 2 << 0 << 0 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 0, true) << 1 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 0, true) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(0, 2, true) << 2 << 0 << 0 << 2;
}

void ConstMIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixMIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(-2) << 2 << 2 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(0) << 0 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(1) << 0 << 1 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(2, 1) << 1 << 2 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(0, 2) << 0 << 2 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.mBegin(1, 0) << 0 << 1 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(-2) << 4 << 0 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(0) << 3 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(1) << 2 << -1 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(2, 1) << 4 << -1 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(0, 2) << 3 << -1 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.mEnd(1, 0) << 2 << -1 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(1, 2) << 1 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(0, 0) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(2, 0) << 2 << 0 << 0 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(-1, 0, true) << 1 << 2 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(2, 0, true) << 0 << 0 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getMIterator(0, 2, true) << 2 << 0 << 0 << 2;
}

void ConstMIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstMIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 0) << m_PrimaryIntMatrix.getConstMIterator(1, 1, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << m_PrimaryIntMatrix.constMBegin(2, 1); //
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constMBegin(2, 1) << m_PrimaryIntMatrix.getConstMIterator(1, 2); //
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 2) << m_PrimaryIntMatrix.getConstMIterator(-1, 0, true); //
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constMEnd(2) << m_PrimaryIntMatrix.constMEnd(0, 0);
}

void ConstMIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstMIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstMIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstMIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstMIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstMIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstMIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstMIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstMIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstMIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstMIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << m_PrimaryIntMatrix.constMBegin(1, 2) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 0) << m_PrimaryIntMatrix.constMBegin(0, 2) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << m_PrimaryIntMatrix.getConstMIterator(-1, 2, true) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 0) << m_PrimaryIntMatrix.getConstMIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 0, true) << m_PrimaryIntMatrix.constMEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constMEnd(1) << m_PrimaryIntMatrix.constMEnd(0, 1) << 0;
}

void ConstMIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(0, 1) << 0 << 2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constMBegin(0, 1) << 1 << 4;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << -1 << 6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << 1 << 10;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(0) << -3 << -3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constMEnd(0) << -1 << 7;
}

void ConstMIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {1, 2, {-3, 2}};

    m_SecondaryIntMatrix = {6, 7, {
                                7, 6, -5,  4, -3, -1, 1,
                                7, 6, -5,  4,  4,  2, 1,
                                7, 6, -5, -1, -3,  2, 1,
                                7, 6,  5,  4, -3,  2, 1,
                                7, 4, -5,  4, -3,  2, 1,
                               -1, 6, -5,  4, -3,  2, 1,
                           }};

    QTest::addColumn<IntMatrixConstMIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstMIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constMBegin(1) << m_PrimaryIntMatrix.constMEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constMBegin(1) << m_SecondaryIntMatrix.constMEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(0, 0) << m_PrimaryIntMatrix.getConstMIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstMIterator(1, 1, true) << m_SecondaryIntMatrix.getConstMIterator(4, 1) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getConstMIterator(2, 3) << m_SecondaryIntMatrix.getConstMIterator(1, 4, true) << 4 << 0;
}

void ConstMIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                         }};

    QTest::addColumn<IntMatrixConstMIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstMIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstMIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constMBegin(1) << m_PrimaryIntMatrix.constMEnd(1) << 5 << m_PrimaryIntMatrix.getConstMIterator(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constMBegin(1) << m_PrimaryIntMatrix.constMEnd(1) << -9 << m_PrimaryIntMatrix.constMEnd(1);
}

void ConstMIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstMIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constMBegin(1) << m_PrimaryIntMatrix.getConstMIterator(1, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 0) << m_PrimaryIntMatrix.constMEnd(1);
}

void ConstMIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstMIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << m_PrimaryIntMatrix.getConstMIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(1, 2) << m_PrimaryIntMatrix.getConstMIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(2, 1) << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << m_PrimaryIntMatrix.constMEnd(-1);
}

void ConstMIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstMIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstMIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << -1 << m_PrimaryIntMatrix.constMBegin(1, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << 2 << m_PrimaryIntMatrix.getConstMIterator(3, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << 3 << m_PrimaryIntMatrix.constMEnd(1, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constMBegin(-1) << 4 << m_PrimaryIntMatrix.constMEnd(1, 2);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.constMBegin(1, 2);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.constMBegin(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getConstMIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getConstMIterator(3, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.constMEnd(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstMIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.constMEnd(1, 2);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constMEnd(-1) << -4 << m_PrimaryIntMatrix.constMBegin(1, 2);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constMEnd(-1) << -3 << m_PrimaryIntMatrix.constMBegin(1, 2);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constMEnd(-1) << -1 << m_PrimaryIntMatrix.getConstMIterator(3, 0);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constMEnd(-1) << 1 << m_PrimaryIntMatrix.constMEnd(1, 2);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constMBegin(0, 2) << -2 << m_SecondaryIntMatrix.constMBegin(0, 2);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constMBegin(0, 2) << -1 << m_SecondaryIntMatrix.constMBegin(0, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.constMBegin(0, 2) << 2 << m_SecondaryIntMatrix.getConstMIterator(2, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constMBegin(0, 2) << 3 << m_SecondaryIntMatrix.constMEnd(0, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constMBegin(0, 2) << 4 << m_SecondaryIntMatrix.constMEnd(0, 2);
}

QTEST_APPLESS_MAIN(ConstMIteratorTests)

#include "tst_constmiteratortests.moc"
