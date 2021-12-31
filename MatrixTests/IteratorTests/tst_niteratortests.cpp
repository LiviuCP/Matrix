#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrixNIterator)
Q_DECLARE_METATYPE(StringMatrixNIterator)

class NIteratorTests : public QObject
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
    void testAsteriskOperatorRead();
    void testAsteriskOperatorWrite();
    void testAsteriskOperatorReadWrite();
    void testArrowOperatorRead();
    void testArrowOperatorWrite();
    void testArrowOperatorReadWrite();
    void testSquareBracketsOperatorRead();
    void testSquareBracketsOperatorWrite();
    void testStdCount();
    void testStdFind();
    void testStdFindWithIncrementAndCount();
    void testStdSort();

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
    void testAsteriskOperatorRead_data();
    void testArrowOperatorRead_data();
    void testSquareBracketsOperatorRead_data();
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

    IntMatrixNIterator m_PrimaryIntIterator;
    IntMatrixNIterator m_SecondaryIntIterator;
    StringMatrixNIterator m_StringIterator;
};

void NIteratorTests::testIteratorCreation()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrix::size_type, expectedRowNr);
    QFETCH(IntMatrix::size_type, expectedColumnNr);
    QFETCH(bool, isPrimaryMatrix);
    QFETCH(bool, expectedValidity);

    QVERIFY2(iterator.getRowNr() == expectedRowNr &&
             iterator.getColumnNr() == expectedColumnNr &&
             iterator.isValidWithMatrix(isPrimaryMatrix ? m_PrimaryIntMatrix : m_SecondaryIntMatrix) == expectedValidity,
             "The iterator has not been correctly created!");
}

void NIteratorTests::testIteratorIsValidWithOneMatrix()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(4, 5);
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_SecondaryIntMatrix.clear();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.nBegin();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntIterator = m_SecondaryIntMatrix.nEnd();
    QVERIFY(!m_PrimaryIntIterator.isValidWithMatrix(m_PrimaryIntMatrix));

    m_PrimaryIntMatrix.clear();
    m_PrimaryIntIterator = m_PrimaryIntMatrix.nBegin();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));

    m_PrimaryIntIterator = m_PrimaryIntMatrix.nEnd();
    QVERIFY(m_PrimaryIntIterator.isValidWithMatrix(m_SecondaryIntMatrix));
}

void NIteratorTests::testEmptyIterator()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();
    IntMatrixNIterator emptyIt;

    QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1, "The iterator has not been correctly created!");
    QVERIFY(!emptyIt.isValidWithMatrix(m_PrimaryIntMatrix) && emptyIt.isValidWithMatrix(m_SecondaryIntMatrix));
}

void NIteratorTests::testIteratorsAreEqual()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(firstIterator == secondIterator && !(firstIterator != secondIterator), "The iterators should be equal!");
}

void NIteratorTests::testIteratorEqualToItself()
{
    QFETCH(IntMatrixNIterator, iterator);

    m_PrimaryIntIterator = iterator;

    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator != m_PrimaryIntIterator) &&
             m_PrimaryIntIterator <= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator > m_PrimaryIntIterator) &&
             m_PrimaryIntIterator >= m_PrimaryIntIterator &&
             !(m_PrimaryIntIterator < m_PrimaryIntIterator),
             "The iterator should be equal to itself!");
}

void NIteratorTests::testIteratorsAreNotEqual()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(firstIterator != secondIterator && !(firstIterator == secondIterator), "The iterators should not be equal!");
}

void NIteratorTests::testLessThanOperator()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(firstIterator < secondIterator && !(firstIterator >= secondIterator), "The first iterator should be less than the second one!");
}

void NIteratorTests::testLessThanOrEqualToOperator()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(firstIterator <= secondIterator && !(firstIterator > secondIterator), "The first iterator should be less than or equal to the second one!");
}

void NIteratorTests::testGreaterThanOperator()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(secondIterator > firstIterator && !(secondIterator <= firstIterator), "The second iterator should be greater than the first one!");
}

void NIteratorTests::testGreaterThanOrEqualToOperator()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);

    QVERIFY2(secondIterator >= firstIterator && !(secondIterator < firstIterator), "The second iterator should be greater than or equal to the first one!");
}

