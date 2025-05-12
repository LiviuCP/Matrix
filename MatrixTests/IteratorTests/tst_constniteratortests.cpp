#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntConstNIter)
Q_DECLARE_METATYPE(StringConstNIter)
Q_DECLARE_METATYPE(IntNIter)

class ConstNIteratorTests : public QObject
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
    void testAsteriskOperator();
    void testAsteriskOperatorPlusEqual();
    void testArrowOperator();
    void testArrowOperatorPlusEqual();
    void testSquareBracketsOperator();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrement();

    // test data
    void testIteratorCreation_data();
    void testIteratorCreationFromNonConstIterator_data();
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
    void testAsteriskOperator_data();
    void testArrowOperator_data();
    void testSquareBracketsOperator_data();
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
    
    IntConstNIter m_PrimaryIntIterator;
    IntConstNIter m_SecondaryIntIterator;
    StringConstNIter m_StringIterator;
};

void ConstNIteratorTests::testIteratorCreation()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstNIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntNIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    
    IntNIter constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstNIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    IntConstNIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ConstNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntConstNIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstNIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstNIteratorTests::testLessThanOperator()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntConstNIter, inputIterator);
    QFETCH(IntConstNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntConstNIter, inputIterator);
    QFETCH(IntConstNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntConstNIter, inputIterator);
    QFETCH(IntConstNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntConstNIter, inputIterator);
    QFETCH(IntConstNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testOperatorPlus()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstNIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorMinus()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstNIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstNIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstNIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntConstNIter, firstIterator);
    QFETCH(IntConstNIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstNIteratorTests::testAsteriskOperator()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ConstNIteratorTests::testAsteriskOperatorPlusEqual()
{
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNBegin();
    m_PrimaryIntMatrix.at(2, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(5, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNBegin();
    m_PrimaryIntMatrix.at(2, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(5, 2);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNBegin();
    m_PrimaryIntMatrix.at(2, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with column capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNBegin();
    m_PrimaryIntMatrix.at(2, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);
}

void ConstNIteratorTests::testArrowOperator()
{
    QFETCH(StringConstNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstNIteratorTests::testArrowOperatorPlusEqual()
{
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.constNBegin();
    m_PrimaryStringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row/column capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_PrimaryStringMatrix.reserve(5, 4);
    m_StringIterator = m_PrimaryStringMatrix.constNBegin();
    m_PrimaryStringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_PrimaryStringMatrix.reserve(5, 2);
    m_StringIterator = m_PrimaryStringMatrix.constNBegin();
    m_PrimaryStringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with column capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_PrimaryStringMatrix.reserve(3, 4);
    m_StringIterator = m_PrimaryStringMatrix.constNBegin();
    m_PrimaryStringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstNIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntConstNIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstNIteratorTests::testStdCount()
{
    QFETCH(IntConstNIter, leftIterator);
    QFETCH(IntConstNIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstNIteratorTests::testStdFind()
{
    QFETCH(IntConstNIter, leftIterator);
    QFETCH(IntConstNIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntConstNIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstNIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constNBegin(), m_PrimaryIntMatrix.constNEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.constNBegin(), m_PrimaryIntMatrix.constNEnd(), 10) == m_PrimaryIntMatrix.constNEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");
}

void ConstNIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstNIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_opt_size_t{8u} << matrix_opt_size_t{8u};
    QTest::newRow("3: column begin iterator") << m_PrimaryIntMatrix.constNColumnBegin(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: column begin iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: column begin iterator") << m_PrimaryIntMatrix.constNColumnBegin(4) << matrix_opt_size_t{0u} << matrix_opt_size_t{4u};
    QTest::newRow("6: column begin iterator") << m_PrimaryIntMatrix.constNColumnBegin(7) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("7: column begin iterator") << m_PrimaryIntMatrix.constNColumnBegin(8) << matrix_opt_size_t{0u} << matrix_opt_size_t{8u};
    QTest::newRow("8: column end iterator") << m_PrimaryIntMatrix.constNColumnEnd(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: column end iterator") << m_PrimaryIntMatrix.constNColumnEnd(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("10: column end iterator") << m_PrimaryIntMatrix.constNColumnEnd(4) << matrix_opt_size_t{0u} << matrix_opt_size_t{5u};
    QTest::newRow("11: column end iterator") << m_PrimaryIntMatrix.constNColumnEnd(7) << matrix_opt_size_t{0u} << matrix_opt_size_t{8u};
    QTest::newRow("12: column end iterator") << m_PrimaryIntMatrix.constNColumnEnd(8) << matrix_opt_size_t{8u} << matrix_opt_size_t{8u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstNIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstNIterator(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstNIterator(44) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstNIterator(70) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstNIterator(71) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.constNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstNIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntNIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.nBegin() << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.nEnd() << matrix_opt_size_t{8u} << matrix_opt_size_t{8u};
    QTest::newRow("3: column begin iterator") << m_PrimaryIntMatrix.nColumnBegin(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: column begin iterator") << m_PrimaryIntMatrix.nColumnBegin(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: column begin iterator") << m_PrimaryIntMatrix.nColumnBegin(4) << matrix_opt_size_t{0u} << matrix_opt_size_t{4u};
    QTest::newRow("6: column begin iterator") << m_PrimaryIntMatrix.nColumnBegin(7) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("7: column begin iterator") << m_PrimaryIntMatrix.nColumnBegin(8) << matrix_opt_size_t{0u} << matrix_opt_size_t{8u};
    QTest::newRow("8: column end iterator") << m_PrimaryIntMatrix.nColumnEnd(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: column end iterator") << m_PrimaryIntMatrix.nColumnEnd(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("10: column end iterator") << m_PrimaryIntMatrix.nColumnEnd(4) << matrix_opt_size_t{0u} << matrix_opt_size_t{5u};
    QTest::newRow("11: column end iterator") << m_PrimaryIntMatrix.nColumnEnd(7) << matrix_opt_size_t{0u} << matrix_opt_size_t{8u};
    QTest::newRow("12: column end iterator") << m_PrimaryIntMatrix.nColumnEnd(8) << matrix_opt_size_t{8u} << matrix_opt_size_t{8u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getNIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getNIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getNIterator(4, 5) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getNIterator(6, 8) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getNIterator(7, 8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getNIterator(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getNIterator(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getNIterator(44) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getNIterator(70) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getNIterator(71) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.nBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.nEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstNIter>("firstIterator");
    QTest::addColumn<IntConstNIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(0) << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(44) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(70) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(71) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("7: column begin iterator, random iterator") << m_PrimaryIntMatrix.constNColumnBegin(0) << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("8: column begin iterator, random iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.getConstNIterator(0, 1);
    QTest::newRow("9: column begin iterator, random iterator") << m_PrimaryIntMatrix.constNColumnBegin(5) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("10: column begin iterator, random iterator") << m_PrimaryIntMatrix.constNColumnBegin(7) << m_PrimaryIntMatrix.getConstNIterator(0, 7);
    QTest::newRow("11: column begin iterator, random iterator") << m_PrimaryIntMatrix.constNColumnBegin(8) << m_PrimaryIntMatrix.getConstNIterator(0, 8);
    QTest::newRow("12: column end iterator, random iterator") << m_PrimaryIntMatrix.constNColumnEnd(0) << m_PrimaryIntMatrix.getConstNIterator(0, 1);
    QTest::newRow("13: column end iterator, random iterator") << m_PrimaryIntMatrix.constNColumnEnd(1) << m_PrimaryIntMatrix.getConstNIterator(0, 2);
    QTest::newRow("14: column end iterator, random iterator") << m_PrimaryIntMatrix.constNColumnEnd(5) << m_PrimaryIntMatrix.getConstNIterator(0, 6);
    QTest::newRow("15: column end iterator, random iterator") << m_PrimaryIntMatrix.constNColumnEnd(7) << m_PrimaryIntMatrix.getConstNIterator(0, 8);
    QTest::newRow("16: column end iterator, end iterator") << m_PrimaryIntMatrix.constNColumnEnd(8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstNIter>("iterator");

    QTest::newRow("1: begin iterator")  << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("7: end iterator")  << m_PrimaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstNIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstNIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstNIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstNIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstNIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstNIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstNIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstNIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstNIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstNIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstNIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstNIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstNIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstNIter>("firstIterator");
    QTest::addColumn<IntConstNIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{1};
    QTest::newRow("3: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{2};
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{28};
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{71};
    QTest::newRow("6: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{72};
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{1};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{27};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{70};
    QTest::newRow("12: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{71};
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-2};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-1};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{26};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{69};
    QTest::newRow("18: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{70};
    QTest::newRow("19: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-28};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-27};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-26};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{43};
    QTest::newRow("24: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{44};
    QTest::newRow("25: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-69};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-43};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{0};
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{1};
    QTest::newRow("31: end iterator, begin iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-72};
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-71};
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-70};
    QTest::newRow("34: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-44};
    QTest::newRow("35: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-1};
    QTest::newRow("36: begin iterator, begin iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 7) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 7) << matrix_diff_t{14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 5) << matrix_diff_t{-2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntConstNIter{} << IntConstNIter{} << matrix_diff_t{0};
}

void ConstNIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntConstNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constNBegin() << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(5, 6);

    QTest::newRow("6: begin iterator") << m_SecondaryIntMatrix.constNBegin() << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << -12;
}

void ConstNIteratorTests::testArrowOperator_data()
{
    m_PrimaryStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    
    QTest::addColumn<StringConstNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.constNBegin() << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getConstNIterator(1, 0) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getConstNIterator(2, 1) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryStringMatrix.getConstNIterator(2, 3) << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(5, 4);

    QTest::newRow("6: begin iterator") << m_SecondaryStringMatrix.constNBegin() << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getConstNIterator(1, 0) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getConstNIterator(2, 1) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryStringMatrix.getConstNIterator(2, 3) << 6;
}

void ConstNIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntConstNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{0} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{1} << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{5} << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{10} << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{11} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-1} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{4} << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{9} << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{10} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{-5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{-4} << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{5} << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-10} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-9} << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-5} << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{1} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-11} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-10} << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-6} << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-1} << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{0} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(3, 6);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{0} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{1} << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{5} << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{10} << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{11} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-1} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{4} << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{9} << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{10} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{-5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{-4} << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{5} << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 1) << matrix_diff_t{6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-10} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-9} << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{-5} << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getConstNIterator(1, 3) << matrix_diff_t{1} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-11} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-10} << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-6} << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{-1} << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getConstNIterator(2, 3) << matrix_diff_t{0} << -12;
}

void ConstNIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};
    
    QTest::addColumn<IntConstNIter>("leftIterator");
    QTest::addColumn<IntConstNIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 1) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 1) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 0) << m_PrimaryIntMatrix.getConstNIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(3, 2) << 2 << matrix_diff_t{2};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 2) << m_PrimaryIntMatrix.constNEnd() << 2 << matrix_diff_t{1};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(2, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 2) << m_PrimaryIntMatrix.constNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2) << m_PrimaryIntMatrix.getConstNIterator(9) << 1 << matrix_diff_t{1};
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2) << m_PrimaryIntMatrix.getConstNIterator(10) << 1 << matrix_diff_t{2};
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3) << m_PrimaryIntMatrix.getConstNIterator(9) << 1 << matrix_diff_t{1};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3) << m_PrimaryIntMatrix.getConstNIterator(10) << 1 << matrix_diff_t{2};
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(13) << 2 << matrix_diff_t{2};
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(13) << m_PrimaryIntMatrix.constNEnd() << 2 << matrix_diff_t{1};
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(12) << 2 << matrix_diff_t{1};
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(12) << m_PrimaryIntMatrix.constNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("19: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 1 << matrix_diff_t{1};
    QTest::newRow("20: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(2) << 8 << matrix_diff_t{2};
    QTest::newRow("21: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(2) << m_PrimaryIntMatrix.constNColumnEnd(2) << 9 << matrix_diff_t{1};
    QTest::newRow("22: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(2) << m_PrimaryIntMatrix.constNColumnEnd(3) << 9 << matrix_diff_t{2};
    QTest::newRow("23: begin iterator, column begin iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnBegin(1) << 1 << matrix_diff_t{2};
    QTest::newRow("24: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 1 << matrix_diff_t{1};
    QTest::newRow("25: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 1 << matrix_diff_t{3};
    QTest::newRow("26: column end iterator, end iterator") << m_PrimaryIntMatrix.constNColumnEnd(1) << m_PrimaryIntMatrix.constNEnd() << 1 << matrix_diff_t{0};
}

void ConstNIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};
    
    QTest::addColumn<IntConstNIter>("leftIterator");
    QTest::addColumn<IntConstNIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntConstNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("3: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("4: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 6 << m_PrimaryIntMatrix.getConstNIterator(4, 1);
    QTest::newRow("5: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("6: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("7: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << -2 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("8: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("9: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("10: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 11 << m_PrimaryIntMatrix.getConstNIterator(19);
    QTest::newRow("11: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("12: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << -1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("13: column begin iterator, end iterator") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("14: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("15: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 6 << m_PrimaryIntMatrix.getConstNIterator(9);
    QTest::newRow("16: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("17: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << -2 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("18: begin iterator, column end iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getConstNIterator(3, 1);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstNIterator(0, 3);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -1 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 0 << m_PrimaryIntMatrix.getConstNIterator(3, 1);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 11 << m_PrimaryIntMatrix.getConstNIterator(19);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << -1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstNIterator(0, 3);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
}

void ConstNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstNIter>("firstIterator");
    QTest::addColumn<IntConstNIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstNIter>("firstIterator");
    QTest::addColumn<IntConstNIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNBegin();
}

void ConstNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstNIter>("inputIterator");
    QTest::addColumn<IntConstNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(6, 4) << m_PrimaryIntMatrix.getConstNIterator(7, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(7, 4) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(0, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(1, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 5);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstNIter>("inputIterator");
    QTest::addColumn<IntConstNIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(5, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(2, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(1, 5) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(0, 5) << m_PrimaryIntMatrix.getConstNIterator(7, 4);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(7, 4) << m_PrimaryIntMatrix.getConstNIterator(6, 4);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin();
}

void ConstNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntConstNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("3: begin iterator, begin iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("4: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("5: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getConstNIterator(4, 0);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{10} << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("8: begin iterator, random iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("9: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("10: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("11: begin iterator, end iterator") << m_PrimaryIntMatrix.constNBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("12: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("13: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-2} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("14: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{3} << m_PrimaryIntMatrix.getConstNIterator(4, 0);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{9} << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{69} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("20: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{71} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("21: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{72} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("22: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << matrix_diff_t{74} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("23: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-47} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("24: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-45} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("25: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-44} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-43} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getConstNIterator(6, 4);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstNIterator(2, 5);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{2} << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("31: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{6} << m_PrimaryIntMatrix.getConstNIterator(2, 6);
    QTest::newRow("32: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{26} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("33: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{27} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{28} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{29} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << matrix_diff_t{31} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("37: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-73} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("38: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("39: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-70} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-24} << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("45: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{2} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("46: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{3} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("47: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << matrix_diff_t{5} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("48: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-74} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("49: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-72} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("50: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-25} << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("56: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{1} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("57: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{2} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("58: random iterator, end iterator") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << matrix_diff_t{4} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("59: end iterator, begin iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("60: end iterator, begin iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("61: end iterator, begin iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("62: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("63: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-26} << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("64: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("65: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("66: end iterator, random iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("67: end iterator, end iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("68: end iterator, end iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("69: end iterator, end iterator") << m_PrimaryIntMatrix.constNEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.constNBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.constNEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.constNEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.constNEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntConstNIter{} << matrix_diff_t{-1} << IntConstNIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntConstNIter{} << matrix_diff_t{1} << IntConstNIter{};
}

QTEST_APPLESS_MAIN(ConstNIteratorTests)

#include "tst_constniteratortests.moc"
