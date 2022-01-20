#include <QtTest>

#include <vector>
#include <tuple>

#include "testutils.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(TripleSizeTypeTuple)
Q_DECLARE_METATYPE(TripleSizeTypeTupleArray)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class CapacityTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testCapacityWithInitListConstructor();
    void testCapacityWithIdenticalMatrixConstructor();
    void testCapacityWithDiagonalMatrixConstructor();
    void testCapacityWithCopyConstructor();
    void testCapacityWithMoveConstructor();
    void testCapacityWithCopyAssignmentOperator();
    void testCapacityWithMoveAssignmentOperator();
    void testCapacityWithTranspose();
    void testCapacityWithResizeWithoutFillingInNewValues();
    void testCapacityWithResizeAndFillInNewValues();
    void testCapacityWithInsertRow();
    void testCapacityWithInsertColumn();
    void testCapacityWithEraseRow();
    void testCapacityWithEraseColumn();
    void testCapacityWithCatByRow();
    void testCapacityWithCatByColumn();
    void testCapacityWithSplitByRow();
    void testCapacityWithSplitByColumn();

    // test data
    void testCapacityWithIdenticalMatrixConstructor_data();
    void testCapacityWithDiagonalMatrixConstructor_data();
    void testCapacityWithCopyConstructor_data();
    void testCapacityWithMoveConstructor_data();
    void testCapacityWithCopyAssignmentOperator_data();
    void testCapacityWithMoveAssignmentOperator_data();
    void testCapacityWithTranspose_data();
    void testCapacityWithResizeWithoutFillingInNewValues_data();
    void testCapacityWithResizeAndFillInNewValues_data();
    void testCapacityWithInsertRow_data();
    void testCapacityWithInsertColumn_data();
    void testCapacityWithEraseRow_data();
    void testCapacityWithEraseColumn_data();
    void testCapacityWithCatByRow_data();
    void testCapacityWithCatByColumn_data();
    void testCapacityWithSplitByRow_data();
    void testCapacityWithSplitByColumn_data();

private:
    // test data helper methods
    void _buildCapacityWithMoveCopyConstructorsTestingTable();
    void _buildCapacityWithAssignmentOperatorsTestingTable();
    void _buildCapacityWithResizeTestingTable();

    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void CapacityTests::testCapacityWithInitListConstructor()
{
    {
        IntMatrix matrix{3, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 3 &&
                 matrix.getColumnCapacity() == 5, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{4, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

        QVERIFY2(matrix.getRowCapacity() == 5 &&
                 matrix.getColumnCapacity() == 3, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{
                            8, 10, {
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                      0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                  }
                        };

        QVERIFY2(matrix.getRowCapacity() == 10 &&
                 matrix.getColumnCapacity() == 12, "Init list constructor initialized matrix with wrong capacity");
    }

    {
        IntMatrix matrix{
                            10, 8, {
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0,
                                        0, 0, 0, 0, 0, 0, 0, 0
                                    }
                        };

        QVERIFY2(matrix.getRowCapacity() == 12 &&
                 matrix.getColumnCapacity() == 10, "Init list constructor initialized matrix with wrong capacity");
    }
}

void CapacityTests::testCapacityWithIdenticalMatrixConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix matrix{rowsCount, columnsCount, elementValue};

    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity &&
             matrix.getColumnCapacity() == expectedColumnCapacity, "Identical matrix constructor initialized matrix with wrong capacity");
}

void CapacityTests::testCapacityWithDiagonalMatrixConstructor()
{
    QFETCH(IntMatrixSizeType, rowsColumnsCount);
    QFETCH(int, nonDiagonalValue);
    QFETCH(int, diagonalValue);
    QFETCH(IntMatrixSizeType, expectedRowColumnCapacity);

    IntMatrix matrix{rowsColumnsCount, std::pair<int, int>{nonDiagonalValue, diagonalValue}};

    QVERIFY2(matrix.getRowCapacity() == expectedRowColumnCapacity &&
             matrix.getColumnCapacity() == expectedRowColumnCapacity, "Diag matrix constructor initialized matrix with wrong capacity");
}

void CapacityTests::testCapacityWithCopyConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{rowsCount, columnsCount, elementValue};
    IntMatrix destMatrix{srcMatrix};

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy constructor failed, capacity of the destination matrix is not correct!");
}

