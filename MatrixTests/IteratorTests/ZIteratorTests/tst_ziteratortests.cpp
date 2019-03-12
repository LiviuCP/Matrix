#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixZIterator = Matrix<int>::ZIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixIterator = Matrix<std::string>::ZIterator;

class ZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ZIteratorTests();
    ~ZIteratorTests();

private slots:
    void testPassingThroughAllElements();
    void testIncrementOperators();
    void testDecrementOperators();
    void testOperatorPlus();
    void testOperatorMinus();
    void testDifferenceOperator();
    void testDereferenceStarOperator();
    void testDereferenceArrowOperator();
    void testDereferenceSquareBracketsOperator();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testSmallerThanOperator();
    void testSmallerThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testIsValidWithMatrix();
    void testPositionGetters();
    void testGetIterator();
    void testRowBeginEndIterators();
    void testStdCount();
    void testStdFind();
    void testStdSort();
    void testIteratingWithAuto();
};

ZIteratorTests::ZIteratorTests()
{

}

ZIteratorTests::~ZIteratorTests()
{

}

void ZIteratorTests::testPassingThroughAllElements()
{
    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        for (IntMatrixZIterator it{matrix.zBegin()}; it != matrix.zEnd(); ++it)
        {
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the Z iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the Z iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int count{0};
        int sum{0};

        IntMatrixZIterator it{matrix.zEnd()};

        while (it != matrix.zBegin())
        {
            --it;
            ++count;
            sum += *it;
        }

        QVERIFY2(count == 12, "Passing through through all matrix elements by using the Z iterator does not work correctly, total elements count is not correct");
        QVERIFY2(sum == 26, "Passing through through all matrix elements by using the Z iterator does not work correctly, sum of the elements is not correct");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int sum{0};

        for (IntMatrixZIterator it{matrix.zBegin()}; it != matrix.zEnd(); ++it)
        {
            if (*it < 0)
            {
                *it *= -1;
            }
            sum += *it;
        }

        QVERIFY2(sum == 78, "Passing through through all matrix elements by using the Z iterator and calculating their absolute values does not work correctly, sum of the absolute values is not correct");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, -7, 8, 9, 10, -11, 12}};
        int sum{0};

        IntMatrixZIterator it{matrix.zEnd()};

        while (it != matrix.zBegin())
        {
            --it;
            if (*it < 0)
            {
                *it *= -1;
            }
            sum += *it;
        }

        QVERIFY2(sum == 78, "Passing through through all matrix elements by using the Z iterator and calculating their absolute values does not work correctly, sum of the absolute values is not correct");
    }
}

