#include <QTest>

#include "tst_resizingtests.h"
#include "tst_resizingtests_data.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class ResizingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixReserve();
    void testIntMatrixResizeWithDefaultNewValues();
    void testIntMatrixResizeAndSetNewValues();
    void testIntMatrixReserveAndResizeWithDefaultNewValues();
    void testIntMatrixReserveAndResizeWithSetNewValues();
    void testIntMatrixShrinkToFit();
    void testIntMatrixInsertRowNoSetValue();
    void testIntMatrixInsertRowSetValue();
    void testIntMatrixInsertColumnNoSetValue();
    void testIntMatrixInsertColumnSetValue();
    void testIntMatrixInsertMultipleRowsSetValue();
    void testIntMatrixInsertMultipleColumnsSetValue();
    void testIntMatrixEraseRow();
    void testIntMatrixEraseMultipleRows();
    void testIntMatrixEraseColumn();
    void testIntMatrixEraseMultipleColumns();
    void testIntMatrixClear();

    void testStringMatrixReserve();
    void testStringMatrixResizeWithDefaultNewValues();
    void testStringMatrixResizeAndSetNewValues();
    void testStringMatrixReserveAndResizeWithDefaultNewValues();
    void testStringMatrixReserveAndResizeWithSetNewValues();
    void testStringMatrixShrinkToFit();
    void testStringMatrixInsertRowNoSetValue();
    void testStringMatrixInsertRowSetValue();
    void testStringMatrixInsertColumnNoSetValue();
    void testStringMatrixInsertColumnSetValue();
    void testStringMatrixInsertMultipleRowsSetValue();
    void testStringMatrixInsertMultipleColumnsSetValue();
    void testStringMatrixEraseRow();
    void testStringMatrixEraseMultipleRows();
    void testStringMatrixEraseColumn();
    void testStringMatrixEraseMultipleColumns();
    void testStringMatrixClear();

    // test data
    void testIntMatrixReserve_data();
    void testIntMatrixResizeWithDefaultNewValues_data();
    void testIntMatrixResizeAndSetNewValues_data();
    void testIntMatrixReserveAndResizeWithDefaultNewValues_data();
    void testIntMatrixReserveAndResizeWithSetNewValues_data();
    void testIntMatrixShrinkToFit_data();
    void testIntMatrixInsertRowNoSetValue_data();
    void testIntMatrixInsertRowSetValue_data();
    void testIntMatrixInsertColumnNoSetValue_data();
    void testIntMatrixInsertColumnSetValue_data();
    void testIntMatrixInsertMultipleRowsSetValue_data();
    void testIntMatrixInsertMultipleColumnsSetValue_data();
    void testIntMatrixEraseRow_data();
    void testIntMatrixEraseMultipleRows_data();
    void testIntMatrixEraseColumn_data();
    void testIntMatrixEraseMultipleColumns_data();
    void testIntMatrixClear_data();

    void testStringMatrixReserve_data();
    void testStringMatrixResizeWithDefaultNewValues_data();
    void testStringMatrixResizeAndSetNewValues_data();
    void testStringMatrixReserveAndResizeWithDefaultNewValues_data();
    void testStringMatrixReserveAndResizeWithSetNewValues_data();
    void testStringMatrixShrinkToFit_data();
    void testStringMatrixInsertRowNoSetValue_data();
    void testStringMatrixInsertRowSetValue_data();
    void testStringMatrixInsertColumnNoSetValue_data();
    void testStringMatrixInsertColumnSetValue_data();
    void testStringMatrixInsertMultipleRowsSetValue_data();
    void testStringMatrixInsertMultipleColumnsSetValue_data();
    void testStringMatrixEraseRow_data();
    void testStringMatrixEraseMultipleRows_data();
    void testStringMatrixEraseColumn_data();
    void testStringMatrixEraseMultipleColumns_data();
    void testStringMatrixClear_data();

private:
    // test data helper methods
    void _buildIntMatrixInsertRowTestingTable();
    void _buildIntMatrixInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
    StringMatrix mPrimaryStringMatrix;
};

void ResizingTests::testIntMatrixReserve()
{
    TEST_MATRIX_RESERVE(int, mPrimaryIntMatrix);
}

void ResizingTests::testIntMatrixResizeWithDefaultNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(requestedRowsCount, requestedColumnsCount);

    TEST_RESERVE_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requestedRowsCount, requestedColumnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    TEST_MATRIX_RESERVE_AND_RESIZE_CHECK_RETAINED_ELEMENT_VALUES(int, matrix, expectedRetainedElementsMatrix);
}

void ResizingTests::testIntMatrixResizeAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_DEFAULT_CAPACITY_AND_SET_NEW_VALUES(int);
}

void ResizingTests::testIntMatrixReserveAndResizeWithDefaultNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);
    QFETCH(matrix_size_t, requestedRowCapacity);
    QFETCH(matrix_size_t, requestedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.reserve(requestedRowCapacity, requestedColumnCapacity);
    matrix.resize(requestedRowsCount, requestedColumnsCount);

    TEST_RESERVE_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requestedRowsCount, requestedColumnsCount, requestedRowCapacity, requestedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    TEST_MATRIX_RESERVE_AND_RESIZE_CHECK_RETAINED_ELEMENT_VALUES(int, matrix, expectedRetainedElementsMatrix);
}

void ResizingTests::testIntMatrixReserveAndResizeWithSetNewValues()
{
    TEST_MATRIX_RESERVE_AND_RESIZE_WITH_SET_NEW_VALUES(int);
}

void ResizingTests::testIntMatrixShrinkToFit()
{
    TEST_MATRIX_SHRINK_TO_FIT(int, mPrimaryIntMatrix);
}

void ResizingTests::testIntMatrixInsertRowNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    bool areRetainedValuesCorrect{true};

    for (matrix_size_t rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr)
    {
        if (rowNr != insertPosition)
        {
            for (matrix_size_t columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr)
            {
                if (matrix.at(rowNr, columnNr) != referenceMatrix.at(rowNr, columnNr))
                {
                    areRetainedValuesCorrect = false;
                    break;
                }
            }
        }
    }

    QVERIFY2(areRetainedValuesCorrect, "Insert row failed, the matrix doesn't have the right values on the existing rows!");
}

void ResizingTests::testIntMatrixInsertRowSetValue()
{
    TEST_MATRIX_INSERT_ROW_SET_VALUE(int);
}

void ResizingTests::testIntMatrixInsertColumnNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    bool areRetainedValuesCorrect{true};

    for (matrix_size_t columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr)
    {
        if (columnNr != insertPosition)
        {
            for (matrix_size_t rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr)
            {
                if (matrix.at(rowNr, columnNr) != referenceMatrix.at(rowNr, columnNr))
                {
                    areRetainedValuesCorrect = false;
                    break;
                }
            }
        }
    }

    QVERIFY2(areRetainedValuesCorrect, "Insert column failed, the matrix doesn't have the right values on the existing columns!");
}

void ResizingTests::testIntMatrixInsertColumnSetValue()
{
    TEST_MATRIX_INSERT_COLUMN_SET_VALUE(int);
}

void ResizingTests::testIntMatrixInsertMultipleRowsSetValue()
{
    TEST_MATRIX_INSERT_MULTIPLE_ROWS_SET_VALUE(int);
}

