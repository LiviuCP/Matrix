#include <QtTest>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)

class ResizingTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testResizeWithoutFillingInNewValues();
    void testResizeAndFillInNewValues();
    void testShrinkToFit();
    void testInsertRowNoSetValue();
    void testInsertRowSetValue();
    void testInsertColumnNoSetValue();
    void testInsertColumnSetValue();
    void testEraseRow();
    void testEraseColumn();
    void testClear();

    // test data
    void testResizeWithoutFillingInNewValues_data();
    void testResizeAndFillInNewValues_data();
    void testShrinkToFit_data();
    void testInsertRowNoSetValue_data();
    void testInsertRowSetValue_data();
    void testInsertColumnNoSetValue_data();
    void testInsertColumnSetValue_data();
    void testEraseRow_data();
    void testEraseColumn_data();
    void testClear_data();

private:
    // test data helper methods
    void _buildInsertRowTestingTable();
    void _buildInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
};

void ResizingTests::testResizeWithoutFillingInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedRetainedElementsMatrix);

    matrix.resize(resizeRowsCount, resizeColumnsCount);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != resizeRowsCount || matrix.getNrOfColumns() != resizeColumnsCount)
    {
        QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
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
}

void ResizingTests::testResizeAndFillInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, fillValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, fillValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Resizing failed, the matrix does not have the correct values!");
    }
}

void ResizingTests::testShrinkToFit()
{
    QFETCH(IntMatrix, matrix);

    mPrimaryIntMatrix = matrix;
    mPrimaryIntMatrix.shrinkToFit();

    if (mPrimaryIntMatrix.getRowCapacity() != matrix.getNrOfRows() || mPrimaryIntMatrix.getColumnCapacity() != matrix.getNrOfColumns())
    {
        QFAIL("Shrinking to fit failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(mPrimaryIntMatrix == matrix, "Shrinking to fit failed, the matrix does not retain its values!");
    }
}

void ResizingTests::testInsertRowNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert row failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != referenceMatrix.getNrOfRows() || matrix.getNrOfColumns() != referenceMatrix.getNrOfColumns())
    {
        QFAIL("Insert row failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
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
}

void ResizingTests::testInsertRowSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertRow(insertPosition, insertedRowValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert row failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == referenceMatrix, "Insert row failed, the matrix doesn't have the right values!");
    }
}

void ResizingTests::testInsertColumnNoSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert column failed, capacity of the matrix is not correct!");
    }
    else if (matrix.getNrOfRows() != referenceMatrix.getNrOfRows() || matrix.getNrOfColumns() != referenceMatrix.getNrOfColumns())
    {
        QFAIL("Insert column failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
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
}

void ResizingTests::testInsertColumnSetValue()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, referenceMatrix);

    matrix.insertColumn(insertPosition, insertedColumnValue);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Insert column failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == referenceMatrix, "Insert column failed, the matrix doesn't have the right values!");
    }
}

void ResizingTests::testEraseRow()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.eraseRow(erasePosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Erase row failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Erase row failed, the matrix doesn't have the right values on the remaining rows!");
    }
}

void ResizingTests::testEraseColumn()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, erasePosition);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrix, expectedMatrix);

    matrix.eraseColumn(erasePosition);

    if (matrix.getRowCapacity() != expectedRowCapacity || matrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Erase column failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(matrix == expectedMatrix, "Erase column failed, the matrix doesn't have the right values on the remaining columns!");
    }
}

void ResizingTests::testClear()
{
    QFETCH(IntMatrix, matrix);

    mPrimaryIntMatrix = matrix;
    mPrimaryIntMatrix.clear();

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == 0 &&
             mPrimaryIntMatrix.getColumnCapacity() == 0, "Clear failed, capacity is not correct!");

    QVERIFY2(mPrimaryIntMatrix.getNrOfRows() == 0 &&
             mPrimaryIntMatrix.getNrOfColumns() == 0, "Clear failed, number of rows and columns is not correct!");
}

void ResizingTests::testResizeWithoutFillingInNewValues_data()
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
    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << 5 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << 5 << 4 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << 1 << 1 << IntMatrix{};
    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

void ResizingTests::testResizeAndFillInNewValues_data()
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
    QTest::newRow("more rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 3 << -1 << 5 << 3 << IntMatrix{5, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, -1, -1, -1}};
    QTest::newRow("more rows, more columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 5 << 4 << -1 << 5 << 4 << IntMatrix{5, 4, {1, 2, 3, -1, 4, 5, 6, -1, 7, 8, 9, -1, 10, 11, 12, -1, -1, -1, -1, -1}};
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -1 << 1 << 1 << IntMatrix{1, 1, -1};
    QTest::newRow("equal rows, equal columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}} << 4 << 3 << -1 << 4 << 3 << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
}

void ResizingTests::testShrinkToFit_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("empty matrix") << IntMatrix{};
    QTest::newRow("square matrix") << IntMatrix{3, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9}};
    QTest::newRow("more rows than columns") << IntMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("less rows than columns") << IntMatrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}};
}

void ResizingTests::testInsertRowNoSetValue_data()
{
    _buildInsertRowTestingTable();
}

void ResizingTests::testInsertRowSetValue_data()
{
    _buildInsertRowTestingTable();
}

void ResizingTests::testInsertColumnNoSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void ResizingTests::testInsertColumnSetValue_data()
{
    _buildInsertColumnTestingTable();
}

void ResizingTests::testEraseRow_data()
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

void ResizingTests::testEraseColumn_data()
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

void ResizingTests::testClear_data()
{
    QTest::addColumn<IntMatrix>("matrix");

    QTest::newRow("non-empty matrix") << IntMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    QTest::newRow("empty matrix") << IntMatrix{};
}

void ResizingTests::_buildInsertRowTestingTable()
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
}

void ResizingTests::_buildInsertColumnTestingTable()
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
}

QTEST_APPLESS_MAIN(ResizingTests)

#include "tst_resizingtests.moc"
