#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstReverseNIterator)
Q_DECLARE_METATYPE(StringMatrixConstReverseNIterator)
Q_DECLARE_METATYPE(IntMatrixReverseNIterator)

class ConstReverseNIteratorTests : public QObject
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
    StringMatrix m_StringMatrix;

    IntMatrixConstReverseNIterator m_PrimaryIntIterator;
    IntMatrixConstReverseNIterator m_SecondaryIntIterator;
    StringMatrixConstReverseNIterator m_StringIterator;
};

void ConstReverseNIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ConstReverseNIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixReverseNIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    IntMatrixConstReverseNIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ConstReverseNIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_SecondaryIntMatrix.clear();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constReverseNBegin();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constReverseNEnd();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntMatrix.clear();
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNBegin();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constReverseNEnd();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstReverseNIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixConstReverseNIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
    QVERIFY(!emptyIt.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIt.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstReverseNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstReverseNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);

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
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstReverseNIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstReverseNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstReverseNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstReverseNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, inputIterator);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, inputIterator);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, inputIterator);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, inputIterator);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(6, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(4, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstReverseNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstReverseNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, firstIterator);
    QFETCH(IntMatrixConstReverseNIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstReverseNIteratorTests::testAsteriskOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
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
}

void ConstReverseNIteratorTests::testArrowOperator()
{
    QFETCH(StringMatrixConstReverseNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstReverseNIteratorTests::testArrowOperatorPlusEqual()
{
    m_StringMatrix = {3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    m_StringIterator = m_StringMatrix.constReverseNBegin();
    m_StringMatrix.at(0, 1) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstReverseNIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstReverseNIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstReverseNIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstReverseNIterator, leftIterator);
    QFETCH(IntMatrixConstReverseNIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstReverseNIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstReverseNIterator, leftIterator);
    QFETCH(IntMatrixConstReverseNIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstReverseNIterator, expectedIterator);

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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 7 << 8 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -1 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(0) << 7 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << 7 << 1 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(4) << 7 << 4 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(7) << 7 << 7 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(8) << 7 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << -1 << 0 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 7 << 0 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(4) << 7 << 3 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(7) << 7 << 6 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(8) << 7 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8) << 7 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(44) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(70) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(71) << 7 << 8 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << -1 << -1 << false << true;
}

void ConstReverseNIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.reverseNBegin() << 7 << 8 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.reverseNEnd() << -1 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(0) << 7 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(1) << 7 << 1 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(4) << 7 << 4 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(7) << 7 << 7 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.reverseNColumnBegin(8) << 7 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(0) << -1 << 0 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(1) << 7 << 0 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(4) << 7 << 3 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(7) << 7 << 6 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.reverseNColumnEnd(8) << 7 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1, 0) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(4, 5) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(6, 8) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(7, 8) << 7 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(1) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(44) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(70) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getReverseNIterator(71) << 7 << 8 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.reverseNBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.reverseNEnd() << -1 << -1 << false << true;
}

void ConstReverseNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(44) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(70) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(71) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(0) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 0);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 1);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 5);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(7) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 7);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 0);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(7) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 6);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 7);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstReverseNIterator>("iterator");

    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.constReverseNBegin();
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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin() << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.constReverseNBegin() << -1;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.constReverseNBegin() << -27;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.constReverseNBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNBegin() << -71;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNBegin() << -72;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -71;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -45;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -1;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 44;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 0;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -1;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 72;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.constReverseNEnd() << 71;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.constReverseNEnd() << 45;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.constReverseNEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd() << 1;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 7) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 7) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << 2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstReverseNIterator{} << IntMatrixConstReverseNIterator{} << 0;
}

void ConstReverseNIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixConstReverseNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << -12;
}

void ConstReverseNIteratorTests::testArrowOperator_data()
{
    m_StringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};

    QTest::addColumn<StringMatrixConstReverseNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{random iterator}") << m_StringMatrix.getConstReverseNIterator(0, 0) << 3;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstReverseNIterator(1, 0) << 2;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstReverseNIterator(2, 1) << 7;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstReverseNIterator(1, 3) << 11;
    QTest::newRow("{begin iterator}") << m_StringMatrix.constReverseNBegin() << 6;
}

void ConstReverseNIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixConstReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 11 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 10 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 6 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 1 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 0 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << -1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << 5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << 4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << -5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1) << -6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 0 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -1 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -10 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -11 << -12;
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

    QTest::addColumn<IntMatrixConstReverseNIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 0) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 2) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 0) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 1) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(3, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 2) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 2) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(9) << m_PrimaryIntMatrix.getConstReverseNIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(10) << m_PrimaryIntMatrix.getConstReverseNIterator(2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(9) << m_PrimaryIntMatrix.getConstReverseNIterator(3) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(10) << m_PrimaryIntMatrix.getConstReverseNIterator(3) << 1 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(13) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(13) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(12) << m_PrimaryIntMatrix.constReverseNEnd() << 2 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << 1;
    QTest::newRow("{column end iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(0) << 8 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(3) << 9 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(3) << m_PrimaryIntMatrix.constReverseNColumnEnd(2) << 9 << 2;
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << m_PrimaryIntMatrix.constReverseNEnd() << 1 << 2;
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << 1;
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(2) << m_PrimaryIntMatrix.constReverseNEnd() << 1 << 3;
    QTest::newRow("{begin iterator, column begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnBegin(2) << 1 << 0;
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

    QTest::addColumn<IntMatrixConstReverseNIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstReverseNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(5);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 6 << m_PrimaryIntMatrix.constReverseNColumnBegin(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstReverseNIterator(7);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 6 << m_PrimaryIntMatrix.constReverseNColumnBegin(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(0);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 3 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << -2 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNColumnBegin(1) << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 11 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 5 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(8);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 1 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 7 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstReverseNIterator(11);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 4 << m_PrimaryIntMatrix.constReverseNColumnEnd(1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 11 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(3, 1) << m_PrimaryIntMatrix.constReverseNEnd() << 10 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 11 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 2 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 9 << m_PrimaryIntMatrix.getConstReverseNIterator(18);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 3);
}

void ConstReverseNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(2, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << m_SecondaryIntMatrix.constReverseNBegin();
}

void ConstReverseNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstReverseNIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(5, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(5, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.constReverseNEnd();
}

void ConstReverseNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstReverseNIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstReverseNIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.constReverseNEnd() << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 4) << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(0, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(1, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << m_PrimaryIntMatrix.getConstReverseNIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getConstReverseNIterator(7, 8) << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.constReverseNBegin() << m_PrimaryIntMatrix.constReverseNBegin();
}

void ConstReverseNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstReverseNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstReverseNIterator>("expectedIterator");

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << 3 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << 1 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << 0 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -2 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -5 << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -11 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -71 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -72 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -73 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNEnd() << -75 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 4 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 2 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 1 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -1 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -4 << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -10 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -70 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -71 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -72 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0) << -74 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 5 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 3 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 2 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 1 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -3 << m_PrimaryIntMatrix.getConstReverseNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -9 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -69 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -70 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -71 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0) << -73 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 48 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 46 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 45 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 44 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 43 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 6 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 2 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -2 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -6 << m_PrimaryIntMatrix.getConstReverseNIterator(2, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -26 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -27 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -28 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(4, 5) << -30 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 74 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 72 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 71 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 70 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 69 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 24 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 3 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << 0 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -1 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -2 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8) << -4 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 75 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 73 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 72 << m_PrimaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 71 << m_PrimaryIntMatrix.getConstReverseNIterator(0, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 70 << m_PrimaryIntMatrix.getConstReverseNIterator(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 25 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 5);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 4 << m_PrimaryIntMatrix.getConstReverseNIterator(3, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 1 << m_PrimaryIntMatrix.getConstReverseNIterator(6, 8);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << 0 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << -1 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constReverseNBegin() << -3 << m_PrimaryIntMatrix.constReverseNBegin();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << -1 << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNBegin() << 1 << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << 0 << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << 1 << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constReverseNEnd() << -1 << m_SecondaryIntMatrix.constReverseNEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstReverseNIterator{} << -1 << IntMatrixConstReverseNIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstReverseNIterator{} << 1 << IntMatrixConstReverseNIterator{};
}

QTEST_APPLESS_MAIN(ConstReverseNIteratorTests)

#include "tst_constreverseniteratortests.moc"
