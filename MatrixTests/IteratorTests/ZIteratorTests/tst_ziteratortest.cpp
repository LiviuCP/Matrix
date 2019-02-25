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
    void test_case1();

};

ZIteratorTests::ZIteratorTests()
{

}

ZIteratorTests::~ZIteratorTests()
{

}

void ZIteratorTests::test_case1()
{

}

QTEST_APPLESS_MAIN(ZIteratorTests)

#include "tst_ziteratortest.moc"