void NIteratorTests::testPreIncrementOperator()
{
    QFETCH(IntMatrixNIterator, inputIterator);
    QFETCH(IntMatrixNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    ++m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testPostIncrementOperator()
{
    QFETCH(IntMatrixNIterator, inputIterator);
    QFETCH(IntMatrixNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator++;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testCombinedIncrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(4, 5);
    m_SecondaryIntIterator = ++(++m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(6, 5),
             "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(4, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator++)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(4, 5),
             "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(4, 5);
    m_SecondaryIntIterator = (++m_PrimaryIntIterator)++;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(4, 5);
    m_SecondaryIntIterator = ++(m_PrimaryIntIterator++);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5),
             "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testPreDecrementOperator()
{
    QFETCH(IntMatrixNIterator, inputIterator);
    QFETCH(IntMatrixNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    --m_PrimaryIntIterator;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testPostDecrementOperator()
{
    QFETCH(IntMatrixNIterator, inputIterator);
    QFETCH(IntMatrixNIterator, expectedIterator);

    m_PrimaryIntIterator = inputIterator;
    m_PrimaryIntIterator--;

    QVERIFY2(m_PrimaryIntIterator == expectedIterator,
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testCombinedDecrementOperators()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(6, 5);
    m_SecondaryIntIterator = --(--m_PrimaryIntIterator);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(4, 5),
             "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(6, 5);
    m_SecondaryIntIterator = (m_PrimaryIntIterator--)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(6, 5),
             "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(6, 5);
    m_SecondaryIntIterator = (--m_PrimaryIntIterator)--;
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(6, 5);
    m_SecondaryIntIterator = --(m_PrimaryIntIterator--);
    QVERIFY2(m_PrimaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5) && m_SecondaryIntIterator == m_PrimaryIntMatrix.getNIterator(5, 5),
             "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element!");
}

void NIteratorTests::testOperatorPlus()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixNIterator, expectedIterator);

    QVERIFY2(iterator + scalarValue == expectedIterator, "Operator + does not work correctly, the resulting iterator does not point to the right element!");
}

void NIteratorTests::testOperatorMinus()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixNIterator, expectedIterator);

    scalarValue = -scalarValue;

    QVERIFY2(iterator - scalarValue == expectedIterator, "Operator - does not work correctly, the resulting iterator does not point to the right element!");
}

void NIteratorTests::testOperatorPlusEqual()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixNIterator, expectedIterator);

    iterator += scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator += does not work correctly, the resulting iterator does not point to the right element!");
}

void NIteratorTests::testOperatorMinusEqual()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrixDiffType, scalarValue);
    QFETCH(IntMatrixNIterator, expectedIterator);

    scalarValue = -scalarValue;
    iterator -= scalarValue;

    QVERIFY2(iterator == expectedIterator, "Operator -= does not work correctly, the resulting iterator does not point to the right element!");
}

void NIteratorTests::testDifferenceOperator()
{
    QFETCH(IntMatrixNIterator, firstIterator);
    QFETCH(IntMatrixNIterator, secondIterator);
    QFETCH(IntMatrix::size_type, expectedDifference);

    QVERIFY2(secondIterator - firstIterator == expectedDifference,
             "The difference operator does not work correctly, difference between iterators is not the expected one!");
}

void NIteratorTests::testAsteriskOperatorRead()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(*iterator == expectedValue, "The asterisk operator does not work correctly when reading the value!");
}

void NIteratorTests::testAsteriskOperatorWrite()
{
    m_PrimaryIntMatrix = {3, 4, -20};
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};
    *m_PrimaryIntMatrix.nBegin() = 1;
    *m_PrimaryIntMatrix.getNIterator(1, 0) = -2;
    *m_PrimaryIntMatrix.getNIterator(2, 1) = -6;
    *m_PrimaryIntMatrix.getNIterator(1, 3) = 11;
    *m_PrimaryIntMatrix.getNIterator(2, 3) = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The asterisk operator does not work correctly when writing the value!");
}

void NIteratorTests::testAsteriskOperatorReadWrite()
{
    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.nBegin();
    m_PrimaryIntMatrix.at(2, 0) = 10;
    m_PrimaryIntIterator += 2;

    QVERIFY(*m_PrimaryIntIterator == 10);

    m_PrimaryIntMatrix = {3, 2, {1, 4, 2, -5, -3, 6}};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.nBegin();
    m_PrimaryIntIterator += 2;
    *m_PrimaryIntIterator = 10;

    QVERIFY(m_PrimaryIntMatrix.at(2, 0) == 10);
}