void ResizingTests::testIntMatrixInsertMultipleColumnsSetValue()
{
    TEST_MATRIX_INSERT_MULTIPLE_COLUMNS_SET_VALUE(int);
}

void ResizingTests::testIntMatrixEraseRow()
{
    TEST_MATRIX_ERASE_ROW(int);
}

void ResizingTests::testIntMatrixEraseMultipleRows()
{
    TEST_MATRIX_ERASE_MULTIPLE_ROWS(int);
}

void ResizingTests::testIntMatrixEraseColumn()
{
    TEST_MATRIX_ERASE_COLUMN(int);
}

void ResizingTests::testIntMatrixEraseMultipleColumns()
{
    TEST_MATRIX_ERASE_MULTIPLE_COLUMNS(int);
}

void ResizingTests::testIntMatrixClear()
{
    TEST_MATRIX_CLEAR(int, mPrimaryIntMatrix);
}

void ResizingTests::testStringMatrixResizeWithDefaultNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, expectedMatrix);

    matrix.resize(requestedRowsCount, requestedColumnsCount);

    TEST_RESERVE_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requestedRowsCount, requestedColumnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == expectedMatrix, "Reserving/resizing failed, the matrix does not have the correct values!");
}

void ResizingTests::testStringMatrixReserve()
{
    TEST_MATRIX_RESERVE(std::string, mPrimaryStringMatrix);
}

void ResizingTests::testStringMatrixResizeAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_DEFAULT_CAPACITY_AND_SET_NEW_VALUES(std::string);
}

void ResizingTests::testStringMatrixReserveAndResizeWithDefaultNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(matrix_size_t, requestedRowsCount);
    QFETCH(matrix_size_t, requestedColumnsCount);
    QFETCH(matrix_size_t, requestedRowCapacity);
    QFETCH(matrix_size_t, requestedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, expectedMatrix);

    matrix.reserve(requestedRowCapacity, requestedColumnCapacity);
    matrix.resize(requestedRowsCount, requestedColumnsCount);

    TEST_RESERVE_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requestedRowsCount, requestedColumnsCount, requestedRowCapacity, requestedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == expectedMatrix, "Reserving/resizing failed, the matrix does not have the correct values!");
}

void ResizingTests::testStringMatrixReserveAndResizeWithSetNewValues()
{
    TEST_MATRIX_RESERVE_AND_RESIZE_WITH_SET_NEW_VALUES(std::string);
}

void ResizingTests::testStringMatrixShrinkToFit()
{
    TEST_MATRIX_SHRINK_TO_FIT(std::string, mPrimaryStringMatrix);
}

void ResizingTests::testStringMatrixInsertRowNoSetValue()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == referenceMatrix, "Insert row failed, the matrix does not have the right values!");
}

void ResizingTests::testStringMatrixInsertRowSetValue()
{
    TEST_MATRIX_INSERT_ROW_SET_VALUE(std::string);
}

void ResizingTests::testStringMatrixInsertColumnNoSetValue()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(matrix_size_t, insertPosition);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == referenceMatrix, "Insert column failed, the matrix doesn't have the right values!");
}

void ResizingTests::testStringMatrixInsertColumnSetValue()
{
    TEST_MATRIX_INSERT_COLUMN_SET_VALUE(std::string);
}

void ResizingTests::testStringMatrixInsertMultipleRowsSetValue()
{
    TEST_MATRIX_INSERT_MULTIPLE_ROWS_SET_VALUE(std::string);
}

void ResizingTests::testStringMatrixInsertMultipleColumnsSetValue()
{
    TEST_MATRIX_INSERT_MULTIPLE_COLUMNS_SET_VALUE(std::string);
}

void ResizingTests::testStringMatrixEraseRow()
{
    TEST_MATRIX_ERASE_ROW(std::string);
}

void ResizingTests::testStringMatrixEraseMultipleRows()
{
    TEST_MATRIX_ERASE_MULTIPLE_ROWS(std::string);
}

void ResizingTests::testStringMatrixEraseColumn()
{
    TEST_MATRIX_ERASE_COLUMN(std::string);
}

void ResizingTests::testStringMatrixEraseMultipleColumns()
{
    TEST_MATRIX_ERASE_MULTIPLE_COLUMNS(std::string);
}

void ResizingTests::testStringMatrixClear()
{
    TEST_MATRIX_CLEAR(std::string, mPrimaryStringMatrix);
}

