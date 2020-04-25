#define ERROR_CHECKING

#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixDIterator = Matrix<int>::DIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixDIterator = Matrix<std::string>::DIterator;

class DIteratorTests : public QObject
{
    Q_OBJECT

public:
    DIteratorTests();
    ~DIteratorTests();

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

DIteratorTests::DIteratorTests()
{

}

DIteratorTests::~DIteratorTests()
{

}

void DIteratorTests::testIteratorCreation()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-2)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == -2  && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(1)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(0, 0)};

        QVERIFY2(it.getCurrentRowNr() == 3 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 4 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 3, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(1, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 3 && it.getDiagonalNr() == 1 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 0)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(0, 2)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 1)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 2)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(-1, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 1 && it.getCurrentColumnNr() == 0 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 0, true)};

        QVERIFY2(it.getCurrentRowNr() == 0 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 2 && it.getDiagonalIndex() == 0, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(-1, 1, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 1 && it.getDiagonalNr() == -1 && it.getDiagonalIndex() == 1, "The iterator has not been correctly created");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(0, 2, true)};

        QVERIFY2(it.getCurrentRowNr() == 2 && it.getCurrentColumnNr() == 2 && it.getDiagonalNr() == 0 && it.getDiagonalIndex() == 2, "The iterator has not been correctly created");
    }
}

void DIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 2)};

        QVERIFY2(it == it, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(1, 2)};
        IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dBegin(-1)};
        IntMatrixDIterator secondIt{matrix.dBegin(2, 1)};
        IntMatrixDIterator thirdIt{matrix.getDIterator(1, 0)};
        IntMatrixDIterator fourthIt{matrix.getDIterator(-1, 0, true)};

        QVERIFY2(firstIt == secondIt && secondIt == thirdIt && thirdIt == fourthIt, "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dEnd(2)};
        IntMatrixDIterator secondIt{matrix.dEnd(0, 2)};

        QVERIFY2(firstIt == secondIt, "The iterators are not equal");
    }
}

void DIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 2)};

        QVERIFY2(!(it != it), "The iterators are not equal");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(1, 2)};
        IntMatrixDIterator secondIt{matrix.getDIterator(1, 0, true)};

        QVERIFY2(firstIt != secondIt, "The iterators are not equal");
    }
}

void DIteratorTests::testSmallerThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixDIterator firstIt{matrix.dBegin(1)};
    IntMatrixDIterator secondIt{matrix.getDIterator(1, 2)};
    IntMatrixDIterator thirdIt{matrix.dEnd(1)};

    QVERIFY2(firstIt < secondIt && secondIt < thirdIt, "The smaller than operator doesn't work correctly");
}

void DIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 2)};

        QVERIFY2(it <= it, "The smaller than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dBegin(-1)};
        IntMatrixDIterator secondIt{matrix.getDIterator(1, 0)};
        IntMatrixDIterator thirdIt{matrix.getDIterator(2, 1)};
        IntMatrixDIterator fourthIt{matrix.getDIterator(-1, 1, true)};
        IntMatrixDIterator fifthIt{matrix.dEnd(-1)};

        QVERIFY2(firstIt <= secondIt && secondIt <= thirdIt && thirdIt <= fourthIt && fourthIt <= fifthIt, "The smaller than or equal operator doesn't work correctly");
    }
}

void DIteratorTests::testGreaterThanOperator()
{
    IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
    IntMatrixDIterator firstIt{matrix.dBegin(1)};
    IntMatrixDIterator secondIt{matrix.getDIterator(1, 2)};
    IntMatrixDIterator thirdIt{matrix.dEnd(1)};

    QVERIFY2(thirdIt > secondIt && secondIt > firstIt, "The greater than operator doesn't work correctly");
}

void DIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 2)};

        QVERIFY2(it >= it, "The greater than or equal operator doesn't work correctly");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dBegin(-1)};
        IntMatrixDIterator secondIt{matrix.getDIterator(1, 0)};
        IntMatrixDIterator thirdIt{matrix.getDIterator(2, 1)};
        IntMatrixDIterator fourthIt{matrix.getDIterator(-1, 1, true)};
        IntMatrixDIterator fifthIt{matrix.dEnd(-1)};

        QVERIFY2(fifthIt >= fourthIt && fourthIt >= thirdIt && thirdIt >= secondIt && secondIt >= firstIt, "The greater than or equal operator doesn't work correctly");
    }
}

void DIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.getDIterator(2, 1) && preIncrementIt == matrix.getDIterator(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator prePreIncrementIt{++(++it)};

        QVERIFY2(it == matrix.getDIterator(2, 1) && prePreIncrementIt == matrix.getDIterator(3, 2),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postIncrementIt == matrix.getDIterator(1, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator postPostIncrementIt{(it++)++};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postPostIncrementIt == matrix.getDIterator(1, 0),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator prePostIncrementIt{(++it)++};

        QVERIFY2(it == matrix.getDIterator(2, 1) && prePostIncrementIt == matrix.getDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator postPreIncrementIt{++(it++)};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postPreIncrementIt == matrix.getDIterator(2, 1),
                 "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.dEnd(2, 1) && preIncrementIt == matrix.dEnd(2, 1),
                 "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.dEnd(2, 1) && postIncrementIt == matrix.dEnd(2, 1),
                 "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void DIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getDIterator(3, 2) && preDecrementIt == matrix.getDIterator(3, 2),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getDIterator(2, 1) && preDecrementIt == matrix.getDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getDIterator(3, 2) && prePreDecrementIt == matrix.getDIterator(2, 1),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator prePreDecrementIt{--(--it)};

        QVERIFY2(it == matrix.getDIterator(2, 1) && prePreDecrementIt == matrix.getDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }


    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getDIterator(3, 2) && postDecrementIt == matrix.dEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postDecrementIt == matrix.getDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getDIterator(3, 2) && postPostDecrementIt == matrix.dEnd(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator postPostDecrementIt{(it--)--};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postPostDecrementIt == matrix.getDIterator(3, 2),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getDIterator(3, 2) && prePostDecrementIt == matrix.getDIterator(3, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator prePostDecrementIt{(--it)--};

        QVERIFY2(it == matrix.getDIterator(2, 1) && prePostDecrementIt == matrix.getDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(-1)};
        IntMatrixDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getDIterator(3, 2) && postPreDecrementIt == matrix.getDIterator(3, 2),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(3, 2)};
        IntMatrixDIterator postPreDecrementIt{--(it--)};

        QVERIFY2(it == matrix.getDIterator(2, 1) && postPreDecrementIt == matrix.getDIterator(2, 1),
                 "The pre- and post-decrement operator do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator preDecrementIt{--it};

        QVERIFY2(it == matrix.getDIterator(1, 0) && preDecrementIt == matrix.getDIterator(1, 0),
                 "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(-1)};
        IntMatrixDIterator postDecrementIt{it--};

        QVERIFY2(it == matrix.getDIterator(1, 0) && postDecrementIt == matrix.getDIterator(1, 0),
                 "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void DIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dBegin(-1)};
        IntMatrixDIterator it2{it1 + (-1)};
        IntMatrixDIterator it3{it1 + 2};
        IntMatrixDIterator it4{it1 + 3};
        IntMatrixDIterator it5{it1 + 4};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.getDIterator(3, 2) && it4 == matrix.dEnd(1, 0) && it5 == matrix.dEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.getDIterator(-1, 1, true)};
        IntMatrixDIterator it2{it1 + (-2)};
        IntMatrixDIterator it3{it1 + (-1)};
        IntMatrixDIterator it4{it1 + (0)};
        IntMatrixDIterator it5{it1 + 1};
        IntMatrixDIterator it6{it1 + 2};
        IntMatrixDIterator it7{it1 + 3};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(2, 1) && it5 == matrix.getDIterator(3, 2) &&
                 it6 == matrix.dEnd(1, 0) && it7 == matrix.dEnd(1, 0), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dEnd(-1)};
        IntMatrixDIterator it2{it1 + (-4)};
        IntMatrixDIterator it3{it1 + (-3)};
        IntMatrixDIterator it4{it1 + (-1)};
        IntMatrixDIterator it5{it1 + 1};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(3, 2) && it5 == matrix.dEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it1{matrix.dBegin(0, 1)};
        IntMatrixDIterator it2{it1 + (-2)};
        IntMatrixDIterator it3{it1 + (-1)};
        IntMatrixDIterator it4{it1 + 2};
        IntMatrixDIterator it5{it1 + 3};
        IntMatrixDIterator it6{it1 + 4};
        QVERIFY2(it2 == matrix.dBegin(0, 1) && it3 == matrix.dBegin(0, 1) && it4 == matrix.getDIterator(2, 3) && it5 == matrix.dEnd(0, 1) && it6 == matrix.dEnd(0, 1),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void DIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dBegin(-1)};
        IntMatrixDIterator it2{it1 -1};
        IntMatrixDIterator it3{it1 - (-2)};
        IntMatrixDIterator it4{it1 - (-3)};
        IntMatrixDIterator it5{it1 - (-4)};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.getDIterator(3, 2) && it4 == matrix.dEnd(1, 0) && it5 == matrix.dEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.getDIterator(-1, 1, true)};
        IntMatrixDIterator it2{it1 - 2};
        IntMatrixDIterator it3{it1 - 1};
        IntMatrixDIterator it4{it1 - 0};
        IntMatrixDIterator it5{it1 - (-1)};
        IntMatrixDIterator it6{it1 - (-2)};
        IntMatrixDIterator it7{it1 - (-3)};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(2, 1) && it5 == matrix.getDIterator(3, 2) &&
                 it6 == matrix.dEnd(1, 0) && it7 == matrix.dEnd(1, 0), "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dEnd(-1)};
        IntMatrixDIterator it2{it1 - 4};
        IntMatrixDIterator it3{it1 - 3};
        IntMatrixDIterator it4{it1 - 1};
        IntMatrixDIterator it5{it1 - (-1)};

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(3, 2) && it5 == matrix.dEnd(1, 0),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it1{matrix.dBegin(0, 1)};
        IntMatrixDIterator it2{it1 -2};
        IntMatrixDIterator it3{it1 -1};
        IntMatrixDIterator it4{it1 - (-2)};
        IntMatrixDIterator it5{it1 - (-3)};
        IntMatrixDIterator it6{it1 - (-4)};
        QVERIFY2(it2 == matrix.dBegin(0, 1) && it3 == matrix.dBegin(0, 1) && it4 == matrix.getDIterator(2, 3) && it5 == matrix.dEnd(0, 1) && it6 == matrix.dEnd(0, 1),
                 "Operator + does not correctly work, the resulting iterator does not point to the right element");
    }
}

void DIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dBegin(-1)};
        IntMatrixDIterator it2{it1};
        IntMatrixDIterator it3{it1};
        IntMatrixDIterator it4{it1};
        IntMatrixDIterator it5{it1};

        it2 += -1;
        it3 += 2;
        it4 += 3;
        it5 += 4;

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.getDIterator(3, 2) && it4 == matrix.dEnd(1, 0) && it5 == matrix.dEnd(1, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.getDIterator(-1, 1, true)};
        IntMatrixDIterator it2{it1};
        IntMatrixDIterator it3{it1};
        IntMatrixDIterator it4{it1};
        IntMatrixDIterator it5{it1};
        IntMatrixDIterator it6{it1};
        IntMatrixDIterator it7{it1};

        it2 += -2;
        it3 += -1;
        it4 += 0;
        it5 += 1;
        it6 += 2;
        it7 += 3;

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(2, 1) && it5 == matrix.getDIterator(3, 2) &&
                 it6 == matrix.dEnd(1, 0) && it7 == matrix.dEnd(1, 0), "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};

        IntMatrixDIterator it1{matrix.dEnd(-1)};
        IntMatrixDIterator it2{it1};
        IntMatrixDIterator it3{it1};
        IntMatrixDIterator it4{it1};
        IntMatrixDIterator it5{it1};

        it2 += -4;
        it3 += -3;
        it4 += -1;
        it5 += 1;

        QVERIFY2(it2 == matrix.dBegin(1, 0) && it3 == matrix.dBegin(1, 0) && it4 == matrix.getDIterator(3, 2) && it5 == matrix.dEnd(1, 0),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }

    // additional test to quick check that on the positive diagonals everything is fine too
    {
        IntMatrix matrix{3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it1{matrix.dBegin(0, 1)};
        IntMatrixDIterator it2{it1};
        IntMatrixDIterator it3{it1};
        IntMatrixDIterator it4{it1};
        IntMatrixDIterator it5{it1};
        IntMatrixDIterator it6{it1};

        it2 += -2;
        it3 += -1;
        it4 += 2;
        it5 += 3;
        it6 += 4;

        QVERIFY2(it2 == matrix.dBegin(0, 1) && it3 == matrix.dBegin(0, 1) && it4 == matrix.getDIterator(2, 3) && it5 == matrix.dEnd(0, 1) && it6 == matrix.dEnd(0, 1),
                 "Operator += does not work correctly, the resulting iterator does not point to the right element");
    }
}

void DIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dBegin(-1)};
        IntMatrixDIterator secondIt{matrix.dBegin(1, 0)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.dEnd(1)};
        IntMatrixDIterator secondIt{matrix.dEnd(0, 1)};

        QVERIFY2(firstIt - secondIt == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
        IntMatrixDIterator secondIt{matrix.getDIterator(-1, 2, true)};

        QVERIFY2(secondIt - firstIt == 1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(1, 2)};
        IntMatrixDIterator secondIt{matrix.getDIterator(1, 0, true)};

        QVERIFY2(secondIt - firstIt == -1, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(-1, 0, true)};
        IntMatrixDIterator secondIt{matrix.dEnd(-1)};

        QVERIFY2(secondIt - firstIt == 3, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator firstIt{matrix.getDIterator(2, 2)};
        IntMatrixDIterator secondIt{matrix.dBegin(0, 0)};

        QVERIFY2(secondIt - firstIt == -2, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void DIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 1)};

        QVERIFY2(*it == -8, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(1, 1, true)};

        *it = 14;

        QVERIFY2(matrix.at(1, 2) == 14, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void DIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixDIterator readIter{matrix.dBegin(0, 1)};

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixDIterator writeIter{matrix.getDIterator(1, 2)};

        writeIter->assign("abcdefghij");

        QVERIFY2(*matrix.getDIterator(1, 1, true) == "abcdefghij",
                 "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void DIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(2, 1)};

        QVERIFY2(it[-1] == 4 && it[0] == -8 && it[1] == 12, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dBegin(0, 1)};

        QVERIFY2(it[0] == 2 && it[1] == 6, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.dEnd(0)};

        QVERIFY2( it[-3] == 1 && it[-2] == -5 && it[-1] == 9, "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12}};
        IntMatrixDIterator it{matrix.getDIterator(0, 1)};

        it[1] = 14;

        QVERIFY2(*matrix.getDIterator(1, 1, true) == 14, "The dereference square brackets operator doesn't work correctly");
    }
}

void DIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixDIterator it{firstMatrix.getDIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixDIterator it{matrix.getDIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixDIterator it{matrix.getDIterator(0, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixDIterator it{matrix.getDIterator(1, 1)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixDIterator it{matrix.getDIterator(1, 1, true)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixDIterator it{matrix.getDIterator(-1, 0, true)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixDIterator it{firstMatrix.getDIterator(1, 0, true)};

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
        IntMatrixDIterator it{firstMatrix.getDIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixDIterator it{firstMatrix.getDIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixDIterator it{firstMatrix.getDIterator(-1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertRow(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
        IntMatrixDIterator it{firstMatrix.getDIterator(1, 0, true)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");

        firstMatrix.insertColumn(1);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }
}

void DIteratorTests::testChangeDiagonal()
{
    IntMatrix matrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
    IntMatrixDIterator it{matrix.dBegin(1)};

    QVERIFY2(*it == 2, "The iterator does not reference the right value");

    it = matrix.getDIterator(-2, 0, true);
    QVERIFY2(it[1] == -11, "the iterator index does not reference the right value");
}

void DIteratorTests::testStdCount()
{
    {
        IntMatrix matrix(1, 2, {2, -3});

        QVERIFY2(std::count(matrix.getDIterator(0, 1), matrix.getDIterator(1, 0, true), -3) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.dBegin(1), matrix.dEnd(1), -3) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
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

        QVERIFY2(std::count(matrix.dBegin(1), matrix.dEnd(1), -1) == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getDIterator(1, 1, true), matrix.getDIterator(4, 5), 4) == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
        QVERIFY2(std::count(matrix.getDIterator(2, 3), matrix.getDIterator(1, 4, true), 4) == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
    }
}

void DIteratorTests::testStdFind()
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

        IntMatrixDIterator it{std::find(matrix.dBegin(1), matrix.dEnd(1), 5)};
        QVERIFY2(it == matrix.getDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixDIterator it{std::find(matrix.dBegin(1), matrix.dEnd(1), 4)};
        QVERIFY2(it == matrix.getDIterator(1, 2), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.dEnd(1), 4);
        QVERIFY2(it == matrix.getDIterator(3, 4), "The iterator doesn't work correctly with std::find, incorrect next element returned");

        ++it;
        it = std::find(it, matrix.dEnd(1), 4);
        QVERIFY2(it == matrix.dEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
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

        IntMatrixDIterator it{std::find(matrix.dBegin(1), matrix.dEnd(1), -9)};
        QVERIFY2(it == matrix.dEnd(1), "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }
}

void DIteratorTests::testStdSort()
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
                             1, -3, -3,  4, -5, 6, 7,
                             1,  2, -1,  4, -5, 6, 7,
                             1,  2, -3,  0, -5, 6, 7,
                             1,  2, -3,  4,  1, 6, 7,
                             1,  2, -3,  4, -5, 2, 7,
                             1,  2, -3,  4, -5, 6, 5,
                         });

        std::sort(matrix.dBegin(1), matrix.dEnd(1));

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
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2,  0,  4, -5,  6, 7,
                             1,  2, -3,  1, -5,  6, 7,
                             1,  2, -3,  4,  5,  6, 7,
                             1,  2, -3,  4, -5, -3, 7,
                             1,  2, -3,  4, -5,  6, 2,
                         });

        std::sort(matrix.getDIterator(1, 2), matrix.getDIterator(4, 5));

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
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2,  0,  4, -5,  6, 7,
                             1,  2, -3,  1, -5,  6, 7,
                             1,  2, -3,  4,  5,  6, 7,
                             1,  2, -3,  4, -5, -3, 7,
                             1,  2, -3,  4, -5,  6, 2,
                         });

        std::sort(matrix.dBegin(1), matrix.getDIterator(4, 5));

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
                             1, -1, -3,  4, -5,  6, 7,
                             1,  2, -3,  4, -5,  6, 7,
                             1,  2, -3,  0, -5,  6, 7,
                             1,  2, -3,  4,  1,  6, 7,
                             1,  2, -3,  4, -5,  2, 7,
                             1,  2, -3,  4, -5,  6, 5,
                         });

        std::sort(matrix.getDIterator(1, 2), matrix.dEnd(1));

        QVERIFY2(matrix == matrixRef, "The iterator doesn't work correctly, the matrix diagonal has not been sorted properly");
    }
}

QTEST_APPLESS_MAIN(DIteratorTests)

#include "tst_diteratortests.moc"
