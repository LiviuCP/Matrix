#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstMIterator = Matrix<int>::ConstMIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstMIterator = Matrix<std::string>::ConstMIterator;

class ConstMIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstMIteratorTests();
    ~ConstMIteratorTests();

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

ConstMIteratorTests::ConstMIteratorTests()
{

}

ConstMIteratorTests::~ConstMIteratorTests()
{

}

void ConstMIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == -1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(2, 0)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2 && it.isValidWithMatrix(matrix), "The iterator has not been correctly created");
    }

    // additional test for checking that an iterator is only valid with the matrix with which it is created
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrix matrixCopy{matrix};
        IntMatrixConstMIterator it{matrix.getConstMIterator(2, 1)};

        QVERIFY(!it.isValidWithMatrix(matrixCopy));
    }
}

void ConstMIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(1, 0)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(1, 0)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 1, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMBegin(-1)};
        IntMatrixConstMIterator secondIt{matrix.constMBegin(2, 1)};
        IntMatrixConstMIterator thirdIt{matrix.getConstMIterator(1, 2)};
        IntMatrixConstMIterator fourthIt{matrix.getConstMIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMEnd(2)};
        IntMatrixConstMIterator secondIt{matrix.constMEnd(0, 0)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ConstMIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(1, 0)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(1, 0)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 0, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ConstMIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstMIterator firstIt{matrix.constMBegin(1)};
    IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 0)};
    IntMatrixConstMIterator thirdIt{matrix.constMEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ConstMIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(1, 0)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMBegin(-1)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 2)};
        IntMatrixConstMIterator thirdIt{matrix.getConstMIterator(2, 1)};
        IntMatrixConstMIterator fourthIt{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator fifthIt{matrix.constMEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ConstMIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstMIterator firstIt{matrix.constMBegin(1)};
    IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 0)};
    IntMatrixConstMIterator thirdIt{matrix.constMEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ConstMIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(1, 0)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMBegin(-1)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 2)};
        IntMatrixConstMIterator thirdIt{matrix.getConstMIterator(2, 1)};
        IntMatrixConstMIterator fourthIt{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator fifthIt{matrix.constMEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ConstMIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && preIncrementIt == matrix.getConstMIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && prePreIncrementIt == matrix.getConstMIterator(3, 0),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postIncrementIt == matrix.getConstMIterator(1, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postPostIncrementIt == matrix.getConstMIterator(1, 2),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && prePostIncrementIt == matrix.getConstMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postPreIncrementIt == matrix.getConstMIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constMEnd(2, 1) && preIncrementIt == matrix.constMEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constMEnd(2, 1) && postIncrementIt == matrix.constMEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstMIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && preDecrementIt == matrix.getConstMIterator(3, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && preDecrementIt == matrix.getConstMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && prePreDecrementIt == matrix.getConstMIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && prePreDecrementIt == matrix.getConstMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && postDecrementIt == matrix.constMEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postDecrementIt == matrix.getConstMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && postPostDecrementIt == matrix.constMEnd(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postPostDecrementIt == matrix.getConstMIterator(3, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && prePostDecrementIt == matrix.getConstMIterator(3, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && prePostDecrementIt == matrix.getConstMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(-1)};
        IntMatrixConstMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstMIterator(3, 0) && postPreDecrementIt == matrix.getConstMIterator(3, 0),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(3, 0)};
        IntMatrixConstMIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstMIterator(2, 1) && postPreDecrementIt == matrix.getConstMIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstMIterator(1, 2) && preDecrementIt == matrix.getConstMIterator(1, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(-1)};
        IntMatrixConstMIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstMIterator(1, 2) && postDecrementIt == matrix.getConstMIterator(1, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstMIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMBegin(-1)};
        IntMatrixConstMIterator it2{it1 + (-1)};
        IntMatrixConstMIterator it3{it1 + 2};
        IntMatrixConstMIterator it4{it1 + 3};
        IntMatrixConstMIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.getConstMIterator(3, 0) && it4 == matrix.constMEnd(1, 2) && it5 == matrix.constMEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator it2{it1 + (-2)};
        IntMatrixConstMIterator it3{it1 + (-1)};
        IntMatrixConstMIterator it4{it1 + (0)};
        IntMatrixConstMIterator it5{it1 + 1};
        IntMatrixConstMIterator it6{it1 + 2};
        IntMatrixConstMIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(2, 1) && it5 == matrix.getConstMIterator(3, 0) &&
                 it6 == matrix.constMEnd(1, 2) && it7 == matrix.constMEnd(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMEnd(-1)};
        IntMatrixConstMIterator it2{it1 + (-4)};
        IntMatrixConstMIterator it3{it1 + (-3)};
        IntMatrixConstMIterator it4{it1 + (-1)};
        IntMatrixConstMIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(3, 0) && it5 == matrix.constMEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstMIterator it1{matrix.constMBegin(0, 2)};
        IntMatrixConstMIterator it2{it1 + (-2)};
        IntMatrixConstMIterator it3{it1 + (-1)};
        IntMatrixConstMIterator it4{it1 + 2};
        IntMatrixConstMIterator it5{it1 + 3};
        IntMatrixConstMIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.constMBegin(0, 2) && it3 == matrix.constMBegin(0, 2) && it4 == matrix.getConstMIterator(2, 0) && it5 == matrix.constMEnd(0, 2) && it6 == matrix.constMEnd(0, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstMIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMBegin(-1)};
        IntMatrixConstMIterator it2{it1 - 1};
        IntMatrixConstMIterator it3{it1 - (-2)};
        IntMatrixConstMIterator it4{it1 - (-3)};
        IntMatrixConstMIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.getConstMIterator(3, 0) && it4 == matrix.constMEnd(1, 2) && it5 == matrix.constMEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator it2{it1 - 2};
        IntMatrixConstMIterator it3{it1 - 1};
        IntMatrixConstMIterator it4{it1 - 0};
        IntMatrixConstMIterator it5{it1 - (-1)};
        IntMatrixConstMIterator it6{it1 - (-2)};
        IntMatrixConstMIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(2, 1) && it5 == matrix.getConstMIterator(3, 0) &&
                 it6 == matrix.constMEnd(1, 2) && it7 == matrix.constMEnd(1, 2), "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMEnd(-1)};
        IntMatrixConstMIterator it2{it1 - 4};
        IntMatrixConstMIterator it3{it1 - 3};
        IntMatrixConstMIterator it4{it1 - 1};
        IntMatrixConstMIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(3, 0) && it5 == matrix.constMEnd(1, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstMIterator it1{matrix.constMBegin(0, 2)};
        IntMatrixConstMIterator it2{it1 - 2};
        IntMatrixConstMIterator it3{it1 - 1};
        IntMatrixConstMIterator it4{it1 - (-2)};
        IntMatrixConstMIterator it5{it1 - (-3)};
        IntMatrixConstMIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.constMBegin(0, 2) && it3 == matrix.constMBegin(0, 2) && it4 == matrix.getConstMIterator(2, 0) && it5 == matrix.constMEnd(0, 2) && it6 == matrix.constMEnd(0, 2),
                 "Operator + does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstMIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMBegin(-1)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.getConstMIterator(3, 0) && it4 == matrix.constMEnd(1, 2) && it5 == matrix.constMEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};
        IntMatrixConstMIterator it6{it1};
        IntMatrixConstMIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(2, 1) && it5 == matrix.getConstMIterator(3, 0) &&
                 it6 == matrix.constMEnd(1, 2) && it7 == matrix.constMEnd(1, 2), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMEnd(-1)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(3, 0) && it5 == matrix.constMEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstMIterator it1{matrix.constMBegin(0, 2)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};
        IntMatrixConstMIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.constMBegin(0, 2) && it3 == matrix.constMBegin(0, 2) && it4 == matrix.getConstMIterator(2, 0) && it5 == matrix.constMEnd(0, 2) && it6 == matrix.constMEnd(0, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstMIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMBegin(-1)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};

        it2 -= 1;
        it3 -= -2;
        it4 -= -3;
        it5 -= -4;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.getConstMIterator(3, 0) && it4 == matrix.constMEnd(1, 2) && it5 == matrix.constMEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.getConstMIterator(-1, 1, true)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};
        IntMatrixConstMIterator it6{it1};
        IntMatrixConstMIterator it7{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= 0;
        it5 -= -1;
        it6 -= -2;
        it7 -= -3;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(2, 1) && it5 == matrix.getConstMIterator(3, 0) &&
                 it6 == matrix.constMEnd(1, 2) && it7 == matrix.constMEnd(1, 2), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};

        IntMatrixConstMIterator it1{matrix.constMEnd(-1)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};

        it2 -= 4;
        it3 -= 3;
        it4 -= 1;
        it5 -= -1;

        QVERIFY2(it2 == matrix.constMBegin(1, 2) && it3 == matrix.constMBegin(1, 2) && it4 == matrix.getConstMIterator(3, 0) && it5 == matrix.constMEnd(1, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {4, -3, 2, 1, -8, 7, 6, -5, 12, -11, 10, 9}};
        IntMatrixConstMIterator it1{matrix.constMBegin(0, 2)};
        IntMatrixConstMIterator it2{it1};
        IntMatrixConstMIterator it3{it1};
        IntMatrixConstMIterator it4{it1};
        IntMatrixConstMIterator it5{it1};
        IntMatrixConstMIterator it6{it1};

        it2 -= 2;
        it3 -= 1;
        it4 -= -2;
        it5 -= -3;
        it6 -= -4;

        QVERIFY2(it2 == matrix.constMBegin(0, 2) && it3 == matrix.constMBegin(0, 2) && it4 == matrix.getConstMIterator(2, 0) && it5 == matrix.constMEnd(0, 2) && it6 == matrix.constMEnd(0, 2),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstMIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMBegin(-1)};
        IntMatrixConstMIterator secondIt{matrix.constMBegin(1, 2)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.constMEnd(1)};
        IntMatrixConstMIterator secondIt{matrix.constMEnd(0, 1)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(2, 1)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(-1, 2, true)};

        QVERIFY2(secondIt - firstIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(1, 0)};
        IntMatrixConstMIterator secondIt{matrix.getConstMIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(-1, 0, true)};
        IntMatrixConstMIterator secondIt{matrix.constMEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator firstIt{matrix.getConstMIterator(2, 0)};
        IntMatrixConstMIterator secondIt{matrix.constMBegin(0, 2)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstMIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
    IntMatrixConstMIterator it{matrix.getConstMIterator(2, 1)};

    QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstMIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{2, 3, {"ghi", "defed", "abc", "pqr", "mno", "jkl"}};
    StringMatrixConstMIterator readIter{matrix.constMBegin(0, 1)};

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstMIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.getConstMIterator(2, 1)};

        QVERIFY2(it[-1] == 4 && it[0] == -8 && it[1] == 12, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMBegin(0, 1)};

        QVERIFY2(it[0] == 2 && it[1] == 6, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10}};
        IntMatrixConstMIterator it{matrix.constMEnd(0)};

        QVERIFY2( it[-3] == 1 && it[-2] == -5 && it[-1] == 9, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }
}

void ConstMIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {-3, 2, 1, 6, -5, 4, 9, -8, 7, 12, -11, 10});
    IntMatrixConstMIterator it{matrix.constMBegin(1)};

    QVERIFY2(*it == 2, "The iterator does not reference the right value");

    it = matrix.getConstMIterator(-2, 0, true);
    QVERIFY2(it[1] == -11, "the iterator index does not reference the right value");
}

void ConstMIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {-3, 2});

        QVERIFY2(std::count(matrix.getConstMIterator(0, 0), matrix.getConstMIterator(1, 0, true), -3) == 0,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.constMBegin(1), matrix.constMEnd(1), -3) == 1,
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

        QVERIFY2(std::count(matrix.constMBegin(1), matrix.constMEnd(1), -1) == 3,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstMIterator(1, 1, true), matrix.getConstMIterator(4, 1), 4) == 1,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstMIterator(2, 3), matrix.getConstMIterator(1, 4, true), 4) == 0,
                 "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void ConstMIteratorTests::testStdFind()
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

        IntMatrixConstMIterator it{std::find(matrix.constMBegin(1), matrix.constMEnd(1), 5)};
        QVERIFY2(it == matrix.getConstMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstMIterator it{std::find(matrix.constMBegin(1), matrix.constMEnd(1), 4)};
        QVERIFY2(it == matrix.getConstMIterator(1, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constMEnd(1), 4);
        QVERIFY2(it == matrix.getConstMIterator(3, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constMEnd(1), 4);
        QVERIFY2(it == matrix.constMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstMIterator it{std::find(matrix.constMBegin(1), matrix.constMEnd(1), -9)};
        QVERIFY2(it == matrix.constMEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

QTEST_APPLESS_MAIN(ConstMIteratorTests)

#include "tst_constmiteratortests.moc"
