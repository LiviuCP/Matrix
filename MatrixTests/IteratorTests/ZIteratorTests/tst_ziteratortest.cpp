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
    void testDereferenceStarOperator();
    void testDereferenceArrowOperator();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testSmallerThanOperator();
    void testSmallerThanOrEqualToOperator();
    void testGreaterThanOperator();
    void testGreaterThanOrEqualToOperator();
    void testGetIterator();
    void testRowBeginEndIterators();
    void testStdCount();
    void testStdFind();
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

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortest.moc"