void ResizingTests::testIntMatrixReserve_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: row capacity < rows count, column capacity < columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: row capacity < rows count, column capacity == columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: row capacity < rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: row capacity < rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: row capacity == rows count, column capacity < columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: row capacity == rows count, column capacity == columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("7: row capacity == rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: row capacity == rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: row capacity > rows count, column capacity < columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: row capacity > rows count, column capacity < columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{6u} << matrix_size_t{2u} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("11: row capacity > rows count, column capacity == columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: row capacity > rows count, column capacity == columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: row capacity > rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: row capacity > rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: row capacity > rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{6u} << matrix_size_t{4u} << matrix_size_t{6u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: row capacity > rows count, column capacity > columns count") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ResizingTests::testIntMatrixResizeWithDefaultNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{};
    QTest::newRow("8: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("9: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("10: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("11: equal rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix1_10x9;
    QTest::newRow("18: more rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x9;
    QTest::newRow("19: more rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << c_IntMatrix1_10x9;
    QTest::newRow("20: more rows, more columns") << IntMatrix{} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{};
    QTest::newRow("21: equal rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_IntMatrix1_7x9;
    QTest::newRow("23: less rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_IntMatrix1_8x9;
    QTest::newRow("24: more rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x7;
    QTest::newRow("25: more rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("27: more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("28: equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixResizeAndSetNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{3u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{5u} << -1 << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{3u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};  // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{4u} << -1 << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("7: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -1 << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{{1, 1}, -1};
    QTest::newRow("8: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{3u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("9: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{4u} << -1 << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1}};
    QTest::newRow("10: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {1, 2, 4, 5, 7, 8, 10, 11, -1, -1}};
    QTest::newRow("11: equal rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{7u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{8u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{9u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{9u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{7u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{8u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_IntMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix2_10x11;
    QTest::newRow("18: more rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{9u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix2_12x9;
    QTest::newRow("19: more rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << c_IntMatrix2_12x11;
    QTest::newRow("20: more rows, more columns") << IntMatrix{} << matrix_size_t{12u} << matrix_size_t{11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{{12, 11}, 5};
    QTest::newRow("21: equal rows, equal columns") << c_IntMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{9u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_IntMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_IntMatrix2_7x11;
    QTest::newRow("23: less rows, more columns") << c_IntMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_IntMatrix2_8x11;
    QTest::newRow("24: more rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{7u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix2_12x7;
    QTest::newRow("25: more rows, less columns") << c_IntMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{8u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix2_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{5u} << -1 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};
    QTest::newRow("27: more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << matrix_size_t{5u} << -1 << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1, 13, 14, 15, 16, -1, -1, -1, -1, -1, -1}};
    QTest::newRow("28: equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << matrix_size_t{3u} << matrix_size_t{3u} << -1 << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixReserveAndResizeWithDefaultNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("8: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("9: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
}

void ResizingTests::testIntMatrixReserveAndResizeWithSetNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << -1 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{3u} << -1 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << -1 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{5u} << -1 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{3u} << -1 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{4u} << -1 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("7: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{3u} << -1 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("8: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{4u} << -1 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << IntMatrix{3, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1}};
    QTest::newRow("9: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << -1 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << IntMatrix{5, 2, {1, 2, 4, 5, 7, 8, 10, 11, -1, -1}};
}

void ResizingTests::testIntMatrixShrinkToFit_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("1: empty matrix") << IntMatrix{};
    QTest::newRow("2: square matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("3: more rows than columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("4: less rows than columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: square matrix") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("6: square matrix") << c_IntMatrix1_8x8;
    QTest::newRow("7: more rows than columns") << c_IntMatrix1_10x9;
    QTest::newRow("8: less rows than columns") << c_IntMatrix1_8x9;
}

void ResizingTests::testIntMatrixInsertRowNoSetValue_data()
{
    _buildIntMatrixInsertRowTestingTable();
}

void ResizingTests::testIntMatrixInsertRowSetValue_data()
{
    _buildIntMatrixInsertRowTestingTable();
}

void ResizingTests::testIntMatrixInsertColumnNoSetValue_data()
{
    _buildIntMatrixInsertColumnTestingTable();
}

void ResizingTests::testIntMatrixInsertColumnSetValue_data()
{
    _buildIntMatrixInsertColumnTestingTable();
}

void ResizingTests::testIntMatrixInsertMultipleRowsSetValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("insertPositions");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{0u, 0u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3a_12x9;
    QTest::newRow("2: append both") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{10u, 11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix2_12x9;
    QTest::newRow("3: prepend, then append") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{0u, 11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3b_12x9;
    QTest::newRow("4: append, then prepend") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{10u, 0u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3b_12x9;
    QTest::newRow("5: insert in the first half, then in the second") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{2u, 9u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3c_12x9;
    QTest::newRow("6: insert in the second half, then in the first") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{8u, 2u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3c_12x9;
    QTest::newRow("7: insert both in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{5u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3d_12x9;
    QTest::newRow("8: insert both in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{4u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3a_11x10;
    QTest::newRow("9: prepend, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{0u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3e_12x9;
    QTest::newRow("10: insert in the middle, then prepend") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{5u, 0u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3f_12x9;
    QTest::newRow("11: prepend, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{0u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3b_11x10;
    QTest::newRow("12: insert in the middle, then prepend") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{4u, 0u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3b_11x10;
    QTest::newRow("13: insert in the middle, then append") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{5u, 11u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3g_12x9;
    QTest::newRow("14: append, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{10u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3g_12x9;
    QTest::newRow("15: insert in the middle, then append") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{4u, 10u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3c_11x10;
    QTest::newRow("16: append, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{9u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_IntMatrix3d_11x10;
}

void ResizingTests::testIntMatrixInsertMultipleColumnsSetValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("insertPositions");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{0u, 0u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3a_9x12;
    QTest::newRow("2: append both") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{10u, 11u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3b_9x12;
    QTest::newRow("3: prepend, then append") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{0u, 11u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3c_9x12;
    QTest::newRow("4: append, then prepend") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{10u, 0u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3c_9x12;
    QTest::newRow("5: insert in the first half, then in the second") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{2u, 9u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3d_9x12;
    QTest::newRow("6: insert in the second half, then in the first") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{8u, 2u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3d_9x12;
    QTest::newRow("7: insert both in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{5u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3e_9x12;
    QTest::newRow("8: insert both in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{4u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3a_10x11;
    QTest::newRow("9: prepend, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{0u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3f_9x12;
    QTest::newRow("10: insert in the middle, then prepend") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{5u, 0u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3g_9x12;
    QTest::newRow("11: prepend, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{0u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3b_10x11;
    QTest::newRow("12: insert in the middle, then prepend") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{4u, 0u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3b_10x11;
    QTest::newRow("13: insert in the middle, then append") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{5u, 11u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3h_9x12;
    QTest::newRow("14: append, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<matrix_size_t>{10u, 5u} << 5 << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3h_9x12;
    QTest::newRow("15: insert in the middle, then append") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{4u, 10u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3c_10x11;
    QTest::newRow("16: append, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<matrix_size_t>{9u, 5u} << 5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_IntMatrix3d_10x11;
}

void ResizingTests::testIntMatrixEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 4, {5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("2: erase at middle position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{1u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 4, {1, 2, 3, 4, 9, 10, 11, 12}};
    QTest::newRow("3: erase at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 4, {1, 2, 3, 4, 5, 6, 7, 8}};
    QTest::newRow("4: erase the only row") << IntMatrix{1, 4, {1, 2, 3, 4}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("5: erase at beginning position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: erase at random position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {1, 2, 3, 4, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: erase at middle position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12}};
    QTest::newRow("8: erase at random position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12}};
    QTest::newRow("9: erase at end position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    QTest::newRow("10: erase at beginning position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase at random position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {1, 2, 3, 4, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("12: erase at middle position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{3u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("13: erase at random position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{4u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14}};
    QTest::newRow("14: erase at end position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("15: erase at beginning position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{7, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("16: erase at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("17: erase at middle position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{4u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("18: erase at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 14, 15, 16}};
    QTest::newRow("19: erase at end position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("20: erase at beginning position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{8, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("21: erase at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{3u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("22: erase at middle position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{4u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("23: erase at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{5u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("24: erase at end position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("25: erase the only row") << IntMatrix{1, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleRows_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("erasePositions");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{0, 0, 0, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("2: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 1, 1} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{1, 3, {1, 2, 3}};
    QTest::newRow("3: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 2} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("4: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 2, 0, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("5: erase from middle") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 1, 1, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("6: erase from end") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 1, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("7: erase from beginning/end") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{0, 2} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {4, 5, 6, 7, 8, 9}};
    QTest::newRow("8: erase from end/beginning") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 0} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {4, 5, 6, 7, 8, 9}};
    QTest::newRow("9: erase from beginning/end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("10: erase from end/beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase from beginning/end by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 5, 4, 0} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("12: erase from beginning/end by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 5, 4, 0, 0} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("13: erase from beginning/end by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6, 5, 0, 0} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("14: erase from beginning/end by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6, 5, 0, 0, 2} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("15: erase from end/beginning by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 0, 0, 3} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("16: erase from end/beginning by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 0, 0, 3, 2} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {5, 6, 7, 8}};
    QTest::newRow("17: erase from end/beginning by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0, 0, 4, 3} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("18: erase from end/beginning by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0, 0, 4, 3, 0} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("19: erase from beginning") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 0, 0, 0} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {9, 10, 11, 12, 13, 14}};
    QTest::newRow("20: erase from beginning") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {11, 12, 13, 14}};
    QTest::newRow("21: erase from beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{6u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {11, 12, 13, 14, 15, 16}};
    QTest::newRow("22: erase from beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0, 0} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {13, 14, 15, 16}};
    QTest::newRow("23: erase from middle") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 2, 1} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 11, 12}};
    QTest::newRow("24: erase from middle") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 2, 1, 1} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{1, 2, {1, 2}};
    QTest::newRow("25: erase from middle") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{3, 3, 2, 2} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 3, 4, 13, 14}};
    QTest::newRow("26: erase from middle") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{3, 3, 2, 2, 1} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 13, 14}};
    QTest::newRow("27: erase from middle") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 3, 3, 2, 2} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 3, 4, 15, 16}};
    QTest::newRow("28: erase from middle") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 3, 3, 2, 2, 1} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 15, 16}};
    QTest::newRow("29: erase from middle") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{4, 4, 3, 3, 2, 2} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 3, 4, 17, 18}};
    QTest::newRow("30: erase from middle") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{4, 4, 3, 3, 2, 2, 1} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 17, 18}};
    QTest::newRow("31: erase from end") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 5, 4, 3} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("32: erase from end") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 5, 4, 3, 2} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 3, 4}};
    QTest::newRow("33: erase from end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 6, 5, 4, 3} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("34: erase from end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 6, 5, 4, 3, 2} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 2, 3, 4}};
    QTest::newRow("35: erase from random positions") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 1, 2, 0} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {7, 8, 11, 12}};
    QTest::newRow("36: erase from random positions") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 4, 1, 2, 0} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} <<IntMatrix{1, 2, {7, 8}};
    QTest::newRow("37: erase from random positions") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{2, 4, 1, 2} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 7, 8, 13, 14}};
    QTest::newRow("38: erase from random positions") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{1, 0, 3, 1, 2} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {5, 6, 9, 10}};
    QTest::newRow("39: erase from random positions") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{6, 0, 2, 4, 2} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {3, 4, 5, 6, 11, 12}};
    QTest::newRow("40: erase from random positions") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 0, 5, 1, 1, 1} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {3, 4, 13, 14}};
    QTest::newRow("41: erase from random positions") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{5, 5, 1, 1, 3, 3} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 7, 8, 9, 10}};
    QTest::newRow("42: erase from random positions") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{1, 6, 5, 1, 3, 1, 0} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {9, 10, 17, 18}};
}

void ResizingTests::testIntMatrixEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{4, 2, {2, 3, 5, 6, 8, 9, 11, 12}};
    QTest::newRow("2: erase at middle position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{1u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 2, {1, 3, 4, 6, 7, 9, 10, 12}};
    QTest::newRow("3: erase at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("4: erase the only column") << IntMatrix{4, 1, {1, 2, 3, 4}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("5: erase at beginning position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 5, {2, 3, 4, 5, 6, 8, 9, 10, 11, 12}};
    QTest::newRow("6: erase at random position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 5, {1, 2, 4, 5, 6, 7, 8, 10, 11, 12}};
    QTest::newRow("7: erase at middle position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 5, {1, 2, 3, 5, 6, 7, 8, 9, 11, 12}};
    QTest::newRow("8: erase at random position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 5, {1, 2, 3, 4, 6, 7, 8, 9, 10, 12}};
    QTest::newRow("9: erase at end position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 5, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11}};
    QTest::newRow("10: erase at beginning position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase at random position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 6, {1, 2, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14}};
    QTest::newRow("12: erase at middle position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 6, {1, 2, 3, 5, 6, 7, 8, 9, 10, 12, 13, 14}};
    QTest::newRow("13: erase at random position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 6, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 13, 14}};
    QTest::newRow("14: erase at end position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << matrix_size_t{6u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}};
    QTest::newRow("15: erase at beginning position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 7, {2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("16: erase at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 7, {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16}};
    QTest::newRow("17: erase at middle position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 7, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16}};
    QTest::newRow("18: erase at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 7, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 15, 16}};
    QTest::newRow("19: erase at end position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("20: erase at beginning position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 8, {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("21: erase at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 8, {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18}};
    QTest::newRow("22: erase at middle position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 8, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18}};
    QTest::newRow("23: erase at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 8, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18}};
    QTest::newRow("24: erase at end position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17}};
    QTest::newRow("25: erase the only column") << IntMatrix{9, 1, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("erasePositions");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{0, 0, 0, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("2: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 1, 1} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 1, {1, 5, 9}};
    QTest::newRow("3: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 2} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 2, {1, 2, 5, 6, 9, 10}};
    QTest::newRow("4: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 2, 0, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("5: erase from middle") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 1, 1, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("6: erase from end") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 1, 0} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << IntMatrix{};
    QTest::newRow("7: erase from beginning/end") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{0, 2} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{3, 2, {2, 3, 6, 7, 10, 11}};
    QTest::newRow("8: erase from end/beginning") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 0} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{3, 2, {2, 3, 6, 7, 10, 11}};
    QTest::newRow("9: erase from beginning/end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("10: erase from end/beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("11: erase from beginning/end by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 5, 4, 0} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 3, {3, 4, 5, 10, 11, 12}};
    QTest::newRow("12: erase from beginning/end by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 5, 4, 0, 0} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {4, 5, 11, 12}};
    QTest::newRow("13: erase from beginning/end by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6, 5, 0, 0} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u} << IntMatrix{2, 3, {4, 5, 6, 12, 13, 14}};
    QTest::newRow("14: erase from beginning/end by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 6, 5, 0, 0, 2} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {4, 5, 12, 13}};
    QTest::newRow("15: erase from end/beginning by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 0, 0, 3} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 3, {3, 4, 5, 10, 11, 12}};
    QTest::newRow("16: erase from end/beginning by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 0, 0, 3, 2} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {3, 4, 10, 11}};
    QTest::newRow("17: erase from end/beginning by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0, 0, 4, 3} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << IntMatrix{2, 3, {3, 4, 5, 11, 12, 13}};
    QTest::newRow("18: erase from end/beginning by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 0, 0, 4, 3, 0} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {4, 5, 12, 13}};
    QTest::newRow("19: erase from beginning") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 0, 0, 0} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u} << IntMatrix{2, 3, {5, 6, 7, 12, 13, 14}};
    QTest::newRow("20: erase from beginning") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {6, 7, 13, 14}};
    QTest::newRow("21: erase from beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{6u} << IntMatrix{2, 3, {6, 7, 8, 14, 15, 16}};
    QTest::newRow("22: erase from beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{0, 0, 0, 0, 0, 0} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {7, 8, 15, 16}};
    QTest::newRow("23: erase from middle") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 2, 1} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 2, {1, 6, 7, 12}};
    QTest::newRow("24: erase from middle") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{3, 2, 2, 1, 1} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 1, {1, 7}};
    QTest::newRow("25: erase from middle") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{3, 3, 2, 2} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {1, 2, 7, 8, 9, 14}};
    QTest::newRow("26: erase from middle") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{3, 3, 2, 2, 1} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {1, 7, 8, 14}};
    QTest::newRow("27: erase from middle") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 3, 3, 2, 2} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 3, {1, 2, 8, 9, 10, 16}};
    QTest::newRow("28: erase from middle") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 3, 3, 2, 2, 1} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {1, 8, 9, 16}};
    QTest::newRow("29: erase from middle") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{4, 4, 3, 3, 2, 2} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 3, {1, 2, 9, 10, 11, 18}};
    QTest::newRow("30: erase from middle") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{4, 4, 3, 3, 2, 2, 1} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {1, 9, 10, 18}};
    QTest::newRow("31: erase from end") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 5, 4, 3} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 3, {1, 2, 3, 8, 9, 10}};
    QTest::newRow("32: erase from end") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{6, 5, 4, 3, 2} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {1, 2, 8, 9}};
    QTest::newRow("33: erase from end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 6, 5, 4, 3} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 3, {1, 2, 3, 9, 10, 11}};
    QTest::newRow("34: erase from end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{7, 6, 5, 4, 3, 2} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {1, 2, 9, 10}};
    QTest::newRow("35: erase from random positions") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{1, 1, 2, 0} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << IntMatrix{2, 2, {4, 6, 10, 12}};
    QTest::newRow("36: erase from random positions") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<matrix_size_t>{2, 4, 1, 2, 0} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 1, {4, 10}};
    QTest::newRow("37: erase from random positions") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{2, 4, 1, 2} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << IntMatrix{2, 3, {1, 4, 7, 8, 11, 14}};
    QTest::newRow("38: erase from random positions") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<matrix_size_t>{1, 0, 3, 1, 2} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {3, 5, 10, 12}};
    QTest::newRow("39: erase from random positions") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{6, 0, 2, 4, 2} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << IntMatrix{2, 3, {2, 3, 6, 10, 11, 14}};
    QTest::newRow("40: erase from random positions") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<matrix_size_t>{4, 0, 5, 1, 1, 1} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {2, 7, 10, 15}};
    QTest::newRow("41: erase from random positions") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{5, 5, 1, 1, 3, 3} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << IntMatrix{2, 3, {1, 4, 5, 10, 13, 14}};
    QTest::newRow("42: erase from random positions") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<matrix_size_t>{1, 6, 5, 1, 3, 1, 0} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 2, {5, 9, 14, 18}};
}

void ResizingTests::testIntMatrixClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("1: non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("2: non-empty matrix") << c_IntMatrix1_8x9;
    QTest::newRow("3: empty matrix") << IntMatrix{};
}

void ResizingTests::testStringMatrixReserve_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: row capacity < rows count, column capacity < columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: row capacity < rows count, column capacity == columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: row capacity < rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: row capacity < rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: row capacity == rows count, column capacity < columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: row capacity == rows count, column capacity == columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("7: row capacity == rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: row capacity == rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: row capacity > rows count, column capacity < columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: row capacity > rows count, column capacity < columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{6u} << matrix_size_t{2u} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("11: row capacity > rows count, column capacity == columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: row capacity > rows count, column capacity == columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_size_t{6u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: row capacity > rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: row capacity > rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: row capacity > rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{6u} << matrix_size_t{4u} << matrix_size_t{6u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: row capacity > rows count, column capacity > columns count") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void ResizingTests::testStringMatrixResizeWithDefaultNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 5, {"First", "Second", "Third", "", "", "Fourth", "Fifth", "Sixth", "", "", "Seventh", "Eighth", "Ninth", "", "", "Tenth", "Eleventh", "Twelfth", "", ""}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", "", "", "", "", ""}};
    QTest::newRow("7: more rows, more columns") << StringMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{{1, 1}, ""};
    QTest::newRow("8: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("9: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", ""}};
    QTest::newRow("10: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "", ""}};
    QTest::newRow("11: equal rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix1_10x11;
    QTest::newRow("18: more rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix1_12x9;
    QTest::newRow("19: more rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << c_StringMatrix1_12x11;
    QTest::newRow("20: more rows, more columns") << StringMatrix{} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{{12, 11}, ""};
    QTest::newRow("21: equal rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_StringMatrix1_7x11;
    QTest::newRow("23: less rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_StringMatrix1_8x11;
    QTest::newRow("24: more rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix1_12x7;
    QTest::newRow("25: more rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix1_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", ""}};
    QTest::newRow("27: more rows, more columns") << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "13th", "14th", "15th", "16th", "", "", "", "", "", ""}};
    QTest::newRow("28: equal rows, equal columns") << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
}

void ResizingTests::testStringMatrixResizeAndSetNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<std::string>("fillValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 5, {"First", "Second", "Third", "/NEW_VALUE/", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("7: more rows, more columns") << StringMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << std::string{"/NEW_VALUE/"} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{{1, 1}, "/NEW_VALUE/"};
    QTest::newRow("8: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("9: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/"}};
    QTest::newRow("10: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("11: equal rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{7u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{8u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{9u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{9u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{7u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{8u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << c_StringMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix2_10x11;
    QTest::newRow("18: more rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{9u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix2_12x9;
    QTest::newRow("19: more rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << c_StringMatrix2_12x11;
    QTest::newRow("20: more rows, more columns") << StringMatrix{} << matrix_size_t{12u} << matrix_size_t{11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{{12, 11}, "5Z"};
    QTest::newRow("21: equal rows, equal columns") << c_StringMatrix1_10x9 << matrix_size_t{10u} << matrix_size_t{9u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << c_StringMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{7u} << matrix_size_t{11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_StringMatrix2_7x11;
    QTest::newRow("23: less rows, more columns") << c_StringMatrix1_10x9 << matrix_size_t{8u} << matrix_size_t{11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << c_StringMatrix2_8x11;
    QTest::newRow("24: more rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{7u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix2_12x7;
    QTest::newRow("25: more rows, less columns") << c_StringMatrix1_10x9 << matrix_size_t{12u} << matrix_size_t{8u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix2_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{5u} << std::string{"/NEW_VALUE/"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};
    QTest::newRow("27: more rows, more columns") << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{5u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "13th", "14th", "15th", "16th", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("28: equal rows, equal columns") << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}} << matrix_size_t{3u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
}

void ResizingTests::testStringMatrixReserveAndResizeWithDefaultNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u} << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << StringMatrix{4, 5, {"First", "Second", "Third", "", "", "Fourth", "Fifth", "Sixth", "", "", "Seventh", "Eighth", "Ninth", "", "", "Tenth", "Eleventh", "Twelfth", "", ""}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}};
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{4u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << StringMatrix{5, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", "", "", "", "", ""}};
    QTest::newRow("7: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("8: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{4u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << StringMatrix{3, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", ""}};
    QTest::newRow("9: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "", ""}};
}

void ResizingTests::testStringMatrixReserveAndResizeWithSetNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowsCount");
    QTest::addColumn<matrix_size_t>("requestedColumnsCount");
    QTest::addColumn<std::string>("fillValue");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u} << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << std::string{"/NEW_VALUE/"} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << StringMatrix{4, 5, {"First", "Second", "Third", "/NEW_VALUE/", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << StringMatrix{5, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("7: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("8: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{4u} << matrix_opt_size_t{3u} << StringMatrix{3, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/"}};
    QTest::newRow("9: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{5u} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u} << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "/NEW_VALUE/", "/NEW_VALUE/"}};
}

void ResizingTests::testStringMatrixShrinkToFit_data()
{
    QTest::addColumn<StringMatrix>("matrix");

    QTest::newRow("1: empty matrix") << StringMatrix{};
    QTest::newRow("2: square matrix") << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
    QTest::newRow("3: more rows than columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("4: less rows than columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("5: square matrix") << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "13th", "14th", "15th", "16th"}};
    QTest::newRow("6: square matrix") << c_StringMatrix1_8x8;
    QTest::newRow("7: more rows than columns") << c_StringMatrix1_10x9;
    QTest::newRow("8: less rows than columns") << c_StringMatrix1_8x9;

}

void ResizingTests::testStringMatrixInsertRowNoSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "", "", "", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"", "", "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "", "", "", "", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"", "", "", "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", "", ""}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"", "", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "", "", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "", "15th", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "", ""}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"", "", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "", "", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "", "15th", "16th", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "", ""}};
}

void ResizingTests::testStringMatrixInsertRowSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << std::string{"/NEW_VALUE/"} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << std::string{"/NEW_VALUE/"} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"/New/", "/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{2u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "/New/", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "/New/", "/New/", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "/New/", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "/New/", "15th", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{8u} << std::string{"/New/"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/", "/New/"}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"/New/", "/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{2u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "/New/", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "/New/", "/New/", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "/New/", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{7u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "/New/", "15th", "16th", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{9u} << std::string{"/New/"} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "/New/", "/New/"}};
}

void ResizingTests::testStringMatrixInsertColumnNoSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "", "Third", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "Tenth", "", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"", "First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"First", "", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "", "Eighth", "Ninth", "Tenth", "", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"", "First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", ""}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", ""}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{9u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", ""}};
}

void ResizingTests::testStringMatrixInsertColumnSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << std::string{"/NEW_VALUE/"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "/NEW_VALUE/", "Third", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "Tenth", "/NEW_VALUE/", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << std::string{"/NEW_VALUE/"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"/NEW_VALUE/", "First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{4u} << std::string{"/NEW_VALUE/"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"First", "/NEW_VALUE/", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "/NEW_VALUE/", "Eighth", "Ninth", "Tenth", "/NEW_VALUE/", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"/NEW_VALUE/", "First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{3u} << std::string{"/NEW_VALUE/"} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{2u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "/New/", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "/New/", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "/New/", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "/New/", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "/New/", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "/New/", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "/New/", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "/New/", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{8u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/"}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "/New/", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{2u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "/New/", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "/New/", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "/New/", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "/New/", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "/New/", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "/New/", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{7u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "/New/", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{9u} << std::string{"/New/"} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "/New/", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "/New/"}};
}

void ResizingTests::testStringMatrixInsertMultipleRowsSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("insertPositions");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{0u, 0u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3a_12x9;
    QTest::newRow("2: append both") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{10u, 11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix2_12x9;
    QTest::newRow("3: prepend, then append") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{0u, 11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3b_12x9;
    QTest::newRow("4: append, then prepend") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{10u, 0u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3b_12x9;
    QTest::newRow("5: insert in the first half, then in the second") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{2u, 9u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3c_12x9;
    QTest::newRow("6: insert in the second half, then in the first") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{8u, 2u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3c_12x9;
    QTest::newRow("7: insert both in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{5u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3d_12x9;
    QTest::newRow("8: insert both in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{4u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3a_11x10;
    QTest::newRow("9: prepend, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{0u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3e_12x9;
    QTest::newRow("10: insert in the middle, then prepend") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{5u, 0u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3f_12x9;
    QTest::newRow("11: prepend, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{0u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3b_11x10;
    QTest::newRow("12: insert in the middle, then prepend") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{4u, 0u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3b_11x10;
    QTest::newRow("13: insert in the middle, then append") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{5u, 11u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3g_12x9;
    QTest::newRow("14: append, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{10u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3g_12x9;
    QTest::newRow("15: insert in the middle, then append") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{4u, 10u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3c_11x10;
    QTest::newRow("16: append, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{9u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << c_StringMatrix3d_11x10;
}

void ResizingTests::testStringMatrixInsertMultipleColumnsSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("insertPositions");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{0u, 0u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3a_9x12;
    QTest::newRow("2: append both") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{10u, 11u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3b_9x12;
    QTest::newRow("3: prepend, then append") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{0u, 11u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3c_9x12;
    QTest::newRow("4: append, then prepend") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{10u, 0u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3c_9x12;
    QTest::newRow("5: insert in the first half, then in the second") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{2u, 9u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3d_9x12;
    QTest::newRow("6: insert in the second half, then in the first") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{8u, 2u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3d_9x12;
    QTest::newRow("7: insert both in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{5u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3e_9x12;
    QTest::newRow("8: insert both in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{4u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3a_10x11;
    QTest::newRow("9: prepend, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{0u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3f_9x12;
    QTest::newRow("10: insert in the middle, then prepend") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{5u, 0u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3g_9x12;
    QTest::newRow("11: prepend, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{0u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3b_10x11;
    QTest::newRow("12: insert in the middle, then prepend") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{4u, 0u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3b_10x11;
    QTest::newRow("13: insert in the middle, then append") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{5u, 11u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3h_9x12;
    QTest::newRow("14: append, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<matrix_size_t>{10u, 5u} << std::string{"5Z"} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3h_9x12;
    QTest::newRow("15: insert in the middle, then append") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{4u, 10u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3c_10x11;
    QTest::newRow("16: append, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<matrix_size_t>{9u, 5u} << std::string{"5Z"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << c_StringMatrix3d_10x11;
}

void ResizingTests::testStringMatrixEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 4, {"Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: erase at middle position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 4, {"First", "Second", "Third", "Fourth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: erase at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth"}};
    QTest::newRow("4: erase the only row") << StringMatrix{1, 4, {"First", "Second", "Third", "Fourth"}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("5: erase at beginning position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{0u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("6: erase at random position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("7: erase at middle position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{3u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("8: erase at random position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{4u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th"}};
    QTest::newRow("9: erase at end position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{5u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("10: erase at beginning position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase at random position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("12: erase at middle position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{3u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("13: erase at random position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{4u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("14: erase at end position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("15: erase at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{7, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("16: erase at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("17: erase at middle position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("18: erase at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("19: erase at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{8, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("21: erase at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("22: erase at middle position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("23: erase at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("24: erase at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("25: erase the only row") << StringMatrix{1, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th"}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleRows_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("erasePositions");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("2: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{1u, 1u, 1u} << matrix_size_t{2u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{1, 3, {"First", "Second", "Third"}};
    QTest::newRow("3: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{2u, 2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("4: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{1u, 2u, 0u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("5: erase from middle") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{2u, 1u, 1u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("6: erase from end") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{3u, 2u, 1u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("7: erase from beginning/end") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{0u, 2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
    QTest::newRow("8: erase from end/beginning") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{3u, 0u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
    QTest::newRow("9: erase from beginning/end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("10: erase from end/beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase from beginning/end by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 5u, 4u, 0u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("12: erase from beginning/end by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 5u, 4u, 0u, 0u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("13: erase from beginning/end by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u, 5u, 0u, 0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("14: erase from beginning/end by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u, 5u, 0u, 0u, 2u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("15: erase from end/beginning by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 0u, 0u, 3u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("16: erase from end/beginning by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 0u, 0u, 3u, 2u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"5th", "6th", "7th", "8th"}};
    QTest::newRow("17: erase from end/beginning by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u, 0u, 4u, 3u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("18: erase from end/beginning by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u, 0u, 4u, 3u, 0u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("19: erase from beginning") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase from beginning") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"11th", "12th", "13th", "14th"}};
    QTest::newRow("21: erase from beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{6u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("22: erase from beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u, 0u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"13th", "14th", "15th", "16th"}};
    QTest::newRow("23: erase from middle") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{3u, 2u, 2u, 1u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "11th", "12th"}};
    QTest::newRow("24: erase from middle") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{3u, 2u, 2u, 1u, 1u} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{1, 2, {"1st", "2nd"}};
    QTest::newRow("25: erase from middle") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{3u, 3u, 2u, 2u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "13th", "14th"}};
    QTest::newRow("26: erase from middle") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{3u, 3u, 2u, 2u, 1u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "13th", "14th"}};
    QTest::newRow("27: erase from middle") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 3u, 3u, 2u, 2u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "15th", "16th"}};
    QTest::newRow("28: erase from middle") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 3u, 3u, 2u, 2u, 1u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "15th", "16th"}};
    QTest::newRow("29: erase from middle") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{4u, 4u, 3u, 3u, 2u, 2u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "17th", "18th"}};
    QTest::newRow("30: erase from middle") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{4u, 4u, 3u, 3u, 2u, 2u, 1u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "17th", "18th"}};
    QTest::newRow("31: erase from end") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 5u, 4u, 3u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th"}};
    QTest::newRow("32: erase from end") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 5u, 4u, 3u, 2u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "3rd", "4th"}};
    QTest::newRow("33: erase from end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 6u, 5u, 4u, 3u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th"}};
    QTest::newRow("34: erase from end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 6u, 5u, 4u, 3u, 2u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "2nd", "3rd", "4th"}};
    QTest::newRow("35: erase from random positions") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{1u, 1u, 2u, 0u} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"7th", "8th", "11th", "12th"}};
    QTest::newRow("36: erase from random positions") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{2u, 4u, 1u, 2u, 0u} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{1, 2, {"7th", "8th"}};
    QTest::newRow("37: erase from random positions") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{2u, 4u, 1u, 2u} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "7th", "8th", "13th", "14th"}};
    QTest::newRow("38: erase from random positions") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{1u, 0u, 3u, 1u, 2u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"5th", "6th", "9th", "10th"}};
    QTest::newRow("39: erase from random positions") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{6u, 0u, 2u, 4u, 2u} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"3rd", "4th", "5th", "6th", "11th", "12th"}};
    QTest::newRow("40: erase from random positions") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 0u, 5u, 1u, 1u, 1u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"3rd", "4th", "13th", "14th"}};
    QTest::newRow("41: erase from random positions") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{5u, 5u, 1u, 1u, 3u, 3u} << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"1st", "2nd", "7th", "8th", "9th", "10th"}};
    QTest::newRow("42: erase from random positions") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{1u, 6u, 5u, 1u, 3u, 1u, 0u} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"9th", "10th", "17th", "18th"}};
}

void ResizingTests::testStringMatrixEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("erasePosition");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{0u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{4, 2, {"Second", "Third", "Fifth", "Sixth", "Eighth", "Ninth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: erase at middle position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{1u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 2, {"First", "Third", "Fourth", "Sixth", "Seventh", "Ninth", "Tenth", "Twelfth"}};
    QTest::newRow("3: erase at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << matrix_size_t{2u} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("4: erase the only column") << StringMatrix{4, 1, {"First", "Second", "Third", "Fourth"}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("5: erase at beginning position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 5, {"2nd", "3rd", "4th", "5th", "6th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("6: erase at random position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 5, {"1st", "2nd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th"}};
    QTest::newRow("7: erase at middle position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 5, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "11th", "12th"}};
    QTest::newRow("8: erase at random position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 5, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "12th"}};
    QTest::newRow("9: erase at end position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 5, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th"}};
    QTest::newRow("10: erase at beginning position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase at random position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 6, {"1st", "2nd", "4th", "5th", "6th", "7th", "8th", "9th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("12: erase at middle position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 6, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "12th", "13th", "14th"}};
    QTest::newRow("13: erase at random position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "13th", "14th"}};
    QTest::newRow("14: erase at end position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << matrix_size_t{6u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "8th", "9th", "10th", "11th", "12th", "13th"}};
    QTest::newRow("15: erase at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 7, {"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("16: erase at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 7, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("17: erase at middle position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "14th", "15th", "16th"}};
    QTest::newRow("18: erase at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "15th", "16th"}};
    QTest::newRow("19: erase at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << matrix_size_t{7u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "9th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("20: erase at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 8, {"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("21: erase at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 8, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("22: erase at middle position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{4u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("23: erase at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{5u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "16th", "17th", "18th"}};
    QTest::newRow("24: erase at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << matrix_size_t{8u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th"}};
    QTest::newRow("25: erase the only column") << StringMatrix{9, 1, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th"}} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<matrix_size_t>>("erasePositions");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("2: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{1u, 1u, 1u} << matrix_size_t{3u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 1, {"First", "Fifth", "Ninth"}};
    QTest::newRow("3: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{2u, 2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{3, 2, {"First", "Second", "Fifth", "Sixth", "Ninth", "Tenth"}};
    QTest::newRow("4: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{1u, 2u, 0u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("5: erase from middle") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{2u, 1u, 1u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("6: erase from end") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{3u, 2u, 1u, 0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{} << StringMatrix{};
    QTest::newRow("7: erase from beginning/end") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{0u, 2u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{3, 2, {"Second", "Third", "Sixth", "Seventh", "Tenth", "Eleventh"}};
    QTest::newRow("8: erase from end/beginning") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<matrix_size_t>{3u, 0u} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{3, 2, {"Second", "Third", "Sixth", "Seventh", "Tenth", "Eleventh"}};
    QTest::newRow("9: erase from beginning/end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("10: erase from end/beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("11: erase from beginning/end by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 5u, 4u, 0u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 3, {"3rd", "4th", "5th", "10th", "11th", "12th"}};
    QTest::newRow("12: erase from beginning/end by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 5u, 4u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"4th", "5th", "11th", "12th"}};
    QTest::newRow("13: erase from beginning/end by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u, 5u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u} << StringMatrix{2, 3, {"4th", "5th", "6th", "12th", "13th", "14th"}};
    QTest::newRow("14: erase from beginning/end by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 6u, 5u, 0u, 0u, 2u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"4th", "5th", "12th", "13th"}};
    QTest::newRow("15: erase from end/beginning by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 0u, 0u, 3u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 3, {"3rd", "4th", "5th", "10th", "11th", "12th"}};
    QTest::newRow("16: erase from end/beginning by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 0u, 0u, 3u, 2u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"3rd", "4th", "10th", "11th"}};
    QTest::newRow("17: erase from end/beginning by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u, 0u, 4u, 3u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << StringMatrix{2, 3, {"3rd", "4th", "5th", "11th", "12th", "13th"}};
    QTest::newRow("18: erase from end/beginning by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 0u, 0u, 4u, 3u, 0u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"4th", "5th", "12th", "13th"}};
    QTest::newRow("19: erase from beginning") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u} << StringMatrix{2, 3, {"5th", "6th", "7th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase from beginning") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"6th", "7th", "13th", "14th"}};
    QTest::newRow("21: erase from beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{6u} << StringMatrix{2, 3, {"6th", "7th", "8th", "14th", "15th", "16th"}};
    QTest::newRow("22: erase from beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{0u, 0u, 0u, 0u, 0u, 0u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"7th", "8th", "15th", "16th"}};
    QTest::newRow("23: erase from middle") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{3u, 2u, 2u, 1u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 2, {"1st", "6th", "7th", "12th"}};
    QTest::newRow("24: erase from middle") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{3u, 2u, 2u, 1u, 1u} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 1, {"1st", "7th"}};
    QTest::newRow("25: erase from middle") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{3u, 3u, 2u, 2u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"1st", "2nd", "7th", "8th", "9th", "14th"}};
    QTest::newRow("26: erase from middle") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{3u, 3u, 2u, 2u, 1u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"1st", "7th", "8th", "14th"}};
    QTest::newRow("27: erase from middle") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 3u, 3u, 2u, 2u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 3, {"1st", "2nd", "8th", "9th", "10th", "16th"}};
    QTest::newRow("28: erase from middle") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 3u, 3u, 2u, 2u, 1u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"1st", "8th", "9th", "16th"}};
    QTest::newRow("29: erase from middle") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{4u, 4u, 3u, 3u, 2u, 2u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 3, {"1st", "2nd", "9th", "10th", "11th", "18th"}};
    QTest::newRow("30: erase from middle") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{4u, 4u, 3u, 3u, 2u, 2u, 1u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"1st", "9th", "10th", "18th"}};
    QTest::newRow("31: erase from end") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 5u, 4u, 3u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 3, {"1st", "2nd", "3rd", "8th", "9th", "10th"}};
    QTest::newRow("32: erase from end") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{6u, 5u, 4u, 3u, 2u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"1st", "2nd", "8th", "9th"}};
    QTest::newRow("33: erase from end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 6u, 5u, 4u, 3u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 3, {"1st", "2nd", "3rd", "9th", "10th", "11th"}};
    QTest::newRow("34: erase from end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{7u, 6u, 5u, 4u, 3u, 2u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"1st", "2nd", "9th", "10th"}};
    QTest::newRow("35: erase from random positions") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{1u, 1u, 2u, 0u} << matrix_size_t{2u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << StringMatrix{2, 2, {"4th", "6th", "10th", "12th"}};
    QTest::newRow("36: erase from random positions") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<matrix_size_t>{2u, 4u, 1u, 2u, 0u} << matrix_size_t{2u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << StringMatrix{2, 1, {"4th", "10th"}};
    QTest::newRow("37: erase from random positions") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{2u, 4u, 1u, 2u} << matrix_size_t{2u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << StringMatrix{2, 3, {"1st", "4th", "7th", "8th", "11th", "14th"}};
    QTest::newRow("38: erase from random positions") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<matrix_size_t>{1u, 0u, 3u, 1u, 2u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"3rd", "5th", "10th", "12th"}};
    QTest::newRow("39: erase from random positions") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{6u, 0u, 2u, 4u, 2u} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << StringMatrix{2, 3, {"2nd", "3rd", "6th", "10th", "11th", "14th"}};
    QTest::newRow("40: erase from random positions") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<matrix_size_t>{4u, 0u, 5u, 1u, 1u, 1u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"2nd", "7th", "10th", "15th"}};
    QTest::newRow("41: erase from random positions") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{5u, 5u, 1u, 1u, 3u, 3u} << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << StringMatrix{2, 3, {"1st", "4th", "5th", "10th", "13th", "14th"}};
    QTest::newRow("42: erase from random positions") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<matrix_size_t>{1u, 6u, 5u, 1u, 3u, 1u, 0u} << matrix_size_t{2u} << matrix_size_t{4u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << StringMatrix{2, 2, {"5th", "9th", "14th", "18th"}};
}

void ResizingTests::testStringMatrixClear_data()
{
    QTest::addColumn<StringMatrix>("matrix");

    QTest::newRow("1: non-empty matrix") << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("2: non-empty matrix") << c_StringMatrix1_8x9;
    QTest::newRow("3: empty matrix") << StringMatrix{};
}

void ResizingTests::_buildIntMatrixInsertRowTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, -1, -1, -1, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("2: insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 3, {-1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("3: insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << -1 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{1u} << -1 << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{4, 4, {1, 2, 3, 4, -1, -1, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << -1 << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{4, 4, {-1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << -1 << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1, -1}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{0u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {-1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("8: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{2u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("9: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{3u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, -1, -1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("10: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{4u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, -1, -1, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("11: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("12: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{7u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, -1, 15, 16}};
    QTest::newRow("13: insert at end position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{8u} << -1 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1, -1}};
    QTest::newRow("14: insert at beginning position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{0u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {-1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("15: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{2u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("16: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{3u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, -1, -1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("17: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{4u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, -1, -1, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("18: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{5u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("19: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{7u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, -1, 15, 16, 17, 18}};
    QTest::newRow("20: insert at end position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{9u} << -1 << matrix_size_t{11u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1, -1}};
}

void ResizingTests::_buildIntMatrixInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{2u} << -1 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 5, {1, 2, -1, 3, 4, 5, 6, -1, 7, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("2: insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << -1 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 5, {-1, 1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12}};
    QTest::newRow("3: insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{4u} << -1 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{1u} << -1 << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{4, 4, {1, -1, 2, 3, 4, -1, 5, 6, 7, -1, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("5: insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{0u} << -1 << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{4, 4, {-1, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12}};
    QTest::newRow("6: insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << matrix_size_t{3u} << -1 << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{4, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{0u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 9, {-1, 1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("8: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{2u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 9, {1, 2, -1, 3, 4, 5, 6, 7, 8, 9, 10, -1, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("9: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{3u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 9, {1, 2, 3, -1, 4, 5, 6, 7, 8, 9, 10, 11, -1, 12, 13, 14, 15, 16}};
    QTest::newRow("10: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{4u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 9, {1, 2, 3, 4, -1, 5, 6, 7, 8, 9, 10, 11, 12, -1, 13, 14, 15, 16}};
    QTest::newRow("11: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{5u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 9, {1, 2, 3, 4, 5, -1, 6, 7, 8, 9, 10, 11, 12, 13, -1, 14, 15, 16}};
    QTest::newRow("12: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{7u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, 12, 13, 14, 15, -1, 16}};
    QTest::newRow("13: insert at end position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << matrix_size_t{8u} << -1 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 10, 11, 12, 13, 14, 15, 16, -1}};
    QTest::newRow("14: insert at beginning position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{0u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 10, {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("15: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{2u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 10, {1, 2, -1, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("16: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{3u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 10, {1, 2, 3, -1, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("17: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{4u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << IntMatrix{2, 10, {1, 2, 3, 4, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, -1, 14, 15, 16, 17, 18}};
    QTest::newRow("18: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{5u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 10, {1, 2, 3, 4, 5, -1, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, 15, 16, 17, 18}};
    QTest::newRow("19: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{7u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 10, {1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1, 17, 18}};
    QTest::newRow("20: insert at end position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << matrix_size_t{9u} << -1 << matrix_size_t{2u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << IntMatrix{2, 10, {1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1}};
}

QTEST_APPLESS_MAIN(ResizingTests)

#include "tst_resizingtests.moc"
