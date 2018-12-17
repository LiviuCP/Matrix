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
    void testResizeAndRemoveOldValuesExceptions();
    void testResizeAndKeepOldValuesExceptions();
    void testTransformToDiagMatrixExceptions();
    void testTransformToEqualElementsMatrixExceptions();
    void testInsertRowNoSetValue();
    void testInsertRowSetValue();
    void testInsertColumnNoSetValue();
    void testInsertColumnSetValue();
    void testEraseRow();
    void testEraseColumn();
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

void ExceptionTests::testResizeAndRemoveOldValuesExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, 0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, 4);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, 0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, 4);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.resize(3, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(3, 0);}, std::runtime_error);
}

void ExceptionTests::testResizeAndKeepOldValuesExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(-3, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(0, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.resize(3, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.resize(3, 0, 5);}, std::runtime_error);
}

void ExceptionTests::testTransformToDiagMatrixExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix.transformToDiagMatrix(-4, 2, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToDiagMatrix(0, 2, 5);}, std::runtime_error);
}

void ExceptionTests::testTransformToEqualElementsMatrixExceptions()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(-3, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(-3, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(-3, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(0, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(0, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(0, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(3, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({matrix.transformToEqualElementsMatrix(3, -4, 5);}, std::runtime_error);
}

void ExceptionTests::testInsertRowNoSetValue()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3);}, std::runtime_error);
}

void ExceptionTests::testInsertRowSetValue()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3, 5);}, std::runtime_error);
}

void ExceptionTests::testInsertColumnNoSetValue()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4);}, std::runtime_error);
}

void ExceptionTests::testInsertColumnSetValue()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4, 5);}, std::runtime_error);
}

void ExceptionTests::testEraseRow()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(2);}, std::runtime_error);
}

void ExceptionTests::testEraseColumn()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(3);}, std::runtime_error);
}

QTEST_APPLESS_MAIN(ExceptionTests)

#include "tst_exceptiontests.moc"
