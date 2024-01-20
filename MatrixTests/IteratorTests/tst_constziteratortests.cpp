#include <QtTest>

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
    StringMatrix m_StringMatrix;

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
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ConstZIteratorTests::testIteratorCreationFromNonConstIterator()
{
    QFETCH(IntMatrixZIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    IntMatrixConstZIterator constIterator{iterator};

    QVERIFY2(constIterator.getRowNr() == expectedRowNr &&
             constIterator.getColumnNr() == expectedColumnNr &&
             constIterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void ConstZIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix = {9, 8, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_SecondaryIntMatrix.clear();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constZBegin();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.constZEnd();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntMatrix.clear();
    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZBegin();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_PrimaryIntMatrix.constZEnd();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void ConstZIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixConstZIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
    QVERIFY(!emptyIt.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIt.isValidWithMatrix(m_SecondaryIntMatrix));
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
    QFETCH(IntMatrix::size_type, expectedDifference);

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
}

void ConstZIteratorTests::testArrowOperator()
{
    QFETCH(StringMatrixConstZIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void ConstZIteratorTests::testArrowOperatorPlusEqual()
{
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    m_StringIterator = m_StringMatrix.constZBegin();
    m_StringMatrix.at(0, 2) = "abcdefghi";
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
    int sum{0}, product{1}, count{0};

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
    int sum{0}, count{0};

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
    int sum{0}, product{1}, count{0};

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
    int sum{0}, product{1}, count{0};

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
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 0 << 0 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.constZEnd() << 8 << 8 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.constZRowBegin(0) << 0 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << 1 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.constZRowBegin(4) << 4 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.constZRowBegin(7) << 7 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.constZRowBegin(8) << 8 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.constZRowEnd(0) << 1 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.constZRowEnd(1) << 2 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.constZRowEnd(4) << 5 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.constZRowEnd(7) << 8 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.constZRowEnd(8) << 8 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 8 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(44) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(70) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(71) << 8 << 7 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.constZBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.constZEnd() << -1 << -1 << false << true;
}

void ConstZIteratorTests::testIteratorCreationFromNonConstIterator_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixZIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.zBegin() << 0 << 0 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.zEnd() << 8 << 8 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.zRowBegin(0) << 0 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.zRowBegin(1) << 1 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.zRowBegin(4) << 4 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.zRowBegin(7) << 7 << 0 << true << true;
    QTest::newRow("{row begin iterator}") << m_PrimaryIntMatrix.zRowBegin(8) << 8 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.zRowEnd(0) << 1 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.zRowEnd(1) << 2 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.zRowEnd(4) << 5 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.zRowEnd(7) << 8 << 0 << true << true;
    QTest::newRow("{row end iterator}") << m_PrimaryIntMatrix.zRowEnd(8) << 8 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(0, 1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(5, 4) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(8, 6) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(8, 7) << 8 << 7 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(1) << 0 << 1 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(44) << 5 << 4 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(70) << 8 << 6 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getZIterator(71) << 8 << 7 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.zBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.zEnd() << -1 << -1 << false << true;
}

void ConstZIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0) << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(44) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(70) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(71) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.constZRowBegin(0) << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.getConstZIterator(1, 0);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.constZRowBegin(5) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.constZRowBegin(7) << m_PrimaryIntMatrix.getConstZIterator(7, 0);
    QTest::newRow("{row begin iterator, random iterator}") << m_PrimaryIntMatrix.constZRowBegin(8) << m_PrimaryIntMatrix.getConstZIterator(8, 0);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.constZRowEnd(0) << m_PrimaryIntMatrix.getConstZIterator(1, 0);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.constZRowEnd(1) << m_PrimaryIntMatrix.getConstZIterator(2, 0);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.constZRowEnd(5) << m_PrimaryIntMatrix.getConstZIterator(6, 0);
    QTest::newRow("{row end iterator, random iterator}") << m_PrimaryIntMatrix.constZRowEnd(7) << m_PrimaryIntMatrix.getConstZIterator(8, 0);
    QTest::newRow("{row end iterator, end iterator}") << m_PrimaryIntMatrix.constZRowEnd(8) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");

    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 0);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.constZEnd();
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

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd() << 0;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd() << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.constZEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.constZEnd() << 28;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZEnd() << 71;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 72;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 70;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 71;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 69;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -28;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 43;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 1;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZBegin() << -72;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZBegin() << -71;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.constZBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.constZBegin() << -44;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZBegin() << -1;
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(7, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(7, 2) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 2) << -2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstZIterator{} << IntMatrixConstZIterator{} << 0;
}

void ConstZIteratorTests::testAsteriskOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -12;
}

void ConstZIteratorTests::testArrowOperator_data()
{
    m_StringMatrix = {4, 3, {"abc", "ba", "abcd", "jihgfedcba", "a", "gfedcba", "abcde", "ihgfedcba", "abcdefgh", "", "abcdefghijk", "fedcba"}};

    QTest::addColumn<StringMatrixConstZIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_StringMatrix.constZBegin() << 3;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstZIterator(0, 1) << 2;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstZIterator(1, 2) << 7;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstZIterator(3, 1) << 11;
    QTest::newRow("{random iterator}") << m_StringMatrix.getConstZIterator(3, 2) << 6;
}

void ConstZIteratorTests::testSquareBracketsOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12}};

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 0 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 1 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 5 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 10 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 11 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << -4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 2) << 6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -11 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -10 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -6 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << -1 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3, 2) << 0 << -12;
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

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(1, 4) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(2, 0) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 3) << m_PrimaryIntMatrix.getConstZIterator(1, 4) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 3) << m_PrimaryIntMatrix.getConstZIterator(2, 0) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(2, 3) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(2, 3) << m_PrimaryIntMatrix.constZEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(2, 2) << m_PrimaryIntMatrix.constZEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(2) << m_PrimaryIntMatrix.getConstZIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(2) << m_PrimaryIntMatrix.getConstZIterator(10) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3) << m_PrimaryIntMatrix.getConstZIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(3) << m_PrimaryIntMatrix.getConstZIterator(10) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(13) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(13) << m_PrimaryIntMatrix.constZEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(12) << m_PrimaryIntMatrix.constZEnd() << 2 << 2;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 1 << 1;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(2) << 8 << 2;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(2) << m_PrimaryIntMatrix.constZRowEnd(2) << 9 << 1;
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(2) << m_PrimaryIntMatrix.constZRowEnd(3) << 9 << 2;
    QTest::newRow("{begin iterator, row begin iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowBegin(1) << 1 << 2;
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 1 << 1;
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 1 << 3;
    QTest::newRow("{row end iterator, end iterator}") << m_PrimaryIntMatrix.constZRowEnd(1) << m_PrimaryIntMatrix.constZEnd() << 1 << 0;
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

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 6 << m_PrimaryIntMatrix.getConstZIterator(1, 4);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << -1 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << -2 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("{row begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZRowEnd(1) << 10 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 5 << m_PrimaryIntMatrix.constZRowBegin(1);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 11 << m_PrimaryIntMatrix.getConstZIterator(19);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{row begin iterator, end iterator}") << m_PrimaryIntMatrix.constZRowBegin(1) << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 6 << m_PrimaryIntMatrix.getConstZIterator(9);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 8 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << -2 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("{begin iterator, row end iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZRowEnd(1) << 10 << m_PrimaryIntMatrix.constZRowEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 0 << m_PrimaryIntMatrix.getConstZIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstZIterator(3, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -1 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 0 << m_PrimaryIntMatrix.getConstZIterator(1, 3);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 11 << m_PrimaryIntMatrix.getConstZIterator(19);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(1, 3) << m_PrimaryIntMatrix.constZEnd() << 10 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -7 << m_PrimaryIntMatrix.getConstZIterator(3, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << -2 << m_PrimaryIntMatrix.getConstZIterator(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 11 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(3, 1) << 10 << m_PrimaryIntMatrix.getConstZIterator(3, 1);
}

void ConstZIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("firstIterator");
    QTest::addColumn<IntMatrixConstZIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constZBegin() << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.constZEnd() << m_SecondaryIntMatrix.constZBegin();
}

void ConstZIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.getConstZIterator(0, 2);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(4, 6) << m_PrimaryIntMatrix.getConstZIterator(4, 7);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(4, 7) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 0) << m_PrimaryIntMatrix.getConstZIterator(5, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 2);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 4) << m_PrimaryIntMatrix.getConstZIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(8, 6) << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.constZEnd();
}

void ConstZIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};

    QTest::addColumn<IntMatrixConstZIterator>("inputIterator");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.constZEnd() << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(8, 7) << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 5) << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 2) << m_PrimaryIntMatrix.getConstZIterator(5, 1);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 1) << m_PrimaryIntMatrix.getConstZIterator(5, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(5, 0) << m_PrimaryIntMatrix.getConstZIterator(4, 7);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(4, 7) << m_PrimaryIntMatrix.getConstZIterator(4, 6);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getConstZIterator(0, 2) << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getConstZIterator(0, 1) << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.constZBegin() << m_PrimaryIntMatrix.constZBegin();
}

void ConstZIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {9, 8, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixConstZIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixConstZIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constZBegin() << -3 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constZBegin() << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.constZBegin() << 0 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << 1 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << 4 << m_PrimaryIntMatrix.getConstZIterator(0, 4);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << 10 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << 70 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.constZBegin() << 71 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << 72 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << 73 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.constZBegin() << 75 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -4 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -2 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << -1 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 0 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 3 << m_PrimaryIntMatrix.getConstZIterator(0, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 9 << m_PrimaryIntMatrix.getConstZIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 69 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 70 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 71 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 72 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(0, 1) << 74 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -47 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -45 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -44 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -43 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -6 << m_PrimaryIntMatrix.getConstZIterator(4, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << -2 << m_PrimaryIntMatrix.getConstZIterator(5, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) <<  0 << m_PrimaryIntMatrix.getConstZIterator(5, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) <<  2 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 6 << m_PrimaryIntMatrix.getConstZIterator(6, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 26 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 27 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 28 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 29 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(5, 4) << 31 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -73 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -71 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -70 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -69 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -24 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << -3 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 0 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 1 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 2 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 3 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 6) << 5 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -74 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -72 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -71 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -70 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -25 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -4 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << -1 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 0 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 2 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getConstZIterator(8, 7) << 4 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constZEnd() << -75 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constZEnd() << -73 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.constZEnd() << -72 << m_PrimaryIntMatrix.constZBegin();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << -71 << m_PrimaryIntMatrix.getConstZIterator(0, 1);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << -26 << m_PrimaryIntMatrix.getConstZIterator(5, 6);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << -5 << m_PrimaryIntMatrix.getConstZIterator(8, 3);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << -2 << m_PrimaryIntMatrix.getConstZIterator(8, 6);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.constZEnd() << -1 << m_PrimaryIntMatrix.getConstZIterator(8, 7);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constZEnd() << 0 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constZEnd() << 1 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.constZEnd() << 3 << m_PrimaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constZBegin() << -1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.constZBegin() << 1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constZEnd() << 0 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constZEnd() << 1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.constZEnd() << -1 << m_SecondaryIntMatrix.constZEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstZIterator{} << -1 << IntMatrixConstZIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixConstZIterator{} << 1 << IntMatrixConstZIterator{};
}

QTEST_APPLESS_MAIN(ConstZIteratorTests)

#include "tst_constziteratortests.moc"
