#include <QtTest>

// add necessary includes here

class IntMatrixTests : public QObject
{
    Q_OBJECT

public:
    IntMatrixTests();
    ~IntMatrixTests();

private slots:
    void test_case1();

};

IntMatrixTests::IntMatrixTests()
{

}

IntMatrixTests::~IntMatrixTests()
{

}

void IntMatrixTests::test_case1()
{

}

QTEST_APPLESS_MAIN(IntMatrixTests)

#include "tst_intmatrixtests.moc"
