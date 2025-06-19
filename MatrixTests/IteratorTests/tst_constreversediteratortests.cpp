#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntConstReverseDIter)
Q_DECLARE_METATYPE(StringConstReverseDIter)
Q_DECLARE_METATYPE(IntReverseDIter)

class ConstReverseDIteratorTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIteratorCreation();
    void testIteratorCreationFromNonConstIterator();
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
    
    IntConstReverseDIter m_PrimaryIntIterator;
    IntConstReverseDIter m_SecondaryIntIterator;
    StringConstReverseDIter m_StringIterator;
};

void ConstReverseDIteratorTests::testIteratorCreation()
{
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    QFETCH(matrix_diff_t, expectedDiagonalNr);
    QFETCH(matrix_opt_size_t, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstReverseDIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntReverseDIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    QFETCH(matrix_diff_t, expectedDiagonalNr);
    QFETCH(matrix_opt_size_t, expectedDiagonalIndex);
    
    IntConstReverseDIter constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.getDiagonalNr() == expectedDiagonalNr &&
             constIterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstReverseDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();
    
    IntConstReverseDIter emptyIterator;

    QVERIFY2(!emptyIterator.getRowNr().has_value() && !emptyIterator.getColumnNr().has_value() && emptyIterator.getDiagonalNr() == 0 && !emptyIterator.getDiagonalIndex().has_value(), "The iterator has not been correctly created");
}

void ConstReverseDIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseDIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 2);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstReverseDIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseDIteratorTests::testLessThanOperator()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseDIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseDIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(1, 0),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseDIterator(2, 1),
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
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseDIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorMinus()
{
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseDIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseDIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseDIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseDIteratorTests::testDifferenceOperator()
{
    QFETCH(IntConstReverseDIter, firstIterator);
    QFETCH(IntConstReverseDIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.reserve(6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstReverseDIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    m_StringIterator = m_StringMatrix.constReverseDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    // test with column capacity offset
    m_StringMatrix = {2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    m_StringMatrix.reserve(2, 5);
    m_StringIterator = m_StringMatrix.constReverseDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseDIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntConstReverseDIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseDIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseDBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 6);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseDIterator({-2, 0});

    QVERIFY(m_PrimaryIntIterator[1] == 7);
}

void ConstReverseDIteratorTests::testStdCount()
{
    QFETCH(IntConstReverseDIter, leftIterator);
    QFETCH(IntConstReverseDIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseDIteratorTests::testStdFind()
{
    QFETCH(IntConstReverseDIter, leftIterator);
    QFETCH(IntConstReverseDIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntConstReverseDIter, expectedIterator);

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
    
    QTest::addColumn<IntConstReverseDIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_diff_t>("expectedDiagonalNr");
    QTest::addColumn<matrix_opt_size_t>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(-2) << matrix_opt_size_t{3u} << matrix_opt_size_t{1u} << matrix_diff_t{-2} << matrix_opt_size_t{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(2, 1) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(0, 0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(1, 2) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(-2) << matrix_opt_size_t{1u} << matrix_opt_size_t{} << matrix_diff_t{-2} << matrix_opt_size_t{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(1) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(2, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{} << matrix_diff_t{-1} << matrix_opt_size_t{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(0, 0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(1, 2) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{-1} << matrix_opt_size_t{2u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 2) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 2) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 0}) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({2, 0}) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({0, 2}) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{2u};
}

void ConstReverseDIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntReverseDIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<matrix_diff_t>("expectedDiagonalNr");
    QTest::addColumn<matrix_opt_size_t>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(-2) << matrix_opt_size_t{3u} << matrix_opt_size_t{1u} << matrix_diff_t{-2} << matrix_opt_size_t{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(2, 1) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(0, 0) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.reverseDBegin(1, 2) << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_diff_t{1} << matrix_opt_size_t{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.reverseDEnd(-2) << matrix_opt_size_t{1u} << matrix_opt_size_t{} << matrix_diff_t{-2} << matrix_opt_size_t{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.reverseDEnd(1) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.reverseDEnd(2, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{} << matrix_diff_t{-1} << matrix_opt_size_t{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.reverseDEnd(0, 0) << matrix_opt_size_t{} << matrix_opt_size_t{} << matrix_diff_t{0} << matrix_opt_size_t{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.reverseDEnd(1, 2) << matrix_opt_size_t{} << matrix_opt_size_t{0u} << matrix_diff_t{1} << matrix_opt_size_t{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_diff_t{-1} << matrix_opt_size_t{2u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(0, 2) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 1) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseDIterator(2, 2) << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << matrix_diff_t{0} << matrix_opt_size_t{0u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 0}) << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_diff_t{-1} << matrix_opt_size_t{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({2, 0}) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_diff_t{2} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({-1, 1}) << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_diff_t{-1} << matrix_opt_size_t{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseDIterator({0, 2}) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_diff_t{0} << matrix_opt_size_t{2u};
}

void ConstReverseDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntConstReverseDIter>("firstIterator");
    QTest::addColumn<IntConstReverseDIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(1, 2) << m_PrimaryIntMatrix.getConstReverseDIterator({1, 0});
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(2, 1);
    QTest::newRow("3: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseDBegin(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 0});
    QTest::newRow("5: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseDEnd(2) << m_PrimaryIntMatrix.constReverseDEnd(0, 2);
}

void ConstReverseDIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
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
    
    QTest::addColumn<IntConstReverseDIter>("firstIterator");
    QTest::addColumn<IntConstReverseDIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.constReverseDBegin(3, 2) << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 0) << m_PrimaryIntMatrix.constReverseDBegin(2, 2) << matrix_diff_t{-2};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 0}) << matrix_diff_t{-1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseDIterator({1, 0}) << matrix_diff_t{-1};
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 0}) << m_PrimaryIntMatrix.constReverseDEnd(-1) << matrix_diff_t{3};
    QTest::newRow("6: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseDEnd(1) << m_PrimaryIntMatrix.constReverseDEnd(1, 2) << matrix_diff_t{0};
}

void ConstReverseDIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntConstReverseDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << matrix_diff_t{0} << 6;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{-1} << 12;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{1} << 4;
    QTest::newRow("6: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-3} << 9;
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-1} << 1;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(6, 5);

    QTest::newRow("9: begin iterator") << m_SecondaryIntMatrix.constReverseDBegin(0, 1) << matrix_diff_t{0} << 6;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.constReverseDBegin(0, 1) << matrix_diff_t{1} << 2;
    QTest::newRow("11: random iterator") << m_SecondaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{-1} << 12;
    QTest::newRow("12: random iterator") << m_SecondaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{0} << -8;
    QTest::newRow("13: random iterator") << m_SecondaryIntMatrix.getConstReverseDIterator(2, 1) << matrix_diff_t{1} << 4;
    QTest::newRow("14: end iterator") << m_SecondaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-3} << 9;
    QTest::newRow("15: end iterator") << m_SecondaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-2} << -5;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.constReverseDEnd(0) << matrix_diff_t{-1} << 1;
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
    
    QTest::addColumn<IntConstReverseDIter>("leftIterator");
    QTest::addColumn<IntConstReverseDIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << -3 << matrix_diff_t{1};
    QTest::newRow("2: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseDBegin(1) << m_SecondaryIntMatrix.constReverseDEnd(1) << -1 << matrix_diff_t{3};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseDIterator({1, 0}) << -3 << matrix_diff_t{0};
    QTest::newRow("4: random iterator, random iterator") << m_SecondaryIntMatrix.getConstReverseDIterator(4, 5) << m_SecondaryIntMatrix.getConstReverseDIterator({1, 4}) << 4 << matrix_diff_t{1};
    QTest::newRow("5: random iterator, random iterator") << m_SecondaryIntMatrix.getConstReverseDIterator(3, 4) << m_SecondaryIntMatrix.getConstReverseDIterator({1, 4}) << 4 << matrix_diff_t{0};
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
    
    QTest::addColumn<IntConstReverseDIter>("leftIterator");
    QTest::addColumn<IntConstReverseDIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntConstReverseDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseDIterator(3, 4);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.constReverseDEnd(1) << -9 << m_PrimaryIntMatrix.constReverseDEnd(1);
}

void ConstReverseDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntConstReverseDIter>("firstIterator");
    QTest::addColumn<IntConstReverseDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseDBegin(1) << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1);
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(0, 1) << m_PrimaryIntMatrix.constReverseDEnd(1);
}

void ConstReverseDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntConstReverseDIter>("firstIterator");
    QTest::addColumn<IntConstReverseDIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(3, 2) << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1) << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1});
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << m_PrimaryIntMatrix.constReverseDEnd(-1);
}

void ConstReverseDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    
    QTest::addColumn<IntConstReverseDIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntConstReverseDIter>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << matrix_diff_t{2} << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("3: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("4: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseDBegin(-1) << matrix_diff_t{4} << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{-2} << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("6: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseDIterator(2, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("9: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{2} << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseDIterator({-1, 1}) << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseDEnd(-1) << matrix_diff_t{-4} << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("12: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseDEnd(-1) << matrix_diff_t{-3} << m_PrimaryIntMatrix.constReverseDBegin(3, 2);
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseDEnd(-1) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstReverseDIterator(1, 0);
    QTest::newRow("14: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseDEnd(-1) << matrix_diff_t{1} << m_PrimaryIntMatrix.constReverseDEnd(3, 2);
    QTest::newRow("15: begin iterator, begin iterator") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << matrix_diff_t{-2} << m_SecondaryIntMatrix.constReverseDBegin(2, 3);
    QTest::newRow("16: begin iterator, begin iterator") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << matrix_diff_t{-1} << m_SecondaryIntMatrix.constReverseDBegin(2, 3);
    QTest::newRow("17: begin iterator, random iterator") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << matrix_diff_t{2} << m_SecondaryIntMatrix.getConstReverseDIterator(0, 1);
    QTest::newRow("18: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << matrix_diff_t{3} << m_SecondaryIntMatrix.constReverseDEnd(2, 3);
    QTest::newRow("19: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseDBegin(2, 3) << matrix_diff_t{4} << m_SecondaryIntMatrix.constReverseDEnd(2, 3);
}

QTEST_APPLESS_MAIN(ConstReverseDIteratorTests)

#include "tst_constreversediteratortests.moc"
