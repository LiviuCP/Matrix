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

static constexpr matrix_size_t c_MaxAllowedDimension{maxAllowedDimension()};
static constexpr matrix_size_t c_ExceedingDimension{c_MaxAllowedDimension + 1};

class CommonExceptionTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testCopiedVectorConstructorExceptions();
    void testMovedVectorConstructorExceptions();
    void testIdenticalMatrixConstructorExceptions();
    void testDiagonalMatrixConstructorExceptions();
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
    void testSwapRowsOrColumnsExceptions();

    // test data
    void testCopiedVectorConstructorExceptions_data();
    void testMovedVectorConstructorExceptions_data();
    void testIdenticalMatrixConstructorExceptions_data();
    void testDiagonalMatrixConstructorExceptions_data();
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
    void testSwapRowsOrColumnsExceptions_data();

private:
    // test data helper methods
    void _buildVectorConstructorExceptionsTestingTable();
    void _buildResizeExceptionsTestingTable();
    void _buildInsertRowExceptionsTestingTable();
    void _buildInsertColumnExceptionsTestingTable();
};

void CommonExceptionTests::testCopiedVectorConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsCount, columnsCount, initList);});
}

void CommonExceptionTests::testMovedVectorConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsCount, columnsCount, std::move(initList));});
}

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(int, elementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix({rowsCount, columnsCount}, elementValue);});
}

void CommonExceptionTests::testDiagonalMatrixConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsColumnsCount);
    QFETCH(int, nonDiagonalElementValue);
    QFETCH(int, diagonalElementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsColumnsCount, std::pair<int, int>{nonDiagonalElementValue, diagonalElementValue});});
}

void CommonExceptionTests::testFunctionAtExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(matrix_size_t, rowNr);
    QFETCH(matrix_size_t, columnNr);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix{srcMatrix}; matrix.at(rowNr, columnNr) = value;});

    // test for the "const" at() too
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {const IntMatrix c_Matrix{srcMatrix}; value = c_Matrix.at(rowNr, columnNr);});

}

void CommonExceptionTests::testSquareBracketsOperatorExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(matrix_diff_t, index);
    QFETCH(int, value);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix{srcMatrix}; matrix[index] = value;});

    // test for the "const" square brackets operator too
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {const IntMatrix c_Matrix{srcMatrix}; value = c_Matrix[index];});
}

void CommonExceptionTests::testResizeWithoutFillingInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, resizeRowsCount);
    QFETCH(matrix_size_t, resizeColumnsCount);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resize(resizeRowsCount, resizeColumnsCount);});
}

void CommonExceptionTests::testResizeAndFillInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, resizeRowsCount);
    QFETCH(matrix_size_t, resizeColumnsCount);
    QFETCH(int, resizeElementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resize(resizeRowsCount, resizeColumnsCount, resizeElementValue);});
}

void CommonExceptionTests::testInsertRowNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertRow(insertPosition);});
}

void CommonExceptionTests::testInsertRowSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(int, insertedRowValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertRow(insertPosition, insertedRowValue);});
}

void CommonExceptionTests::testInsertColumnNoSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertColumn(insertPosition);});
}

void CommonExceptionTests::testInsertColumnSetValueExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(int, insertedColumnValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.insertColumn(insertPosition, insertedColumnValue);});
}

void CommonExceptionTests::testEraseRowExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, erasePosition);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.eraseRow(erasePosition);});
}

void CommonExceptionTests::testEraseColumnExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, erasePosition);

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
    QFETCH(matrix_size_t, splitPosition);
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
    QFETCH(matrix_size_t, splitPosition);
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

void CommonExceptionTests::testSwapRowsOrColumnsExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, firstRowColumnNr);
    QFETCH(matrix_size_t, secondRowColumnNr);

    IntMatrix transposedMatrix;
    matrix.transpose(transposedMatrix);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.swapRows(firstRowColumnNr, secondRowColumnNr);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {transposedMatrix.swapColumns(firstRowColumnNr, secondRowColumnNr);});
}

