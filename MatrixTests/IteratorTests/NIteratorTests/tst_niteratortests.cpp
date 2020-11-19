#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixNIterator = Matrix<int>::NIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixNIterator = Matrix<std::string>::NIterator;

class NIteratorTests : public QObject
{
    Q_OBJECT

public:
    NIteratorTests();
    ~NIteratorTests();

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

NIteratorTests::NIteratorTests()
{

}

NIteratorTests::~NIteratorTests()
{

}

void NIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator preIncrementIt{++it};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == -3, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator postIncrementIt{it++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator preIncrementIt{++it};

        QVERIFY2(it == matrix.nEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(preIncrementIt == matrix.nEnd(), "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator postIncrementIt{it++};

        QVERIFY2(it == matrix.nEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postIncrementIt == matrix.nEnd(), "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void NIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator preDecrementIt{--it};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 4, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.nEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator postDecrementIt{it--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.nEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nEnd()};

        IntMatrixNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(2, 1)};

        IntMatrixNIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator preDecrementIt{--it};

        QVERIFY2(*it == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 1, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.nBegin()};

        IntMatrixNIterator postDecrementIt{it--};

        QVERIFY2(*it == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 1, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void NIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nBegin() + 2};
        IntMatrixNIterator secondIter{matrix.nBegin() + (-2)};

        QVERIFY2(*firstIter == -3, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.getNIterator(2, 0) + 2};
        IntMatrixNIterator secondIter{matrix.getNIterator(2, 0) + (-2)};

        QVERIFY2(*firstIter == -5, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nEnd() + (-3)};
        IntMatrixNIterator secondIter{matrix.nEnd() + (-6)};

        QVERIFY2(*firstIter == 4, "Operator + does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.nBegin() == matrix.nBegin() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() == matrix.nBegin() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nBegin() + 6, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nBegin() + 7, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nEnd() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nEnd() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() == matrix.nEnd() + (-7), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(0, 0) == matrix.nBegin() + 0, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) == matrix.nBegin() + 1, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) == matrix.nBegin() + 2, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) == matrix.nBegin() + 3, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) == matrix.nBegin() + 4, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 1) == matrix.nBegin() + 5, "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(0, 0) == matrix.nEnd() + (-6), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) == matrix.nEnd() + (-5), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) == matrix.nEnd() + (-4), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) == matrix.nEnd() + (-3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) == matrix.nEnd() + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 1) == matrix.nEnd() + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(1, 0) + 2 == matrix.getNIterator(0, 1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) + (-2) == matrix.getNIterator(1, 0), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) + 2 == matrix.getNIterator(2, 1) + (-1), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) + 2 == matrix.getNIterator(1, 0) + (3), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) + (-1) == matrix.getNIterator(2, 1) + (-2), "Operator + does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(1, 0) + (-2) == matrix.nBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) + (-1) == matrix.nBegin(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) + 5 == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) + 6 == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.nBegin() + (-1) == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() + 1 == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() + 1 == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() + (-1) == matrix.nEnd(), "Operator + does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixNIterator it{};
        IntMatrixNIterator firstIter{it + (-1)};
        IntMatrixNIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not work correctly, the resulting iterator is not the right one");
    }
}

void NIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nBegin() - (-2)};
        IntMatrixNIterator secondIter{matrix.nBegin() - 2};

        QVERIFY2(*firstIter == -3, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.getNIterator(2, 0) - (-2)};
        IntMatrixNIterator secondIter{matrix.getNIterator(2, 0) - 2};

        QVERIFY2(*firstIter == -5, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nEnd() - 3};
        IntMatrixNIterator secondIter{matrix.nEnd() - 6};

        QVERIFY2(*firstIter == 4, "Operator - does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.nBegin() == matrix.nBegin() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() == matrix.nBegin() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nBegin() - (-6), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nBegin() - (-7), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nEnd() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() == matrix.nEnd() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() == matrix.nEnd() - 7, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(0, 0) == matrix.nBegin() - 0, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) == matrix.nBegin() - (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) == matrix.nBegin() - (-2), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) == matrix.nBegin() - (-3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) == matrix.nBegin() - (-4), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 1) == matrix.nBegin() - (-5), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(0, 0) == matrix.nEnd() - 6, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) == matrix.nEnd() - 5, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) == matrix.nEnd() - 4, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) == matrix.nEnd() - 3, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) == matrix.nEnd() - 2, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 1) == matrix.nEnd() - 1, "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(1, 0) - (-2) == matrix.getNIterator(0, 1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(0, 1) - 2 == matrix.getNIterator(1, 0), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) - (-2) == matrix.getNIterator(2, 1) + (-1), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(2, 0) - (-2) == matrix.getNIterator(1, 0) + (3), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 1) - 1 == matrix.getNIterator(2, 1) + (-2), "Operator - does not work correctly, the resulting iterator is not the right one");

        QVERIFY2(matrix.getNIterator(1, 0) - 2 == matrix.nBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) - 1 == matrix.nBegin(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) - (-5) == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.getNIterator(1, 0) - (-6) == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.nBegin() - 1 == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nBegin() - (-1) == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() - (-1) == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(matrix.nEnd() - 1 == matrix.nEnd(), "Operator - does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixNIterator it{};
        IntMatrixNIterator firstIter{it - 1};
        IntMatrixNIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not work correctly, the resulting iterator is not the right one");
    }
}

