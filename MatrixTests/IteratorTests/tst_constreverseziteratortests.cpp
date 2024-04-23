#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstReverseZIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseZIterator)
Q_DECLARE_METATYPE(IntMatrixReverseZIterator)

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

    IntMatrixConstReverseZIterator m_PrimaryIntIterator;
    IntMatrixConstReverseZIterator m_SecondaryIntIterator;
    StringMatrixConstReverseZIterator m_StringIterator;
};

void ConstReverseZIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixReverseZIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);

    IntMatrixConstReverseZIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixConstReverseZIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
}

void ConstReverseZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);

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
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseZIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstReverseZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, inputIterator);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, inputIterator);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

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
    QFETCH(IntMatrixConstReverseZIterator, inputIterator);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, inputIterator);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

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
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, firstIterator);
    QFETCH(IntMatrixConstReverseZIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseZIteratorTests::testAsteriskOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
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
    m_PrimaryIntMatrix.resize(2, 3, 4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 4, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with column capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseZBegin();
    m_PrimaryIntMatrix.at(1, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

}

void ConstReverseZIteratorTests::testArrowOperator()
{
    QFETCH(StringMatrixConstReverseZIterator, iterator);
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
    m_PrimaryStringMatrix.resize(2, 3, 4, 5);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.resize(2, 3, 4, 3);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with column capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
    m_PrimaryStringMatrix.resize(2, 3, 2, 5);
    m_StringIterator = m_PrimaryStringMatrix.constReverseZBegin();
    m_PrimaryStringMatrix.at(1, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstReverseZIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstReverseZIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseZIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstReverseZIterator, leftIterator);
    QFETCH(IntMatrixConstReverseZIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseZIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstReverseZIterator, leftIterator);
    QFETCH(IntMatrixConstReverseZIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstReverseZIterator, expectedIterator);

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
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 8 << 7;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << 0 << -1;
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(0) << 0 << 7;
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << 1 << 7;
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(4) << 4 << 7;
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(7) << 7 << 7;
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(8) << 8 << 7;
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(0) << 0 << -1;
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 0 << 7;
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(4) << 3 << 7;
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(7) << 6 << 7;
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(8) << 7 << 7;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 0 << 0;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 0 << 1;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 5 << 4;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 8 << 6;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7) << 8 << 7;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0) << 0 << 0;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1) << 0 << 1;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(44) << 5 << 4;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(70) << 8 << 6;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(71) << 8 << 7;
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << -1 << -1;
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << -1 << -1;
}

void ConstReverseZIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.reverseZBegin() << 8 << 7;
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.reverseZEnd() << 0 << -1;
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(0) << 0 << 7;
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(1) << 1 << 7;
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(4) << 4 << 7;
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(7) << 7 << 7;
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.reverseZRowBegin(8) << 8 << 7;
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(0) << 0 << -1;
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(1) << 0 << 7;
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(4) << 3 << 7;
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(7) << 6 << 7;
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.reverseZRowEnd(8) << 7 << 7;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 0) << 0 << 0;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0, 1) << 0 << 1;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(5, 4) << 5 << 4;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 6) << 8 << 6;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(8, 7) << 8 << 7;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(0) << 0 << 0;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(1) << 0 << 1;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(44) << 5 << 4;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(70) << 8 << 6;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getReverseZIterator(71) << 8 << 7;
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.reverseZBegin() << -1 << -1;
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.reverseZEnd() << -1 << -1;
}

void ConstReverseZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("secondIterator");

    QTest::newRow("1: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(44) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(70) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(71) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 7);
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
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstReverseZIterator>("iterator");

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
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZBegin() << 0;
    QTest::newRow("2: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.constReverseZBegin() << -1;
    QTest::newRow("3: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.constReverseZBegin() << -27;
    QTest::newRow("4: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.constReverseZBegin() << -70;
    QTest::newRow("5: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZBegin() << -71;
    QTest::newRow("6: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZBegin() << -72;
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 1;
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 0;
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -26;
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -69;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -70;
    QTest::newRow("12: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -71;
    QTest::newRow("13: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 27;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 26;
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 0;
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -43;
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -44;
    QTest::newRow("18: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -45;
    QTest::newRow("19: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 70;
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 69;
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 43;
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 0;
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -1;
    QTest::newRow("24: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -2;
    QTest::newRow("25: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 71;
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 70;
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 44;
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 1;
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 0;
    QTest::newRow("30: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -1;
    QTest::newRow("31: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 72;
    QTest::newRow("32: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.constReverseZEnd() << 71;
    QTest::newRow("33: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.constReverseZEnd() << 45;
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.constReverseZEnd() << 2;
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd() << 1;
    QTest::newRow("36: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << m_PrimaryIntMatrix.constReverseZEnd() << 0;
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(7, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 14;
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(7, 2) << -14;
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -2;
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2) << 2;
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZEnd() << 0;
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.constReverseZBegin() << 0;
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << m_SecondaryIntMatrix.constReverseZBegin() << 0;
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << m_SecondaryIntMatrix.constReverseZEnd() << 0;
    QTest::newRow("45: empty iterator, empty iterator") << IntMatrixConstReverseZIterator{} << IntMatrixConstReverseZIterator{} << 0;
}

void ConstReverseZIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstReverseZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("6: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << -12;
}

void ConstReverseZIteratorTests::testArrowOperator_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringMatrixConstReverseZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(0, 0) << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(0, 1) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(1, 2) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryStringMatrix.constReverseZBegin() << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.resize(4, 3, 6, 3);

    QTest::newRow("6: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(0, 0) << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(0, 1) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(1, 2) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getConstReverseZIterator(3, 1) << 11;
    QTest::newRow("10: begin iterator") << m_SecondaryStringMatrix.constReverseZBegin() << 6;
}

void ConstReverseZIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 11 << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 10 << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 6 << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 1 << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 0 << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 10 << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 9 << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 5 << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 0 << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << -1 << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << 5 << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << 4 << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << 0 << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << -5 << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2) << -6 << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 1 << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 0 << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -4 << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -9 << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -10 << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 0 << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -1 << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -5 << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -10 << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -11 << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 11 << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 10 << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 6 << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 1 << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 0 << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 10 << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 9 << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 5 << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << 0 << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(3, 1) << -1 << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << 5 << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << 4 << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << 0 << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << -5 << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(1, 2) << -6 << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << 1 << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << 0 << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << -4 << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << -9 << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 1) << -10 << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << 0 << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << -1 << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << -5 << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << -10 << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getConstReverseZIterator(0, 0) << -11 << -12;
}

void ConstReverseZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    QTest::addColumn<IntMatrixConstReverseZIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 2 << 3;
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << -5 << 0;
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 3) << 1 << 1;
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << 1 << 2;
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 3) << 1 << 1;
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(1, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << 1 << 2;
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(2, 3) << 2 << 1;
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 3) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << 2;
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(2, 2) << 2 << 1;
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(2, 2) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << 2;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(9) << m_PrimaryIntMatrix.getConstReverseZIterator(2) << 1 << 2;
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(10) << m_PrimaryIntMatrix.getConstReverseZIterator(2) << 1 << 2;
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(9) << m_PrimaryIntMatrix.getConstReverseZIterator(3) << 1 << 1;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(10) << m_PrimaryIntMatrix.getConstReverseZIterator(3) << 1 << 1;
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(13) << 2 << 1;
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(13) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << 2;
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(12) << 2 << 1;
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(12) << m_PrimaryIntMatrix.constReverseZEnd() << 2 << 2;
    QTest::newRow("19: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << 1;
    QTest::newRow("20: row end iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(3) << m_PrimaryIntMatrix.constReverseZRowEnd(0) << 8 << 2;
    QTest::newRow("21: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(3) << m_PrimaryIntMatrix.constReverseZRowEnd(3) << 9 << 1;
    QTest::newRow("22: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(3) << m_PrimaryIntMatrix.constReverseZRowEnd(2) << 9 << 2;
    QTest::newRow("23: row end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowEnd(1) << m_PrimaryIntMatrix.constReverseZEnd() << 1 << 2;
    QTest::newRow("24: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << 1;
    QTest::newRow("25: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(2) << m_PrimaryIntMatrix.constReverseZEnd() << 1 << 3;
    QTest::newRow("26: begin iterator, row begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowBegin(2) << 1 << 0;
}

void ConstReverseZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    QTest::addColumn<IntMatrixConstReverseZIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstReverseZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(5);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZEnd() << 10 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("3: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 6 << m_PrimaryIntMatrix.constReverseZRowBegin(1);
    QTest::newRow("4: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("5: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstReverseZIterator(7);
    QTest::newRow("6: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << -1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("7: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("8: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("9: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 6 << m_PrimaryIntMatrix.constReverseZRowBegin(1);
    QTest::newRow("10: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(0);
    QTest::newRow("11: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 3 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("12: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << -2 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: row begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZRowBegin(1) << m_PrimaryIntMatrix.constReverseZEnd() << 10 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("14: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 11 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("15: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 0);
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(8);
    QTest::newRow("17: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 1 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("18: begin iterator, row end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.constReverseZRowEnd(1) << 10 << m_PrimaryIntMatrix.constReverseZRowEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << 7 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 0);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstReverseZIterator(11);
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
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 9 << m_PrimaryIntMatrix.getConstReverseZIterator(18);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstReverseZIterator(3, 1);
}

void ConstReverseZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << m_PrimaryIntMatrix.constReverseZEnd();
}

void ConstReverseZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("secondIterator");

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
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstReverseZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("expectedIterator");

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
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstReverseZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstReverseZIterator>("expectedIterator");

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
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstReverseZIterator>("expectedIterator");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << 3 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("2: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << 1 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("3: end iterator, end iterator") << m_PrimaryIntMatrix.constReverseZEnd() << 0 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("4: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("5: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -2 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("6: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -5 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -11 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("8: end iterator, random iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -71 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("9: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -72 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("10: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -73 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("11: end iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZEnd() << -75 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 4 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("13: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 2 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("14: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 1 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -1 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -4 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -10 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -70 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("20: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -71 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("21: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -72 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("22: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0) << -74 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("23: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 5 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("24: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 3 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 2 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 1 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -3 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 4);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -9 << m_PrimaryIntMatrix.getConstReverseZIterator(1, 2);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -69 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("31: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -70 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -71 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1) << -73 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 48 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 46 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 45 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 44 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 43 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 6 << m_PrimaryIntMatrix.getConstReverseZIterator(4, 6);
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 2 << m_PrimaryIntMatrix.getConstReverseZIterator(5, 2);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -2 << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -6 << m_PrimaryIntMatrix.getConstReverseZIterator(6, 2);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -26 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("45: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -27 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("46: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -28 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("47: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(5, 4) << -30 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("48: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 74 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("49: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 72 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("50: random iterator, end iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 71 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 70 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 69 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 24 << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 3 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 3);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << 0 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("56: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -1 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("57: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -2 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("58: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6) << -4 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("50: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 75 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("60: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 73 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("61: begin iterator, end iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 72 << m_PrimaryIntMatrix.constReverseZEnd();
    QTest::newRow("62: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 71 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 0);
    QTest::newRow("63: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 70 << m_PrimaryIntMatrix.getConstReverseZIterator(0, 1);
    QTest::newRow("64: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 25 << m_PrimaryIntMatrix.getConstReverseZIterator(5, 6);
    QTest::newRow("65: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 4 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 3);
    QTest::newRow("66: begin iterator, random iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 1 << m_PrimaryIntMatrix.getConstReverseZIterator(8, 6);
    QTest::newRow("67: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << 0 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("68: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << -1 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("69: begin iterator, begin iterator") << m_PrimaryIntMatrix.constReverseZBegin() << -3 << m_PrimaryIntMatrix.constReverseZBegin();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << -1 << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.constReverseZBegin() << 1 << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << 0 << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << 1 << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.constReverseZEnd() << -1 << m_SecondaryIntMatrix.constReverseZEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntMatrixConstReverseZIterator{} << -1 << IntMatrixConstReverseZIterator{};
    QTest::newRow("76: empty iterator, empty iterator") << IntMatrixConstReverseZIterator{} << 1 << IntMatrixConstReverseZIterator{};
}

QTEST_APPLESS_MAIN(ConstReverseZIteratorTests)

#include "tst_constreverseziteratortests.moc"
