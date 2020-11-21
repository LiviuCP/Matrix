#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseNIterator = Matrix<int>::ReverseNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseNIterator = Matrix<std::string>::ReverseNIterator;

class ReverseNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseNIteratorTests();
    ~ReverseNIteratorTests();

private slots:
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testOperatorPlusEqual();
    void testOperatorMinusEqual();
    void testDifferenceOperator();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testSmallerThanOperator();
    void testSmallerThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testDereferenceAsteriskOperator();
    void testDereferenceArrowOperator();
    void testDereferenceSquareBracketsOperator();
    void testIsValidWithMatrix();
    void testPositionGetters();

    void testPassingThroughAllElements();
    void testColumnBeginEndIterators();
    void testGetNIterator();

    void testStdCount();
    void testStdFind();
    void testStdSort();
};

ReverseNIteratorTests::ReverseNIteratorTests()
{

}

ReverseNIteratorTests::~ReverseNIteratorTests()
{

}

void ReverseNIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator preIncrementIt{++it};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == 4, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator postIncrementIt{it++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.reverseNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.reverseNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.reverseNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.reverseNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseNIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -3, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.reverseNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.reverseNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        IntMatrixReverseNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 0)};

        IntMatrixReverseNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        IntMatrixReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseNIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin() + 2};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin() + (-2)};

        QVERIFY2(*firstIter == 4, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(0, 1) + 2};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(0, 1) + (-2)};

        QVERIFY2(*firstIter == 2, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd() + (-3)};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd() + (-6)};

        QVERIFY2(*firstIter == -3, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNBegin() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNBegin() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNBegin() + 6, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNBegin() + 7, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNEnd() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNEnd() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNEnd() + (-7), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(2, 1) == matrix.reverseNBegin() + 0, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) == matrix.reverseNBegin() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) == matrix.reverseNBegin() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 0) == matrix.reverseNBegin() + 3, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) == matrix.reverseNBegin() + 4, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 0) == matrix.reverseNBegin() + 5, "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(2, 1) == matrix.reverseNEnd() + (-6), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) == matrix.reverseNEnd() + (-5), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) == matrix.reverseNEnd() + (-4), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 0) == matrix.reverseNEnd() + (-3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) == matrix.reverseNEnd() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 0) == matrix.reverseNEnd() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(0, 1) + 2 == matrix.getReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) + (-2) == matrix.getReverseNIterator(0, 1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 1) + 1 == matrix.getReverseNIterator(2, 0) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) + (-3) == matrix.getReverseNIterator(2, 0) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 1) + (2) == matrix.getReverseNIterator(1, 1) + (1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(1, 1) + (-2) == matrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) + (-1) == matrix.reverseNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) + 5 == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) + 6 == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseNBegin() + (-1) == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() + 1 == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() + 1 == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() + (-1) == matrix.reverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixReverseNIterator it{};
        IntMatrixReverseNIterator firstIter{it + (-1)};
        IntMatrixReverseNIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
    }
}

void ReverseNIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin() - (-2)};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin() - 2};

        QVERIFY2(*firstIter == 4, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(0, 1) - (-2)};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(0, 1) - 2};

        QVERIFY2(*firstIter == 2, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd() - 3};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd() - 6};

        QVERIFY2(*firstIter == -3, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNBegin() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNBegin() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNBegin() - (-6), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNBegin() - (-7), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNEnd() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() == matrix.reverseNEnd() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNEnd() - 7, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(2, 1) == matrix.reverseNBegin() - 0, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) == matrix.reverseNBegin() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) == matrix.reverseNBegin() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 0) == matrix.reverseNBegin() - (-3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) == matrix.reverseNBegin() - (-4), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 0) == matrix.reverseNBegin() - (-5), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(2, 1) == matrix.reverseNEnd() - 6, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) == matrix.reverseNEnd() - 5, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) == matrix.reverseNEnd() - 4, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 0) == matrix.reverseNEnd() - 3, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) == matrix.reverseNEnd() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 0) == matrix.reverseNEnd() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(1, 1) - (-2) == matrix.getReverseNIterator(2, 0), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(2, 0) - 2 == matrix.getReverseNIterator(1, 1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) - (-2) == matrix.getReverseNIterator(0, 0) + (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(0, 1) - (-2) == matrix.getReverseNIterator(1, 1) + (3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 0) - 1 == matrix.getReverseNIterator(0, 0) + (-2), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseNIterator(1, 1) - 2 == matrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) - 1 == matrix.reverseNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) - (-5) == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseNIterator(1, 1) - (-6) == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseNBegin() - 1 == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNBegin() - (-1) == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() - (-1) == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseNEnd() - 1 == matrix.reverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixReverseNIterator it{};
        IntMatrixReverseNIterator firstIter{it - 1};
        IntMatrixReverseNIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
    }
}

void ReverseNIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 4, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(0, 1)};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(0, 1)};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 2, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        firstIter += -3;
        secondIter += -6;

        QVERIFY2(*firstIter == -3, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it;

        it = matrix.reverseNBegin(); it  += -2; QVERIFY2(it == matrix.reverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += -1; QVERIFY2(it == matrix.reverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 6; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 7; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += 1; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += 2; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -7; QVERIFY2(it == matrix.reverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.reverseNBegin(); it += 0; QVERIFY2(it == matrix.getReverseNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 1; QVERIFY2(it == matrix.getReverseNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 2; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 3; QVERIFY2(it == matrix.getReverseNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 4; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 5; QVERIFY2(it == matrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.reverseNEnd(); it += -6; QVERIFY2(it == matrix.getReverseNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -5; QVERIFY2(it == matrix.getReverseNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -4; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -3; QVERIFY2(it == matrix.getReverseNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -2; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -1; QVERIFY2(it == matrix.getReverseNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getReverseNIterator(0, 1); it += 2; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(1, 0); it += -2; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(2, 1); it += 1; QVERIFY2(it == matrix.getReverseNIterator(2, 0) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(1, 0); it += -3; QVERIFY2(it == matrix.getReverseNIterator(2, 0) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(2, 1); it += 2; QVERIFY2(it == matrix.getReverseNIterator(1, 1) + (1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getReverseNIterator(1, 1); it += -2; QVERIFY2(it == matrix.reverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(1, 1); it += -1; QVERIFY2(it == matrix.reverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(1, 1); it += 5; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getReverseNIterator(1, 1); it += 6; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixReverseNIterator it;

        it = matrix.reverseNBegin(); it += -1; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNBegin(); it += 1; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += 1; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.reverseNEnd(); it += -1; QVERIFY2(it == matrix.reverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixReverseNIterator it{};
        IntMatrixReverseNIterator firstIter{it};
        IntMatrixReverseNIterator secondIter{it};

        firstIter += -1;
        secondIter += 1;

        QVERIFY2(firstIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
    }
}

void ReverseNIteratorTests::testOperatorMinusEqual()
{
    {
        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
            IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 4, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(0, 1)};
            IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(0, 1)};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 2, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
            IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

            firstIter -= 3;
            secondIter -= 6;

            QVERIFY2(*firstIter == -3, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
            IntMatrixReverseNIterator it;

            it = matrix.reverseNBegin(); it  -= 2; QVERIFY2(it == matrix.reverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= 1; QVERIFY2(it == matrix.reverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -6; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -7; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= -1; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= -2; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 7; QVERIFY2(it == matrix.reverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.reverseNBegin(); it -= 0; QVERIFY2(it == matrix.getReverseNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -1; QVERIFY2(it == matrix.getReverseNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -2; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -3; QVERIFY2(it == matrix.getReverseNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -4; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -5; QVERIFY2(it == matrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.reverseNEnd(); it -= 6; QVERIFY2(it == matrix.getReverseNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 5; QVERIFY2(it == matrix.getReverseNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 4; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 3; QVERIFY2(it == matrix.getReverseNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 2; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 1; QVERIFY2(it == matrix.getReverseNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getReverseNIterator(0, 1); it -= -2; QVERIFY2(it == matrix.getReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(1, 0); it -= 2; QVERIFY2(it == matrix.getReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(2, 1); it -= -1; QVERIFY2(it == matrix.getReverseNIterator(2, 0) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(1, 0); it -= 3; QVERIFY2(it == matrix.getReverseNIterator(2, 0) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(2, 1); it -= -2; QVERIFY2(it == matrix.getReverseNIterator(1, 1) + (1), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getReverseNIterator(1, 1); it -= 2; QVERIFY2(it == matrix.reverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(1, 1); it -= 1; QVERIFY2(it == matrix.reverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(1, 1); it -= -5; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getReverseNIterator(1, 1); it -= -6; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrix matrix{};
            IntMatrixReverseNIterator it;

            it = matrix.reverseNBegin(); it -= 1; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNBegin(); it -= -1; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= -1; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.reverseNEnd(); it -= 1; QVERIFY2(it == matrix.reverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrixReverseNIterator it{};
            IntMatrixReverseNIterator firstIter{it};
            IntMatrixReverseNIterator secondIter{it};

            firstIter -= 1;
            secondIter -= -1;

            QVERIFY2(firstIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
            QVERIFY2(secondIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
        }
    }
}

void ReverseNIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.reverseNEnd() - matrix.reverseNBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNBegin() - matrix.reverseNEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNBegin() - matrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNEnd() - matrix.reverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseNIterator(1, 0) - matrix.getReverseNIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseNIterator(0, 1) - matrix.getReverseNIterator(1, 0) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseNIterator(2, 0) - matrix.reverseNBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNBegin() - matrix.getReverseNIterator(2, 0) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseNIterator(1, 1) - matrix.reverseNEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNEnd() - matrix.getReverseNIterator(1, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseNIterator(2, 0) - matrix.getReverseNIterator(2, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseNEnd() - matrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNEnd() - matrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNBegin() - matrix.reverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseNEnd() - matrix.reverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixReverseNIterator firstIter{};
        IntMatrixReverseNIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ReverseNIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.reverseNBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.reverseNEnd(), "The two iterators are not equal");

        secondIter = matrix.reverseNEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(2, 1)};

        QVERIFY2(it == matrix.reverseNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(5)};

        QVERIFY2(it == matrix.reverseNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(2, 1)};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.reverseNBegin() == matrix.reverseNColumnBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.reverseNColumnEnd(1) == matrix.reverseNColumnBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.reverseNColumnEnd(0) == matrix.reverseNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.reverseNColumnBegin(1) == matrix.getReverseNIterator(1, 1), "The two iterators are not equal");
        QVERIFY2(matrix.reverseNColumnEnd(1) == matrix.getReverseNIterator(1, 0), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.reverseNColumnBegin(1) == matrix.getReverseNIterator(3), "The two iterators are not equal");
        QVERIFY2(matrix.reverseNColumnEnd(1) == matrix.getReverseNIterator(1), "The two iterators are not equal");
    }
}

void ReverseNIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        QVERIFY2(matrix.reverseNBegin() != matrix.reverseNEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.reverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(1, 1)};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(0, 0)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.reverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12}};

        QVERIFY2(matrix.reverseNColumnBegin(2) != matrix.reverseNColumnBegin(1), "The matrix begin iterator of the first column equals the begin iterator of the second column");
        QVERIFY2(matrix.reverseNColumnEnd(2) != matrix.reverseNColumnEnd(1), "The matrix end iterator of the first column equals the end iterator of the second column");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.getReverseNIterator(1)};
        IntMatrixReverseNIterator secondIter{matrix.getReverseNIterator(4)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.reverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseNEnd(), "The second iterator equals the end iterator");
    }
}

void ReverseNIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.reverseNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.reverseNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.reverseNBegin() < matrix.getReverseNIterator(1, 3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 3) < matrix.reverseNColumnBegin(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(2) < matrix.getReverseNIterator(0, 2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(0, 2) < matrix.reverseNColumnEnd(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(2) < matrix.getReverseNIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 1) < matrix.reverseNColumnBegin(0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(0) < matrix.reverseNEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ReverseNIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.reverseNBegin() <= matrix.getReverseNIterator(2, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(2, 3) <= matrix.getReverseNIterator(1, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 3) <= matrix.reverseNColumnBegin(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(2) <= matrix.getReverseNIterator(2, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(2, 2) <= matrix.reverseNColumnEnd(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(2) <= matrix.getReverseNIterator(2, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(2, 1) <= matrix.reverseNColumnBegin(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(0) <= matrix.getReverseNIterator(2, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(2, 0) <= matrix.reverseNColumnEnd(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(0) <= matrix.reverseNEnd(), "The first iterator is greater than the second iterator");
    }
}

void ReverseNIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.reverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.reverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.reverseNEnd() > matrix.reverseNColumnBegin(0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(0) > matrix.getReverseNIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 1) > matrix.reverseNColumnEnd(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(2) > matrix.getReverseNIterator(1, 2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 2) > matrix.reverseNColumnBegin(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(2) > matrix.getReverseNIterator(1, 3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 3) > matrix.reverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.reverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator firstIter{matrix.reverseNEnd()};
        IntMatrixReverseNIterator secondIter{matrix.reverseNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.reverseNEnd() >= matrix.reverseNColumnEnd(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(0) >= matrix.getReverseNIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(0, 0) >= matrix.reverseNColumnBegin(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(0) >= matrix.getReverseNIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(0, 1) >= matrix.reverseNColumnEnd(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseNColumnEnd(2) >= matrix.getReverseNIterator(1, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(1, 2) >= matrix.reverseNColumnBegin(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseNColumnBegin(2) >= matrix.getReverseNIterator(2, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(2, 2) >= matrix.getReverseNIterator(0, 3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseNIterator(0, 3) >= matrix.reverseNBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ReverseNIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator readIter{matrix.reverseNBegin()};

        matrix.at(0, 1) = 10;
        ++readIter;
        ++readIter;

        QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator writeIter{matrix.reverseNBegin()};

        ++writeIter;
        ++writeIter;
        *writeIter = 10;

        QVERIFY2(matrix.at(0, 1) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void ReverseNIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
        StringMatrixReverseNIterator readIter{matrix.reverseNBegin()};

        ++readIter;

        QVERIFY2(readIter->size() == 4, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
        StringMatrixReverseNIterator writeIter{matrix.reverseNBegin()};

        ++writeIter;
        ++writeIter;

        writeIter->assign("abcdefghi");

        QVERIFY2(matrix.at(0, 1) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void ReverseNIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator firstReadIter{matrix.reverseNBegin()};
        IntMatrixReverseNIterator secondReadIter{matrix.getReverseNIterator(2, 0)};
        IntMatrixReverseNIterator thirdReadIter{matrix.reverseNEnd()};

        QVERIFY2(firstReadIter[0] == 6 && firstReadIter[1] == -5 && firstReadIter[2] == 4 && firstReadIter[3] == -3 && firstReadIter[4] == 2 && firstReadIter[5] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(secondReadIter[-3] == 6 && secondReadIter[-2] == -5 && secondReadIter[-1] == 4 && secondReadIter[0] == -3 && secondReadIter[1] == 2 && secondReadIter[2] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(thirdReadIter[-6] == 6 && thirdReadIter[-5] == -5 && thirdReadIter[-4] == 4 && thirdReadIter[-3] == -3 && thirdReadIter[-2] == 2 && thirdReadIter[-1] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator writeIter{matrix.reverseNBegin()};

        writeIter[0] = 7;
        writeIter[2] = -8;
        writeIter[5] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -3 && matrix.at(0, 1) == -8 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator writeIter{matrix.getReverseNIterator(2, 0)};

        writeIter[-3] = 7;
        writeIter[0] = -8;
        writeIter[2] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -8 && matrix.at(0, 1) == 4 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixReverseNIterator writeIter{matrix.reverseNEnd()};

        writeIter[-6] = 7;
        writeIter[-3] = -8;
        writeIter[-1] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -8 && matrix.at(0, 1) == 4 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }
}

void ReverseNIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, {7, -9, -11, 8, 10, 12}};
        IntMatrixReverseNIterator it{firstMatrix.getReverseNIterator(0, 1)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 1)};

        matrix.resize(3, 2);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 1)};

        matrix.resizeWithValue(4, 2, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 1)};

        matrix.resizeWithValue(3, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(0, 1)};

        matrix.resizeWithValue(5, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixReverseNIterator it{firstMatrix.getReverseNIterator(0, 1)};

        secondMatrix = std::move(firstMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
        QVERIFY2(it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (true)");

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixReverseNIterator it{firstMatrix.getReverseNIterator(0, 1)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixReverseNIterator it{firstMatrix.getReverseNIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ReverseNIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrix secondMatrix{3, 2, {7, 10, 8, -11, -9, 12}};

    IntMatrixReverseNIterator it{firstMatrix.getReverseNIterator(0, 1)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixReverseNIterator newIt{firstMatrix.getReverseNIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ReverseNIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixReverseNIterator it{matrix.reverseNBegin()}; it != matrix.reverseNEnd(); ++it)
        {
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int count{0};
        int sum{0};

        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        while (it != matrix.reverseNBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int sum{0};

        for (IntMatrixReverseNIterator it{matrix.reverseNBegin()}; it != matrix.reverseNEnd(); ++it)
        {
            if (*it < 0)
            {
                *it *= -1;
            }
            sum += *it;
        }

        QVERIFY2(sum == 78, "Passing through through all matrix elements by using the iterator and calculating their absolute values does not work correctly, sum of the absolute values is not correct");
    }

    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int sum{0};

        IntMatrixReverseNIterator it{matrix.reverseNEnd()};

        while (it != matrix.reverseNBegin())
        {
            --it;
            if (*it < 0)
            {
                *it *= -1;
            }
            sum += *it;
        }

        QVERIFY2(sum == 78, "Passing through through all matrix elements by using the iterator and calculating their absolute values does not work correctly, sum of the absolute values is not correct");
    }
}

void ReverseNIteratorTests::testColumnBeginEndIterators()
{
    IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

    IntMatrixReverseNIterator firstColumnBeginIter{matrix.reverseNColumnBegin(0)};
    IntMatrixReverseNIterator thirdColumnEndIter{matrix.reverseNColumnEnd(2)};

    QVERIFY2(*firstColumnBeginIter == 2, "The matrix begin ZIterator of the first column does not point to the right element");
    QVERIFY2(*thirdColumnEndIter == 4, "The matrix end ZIterator of the second column does not point to the right element");
}

void ReverseNIteratorTests::testGetNIterator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(1, 0)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixReverseNIterator it{matrix.getReverseNIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseNIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(matrix.reverseNBegin(), matrix.reverseNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.reverseNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(4, 1), matrix.getReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(0, 2), matrix.getReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(0, 2), matrix.getReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(4, 1), matrix.getReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.getReverseNIterator(3, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(3, 2), matrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.getReverseNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(2, 2), matrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(9), matrix.getReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(10), matrix.getReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(9), matrix.getReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(10), matrix.getReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.getReverseNIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(13), matrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.getReverseNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseNIterator(12), matrix.reverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnEnd(3), matrix.reverseNColumnBegin(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnBegin(3), matrix.reverseNColumnEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnBegin(3), matrix.reverseNColumnEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnEnd(1), matrix.reverseNEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNColumnBegin(2), matrix.reverseNEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseNBegin(), matrix.reverseNColumnBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ReverseNIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        IntMatrixReverseNIterator it{find(matrix.reverseNBegin(), matrix.reverseNEnd(), 4)};

        ++it;

        QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNEnd(), 10) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

        IntMatrixReverseNIterator it{matrix.reverseNBegin()};

        while(it != matrix.reverseNEnd())
        {
            it = find(it, matrix.reverseNEnd(), 9);

            if (it != matrix.reverseNEnd())
            {
                *it = 10;
            }
        }

        int expectedNumber{std::count(matrix.reverseNBegin(), matrix.reverseNEnd(), 10)};

        QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, -2, 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNEnd(), 5) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNEnd(), 10) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 6) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 5) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 8) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), -1) == matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 1) == matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNColumnEnd(1), 10) == matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNEnd(), 6) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNEnd(), -1) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNEnd(), 3) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNEnd(), -2) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseNColumnBegin(1), matrix.reverseNEnd(), 10) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 11) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 5) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 0) != matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 1) == matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.reverseNColumnEnd(1), 10) == matrix.reverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), 7) != matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), -7) != matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), -2) != matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), -1) == matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), 11) == matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1), 10) == matrix.getReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getReverseNIterator(3, 1), matrix.reverseNEnd(), 0) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(3, 1), matrix.reverseNEnd(), -1) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(3, 1), matrix.reverseNEnd(), 4) != matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(3, 1), matrix.reverseNEnd(), 11) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseNIterator(3, 1), matrix.reverseNEnd(), 10) == matrix.reverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 3), 11) != matrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 3), 2) != matrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 3), 9) != matrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 3), 0) == matrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 3), 10) == matrix.getReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    }
}

void ReverseNIteratorTests::testStdSort()
{
    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

        std::sort(matrix.reverseNBegin(), matrix.reverseNEnd());

        QVERIFY2(matrix.at(0, 0) == 11 && matrix.at(1, 0) == 9 && matrix.at(2, 0) == 9 && matrix.at(3, 0) == 9 && matrix.at(4, 0) == 8 &&
                 matrix.at(0, 1) ==  8 && matrix.at(1, 1) ==  7 && matrix.at(2, 1) ==  6 && matrix.at(3, 1) == 5 && matrix.at(4, 1) == 4 &&
                 matrix.at(0, 2) ==  3 && matrix.at(1, 2) ==  2 && matrix.at(2, 2) ==  2 && matrix.at(3, 2) == 2 && matrix.at(4, 2) == 1 &&
                 matrix.at(0, 3) ==  1 && matrix.at(1, 3) ==  0 && matrix.at(2, 3) ==  -1 && matrix.at(3, 3) == -2 && matrix.at(4, 3) == -7,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{5, 4, {
                                    -1, 5,  2, -7,
                                     1, 9, -2,  7,
                                     3, 8,  2,  2,
                                     1, 0,  8,  9,
                                     4, 6,  9,  11
                               }};

        for (int col{0}; col<matrix.getNrOfColumns(); ++col)
        {
            std::sort(matrix.reverseNColumnBegin(col), matrix.reverseNColumnEnd(col));
        }

        QVERIFY2(matrix.at(0, 0) == 4 && matrix.at(1, 0) == 3 && matrix.at(2, 0) == 1 && matrix.at(3, 0) == 1 && matrix.at(4, 0) == -1 &&
                 matrix.at(0, 1) ==  9 && matrix.at(1, 1) == 8 && matrix.at(2, 1) == 6 && matrix.at(3, 1) == 5 && matrix.at(4, 1) == 0 &&
                 matrix.at(0, 2) == 9 && matrix.at(1, 2) == 8 && matrix.at(2, 2) == 2 && matrix.at(3, 2) == 2 && matrix.at(4, 2) == -2 &&
                 matrix.at(0, 3) == 11 && matrix.at(1, 3) == 9 && matrix.at(2, 3) == 7 && matrix.at(3, 3) == 2 && matrix.at(4, 3) == -7,

                 "The iterator objects don't work correctly, the per column sorting has not been done properly");

    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, (7), 3, 8, 2, 2, 1, (0), 8, 9, 4, 6, 9, 11}};

        std::sort(matrix.getReverseNIterator(1, 3), matrix.getReverseNIterator(3, 1));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 1   && matrix.at(2, 0) == 3 && matrix.at(3, 0) == 1    && matrix.at(4, 0) ==  4 &&
                 matrix.at(0, 1) ==  5 && matrix.at(1, 1) == 9   && matrix.at(2, 1) == 8 && matrix.at(3, 1) == (0) && matrix.at(4, 1) == 9 &&
                 matrix.at(0, 2) ==  8 && matrix.at(1, 2) == 7   && matrix.at(2, 2) == 6 && matrix.at(3, 2) == 2    && matrix.at(4, 2) ==  2 &&
                 matrix.at(0, 3) ==  -2 && matrix.at(1, 3) == (-7) && matrix.at(2, 3) == 2 && matrix.at(3, 3) == 9    && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{5, 4, {(-1), 5, 2, -7,  1, 9, (-2), 7,  3, 8, 2, 2,  1, 0, 8, 9,  4, 6, 9, 11}};

        std::sort(matrix.reverseNBegin(), matrix.getReverseNIterator(1, 2));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 1    && matrix.at(2, 0) == 3 && matrix.at(3, 0) == 1 && matrix.at(4, 0) == 4 &&
                 matrix.at(0, 1) ==  5 && matrix.at(1, 1) == 9    && matrix.at(2, 1) == 8 && matrix.at(3, 1) == 0 && matrix.at(4, 1) == 6 &&
                 matrix.at(0, 2) ==  2 && matrix.at(1, 2) == (-2) && matrix.at(2, 2) == 11 && matrix.at(3, 2) == 9 && matrix.at(4, 2) == 9 &&
                 matrix.at(0, 3) == 8 && matrix.at(1, 3) == 7    && matrix.at(2, 3) == 2 && matrix.at(3, 3) == 2 && matrix.at(4, 3) == -7,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, (-2), 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        std::sort(matrix.getReverseNIterator(1, 2), matrix.reverseNEnd());

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(1, 0) == 8    && matrix.at(2, 0) == 6  && matrix.at(3, 0) == 5 && matrix.at(4, 0) == 4 &&
                 matrix.at(0, 1) ==  3 && matrix.at(1, 1) == 2    && matrix.at(2, 1) == 1  && matrix.at(3, 1) == 1 && matrix.at(4, 1) == 0 &&
                 matrix.at(0, 2) ==  -1 && matrix.at(1, 2) == (-2) && matrix.at(2, 2) == 2 && matrix.at(3, 2) == 8 && matrix.at(4, 2) == 9 &&
                 matrix.at(0, 3) ==  -7 && matrix.at(1, 3) == 7    && matrix.at(2, 3) == 2  && matrix.at(3, 3) == 9 && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }
}

QTEST_APPLESS_MAIN(ReverseNIteratorTests)

#include "tst_reverseniteratortests.moc"