void ZIteratorTests::testIncrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator preIncrementIt{++it};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preIncrementIt == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator prePreIncrementIt{++(++it)};

        QVERIFY2(*it == 2, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreIncrementIt == -3, "The pre-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator postIncrementIt{it++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator postPostIncrementIt{(it++)++};

        QVERIFY2(*it == 2, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostIncrementIt == 1, "The post-increment operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator prePostIncrementIt{(++it)++};

        QVERIFY2(*it == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostIncrementIt == 2, "The pre- and post-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator postPreIncrementIt{++(it++)};

        QVERIFY2(*it == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreIncrementIt == 2, "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator postPreIncrementIt{++it};

        QVERIFY2(it == matrix.zEnd(), "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPreIncrementIt == matrix.zEnd(), "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator postPreIncrementIt{it++};

        QVERIFY2(it == matrix.zEnd(), "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPreIncrementIt == matrix.zEnd(), "The post- and pre-increment operators do not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ZIteratorTests::testDecrementOperators()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator preDecrementIt{--it};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator preDecrementIt{--it};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*preDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == 6, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator prePreDecrementIt{--(--it)};

        QVERIFY2(*it == -5, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePreDecrementIt == 4, "The pre-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator postDecrementIt{it--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postDecrementIt == matrix.zEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator postDecrementIt{it--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(postPostDecrementIt == matrix.zEnd(), "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator postPostDecrementIt{(it--)--};

        QVERIFY2(*it == -5, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPostDecrementIt == 6, "The post-decrement operator does not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == 6, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator prePostDecrementIt{(--it)--};

        QVERIFY2(*it == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*prePostDecrementIt == -5, "The pre- and post-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zEnd()};

        IntMatrixZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 6, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 2)};

        IntMatrixZIterator postPreDecrementIt{--(it--)};

        QVERIFY2(*it == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == -5, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator postPreDecrementIt{--it};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.zBegin()};

        IntMatrixZIterator postPreDecrementIt{it--};

        QVERIFY2(*it == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
        QVERIFY2(*postPreDecrementIt == 1, "The post- and pre-decrement operators do not work correctly, the resulting iterator doesn't point to the right element");
    }
}

void ZIteratorTests::testOperatorPlus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.zBegin() + 2};
        IntMatrixZIterator secondIter{matrix.zBegin() + (-2)};

        QVERIFY2(*firstIter == -3, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.getZIterator(0, 2) + 2};
        IntMatrixZIterator secondIter{matrix.getZIterator(0, 2) + (-2)};

        QVERIFY2(*firstIter == -5, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.zEnd() + (-3)};
        IntMatrixZIterator secondIter{matrix.zEnd() + (-6)};

        QVERIFY2(*firstIter == 4, "Operator + does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator + does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zBegin() == matrix.zBegin() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() == matrix.zBegin() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zBegin() + 6, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zBegin() + 7, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zEnd() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zEnd() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() == matrix.zEnd() + (-7), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 0) == matrix.zBegin() + 0, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) == matrix.zBegin() + 1, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) == matrix.zBegin() + 2, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) == matrix.zBegin() + 3, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) == matrix.zBegin() + 4, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 2) == matrix.zBegin() + 5, "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 0) == matrix.zEnd() + (-6), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) == matrix.zEnd() + (-5), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) == matrix.zEnd() + (-4), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) == matrix.zEnd() + (-3), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) == matrix.zEnd() + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 2) == matrix.zEnd() + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 1) + 2 == matrix.getZIterator(1, 0), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) + (-2) == matrix.getZIterator(0, 1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) + 2 == matrix.getZIterator(1, 2) + (-1), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) + 2 == matrix.getZIterator(0, 1) + (3), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) + (-1) == matrix.getZIterator(1, 2) + (-2), "Operator + does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 1) + (-2) == matrix.zBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) + (-1) == matrix.zBegin(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) + 5 == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) + 6 == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.zBegin() + (-1) == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() + 1 == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() + 1 == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() + (-1) == matrix.zEnd(), "Operator + does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixZIterator it{};
        IntMatrixZIterator firstIter{it + (-1)};
        IntMatrixZIterator secondIter{it + 1};

        QVERIFY2(firstIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator + does not correctly work, the resulting iterator is not the right one");
    }
}

void ZIteratorTests::testOperatorMinus()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.zBegin() - (-2)};
        IntMatrixZIterator secondIter{matrix.zBegin() - 2};

        QVERIFY2(*firstIter == -3, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.getZIterator(0, 2) - (-2)};
        IntMatrixZIterator secondIter{matrix.getZIterator(0, 2) - 2};

        QVERIFY2(*firstIter == -5, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstIter{matrix.zEnd() - 3};
        IntMatrixZIterator secondIter{matrix.zEnd() - 6};

        QVERIFY2(*firstIter == 4, "Operator - does not correctly work, the resulting iterator does not return the right value");
        QVERIFY2(*secondIter == 1, "operator - does not correctly work, the resulting iterator does not return the right value");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zBegin() == matrix.zBegin() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() == matrix.zBegin() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zBegin() - (-6), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zBegin() - (-7), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zEnd() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() == matrix.zEnd() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() == matrix.zEnd() - 7, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 0) == matrix.zBegin() - 0, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) == matrix.zBegin() - (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) == matrix.zBegin() - (-2), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) == matrix.zBegin() - (-3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) == matrix.zBegin() - (-4), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 2) == matrix.zBegin() - (-5), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 0) == matrix.zEnd() - 6, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) == matrix.zEnd() - 5, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) == matrix.zEnd() - 4, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) == matrix.zEnd() - 3, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) == matrix.zEnd() - 2, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 2) == matrix.zEnd() - 1, "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 1) - (-2) == matrix.getZIterator(1, 0), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 0) - 2 == matrix.getZIterator(0, 1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) - (-2) == matrix.getZIterator(1, 2) + (-1), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 2) - (-2) == matrix.getZIterator(0, 1) + (3), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(1, 1) - 1 == matrix.getZIterator(1, 2) + (-2), "Operator - does not correctly work, the resulting iterator is not the right one");

        QVERIFY2(matrix.getZIterator(0, 1) - 2 == matrix.zBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) - 1 == matrix.zBegin(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) - (-5) == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.getZIterator(0, 1) - (-6) == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.zBegin() - 1 == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zBegin() - (-1) == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() - (-1) == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(matrix.zEnd() - 1 == matrix.zEnd(), "Operator - does not correctly work, the resulting iterator is not the right one");
    }

    {
        IntMatrixZIterator it{};
        IntMatrixZIterator firstIter{it - 1};
        IntMatrixZIterator secondIter{it - (-1)};

        QVERIFY2(firstIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
        QVERIFY2(secondIter == it, "Operator - does not correctly work, the resulting iterator is not the right one");
    }
}