void NIteratorTests::testArrowOperatorRead()
{
    QFETCH(StringMatrixNIterator, iterator);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator->size() == static_cast<size_t>(expectedValue), "The arrow operator does not work correctly when reading the value!");
}

void NIteratorTests::testArrowOperatorWrite()
{
    m_PrimaryStringMatrix = {3, 4, "zzz"};
    m_SecondaryStringMatrix = {3, 4, {"abc", "zzz","zzz","zzz","ba","zzz","zzz","abcdefghijk","zzz","gfedcba","zzz","fedcba"}};
    m_PrimaryStringMatrix.nBegin()->assign("abc");
    m_PrimaryStringMatrix.getNIterator(1, 0)->assign("ba");
    m_PrimaryStringMatrix.getNIterator(2, 1)->assign("gfedcba");
    m_PrimaryStringMatrix.getNIterator(1, 3)->assign("abcdefghijk");
    m_PrimaryStringMatrix.getNIterator(2, 3)->assign("fedcba");

    QVERIFY2(m_PrimaryStringMatrix == m_SecondaryStringMatrix, "The arrow operator does not work correctly when writing the value!");
}

void NIteratorTests::testArrowOperatorReadWrite()
{
    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.nBegin();
    m_PrimaryStringMatrix.at(2, 0) = "abcdefghi";
    m_StringIterator += 2;

    QVERIFY(m_StringIterator->size() == 9);

    m_PrimaryStringMatrix = {3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    m_StringIterator = m_PrimaryStringMatrix.nBegin();
    m_StringIterator += 2;
    m_StringIterator->assign("abcdefghi");

    QVERIFY(m_PrimaryStringMatrix.at(2, 0) == "abcdefghi");
}

void NIteratorTests::testSquareBracketsOperatorRead()
{
    QFETCH(IntMatrixNIterator, iterator);
    QFETCH(IntMatrixDiffType, index);
    QFETCH(int, expectedValue);

    QVERIFY2(iterator[index] == expectedValue,
             "The dereference square brackets operator doesn't work correctly when reading the value from the given index!");
}

void NIteratorTests::testSquareBracketsOperatorWrite()
{
    m_SecondaryIntMatrix = {3, 4, {1, -20, -20, -20, -2, -20, -20, 11, -20, -6, -20, -12}};

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.nBegin();
    m_PrimaryIntIterator[0] = 1;
    m_PrimaryIntIterator[1] = -2;
    m_PrimaryIntIterator[5] = -6;
    m_PrimaryIntIterator[10] = 11;
    m_PrimaryIntIterator[11] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(1, 0);
    m_PrimaryIntIterator[-1] = 1;
    m_PrimaryIntIterator[0] = -2;
    m_PrimaryIntIterator[4] = -6;
    m_PrimaryIntIterator[9] = 11;
    m_PrimaryIntIterator[10] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(2, 1);
    m_PrimaryIntIterator[-5] = 1;
    m_PrimaryIntIterator[-4] = -2;
    m_PrimaryIntIterator[0] = -6;
    m_PrimaryIntIterator[5] = 11;
    m_PrimaryIntIterator[6] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(1, 3);
    m_PrimaryIntIterator[-10] = 1;
    m_PrimaryIntIterator[-9] = -2;
    m_PrimaryIntIterator[-5] = -6;
    m_PrimaryIntIterator[0] = 11;
    m_PrimaryIntIterator[1] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");

    m_PrimaryIntMatrix = {3, 4, -20};
    m_PrimaryIntIterator = m_PrimaryIntMatrix.getNIterator(2, 3);
    m_PrimaryIntIterator[-11] = 1;
    m_PrimaryIntIterator[-10] = -2;
    m_PrimaryIntIterator[-6] = -6;
    m_PrimaryIntIterator[-1] = 11;
    m_PrimaryIntIterator[0] = -12;

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix,
             "The dereference square brackets operator doesn't work correctly when writing the value to the given index!");
}

void NIteratorTests::testStdCount()
{
    QFETCH(IntMatrixNIterator, leftIterator);
    QFETCH(IntMatrixNIterator, rightIterator);
    QFETCH(int, countedValue);
    QFETCH(IntMatrixDiffType, expectedCount);

    QVERIFY2(std::count(leftIterator, rightIterator, countedValue) == expectedCount, "The std::count algorithm does not return the expected value!");
}

