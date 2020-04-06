#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixReverseZIterator = Matrix<int>::ReverseZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixReverseZIterator = Matrix<std::string>::ReverseZIterator;

class ReverseZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ReverseZIteratorTests();
    ~ReverseZIteratorTests();

private slots:
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
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
    void testRowBeginEndIterators();
    void testGetZIterator();

    void testStdCount();
    void testStdFind();
    void testStdSort();
};

ReverseZIteratorTests::ReverseZIteratorTests()
{

}

ReverseZIteratorTests::~ReverseZIteratorTests()
{

}

void ReverseZIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator preIncrementIt{++it};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == 4, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator postIncrementIt{it++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.reverseZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.reverseZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.reverseZEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.reverseZEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseZIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -3, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.reverseZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.reverseZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        IntMatrixReverseZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 0)};

        IntMatrixReverseZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        IntMatrixReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ReverseZIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin() + 2};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin() + (-2)};

        QVERIFY2(*firstIter == 4, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.getReverseZIterator(1, 0) + 2};
        IntMatrixReverseZIterator secondIter{matrix.getReverseZIterator(1, 0) + (-2)};

        QVERIFY2(*firstIter == 2, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd() + (-3)};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd() + (-6)};

        QVERIFY2(*firstIter == -3, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZBegin() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZBegin() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZBegin() + 6, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZBegin() + 7, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZEnd() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZEnd() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZEnd() + (-7), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 2) == matrix.reverseZBegin() + 0, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) == matrix.reverseZBegin() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) == matrix.reverseZBegin() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 2) == matrix.reverseZBegin() + 3, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) == matrix.reverseZBegin() + 4, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 0) == matrix.reverseZBegin() + 5, "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 2) == matrix.reverseZEnd() + (-6), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) == matrix.reverseZEnd() + (-5), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) == matrix.reverseZEnd() + (-4), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 2) == matrix.reverseZEnd() + (-3), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) == matrix.reverseZEnd() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 0) == matrix.reverseZEnd() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 0) + 2 == matrix.getReverseZIterator(0, 1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) + (-2) == matrix.getReverseZIterator(1, 0), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 2) + 1 == matrix.getReverseZIterator(0, 2) + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) + (-3) == matrix.getReverseZIterator(0, 2) + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 2) + (2) == matrix.getReverseZIterator(1, 1) + (1), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 1) + (-2) == matrix.reverseZBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) + (-1) == matrix.reverseZBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) + 5 == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) + 6 == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseZBegin() + (-1) == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() + 1 == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() + 1 == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() + (-1) == matrix.reverseZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixReverseZIterator it{};
        IntMatrixReverseZIterator firstIter{it + (-1)};
        IntMatrixReverseZIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
    }
}

void ReverseZIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin() - (-2)};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin() - 2};

        QVERIFY2(*firstIter == 4, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.getReverseZIterator(1, 0) - (-2)};
        IntMatrixReverseZIterator secondIter{matrix.getReverseZIterator(1, 0) - 2};

        QVERIFY2(*firstIter == 2, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd() - 3};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd() - 6};

        QVERIFY2(*firstIter == -3, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZBegin() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZBegin() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZBegin() - (-6), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZBegin() - (-7), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZEnd() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() == matrix.reverseZEnd() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZEnd() - 7, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 2) == matrix.reverseZBegin() - 0, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) == matrix.reverseZBegin() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) == matrix.reverseZBegin() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 2) == matrix.reverseZBegin() - (-3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) == matrix.reverseZBegin() - (-4), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 0) == matrix.reverseZBegin() - (-5), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 2) == matrix.reverseZEnd() - 6, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) == matrix.reverseZEnd() - 5, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) == matrix.reverseZEnd() - 4, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 2) == matrix.reverseZEnd() - 3, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) == matrix.reverseZEnd() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 0) == matrix.reverseZEnd() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 1) - (-2) == matrix.getReverseZIterator(0, 2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 2) - 2 == matrix.getReverseZIterator(1, 1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) - (-2) == matrix.getReverseZIterator(0, 0) + (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 0) - (-2) == matrix.getReverseZIterator(1, 1) + (3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(0, 1) - 1 == matrix.getReverseZIterator(0, 0) + (-2), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getReverseZIterator(1, 1) - 2 == matrix.reverseZBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) - 1 == matrix.reverseZBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) - (-5) == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getReverseZIterator(1, 1) - (-6) == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseZBegin() - 1 == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZBegin() - (-1) == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() - (-1) == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.reverseZEnd() - 1 == matrix.reverseZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixReverseZIterator it{};
        IntMatrixReverseZIterator firstIter{it - 1};
        IntMatrixReverseZIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
    }
}

void ReverseZIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZEnd() - matrix.reverseZBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZBegin() - matrix.reverseZEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZBegin() - matrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZEnd() - matrix.reverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseZIterator(0, 1) - matrix.getReverseZIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseZIterator(1, 0) - matrix.getReverseZIterator(0, 1) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseZIterator(0, 2) - matrix.reverseZBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZBegin() - matrix.getReverseZIterator(0, 2) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseZIterator(1, 1) - matrix.reverseZEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZEnd() - matrix.getReverseZIterator(1, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getReverseZIterator(0, 2) - matrix.getReverseZIterator(0, 2) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseZEnd() - matrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZEnd() - matrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZBegin() - matrix.reverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.reverseZEnd() - matrix.reverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixReverseZIterator firstIter{};
        IntMatrixReverseZIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ReverseZIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.reverseZBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.reverseZEnd(), "The two iterators are not equal");

        secondIter = matrix.reverseZEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 2)};

        QVERIFY2(it == matrix.reverseZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(5)};

        QVERIFY2(it == matrix.reverseZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.getReverseZIterator(1, 2)};
        IntMatrixReverseZIterator secondIter{matrix.getReverseZIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZBegin() == matrix.reverseZRowBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.reverseZRowEnd(1) == matrix.reverseZRowBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.reverseZRowEnd(0) == matrix.reverseZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZRowBegin(1) == matrix.getReverseZIterator(1, 1), "The two iterators are not equal");
        QVERIFY2(matrix.reverseZRowEnd(1) == matrix.getReverseZIterator(0, 1), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.reverseZRowBegin(1) == matrix.getReverseZIterator(3), "The two iterators are not equal");
        QVERIFY2(matrix.reverseZRowEnd(1) == matrix.getReverseZIterator(1), "The two iterators are not equal");
    }
}

void ReverseZIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        QVERIFY2(matrix.reverseZBegin() != matrix.reverseZEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.reverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.getReverseZIterator(1, 1)};
        IntMatrixReverseZIterator secondIter{matrix.getReverseZIterator(0, 0)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.reverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        QVERIFY2(matrix.reverseZRowBegin(2) != matrix.reverseZRowBegin(1), "The matrix begin iterator of the first row equals the begin iterator of the second row");
        QVERIFY2(matrix.reverseZRowEnd(2) != matrix.reverseZRowEnd(1), "The matrix end iterator of the first row equals the end iterator of the second row");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.getReverseZIterator(1)};
        IntMatrixReverseZIterator secondIter{matrix.getReverseZIterator(4)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.reverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.reverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.reverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.reverseZEnd(), "The second iterator equals the end iterator");
    }
}

void ReverseZIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.reverseZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.reverseZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.reverseZBegin() < matrix.getReverseZIterator(3, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(3, 1) < matrix.reverseZRowBegin(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(2) < matrix.getReverseZIterator(2, 0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(2, 0) < matrix.reverseZRowEnd(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(2) < matrix.getReverseZIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(1, 1) < matrix.reverseZRowBegin(0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(0) < matrix.reverseZEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ReverseZIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.reverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.reverseZBegin() <= matrix.getReverseZIterator(3, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(3, 2) <= matrix.getReverseZIterator(3, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(3, 1) <= matrix.reverseZRowBegin(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(2) <= matrix.getReverseZIterator(2, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(2, 2) <= matrix.reverseZRowEnd(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(2) <= matrix.getReverseZIterator(1, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(1, 2) <= matrix.reverseZRowBegin(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(0) <= matrix.getReverseZIterator(0, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(0, 2) <= matrix.reverseZRowEnd(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(0) <= matrix.reverseZEnd(), "The first iterator is greater than the second iterator");
    }
}

void ReverseZIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.reverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.reverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.reverseZEnd() > matrix.reverseZRowBegin(0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(0) > matrix.getReverseZIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(1, 1) > matrix.reverseZRowEnd(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(2) > matrix.getReverseZIterator(2, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(2, 1) > matrix.reverseZRowBegin(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(2) > matrix.getReverseZIterator(3, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getReverseZIterator(3, 1) > matrix.reverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.reverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator firstIter{matrix.reverseZEnd()};
        IntMatrixReverseZIterator secondIter{matrix.reverseZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.reverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.reverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.reverseZEnd() >= matrix.reverseZRowEnd(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(0) >= matrix.getReverseZIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(0, 0) >= matrix.reverseZRowBegin(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(0) >= matrix.getReverseZIterator(1, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(1, 0) >= matrix.reverseZRowEnd(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseZRowEnd(2) >= matrix.getReverseZIterator(2, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(2, 1) >= matrix.reverseZRowBegin(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.reverseZRowBegin(2) >= matrix.getReverseZIterator(2, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(2, 2) >= matrix.getReverseZIterator(3, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getReverseZIterator(3, 0) >= matrix.reverseZBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ReverseZIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator readIter{matrix.reverseZBegin()};

        matrix.at(1, 0) = 10;
        ++readIter;
        ++readIter;

        QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator writeIter{matrix.reverseZBegin()};

        ++writeIter;
        ++writeIter;
        *writeIter = 10;

        QVERIFY2(matrix.at(1, 0) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void ReverseZIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
        StringMatrixReverseZIterator readIter{matrix.reverseZBegin()};

        ++readIter;

        QVERIFY2(readIter->size() == 4, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixReverseZIterator writeIter{matrix.reverseZBegin()};

        ++writeIter;
        ++writeIter;

        writeIter->assign("abcdefghi");

        QVERIFY2(matrix.at(1, 0) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void ReverseZIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator firstReadIter{matrix.reverseZBegin()};
        IntMatrixReverseZIterator secondReadIter{matrix.getReverseZIterator(0, 2)};
        IntMatrixReverseZIterator thirdReadIter{matrix.reverseZEnd()};

        QVERIFY2(firstReadIter[0] == 6 && firstReadIter[1] == -5 && firstReadIter[2] == 4 && firstReadIter[3] == -3 && firstReadIter[4] == 2 && firstReadIter[5] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(secondReadIter[-3] == 6 && secondReadIter[-2] == -5 && secondReadIter[-1] == 4 && secondReadIter[0] == -3 && secondReadIter[1] == 2 && secondReadIter[2] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(thirdReadIter[-6] == 6 && thirdReadIter[-5] == -5 && thirdReadIter[-4] == 4 && thirdReadIter[-3] == -3 && thirdReadIter[-2] == 2 && thirdReadIter[-1] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator writeIter{matrix.reverseZBegin()};

        writeIter[0] = 7;
        writeIter[2] = -8;
        writeIter[5] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -3 && matrix.at(1, 0) == -8 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator writeIter{matrix.getReverseZIterator(0, 2)};

        writeIter[-3] = 7;
        writeIter[0] = -8;
        writeIter[2] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -8 && matrix.at(1, 0) == 4 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixReverseZIterator writeIter{matrix.reverseZEnd()};

        writeIter[-6] = 7;
        writeIter[-3] = -8;
        writeIter[-1] = 9;

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -8 && matrix.at(1, 0) == 4 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 7,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }
}

void ReverseZIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixReverseZIterator it{firstMatrix.getReverseZIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixReverseZIterator it{firstMatrix.getReverseZIterator(1, 0)};

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
        IntMatrixReverseZIterator it{firstMatrix.getReverseZIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixReverseZIterator it{firstMatrix.getReverseZIterator(1, 0)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ReverseZIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrix secondMatrix{2, 3, {7, 8, -9, 10, -11, 12}};

    IntMatrixReverseZIterator it{firstMatrix.getReverseZIterator(1, 0)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixReverseZIterator newIt{firstMatrix.getReverseZIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ReverseZIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it != matrix.reverseZEnd(); ++it)
        {
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        while (it != matrix.reverseZBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int sum{0};

        for (IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it != matrix.reverseZEnd(); ++it)
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
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int sum{0};

        IntMatrixReverseZIterator it{matrix.reverseZEnd()};

        while (it != matrix.reverseZBegin())
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

void ReverseZIteratorTests::testRowBeginEndIterators()
{
    IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

    IntMatrixReverseZIterator firstRowBeginIter{matrix.reverseZRowBegin(0)};
    IntMatrixReverseZIterator thirdRowEndIter{matrix.reverseZRowEnd(2)};

    QVERIFY2(*firstRowBeginIter == 2, "The matrix begin ZIterator of the first row does not point to the right element");
    QVERIFY2(*thirdRowEndIter == 4, "The matrix end ZIterator of the second row does not point to the right element");
}

void ReverseZIteratorTests::testGetZIterator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(0, 1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixReverseZIterator it{matrix.getReverseZIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ReverseZIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(matrix.reverseZBegin(), matrix.reverseZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.reverseZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(1, 4), matrix.getReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(2, 0), matrix.getReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(2, 0), matrix.getReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(1, 4), matrix.getReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.getReverseZIterator(2, 3), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(2, 3), matrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.getReverseZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(2, 2), matrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(9), matrix.getReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(10), matrix.getReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(9), matrix.getReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(10), matrix.getReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.getReverseZIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(13), matrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.getReverseZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getReverseZIterator(12), matrix.reverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowEnd(3), matrix.reverseZRowBegin(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowBegin(3), matrix.reverseZRowEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowBegin(3), matrix.reverseZRowEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowEnd(1), matrix.reverseZEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZRowBegin(2), matrix.reverseZEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.reverseZBegin(), matrix.reverseZRowBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ReverseZIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        IntMatrixReverseZIterator it{find(matrix.reverseZBegin(), matrix.reverseZEnd(), 4)};

        ++it;

        QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZEnd(), 10) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non existing value has been found in the matrix");

        IntMatrixReverseZIterator it{matrix.reverseZBegin()};

        while(it != matrix.reverseZEnd())
        {
            it = find(it, matrix.reverseZEnd(), 9);

            if (it != matrix.reverseZEnd())
            {
                *it = 10;
            }
        }

        int expectedNumber{std::count(matrix.reverseZBegin(), matrix.reverseZEnd(), 10)};

        QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZEnd(), 5) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZEnd(), 10) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 6) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 5) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 8) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), -1) == matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 1) == matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZRowEnd(1), 10) == matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZEnd(), 6) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZEnd(), -1) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZEnd(), 3) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZEnd(), -2) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseZRowBegin(1), matrix.reverseZEnd(), 10) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 11) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 5) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 0) != matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 1) == matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.reverseZRowEnd(1), 10) == matrix.reverseZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), 7) != matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), -7) != matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), -2) != matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), -1) == matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), 11) == matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3), 10) == matrix.getReverseZIterator(1, 3), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getReverseZIterator(1, 3), matrix.reverseZEnd(), 0) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(1, 3), matrix.reverseZEnd(), -1) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(1, 3), matrix.reverseZEnd(), 4) != matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(1, 3), matrix.reverseZEnd(), 11) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getReverseZIterator(1, 3), matrix.reverseZEnd(), 10) == matrix.reverseZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.reverseZBegin(), matrix.getReverseZIterator(3, 1), 11) != matrix.getReverseZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.getReverseZIterator(3, 1), 2) != matrix.getReverseZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.getReverseZIterator(3, 1), 9) != matrix.getReverseZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.getReverseZIterator(3, 1), 0) == matrix.getReverseZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.reverseZBegin(), matrix.getReverseZIterator(3, 1), 10) == matrix.getReverseZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
    }
}

