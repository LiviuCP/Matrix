#include <QtTest>

#include "tst_resizingtests.h"
#include "tst_resizingtests_data.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class ResizingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixResizeWithDefaultCapacityAndDefaultNewValues();
    void testIntMatrixResizeWithDefaultCapacityAndSetNewValues();
    void testIntMatrixResizeWithFixedCapacityAndDefaultNewValues();
    void testIntMatrixResizeWithFixedCapacityAndSetNewValues();
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

    void testStringMatrixResizeWithDefaultCapacityAndDefaultNewValues();
    void testStringMatrixResizeWithDefaultCapacityAndSetNewValues();
    void testStringMatrixResizeWithFixedCapacityAndDefaultNewValues();
    void testStringMatrixResizeWithFixedCapacityAndSetNewValues();
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
    void testIntMatrixResizeWithDefaultCapacityAndDefaultNewValues_data();
    void testIntMatrixResizeWithDefaultCapacityAndSetNewValues_data();
    void testIntMatrixResizeWithFixedCapacityAndDefaultNewValues_data();
    void testIntMatrixResizeWithFixedCapacityAndSetNewValues_data();
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

    void testStringMatrixResizeWithDefaultCapacityAndDefaultNewValues_data();
    void testStringMatrixResizeWithDefaultCapacityAndSetNewValues_data();
    void testStringMatrixResizeWithFixedCapacityAndDefaultNewValues_data();
    void testStringMatrixResizeWithFixedCapacityAndSetNewValues_data();
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

void ResizingTests::testIntMatrixResizeWithDefaultCapacityAndDefaultNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    TEST_MATRIX_RESIZE_CHECK_RETAINED_ELEMENT_VALUES(int, matrix, expectedRetainedElementsMatrix);
}

void ResizingTests::testIntMatrixResizeWithDefaultCapacityAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_DEFAULT_CAPACITY_AND_SET_NEW_VALUES(int);
}

void ResizingTests::testIntMatrixResizeWithFixedCapacityAndDefaultNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(matrix.getNrOfRows(), matrix.getNrOfColumns(), resizeRowCapacity, resizeColumnCapacity);
    matrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
    TEST_MATRIX_RESIZE_CHECK_RETAINED_ELEMENT_VALUES(int, matrix, expectedRetainedElementsMatrix);
}

void ResizingTests::testIntMatrixResizeWithFixedCapacityAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_FIXED_CAPACITY_AND_SET_NEW_VALUES(int);
}

void ResizingTests::testIntMatrixShrinkToFit()
{
    TEST_MATRIX_SHRINK_TO_FIT(int, mPrimaryIntMatrix);
}

void ResizingTests::testIntMatrixInsertRowNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    bool areRetainedValuesCorrect{true};

    for (IntMatrixSizeType rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr)
    {
        if (rowNr != insertPosition)
        {
            for (IntMatrixSizeType columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr)
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
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    bool areRetainedValuesCorrect{true};

    for (IntMatrixSizeType columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr)
    {
        if (columnNr != insertPosition)
        {
            for (IntMatrixSizeType rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr)
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

void ResizingTests::testStringMatrixResizeWithDefaultCapacityAndDefaultNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, resizeRowsCount);
    QFETCH(StringMatrixSizeType, resizeColumnsCount);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, expectedMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");
}

void ResizingTests::testStringMatrixResizeWithDefaultCapacityAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_DEFAULT_CAPACITY_AND_SET_NEW_VALUES(std::string);
}

void ResizingTests::testStringMatrixResizeWithFixedCapacityAndDefaultNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, resizeRowsCount);
    QFETCH(StringMatrixSizeType, resizeColumnsCount);
    QFETCH(StringMatrixSizeType, resizeRowCapacity);
    QFETCH(StringMatrixSizeType, resizeColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixSizeType, expectedColumnCapacityOffset);
    QFETCH(StringMatrix, expectedMatrix);

    matrix.resize(matrix.getNrOfRows(), matrix.getNrOfColumns(), resizeRowCapacity, resizeColumnCapacity);
    matrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");
}

void ResizingTests::testStringMatrixResizeWithFixedCapacityAndSetNewValues()
{
    TEST_MATRIX_RESIZE_WITH_FIXED_CAPACITY_AND_SET_NEW_VALUES(std::string);
}

void ResizingTests::testStringMatrixShrinkToFit()
{
    TEST_MATRIX_SHRINK_TO_FIT(std::string, mPrimaryStringMatrix);
}

void ResizingTests::testStringMatrixInsertRowNoSetValue()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, insertPosition);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixSizeType, expectedColumnCapacityOffset);
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
    QFETCH(StringMatrixSizeType, insertPosition);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixSizeType, expectedColumnCapacityOffset);
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

