#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstDIterator)
Q_DECLARE_METATYPE(StringMatrixConstDIterator)
Q_DECLARE_METATYPE(IntMatrixDIterator)

class ConstDIteratorTests : public QObject
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

    IntMatrixConstDIterator m_PrimaryIntIterator;
    IntMatrixConstDIterator m_SecondaryIntIterator;
    StringMatrixConstDIterator m_StringIterator;
};

void ConstDIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstDIterator, iterator);
    QFETCH(IntMatrixOptSizeType, expectedRowNr);
    QFETCH(IntMatrixOptSizeType, expectedColumnNr);
    QFETCH(IntMatrixDiffType, expectedDiagonalNr);
    QFETCH(IntMatrixOptSizeType, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstDIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixOptSizeType, expectedRowNr);
    QFETCH(IntMatrixOptSizeType, expectedColumnNr);
    QFETCH(IntMatrixDiffType, expectedDiagonalNr);
    QFETCH(IntMatrixOptSizeType, expectedDiagonalIndex);

    IntMatrixConstDIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.getDiagonalNr() == expectedDiagonalNr &&
             constIterator.getDiagonalIndex() == expectedDiagonalIndex,
             "The iterator has not been correctly created!");
}

void ConstDIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix.clear();

    IntMatrixConstDIterator emptyIterator;

    QVERIFY2(!emptyIterator.getRowNr().has_value() && !emptyIterator.getColumnNr().has_value() && emptyIterator.getDiagonalNr() == 0 && !emptyIterator.getDiagonalIndex().has_value(), "The iterator has not been correctly created");
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0),
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

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(3, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(3, 2);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstDIterator(2, 1),
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
    QFETCH(IntMatrixDiffType, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstDIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    // test with row capacity offset
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntMatrix.resize(4, 3, 6, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");
}

void ConstDIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_StringMatrix.constDBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    // test with column capacity offset
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringMatrix.resize(2, 3, 2, 5);
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

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstDIterator({-2, 0});

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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixDiffType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constDBegin(-2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << -2 << IntMatrixOptSizeType{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constDBegin(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << 0 << IntMatrixOptSizeType{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constDBegin(1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << 1 << IntMatrixOptSizeType{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constDBegin(2, 1) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constDBegin(0, 0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << 0 << IntMatrixOptSizeType{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.constDBegin(1, 2) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << 1 << IntMatrixOptSizeType{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.constDEnd(-2) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u} << -2 << IntMatrixOptSizeType{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.constDEnd(0) << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{3u} << 0 << IntMatrixOptSizeType{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.constDEnd(1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << 1 << IntMatrixOptSizeType{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.constDEnd(2, 1) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{3u} << -1 << IntMatrixOptSizeType{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.constDEnd(0, 0) << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{3u} << 0 << IntMatrixOptSizeType{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.constDEnd(1, 2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << 1 << IntMatrixOptSizeType{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstDIterator(0, 2) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << 2 << IntMatrixOptSizeType{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << -1 << IntMatrixOptSizeType{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << 0 << IntMatrixOptSizeType{2u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 0}) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstDIterator({2, 0}) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << 2 << IntMatrixOptSizeType{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << -1 << IntMatrixOptSizeType{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstDIterator({0, 2}) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << 0 << IntMatrixOptSizeType{2u};
}

void ConstDIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("iterator");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixDiffType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedDiagonalIndex");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.dBegin(-2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << -2 << IntMatrixOptSizeType{0u};
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.dBegin(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << 0 << IntMatrixOptSizeType{0u};
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.dBegin(1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << 1 << IntMatrixOptSizeType{0u};
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.dBegin(2, 1) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.dBegin(0, 0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << 0 << IntMatrixOptSizeType{0u};
    QTest::newRow("6: begin iterator") << m_PrimaryIntMatrix.dBegin(1, 2) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << 1 << IntMatrixOptSizeType{0u};
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.dEnd(-2) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u} << -2 << IntMatrixOptSizeType{2u};
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.dEnd(0) << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{3u} << 0 << IntMatrixOptSizeType{3u};
    QTest::newRow("9: end iterator") << m_PrimaryIntMatrix.dEnd(1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << 1 << IntMatrixOptSizeType{2u};
    QTest::newRow("10: end iterator") << m_PrimaryIntMatrix.dEnd(2, 1) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{3u} << -1 << IntMatrixOptSizeType{3u};
    QTest::newRow("11: end iterator") << m_PrimaryIntMatrix.dEnd(0, 0) << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{3u} << 0 << IntMatrixOptSizeType{3u};
    QTest::newRow("12: end iterator") << m_PrimaryIntMatrix.dEnd(1, 2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << 1 << IntMatrixOptSizeType{2u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getDIterator(1, 0) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getDIterator(0, 2) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << 2 << IntMatrixOptSizeType{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getDIterator(2, 1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << -1 << IntMatrixOptSizeType{1u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getDIterator(2, 2) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << 0 << IntMatrixOptSizeType{2u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getDIterator({-1, 0}) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << -1 << IntMatrixOptSizeType{0u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getDIterator({2, 0}) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << 2 << IntMatrixOptSizeType{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getDIterator({-1, 1}) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << -1 << IntMatrixOptSizeType{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getDIterator({0, 2}) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << 0 << IntMatrixOptSizeType{2u};
}

void ConstDIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.getConstDIterator({1, 1});
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.constDBegin(2, 1);
    QTest::newRow("3: begin iterator, random iterator") << m_PrimaryIntMatrix.constDBegin(2, 1) << m_PrimaryIntMatrix.getConstDIterator(1, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << m_PrimaryIntMatrix.getConstDIterator({-1, 0});
    QTest::newRow("5: end iterator, end iterator") << m_PrimaryIntMatrix.constDEnd(2) << m_PrimaryIntMatrix.constDEnd(0, 2);
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

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.constDBegin(1, 0) << 0;
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 2) << m_PrimaryIntMatrix.constDBegin(0, 0) << -2;
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator({-1, 2}) << 1;
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.getConstDIterator({1, 0}) << -1;
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 0}) << m_PrimaryIntMatrix.constDEnd(-1) << 3;
    QTest::newRow("6: end iterator, end iterator") << m_PrimaryIntMatrix.constDEnd(1) << m_PrimaryIntMatrix.constDEnd(0, 1) << 0;
}

void ConstDIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constDBegin(0, 1) << 0 << 2;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constDBegin(0, 1) << 1 << 6;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << -1 << 4;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << 0 << -8;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << 1 << 12;
    QTest::newRow("6: end iterator") << m_PrimaryIntMatrix.constDEnd(0) << -3 << 1;
    QTest::newRow("7: end iterator") << m_PrimaryIntMatrix.constDEnd(0) << -2 << -5;
    QTest::newRow("8: end iterator") << m_PrimaryIntMatrix.constDEnd(0) << -1 << 9;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("9: begin iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << 0 << 2;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << 1 << 6;
    QTest::newRow("11: random iterator") << m_SecondaryIntMatrix.getConstDIterator(2, 1) << -1 << 4;
    QTest::newRow("12: random iterator") << m_SecondaryIntMatrix.getConstDIterator(2, 1) << 0 << -8;
    QTest::newRow("13: random iterator") << m_SecondaryIntMatrix.getConstDIterator(2, 1) << 1 << 12;
    QTest::newRow("14: end iterator") << m_SecondaryIntMatrix.constDEnd(0) << -3 << 1;
    QTest::newRow("15: end iterator") << m_SecondaryIntMatrix.constDEnd(0) << -2 << -5;
    QTest::newRow("16: end iterator") << m_SecondaryIntMatrix.constDEnd(0) << -1 << 9;
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

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << -3 << 1;
    QTest::newRow("2: begin iterator, end iterator") << m_SecondaryIntMatrix.constDBegin(1) << m_SecondaryIntMatrix.constDEnd(1) << -1 << 3;
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(0, 1) << m_PrimaryIntMatrix.getConstDIterator({1, 0}) << -3 << 0;
    QTest::newRow("4: random iterator, random iterator") << m_SecondaryIntMatrix.getConstDIterator({1, 1}) << m_SecondaryIntMatrix.getConstDIterator(4, 5) << 4 << 1;
    QTest::newRow("5: random iterator, random iterator") << m_SecondaryIntMatrix.getConstDIterator(2, 3) << m_SecondaryIntMatrix.getConstDIterator({1, 4}) << 4 << 0;
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

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << 5 << m_PrimaryIntMatrix.getConstDIterator(3, 4);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.constDEnd(1) << -9 << m_PrimaryIntMatrix.constDEnd(1);
}

void ConstDIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constDBegin(1) << m_PrimaryIntMatrix.getConstDIterator(1, 2);
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 2) << m_PrimaryIntMatrix.constDEnd(1);
}

void ConstDIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstDIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constDBegin(-1) << m_PrimaryIntMatrix.getConstDIterator(1, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(1, 0) << m_PrimaryIntMatrix.getConstDIterator(2, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator(2, 1) << m_PrimaryIntMatrix.getConstDIterator({-1, 1});
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << m_PrimaryIntMatrix.constDEnd(-1);
}

void ConstDIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixConstDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstDIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constDBegin(-1) << -1 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constDBegin(-1) << 2 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("3: begin iterator, end iterator") << m_PrimaryIntMatrix.constDBegin(-1) << 3 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("4: begin iterator, end iterator") << m_PrimaryIntMatrix.constDBegin(-1) << 4 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << -2 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("6: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << -1 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << 0 << m_PrimaryIntMatrix.getConstDIterator(2, 1);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << 1 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("9: random iterator, end iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << 2 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstDIterator({-1, 1}) << 3 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.constDEnd(-1) << -4 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("12: end iterator, begin iterator") << m_PrimaryIntMatrix.constDEnd(-1) << -3 << m_PrimaryIntMatrix.constDBegin(1, 0);
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.constDEnd(-1) << -1 << m_PrimaryIntMatrix.getConstDIterator(3, 2);
    QTest::newRow("14: end iterator, end iterator") << m_PrimaryIntMatrix.constDEnd(-1) << 1 << m_PrimaryIntMatrix.constDEnd(1, 0);
    QTest::newRow("15: begin iterator, begin iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << -2 << m_SecondaryIntMatrix.constDBegin(0, 1);
    QTest::newRow("16: begin iterator, begin iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << -1 << m_SecondaryIntMatrix.constDBegin(0, 1);
    QTest::newRow("17: begin iterator, random iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << 2 << m_SecondaryIntMatrix.getConstDIterator(2, 3);
    QTest::newRow("18: begin iterator, end iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << 3 << m_SecondaryIntMatrix.constDEnd(0, 1);
    QTest::newRow("19: begin iterator, end iterator") << m_SecondaryIntMatrix.constDBegin(0, 1) << 4 << m_SecondaryIntMatrix.constDEnd(0, 1);
}

QTEST_APPLESS_MAIN(ConstDIteratorTests)

#include "tst_constditeratortests.moc"
