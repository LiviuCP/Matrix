#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseDIterator = Matrix<int>::ConstReverseDIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseDIterator = Matrix<std::string>::ConstReverseDIterator;

class ConstReverseDIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseDIteratorTests();
    ~ConstReverseDIteratorTests();

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

ConstReverseDIteratorTests::ConstReverseDIteratorTests()
{

}

ConstReverseDIteratorTests::~ConstReverseDIteratorTests()
{

}

void ConstReverseDIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == -1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    // additional test for checking that an iterator is only valid with the matrix with which it is created
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrix matrixCopy{matrix};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 1)};

        QVERIFY(!it.isValidWithMatrix(matrixCopy));
    }
}

void ConstReverseDIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 2)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(1, 2)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(1, 0, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDBegin(2, 1)};
        IntMatrixConstReverseDIterator thirdIt{matrix.getConstReverseDIterator(3, 2)};
        IntMatrixConstReverseDIterator fourthIt{matrix.getConstReverseDIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDEnd(2)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDEnd(0, 2)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ConstReverseDIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 2)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(1, 2)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(1, 1, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ConstReverseDIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(1)};
    IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(0, 1)};
    IntMatrixConstReverseDIterator thirdIt{matrix.constReverseDEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ConstReverseDIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 2)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(3, 2)};
        IntMatrixConstReverseDIterator thirdIt{matrix.getConstReverseDIterator(2, 1)};
        IntMatrixConstReverseDIterator fourthIt{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator fifthIt{matrix.constReverseDEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ConstReverseDIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(1)};
    IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(0, 1)};
    IntMatrixConstReverseDIterator thirdIt{matrix.constReverseDEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ConstReverseDIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 2)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(3, 2)};
        IntMatrixConstReverseDIterator thirdIt{matrix.getConstReverseDIterator(2, 1)};
        IntMatrixConstReverseDIterator fourthIt{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator fifthIt{matrix.constReverseDEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ConstReverseDIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && preIncrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && prePreIncrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postIncrementIt == matrix.getConstReverseDIterator(3, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postPostIncrementIt == matrix.getConstReverseDIterator(3, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && prePostIncrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postPreIncrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constReverseDEnd(2, 1) && preIncrementIt == matrix.constReverseDEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constReverseDEnd(2, 1) && postIncrementIt == matrix.constReverseDEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseDIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && preDecrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && preDecrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && prePreDecrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && prePreDecrementIt == matrix.getConstReverseDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && postDecrementIt == matrix.constReverseDEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postDecrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && postPostDecrementIt == matrix.constReverseDEnd(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postPostDecrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && prePostDecrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && prePostDecrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstReverseDIterator(1, 0) && postPreDecrementIt == matrix.getConstReverseDIterator(1, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(1, 0)};
        IntMatrixConstReverseDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstReverseDIterator(2, 1) && postPreDecrementIt == matrix.getConstReverseDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstReverseDIterator(3, 2) && preDecrementIt == matrix.getConstReverseDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstReverseDIterator(3, 2) && postDecrementIt == matrix.getConstReverseDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseDIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator it2{it1 + (-1)};
        IntMatrixConstReverseDIterator it3{it1 + 2};
        IntMatrixConstReverseDIterator it4{it1 + 3};
        IntMatrixConstReverseDIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.getConstReverseDIterator(1, 0) && it4 == matrix.constReverseDEnd(3, 2) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator it2{it1 + (-2)};
        IntMatrixConstReverseDIterator it3{it1 + (-1)};
        IntMatrixConstReverseDIterator it4{it1 + (0)};
        IntMatrixConstReverseDIterator it5{it1 + 1};
        IntMatrixConstReverseDIterator it6{it1 + 2};
        IntMatrixConstReverseDIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(2, 1) && it5 == matrix.getConstReverseDIterator(1, 0) &&
                 it6 == matrix.constReverseDEnd(3, 2) && it7 == matrix.constReverseDEnd(3, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator it2{it1 + (-4)};
        IntMatrixConstReverseDIterator it3{it1 + (-3)};
        IntMatrixConstReverseDIterator it4{it1 + (-1)};
        IntMatrixConstReverseDIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(1, 0) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(2, 3)};
        IntMatrixConstReverseDIterator it2{it1 + (-2)};
        IntMatrixConstReverseDIterator it3{it1 + (-1)};
        IntMatrixConstReverseDIterator it4{it1 + 2};
        IntMatrixConstReverseDIterator it5{it1 + 3};
        IntMatrixConstReverseDIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.constReverseDBegin(2, 3) && it3 == matrix.constReverseDBegin(2, 3) && it4 == matrix.getConstReverseDIterator(0, 1) && it5 == matrix.constReverseDEnd(2, 3) && it6 == matrix.constReverseDEnd(2, 3),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseDIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator it2{it1 -1};
        IntMatrixConstReverseDIterator it3{it1 - (-2)};
        IntMatrixConstReverseDIterator it4{it1 - (-3)};
        IntMatrixConstReverseDIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.getConstReverseDIterator(1, 0) && it4 == matrix.constReverseDEnd(3, 2) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator it2{it1 - 2};
        IntMatrixConstReverseDIterator it3{it1 - 1};
        IntMatrixConstReverseDIterator it4{it1 - 0};
        IntMatrixConstReverseDIterator it5{it1 - (-1)};
        IntMatrixConstReverseDIterator it6{it1 - (-2)};
        IntMatrixConstReverseDIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(2, 1) && it5 == matrix.getConstReverseDIterator(1, 0) &&
                 it6 == matrix.constReverseDEnd(3, 2) && it7 == matrix.constReverseDEnd(3, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator it2{it1 - 4};
        IntMatrixConstReverseDIterator it3{it1 - 3};
        IntMatrixConstReverseDIterator it4{it1 - 1};
        IntMatrixConstReverseDIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(1, 0) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(2, 3)};
        IntMatrixConstReverseDIterator it2{it1 -2};
        IntMatrixConstReverseDIterator it3{it1 -1};
        IntMatrixConstReverseDIterator it4{it1 - (-2)};
        IntMatrixConstReverseDIterator it5{it1 - (-3)};
        IntMatrixConstReverseDIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.constReverseDBegin(2, 3) && it3 == matrix.constReverseDBegin(2, 3) && it4 == matrix.getConstReverseDIterator(0, 1) && it5 == matrix.constReverseDEnd(2, 3) && it6 == matrix.constReverseDEnd(2, 3),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseDIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.getConstReverseDIterator(1, 0) && it4 == matrix.constReverseDEnd(3, 2) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};
        IntMatrixConstReverseDIterator it6{it1};
        IntMatrixConstReverseDIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(2, 1) && it5 == matrix.getConstReverseDIterator(1, 0) &&
                 it6 == matrix.constReverseDEnd(3, 2) && it7 == matrix.constReverseDEnd(3, 2), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(1, 0) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(2, 3)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};
        IntMatrixConstReverseDIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.constReverseDBegin(2, 3) && it3 == matrix.constReverseDBegin(2, 3) && it4 == matrix.getConstReverseDIterator(0, 1) && it5 == matrix.constReverseDEnd(2, 3) && it6 == matrix.constReverseDEnd(2, 3),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseDIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};

        it2 -= 1;
        it3 -= -2;
        it4 -= -3;
        it5 -= -4;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.getConstReverseDIterator(1, 0) && it4 == matrix.constReverseDEnd(3, 2) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.getConstReverseDIterator(-1, 1, true)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};
        IntMatrixConstReverseDIterator it6{it1};
        IntMatrixConstReverseDIterator it7{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= 0;
        it5 -= -1;
        it6 -= -2;
        it7 -= -3;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(2, 1) && it5 == matrix.getConstReverseDIterator(1, 0) &&
                 it6 == matrix.constReverseDEnd(3, 2) && it7 == matrix.constReverseDEnd(3, 2), "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstReverseDIterator it1{matrix.constReverseDEnd(-1)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};

        it2 -= 4;
        it3 -= 3;
        it4 -= 1;
        it5 -= -1;

        QVERIFY2(it2 == matrix.constReverseDBegin(3, 2) && it3 == matrix.constReverseDBegin(3, 2) && it4 == matrix.getConstReverseDIterator(1, 0) && it5 == matrix.constReverseDEnd(3, 2),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it1{matrix.constReverseDBegin(2, 3)};
        IntMatrixConstReverseDIterator it2{it1};
        IntMatrixConstReverseDIterator it3{it1};
        IntMatrixConstReverseDIterator it4{it1};
        IntMatrixConstReverseDIterator it5{it1};
        IntMatrixConstReverseDIterator it6{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= -2;
        it5 -= -3;
        it6 -= -4;

        QVERIFY2(it2 == matrix.constReverseDBegin(2, 3) && it3 == matrix.constReverseDBegin(2, 3) && it4 == matrix.getConstReverseDIterator(0, 1) && it5 == matrix.constReverseDEnd(2, 3) && it6 == matrix.constReverseDEnd(2, 3),
                 "Operator -= does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseDIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDBegin(-1)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDBegin(3, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.constReverseDEnd(1)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDEnd(1, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(2, 1)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(-1, 0, true)};

        QVERIFY2(firstIt - secondIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(0, 1)};
        IntMatrixConstReverseDIterator secondIt{matrix.getConstReverseDIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(-1, 0, true)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator firstIt{matrix.getConstReverseDIterator(0, 0)};
        IntMatrixConstReverseDIterator secondIt{matrix.constReverseDBegin(2, 2)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstReverseDIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 1)};

    QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstReverseDIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{2, 3, {"abc", "pqr", "ghi", "jkl", "mno", "defed"}};
    StringMatrixConstReverseDIterator readIter{matrix.constReverseDBegin(0, 1)};

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstReverseDIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.getConstReverseDIterator(2, 1)};

        QVERIFY2(it[-1] == 12 && it[0] == -8 && it[1] == 4, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(0, 1)};

        QVERIFY2(it[0] == 6 && it[1] == 2, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstReverseDIterator it{matrix.constReverseDEnd(0)};

        QVERIFY2( it[-3] == 9 && it[-2] == -5 && it[-1] == 1, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }
}

void ConstReverseDIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
    IntMatrixConstReverseDIterator it{matrix.constReverseDBegin(1)};

    QVERIFY2(*it == 6, "The iterator does not reference the right value");

    it = matrix.getConstReverseDIterator(-2, 0, true);
    QVERIFY2(it[1] == 7, "the iterator index does not reference the right value");
}

void ConstReverseDIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {2, -3});

        QVERIFY2(std::count(matrix.getConstReverseDIterator(0, 1), matrix.getConstReverseDIterator(1, 0, true), -3) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.constReverseDBegin(1), matrix.constReverseDEnd(1), -3) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
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

        QVERIFY2(std::count(matrix.constReverseDBegin(1), matrix.constReverseDEnd(1), -1) == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstReverseDIterator(4, 5), matrix.getConstReverseDIterator(1, 4, true), 4) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstReverseDIterator(3, 4), matrix.getConstReverseDIterator(1, 4, true), 4) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void ConstReverseDIteratorTests::testStdFind()
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

        IntMatrixConstReverseDIterator it{std::find(matrix.constReverseDBegin(1), matrix.constReverseDEnd(1), 5)};
        QVERIFY2(it == matrix.getConstReverseDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstReverseDIterator it{std::find(matrix.constReverseDBegin(1), matrix.constReverseDEnd(1), 4)};
        QVERIFY2(it == matrix.getConstReverseDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constReverseDEnd(1), 4);
        QVERIFY2(it == matrix.getConstReverseDIterator(1, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constReverseDEnd(1), 4);
        QVERIFY2(it == matrix.constReverseDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstReverseDIterator it{std::find(matrix.constReverseDBegin(1), matrix.constReverseDEnd(1), -9)};
        QVERIFY2(it == matrix.constReverseDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

QTEST_APPLESS_MAIN(ConstReverseDIteratorTests)

#include "tst_constreversediteratortests.moc"
