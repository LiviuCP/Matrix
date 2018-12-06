#include <QtTest>

// add necessary includes here

class DecimalMatrixTests : public QObject
{
    Q_OBJECT

public:
    DecimalMatrixTests();
    ~DecimalMatrixTests();

private slots:
    void test_case1();

};

DecimalMatrixTests::DecimalMatrixTests()
{

}

DecimalMatrixTests::~DecimalMatrixTests()
{

}

void DecimalMatrixTests::test_case1()
{

}

QTEST_APPLESS_MAIN(DecimalMatrixTests)

#include "tst_decimalmatrixtests.moc"
