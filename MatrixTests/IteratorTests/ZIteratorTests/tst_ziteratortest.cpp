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
        IntMatrix matrix{};
        int count{0};

        for (IntMatrixZIterator it{matrix.zBegin()}; it != matrix.zEnd(); ++it)
        {
            ++count;
        }

        QVERIFY2(count == 0, "The Z Iterator does not work correctly, there are no elements to pass through");
    }
}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortest.moc"
