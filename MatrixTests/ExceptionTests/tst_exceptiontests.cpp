#include <QtTest>

#include "../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;

class ExceptionTests : public QObject
{
    Q_OBJECT

public:
    ExceptionTests();
    ~ExceptionTests();

private slots:
    void testInitListConstructorExceptions();
    void testIdenticalMatrixConstructorExceptions();
    void testDiagMatrixConstructorExceptions();
    void testFunctionAtExceptions();
    void testSquareBracketsOperatorExceptions();
};

ExceptionTests::ExceptionTests()
{

}

ExceptionTests::~ExceptionTests()
{

}

void ExceptionTests::testInitListConstructorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, -2, {1, 2, 3, 4});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, 0, {1, 2, 3, 4});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, 2, {1, 2, 3, 4});}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, -2, {1, 2, 3, 4});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, 0, {1, 2, 3, 4});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, 2, {1, 2, 3, 4});}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 0, {1, 2, 3, 4});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, -2, {1, 2, 3, 4});}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4});}, std::runtime_error);
}

void ExceptionTests::testIdenticalMatrixConstructorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, -2, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, 2, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, -2, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, 2, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, -2, 5);}, std::runtime_error);
}

void ExceptionTests::testDiagMatrixConstructorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, std::pair<int, int>{2, 5});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, std::pair<int, int>{2, 5});}, std::runtime_error);
}

void ExceptionTests::testFunctionAtExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix.at(-1, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(-1, 1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(-1, 3) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(1, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(1, 3) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(2, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(2, 1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.at(2, 3) = 0;}, std::runtime_error);
}

void ExceptionTests::testSquareBracketsOperatorExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix[-1] = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix[6] = 0;}, std::runtime_error);
}



QTEST_APPLESS_MAIN(ExceptionTests)

#include "tst_exceptiontests.moc"