void NIteratorTests::testOperatorPlusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == -3, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.getNIterator(2, 0)};
        IntMatrixNIterator secondIter{matrix.getNIterator(2, 0)};

        firstIter += 2;
        secondIter += -2;

        QVERIFY2(*firstIter == -5, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        firstIter += -3;
        secondIter += -6;

        QVERIFY2(*firstIter == 4, "Operator += does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator += does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it;

        it = matrix.nBegin(); it += -2; QVERIFY2(it == matrix.nBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += -1; QVERIFY2(it == matrix.nBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 6; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 7; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += 1; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += 2; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -7; QVERIFY2(it == matrix.nBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.nBegin(); it += 0; QVERIFY2(it == matrix.getNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 1; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 2; QVERIFY2(it == matrix.getNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 3; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 4; QVERIFY2(it == matrix.getNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 5; QVERIFY2(it == matrix.getNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.nEnd(); it += -6; QVERIFY2(it == matrix.getNIterator(0, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -5; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -4; QVERIFY2(it == matrix.getNIterator(2, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -3; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -2; QVERIFY2(it == matrix.getNIterator(1, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -1; QVERIFY2(it == matrix.getNIterator(2, 1), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getNIterator(1, 0); it += 2; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(0, 1); it += -2; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(2, 0); it += 2; QVERIFY2(it == matrix.getNIterator(2, 1) + (-1), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(2, 0); it += 2; QVERIFY2(it == matrix.getNIterator(1, 0) + (3), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 1); it += (-1); QVERIFY2(it == matrix.getNIterator(2, 1) + (-2), "Operator += does not work correctly, the resulting iterator is not the right one");

        it = matrix.getNIterator(1, 0); it += -2; QVERIFY2(it == matrix.nBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it += -1; QVERIFY2(it == matrix.nBegin(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it += 5; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it += 6; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixNIterator it;

        it = matrix.nBegin(); it += -1; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 1; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += 1; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -1; QVERIFY2(it == matrix.nEnd(), "Operator += does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixNIterator it;
        IntMatrixNIterator firstIter{it};
        IntMatrixNIterator secondIter{it};

        firstIter += -1;
        secondIter += 1;

        QVERIFY2(firstIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator += does not work correctly, the resulting iterator is not the right one");
    }
}

void NIteratorTests::testOperatorMinusEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        firstIter -= -2;
        secondIter -= 2;

        QVERIFY2(*firstIter == -3, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.getNIterator(2, 0)};
        IntMatrixNIterator secondIter{matrix.getNIterator(2, 0)};

        firstIter -= -2;
        secondIter -= 2;

        QVERIFY2(*firstIter == -5, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        firstIter -= 3;
        secondIter -= 6;

        QVERIFY2(*firstIter == 4, "Operator -= does not work correctly, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "Operator -= does not work correctly, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it;

        it = matrix.nBegin(); it -= 2; QVERIFY2(it == matrix.nBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= 1; QVERIFY2(it == matrix.nBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -6; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -7; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= -1; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= -2; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 7; QVERIFY2(it == matrix.nBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.nBegin(); it -= 0; QVERIFY2(it == matrix.getNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -1; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -2; QVERIFY2(it == matrix.getNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -3; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -4; QVERIFY2(it == matrix.getNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it -= -5; QVERIFY2(it == matrix.getNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.nEnd(); it -= 6; QVERIFY2(it == matrix.getNIterator(0, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 5; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 4; QVERIFY2(it == matrix.getNIterator(2, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 3; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 2; QVERIFY2(it == matrix.getNIterator(1, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it -= 1; QVERIFY2(it == matrix.getNIterator(2, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.getNIterator(1, 0); it -= -2; QVERIFY2(it == matrix.getNIterator(0, 1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(0, 1); it -= 2; QVERIFY2(it == matrix.getNIterator(1, 0), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(2, 0); it -= -2; QVERIFY2(it == matrix.getNIterator(2, 1) + (-1), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(2, 0); it -= -2; QVERIFY2(it == matrix.getNIterator(1, 0) + (3), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 1); it -= 1; QVERIFY2(it == matrix.getNIterator(2, 1) + (-2), "Operator -= does not work correctly, the resulting iterator is not the right one");

        it = matrix.getNIterator(1, 0); it -= 2; QVERIFY2(it == matrix.nBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it -= 1; QVERIFY2(it == matrix.nBegin(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it -= -5; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.getNIterator(1, 0); it -= -6; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};
        IntMatrixNIterator it;

        it = matrix.nBegin(); it += -1; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nBegin(); it += 1; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += 1; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
        it = matrix.nEnd(); it += -1; QVERIFY2(it == matrix.nEnd(), "Operator -= does not work correctly, the resulting iterator is not the right one");
    }

    {
        IntMatrixNIterator it;
        IntMatrixNIterator firstIter{it};
        IntMatrixNIterator secondIter{it};

        firstIter -= 1;
        secondIter -= -1;

        QVERIFY2(firstIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator -= does not work correctly, the resulting iterator is not the right one");
    }
}

void NIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.nEnd() - matrix.nBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nBegin() - matrix.nEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nBegin() - matrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nEnd() - matrix.nEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getNIterator(0, 1) - matrix.getNIterator(1, 0) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getNIterator(1, 0) - matrix.getNIterator(0, 1) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getNIterator(0, 1) - matrix.nBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nBegin() - matrix.getNIterator(0, 1) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getNIterator(1, 0) - matrix.nEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nEnd() - matrix.getNIterator(1, 0) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getNIterator(0, 1) - matrix.getNIterator(0, 1) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.nEnd() - matrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nEnd() - matrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nBegin() - matrix.nBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.nEnd() - matrix.nEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixNIterator firstIter{};
        IntMatrixNIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void NIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.nBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.nEnd(), "The two iterators are not equal");

        secondIter = matrix.nEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 0)};

        QVERIFY2(it == matrix.nBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0)};

        QVERIFY2(it == matrix.nBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.getNIterator(2, 1)};
        IntMatrixNIterator secondIter{matrix.getNIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.nBegin() == matrix.nEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        QVERIFY2(matrix.nBegin() == matrix.nColumnBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.nColumnEnd(0) == matrix.nColumnBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.nColumnEnd(1) == matrix.nEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.nColumnBegin(1) == matrix.getNIterator(0, 1), "The two iterators are not equal");
        QVERIFY2(matrix.nColumnEnd(1) == matrix.getNIterator(0, 2), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

        QVERIFY2(matrix.nColumnBegin(1) == matrix.getNIterator(2), "The two iterators are not equal");
        QVERIFY2(matrix.nColumnEnd(1) == matrix.getNIterator(4), "The two iterators are not equal");
    }
}

void NIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        QVERIFY2(matrix.nBegin() != matrix.nEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.nBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.nBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.nEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.nEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.getNIterator(1, 0)};
        IntMatrixNIterator secondIter{matrix.getNIterator(2, 1)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.nBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.nBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.nEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.nEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 5, 9, 2, 6, 10, 3, 7, 11, 4, 8, 12}};

        QVERIFY2(matrix.nColumnBegin(0) != matrix.nColumnBegin(1), "The matrix begin iterator of the first column equals the begin iterator of the second column");
        QVERIFY2(matrix.nColumnEnd(0) != matrix.nColumnEnd(1), "The matrix end iterator of the first column equals the end iterator of the second column");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.getNIterator(1)};
        IntMatrixNIterator secondIter{matrix.getNIterator(5)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.nBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.nBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.nEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.nEnd(), "The second iterator equals the end iterator");
    }
}

void NIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.nBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.nEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.nEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.nBegin() < matrix.getNIterator(1, 0), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 0) < matrix.nColumnBegin(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.nColumnBegin(1) < matrix.getNIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 1) < matrix.nColumnEnd(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.nColumnEnd(1) < matrix.getNIterator(1, 2), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 2) < matrix.nColumnBegin(3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.nColumnBegin(3) < matrix.nEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void NIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.nBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.nEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.nBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.nEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.nEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.nEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.nBegin() <= matrix.getNIterator(0, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 0) <= matrix.getNIterator(1, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getNIterator(1, 0) <= matrix.nColumnBegin(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.nColumnBegin(1) <= matrix.getNIterator(1, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getNIterator(1, 1) <= matrix.nColumnEnd(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.nColumnEnd(1) <= matrix.getNIterator(0, 2), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 2) <= matrix.nColumnBegin(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.nColumnBegin(3) <= matrix.getNIterator(0, 3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 3) <= matrix.nColumnEnd(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.nColumnEnd(3) <= matrix.nEnd(), "The first iterator is greater than the second iterator");
    }
}

void NIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.nEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.nBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.nBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.nEnd() > matrix.nColumnBegin(3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.nColumnBegin(3) > matrix.getNIterator(1, 2), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 2) > matrix.nColumnEnd(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.nColumnEnd(1) > matrix.getNIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 1) > matrix.nColumnBegin(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.nColumnBegin(1) > matrix.getNIterator(1, 0), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getNIterator(1, 0) > matrix.nBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void NIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.nEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.nBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nBegin()};
        IntMatrixNIterator secondIter{matrix.nBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.nEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.nBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.nBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator firstIter{matrix.nEnd()};
        IntMatrixNIterator secondIter{matrix.nEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.nEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.nBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, -5, 9, 2, 6, -10, -3, 7, 11, 4, -8, 12}};

        QVERIFY2(matrix.nEnd() >= matrix.nColumnEnd(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.nColumnEnd(3) >= matrix.getNIterator(0, 3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 3) >= matrix.nColumnBegin(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.nColumnBegin(3) >= matrix.getNIterator(0, 2), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 2) >= matrix.nColumnEnd(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.nColumnEnd(1) >= matrix.getNIterator(1, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getNIterator(1, 1) >= matrix.nColumnBegin(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.nColumnBegin(1) >= matrix.getNIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getNIterator(1, 0) >= matrix.getNIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getNIterator(0, 0) >= matrix.nBegin(), "The first iterator is smaller than the second iterator");
    }
}

void NIteratorTests::testDereferenceAsteriskOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator readIter{matrix.nBegin()};

        matrix.at(2, 0) = 10;
        ++readIter;
        ++readIter;

        QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator writeIter{matrix.nBegin()};

        ++writeIter;
        ++writeIter;
        *writeIter = 10;

        QVERIFY2(matrix.at(2, 0) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void NIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
        StringMatrixNIterator readIter{matrix.nBegin()};

        ++readIter;

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{3, 2, {"abc", "jkl", "defed", "mno", "ghi", "pqr"}};
        StringMatrixNIterator writeIter{matrix.nBegin()};

        ++writeIter;
        ++writeIter;

        writeIter->assign("abcdefghi");

        QVERIFY2(matrix.at(2, 0) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void NIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator firstReadIter{matrix.nBegin()};
        IntMatrixNIterator secondReadIter{matrix.getNIterator(0, 1)};
        IntMatrixNIterator thirdReadIter{matrix.nEnd()};

        QVERIFY2(firstReadIter[0] == 1 && firstReadIter[1] == 2 && firstReadIter[2] == -3 && firstReadIter[3] == 4 && firstReadIter[4] == -5 && firstReadIter[5] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(secondReadIter[-3] == 1 && secondReadIter[-2] == 2 && secondReadIter[-1] == -3 && secondReadIter[0] == 4 && secondReadIter[1] == -5 && secondReadIter[2] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(thirdReadIter[-6] == 1 && thirdReadIter[-5] == 2 && thirdReadIter[-4] == -3 && thirdReadIter[-3] == 4 && thirdReadIter[-2] == -5 && thirdReadIter[-1] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator writeIter{matrix.nBegin()};

        writeIter[0] = 7;
        writeIter[2] = -8;
        writeIter[5] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -8 && matrix.at(0, 1) == 4 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator writeIter{matrix.getNIterator(0, 1)};

        writeIter[-3] = 7;
        writeIter[0] = -8;
        writeIter[2] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -3 && matrix.at(0, 1) == -8 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};

        IntMatrixNIterator writeIter{matrix.nEnd()};

        writeIter[-6] = 7;
        writeIter[-3] = -8;
        writeIter[-1] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(1, 0) == 2 && matrix.at(2, 0) == -3 && matrix.at(0, 1) == -8 && matrix.at(1, 1) == -5 && matrix.at(2, 1) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }
}

void NIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, {7, -9, -11, 8, 10, 12}};
        IntMatrixNIterator it{firstMatrix.getNIterator(0, 1)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 1)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 1)};

        matrix.resize(3, 2);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 1)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 1)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(0, 1)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixNIterator it{firstMatrix.getNIterator(0, 1)};

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
        IntMatrixNIterator it{firstMatrix.getNIterator(0, 1)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixNIterator it{firstMatrix.getNIterator(0, 1)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void NIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{3, 2, {1, 4, 2, -5, -3, 6}};
    IntMatrix secondMatrix{3, 2, {7, 10, 8, -11, -9, 12}};

    IntMatrixNIterator it{firstMatrix.getNIterator(0, 1)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixNIterator newIt{firstMatrix.getNIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void NIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{3, 4, {1, 4, -7, 10, 2, -5, 8, -11, -3, 6, 9, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixNIterator it{matrix.nBegin()}; it != matrix.nEnd(); ++it)
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

        IntMatrixNIterator it{matrix.nEnd()};

        while (it != matrix.nBegin())
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

        for (IntMatrixNIterator it{matrix.nBegin()}; it != matrix.nEnd(); ++it)
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

        IntMatrixNIterator it{matrix.nEnd()};

        while (it != matrix.nBegin())
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

void NIteratorTests::testColumnBeginEndIterators()
{
    IntMatrix matrix{2, 3, {1, -3, -5, 2, 4, 6}};

    IntMatrixNIterator firstColBeginIter{matrix.nColumnBegin(0)};
    IntMatrixNIterator secondColEndIter{matrix.nColumnEnd(1)};

    QVERIFY2(*firstColBeginIter == 1, "The matrix begin iterator of the first column does not point to the right element");
    QVERIFY2(*secondColEndIter == -5, "The matrix end iterator of the second column does not point to the right element");
}

void NIteratorTests::testGetNIterator()
{
    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(1, 0)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{3, 2, {1, 4, 2, -5, -3, 6}};
        IntMatrixNIterator it{matrix.getNIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void NIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

    int matchCount{count(matrix.nBegin(), matrix.nEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.nEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(2, 0), matrix.getNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(2, 0), matrix.getNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(3, 0), matrix.getNIterator(4, 1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(3, 0), matrix.getNIterator(0, 2), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.getNIterator(3, 2), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(3, 2), matrix.nEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.getNIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(2, 2), matrix.nEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(2), matrix.getNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(2), matrix.getNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(3), matrix.getNIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(3), matrix.getNIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.getNIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(13), matrix.nEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.getNIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.getNIterator(12), matrix.nEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnBegin(1), matrix.nColumnEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnBegin(1), matrix.nColumnEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnBegin(2), matrix.nColumnEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnBegin(2), matrix.nColumnEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.nColumnBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnBegin(1), matrix.nEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nBegin(), matrix.nColumnEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");

    matchCount = count(matrix.nColumnEnd(1), matrix.nEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with the iterator, incorrect number of matches returned");
}

void NIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        IntMatrixNIterator it{find(matrix.nBegin(), matrix.nEnd(), 4)};

        ++it;

        QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 1, 9, 8}};

        QVERIFY2(find(matrix.nBegin(), matrix.nEnd(), 10) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non existing value has been found in the matrix");

        IntMatrixNIterator it{matrix.nBegin()};

        while(it != matrix.nEnd())
        {
            it = find(it, matrix.nEnd(), 9);

            if (it != matrix.nEnd())
            {
                *it = 10;
            }
        }

        int expectedNumber{std::count(matrix.nBegin(), matrix.nEnd(), 10)};

        QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, -2, 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        QVERIFY2(find(matrix.nBegin(), matrix.nEnd(), 5) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.nEnd(), 10) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), 5) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), 6) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), 8) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), -1) == matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), -2) == matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nColumnEnd(1), 10) == matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nEnd(), 5) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nEnd(), 11) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nEnd(), -2) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nEnd(), -1) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.nColumnBegin(1), matrix.nEnd(), 10) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.nBegin(), matrix.nColumnEnd(1), -1) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.nColumnEnd(1), 6) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.nColumnEnd(1), 8) != matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.nColumnEnd(1), -2) == matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.nColumnEnd(1), 10) == matrix.nColumnEnd(1), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), 0) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), -7) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), -2) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), -1) == matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), 11) == matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3), 10) == matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.nEnd(), 0) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.nEnd(), 11) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.nEnd(), -2) != matrix.nEnd(), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.nEnd(), -1) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getNIterator(3, 1), matrix.nEnd(), 10) == matrix.nEnd(), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.nBegin(), matrix.getNIterator(1, 3), -1) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.getNIterator(1, 3), -7) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.getNIterator(1, 3), -2) != matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.getNIterator(1, 3), 11) == matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.nBegin(), matrix.getNIterator(1, 3), 10) == matrix.getNIterator(1, 3), "The iterator doesn't work correctly with std::find, a non-existing value has been found in the given range");
    }
}

