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
    void testCopiedVectorConstructorExceptions();
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
    void testSwapRowsOrColumnsExceptions();

    // test data
    void testIdenticalMatrixConstructorExceptions_data();
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
    void _buildResizeExceptionsTestingTable();
    void _buildInsertRowExceptionsTestingTable();
    void _buildInsertColumnExceptionsTestingTable();
};

void CommonExceptionTests::testCopiedVectorConstructorExceptions()
{
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, 2, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, 5, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(2, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(2, 3, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(5, 0, {1, 2, 3, 4});});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(5, 5, {1, 2, 3, 4});});
}

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(int, elementValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(elementValue, rowsCount, columnsCount);});
}

void CommonExceptionTests::testDiagMatrixConstructorExceptions()
{
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(0, std::pair<int, int>{2, 5});});
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
    QFETCH(matrix_size_t, index);
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

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue);});
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

void CommonExceptionTests::testIdenticalMatrixConstructorExceptions_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<int>("elementValue");

    QTest::newRow("1: null rows and columns count") << 0u << 0u << 5;
    QTest::newRow("2: null rows count") << 0u << 2u << 5;
    QTest::newRow("3: null columns count") << 2u << 0u << 5;
}

void CommonExceptionTests::testFunctionAtExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<matrix_size_t>("rowNr");
    QTest::addColumn<matrix_size_t>("columnNr");
    QTest::addColumn<int>("value");

    QTest::newRow("1: column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1u << 3u << 0;
    QTest::newRow("2: row number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2u << 1u << 0;
    QTest::newRow("3: row and column number out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2u << 3u << 0;
    QTest::newRow("4: empty matrix") << IntMatrix{} << 0u << 0u << 0;
}

void CommonExceptionTests::testSquareBracketsOperatorExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<matrix_size_t>("index");
    QTest::addColumn<int>("value");

    QTest::newRow("1: index out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 6u << 0;
    QTest::newRow("2: empty matrix") << IntMatrix{} << 0u << 0;
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

    QTest::newRow("1: erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 2u;
    QTest::newRow("2: empty matrix") << IntMatrix{} << 0u;
}

void CommonExceptionTests::testEraseColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");

    QTest::newRow("1: erase position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3u;
    QTest::newRow("2: empty matrix") << IntMatrix{} << 0u;
}

void CommonExceptionTests::testCatByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("1: all different") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 2, {7, 8, 9, 10}} << ConcatMode::ALL_DIFFERENT;
    QTest::newRow("2: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 1, 9} << ConcatMode::ALL_DIFFERENT;
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
    QTest::newRow("2: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{1, 1, 9} << ConcatMode::ALL_DIFFERENT;
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

    QTest::newRow("1: destination both") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1u << SplitMode::DESTINATION_BOTH;
    QTest::newRow("2: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::DESTINATION_BOTH;
    QTest::newRow("3: destination all") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 1u << SplitMode::DESTINATION_ALL;
    QTest::newRow("4: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0u << SplitMode::DESTINATION_ALL;
    QTest::newRow("5: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::ALL_DIFFERENT;
    QTest::newRow("6: all different") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2u << SplitMode::ALL_DIFFERENT;
    QTest::newRow("7: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSplitByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("1: destination both") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 1u << SplitMode::DESTINATION_BOTH;
    QTest::newRow("2: destination both") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::DESTINATION_BOTH;
    QTest::newRow("3: destination all") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << 1u << SplitMode::DESTINATION_ALL;
    QTest::newRow("4: destination all") << IntMatrix{} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0u << SplitMode::DESTINATION_ALL;
    QTest::newRow("5: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::ALL_DIFFERENT;
    QTest::newRow("6: all different") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{} << IntMatrix{} << 2u << SplitMode::ALL_DIFFERENT;
    QTest::newRow("7: all different") << IntMatrix{} << IntMatrix{} << IntMatrix{} << 0u << SplitMode::ALL_DIFFERENT;
}

void CommonExceptionTests::testSwapRowsOrColumnsExceptions_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("firstRowColumnNr");
    QTest::addColumn<matrix_size_t>("secondRowColumnNr");

    QTest::newRow("1: second out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 1u << 4u;
    QTest::newRow("2: first out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 4u << 1u;
    QTest::newRow("3: both out of range") << IntMatrix{4, 2, {7, 8, 9, 10, 11, 12, 13, 14}} << 4u << 4u;

    // empty matrixes involved
    QTest::newRow("4: empty matrix") << IntMatrix{} << 0u << 0u;
}

void CommonExceptionTests::_buildResizeExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");

    QTest::newRow("1: null rows and columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0u << 0u << 5;
    QTest::newRow("2: null rows and columns count") << IntMatrix{} << 0u << 0u << 5;
    QTest::newRow("3: null rows count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 0u << 4u << 5;
    QTest::newRow("4: null rows count") << IntMatrix{} << 0u << 4u << 5;
    QTest::newRow("5: null columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3u << 0u << 5;
    QTest::newRow("6: null columns count") << IntMatrix{} << 3u << 0u << 5;
}

void CommonExceptionTests::_buildInsertRowExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");

    QTest::newRow("1: insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 3u << 5;
    QTest::newRow("2: empty matrix") << IntMatrix{} << 0u << 1;
}

void CommonExceptionTests::_buildInsertColumnExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");

    QTest::newRow("1: insert position out of range") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << 4u << 5;
    QTest::newRow("2: empty matrix") << IntMatrix{} << 0u << 2;
}

QTEST_APPLESS_MAIN(CommonExceptionTests)

#include "tst_commonexceptiontests.moc"
