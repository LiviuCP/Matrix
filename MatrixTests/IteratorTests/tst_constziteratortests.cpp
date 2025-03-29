#include <QtTest>
#include <cmath>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixConstZIterator)
Q_DECLARE_METATYPE(StringMatrixConstZIterator)
Q_DECLARE_METATYPE(IntMatrixZIterator)

class ConstZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstZIteratorTests();

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
    void testAutoWithLocalCopyRead();   // "auto" syntax tested for const matrixes (this is where ConstZIterators apply)
    void testAutoWithLocalCopyWrite();
    void testConstAutoWithLocalCopy();
    void testConstAutoWithReference();
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
    const IntMatrix m_ThirdIntMatrix; // used for testing "auto" syntax
    StringMatrix m_PrimaryStringMatrix;
    StringMatrix m_SecondaryStringMatrix;

    IntMatrixConstZIterator m_PrimaryIntIterator;
    IntMatrixConstZIterator m_SecondaryIntIterator;
    StringMatrixConstZIterator m_StringIterator;
};

ConstZIteratorTests::ConstZIteratorTests()
    : m_ThirdIntMatrix{2, 3, {-1, 2, -3, 4, -5, 6}}
{
}

void ConstZIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixOptSizeType, expectedRowNr);
    QFETCH(IntMatrixOptSizeType, expectedColumnNr);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstZIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrixOptSizeType, expectedRowNr);
    QFETCH(IntMatrixOptSizeType, expectedColumnNr);

    IntMatrixConstZIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr,
             "The iterator has not been correctly created!");
}

void ConstZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixConstZIterator emptyIt;

    QVERIFY2(!emptyIt.getRowNr().has_value() && !emptyIt.getColumnNr().has_value(), "The iterator has not been correctly created!");
}

void ConstZIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void ConstZIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixConstZIterator, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void ConstZIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void ConstZIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void ConstZIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void ConstZIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void ConstZIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void ConstZIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixConstZIterator, inputIterator);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixConstZIterator, inputIterator);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 4);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 6),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 4);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 4),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 4);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 6) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 4);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixConstZIterator, inputIterator);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixConstZIterator, inputIterator);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 6);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 4),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 6);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 6),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 6);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 4) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 6);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getConstZIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void ConstZIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstZIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstZIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstZIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void ConstZIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixConstZIterator, firstIterator);
    QFETCH(IntMatrixConstZIterator, secondIterator);
    QFETCH(IntMatrixDiffType, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void ConstZIteratorTests::testAsteriskOperator()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void ConstZIteratorTests::testAsteriskOperatorPlusEqual()
{
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row/column capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 4, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with row capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 4, 3);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    // test with column capacity offset
    m_PrimaryIntMatrix = {2, 3, {1, 2, -3, 4, -5, 6}};
    m_PrimaryIntMatrix.resize(2, 3, 2, 5);
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZBegin();
    m_PrimaryIntMatrix.at(0, 2) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);
}

