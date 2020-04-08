#define ERROR_CHECKING

#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseDIterator = Matrix<int>::ReverseDIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseDIterator = Matrix<std::string>::ReverseDIterator;

class ReverseDIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseDIteratorTests();
    ~ReverseDIteratorTests();

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
    void testDifferenceOperator();
    void testDereferenceAsteriskOperator();
    void testDereferenceArrowOperator();
    void testDereferenceSquareBracketsOperator();
    void testIsValidWithMatrix();
    void testChangeDiagonal();
    void testStdCount();
    void testStdFind();
    void testStdSort();
};

ReverseDIteratorTests::ReverseDIteratorTests()
{

}

ReverseDIteratorTests::~ReverseDIteratorTests()
{

}

void ReverseDIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }
}

void ReverseDIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 2)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(1, 2)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 0, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDBegin(2, 1)};
        IntMatrixReverseDIterator thirdIt{matrix.getReverseDIterator(3, 2)};
        IntMatrixReverseDIterator fourthIt{matrix.getReverseDIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(2)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(0, 2)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ReverseDIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 2)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(1, 2)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ReverseDIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(1)};
    IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(0, 1)};
    IntMatrixReverseDIterator thirdIt{matrix.reverseDEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ReverseDIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 2)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(3, 2)};
        IntMatrixReverseDIterator thirdIt{matrix.getReverseDIterator(2, 1)};
        IntMatrixReverseDIterator fourthIt{matrix.getReverseDIterator(-1, 1, true)};
        IntMatrixReverseDIterator fifthIt{matrix.reverseDEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ReverseDIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(1)};
    IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(0, 1)};
    IntMatrixReverseDIterator thirdIt{matrix.reverseDEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 2)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(3, 2)};
        IntMatrixReverseDIterator thirdIt{matrix.getReverseDIterator(2, 1)};
        IntMatrixReverseDIterator fourthIt{matrix.getReverseDIterator(-1, 1, true)};
        IntMatrixReverseDIterator fifthIt{matrix.reverseDEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ReverseDIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && preIncrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && prePreIncrementIt == matrix.getReverseDIterator(1, 0),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postIncrementIt == matrix.getReverseDIterator(3, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postPostIncrementIt == matrix.getReverseDIterator(3, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && prePostIncrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postPreIncrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.reverseDEnd(2, 1) && preIncrementIt == matrix.reverseDEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.reverseDEnd(2, 1) && postIncrementIt == matrix.reverseDEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseDIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && preDecrementIt == matrix.getReverseDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && preDecrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && prePreDecrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && prePreDecrementIt == matrix.getReverseDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && postDecrementIt == matrix.reverseDEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postDecrementIt == matrix.getReverseDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && postPostDecrementIt == matrix.reverseDEnd(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postPostDecrementIt == matrix.getReverseDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && prePostDecrementIt == matrix.getReverseDIterator(1, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && prePostDecrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getReverseDIterator(1, 0) && postPreDecrementIt == matrix.getReverseDIterator(1, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0)};
        IntMatrixReverseDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getReverseDIterator(2, 1) && postPreDecrementIt == matrix.getReverseDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getReverseDIterator(3, 2) && preDecrementIt == matrix.getReverseDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getReverseDIterator(3, 2) && postDecrementIt == matrix.getReverseDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseDIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator it2{it1 + (-1)};
        IntMatrixReverseDIterator it3{it1 + 2};
        IntMatrixReverseDIterator it4{it1 + 3};
        IntMatrixReverseDIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.getReverseDIterator(1, 0) && it4 == matrix.reverseDEnd(3, 2) && it5 == matrix.reverseDEnd(3, 2),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.getReverseDIterator(-1, 1, true)};
        IntMatrixReverseDIterator it2{it1 + (-2)};
        IntMatrixReverseDIterator it3{it1 + (-1)};
        IntMatrixReverseDIterator it4{it1 + (0)};
        IntMatrixReverseDIterator it5{it1 + 1};
        IntMatrixReverseDIterator it6{it1 + 2};
        IntMatrixReverseDIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.reverseDBegin(3, 2) && it4 == matrix.getReverseDIterator(2, 1) && it5 == matrix.getReverseDIterator(1, 0) &&
                 it6 == matrix.reverseDEnd(3, 2) && it7 == matrix.reverseDEnd(3, 2), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator it2{it1 + (-4)};
        IntMatrixReverseDIterator it3{it1 + (-3)};
        IntMatrixReverseDIterator it4{it1 + (-1)};
        IntMatrixReverseDIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.reverseDBegin(3, 2) && it4 == matrix.getReverseDIterator(1, 0) && it5 == matrix.reverseDEnd(3, 2),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it1{matrix.reverseDBegin(2, 3)};
        IntMatrixReverseDIterator it2{it1 + (-2)};
        IntMatrixReverseDIterator it3{it1 + (-1)};
        IntMatrixReverseDIterator it4{it1 + 2};
        IntMatrixReverseDIterator it5{it1 + 3};
        IntMatrixReverseDIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.reverseDBegin(2, 3) && it3 == matrix.reverseDBegin(2, 3) && it4 == matrix.getReverseDIterator(0, 1) && it5 == matrix.reverseDEnd(2, 3) && it6 == matrix.reverseDEnd(2, 3),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void ReverseDIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator it2{it1 -1};
        IntMatrixReverseDIterator it3{it1 - (-2)};
        IntMatrixReverseDIterator it4{it1 - (-3)};
        IntMatrixReverseDIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.getReverseDIterator(1, 0) && it4 == matrix.reverseDEnd(3, 2) && it5 == matrix.reverseDEnd(3, 2),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.getReverseDIterator(-1, 1, true)};
        IntMatrixReverseDIterator it2{it1 - 2};
        IntMatrixReverseDIterator it3{it1 - 1};
        IntMatrixReverseDIterator it4{it1 - 0};
        IntMatrixReverseDIterator it5{it1 - (-1)};
        IntMatrixReverseDIterator it6{it1 - (-2)};
        IntMatrixReverseDIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.reverseDBegin(3, 2) && it4 == matrix.getReverseDIterator(2, 1) && it5 == matrix.getReverseDIterator(1, 0) &&
                 it6 == matrix.reverseDEnd(3, 2) && it7 == matrix.reverseDEnd(3, 2), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixReverseDIterator it1{matrix.reverseDEnd(-1)};
        IntMatrixReverseDIterator it2{it1 - 4};
        IntMatrixReverseDIterator it3{it1 - 3};
        IntMatrixReverseDIterator it4{it1 - 1};
        IntMatrixReverseDIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.reverseDBegin(3, 2) && it3 == matrix.reverseDBegin(3, 2) && it4 == matrix.getReverseDIterator(1, 0) && it5 == matrix.reverseDEnd(3, 2),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it1{matrix.reverseDBegin(2, 3)};
        IntMatrixReverseDIterator it2{it1 -2};
        IntMatrixReverseDIterator it3{it1 -1};
        IntMatrixReverseDIterator it4{it1 - (-2)};
        IntMatrixReverseDIterator it5{it1 - (-3)};
        IntMatrixReverseDIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.reverseDBegin(2, 3) && it3 == matrix.reverseDBegin(2, 3) && it4 == matrix.getReverseDIterator(0, 1) && it5 == matrix.reverseDEnd(2, 3) && it6 == matrix.reverseDEnd(2, 3),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void ReverseDIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDBegin(-1)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDBegin(3, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(1, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(-1, 0, true)};

        QVERIFY2(firstIt - secondIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(0, 1)};
        IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(-1, 0, true)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(0, 0)};
        IntMatrixReverseDIterator secondIt{matrix.reverseDBegin(2, 2)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ReverseDIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 1)};

        QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 1, true)};

        *it = 14;

        QVERIFY2(matrix.at(0, 1) == 14, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void ReverseDIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
        StringMatrixReverseDIterator readIter{matrix.reverseDBegin(0, 1)};

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixReverseDIterator writeIter{matrix.getReverseDIterator(1, 2)};

        writeIter->assign("abcdefghij");

        QVERIFY2(*matrix.getReverseDIterator(1, 0, true) == "abcdefghij",
                 "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void ReverseDIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 1)};

        QVERIFY2(it[-1] == 12 && it[0] == -8 && it[1] == 4, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDBegin(0, 1)};

        QVERIFY2(it[0] == 6 && it[1] == 2, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.reverseDEnd(0)};

        QVERIFY2( it[-3] == 9 && it[-2] == -5 && it[-1] == 1, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 1)};

        it[-1] = 14;

        QVERIFY2(*matrix.getReverseDIterator(1, 0, true) == 14, "The dereference square brackets operator doesn't work correctly");
    }
}

void ReverseDIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 1)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 1, true)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 0, true)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(1, 0, true)};

        secondMatrix = std::move(firstMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
        QVERIFY2(it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (true)");

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(-1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertRow(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixReverseDIterator it{firstMatrix.getReverseDIterator(1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertColumn(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }
}

void ReverseDIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
    IntMatrixReverseDIterator it{matrix.reverseDBegin(1)};

    QVERIFY2(*it == 6, "The iterator does not reference the right value");

    it = matrix.getReverseDIterator(-2, 0, true);
    QVERIFY2(it[1] == 7, "the iterator index does not reference the right value");
}

void ReverseDIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {2, -3});

        QVERIFY2(std::count(matrix.getReverseDIterator(0, 1), matrix.getReverseDIterator(1, 0, true), -3) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.reverseDBegin(1), matrix.reverseDEnd(1), -3) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5, 6,  7,
                             1,  2,  4,  4, -5, 6,  7,
                             1,  2, -3, -1, -5, 6,  7,
                             1,  2, -3,  4,  5, 6,  7,
                             1,  2, -3,  4, -5, 4,  7,
                             1,  2, -3,  4, -5, 6, -1,
                         });

        QVERIFY2(std::count(matrix.reverseDBegin(1), matrix.reverseDEnd(1), -1) == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getReverseDIterator(4, 5), matrix.getReverseDIterator(1, 4, true), 4) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getReverseDIterator(3, 4), matrix.getReverseDIterator(1, 4, true), 4) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void ReverseDIteratorTests::testStdFind()
{
    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5, 6,  7,
                             1,  2,  4,  4, -5, 6,  7,
                             1,  2, -3, -1, -5, 6,  7,
                             1,  2, -3,  4,  5, 6,  7,
                             1,  2, -3,  4, -5, 4,  7,
                             1,  2, -3,  4, -5, 6, -1,
                         });

        IntMatrixReverseDIterator it{std::find(matrix.reverseDBegin(1), matrix.reverseDEnd(1), 5)};
        QVERIFY2(it == matrix.getReverseDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5, 6,  7,
                             1,  2,  4,  4, -5, 6,  7,
                             1,  2, -3, -1, -5, 6,  7,
                             1,  2, -3,  4,  4, 6,  7,
                             1,  2, -3,  4, -5, 5,  7,
                             1,  2, -3,  4, -5, 6, -1,
                         });

        IntMatrixReverseDIterator it{std::find(matrix.reverseDBegin(1), matrix.reverseDEnd(1), 4)};
        QVERIFY2(it == matrix.getReverseDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.reverseDEnd(1), 4);
        QVERIFY2(it == matrix.getReverseDIterator(1, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.reverseDEnd(1), 4);
        QVERIFY2(it == matrix.reverseDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5, 6,  7,
                             1,  2,  4,  4, -5, 6,  7,
                             1,  2, -3, -1, -5, 6,  7,
                             1,  2, -3,  4,  5, 6,  7,
                             1,  2, -3,  4, -5, 4,  7,
                             1,  2, -3,  4, -5, 6, -1,
                         });

        IntMatrixReverseDIterator it{std::find(matrix.reverseDBegin(1), matrix.reverseDEnd(1), -9)};
        QVERIFY2(it == matrix.reverseDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

void ReverseDIteratorTests::testStdSort()
{
    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5, 6, 7,
                             1,  2, -3,  4, -5, 6, 7,
                             1,  2, -3,  1, -5, 6, 7,
                             1,  2, -3,  4,  0, 6, 7,
                             1,  2, -3,  4, -5, 5, 7,
                             1,  2, -3,  4, -5, 6, 2,
                         });

        IntMatrix matrixRef(6, 7, {
                             1,  5, -3,  4, -5,  6,  7,
                             1,  2,  2,  4, -5,  6,  7,
                             1,  2, -3,  1, -5,  6,  7,
                             1,  2, -3,  4,  0,  6,  7,
                             1,  2, -3,  4, -5, -1,  7,
                             1,  2, -3,  4, -5,  6, -3,
                         });

        std::sort(matrix.reverseDBegin(1), matrix.reverseDEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2,  5,  4, -5,  6, 7,
                             1,  2, -3, -3, -5,  6, 7,
                             1,  2, -3,  4,  1,  6, 7,
                             1,  2, -3,  4, -5,  0, 7,
                             1,  2, -3,  4, -5,  6, 2,
                         });

        IntMatrix matrixRef(6, 7, {
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2,  5,  4, -5,  6, 7,
                             1,  2, -3,  1, -5,  6, 7,
                             1,  2, -3,  4,  0,  6, 7,
                             1,  2, -3,  4, -5, -3, 7,
                             1,  2, -3,  4, -5,  6, 2,
                         });

        std::sort(matrix.getReverseDIterator(4, 5), matrix.getReverseDIterator(1, 2));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2,  5,  4, -5,  6, 7,
                             1,  2, -3,  1, -5,  6, 7,
                             1,  2, -3,  4,  0,  6, 7,
                             1,  2, -3,  4, -5, -3, 7,
                             1,  2, -3,  4, -5,  6, 2,
                         });

        IntMatrix matrixRef(6, 7, {
                             1, -1, -3,  4, -5, 6,  7,
                             1,  2,  5,  4, -5, 6,  7,
                             1,  2, -3,  2, -5, 6,  7,
                             1,  2, -3,  4,  1, 6,  7,
                             1,  2, -3,  4, -5, 0,  7,
                             1,  2, -3,  4, -5, 6, -3,
                         });

        std::sort(matrix.reverseDBegin(1), matrix.getReverseDIterator(1, 2));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }

    {
        IntMatrix matrix(6, 7, {
                             1, -1, -3, 4, -5,  6, 7,
                             1,  2,  1, 4, -5,  6, 7,
                             1,  2, -3, 5, -5,  6, 7,
                             1,  2, -3, 4, -3,  6, 7,
                             1,  2, -3, 4, -5,  0, 7,
                             1,  2, -3, 4, -5,  6, 2,
                         });

        IntMatrix matrixRef(6, 7, {
                             1, 5, -3, 4, -5,  6, 7,
                             1, 2,  1, 4, -5,  6, 7,
                             1, 2, -3, 0, -5,  6, 7,
                             1, 2, -3, 4, -1,  6, 7,
                             1, 2, -3, 4, -5, -3, 7,
                             1, 2, -3, 4, -5,  6, 2,
                         });

        std::sort(matrix.getReverseDIterator(4, 5), matrix.reverseDEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }
}

QTEST_APPLESS_MAIN(ReverseDIteratorTests)

#include "tst_reversediteratortests.moc"