void CapacityTests::testCapacityWithMoveConstructor()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{rowsCount, columnsCount, elementValue};
    IntMatrix destMatrix{std::move(srcMatrix)};

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Move constructor failed, capacity of the destination matrix is not correct!");
}

void CapacityTests::testCapacityWithCopyAssignmentOperator()
{
    QFETCH(IntMatrixSizeType, srcMatrixRowsCount);
    QFETCH(IntMatrixSizeType, srcMatrixColumnsCount);
    QFETCH(int, srcMatrixElementValue);
    QFETCH(IntMatrixSizeType, destMatrixRowsCount);
    QFETCH(IntMatrixSizeType, destMatrixColumnsCount);
    QFETCH(int, destMatrixElementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue};

    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0)
    {
        IntMatrix destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue};
        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        IntMatrix destMatrix;
        destMatrix = srcMatrix;

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
}

void CapacityTests::testCapacityWithMoveAssignmentOperator()
{
    QFETCH(IntMatrixSizeType, srcMatrixRowsCount);
    QFETCH(IntMatrixSizeType, srcMatrixColumnsCount);
    QFETCH(int, srcMatrixElementValue);
    QFETCH(IntMatrixSizeType, destMatrixRowsCount);
    QFETCH(IntMatrixSizeType, destMatrixColumnsCount);
    QFETCH(int, destMatrixElementValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    IntMatrix srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue};

    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0)
    {
        IntMatrix destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue};
        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
    else
    {
        IntMatrix destMatrix;
        destMatrix = std::move(srcMatrix);

        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!");
    }
}

void CapacityTests::testCapacityWithTranspose()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isTransposedToItself);

    mPrimaryIntMatrix = srcMatrix;

    if (isTransposedToItself)
    {
        mPrimaryIntMatrix.transpose(mPrimaryIntMatrix);

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
                 mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
    }
    else
    {
        mSecondaryIntMatrix = destMatrix;
        mPrimaryIntMatrix.transpose(mSecondaryIntMatrix);

        QVERIFY2(mSecondaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
                 mSecondaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!");
    }
}