void ZIteratorTests::testDifferenceOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zEnd() - matrix.zBegin() == 6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zBegin() - matrix.zEnd() == -6, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zBegin() - matrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zEnd() - matrix.zEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getZIterator(1, 0) - matrix.getZIterator(0, 1) == 2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getZIterator(0, 1) - matrix.getZIterator(1, 0) == -2, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getZIterator(1, 0) - matrix.zBegin() == 3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zBegin() - matrix.getZIterator(1, 0) == -3, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getZIterator(0, 1) - matrix.zEnd() == -5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zEnd() - matrix.getZIterator(0, 1) == 5, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.getZIterator(1, 0) - matrix.getZIterator(1, 0) == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.zEnd() - matrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zEnd() - matrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zBegin() - matrix.zBegin() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(matrix.zEnd() - matrix.zEnd() == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }

    {
        IntMatrixZIterator firstIter{};
        IntMatrixZIterator secondIter{};

        QVERIFY2(firstIter - secondIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
        QVERIFY2(secondIter - firstIter == 0, "The difference operator does not work correctly, difference between iterators is wrong");
    }
}

void ZIteratorTests::testDereferenceStarOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator readIter{matrix.zBegin()};

        matrix.at(0, 2) = 10;
        ++readIter;
        ++readIter;

        QVERIFY2(*readIter == 10, "The dereference (*) operator does not work correctly, the pointed value is not correctly read");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator writeIter{matrix.zBegin()};

        ++writeIter;
        ++writeIter;
        *writeIter = 10;

        QVERIFY2(matrix.at(0, 2) == 10, "The dereference (*) operator does not work correctly, the value is not correctly written to the pointed location");
    }
}

void ZIteratorTests::testDereferenceArrowOperator()
{
    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixIterator readIter{matrix.zBegin()};

        ++readIter;

        QVERIFY2(readIter->size() == 5, "The dereference (->) operator does not work correctly, the method of the item class does not return the right string size");
    }

    {
        StringMatrix matrix{2, 3, {"abc", "defed", "ghi", "jkl", "mno", "pqr"}};
        StringMatrixIterator writeIter{matrix.zBegin()};

        ++writeIter;
        ++writeIter;

        writeIter->assign("abcdefghi");

        QVERIFY2(matrix.at(0, 2) == "abcdefghi", "The dereference (->) operator does not work correctly, the method of the item class does not write the correct value to the expected location");
    }
}

