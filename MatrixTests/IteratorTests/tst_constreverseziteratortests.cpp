#include <QTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntConstReverseZIter)
Q_DECLARE_METATYPE(StringConstReverseZIter)
Q_DECLARE_METATYPE(IntReverseZIter)

class ConstReverseZIteratorTests : public QObject
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
    
    IntConstReverseZIter m_PrimaryIntIterator;
    IntConstReverseZIter m_SecondaryIntIterator;
    StringConstReverseZIter m_StringIterator;
};

void ConstReverseZIteratorTests::testIteratorCreation()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntReverseZIter, iterator);
    QFETCH(matrix_opt_size_t, expectedRowNr);
    QFETCH(matrix_opt_size_t, expectedColumnNr);
    
    IntConstReverseZIter constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    IntConstReverseZIter emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntConstReverseZIter, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstReverseZIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseZIteratorTests::testLessThanOperator()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstReverseZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntConstReverseZIter, inputIterator);
    QFETCH(IntConstReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntConstReverseZIter, inputIterator);
    QFETCH(IntConstReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 4),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 6),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntConstReverseZIter, inputIterator);
    QFETCH(IntConstReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntConstReverseZIter, inputIterator);
    QFETCH(IntConstReverseZIter, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 6),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 4),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorPlus()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseZIter, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorMinus()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseZIter, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseZIter, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_diff_t, scalarValue);
    QFETCH(IntConstReverseZIter, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntConstReverseZIter, firstIterator);
    QFETCH(IntConstReverseZIter, secondIterator);
    QFETCH(matrix_diff_t, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseZIteratorTests::testAsteriskOperator()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ConstReverseZIteratorTests::testAsteriskOperatorPlusEqual()
{
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(4, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with column capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.reserve(2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

}

void ConstReverseZIteratorTests::testArrowOperator()
{
    QFETCH(StringConstReverseZIter, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseZIteratorTests::testArrowOperatorPlusEqual()
{
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row/column capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.reserve(4, 5);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.reserve(4, 3);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with column capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.reserve(2, 5);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstReverseZIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntConstReverseZIter, iterator);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseZIteratorTests::testStdCount()
{
    QFETCH(IntConstReverseZIter, leftIterator);
    QFETCH(IntConstReverseZIter, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(matrix_diff_t, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseZIteratorTests::testStdFind()
{
    QFETCH(IntConstReverseZIter, leftIterator);
    QFETCH(IntConstReverseZIter, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntConstReverseZIter, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstReverseZIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constReverseZBegin(), m_PrimaryIntMatrix.constReverseZEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.constReverseZBegin(), m_PrimaryIntMatrix.constReverseZEnd(), 10) == m_PrimaryIntMatrix.constReverseZEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");
}

void ConstReverseZIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseZIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_opt_size_t{0u} << matrix_opt_size_t{};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{7u};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(4) << matrix_opt_size_t{4u} << matrix_opt_size_t{7u};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(8) << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(4) << matrix_opt_size_t{3u} << matrix_opt_size_t{7u};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(7) << matrix_opt_size_t{6u} << matrix_opt_size_t{7u};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_opt_size_t{5u} << matrix_opt_size_t{4u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_opt_size_t{8u} << matrix_opt_size_t{6u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7) << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("18: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("19: end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstReverseZIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntReverseZIter>("iterator");
    QTest::addColumn<matrix_opt_size_t>("expectedRowNr");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.reverseZEnd() << matrix_opt_size_t{0u} << matrix_opt_size_t{};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << matrix_opt_size_t{1u} << matrix_opt_size_t{7u};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(4) << matrix_opt_size_t{4u} << matrix_opt_size_t{7u};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(7) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(8) << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(0) << matrix_opt_size_t{0u} << matrix_opt_size_t{};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(1) << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(4) << matrix_opt_size_t{3u} << matrix_opt_size_t{7u};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(7) << matrix_opt_size_t{6u} << matrix_opt_size_t{7u};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(8) << matrix_opt_size_t{7u} << matrix_opt_size_t{7u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << matrix_opt_size_t{5u} << matrix_opt_size_t{4u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << matrix_opt_size_t{8u} << matrix_opt_size_t{6u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << matrix_opt_size_t{8u} << matrix_opt_size_t{7u};
    QTest::newRow("18: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("19: end iterator") << m_SecondaryIntMatrix.reverseZEnd() << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void ConstReverseZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseZIter>("firstIterator");
    QTest::addColumn<IntConstReverseZIter>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
    QTest::newRow("7: row begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 7);
    QTest::newRow("8: row begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 7);
    QTest::newRow("9: row begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(5) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 7);
    QTest::newRow("10: row begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(7) << m_PrimaryIntMatrix.getConstReverseZIterator(7, 7);
    QTest::newRow("11: row begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(8) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
    QTest::newRow("12: row end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(0) << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: row end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 7);
    QTest::newRow("14: row end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(5) << m_PrimaryIntMatrix.getConstReverseZIterator(4, 7);
    QTest::newRow("15: row end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(7) << m_PrimaryIntMatrix.getConstReverseZIterator(6, 7);
    QTest::newRow("16: row end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(8) << m_PrimaryIntMatrix.getConstReverseZIterator(7, 7);
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZEnd();
}

void ConstReverseZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntConstReverseZIter>("iterator");

    QTest::newRow("1: end iterator")  << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("2: random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("3: random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("4: random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("5: random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("6: random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
    QTest::newRow("7: begin iterator")  << m_PrimaryIntMatrix.constReverseZBegin();
}

void ConstReverseZIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseZIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseZIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseZIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstReverseZIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstReverseZIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstReverseZIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstReverseZIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstReverseZIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstReverseZIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseZIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseZIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseZIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstReverseZIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseZIter>("firstIterator");
    QTest::addColumn<IntConstReverseZIter>("secondIterator");
    QTest::addColumn<matrix_diff_t>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{0};
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-1};
    QTest::newRow("3: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-27};
    QTest::newRow("4: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-70};
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-71};
    QTest::newRow("6: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-72};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{1};
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{0};
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-26};
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-69};
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-70};
    QTest::newRow("12: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-71};
    QTest::newRow("13: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{27};
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{26};
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{0};
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-43};
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-44};
    QTest::newRow("18: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-45};
    QTest::newRow("19: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{70};
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{69};
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{43};
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{0};
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-1};
    QTest::newRow("24: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-2};
    QTest::newRow("25: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{71};
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{70};
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{44};
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{1};
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{0};
    QTest::newRow("30: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-1};
    QTest::newRow("31: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{72};
    QTest::newRow("32: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{71};
    QTest::newRow("33: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{45};
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{2};
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{1};
    QTest::newRow("36: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{0};
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(7, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{14};
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(7, 2) << matrix_diff_t{-14};
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-2};
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2) << matrix_diff_t{2};
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZEnd() << matrix_diff_t{0};
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{0};
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{0};
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << matrix_diff_t{0};
    QTest::newRow("45: empty iterator, empty iterator") << IntConstReverseZIter{} << IntConstReverseZIter{} << matrix_diff_t{0};
}

void ConstReverseZIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    
    QTest::addColumn<IntConstReverseZIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(6, 5);

    QTest::newRow("6: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << -12;
}

void ConstReverseZIteratorTests::testArrowOperator_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};
    
    QTest::addColumn<StringConstReverseZIter>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(0, 0) << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(0, 1) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(1, 2) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryStringMatrix.constReverseZBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.reserve(6, 3);

    QTest::newRow("6: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(0, 0) << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(0, 1) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(1, 2) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryStringMatrix.constReverseZBegin() << 6;
}

void ConstReverseZIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};
    
    QTest::addColumn<IntConstReverseZIter>("iterator");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{10} << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{9} << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{5} << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{0} << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{-1} << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{5} << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{4} << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{0} << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{-5} << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{-6} << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{1} << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{0} << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-4} << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-9} << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-10} << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-11} << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.reserve(4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{11} << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{10} << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{6} << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{1} << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{0} << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{10} << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{9} << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{5} << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{0} << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << matrix_diff_t{-1} << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{5} << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{4} << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{0} << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{-5} << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << matrix_diff_t{-6} << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{1} << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{0} << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-4} << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-9} << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-10} << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{0} << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-1} << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-5} << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-10} << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-11} << -12;
}

void ConstReverseZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};
    
    QTest::addColumn<IntConstReverseZIter>("leftIterator");
    QTest::addColumn<IntConstReverseZIter>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<matrix_diff_t>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 2 << matrix_diff_t{3};
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << -5 << matrix_diff_t{0};
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 3) << 1 << matrix_diff_t{1};
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << 1 << matrix_diff_t{2};
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(2, 3) << 2 << matrix_diff_t{1};
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(2, 2) << 2 << matrix_diff_t{1};
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 2) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << matrix_diff_t{2};
    QTest::newRow("11: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << matrix_diff_t{1};
    QTest::newRow("12: row end iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(3) << m_PrimaryIntMatrix.constReverseZRowEnd(0) << 8 << matrix_diff_t{2};
    QTest::newRow("13: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(3) << m_PrimaryIntMatrix.constReverseZRowEnd(3) << 9 << matrix_diff_t{1};
    QTest::newRow("14: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(3) << m_PrimaryIntMatrix.constReverseZRowEnd(2) << 9 << matrix_diff_t{2};
    QTest::newRow("15: row end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(1) << m_PrimaryIntMatrix.constReverseZEnd() << 1 << matrix_diff_t{2};
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << matrix_diff_t{1};
    QTest::newRow("17: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(2) << m_PrimaryIntMatrix.constReverseZEnd() << 1 << matrix_diff_t{3};
    QTest::newRow("18: begin iterator, row begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowBegin(2) << 1 << matrix_diff_t{0};
}

void ConstReverseZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};
    
    QTest::addColumn<IntConstReverseZIter>("leftIterator");
    QTest::addColumn<IntConstReverseZIter>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntConstReverseZIter>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 10 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("3: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 6 << m_PrimaryIntMatrix.constReverseZRowBegin(1);
    QTest::newRow("4: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("5: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("6: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << -1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("7: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("8: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("9: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 6 << m_PrimaryIntMatrix.constReverseZRowBegin(1);
    QTest::newRow("10: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("11: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 3 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("12: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << -2 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 10 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("14: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 11 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("15: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3);
    QTest::newRow("17: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("18: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << 7 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 0);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstReverseZIterator(2, 1);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << 11 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << m_PrimaryIntMatrix.constReverseZEnd() << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 4 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 11 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 10 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 11 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 2 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 2);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 9 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 3);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
}

void ConstReverseZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntConstReverseZIter>("firstIterator");
    QTest::addColumn<IntConstReverseZIter>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd();
}

void ConstReverseZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseZIter>("firstIterator");
    QTest::addColumn<IntConstReverseZIter>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.constReverseZBegin();
}

void ConstReverseZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntConstReverseZIter>("inputIterator");
    QTest::addColumn<IntConstReverseZIter>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 5);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 5) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 1);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 0);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(4, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(4, 7) << m_PrimaryIntMatrix.getConstReverseZIterator(4, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd();
}

void ConstReverseZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    
    QTest::addColumn<IntConstReverseZIter>("inputIterator");
    QTest::addColumn<IntConstReverseZIter>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(4, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(4, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(4, 7) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 0);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 1);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7) << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin();
}

void ConstReverseZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {{9, 8}, -5};
    m_SecondaryIntMatrix.clear();
    
    QTest::addColumn<IntConstReverseZIter>("iterator");
    QTest::addColumn<matrix_diff_t>("scalarValue");
    QTest::addColumn<IntConstReverseZIter>("expectedIterator");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{1} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("3: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{0} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("4: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("5: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("6: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-5} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-11} << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("8: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-71} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("9: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-72} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("10: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-73} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << matrix_diff_t{-75} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{4} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{2} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{1} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-1} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-4} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-10} << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-70} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("20: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("21: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-72} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("22: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << matrix_diff_t{-74} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("23: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{5} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("24: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{3} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{2} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-3} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-9} << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-69} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("31: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-70} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-71} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << matrix_diff_t{-73} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{48} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{46} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{45} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{44} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{43} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{6} << m_PrimaryIntMatrix.getConstReverseZIterator(4, 6);
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{2} << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-2} << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-6} << m_PrimaryIntMatrix.getConstReverseZIterator(6, 2);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-26} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("45: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-27} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("46: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-28} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("47: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << matrix_diff_t{-30} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("48: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{74} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("49: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{72} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("50: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{71} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{69} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{24} << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{3} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 3);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{0} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("56: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("57: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-2} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("58: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << matrix_diff_t{-4} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("50: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{75} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("60: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{73} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("61: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{72} << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("62: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{71} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("63: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{70} << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("64: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{25} << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("65: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{4} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 3);
    QTest::newRow("66: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{1} << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("67: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{0} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("68: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-1} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("69: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << matrix_diff_t{-3} << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << matrix_diff_t{1} << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << matrix_diff_t{0} << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << matrix_diff_t{1} << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << matrix_diff_t{-1} << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntConstReverseZIter{} << matrix_diff_t{-1} << IntConstReverseZIter{};
    QTest::newRow("76: empty iterator, empty iterator") << IntConstReverseZIter{} << matrix_diff_t{1} << IntConstReverseZIter{};
}

QTEST_APPLESS_MAIN(ConstReverseZIteratorTests)

#include "tst_constreverseziteratortests.moc"
