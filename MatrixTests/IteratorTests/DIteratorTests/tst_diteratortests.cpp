#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixDIterator = Matrix<int>::DIterator;
using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using StringMatrix = Matrix<std::string>;
using StringMatrixDIterator = Matrix<std::string>::DIterator;

class DIteratorTests : public QObject
{
    Q_OBJECT

public:
    DIteratorTests();

private slots:
    // test functions
    void initTestCase();
    void testIteratorCreation();
    void testIteratorIsValid();
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
    void testSquareBracketsOperatorRead();
    void testSquareBracketsOperatorWrite();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrement();
    void testStdSort();

    // test data
    void testIteratorCreation_data();
    void testIteratorsAreEqual_data();
    void testLessThanOperator_data();
    void testLessThanOrEqualToOperator_data();
    void testGreaterThanOperator_data();
    void testGreaterThanOrEqualToOperator_data();
    void testOperatorPlus_data();
    void testOperatorMinus_data();
    void testOperatorPlusEqual_data();
    void testOperatorMinusEqual_data();
    void testDifferenceOperator_data();
    void testSquareBracketsOperatorRead_data();
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

    IntMatrixDIterator m_PrimaryIntIterator;
    IntMatrixDIterator m_SecondaryIntIterator;
    StringMatrixDIterator m_StringIterator;
};

/* Initialization of the test should be made by constructor and not by initTestCase() function for following reasons:
   - the diagonal iterator objects can only be initialized via Matrix functions (their constructors are private)
   - non-empty matrixes are required for creating diagonal iterators
   A minimal initialization is required to make iterators functional. These can then be modified by any of the type-compatible matrixes.
*/
DIteratorTests::DIteratorTests()
    : m_PrimaryIntMatrix{1, 1, 0}
    , m_SecondaryIntMatrix{1, 1, 0}
    , m_StringMatrix{1, 1, ""}
    , m_PrimaryIntIterator{m_PrimaryIntMatrix.dEnd(0)}
    , m_SecondaryIntIterator{m_SecondaryIntMatrix.dEnd(0)}
    , m_StringIterator{m_StringMatrix.dEnd(0)}
{
}

/* Initialization has been made through constructor, this special method should only check that it has been done correctly */
void DIteratorTests::initTestCase()
{
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));
    QVERIFY(m_SecondaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
    QVERIFY(m_StringIterator.isValidWithMatrix(m_StringMatrix));

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void DIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalNr);
    QFETCH(IntMatrix::size_type, expectedDiagonalIndex);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.getDiagonalNr() == expectedDiagonalNr &&
             iterator.getDiagonalIndex() == expectedDiagonalIndex &&
             iterator.isValidWithMatrix(m_PrimaryIntMatrix),
             "The iterator has not been correctly created!");
}

// additional test for checking that an iterator is only valid with the matrix with which it is created
void DIteratorTests::testIteratorIsValid()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = m_PrimaryIntMatrix;
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(2, 1);

    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void DIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator, "The iterators should be equal!");
}

void DIteratorTests::testIteratorEqualToItself()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(1, 2);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void DIteratorTests::testIteratorsAreNotEqual()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(1, 2);
    m_SecondaryIntIterator = m_PrimaryIntMatrix.getDIterator(1, 0, true);

    QVERIFY2(m_PrimaryIntIterator != m_SecondaryIntIterator, "The iterators should not be equal!");
}

void DIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator, "The first iterator should be less than the second one!");
}

void DIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator, "The first iterator should be less than or equal to the second one!");
}

void DIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator, "The second iterator should be greater than the first one!");
}

void DIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator, "The second iterator should be greater than or equal to the second one!");
}

