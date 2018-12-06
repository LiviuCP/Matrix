#include <QtTest>

// add necessary includes here

class ExceptionTests : public QObject
{
    Q_OBJECT

public:
    ExceptionTests();
    ~ExceptionTests();

private slots:
    void test_case1();

};

ExceptionTests::ExceptionTests()
{

}

ExceptionTests::~ExceptionTests()
{

}

void ExceptionTests::test_case1()
{

}

QTEST_APPLESS_MAIN(ExceptionTests)

#include "tst_exceptiontests.moc"
