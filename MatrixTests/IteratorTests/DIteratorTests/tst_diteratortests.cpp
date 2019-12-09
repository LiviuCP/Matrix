#include <QtTest>

#include "../../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixDIterator = Matrix<int>::DIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixDIterator = Matrix<std::string>::DIterator;

class DIteratorTests : public QObject
{
    Q_OBJECT

public:
    DIteratorTests();
    ~DIteratorTests();

private slots:
    void emptyTest();
};

DIteratorTests::DIteratorTests()
{

}

DIteratorTests::~DIteratorTests()
{

}

void DIteratorTests::emptyTest()
{
    IntMatrixDIterator it;
    Q_UNUSED(it);
    QVERIFY(true == true);
}

QTEST_APPLESS_MAIN(DIteratorTests)

#include "tst_diteratortests.moc"
