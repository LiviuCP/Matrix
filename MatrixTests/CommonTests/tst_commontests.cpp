#include <QtTest>

// add necessary includes here

class CommonTests : public QObject
{
    Q_OBJECT

public:
    CommonTests();
    ~CommonTests();

private slots:
    void test_case1();

};

CommonTests::CommonTests()
{

}

CommonTests::~CommonTests()
{

}

void CommonTests::test_case1()
{

}

QTEST_APPLESS_MAIN(CommonTests)

#include "tst_commontests.moc"