void NIteratorTests::testStdFind()
{
    QFETCH(IntMatrixNIterator, leftIterator);
    QFETCH(IntMatrixNIterator, rightIterator);
    QFETCH(int, searchedValue);
    QFETCH(IntMatrixNIterator, expectedIterator);

    m_PrimaryIntIterator = std::find(leftIterator, rightIterator, searchedValue);
    QVERIFY2(m_PrimaryIntIterator == expectedIterator, "The std::find algorithm does not return the expected iterator!");
}

void NIteratorTests::testStdFindWithIncrementAndCount()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};

    m_PrimaryIntIterator = std::find(m_PrimaryIntMatrix.nBegin(), m_PrimaryIntMatrix.nEnd(), 4);

    ++m_PrimaryIntIterator;

    QVERIFY2(*m_PrimaryIntIterator == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned!");
    QVERIFY2(std::find(m_PrimaryIntMatrix.nBegin(), m_PrimaryIntMatrix.nEnd(), 10) == m_PrimaryIntMatrix.nEnd(),
             "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix!");

    m_PrimaryIntIterator = m_PrimaryIntMatrix.nBegin();

    while(m_PrimaryIntIterator != m_PrimaryIntMatrix.nEnd())
    {
        m_PrimaryIntIterator = std::find(m_PrimaryIntIterator, m_PrimaryIntMatrix.nEnd(), 9);

        if (m_PrimaryIntIterator != m_PrimaryIntMatrix.nEnd())
        {
            *m_PrimaryIntIterator = 10;
        }
    }

    QVERIFY2(std::count(m_PrimaryIntMatrix.nBegin(), m_PrimaryIntMatrix.nEnd(), 10) == 3,
             "The iterator doesn't work properly with std::find, element values haven't been correctly replaced!");
}

void NIteratorTests::testStdSort()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5,  2, -7,
                               1, 9, -2,  7,
                               3, 8,  2,  2,
                               1, 0,  8,  9,
                               4, 6,  9,  11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                -1, 0, -2, -7,
                                 1, 5,  2,  2,
                                 1, 6,  2,  7,
                                 3, 8,  8,  9,
                                 4, 9,  9,  11
                            }};

    for (int col{0}; col<m_PrimaryIntMatrix.getNrOfColumns(); ++col)
    {
        std::sort(m_PrimaryIntMatrix.nColumnBegin(col), m_PrimaryIntMatrix.nColumnEnd(col));
    }

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                               -7, 1, 4, 8,
                               -2, 2, 5, 9,
                               -1, 2, 6, 9,
                                0, 2, 7, 9,
                                1, 3, 8, 11
                            }};

    std::sort(m_PrimaryIntMatrix.nBegin(), m_PrimaryIntMatrix.nEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                               -1, 5, 2, -7,
                                1, 9, -2, 7,
                                3, 8, 2, 2,
                                1, 0, 8, 9,
                                4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                -1, 5, 0, 9,
                                 1, 9, 2, 7,
                                 3, 8, 2, 2,
                                 1, -7, 6, 9,
                                 4, -2, 8, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getNIterator(3, 1), m_PrimaryIntMatrix.getNIterator(1, 3));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                -1, 3, 9, -7,
                                 0, 4, -2, 7,
                                 1, 5, 2, 2,
                                 1, 6, 8, 9,
                                 2, 8, 9, 11
                            }};

    std::sort(m_PrimaryIntMatrix.nBegin(), m_PrimaryIntMatrix.getNIterator(1, 2));

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");

    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    m_SecondaryIntMatrix = {5, 4, {
                                -1, 5, 2, 7,
                                 1, 9, -7, 8,
                                 3, 8, -2, 9,
                                 1, 0, 2, 9,
                                 4, 6, 2, 11
                            }};

    std::sort(m_PrimaryIntMatrix.getNIterator(1, 2), m_PrimaryIntMatrix.nEnd());

    QVERIFY2(m_PrimaryIntMatrix == m_SecondaryIntMatrix, "The std::sort algorithm does not sort the matrix as expected!");
}

