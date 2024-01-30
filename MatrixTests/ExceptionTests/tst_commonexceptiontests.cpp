#define CONVERT_TO_EXCEPTIONS

#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

// uncomment if compiler supports std::ranges

// static_assert(std::ranges::range<IntMatrix>);
// static_assert(std::ranges::common_range<IntMatrix>);
// static_assert(std::ranges::random_access_range<IntMatrix>);
// static_assert(std::ranges::sized_range<IntMatrix>);

// static_assert(!std::ranges::view<IntMatrix>);
// static_assert(!std::ranges::viewable_range<IntMatrix>);
// static_assert(!std::ranges::contiguous_range<IntMatrix>);
// static_assert(!std::ranges::borrowed_range<IntMatrix>);

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
    void testSwapRowsOrColumnsExceptions();
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
    void testCatByRowExceptions_data();
    void testCatByColumnExceptions_data();
    void testSplitByRowExceptions_data();
    void testSplitByColumnExceptions_data();
    void testSwapItemsExceptions_data();
    void testSwapRowsOrColumnsExceptions_data();
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
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(-2, -2, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(-2, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(-2, 2, {1, 2, 3, 4});});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, -2, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, 2, {1, 2, 3, 4});});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(2, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(2, -2, {1, 2, 3, 4});});

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(2, 3, {1, 2, 3, 4});});
}

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsCount, columnsCount, elementValue);});
}

void CommonExceptionTests::testDiagMatrixConstructorExceptions()
{
    QFETCH(IntMatrixSizeType, rowsColumnsCount);
    QFETCH(int, nonDiagonalValue);
    QFETCH(int, diagonalValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsColumnsCount, std::pair<int, int>{nonDiagonalValue, diagonalValue});});
}

void CommonExceptionTests::testFunctionAtExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix{srcMatrix}; matrix.at(rowNr, columnNr) = value;});

    // test for the "const" at() too
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {const IntMatrix c_Matrix{srcMatrix}; value = c_Matrix.at(rowNr, columnNr);});

}

void CommonExceptionTests::testSquareBracketsOperatorExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrixSizeType, index);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix{srcMatrix}; matrix[index] = value;});

    // test for the "const" square brackets operator too
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {const IntMatrix c_Matrix{srcMatrix}; value = c_Matrix[index];});
}

void CommonExceptionTests::testResizeWithoutFillingInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resize(resizeRowsCount, resizeColumnsCount);});
}

void CommonExceptionTests::testResizeAndFillInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, resizeElementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue);});
}

void CommonExceptionTests::testInsertRowNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertRow(insertPosition);});
}

void CommonExceptionTests::testInsertRowSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertRow(insertPosition, insertedRowValue);});
}

void CommonExceptionTests::testInsertColumnNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertColumn(insertPosition);});
}

void CommonExceptionTests::testInsertColumnSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertColumn(insertPosition, insertedColumnValue);});
}

void CommonExceptionTests::testEraseRowExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.eraseRow(erasePosition);});
}

void CommonExceptionTests::testEraseColumnExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.eraseColumn(erasePosition);});
}

void CommonExceptionTests::testCatByRowExceptions()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case ConcatMode::ALL_DIFFERENT:
                                     destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_FIRST:
                                     destMatrix.catByRow(destMatrix, secondSrcMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_SECOND:
                                     destMatrix.catByRow(firstSrcMatrix, destMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_ALL:
                                     destMatrix.catByRow(destMatrix, destMatrix);
                                     break;
                                 case ConcatMode::SOURCE_BOTH:
                                     destMatrix.catByRow(firstSrcMatrix, firstSrcMatrix);
                                     break;
                                 default:
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testCatByColumnExceptions()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case ConcatMode::ALL_DIFFERENT:
                                     destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_FIRST:
                                     destMatrix.catByColumn(destMatrix, secondSrcMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_SECOND:
                                     destMatrix.catByColumn(firstSrcMatrix, destMatrix);
                                     break;
                                 case ConcatMode::DESTINATION_ALL:
                                     destMatrix.catByColumn(destMatrix, destMatrix);
                                     break;
                                 case ConcatMode::SOURCE_BOTH:
                                     destMatrix.catByColumn(firstSrcMatrix, firstSrcMatrix);
                                     break;
                                 default:
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testSplitByRowExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
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
                             });
}

void CommonExceptionTests::testSplitByColumnExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
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
                             });
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

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, firstMatrix, secondItemRowNr, secondItemColumnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapItems(firstItemRowNr, firstItemColumnNr, secondMatrix, secondItemRowNr, secondItemColumnNr);
                                 }
                             });
}

