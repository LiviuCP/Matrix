#include <QtTest>

// add necessary includes here

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

}

QTEST_APPLESS_MAIN(MatrixTest)

#include "tst_matrixtest.moc"