void NIteratorTests::testIteratorCreation_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixNIterator>("iterator");
    QTest::addColumn<IntMatrixSizeType>("expectedRowNr");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnNr");
    QTest::addColumn<bool>("isPrimaryMatrix");
    QTest::addColumn<bool>("expectedValidity");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 0 << 0 << true << true;
    QTest::newRow("{end iterator}") << m_PrimaryIntMatrix.nEnd() << 8 << 8 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.nColumnBegin(0) << 0 << 0 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << 0 << 1 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.nColumnBegin(4) << 0 << 4 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.nColumnBegin(7) << 0 << 7 << true << true;
    QTest::newRow("{column begin iterator}") << m_PrimaryIntMatrix.nColumnBegin(8) << 0 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.nColumnEnd(0) << 0 << 1 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.nColumnEnd(1) << 0 << 2 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.nColumnEnd(4) << 0 << 5 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.nColumnEnd(7) << 0 << 8 << true << true;
    QTest::newRow("{column end iterator}") << m_PrimaryIntMatrix.nColumnEnd(8) << 8 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(0, 0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << 7 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(0) << 0 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1) << 1 << 0 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(44) << 4 << 5 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(70) << 6 << 8 << true << true;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(71) << 7 << 8 << true << true;
    QTest::newRow("{begin iterator}") << m_SecondaryIntMatrix.nBegin() << -1 << -1 << false << true;
    QTest::newRow("{end iterator}") << m_SecondaryIntMatrix.nEnd() << -1 << -1 << false << true;
}

void NIteratorTests::testIteratorsAreEqual_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixNIterator>("firstIterator");
    QTest::addColumn<IntMatrixNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(0) << m_PrimaryIntMatrix.getNIterator(0, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1) << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(44) << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(70) << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(71) << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.nColumnBegin(0) << m_PrimaryIntMatrix.getNIterator(0, 0);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.getNIterator(0, 1);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.nColumnBegin(5) << m_PrimaryIntMatrix.getNIterator(0, 5);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.nColumnBegin(7) << m_PrimaryIntMatrix.getNIterator(0, 7);
    QTest::newRow("{column begin iterator, random iterator}") << m_PrimaryIntMatrix.nColumnBegin(8) << m_PrimaryIntMatrix.getNIterator(0, 8);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.nColumnEnd(0) << m_PrimaryIntMatrix.getNIterator(0, 1);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.nColumnEnd(1) << m_PrimaryIntMatrix.getNIterator(0, 2);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.nColumnEnd(5) << m_PrimaryIntMatrix.getNIterator(0, 6);
    QTest::newRow("{column end iterator, random iterator}") << m_PrimaryIntMatrix.nColumnEnd(7) << m_PrimaryIntMatrix.getNIterator(0, 8);
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.nColumnEnd(8) << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.nEnd();
}

void NIteratorTests::testIteratorEqualToItself_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixNIterator>("iterator");

    QTest::newRow("{begin iterator}")  << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(0, 0);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{end iterator}")  << m_PrimaryIntMatrix.nEnd();
}

void NIteratorTests::testIteratorsAreNotEqual_data()
{
    _buildLessThanOperatorTestingTable();
}

void NIteratorTests::testLessThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void NIteratorTests::testLessThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void NIteratorTests::testGreaterThanOperator_data()
{
    _buildLessThanOperatorTestingTable();
}

void NIteratorTests::testGreaterThanOrEqualToOperator_data()
{
    _buildLessThanOrEqualOperatorTestingTable();
}

void NIteratorTests::testPreIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void NIteratorTests::testPostIncrementOperator_data()
{
    _buildIncrementOperatorTestingTable();
}

void NIteratorTests::testPreDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void NIteratorTests::testPostDecrementOperator_data()
{
    _buildDecrementOperatorTestingTable();
}

void NIteratorTests::testOperatorPlus_data()
{
    _buildOperatorPlusTestingTable();
}

void NIteratorTests::testOperatorMinus_data()
{
    _buildOperatorPlusTestingTable();
}

void NIteratorTests::testOperatorPlusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void NIteratorTests::testOperatorMinusEqual_data()
{
    _buildOperatorPlusTestingTable();
}

