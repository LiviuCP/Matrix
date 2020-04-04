#include <QtTest>

#include "../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;
using IntMatrixZIterator = Matrix<int>::ZIterator;
using IntMatrixConstZIterator = Matrix<int>::ConstZIterator;
using IntMatrixReverseZIterator = Matrix<int>::ReverseZIterator;
using IntMatrixConstReverseZIterator = Matrix<int>::ConstReverseZIterator;
using IntMatrixDIterator = Matrix<int>::DIterator;
using IntMatrixConstDIterator = Matrix<int>::ConstDIterator;
using IntMatrixReverseDIterator = Matrix<int>::ReverseDIterator;
using StringMatrix = Matrix<std::string>;
using StringMatrixZIterator = Matrix<std::string>::ZIterator;
using StringMatrixConstZIterator = Matrix<std::string>::ConstZIterator;
using StringMatrixReverseZIterator = Matrix<std::string>::ReverseZIterator;
using StringMatrixConstReverseZIterator = Matrix<std::string>::ConstReverseZIterator;
using StringMatrixDIterator = Matrix<std::string>::DIterator;
using StringMatrixConstDIterator = Matrix<std::string>::ConstDIterator;
using StringMatrixReverseDIterator = Matrix<std::string>::ReverseDIterator;

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
    void testInsertRowNoSetValueExceptions();
    void testInsertRowSetValueExceptions();
    void testInsertColumnNoSetValueExceptions();
    void testInsertColumnSetValueExceptions();
    void testEraseRowExceptions();
    void testEraseColumnExceptions();
    void testCatByRowExceptions();
    void testCatByColumnExceptions();
    void testSplitByRowExceptions();
    void testSplitByColumnExceptions();
    void testSwapItemsExceptions();
    void testSwapRowsExceptions();
    void testSwapColumnsExceptions();
    void testSwapRowColumnExceptions();
    void testCopyExceptions();
    void testZIteratorExceptions();
    void testConstZIteratorExceptions();
    void testReverseZIteratorExceptions();
    void testConstReverseZIteratorExceptions();
    void testDIteratorExceptions();
    void testConstDIteratorExceptions();
    void testReverseDIteratorExceptions();
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
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.at(0, 0) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(-1, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(-1, 1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(-1, 3) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(1, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(1, 3) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(2, -1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(2, 1) = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.at(2, 3) = 0;}, std::runtime_error);
}

void ExceptionTests::testSquareBracketsOperatorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix[-1] = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix[6] = 0;}, std::runtime_error);
}

void ExceptionTests::testResizeAndRemoveOldValuesExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(-3, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(-3, 0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(-3, 4);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(0, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(0, 0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(0, 4);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(3, -4);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resize(3, 0);}, std::runtime_error);
}

void ExceptionTests::testResizeAndKeepOldValuesExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(-3, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(-3, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(-3, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(0, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(0, 0, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(0, 4, 5);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(3, -4, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.resizeWithValue(3, 0, 5);}, std::runtime_error);
}

void ExceptionTests::testInsertRowNoSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertRow(0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3);}, std::runtime_error);
}

void ExceptionTests::testInsertRowSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertRow(0, 1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3, 5);}, std::runtime_error);
}

void ExceptionTests::testInsertColumnNoSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertColumn(0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4);}, std::runtime_error);
}

void ExceptionTests::testInsertColumnSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertColumn(0, 2);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4, 5);}, std::runtime_error);
}

void ExceptionTests::testEraseRowExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(2);}, std::runtime_error);
}

void ExceptionTests::testEraseColumnExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(3);}, std::runtime_error);
}

void ExceptionTests::testCatByRowExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstSrcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondSrcMatrix(2, 2, {7, 8, 9, 10});
                                  IntMatrix destMatrix;

                                  destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix);
                             },

                             std::runtime_error);
}