/* In addition to testing resulting capacity a consistency check (size and retained element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CapacityTests::testCapacityWithResizeWithoutFillingInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, requestedRowCapacity);
    QFETCH(IntMatrixSizeType, requestedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    mPrimaryIntMatrix = matrix;
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    const IntMatrixSizeType c_RetainedNrOfRows{std::min(resizeRowsCount, mSecondaryIntMatrix.getNrOfRows())};
    const IntMatrixSizeType c_RetainedNrOfColumns{std::min(resizeColumnsCount, mSecondaryIntMatrix.getNrOfColumns())};

    mPrimaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    if (mSecondaryIntMatrix.getRowCapacity() != expectedRowCapacity || mSecondaryIntMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else if (mSecondaryIntMatrix.getNrOfRows() != mPrimaryIntMatrix.getNrOfRows() || mSecondaryIntMatrix.getNrOfColumns() != mPrimaryIntMatrix.getNrOfColumns())
    {
        QFAIL("Resizing failed, number of rows or columns of the matrix is not correct!");
    }
    else
    {
        bool areRetainedValuesCorrect{true};

        for (IntMatrixSizeType rowNr{0}; rowNr < c_RetainedNrOfRows; ++rowNr)
        {
            for (IntMatrixSizeType columnNr{0}; columnNr < c_RetainedNrOfColumns; ++columnNr)
            {
                areRetainedValuesCorrect = areRetainedValuesCorrect && (mSecondaryIntMatrix.at(rowNr, columnNr) == mPrimaryIntMatrix.at(rowNr, columnNr));
            }
        }

        QVERIFY2(areRetainedValuesCorrect, "Resizing failed, the matrix does not have the correct values for the retained items!");
    }
}

/* In addition to testing resulting capacity a consistency check (size and element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CapacityTests::testCapacityWithResizeAndFillInNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(int, resizeElementValue);
    QFETCH(IntMatrixSizeType, requestedRowCapacity);
    QFETCH(IntMatrixSizeType, requestedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    mPrimaryIntMatrix = matrix;
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    mPrimaryIntMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue);
    mSecondaryIntMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue, requestedRowCapacity, requestedColumnCapacity);

    if (mSecondaryIntMatrix.getRowCapacity() != expectedRowCapacity || mSecondaryIntMatrix.getColumnCapacity() != expectedColumnCapacity)
    {
        QFAIL("Resizing failed, capacity of the matrix is not correct!");
    }
    else
    {
        QVERIFY2(mSecondaryIntMatrix == mPrimaryIntMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");
    }
}

void CapacityTests::testCapacityWithInsertRow()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedRowValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isInsertedRowValueSet);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    if (isInsertedRowValueSet)
    {
        mPrimaryIntMatrix.insertRow(insertPosition, insertedRowValue);
    }
    else
    {
        mPrimaryIntMatrix.insertRow(insertPosition);
    }

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
             mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Insert row failed, capacity of the matrix is not correct!");
}

void CapacityTests::testCapacityWithInsertColumn()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(IntMatrixSizeType, insertPosition);
    QFETCH(int, insertedColumnValue);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(bool, isInsertedColumnValueSet);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    if (isInsertedColumnValueSet)
    {
        mPrimaryIntMatrix.insertColumn(insertPosition, insertedColumnValue);
    }
    else
    {
        mPrimaryIntMatrix.insertColumn(insertPosition);
    }

    QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == expectedRowCapacity &&
             mPrimaryIntMatrix.getColumnCapacity() == expectedColumnCapacity, "Insert column failed, capacity of the matrix is not correct!");
}

void CapacityTests::testCapacityWithEraseRow()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(TripleSizeTypeTupleArray, erasedRowAndExpectedCapacity);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    for (const auto& data : erasedRowAndExpectedCapacity)
    {
        mPrimaryIntMatrix.eraseRow(std::get<0>(data));

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == std::get<1>(data) &&
                 mPrimaryIntMatrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!");
    }
}

void CapacityTests::testCapacityWithEraseColumn()
{
    QFETCH(IntMatrixSizeType, rowsCount);
    QFETCH(IntMatrixSizeType, columnsCount);
    QFETCH(int, elementValue);
    QFETCH(TripleSizeTypeTupleArray, erasedColumnAndExpectedCapacity);

    mPrimaryIntMatrix = {rowsCount, columnsCount, elementValue};

    for (const auto& data : erasedColumnAndExpectedCapacity)
    {
        mPrimaryIntMatrix.eraseColumn(std::get<0>(data));

        QVERIFY2(mPrimaryIntMatrix.getRowCapacity() == std::get<1>(data) &&
                 mPrimaryIntMatrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!");
    }
}

void CapacityTests::testCapacityWithCatByRow()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
    }

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

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Vertical concatenation failed, capacity of the destination matrix is not correct!");
}

void CapacityTests::testCapacityWithCatByColumn()
{
    QFETCH(IntMatrix, destMatrix);
    QFETCH(IntMatrix, firstSrcMatrix);
    QFETCH(IntMatrix, secondSrcMatrix);
    QFETCH(ConcatMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
    }

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

    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity &&
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Horizontal concatenation failed, capacity of the destination matrix is not correct!");
}

void CapacityTests::testCapacityWithSplitByRow()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(bool, isFirstDestResized);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        if (isFirstDestResized)
        {
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
        else
        {
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
    }

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
    default:
        QFAIL("exception scenario");
        break;
    }

    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity &&
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Vertical split failed, capacity of the first destination matrix is not correct!");

    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity &&
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Vertical split failed, capacity of the second destination matrix is not correct!");
}

void CapacityTests::testCapacityWithSplitByColumn()
{
    QFETCH(IntMatrix, srcMatrix);
    QFETCH(IntMatrix, firstDestMatrix);
    QFETCH(IntMatrix, secondDestMatrix);
    QFETCH(IntMatrixSizeType, splitPosition);
    QFETCH(SplitMode, mode);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, resizeRowCapacity);
    QFETCH(IntMatrixSizeType, resizeColumnCapacity);
    QFETCH(bool, isFirstDestResized);
    QFETCH(IntMatrixSizeType, expectedFirstDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedFirstDestColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestRowCapacity);
    QFETCH(IntMatrixSizeType, expectedSecondDestColumnCapacity);

    if (resizeRowsCount > 0 && resizeColumnsCount > 0)
    {
        if (isFirstDestResized)
        {
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
        else
        {
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity);
        }
    }

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
    default:
        QFAIL("exception scenario");
        break;
    }

    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity &&
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Horizontal split failed, capacity of the first destination matrix is not correct!");

    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity &&
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Horizontal split failed, capacity of the second destination matrix is not correct!");
}

void CapacityTests::testCapacityWithIdenticalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("small size matrix") << 3 << 4 << -5 << 3 << 5;
    QTest::newRow("small size matrix") << 4 << 3 << -5 << 5 << 3;
    QTest::newRow("large size matrix") << 25 << 20 << -2 << 31 << 25;
    QTest::newRow("large size matrix") << 20 << 25 << -2 << 25 << 31;
}

void CapacityTests::testCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowColumnCapacity");

    QTest::newRow("small size matrix") << 3 << -2 << -3 << 3;
    QTest::newRow("small size matrix") << 4 << -2 << -3 << 5;
    QTest::newRow("medium size matrix") << 8 << -2 << -3 << 10;
    QTest::newRow("medium size matrix") << 10 << -2 << -3 << 12;
}

void CapacityTests::testCapacityWithCopyConstructor_data()
{
    _buildCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testCapacityWithMoveConstructor_data()
{
    _buildCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testCapacityWithCopyAssignmentOperator_data()
{
    _buildCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testCapacityWithMoveAssignmentOperator_data()
{
    _buildCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testCapacityWithTranspose_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("transposed matrix initially empty") << IntMatrix{3, 4, 2} << IntMatrix{} << 5 << 3 << false;
    QTest::newRow("transposed matrix initially empty") << IntMatrix{4, 3, 2} << IntMatrix{} << 3 << 5 << false;
    QTest::newRow("transposed matrix initially empty") << IntMatrix{7, 8, 2} << IntMatrix{} << 10 << 8 << false;
    QTest::newRow("transposed matrix initially empty") << IntMatrix{8, 7, 2} << IntMatrix{} << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 6, 2} << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 6, 2} << 7 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 7, 2} << 8 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 7, 2} << 7 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{7, 8, 2} << 8 << 10 << false;
    QTest::newRow("matrix transposed to itself") << IntMatrix{3, 3, 2} << IntMatrix{3, 3, 2} << 3 << 3 << true;
    QTest::newRow("matrix transposed to itself") << IntMatrix{3, 4, 2} << IntMatrix{3, 4, 2} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << IntMatrix{4, 3, 2} << IntMatrix{4, 3, 2} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << IntMatrix{4, 4, 2} << IntMatrix{4, 4, 2} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << IntMatrix{7, 8, 2} << IntMatrix{7, 8, 2} << 8 << 10 << true;
    QTest::newRow("matrix transposed to itself") << IntMatrix{8, 7, 2} << IntMatrix{8, 7, 2} << 10 << 8 << true;
}

void CapacityTests::testCapacityWithResizeWithoutFillingInNewValues_data()
{
    _buildCapacityWithResizeTestingTable();
}

void CapacityTests::testCapacityWithResizeAndFillInNewValues_data()
{
    _buildCapacityWithResizeTestingTable();
}

void CapacityTests::testCapacityWithInsertRow_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("inserted row value NOT set") << 3 << 4 << -2 << 1 << 5 << 6 << 5 << false;
    QTest::newRow("inserted row value set") << 3 << 4 << -2 << 1 << 5 << 6 << 5 << true;
    QTest::newRow("inserted row value NOT set") << 6 << 5 << -2 << 3 << 5 << 7 << 6 << false;
    QTest::newRow("inserted row value set") << 6 << 5 << -2 << 3 << 5 << 7 << 6 << true;
    QTest::newRow("inserted row value NOT set") << 8 << 2 << -2 << 5 << 5 << 10 << 2 << false;
    QTest::newRow("inserted row value set") << 8 << 2 << -2 << 5 << 5 << 10 << 2 << true;
}

void CapacityTests::testCapacityWithInsertColumn_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("inserted column value NOT set") << 5 << 3 << 4 << 1 << 1 << 6 << 6 << false;
    QTest::newRow("inserted column value set") << 5 << 3 << 4 << 1 << 1 << 6 << 6 << true;
    QTest::newRow("inserted column value NOT set") << 5 << 7 << 4 << 1 << 1 << 6 << 8 << false;
    QTest::newRow("inserted column value set") << 5 << 7 << 4 << 1 << 1 << 6 << 8 << true;
    QTest::newRow("inserted column value NOT set") << 5 << 14 << 4 << 1 << 1 << 6 << 17 << false;
    QTest::newRow("inserted column value set") << 5 << 14 << 4 << 1 << 1 << 6 << 17 << true;
}

void CapacityTests::testCapacityWithEraseRow_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedRowAndExpectedCapacity");

    QTest::newRow("less rows than columns") << 3 << 4 << -2 << TripleSizeTypeTupleArray{{1, 3, 5}, {1, 3, 5}, {0, 0, 0}};
    QTest::newRow("square matrix") << 4 << 4 << -2 << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 2, 5}, {0, 0, 0}};
    QTest::newRow("more rows than columns") << 7 << 5 << -2 << TripleSizeTypeTupleArray{{1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 4, 6}, {1, 2, 6}, {0, 0, 0}};
}

void CapacityTests::testCapacityWithEraseColumn_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedColumnAndExpectedCapacity");

    QTest::newRow("less columns than rows") << 4 << 3 << 4 << TripleSizeTypeTupleArray{{1, 5, 3}, {1, 5, 3}, {0, 0, 0}};
    QTest::newRow("square matrix") << 4 << 4 << 4 << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 5, 2}, {0, 0, 0}};
    QTest::newRow("more columns than rows") << 5 << 7 << 4 << TripleSizeTypeTupleArray{{1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 4}, {1, 6, 2}, {0, 0, 0}};
}

void CapacityTests::testCapacityWithCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8 << 9 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8 << 9 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8 << 8 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8 << 9 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{10, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 12 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 7;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7 << 9 << 7;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8 << 9 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7 << 10 << 7;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8 << 10 << 8;
}

void CapacityTests::testCapacityWithCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("firstSrcMatrix");
    QTest::addColumn<IntMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9 << 8 << 9;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9 << 8 << 9;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8 << 8 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9 << 8 << 9;
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{5, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{5, 10, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 12;
    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 7 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9 << 7 << 9;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9 << 8 << 9;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10 << 7 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10 << 8 << 10;
}

void CapacityTests::testCapacityWithSplitByRow_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 17 << false << 18 << 21 << 8 << 17;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 18 << false << 18 << 21 << 8 << 18;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 7 << 18;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 17 << true << 10 << 17 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 18 << true << 10 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << true << 10 << 17 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << true << 10 << 18 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 18 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << false << 10 << 21 << 8 << 17;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << false << 10 << 21 << 8 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 15, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 7 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 17 << false << 18 << 21 << 10 << 17;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 18 << false << 18 << 21 << 10 << 18;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 18;
    QTest::newRow("scenario: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 17 << true << 8 << 17 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 18 << true << 8 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 7 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << true << 8 << 17 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << true << 8 << 18 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 7 << 18 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << false << 8 << 21 << 10 << 17;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << false << 8 << 21 << 10 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 15, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 8 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
}

void CapacityTests::testCapacityWithSplitByColumn_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<IntMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 17 << 6 << false << 21 << 18 << 17 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 18 << 6 << false << 21 << 18 << 18 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 7;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << false << 21 << 10 << 17 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << false << 21 << 10 << 18 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 6, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 18 << 7;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 17 << 7 << false << 21 << 18 << 17 << 10;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 18 << 7 << false << 21 << 18 << 18 << 10;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 8;
    QTest::newRow("scenario: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 18;
    QTest::newRow("scenario: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << false << 21 << 8 << 17 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << false << 21 << 8 << 18 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 7, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 18 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
}

void CapacityTests::_buildCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("small size matrix") << 3 << 4 << -1 << 3 << 5;
    QTest::newRow("small size matrix") << 4 << 3 << -1 << 5 << 3;
    QTest::newRow("medium size matrix") << 7 << 8 << -1 << 8 << 10;
    QTest::newRow("medium size matrix") << 8 << 7 << -1 << 10 << 8;
}

void CapacityTests::_buildCapacityWithAssignmentOperatorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("srcMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("srcMatrixColumnsCount");
    QTest::addColumn<int>("srcMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("destMatrixRowsCount");
    QTest::addColumn<IntMatrixSizeType>("destMatrixColumnsCount");
    QTest::addColumn<int>("destMatrixElementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("destination matrix initially empty") << 3 << 4 << -1 << 0 << 0 << 0 << 3 << 5;
    QTest::newRow("destination matrix initially empty") << 4 << 3 << -1 << 0 << 0 << 0 << 5 << 3;
    QTest::newRow("destination matrix initially empty") << 7 << 8 << -1 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("destination matrix initially empty") << 8 << 7 << -1 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("destination matrix initially NOT empty") << 3 << 4 << -1 << 2 << 3 << -5 << 3 << 5;
    QTest::newRow("destination matrix initially NOT empty") << 4 << 3 << -1 << 2 << 3 << -5 << 5 << 3;
    QTest::newRow("destination matrix initially NOT empty") << 7 << 8 << -1 << 3 << 4 << -5 << 8 << 10;
    QTest::newRow("destination matrix initially NOT empty") << 8 << 7 << -1 << 3 << 4 << -5 << 10 << 8;
}

void CapacityTests::_buildCapacityWithResizeTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<IntMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 0 << 0 << 10 << 7;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 7 << 10 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 0 << 10 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 0 << 0 << 9 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 6 << 10 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 7 << 10 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 0 << 10 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 0 << 0 << 9 << 7;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 0 << 0 << 10 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 7 << 12 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 0 << 12 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 7 << 13 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 0 << 13 << 8;
    QTest::newRow("more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 0 << 0 << 11 << 8;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 0 << 0 << 10 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 0 << 0 << 11 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 6 << 12 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 7 << 12 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 0 << 12 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 6 << 13 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 7 << 13 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 0 << 13 << 7;
    QTest::newRow("more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 0 << 0 << 11 << 7;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 7 << 10 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 8 << 10 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 0 << 10 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 7 << 11 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 8 << 11 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 0 << 11 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 7 << 12 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 8 << 12 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 0 << 12 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 7 << 13 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 8 << 13 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 0 << 13 << 9;
    QTest::newRow("less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 0 << 0 << 9 << 9;
}

QTEST_APPLESS_MAIN(CapacityTests)

#include "tst_capacitytests.moc"