void ZIteratorTests::testDereferenceSquareBracketsOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator firstReadIter{matrix.zBegin()};
        IntMatrixZIterator secondReadIter{matrix.getZIterator(1, 0)};
        IntMatrixZIterator thirdReadIter{matrix.zEnd()};

        QVERIFY2(firstReadIter[0] == 1 && firstReadIter[1] == 2 && firstReadIter[2] == -3 && firstReadIter[3] == 4 && firstReadIter[4] == -5 && firstReadIter[5] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(secondReadIter[-3] == 1 && secondReadIter[-2] == 2 && secondReadIter[-1] == -3 && secondReadIter[0] == 4 && secondReadIter[1] == -5 && secondReadIter[2] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");

        QVERIFY2(thirdReadIter[-6] == 1 && thirdReadIter[-5] == 2 && thirdReadIter[-4] == -3 && thirdReadIter[-3] == 4 && thirdReadIter[-2] == -5 && thirdReadIter[-1] == 6,
                "The dereference square brackets operator doesn't work correctly, returned value is incorrect for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator writeIter{matrix.zBegin()};

        writeIter[0] = 7;
        writeIter[2] = -8;
        writeIter[5] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -8 && matrix.at(1, 0) == 4 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator writeIter{matrix.getZIterator(1, 0)};

        writeIter[-3] = 7;
        writeIter[0] = -8;
        writeIter[2] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -3 && matrix.at(1, 0) == -8 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        IntMatrixZIterator writeIter{matrix.zEnd()};

        writeIter[-6] = 7;
        writeIter[-3] = -8;
        writeIter[-1] = 9;

        QVERIFY2(matrix.at(0, 0) == 7 && matrix.at(0, 1) == 2 && matrix.at(0, 2) == -3 && matrix.at(1, 0) == -8 && matrix.at(1, 1) == -5 && matrix.at(1, 2) == 9,
                 "The dereference square brackets operator doesn't work correctly, value has been written properly for at least one element");
    }
}

void ZIteratorTests::testIteratorsAreEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
        QVERIFY2(firstIter == matrix.zBegin(), "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");

        ++firstIter;
        ++firstIter;
        ++firstIter;
        ++firstIter;

        QVERIFY2(firstIter == matrix.zEnd(), "The two iterators are not equal");

        secondIter = matrix.zEnd();

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(0, 0)};

        QVERIFY2(it == matrix.zBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(0)};

        QVERIFY2(it == matrix.zBegin(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.getZIterator(1, 2)};
        IntMatrixZIterator secondIter{matrix.getZIterator(5)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.zBegin() == matrix.zEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zBegin() == matrix.zRowBegin(0), "The two iterators are not equal");
        QVERIFY2(matrix.zRowEnd(0) == matrix.zRowBegin(1), "The two iterators are not equal");
        QVERIFY2(matrix.zRowEnd(1) == matrix.zEnd(), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zRowBegin(1) == matrix.getZIterator(1, 0), "The two iterators are not equal");
        QVERIFY2(matrix.zRowEnd(1) == matrix.getZIterator(2, 0), "The two iterators are not equal");
    }

    {
        IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

        QVERIFY2(matrix.zRowBegin(1) == matrix.getZIterator(2), "The two iterators are not equal");
        QVERIFY2(matrix.zRowEnd(1) == matrix.getZIterator(4), "The two iterators are not equal");
    }
}

void ZIteratorTests::testIteratorsAreNotEqual()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        QVERIFY2(matrix.zBegin() != matrix.zEnd(), "The begin iterator equals the end iterator");

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(firstIter != secondIter, "The two iterators are equal");
        QVERIFY2(firstIter != matrix.zBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.zBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.zEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.zEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.getZIterator(0, 1)};
        IntMatrixZIterator secondIter{matrix.getZIterator(1, 2)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.zBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.zBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.zEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.zEnd(), "The second iterator equals the end iterator");
    }

    {
        IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

        QVERIFY2(matrix.zRowBegin(0) != matrix.zRowBegin(1), "The matrix begin ZIterator of the first row equals the begin ZIterator of the second row");
        QVERIFY2(matrix.zRowEnd(0) != matrix.zRowEnd(1), "The matrix end ZIterator of the first row equals the end ZIterator of the second row");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.getZIterator(1)};
        IntMatrixZIterator secondIter{matrix.getZIterator(5)};

        QVERIFY2(firstIter != secondIter, "The begin iterator equals the end iterator");
        QVERIFY2(firstIter != matrix.zBegin(), "The first iterator equals the begin iterator");
        QVERIFY2(secondIter != matrix.zBegin(), "The second iterator equals the begin iterator");
        QVERIFY2(firstIter != matrix.zEnd(), "The first iterator equals the end iterator");
        QVERIFY2(secondIter != matrix.zEnd(), "The second iterator equals the end iterator");
    }
}