void NIteratorTests::testDifferenceOperator_data()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixNIterator>("firstIterator");
    QTest::addColumn<IntMatrixNIterator>("secondIterator");
    QTest::addColumn<IntMatrixDiffType>("expectedDifference");

    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.nEnd() << 0;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.nEnd() << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.nEnd() << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.nEnd() << 28;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.nEnd() << 71;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nEnd() << 72;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.getNIterator(7, 8) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(7, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(7, 8) << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(7, 8) << 27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(7, 8) << 70;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(7, 8) << 71;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.getNIterator(6, 8) << -2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(6, 8) << -1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(6, 8) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(6, 8) << 26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(6, 8) << 69;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(6, 8) << 70;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.getNIterator(4, 5) << -28;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(4, 5) << -27;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(4, 5) << -26;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(4, 5) << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(4, 5) << 43;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(4, 5) << 44;
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.getNIterator(1, 0) << -71;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(1, 0) << -70;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(1, 0) << -69;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(1, 0) << -43;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(1, 0) << 0;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 0) << 1;
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.nBegin() << -72;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.nBegin() << -71;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.nBegin() << -70;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.nBegin() << -44;
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.nBegin() << -1;
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nBegin() << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 7) << m_PrimaryIntMatrix.getNIterator(4, 5) << -14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(2, 7) << 14;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 5) << m_PrimaryIntMatrix.getNIterator(4, 5) << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(2, 5) << -2;
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.nEnd() << 0;
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.nBegin() << 0;
    QTest::newRow("{begin iterator, begin iterator}") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.nBegin() << 0;
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.nEnd() << 0;
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixNIterator{} << IntMatrixNIterator{} << 0;
}

void NIteratorTests::testAsteriskOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << -12;
}

void NIteratorTests::testArrowOperatorRead_data()
{
    m_PrimaryStringMatrix = {3, 4, {"abc", "jihgfedcba", "abcde", "", "ba", "a", "ihgfedcba", "abcdefghijk", "abcd", "gfedcba", "abcdefgh", "fedcba"}};

    QTest::addColumn<StringMatrixNIterator>("iterator");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryStringMatrix.nBegin() << 3;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getNIterator(1, 0) << 2;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getNIterator(2, 1) << 7;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getNIterator(1, 3) << 11;
    QTest::newRow("{random iterator}") << m_PrimaryStringMatrix.getNIterator(2, 3) << 6;
}

void NIteratorTests::testSquareBracketsOperatorRead_data()
{
    m_PrimaryIntMatrix = {3, 4, {1, -4, 7, -10, -2, 5, -8, 11, 3, -6, 9, -12}};

    QTest::addColumn<IntMatrixNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("index");
    QTest::addColumn<int>("expectedValue");

    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 0 << 1;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 1 << -2;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 5 << -6;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 10 << 11;
    QTest::newRow("{begin iterator}") << m_PrimaryIntMatrix.nBegin() << 11 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << -1 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 0 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 4 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 9 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 10 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << -5 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << -4 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << 0 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << 5 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 1) << 6 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << -10 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << -9 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << -5 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << 0 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 3) << 1 << -12;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << -11 << 1;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << -10 << -2;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << -6 << -6;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << -1 << 11;
    QTest::newRow("{random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 3) << 0 << -12;
}

void NIteratorTests::testStdCount_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 1, 9, 8
                          }};

    QTest::addColumn<IntMatrixNIterator>("leftIterator");
    QTest::addColumn<IntMatrixNIterator>("rightIterator");
    QTest::addColumn<int>("countedValue");
    QTest::addColumn<IntMatrixDiffType>("expectedCount");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nEnd() << 2 << 3;
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nEnd() << -5 << 0;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(4, 1) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(0, 2) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 0) << m_PrimaryIntMatrix.getNIterator(4, 1) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 0) << m_PrimaryIntMatrix.getNIterator(0, 2) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(3, 2) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 2) << m_PrimaryIntMatrix.nEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(2, 2) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(2, 2) << m_PrimaryIntMatrix.nEnd() << 2 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2) << m_PrimaryIntMatrix.getNIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2) << m_PrimaryIntMatrix.getNIterator(10) << 1 << 2;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3) << m_PrimaryIntMatrix.getNIterator(9) << 1 << 1;
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3) << m_PrimaryIntMatrix.getNIterator(10) << 1 << 2;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(13) << 2 << 2;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(13) << m_PrimaryIntMatrix.nEnd() << 2 << 1;
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(12) << 2 << 1;
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(12) << m_PrimaryIntMatrix.nEnd() << 2 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << 1 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(2) << 8 << 2;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(2) << m_PrimaryIntMatrix.nColumnEnd(2) << 9 << 1;
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(2) << m_PrimaryIntMatrix.nColumnEnd(3) << 9 << 2;
    QTest::newRow("{begin iterator, column begin iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnBegin(1) << 1 << 2;
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << 1 << 1;
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << 1 << 3;
    QTest::newRow("{column end iterator, end iterator}") << m_PrimaryIntMatrix.nColumnEnd(1) << m_PrimaryIntMatrix.nEnd() << 1 << 0;
}