void ExceptionTests::testCatByColumnExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstSrcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondSrcMatrix(2, 2, {7, 8, 9, 10});
                                  IntMatrix destMatrix;

                                  destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSplitByRowExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstSecondDestMatrix;

                                  srcMatrix.splitByRow(firstSecondDestMatrix, firstSecondDestMatrix, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcFirstSecondDestMatrix(2, 3, {1, 2, 3, 4, 5, 6});

                                  srcFirstSecondDestMatrix.splitByRow(srcFirstSecondDestMatrix, srcFirstSecondDestMatrix, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, 0);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, 2);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSplitByColumnExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstSecondDestMatrix;

                                  srcMatrix.splitByColumn(firstSecondDestMatrix, firstSecondDestMatrix, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destFirstSecondSrcMatrix(3, 2, {1, 2, 3, 4, 5, 6});

                                  destFirstSecondSrcMatrix.splitByColumn(destFirstSecondSrcMatrix, destFirstSecondSrcMatrix, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, 0);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix srcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix firstDestMatrix;
                                  IntMatrix secondDestMatrix;

                                  srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, 2);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSwapItemsExceptions()
{
    // test invalid negative indexes

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, 1, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, 1, secondMatrix, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, 1, secondMatrix, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, 1, secondMatrix, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, -1, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, -1, secondMatrix, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, -1, secondMatrix, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, -1, secondMatrix, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, -1, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, -1, secondMatrix, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, -1, secondMatrix, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(-1, -1, secondMatrix, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, -1, -1);
                             },

                             std::runtime_error);

    // test invalid positive indexes (out of range)

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 1, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 1, secondMatrix, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 1, secondMatrix, 1, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 1, secondMatrix, 2, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, 2, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, 2, secondMatrix, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, 2, secondMatrix, 1, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(1, 2, secondMatrix, 2, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 2, secondMatrix, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 2, secondMatrix, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 2, secondMatrix, 1, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(3, 2, secondMatrix, 2, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, 1, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapItems(0, 1, secondMatrix, 2, 3);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSwapRowsExceptions()
{
    // test negative column index
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(-1, secondMatrix, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(1, secondMatrix, -2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(-1, secondMatrix, -2);
                             },

                             std::runtime_error);

    // test row index out of range
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(1, secondMatrix, 4);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(3, secondMatrix, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(4, 2, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRows(3, secondMatrix, 4);
                             },

                             std::runtime_error);

    // test unequal length rows
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapRows(1, secondMatrix, 0);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSwapColumnsExceptions()
{
    // test negative column index
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(-1, secondMatrix, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(1, secondMatrix, -2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(-1, secondMatrix, -2);
                             },

                             std::runtime_error);

    // test column index out of range
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(1, secondMatrix, 4);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(3, secondMatrix, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapColumns(3, secondMatrix, 4);
                             },

                             std::runtime_error);

    // test unequal length columns
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 3, {7, 8, 9, 10, 11, 12});

                                  firstMatrix.swapColumns(1, secondMatrix, 0);
                             },

                             std::runtime_error);
}

void ExceptionTests::testSwapRowColumnExceptions()
{
    // test negative row/column index
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(-1, secondMatrix, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(0, secondMatrix, -3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(-1, secondMatrix, -3);
                             },

                             std::runtime_error);

    // test row/column index out of range
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(2, secondMatrix, 3);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(0, secondMatrix, 4);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18});

                                  firstMatrix.swapRowColumn(2, secondMatrix, 4);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondMatrix(2, 4, {7, 8, 9, 10, 11, 12, 13, 14});

                                  firstMatrix.swapRowColumn(1, firstMatrix, 3);
                             },

                             std::runtime_error);

    //test same matrix exception
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstMatrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9});

                                  firstMatrix.swapRowColumn(1, firstMatrix, 2);
                             },

                             std::runtime_error);
}

void ExceptionTests::testCopyExceptions()
{
    // test negative argument exceptions
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, 2, 2, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, -2, 2, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, -2, 2, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, -1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, -1, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, -1, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, -1,- 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, 1, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, 1, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, 1, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, -1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, -1, 1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, -1, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, -2, -1, -1, -1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, 2, -2, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, -2, -2, -1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, -2, -2, -1, -1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, -3, -2, -2, -1, -1, -1);
                             },

                             std::runtime_error);

    //test same matrix exception
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});

                                  matrix.copy(matrix, 2, 2, 0, 0, 0, 1);
                             },

                             std::runtime_error);

    // test out of range element copying
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 1, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 1, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 1, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 1, 2, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 3, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 3, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 3, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 3, 2, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 3, 1, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 3, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 3, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 3, 3, 2, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, 2, 1);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, 1, 2);
                             },

                             std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix destMatrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12});
                                  IntMatrix srcMatrix(5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32});

                                  destMatrix.copy(srcMatrix, 3, 2, 2, 1, 2, 2);
                             },

                             std::runtime_error);
}

