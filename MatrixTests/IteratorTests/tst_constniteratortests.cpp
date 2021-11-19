#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstNIterator = Matrix<int>::ConstNIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstNIterator = Matrix<std::string>::ConstNIterator;

Q_DECLARE_METATYPE(IntMatrixConstNIterator)
Q_DECLARE_METATYPE(StringMatrixConstNIterator)

class ConstNIteratorTests : public QObject
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

    IntMatrixConstNIterator m_PrimaryIntIterator;
    IntMatrixConstNIterator m_SecondaryIntIterator;
    StringMatrixConstNIterator m_StringIterator;
};

void ConstNIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ConstNIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_SecondaryIntMatrix.clear();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constNBegin();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constNEnd();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntMatrix.clear();
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNBegin();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constNEnd();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstNIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixConstNIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
    QVERIFY(!emptyIt.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIt.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstNIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstNIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixConstNIterator, iterator);

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
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstNIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstNIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstNIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstNIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstNIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixConstNIterator, inputIterator);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixConstNIterator, inputIterator);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(4, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixConstNIterator, inputIterator);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixConstNIterator, inputIterator);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(4, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(6, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstNIterator(6, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstNIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstNIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstNIterator, firstIterator);
    QFETCH(IntMatrixConstNIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstNIteratorTests::testAsteriskOperator()
{
    QFETCH(IntMatrixConstNIterator, iterator);
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
}

void ConstNIteratorTests::testArrowOperator()
{
    QFETCH(StringMatrixConstNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstNIteratorTests::testArrowOperatorPlusEqual()
{
    m_StringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_StringIterator = m_StringMatrix.constNBegin();
    m_StringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstNIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstNIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstNIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstNIterator, leftIterator);
    QFETCH(IntMatrixConstNIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstNIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstNIterator, leftIterator);
    QFETCH(IntMatrixConstNIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstNIterator, expectedIterator);

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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstNIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 0 << 0 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constNEnd() << 8 << 8 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constNColumnBegin(0) << 0 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << 0 << 1 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constNColumnBegin(4) << 0 << 4 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constNColumnBegin(7) << 0 << 7 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.constNColumnBegin(8) << 0 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(0) << 0 << 1 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(1) << 0 << 2 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(4) << 0 << 5 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(7) << 0 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(8) << 8 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 7 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(44) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(70) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(71) << 7 << 8 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.constNBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constNEnd() << -1 << -1 << false << true;
}

void ConstNIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(0) << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(44) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(70) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(71) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnBegin(0) << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.getConstNIterator(0, 1);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnBegin(5) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnBegin(7) << m_PrimaryIntMatrix.getConstNIterator(0, 7);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnBegin(8) << m_PrimaryIntMatrix.getConstNIterator(0, 8);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnEnd(0) << m_PrimaryIntMatrix.getConstNIterator(0, 1);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnEnd(1) << m_PrimaryIntMatrix.getConstNIterator(0, 2);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnEnd(5) << m_PrimaryIntMatrix.getConstNIterator(0, 6);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.constNColumnEnd(7) << m_PrimaryIntMatrix.getConstNIterator(0, 8);
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstNIterator>("iterator");

    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(0, 0);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.constNEnd();
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
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstNIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd() << 0;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd() << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.constNEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.constNEnd() << 28;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNEnd() << 71;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 72;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 70;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 71;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 69;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -28;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 43;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 0;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 1;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNBegin() << -72;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNBegin() << -71;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.constNBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.constNBegin() << -44;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNBegin() << -1;
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 7) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 7) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 5) << -2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstNIterator{} << IntMatrixConstNIterator{} << 0;
}

void ConstNIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixConstNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -12;
}

void ConstNIteratorTests::testArrowOperator_data()
{
    m_StringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};

    QTest::addColumn<StringMatrixConstNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_StringMatrix.constNBegin() << 3;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstNIterator(1, 0) << 2;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstNIterator(2, 1) << 7;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstNIterator(1, 3) << 11;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstNIterator(2, 3) << 6;
}

void ConstNIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixConstNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 0 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 1 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 5 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 10 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 11 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << -5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << -4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << 5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 1) << 6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -11 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -10 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -6 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << -1 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 3) << 0 << -12;
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

    QTest::addColumn<IntMatrixConstNIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstNIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 1) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(0, 2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 1) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 0) << m_PrimaryIntMatrix.getConstNIterator(0, 2) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(3, 2) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 2) << m_PrimaryIntMatrix.constNEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 2) << m_PrimaryIntMatrix.constNEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2) << m_PrimaryIntMatrix.getConstNIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2) << m_PrimaryIntMatrix.getConstNIterator(10) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3) << m_PrimaryIntMatrix.getConstNIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3) << m_PrimaryIntMatrix.getConstNIterator(10) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(13) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(13) << m_PrimaryIntMatrix.constNEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(12) << m_PrimaryIntMatrix.constNEnd() << 2 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 1 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(2) << 8 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(2) << m_PrimaryIntMatrix.constNColumnEnd(2) << 9 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(2) << m_PrimaryIntMatrix.constNColumnEnd(3) << 9 << 2;
    QTest::newRow("{begin iterator, column begin iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnBegin(1) << 1 << 2;
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 1 << 1;
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 1 << 3;
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnEnd(1) << m_PrimaryIntMatrix.constNEnd() << 1 << 0;
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

    QTest::addColumn<IntMatrixConstNIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstNIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 6 << m_PrimaryIntMatrix.getConstNIterator(4, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << -2 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 5 << m_PrimaryIntMatrix.constNColumnBegin(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 11 << m_PrimaryIntMatrix.getConstNIterator(19);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << -1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.constNColumnBegin(1) << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 6 << m_PrimaryIntMatrix.getConstNIterator(9);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 8 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << -2 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNColumnEnd(1) << 10 << m_PrimaryIntMatrix.constNColumnEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getConstNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstNIterator(0, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -1 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 0 << m_PrimaryIntMatrix.getConstNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 11 << m_PrimaryIntMatrix.getConstNIterator(19);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << -1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(3, 1) << m_PrimaryIntMatrix.constNEnd() << 10 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getConstNIterator(0, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getConstNIterator(1, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getConstNIterator(1, 3);
}

void ConstNIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstNIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstNIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constNBegin() << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constNEnd() << m_SecondaryIntMatrix.constNBegin();
}

void ConstNIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstNIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.getConstNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(6, 4) << m_PrimaryIntMatrix.getConstNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(7, 4) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(0, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(1, 5) << m_PrimaryIntMatrix.getConstNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(4, 5) << m_PrimaryIntMatrix.getConstNIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(6, 8) << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.constNEnd();
}

void ConstNIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixConstNIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstNIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.constNEnd() << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(7, 8) << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(5, 5) << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(2, 5) << m_PrimaryIntMatrix.getConstNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(1, 5) << m_PrimaryIntMatrix.getConstNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(0, 5) << m_PrimaryIntMatrix.getConstNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(7, 4) << m_PrimaryIntMatrix.getConstNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstNIterator(2, 0) << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getConstNIterator(1, 0) << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.constNBegin() << m_PrimaryIntMatrix.constNBegin();
}

void ConstNIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constNBegin() << -3 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constNBegin() << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constNBegin() << 0 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << 1 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << 4 << m_PrimaryIntMatrix.getConstNIterator(4, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << 10 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << 70 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constNBegin() << 71 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << 72 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << 73 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constNBegin() << 75 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -4 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -2 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << -1 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 0 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 3 << m_PrimaryIntMatrix.getConstNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 9 << m_PrimaryIntMatrix.getConstNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 69 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 70 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 71 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 72 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(1, 0) << 74 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -47 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -45 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -44 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -43 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -6 << m_PrimaryIntMatrix.getConstNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << -2 << m_PrimaryIntMatrix.getConstNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) <<  0 << m_PrimaryIntMatrix.getConstNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) <<  2 << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 6 << m_PrimaryIntMatrix.getConstNIterator(2, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 26 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 27 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 28 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 29 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(4, 5) << 31 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -73 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -71 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -70 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -69 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -24 << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << -3 << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 0 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 1 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 2 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 3 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(6, 8) << 5 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -74 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -72 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -71 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -70 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -25 << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -4 << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << -1 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 0 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 2 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstNIterator(7, 8) << 4 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constNEnd() << -75 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constNEnd() << -73 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constNEnd() << -72 << m_PrimaryIntMatrix.constNBegin();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << -71 << m_PrimaryIntMatrix.getConstNIterator(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << -26 << m_PrimaryIntMatrix.getConstNIterator(6, 5);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << -5 << m_PrimaryIntMatrix.getConstNIterator(3, 8);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << -2 << m_PrimaryIntMatrix.getConstNIterator(6, 8);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constNEnd() << -1 << m_PrimaryIntMatrix.getConstNIterator(7, 8);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constNEnd() << 0 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constNEnd() << 1 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constNEnd() << 3 << m_PrimaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constNBegin() << -1 << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constNBegin() << 1 << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constNEnd() << 0 << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constNEnd() << 1 << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constNEnd() << -1 << m_SecondaryIntMatrix.constNEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstNIterator{} << -1 << IntMatrixConstNIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstNIterator{} << 1 << IntMatrixConstNIterator{};
}

QTEST_APPLESS_MAIN(ConstNIteratorTests)

#include "tst_constniteratortests.moc"