void NIteratorTests::testStdFind_data()
{
    m_PrimaryIntMatrix = {5, 4, {
                              -1, 5, 2, -7,
                               1, 9, -2, 7,
                               3, 8, 2, 2,
                               1, 0, 8, 9,
                               4, 6, 9, 11
                          }};

    QTest::addColumn<IntMatrixNIterator>("leftIterator");
    QTest::addColumn<IntMatrixNIterator>("rightIterator");
    QTest::addColumn<int>("searchedValue");
    QTest::addColumn<IntMatrixNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nEnd() << 5 << m_PrimaryIntMatrix.nColumnBegin(1);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nEnd() << 10 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << 5 << m_PrimaryIntMatrix.nColumnBegin(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << 6 << m_PrimaryIntMatrix.getNIterator(4, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << 8 << m_PrimaryIntMatrix.getNIterator(2, 1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << -1 << m_PrimaryIntMatrix.nColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << -2 << m_PrimaryIntMatrix.nColumnEnd(1);
    QTest::newRow("{column begin iterator, column end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nColumnEnd(1) << 10 << m_PrimaryIntMatrix.nColumnEnd(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << 5 << m_PrimaryIntMatrix.nColumnBegin(1);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << 11 << m_PrimaryIntMatrix.getNIterator(19);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << -2 << m_PrimaryIntMatrix.getNIterator(1, 2);
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << -1 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{column begin iterator, end iterator}") << m_PrimaryIntMatrix.nColumnBegin(1) << m_PrimaryIntMatrix.nEnd() << 10 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << -1 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << 6 << m_PrimaryIntMatrix.getNIterator(9);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << 8 << m_PrimaryIntMatrix.getNIterator(2, 1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << -2 << m_PrimaryIntMatrix.nColumnEnd(1);
    QTest::newRow("{begin iterator, column end iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nColumnEnd(1) << 10 << m_PrimaryIntMatrix.nColumnEnd(1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << 0 << m_PrimaryIntMatrix.getNIterator(3, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getNIterator(0, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getNIterator(1, 2);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << -1 << m_PrimaryIntMatrix.getNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getNIterator(1, 3);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.getNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getNIterator(1, 3);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.nEnd() << 0 << m_PrimaryIntMatrix.getNIterator(3, 1);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.nEnd() << 11 << m_PrimaryIntMatrix.getNIterator(19);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.nEnd() << -2 << m_PrimaryIntMatrix.getNIterator(1, 2);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.nEnd() << -1 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(3, 1) << m_PrimaryIntMatrix.nEnd() << 10 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 3) << -1 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 3) << -7 << m_PrimaryIntMatrix.getNIterator(0, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 3) << -2 << m_PrimaryIntMatrix.getNIterator(1, 2);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 3) << 11 << m_PrimaryIntMatrix.getNIterator(1, 3);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 3) << 10 << m_PrimaryIntMatrix.getNIterator(1, 3);
}

void NIteratorTests::_buildLessThanOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixNIterator>("firstIterator");
    QTest::addColumn<IntMatrixNIterator>("secondIterator");

    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.nEnd();
}

void NIteratorTests::_buildLessThanOrEqualOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixNIterator>("firstIterator");
    QTest::addColumn<IntMatrixNIterator>("secondIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.nBegin() << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_SecondaryIntMatrix.nEnd() << m_SecondaryIntMatrix.nBegin();
}

void NIteratorTests::_buildIncrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixNIterator>("inputIterator");
    QTest::addColumn<IntMatrixNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, random iterator}")  << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.getNIterator(2, 0);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(6, 4) << m_PrimaryIntMatrix.getNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(7, 4) << m_PrimaryIntMatrix.getNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(0, 5) << m_PrimaryIntMatrix.getNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(1, 5) << m_PrimaryIntMatrix.getNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(4, 5) << m_PrimaryIntMatrix.getNIterator(5, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(6, 8) << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}")  << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}")  << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.nEnd();
}

