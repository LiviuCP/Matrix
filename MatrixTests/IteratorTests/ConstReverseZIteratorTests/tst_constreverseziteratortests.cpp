#define ERROR_CHECKING

#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstReverseZIterator = Matrix<int>::ConstReverseZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstReverseZIterator = Matrix<std::string>::ConstReverseZIterator;

class ConstReverseZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstReverseZIteratorTests();
    ~ConstReverseZIteratorTests();

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
    void testRowBeginEndIterators();
    void testGetZIterator();

    void testStdCount();
    void testStdFind();
};

ConstReverseZIteratorTests::ConstReverseZIteratorTests()
{

}

ConstReverseZIteratorTests::~ConstReverseZIteratorTests()
{

}

void ConstReverseZIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator preIncrementIt{++it};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == -5, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == 4, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator postIncrementIt{it++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == -5, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 6, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == -5, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == -5, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constReverseZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.constReverseZEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constReverseZEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.constReverseZEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseZIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 2, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -3, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.constReverseZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.constReverseZEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 2, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 1, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 2, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        IntMatrixConstReverseZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 0)};

        IntMatrixConstReverseZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 2, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()};

        IntMatrixConstReverseZIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstReverseZIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin() + 2};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin() + (-2)};

        QVERIFY2(*firstIter == 4, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 0) + 2};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(1, 0) + (-2)};

        QVERIFY2(*firstIter == 2, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd() + (-3)};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd() + (-6)};

        QVERIFY2(*firstIter == -3, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZBegin() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZBegin() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZBegin() + 6, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZBegin() + 7, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZEnd() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZEnd() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZEnd() + (-7), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 2) == matrix.constReverseZBegin() + 0, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) == matrix.constReverseZBegin() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) == matrix.constReverseZBegin() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) == matrix.constReverseZBegin() + 3, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) == matrix.constReverseZBegin() + 4, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 0) == matrix.constReverseZBegin() + 5, "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 2) == matrix.constReverseZEnd() + (-6), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) == matrix.constReverseZEnd() + (-5), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) == matrix.constReverseZEnd() + (-4), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) == matrix.constReverseZEnd() + (-3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) == matrix.constReverseZEnd() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 0) == matrix.constReverseZEnd() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 0) + 2 == matrix.getConstReverseZIterator(0, 1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) + (-2) == matrix.getConstReverseZIterator(1, 0), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 2) + 1 == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) + (-3) == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 2) + (2) == matrix.getConstReverseZIterator(1, 1) + (1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 1) + (-2) == matrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) + (-1) == matrix.constReverseZBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) + 5 == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) + 6 == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseZBegin() + (-1) == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() + 1 == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() + 1 == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() + (-1) == matrix.constReverseZEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseZIterator it{};
        IntMatrixConstReverseZIterator firstIter{it + (-1)};
        IntMatrixConstReverseZIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseZIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin() - (-2)};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin() - 2};

        QVERIFY2(*firstIter == 4, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 0) - (-2)};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(1, 0) - 2};

        QVERIFY2(*firstIter == 2, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd() - 3};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd() - 6};

        QVERIFY2(*firstIter == -3, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZBegin() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZBegin() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZBegin() - (-6), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZBegin() - (-7), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZEnd() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() == matrix.constReverseZEnd() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZEnd() - 7, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 2) == matrix.constReverseZBegin() - 0, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) == matrix.constReverseZBegin() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) == matrix.constReverseZBegin() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) == matrix.constReverseZBegin() - (-3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) == matrix.constReverseZBegin() - (-4), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 0) == matrix.constReverseZBegin() - (-5), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 2) == matrix.constReverseZEnd() - 6, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) == matrix.constReverseZEnd() - 5, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) == matrix.constReverseZEnd() - 4, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) == matrix.constReverseZEnd() - 3, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) == matrix.constReverseZEnd() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 0) == matrix.constReverseZEnd() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - (-2) == matrix.getConstReverseZIterator(0, 2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) - 2 == matrix.getConstReverseZIterator(1, 1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) - (-2) == matrix.getConstReverseZIterator(0, 0) + (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) - (-2) == matrix.getConstReverseZIterator(1, 1) + (3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) - 1 == matrix.getConstReverseZIterator(0, 0) + (-2), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - 2 == matrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - 1 == matrix.constReverseZBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - (-5) == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - (-6) == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseZBegin() - 1 == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZBegin() - (-1) == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() - (-1) == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constReverseZEnd() - 1 == matrix.constReverseZEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseZIterator it{};
        IntMatrixConstReverseZIterator firstIter{it - 1};
        IntMatrixConstReverseZIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseZIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 4, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 0)};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(1, 0)};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == 2, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        firstIter += -3;
        secondIter += -6;

        QVERIFY2(*firstIter == -3, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 6, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it;

        it = matrix.constReverseZBegin(); it  += -2; QVERIFY2(it == matrix.constReverseZBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += -1; QVERIFY2(it == matrix.constReverseZBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 6; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 7; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += 1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += 2; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -7; QVERIFY2(it == matrix.constReverseZBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constReverseZBegin(); it += 0; QVERIFY2(it == matrix.getConstReverseZIterator(1, 2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 1; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 4; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 5; QVERIFY2(it == matrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constReverseZEnd(); it += -6; QVERIFY2(it == matrix.getConstReverseZIterator(1, 2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -5; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -4; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -2; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -1; QVERIFY2(it == matrix.getConstReverseZIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstReverseZIterator(1, 0); it += 2; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(0, 1); it += -2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(1, 2); it += 1; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(0, 1); it += -3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(1, 2); it += 2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1) + (1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstReverseZIterator(1, 1); it += -2; QVERIFY2(it == matrix.constReverseZBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(1, 1); it += -1; QVERIFY2(it == matrix.constReverseZBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(1, 1); it += 5; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstReverseZIterator(1, 1); it += 6; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixConstReverseZIterator it;

        it = matrix.constReverseZBegin(); it += -1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZBegin(); it += 1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += 1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constReverseZEnd(); it += -1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstReverseZIterator it{};
        IntMatrixConstReverseZIterator firstIter{it};
        IntMatrixConstReverseZIterator secondIter{it};

        firstIter += -1;
        secondIter += 1;

        QVERIFY2(firstIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstReverseZIteratorTests::testOperatorMinusEqual()
{
    {
        {
            IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

            IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
            IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 4, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

            IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 0)};
            IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(1, 0)};

            firstIter -= -2;
            secondIter -= 2;

            QVERIFY2(*firstIter == 2, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

            IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
            IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

            firstIter -= 3;
            secondIter -= 6;

            QVERIFY2(*firstIter == -3, "Operator -= does not work correctly, the resulting iterator does not return the right value");
            QVERIFY2(*secondIter == 6, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        }

        {
            IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
            IntMatrixConstReverseZIterator it;

            it = matrix.constReverseZBegin(); it  -= 2; QVERIFY2(it == matrix.constReverseZBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= 1; QVERIFY2(it == matrix.constReverseZBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -6; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -7; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= -1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= -2; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 7; QVERIFY2(it == matrix.constReverseZBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.constReverseZBegin(); it -= 0; QVERIFY2(it == matrix.getConstReverseZIterator(1, 2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -1; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -4; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -5; QVERIFY2(it == matrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.constReverseZEnd(); it -= 6; QVERIFY2(it == matrix.getConstReverseZIterator(1, 2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 5; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 4; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 2; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 1; QVERIFY2(it == matrix.getConstReverseZIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getConstReverseZIterator(1, 0); it -= -2; QVERIFY2(it == matrix.getConstReverseZIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(0, 1); it -= 2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(1, 2); it -= -1; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(0, 1); it -= 3; QVERIFY2(it == matrix.getConstReverseZIterator(0, 2) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(1, 2); it -= -2; QVERIFY2(it == matrix.getConstReverseZIterator(1, 1) + (1), "Operator -= does not work correctly, the resulting iterator is not the right one");

            it = matrix.getConstReverseZIterator(1, 1); it -= 2; QVERIFY2(it == matrix.constReverseZBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(1, 1); it -= 1; QVERIFY2(it == matrix.constReverseZBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(1, 1); it -= -5; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.getConstReverseZIterator(1, 1); it -= -6; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrix matrix{};
            IntMatrixConstReverseZIterator it;

            it = matrix.constReverseZBegin(); it -= 1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZBegin(); it -= -1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= -1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
            it = matrix.constReverseZEnd(); it -= 1; QVERIFY2(it == matrix.constReverseZEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        }

        {
            IntMatrixConstReverseZIterator it{};
            IntMatrixConstReverseZIterator firstIter{it};
            IntMatrixConstReverseZIterator secondIter{it};

            firstIter -= 1;
            secondIter -= -1;

            QVERIFY2(firstIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
            QVERIFY2(secondIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
        }
    }
}

void ConstReverseZIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZEnd() - matrix.constReverseZBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZBegin() - matrix.constReverseZEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZBegin() - matrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZEnd() - matrix.constReverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseZIterator(0, 1) - matrix.getConstReverseZIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) - matrix.getConstReverseZIterator(0, 1) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) - matrix.constReverseZBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZBegin() - matrix.getConstReverseZIterator(0, 2) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) - matrix.constReverseZEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZEnd() - matrix.getConstReverseZIterator(1, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) - matrix.getConstReverseZIterator(0, 2) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseZEnd() - matrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZEnd() - matrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZBegin() - matrix.constReverseZBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constReverseZEnd() - matrix.constReverseZEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixConstReverseZIterator firstIter{};
        IntMatrixConstReverseZIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstReverseZIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.constReverseZBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.constReverseZEnd(), "The two iterators are not equal");

        secondIter = matrix.constReverseZEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 2)};

        QVERIFY2(it == matrix.constReverseZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(5)};

        QVERIFY2(it == matrix.constReverseZBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 2)};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZBegin() == matrix.constReverseZRowBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseZRowEnd(1) == matrix.constReverseZRowBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseZRowEnd(0) == matrix.constReverseZEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZRowBegin(1) == matrix.getConstReverseZIterator(1, 1), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseZRowEnd(1) == matrix.getConstReverseZIterator(0, 1), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.constReverseZRowBegin(1) == matrix.getConstReverseZIterator(3), "The two iterators are not equal");
        QVERIFY2(matrix.constReverseZRowEnd(1) == matrix.getConstReverseZIterator(1), "The two iterators are not equal");
    }
}

void ConstReverseZIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        QVERIFY2(matrix.constReverseZBegin() != matrix.constReverseZEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.constReverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1, 1)};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(0, 0)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constReverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseZEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        QVERIFY2(matrix.constReverseZRowBegin(2) != matrix.constReverseZRowBegin(1), "The matrix begin iterator of the first row equals the begin iterator of the second row");
        QVERIFY2(matrix.constReverseZRowEnd(2) != matrix.constReverseZRowEnd(1), "The matrix end iterator of the first row equals the end iterator of the second row");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.getConstReverseZIterator(1)};
        IntMatrixConstReverseZIterator secondIter{matrix.getConstReverseZIterator(4)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constReverseZBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constReverseZBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constReverseZEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constReverseZEnd(), "The second iterator equals the end iterator");
    }
}

void ConstReverseZIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constReverseZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constReverseZEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constReverseZBegin() < matrix.getConstReverseZIterator(3, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(3, 1) < matrix.constReverseZRowBegin(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(2) < matrix.getConstReverseZIterator(2, 0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(2, 0) < matrix.constReverseZRowEnd(2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(2) < matrix.getConstReverseZIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) < matrix.constReverseZRowBegin(0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(0) < matrix.constReverseZEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ConstReverseZIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constReverseZEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constReverseZBegin() <= matrix.getConstReverseZIterator(3, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(3, 2) <= matrix.getConstReverseZIterator(3, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(3, 1) <= matrix.constReverseZRowBegin(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(2) <= matrix.getConstReverseZIterator(2, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(2, 2) <= matrix.constReverseZRowEnd(2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(2) <= matrix.getConstReverseZIterator(1, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(1, 2) <= matrix.constReverseZRowBegin(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(0) <= matrix.getConstReverseZIterator(0, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(0, 2) <= matrix.constReverseZRowEnd(0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(0) <= matrix.constReverseZEnd(), "The first iterator is greater than the second iterator");
    }
}

void ConstReverseZIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constReverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constReverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constReverseZEnd() > matrix.constReverseZRowBegin(0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(0) > matrix.getConstReverseZIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(1, 1) > matrix.constReverseZRowEnd(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(2) > matrix.getConstReverseZIterator(2, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(2, 1) > matrix.constReverseZRowBegin(2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(2) > matrix.getConstReverseZIterator(3, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(3, 1) > matrix.constReverseZBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ConstReverseZIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constReverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator firstIter{matrix.constReverseZEnd()};
        IntMatrixConstReverseZIterator secondIter{matrix.constReverseZEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constReverseZEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constReverseZBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.constReverseZEnd() >= matrix.constReverseZRowEnd(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(0) >= matrix.getConstReverseZIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(0, 0) >= matrix.constReverseZRowBegin(0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(0) >= matrix.getConstReverseZIterator(1, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(1, 0) >= matrix.constReverseZRowEnd(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseZRowEnd(2) >= matrix.getConstReverseZIterator(2, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(2, 1) >= matrix.constReverseZRowBegin(2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constReverseZRowBegin(2) >= matrix.getConstReverseZIterator(2, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(2, 2) >= matrix.getConstReverseZIterator(3, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstReverseZIterator(3, 0) >= matrix.constReverseZBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ConstReverseZIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator readIter{matrix.constReverseZBegin()};

        matrix.at(1, 0) = 10;
        ++readIter;
        ++readIter;

        QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }
}

void ConstReverseZIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mnop", "qr"}};
        StringMatrixConstReverseZIterator readIter{matrix.constReverseZBegin()};

        ++readIter;

        QVERIFY2(readIter->size() == 4, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }
}

void ConstReverseZIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixConstReverseZIterator firstReadIter{matrix.constReverseZBegin()};
        IntMatrixConstReverseZIterator secondReadIter{matrix.getConstReverseZIterator(0, 2)};
        IntMatrixConstReverseZIterator thirdReadIter{matrix.constReverseZEnd()};

        QVERIFY2(firstReadIter[0] == 6 && firstReadIter[1] == -5 && firstReadIter[2] == 4 && firstReadIter[3] == -3 && firstReadIter[4] == 2 && firstReadIter[5] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(secondReadIter[-3] == 6 && secondReadIter[-2] == -5 && secondReadIter[-1] == 4 && secondReadIter[0] == -3 && secondReadIter[1] == 2 && secondReadIter[2] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(thirdReadIter[-6] == 6 && thirdReadIter[-5] == -5 && thirdReadIter[-4] == 4 && thirdReadIter[-3] == -3 && thirdReadIter[-2] == 2 && thirdReadIter[-1] == 1,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }
}

void ConstReverseZIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixConstReverseZIterator it{firstMatrix.getConstReverseZIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixConstReverseZIterator it{firstMatrix.getConstReverseZIterator(1, 0)};

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
        IntMatrixConstReverseZIterator it{firstMatrix.getConstReverseZIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixConstReverseZIterator it{firstMatrix.getConstReverseZIterator(1, 0)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ConstReverseZIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrix secondMatrix{2, 3, {7, 8, -9, 10, -11, 12}};

    IntMatrixConstReverseZIterator it{firstMatrix.getConstReverseZIterator(1, 0)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixConstReverseZIterator newIt{firstMatrix.getConstReverseZIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ConstReverseZIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; it != matrix.constReverseZEnd(); ++it)
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

        IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()};

        while (it != matrix.constReverseZBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }
}

void ConstReverseZIteratorTests::testRowBeginEndIterators()
{
    IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

    IntMatrixConstReverseZIterator firstRowBeginIter{matrix.constReverseZRowBegin(0)};
    IntMatrixConstReverseZIterator thirdRowEndIter{matrix.constReverseZRowEnd(2)};

    QVERIFY2(*firstRowBeginIter == 2, "The matrix begin iterator of the first row does not point to the right element");
    QVERIFY2(*thirdRowEndIter == 4, "The matrix end iterator of the second row does not point to the right element");
}

void ConstReverseZIteratorTests::testGetZIterator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(0, 1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstReverseZIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(matrix.constReverseZBegin(), matrix.constReverseZEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.constReverseZEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(1, 4), matrix.getConstReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(2, 0), matrix.getConstReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(2, 0), matrix.getConstReverseZIterator(0, 3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(1, 4), matrix.getConstReverseZIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(2, 3), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(2, 3), matrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(2, 2), matrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(9), matrix.getConstReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(10), matrix.getConstReverseZIterator(2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(9), matrix.getConstReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(10), matrix.getConstReverseZIterator(3), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(13), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(13), matrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstReverseZIterator(12), matrix.constReverseZEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 5);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowEnd(3), matrix.constReverseZRowBegin(0), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowBegin(3), matrix.constReverseZRowEnd(3), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowBegin(3), matrix.constReverseZRowEnd(2), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowEnd(1), matrix.constReverseZEnd(), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZRowBegin(2), matrix.constReverseZEnd(), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constReverseZBegin(), matrix.constReverseZRowBegin(2), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstReverseZIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        IntMatrixConstReverseZIterator it{find(matrix.constReverseZBegin(), matrix.constReverseZEnd(), 4)};

        ++it;

        QVERIFY2(*it == 1, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZEnd(), 5) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZEnd(), 10) == matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 6) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 5) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 8) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), -1) == matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 1) == matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZRowEnd(1), 10) == matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZEnd(), 6) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZEnd(), -1) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZEnd(), 3) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZEnd(), -2) == matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseZRowBegin(1), matrix.constReverseZEnd(), 10) == matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 11) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 5) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 0) != matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 1) == matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.constReverseZRowEnd(1), 10) == matrix.constReverseZRowEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), 7) != matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), -7) != matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), -2) != matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), -1) == matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), 11) == matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(3, 1), matrix.getConstReverseZIterator(1, 3), 10) == matrix.getConstReverseZIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstReverseZIterator(1, 3), matrix.constReverseZEnd(), 0) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(1, 3), matrix.constReverseZEnd(), -1) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(1, 3), matrix.constReverseZEnd(), 4) != matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(1, 3), matrix.constReverseZEnd(), 11) == matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstReverseZIterator(1, 3), matrix.constReverseZEnd(), 10) == matrix.constReverseZEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(3, 1), 11) != matrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(3, 1), 2) != matrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(3, 1), 9) != matrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(3, 1), 0) == matrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constReverseZBegin(), matrix.getConstReverseZIterator(3, 1), 10) == matrix.getConstReverseZIterator(3, 1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    }
}

QTEST_APPLESS_MAIN(ConstReverseZIteratorTests)

#include "tst_constreverseziteratortests.moc"