void ZIteratorTests::testSmallerThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.zBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.zEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zBegin() < firstIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(firstIter < secondIter, "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(secondIter < matrix.zEnd(), "The first iterator is greater than or equal to the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.zBegin() < matrix.getZIterator(0, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(0, 1) < matrix.zRowBegin(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.zRowBegin(1) < matrix.getZIterator(1, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(1, 1) < matrix.zRowEnd(1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.zRowEnd(1) < matrix.getZIterator(2, 1), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(2, 1) < matrix.zRowBegin(3), "The first iterator is greater than or equal to the second iterator");
        QVERIFY2(matrix.zRowBegin(3) < matrix.zEnd(), "The first iterator is greater than or equal to the second iterator");
    }
}

void ZIteratorTests::testSmallerThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.zBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.zEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.zBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.zEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.zEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zBegin() <= firstIter, "The first iterator is greater than the second iterator");
        QVERIFY2(firstIter <= secondIter, "The first iterator is greater than the second iterator");
        QVERIFY2(secondIter <= matrix.zEnd(), "The first iterator is greater than the second iterator");

    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.zBegin() <= matrix.getZIterator(0, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getZIterator(0, 0) <= matrix.getZIterator(0, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getZIterator(0, 1) <= matrix.zRowBegin(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.zRowBegin(1) <= matrix.getZIterator(1, 1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getZIterator(1, 1) <= matrix.zRowEnd(1), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.zRowEnd(1) <= matrix.getZIterator(2, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getZIterator(2, 0) <= matrix.zRowBegin(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.zRowBegin(3) <= matrix.getZIterator(3, 0), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.getZIterator(3, 0) <= matrix.zRowEnd(3), "The first iterator is greater than the second iterator");
        QVERIFY2(matrix.zRowEnd(3) <= matrix.zEnd(), "The first iterator is greater than the second iterator");
    }
}

void ZIteratorTests::testGreaterThanOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.zEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.zBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zEnd() > secondIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(secondIter > firstIter, "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(firstIter > matrix.zBegin(), "The first iterator is smaller than or equal to the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.zEnd() > matrix.zRowBegin(3), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.zRowBegin(3) > matrix.getZIterator(2, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(2, 1) > matrix.zRowEnd(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.zRowEnd(1) > matrix.getZIterator(1, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(1, 1) > matrix.zRowBegin(1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.zRowBegin(1) > matrix.getZIterator(0, 1), "The first iterator is smaller than or equal to the second iterator");
        QVERIFY2(matrix.getZIterator(0, 1) > matrix.zBegin(), "The first iterator is smaller than or equal to the second iterator");
    }
}

void ZIteratorTests::testGreaterThanOrEqualToOperator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;
        ++secondIter;

        QVERIFY2(matrix.zEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.zBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zBegin()};
        IntMatrixZIterator secondIter{matrix.zBegin()};

        ++firstIter;
        ++secondIter;

        QVERIFY2(matrix.zEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.zBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.zBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator firstIter{matrix.zEnd()};
        IntMatrixZIterator secondIter{matrix.zEnd()};

        --firstIter;
        --secondIter;

        QVERIFY2(matrix.zEnd() >= secondIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(secondIter >= firstIter, "The first iterator is smaller than the second iterator");
        QVERIFY2(firstIter >= matrix.zBegin(), "The first iterator is smaller than the second iterator");
    }

    {
        IntMatrix matrix{4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, -10, 11, 12}};

        QVERIFY2(matrix.zEnd() >= matrix.zRowEnd(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.zRowEnd(3) >= matrix.getZIterator(3, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getZIterator(3, 0) >= matrix.zRowBegin(3), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.zRowBegin(3) >= matrix.getZIterator(2, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getZIterator(2, 0) >= matrix.zRowEnd(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.zRowEnd(1) >= matrix.getZIterator(1, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getZIterator(1, 1) >= matrix.zRowBegin(1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.zRowBegin(1) >= matrix.getZIterator(0, 1), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getZIterator(0, 1) >= matrix.getZIterator(0, 0), "The first iterator is smaller than the second iterator");
        QVERIFY2(matrix.getZIterator(0, 0) >= matrix.zBegin(), "The first iterator is smaller than the second iterator");
    }
}

void ZIteratorTests::testIsValidWithMatrix()
{
    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, {7, 8, -9, 10, -11, 12}};
        IntMatrixZIterator it{firstMatrix.getZIterator(1, 0)};

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
        QVERIFY2(!it.isValidWithMatrix(secondMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 0)};

        matrix.clear();

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 0)};

        matrix.resize(2, 3);

        QVERIFY2(it.isValidWithMatrix(matrix), "The validity function does not return the right value (true)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 0)};

        matrix.resizeWithValue(2, 4, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 0)};

        matrix.resizeWithValue(4, 3, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1, 0)};

        matrix.resizeWithValue(4, 5, -5);

        QVERIFY2(!it.isValidWithMatrix(matrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{3, 2, 5};
        IntMatrixZIterator it{firstMatrix.getZIterator(1, 0)};

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
        IntMatrixZIterator it{firstMatrix.getZIterator(1, 0)};

        firstMatrix = std::move(secondMatrix);

        QVERIFY2(!it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (false)");
    }

    {
        IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrix secondMatrix{2, 3, 5};
        IntMatrixZIterator it{firstMatrix.getZIterator(1, 0)};

        firstMatrix = secondMatrix;

        QVERIFY2(it.isValidWithMatrix(firstMatrix), "The validity function does not return the right value (true)");
    }
}

void ZIteratorTests::testPositionGetters()
{
    IntMatrix firstMatrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrix secondMatrix{2, 3, {7, 8, -9, 10, -11, 12}};

    IntMatrixZIterator it{firstMatrix.getZIterator(1, 0)};

    firstMatrix = std::move(secondMatrix);

    IntMatrixZIterator newIt{firstMatrix.getZIterator(it.getCurrentRowNr(), it.getCurrentColumnNr())};

    QVERIFY2(*newIt == 10, "The position getters do not work correctly, iterator dereferencing does not return the right value");
}

void ZIteratorTests::testGetIterator()
{
    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(0, 1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }

    {
        IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
        IntMatrixZIterator it{matrix.getZIterator(1)};

        QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
    }
}

void ZIteratorTests::testRowBeginEndIterators()
{
    IntMatrix matrix{3, 2, {1, 2, -3, 4, -5, 6}};

    IntMatrixZIterator firstRowBeginIter{matrix.zRowBegin(0)};
    IntMatrixZIterator secondRowEndIter{matrix.zRowEnd(1)};

    QVERIFY2(*firstRowBeginIter == 1, "The matrix begin ZIterator of the first row does not point to the right element");
    QVERIFY2(*secondRowEndIter == -5, "The matrix end ZIterator of the second row does not point to the right element");
}

void ZIteratorTests::testStdCount()
{
    using namespace std;

    IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

    int matchCount{count(matrix.zBegin(), matrix.zEnd(), 2)};
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.zEnd(), -5);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(0, 2), matrix.getZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(0, 2), matrix.getZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(0, 3), matrix.getZIterator(1, 4), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(0, 3), matrix.getZIterator(2, 0), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.getZIterator(2, 3), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(2, 3), matrix.zEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.getZIterator(2, 2), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(2, 2), matrix.zEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(2), matrix.getZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(2), matrix.getZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(3), matrix.getZIterator(9), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(3), matrix.getZIterator(10), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.getZIterator(13), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(13), matrix.zEnd(), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.getZIterator(12), 2);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.getZIterator(12), matrix.zEnd(), 2);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowBegin(1), matrix.zRowEnd(1), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowBegin(1), matrix.zRowEnd(2), 8);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowBegin(2), matrix.zRowEnd(2), 9);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowBegin(2), matrix.zRowEnd(3), 9);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.zRowBegin(1), 1);
    QVERIFY2(matchCount == 2, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowBegin(1), matrix.zEnd(), 1);
    QVERIFY2(matchCount == 1, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zBegin(), matrix.zRowEnd(1), 1);
    QVERIFY2(matchCount == 3, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");

    matchCount = count(matrix.zRowEnd(1), matrix.zEnd(), 1);
    QVERIFY2(matchCount == 0, "The std::count doesn't work correctly with ZIterator, incorrect number of matches returned");
}

void ZIteratorTests::testStdFind()
{
    using namespace std;

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        IntMatrixZIterator it{find(matrix.zBegin(), matrix.zEnd(), 4)};

        ++it;

        QVERIFY2(*it == 5, "The iterator doesn't work correctly with std::find, incorrect next element returned");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 1, 2, -2, 2, 8, 9, -7, 7, 2, 9, 8}};

        QVERIFY2(find(matrix.zBegin(), matrix.zEnd(), 10) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non existing value has been found in the matrix");

        IntMatrixZIterator it{matrix.zBegin()};

        while(it != matrix.zEnd())
        {
            it = find(it, matrix.zEnd(), 9);

            if (it != matrix.zEnd())
            {
                *it = 10;
            }
        }

        int expectedNumber{std::count(matrix.zBegin(), matrix.zEnd(), 10)};

        QVERIFY2(expectedNumber == 3, "The iterator doesn't work properly with std::find, element values haven't been correctly replaced");
    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        QVERIFY2(find(matrix.zBegin(), matrix.zEnd(), 5) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.zEnd(), 10) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), 5) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), 6) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), 8) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), -1) == matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), -2) == matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zRowEnd(1), 10) == matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.zRowBegin(1), matrix.zEnd(), 5) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zEnd(), 11) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zEnd(), -2) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zEnd(), -1) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.zRowBegin(1), matrix.zEnd(), 10) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.zBegin(), matrix.zRowEnd(1), -1) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.zRowEnd(1), 6) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.zRowEnd(1), 8) != matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.zRowEnd(1), -2) == matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.zRowEnd(1), 10) == matrix.zRowEnd(1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), 0) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), -7) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), -2) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), -1) == matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), 11) == matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1), 10) == matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.zEnd(), 0) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.zEnd(), 11) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.zEnd(), -2) != matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.zEnd(), -1) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.getZIterator(1, 3), matrix.zEnd(), 10) == matrix.zEnd(), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");

        QVERIFY2(find(matrix.zBegin(), matrix.getZIterator(3, 1), -1) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.getZIterator(3, 1), -7) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.getZIterator(3, 1), -2) != matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, an existing value hasn't been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.getZIterator(3, 1), 11) == matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
        QVERIFY2(find(matrix.zBegin(), matrix.getZIterator(3, 1), 10) == matrix.getZIterator(3, 1), "The ZIterator doesn't correctly work with std::find, a non-existing value has been found in the given range");
    }
}