void ExceptionTests::testZIteratorExceptions()
{
    // test zBegin() and zEnd() dereference errors
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it{matrix.zBegin()}; *it = -9;  }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it{matrix.zEnd()};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixZIterator it{matrix.zEnd()};   *it = -14; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixZIterator it{matrix.zBegin()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixZIterator it{matrix.zEnd()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixZIterator it{matrix.zEnd()}; Q_UNUSED(it->size());}, std::runtime_error);

    // test wrong indexes (negative or out-of-bound)
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(-1, 0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(0, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(0, 0);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(-1, 1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(-1, 3);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(1, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(1, 3);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(2, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(2, 1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(2, 3);   Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixZIterator it = matrix.getZIterator(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixZIterator it = matrix.getZIterator(6);  Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it = matrix.zRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it = matrix.zRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it = matrix.zRowBegin(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixZIterator it = matrix.zRowEnd(0);    Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixZIterator it = matrix.zRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixZIterator it = matrix.zRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixZIterator it = matrix.zRowBegin(4);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixZIterator it = matrix.zRowEnd(4);    Q_UNUSED(it)}, std::runtime_error);

    // test iterators pointing to different matrixes
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); int diff{firstMatrix.zEnd() - secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); int diff{firstMatrix.zEnd() - secondMatrix.zBegin()};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); int diff{firstMatrix.zBegin() - secondMatrix.zEnd()};
                              Q_UNUSED(diff);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areEqual{firstMatrix.zEnd() == secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areEqual{firstMatrix.zEnd() == secondMatrix.zBegin()};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areEqual{firstMatrix.zBegin() == secondMatrix.zEnd()};
                              Q_UNUSED(areEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areNotEqual{firstMatrix.zEnd() != secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areNotEqual{firstMatrix.zEnd() != secondMatrix.zBegin()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areNotEqual{firstMatrix.zBegin() != secondMatrix.zEnd()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThan{firstMatrix.zEnd() < secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThan{firstMatrix.zEnd() < secondMatrix.zBegin()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThan{firstMatrix.zBegin() < secondMatrix.zEnd()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThanOrEqualTo{firstMatrix.zEnd() <= secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThanOrEqualTo{firstMatrix.zEnd() <= secondMatrix.zBegin()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThanOrEqualTo{firstMatrix.zBegin() <= secondMatrix.zEnd()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThan{firstMatrix.zEnd() > secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThan{firstMatrix.zEnd() > secondMatrix.zBegin()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThan{firstMatrix.zBegin() > secondMatrix.zEnd()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThanOrEqualTo{firstMatrix.zEnd() >= secondMatrix.getZIterator(1, 0)};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThanOrEqualTo{firstMatrix.zEnd() >= secondMatrix.zBegin()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThanOrEqualTo{firstMatrix.zBegin() >= secondMatrix.zEnd()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);

    //test dereference bracket operator exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zBegin()}; it[-2] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zBegin()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zBegin()}; it[6] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zBegin()}; it[7] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.getZIterator(1, 0)}; it[-5] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.getZIterator(1, 0)}; it[-4] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.getZIterator(1, 0)}; it[3] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.getZIterator(1, 0)}; it[4] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zEnd()}; it[-8] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zEnd()}; it[-7] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zEnd()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixZIterator it{matrix.zEnd()}; it[1] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zBegin()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zBegin()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zBegin()}; it[1] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zEnd()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zEnd()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixZIterator it{matrix.zEnd()}; it[1] = 7; }, std::runtime_error);
}

void ExceptionTests::testConstZIteratorExceptions()
{
    // test zBegin() and zEnd() dereference errors
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED((*it).size());}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED((*it).size());}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED((*it).size());}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it->size());}, std::runtime_error);

    // test wrong indexes (negative or out-of-bound)
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(-1, 0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(0, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(0, 0);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(-1, 1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(-1, 3);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(1, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(1, 3);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(2, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(2, 1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(2, 3);   Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstZIterator it = matrix.getConstZIterator(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstZIterator it = matrix.getConstZIterator(6);  Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstZIterator it = matrix.constZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstZIterator it = matrix.constZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstZIterator it = matrix.constZRowBegin(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstZIterator it = matrix.constZRowEnd(0);    Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstZIterator it = matrix.constZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstZIterator it = matrix.constZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstZIterator it = matrix.constZRowBegin(4);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstZIterator it = matrix.constZRowEnd(4);    Q_UNUSED(it)}, std::runtime_error);

    // test iterators pointing to different matrixes
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); int diff{firstMatrix.constZEnd() - secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); int diff{firstMatrix.constZEnd() - secondMatrix.constZBegin()};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); int diff{firstMatrix.constZBegin() - secondMatrix.constZEnd()};
                              Q_UNUSED(diff);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areEqual{firstMatrix.constZEnd() == secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areEqual{firstMatrix.constZEnd() == secondMatrix.constZBegin()};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areEqual{firstMatrix.constZBegin() == secondMatrix.constZEnd()};
                              Q_UNUSED(areEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areNotEqual{firstMatrix.constZEnd() != secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areNotEqual{firstMatrix.constZEnd() != secondMatrix.constZBegin()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areNotEqual{firstMatrix.constZBegin() != secondMatrix.constZEnd()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThan{firstMatrix.constZEnd() < secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThan{firstMatrix.constZEnd() < secondMatrix.constZBegin()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThan{firstMatrix.constZBegin() < secondMatrix.constZEnd()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThanOrEqualTo{firstMatrix.constZEnd() <= secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThanOrEqualTo{firstMatrix.constZEnd() <= secondMatrix.constZBegin()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThanOrEqualTo{firstMatrix.constZBegin() <= secondMatrix.constZEnd()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThan{firstMatrix.constZEnd() > secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThan{firstMatrix.constZEnd() > secondMatrix.constZBegin()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThan{firstMatrix.constZBegin() > secondMatrix.constZEnd()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThanOrEqualTo{firstMatrix.constZEnd() >= secondMatrix.getConstZIterator(1, 0)};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThanOrEqualTo{firstMatrix.constZEnd() >= secondMatrix.constZBegin()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThanOrEqualTo{firstMatrix.constZBegin() >= secondMatrix.constZEnd()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);

    //test dereference bracket operator exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[-2]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[6]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[7]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)}; Q_UNUSED(it[-5]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)}; Q_UNUSED(it[-4]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)}; Q_UNUSED(it[3]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.getConstZIterator(1, 0)}; Q_UNUSED(it[4]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[-8]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[-7]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[1]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZBegin()}; Q_UNUSED(it[1]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstZIterator it{matrix.constZEnd()}; Q_UNUSED(it[1]); }, std::runtime_error);
}

void ExceptionTests::testReverseZIteratorExceptions()
{
    // test zBegin() and zEnd() dereference errors
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it{matrix.reverseZBegin()}; *it = -9;  }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it{matrix.reverseZEnd()};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseZIterator it{matrix.reverseZEnd()};   *it = -14; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZBegin()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED(it->size());}, std::runtime_error);

    // test wrong indexes (negative or out-of-bound)
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1, 0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(0, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(0, 0);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1, 1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1, 3);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(1, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(1, 3);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(2, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(2, 1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(2, 3);   Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixReverseZIterator it = matrix.getReverseZIterator(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixReverseZIterator it = matrix.getReverseZIterator(6);  Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it = matrix.reverseZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it = matrix.reverseZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it = matrix.reverseZRowBegin(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixReverseZIterator it = matrix.reverseZRowEnd(0);    Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseZIterator it = matrix.reverseZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseZIterator it = matrix.reverseZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseZIterator it = matrix.reverseZRowBegin(4);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseZIterator it = matrix.reverseZRowEnd(4);    Q_UNUSED(it)}, std::runtime_error);

    // test iterators pointing to different matrixes
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); int diff{firstMatrix.reverseZEnd() - secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); int diff{firstMatrix.reverseZEnd() - secondMatrix.reverseZBegin()};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); int diff{firstMatrix.reverseZBegin() - secondMatrix.reverseZEnd()};
                              Q_UNUSED(diff);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areEqual{firstMatrix.reverseZEnd() == secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areEqual{firstMatrix.reverseZEnd() == secondMatrix.reverseZBegin()};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areEqual{firstMatrix.reverseZBegin() == secondMatrix.reverseZEnd()};
                              Q_UNUSED(areEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areNotEqual{firstMatrix.reverseZEnd() != secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areNotEqual{firstMatrix.reverseZEnd() != secondMatrix.reverseZBegin()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areNotEqual{firstMatrix.reverseZBegin() != secondMatrix.reverseZEnd()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThan{firstMatrix.reverseZEnd() < secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThan{firstMatrix.reverseZEnd() < secondMatrix.reverseZBegin()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThan{firstMatrix.reverseZBegin() < secondMatrix.reverseZEnd()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThanOrEqualTo{firstMatrix.reverseZEnd() <= secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThanOrEqualTo{firstMatrix.reverseZEnd() <= secondMatrix.reverseZBegin()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThanOrEqualTo{firstMatrix.reverseZBegin() <= secondMatrix.reverseZEnd()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThan{firstMatrix.reverseZEnd() > secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThan{firstMatrix.reverseZEnd() > secondMatrix.reverseZBegin()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThan{firstMatrix.reverseZBegin() > secondMatrix.reverseZEnd()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThanOrEqualTo{firstMatrix.reverseZEnd() >= secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThanOrEqualTo{firstMatrix.reverseZEnd() >= secondMatrix.reverseZBegin()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThanOrEqualTo{firstMatrix.reverseZBegin() >= secondMatrix.reverseZEnd()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);

    //test dereference bracket operator exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[-2] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[6] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[7] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)}; it[-4] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)}; it[-3] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)}; it[4] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.getReverseZIterator(1, 0)}; it[5] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[-8] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[-7] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[1] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZBegin()}; it[1] = 7; }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[-1] = 7;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[0] = 7; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseZIterator it{matrix.reverseZEnd()}; it[1] = 7; }, std::runtime_error);
}

void ExceptionTests::testConstReverseZIteratorExceptions()
{
    // test zBegin() and zEnd() dereference errors
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZBegin()}; Q_UNUSED((*it).size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED((*it).size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED((*it).size());}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZBegin()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix; StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED(it->size()); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(2, 3, {"abc", "def", "ghi", "jkl", "mno", "pqr"}); StringMatrixReverseZIterator it{matrix.reverseZEnd()}; Q_UNUSED(it->size());}, std::runtime_error);

    // test wrong indexes (negative or out-of-bound)
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1, 0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(0, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(0, 0);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1, -1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1, 1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1, 3);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(1, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(1, 3);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(2, -1);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(2, 1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(2, 3);   Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                           IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); IntMatrixConstReverseZIterator it = matrix.getConstReverseZIterator(6);  Q_UNUSED(it)}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstReverseZIterator it = matrix.constReverseZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstReverseZIterator it = matrix.constReverseZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstReverseZIterator it = matrix.constReverseZRowBegin(0);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix;                                                IntMatrixConstReverseZIterator it = matrix.constReverseZRowEnd(0);    Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstReverseZIterator it = matrix.constReverseZRowBegin(-1); Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstReverseZIterator it = matrix.constReverseZRowEnd(-1);   Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstReverseZIterator it = matrix.constReverseZRowBegin(4);  Q_UNUSED(it)}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstReverseZIterator it = matrix.constReverseZRowEnd(4);    Q_UNUSED(it)}, std::runtime_error);

    // test iterators pointing to different matrixes
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); int diff{firstMatrix.reverseZEnd() - secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); int diff{firstMatrix.reverseZEnd() - secondMatrix.reverseZBegin()};
                              Q_UNUSED(diff);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); int diff{firstMatrix.reverseZBegin() - secondMatrix.reverseZEnd()};
                              Q_UNUSED(diff);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areEqual{firstMatrix.reverseZEnd() == secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areEqual{firstMatrix.reverseZEnd() == secondMatrix.reverseZBegin()};
                              Q_UNUSED(areEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areEqual{firstMatrix.reverseZBegin() == secondMatrix.reverseZEnd()};
                              Q_UNUSED(areEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool areNotEqual{firstMatrix.reverseZEnd() != secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool areNotEqual{firstMatrix.reverseZEnd() != secondMatrix.reverseZBegin()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool areNotEqual{firstMatrix.reverseZBegin() != secondMatrix.reverseZEnd()};
                              Q_UNUSED(areNotEqual);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThan{firstMatrix.reverseZEnd() < secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThan{firstMatrix.reverseZEnd() < secondMatrix.reverseZBegin()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThan{firstMatrix.reverseZBegin() < secondMatrix.reverseZEnd()};
                              Q_UNUSED(isSmallerThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isSmallerThanOrEqualTo{firstMatrix.reverseZEnd() <= secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isSmallerThanOrEqualTo{firstMatrix.reverseZEnd() <= secondMatrix.reverseZBegin()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isSmallerThanOrEqualTo{firstMatrix.reverseZBegin() <= secondMatrix.reverseZEnd()};
                              Q_UNUSED(isSmallerThanOrEqualTo);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThan{firstMatrix.reverseZEnd() > secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThan{firstMatrix.reverseZEnd() > secondMatrix.reverseZBegin()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThan{firstMatrix.reverseZBegin() > secondMatrix.reverseZEnd()};
                              Q_UNUSED(isGreaterThan);}, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(2, 3, -5); bool isGreaterThanOrEqualTo{firstMatrix.reverseZEnd() >= secondMatrix.getReverseZIterator(1, 0)};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(firstMatrix); bool isGreaterThanOrEqualTo{firstMatrix.reverseZEnd() >= secondMatrix.reverseZBegin()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix firstMatrix(2, 3, 4); IntMatrix secondMatrix(std::move(firstMatrix)); bool isGreaterThanOrEqualTo{firstMatrix.reverseZBegin() >= secondMatrix.reverseZEnd()};
                              Q_UNUSED(isGreaterThanOrEqualTo);}, std::runtime_error);

    //test dereference bracket operator exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[-2]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[6]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[7]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)}; Q_UNUSED(it[-4]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)}; Q_UNUSED(it[-3]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)}; Q_UNUSED(it[4]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.getConstReverseZIterator(1, 0)}; Q_UNUSED(it[5]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[-8]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[-7]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[1]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZBegin()}; Q_UNUSED(it[1]); }, std::runtime_error);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[-1]);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstReverseZIterator it{matrix.constReverseZEnd()}; Q_UNUSED(it[1]); }, std::runtime_error);
}

void ExceptionTests::testDIteratorExceptions()
{
    // iterator creation
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.dBegin(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.dBegin(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.dEnd(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.dEnd(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.getDIterator(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixDIterator it{matrix.getDIterator(0, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dBegin(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.dEnd(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-2, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-2, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(3, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(3, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(0, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(0, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(1, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-1, 1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixDIterator it{matrix.getDIterator(-1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    // equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    // not equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    // smaller than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    // smaller than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    // greater than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    // greater than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 2)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(-1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    // difference operator exceptions
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.getDIterator(2, 1)};
                                 IntMatrixDIterator secondIt{matrix.getDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{matrix.dEnd(1, 2)};
                                 IntMatrixDIterator secondIt{matrix.dEnd(-1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(1, 2)};
                                 IntMatrixDIterator secondIt{secondMatrix.getDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixDIterator firstIt{firstMatrix.getDIterator(-1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixDIterator secondIt{firstMatrix.getDIterator(2, 1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    // dereference exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.dEnd(-1)};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.dEnd(0, 2)};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixDIterator it{matrix.dEnd(-1)};  it->assign("c"); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixDIterator it{matrix.dEnd(0, 2)}; it->assign("c"); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.dBegin(0, 1)};   it[-1] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.dEnd(0, 0)};   it[0] = 14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.getDIterator(2, 1)};   it[2] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.getDIterator(0, 1, true)};   it[-2] = 14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.getDIterator(1, 0, true)};   it[3] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixDIterator it{matrix.dBegin(-1)};   it[-2] = 14; }, std::runtime_error);
}

void ExceptionTests::testConstDIteratorExceptions()
{
    // iterator creation
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.constDBegin(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.constDBegin(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.constDEnd(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.constDEnd(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.getConstDIterator(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixConstDIterator it{matrix.getConstDIterator(0, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDBegin(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.constDEnd(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-2, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-2, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(3, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(3, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(0, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(0, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(1, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-1, 1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixConstDIterator it{matrix.getConstDIterator(-1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    // equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    // not equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    // smaller than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    // smaller than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    // greater than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    // greater than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 2)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(-1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    // difference operator exceptions
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.getConstDIterator(2, 1)};
                                 IntMatrixConstDIterator secondIt{matrix.getConstDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{matrix.constDEnd(1, 2)};
                                 IntMatrixConstDIterator secondIt{matrix.constDEnd(-1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(1, 2)};
                                 IntMatrixConstDIterator secondIt{secondMatrix.getConstDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixConstDIterator firstIt{firstMatrix.getConstDIterator(-1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixConstDIterator secondIt{firstMatrix.getConstDIterator(2, 1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    // dereference exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.constDEnd(-1)};   Q_UNUSED(*it); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.constDEnd(0, 2)};   Q_UNUSED(*it); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixConstDIterator it{matrix.constDEnd(-1)};  Q_UNUSED(it->size()); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixConstDIterator it{matrix.constDEnd(0, 2)}; Q_UNUSED(it->size()); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.constDBegin(0, 1)};   Q_UNUSED(it[-1]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.constDEnd(0, 0)};   Q_UNUSED(it[0]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.getConstDIterator(2, 1)};   Q_UNUSED(it[2]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.getConstDIterator(0, 1, true)};   Q_UNUSED(it[-2]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.getConstDIterator(1, 0, true)};   Q_UNUSED(it[3]); }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixConstDIterator it{matrix.constDBegin(-1)};   Q_UNUSED(it[-2]); }, std::runtime_error);
}

void ExceptionTests::testReverseDIteratorExceptions()
{
    // iterator creation
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.reverseDBegin(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.reverseDBegin(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.reverseDEnd(0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.reverseDEnd(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDBegin(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(-2)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.reverseDEnd(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 0)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 3)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, -1)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-2, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-2, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(3, 0, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(3, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 2, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, 1, true)}; Q_UNUSED(it);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, -3, 4, -5, 6}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(-1, -1, true)}; Q_UNUSED(it);}, std::runtime_error);
    // equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool areEqual{firstIt == secondIt}; Q_UNUSED(areEqual);
                             }, std::runtime_error);
    // not equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool areNotEqual{firstIt != secondIt}; Q_UNUSED(areNotEqual);
                             }, std::runtime_error);
    // smaller than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool isSmallerThan{firstIt < secondIt}; Q_UNUSED(isSmallerThan);
                             }, std::runtime_error);
    // smaller than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool isSmallerThanOrEqual{firstIt <= secondIt}; Q_UNUSED(isSmallerThanOrEqual);
                             }, std::runtime_error);
    // greater than operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool isGreaterThan{firstIt > secondIt}; Q_UNUSED(isGreaterThan);
                             }, std::runtime_error);
    // greater than or equal operator
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 2)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 3, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(-1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(4, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12, 13, -14, 15, -16});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 firstMatrix.insertColumn(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(1, 0, true)};
                                 bool isGreaterThanOrEqual{firstIt >= secondIt}; Q_UNUSED(isGreaterThanOrEqual);
                             }, std::runtime_error);
    // difference operator exceptions
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.getReverseDIterator(2, 1)};
                                 IntMatrixReverseDIterator secondIt{matrix.getReverseDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix matrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{matrix.reverseDEnd(1, 2)};
                                 IntMatrixReverseDIterator secondIt{matrix.reverseDEnd(-1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrix secondMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(1, 2)};
                                 IntMatrixReverseDIterator secondIt{secondMatrix.getReverseDIterator(1, 1, true)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({
                                 IntMatrix firstMatrix(3, 4, {1, 2, -3, 4, -5, 6, 7, -8, 9, 10, -11, 12});
                                 IntMatrixReverseDIterator firstIt{firstMatrix.getReverseDIterator(-1, 1, true)};
                                 firstMatrix.insertRow(1);
                                 IntMatrixReverseDIterator secondIt{firstMatrix.getReverseDIterator(2, 1)};
                                 int difference{firstIt - secondIt}; Q_UNUSED(difference);
                             }, std::runtime_error);
    // dereference exceptions
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.reverseDEnd(-1)};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.reverseDEnd(0, 2)};   *it = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixReverseDIterator it{matrix.reverseDEnd(-1)};  it->assign("c"); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({StringMatrix matrix(4, 3, {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l"}); StringMatrixReverseDIterator it{matrix.reverseDEnd(0, 2)}; it->assign("c"); },
                             std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.reverseDBegin(0, 1)};   it[-1] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.reverseDEnd(0, 0)};   it[0] = 14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(2, 1)};   it[2] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(0, 1, true)};   it[-2] = 14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.getReverseDIterator(1, 0, true)};   it[3] = -14; }, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}); IntMatrixReverseDIterator it{matrix.reverseDBegin(-1)};   it[-2] = 14; }, std::runtime_error);
}

QTEST_APPLESS_MAIN(ExceptionTests)

#include "tst_exceptiontests.moc"