void DIteratorTests::testIncrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    IntMatrixDIterator postPreIncrementIt{++(m_PrimaryIntIterator++)};

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && postPreIncrementIt == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.dEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.dEnd(2, 1),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.dEnd(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.dEnd(2, 1),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void DIteratorTests::testDecrementOperators()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");


    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.dEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.dEnd(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dEnd(-1);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 2),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(3, 2);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(2, 1),
             "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(-1);
    m_SecondaryIntIterator = m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 0),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void DIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixDIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void DIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixDIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void DIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixDIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void DIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixDIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void DIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixDIterator, firstIterator);
    QFETCH(IntMatrixDIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference, "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void DIteratorTests::testAsteriskOperator()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(2, 1);

    QVERIFY2(*m_PrimaryIntIterator == -8, "The asterisk operator does not work correctly when reading the value!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(1, 1, true);
    *m_PrimaryIntIterator = 14;

    QVERIFY2(m_PrimaryIntMatrix.at(1, 2) == 14, "The asterisk operator does not work correctly when writing the value!");
}

void DIteratorTests::testArrowOperator()
{
    m_StringMatrix = {2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};

    m_StringIterator = m_StringMatrix.dBegin(0, 1);

    QVERIFY2(m_StringIterator->size() == 5, "The arrow operator does not work correctly when reading the value!");

    m_StringIterator = m_StringMatrix.getDIterator(1, 2);
    m_StringIterator->assign("abcdefghij");

    QVERIFY2(*m_StringMatrix.getDIterator(1, 1, true) == "abcdefghij",
             "The arrow operator does not work correctly when writing the value!");
}

void DIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixDIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue, "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void DIteratorTests::testSquareBracketsOperatorWrite()
{
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(0, 1);
    m_PrimaryIntIterator[1] = 14;

    QVERIFY2(*m_PrimaryIntMatrix.getDIterator(1, 1, true) == 14, "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void DIteratorTests::testChangeDiagonal()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.dBegin(1);

    QVERIFY(*m_PrimaryIntIterator == 2);

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getDIterator(-2, 0, true);

    QVERIFY(m_PrimaryIntIterator[1] == -11);
}

void DIteratorTests::testStdCount()
{
    QFETCH(IntMatrixDIterator, leftIterator);
    QFETCH(IntMatrixDIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void DIteratorTests::testStdFind()
{
    QFETCH(IntMatrixDIterator, leftIterator);
    QFETCH(IntMatrixDIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixDIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void DIteratorTests::testStdFindWithIncrement()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  4, 6,  7,
                              1,  2, -3,  4, -5, 5,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.dBegin(1), m_PrimaryIntMatrix.dEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(1, 2), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.dEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getDIterator(3, 4), "The std::find algorithm does not return the expected iterator!");

    ++m_PrimaryIntIterator;
    m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.dEnd(1), 4);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.dEnd(1), "The std::find algorithm does not return the expected iterator!");
}

void DIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6, 7,
                              1,  2, -3,  4, -5, 6, 7,
                              1,  2, -3,  1, -5, 6, 7,
                              1,  2, -3,  4,  0, 6, 7,
                              1,  2, -3,  4, -5, 5, 7,
                              1,  2, -3,  4, -5, 6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -3, -3,  4, -5, 6, 7,
                                1,  2, -1,  4, -5, 6, 7,
                                1,  2, -3,  0, -5, 6, 7,
                                1,  2, -3,  4,  1, 6, 7,
                                1,  2, -3,  4, -5, 2, 7,
                                1,  2, -3,  4, -5, 6, 5,
                            }};

    std::sort(m_PrimaryIntMatrix.dBegin(1), m_PrimaryIntMatrix.dEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5,  6, 7,
                              1,  2,  5,  4, -5,  6, 7,
                              1,  2, -3,  1, -5,  6, 7,
                              1,  2, -3,  4,  0,  6, 7,
                              1,  2, -3,  4, -5, -3, 7,
                              1,  2, -3,  4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5,  6, 7,
                                1,  2,  0,  4, -5,  6, 7,
                                1,  2, -3,  1, -5,  6, 7,
                                1,  2, -3,  4,  5,  6, 7,
                                1,  2, -3,  4, -5, -3, 7,
                                1,  2, -3,  4, -5,  6, 2,
                            }};

    std::sort(m_PrimaryIntMatrix.getDIterator(1, 2), m_PrimaryIntMatrix.getDIterator(4, 5));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5,  6, 7,
                              1,  2,  5,  4, -5,  6, 7,
                              1,  2, -3,  1, -5,  6, 7,
                              1,  2, -3,  4,  0,  6, 7,
                              1,  2, -3,  4, -5, -3, 7,
                              1,  2, -3,  4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5,  6, 7,
                                1,  2,  0,  4, -5,  6, 7,
                                1,  2, -3,  1, -5,  6, 7,
                                1,  2, -3,  4,  5,  6, 7,
                                1,  2, -3,  4, -5, -3, 7,
                                1,  2, -3,  4, -5,  6, 2,
                            }};

    std::sort(m_PrimaryIntMatrix.dBegin(1), m_PrimaryIntMatrix.getDIterator(4, 5));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5,  6, 7,
                              1,  2,  5,  4, -5,  6, 7,
                              1,  2, -3,  1, -5,  6, 7,
                              1,  2, -3,  4,  0,  6, 7,
                              1,  2, -3,  4, -5, -3, 7,
                              1,  2, -3,  4, -5,  6, 2,
                          }};

    m_SecondaryIntMatrix = {6, 7, {
                                1, -1, -3,  4, -5,  6, 7,
                                1,  2, -3,  4, -5,  6, 7,
                                1,  2, -3,  0, -5,  6, 7,
                                1,  2, -3,  4,  1,  6, 7,
                                1,  2, -3,  4, -5,  2, 7,
                                1,  2, -3,  4, -5,  6, 5,
                            }};

    std::sort(m_PrimaryIntMatrix.getDIterator(1, 2), m_PrimaryIntMatrix.dEnd(1));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

