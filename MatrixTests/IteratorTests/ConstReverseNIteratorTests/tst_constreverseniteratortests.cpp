#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseNIterator = Matrix<int>::ConstReverseNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseNIterator = Matrix<std::string>::ConstReverseNIterator;

class ConstReverseNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseNIteratorTests();
    ~ConstReverseNIteratorTests();

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
};

ConstReverseNIteratorTests::ConstReverseNIteratorTests()
{

}

ConstReverseNIteratorTests::~ConstReverseNIteratorTests()
{

}

void ConstReverseNIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator preIncrementIt{++it};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == 4, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator postIncrementIt{it++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constReverseNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.constReverseNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constReverseNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.constReverseNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseNIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -3, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.constReverseNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.constReverseNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        IntMatrixConstReverseNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 0)};

        IntMatrixConstReverseNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()};

        IntMatrixConstReverseNIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseNIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin() + 2};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin() + (-2)};

        QVERIFY2(*firstIter == 4, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(0, 1) + 2};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(0, 1) + (-2)};

        QVERIFY2(*firstIter == 2, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd() + (-3)};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd() + (-6)};

        QVERIFY2(*firstIter == -3, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNBegin() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNBegin() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNBegin() + 6, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNBegin() + 7, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNEnd() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNEnd() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNEnd() + (-7), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(2, 1) == matrix.constReverseNBegin() + 0, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) == matrix.constReverseNBegin() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) == matrix.constReverseNBegin() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) == matrix.constReverseNBegin() + 3, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) == matrix.constReverseNBegin() + 4, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 0) == matrix.constReverseNBegin() + 5, "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(2, 1) == matrix.constReverseNEnd() + (-6), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) == matrix.constReverseNEnd() + (-5), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) == matrix.constReverseNEnd() + (-4), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) == matrix.constReverseNEnd() + (-3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) == matrix.constReverseNEnd() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 0) == matrix.constReverseNEnd() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(0, 1) + 2 == matrix.getConstReverseNIterator(1, 0), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) + (-2) == matrix.getConstReverseNIterator(0, 1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 1) + 1 == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) + (-3) == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 1) + (2) == matrix.getConstReverseNIterator(1, 1) + (1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(1, 1) + (-2) == matrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) + (-1) == matrix.constReverseNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) + 5 == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) + 6 == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseNBegin() + (-1) == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() + 1 == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() + 1 == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() + (-1) == matrix.constReverseNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseNIterator it{};
        IntMatrixConstReverseNIterator firstIter{it + (-1)};
        IntMatrixConstReverseNIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseNIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin() - (-2)};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin() - 2};

        QVERIFY2(*firstIter == 4, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(0, 1) - (-2)};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(0, 1) - 2};

        QVERIFY2(*firstIter == 2, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd() - 3};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd() - 6};

        QVERIFY2(*firstIter == -3, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNBegin() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNBegin() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNBegin() - (-6), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNBegin() - (-7), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNEnd() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() == matrix.constReverseNEnd() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNEnd() - 7, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(2, 1) == matrix.constReverseNBegin() - 0, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) == matrix.constReverseNBegin() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) == matrix.constReverseNBegin() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) == matrix.constReverseNBegin() - (-3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) == matrix.constReverseNBegin() - (-4), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 0) == matrix.constReverseNBegin() - (-5), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(2, 1) == matrix.constReverseNEnd() - 6, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) == matrix.constReverseNEnd() - 5, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) == matrix.constReverseNEnd() - 4, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) == matrix.constReverseNEnd() - 3, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) == matrix.constReverseNEnd() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 0) == matrix.constReverseNEnd() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - (-2) == matrix.getConstReverseNIterator(2, 0), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) - 2 == matrix.getConstReverseNIterator(1, 1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) - (-2) == matrix.getConstReverseNIterator(0, 0) + (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) - (-2) == matrix.getConstReverseNIterator(1, 1) + (3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) - 1 == matrix.getConstReverseNIterator(0, 0) + (-2), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - 2 == matrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - 1 == matrix.constReverseNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - (-5) == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - (-6) == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseNBegin() - 1 == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNBegin() - (-1) == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() - (-1) == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseNEnd() - 1 == matrix.constReverseNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseNIterator it{};
        IntMatrixConstReverseNIterator firstIter{it - 1};
        IntMatrixConstReverseNIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseNIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 4, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(0, 1)};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(0, 1)};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 2, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        firstIter += -3;
        secondIter += -6;

        QVERIFY2(*firstIter == -3, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it;

        it = matrix.constReverseNBegin(); it  += -2; QVERIFY2(it == matrix.constReverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += -1; QVERIFY2(it == matrix.constReverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 6; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 7; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += 1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += 2; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -7; QVERIFY2(it == matrix.constReverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constReverseNBegin(); it += 0; QVERIFY2(it == matrix.getConstReverseNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 1; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 2; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 4; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 5; QVERIFY2(it == matrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constReverseNEnd(); it += -6; QVERIFY2(it == matrix.getConstReverseNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -5; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -4; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -1; QVERIFY2(it == matrix.getConstReverseNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstReverseNIterator(0, 1); it += 2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(1, 0); it += -2; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(2, 1); it += 1; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(1, 0); it += -3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(2, 1); it += 2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1) + (1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstReverseNIterator(1, 1); it += -2; QVERIFY2(it == matrix.constReverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(1, 1); it += -1; QVERIFY2(it == matrix.constReverseNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(1, 1); it += 5; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseNIterator(1, 1); it += 6; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixConstReverseNIterator it;

        it = matrix.constReverseNBegin(); it += -1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNBegin(); it += 1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += 1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseNEnd(); it += -1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseNIterator it{};
        IntMatrixConstReverseNIterator firstIter{it};
        IntMatrixConstReverseNIterator secondIter{it};

        firstIter += -1;
        secondIter += 1;

        QVERIFY2(firstIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseNIteratorTests::testOperatorMinusEqual()
{
    {
        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
            IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 4, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(0, 1)};
            IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(0, 1)};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 2, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

            IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
            IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

            firstIter -= 3;
            secondIter -= 6;

            QVERIFY2(*firstIter == -3, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
            IntMatrixConstReverseNIterator it;

            it = matrix.constReverseNBegin(); it  -= 2; QVERIFY2(it == matrix.constReverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= 1; QVERIFY2(it == matrix.constReverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -6; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -7; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= -1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= -2; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 7; QVERIFY2(it == matrix.constReverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.constReverseNBegin(); it -= 0; QVERIFY2(it == matrix.getConstReverseNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -1; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -2; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -4; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -5; QVERIFY2(it == matrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.constReverseNEnd(); it -= 6; QVERIFY2(it == matrix.getConstReverseNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 5; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 4; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 1; QVERIFY2(it == matrix.getConstReverseNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getConstReverseNIterator(0, 1); it -= -2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(1, 0); it -= 2; QVERIFY2(it == matrix.getConstReverseNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(2, 1); it -= -1; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(1, 0); it -= 3; QVERIFY2(it == matrix.getConstReverseNIterator(2, 0) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(2, 1); it -= -2; QVERIFY2(it == matrix.getConstReverseNIterator(1, 1) + (1), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getConstReverseNIterator(1, 1); it -= 2; QVERIFY2(it == matrix.constReverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(1, 1); it -= 1; QVERIFY2(it == matrix.constReverseNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(1, 1); it -= -5; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseNIterator(1, 1); it -= -6; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrix matrix{};
            IntMatrixConstReverseNIterator it;

            it = matrix.constReverseNBegin(); it -= 1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNBegin(); it -= -1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= -1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseNEnd(); it -= 1; QVERIFY2(it == matrix.constReverseNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrixConstReverseNIterator it{};
            IntMatrixConstReverseNIterator firstIter{it};
            IntMatrixConstReverseNIterator secondIter{it};

            firstIter -= 1;
            secondIter -= -1;

            QVERIFY2(firstIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
            QVERIFY2(secondIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
        }
    }
}

void ConstReverseNIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constReverseNEnd() - matrix.constReverseNBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNBegin() - matrix.constReverseNEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNBegin() - matrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNEnd() - matrix.constReverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseNIterator(1, 0) - matrix.getConstReverseNIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) - matrix.getConstReverseNIterator(1, 0) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) - matrix.constReverseNBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNBegin() - matrix.getConstReverseNIterator(2, 0) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) - matrix.constReverseNEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNEnd() - matrix.getConstReverseNIterator(1, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) - matrix.getConstReverseNIterator(2, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseNEnd() - matrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNEnd() - matrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNBegin() - matrix.constReverseNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseNEnd() - matrix.constReverseNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixConstReverseNIterator firstIter{};
        IntMatrixConstReverseNIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstReverseNIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.constReverseNBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.constReverseNEnd(), "The two iterators are not equal");

        secondIter = matrix.constReverseNEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(2, 1)};

        QVERIFY2(it == matrix.constReverseNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(5)};

        QVERIFY2(it == matrix.constReverseNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(2, 1)};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constReverseNBegin() == matrix.constReverseNColumnBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseNColumnEnd(1) == matrix.constReverseNColumnBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseNColumnEnd(0) == matrix.constReverseNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.constReverseNColumnBegin(1) == matrix.getConstReverseNIterator(1, 1), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseNColumnEnd(1) == matrix.getConstReverseNIterator(1, 0), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.constReverseNColumnBegin(1) == matrix.getConstReverseNIterator(3), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseNColumnEnd(1) == matrix.getConstReverseNIterator(1), "The two iterators are not equal");
    }
}

void ConstReverseNIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        QVERIFY2(matrix.constReverseNBegin() != matrix.constReverseNEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.constReverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(1, 1)};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(0, 0)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constReverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12}};

        QVERIFY2(matrix.constReverseNColumnBegin(2) != matrix.constReverseNColumnBegin(1), "The matrix begin iterator of the first column equals the begin iterator of the second column");
        QVERIFY2(matrix.constReverseNColumnEnd(2) != matrix.constReverseNColumnEnd(1), "The matrix end iterator of the first column equals the end iterator of the second column");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.getConstReverseNIterator(1)};
        IntMatrixConstReverseNIterator secondIter{matrix.getConstReverseNIterator(4)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constReverseNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseNEnd(), "The second iterator equals the end iterator");
    }
}

void ConstReverseNIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constReverseNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constReverseNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constReverseNBegin() < matrix.getConstReverseNIterator(1, 3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 3) < matrix.constReverseNColumnBegin(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(2) < matrix.getConstReverseNIterator(0, 2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(0, 2) < matrix.constReverseNColumnEnd(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(2) < matrix.getConstReverseNIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) < matrix.constReverseNColumnBegin(0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(0) < matrix.constReverseNEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ConstReverseNIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constReverseNBegin() <= matrix.getConstReverseNIterator(2, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(2, 3) <= matrix.getConstReverseNIterator(1, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 3) <= matrix.constReverseNColumnBegin(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(2) <= matrix.getConstReverseNIterator(2, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(2, 2) <= matrix.constReverseNColumnEnd(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(2) <= matrix.getConstReverseNIterator(2, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(2, 1) <= matrix.constReverseNColumnBegin(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(0) <= matrix.getConstReverseNIterator(2, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(2, 0) <= matrix.constReverseNColumnEnd(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(0) <= matrix.constReverseNEnd(), "The first iterator is greater than the second iterator");
    }
}

void ConstReverseNIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constReverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constReverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constReverseNEnd() > matrix.constReverseNColumnBegin(0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(0) > matrix.getConstReverseNIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 1) > matrix.constReverseNColumnEnd(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(2) > matrix.getConstReverseNIterator(1, 2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 2) > matrix.constReverseNColumnBegin(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(2) > matrix.getConstReverseNIterator(1, 3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 3) > matrix.constReverseNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ConstReverseNIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNBegin()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator firstIter{matrix.constReverseNEnd()};
        IntMatrixConstReverseNIterator secondIter{matrix.constReverseNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constReverseNEnd() >= matrix.constReverseNColumnEnd(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(0) >= matrix.getConstReverseNIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(0, 0) >= matrix.constReverseNColumnBegin(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(0) >= matrix.getConstReverseNIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(0, 1) >= matrix.constReverseNColumnEnd(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseNColumnEnd(2) >= matrix.getConstReverseNIterator(1, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(1, 2) >= matrix.constReverseNColumnBegin(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseNColumnBegin(2) >= matrix.getConstReverseNIterator(2, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(2, 2) >= matrix.getConstReverseNIterator(0, 3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseNIterator(0, 3) >= matrix.constReverseNBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ConstReverseNIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixConstReverseNIterator readIter{matrix.constReverseNBegin()};

    matrix.at(0, 1) = 10;
    ++readIter;
    ++readIter;

    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstReverseNIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mnop", "ghi", "qr"}};
    StringMatrixConstReverseNIterator readIter{matrix.constReverseNBegin()};

    ++readIter;

    QVERIFY2(readIter->size() == 4, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstReverseNIteratorTests::testDereferenceSquareBracketsOperator()
{
    IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

    IntMatrixConstReverseNIterator firstReadIter{matrix.constReverseNBegin()};
    IntMatrixConstReverseNIterator secondReadIter{matrix.getConstReverseNIterator(2, 0)};
    IntMatrixConstReverseNIterator thirdReadIter{matrix.constReverseNEnd()};

    QVERIFY2(firstReadIter[0] == 6 && firstReadIter[1] == -5 && firstReadIter[2] == 4 && firstReadIter[3] == -3 && firstReadIter[4] == 2 && firstReadIter[5] == 1,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(secondReadIter[-3] == 6 && secondReadIter[-2] == -5 && secondReadIter[-1] == 4 && secondReadIter[0] == -3 && secondReadIter[1] == 2 && secondReadIter[2] == 1,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(thirdReadIter[-6] == 6 && thirdReadIter[-5] == -5 && thirdReadIter[-4] == 4 && thirdReadIter[-3] == -3 && thirdReadIter[-2] == 2 && thirdReadIter[-1] == 1,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
}

void ConstReverseNIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, {7, -9, -11, 8, 10, 12}};
        IntMatrixConstReverseNIterator it{firstMatrix.getConstReverseNIterator(0, 1)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 1)};

        matrix.resize(3, 2);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 1)};

        matrix.resizeWithValue(4, 2, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 1)};

        matrix.resizeWithValue(3, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(0, 1)};

        matrix.resizeWithValue(5, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixConstReverseNIterator it{firstMatrix.getConstReverseNIterator(0, 1)};

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
        IntMatrixConstReverseNIterator it{firstMatrix.getConstReverseNIterator(0, 1)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixConstReverseNIterator it{firstMatrix.getConstReverseNIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ConstReverseNIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrix secondMatrix{3, 2, {7, 10, 8, -11, -9, 12}};

    IntMatrixConstReverseNIterator it{firstMatrix.getConstReverseNIterator(0, 1)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixConstReverseNIterator newIt{firstMatrix.getConstReverseNIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ConstReverseNIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixConstReverseNIterator it{matrix.constReverseNBegin()}; it != matrix.constReverseNEnd(); ++it)
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

        IntMatrixConstReverseNIterator it{matrix.constReverseNEnd()};

        while (it != matrix.constReverseNBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }
}

void ConstReverseNIteratorTests::testColumnBeginEndIterators()
{
    IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

    IntMatrixConstReverseNIterator firstColumnBeginIter{matrix.constReverseNColumnBegin(0)};
    IntMatrixConstReverseNIterator thirdColumnEndIter{matrix.constReverseNColumnEnd(2)};

    QVERIFY2(*firstColumnBeginIter == 2, "The matrix begin ZIterator of the first column does not point to the right element");
    QVERIFY2(*thirdColumnEndIter == 4, "The matrix end ZIterator of the second column does not point to the right element");
}

void ConstReverseNIteratorTests::testGetNIterator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(1, 0)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstReverseNIterator it{matrix.getConstReverseNIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseNIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(matrix.constReverseNBegin(), matrix.constReverseNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.constReverseNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(4, 1), matrix.getConstReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(0, 2), matrix.getConstReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(0, 2), matrix.getConstReverseNIterator(3, 0), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(4, 1), matrix.getConstReverseNIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(3, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(3, 2), matrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(2, 2), matrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(9), matrix.getConstReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(10), matrix.getConstReverseNIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(9), matrix.getConstReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(10), matrix.getConstReverseNIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(13), matrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseNIterator(12), matrix.constReverseNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnEnd(3), matrix.constReverseNColumnBegin(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnBegin(3), matrix.constReverseNColumnEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnBegin(3), matrix.constReverseNColumnEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnEnd(1), matrix.constReverseNEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNColumnBegin(2), matrix.constReverseNEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseNBegin(), matrix.constReverseNColumnBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstReverseNIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        IntMatrixConstReverseNIterator it{find(matrix.constReverseNBegin(), matrix.constReverseNEnd(), 4)};

        ++it;

        QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, -2, 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNEnd(), 5) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNEnd(), 10) == matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 6) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 5) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 8) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), -1) == matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 1) == matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNColumnEnd(1), 10) == matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNEnd(), 6) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNEnd(), -1) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNEnd(), 3) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNEnd(), -2) == matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseNColumnBegin(1), matrix.constReverseNEnd(), 10) == matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 11) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 5) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 0) != matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 1) == matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.constReverseNColumnEnd(1), 10) == matrix.constReverseNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), 7) != matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), -7) != matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), -2) != matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), -1) == matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), 11) == matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(1, 3), matrix.getConstReverseNIterator(3, 1), 10) == matrix.getConstReverseNIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstReverseNIterator(3, 1), matrix.constReverseNEnd(), 0) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(3, 1), matrix.constReverseNEnd(), -1) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(3, 1), matrix.constReverseNEnd(), 4) != matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(3, 1), matrix.constReverseNEnd(), 11) == matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseNIterator(3, 1), matrix.constReverseNEnd(), 10) == matrix.constReverseNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(1, 3), 11) != matrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(1, 3), 2) != matrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(1, 3), 9) != matrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(1, 3), 0) == matrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseNBegin(), matrix.getConstReverseNIterator(1, 3), 10) == matrix.getConstReverseNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    }
}

QTEST_APPLESS_MAIN(ConstReverseNIteratorTests)

#include "tst_constreverseniteratortests.moc"