void CommonExceptionTests::testCopiedVectorConstructorExceptions_data()
{
    _buildVectorConstructorExceptionsTestingTable();
}

void CommonExceptionTests::testMovedVectorConstructorExceptions_data()
{
    _buildVectorConstructorExceptionsTestingTable();
}

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<int>("elementValue");

    QTest::newRow("1: null rows and columns count") << matrix_size_t{0u} << matrix_size_t{0u} << 5;
    QTest::newRow("2: null rows count") << matrix_size_t{0u} << matrix_size_t{2u} << 5;
    QTest::newRow("3: null columns count") << matrix_size_t{2u} << matrix_size_t{0u} << 5;
    QTest::newRow("4: exceeding rows and columns count") << c_ExceedingDimension << c_ExceedingDimension << 5;
    QTest::newRow("5: exceeding rows count") << c_ExceedingDimension << matrix_size_t{2u} << 5;
    QTest::newRow("6: exceeding rows count") << c_ExceedingDimension << c_MaxAllowedDimension << 5;
    QTest::newRow("7: exceeding columns count") << matrix_size_t{2u} << c_ExceedingDimension << 5;
    QTest::newRow("8: exceeding columns count") << c_MaxAllowedDimension << c_ExceedingDimension << 5;
    QTest::newRow("9: exceeding rows count, null columns count") << c_ExceedingDimension << matrix_size_t{0u} << 5;
    QTest::newRow("10: null rows count, exceeding columns count") << matrix_size_t{0u} << c_ExceedingDimension << 5;
}

void CommonExceptionTests::testDiagonalMatrixConstructorExceptions_data()
{
    QTest::addColumn<matrix_size_t>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalElementValue");
    QTest::addColumn<int>("diagonalElementValue");

    QTest::newRow("1: null rows and columns count") << matrix_size_t{0u} << 2 << 5;
    QTest::newRow("2: exceeding rows and columns count") << c_ExceedingDimension << 2 << 5;
}