/* Note the data tag for each row is the order in which tagged elements are inserted within row not the order in which they are used
   For example the testing methods for the < and > operators share the same table but their usage is in different order:
    - for < the first iterator is on the left side while the second is on the right side
    - for > the second iterator is placed on the left side while the first is on the right side (it1 < it2 <=> it2 > it1)
*/

void DIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalNr");
    QTest::addColumn<IntMatrixSizeType>("expectedDiagonalIndex");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(-2) << 2 << 0 << -2 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(0) << 0 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(1) << 0 << 1 << 1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(2, 1) << 1 << 0 << -1 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(0, 0) << 0 << 0 << 0 << 0;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(1, 2) << 0 << 1 << 1 << 0;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(-2) << 4 << 2 << -2 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(0) << 3 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(1) << 2 << 3 << 1 << 2;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(2, 1) << 4 << 3 << -1 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(0, 0) << 3 << 3 << 0 << 3;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(1, 2) << 2 << 3 << 1 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(1, 0) << 1 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(0, 2) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 2) << 2 << 2 << 0 << 2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 0, true) << 1 << 0 << -1 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 0, true) << 0 << 2 << 2 << 0;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << 2 << 1 << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(0, 2, true) << 2 << 2 << 0 << 2;
}

void DIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("firstIterator");
    QTest::addColumn<IntMatrixDIterator>("secondIterator");

    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(1, 2) << m_PrimaryIntMatrix.getDIterator(1, 1, true);
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.dBegin(-1) << m_PrimaryIntMatrix.dBegin(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.dBegin(2, 1) << m_PrimaryIntMatrix.getDIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(1, 0) << m_PrimaryIntMatrix.getDIterator(-1, 0, true);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.dEnd(2) << m_PrimaryIntMatrix.dEnd(0, 2);
}

void DIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void DIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void DIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void DIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void DIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void DIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void DIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void DIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void DIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("firstIterator");
    QTest::addColumn<IntMatrixDIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.dBegin(-1) << m_PrimaryIntMatrix.dBegin(1, 0) << 0;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getDIterator(2, 2) << m_PrimaryIntMatrix.dBegin(0, 0) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getDIterator(-1, 2, true) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(1, 2) << m_PrimaryIntMatrix.getDIterator(1, 0, true) << -1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 0, true) << m_PrimaryIntMatrix.dEnd(-1) << 3;
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.dEnd(1) << m_PrimaryIntMatrix.dEnd(0, 1) << 0;
}

void DIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(0, 1) << 0 << 2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.dBegin(0, 1) << 1 << 6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << -1 << 4;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << 0 << -8;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << 1 << 12;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(0) << -3 << 1;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(0) << -2 << -5;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.dEnd(0) << -1 << 9;
}

