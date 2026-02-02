#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntConstReverseNIter)
Q_DECLARE_METATYPE(StringConstReverseNIter)
Q_DECLARE_METATYPE(IntReverseNIter)

class ConstReverseNIteratorTests : public QObject
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
    
    IntConstReverseNIter m_PrimaryIntIterator;
    IntConstReverseNIter m_SecondaryIntIterator;
    StringConstReverseNIter m_StringIterator;
};

void ConstReverseNIteratorTests::testIteratorCreation()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseNIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntReverseNIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    
    IntConstReverseNIter constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseNIteratorTests::testEmptyIterator()
{
    IntConstReverseNIter emptyIt;
    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ConstReverseNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntConstReverseNIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstReverseNIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseNIteratorTests::testLessThanOperator()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstReverseNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntConstReverseNIter, inputIterator);
    QFETCH(IntConstReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntConstReverseNIter, inputIterator);
    QFETCH(IntConstReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntConstReverseNIter, inputIterator);
    QFETCH(IntConstReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntConstReverseNIter, inputIterator);
    QFETCH(IntConstReverseNIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorPlus()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseNIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorMinus()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseNIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseNIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseNIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntConstReverseNIter, firstIterator);
    QFETCH(IntConstReverseNIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseNIteratorTests::testAsteriskOperator()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ConstReverseNIteratorTests::testAsteriskOperatorPlusEqual()
{
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(5, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(5, 2);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with column capacity offset
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntMatrix.reserve(3, 4);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNBegin();
    m_PrimaryIntMatrix.at(0, 1) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);
}

void ConstReverseNIteratorTests::testArrowOperator()
{
    QFETCH(StringConstReverseNIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseNIteratorTests::testArrowOperatorPlusEqual()
{
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_StringIterator = m_PrimaryStringMatrix.constReverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row/column capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.reserve(5, 4);
    m_StringIterator = m_PrimaryStringMatrix.constReverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.reserve(5, 2);
    m_StringIterator = m_PrimaryStringMatrix.constReverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with column capacity offset
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_PrimaryStringMatrix.reserve(3, 4);
    m_StringIterator = m_PrimaryStringMatrix.constReverseNBegin();
    m_PrimaryStringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstReverseNIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntConstReverseNIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseNIteratorTests::testStdCount()
{
    QFETCH(IntConstReverseNIter, leftIterator);
    QFETCH(IntConstReverseNIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseNIteratorTests::testStdFind()
{
    QFETCH(IntConstReverseNIter, leftIterator);
    QFETCH(IntConstReverseNIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntConstReverseNIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstReverseNIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constReverseNBegin(), m_PrimaryIntMatrix.constReverseNEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.constReverseNBegin(), m_PrimaryIntMatrix.constReverseNEnd(), 10) == m_PrimaryIntMatrix.constReverseNEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");
}

void ConstReverseNIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseNIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("3: column begin iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(0) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("4: column begin iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{1u};
    QTest::newRow("5: column begin iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{4u};
    QTest::newRow("6: column begin iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("7: column begin iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("8: column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("9: column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("10: column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{3u};
    QTest::newRow("11: column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{6u};
    QTest::newRow("12: column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("18: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("19: end iterator") << m_SecondaryIntMatrix.constReverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstReverseNIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseNIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseNBegin() << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.reverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("3: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("4: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{1u};
    QTest::newRow("5: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{4u};
    QTest::newRow("6: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("7: column begin iterator") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("8: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << matrix_opt_size_t{} << matrix_opt_size_t{0u};
    QTest::newRow("9: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("10: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(4) << matrix_opt_size_t{7u} << matrix_opt_size_t{3u};
    QTest::newRow("11: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{6u};
    QTest::newRow("12: column end iterator") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << matrix_opt_size_t{4u} << matrix_opt_size_t{5u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << matrix_opt_size_t{7u} << matrix_opt_size_t{8u};
    QTest::newRow("18: begin iterator") << m_SecondaryIntMatrix.reverseNBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("19: end iterator") << m_SecondaryIntMatrix.reverseNEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstReverseNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseNIter>("firstIterator");
    QTest::addColumn<IntConstReverseNIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("7: column begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(0) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 0);
    QTest::newRow("8: column begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 1);
    QTest::newRow("9: column begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 5);
    QTest::newRow("10: column begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(7) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 7);
    QTest::newRow("11: column begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("12: column end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("13: column end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 0);
    QTest::newRow("14: column end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("15: column end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(7) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 6);
    QTest::newRow("16: column end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 7);
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstReverseNIter>("iterator");

    QTest::newRow("1: end iterator")  << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("2: random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("3: random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("4: random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("5: random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("6: random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("7: begin iterator")  << m_PrimaryIntMatrix.constReverseNBegin();
}

void ConstReverseNIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseNIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseNIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseNIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseNIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseNIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstReverseNIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstReverseNIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstReverseNIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstReverseNIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseNIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseNIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseNIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseNIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseNIter>("firstIterator");
    QTest::addColumn<IntConstReverseNIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-1};
    QTest::newRow("3: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-27};
    QTest::newRow("4: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-70};
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-71};
    QTest::newRow("6: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-72};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-26};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-69};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-70};
    QTest::newRow("12: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-71};
    QTest::newRow("13: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{27};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{26};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-43};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-44};
    QTest::newRow("18: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-45};
    QTest::newRow("19: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{70};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{69};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{43};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-1};
    QTest::newRow("24: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-2};
    QTest::newRow("25: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{44};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{1};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{0};
    QTest::newRow("30: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-1};
    QTest::newRow("31: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{72};
    QTest::newRow("32: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{71};
    QTest::newRow("33: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{45};
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{2};
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{1};
    QTest::newRow("36: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 7) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 7) << matrix_diff_t{-14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << matrix_diff_t{2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntConstReverseNIter{} << IntConstReverseNIter{} << matrix_diff_t{0};
}

void ConstReverseNIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntConstReverseNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(5, 6);

    QTest::newRow("6: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << -12;
}

void ConstReverseNIteratorTests::testArrowOperator_data()
{
    m_PrimaryStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};
    
    QTest::addColumn<StringConstReverseNIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryStringMatrix.getConstReverseNIterator(0, 0) << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getConstReverseNIterator(1, 0) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getConstReverseNIterator(2, 1) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryStringMatrix.constReverseNBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(5, 4);

    QTest::newRow("6: random iterator") << m_SecondaryStringMatrix.getConstReverseNIterator(0, 0) << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getConstReverseNIterator(1, 0) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getConstReverseNIterator(2, 1) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryStringMatrix.constReverseNBegin() << 6;
}

void ConstReverseNIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};
    
    QTest::addColumn<IntConstReverseNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{10} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{9} << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{5} << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{-1} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{4} << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{-5} << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{-6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{1} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-4} << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-9} << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-10} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-11} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(3, 6);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{10} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{9} << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{5} << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{0} << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 3) << matrix_diff_t{-1} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{4} << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{0} << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{-5} << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(2, 1) << matrix_diff_t{-6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{1} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{0} << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-4} << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-9} << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-10} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-11} << -12;
}

void ConstReverseNIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};
    
    QTest::addColumn<IntConstReverseNIter>("leftIterator");
    QTest::addColumn<IntConstReverseNIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 0) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 0) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(3, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 2) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(2, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 2) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << matrix_diff_t{1};
    QTest::newRow("12: column end iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << 8 << matrix_diff_t{2};
    QTest::newRow("13: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(3) << 9 << matrix_diff_t{1};
    QTest::newRow("14: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(2) << 9 << matrix_diff_t{2};
    QTest::newRow("15: column end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << m_PrimaryIntMatrix.constReverseNEnd() << 1 << matrix_diff_t{2};
    QTest::newRow("16: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << matrix_diff_t{1};
    QTest::newRow("17: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(2) << m_PrimaryIntMatrix.constReverseNEnd() << 1 << matrix_diff_t{3};
    QTest::newRow("18: begin iterator, column begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnBegin(2) << 1 << matrix_diff_t{0};
}

void ConstReverseNIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};
    
    QTest::addColumn<IntConstReverseNIter>("leftIterator");
    QTest::addColumn<IntConstReverseNIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntConstReverseNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("3: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 6 << m_PrimaryIntMatrix.constReverseNColumnBegin(1);
    QTest::newRow("4: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("5: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("6: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("7: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("8: column begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("9: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 6 << m_PrimaryIntMatrix.constReverseNColumnBegin(1);
    QTest::newRow("10: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("11: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 3 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("12: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << -2 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("13: column begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("14: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 11 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("15: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("16: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("17: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("18: begin iterator, column end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 7 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 3);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 2);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 4 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 11 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 11 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 2 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 3);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 9 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 3);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
}

void ConstReverseNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstReverseNIter>("firstIterator");
    QTest::addColumn<IntConstReverseNIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseNIter>("firstIterator");
    QTest::addColumn<IntConstReverseNIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNBegin();
}

void ConstReverseNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstReverseNIter>("inputIterator");
    QTest::addColumn<IntConstReverseNIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(5, 8);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    
    QTest::addColumn<IntConstReverseNIter>("inputIterator");
    QTest::addColumn<IntConstReverseNIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8) << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin();
}

void ConstReverseNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{8, 9}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseNIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntConstReverseNIter>("expectedIterator");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("3: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("4: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("5: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("6: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-11} << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("8: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("9: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("10: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{4} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-10} << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("20: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("21: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-72} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("22: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << matrix_diff_t{-74} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("23: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{5} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("24: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-9} << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("31: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << matrix_diff_t{-73} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{48} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{46} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{45} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{44} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{43} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{6} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4);
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{2} << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getConstReverseNIterator(2, 6);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-26} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("45: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-27} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("46: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-28} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("47: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << matrix_diff_t{-30} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("48: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{74} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("49: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{72} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("50: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{71} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{69} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{24} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{3} << m_PrimaryIntMatrix.getConstReverseNIterator(3, 8);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("56: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("57: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-2} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("58: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << matrix_diff_t{-4} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("59: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("60: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("61: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("62: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("63: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("64: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{25} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("65: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getConstReverseNIterator(3, 8);
    QTest::newRow("66: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("67: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("68: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("69: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseNBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseNBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseNEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseNEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseNEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntConstReverseNIter{} << matrix_diff_t{-1} << IntConstReverseNIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntConstReverseNIter{} << matrix_diff_t{1} << IntConstReverseNIter{};
}

QTEST_APPLESS_MAIN(ConstReverseNIteratorTests)

#include "tst_constreverseniteratortests.moc"
