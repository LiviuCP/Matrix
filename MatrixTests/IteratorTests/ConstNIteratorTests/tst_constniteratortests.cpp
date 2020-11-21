#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixConstNIterator = Matrix<int>::ConstNIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixConstNIterator = Matrix<std::string>::ConstNIterator;

class ConstNIteratorTests : public QObject
{
    Q_OBJECT

public:
    ConstNIteratorTests();
    ~ConstNIteratorTests();

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

ConstNIteratorTests::ConstNIteratorTests()
{

}

ConstNIteratorTests::~ConstNIteratorTests()
{

}

void ConstNIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator preIncrementIt{++it};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == -3, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator postIncrementIt{it++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.constNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.constNEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.constNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.constNEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstNIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator preDecrementIt{--it};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 4, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.constNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator postDecrementIt{it--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.constNEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNEnd()};

        IntMatrixConstNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(2, 1)};

        IntMatrixConstNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.constNBegin()};

        IntMatrixConstNIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ConstNIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNBegin() + 2};
        IntMatrixConstNIterator secondIter{matrix.constNBegin() + (-2)};

        QVERIFY2(*firstIter == -3, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(2, 0) + 2};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(2, 0) + (-2)};

        QVERIFY2(*firstIter == -5, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNEnd() + (-3)};
        IntMatrixConstNIterator secondIter{matrix.constNEnd() + (-6)};

        QVERIFY2(*firstIter == 4, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constNBegin() == matrix.constNBegin() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() == matrix.constNBegin() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNBegin() + 6, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNBegin() + 7, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNEnd() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNEnd() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() == matrix.constNEnd() + (-7), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(0, 0) == matrix.constNBegin() + 0, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) == matrix.constNBegin() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) == matrix.constNBegin() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) == matrix.constNBegin() + 3, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) == matrix.constNBegin() + 4, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 1) == matrix.constNBegin() + 5, "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(0, 0) == matrix.constNEnd() + (-6), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) == matrix.constNEnd() + (-5), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) == matrix.constNEnd() + (-4), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) == matrix.constNEnd() + (-3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) == matrix.constNEnd() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 1) == matrix.constNEnd() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(1, 0) + 2 == matrix.getConstNIterator(0, 1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) + (-2) == matrix.getConstNIterator(1, 0), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) + 2 == matrix.getConstNIterator(2, 1) + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) + 2 == matrix.getConstNIterator(1, 0) + (3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) + (-1) == matrix.getConstNIterator(2, 1) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(1, 0) + (-2) == matrix.constNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) + (-1) == matrix.constNBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) + 5 == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) + 6 == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constNBegin() + (-1) == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() + 1 == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() + 1 == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() + (-1) == matrix.constNEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstNIterator it{};
        IntMatrixConstNIterator firstIter{it + (-1)};
        IntMatrixConstNIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstNIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNBegin() - (-2)};
        IntMatrixConstNIterator secondIter{matrix.constNBegin() - 2};

        QVERIFY2(*firstIter == -3, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(2, 0) - (-2)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(2, 0) - 2};

        QVERIFY2(*firstIter == -5, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNEnd() - 3};
        IntMatrixConstNIterator secondIter{matrix.constNEnd() - 6};

        QVERIFY2(*firstIter == 4, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constNBegin() == matrix.constNBegin() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() == matrix.constNBegin() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNBegin() - (-6), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNBegin() - (-7), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNEnd() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() == matrix.constNEnd() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() == matrix.constNEnd() - 7, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(0, 0) == matrix.constNBegin() - 0, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) == matrix.constNBegin() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) == matrix.constNBegin() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) == matrix.constNBegin() - (-3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) == matrix.constNBegin() - (-4), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 1) == matrix.constNBegin() - (-5), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(0, 0) == matrix.constNEnd() - 6, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) == matrix.constNEnd() - 5, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) == matrix.constNEnd() - 4, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) == matrix.constNEnd() - 3, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) == matrix.constNEnd() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 1) == matrix.constNEnd() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(1, 0) - (-2) == matrix.getConstNIterator(0, 1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(0, 1) - 2 == matrix.getConstNIterator(1, 0), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) - (-2) == matrix.getConstNIterator(2, 1) + (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(2, 0) - (-2) == matrix.getConstNIterator(1, 0) + (3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 1) - 1 == matrix.getConstNIterator(2, 1) + (-2), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getConstNIterator(1, 0) - 2 == matrix.constNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) - 1 == matrix.constNBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) - (-5) == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getConstNIterator(1, 0) - (-6) == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constNBegin() - 1 == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNBegin() - (-1) == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() - (-1) == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.constNEnd() - 1 == matrix.constNEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstNIterator it{};
        IntMatrixConstNIterator firstIter{it - 1};
        IntMatrixConstNIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstNIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == -3, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(2, 0)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(2, 0)};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == -5, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        firstIter += -3;
        secondIter += -6;

        QVERIFY2(*firstIter == 4, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it;

        it = matrix.constNBegin(); it += -2; QVERIFY2(it == matrix.constNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += -1; QVERIFY2(it == matrix.constNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 6; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 7; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += 1; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += 2; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -7; QVERIFY2(it == matrix.constNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constNBegin(); it += 0; QVERIFY2(it == matrix.getConstNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 1; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 2; QVERIFY2(it == matrix.getConstNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 3; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 4; QVERIFY2(it == matrix.getConstNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 5; QVERIFY2(it == matrix.getConstNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.constNEnd(); it += -6; QVERIFY2(it == matrix.getConstNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -5; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -4; QVERIFY2(it == matrix.getConstNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -3; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -2; QVERIFY2(it == matrix.getConstNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -1; QVERIFY2(it == matrix.getConstNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstNIterator(1, 0); it += 2; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(0, 1); it += -2; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(2, 0); it += 2; QVERIFY2(it == matrix.getConstNIterator(2, 1) + (-1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(2, 0); it += 2; QVERIFY2(it == matrix.getConstNIterator(1, 0) + (3), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 1); it += (-1); QVERIFY2(it == matrix.getConstNIterator(2, 1) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstNIterator(1, 0); it += -2; QVERIFY2(it == matrix.constNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it += -1; QVERIFY2(it == matrix.constNBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it += 5; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it += 6; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixConstNIterator it;

        it = matrix.constNBegin(); it += -1; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 1; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += 1; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -1; QVERIFY2(it == matrix.constNEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstNIterator it;
        IntMatrixConstNIterator firstIter{it};
        IntMatrixConstNIterator secondIter{it};

        firstIter += -1;
        secondIter += 1;

        QVERIFY2(firstIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstNIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        firstIter -= -2;
        secondIter -= 2;

        QVERIFY2(*firstIter == -3, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(2, 0)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(2, 0)};

        firstIter -= -2;
        secondIter -= 2;

        QVERIFY2(*firstIter == -5, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        firstIter -= 3;
        secondIter -= 6;

        QVERIFY2(*firstIter == 4, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it;

        it = matrix.constNBegin(); it -= 2; QVERIFY2(it == matrix.constNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= 1; QVERIFY2(it == matrix.constNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -6; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -7; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= -1; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= -2; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 7; QVERIFY2(it == matrix.constNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.constNBegin(); it -= 0; QVERIFY2(it == matrix.getConstNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -1; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -2; QVERIFY2(it == matrix.getConstNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -3; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -4; QVERIFY2(it == matrix.getConstNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it -= -5; QVERIFY2(it == matrix.getConstNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.constNEnd(); it -= 6; QVERIFY2(it == matrix.getConstNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 5; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 4; QVERIFY2(it == matrix.getConstNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 3; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 2; QVERIFY2(it == matrix.getConstNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it -= 1; QVERIFY2(it == matrix.getConstNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstNIterator(1, 0); it -= -2; QVERIFY2(it == matrix.getConstNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(0, 1); it -= 2; QVERIFY2(it == matrix.getConstNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(2, 0); it -= -2; QVERIFY2(it == matrix.getConstNIterator(2, 1) + (-1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(2, 0); it -= -2; QVERIFY2(it == matrix.getConstNIterator(1, 0) + (3), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 1); it -= 1; QVERIFY2(it == matrix.getConstNIterator(2, 1) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.getConstNIterator(1, 0); it -= 2; QVERIFY2(it == matrix.constNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it -= 1; QVERIFY2(it == matrix.constNBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it -= -5; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getConstNIterator(1, 0); it -= -6; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixConstNIterator it;

        it = matrix.constNBegin(); it += -1; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNBegin(); it += 1; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += 1; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.constNEnd(); it += -1; QVERIFY2(it == matrix.constNEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixConstNIterator it;
        IntMatrixConstNIterator firstIter{it};
        IntMatrixConstNIterator secondIter{it};

        firstIter -= 1;
        secondIter -= -1;

        QVERIFY2(firstIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
    }
}

void ConstNIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constNEnd() - matrix.constNBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNBegin() - matrix.constNEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNBegin() - matrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNEnd() - matrix.constNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstNIterator(0, 1) - matrix.getConstNIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstNIterator(1, 0) - matrix.getConstNIterator(0, 1) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstNIterator(0, 1) - matrix.constNBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNBegin() - matrix.getConstNIterator(0, 1) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstNIterator(1, 0) - matrix.constNEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNEnd() - matrix.getConstNIterator(1, 0) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getConstNIterator(0, 1) - matrix.getConstNIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constNEnd() - matrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNEnd() - matrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNBegin() - matrix.constNBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.constNEnd() - matrix.constNEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixConstNIterator firstIter{};
        IntMatrixConstNIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ConstNIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.constNBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.constNEnd(), "The two iterators are not equal");

        secondIter = matrix.constNEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 0)};

        QVERIFY2(it == matrix.constNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0)};

        QVERIFY2(it == matrix.constNBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(2, 1)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.constNBegin() == matrix.constNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.constNBegin() == matrix.constNColumnBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.constNColumnEnd(0) == matrix.constNColumnBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.constNColumnEnd(1) == matrix.constNEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.constNColumnBegin(1) == matrix.getConstNIterator(0, 1), "The two iterators are not equal");
        QVERIFY2(matrix.constNColumnEnd(1) == matrix.getConstNIterator(0, 2), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.constNColumnBegin(1) == matrix.getConstNIterator(2), "The two iterators are not equal");
        QVERIFY2(matrix.constNColumnEnd(1) == matrix.getConstNIterator(4), "The two iterators are not equal");
    }
}

void ConstNIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        QVERIFY2(matrix.constNBegin() != matrix.constNEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.constNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(1, 0)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(2, 1)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constNEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12}};

        QVERIFY2(matrix.constNColumnBegin(0) != matrix.constNColumnBegin(1), "The matrix begin iterator of the first column equals the begin iterator of the second column");
        QVERIFY2(matrix.constNColumnEnd(0) != matrix.constNColumnEnd(1), "The matrix end iterator of the first column equals the end iterator of the second column");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.getConstNIterator(1)};
        IntMatrixConstNIterator secondIter{matrix.getConstNIterator(5)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.constNBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.constNBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.constNEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.constNEnd(), "The second iterator equals the end iterator");
    }
}

void ConstNIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.constNEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constNBegin() < matrix.getConstNIterator(1, 0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 0) < matrix.constNColumnBegin(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnBegin(1) < matrix.getConstNIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 1) < matrix.constNColumnEnd(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnEnd(1) < matrix.getConstNIterator(1, 2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 2) < matrix.constNColumnBegin(3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnBegin(3) < matrix.constNEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ConstNIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.constNEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constNBegin() <= matrix.getConstNIterator(0, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 0) <= matrix.getConstNIterator(1, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 0) <= matrix.constNColumnBegin(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constNColumnBegin(1) <= matrix.getConstNIterator(1, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 1) <= matrix.constNColumnEnd(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constNColumnEnd(1) <= matrix.getConstNIterator(0, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 2) <= matrix.constNColumnBegin(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constNColumnBegin(3) <= matrix.getConstNIterator(0, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 3) <= matrix.constNColumnEnd(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.constNColumnEnd(3) <= matrix.constNEnd(), "The first iterator is greater than the second iterator");
    }
}

void ConstNIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.constNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constNEnd() > matrix.constNColumnBegin(3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnBegin(3) > matrix.getConstNIterator(1, 2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 2) > matrix.constNColumnEnd(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnEnd(1) > matrix.getConstNIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 1) > matrix.constNColumnBegin(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.constNColumnBegin(1) > matrix.getConstNIterator(1, 0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 0) > matrix.constNBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ConstNIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.constNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNBegin()};
        IntMatrixConstNIterator secondIter{matrix.constNBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.constNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator firstIter{matrix.constNEnd()};
        IntMatrixConstNIterator secondIter{matrix.constNEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.constNEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.constNBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.constNEnd() >= matrix.constNColumnEnd(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constNColumnEnd(3) >= matrix.getConstNIterator(0, 3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 3) >= matrix.constNColumnBegin(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constNColumnBegin(3) >= matrix.getConstNIterator(0, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 2) >= matrix.constNColumnEnd(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constNColumnEnd(1) >= matrix.getConstNIterator(1, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 1) >= matrix.constNColumnBegin(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.constNColumnBegin(1) >= matrix.getConstNIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstNIterator(1, 0) >= matrix.getConstNIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getConstNIterator(0, 0) >= matrix.constNBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ConstNIteratorTests::testDereferenceAsteriskOperator()
{
    IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrixConstNIterator readIter{matrix.constNBegin()};

    matrix.at(2, 0) = 10;
    ++readIter;
    ++readIter;

    QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
}

void ConstNIteratorTests::testDereferenceArrowOperator()
{
    StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
    StringMatrixConstNIterator readIter{matrix.constNBegin()};

    ++readIter;

    QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
}

void ConstNIteratorTests::testDereferenceSquareBracketsOperator()
{
    IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

    IntMatrixConstNIterator firstReadIter{matrix.constNBegin()};
    IntMatrixConstNIterator secondReadIter{matrix.getConstNIterator(0, 1)};
    IntMatrixConstNIterator thirdReadIter{matrix.constNEnd()};

    QVERIFY2(firstReadIter[0] == 1 && firstReadIter[1] == 2 && firstReadIter[2] == -3 && firstReadIter[3] == 4 && firstReadIter[4] == -5 && firstReadIter[5] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(secondReadIter[-3] == 1 && secondReadIter[-2] == 2 && secondReadIter[-1] == -3 && secondReadIter[0] == 4 && secondReadIter[1] == -5 && secondReadIter[2] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

    QVERIFY2(thirdReadIter[-6] == 1 && thirdReadIter[-5] == 2 && thirdReadIter[-4] == -3 && thirdReadIter[-3] == 4 && thirdReadIter[-2] == -5 && thirdReadIter[-1] == 6,
            "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
}

void ConstNIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, {7, -9, -11, 8, 10, 12}};
        IntMatrixConstNIterator it{firstMatrix.getConstNIterator(0, 1)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 1)};

        matrix.resize(3, 2);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 1)};

        matrix.resizeWithValue(4, 2, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 1)};

        matrix.resizeWithValue(3, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(0, 1)};

        matrix.resizeWithValue(5, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixConstNIterator it{firstMatrix.getConstNIterator(0, 1)};

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
        IntMatrixConstNIterator it{firstMatrix.getConstNIterator(0, 1)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixConstNIterator it{firstMatrix.getConstNIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ConstNIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrix secondMatrix{3, 2, {7, 10, 8, -11, -9, 12}};

    IntMatrixConstNIterator it{firstMatrix.getConstNIterator(0, 1)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixConstNIterator newIt{firstMatrix.getConstNIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ConstNIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixConstNIterator it{matrix.constNBegin()}; it != matrix.constNEnd(); ++it)
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

        IntMatrixConstNIterator it{matrix.constNEnd()};

        while (it != matrix.constNBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the iterator does not work correctly, sum of the elements is not correct");
    }
}

void ConstNIteratorTests::testColumnBeginEndIterators()
{
    IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

    IntMatrixConstNIterator firstColBeginIter{matrix.constNColumnBegin(0)};
    IntMatrixConstNIterator secondColEndIter{matrix.constNColumnEnd(1)};

    QVERIFY2(*firstColBeginIter == 1, "The matrix begin iterator of the first column does not point to the right element");
    QVERIFY2(*secondColEndIter == -5, "The matrix end iterator of the second column does not point to the right element");
}

void ConstNIteratorTests::testGetNIterator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(1, 0)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixConstNIterator it{matrix.getConstNIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ConstNIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(matrix.constNBegin(), matrix.constNEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.constNEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(2, 0), matrix.getConstNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(2, 0), matrix.getConstNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(3, 0), matrix.getConstNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(3, 0), matrix.getConstNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.getConstNIterator(3, 2), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(3, 2), matrix.constNEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.getConstNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(2, 2), matrix.constNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(2), matrix.getConstNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(2), matrix.getConstNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(3), matrix.getConstNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(3), matrix.getConstNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.getConstNIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(13), matrix.constNEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.getConstNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getConstNIterator(12), matrix.constNEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnBegin(1), matrix.constNColumnEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnBegin(2), matrix.constNColumnEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnBegin(2), matrix.constNColumnEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.constNColumnBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnBegin(1), matrix.constNEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNBegin(), matrix.constNColumnEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.constNColumnEnd(1), matrix.constNEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void ConstNIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        IntMatrixConstNIterator it{find(matrix.constNBegin(), matrix.constNEnd(), 4)};

        ++it;

        QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};
        QVERIFY2(find(matrix.constNBegin(), matrix.constNEnd(), 10) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, -2, 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        QVERIFY2(find(matrix.constNBegin(), matrix.constNEnd(), 5) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.constNEnd(), 10) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), 5) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), 6) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), 8) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), -1) == matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), -2) == matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNColumnEnd(1), 10) == matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNEnd(), 5) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNEnd(), 11) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNEnd(), -2) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNEnd(), -1) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constNColumnBegin(1), matrix.constNEnd(), 10) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constNBegin(), matrix.constNColumnEnd(1), -1) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.constNColumnEnd(1), 6) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.constNColumnEnd(1), 8) != matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.constNColumnEnd(1), -2) == matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.constNColumnEnd(1), 10) == matrix.constNColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), 0) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), -7) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), -2) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), -1) == matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), 11) == matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.getConstNIterator(1, 3), 10) == matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.constNEnd(), 0) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.constNEnd(), 11) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.constNEnd(), -2) != matrix.constNEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.constNEnd(), -1) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getConstNIterator(3, 1), matrix.constNEnd(), 10) == matrix.constNEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.constNBegin(), matrix.getConstNIterator(1, 3), -1) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.getConstNIterator(1, 3), -7) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.getConstNIterator(1, 3), -2) != matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.getConstNIterator(1, 3), 11) == matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.constNBegin(), matrix.getConstNIterator(1, 3), 10) == matrix.getConstNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    }
}

QTEST_APPLESS_MAIN(ConstNIteratorTests)

#include "tst_constniteratortests.moc"
