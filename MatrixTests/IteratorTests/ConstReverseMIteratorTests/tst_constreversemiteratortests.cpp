#include <QtTest>

#include "matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseMIterator = Matrix<int>::ConstReverseMIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseMIterator = Matrix<std::string>::ConstReverseMIterator;

class ConstReverseMIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseMIteratorTests();
    ~ConstReverseMIteratorTests();

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
};

ConstReverseMIteratorTests::ConstReverseMIteratorTests()
{

}

ConstReverseMIteratorTests::~ConstReverseMIteratorTests()
{

}

void ConstReverseMIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    // additional test for checking that an iterator is only valid with the matrix with which it is created
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrix matrixCopy{matrix};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 1)};

        QVERIFY(!it.isValidWithMatrix(matrixCopy));
    }
}

void ConstReverseMIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 0)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(1, 0)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(1, 0, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMBegin(2, 1)};
        IntMatrixConstReverseMIterator thirdIt{matrix.getConstReverseMIterator(3, 0)};
        IntMatrixConstReverseMIterator fourthIt{matrix.getConstReverseMIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMEnd(2)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMEnd(0, 0)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ConstReverseMIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 0)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(1, 0)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(1, 1, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ConstReverseMIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(1)};
    IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(0, 1)};
    IntMatrixConstReverseMIterator thirdIt{matrix.constReverseMEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ConstReverseMIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 0)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(3, 0)};
        IntMatrixConstReverseMIterator thirdIt{matrix.getConstReverseMIterator(2, 1)};
        IntMatrixConstReverseMIterator fourthIt{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator fifthIt{matrix.constReverseMEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ConstReverseMIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(1)};
    IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(0, 1)};
    IntMatrixConstReverseMIterator thirdIt{matrix.constReverseMEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ConstReverseMIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 0)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(3, 0)};
        IntMatrixConstReverseMIterator thirdIt{matrix.getConstReverseMIterator(2, 1)};
        IntMatrixConstReverseMIterator fourthIt{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator fifthIt{matrix.constReverseMEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ConstReverseMIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && preIncrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && prePreIncrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postIncrementIt == matrix.getConstReverseMIterator(3, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postPostIncrementIt == matrix.getConstReverseMIterator(3, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && prePostIncrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postPreIncrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constReverseMEnd(2, 1) && preIncrementIt == matrix.constReverseMEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constReverseMEnd(2, 1) && postIncrementIt == matrix.constReverseMEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseMIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && preDecrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && preDecrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && prePreDecrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && prePreDecrementIt == matrix.getConstReverseMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && postDecrementIt == matrix.constReverseMEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postDecrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && postPostDecrementIt == matrix.constReverseMEnd(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postPostDecrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && prePostDecrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && prePostDecrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstReverseMIterator(1, 2) && postPreDecrementIt == matrix.getConstReverseMIterator(1, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(1, 2)};
        IntMatrixConstReverseMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstReverseMIterator(2, 1) && postPreDecrementIt == matrix.getConstReverseMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseMIterator(3, 0) && preDecrementIt == matrix.getConstReverseMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseMIterator(3, 0) && postDecrementIt == matrix.getConstReverseMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseMIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator it2{it1 + (-1)};
        IntMatrixConstReverseMIterator it3{it1 + 2};
        IntMatrixConstReverseMIterator it4{it1 + 3};
        IntMatrixConstReverseMIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.getConstReverseMIterator(1, 2) && it4 == matrix.constReverseMEnd(3, 0) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator it2{it1 + (-2)};
        IntMatrixConstReverseMIterator it3{it1 + (-1)};
        IntMatrixConstReverseMIterator it4{it1 + (0)};
        IntMatrixConstReverseMIterator it5{it1 + 1};
        IntMatrixConstReverseMIterator it6{it1 + 2};
        IntMatrixConstReverseMIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(2, 1) && it5 == matrix.getConstReverseMIterator(1, 2) &&
                 it6 == matrix.constReverseMEnd(3, 0) && it7 == matrix.constReverseMEnd(3, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator it2{it1 + (-4)};
        IntMatrixConstReverseMIterator it3{it1 + (-3)};
        IntMatrixConstReverseMIterator it4{it1 + (-1)};
        IntMatrixConstReverseMIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(1, 2) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(2, 0)};
        IntMatrixConstReverseMIterator it2{it1 + (-2)};
        IntMatrixConstReverseMIterator it3{it1 + (-1)};
        IntMatrixConstReverseMIterator it4{it1 + 2};
        IntMatrixConstReverseMIterator it5{it1 + 3};
        IntMatrixConstReverseMIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.constReverseMBegin(2, 0) && it3 == matrix.constReverseMBegin(2, 0) && it4 == matrix.getConstReverseMIterator(0, 2) && it5 == matrix.constReverseMEnd(2, 0) && it6 == matrix.constReverseMEnd(2, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseMIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator it2{it1 - 1};
        IntMatrixConstReverseMIterator it3{it1 - (-2)};
        IntMatrixConstReverseMIterator it4{it1 - (-3)};
        IntMatrixConstReverseMIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.getConstReverseMIterator(1, 2) && it4 == matrix.constReverseMEnd(3, 0) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator it2{it1 - 2};
        IntMatrixConstReverseMIterator it3{it1 - 1};
        IntMatrixConstReverseMIterator it4{it1 - 0};
        IntMatrixConstReverseMIterator it5{it1 - (-1)};
        IntMatrixConstReverseMIterator it6{it1 - (-2)};
        IntMatrixConstReverseMIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(2, 1) && it5 == matrix.getConstReverseMIterator(1, 2) &&
                 it6 == matrix.constReverseMEnd(3, 0) && it7 == matrix.constReverseMEnd(3, 0), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator it2{it1 - 4};
        IntMatrixConstReverseMIterator it3{it1 - 3};
        IntMatrixConstReverseMIterator it4{it1 - 1};
        IntMatrixConstReverseMIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(1, 2) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(2, 0)};
        IntMatrixConstReverseMIterator it2{it1 - 2};
        IntMatrixConstReverseMIterator it3{it1 - 1};
        IntMatrixConstReverseMIterator it4{it1 - (-2)};
        IntMatrixConstReverseMIterator it5{it1 - (-3)};
        IntMatrixConstReverseMIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.constReverseMBegin(2, 0) && it3 == matrix.constReverseMBegin(2, 0) && it4 == matrix.getConstReverseMIterator(0, 2) && it5 == matrix.constReverseMEnd(2, 0) && it6 == matrix.constReverseMEnd(2, 0),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseMIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.getConstReverseMIterator(1, 2) && it4 == matrix.constReverseMEnd(3, 0) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};
        IntMatrixConstReverseMIterator it6{it1};
        IntMatrixConstReverseMIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(2, 1) && it5 == matrix.getConstReverseMIterator(1, 2) &&
                 it6 == matrix.constReverseMEnd(3, 0) && it7 == matrix.constReverseMEnd(3, 0), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(1, 2) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(2, 0)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};
        IntMatrixConstReverseMIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.constReverseMBegin(2, 0) && it3 == matrix.constReverseMBegin(2, 0) && it4 == matrix.getConstReverseMIterator(0, 2) && it5 == matrix.constReverseMEnd(2, 0) && it6 == matrix.constReverseMEnd(2, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseMIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};

        it2 -= 1;
        it3 -= -2;
        it4 -= -3;
        it5 -= -4;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.getConstReverseMIterator(1, 2) && it4 == matrix.constReverseMEnd(3, 0) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.getConstReverseMIterator(-1, 1, true)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};
        IntMatrixConstReverseMIterator it6{it1};
        IntMatrixConstReverseMIterator it7{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= 0;
        it5 -= -1;
        it6 -= -2;
        it7 -= -3;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(2, 1) && it5 == matrix.getConstReverseMIterator(1, 2) &&
                 it6 == matrix.constReverseMEnd(3, 0) && it7 == matrix.constReverseMEnd(3, 0), "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstReverseMIterator it1{matrix.constReverseMEnd(-1)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};

        it2 -= 4;
        it3 -= 3;
        it4 -= 1;
        it5 -= -1;

        QVERIFY2(it2 == matrix.constReverseMBegin(3, 0) && it3 == matrix.constReverseMBegin(3, 0) && it4 == matrix.getConstReverseMIterator(1, 2) && it5 == matrix.constReverseMEnd(3, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstReverseMIterator it1{matrix.constReverseMBegin(2, 0)};
        IntMatrixConstReverseMIterator it2{it1};
        IntMatrixConstReverseMIterator it3{it1};
        IntMatrixConstReverseMIterator it4{it1};
        IntMatrixConstReverseMIterator it5{it1};
        IntMatrixConstReverseMIterator it6{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= -2;
        it5 -= -3;
        it6 -= -4;

        QVERIFY2(it2 == matrix.constReverseMBegin(2, 0) && it3 == matrix.constReverseMBegin(2, 0) && it4 == matrix.getConstReverseMIterator(0, 2) && it5 == matrix.constReverseMEnd(2, 0) && it6 == matrix.constReverseMEnd(2, 0),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseMIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMBegin(-1)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMBegin(3, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.constReverseMEnd(1)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMEnd(1, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(2, 1)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(-1, 0, true)};

        QVERIFY2(firstIt - secondIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(0, 1)};
        IntMatrixConstReverseMIterator secondIt{matrix.getConstReverseMIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(-1, 0, true)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator firstIt{matrix.getConstReverseMIterator(0, 2)};
        IntMatrixConstReverseMIterator secondIt{matrix.constReverseMBegin(2, 0)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstReverseMIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 1)};

    QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstReverseMIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{2, 3, {"ghi", "pqr", "abc", "defed", "mno", "jkl"}};
    StringMatrixConstReverseMIterator readIter{matrix.constReverseMBegin(0, 1)};

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstReverseMIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.getConstReverseMIterator(2, 1)};

        QVERIFY2(it[-1] == 12 && it[0] == -8 && it[1] == 4, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(0, 1)};

        QVERIFY2(it[0] == 6 && it[1] == 2, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstReverseMIterator it{matrix.constReverseMEnd(0)};

        QVERIFY2( it[-3] == 9 && it[-2] == -5 && it[-1] == 1, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }
}

void ConstReverseMIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10});
    IntMatrixConstReverseMIterator it{matrix.constReverseMBegin(1)};

    QVERIFY2(*it == 6, "The iterator does not reference the right value");

    it = matrix.getConstReverseMIterator(-2, 0, true);
    QVERIFY2(it[1] == 7, "the iterator index does not reference the right value");
}

void ConstReverseMIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {-3, 2});

        QVERIFY2(std::count(matrix.getConstReverseMIterator(0, 0), matrix.getConstReverseMIterator(1, 0, true), -3) == 0,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.constReverseMBegin(1), matrix.constReverseMEnd(1), -3) == 1,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
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

        QVERIFY2(std::count(matrix.constReverseMBegin(1), matrix.constReverseMEnd(1), -1) == 3,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstReverseMIterator(4, 1), matrix.getConstReverseMIterator(1, 4, true), 4) == 1,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstReverseMIterator(3, 2), matrix.getConstReverseMIterator(1, 4, true), 4) == 0,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void ConstReverseMIteratorTests::testStdFind()
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

        IntMatrixConstReverseMIterator it{std::find(matrix.constReverseMBegin(1), matrix.constReverseMEnd(1), 5)};
        QVERIFY2(it == matrix.getConstReverseMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstReverseMIterator it{std::find(matrix.constReverseMBegin(1), matrix.constReverseMEnd(1), 4)};
        QVERIFY2(it == matrix.getConstReverseMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constReverseMEnd(1), 4);
        QVERIFY2(it == matrix.getConstReverseMIterator(1, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constReverseMEnd(1), 4);
        QVERIFY2(it == matrix.constReverseMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstReverseMIterator it{std::find(matrix.constReverseMBegin(1), matrix.constReverseMEnd(1), -9)};
        QVERIFY2(it == matrix.constReverseMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

QTEST_APPLESS_MAIN(ConstReverseMIteratorTests)

#include "tst_constreversemiteratortests.moc"