void ResizingTests::testIntMatrixResizeWithDefaultCapacityAndDefaultNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << 4 << 2 << 0 << 0 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 2 << 3 << 0 << 0 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 2 << 0 << 0 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << 4 << 5 << 0 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << 5 << 3 << 0 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << 5 << 4 << 0 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: more rows, more columns") << IntMatrix{} << 1 << 1 << 1 << 1 << 0 << 0 << IntMatrix{};
    QTest::newRow("8: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << 4 << 3 << 0 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("9: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << 3 << 4 << 0 << 0 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("10: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << 5 << 2 << 0 << 0 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("11: equal rows, less columns") << c_IntMatrix1_10x9 << 10 << 7 << 10 << 7 << 0 << 0 << c_IntMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_IntMatrix1_10x9 << 10 << 8 << 10 << 8 << 0 << 0 << c_IntMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_IntMatrix1_10x9 << 7 << 9 << 7 << 9 << 0 << 0 << c_IntMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_IntMatrix1_10x9 << 8 << 9 << 8 << 9 << 0 << 0 << c_IntMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_IntMatrix1_10x9 << 7 << 7 << 7 << 7 << 0 << 0 << c_IntMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_IntMatrix1_10x9 << 8 << 8 << 8 << 8 << 0 << 0 << c_IntMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_IntMatrix1_10x9 << 10 << 11 << 10 << 11 << 0 << 0 << c_IntMatrix1_10x9;
    QTest::newRow("18: more rows, equal columns") << c_IntMatrix1_10x9 << 12 << 9 << 12 << 9 << 0 << 0 << c_IntMatrix1_10x9;
    QTest::newRow("19: more rows, more columns") << c_IntMatrix1_10x9 << 12 << 11 << 12 << 11 << 0 << 0 << c_IntMatrix1_10x9;
    QTest::newRow("20: more rows, more columns") << IntMatrix{} << 12 << 11 << 12 << 11 << 0 << 0 << IntMatrix{};
    QTest::newRow("21: equal rows, equal columns") << c_IntMatrix1_10x9 << 10 << 9 << 10 << 9 << 0 << 0 << c_IntMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_IntMatrix1_10x9 << 7 << 11 << 7 << 11 << 0 << 0 << c_IntMatrix1_7x9;
    QTest::newRow("23: less rows, more columns") << c_IntMatrix1_10x9 << 8 << 11 << 8 << 11 << 0 << 0 << c_IntMatrix1_8x9;
    QTest::newRow("24: more rows, less columns") << c_IntMatrix1_10x9 << 12 << 7 << 12 << 7 << 0 << 0 << c_IntMatrix1_10x7;
    QTest::newRow("25: more rows, less columns") << c_IntMatrix1_10x9 << 12 << 8 << 12 << 8 << 0 << 0 << c_IntMatrix1_10x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 5 << 3 << 5 << 0 << 0 << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("27: more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 5 << 5 << 5 << 0 << 0 << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("28: equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 3 << 3 << 3 << 3 << 0 << 0 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixResizeWithDefaultCapacityAndSetNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << -1 << 4 << 2 << 0 << 0 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << -1 << 2 << 3 << 0 << 0 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -1 << 3 << 2 << 0 << 0 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << -1 << 4 << 5 << 0 << 0 << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << -1 << 5 << 3 << 0 << 0 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};  // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << -1 << 5 << 4 << 0 << 0 << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("7: more rows, more columns") << IntMatrix{} << 1 << 1 << -1 << 1 << 1 << 0 << 0 << IntMatrix{1, 1, -1};
    QTest::newRow("8: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << -1 << 4 << 3 << 0 << 0 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("9: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << -1 << 3 << 4 << 0 << 0 << IntMatrix{3, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1}};
    QTest::newRow("10: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << -1 << 5 << 2 << 0 << 0 << IntMatrix{5, 2, {1, 2, 4, 5, 7, 8, 10, 11, -1, -1}};
    QTest::newRow("11: equal rows, less columns") << c_IntMatrix1_10x9 << 10 << 7 << 5 << 10 << 7 << 0 << 0 << c_IntMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_IntMatrix1_10x9 << 10 << 8 << 5 << 10 << 8 << 0 << 0 << c_IntMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_IntMatrix1_10x9 << 7 << 9 << 5 << 7 << 9 << 0 << 0 << c_IntMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_IntMatrix1_10x9 << 8 << 9 << 5 << 8 << 9 << 0 << 0 << c_IntMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_IntMatrix1_10x9 << 7 << 7 << 5 << 7 << 7 << 0 << 0 << c_IntMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_IntMatrix1_10x9 << 8 << 8 << 5 << 8 << 8 << 0 << 0 << c_IntMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_IntMatrix1_10x9 << 10 << 11 << 5 << 10 << 11 << 0 << 0 << c_IntMatrix2_10x11;
    QTest::newRow("18: more rows, equal columns") << c_IntMatrix1_10x9 << 12 << 9 << 5 << 12 << 9 << 0 << 0 << c_IntMatrix2_12x9;
    QTest::newRow("19: more rows, more columns") << c_IntMatrix1_10x9 << 12 << 11 << 5 << 12 << 11 << 0 << 0 << c_IntMatrix2_12x11;
    QTest::newRow("20: more rows, more columns") << IntMatrix{} << 12 << 11 << 5 << 12 << 11 << 0 << 0 << IntMatrix{12, 11, 5};
    QTest::newRow("21: equal rows, equal columns") << c_IntMatrix1_10x9 << 10 << 9 << 5 << 10 << 9 << 0 << 0 << c_IntMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_IntMatrix1_10x9 << 7 << 11 << 5 << 7 << 11 << 0 << 0 << c_IntMatrix2_7x11;
    QTest::newRow("23: less rows, more columns") << c_IntMatrix1_10x9 << 8 << 11 << 5 << 8 << 11 << 0 << 0 << c_IntMatrix2_8x11;
    QTest::newRow("24: more rows, less columns") << c_IntMatrix1_10x9 << 12 << 7 << 5 << 12 << 7 << 0 << 0 << c_IntMatrix2_12x7;
    QTest::newRow("25: more rows, less columns") << c_IntMatrix1_10x9 << 12 << 8 << 5 << 12 << 8 << 0 << 0 << c_IntMatrix2_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 5 << -1 << 3 << 5 << 0 << 0 << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};
    QTest::newRow("27: more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 5 << -1 << 5 << 5 << 0 << 0 << IntMatrix{5, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1, 13, 14, 15, 16, -1, -1, -1, -1, -1, -1}};
    QTest::newRow("28: equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 3 << 3 << -1 << 3 << 3 << 0 << 0 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixResizeWithFixedCapacityAndDefaultNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << 10 << 8 << 3 << 3 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 10 << 8 << 4 << 2 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 11 << 10 << 4 << 4 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << 11 << 10 << 3 << 2 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << 10 << 8 << 2 << 2 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << 10 << 9 << 2 << 2 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << 10 << 9 << 3 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("8: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << 11 << 9 << 4 << 2 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("9: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << 10 << 8 << 2 << 3 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
}

void ResizingTests::testIntMatrixResizeWithFixedCapacityAndSetNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << -1 << 10 << 8 << 3 << 3 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << -1 << 10 << 8 << 4 << 2 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("3: less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -1 << 11 << 10 << 4 << 4 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("4: equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << -1 << 11 << 10 << 3 << 2 << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};
    QTest::newRow("5: more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << -1 << 10 << 8 << 2 << 2 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};
    QTest::newRow("6: more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << -1 << 10 << 9 << 2 << 2 << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("7: equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << -1 << 10 << 9 << 3 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("8: less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << -1 << 11 << 9 << 4 << 2 << IntMatrix{3, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1}};
    QTest::newRow("9: more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << -1 << 10 << 8 << 2 << 3 << IntMatrix{5, 2, {1, 2, 4, 5, 7, 8, 10, 11, -1, -1}};
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
    QTest::addColumn<std::vector<IntMatrixSizeType>>("insertPositions");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{0, 0} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3a_12x9;
    QTest::newRow("2: append both") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{10, 11} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix2_12x9;
    QTest::newRow("3: prepend, then append") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{0, 11} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3b_12x9;
    QTest::newRow("4: append, then prepend") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{10, 0} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3b_12x9;
    QTest::newRow("5: insert in the first half, then in the second") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{2, 9} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3c_12x9;
    QTest::newRow("6: insert in the second half, then in the first") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{8, 2} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3c_12x9;
    QTest::newRow("7: insert both in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{5, 5} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3d_12x9;
    QTest::newRow("8: insert both in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{4, 5} << 5 << 11 << 12 << 0 << 1 << c_IntMatrix3a_11x10;
    QTest::newRow("9: prepend, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{0, 5} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3e_12x9;
    QTest::newRow("10: insert in the middle, then prepend") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{5, 0} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3f_12x9;
    QTest::newRow("11: prepend, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{0, 5} << 5 << 11 << 12 << 0 << 1 << c_IntMatrix3b_11x10;
    QTest::newRow("12: insert in the middle, then prepend") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{4, 0} << 5 << 11 << 12 << 0 << 1 << c_IntMatrix3b_11x10;
    QTest::newRow("13: insert in the middle, then append") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{5, 11} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3g_12x9;
    QTest::newRow("14: append, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{10, 5} << 5 << 12 << 11 << 0 << 1 << c_IntMatrix3g_12x9;
    QTest::newRow("15: insert in the middle, then append") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{4, 10} << 5 << 11 << 12 << 0 << 1 << c_IntMatrix3c_11x10;
    QTest::newRow("16: append, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{9, 5} << 5 << 11 << 12 << 0 << 1 << c_IntMatrix3d_11x10;
}

void ResizingTests::testIntMatrixInsertMultipleColumnsSetValue_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<IntMatrixSizeType>>("insertPositions");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{0, 0} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3a_9x12;
    QTest::newRow("2: append both") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{10, 11} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3b_9x12;
    QTest::newRow("3: prepend, then append") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{0, 11} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3c_9x12;
    QTest::newRow("4: append, then prepend") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{10, 0} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3c_9x12;
    QTest::newRow("5: insert in the first half, then in the second") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{2, 9} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3d_9x12;
    QTest::newRow("6: insert in the second half, then in the first") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{8, 2} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3d_9x12;
    QTest::newRow("7: insert both in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{5, 5} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3e_9x12;
    QTest::newRow("8: insert both in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{4, 5} << 5 << 12 << 11 << 1 << 0 << c_IntMatrix3a_10x11;
    QTest::newRow("9: prepend, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{0, 5} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3f_9x12;
    QTest::newRow("10: insert in the middle, then prepend") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{5, 0} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3g_9x12;
    QTest::newRow("11: prepend, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{0, 5} << 5 << 12 << 11 << 1 << 0 << c_IntMatrix3b_10x11;
    QTest::newRow("12: insert in the middle, then prepend") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{4, 0} << 5 << 12 << 11 << 1 << 0 << c_IntMatrix3b_10x11;
    QTest::newRow("13: insert in the middle, then append") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{5, 11} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3h_9x12;
    QTest::newRow("14: append, then insert in the middle") << c_IntMatrix3_9x10 << std::vector<IntMatrixSizeType>{10, 5} << 5 << 11 << 12 << 1 << 0 << c_IntMatrix3h_9x12;
    QTest::newRow("15: insert in the middle, then append") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{4, 10} << 5 << 12 << 11 << 1 << 0 << c_IntMatrix3c_10x11;
    QTest::newRow("16: append, then insert in the middle") << c_IntMatrix1_10x9 << std::vector<IntMatrixSizeType>{9, 5} << 5 << 12 << 11 << 1 << 0 << c_IntMatrix3d_10x11;
}

void ResizingTests::testIntMatrixEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 3 << 5 << 1 << 0 << IntMatrix{2, 4, {5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("2: erase at middle position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 3 << 5 << 0 << 0 << IntMatrix{2, 4, {1, 2, 3, 4, 9, 10, 11, 12}};
    QTest::newRow("3: erase at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 5 << 0 << 0 << IntMatrix{2, 4, {1, 2, 3, 4, 5, 6, 7, 8}};
    QTest::newRow("4: erase the only row") << IntMatrix{1, 4, {1, 2, 3, 4}} << 0 << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("5: erase at beginning position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 7 << 2 << 1 << 0 << IntMatrix{5, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: erase at random position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 7 << 2 << 1 << 0 << IntMatrix{5, 2, {1, 2, 3, 4, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("7: erase at middle position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 7 << 2 << 0 << 0 << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12}};
    QTest::newRow("8: erase at random position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 7 << 2 << 0 << 0 << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12}};
    QTest::newRow("9: erase at end position") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 7 << 2 << 0 << 0 << IntMatrix{5, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}};
    QTest::newRow("10: erase at beginning position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 0 << 8 << 2 << 1 << 0 << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase at random position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 2 << 8 << 2 << 1 << 0 << IntMatrix{6, 2, {1, 2, 3, 4, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("12: erase at middle position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 8 << 2 << 0 << 0 << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("13: erase at random position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 4 << 8 << 2 << 0 << 0 << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14}};
    QTest::newRow("14: erase at end position") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 6 << 8 << 2 << 0 << 0 << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("15: erase at beginning position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 0 << 10 << 2 << 2 << 0 << IntMatrix{7, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("16: erase at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 3 << 10 << 2 << 2 << 0 << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("17: erase at middle position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 4 << 10 << 2 << 1 << 0 << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("18: erase at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 10 << 2 << 1 << 0 << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 14, 15, 16}};
    QTest::newRow("19: erase at end position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 7 << 10 << 2 << 1 << 0 << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("20: erase at beginning position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 11 << 2 << 2 << 0 << IntMatrix{8, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("21: erase at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 3 << 11 << 2 << 2 << 0 << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("22: erase at middle position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 4 << 11 << 2 << 1 << 0 << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("23: erase at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 5 << 11 << 2 << 1 << 0 << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("24: erase at end position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 8 << 11 << 2 << 1 << 0 << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("25: erase the only row") << IntMatrix{1, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 0 << 0 << 0 << -1 << -1 << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleRows_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<IntMatrixSizeType>>("erasePositions");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("2: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 1, 1} << 2 << 3 << 0 << 0 << IntMatrix{1, 3, {1, 2, 3}};
    QTest::newRow("3: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 2} << 5 << 3 << 0 << 0 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("4: erase from random positions") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 2, 0, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("5: erase from middle") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 1, 1, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("6: erase from end") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 1, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("7: erase from beginning/end") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{0, 2} << 5 << 3 << 1 << 0 << IntMatrix{2, 3, {4, 5, 6, 7, 8, 9}};
    QTest::newRow("8: erase from end/beginning") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 0} << 5 << 3 << 1 << 0 << IntMatrix{2, 3, {4, 5, 6, 7, 8, 9}};
    QTest::newRow("9: erase from beginning/end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6} << 10 << 2 << 2 << 0 << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("10: erase from end/beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0} << 10 << 2 << 2 << 0 << IntMatrix{6, 2, {3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase from beginning/end by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 5, 4, 0} << 8 << 2 << 2 << 0 << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("12: erase from beginning/end by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 5, 4, 0, 0} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("13: erase from beginning/end by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6, 5, 0, 0} << 10 << 2 << 4 << 0 << IntMatrix{3, 2, {7, 8, 9, 10, 11, 12}};
    QTest::newRow("14: erase from beginning/end by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6, 5, 0, 0, 2} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("15: erase from end/beginning by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 0, 0, 3} << 8 << 2 << 2 << 0 << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("16: erase from end/beginning by changing order") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 0, 0, 3, 2} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {5, 6, 7, 8}};
    QTest::newRow("17: erase from end/beginning by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0, 0, 4, 3} << 10 << 2 << 3 << 0 << IntMatrix{3, 2, {5, 6, 7, 8, 9, 10}};
    QTest::newRow("18: erase from end/beginning by changing order") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0, 0, 4, 3, 0} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {7, 8, 9, 10}};
    QTest::newRow("19: erase from beginning") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0} << 8 << 2 << 4 << 0 << IntMatrix{3, 2, {9, 10, 11, 12, 13, 14}};
    QTest::newRow("20: erase from beginning") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {11, 12, 13, 14}};
    QTest::newRow("21: erase from beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0} << 10 << 2 << 6 << 0 << IntMatrix{3, 2, {11, 12, 13, 14, 15, 16}};
    QTest::newRow("22: erase from beginning") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0, 0} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {13, 14, 15, 16}};
    QTest::newRow("23: erase from middle") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 2, 1} << 7 << 2 << 0 << 0 << IntMatrix{2, 2, {1, 2, 11, 12}};
    QTest::newRow("24: erase from middle") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 2, 1, 1} << 2 << 2 << 0 << 0 << IntMatrix{1, 2, {1, 2}};
    QTest::newRow("25: erase from middle") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{3, 3, 2, 2} << 8 << 2 << 0 << 0 << IntMatrix{3, 2, {1, 2, 3, 4, 13, 14}};
    QTest::newRow("26: erase from middle") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {1, 2, 13, 14}};
    QTest::newRow("27: erase from middle") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 3, 3, 2, 2} << 10 << 2 << 1 << 0 << IntMatrix{3, 2, {1, 2, 3, 4, 15, 16}};
    QTest::newRow("28: erase from middle") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {1, 2, 15, 16}};
    QTest::newRow("29: erase from middle") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{4, 4, 3, 3, 2, 2} << 11 << 2 << 1 << 0 << IntMatrix{3, 2, {1, 2, 3, 4, 17, 18}};
    QTest::newRow("30: erase from middle") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{4, 4, 3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {1, 2, 17, 18}};
    QTest::newRow("31: erase from end") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 5, 4, 3} << 8 << 2 << 0 << 0 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("32: erase from end") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 5, 4, 3, 2} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {1, 2, 3, 4}};
    QTest::newRow("33: erase from end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 6, 5, 4, 3} << 10 << 2 << 1 << 0 << IntMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("34: erase from end") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 6, 5, 4, 3, 2} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {1, 2, 3, 4}};
    QTest::newRow("35: erase from random positions") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 1, 2, 0} << 7 << 2 << 3 << 0 << IntMatrix{2, 2, {7, 8, 11, 12}};
    QTest::newRow("36: erase from random positions") << IntMatrix{6, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 4, 1, 2, 0} << 2 << 2 << 0 << 0 <<IntMatrix{1, 2, {7, 8}};
    QTest::newRow("37: erase from random positions") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{2, 4, 1, 2} << 8 << 2 << 2 << 0 << IntMatrix{3, 2, {1, 2, 7, 8, 13, 14}};
    QTest::newRow("38: erase from random positions") << IntMatrix{7, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{1, 0, 3, 1, 2} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {5, 6, 9, 10}};
    QTest::newRow("39: erase from random positions") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{6, 0, 2, 4, 2} << 10 << 2 << 3 << 0 << IntMatrix{3, 2, {3, 4, 5, 6, 11, 12}};
    QTest::newRow("40: erase from random positions") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 0, 5, 1, 1, 1} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {3, 4, 13, 14}};
    QTest::newRow("41: erase from random positions") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{5, 5, 1, 1, 3, 3} << 11 << 2 << 3 << 0 << IntMatrix{3, 2, {1, 2, 7, 8, 9, 10}};
    QTest::newRow("42: erase from random positions") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{1, 6, 5, 1, 3, 1, 0} << 4 << 2 << 1 << 0 << IntMatrix{2, 2, {9, 10, 17, 18}};
}

void ResizingTests::testIntMatrixEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 5 << 3 << 0 << 1 << IntMatrix{4, 2, {2, 3, 5, 6, 8, 9, 11, 12}};
    QTest::newRow("2: erase at middle position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 5 << 3 << 0 << 0 << IntMatrix{4, 2, {1, 3, 4, 6, 7, 9, 10, 12}};
    QTest::newRow("3: erase at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 5 << 3 << 0 << 0 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("4: erase the only column") << IntMatrix{4, 1, {1, 2, 3, 4}} << 0 << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("5: erase at beginning position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 2 << 7 << 0 << 1 << IntMatrix{2, 5, {2, 3, 4, 5, 6, 8, 9, 10, 11, 12}};
    QTest::newRow("6: erase at random position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 2 << 7 << 0 << 1 << IntMatrix{2, 5, {1, 2, 4, 5, 6, 7, 8, 10, 11, 12}};
    QTest::newRow("7: erase at middle position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 7 << 0 << 0 << IntMatrix{2, 5, {1, 2, 3, 5, 6, 7, 8, 9, 11, 12}};
    QTest::newRow("8: erase at random position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << 7 << 0 << 0 << IntMatrix{2, 5, {1, 2, 3, 4, 6, 7, 8, 9, 10, 12}};
    QTest::newRow("9: erase at end position") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << 7 << 0 << 0 << IntMatrix{2, 5, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11}};
    QTest::newRow("10: erase at beginning position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 0 << 2 << 8 << 0 << 1 << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14}};
    QTest::newRow("11: erase at random position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 2 << 2 << 8 << 0 << 1 << IntMatrix{2, 6, {1, 2, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14}};
    QTest::newRow("12: erase at middle position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 3 << 2 << 8 << 0 << 0 << IntMatrix{2, 6, {1, 2, 3, 5, 6, 7, 8, 9, 10, 12, 13, 14}};
    QTest::newRow("13: erase at random position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 4 << 2 << 8 << 0 << 0 << IntMatrix{2, 6, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 13, 14}};
    QTest::newRow("14: erase at end position") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << 6 << 2 << 8 << 0 << 0 << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 8, 9, 10, 11, 12, 13}};
    QTest::newRow("15: erase at beginning position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 0 << 2 << 10 << 0 << 2 << IntMatrix{2, 7, {2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("16: erase at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 3 << 2 << 10 << 0 << 2 << IntMatrix{2, 7, {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16}};
    QTest::newRow("17: erase at middle position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 4 << 2 << 10 << 0 << 1 << IntMatrix{2, 7, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16}};
    QTest::newRow("18: erase at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 2 << 10 << 0 << 1 << IntMatrix{2, 7, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 15, 16}};
    QTest::newRow("19: erase at end position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 7 << 2 << 10 << 0 << 1 << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 9, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("20: erase at beginning position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << 2 << 11 << 0 << 2 << IntMatrix{2, 8, {2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("21: erase at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 3 << 2 << 11 << 0 << 2 << IntMatrix{2, 8, {1, 2, 3, 5, 6, 7, 8, 9, 10, 11, 12, 14, 15, 16, 17, 18}};
    QTest::newRow("22: erase at middle position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 4 << 2 << 11 << 0 << 1 << IntMatrix{2, 8, {1, 2, 3, 4, 6, 7, 8, 9, 10, 11, 12, 13, 15, 16, 17, 18}};
    QTest::newRow("23: erase at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 5 << 2 << 11 << 0 << 1 << IntMatrix{2, 8, {1, 2, 3, 4, 5, 7, 8, 9, 10, 11, 12, 13, 14, 16, 17, 18}};
    QTest::newRow("24: erase at end position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 8 << 2 << 11 << 0 << 1 << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 10, 11, 12, 13, 14, 15, 16, 17}};
    QTest::newRow("25: erase the only column") << IntMatrix{9, 1, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 0 << 0 << 0 << -1 << -1 << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<std::vector<IntMatrixSizeType>>("erasePositions");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("2: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 1, 1} << 3 << 2 << 0 << 0 << IntMatrix{3, 1, {1, 5, 9}};
    QTest::newRow("3: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 2} << 3 << 5 << 0 << 0 << IntMatrix{3, 2, {1, 2, 5, 6, 9, 10}};
    QTest::newRow("4: erase from random positions") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 2, 0, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("5: erase from middle") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 1, 1, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("6: erase from end") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 1, 0} << 0 << 0 << -1 << -1 << IntMatrix{};
    QTest::newRow("7: erase from beginning/end") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{0, 2} << 3 << 5 << 0 << 1 << IntMatrix{3, 2, {2, 3, 6, 7, 10, 11}};
    QTest::newRow("8: erase from end/beginning") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 0} << 3 << 5 << 0 << 1 << IntMatrix{3, 2, {2, 3, 6, 7, 10, 11}};
    QTest::newRow("9: erase from beginning/end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6} << 2 << 10 << 0 << 2 << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("10: erase from end/beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0} << 2 << 10 << 0 << 2 << IntMatrix{2, 6, {2, 3, 4, 5, 6, 7, 10, 11, 12, 13, 14, 15}};
    QTest::newRow("11: erase from beginning/end by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 5, 4, 0} << 2 << 8 << 0 << 2 << IntMatrix{2, 3, {3, 4, 5, 10, 11, 12}};
    QTest::newRow("12: erase from beginning/end by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 5, 4, 0, 0} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {4, 5, 11, 12}};
    QTest::newRow("13: erase from beginning/end by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6, 5, 0, 0} << 2 << 10 << 0 << 4 << IntMatrix{2, 3, {4, 5, 6, 12, 13, 14}};
    QTest::newRow("14: erase from beginning/end by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 6, 5, 0, 0, 2} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {4, 5, 12, 13}};
    QTest::newRow("15: erase from end/beginning by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 0, 0, 3} << 2 << 8 << 0 << 2 << IntMatrix{2, 3, {3, 4, 5, 10, 11, 12}};
    QTest::newRow("16: erase from end/beginning by changing order") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 0, 0, 3, 2} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {3, 4, 10, 11}};
    QTest::newRow("17: erase from end/beginning by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0, 0, 4, 3} << 2 << 10 << 0 << 3 << IntMatrix{2, 3, {3, 4, 5, 11, 12, 13}};
    QTest::newRow("18: erase from end/beginning by changing order") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 0, 0, 4, 3, 0} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {4, 5, 12, 13}};
    QTest::newRow("19: erase from beginning") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0} << 2 << 8 << 0 << 4 << IntMatrix{2, 3, {5, 6, 7, 12, 13, 14}};
    QTest::newRow("20: erase from beginning") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {6, 7, 13, 14}};
    QTest::newRow("21: erase from beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0} << 2 << 10 << 0 << 6 << IntMatrix{2, 3, {6, 7, 8, 14, 15, 16}};
    QTest::newRow("22: erase from beginning") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{0, 0, 0, 0, 0, 0} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {7, 8, 15, 16}};
    QTest::newRow("23: erase from middle") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 2, 1} << 2 << 7 << 0 << 0 << IntMatrix{2, 2, {1, 6, 7, 12}};
    QTest::newRow("24: erase from middle") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{3, 2, 2, 1, 1} << 2 << 2 << 0 << 0 << IntMatrix{2, 1, {1, 7}};
    QTest::newRow("25: erase from middle") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{3, 3, 2, 2} << 2 << 8 << 0 << 0 << IntMatrix{2, 3, {1, 2, 7, 8, 9, 14}};
    QTest::newRow("26: erase from middle") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {1, 7, 8, 14}};
    QTest::newRow("27: erase from middle") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 3, 3, 2, 2} << 2 << 10 << 0 << 1 << IntMatrix{2, 3, {1, 2, 8, 9, 10, 16}};
    QTest::newRow("28: erase from middle") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {1, 8, 9, 16}};
    QTest::newRow("29: erase from middle") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{4, 4, 3, 3, 2, 2} << 2 << 11 << 0 << 1 << IntMatrix{2, 3, {1, 2, 9, 10, 11, 18}};
    QTest::newRow("30: erase from middle") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{4, 4, 3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {1, 9, 10, 18}};
    QTest::newRow("31: erase from end") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 5, 4, 3} << 2 << 8 << 0 << 0 << IntMatrix{2, 3, {1, 2, 3, 8, 9, 10}};
    QTest::newRow("32: erase from end") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{6, 5, 4, 3, 2} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {1, 2, 8, 9}};
    QTest::newRow("33: erase from end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 6, 5, 4, 3} << 2 << 10 << 0 << 1 << IntMatrix{2, 3, {1, 2, 3, 9, 10, 11}};
    QTest::newRow("34: erase from end") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{7, 6, 5, 4, 3, 2} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {1, 2, 9, 10}};
    QTest::newRow("35: erase from random positions") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{1, 1, 2, 0} << 2 << 7 << 0 << 3 << IntMatrix{2, 2, {4, 6, 10, 12}};
    QTest::newRow("36: erase from random positions") << IntMatrix{2, 6, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << std::vector<IntMatrixSizeType>{2, 4, 1, 2, 0} << 2 << 2 << 0 << 0 << IntMatrix{2, 1, {4, 10}};
    QTest::newRow("37: erase from random positions") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{2, 4, 1, 2} << 2 << 8 << 0 << 2 << IntMatrix{2, 3, {1, 4, 7, 8, 11, 14}};
    QTest::newRow("38: erase from random positions") << IntMatrix{2, 7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}} << std::vector<IntMatrixSizeType>{1, 0, 3, 1, 2} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {3, 5, 10, 12}};
    QTest::newRow("39: erase from random positions") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{6, 0, 2, 4, 2} << 2 << 10 << 0 << 3 << IntMatrix{2, 3, {2, 3, 6, 10, 11, 14}};
    QTest::newRow("40: erase from random positions") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << std::vector<IntMatrixSizeType>{4, 0, 5, 1, 1, 1} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {2, 7, 10, 15}};
    QTest::newRow("41: erase from random positions") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{5, 5, 1, 1, 3, 3} << 2 << 11 << 0 << 3 << IntMatrix{2, 3, {1, 4, 5, 10, 13, 14}};
    QTest::newRow("42: erase from random positions") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << std::vector<IntMatrixSizeType>{1, 6, 5, 1, 3, 1, 0} << 2 << 4 << 0 << 1 << IntMatrix{2, 2, {5, 9, 14, 18}};
}

void ResizingTests::testIntMatrixClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("1: non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("2: non-empty matrix") << c_IntMatrix1_8x9;
    QTest::newRow("3: empty matrix") << IntMatrix{};
}

void ResizingTests::testStringMatrixResizeWithDefaultCapacityAndDefaultNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 2 << 4 << 2 << 0 << 0 << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << 2 << 3 << 0 << 0 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 2  << 3 << 2 << 0 << 0 << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 5 << 4 << 5 << 0 << 0 << StringMatrix{4, 5, {"First", "Second", "Third", "", "", "Fourth", "Fifth", "Sixth", "", "", "Seventh", "Eighth", "Ninth", "", "", "Tenth", "Eleventh", "Twelfth", "", ""}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 3 << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 4 << 5 << 4 << 0 << 0 << StringMatrix{5, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", "", "", "", "", ""}};
    QTest::newRow("7: more rows, more columns") << StringMatrix{} << 1 << 1 << 1 << 1 << 0 << 0 << StringMatrix{1, 1, ""};
    QTest::newRow("8: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 3 << 4 << 3 << 0 << 0 << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("9: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 4 << 3 << 4 << 0 << 0 << StringMatrix{3, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", ""}};
    QTest::newRow("10: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 2 << 5 << 2 << 0 << 0 << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "", ""}};
    QTest::newRow("11: equal rows, less columns") << c_StringMatrix1_10x9 << 10 << 7 << 10 << 7 << 0 << 0 << c_StringMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_StringMatrix1_10x9 << 10 << 8 << 10 << 8 << 0 << 0 << c_StringMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_StringMatrix1_10x9 << 7 << 9  << 7 << 9 << 0 << 0 << c_StringMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_StringMatrix1_10x9 << 8 << 9  << 8 << 9 << 0 << 0 << c_StringMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_StringMatrix1_10x9 << 7 << 7 << 7 << 7 << 0 << 0 << c_StringMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_StringMatrix1_10x9 << 8 << 8 << 8 << 8 << 0 << 0 << c_StringMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_StringMatrix1_10x9 << 10 << 11 << 10 << 11 << 0 << 0 << c_StringMatrix1_10x11;
    QTest::newRow("18: more rows, equal columns") << c_StringMatrix1_10x9 << 12 << 9 << 12 << 9 << 0 << 0 << c_StringMatrix1_12x9;
    QTest::newRow("19: more rows, more columns") << c_StringMatrix1_10x9 << 12 << 11 << 12 << 11 << 0 << 0 << c_StringMatrix1_12x11;
    QTest::newRow("20: more rows, more columns") << StringMatrix{} << 12 << 11 << 12 << 11 << 0 << 0 << StringMatrix{12, 11, ""};
    QTest::newRow("21: equal rows, equal columns") << c_StringMatrix1_10x9 << 10 << 9 << 10 << 9 << 0 << 0 << c_StringMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_StringMatrix1_10x9 << 7 << 11 << 7 << 11 << 0 << 0 << c_StringMatrix1_7x11;
    QTest::newRow("23: less rows, more columns") << c_StringMatrix1_10x9 << 8 << 11 << 8 << 11 << 0 << 0 << c_StringMatrix1_8x11;
    QTest::newRow("24: more rows, less columns") << c_StringMatrix1_10x9 << 12 << 7 << 12 << 7 << 0 << 0 << c_StringMatrix1_12x7;
    QTest::newRow("25: more rows, less columns") << c_StringMatrix1_10x9 << 12 << 8 << 12 << 8 << 0 << 0 << c_StringMatrix1_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 5 << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", ""}};
    QTest::newRow("27: more rows, more columns") << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "13th", "14th", "15th", "16th"}} << 5 << 5 << 5 << 5 << 0 << 0 << StringMatrix{5, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "13th", "14th", "15th", "16th", "", "", "", "", "", ""}};
    QTest::newRow("28: equal rows, equal columns") << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}} << 3 << 3 << 3 << 3 << 0 << 0 << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
}

void ResizingTests::testStringMatrixResizeWithDefaultCapacityAndSetNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("fillValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 2 << std::string{"/NEW_VALUE/"} << 4 << 2 << 0 << 0 << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << std::string{"/NEW_VALUE/"} << 2 << 3 << 0 << 0 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 2 << std::string{"/NEW_VALUE/"} << 3 << 2 << 0 << 0 << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 5 << std::string{"/NEW_VALUE/"} << 4 << 5 << 0 << 0 << StringMatrix{4, 5, {"First", "Second", "Third", "/NEW_VALUE/", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 3 << std::string{"/NEW_VALUE/"} << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}}; // capacity stays unchanged
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 4 << std::string{"/NEW_VALUE/"} << 5 << 4 << 0 << 0 << StringMatrix{5, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("7: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"/NEW_VALUE/"} << 1 << 1 << 0 << 0 << StringMatrix{1, 1, "/NEW_VALUE/"};
    QTest::newRow("8: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 3 << std::string{"/NEW_VALUE/"} << 4 << 3 << 0 << 0 << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("9: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 4 << std::string{"/NEW_VALUE/"} << 3 << 4 << 0 << 0 << StringMatrix{3, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/"}};
    QTest::newRow("10: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 2 << std::string{"/NEW_VALUE/"} << 5 << 2 << 0 << 0 << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("11: equal rows, less columns") << c_StringMatrix1_10x9 << 10 << 7 << std::string{"5Z"} << 10 << 7 << 0 << 0 << c_StringMatrix1_10x7;
    QTest::newRow("12: equal rows, less columns") << c_StringMatrix1_10x9 << 10 << 8 << std::string{"5Z"} << 10 << 8 << 0 << 0 << c_StringMatrix1_10x8;
    QTest::newRow("13: less rows, equal columns") << c_StringMatrix1_10x9 << 7 << 9 << std::string{"5Z"} << 7 << 9 << 0 << 0 << c_StringMatrix1_7x9;
    QTest::newRow("14: less rows, equal columns") << c_StringMatrix1_10x9 << 8 << 9 << std::string{"5Z"} << 8 << 9 << 0 << 0 << c_StringMatrix1_8x9;
    QTest::newRow("15: less rows, less columns") << c_StringMatrix1_10x9 << 7 << 7 << std::string{"5Z"} << 7 << 7 << 0 << 0 << c_StringMatrix1_7x7;
    QTest::newRow("16: less rows, less columns") << c_StringMatrix1_10x9 << 8 << 8 << std::string{"5Z"} << 8 << 8 << 0 << 0 << c_StringMatrix1_8x8;
    QTest::newRow("17: equal rows, more columns") << c_StringMatrix1_10x9 << 10 << 11 << std::string{"5Z"} << 10 << 11 << 0 << 0 << c_StringMatrix2_10x11;
    QTest::newRow("18: more rows, equal columns") << c_StringMatrix1_10x9 << 12 << 9 << std::string{"5Z"} << 12 << 9 << 0 << 0 << c_StringMatrix2_12x9;
    QTest::newRow("19: more rows, more columns") << c_StringMatrix1_10x9 << 12 << 11 << std::string{"5Z"} << 12 << 11 << 0 << 0 << c_StringMatrix2_12x11;
    QTest::newRow("20: more rows, more columns") << StringMatrix{} << 12 << 11 << std::string{"5Z"} << 12 << 11 << 0 << 0 << StringMatrix{12, 11, "5Z"};
    QTest::newRow("21: equal rows, equal columns") << c_StringMatrix1_10x9 << 10 << 9 << std::string{"5Z"} << 10 << 9 << 0 << 0 << c_StringMatrix1_10x9;
    QTest::newRow("22: less rows, more columns") << c_StringMatrix1_10x9 << 7 << 11 << std::string{"5Z"} << 7 << 11 << 0 << 0 << c_StringMatrix2_7x11;
    QTest::newRow("23: less rows, more columns") << c_StringMatrix1_10x9 << 8 << 11 << std::string{"5Z"} << 8 << 11 << 0 << 0 << c_StringMatrix2_8x11;
    QTest::newRow("24: more rows, less columns") << c_StringMatrix1_10x9 << 12 << 7 << std::string{"5Z"} << 12 << 7 << 0 << 0 << c_StringMatrix2_12x7;
    QTest::newRow("25: more rows, less columns") << c_StringMatrix1_10x9 << 12 << 8 << std::string{"5Z"} << 12 << 8 << 0 << 0 << c_StringMatrix2_12x8;

    // additional tests for unchanged capacity
    QTest::newRow("26: equal rows, more columns") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 5 << std::string{"/NEW_VALUE/"} << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};
    QTest::newRow("27: more rows, more columns") << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "13th", "14th", "15th", "16th"}} << 5 << 5 << std::string{"/NEW_VALUE/"} << 5 << 5 << 0 << 0 << StringMatrix{5, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "13th", "14th", "15th", "16th", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("28: equal rows, equal columns") << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}} << 3 << 3 << std::string{"/NEW_VALUE/"} << 3 << 3 << 0 << 0 << StringMatrix{3, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
}

void ResizingTests::testStringMatrixResizeWithFixedCapacityAndDefaultNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 2 << 10 << 8 << 3 << 3 << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << 10 << 8 << 4 << 2 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 2  << 11 << 10 << 4 << 4 << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 5 << 11 << 10 << 3 << 2 << StringMatrix{4, 5, {"First", "Second", "Third", "", "", "Fourth", "Fifth", "Sixth", "", "", "Seventh", "Eighth", "Ninth", "", "", "Tenth", "Eleventh", "Twelfth", "", ""}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 3 << 10 << 8 << 2 << 2 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}};
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 4 << 10 << 9 << 2 << 2 << StringMatrix{5, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", "", "", "", "", ""}};
    QTest::newRow("7: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 3 << 10 << 9 << 3 << 3 << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("8: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 4 << 11 << 9 << 4 << 2 << StringMatrix{3, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", ""}};
    QTest::newRow("9: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 2 << 10 << 8 << 2 << 3 << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "", ""}};
}

void ResizingTests::testStringMatrixResizeWithFixedCapacityAndSetNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("fillValue");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 2 << std::string{"/NEW_VALUE/"} << 10 << 8 << 3 << 3 << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << std::string{"/NEW_VALUE/"} << 10 << 8 << 4 << 2 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("3: less rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 2 << std::string{"/NEW_VALUE/"} << 11 << 10 << 4 << 4 << StringMatrix{3, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth"}};
    QTest::newRow("4: equal rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 5 << std::string{"/NEW_VALUE/"} << 11 << 10 << 3 << 2 << StringMatrix{4, 5, {"First", "Second", "Third", "/NEW_VALUE/", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("5: more rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 3 << std::string{"/NEW_VALUE/"} << 10 << 8 << 2 << 2 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("6: more rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 4 << std::string{"/NEW_VALUE/"} << 10 << 9 << 2 << 2 << StringMatrix{5, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};
    QTest::newRow("7: equal rows, equal columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 3 << std::string{"/NEW_VALUE/"} << 10 << 9 << 3 << 3 << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("8: less rows, more columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 4 << std::string{"/NEW_VALUE/"} << 11 << 9 << 4 << 2 << StringMatrix{3, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/"}};
    QTest::newRow("9: more rows, less columns") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 5 << 2 << std::string{"/NEW_VALUE/"} << 10 << 8 << 2 << 3 << StringMatrix{5, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh", "/NEW_VALUE/", "/NEW_VALUE/"}};
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
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 5 << 3 << 0 << 0 <<StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "", "", "", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"", "", "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "", "", "", "", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"", "", "", "", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "", "", "", ""}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"", "", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 2 << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "", "", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "", "15th", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 8 << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "", ""}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"", "", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 2 << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "", "", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 7 << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "", "15th", "16th", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 9 << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "", ""}};
}

void ResizingTests::testStringMatrixInsertRowSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << std::string{"/NEW_VALUE/"} << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << std::string{"/NEW_VALUE/"} << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << std::string{"/NEW_VALUE/"} << 5 << 3 << 0 << 0 << StringMatrix{5, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << std::string{"/NEW_VALUE/"} << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << std::string{"/NEW_VALUE/"} << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << std::string{"/NEW_VALUE/"} << 6 << 5 << 1 << 0 << StringMatrix{4, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/", "/NEW_VALUE/"}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << std::string{"/New/"} << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"/New/", "/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 2 << std::string{"/New/"} << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "/New/", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << std::string{"/New/"} << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "/New/", "/New/", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << std::string{"/New/"} << 10 << 2 << 0 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << std::string{"/New/"} << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "/New/", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << std::string{"/New/"} << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "/New/", "15th", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 8 << std::string{"/New/"} << 10 << 2 << 1 << 0 << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/", "/New/"}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << std::string{"/New/"} << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"/New/", "/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 2 << std::string{"/New/"} << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "/New/", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << std::string{"/New/"} << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "/New/", "/New/", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << std::string{"/New/"} << 11 << 2 << 0 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << std::string{"/New/"} << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "/New/", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 7 << std::string{"/New/"} << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "/New/", "15th", "16th", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 9 << std::string{"/New/"} << 11 << 2 << 1 << 0 << StringMatrix{10, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "/New/", "/New/"}};
}

void ResizingTests::testStringMatrixInsertColumnNoSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "", "Third", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "Tenth", "", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"", "First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "Eighth", "", "Ninth", "Tenth", "Eleventh", "Twelfth", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"First", "", "Second", "Third", "Fourth", "", "Fifth", "Sixth", "Seventh", "", "Eighth", "Ninth", "Tenth", "", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"", "First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"First", "Second", "Third", "", "Fourth", "Fifth", "Sixth", "", "Seventh", "Eighth", "Ninth", "", "Tenth", "Eleventh", "Twelfth", ""}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 2 << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 8 << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", ""}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 2 << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 7 << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 9 << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", ""}};
}

void ResizingTests::testStringMatrixInsertColumnSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << std::string{"/NEW_VALUE/"} << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "/NEW_VALUE/", "Third", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "Tenth", "/NEW_VALUE/", "Eleventh", "Twelfth"}};
    QTest::newRow("2: insert at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << std::string{"/NEW_VALUE/"} << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"/NEW_VALUE/", "First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: insert at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 4 << std::string{"/NEW_VALUE/"} << 3 << 5 << 0 << 0 << StringMatrix{3, 5, {"First", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "Eighth", "/NEW_VALUE/", "Ninth", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << std::string{"/NEW_VALUE/"} << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"First", "/NEW_VALUE/", "Second", "Third", "Fourth", "/NEW_VALUE/", "Fifth", "Sixth", "Seventh", "/NEW_VALUE/", "Eighth", "Ninth", "Tenth", "/NEW_VALUE/", "Eleventh", "Twelfth"}};
    QTest::newRow("5: insert at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << std::string{"/NEW_VALUE/"} << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"/NEW_VALUE/", "First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("6: insert at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 3 << std::string{"/NEW_VALUE/"} << 5 << 6 << 0 << 1 << StringMatrix{4, 4, {"First", "Second", "Third", "/NEW_VALUE/", "Fourth", "Fifth", "Sixth", "/NEW_VALUE/", "Seventh", "Eighth", "Ninth", "/NEW_VALUE/", "Tenth", "Eleventh", "Twelfth", "/NEW_VALUE/"}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << std::string{"/New/"} << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("8: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 2 << std::string{"/New/"} << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "/New/", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "/New/", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("9: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << std::string{"/New/"} << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "/New/", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "/New/", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("10: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << std::string{"/New/"} << 2 << 10 << 0 << 0 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "/New/", "13th", "14th", "15th", "16th"}};
    QTest::newRow("11: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << std::string{"/New/"} << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "/New/", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "/New/", "14th", "15th", "16th"}};
    QTest::newRow("12: insert at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << std::string{"/New/"} << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "/New/", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "/New/", "16th"}};
    QTest::newRow("13: insert at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 8 << std::string{"/New/"} << 2 << 10 << 0 << 1 << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "/New/", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/"}};
    QTest::newRow("14: insert at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << std::string{"/New/"} << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"/New/", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "/New/", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("15: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 2 << std::string{"/New/"} << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "/New/", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "/New/", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("16: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << std::string{"/New/"} << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "/New/", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "/New/", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("17: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << std::string{"/New/"} << 2 << 11 << 0 << 0 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "/New/", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "/New/", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("18: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << std::string{"/New/"} << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "/New/", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "/New/", "15th", "16th", "17th", "18th"}};
    QTest::newRow("19: insert at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 7 << std::string{"/New/"} << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "/New/", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "/New/", "17th", "18th"}};
    QTest::newRow("20: insert at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 9 << std::string{"/New/"} << 2 << 11 << 0 << 1 << StringMatrix{2, 10, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "/New/", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th", "/New/"}};
}

void ResizingTests::testStringMatrixInsertMultipleRowsSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<StringMatrixSizeType>>("insertPositions");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{0, 0} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3a_12x9;
    QTest::newRow("2: append both") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{10, 11} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix2_12x9;
    QTest::newRow("3: prepend, then append") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{0, 11} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3b_12x9;
    QTest::newRow("4: append, then prepend") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{10, 0} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3b_12x9;
    QTest::newRow("5: insert in the first half, then in the second") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{2, 9} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3c_12x9;
    QTest::newRow("6: insert in the second half, then in the first") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{8, 2} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3c_12x9;
    QTest::newRow("7: insert both in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{5, 5} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3d_12x9;
    QTest::newRow("8: insert both in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{4, 5} << std::string{"5Z"} << 11 << 12 << 0 << 1 << c_StringMatrix3a_11x10;
    QTest::newRow("9: prepend, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{0, 5} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3e_12x9;
    QTest::newRow("10: insert in the middle, then prepend") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{5, 0} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3f_12x9;
    QTest::newRow("11: prepend, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{0, 5} << std::string{"5Z"} << 11 << 12 << 0 << 1 << c_StringMatrix3b_11x10;
    QTest::newRow("12: insert in the middle, then prepend") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{4, 0} << std::string{"5Z"} << 11 << 12 << 0 << 1 << c_StringMatrix3b_11x10;
    QTest::newRow("13: insert in the middle, then append") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{5, 11} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3g_12x9;
    QTest::newRow("14: append, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{10, 5} << std::string{"5Z"} << 12 << 11 << 0 << 1 << c_StringMatrix3g_12x9;
    QTest::newRow("15: insert in the middle, then append") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{4, 10} << std::string{"5Z"} << 11 << 12 << 0 << 1 << c_StringMatrix3c_11x10;
    QTest::newRow("16: append, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{9, 5} << std::string{"5Z"} << 11 << 12 << 0 << 1 << c_StringMatrix3d_11x10;
}

void ResizingTests::testStringMatrixInsertMultipleColumnsSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<StringMatrixSizeType>>("insertPositions");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("1: prepend both") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{0, 0} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3a_9x12;
    QTest::newRow("2: append both") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{10, 11} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3b_9x12;
    QTest::newRow("3: prepend, then append") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{0, 11} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3c_9x12;
    QTest::newRow("4: append, then prepend") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{10, 0} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3c_9x12;
    QTest::newRow("5: insert in the first half, then in the second") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{2, 9} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3d_9x12;
    QTest::newRow("6: insert in the second half, then in the first") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{8, 2} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3d_9x12;
    QTest::newRow("7: insert both in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{5, 5} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3e_9x12;
    QTest::newRow("8: insert both in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{4, 5} << std::string{"5Z"} << 12 << 11 << 1 << 0 << c_StringMatrix3a_10x11;
    QTest::newRow("9: prepend, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{0, 5} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3f_9x12;
    QTest::newRow("10: insert in the middle, then prepend") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{5, 0} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3g_9x12;
    QTest::newRow("11: prepend, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{0, 5} << std::string{"5Z"} << 12 << 11 << 1 << 0 << c_StringMatrix3b_10x11;
    QTest::newRow("12: insert in the middle, then prepend") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{4, 0} << std::string{"5Z"} << 12 << 11 << 1 << 0 << c_StringMatrix3b_10x11;
    QTest::newRow("13: insert in the middle, then append") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{5, 11} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3h_9x12;
    QTest::newRow("14: append, then insert in the middle") << c_StringMatrix3_9x10 << std::vector<StringMatrixSizeType>{10, 5} << std::string{"5Z"} << 11 << 12 << 1 << 0 << c_StringMatrix3h_9x12;
    QTest::newRow("15: insert in the middle, then append") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{4, 10} << std::string{"5Z"} << 12 << 11 << 1 << 0 << c_StringMatrix3c_10x11;
    QTest::newRow("16: append, then insert in the middle") << c_StringMatrix1_10x9 << std::vector<StringMatrixSizeType>{9, 5} << std::string{"5Z"} << 12 << 11 << 1 << 0 << c_StringMatrix3d_10x11;
}

void ResizingTests::testStringMatrixEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 3 << 5 << 1 << 0 << StringMatrix{2, 4, {"Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: erase at middle position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 3 << 5 << 0 << 0 << StringMatrix{2, 4, {"First", "Second", "Third", "Fourth", "Ninth", "Tenth", "Eleventh", "Twelfth"}};
    QTest::newRow("3: erase at end position") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 3 << 5 << 0 << 0 << StringMatrix{2, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth"}};
    QTest::newRow("4: erase the only row") << StringMatrix{1, 4, {"First", "Second", "Third", "Fourth"}} << 0 << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("5: erase at beginning position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 0 << 7 << 2 << 1 << 0 << StringMatrix{5, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("6: erase at random position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 2 << 7 << 2 << 1 << 0 << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("7: erase at middle position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 3 << 7 << 2 << 0 << 0 << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("8: erase at random position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 4 << 7 << 2 << 0 << 0 << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th"}};
    QTest::newRow("9: erase at end position") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 5 << 7 << 2 << 0 << 0 << StringMatrix{5, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("10: erase at beginning position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 0 << 8 << 2 << 1 << 0 << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase at random position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 2 << 8 << 2 << 1 << 0 << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("12: erase at middle position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 3 << 8 << 2 << 0 << 0 << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("13: erase at random position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 4 << 8 << 2 << 0 << 0 << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("14: erase at end position") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 6 << 8 << 2 << 0 << 0 << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("15: erase at beginning position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << 10 << 2 << 2 << 0 << StringMatrix{7, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("16: erase at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << 10 << 2 << 2 << 0 << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("17: erase at middle position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << 10 << 2 << 1 << 0 << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("18: erase at random position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << 10 << 2 << 1 << 0 << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("19: erase at end position") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << 10 << 2 << 1 << 0 << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase at beginning position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << 11 << 2 << 2 << 0 << StringMatrix{8, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("21: erase at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << 11 << 2 << 2 << 0 << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("22: erase at middle position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << 11 << 2 << 1 << 0 << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("23: erase at random position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << 11 << 2 << 1 << 0 << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("24: erase at end position") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 8 << 11 << 2 << 1 << 0 << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("25: erase the only row") << StringMatrix{1, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th"}} << 0 << 0 << 0 << -1 << -1 << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleRows_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<StringMatrixSizeType>>("erasePositions");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("2: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{1, 1, 1} << 2 << 3 << 0 << 0 << StringMatrix{1, 3, {"First", "Second", "Third"}};
    QTest::newRow("3: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{2, 2} << 5 << 3 << 0 << 0 << StringMatrix{2, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth"}};
    QTest::newRow("4: erase from random positions") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{1, 2, 0, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("5: erase from middle") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{2, 1, 1, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("6: erase from end") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{3, 2, 1, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("7: erase from beginning/end") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{0, 2} << 5 << 3 << 1 << 0 << StringMatrix{2, 3, {"Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
    QTest::newRow("8: erase from end/beginning") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{3, 0} << 5 << 3 << 1 << 0 << StringMatrix{2, 3, {"Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth"}};
    QTest::newRow("9: erase from beginning/end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6} << 10 << 2 << 2 << 0 << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("10: erase from end/beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0} << 10 << 2 << 2 << 0 << StringMatrix{6, 2, {"3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase from beginning/end by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 5, 4, 0} << 8 << 2 << 2 << 0 << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("12: erase from beginning/end by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 5, 4, 0, 0} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("13: erase from beginning/end by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6, 5, 0, 0} << 10 << 2 << 4 << 0 << StringMatrix{3, 2, {"7th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("14: erase from beginning/end by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6, 5, 0, 0, 2} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("15: erase from end/beginning by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 0, 0, 3} << 8 << 2 << 2 << 0 << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("16: erase from end/beginning by changing order") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 0, 0, 3, 2} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"5th", "6th", "7th", "8th"}};
    QTest::newRow("17: erase from end/beginning by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0, 0, 4, 3} << 10 << 2 << 3 << 0 << StringMatrix{3, 2, {"5th", "6th", "7th", "8th", "9th", "10th"}};
    QTest::newRow("18: erase from end/beginning by changing order") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0, 0, 4, 3, 0} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"7th", "8th", "9th", "10th"}};
    QTest::newRow("19: erase from beginning") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0} << 8 << 2 << 4 << 0 << StringMatrix{3, 2, {"9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase from beginning") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"11th", "12th", "13th", "14th"}};
    QTest::newRow("21: erase from beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0} << 10 << 2 << 6 << 0 << StringMatrix{3, 2, {"11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("22: erase from beginning") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0, 0} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"13th", "14th", "15th", "16th"}};
    QTest::newRow("23: erase from middle") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{3, 2, 2, 1} << 7 << 2 << 0 << 0 <<StringMatrix{2, 2, {"1st", "2nd", "11th", "12th"}};
    QTest::newRow("24: erase from middle") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{3, 2, 2, 1, 1} << 2 << 2 << 0 << 0 << StringMatrix{1, 2, {"1st", "2nd"}};
    QTest::newRow("25: erase from middle") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{3, 3, 2, 2} << 8 << 2 << 0 << 0 << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "13th", "14th"}};
    QTest::newRow("26: erase from middle") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 <<StringMatrix{2, 2, {"1st", "2nd", "13th", "14th"}};
    QTest::newRow("27: erase from middle") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 3, 3, 2, 2} << 10 << 2 << 1 << 0 << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "15th", "16th"}};
    QTest::newRow("28: erase from middle") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"1st", "2nd", "15th", "16th"}};
    QTest::newRow("29: erase from middle") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{4, 4, 3, 3, 2, 2} << 11 << 2 << 1 << 0 << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "17th", "18th"}};
    QTest::newRow("30: erase from middle") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{4, 4, 3, 3, 2, 2, 1} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"1st", "2nd", "17th", "18th"}};
    QTest::newRow("31: erase from end") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 5, 4, 3} << 8 << 2 << 0 << 0 << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th"}};
    QTest::newRow("32: erase from end") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 5, 4, 3, 2} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"1st", "2nd", "3rd", "4th"}};
    QTest::newRow("33: erase from end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 6, 5, 4, 3} << 10 << 2 << 1 << 0 << StringMatrix{3, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th"}};
    QTest::newRow("34: erase from end") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 6, 5, 4, 3, 2} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"1st", "2nd", "3rd", "4th"}};
    QTest::newRow("35: erase from random positions") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{1, 1, 2, 0} << 7 << 2 << 3 << 0 << StringMatrix{2, 2, {"7th", "8th", "11th", "12th"}};
    QTest::newRow("36: erase from random positions") << StringMatrix{6, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{2, 4, 1, 2, 0} << 2 << 2 << 0 << 0 << StringMatrix{1, 2, {"7th", "8th"}};
    QTest::newRow("37: erase from random positions") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{2, 4, 1, 2} << 8 << 2 << 2 << 0 << StringMatrix{3, 2, {"1st", "2nd", "7th", "8th", "13th", "14th"}};
    QTest::newRow("38: erase from random positions") << StringMatrix{7, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{1, 0, 3, 1, 2} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"5th", "6th", "9th", "10th"}};
    QTest::newRow("39: erase from random positions") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{6, 0, 2, 4, 2} << 10 << 2 << 3 << 0 << StringMatrix{3, 2, {"3rd", "4th", "5th", "6th", "11th", "12th"}};
    QTest::newRow("40: erase from random positions") << StringMatrix{8, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 0, 5, 1, 1, 1} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"3rd", "4th", "13th", "14th"}};
    QTest::newRow("41: erase from random positions") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{5, 5, 1, 1, 3, 3} << 11 << 2 << 3 << 0 << StringMatrix{3, 2, {"1st", "2nd", "7th", "8th", "9th", "10th"}};
    QTest::newRow("42: erase from random positions") << StringMatrix{9, 2, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{1, 6, 5, 1, 3, 1, 0} << 4 << 2 << 1 << 0 << StringMatrix{2, 2, {"9th", "10th", "17th", "18th"}};
}

void ResizingTests::testStringMatrixEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase at beginning position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 0 << 5 << 3 << 0 << 1 << StringMatrix{4, 2, {"Second", "Third", "Fifth", "Sixth", "Eighth", "Ninth", "Eleventh", "Twelfth"}};
    QTest::newRow("2: erase at middle position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 1 << 5 << 3 << 0 << 0 << StringMatrix{4, 2, {"First", "Third", "Fourth", "Sixth", "Seventh", "Ninth", "Tenth", "Twelfth"}};
    QTest::newRow("3: erase at end position") << StringMatrix{4, 3, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << 2 << 5 << 3 << 0 << 0 << StringMatrix{4, 2, {"First", "Second", "Fourth", "Fifth", "Seventh", "Eighth", "Tenth", "Eleventh"}};
    QTest::newRow("4: erase the only column") << StringMatrix{4, 1, {"First", "Second", "Third", "Fourth"}} << 0 << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("5: erase at beginning position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 0 << 2 << 7 << 0 << 1 << StringMatrix{2, 5, {"2nd", "3rd", "4th", "5th", "6th", "8th", "9th", "10th", "11th", "12th"}};
    QTest::newRow("6: erase at random position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 2 << 2 << 7 << 0 << 1 << StringMatrix{2, 5, {"1st", "2nd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th"}};
    QTest::newRow("7: erase at middle position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 3 << 2 << 7 << 0 << 0 << StringMatrix{2, 5, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "11th", "12th"}};
    QTest::newRow("8: erase at random position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 4 << 2 << 7 << 0 << 0 << StringMatrix{2, 5, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "12th"}};
    QTest::newRow("9: erase at end position") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << 5 << 2 << 7 << 0 << 0 << StringMatrix{2, 5, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th"}};
    QTest::newRow("10: erase at beginning position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 0 << 2 << 8 << 0 << 1 << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "9th", "10th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("11: erase at random position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 2 << 2 << 8 << 0 << 1 << StringMatrix{2, 6, {"1st", "2nd", "4th", "5th", "6th", "7th", "8th", "9th", "11th", "12th", "13th", "14th"}};
    QTest::newRow("12: erase at middle position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 3 << 2 << 8 << 0 << 0 << StringMatrix{2, 6, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "12th", "13th", "14th"}};
    QTest::newRow("13: erase at random position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 4 << 2 << 8 << 0 << 0 << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "13th", "14th"}};
    QTest::newRow("14: erase at end position") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << 6 << 2 << 8 << 0 << 0 << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "8th", "9th", "10th", "11th", "12th", "13th"}};
    QTest::newRow("15: erase at beginning position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 0 << 2 << 10 << 0 << 2 << StringMatrix{2, 7, {"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("16: erase at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 3 << 2 << 10 << 0 << 2 << StringMatrix{2, 7, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "13th", "14th", "15th", "16th"}};
    QTest::newRow("17: erase at middle position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 4 << 2 << 10 << 0 << 1 << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "14th", "15th", "16th"}};
    QTest::newRow("18: erase at random position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 5 << 2 << 10 << 0 << 1 << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "15th", "16th"}};
    QTest::newRow("19: erase at end position") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << 7 << 2 << 10 << 0 << 1 << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "9th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("20: erase at beginning position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 0 << 2 << 11 << 0 << 2 << StringMatrix{2, 8, {"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("21: erase at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 3 << 2 << 11 << 0 << 2 << StringMatrix{2, 8, {"1st", "2nd", "3rd", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "14th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("22: erase at middle position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 4 << 2 << 11 << 0 << 1 << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "15th", "16th", "17th", "18th"}};
    QTest::newRow("23: erase at random position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 5 << 2 << 11 << 0 << 1 << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "16th", "17th", "18th"}};
    QTest::newRow("24: erase at end position") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << 8 << 2 << 11 << 0 << 1 << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th"}};
    QTest::newRow("25: erase the only column") << StringMatrix{9, 1, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th"}} << 0 << 0 << 0 << -1 << -1 << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<std::vector<StringMatrixSizeType>>("erasePositions");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("1: erase from beginning") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("2: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{1, 1, 1} << 3 << 2 << 0 << 0 << StringMatrix{3, 1, {"First", "Fifth", "Ninth"}};
    QTest::newRow("3: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{2, 2} << 3 << 5 << 0 << 0 << StringMatrix{3, 2, {"First", "Second", "Fifth", "Sixth", "Ninth", "Tenth"}};
    QTest::newRow("4: erase from random positions") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{1, 2, 0, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("5: erase from middle") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{2, 1, 1, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("6: erase from end") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{3, 2, 1, 0} << 0 << 0 << -1 << -1 << StringMatrix{};
    QTest::newRow("7: erase from beginning/end") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{0, 2} << 3 << 5 << 0 << 1 << StringMatrix{3, 2, {"Second", "Third", "Sixth", "Seventh", "Tenth", "Eleventh"}};
    QTest::newRow("8: erase from end/beginning") << StringMatrix{3, 4, {"First", "Second", "Third", "Fourth", "Fifth", "Sixth", "Seventh", "Eighth", "Ninth", "Tenth", "Eleventh", "Twelfth"}} << std::vector<StringMatrixSizeType>{3, 0} << 3 << 5 << 0 << 1 << StringMatrix{3, 2, {"Second", "Third", "Sixth", "Seventh", "Tenth", "Eleventh"}};
    QTest::newRow("9: erase from beginning/end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6} << 2 << 10 << 0 << 2 << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("10: erase from end/beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0} << 2 << 10 << 0 << 2 << StringMatrix{2, 6, {"2nd", "3rd", "4th", "5th", "6th", "7th", "10th", "11th", "12th", "13th", "14th", "15th"}};
    QTest::newRow("11: erase from beginning/end by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 5, 4, 0} << 2 << 8 << 0 << 2 << StringMatrix{2, 3, {"3rd", "4th", "5th", "10th", "11th", "12th"}};
    QTest::newRow("12: erase from beginning/end by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 5, 4, 0, 0} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"4th", "5th", "11th", "12th"}};
    QTest::newRow("13: erase from beginning/end by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6, 5, 0, 0} << 2 << 10 << 0 << 4 << StringMatrix{2, 3, {"4th", "5th", "6th", "12th", "13th", "14th"}};
    QTest::newRow("14: erase from beginning/end by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 6, 5, 0, 0, 2} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"4th", "5th", "12th", "13th"}};
    QTest::newRow("15: erase from end/beginning by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 0, 0, 3} << 2 << 8 << 0 << 2 << StringMatrix{2, 3, {"3rd", "4th", "5th", "10th", "11th", "12th"}};
    QTest::newRow("16: erase from end/beginning by changing order") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 0, 0, 3, 2} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"3rd", "4th", "10th", "11th"}};
    QTest::newRow("17: erase from end/beginning by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0, 0, 4, 3} << 2 << 10 << 0 << 3 << StringMatrix{2, 3, {"3rd", "4th", "5th", "11th", "12th", "13th"}};
    QTest::newRow("18: erase from end/beginning by changing order") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 0, 0, 4, 3, 0} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"4th", "5th", "12th", "13th"}};
    QTest::newRow("19: erase from beginning") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0} << 2 << 8 << 0 << 4 << StringMatrix{2, 3, {"5th", "6th", "7th", "12th", "13th", "14th"}};
    QTest::newRow("20: erase from beginning") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"6th", "7th", "13th", "14th"}};
    QTest::newRow("21: erase from beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0} << 2 << 10 << 0 << 6 << StringMatrix{2, 3, {"6th", "7th", "8th", "14th", "15th", "16th"}};
    QTest::newRow("22: erase from beginning") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{0, 0, 0, 0, 0, 0} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"7th", "8th", "15th", "16th"}};
    QTest::newRow("23: erase from middle") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{3, 2, 2, 1} << 2 << 7 << 0 << 0 << StringMatrix{2, 2, {"1st", "6th", "7th", "12th"}};
    QTest::newRow("24: erase from middle") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{3, 2, 2, 1, 1} << 2 << 2 << 0 << 0 << StringMatrix{2, 1, {"1st", "7th"}};
    QTest::newRow("25: erase from middle") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{3, 3, 2, 2} << 2 << 8 << 0 << 0 << StringMatrix{2, 3, {"1st", "2nd", "7th", "8th", "9th", "14th"}};
    QTest::newRow("26: erase from middle") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"1st", "7th", "8th", "14th"}};
    QTest::newRow("27: erase from middle") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 3, 3, 2, 2} << 2 << 10 << 0 << 1 << StringMatrix{2, 3, {"1st", "2nd", "8th", "9th", "10th", "16th"}};
    QTest::newRow("28: erase from middle") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"1st", "8th", "9th", "16th"}};
    QTest::newRow("29: erase from middle") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{4, 4, 3, 3, 2, 2} << 2 << 11 << 0 << 1 << StringMatrix{2, 3, {"1st", "2nd", "9th", "10th", "11th", "18th"}};
    QTest::newRow("30: erase from middle") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{4, 4, 3, 3, 2, 2, 1} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"1st", "9th", "10th", "18th"}};
    QTest::newRow("31: erase from end") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 5, 4, 3} << 2 << 8 << 0 << 0 << StringMatrix{2, 3, {"1st", "2nd", "3rd", "8th", "9th", "10th"}};
    QTest::newRow("32: erase from end") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{6, 5, 4, 3, 2} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"1st", "2nd", "8th", "9th"}};
    QTest::newRow("33: erase from end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 6, 5, 4, 3} << 2 << 10 << 0 << 1 << StringMatrix{2, 3, {"1st", "2nd", "3rd", "9th", "10th", "11th"}};
    QTest::newRow("34: erase from end") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{7, 6, 5, 4, 3, 2} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"1st", "2nd", "9th", "10th"}};
    QTest::newRow("35: erase from random positions") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{1, 1, 2, 0} << 2 << 7 << 0 << 3 << StringMatrix{2, 2, {"4th", "6th", "10th", "12th"}};
    QTest::newRow("36: erase from random positions") << StringMatrix{2, 6, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th"}} << std::vector<StringMatrixSizeType>{2, 4, 1, 2, 0} << 2 << 2 << 0 << 0 << StringMatrix{2, 1, {"4th", "10th"}};
    QTest::newRow("37: erase from random positions") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{2, 4, 1, 2} << 2 << 8 << 0 << 2 << StringMatrix{2, 3, {"1st", "4th", "7th", "8th", "11th", "14th"}};
    QTest::newRow("38: erase from random positions") << StringMatrix{2, 7, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th"}} << std::vector<StringMatrixSizeType>{1, 0, 3, 1, 2} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"3rd", "5th", "10th", "12th"}};
    QTest::newRow("39: erase from random positions") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{6, 0, 2, 4, 2} << 2 << 10 << 0 << 3 << StringMatrix{2, 3, {"2nd", "3rd", "6th", "10th", "11th", "14th"}};
    QTest::newRow("40: erase from random positions") << StringMatrix{2, 8, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th"}} << std::vector<StringMatrixSizeType>{4, 0, 5, 1, 1, 1} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"2nd", "7th", "10th", "15th"}};
    QTest::newRow("41: erase from random positions") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{5, 5, 1, 1, 3, 3} << 2 << 11 << 0 << 3 << StringMatrix{2, 3, {"1st", "4th", "5th", "10th", "13th", "14th"}};
    QTest::newRow("42: erase from random positions") << StringMatrix{2, 9, {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th", "17th", "18th"}} << std::vector<StringMatrixSizeType>{1, 6, 5, 1, 3, 1, 0} << 2 << 4 << 0 << 1 << StringMatrix{2, 2, {"5th", "9th", "14th", "18th"}};
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
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1 << 5 << 3 << 0 << 0 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, -1, -1, -1, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("2: insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 5 << 3 << 0 << 0 << IntMatrix{5, 3, {-1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("3: insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1 << 5 << 3 << 0 << 0 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << -1 << 6 << 5 << 1 << 0 << IntMatrix{4, 4, {1, 2, 3, 4, -1, -1, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("5: insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 6 << 5 << 1 << 0 << IntMatrix{4, 4, {-1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("6: insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -1 << 6 << 5 << 1 << 0 << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1, -1}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 0 << -1 << 10 << 2 << 0 << 0 << IntMatrix{9, 2, {-1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("8: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 2 << -1 << 10 << 2 << 0 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("9: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 3 << -1 << 10 << 2 << 0 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, -1, -1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("10: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 4 << -1 << 10 << 2 << 0 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, -1, -1, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("11: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << -1 << 10 << 2 << 1 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("12: insert at random position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 7 << -1 << 10 << 2 << 1 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, -1, 15, 16}};
    QTest::newRow("13: insert at end position") << IntMatrix{8, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 8 << -1 << 10 << 2 << 1 << 0 << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1, -1}};
    QTest::newRow("14: insert at beginning position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << -1 << 11 << 2 << 0 << 0 << IntMatrix{10, 2, {-1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("15: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << -1 << 11 << 2 << 0 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("16: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 3 << -1 << 11 << 2 << 0 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, -1, -1, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("17: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 4 << -1 << 11 << 2 << 0 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, -1, -1, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("18: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 5 << -1 << 11 << 2 << 1 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -1, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("19: insert at random position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 7 << -1 << 11 << 2 << 1 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, -1, 15, 16, 17, 18}};
    QTest::newRow("20: insert at end position") << IntMatrix{9, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 9 << -1 << 11 << 2 << 1 << 0 << IntMatrix{10, 2, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1, -1}};
}

void ResizingTests::_buildIntMatrixInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("1: insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1 << 3 << 5 << 0 << 0 << IntMatrix{3, 5, {1, 2, -1, 3, 4, 5, 6, -1, 7, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("2: insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 3 << 5 << 0 << 0 << IntMatrix{3, 5, {-1, 1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12}};
    QTest::newRow("3: insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1 << 3 << 5 << 0 << 0 << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("4: insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << -1 << 5 << 6 << 0 << 1 << IntMatrix{4, 4, {1, -1, 2, 3, 4, -1, 5, 6, 7, -1, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("5: insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 5 << 6 << 0 << 1 << IntMatrix{4, 4, {-1, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12}};
    QTest::newRow("6: insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -1 << 5 << 6 << 0 << 1 << IntMatrix{4, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1}};

    // test left/right available capacity scenarios
    QTest::newRow("7: insert at beginning position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 0 << -1 << 2 << 10 << 0 << 0 << IntMatrix{2, 9, {-1, 1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("8: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 2 << -1 << 2 << 10 << 0 << 0 << IntMatrix{2, 9, {1, 2, -1, 3, 4, 5, 6, 7, 8, 9, 10, -1, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("9: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 3 << -1 << 2 << 10 << 0 << 0 << IntMatrix{2, 9, {1, 2, 3, -1, 4, 5, 6, 7, 8, 9, 10, 11, -1, 12, 13, 14, 15, 16}};
    QTest::newRow("10: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 4 << -1 << 2 << 10 << 0 << 0 << IntMatrix{2, 9, {1, 2, 3, 4, -1, 5, 6, 7, 8, 9, 10, 11, 12, -1, 13, 14, 15, 16}};
    QTest::newRow("11: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << -1 << 2 << 10 << 0 << 1 << IntMatrix{2, 9, {1, 2, 3, 4, 5, -1, 6, 7, 8, 9, 10, 11, 12, 13, -1, 14, 15, 16}};
    QTest::newRow("12: insert at random position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 7 << -1 << 2 << 10 << 0 << 1 << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, 12, 13, 14, 15, -1, 16}};
    QTest::newRow("13: insert at end position") << IntMatrix{2, 8, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 8 << -1 << 2 << 10 << 0 << 1 << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, -1, 9, 10, 11, 12, 13, 14, 15, 16, -1}};
    QTest::newRow("14: insert at beginning position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 0 << -1 << 2 << 11 << 0 << 0 << IntMatrix{2, 10, {-1, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("15: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 2 << -1 << 2 << 11 << 0 << 0 << IntMatrix{2, 10, {1, 2, -1, 3, 4, 5, 6, 7, 8, 9, 10, 11, -1, 12, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("16: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 3 << -1 << 2 << 11 << 0 << 0 << IntMatrix{2, 10, {1, 2, 3, -1, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, 13, 14, 15, 16, 17, 18}};
    QTest::newRow("17: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 4 << -1 << 2 << 11 << 0 << 0 << IntMatrix{2, 10, {1, 2, 3, 4, -1, 5, 6, 7, 8, 9, 10, 11, 12, 13, -1, 14, 15, 16, 17, 18}};
    QTest::newRow("18: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 5 << -1 << 2 << 11 << 0 << 1 << IntMatrix{2, 10, {1, 2, 3, 4, 5, -1, 6, 7, 8, 9, 10, 11, 12, 13, 14, -1, 15, 16, 17, 18}};
    QTest::newRow("19: insert at random position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 7 << -1 << 2 << 11 << 0 << 1 << IntMatrix{2, 10, {1, 2, 3, 4, 5, 6, 7, -1, 8, 9, 10, 11, 12, 13, 14, 15, 16, -1, 17, 18}};
    QTest::newRow("20: insert at end position") << IntMatrix{2, 9, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}} << 9 << -1 << 2 << 11 << 0 << 1 << IntMatrix{2, 10, {1, 2, 3, 4, 5, 6, 7, 8, 9, -1, 10, 11, 12, 13, 14, 15, 16, 17, 18, -1}};
}

QTEST_APPLESS_MAIN(ResizingTests)

#include "tst_resizingtests.moc"