void CommonExceptionTests::testFunctionAtExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<matrix_size_t>("rowNr");
    QTest::addColumn<matrix_size_t>("columnNr");
    QTest::addColumn<int>("value");

    QTest::newRow("1: column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{1u} << matrix_size_t{3u} << 0;
    QTest::newRow("2: row number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{2u} << matrix_size_t{1u} << 0;
    QTest::newRow("3: row and column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{2u} << matrix_size_t{3u} << 0;
    QTest::newRow("4: empty matrix") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{0u} << 0;
}

void CommonExceptionTests::testSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<matrix_diff_t>("index");
    QTest::addColumn<int>("value");

    QTest::newRow("1: negative index, non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_diff_t{-1} << 0;
    QTest::newRow("2: index out of range, non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_diff_t{6} << 0;
    QTest::newRow("3: negative index, empty matrix") << IntMatrix{} << matrix_diff_t{-1} << 0;
    QTest::newRow("4: index out of range, empty matrix") << IntMatrix{} << matrix_diff_t{0} << 0;
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
    QTest::addColumn<matrix_size_t>("erasePosition");

    QTest::newRow("1: erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{2u};
    QTest::newRow("2: empty matrix") << IntMatrix{} << matrix_size_t{0u};
}

void CommonExceptionTests::testEraseColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");

    QTest::newRow("1: erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{3u};
    QTest::newRow("2: empty matrix") << IntMatrix{} << matrix_size_t{0u};
}

void CommonExceptionTests::testCatByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("1: all different") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("2: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{{1, 9}, 1} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("3: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 2, {7, 8}} << ConcatMode::DESTINATION_FIRST;
    QTest::newRow("4: all different") << IntMatrix{} << IntMatrix{2, 1, {1, 2}} << IntMatrix{} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("5: destination second") << IntMatrix{} << IntMatrix{2, 2, {3, 4, 5, 6}} << IntMatrix{} << ConcatMode::DESTINATION_SECOND;
}

void CommonExceptionTests::testCatByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("1: all different") << IntMatrix{} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("2: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{{1, 9}, 1} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("3: destination first") << IntMatrix{} << IntMatrix{} << IntMatrix{2, 1, {7, 8}} << ConcatMode::DESTINATION_FIRST;
    QTest::newRow("4: all different") << IntMatrix{} << IntMatrix{1, 2, {1, 2}} << IntMatrix{} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("5: destination second") << IntMatrix{} << IntMatrix{2, 2, {3, 4, 5, 6}} << IntMatrix{} << ConcatMode::DESTINATION_SECOND;
}

void CommonExceptionTests::testSplitByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("1: destination both") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{1u} << SplitMode::DESTINATION_BOTH;
    QTest::newRow("2: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::DESTINATION_BOTH;
    QTest::newRow("3: destination all") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{1u} << SplitMode::DESTINATION_ALL;
    QTest::newRow("4: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{0u} << SplitMode::DESTINATION_ALL;
    QTest::newRow("5: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::ALL_DIFFERENT;
    QTest::newRow("6: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{2u} << SplitMode::ALL_DIFFERENT;
    QTest::newRow("7: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSplitByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("1: destination both") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{1u} << SplitMode::DESTINATION_BOTH;
    QTest::newRow("2: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::DESTINATION_BOTH;
    QTest::newRow("3: destination all") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << matrix_size_t{1u} << SplitMode::DESTINATION_ALL;
    QTest::newRow("4: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{0u} << SplitMode::DESTINATION_ALL;
    QTest::newRow("5: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::ALL_DIFFERENT;
    QTest::newRow("6: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << matrix_size_t{2u} << SplitMode::ALL_DIFFERENT;
    QTest::newRow("7: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSwapRowsOrColumnsExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("firstRowColumnNr");
    QTest::addColumn<matrix_size_t>("secondRowColumnNr");

    QTest::newRow("1: second out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{1u} << matrix_size_t{4u};
    QTest::newRow("2: first out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{4u} << matrix_size_t{1u};
    QTest::newRow("3: both out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{4u} << matrix_size_t{4u};

    // empty matrixes involved
    QTest::newRow("4: empty matrix") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{0u};
}

void CommonExceptionTests::_buildVectorConstructorExceptionsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<int>>("initList");

    QTest::newRow("1: null rows and columns count") << matrix_size_t{0u} << matrix_size_t{0u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("2: null rows count") << matrix_size_t{0u} << matrix_size_t{2u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("3: null rows count") << matrix_size_t{0u} << c_MaxAllowedDimension << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("4: null columns count") << matrix_size_t{2u} << matrix_size_t{0u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("5: null columns count") << c_MaxAllowedDimension << matrix_size_t{0u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("6: exceeding rows count") << c_ExceedingDimension << matrix_size_t{2} << std::vector<int>(2 * c_ExceedingDimension, 0);
    QTest::newRow("7: exceeding rows count") << c_ExceedingDimension << c_MaxAllowedDimension << std::vector<int>(c_ExceedingDimension * c_MaxAllowedDimension, 0);
    QTest::newRow("8: exceeding columns count") << matrix_size_t{2} << c_ExceedingDimension << std::vector<int>(2 * c_ExceedingDimension, 0);
    QTest::newRow("9: exceeding columns count") << c_MaxAllowedDimension << c_ExceedingDimension << std::vector<int>(c_MaxAllowedDimension * c_ExceedingDimension, 0);
    QTest::newRow("10: null rows count, exceeding columns count") << matrix_size_t{0u} << c_ExceedingDimension << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("11: exceeding rows count, null columns count") << c_ExceedingDimension << matrix_size_t{0u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("12: exceeding rows and columns count") << c_ExceedingDimension << c_ExceedingDimension << std::vector<int>(c_ExceedingDimension * c_ExceedingDimension, 0);
    QTest::newRow("13: less init elements than required") << matrix_size_t{2u} << matrix_size_t{3u} << std::vector<int>{1, 2, 3, 4, 5};
    QTest::newRow("14: less init elements than required") << matrix_size_t{1u} << matrix_size_t{5u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("15: less init elements than required") << matrix_size_t{1u} << c_MaxAllowedDimension << std::vector<int>(c_MaxAllowedDimension - 1, 0);
    QTest::newRow("16: less init elements than required") << matrix_size_t{5u} << matrix_size_t{1u} << std::vector<int>{1, 2, 3, 4};
    QTest::newRow("17: less init elements than required") << c_MaxAllowedDimension << matrix_size_t{1u} << std::vector<int>(c_MaxAllowedDimension - 1, 0);
    QTest::newRow("18: less init elements than required") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::vector<int>(c_MaxAllowedDimension * c_MaxAllowedDimension - 1, 0);
}

void CommonExceptionTests::_buildResizeExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");

    QTest::newRow("1: null rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{0u} << matrix_size_t{0u} << 5;
    QTest::newRow("2: null rows and columns count") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{0u} << 5;
    QTest::newRow("3: null rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{0u} << matrix_size_t{4u} << 5;
    QTest::newRow("4: null rows count") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{4u} << 5;
    QTest::newRow("5: null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{3u} << matrix_size_t{0u} << 5;
    QTest::newRow("6: null columns count") << IntMatrix{} << matrix_size_t{3u} << matrix_size_t{0u} << 5;
    QTest::newRow("7: exceeding rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << c_ExceedingDimension << matrix_size_t{4u} << 5;
    QTest::newRow("8: exceeding rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << c_ExceedingDimension << c_MaxAllowedDimension << 5;
    QTest::newRow("9: exceeding rows count") << IntMatrix{} << c_ExceedingDimension << matrix_size_t{4u} << 5;
    QTest::newRow("10: exceeding rows count") << IntMatrix{} << c_ExceedingDimension << c_MaxAllowedDimension << 5;
    QTest::newRow("11: exceeding columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{3u} << c_ExceedingDimension << 5;
    QTest::newRow("12: exceeding columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << c_MaxAllowedDimension << c_ExceedingDimension << 5;
    QTest::newRow("13: exceeding columns count") << IntMatrix{} << matrix_size_t{3u} << c_ExceedingDimension << 5;
    QTest::newRow("14: exceeding columns count") << IntMatrix{} << c_MaxAllowedDimension << c_ExceedingDimension << 5;
    QTest::newRow("15: null rows count, exceeding columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{0u} << c_ExceedingDimension << 5;
    QTest::newRow("16: null rows count, exceeding columns count") << IntMatrix{} << matrix_size_t{0u} << c_ExceedingDimension << 5;
    QTest::newRow("17: exceeding rows count, null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << c_ExceedingDimension << matrix_size_t{0u} << 5;
    QTest::newRow("18: exceeding rows count, null columns count") << IntMatrix{} << c_ExceedingDimension << matrix_size_t{0u} << 5;
    QTest::newRow("19: exceeding rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << c_ExceedingDimension << c_ExceedingDimension << 5;
    QTest::newRow("20: exceeding rows and columns count") << IntMatrix{} << c_ExceedingDimension << c_ExceedingDimension << 5;
}

void CommonExceptionTests::_buildInsertRowExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");

    QTest::newRow("1: insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{3u} << 5;
    QTest::newRow("2: empty matrix") << IntMatrix{} << matrix_size_t{0u} << 1;
    QTest::newRow("3: maximum rows count reached") << IntMatrix{{c_MaxAllowedDimension, 2}, -5} << matrix_size_t{2u} << 3;
}

void CommonExceptionTests::_buildInsertColumnExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");

    QTest::newRow("1: insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << matrix_size_t{4u} << 5;
    QTest::newRow("2: empty matrix") << IntMatrix{} << matrix_size_t{0u} << 2;
    QTest::newRow("3: maximum columns count reached") << IntMatrix{{2, c_MaxAllowedDimension}, -5} << matrix_size_t{2u} << 3;
}

QTEST_APPLESS_MAIN(CommonExceptionTests)

#include "tst_commonexceptiontests.moc"