void ZIteratorTests::testStdSort()
{
    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, -2, 2, 8, 9, -7, 7, 2, 9, 11}};

        std::sort(matrix.zBegin(), matrix.zEnd());

        QVERIFY2(matrix.at(0, 0) == -7 && matrix.at(0, 1) == -2 && matrix.at(0, 2) == -1 && matrix.at(0, 3) == 0 && matrix.at(0, 4) == 1 &&
                 matrix.at(1, 0) ==  1 && matrix.at(1, 1) ==  2 && matrix.at(1, 2) ==  2 && matrix.at(1, 3) == 2 && matrix.at(1, 4) == 3 &&
                 matrix.at(2, 0) ==  4 && matrix.at(2, 1) ==  5 && matrix.at(2, 2) ==  6 && matrix.at(2, 3) == 7 && matrix.at(2, 4) == 8 &&
                 matrix.at(3, 0) ==  8 && matrix.at(3, 1) ==  9 && matrix.at(3, 2) ==  9 && matrix.at(3, 3) == 9 && matrix.at(3, 4) == 11,

                 "The ZIterator objects don't work correctly, the matrix has not been sorted properly");

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
            std::sort(matrix.zRowBegin(row), matrix.zRowEnd(row));
        }

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 1 && matrix.at(0, 2) == 1 && matrix.at(0, 3) == 3 && matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) ==  0 && matrix.at(1, 1) == 5 && matrix.at(1, 2) == 6 && matrix.at(1, 3) == 8 && matrix.at(1, 4) == 9 &&
                 matrix.at(2, 0) == -2 && matrix.at(2, 1) == 2 && matrix.at(2, 2) == 2 && matrix.at(2, 3) == 8 && matrix.at(2, 4) == 9 &&
                 matrix.at(3, 0) == -7 && matrix.at(3, 1) == 2 && matrix.at(3, 2) == 7 && matrix.at(3, 3) == 9 && matrix.at(3, 4) == 11,

                 "The ZIterator objects don't work correctly, the per row sorting has not been done properly");

    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, (0), 6, 2, -2, 2, 8, 9, -7, (7), 2, 9, 11}};

        std::sort(matrix.getZIterator(1, 3), matrix.getZIterator(3, 1));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 1   && matrix.at(0, 2) == 3 && matrix.at(0, 3) == 1    && matrix.at(0, 4) ==  4 &&
                 matrix.at(1, 0) ==  5 && matrix.at(1, 1) == 9   && matrix.at(1, 2) == 8 && matrix.at(1, 3) == (-7) && matrix.at(1, 4) == -2 &&
                 matrix.at(2, 0) ==  0 && matrix.at(2, 1) == 2   && matrix.at(2, 2) == 2 && matrix.at(2, 3) == 6    && matrix.at(2, 4) ==  8 &&
                 matrix.at(3, 0) ==  9 && matrix.at(3, 1) == (7) && matrix.at(3, 2) == 2 && matrix.at(3, 3) == 9    && matrix.at(3, 4) == 11,

                 "The ZIterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{4, 5, {(-1), 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

        std::sort(matrix.zBegin(), matrix.getZIterator(2, 1));

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 0    && matrix.at(0, 2) == 1 && matrix.at(0, 3) == 1 && matrix.at(0, 4) == 2 &&
                 matrix.at(1, 0) ==  3 && matrix.at(1, 1) == 4    && matrix.at(1, 2) == 5 && matrix.at(1, 3) == 6 && matrix.at(1, 4) == 8 &&
                 matrix.at(2, 0) ==  9 && matrix.at(2, 1) == (-2) && matrix.at(2, 2) == 2 && matrix.at(2, 3) == 8 && matrix.at(2, 4) == 9 &&
                 matrix.at(3, 0) == -7 && matrix.at(3, 1) == 7    && matrix.at(3, 2) == 2 && matrix.at(3, 3) == 9 && matrix.at(3, 4) == 11,

                 "The ZIterator objects don't work correctly, the matrix has not been sorted properly");

    }

    {
        IntMatrix matrix{4, 5, {-1, 1, 3, 1, 4, 5, 9, 8, 0, 6, 2, (-2), 2, 8, 9, -7, 7, 2, 9, 11}};

        std::sort(matrix.getZIterator(2, 1), matrix.zEnd());

        QVERIFY2(matrix.at(0, 0) == -1 && matrix.at(0, 1) == 1    && matrix.at(0, 2) == 3  && matrix.at(0, 3) == 1 && matrix.at(0, 4) == 4 &&
                 matrix.at(1, 0) ==  5 && matrix.at(1, 1) == 9    && matrix.at(1, 2) == 8  && matrix.at(1, 3) == 0 && matrix.at(1, 4) == 6 &&
                 matrix.at(2, 0) ==  2 && matrix.at(2, 1) == (-7) && matrix.at(2, 2) == -2 && matrix.at(2, 3) == 2 && matrix.at(2, 4) == 2 &&
                 matrix.at(3, 0) ==  7 && matrix.at(3, 1) == 8    && matrix.at(3, 2) == 9  && matrix.at(3, 3) == 9 && matrix.at(3, 4) == 11,

                 "The ZIterator objects don't work correctly, the matrix has not been sorted properly");

    }
}

void ZIteratorTests::testIteratingWithAuto()
{
    {
        IntMatrix matrix{2, 3, {-1, 2, -3, 4, -5, 6}};

        int sum{0};
        int prod{1};
        int count{0};

        for (auto element : matrix)
        {
            sum += element;
            prod *= element;
            ++count;
        }

        QVERIFY2(sum == 3 && prod == -720 && count == 6, "Iterating through the matrix elements by using the auto keyword does not work correctly");
    }
}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortests.moc"
