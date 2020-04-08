#define ERROR_CHECKING

#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstZIterator = Matrix<int>::ConstZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstZIterator = Matrix<std::string>::ConstZIterator;

class ConstZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstZIteratorTests();
    ~ConstZIteratorTests();

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
    void testIteratingWithAuto();

    void testStdCount();
    void testStdFind();
};

ConstZIteratorTests::ConstZIteratorTests()
{

}

ConstZIteratorTests::~ConstZIteratorTests()
{

}

void ConstZIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator preIncrementIt{++it};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == -3, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator postIncrementIt{it++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.constZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constZEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.constZEnd(), "The post-increment operators does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstZIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator preDecrementIt{--it};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 4, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.constZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator postDecrementIt{it--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.constZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZEnd()};

        IntMatrixConstZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 2)};

        IntMatrixConstZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operators does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.constZBegin()};

        IntMatrixConstZIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operators does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstZIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.constZBegin() + 2};
        IntMatrixConstZIterator secondIter{matrix.constZBegin() + (-2)};

        QVERIFY2(*firstIter == -3, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.getConstZIterator(0, 2) + 2};
        IntMatrixConstZIterator secondIter{matrix.getConstZIterator(0, 2) + (-2)};

        QVERIFY2(*firstIter == -5, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.constZEnd() + (-3)};
        IntMatrixConstZIterator secondIter{matrix.constZEnd() + (-6)};

        QVERIFY2(*firstIter == 4, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZBegin() == matrix.constZBegin() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() == matrix.constZBegin() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZBegin() + 6, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZBegin() + 7, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZEnd() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZEnd() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() == matrix.constZEnd() + (-7), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 0) == matrix.constZBegin() + 0, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) == matrix.constZBegin() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) == matrix.constZBegin() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) == matrix.constZBegin() + 3, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) == matrix.constZBegin() + 4, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 2) == matrix.constZBegin() + 5, "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 0) == matrix.constZEnd() + (-6), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) == matrix.constZEnd() + (-5), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) == matrix.constZEnd() + (-4), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) == matrix.constZEnd() + (-3), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) == matrix.constZEnd() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 2) == matrix.constZEnd() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 1) + 2 == matrix.getConstZIterator(1, 0), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) + (-2) == matrix.getConstZIterator(0, 1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) + 2 == matrix.getConstZIterator(1, 2) + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) + 2 == matrix.getConstZIterator(0, 1) + (3), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) + (-1) == matrix.getConstZIterator(1, 2) + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 1) + (-2) == matrix.constZBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) + (-1) == matrix.constZBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) + 5 == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) + 6 == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constZBegin() + (-1) == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() + 1 == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() + 1 == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() + (-1) == matrix.constZEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstZIterator it{};
        IntMatrixConstZIterator firstIter{it + (-1)};
        IntMatrixConstZIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
    }
}

void ConstZIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.constZBegin() - (-2)};
        IntMatrixConstZIterator secondIter{matrix.constZBegin() - 2};

        QVERIFY2(*firstIter == -3, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.getConstZIterator(0, 2) - (-2)};
        IntMatrixConstZIterator secondIter{matrix.getConstZIterator(0, 2) - 2};

        QVERIFY2(*firstIter == -5, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstZIterator firstIter{matrix.constZEnd() - 3};
        IntMatrixConstZIterator secondIter{matrix.constZEnd() - 6};

        QVERIFY2(*firstIter == 4, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZBegin() == matrix.constZBegin() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() == matrix.constZBegin() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZBegin() - (-6), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZBegin() - (-7), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZEnd() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() == matrix.constZEnd() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() == matrix.constZEnd() - 7, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 0) == matrix.constZBegin() - 0, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) == matrix.constZBegin() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) == matrix.constZBegin() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) == matrix.constZBegin() - (-3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) == matrix.constZBegin() - (-4), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 2) == matrix.constZBegin() - (-5), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 0) == matrix.constZEnd() - 6, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) == matrix.constZEnd() - 5, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) == matrix.constZEnd() - 4, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) == matrix.constZEnd() - 3, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) == matrix.constZEnd() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 2) == matrix.constZEnd() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 1) - (-2) == matrix.getConstZIterator(1, 0), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 0) - 2 == matrix.getConstZIterator(0, 1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) - (-2) == matrix.getConstZIterator(1, 2) + (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 2) - (-2) == matrix.getConstZIterator(0, 1) + (3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(1, 1) - 1 == matrix.getConstZIterator(1, 2) + (-2), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstZIterator(0, 1) - 2 == matrix.constZBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) - 1 == matrix.constZBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) - (-5) == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstZIterator(0, 1) - (-6) == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constZBegin() - 1 == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZBegin() - (-1) == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() - (-1) == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.constZEnd() - 1 == matrix.constZEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstZIterator it{};
        IntMatrixConstZIterator firstIter{it - 1};
        IntMatrixConstZIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
    }
}

void ConstZIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZEnd() - matrix.constZBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZBegin() - matrix.constZEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZBegin() - matrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZEnd() - matrix.constZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstZIterator(1, 0) - matrix.getConstZIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstZIterator(0, 1) - matrix.getConstZIterator(1, 0) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstZIterator(1, 0) - matrix.constZBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZBegin() - matrix.getConstZIterator(1, 0) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstZIterator(0, 1) - matrix.constZEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZEnd() - matrix.getConstZIterator(0, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstZIterator(1, 0) - matrix.getConstZIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constZEnd() - matrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZEnd() - matrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZBegin() - matrix.constZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constZEnd() - matrix.constZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixConstZIterator firstIter{};
        IntMatrixConstZIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstZIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.constZBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.constZEnd(), "The two iterators are not equal");

        secondIter = matrix.constZEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(0, 0)};

        QVERIFY2(it == matrix.constZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(0)};

        QVERIFY2(it == matrix.constZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.getConstZIterator(1, 2)};
        IntMatrixConstZIterator secondIter{matrix.getConstZIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constZBegin() == matrix.constZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZBegin() == matrix.constZRowBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.constZRowEnd(0) == matrix.constZRowBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.constZRowEnd(1) == matrix.constZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZRowBegin(1) == matrix.getConstZIterator(1, 0), "The two iterators are not equal");
        QVERIFY2(matrix.constZRowEnd(1) == matrix.getConstZIterator(2, 0), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constZRowBegin(1) == matrix.getConstZIterator(2), "The two iterators are not equal");
        QVERIFY2(matrix.constZRowEnd(1) == matrix.getConstZIterator(4), "The two iterators are not equal");
    }
}

void ConstZIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        QVERIFY2(matrix.constZBegin() != matrix.constZEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.constZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.getConstZIterator(0, 1)};
        IntMatrixConstZIterator secondIter{matrix.getConstZIterator(1, 2)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        QVERIFY2(matrix.constZRowBegin(0) != matrix.constZRowBegin(1), "The matrix begin iterator of the first row equals the begin iterator of the second row");
        QVERIFY2(matrix.constZRowEnd(0) != matrix.constZRowEnd(1), "The matrix end iterator of the first row equals the end iterator of the second row");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.getConstZIterator(1)};
        IntMatrixConstZIterator secondIter{matrix.getConstZIterator(5)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constZEnd(), "The second iterator equals the end iterator");
    }
}

void ConstZIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constZBegin() < matrix.getConstZIterator(0, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 1) < matrix.constZRowBegin(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constZRowBegin(1) < matrix.getConstZIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(1, 1) < matrix.constZRowEnd(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constZRowEnd(1) < matrix.getConstZIterator(2, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(2, 1) < matrix.constZRowBegin(3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constZRowBegin(3) < matrix.constZEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ConstZIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constZBegin() <= matrix.getConstZIterator(0, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 0) <= matrix.getConstZIterator(0, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 1) <= matrix.constZRowBegin(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constZRowBegin(1) <= matrix.getConstZIterator(1, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstZIterator(1, 1) <= matrix.constZRowEnd(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constZRowEnd(1) <= matrix.getConstZIterator(2, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstZIterator(2, 0) <= matrix.constZRowBegin(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constZRowBegin(3) <= matrix.getConstZIterator(3, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstZIterator(3, 0) <= matrix.constZRowEnd(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constZRowEnd(3) <= matrix.constZEnd(), "The first iterator is greater than the second iterator");
    }
}

void ConstZIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constZEnd() > matrix.constZRowBegin(3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constZRowBegin(3) > matrix.getConstZIterator(2, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(2, 1) > matrix.constZRowEnd(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constZRowEnd(1) > matrix.getConstZIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(1, 1) > matrix.constZRowBegin(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constZRowBegin(1) > matrix.getConstZIterator(0, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 1) > matrix.constZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ConstZIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZBegin()};
        IntMatrixConstZIterator secondIter{matrix.constZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator firstIter{matrix.constZEnd()};
        IntMatrixConstZIterator secondIter{matrix.constZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constZEnd() >= matrix.constZRowEnd(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constZRowEnd(3) >= matrix.getConstZIterator(3, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstZIterator(3, 0) >= matrix.constZRowBegin(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constZRowBegin(3) >= matrix.getConstZIterator(2, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstZIterator(2, 0) >= matrix.constZRowEnd(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constZRowEnd(1) >= matrix.getConstZIterator(1, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstZIterator(1, 1) >= matrix.constZRowBegin(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constZRowBegin(1) >= matrix.getConstZIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 1) >= matrix.getConstZIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstZIterator(0, 0) >= matrix.constZBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ConstZIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixConstZIterator readIter{matrix.constZBegin()};

    matrix.at(0, 2) = 10;
    ++readIter;
    ++readIter;

    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstZIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
    StringMatrixConstZIterator readIter{matrix.constZBegin()};

    ++readIter;

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstZIteratorTests::testDereferenceSquareBracketsOperator()
{
    IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

    IntMatrixConstZIterator firstReadIter{matrix.constZBegin()};
    IntMatrixConstZIterator secondReadIter{matrix.getConstZIterator(1, 0)};
    IntMatrixConstZIterator thirdReadIter{matrix.constZEnd()};

    QVERIFY2(firstReadIter[0] == 1 && firstReadIter[1] == 2 && firstReadIter[2] == -3 && firstReadIter[3] == 4 && firstReadIter[4] == -5 && firstReadIter[5] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(secondReadIter[-3] == 1 && secondReadIter[-2] == 2 && secondReadIter[-1] == -3 && secondReadIter[0] == 4 && secondReadIter[1] == -5 && secondReadIter[2] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(thirdReadIter[-6] == 1 && thirdReadIter[-5] == 2 && thirdReadIter[-4] == -3 && thirdReadIter[-3] == 4 && thirdReadIter[-2] == -5 && thirdReadIter[-1] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
}

void ConstZIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixConstZIterator it{firstMatrix.getConstZIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixConstZIterator it{firstMatrix.getConstZIterator(1, 0)};

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
        IntMatrixConstZIterator it{firstMatrix.getConstZIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixConstZIterator it{firstMatrix.getConstZIterator(1, 0)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ConstZIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrix secondMatrix{2, 3, {7, 8, -9, 10, -11, 12}};

    IntMatrixConstZIterator it{firstMatrix.getConstZIterator(1, 0)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixConstZIterator newIt{firstMatrix.getConstZIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ConstZIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixConstZIterator it{matrix.constZBegin()}; it != matrix.constZEnd(); ++it)
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

        IntMatrixConstZIterator it{matrix.constZEnd()};

        while (it != matrix.constZBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }
}

void ConstZIteratorTests::testRowBeginEndIterators()
{
    IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

    IntMatrixConstZIterator firstRowBeginIter{matrix.constZRowBegin(0)};
    IntMatrixConstZIterator secondRowEndIter{matrix.constZRowEnd(1)};

    QVERIFY2(*firstRowBeginIter == 1, "The matrix begin iterator of the first row does not point to the right element");
    QVERIFY2(*secondRowEndIter == -5, "The matrix end iterator of the second row does not point to the right element");
}

void ConstZIteratorTests::testGetZIterator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(0, 1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstZIterator it{matrix.getConstZIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstZIteratorTests::testIteratingWithAuto()
{
    {
        IntMatrix matrix{2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (const auto element : matrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword does not work correctly");
    }

    {
        IntMatrix matrix{2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (const auto& element : matrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword does not work correctly");
    }
}

void ConstZIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(matrix.constZBegin(), matrix.constZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.constZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(0, 2), matrix.getConstZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(0, 2), matrix.getConstZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(0, 3), matrix.getConstZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(0, 3), matrix.getConstZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.getConstZIterator(2, 3), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(2, 3), matrix.constZEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.getConstZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(2, 2), matrix.constZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(2), matrix.getConstZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(2), matrix.getConstZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(3), matrix.getConstZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(3), matrix.getConstZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.getConstZIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(13), matrix.constZEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.getConstZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstZIterator(12), matrix.constZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowBegin(1), matrix.constZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowBegin(1), matrix.constZRowEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowBegin(2), matrix.constZRowEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowBegin(2), matrix.constZRowEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.constZRowBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowBegin(1), matrix.constZEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZBegin(), matrix.constZRowEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constZRowEnd(1), matrix.constZEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstZIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        IntMatrixConstZIterator it{find(matrix.constZBegin(), matrix.constZEnd(), 4)};

        ++it;

        QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};
        QVERIFY2(find(matrix.constZBegin(), matrix.constZEnd(), 10) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non existing value has been found in the matrix");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        QVERIFY2(find(matrix.constZBegin(), matrix.constZEnd(), 5) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.constZEnd(), 10) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), 5) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), 6) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), 8) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), -1) == matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), -2) == matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZRowEnd(1), 10) == matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZEnd(), 5) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZEnd(), 11) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZEnd(), -2) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZEnd(), -1) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constZRowBegin(1), matrix.constZEnd(), 10) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constZBegin(), matrix.constZRowEnd(1), -1) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.constZRowEnd(1), 6) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.constZRowEnd(1), 8) != matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.constZRowEnd(1), -2) == matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.constZRowEnd(1), 10) == matrix.constZRowEnd(1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), 0) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), -7) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), -2) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), -1) == matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), 11) == matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.getConstZIterator(3, 1), 10) == matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.constZEnd(), 0) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.constZEnd(), 11) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.constZEnd(), -2) != matrix.constZEnd(), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.constZEnd(), -1) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstZIterator(1, 3), matrix.constZEnd(), 10) == matrix.constZEnd(), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constZBegin(), matrix.getConstZIterator(3, 1), -1) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.getConstZIterator(3, 1), -7) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.getConstZIterator(3, 1), -2) != matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.getConstZIterator(3, 1), 11) == matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constZBegin(), matrix.getConstZIterator(3, 1), 10) == matrix.getConstZIterator(3, 1), "The iterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
    }
}

QTEST_APPLESS_MAIN(ConstZIteratorTests)

#include "tst_constziteratortests.moc"