void DIteratorTests::testStdCount_data()
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

    QTest::addColumn<IntMatrixDIterator>("leftIterator");
    QTest::addColumn<IntMatrixDIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.dBegin(1) << m_PrimaryIntMatrix.dEnd(1) << -3 << 1;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.dBegin(1) << m_SecondaryIntMatrix.dEnd(1) << -1 << 3;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(0, 1) << m_PrimaryIntMatrix.getDIterator(1, 0, true) << -3 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getDIterator(1, 1, true) << m_SecondaryIntMatrix.getDIterator(4, 5) << 4 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_SecondaryIntMatrix.getDIterator(2, 3) << m_SecondaryIntMatrix.getDIterator(1, 4, true) << 4 << 0;
}

void DIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {6, 7, {
                              1, -1, -3,  4, -5, 6,  7,
                              1,  2,  4,  4, -5, 6,  7,
                              1,  2, -3, -1, -5, 6,  7,
                              1,  2, -3,  4,  5, 6,  7,
                              1,  2, -3,  4, -5, 4,  7,
                              1,  2, -3,  4, -5, 6, -1,
                          }};

    QTest::addColumn<IntMatrixDIterator>("leftIterator");
    QTest::addColumn<IntMatrixDIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.dBegin(1) << m_PrimaryIntMatrix.dEnd(1) << 5 << m_PrimaryIntMatrix.getDIterator(3, 4);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.dBegin(1) << m_PrimaryIntMatrix.dEnd(1) << -9 << m_PrimaryIntMatrix.dEnd(1);
}

void DIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("firstIterator");
    QTest::addColumn<IntMatrixDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.dBegin(1) << m_PrimaryIntMatrix.getDIterator(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getDIterator(1, 2) << m_PrimaryIntMatrix.dEnd(1);
}

void DIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("firstIterator");
    QTest::addColumn<IntMatrixDIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.dBegin(-1) << m_PrimaryIntMatrix.getDIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(1, 0) << m_PrimaryIntMatrix.getDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(2, 1) << m_PrimaryIntMatrix.getDIterator(-1, 1, true);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << m_PrimaryIntMatrix.dEnd(-1);
}

void DIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    m_SecondaryIntMatrix = {3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

    QTest::addColumn<IntMatrixDIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixDIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.dBegin(-1) << -1 << m_PrimaryIntMatrix.dBegin(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.dBegin(-1) << 2 << m_PrimaryIntMatrix.getDIterator(3, 2);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.dBegin(-1) << 3 << m_PrimaryIntMatrix.dEnd(1, 0);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.dBegin(-1) << 4 << m_PrimaryIntMatrix.dEnd(1, 0);

    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << -2 << m_PrimaryIntMatrix.dBegin(1, 0);
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << -1 << m_PrimaryIntMatrix.dBegin(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << 0 << m_PrimaryIntMatrix.getDIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << 1 << m_PrimaryIntMatrix.getDIterator(3, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << 2 << m_PrimaryIntMatrix.dEnd(1, 0);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getDIterator(-1, 1, true) << 3 << m_PrimaryIntMatrix.dEnd(1, 0);

    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.dEnd(-1) << -4 << m_PrimaryIntMatrix.dBegin(1, 0);
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.dEnd(-1) << -3 << m_PrimaryIntMatrix.dBegin(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.dEnd(-1) << -1 << m_PrimaryIntMatrix.getDIterator(3, 2);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.dEnd(-1) << 1 << m_PrimaryIntMatrix.dEnd(1, 0);

    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.dBegin(0, 1) << -2 << m_SecondaryIntMatrix.dBegin(0, 1);
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.dBegin(0, 1) << -1 << m_SecondaryIntMatrix.dBegin(0, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_SecondaryIntMatrix.dBegin(0, 1) << 2 << m_SecondaryIntMatrix.getDIterator(2, 3);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.dBegin(0, 1) << 3 << m_SecondaryIntMatrix.dEnd(0, 1);
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.dBegin(0, 1) << 4 << m_SecondaryIntMatrix.dEnd(0, 1);
}

QTEST_APPLESS_MAIN(DIteratorTests)

#include "tst_diteratortests.moc"