void NIteratorTests::testStdSort()
{
    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, 7, 3, 8, 2, 2, 1, 0, 8, 9, 4, 6, 9, 11}};

        std::sort(matrix.nBegin(), matrix.nEnd());

        QVERIFY2(matrix.at(0, 0) == -7 && matrix.at(1, 0) == -2 && matrix.at(2, 0) == -1 && matrix.at(3, 0) == 0 && matrix.at(4, 0) == 1 &&
                 matrix.at(0, 1) ==  1 && matrix.at(1, 1) ==  2 && matrix.at(2, 1) ==  2 && matrix.at(3, 1) == 2 && matrix.at(4, 1) == 3 &&
                 matrix.at(0, 2) ==  4 && matrix.at(1, 2) ==  5 && matrix.at(2, 2) ==  6 && matrix.at(3, 2) == 7 && matrix.at(4, 2) == 8 &&
                 matrix.at(0, 3) ==  8 && matrix.at(1, 3) ==  9 && matrix.at(2, 3) ==  9 && matrix.at(3, 3) == 9 && matrix.at(4, 3) == 11,

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
            std::sort(matrix.nColumnBegin(col), matrix.nColumnEnd(col));
        }

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 1 && matrix.at(2, 0) == 1 && matrix.at(3, 0) == 3 && matrix.at(4, 0) == 4 &&
                 matrix.at(0, 1) ==  0 && matrix.at(1, 1) == 5 && matrix.at(2, 1) == 6 && matrix.at(3, 1) == 8 && matrix.at(4, 1) == 9 &&
                 matrix.at(0, 2) == -2 && matrix.at(1, 2) == 2 && matrix.at(2, 2) == 2 && matrix.at(3, 2) == 8 && matrix.at(4, 2) == 9 &&
                 matrix.at(0, 3) == -7 && matrix.at(1, 3) == 2 && matrix.at(2, 3) == 7 && matrix.at(3, 3) == 9 && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the per column sorting has not been done properly");

    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7, 1, 9, -2, (7), 3, 8, 2, 2, 1, (0), 8, 9, 4, 6, 9, 11}};

        std::sort(matrix.getNIterator(3, 1), matrix.getNIterator(1, 3));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 1   && matrix.at(2, 0) == 3 && matrix.at(3, 0) == 1    && matrix.at(4, 0) ==  4 &&
                 matrix.at(0, 1) ==  5 && matrix.at(1, 1) == 9   && matrix.at(2, 1) == 8 && matrix.at(3, 1) == (-7) && matrix.at(4, 1) == -2 &&
                 matrix.at(0, 2) ==  0 && matrix.at(1, 2) == 2   && matrix.at(2, 2) == 2 && matrix.at(3, 2) == 6    && matrix.at(4, 2) ==  8 &&
                 matrix.at(0, 3) ==  9 && matrix.at(1, 3) == (7) && matrix.at(2, 3) == 2 && matrix.at(3, 3) == 9    && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{5, 4, {(-1), 5, 2, -7,  1, 9, (-2), 7,  3, 8, 2, 2,  1, 0, 8, 9,  4, 6, 9, 11}};

        std::sort(matrix.nBegin(), matrix.getNIterator(1, 2));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 0    && matrix.at(2, 0) == 1 && matrix.at(3, 0) == 1 && matrix.at(4, 0) == 2 &&
                 matrix.at(0, 1) ==  3 && matrix.at(1, 1) == 4    && matrix.at(2, 1) == 5 && matrix.at(3, 1) == 6 && matrix.at(4, 1) == 8 &&
                 matrix.at(0, 2) ==  9 && matrix.at(1, 2) == (-2) && matrix.at(2, 2) == 2 && matrix.at(3, 2) == 8 && matrix.at(4, 2) == 9 &&
                 matrix.at(0, 3) == -7 && matrix.at(1, 3) == 7    && matrix.at(2, 3) == 2 && matrix.at(3, 3) == 9 && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{5, 4, {-1, 5, 2, -7,   1, 9, (-2), 7,   3, 8, 2, 2,   1, 0, 8, 9,   4, 6, 9, 11}};

        std::sort(matrix.getNIterator(1, 2), matrix.nEnd());

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(1, 0) == 1    && matrix.at(2, 0) == 3  && matrix.at(3, 0) == 1 && matrix.at(4, 0) == 4 &&
                 matrix.at(0, 1) ==  5 && matrix.at(1, 1) == 9    && matrix.at(2, 1) == 8  && matrix.at(3, 1) == 0 && matrix.at(4, 1) == 6 &&
                 matrix.at(0, 2) ==  2 && matrix.at(1, 2) == (-7) && matrix.at(2, 2) == -2 && matrix.at(3, 2) == 2 && matrix.at(4, 2) == 2 &&
                 matrix.at(0, 3) ==  7 && matrix.at(1, 3) == 8    && matrix.at(2, 3) == 9  && matrix.at(3, 3) == 9 && matrix.at(4, 3) == 11,

                 "The iterator objects don't work correctly, the matrix has not been sorted properly");

    }
}

QTEST_APPLESS_MAIN(NIteratorTests)

#include "tst_niteratortests.moc"
