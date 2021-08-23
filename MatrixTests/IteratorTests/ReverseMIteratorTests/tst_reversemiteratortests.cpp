#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseMIterator = Matrix<int>::ReverseMIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseMIterator = Matrix<std::string>::ReverseMIterator;

class ReverseMIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseMIteratorTests();
    ~ReverseMIteratorTests();

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

ReverseMIteratorTests::ReverseMIteratorTests()
{

}

ReverseMIteratorTests::~ReverseMIteratorTests()
{

}

void ReverseMIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    // additional test for checking that an iterator is only valid with the matrix with which it is created
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrix matrixCopy{matrix};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 1)};

        QVERIFY(!it.isValidWithMatrix(matrixCopy));
    }
}

void ReverseMIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 0)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(1, 0)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(1, 0, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMBegin(2, 1)};
        IntMatrixReverseMIterator thirdIt{matrix.getReverseMIterator(3, 0)};
        IntMatrixReverseMIterator fourthIt{matrix.getReverseMIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMEnd(2)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMEnd(0, 0)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ReverseMIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 0)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(1, 0)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(1, 1, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ReverseMIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(1)};
    IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(0, 1)};
    IntMatrixReverseMIterator thirdIt{matrix.reverseMEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ReverseMIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 0)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(3, 0)};
        IntMatrixReverseMIterator thirdIt{matrix.getReverseMIterator(2, 1)};
        IntMatrixReverseMIterator fourthIt{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator fifthIt{matrix.reverseMEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ReverseMIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(1)};
    IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(0, 1)};
    IntMatrixReverseMIterator thirdIt{matrix.reverseMEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ReverseMIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 0)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(3, 0)};
        IntMatrixReverseMIterator thirdIt{matrix.getReverseMIterator(2, 1)};
        IntMatrixReverseMIterator fourthIt{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator fifthIt{matrix.reverseMEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ReverseMIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && preIncrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && prePreIncrementIt == matrix.getReverseMIterator(1, 2),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postIncrementIt == matrix.getReverseMIterator(3, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postPostIncrementIt == matrix.getReverseMIterator(3, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && prePostIncrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postPreIncrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.reverseMEnd(2, 1) && preIncrementIt == matrix.reverseMEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.reverseMEnd(2, 1) && postIncrementIt == matrix.reverseMEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseMIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && preDecrementIt == matrix.getReverseMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && preDecrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && prePreDecrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && prePreDecrementIt == matrix.getReverseMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && postDecrementIt == matrix.reverseMEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postDecrementIt == matrix.getReverseMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && postPostDecrementIt == matrix.reverseMEnd(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postPostDecrementIt == matrix.getReverseMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && prePostDecrementIt == matrix.getReverseMIterator(1, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && prePostDecrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getReverseMIterator(1, 2) && postPreDecrementIt == matrix.getReverseMIterator(1, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 2)};
        IntMatrixReverseMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getReverseMIterator(2, 1) && postPreDecrementIt == matrix.getReverseMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseMIterator(3, 0) && preDecrementIt == matrix.getReverseMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseMIterator(3, 0) && postDecrementIt == matrix.getReverseMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseMIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator it2{it1 + (-1)};
        IntMatrixReverseMIterator it3{it1 + 2};
        IntMatrixReverseMIterator it4{it1 + 3};
        IntMatrixReverseMIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.getReverseMIterator(1, 2) && it4 == matrix.reverseMEnd(3, 0) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator it2{it1 + (-2)};
        IntMatrixReverseMIterator it3{it1 + (-1)};
        IntMatrixReverseMIterator it4{it1 + (0)};
        IntMatrixReverseMIterator it5{it1 + 1};
        IntMatrixReverseMIterator it6{it1 + 2};
        IntMatrixReverseMIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(2, 1) && it5 == matrix.getReverseMIterator(1, 2) &&
                 it6 == matrix.reverseMEnd(3, 0) && it7 == matrix.reverseMEnd(3, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator it2{it1 + (-4)};
        IntMatrixReverseMIterator it3{it1 + (-3)};
        IntMatrixReverseMIterator it4{it1 + (-1)};
        IntMatrixReverseMIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(1, 2) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixReverseMIterator it1{matrix.reverseMBegin(2, 0)};
        IntMatrixReverseMIterator it2{it1 + (-2)};
        IntMatrixReverseMIterator it3{it1 + (-1)};
        IntMatrixReverseMIterator it4{it1 + 2};
        IntMatrixReverseMIterator it5{it1 + 3};
        IntMatrixReverseMIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.reverseMBegin(2, 0) && it3 == matrix.reverseMBegin(2, 0) && it4 == matrix.getReverseMIterator(0, 2) && it5 == matrix.reverseMEnd(2, 0) && it6 == matrix.reverseMEnd(2, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseMIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator it2{it1 - 1};
        IntMatrixReverseMIterator it3{it1 - (-2)};
        IntMatrixReverseMIterator it4{it1 - (-3)};
        IntMatrixReverseMIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.getReverseMIterator(1, 2) && it4 == matrix.reverseMEnd(3, 0) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator it2{it1 - 2};
        IntMatrixReverseMIterator it3{it1 - 1};
        IntMatrixReverseMIterator it4{it1 - 0};
        IntMatrixReverseMIterator it5{it1 - (-1)};
        IntMatrixReverseMIterator it6{it1 - (-2)};
        IntMatrixReverseMIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(2, 1) && it5 == matrix.getReverseMIterator(1, 2) &&
                 it6 == matrix.reverseMEnd(3, 0) && it7 == matrix.reverseMEnd(3, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator it2{it1 - 4};
        IntMatrixReverseMIterator it3{it1 - 3};
        IntMatrixReverseMIterator it4{it1 - 1};
        IntMatrixReverseMIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(1, 2) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixReverseMIterator it1{matrix.reverseMBegin(2, 0)};
        IntMatrixReverseMIterator it2{it1 - 2};
        IntMatrixReverseMIterator it3{it1 - 1};
        IntMatrixReverseMIterator it4{it1 - (-2)};
        IntMatrixReverseMIterator it5{it1 - (-3)};
        IntMatrixReverseMIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.reverseMBegin(2, 0) && it3 == matrix.reverseMBegin(2, 0) && it4 == matrix.getReverseMIterator(0, 2) && it5 == matrix.reverseMEnd(2, 0) && it6 == matrix.reverseMEnd(2, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseMIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.getReverseMIterator(1, 2) && it4 == matrix.reverseMEnd(3, 0) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};
        IntMatrixReverseMIterator it6{it1};
        IntMatrixReverseMIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(2, 1) && it5 == matrix.getReverseMIterator(1, 2) &&
                 it6 == matrix.reverseMEnd(3, 0) && it7 == matrix.reverseMEnd(3, 0), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(1, 2) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixReverseMIterator it1{matrix.reverseMBegin(2, 0)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};
        IntMatrixReverseMIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.reverseMBegin(2, 0) && it3 == matrix.reverseMBegin(2, 0) && it4 == matrix.getReverseMIterator(0, 2) && it5 == matrix.reverseMEnd(2, 0) && it6 == matrix.reverseMEnd(2, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseMIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};

        it2 -= 1;
        it3 -= -2;
        it4 -= -3;
        it5 -= -4;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.getReverseMIterator(1, 2) && it4 == matrix.reverseMEnd(3, 0) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.getReverseMIterator(-1, 1, true)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};
        IntMatrixReverseMIterator it6{it1};
        IntMatrixReverseMIterator it7{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= 0;
        it5 -= -1;
        it6 -= -2;
        it7 -= -3;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(2, 1) && it5 == matrix.getReverseMIterator(1, 2) &&
                 it6 == matrix.reverseMEnd(3, 0) && it7 == matrix.reverseMEnd(3, 0), "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixReverseMIterator it1{matrix.reverseMEnd(-1)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};

        it2 -= 4;
        it3 -= 3;
        it4 -= 1;
        it5 -= -1;

        QVERIFY2(it2 == matrix.reverseMBegin(3, 0) && it3 == matrix.reverseMBegin(3, 0) && it4 == matrix.getReverseMIterator(1, 2) && it5 == matrix.reverseMEnd(3, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixReverseMIterator it1{matrix.reverseMBegin(2, 0)};
        IntMatrixReverseMIterator it2{it1};
        IntMatrixReverseMIterator it3{it1};
        IntMatrixReverseMIterator it4{it1};
        IntMatrixReverseMIterator it5{it1};
        IntMatrixReverseMIterator it6{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= -2;
        it5 -= -3;
        it6 -= -4;

        QVERIFY2(it2 == matrix.reverseMBegin(2, 0) && it3 == matrix.reverseMBegin(2, 0) && it4 == matrix.getReverseMIterator(0, 2) && it5 == matrix.reverseMEnd(2, 0) && it6 == matrix.reverseMEnd(2, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseMIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMBegin(-1)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMBegin(3, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.reverseMEnd(1)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMEnd(1, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(2, 1)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(-1, 0, true)};

        QVERIFY2(firstIt - secondIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(0, 1)};
        IntMatrixReverseMIterator secondIt{matrix.getReverseMIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(-1, 0, true)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator firstIt{matrix.getReverseMIterator(0, 2)};
        IntMatrixReverseMIterator secondIt{matrix.reverseMBegin(2, 0)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ReverseMIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 1)};

        QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(1, 1, true)};

        *it = 14;

        QVERIFY2(matrix.at(0, 1) == 14, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void ReverseMIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"ghi", "pqr", "abc", "defed", "mno", "jkl"}};
        StringMatrixReverseMIterator readIter{matrix.reverseMBegin(0, 1)};

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"ghi", "pqr", "abc", "defed", "mno", "jkl"}};
        StringMatrixReverseMIterator writeIter{matrix.getReverseMIterator(1, 0)};

        writeIter->assign("abcdefghij");

        QVERIFY2(*matrix.getReverseMIterator(1, 0, true) == "abcdefghij",
                 "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void ReverseMIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(2, 1)};

        QVERIFY2(it[-1] == 12 && it[0] == -8 && it[1] == 4, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMBegin(0, 1)};

        QVERIFY2(it[0] == 6 && it[1] == 2, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.reverseMEnd(0)};

        QVERIFY2( it[-3] == 9 && it[-2] == -5 && it[-1] == 1, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixReverseMIterator it{matrix.getReverseMIterator(0, 1)};

        it[-1] = 14;

        QVERIFY2(*matrix.getReverseMIterator(1, 0, true) == 14, "The dereference square brackets operator doesn't work correctly");
    }
}

void ReverseMIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10});
    IntMatrixReverseMIterator it{matrix.reverseMBegin(1)};

    QVERIFY2(*it == 6, "The iterator does not reference the right value");

    it = matrix.getReverseMIterator(-2, 0, true);
    QVERIFY2(it[1] == 7, "the iterator index does not reference the right value");
}

void ReverseMIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {-3, 2});

        QVERIFY2(std::count(matrix.getReverseMIterator(0, 0), matrix.getReverseMIterator(1, 0, true), -3) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.reverseMBegin(1), matrix.reverseMEnd(1), -3) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
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

        QVERIFY2(std::count(matrix.reverseMBegin(1), matrix.reverseMEnd(1), -1) == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getReverseMIterator(4, 1), matrix.getReverseMIterator(1, 4, true), 4) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getReverseMIterator(3, 2), matrix.getReverseMIterator(1, 4, true), 4) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void ReverseMIteratorTests::testStdFind()
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

        IntMatrixReverseMIterator it{std::find(matrix.reverseMBegin(1), matrix.reverseMEnd(1), 5)};
        QVERIFY2(it == matrix.getReverseMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixReverseMIterator it{std::find(matrix.reverseMBegin(1), matrix.reverseMEnd(1), 4)};
        QVERIFY2(it == matrix.getReverseMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.reverseMEnd(1), 4);
        QVERIFY2(it == matrix.getReverseMIterator(1, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.reverseMEnd(1), 4);
        QVERIFY2(it == matrix.reverseMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixReverseMIterator it{std::find(matrix.reverseMBegin(1), matrix.reverseMEnd(1), -9)};
        QVERIFY2(it == matrix.reverseMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

void ReverseMIteratorTests::testStdSort()
{
    {
        IntMatrix matrix(6, 7, {
                             7, 6, -5,  4, -3, -1, 1,
                             7, 6, -5,  4, -3,  2, 1,
                             7, 6, -5,  1, -3,  2, 1,
                             7, 6,  0,  4, -3,  2, 1,
                             7, 5, -5,  4, -3,  2, 1,
                             2, 6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5,  4, -3,  5, 1,
                             7,  6, -5,  4,  2,  2, 1,
                             7,  6, -5,  1, -3,  2, 1,
                             7,  6,  0,  4, -3,  2, 1,
                             7, -1, -5,  4, -3,  2, 1,
                            -3,  6, -5,  4, -3,  2, 1,
                         });

        std::sort(matrix.reverseMBegin(1), matrix.reverseMEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7, 6, -5,  4, -3, -1, 1,
                             7, 6, -5,  4,  5,  2, 1,
                             7, 6, -5, -3, -3,  2, 1,
                             7, 6,  1,  4, -3,  2, 1,
                             7, 0, -5,  4, -3,  2, 1,
                             2, 6, -5,  4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5, 4, -3, -1, 1,
                             7,  6, -5, 4,  5,  2, 1,
                             7,  6, -5, 1, -3,  2, 1,
                             7,  6,  0, 4, -3,  2, 1,
                             7, -3, -5, 4, -3,  2, 1,
                             2,  6, -5, 4, -3,  2, 1,
                         });

        std::sort(matrix.getReverseMIterator(4, 1), matrix.getReverseMIterator(1, 4));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7,  6, -5, 4, -3, -1, 1,
                             7,  6, -5, 4,  5,  2, 1,
                             7,  6, -5, 1, -3,  2, 1,
                             7,  6,  0, 4, -3,  2, 1,
                             7, -3, -5, 4, -3,  2, 1,
                             2,  6, -5, 4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7, 6, -5, 4, -3, -1, 1,
                             7, 6, -5, 4,  5,  2, 1,
                             7, 6, -5, 2, -3,  2, 1,
                             7, 6,  1, 4, -3,  2, 1,
                             7, 0, -5, 4, -3,  2, 1,
                            -3, 6, -5, 4, -3,  2, 1,
                         });

        std::sort(matrix.reverseMBegin(1), matrix.getReverseMIterator(1, 4));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             7, 6, -5, 4, -3, -1, 1,
                             7, 6, -5, 4,  1,  2, 1,
                             7, 6, -5, 5, -3,  2, 1,
                             7, 6, -3, 4, -3,  2, 1,
                             7, 0, -5, 4, -3,  2, 1,
                             2, 6, -5, 4, -3,  2, 1,
                         });

        IntMatrix matrixRef(6, 7, {
                             7,  6, -5, 4, -3, 5, 1,
                             7,  6, -5, 4,  1, 2, 1,
                             7,  6, -5, 0, -3, 2, 1,
                             7,  6, -1, 4, -3, 2, 1,
                             7, -3, -5, 4, -3, 2, 1,
                             2,  6, -5, 4, -3, 2, 1,
                         });

        std::sort(matrix.getReverseMIterator(4, 1), matrix.reverseMEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }
}

QTEST_APPLESS_MAIN(ReverseMIteratorTests)

#include "tst_reversemiteratortests.moc"
