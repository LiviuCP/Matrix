#include <QtTest>

#include "tst_resizingtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(StringMatrix)

class ResizingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixResizeWithoutFillingInNewValues();
    void testIntMatrixResizeAndFillInNewValues();
    void testIntMatrixShrinkToFit();
    void testIntMatrixInsertRowNoSetValue();
    void testIntMatrixInsertRowSetValue();
    void testIntMatrixInsertColumnNoSetValue();
    void testIntMatrixInsertColumnSetValue();
    void testIntMatrixEraseRow();
    void testIntMatrixEraseMultipleRows();
    void testIntMatrixEraseColumn();
    void testIntMatrixEraseMultipleColumns();
    void testIntMatrixClear();

    void testStringMatrixResizeWithoutFillingInNewValues();
    void testStringMatrixResizeAndFillInNewValues();
    void testStringMatrixShrinkToFit();
    void testStringMatrixInsertRowNoSetValue();
    void testStringMatrixInsertRowSetValue();
    void testStringMatrixInsertColumnNoSetValue();
    void testStringMatrixInsertColumnSetValue();
    void testStringMatrixEraseRow();
    void testStringMatrixEraseMultipleRows();
    void testStringMatrixEraseColumn();
    void testStringMatrixEraseMultipleColumns();
    void testStringMatrixClear();

    // test data
    void testIntMatrixResizeWithoutFillingInNewValues_data();
    void testIntMatrixResizeAndFillInNewValues_data();
    void testIntMatrixShrinkToFit_data();
    void testIntMatrixInsertRowNoSetValue_data();
    void testIntMatrixInsertRowSetValue_data();
    void testIntMatrixInsertColumnNoSetValue_data();
    void testIntMatrixInsertColumnSetValue_data();
    void testIntMatrixEraseRow_data();
    void testIntMatrixEraseMultipleRows_data();
    void testIntMatrixEraseColumn_data();
    void testIntMatrixEraseMultipleColumns_data();
    void testIntMatrixClear_data();

    void testStringMatrixResizeWithoutFillingInNewValues_data();
    void testStringMatrixResizeAndFillInNewValues_data();
    void testStringMatrixShrinkToFit_data();
    void testStringMatrixInsertRowNoSetValue_data();
    void testStringMatrixInsertRowSetValue_data();
    void testStringMatrixInsertColumnNoSetValue_data();
    void testStringMatrixInsertColumnSetValue_data();
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

void ResizingTests::testIntMatrixResizeWithoutFillingInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, expectedRowCapacity, expectedColumnCapacity);

    bool areRetainedValuesCorrect{true};

    for(IntMatrixSizeType rowNr{0}; rowNr < expectedRetainedElementsMatrix.getNrOfRows(); ++rowNr)
    {
        for(IntMatrixSizeType columnNr{0}; columnNr < expectedRetainedElementsMatrix.getNrOfColumns(); ++columnNr)
        {
            areRetainedValuesCorrect = areRetainedValuesCorrect && (matrix.at(rowNr, columnNr) == expectedRetainedElementsMatrix.at(rowNr, columnNr));
        }
    }

    QVERIFY2(areRetainedValuesCorrect, "Resizing failed, the retained element values are not correct!");
}

void ResizingTests::testIntMatrixResizeAndFillInNewValues()
{
    TEST_MATRIX_RESIZE_AND_FILL_IN_NEW_VALUES(int);
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
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

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
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

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

void ResizingTests::testStringMatrixResizeWithoutFillingInNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, resizeRowsCount);
    QFETCH(StringMatrixSizeType, resizeColumnsCount);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);
    QFETCH(StringMatrix, expectedMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, resizeRowsCount, resizeColumnsCount, expectedRowCapacity, expectedColumnCapacity);

    QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");
}

