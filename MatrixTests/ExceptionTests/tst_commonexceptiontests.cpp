#include <QTest>

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
    void testVectorConstructorExceptions();
    void testIdenticalElementsConstructorExceptions();
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
    void testVectorConstructorExceptions_data();
    void testIdenticalElementsConstructorExceptions_data();
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
    void _buildResizeExceptionsTestingTable();
    void _buildInsertRowExceptionsTestingTable();
    void _buildInsertColumnExceptionsTestingTable();
};

void CommonExceptionTests::testVectorConstructorExceptions()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {IntMatrix matrix(rowsCount, columnsCount, std::move(initList));});
}

void CommonExceptionTests::testIdenticalElementsConstructorExceptions()
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
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resize(requestedRowsCount, requestedColumnsCount);});
}

void CommonExceptionTests::testResizeAndFillInNewValuesExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);
    QFETCH(int, fillValue);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.resize(requestedRowsCount, requestedColumnsCount, fillValue);});
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
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(ConcatMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case ConcatMode::SOURCE_TO_DESTINATION:
                                     destMatrix.catByRow(srcMatrix);
                                     break;
                                 case ConcatMode::TO_ITSELF:
                                     destMatrix.catByRow(destMatrix);
                                     break;
                                 default:
                                     assert(false);
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testCatByColumnExceptions()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(ConcatMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case ConcatMode::SOURCE_TO_DESTINATION:
                                     destMatrix.catByColumn(srcMatrix);
                                     break;
                                 case ConcatMode::TO_ITSELF:
                                     destMatrix.catByColumn(destMatrix);
                                     break;
                                 default:
                                     assert(false);
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testSplitByRowExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, destMatrix);
    QFETCH(matrix_size_t, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case SplitMode::SOURCE_TO_DESTINATION:
                                     srcMatrix.splitByRow(destMatrix, splitPosition);
                                     break;
                                 case SplitMode::TO_ITSELF:
                                     destMatrix.splitByRow(destMatrix, splitPosition);
                                     break;
                                 default:
                                     assert(false);
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testSplitByColumnExceptions()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, destMatrix);
    QFETCH(matrix_size_t, splitPosition);
    QFETCH(SplitMode, mode);

    QVERIFY_THROWS_EXCEPTION(std::runtime_error,
                             {
                                 switch(mode)
                                 {
                                 case SplitMode::SOURCE_TO_DESTINATION:
                                     srcMatrix.splitByColumn(destMatrix, splitPosition);
                                     break;
                                 case SplitMode::TO_ITSELF:
                                     destMatrix.splitByColumn(destMatrix, splitPosition);
                                     break;
                                 default:
                                     assert(false);
                                     break;
                                 }
                             });
}

void CommonExceptionTests::testSwapRowsOrColumnsExceptions()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, firstRowColumnNr);
    QFETCH(matrix_size_t, secondRowColumnNr);

    IntMatrix auxMatrix{matrix};
    auxMatrix.transpose();

    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {matrix.swapRows(firstRowColumnNr, secondRowColumnNr);});
    QVERIFY_THROWS_EXCEPTION(std::runtime_error, {auxMatrix.swapColumns(firstRowColumnNr, secondRowColumnNr);});
}

void CommonExceptionTests::testVectorConstructorExceptions_data()
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

