#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixZIterator = Matrix<int>::ZIterator;

class ZIteratorTests : public QObject
{
    Q_OBJECT

public:
    ZIteratorTests();
    ~ZIteratorTests();

private slots:
    void testPassingThroughAllElements();
    void testIncrementOperators();
    void testDereferenceStarOperator();
    void testIteratorsAreEqual();
    void testIteratorsAreNotEqual();
    void testGetIterator();
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
        IntMatrix matrix{};
        int count{0};

        for (IntMatrixZIterator it{matrix.zBegin()}; it != matrix.zEnd(); ++it)
        {
            ++count;
        }

        QVERIFY2(count == 0, "The Z Iterator does not work correctly, there are no elements to pass through");
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
        IntMatrixZIterator firstIter{matrix.getZIterator(1, 2)};
        IntMatrixZIterator secondIter{matrix.getZIterator(1, 2)};

        QVERIFY2(firstIter == secondIter, "The two iterators are not equal");
    }

    {
        IntMatrix matrix{};

        QVERIFY2(matrix.zBegin() == matrix.zEnd(), "The two iterators are not equal");
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
}

void ZIteratorTests::testGetIterator()
{
    IntMatrix matrix{2, 3, {1, 2, -3, 4, -5, 6}};
    IntMatrixZIterator it{matrix.getZIterator(0, 1)};

    QVERIFY2(*it == 2, "The getIterator() method does not work correctly, the resulting iterator does not point to the right element");
}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortest.moc"