void ResizingTests::testStringMatrixResizeAndFillInNewValues()
{
    TEST_MATRIX_RESIZE_AND_FILL_IN_NEW_VALUES(std::string);
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
    QFETCH(StringMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    TEST_INSERT_ROW_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

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
    QFETCH(StringMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    TEST_INSERT_COLUMN_CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, referenceMatrix.getNrOfRows(), referenceMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

    QVERIFY2(matrix == referenceMatrix, "Insert column failed, the matrix doesn't have the right values!");
}

void ResizingTests::testStringMatrixInsertColumnSetValue()
{
    TEST_MATRIX_INSERT_COLUMN_SET_VALUE(std::string);
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

void ResizingTests::testIntMatrixResizeWithoutFillingInNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedRetainedElementsMatrix");

    QTest::newRow("equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << 4 << 2 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 2 << 3 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << 3 << 2 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << 4 << 5 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << 5 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}; // capacity stays unchanged
    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << 5 << 4 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << 1 << 1 << IntMatrix{};
    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << 3 << 4 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << 5 << 2 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};

    // additional tests for unchanged capacity
    QTest::newRow("equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 5 << 3 << 5 << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 5 << 5 << 5 << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
    QTest::newRow("equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 3 << 3 << 3 << 3 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixResizeAndFillInNewValues_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("fillValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("equal rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 2 << -1 << 4 << 2 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("less rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << -1 << 2 << 3 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("less rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 2 << -1 << 3 << 2 << IntMatrix{3, 2, {1, 2, 4, 5, 7, 8}};
    QTest::newRow("equal rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 5 << -1 << 4 << 5 << IntMatrix{4, 5, {1, 2, 3, -1, -1, 4, 5, 6, -1, -1, 7, 8, 9, -1, -1, 10, 11, 12, -1, -1}};
    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << -1 << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};  // capacity stays unchanged
    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << -1 << 5 << 4 << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -1 << 1 << 1 << IntMatrix{1, 1, -1};
    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << -1 << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 4 << -1 << 3 << 4 << IntMatrix{3, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1}};
    QTest::newRow("more rows, less columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 2 << -1 << 5 << 2 << IntMatrix{5, 2, {1, 2, 4, 5, 7, 8, 10, 11, -1, -1}};

    // additional tests for unchanged capacity
    QTest::newRow("equal rows, more columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << 5 << -1 << 3 << 5 << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};
    QTest::newRow("more rows, more columns") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}} << 5 << 5 << -1 << 5 << 5 << IntMatrix{5, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1, 13, 14, 15, 16, -1, -1, -1, -1, -1, -1}};
    QTest::newRow("equal rows, equal columns") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}} << 3 << 3 << -1 << 3 << 3 << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
}

void ResizingTests::testIntMatrixShrinkToFit_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("empty matrix") << IntMatrix{};
    QTest::newRow("square matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("more rows than columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows than columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
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

void ResizingTests::testIntMatrixEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 3 << 5 << IntMatrix{2, 4, {5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("erase at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 3 << 5 << IntMatrix{2, 4, {1, 2, 3, 4, 9, 10, 11, 12}};
    QTest::newRow("erase at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 3 << 5 << IntMatrix{2, 4, {1, 2, 3, 4, 5, 6, 7, 8}};
    QTest::newRow("erase the only row") << IntMatrix{1, 4, {1, 2, 3, 4}} << 0 << 0 << 0 << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleRows_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("erasedRowsCount");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 4 << 0 << 0 << IntMatrix{};
    QTest::newRow("erase at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 3 << 2 << 3 << IntMatrix{1, 3, {1, 2, 3}};
    QTest::newRow("erase at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 2 << 5 << 3 << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
}

void ResizingTests::testIntMatrixEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 5 << 3 << IntMatrix{4, 2, {2, 3, 5, 6, 8, 9, 11, 12}};
    QTest::newRow("erase at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 5 << 3 << IntMatrix{4, 2, {1, 3, 4, 6, 7, 9, 10, 12}};
    QTest::newRow("erase at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 5 << 3 << IntMatrix{4, 2, {1, 2, 4, 5, 7, 8, 10, 11}};
    QTest::newRow("erase the only column") << IntMatrix{4, 1, {1, 2, 3, 4}} << 0 << 0 << 0 << IntMatrix{};
}

void ResizingTests::testIntMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("erasePosition");
    QTest::addColumn<IntMatrixSizeType>("erasedColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << 4 << 0 << 0 << IntMatrix{};
    QTest::newRow("erase at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << 3 << 3 << 2 << IntMatrix{3, 1, {1, 5, 9}};
    QTest::newRow("erase at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << 2 << 3 << 5 << IntMatrix{3, 2, {1, 2, 5, 6, 9, 10}};
}

void ResizingTests::testIntMatrixClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("empty matrix") << IntMatrix{};
}

void ResizingTests::testStringMatrixResizeWithoutFillingInNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("equal rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 2 << 4 << 2 << StringMatrix{4, 2, {"1", "2", "4", "5", "7", "8", "10", "11"}};
    QTest::newRow("less rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 3 << 2 << 3 << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("less rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 2  << 3 << 2 << StringMatrix{3, 2, {"1", "2", "4", "5", "7", "8"}};
    QTest::newRow("equal rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 5 << 4 << 5 << StringMatrix{4, 5, {"1", "2", "3", "", "", "4", "5", "6", "", "", "7", "8", "9", "", "", "10", "11", "12", "", ""}};
    QTest::newRow("more rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 3 << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "", "", ""}}; // capacity stays unchanged
    QTest::newRow("more rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 4 << 5 << 4 << StringMatrix{5, 4, {"1", "2", "3", "", "4", "5", "6", "", "7", "8", "9", "", "10", "11", "12", "", "", "", "", ""}};
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << 1 << 1 << StringMatrix{1, 1, ""};
    QTest::newRow("equal rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 3 << 4 << 3 << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("less rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 4 << 3 << 4 << StringMatrix{3, 4, {"1", "2", "3", "", "4", "5", "6", "", "7", "8", "9", ""}};
    QTest::newRow("more rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 2 << 5 << 2 << StringMatrix{5, 2, {"1", "2", "4", "5", "7", "8", "10", "11", "", ""}};

    // additional tests for unchanged capacity
    QTest::newRow("equal rows, more columns") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 5 << 3 << 5 << StringMatrix{3, 5, {"1", "2", "3", "4", "", "5", "6", "7", "8", "", "9", "10", "11", "12", ""}};
    QTest::newRow("more rows, more columns") << StringMatrix{4, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}} << 5 << 5 << 5 << 5 << StringMatrix{5, 5, {"1", "2", "3", "4", "", "5", "6", "7", "8", "", "9", "10", "11", "12", "", "13", "14", "15", "16", "", "", "", "", "", ""}};
    QTest::newRow("equal rows, equal columns") << StringMatrix{3, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9"}} << 3 << 3 << 3 << 3 << StringMatrix{3, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9"}};
}

void ResizingTests::testStringMatrixResizeAndFillInNewValues_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("fillValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("equal rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 2 << std::string{"-1"} << 4 << 2 << StringMatrix{4, 2, {"1", "2", "4", "5", "7", "8", "10", "11"}};
    QTest::newRow("less rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 3 << std::string{"-1"} << 2 << 3 << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("less rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 2 << std::string{"-1"} << 3 << 2 << StringMatrix{3, 2, {"1", "2", "4", "5", "7", "8"}};
    QTest::newRow("equal rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 5 << std::string{"-1"} << 4 << 5 << StringMatrix{4, 5, {"1", "2", "3", "-1", "-1", "4", "5", "6", "-1", "-1", "7", "8", "9", "-1", "-1", "10", "11", "12", "-1", "-1"}};
    QTest::newRow("more rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 3 << std::string{"-1"} << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "-1", "-1", "-1"}}; // capacity stays unchanged
    QTest::newRow("more rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 4 << std::string{"-1"} << 5 << 4 << StringMatrix{5, 4, {"1", "2", "3", "-1", "4", "5", "6", "-1", "7", "8", "9", "-1", "10", "11", "12", "-1", "-1", "-1", "-1", "-1"}};
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"-1"} << 1 << 1 << StringMatrix{1, 1, "-1"};
    QTest::newRow("equal rows, equal columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 3 << std::string{"-1"} << 4 << 3 << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("less rows, more columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 4 << std::string{"-1"} << 3 << 4 << StringMatrix{3, 4, {"1", "2", "3", "-1", "4", "5", "6", "-1", "7", "8", "9", "-1"}};
    QTest::newRow("more rows, less columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 5 << 2 << std::string{"-1"} << 5 << 2 << StringMatrix{5, 2, {"1", "2", "4", "5", "7", "8", "10", "11", "-1", "-1"}};

    // additional tests for unchanged capacity
    QTest::newRow("equal rows, more columns") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 5 << std::string{"-1"} << 3 << 5 << StringMatrix{3, 5, {"1", "2", "3", "4", "-1", "5", "6", "7", "8", "-1", "9", "10", "11", "12", "-1"}};
    QTest::newRow("more rows, more columns") << StringMatrix{4, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}} << 5 << 5 << std::string{"-1"} << 5 << 5 << StringMatrix{5, 5, {"1", "2", "3", "4", "-1", "5", "6", "7", "8", "-1", "9", "10", "11", "12", "-1", "13", "14", "15", "16", "-1", "-1", "-1", "-1", "-1", "-1"}};
    QTest::newRow("equal rows, equal columns") << StringMatrix{3, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9"}} << 3 << 3 << std::string{"-1"} << 3 << 3 << StringMatrix{3, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9"}};
}

void ResizingTests::testStringMatrixShrinkToFit_data()
{
    QTest::addColumn<StringMatrix>("matrix");

    QTest::newRow("empty matrix") << StringMatrix{};
    QTest::newRow("square matrix") << StringMatrix{3, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9"}};
    QTest::newRow("more rows than columns") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("less rows than columns") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("square matrix") << StringMatrix{4, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "13", "14", "15", "16"}};
}

void ResizingTests::testStringMatrixInsertRowNoSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "", "", "", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 5 << 3 << StringMatrix{5, 3, {"", "", "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "", "", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 6 << 5 << StringMatrix{4, 4, {"1", "2", "3", "4", "", "", "", "", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 6 << 5 << StringMatrix{4, 4, {"", "", "", "", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 6 << 5 << StringMatrix{4, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "", "", "", ""}};
}

void ResizingTests::testStringMatrixInsertRowSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << std::string{"-1"} << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "-1", "-1", "-1", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << std::string{"-1"} << 5 << 3 << StringMatrix{5, 3, {"-1", "-1", "-1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << std::string{"-1"} << 5 << 3 << StringMatrix{5, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "-1", "-1", "-1"}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << std::string{"-1"} << 6 << 5 << StringMatrix{4, 4, {"1", "2", "3", "4", "-1", "-1", "-1", "-1", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << std::string{"-1"} << 6 << 5 << StringMatrix{4, 4, {"-1", "-1", "-1", "-1", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << std::string{"-1"} << 6 << 5 << StringMatrix{4, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12", "-1", "-1", "-1", "-1"}};
}

void ResizingTests::testStringMatrixInsertColumnNoSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 3 << 5 << StringMatrix{3, 5, {"1", "2", "", "3", "4", "5", "6", "", "7", "8", "9", "10", "", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 3 << 5 << StringMatrix{3, 5, {"", "1", "2", "3", "4", "", "5", "6", "7", "8", "", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << 3 << 5 << StringMatrix{3, 5, {"1", "2", "3", "4", "", "5", "6", "7", "8", "", "9", "10", "11", "12", ""}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 5 << 6 << StringMatrix{4, 4, {"1", "", "2", "3", "4", "", "5", "6", "7", "", "8", "9", "10", "", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 5 << 6 << StringMatrix{4, 4, {"", "1", "2", "3", "", "4", "5", "6", "", "7", "8", "9", "", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << 5 << 6 << StringMatrix{4, 4, {"1", "2", "3", "", "4", "5", "6", "", "7", "8", "9", "", "10", "11", "12", ""}};
}

void ResizingTests::testStringMatrixInsertColumnSetValue_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << std::string{"-1"} << 3 << 5 << StringMatrix{3, 5, {"1", "2", "-1", "3", "4", "5", "6", "-1", "7", "8", "9", "10", "-1", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << std::string{"-1"} << 3 << 5 << StringMatrix{3, 5, {"-1", "1", "2", "3", "4", "-1", "5", "6", "7", "8", "-1", "9", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 4 << std::string{"-1"} << 3 << 5 << StringMatrix{3, 5, {"1", "2", "3", "4", "-1", "5", "6", "7", "8", "-1", "9", "10", "11", "12", "-1"}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << std::string{"-1"} << 5 << 6 << StringMatrix{4, 4, {"1", "-1", "2", "3", "4", "-1", "5", "6", "7", "-1", "8", "9", "10", "-1", "11", "12"}};
    QTest::newRow("insert at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << std::string{"-1"} << 5 << 6 << StringMatrix{4, 4, {"-1", "1", "2", "3", "-1", "4", "5", "6", "-1", "7", "8", "9", "-1", "10", "11", "12"}};
    QTest::newRow("insert at end position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 3 << std::string{"-1"} << 5 << 6 << StringMatrix{4, 4, {"1", "2", "3", "-1", "4", "5", "6", "-1", "7", "8", "9", "-1", "10", "11", "12", "-1"}};

}

void ResizingTests::testStringMatrixEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 3 << 5 << StringMatrix{2, 4, {"5", "6", "7", "8", "9", "10", "11", "12"}};
    QTest::newRow("erase at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 3 << 5 << StringMatrix{2, 4, {"1", "2", "3", "4", "9", "10", "11", "12"}};
    QTest::newRow("erase at end position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 3 << 5 << StringMatrix{2, 4, {"1", "2", "3", "4", "5", "6", "7", "8"}};
    QTest::newRow("erase the only row") << StringMatrix{1, 4, {"1", "2", "3", "4"}} << 0 << 0 << 0 << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleRows_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("erasedRowsCount");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 4 << 0 << 0 << StringMatrix{};
    QTest::newRow("erase at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 3 << 2 << 3 << StringMatrix{1, 3, {"1", "2", "3"}};
    QTest::newRow("erase at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 2 << 5 << 3 << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}};
}

void ResizingTests::testStringMatrixEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 5 << 3 << StringMatrix{4, 2, {"2", "3", "5", "6", "8", "9", "11", "12"}};
    QTest::newRow("erase at random position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 5 << 3 << StringMatrix{4, 2, {"1", "3", "4", "6", "7", "9", "10", "12"}};
    QTest::newRow("erase at end position") << StringMatrix{4, 3, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 5 << 3 << StringMatrix{4, 2, {"1", "2", "4", "5", "7", "8", "10", "11"}};
    QTest::newRow("erase the only column") << StringMatrix{4, 1, {"1", "2", "3", "4"}} << 0 << 0 << 0 << StringMatrix{};
}

void ResizingTests::testStringMatrixEraseMultipleColumns_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("erasePosition");
    QTest::addColumn<StringMatrixSizeType>("erasedColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrix>("expectedMatrix");

    QTest::newRow("erase at beginning position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 0 << 4 << 0 << 0 << StringMatrix{};
    QTest::newRow("erase at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 1 << 3 << 3 << 2 << StringMatrix{3, 1, {"1", "5", "9"}};
    QTest::newRow("erase at random position") << StringMatrix{3, 4, {"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"}} << 2 << 2 << 3 << 5 << StringMatrix{3, 2, {"1", "2", "5", "6", "9", "10"}};
}

void ResizingTests::testStringMatrixClear_data()
{
    QTest::addColumn<StringMatrix>("matrix");

    QTest::newRow("non-empty matrix") << StringMatrix{2, 3, {"1", "2", "3", "4", "5", "6"}};
    QTest::newRow("empty matrix") << StringMatrix{};
}

void ResizingTests::_buildIntMatrixInsertRowTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1 << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, -1, -1, -1, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 5 << 3 << IntMatrix{5, 3, {-1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1 << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << -1 << 6 << 5 << IntMatrix{4, 4, {1, 2, 3, 4, -1, -1, -1, -1, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 6 << 5 << IntMatrix{4, 4, {-1, -1, -1, -1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -1 << 6 << 5 << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1, -1}};
}

void ResizingTests::_buildIntMatrixInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrix>("referenceMatrix");

    QTest::newRow("insert at random position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 2 << -1 << 3 << 5 << IntMatrix{3, 5, {1, 2, -1, 3, 4, 5, 6, -1, 7, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("insert at beginning position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 3 << 5 << IntMatrix{3, 5, {-1, 1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12}};
    QTest::newRow("insert at end position") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << -1 << 3 << 5 << IntMatrix{3, 5, {1, 2, 3, 4, -1, 5, 6, 7, 8, -1, 9, 10, 11, 12, -1}};

    // test maximum capacity reached scenarios
    QTest::newRow("insert at random position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 1 << -1 << 5 << 6 << IntMatrix{4, 4, {1, -1, 2, 3, 4, -1, 5, 6, 7, -1, 8, 9, 10, -1, 11, 12}};
    QTest::newRow("insert at beginning position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 0 << -1 << 5 << 6 << IntMatrix{4, 4, {-1, 1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12}};
    QTest::newRow("insert at end position") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 3 << -1 << 5 << 6 << IntMatrix{4, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1}};
}

QTEST_APPLESS_MAIN(ResizingTests)

#include "tst_resizingtests.moc"
