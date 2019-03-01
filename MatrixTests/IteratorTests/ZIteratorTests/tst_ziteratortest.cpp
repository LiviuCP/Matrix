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
    void testRowBeginEndIterators();
    void testStdCount();
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

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortest.moc"
