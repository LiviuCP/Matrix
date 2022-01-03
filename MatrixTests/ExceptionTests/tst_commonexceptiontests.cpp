#define CONVERT_TO_EXCEPTIONS

#include <QtTest>

#include "testutils.h"

class CommonExceptionTests : public QObject
{
    Q_OBJECT

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
};

void CommonExceptionTests::testInitListConstructorExceptions()
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

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions()
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

void CommonExceptionTests::testDiagMatrixConstructorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(-2, std::pair<int, int>{2, 5});}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(0, std::pair<int, int>{2, 5});}, std::runtime_error);
}

void CommonExceptionTests::testFunctionAtExceptions()
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

    // test for the "const" at() too
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix; (void)matrix.at(0, 0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(-1, -1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(-1, 1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(-1, 3);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(1, -1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(1, 3);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(2, -1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(2, 1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix.at(2, 3);}, std::runtime_error);
}

void CommonExceptionTests::testSquareBracketsOperatorExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix[-1] = 0;}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix[6] = 0;}, std::runtime_error);

    // test for the "const" square brackets operator too
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix[-1];}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({const IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); (void)matrix[6];}, std::runtime_error);
}

void CommonExceptionTests::testResizeAndRemoveOldValuesExceptions()
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

void CommonExceptionTests::testResizeAndKeepOldValuesExceptions()
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

void CommonExceptionTests::testInsertRowNoSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertRow(0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3);}, std::runtime_error);
}

void CommonExceptionTests::testInsertRowSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertRow(0, 1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertRow(3, 5);}, std::runtime_error);
}

void CommonExceptionTests::testInsertColumnNoSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertColumn(0);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4);}, std::runtime_error);
}

void CommonExceptionTests::testInsertColumnSetValueExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix; matrix.insertColumn(0, 2);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(-1, 5);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.insertColumn(4, 5);}, std::runtime_error);
}

void CommonExceptionTests::testEraseRowExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseRow(2);}, std::runtime_error);
}

void CommonExceptionTests::testEraseColumnExceptions()
{
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(-1);}, std::runtime_error);
    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(2, 3, {1, 2, 3, 4, 5, 6}); matrix.eraseColumn(3);}, std::runtime_error);
}

void CommonExceptionTests::testCatByRowExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstSrcMatrix(2, 3, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondSrcMatrix(2, 2, {7, 8, 9, 10});
                                  IntMatrix destMatrix;

                                  destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix);
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testCatByColumnExceptions()
{
    QVERIFY_EXCEPTION_THROWN({
                                  IntMatrix firstSrcMatrix(3, 2, {1, 2, 3, 4, 5, 6});
                                  IntMatrix secondSrcMatrix(2, 2, {7, 8, 9, 10});
                                  IntMatrix destMatrix;

                                  destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix);
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSplitByRowExceptions()
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

void CommonExceptionTests::testSplitByColumnExceptions()
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

void CommonExceptionTests::testSwapItemsExceptions()
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

void CommonExceptionTests::testSwapRowsExceptions()
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

void CommonExceptionTests::testSwapColumnsExceptions()
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

void CommonExceptionTests::testSwapRowColumnExceptions()
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

void CommonExceptionTests::testCopyExceptions()
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

QTEST_APPLESS_MAIN(CommonExceptionTests)

#include "tst_commonexceptiontests.moc"
