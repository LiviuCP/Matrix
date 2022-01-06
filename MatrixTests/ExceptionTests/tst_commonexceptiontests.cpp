#define CONVERT_TO_EXCEPTIONS

#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(SplitMode)

class CommonExceptionTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testInitListConstructorExceptions();
    void testIdenticalMatrixConstructorExceptions();
    void testDiagMatrixConstructorExceptions();
    void testFunctionAtExceptions();
    void testSquareBracketsOperatorExceptions();
    void testResizeWithoutFillingInNewValuesExceptions();
    void testResizeAndFillInNewValuesExceptions();
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

    // test data
    void testIdenticalMatrixConstructorExceptions_data();
    void testDiagMatrixConstructorExceptions_data();
    void testFunctionAtExceptions_data();
    void testSquareBracketsOperatorExceptions_data();
    void testResizeWithoutFillingInNewValuesExceptions_data();
    void testResizeAndFillInNewValuesExceptions_data();
    void testInsertRowNoSetValueExceptions_data();
    void testInsertRowSetValueExceptions_data();
    void testInsertColumnNoSetValueExceptions_data();
    void testInsertColumnSetValueExceptions_data();
    void testEraseRowExceptions_data();
    void testEraseColumnExceptions_data();
    void testSplitByRowExceptions_data();
    void testSplitByColumnExceptions_data();
    void testSwapItemsExceptions_data();
    void testSwapRowsExceptions_data();
    void testSwapColumnsExceptions_data();
    void testSwapRowColumnExceptions_data();
    void testCopyExceptions_data();

private:
    // test data helper methods
    void _buildResizeExceptionsTestingTable();
    void _buildInsertRowExceptionsTestingTable();
    void _buildInsertColumnExceptionsTestingTable();
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
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(rowsCount, columnsCount, elementValue);}, std::runtime_error);
}

void CommonExceptionTests::testDiagMatrixConstructorExceptions()
{
    QFETCH(IntMatrixSizeType, rowsColumnsCount);
    QFETCH(int, nonDiagonalValue);
    QFETCH(int, diagonalValue);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix(rowsColumnsCount, std::pair<int, int>{nonDiagonalValue, diagonalValue});}, std::runtime_error);
}

void CommonExceptionTests::testFunctionAtExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(int, value);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix{srcMatrix}; matrix.at(rowNr, columnNr) = value;}, std::runtime_error);

    // test for the "const" at() too
    QVERIFY_EXCEPTION_THROWN({const IntMatrix c_Matrix{srcMatrix}; value = c_Matrix.at(rowNr, columnNr);}, std::runtime_error);

}

void CommonExceptionTests::testSquareBracketsOperatorExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrixSizeType, index);
    QFETCH(int, value);

    QVERIFY_EXCEPTION_THROWN({IntMatrix matrix{srcMatrix}; matrix[index] = value;}, std::runtime_error);

    // test for the "const" square brackets operator too
    QVERIFY_EXCEPTION_THROWN({const IntMatrix c_Matrix(2, 3, {1, 2, 3, 4, 5, 6}); value = c_Matrix[index];}, std::runtime_error);
}

void CommonExceptionTests::testResizeWithoutFillingInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);

    QVERIFY_EXCEPTION_THROWN({matrix.resize(resizeRowsCount, resizeColumnsCount);}, std::runtime_error);
}

void CommonExceptionTests::testResizeAndFillInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, resizeElementValue);

    QVERIFY_EXCEPTION_THROWN({matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue);}, std::runtime_error);
}

void CommonExceptionTests::testInsertRowNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);

    QVERIFY_EXCEPTION_THROWN({matrix.insertRow(insertPosition);}, std::runtime_error);
}

void CommonExceptionTests::testInsertRowSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);

    QVERIFY_EXCEPTION_THROWN({matrix.insertRow(insertPosition, insertedRowValue);}, std::runtime_error);
}

void CommonExceptionTests::testInsertColumnNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);

    QVERIFY_EXCEPTION_THROWN({matrix.insertColumn(insertPosition);}, std::runtime_error);
}

void CommonExceptionTests::testInsertColumnSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);

    QVERIFY_EXCEPTION_THROWN({matrix.insertColumn(insertPosition, insertedColumnValue);}, std::runtime_error);
}

void CommonExceptionTests::testEraseRowExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);

    QVERIFY_EXCEPTION_THROWN({matrix.eraseRow(erasePosition);}, std::runtime_error);
}