void CommonExceptionTests::testSwapRowsOrColumnsExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, firstRowColumnNr);
    QFETCH(IntMatrixSizeType, secondRowColumnNr);
    QFETCH(bool, isSwapWithinMatrix);

    IntMatrix firstMatrixTransposed;
    IntMatrix secondMatrixTransposed;

    firstMatrix.transpose(firstMatrixTransposed);
    secondMatrix.transpose(secondMatrixTransposed);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapRows(firstRowColumnNr, firstMatrix, secondRowColumnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapRows(firstRowColumnNr, secondMatrix, secondRowColumnNr);
                                 }
                             });

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrixTransposed.swapColumns(firstRowColumnNr, firstMatrixTransposed, secondRowColumnNr);
                                 }
                                 else
                                 {
                                     firstMatrixTransposed.swapColumns(firstRowColumnNr, secondMatrixTransposed, secondRowColumnNr);
                                 }
                             });
}

void CommonExceptionTests::testSwapRowColumnExceptions()
{
    QFETCH(IntMatrix, firstMatrix);
    QFETCH(IntMatrix, secondMatrix);
    QFETCH(IntMatrixSizeType, rowNr);
    QFETCH(IntMatrixSizeType, columnNr);
    QFETCH(bool, isSwapWithinMatrix);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 if (isSwapWithinMatrix)
                                 {
                                     firstMatrix.swapRowColumn(rowNr, firstMatrix, columnNr);
                                 }
                                 else
                                 {
                                     firstMatrix.swapRowColumn(rowNr, secondMatrix, columnNr);
                                 }
                             });
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

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 if (isSameMatrix)
                                 {
                                     destMatrix.copy(destMatrix, copiedRowsCount, copiedColumnsCount, srcCopyRowNr, srcCopyColumnNr, destCopyRowNr, destCopyColumnNr);
                                 }
                                 else
                                 {
                                     destMatrix.copy(srcMatrix, copiedRowsCount, copiedColumnsCount, srcCopyRowNr, srcCopyColumnNr, destCopyRowNr, destCopyColumnNr);
                                 }
                             });
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

    QTest::newRow("negative row and column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << -1 << 0;
    QTest::newRow("negative row number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 1 << 0;
    QTest::newRow("negative row number, column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 3 << 0;
    QTest::newRow("negative column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << -1 << 0;
    QTest::newRow("column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << 3 << 0;
    QTest::newRow("row number out of range, negative column number") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << -1 << 0;
    QTest::newRow("row number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 0;
    QTest::newRow("row and column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2 << 3 << 0;
    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 0 << 0;
}

void CommonExceptionTests::testSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrixSizeType>("index");
    QTest::addColumn<int>("value");

    QTest::newRow("negative index") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 0;
    QTest::newRow("index out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 6 << 0;
    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 0;
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
    QTest::newRow("empty matrix") << IntMatrix{} << 0;
}

void CommonExceptionTests::testEraseColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");

    QTest::newRow("negative erase position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1;
    QTest::newRow("erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3;
    QTest::newRow("empty matrix") << IntMatrix{} << 0;
}

void CommonExceptionTests::testCatByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 1, 9} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 2, {7, 8}} << ConcatMode::DESTINATION_FIRST;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{2, 1, {1, 2}} << IntMatrix{} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: destination second") << IntMatrix{} << IntMatrix{2, 2, {3, 4, 5, 6}} << IntMatrix{} << ConcatMode::DESTINATION_SECOND;
}

void CommonExceptionTests::testCatByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 1, 9} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{2, 1, {7, 8}} << ConcatMode::DESTINATION_FIRST;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{1, 2, {1, 2}} << IntMatrix{} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("scenario: destination second") << IntMatrix{} << IntMatrix{2, 2, {3, 4, 5, 6}} << IntMatrix{} << ConcatMode::DESTINATION_SECOND;
}

void CommonExceptionTests::testSplitByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("scenario: destination both") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination all") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << -1 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSplitByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("scenario: destination both") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::DESTINATION_BOTH;
    QTest::newRow("scenario: destination all") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << SplitMode::DESTINATION_ALL;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << -1 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2 << SplitMode::ALL_DIFFERENT;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0 << SplitMode::ALL_DIFFERENT;
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
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << -1 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << 1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << -1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << -1 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << 1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << -1 << -1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << -1 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << 1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << -1 << -1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << -1 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << 1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 2 << -1 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 1 << 2 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 1 << 3 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 1 << 3 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 2 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 3 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << 2 << 3 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 2 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 2 << 2 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 2 << 3 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 2 << 3 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 3 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 3 << 2 << true;

    // a combination of exceptions
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 1 << 1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 3 << 1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 1 << 1 << 2 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 2 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << -1 << 2 << 2 << -1 << false;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << 1 << -1 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1 << -1 << 1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 2 << 1 << 3 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << -1 << 2 << 2 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << -1 << 2 << 3 << -1 << true;

    // empty matrixes involved
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{2, 3, {7, 8, 9, 10, 11, 12}} << 0 << 0 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 0 << 1 << 0 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{} << 0 << 0 << 0 << 0 << false;
    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{} << 0 << 0 << 0 << 0 << true;
}

void CommonExceptionTests::testSwapRowsOrColumnsExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("firstRowColumnNr");
    QTest::addColumn<IntMatrixSizeType>("secondRowColumnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << -2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << 1 << 0 << false;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << -2 << true;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << -2 << true;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 4 << true;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 4 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 4 << 4 << true;

    // a combination of exceptions
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << -1 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 3 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << -1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15}} << 3 << 1 << false;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 3 << -1 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << -1 << 3 << true;

    // empty matrixes involved
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 0 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 1 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{} << 0 << 0 << false;
    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{} << 0 << 0 << true;
}