void ConstZIteratorTests::testArrowOperator()
{
    QFETCH(StringMatrixConstZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstZIteratorTests::testArrowOperatorPlusEqual()
{
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.constZBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row/column capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.resize(2, 3, 4, 5);
    m_StringIterator = m_PrimaryStringMatrix.constZBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with row capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.resize(2, 3, 4, 3);
    m_StringIterator = m_PrimaryStringMatrix.constZBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    // test with column capacity offset
    m_PrimaryStringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_PrimaryStringMatrix.resize(2, 3, 2, 5);
    m_StringIterator = m_PrimaryStringMatrix.constZBegin();
    m_PrimaryStringMatrix.at(0, 2) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);
}

void ConstZIteratorTests::testSquareBracketsOperator()
{
    QFETCH(IntMatrixConstZIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void ConstZIteratorTests::testAutoWithLocalCopyRead()
{
    int sum{0}, product{1};
    size_t count{0};

    for (auto element : m_ThirdIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using auto (read) does not work correctly!");
}

void ConstZIteratorTests::testAutoWithLocalCopyWrite()
{
    int sum{0};
    size_t count{0};

    for (auto element : m_ThirdIntMatrix)
    {
        element = std::abs(element);
        sum += element;
        ++count;
    }

    QVERIFY2(sum == 21 && count == 6, "Iterating through the matrix elements by using auto (write) does not work correctly!");
}

void ConstZIteratorTests::testConstAutoWithLocalCopy()
{
    int sum{0}, product{1};
    size_t count{0};

    for (const auto element : m_ThirdIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using const auto does not work correctly!");
}

void ConstZIteratorTests::testConstAutoWithReference()
{
    int sum{0}, product{1};
    size_t count{0};

    for (const auto& element : m_ThirdIntMatrix)
    {
        sum += element;
        product *= element;
        ++count;
    }

    QVERIFY2(sum == 3 && product == -720 && count == 6, "Iterating through the matrix elements by using const auto& does not work correctly!");
}

void ConstZIteratorTests::testStdCount()
{
    QFETCH(IntMatrixConstZIterator, leftIterator);
    QFETCH(IntMatrixConstZIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void ConstZIteratorTests::testStdFind()
{
    QFETCH(IntMatrixConstZIterator, leftIterator);
    QFETCH(IntMatrixConstZIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixConstZIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void ConstZIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.constZBegin(), m_PrimaryIntMatrix.constZEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.constZBegin(), m_PrimaryIntMatrix.constZEnd(), 10) == m_PrimaryIntMatrix.constZEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");
}

void ConstZIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constZBegin() << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.constZEnd() << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.constZRowBegin(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.constZRowBegin(4) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.constZRowBegin(7) << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.constZRowBegin(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.constZRowEnd(0) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.constZRowEnd(1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.constZRowEnd(4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.constZRowEnd(7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.constZRowEnd(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstZIterator(44) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstZIterator(70) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstZIterator(71) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.constZBegin() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.constZEnd() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
}

void ConstZIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.zBegin() << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: end iterator") << m_PrimaryIntMatrix.zEnd() << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("3: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(1) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(4) << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(7) << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: row begin iterator") << m_PrimaryIntMatrix.zRowBegin(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: row end iterator") << m_PrimaryIntMatrix.zRowEnd(0) << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: row end iterator") << m_PrimaryIntMatrix.zRowEnd(1) << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("10: row end iterator") << m_PrimaryIntMatrix.zRowEnd(4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: row end iterator") << m_PrimaryIntMatrix.zRowEnd(7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{0u};
    QTest::newRow("12: row end iterator") << m_PrimaryIntMatrix.zRowEnd(8) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{8u};
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getZIterator(0, 1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getZIterator(5, 4) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 6) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getZIterator(8, 7) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getZIterator(0) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getZIterator(1) << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getZIterator(44) << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{4u};
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getZIterator(70) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{6u};
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getZIterator(71) << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{7u};
    QTest::newRow("23: begin iterator") << m_SecondaryIntMatrix.zBegin() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
    QTest::newRow("24: end iterator") << m_SecondaryIntMatrix.zEnd() << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
}

void ConstZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0) << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(44) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(70) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(71) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("7: row begin iterator, random iterator") << m_PrimaryIntMatrix.constZRowBegin(0) << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("8: row begin iterator, random iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.getConstZIterator(1, 0);
    QTest::newRow("9: row begin iterator, random iterator") << m_PrimaryIntMatrix.constZRowBegin(5) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("10: row begin iterator, random iterator") << m_PrimaryIntMatrix.constZRowBegin(7) << m_PrimaryIntMatrix.getConstZIterator(7, 0);
    QTest::newRow("11: row begin iterator, random iterator") << m_PrimaryIntMatrix.constZRowBegin(8) << m_PrimaryIntMatrix.getConstZIterator(8, 0);
    QTest::newRow("12: row end iterator, random iterator") << m_PrimaryIntMatrix.constZRowEnd(0) << m_PrimaryIntMatrix.getConstZIterator(1, 0);
    QTest::newRow("13: row end iterator, random iterator") << m_PrimaryIntMatrix.constZRowEnd(1) << m_PrimaryIntMatrix.getConstZIterator(2, 0);
    QTest::newRow("14: row end iterator, random iterator") << m_PrimaryIntMatrix.constZRowEnd(5) << m_PrimaryIntMatrix.getConstZIterator(6, 0);
    QTest::newRow("15: row end iterator, random iterator") << m_PrimaryIntMatrix.constZRowEnd(7) << m_PrimaryIntMatrix.getConstZIterator(8, 0);
    QTest::newRow("16: row end iterator, end iterator") << m_PrimaryIntMatrix.constZRowEnd(8) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("17: begin iterator, end iterator") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");

    QTest::newRow("1: begin iterator")  << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("7: end iterator")  << m_PrimaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstZIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstZIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstZIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void ConstZIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void ConstZIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstZIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void ConstZIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstZIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void ConstZIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstZIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstZIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstZIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void ConstZIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("1: end iterator, end iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd() << 0;
    QTest::newRow("2: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd() << 1;
    QTest::newRow("3: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.constZEnd() << 2;
    QTest::newRow("4: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.constZEnd() << 28;
    QTest::newRow("5: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZEnd() << 71;
    QTest::newRow("6: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 72;
    QTest::newRow("7: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -1;
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 0;
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 1;
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 27;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 70;
    QTest::newRow("12: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 71;
    QTest::newRow("13: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -2;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -1;
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 0;
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 26;
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 69;
    QTest::newRow("18: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 70;
    QTest::newRow("19: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -28;
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -27;
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -26;
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 0;
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 43;
    QTest::newRow("24: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 44;
    QTest::newRow("25: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -71;
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -70;
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -69;
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -43;
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0;
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 1;
    QTest::newRow("31: end iterator, begin iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZBegin() << -72;
    QTest::newRow("32: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZBegin() << -71;
    QTest::newRow("33: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.constZBegin() << -70;
    QTest::newRow("34: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.constZBegin() << -44;
    QTest::newRow("35: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZBegin() << -1;
    QTest::newRow("36: begin iterator, begin iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin() << 0;
    QTest::newRow("37: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(7, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -14;
    QTest::newRow("38: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(7, 2) << 14;
    QTest::newRow("39: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 2;
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 2) << -2;
    QTest::newRow("41: begin iterator, end iterator") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd() << 0;
    QTest::newRow("42: end iterator, begin iterator") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZBegin() << 0;
    QTest::newRow("43: begin iterator, begin iterator") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZBegin() << 0;
    QTest::newRow("44: end iterator, end iterator") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZEnd() << 0;
    QTest::newRow("45: empty iterator, empty iterator") << IntMatrixConstZIterator{} << IntMatrixConstZIterator{} << 0;
}

void ConstZIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 1;
    QTest::newRow("2: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -2;
    QTest::newRow("3: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -6;
    QTest::newRow("4: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -12;

    // test with row/column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 6, 5);

    QTest::newRow("6: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 1;
    QTest::newRow("7: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << -2;
    QTest::newRow("8: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << -6;
    QTest::newRow("9: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << -12;
}

void ConstZIteratorTests::testArrowOperator_data()
{
    m_PrimaryStringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringMatrixConstZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryStringMatrix.constZBegin() << 3;
    QTest::newRow("2: random iterator") << m_PrimaryStringMatrix.getConstZIterator(0, 1) << 2;
    QTest::newRow("3: random iterator") << m_PrimaryStringMatrix.getConstZIterator(1, 2) << 7;
    QTest::newRow("4: random iterator") << m_PrimaryStringMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("5: random iterator") << m_PrimaryStringMatrix.getConstZIterator(3, 2) << 6;

    // test with row capacity offset
    m_SecondaryStringMatrix = m_PrimaryStringMatrix;
    m_SecondaryStringMatrix.resize(4, 3, 6, 3);

    QTest::newRow("6: begin iterator") << m_SecondaryStringMatrix.constZBegin() << 3;
    QTest::newRow("7: random iterator") << m_SecondaryStringMatrix.getConstZIterator(0, 1) << 2;
    QTest::newRow("8: random iterator") << m_SecondaryStringMatrix.getConstZIterator(1, 2) << 7;
    QTest::newRow("9: random iterator") << m_SecondaryStringMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("10: random iterator") << m_SecondaryStringMatrix.getConstZIterator(3, 2) << 6;
}

void ConstZIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("1: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 0 << 1;
    QTest::newRow("2: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 1 << -2;
    QTest::newRow("3: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 5 << -6;
    QTest::newRow("4: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 10 << 11;
    QTest::newRow("5: begin iterator") << m_PrimaryIntMatrix.constZBegin() << 11 << -12;
    QTest::newRow("6: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -1 << 1;
    QTest::newRow("7: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0 << -2;
    QTest::newRow("8: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 4 << -6;
    QTest::newRow("9: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 9 << 11;
    QTest::newRow("10: random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 10 << -12;
    QTest::newRow("11: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -5 << 1;
    QTest::newRow("12: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -4 << -2;
    QTest::newRow("13: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 0 << -6;
    QTest::newRow("14: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 5 << 11;
    QTest::newRow("15: random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 6 << -12;
    QTest::newRow("16: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -10 << 1;
    QTest::newRow("17: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -9 << -2;
    QTest::newRow("18: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -5 << -6;
    QTest::newRow("19: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 0 << 11;
    QTest::newRow("20: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 1 << -12;
    QTest::newRow("21: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -11 << 1;
    QTest::newRow("22: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -10 << -2;
    QTest::newRow("23: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -6 << -6;
    QTest::newRow("24: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -1 << 11;
    QTest::newRow("25: random iterator") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << 0 << -12;

    // test with column capacity offset
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_SecondaryIntMatrix.resize(4, 3, 4, 5);

    QTest::newRow("26: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 0 << 1;
    QTest::newRow("27: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 1 << -2;
    QTest::newRow("28: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 5 << -6;
    QTest::newRow("29: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 10 << 11;
    QTest::newRow("30: begin iterator") << m_SecondaryIntMatrix.constZBegin() << 11 << -12;
    QTest::newRow("31: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << -1 << 1;
    QTest::newRow("32: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << 0 << -2;
    QTest::newRow("33: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << 4 << -6;
    QTest::newRow("34: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << 9 << 11;
    QTest::newRow("35: random iterator") << m_SecondaryIntMatrix.getConstZIterator(0, 1) << 10 << -12;
    QTest::newRow("36: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << -5 << 1;
    QTest::newRow("37: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << -4 << -2;
    QTest::newRow("38: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << 0 << -6;
    QTest::newRow("39: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << 5 << 11;
    QTest::newRow("40: random iterator") << m_SecondaryIntMatrix.getConstZIterator(1, 2) << 6 << -12;
    QTest::newRow("41: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << -10 << 1;
    QTest::newRow("42: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << -9 << -2;
    QTest::newRow("43: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << -5 << -6;
    QTest::newRow("44: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << 0 << 11;
    QTest::newRow("45: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 1) << 1 << -12;
    QTest::newRow("46: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << -11 << 1;
    QTest::newRow("47: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << -10 << -2;
    QTest::newRow("48: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << -6 << -6;
    QTest::newRow("49: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << -1 << 11;
    QTest::newRow("50: random iterator") << m_SecondaryIntMatrix.getConstZIterator(3, 2) << 0 << -12;
}

void ConstZIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 1,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 8
                          }};

    QTest::addColumn<IntMatrixConstZIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstZIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 2 << 3;
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << -5 << 0;
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(1, 4) << 1 << 1;
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(2, 0) << 1 << 2;
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 3) << m_PrimaryIntMatrix.getConstZIterator(1, 4) << 1 << 1;
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 3) << m_PrimaryIntMatrix.getConstZIterator(2, 0) << 1 << 2;
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(2, 3) << 2 << 2;
    QTest::newRow("8: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(2, 3) << m_PrimaryIntMatrix.constZEnd() << 2 << 1;
    QTest::newRow("9: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(2, 2) << 2 << 1;
    QTest::newRow("10: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(2, 2) << m_PrimaryIntMatrix.constZEnd() << 2 << 2;
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(2) << m_PrimaryIntMatrix.getConstZIterator(9) << 1 << 1;
    QTest::newRow("12: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(2) << m_PrimaryIntMatrix.getConstZIterator(10) << 1 << 2;
    QTest::newRow("13: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(3) << m_PrimaryIntMatrix.getConstZIterator(9) << 1 << 1;
    QTest::newRow("14: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(3) << m_PrimaryIntMatrix.getConstZIterator(10) << 1 << 2;
    QTest::newRow("15: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(13) << 2 << 2;
    QTest::newRow("16: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(13) << m_PrimaryIntMatrix.constZEnd() << 2 << 1;
    QTest::newRow("17: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(12) << 2 << 1;
    QTest::newRow("18: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(12) << m_PrimaryIntMatrix.constZEnd() << 2 << 2;
    QTest::newRow("19: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 1 << 1;
    QTest::newRow("20: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(2) << 8 << 2;
    QTest::newRow("21: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(2) << m_PrimaryIntMatrix.constZRowEnd(2) << 9 << 1;
    QTest::newRow("22: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(2) << m_PrimaryIntMatrix.constZRowEnd(3) << 9 << 2;
    QTest::newRow("23: begin iterator, row begin iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowBegin(1) << 1 << 2;
    QTest::newRow("24: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 1 << 1;
    QTest::newRow("25: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 1 << 3;
    QTest::newRow("26: row end iterator, end iterator") << m_PrimaryIntMatrix.constZRowEnd(1) << m_PrimaryIntMatrix.constZEnd() << 1 << 0;
}

void ConstZIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {4, 5, {
                              -1, 1, 3, 1, 4,
                               5, 9, 8, 0, 6,
                               2, -2, 2, 8, 9,
                              -7, 7, 2, 9, 11
                          }};

    QTest::addColumn<IntMatrixConstZIterator>("leftIterator");
    QTest::addColumn<IntMatrixConstZIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("2: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("3: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("4: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 6 << m_PrimaryIntMatrix.getConstZIterator(1, 4);
    QTest::newRow("5: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("6: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << -1 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("7: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << -2 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("8: row begin iterator, row end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 10 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("9: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("10: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 11 << m_PrimaryIntMatrix.getConstZIterator(19);
    QTest::newRow("11: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("12: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("13: row begin iterator, end iterator") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("14: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("15: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 6 << m_PrimaryIntMatrix.getConstZIterator(9);
    QTest::newRow("16: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("17: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << -2 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("18: begin iterator, row end iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 10 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getConstZIterator(1, 3);
    QTest::newRow("20: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstZIterator(3, 0);
    QTest::newRow("21: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("22: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -1 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("23: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("24: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("25: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 0 << m_PrimaryIntMatrix.getConstZIterator(1, 3);
    QTest::newRow("26: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 11 << m_PrimaryIntMatrix.getConstZIterator(19);
    QTest::newRow("27: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("28: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("29: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("30: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("31: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstZIterator(3, 0);
    QTest::newRow("32: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("33: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("34: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
}

void ConstZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("2: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("6: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("2: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("3: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("4: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("5: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("6: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("7: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("8: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("9: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("10: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("11: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("12: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("13: end iterator, end iterator") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("14: begin iterator, end iterator") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("15: end iterator, begin iterator") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZBegin();
}

void ConstZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, random iterator")  << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(4, 6) << m_PrimaryIntMatrix.getConstZIterator(4, 7);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(4, 7) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 0) << m_PrimaryIntMatrix.getConstZIterator(5, 1);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 2);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 5);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("9: random iterator, end iterator")  << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("10: end iterator, end iterator")  << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("1: end iterator, random iterator")  << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("2: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("3: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 5) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("4: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 1);
    QTest::newRow("5: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("6: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(5, 0) << m_PrimaryIntMatrix.getConstZIterator(4, 7);
    QTest::newRow("7: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(4, 7) << m_PrimaryIntMatrix.getConstZIterator(4, 6);
    QTest::newRow("8: random iterator, random iterator")  << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("9: random iterator, begin iterator")  << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("10: begin iterator, begin iterator")  << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin();
}

void ConstZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("1: begin iterator, begin iterator") << m_PrimaryIntMatrix.constZBegin() << -3 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("2: begin iterator, begin iterator") << m_PrimaryIntMatrix.constZBegin() << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("3: begin iterator, begin iterator") << m_PrimaryIntMatrix.constZBegin() << 0 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("4: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << 1 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("5: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << 4 << m_PrimaryIntMatrix.getConstZIterator(0, 4);
    QTest::newRow("6: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << 10 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("7: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << 70 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("8: begin iterator, random iterator") << m_PrimaryIntMatrix.constZBegin() << 71 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("9: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << 72 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("10: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << 73 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("11: begin iterator, end iterator") << m_PrimaryIntMatrix.constZBegin() << 75 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("12: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -4 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("13: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -2 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("14: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("15: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("16: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 3 << m_PrimaryIntMatrix.getConstZIterator(0, 4);
    QTest::newRow("17: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 9 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("18: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 69 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("19: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 70 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("20: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 71 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("21: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 72 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("22: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 74 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("23: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -47 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("24: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -45 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("25: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -44 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("26: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -43 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("27: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -6 << m_PrimaryIntMatrix.getConstZIterator(4, 6);
    QTest::newRow("28: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -2 << m_PrimaryIntMatrix.getConstZIterator(5, 2);
    QTest::newRow("29: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) <<  0 << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("30: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) <<  2 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("31: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 6 << m_PrimaryIntMatrix.getConstZIterator(6, 2);
    QTest::newRow("32: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 26 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("33: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 27 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("34: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 28 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("35: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 29 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("36: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 31 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("37: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -73 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("38: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -71 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("39: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -70 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("40: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -69 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("41: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -24 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("42: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -3 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("43: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 0 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("44: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 1 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("45: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 2 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("46: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 3 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("47: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 5 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("48: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -74 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("49: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -72 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("50: random iterator, begin iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -71 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("51: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -70 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("52: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -25 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("53: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -4 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("54: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -1 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("55: random iterator, random iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 0 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("56: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("57: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 2 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("58: random iterator, end iterator") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 4 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("59: end iterator, begin iterator") << m_PrimaryIntMatrix.constZEnd() << -75 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("60: end iterator, begin iterator") << m_PrimaryIntMatrix.constZEnd() << -73 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("61: end iterator, begin iterator") << m_PrimaryIntMatrix.constZEnd() << -72 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("62: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << -71 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("63: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << -26 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("64: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << -5 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("65: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("66: end iterator, random iterator") << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("67: end iterator, end iterator") << m_PrimaryIntMatrix.constZEnd() << 0 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("68: end iterator, end iterator") << m_PrimaryIntMatrix.constZEnd() << 1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("69: end iterator, end iterator") << m_PrimaryIntMatrix.constZEnd() << 3 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("70: begin iterator, end iterator") << m_SecondaryIntMatrix.constZBegin() << -1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("71: begin iterator, end iterator") << m_SecondaryIntMatrix.constZBegin() << 1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("72: end iterator, end iterator") << m_SecondaryIntMatrix.constZEnd() << 0 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("73: end iterator, end iterator") << m_SecondaryIntMatrix.constZEnd() << 1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("74: end iterator, end iterator") << m_SecondaryIntMatrix.constZEnd() << -1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("75: empty iterator, empty iterator") << IntMatrixConstZIterator{} << -1 << IntMatrixConstZIterator{};
    QTest::newRow("76: empty iterator, empty iterator") << IntMatrixConstZIterator{} << 1 << IntMatrixConstZIterator{};
}

QTEST_APPLESS_MAIN(ConstZIteratorTests)

#include "tst_constziteratortests.moc"