void CommonExceptionTests::testEraseColumnExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);

    QVERIFY_EXCEPTION_THROWN({matrix.eraseColumn(erasePosition);}, std::runtime_error);
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
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_EXCEPTION_THROWN({
                                 switch(mode)
                                 {
                                 case SplitMode::ALL_DIFFERENT:
                                     srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::SOURCE_FIRST:
                                     firstDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::SOURCE_SECOND:
                                     secondDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::DESTINATION_BOTH:
                                     srcMatrix.splitByRow(firstDestMatrix, firstDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::DESTINATION_ALL:
                                     firstDestMatrix.splitByRow(firstDestMatrix, firstDestMatrix, splitPosition);
                                     break;
                                 default:
                                     break;
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSplitByColumnExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_EXCEPTION_THROWN({
                                 switch(mode)
                                 {
                                 case SplitMode::ALL_DIFFERENT:
                                     srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::SOURCE_FIRST:
                                     firstDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::SOURCE_SECOND:
                                     secondDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::DESTINATION_BOTH:
                                     srcMatrix.splitByColumn(firstDestMatrix, firstDestMatrix, splitPosition);
                                     break;
                                 case SplitMode::DESTINATION_ALL:
                                     firstDestMatrix.splitByColumn(firstDestMatrix, firstDestMatrix, splitPosition);
                                     break;
                                 default:
                                     break;
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSwapItemsExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstItemRowNr);
    QFETCH(IntMatrixSizeType, firstItemColumnNr);
    QFETCH(IntMatrixSizeType, secondItemRowNr);
    QFETCH(IntMatrixSizeType, secondItemColumnNr);
    QFETCH(bool, isSwapWithinMatrix);

    QVERIFY_EXCEPTION_THROWN({
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, firstMatrix, secondItemRowNr, secondItemColumnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, secondMatrix, secondItemRowNr, secondItemColumnNr);
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSwapRowsExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstRowNr);
    QFETCH(IntMatrixSizeType, secondRowNr);
    QFETCH(bool, isSwapWithinMatrix);

    QVERIFY_EXCEPTION_THROWN({
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapRows(firstRowNr, firstMatrix, secondRowNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapRows(firstRowNr, secondMatrix, secondRowNr);
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSwapColumnsExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstColumnNr);
    QFETCH(IntMatrixSizeType, secondColumnNr);
    QFETCH(bool, isSwapWithinMatrix);

    QVERIFY_EXCEPTION_THROWN({
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapColumns(firstColumnNr, firstMatrix, secondColumnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapColumns(firstColumnNr, secondMatrix, secondColumnNr);
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testSwapRowColumnExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(bool, isSwapWithinMatrix);

    QVERIFY_EXCEPTION_THROWN({
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapRowColumn(rowNr, firstMatrix, columnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapRowColumn(rowNr, secondMatrix, columnNr);
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testCopyExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrixSizeType, copiedRowsCount);
    QFETCH(IntMatrixSizeType, copiedColumnsCount);
    QFETCH(IntMatrixSizeType, srcCopyRowNr);
    QFETCH(IntMatrixSizeType, srcCopyColumnNr);
    QFETCH(IntMatrixSizeType, destCopyRowNr);
    QFETCH(IntMatrixSizeType, destCopyColumnNr);
    QFETCH(bool, isSameMatrix);

    QVERIFY_EXCEPTION_THROWN({
                                 if (isSameMatrix)
                                 {
                                     destMatrix.copy(destMatrix, copiedRowsCount, copiedColumnsCount, srcCopyRowNr, srcCopyColumnNr, destCopyRowNr, destCopyColumnNr);
                                 }
                                 else
                                 {
                                     destMatrix.copy(srcMatrix, copiedRowsCount, copiedColumnsCount, srcCopyRowNr, srcCopyColumnNr, destCopyRowNr, destCopyColumnNr);
                                 }
                             },

                             std::runtime_error);
}

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");

    QTest::newRow("negative rows and columns count") << -2 << -2 << 5;
    QTest::newRow("negative rows and null columns count") << -2 << 0 << 5;
    QTest::newRow("negative rows count") << -2 << 2 << 5;
    QTest::newRow("negative columns count") << 2 << -2 << 5;
    QTest::newRow("null rows and negative columns count") << 0 << -2 << 5;
    QTest::newRow("null rows and columns count") << 0 << 0 << 5;
    QTest::newRow("null rows count") << 0 << 2 << 5;
    QTest::newRow("null columns count") << 2 << 0 << 5;
}

void CommonExceptionTests::testDiagMatrixConstructorExceptions_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");

    QTest::newRow("negative size") << -2 << 2 << 5;
    QTest::newRow("null size") << 0 << 2 << 5;
}

void CommonExceptionTests::testFunctionAtExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrixSizeType>("rowNr");
    QTest::addColumn<IntMatrixSizeType>("columnNr");
    QTest::addColumn<int>("value");

    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 0 << 0;
    QTest::newRow("negative row and column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << -1 << 0;
    QTest::newRow("negative row number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 1 << 0;
    QTest::newRow("negative row number, column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 3 << 0;
    QTest::newRow("negative column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << -1 << 0;
    QTest::newRow("column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 3 << 0;
    QTest::newRow("row number out of range, negative column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << -1 << 0;
    QTest::newRow("row number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 0;
    QTest::newRow("row and column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 3 << 0;
}

void CommonExceptionTests::testSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrixSizeType>("index");
    QTest::addColumn<int>("value");

    QTest::newRow("negative index") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 0;
    QTest::newRow("index out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 6 << 0;
}

void CommonExceptionTests::testResizeWithoutFillingInNewValuesExceptions_data()
{
    _buildResizeExceptionsTestingTable();
}

void CommonExceptionTests::testResizeAndFillInNewValuesExceptions_data()
{
    _buildResizeExceptionsTestingTable();
}

void CommonExceptionTests::testInsertRowNoSetValueExceptions_data()
{
    _buildInsertRowExceptionsTestingTable();
}

void CommonExceptionTests::testInsertRowSetValueExceptions_data()
{
    _buildInsertRowExceptionsTestingTable();
}

void CommonExceptionTests::testInsertColumnNoSetValueExceptions_data()
{
    _buildInsertColumnExceptionsTestingTable();
}

void CommonExceptionTests::testInsertColumnSetValueExceptions_data()
{
    _buildInsertColumnExceptionsTestingTable();
}

void CommonExceptionTests::testEraseRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");

    QTest::newRow("negative erase position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1;
    QTest::newRow("erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2;
}

void CommonExceptionTests::testEraseColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");

    QTest::newRow("negative erase position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1;
    QTest::newRow("erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3;
}

void CommonExceptionTests::testSplitByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("scenario: destination both") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination all") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << -1 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSplitByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("scenario: destination both") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination all") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << -1 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSwapItemsExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("firstItemColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondItemColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 1 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 1 << 1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 1 << 2 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 2 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 2 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 2 << 1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << 1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 1 << 2 << 3 << false;
}

void CommonExceptionTests::testSwapRowsExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << 1 << 0 << false;
}

void CommonExceptionTests::testSwapColumnsExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << 1 << 0 << false;
}

void CommonExceptionTests::testSwapRowColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("rowNr");
    QTest::addColumn<IntMatrixSizeType>("columnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << -3 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << -3 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix(2, 3, {1, 2, 3, 4, 5, 6}) << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 3 << false;
    QTest::newRow("same matrix") << IntMatrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}) << IntMatrix(3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}) << 1 << 2 << true;
}

void CommonExceptionTests::testCopyExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrixSizeType>("copiedRowsCount");
    QTest::addColumn<IntMatrixSizeType>("copiedColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("srcCopyRowNr");
    QTest::addColumn<IntMatrixSizeType>("srcCopyColumnNr");
    QTest::addColumn<IntMatrixSizeType>("destCopyRowNr");
    QTest::addColumn<IntMatrixSizeType>("destCopyColumnNr");
    QTest::addColumn<bool>("isSameMatrix");

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << 2 << 2 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -2 << 2 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << 2 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << -1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << -1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << 1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << -1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << -1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << 1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << -1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << -1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << 1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << -1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << -1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << 2 << -2 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << -1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << -1 << -1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 2 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 2 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 1 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 2 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 1 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 2 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 1 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 2 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 2 << 1 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 2 << 2 << false;

    QTest::newRow("different matrixes") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}
                                        << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 2 << 0 << 0 << 0 << 1 << true;
}

void CommonExceptionTests::_buildResizeExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");

    QTest::newRow("negative rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << -4 << 5;
    QTest::newRow("negative rows, null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << 0 << 5;
    QTest::newRow("negative rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << 4 << 5;
    QTest::newRow("null rows, negative columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << -4 << 5;
    QTest::newRow("null rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 0 << 5;
    QTest::newRow("null rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 4 << 5;
    QTest::newRow("negative columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << -4 << 5;
    QTest::newRow("null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << 0 << 5;
}

void CommonExceptionTests::_buildInsertRowExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");

    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 1;
    QTest::newRow("negative insert position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 5;
    QTest::newRow("insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << 5;
}

void CommonExceptionTests::_buildInsertColumnExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");

    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 2;
    QTest::newRow("negative insert position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 5;
    QTest::newRow("insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 4 << 5;
}

QTEST_APPLESS_MAIN(CommonExceptionTests)

#include "tst_commonexceptiontests.moc"