void CommonExceptionTests::testSwapRowColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("firstMatrix");
    QTest::addColumn<IntMatrix>("secondMatrix");
    QTest::addColumn<IntMatrixSizeType>("rowNr");
    QTest::addColumn<IntMatrixSizeType>("columnNr");
    QTest::addColumn<bool>("isSwapWithinMatrix");

    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << -3 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << -3 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << 4 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 4, {7, 8, 9, 10, 11, 12, 13, 14}} << 1 << 3 << false;
    QTest::newRow("same matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 1 << 2 << true;

    // combination of exceptions
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << -1 << 4 << false;
    QTest::newRow("same matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << -1 << 2 << true;
    QTest::newRow("same matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 3 << -1 << true;

    // empty matrixes involved
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 3 << false;
    QTest::newRow("different matrixes") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << 1 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{} << 0 << 0 << false;
    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{} << 0 << 0 << true;
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

    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << 2 << 2 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -2 << 2 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << 2 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << -1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << 1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << 1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -2 << -1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << 2 << -2 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << -1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << -3 << -2 << -2 << -1 << -1 << -1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 1 << 2 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 3 << 2 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 1 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 3 << 2 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 1 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 2 << 1 << 2 << 2 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 1 << 0 << 0 << 2 << 1 << false;
    QTest::newRow("different matrixes") << IntMatrix{5, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}} << IntMatrix{} << 1 << 1 << 1 << 2 << 0 << 0 << false;
    QTest::newRow("different matrixes") << IntMatrix{} << IntMatrix{} << 1 << 1 << 0 << 0 << 0 << 0 << false;
    QTest::newRow("same matrix") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 2 << 0 << 0 << 0 << 1 << true;
    QTest::newRow("same matrix") << IntMatrix{} << IntMatrix{} << 1 << 1 << 0 << 0 << 0 << 0 << true;
}

void CommonExceptionTests::_buildResizeExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");

    QTest::newRow("negative rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << -4 << 5;
    QTest::newRow("negative rows and columns count") << IntMatrix{} << -3 << -4 << 5;
    QTest::newRow("negative rows, null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << 0 << 5;
    QTest::newRow("negative rows, null columns count") << IntMatrix{} << -3 << 0 << 5;
    QTest::newRow("negative rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -3 << 4 << 5;
    QTest::newRow("negative rows count") << IntMatrix{} << -3 << 4 << 5;
    QTest::newRow("null rows, negative columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << -4 << 5;
    QTest::newRow("null rows, negative columns count") << IntMatrix{} << 0 << -4 << 5;
    QTest::newRow("null rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 0 << 5;
    QTest::newRow("null rows and columns count") << IntMatrix{} << 0 << 0 << 5;
    QTest::newRow("null rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0 << 4 << 5;
    QTest::newRow("null rows count") << IntMatrix{} << 0 << 4 << 5;
    QTest::newRow("negative columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << -4 << 5;
    QTest::newRow("negative columns count") << IntMatrix{} << 3 << -4 << 5;
    QTest::newRow("null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << 0 << 5;
    QTest::newRow("null columns count") << IntMatrix{} << 3 << 0 << 5;
}

void CommonExceptionTests::_buildInsertRowExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");

    QTest::newRow("negative insert position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 5;
    QTest::newRow("insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3 << 5;
    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 1;
}

void CommonExceptionTests::_buildInsertColumnExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");

    QTest::newRow("negative insert position") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << -1 << 5;
    QTest::newRow("insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 4 << 5;
    QTest::newRow("empty matrix") << IntMatrix{} << 0 << 2;
}

QTEST_APPLESS_MAIN(CommonExceptionTests)

#include "tst_commonexceptiontests.moc"