void ReverseZIteratorTests::testStdSort()
{
    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        std::sort(matrix.reverseZBegin(), matrix.reverseZEnd());

        QVERIFY2(matrix.at(0, 0) == 11 && matrix.at(0, 1) == 9 && matrix.at(0, 2) == 9 && matrix.at(0, 3) == 9 && matrix.at(0, 4) == 8 &&
                 matrix.at(1, 0) ==  8 && matrix.at(1, 1) ==  7 && matrix.at(1, 2) ==  6 && matrix.at(1, 3) == 5 && matrix.at(1, 4) == 4 &&
                 matrix.at(2, 0) ==  3 && matrix.at(2, 1) ==  2 && matrix.at(2, 2) ==  2 && matrix.at(2, 3) == 2 && matrix.at(2, 4) == 1 &&
                 matrix.at(3, 0) ==  1 && matrix.at(3, 1) ==  0 && matrix.at(3, 2) ==  -1 && matrix.at(3, 3) == -2 && matrix.at(3, 4) == -7,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{4, 5, {
                                    -1,  1, 3, 1, 4,
                                     5,  9, 8, 0, 6,
                                     2, -2, 2, 8, 9,
                                    -7,  7, 2, 9, 11
                               }};

        for (int row{0}; row<matrix.getNrOfRows(); ++row)
        {
            std::sort(matrix.reverseZRowBegin(row), matrix.reverseZRowEnd(row));
        }

        QVERIFY2(matrix.at(0, 0) == 4 && matrix.at(0, 1) == 3 && matrix.at(0, 2) == 1 && matrix.at(0, 3) == 1 && matrix.at(0, 4) == -1 &&
                 matrix.at(1, 0) ==  9 && matrix.at(1, 1) == 8 && matrix.at(1, 2) == 6 && matrix.at(1, 3) == 5 && matrix.at(1, 4) == 0 &&
                 matrix.at(2, 0) == 9 && matrix.at(2, 1) == 8 && matrix.at(2, 2) == 2 && matrix.at(2, 3) == 2 && matrix.at(2, 4) == -2 &&
                 matrix.at(3, 0) == 11 && matrix.at(3, 1) == 9 && matrix.at(3, 2) == 7 && matrix.at(3, 3) == 2 && matrix.at(3, 4) == -7,

                 "The iterator objects don't work correctly, the per row sorting has not been done properly");

    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, (0), 6, 2, -2, 2, 8, 9, -7, (7), 2, 9, 11}};

        std::sort(matrix.getReverseZIterator(3, 1), matrix.getReverseZIterator(1, 3));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 1   && matrix.at(0, 2) == 3 && matrix.at(0, 3) == 1    && matrix.at(0, 4) ==  4 &&
                 matrix.at(1, 0) ==  5 && matrix.at(1, 1) == 9   && matrix.at(1, 2) == 8 && matrix.at(1, 3) == (0) && matrix.at(1, 4) == 9 &&
                 matrix.at(2, 0) ==  8 && matrix.at(2, 1) == 7   && matrix.at(2, 2) == 6 && matrix.at(2, 3) == 2    && matrix.at(2, 4) ==  2 &&
                 matrix.at(3, 0) ==  -2 && matrix.at(3, 1) == (-7) && matrix.at(3, 2) == 2 && matrix.at(3, 3) == 9    && matrix.at(3, 4) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, (11)}};

        std::sort(matrix.reverseZBegin(), matrix.getReverseZIterator(2, 1));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 1    && matrix.at(0, 2) == 3 && matrix.at(0, 3) == 1 && matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) ==  5 && matrix.at(1, 1) == 9    && matrix.at(1, 2) == 8 && matrix.at(1, 3) == 0 && matrix.at(1, 4) == 6 &&
                 matrix.at(2, 0) ==  2 && matrix.at(2, 1) == (-2) && matrix.at(2, 2) == 11 && matrix.at(2, 3) == 9 && matrix.at(2, 4) == 9 &&
                 matrix.at(3, 0) == 8 && matrix.at(3, 1) == 7    && matrix.at(3, 2) == 2 && matrix.at(3, 3) == 2 && matrix.at(3, 4) == -7,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

        std::sort(matrix.getReverseZIterator(2, 1), matrix.reverseZEnd());

        QVERIFY2(matrix.at(0, 0) == 9 && matrix.at(0, 1) == 8    && matrix.at(0, 2) == 6  && matrix.at(0, 3) == 5 && matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) ==  3 && matrix.at(1, 1) == 2    && matrix.at(1, 2) == 1  && matrix.at(1, 3) == 1 && matrix.at(1, 4) == 0 &&
                 matrix.at(2, 0) ==  -1 && matrix.at(2, 1) == (-2) && matrix.at(2, 2) == 2 && matrix.at(2, 3) == 8 && matrix.at(2, 4) == 9 &&
                 matrix.at(3, 0) ==  -7 && matrix.at(3, 1) == 7    && matrix.at(3, 2) == 2  && matrix.at(3, 3) == 9 && matrix.at(3, 4) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }
}

QTEST_APPLESS_MAIN(ReverseZIteratorTests)

#include "tst_reverseziteratortests.moc"