void NIteratorTests::_buildDecrementOperatorTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};

    QTest::addColumn<IntMatrixNIterator>("inputIterator");
    QTest::addColumn<IntMatrixNIterator>("expectedIterator");

    QTest::newRow("{end iterator, random iterator}")  << m_PrimaryIntMatrix.nEnd() << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(7, 8) << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(5, 5) << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(2, 5) << m_PrimaryIntMatrix.getNIterator(1, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(1, 5) << m_PrimaryIntMatrix.getNIterator(0, 5);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(0, 5) << m_PrimaryIntMatrix.getNIterator(7, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(7, 4) << m_PrimaryIntMatrix.getNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}")  << m_PrimaryIntMatrix.getNIterator(2, 0) << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, begin iterator}")  << m_PrimaryIntMatrix.getNIterator(1, 0) << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, begin iterator}")  << m_PrimaryIntMatrix.nBegin() << m_PrimaryIntMatrix.nBegin();
}

void NIteratorTests::_buildOperatorPlusTestingTable()
{
    m_PrimaryIntMatrix = {8, 9, -5};
    m_SecondaryIntMatrix.clear();

    QTest::addColumn<IntMatrixNIterator>("iterator");
    QTest::addColumn<IntMatrixDiffType>("scalarValue");
    QTest::addColumn<IntMatrixNIterator>("expectedIterator");

    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.nBegin() << -3 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.nBegin() << -1 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, begin iterator}") << m_PrimaryIntMatrix.nBegin() << 0 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << 1 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << 4 << m_PrimaryIntMatrix.getNIterator(4, 0);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << 10 << m_PrimaryIntMatrix.getNIterator(2, 1);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << 70 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{begin iterator, random iterator}") << m_PrimaryIntMatrix.nBegin() << 71 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << 72 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << 73 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_PrimaryIntMatrix.nBegin() << 75 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << -4 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << -2 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << -1 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 0 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 3 << m_PrimaryIntMatrix.getNIterator(4, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 9 << m_PrimaryIntMatrix.getNIterator(2, 1);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 69 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 70 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 71 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 72 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(1, 0) << 74 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -47 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -45 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -44 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -43 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -6 << m_PrimaryIntMatrix.getNIterator(6, 4);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << -2 << m_PrimaryIntMatrix.getNIterator(2, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) <<  0 << m_PrimaryIntMatrix.getNIterator(4, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) <<  2 << m_PrimaryIntMatrix.getNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 6 << m_PrimaryIntMatrix.getNIterator(2, 6);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 26 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 27 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 28 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 29 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(4, 5) << 31 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -73 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -71 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -70 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -69 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -24 << m_PrimaryIntMatrix.getNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << -3 << m_PrimaryIntMatrix.getNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 0 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 1 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 2 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 3 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(6, 8) << 5 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -74 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -72 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, begin iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -71 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -70 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -25 << m_PrimaryIntMatrix.getNIterator(6, 5);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -4 << m_PrimaryIntMatrix.getNIterator(3, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << -1 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{random iterator, random iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << 0 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << 1 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << 2 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{random iterator, end iterator}") << m_PrimaryIntMatrix.getNIterator(7, 8) << 4 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.nEnd() << -75 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.nEnd() << -73 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{end iterator, begin iterator}") << m_PrimaryIntMatrix.nEnd() << -72 << m_PrimaryIntMatrix.nBegin();
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << -71 << m_PrimaryIntMatrix.getNIterator(1, 0);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << -26 << m_PrimaryIntMatrix.getNIterator(6, 5);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << -5 << m_PrimaryIntMatrix.getNIterator(3, 8);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << -2 << m_PrimaryIntMatrix.getNIterator(6, 8);
    QTest::newRow("{end iterator, random iterator}") << m_PrimaryIntMatrix.nEnd() << -1 << m_PrimaryIntMatrix.getNIterator(7, 8);
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.nEnd() << 0 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.nEnd() << 1 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_PrimaryIntMatrix.nEnd() << 3 << m_PrimaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.nBegin() << -1 << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{begin iterator, end iterator}") << m_SecondaryIntMatrix.nBegin() << 1 << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.nEnd() << 0 << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.nEnd() << 1 << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{end iterator, end iterator}") << m_SecondaryIntMatrix.nEnd() << -1 << m_SecondaryIntMatrix.nEnd();
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixNIterator{} << -1 << IntMatrixNIterator{};
    QTest::newRow("{empty iterator, empty iterator}") << IntMatrixNIterator{} << 1 << IntMatrixNIterator{};
}

QTEST_APPLESS_MAIN(NIteratorTests)

#include "tst_niteratortests.moc"
