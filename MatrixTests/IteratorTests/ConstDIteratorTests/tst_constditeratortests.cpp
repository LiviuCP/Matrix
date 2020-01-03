#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstDIterator = Matrix<int>::ConstDIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstDIterator = Matrix<std::string>::ConstDIterator;

class ConstDIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstDIteratorTests();
    ~ConstDIteratorTests();

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
};

ConstDIteratorTests::ConstDIteratorTests()
{

}

ConstDIteratorTests::~ConstDIteratorTests()
{

}

void ConstDIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(2, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The ConstDIterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The ConstDIterator has not been correctly created");
    }
}

void ConstDIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 2)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(1, 2)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDBegin(-1)};
        IntMatrixConstDIterator secondIt{matrix.constDBegin(2, 1)};
        IntMatrixConstDIterator thirdIt{matrix.getConstDIterator(1, 0)};
        IntMatrixConstDIterator fourthIt{matrix.getConstDIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDEnd(2)};
        IntMatrixConstDIterator secondIt{matrix.constDEnd(0, 2)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void ConstDIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 2)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(1, 2)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 0, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void ConstDIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstDIterator firstIt{matrix.constDBegin(1)};
    IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 2)};
    IntMatrixConstDIterator thirdIt{matrix.constDEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void ConstDIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 2)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDBegin(-1)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 0)};
        IntMatrixConstDIterator thirdIt{matrix.getConstDIterator(2, 1)};
        IntMatrixConstDIterator fourthIt{matrix.getConstDIterator(-1, 1, true)};
        IntMatrixConstDIterator fifthIt{matrix.constDEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void ConstDIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstDIterator firstIt{matrix.constDBegin(1)};
    IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 2)};
    IntMatrixConstDIterator thirdIt{matrix.constDEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void ConstDIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 2)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDBegin(-1)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 0)};
        IntMatrixConstDIterator thirdIt{matrix.getConstDIterator(2, 1)};
        IntMatrixConstDIterator fourthIt{matrix.getConstDIterator(-1, 1, true)};
        IntMatrixConstDIterator fifthIt{matrix.constDEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void ConstDIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && preIncrementIt == matrix.getConstDIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && prePreIncrementIt == matrix.getConstDIterator(3, 2),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postIncrementIt == matrix.getConstDIterator(1, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postPostIncrementIt == matrix.getConstDIterator(1, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && prePostIncrementIt == matrix.getConstDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postPreIncrementIt == matrix.getConstDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constDEnd(2, 1) && preIncrementIt == matrix.constDEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constDEnd(2, 1) && postIncrementIt == matrix.constDEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstDIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && preDecrementIt == matrix.getConstDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && preDecrementIt == matrix.getConstDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && prePreDecrementIt == matrix.getConstDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && prePreDecrementIt == matrix.getConstDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && postDecrementIt == matrix.constDEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postDecrementIt == matrix.getConstDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && postPostDecrementIt == matrix.constDEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postPostDecrementIt == matrix.getConstDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && prePostDecrementIt == matrix.getConstDIterator(3, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && prePostDecrementIt == matrix.getConstDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(-1)};
        IntMatrixConstDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstDIterator(3, 2) && postPreDecrementIt == matrix.getConstDIterator(3, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(3, 2)};
        IntMatrixConstDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getConstDIterator(2, 1) && postPreDecrementIt == matrix.getConstDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getConstDIterator(1, 0) && preDecrementIt == matrix.getConstDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(-1)};
        IntMatrixConstDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getConstDIterator(1, 0) && postDecrementIt == matrix.getConstDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstDIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.constDBegin(-1)};
        IntMatrixConstDIterator it2{it1 + (-1)};
        IntMatrixConstDIterator it3{it1 + 2};
        IntMatrixConstDIterator it4{it1 + 3};
        IntMatrixConstDIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.getConstDIterator(3, 2) && it4 == matrix.constDEnd(1, 0) && it5 == matrix.constDEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.getConstDIterator(-1, 1, true)};
        IntMatrixConstDIterator it2{it1 + (-2)};
        IntMatrixConstDIterator it3{it1 + (-1)};
        IntMatrixConstDIterator it4{it1 + (0)};
        IntMatrixConstDIterator it5{it1 + 1};
        IntMatrixConstDIterator it6{it1 + 2};
        IntMatrixConstDIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.constDBegin(1, 0) && it4 == matrix.getConstDIterator(2, 1) && it5 == matrix.getConstDIterator(3, 2) &&
                 it6 == matrix.constDEnd(1, 0) && it7 == matrix.constDEnd(1, 0), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.constDEnd(-1)};
        IntMatrixConstDIterator it2{it1 + (-4)};
        IntMatrixConstDIterator it3{it1 + (-3)};
        IntMatrixConstDIterator it4{it1 + (-1)};
        IntMatrixConstDIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.constDBegin(1, 0) && it4 == matrix.getConstDIterator(3, 2) && it5 == matrix.constDEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it1{matrix.constDBegin(0, 1)};
        IntMatrixConstDIterator it2{it1 + (-2)};
        IntMatrixConstDIterator it3{it1 + (-1)};
        IntMatrixConstDIterator it4{it1 + 2};
        IntMatrixConstDIterator it5{it1 + 3};
        IntMatrixConstDIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.constDBegin(0, 1) && it3 == matrix.constDBegin(0, 1) && it4 == matrix.getConstDIterator(2, 3) && it5 == matrix.constDEnd(0, 1) && it6 == matrix.constDEnd(0, 1),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void ConstDIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.constDBegin(-1)};
        IntMatrixConstDIterator it2{it1 -1};
        IntMatrixConstDIterator it3{it1 - (-2)};
        IntMatrixConstDIterator it4{it1 - (-3)};
        IntMatrixConstDIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.getConstDIterator(3, 2) && it4 == matrix.constDEnd(1, 0) && it5 == matrix.constDEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.getConstDIterator(-1, 1, true)};
        IntMatrixConstDIterator it2{it1 - 2};
        IntMatrixConstDIterator it3{it1 - 1};
        IntMatrixConstDIterator it4{it1 - 0};
        IntMatrixConstDIterator it5{it1 - (-1)};
        IntMatrixConstDIterator it6{it1 - (-2)};
        IntMatrixConstDIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.constDBegin(1, 0) && it4 == matrix.getConstDIterator(2, 1) && it5 == matrix.getConstDIterator(3, 2) &&
                 it6 == matrix.constDEnd(1, 0) && it7 == matrix.constDEnd(1, 0), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixConstDIterator it1{matrix.constDEnd(-1)};
        IntMatrixConstDIterator it2{it1 - 4};
        IntMatrixConstDIterator it3{it1 - 3};
        IntMatrixConstDIterator it4{it1 - 1};
        IntMatrixConstDIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.constDBegin(1, 0) && it3 == matrix.constDBegin(1, 0) && it4 == matrix.getConstDIterator(3, 2) && it5 == matrix.constDEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it1{matrix.constDBegin(0, 1)};
        IntMatrixConstDIterator it2{it1 -2};
        IntMatrixConstDIterator it3{it1 -1};
        IntMatrixConstDIterator it4{it1 - (-2)};
        IntMatrixConstDIterator it5{it1 - (-3)};
        IntMatrixConstDIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.constDBegin(0, 1) && it3 == matrix.constDBegin(0, 1) && it4 == matrix.getConstDIterator(2, 3) && it5 == matrix.constDEnd(0, 1) && it6 == matrix.constDEnd(0, 1),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void ConstDIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDBegin(-1)};
        IntMatrixConstDIterator secondIt{matrix.constDBegin(1, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.constDEnd(1)};
        IntMatrixConstDIterator secondIt{matrix.constDEnd(0, 1)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(-1, 2, true)};

        QVERIFY2(secondIt - firstIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(1, 2)};
        IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(-1, 0, true)};
        IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 2)};
        IntMatrixConstDIterator secondIt{matrix.constDBegin(0, 0)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstDIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixConstDIterator it{matrix.getConstDIterator(2, 1)};

    QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstDIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    StringMatrixConstDIterator readIter{matrix.constDBegin(0, 1)};

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstDIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(2, 1)};

        QVERIFY2(it[-1] == 4 && it[0] == -8 && it[1] == 12, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDBegin(0, 1)};

        QVERIFY2(it[0] == 2 && it[1] == 6, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixConstDIterator it{matrix.constDEnd(0)};

        QVERIFY2( it[-3] == 1 && it[-2] == -5 && it[-1] == 9, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }
}

void ConstDIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(0, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 1)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(1, 1, true)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 0, true)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(1, 0, true)};

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
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(-1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertRow(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixConstDIterator it{firstMatrix.getConstDIterator(1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertColumn(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }
}

void ConstDIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
    IntMatrixConstDIterator it{matrix.constDBegin(1)};

    QVERIFY2(*it == 2, "The iterator does not reference the right value");

    it = matrix.getConstDIterator(-2, 0, true);
    QVERIFY2(it[1] == -11, "the iterator index does not reference the right value");
}

void ConstDIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {2, -3});

        QVERIFY2(std::count(matrix.getConstDIterator(0, 1), matrix.getConstDIterator(1, 0, true), -3) == 0,
                 "The std::count doesn't work correctly with ConstDIterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.constDBegin(1), matrix.constDEnd(1), -3) == 1,
                 "The std::count doesn't work correctly with ConstDIterator, incorrect number of matches returned");
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

        QVERIFY2(std::count(matrix.constDBegin(1), matrix.constDEnd(1), -1) == 3,
                 "The std::count doesn't work correctly with ConstDIterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstDIterator(1, 1, true), matrix.getConstDIterator(4, 5), 4) == 1,
                 "The std::count doesn't work correctly with ConstDIterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getConstDIterator(2, 3), matrix.getConstDIterator(1, 4, true), 4) == 0,
                 "The std::count doesn't work correctly with ConstDIterator, incorrect number of matches returned");
    }
}

void ConstDIteratorTests::testStdFind()
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

        IntMatrixConstDIterator it{std::find(matrix.constDBegin(1), matrix.constDEnd(1), 5)};
        QVERIFY2(it == matrix.getConstDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstDIterator it{std::find(matrix.constDBegin(1), matrix.constDEnd(1), 4)};
        QVERIFY2(it == matrix.getConstDIterator(1, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constDEnd(1), 4);
        QVERIFY2(it == matrix.getConstDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.constDEnd(1), 4);
        QVERIFY2(it == matrix.constDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixConstDIterator it{std::find(matrix.constDBegin(1), matrix.constDEnd(1), -9)};
        QVERIFY2(it == matrix.constDEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

QTEST_APPLESS_MAIN(ConstDIteratorTests)

#include "tst_constditeratortests.moc"
