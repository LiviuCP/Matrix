#include <QtTest>

#include "../MatrixLib/matrix.h"

class MatrixTest : public QObject
{
    Q_OBJECT

public:
    MatrixTest();
    ~MatrixTest();

private slots:
    void test_case1();

};

MatrixTest::MatrixTest()
{

}

MatrixTest::~MatrixTest()
{

}

void MatrixTest::test_case1()
{
    Matrix<int> matrix{};
    matrix.resize(1,1);
}

QTEST_APPLESS_MAIN(MatrixTest)

#include "tst_matrixtest.moc"
