#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixMIterator = Matrix<int>::MIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixMIterator = Matrix<std::string>::MIterator;

class MIteratorTests : public QObject
{
    Q_OBJECT

public:
    MIteratorTests();
    ~MIteratorTests();

private slots:
    void testIteratorCreation();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testSmallerThanOperator();
    void testSmallerThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testDereferenceAsteriskOperator();
    void testDereferenceArrowOperator();
    void testDereferenceSquareBracketsOperator();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdSort();
};

MIteratorTests::MIteratorTests()
{

}

MIteratorTests::~MIteratorTests()
{

}

void MIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-2)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == 2 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-2)};

        QVERIFY2(it.getRowNr() == 4 && it.getColumnNr() == 0 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(0)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(0)};

        QVERIFY2(it.getRowNr() == 3 && it.getColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(1)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(1)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == -1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(0, 2)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(0, 2)};

        QVERIFY2(it.getRowNr() == 3 && it.getColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(2, 1)};

        QVERIFY2(it.getRowNr() == 1 && it.getColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(2, 1)};

        QVERIFY2(it.getRowNr() == 4 && it.getColumnNr() == -1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(1, 0)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(1, 0)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == -1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 2)};

        QVERIFY2(it.getRowNr() == 1 && it.getColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(0, 0)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(2, 1)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(2, 0)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(-1, 0, true)};

        QVERIFY2(it.getRowNr() == 1 && it.getColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(2, 0, true)};

        QVERIFY2(it.getRowNr() == 0 && it.getColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(-1, 1, true)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(0, 2, true)};

        QVERIFY2(it.getRowNr() == 2 && it.getColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    // test empty iterator creation (not bound to any matrix) - an empty diagonal iterator should be invalid for any matrix (empty or not)
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator emptyIt;

        QVERIFY2(emptyIt.getRowNr() == -1 && emptyIt.getColumnNr() == -1 && emptyIt.getDiagonalNr() == 0 && emptyIt.getDiagonalIndex() == -1 && !emptyIt.isValidWithMatrix(matrix),  "The iterator has not been correctly created");

        matrix.clear();

        QVERIFY(!emptyIt.isValidWithMatrix(matrix));
    }

    // additional test for checking that an iterator is only valid with the matrix with which it is created
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrix matrixCopy{matrix};
        IntMatrixMIterator it{matrix.getMIterator(2, 1)};

        QVERIFY(!it.isValidWithMatrix(matrixCopy));
    }
}

void MIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 0)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(1, 0)};
        IntMatrixMIterator secondIt{matrix.getMIterator(1, 1, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mBegin(-1)};
        IntMatrixMIterator secondIt{matrix.mBegin(2, 1)};
        IntMatrixMIterator thirdIt{matrix.getMIterator(1, 2)};
        IntMatrixMIterator fourthIt{matrix.getMIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mEnd(2)};
        IntMatrixMIterator secondIt{matrix.mEnd(0, 0)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void MIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 0)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(1, 0)};
        IntMatrixMIterator secondIt{matrix.getMIterator(1, 0, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void MIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixMIterator firstIt{matrix.mBegin(1)};
    IntMatrixMIterator secondIt{matrix.getMIterator(1, 0)};
    IntMatrixMIterator thirdIt{matrix.mEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void MIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 0)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mBegin(-1)};
        IntMatrixMIterator secondIt{matrix.getMIterator(1, 2)};
        IntMatrixMIterator thirdIt{matrix.getMIterator(2, 1)};
        IntMatrixMIterator fourthIt{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator fifthIt{matrix.mEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void MIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixMIterator firstIt{matrix.mBegin(1)};
    IntMatrixMIterator secondIt{matrix.getMIterator(1, 0)};
    IntMatrixMIterator thirdIt{matrix.mEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void MIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 0)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mBegin(-1)};
        IntMatrixMIterator secondIt{matrix.getMIterator(1, 2)};
        IntMatrixMIterator thirdIt{matrix.getMIterator(2, 1)};
        IntMatrixMIterator fourthIt{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator fifthIt{matrix.mEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void MIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getMIterator(2, 1) && preIncrementIt == matrix.getMIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getMIterator(2, 1) && prePreIncrementIt == matrix.getMIterator(3, 0),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postIncrementIt == matrix.getMIterator(1, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postPostIncrementIt == matrix.getMIterator(1, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getMIterator(2, 1) && prePostIncrementIt == matrix.getMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postPreIncrementIt == matrix.getMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.mEnd(2, 1) && preIncrementIt == matrix.mEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.mEnd(2, 1) && postIncrementIt == matrix.mEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void MIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getMIterator(3, 0) && preDecrementIt == matrix.getMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getMIterator(2, 1) && preDecrementIt == matrix.getMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getMIterator(3, 0) && prePreDecrementIt == matrix.getMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getMIterator(2, 1) && prePreDecrementIt == matrix.getMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getMIterator(3, 0) && postDecrementIt == matrix.mEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postDecrementIt == matrix.getMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getMIterator(3, 0) && postPostDecrementIt == matrix.mEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postPostDecrementIt == matrix.getMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getMIterator(3, 0) && prePostDecrementIt == matrix.getMIterator(3, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getMIterator(2, 1) && prePostDecrementIt == matrix.getMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(-1)};
        IntMatrixMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getMIterator(3, 0) && postPreDecrementIt == matrix.getMIterator(3, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(3, 0)};
        IntMatrixMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getMIterator(2, 1) && postPreDecrementIt == matrix.getMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getMIterator(1, 2) && preDecrementIt == matrix.getMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(-1)};
        IntMatrixMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getMIterator(1, 2) && postDecrementIt == matrix.getMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void MIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mBegin(-1)};
        IntMatrixMIterator it2{it1 + (-1)};
        IntMatrixMIterator it3{it1 + 2};
        IntMatrixMIterator it4{it1 + 3};
        IntMatrixMIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.getMIterator(3, 0) && it4 == matrix.mEnd(1, 2) && it5 == matrix.mEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator it2{it1 + (-2)};
        IntMatrixMIterator it3{it1 + (-1)};
        IntMatrixMIterator it4{it1 + (0)};
        IntMatrixMIterator it5{it1 + 1};
        IntMatrixMIterator it6{it1 + 2};
        IntMatrixMIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(2, 1) && it5 == matrix.getMIterator(3, 0) &&
                 it6 == matrix.mEnd(1, 2) && it7 == matrix.mEnd(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mEnd(-1)};
        IntMatrixMIterator it2{it1 + (-4)};
        IntMatrixMIterator it3{it1 + (-3)};
        IntMatrixMIterator it4{it1 + (-1)};
        IntMatrixMIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(3, 0) && it5 == matrix.mEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixMIterator it1{matrix.mBegin(0, 2)};
        IntMatrixMIterator it2{it1 + (-2)};
        IntMatrixMIterator it3{it1 + (-1)};
        IntMatrixMIterator it4{it1 + 2};
        IntMatrixMIterator it5{it1 + 3};
        IntMatrixMIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.mBegin(0, 2) && it3 == matrix.mBegin(0, 2) && it4 == matrix.getMIterator(2, 0) && it5 == matrix.mEnd(0, 2) && it6 == matrix.mEnd(0, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void MIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mBegin(-1)};
        IntMatrixMIterator it2{it1 - 1};
        IntMatrixMIterator it3{it1 - (-2)};
        IntMatrixMIterator it4{it1 - (-3)};
        IntMatrixMIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.getMIterator(3, 0) && it4 == matrix.mEnd(1, 2) && it5 == matrix.mEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator it2{it1 - 2};
        IntMatrixMIterator it3{it1 - 1};
        IntMatrixMIterator it4{it1 - 0};
        IntMatrixMIterator it5{it1 - (-1)};
        IntMatrixMIterator it6{it1 - (-2)};
        IntMatrixMIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(2, 1) && it5 == matrix.getMIterator(3, 0) &&
                 it6 == matrix.mEnd(1, 2) && it7 == matrix.mEnd(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mEnd(-1)};
        IntMatrixMIterator it2{it1 - 4};
        IntMatrixMIterator it3{it1 - 3};
        IntMatrixMIterator it4{it1 - 1};
        IntMatrixMIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(3, 0) && it5 == matrix.mEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixMIterator it1{matrix.mBegin(0, 2)};
        IntMatrixMIterator it2{it1 - 2};
        IntMatrixMIterator it3{it1 - 1};
        IntMatrixMIterator it4{it1 - (-2)};
        IntMatrixMIterator it5{it1 - (-3)};
        IntMatrixMIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.mBegin(0, 2) && it3 == matrix.mBegin(0, 2) && it4 == matrix.getMIterator(2, 0) && it5 == matrix.mEnd(0, 2) && it6 == matrix.mEnd(0, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void MIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mBegin(-1)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.getMIterator(3, 0) && it4 == matrix.mEnd(1, 2) && it5 == matrix.mEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};
        IntMatrixMIterator it6{it1};
        IntMatrixMIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(2, 1) && it5 == matrix.getMIterator(3, 0) &&
                 it6 == matrix.mEnd(1, 2) && it7 == matrix.mEnd(1, 2), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mEnd(-1)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(3, 0) && it5 == matrix.mEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixMIterator it1{matrix.mBegin(0, 2)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};
        IntMatrixMIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.mBegin(0, 2) && it3 == matrix.mBegin(0, 2) && it4 == matrix.getMIterator(2, 0) && it5 == matrix.mEnd(0, 2) && it6 == matrix.mEnd(0, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void MIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mBegin(-1)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};

        it2 -= 1;
        it3 -= -2;
        it4 -= -3;
        it5 -= -4;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.getMIterator(3, 0) && it4 == matrix.mEnd(1, 2) && it5 == matrix.mEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.getMIterator(-1, 1, true)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};
        IntMatrixMIterator it6{it1};
        IntMatrixMIterator it7{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= 0;
        it5 -= -1;
        it6 -= -2;
        it7 -= -3;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(2, 1) && it5 == matrix.getMIterator(3, 0) &&
                 it6 == matrix.mEnd(1, 2) && it7 == matrix.mEnd(1, 2), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixMIterator it1{matrix.mEnd(-1)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};

        it2 -= 4;
        it3 -= 3;
        it4 -= 1;
        it5 -= -1;

        QVERIFY2(it2 == matrix.mBegin(1, 2) && it3 == matrix.mBegin(1, 2) && it4 == matrix.getMIterator(3, 0) && it5 == matrix.mEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixMIterator it1{matrix.mBegin(0, 2)};
        IntMatrixMIterator it2{it1};
        IntMatrixMIterator it3{it1};
        IntMatrixMIterator it4{it1};
        IntMatrixMIterator it5{it1};
        IntMatrixMIterator it6{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= -2;
        it5 -= -3;
        it6 -= -4;

        QVERIFY2(it2 == matrix.mBegin(0, 2) && it3 == matrix.mBegin(0, 2) && it4 == matrix.getMIterator(2, 0) && it5 == matrix.mEnd(0, 2) && it6 == matrix.mEnd(0, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void MIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mBegin(-1)};
        IntMatrixMIterator secondIt{matrix.mBegin(1, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.mEnd(1)};
        IntMatrixMIterator secondIt{matrix.mEnd(0, 1)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(2, 1)};
        IntMatrixMIterator secondIt{matrix.getMIterator(-1, 2, true)};

        QVERIFY2(secondIt - firstIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(1, 0)};
        IntMatrixMIterator secondIt{matrix.getMIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(-1, 0, true)};
        IntMatrixMIterator secondIt{matrix.mEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator firstIt{matrix.getMIterator(2, 0)};
        IntMatrixMIterator secondIt{matrix.mBegin(0, 2)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void MIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(2, 1)};

        QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(1, 1, true)};

        *it = 14;

        QVERIFY2(matrix.at(1, 0) == 14, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void MIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"ghi", "defed", "abc", "pqr", "mno", "jkl"}};
        StringMatrixMIterator readIter{matrix.mBegin(0, 1)};

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"ghi", "defed", "abc", "pqr", "mno", "jkl"}};
        StringMatrixMIterator writeIter{matrix.getMIterator(1, 0)};

        writeIter->assign("abcdefghij");

        QVERIFY2(*matrix.getMIterator(1, 1, true) == "abcdefghij",
                 "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void MIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(2, 1)};

        QVERIFY2(it[-1] == 4 && it[0] == -8 && it[1] == 12, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mBegin(0, 1)};

        QVERIFY2(it[0] == 2 && it[1] == 6, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.mEnd(0)};

        QVERIFY2( it[-3] == 1 && it[-2] == -5 && it[-1] == 9, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixMIterator it{matrix.getMIterator(0, 1)};

        it[1] = 14;

        QVERIFY2(*matrix.getMIterator(1, 1, true) == 14, "The dereference square brackets operator doesn't work correctly");
    }
}

void MIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10});
    IntMatrixMIterator it{matrix.mBegin(1)};

    QVERIFY2(*it == 2, "The iterator does not reference the right value");

    it = matrix.getMIterator(-2, 0, true);
    QVERIFY2(it[1] == -11, "the iterator index does not reference the right value");
}

void MIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {-3, 2});

        QVERIFY2(std::count(matrix.getMIterator(0, 0), matrix.getMIterator(1, 0, true), -3) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.mBegin(1), matrix.mEnd(1), -3) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }

    {
        IntMatrix matrix(6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                         });

        QVERIFY2(std::count(matrix.mBegin(1), matrix.mEnd(1), -1) == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getMIterator(1, 1, true), matrix.getMIterator(4, 1), 4) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getMIterator(2, 3), matrix.getMIterator(1, 4, true), 4) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void MIteratorTests::testStdFind()
{
    {
        IntMatrix matrix(6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                         });

        IntMatrixMIterator it{std::find(matrix.mBegin(1), matrix.mEnd(1), 5)};
        QVERIFY2(it == matrix.getMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix(6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  4,  4, -3,  2, 1,
                              7, 5, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                         });

        IntMatrixMIterator it{std::find(matrix.mBegin(1), matrix.mEnd(1), 4)};
        QVERIFY2(it == matrix.getMIterator(1, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.mEnd(1), 4);
        QVERIFY2(it == matrix.getMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.mEnd(1), 4);
        QVERIFY2(it == matrix.mEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix(6, 7, {
                              7, 6, -5,  4, -3, -1, 1,
                              7, 6, -5,  4,  4,  2, 1,
                              7, 6, -5, -1, -3,  2, 1,
                              7, 6,  5,  4, -3,  2, 1,
                              7, 4, -5,  4, -3,  2, 1,
                             -1, 6, -5,  4, -3,  2, 1,
                         });

        IntMatrixMIterator it{std::find(matrix.mBegin(1), matrix.mEnd(1), -9)};
        QVERIFY2(it == matrix.mEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

void MIteratorTests::testStdSort()
{
    {
        IntMatrix matrix(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4, -3,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  0,  4, -3,  2, 1,
                             7,  5, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5,  4, -3, -3, 1,
                             7,  6, -5,  4, -1,  2, 1,
                             7,  6, -5,  0, -3,  2, 1,
                             7,  6,  1,  4, -3,  2, 1,
                             7,  2, -5,  4, -3,  2, 1,
                             5,  6, -5,  4, -3,  2, 1,
                         });

        std::sort(matrix.mBegin(1), matrix.mEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4,  5,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  0,  4, -3,  2, 1,
                             7, -3, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4,  0,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  5,  4, -3,  2, 1,
                             7, -3, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        std::sort(matrix.getMIterator(1, 4), matrix.getMIterator(4, 1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4,  5,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  0,  4, -3,  2, 1,
                             7, -3, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4,  0,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  5,  4, -3,  2, 1,
                             7, -3, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        std::sort(matrix.mBegin(1), matrix.getMIterator(4, 1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7,  6, -5,  4, -3, -1, 1,
                             7,  6, -5,  4,  5,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  0,  4, -3,  2, 1,
                             7, -3, -5,  4, -3,  2, 1,
                             2,  6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7, 6, -5,  4, -3, -1, 1,
                             7, 6, -5,  4, -3,  2, 1,
                             7, 6, -5,  0, -3,  2, 1,
                             7, 6,  1,  4, -3,  2, 1,
                             7, 2, -5,  4, -3,  2, 1,
                             5, 6, -5,  4, -3,  2, 1,
                         });

        std::sort(matrix.getMIterator(1, 4), matrix.mEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }
}

QTEST_APPLESS_MAIN(MIteratorTests)

#include "tst_miteratortests.moc"