void CommonExceptionTests::testIdenticalElementsConstructorExceptions_data()
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
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("1: different matrixes, different columns count") << IntMatrix{} << IntMatrix{2, 1, {1, 2}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("2: different matrixes, different columns count") << IntMatrix{2, 1, {1, 2}} << IntMatrix{} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("3: different matrixes, different columns count") << IntMatrix{2, 1, {1, 2}} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("4: different matrixes, different columns count") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}} << IntMatrix{2, 1, {1, 2}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("5: different matrixes, different columns count") << IntMatrix{{4, 7}, 6} << IntMatrix{{10, 8}, -2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("6: different matrixes, different columns count") << IntMatrix{{6, 8}, 12} << IntMatrix{{6, 9}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("7: different matrixes, different columns count") << IntMatrix{{6, 9}, -3} << IntMatrix{{6, 8}, 12} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("8: different matrixes, different columns count") << IntMatrix{{10, 8}, -2} << IntMatrix{{4, 7}, 6} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("9: different matrixes, different columns count") << IntMatrix{{c_HalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 3}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("10: different matrixes, different columns count") << IntMatrix{{c_HalfMaxAllowedDimension, 3}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("11: different matrixes, different columns count") << IntMatrix{{c_HalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 3}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("12: different matrixes, different columns count") << IntMatrix{{c_HalfMaxAllowedDimension, 3}, -3} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("13: different matrixes, different columns count") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 3}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("14: different matrixes, different columns count") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 3}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("15: different matrixes, same columns count") << IntMatrix{{1, 2}, 2} << IntMatrix{{c_MaxAllowedDimension, 2}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("16: different matrixes, same columns count") << IntMatrix{{2, 2}, 2} << IntMatrix{{c_LargeDimension2, 2}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("17: different matrixes, same columns count") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("18: different matrixes, same columns count") << IntMatrix{{c_LargeDimension2, 2}, -3} << IntMatrix{{2, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("19: different matrixes, same columns count") << IntMatrix{{c_MaxAllowedDimension, 2}, -3} << IntMatrix{{1, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("20: different matrixes, same columns count") << IntMatrix{{c_MaxAllowedDimension, 2}, -3} << IntMatrix{{c_MaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("21: same matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, 2} << ConcatMode::TO_ITSELF;
    QTest::newRow("22: same matrix") << IntMatrix{{c_MaxAllowedDimension, 2}, -3} << IntMatrix{{c_MaxAllowedDimension, 2}, 2} << ConcatMode::TO_ITSELF;

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("23: different matrixes, same columns count") << IntMatrix{{c_HalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
        QTest::newRow("24: different matrixes, same columns count") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 2}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    }
}

void CommonExceptionTests::testCatByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");

    QTest::newRow("1: different matrixes, different rows count") << IntMatrix{} << IntMatrix{1, 2, {1, 2}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("2: different matrixes, different rows count") << IntMatrix{1, 2, {1, 2}} << IntMatrix{} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("3: different matrixes, different rows count") << IntMatrix{1, 2, {1, 2}} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("4: different matrixes, different rows count") << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}} << IntMatrix{1, 2, {1, 2}} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("5: different matrixes, different rows count") << IntMatrix{{7, 4}, 6} << IntMatrix{{8, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("6: different matrixes, different rows count") << IntMatrix{{8, 6}, 12} << IntMatrix{{9, 6}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("7: different matrixes, different rows count") << IntMatrix{{9, 6}, -3} << IntMatrix{{8, 6}, 12} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("8: different matrixes, different rows count") << IntMatrix{{8, 10}, -2} << IntMatrix{{7, 4}, 6} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("9: different matrixes, different rows count") << IntMatrix{{2, c_HalfMaxAllowedDimension}, -3} << IntMatrix{{3, c_HalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("10: different matrixes, different rows count") << IntMatrix{{3, c_HalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_HalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("11: different matrixes, different rows count") << IntMatrix{{2, c_HalfMaxAllowedDimension}, -3} << IntMatrix{{3, c_IncrHalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("12: different matrixes, different rows count") << IntMatrix{{3, c_HalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("13: different matrixes, different rows count") << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, -3} << IntMatrix{{3, c_HalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("14: different matrixes, different rows count") << IntMatrix{{3, c_IncrHalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_HalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("15: different matrixes, same rows count") << IntMatrix{{2, 1}, 2} << IntMatrix{{2, c_MaxAllowedDimension}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("16: different matrixes, same rows count") << IntMatrix{{2, 2}, 2} << IntMatrix{{2, c_LargeDimension2}, -3} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("17: different matrixes, same rows count") << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("18: different matrixes, same rows count") << IntMatrix{{2, c_LargeDimension2}, -3} << IntMatrix{{2, 2}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("19: different matrixes, same rows count") << IntMatrix{{2, c_MaxAllowedDimension}, -3} << IntMatrix{{2, 1}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("20: different matrixes, same rows count") << IntMatrix{{2, c_MaxAllowedDimension}, -3} << IntMatrix{{2, c_MaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    QTest::newRow("21: same matrix") << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, 2} << ConcatMode::TO_ITSELF;
    QTest::newRow("22: same matrix") << IntMatrix{{2, c_MaxAllowedDimension}, -3} << IntMatrix{{2, c_MaxAllowedDimension}, 2} << ConcatMode::TO_ITSELF;

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("23: different matrixes, same rows count") << IntMatrix{{2, c_HalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
        QTest::newRow("24: different matrixes, same rows count") << IntMatrix{{2, c_IncrHalfMaxAllowedDimension}, -3} << IntMatrix{{2, c_HalfMaxAllowedDimension}, 2} << ConcatMode::SOURCE_TO_DESTINATION;
    }
}

void CommonExceptionTests::testSplitByRowExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("1: source split to destination") << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("2: source split to destination") << IntMatrix{} << IntMatrix{} << matrix_size_t{1u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("3: source split to destination") << IntMatrix{1, 3, {1, -2, 3}} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("4: source split to destination") << IntMatrix{1, 3, {1, -2, 3}} << IntMatrix{} << matrix_size_t{1u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("5: source split to destination") << IntMatrix{1, 3, {1, -2, 3}} << IntMatrix{} << matrix_size_t{2u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("6: source split to destination") << IntMatrix{2, 3, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("7: source split to destination") << IntMatrix{2, 3, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{2u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("8: source split to destination") << IntMatrix{2, 3, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{3u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("9: source split to destination") << IntMatrix{{c_MaxAllowedDimension, 3}, -5} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("10: source split to destination") << IntMatrix{{c_MaxAllowedDimension, 3}, -5} << IntMatrix{} << c_MaxAllowedDimension << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("11: source split to destination") << IntMatrix{{c_MaxAllowedDimension, 3}, -5} << IntMatrix{} << c_ExceedingDimension << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("12: source split to itself") << IntMatrix{2, 3, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{1u} << SplitMode::TO_ITSELF;
}

void CommonExceptionTests::testSplitByColumnExceptions_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");

    QTest::newRow("1: source split to destination") << IntMatrix{} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("2: source split to destination") << IntMatrix{} << IntMatrix{} << matrix_size_t{1u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("3: source split to destination") << IntMatrix{3, 1, {1, -2, 3}} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("4: source split to destination") << IntMatrix{3, 1, {1, -2, 3}} << IntMatrix{} << matrix_size_t{1u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("5: source split to destination") << IntMatrix{3, 1, {1, -2, 3}} << IntMatrix{} << matrix_size_t{2u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("6: source split to destination") << IntMatrix{3, 2, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("7: source split to destination") << IntMatrix{3, 2, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{2u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("8: source split to destination") << IntMatrix{3, 2, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{3u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("9: source split to destination") << IntMatrix{{3, c_MaxAllowedDimension}, -5} << IntMatrix{} << matrix_size_t{0u} << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("10: source split to destination") << IntMatrix{{3, c_MaxAllowedDimension}, -5} << IntMatrix{} << c_MaxAllowedDimension << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("11: source split to destination") << IntMatrix{{3, c_MaxAllowedDimension}, -5} << IntMatrix{} << c_ExceedingDimension << SplitMode::SOURCE_TO_DESTINATION;
    QTest::newRow("12: source split to itself") << IntMatrix{3, 2, {1, -2, 3, -4, 5, -6}} << IntMatrix{} << matrix_size_t{1u} << SplitMode::TO_ITSELF;
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

void CommonExceptionTests::_buildResizeExceptionsTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<int>("fillValue");

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
