#include <QtTest>

#include <vector>
#include <tuple>

#include "testutils.h"
#include "tst_capacitytests.h"
#include "tst_resizingtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(TripleSizeTypeTuple) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(TripleSizeTypeTupleArray) // same here
Q_DECLARE_METATYPE(StringMatrix)
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class CapacityTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testIntMatrixCapacityWithInitListConstructor();
    void testIntMatrixCapacityWithIdenticalMatrixConstructor();
    void testIntMatrixCapacityWithDiagonalMatrixConstructor();
    void testIntMatrixCapacityWithCopyConstructor();
    void testIntMatrixCapacityWithMoveConstructor();
    void testIntMatrixCapacityWithCopyAssignmentOperator();
    void testIntMatrixCapacityWithMoveAssignmentOperator();
    void testIntMatrixCapacityWithTranspose();
    void testIntMatrixCapacityWithResizeWithoutFillingInNewValues();
    void testIntMatrixCapacityWithResizeAndFillInNewValues();
    void testIntMatrixCapacityWithInsertRow();
    void testIntMatrixCapacityWithInsertColumn();
    void testIntMatrixCapacityWithEraseRow();
    void testIntMatrixCapacityWithEraseColumn();
    void testIntMatrixCapacityWithCatByRow();
    void testIntMatrixCapacityWithCatByColumn();
    void testIntMatrixCapacityWithSplitByRow();
    void testIntMatrixCapacityWithSplitByColumn();
    void testIntMatrixCapacityWithResizeAndEraseRowAndOrColumn(); // combined IntMatrix test (resize + erase row/column)

    void testStringMatrixCapacityWithInitListConstructor();
    void testStringMatrixCapacityWithIdenticalMatrixConstructor();
    void testStringMatrixCapacityWithDiagonalMatrixConstructor();
    void testStringMatrixCapacityWithCopyConstructor();
    void testStringMatrixCapacityWithMoveConstructor();
    void testStringMatrixCapacityWithCopyAssignmentOperator();
    void testStringMatrixCapacityWithMoveAssignmentOperator();
    void testStringMatrixCapacityWithTranspose();
    void testStringMatrixCapacityWithResizeWithoutFillingInNewValues();
    void testStringMatrixCapacityWithResizeAndFillInNewValues();
    void testStringMatrixCapacityWithInsertRow();
    void testStringMatrixCapacityWithInsertColumn();
    void testStringMatrixCapacityWithEraseRow();
    void testStringMatrixCapacityWithEraseColumn();
    void testStringMatrixCapacityWithCatByRow();
    void testStringMatrixCapacityWithCatByColumn();
    void testStringMatrixCapacityWithSplitByRow();
    void testStringMatrixCapacityWithSplitByColumn();
    void testStringMatrixCapacityWithResizeAndEraseRowAndOrColumn(); // combined StringMatrix test (resize + erase row/column)

    // test data
    void testIntMatrixCapacityWithIdenticalMatrixConstructor_data();
    void testIntMatrixCapacityWithDiagonalMatrixConstructor_data();
    void testIntMatrixCapacityWithCopyConstructor_data();
    void testIntMatrixCapacityWithMoveConstructor_data();
    void testIntMatrixCapacityWithCopyAssignmentOperator_data();
    void testIntMatrixCapacityWithMoveAssignmentOperator_data();
    void testIntMatrixCapacityWithTranspose_data();
    void testIntMatrixCapacityWithResizeWithoutFillingInNewValues_data();
    void testIntMatrixCapacityWithResizeAndFillInNewValues_data();
    void testIntMatrixCapacityWithInsertRow_data();
    void testIntMatrixCapacityWithInsertColumn_data();
    void testIntMatrixCapacityWithEraseRow_data();
    void testIntMatrixCapacityWithEraseColumn_data();
    void testIntMatrixCapacityWithCatByRow_data();
    void testIntMatrixCapacityWithCatByColumn_data();
    void testIntMatrixCapacityWithSplitByRow_data();
    void testIntMatrixCapacityWithSplitByColumn_data();
    void testIntMatrixCapacityWithResizeAndEraseRowAndOrColumn_data();

    void testStringMatrixCapacityWithIdenticalMatrixConstructor_data();
    void testStringMatrixCapacityWithDiagonalMatrixConstructor_data();
    void testStringMatrixCapacityWithCopyConstructor_data();
    void testStringMatrixCapacityWithMoveConstructor_data();
    void testStringMatrixCapacityWithCopyAssignmentOperator_data();
    void testStringMatrixCapacityWithMoveAssignmentOperator_data();
    void testStringMatrixCapacityWithTranspose_data();
    void testStringMatrixCapacityWithResizeWithoutFillingInNewValues_data();
    void testStringMatrixCapacityWithResizeAndFillInNewValues_data();
    void testStringMatrixCapacityWithInsertRow_data();
    void testStringMatrixCapacityWithInsertColumn_data();
    void testStringMatrixCapacityWithEraseRow_data();
    void testStringMatrixCapacityWithEraseColumn_data();
    void testStringMatrixCapacityWithCatByRow_data();
    void testStringMatrixCapacityWithCatByColumn_data();
    void testStringMatrixCapacityWithSplitByRow_data();
    void testStringMatrixCapacityWithSplitByColumn_data();
    void testStringMatrixCapacityWithResizeAndEraseRowAndOrColumn_data();

private:
    // test data helper methods
    void _buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable();
    void _buildIntMatrixCapacityWithAssignmentOperatorsTestingTable();
    void _buildIntMatrixCapacityWithResizeTestingTable();

    void _buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable();
    void _buildStringMatrixCapacityWithAssignmentOperatorsTestingTable();
    void _buildStringMatrixCapacityWithResizeTestingTable();

    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;

    StringMatrix mPrimaryStringMatrix;
    StringMatrix mSecondaryStringMatrix;
};

void CapacityTests::testIntMatrixCapacityWithInitListConstructor()
{
    {
        IntMatrix matrix{3, 4, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 3, 5);
    }

    {
        IntMatrix matrix{4, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 5, 3);
    }

    {
        IntMatrix matrix{8, 10, {
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0
                                }};

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 10, 12);
    }

    {
        IntMatrix matrix{10, 8, {
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
                                }};

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 12, 10);
    }
}

void CapacityTests::testIntMatrixCapacityWithIdenticalMatrixConstructor()
{
    TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(int);
}

void CapacityTests::testIntMatrixCapacityWithDiagonalMatrixConstructor()
{
    TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(int);
}

void CapacityTests::testIntMatrixCapacityWithCopyConstructor()
{
    TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(int);
}

void CapacityTests::testIntMatrixCapacityWithMoveConstructor()
{
    TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(int);
}

void CapacityTests::testIntMatrixCapacityWithCopyAssignmentOperator()
{
    TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(int);
}

void CapacityTests::testIntMatrixCapacityWithMoveAssignmentOperator()
{
    TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(int);
}

void CapacityTests::testIntMatrixCapacityWithTranspose()
{
    TEST_CAPACITY_WITH_TRANSPOSE(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

/* In addition to testing resulting capacity a consistency check (size and retained element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CapacityTests::testIntMatrixCapacityWithResizeWithoutFillingInNewValues()
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

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(mSecondaryIntMatrix, mPrimaryIntMatrix.getNrOfRows(), mPrimaryIntMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

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

/* In addition to testing resulting capacity a consistency check (size and element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void CapacityTests::testIntMatrixCapacityWithResizeAndFillInNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

void CapacityTests::testIntMatrixCapacityWithInsertRow()
{
    TEST_CAPACITY_WITH_INSERT_ROW(int);
}

void CapacityTests::testIntMatrixCapacityWithInsertColumn()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN(int);
}

void CapacityTests::testIntMatrixCapacityWithEraseRow()
{
    TEST_CAPACITY_WITH_ERASE_ROW(int);
}

void CapacityTests::testIntMatrixCapacityWithEraseColumn()
{
    TEST_CAPACITY_WITH_ERASE_COLUMN(int);
}

void CapacityTests::testIntMatrixCapacityWithCatByRow()
{
    TEST_CAPACITY_WITH_CAT_BY_ROW(int);
}

void CapacityTests::testIntMatrixCapacityWithCatByColumn()
{
    TEST_CAPACITY_WITH_CAT_BY_COLUMN(int);
}

void CapacityTests::testIntMatrixCapacityWithSplitByRow()
{
    TEST_CAPACITY_WITH_SPLIT_BY_ROW(int);
}

void CapacityTests::testIntMatrixCapacityWithSplitByColumn()
{
    TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(int);
}

void CapacityTests::testIntMatrixCapacityWithResizeAndEraseRowAndOrColumn()
{
    TEST_CAPACITY_WITH_REZIZE_AND_ERASE_ROW_AND_OR_COLUMN(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

void CapacityTests::testStringMatrixCapacityWithInitListConstructor()
{
    {
        StringMatrix matrix{3, 4, {"Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 3, 5);
    }

    {
        StringMatrix matrix{4, 3, {"Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 5, 3);
    }

    {
        StringMatrix matrix{8, 10, {
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"
                                   }};

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 10, 12);
    }

    {
        StringMatrix matrix{10, 8, {
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value",
                                        "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"
                                   }};

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 12, 10);
    }
}

void CapacityTests::testStringMatrixCapacityWithIdenticalMatrixConstructor()
{
    TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithDiagonalMatrixConstructor()
{
    TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithCopyConstructor()
{
    TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithMoveConstructor()
{
    TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithCopyAssignmentOperator()
{
    TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithMoveAssignmentOperator()
{
    TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(std::string);
}

void CapacityTests::testStringMatrixCapacityWithTranspose()
{
    TEST_CAPACITY_WITH_TRANSPOSE(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

/* Unlike the integer matrix scenario here it is possible to perform the consistency check by comparing the two resized matrixes (==)
   as the default values of the new elements are well determined */
void CapacityTests::testStringMatrixCapacityWithResizeWithoutFillingInNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, resizeRowsCount);
    QFETCH(StringMatrixSizeType, resizeColumnsCount);
    QFETCH(StringMatrixSizeType, requestedRowCapacity);
    QFETCH(StringMatrixSizeType, requestedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);

    mPrimaryStringMatrix = matrix;
    mSecondaryStringMatrix = mPrimaryStringMatrix;

    mPrimaryStringMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryStringMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(mSecondaryStringMatrix, mPrimaryStringMatrix.getNrOfRows(), mPrimaryStringMatrix.getNrOfColumns(), expectedRowCapacity, expectedColumnCapacity);

    QVERIFY2(mSecondaryStringMatrix == mPrimaryStringMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");
}

/* Same way to perform consistency check as for integer matrix scenario */
void CapacityTests::testStringMatrixCapacityWithResizeAndFillInNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void CapacityTests::testStringMatrixCapacityWithInsertRow()
{
    TEST_CAPACITY_WITH_INSERT_ROW(std::string);
}

void CapacityTests::testStringMatrixCapacityWithInsertColumn()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN(std::string);
}

void CapacityTests::testStringMatrixCapacityWithEraseRow()
{
    TEST_CAPACITY_WITH_ERASE_ROW(std::string);
}

void CapacityTests::testStringMatrixCapacityWithEraseColumn()
{
    TEST_CAPACITY_WITH_ERASE_COLUMN(std::string);
}

void CapacityTests::testStringMatrixCapacityWithCatByRow()
{
    TEST_CAPACITY_WITH_CAT_BY_ROW(std::string);
}

void CapacityTests::testStringMatrixCapacityWithCatByColumn()
{
    TEST_CAPACITY_WITH_CAT_BY_COLUMN(std::string);
}

void CapacityTests::testStringMatrixCapacityWithSplitByRow()
{
    TEST_CAPACITY_WITH_SPLIT_BY_ROW(std::string);
}

void CapacityTests::testStringMatrixCapacityWithSplitByColumn()
{
    TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(std::string);
}

void CapacityTests::testStringMatrixCapacityWithResizeAndEraseRowAndOrColumn()
{
    TEST_CAPACITY_WITH_REZIZE_AND_ERASE_ROW_AND_OR_COLUMN(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void CapacityTests::testIntMatrixCapacityWithIdenticalMatrixConstructor_data()
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

void CapacityTests::testIntMatrixCapacityWithDiagonalMatrixConstructor_data()
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

void CapacityTests::testIntMatrixCapacityWithCopyConstructor_data()
{
    _buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithMoveConstructor_data()
{
    _buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithCopyAssignmentOperator_data()
{
    _buildIntMatrixCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithMoveAssignmentOperator_data()
{
    _buildIntMatrixCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithTranspose_data()
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

void CapacityTests::testIntMatrixCapacityWithResizeWithoutFillingInNewValues_data()
{
    _buildIntMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithResizeAndFillInNewValues_data()
{
    _buildIntMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithInsertRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("inserted row value NOT set") << IntMatrix{3, 4, -2} << 1 << 5 << 6 << 5 << false;
    QTest::newRow("inserted row value set") << IntMatrix{3, 4, -2} << 1 << 5 << 6 << 5 << true;
    QTest::newRow("inserted row value NOT set") << IntMatrix{6, 5, -2} << 3 << 5 << 7 << 6 << false;
    QTest::newRow("inserted row value set") << IntMatrix{6, 5, -2} << 3 << 5 << 7 << 6 << true;
    QTest::newRow("inserted row value NOT set") << IntMatrix{8, 2, -2} << 5 << 5 << 10 << 2 << false;
    QTest::newRow("inserted row value set") << IntMatrix{8, 2, -2} << 5 << 5 << 10 << 2 << true;
}

void CapacityTests::testIntMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("inserted column value NOT set") << IntMatrix{5, 3, 4} << 1 << 1 << 6 << 6 << false;
    QTest::newRow("inserted column value set") << IntMatrix{5, 3, 4} << 1 << 1 << 6 << 6 << true;
    QTest::newRow("inserted column value NOT set") << IntMatrix{5, 7, 4} << 1 << 1 << 6 << 8 << false;
    QTest::newRow("inserted column value set") << IntMatrix{5, 7, 4} << 1 << 1 << 6 << 8 << true;
    QTest::newRow("inserted column value NOT set") << IntMatrix{5, 14, 4} << 1 << 1 << 6 << 17 << false;
    QTest::newRow("inserted column value set") << IntMatrix{5, 14, 4} << 1 << 1 << 6 << 17 << true;
}

void CapacityTests::testIntMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedRowAndExpectedCapacity");

    QTest::newRow("less rows than columns") << IntMatrix{3, 4, -2} << TripleSizeTypeTupleArray{{1, 3, 5}, {1, 3, 5}, {0, 0, 0}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, -2} << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 2, 5}, {0, 0, 0}};
    QTest::newRow("more rows than columns") << IntMatrix{7, 5, -2} << TripleSizeTypeTupleArray{{1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 4, 6}, {1, 2, 6}, {0, 0, 0}};
}

void CapacityTests::testIntMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedColumnAndExpectedCapacity");

    QTest::newRow("less columns than rows") << IntMatrix{4, 3, 4} << TripleSizeTypeTupleArray{{1, 5, 3}, {1, 5, 3}, {0, 0, 0}};
    QTest::newRow("square matrix") << IntMatrix{4, 4, 4} << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 5, 2}, {0, 0, 0}};
    QTest::newRow("more columns than rows") << IntMatrix{5, 7, 4} << TripleSizeTypeTupleArray{{1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 4}, {1, 6, 2}, {0, 0, 0}};
}

void CapacityTests::testIntMatrixCapacityWithCatByRow_data()
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
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 7 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 8 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 9 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 11 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 11 << 8 << 10 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 12 << 8 << 11 << 8;

    // column capacity too
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 9 << 11 << 8;

    // additional tests
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{7, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{10, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;

    // empty matrix concatenation
    QTest::newRow("scenario: source both") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0;
}

void CapacityTests::testIntMatrixCapacityWithCatByColumn_data()
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
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 7 << 8 << 10;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 8 << 8 << 10;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 9 << 8 << 10;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 11 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 11 << 8 << 10;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 12 << 8 << 11;

    // row capacity too
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 12 << 8 << 11;

    // additional tests
    QTest::newRow("scenario: all different") << IntMatrix{} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{5, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{5, 10, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << IntMatrix{6, 6, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;

    // empty matrix concatenation
    QTest::newRow("scenario: source both") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("scenario: all different") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0;
}

void CapacityTests::testIntMatrixCapacityWithSplitByRow_data()
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

void CapacityTests::testIntMatrixCapacityWithSplitByColumn_data()
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

void CapacityTests::testIntMatrixCapacityWithResizeAndEraseRowAndOrColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<IntMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("erasedRowNr");
    QTest::addColumn<IntMatrixSizeType>("erasedColumnNr");
    QTest::addColumn<bool>("shouldEraseColumnBeforeRow");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 9 << 2 << -1 << false << 12 << 9;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 8 << 2 << -1 << false << 12 << 8;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 7 << 2 << -1 << false << 12 << 7;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 6 << 2 << -1 << false << 12 << 6;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 5 << 2 << -1 << false << 12 << 6;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 4 << 2 << -1 << false << 23 << 6;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 3 << 2 << -1 << false << 20 << 6;
    QTest::newRow("oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 2 << 2 << -1 << false << 18 << 6;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 9 << -1 << 1 << false << 45 << 9;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 8 << -1 << 1 << false << 29 << 8;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 7 << -1 << 1 << false << 28 << 7;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 6 << -1 << 1 << false << 27 << 6;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 5 << -1 << 1 << false << 24 << 6;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 4 << -1 << 1 << false << 23 << 6;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 3 << -1 << 1 << false << 20 << 6;
    QTest::newRow("oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 2 << -1 << 1 << false << 18 << 6;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << -1 << false << 12 << 41;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << -1 << false << 12 << 25;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << -1 << false << 12 << 24;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << -1 << false << 12 << 23;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << -1 << false << 12 << 20;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << -1 << false << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << -1 << false << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << -1 << false << 18 << 14;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << 1 << false << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << 1 << false << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << 1 << false << 18 << 14;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << 1 << true << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << 1 << true << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << 1 << true << 18 << 14;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 9 << 45 << -1 << 2 << false << 9 << 12;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 8 << 29 << -1 << 2 << false << 8 << 12;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 7 << 28 << -1 << 2 << false << 7 << 12;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 6 << 27 << -1 << 2 << false << 6 << 12;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 5 << 24 << -1 << 2 << false << 6 << 12;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 4 << 23 << -1 << 2 << false << 6 << 23;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 3 << 20 << -1 << 2 << false << 6 << 20;
    QTest::newRow("oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 2 << 18 << -1 << 2 << false << 6 << 18;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 9 << 45 << 1 << -1 << false << 9 << 45;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 8 << 29 << 1 << -1 << false << 8 << 29;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 7 << 28 << 1 << -1 << false << 7 << 28;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 6 << 27 << 1 << -1 << false << 6 << 27;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 5 << 24 << 1 << -1 << false << 6 << 24;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 4 << 23 << 1 << -1 << false << 6 << 23;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 3 << 20 << 1 << -1 << false << 6 << 20;
    QTest::newRow("oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 2 << 18 << 1 << -1 << false << 6 << 18;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << -1 << 2 << false << 41 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << -1 << 2 << false << 25 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << -1 << 2 << false << 24 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << -1 << 2 << false << 23 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << -1 << 2 << false << 20 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << -1 << 2 << false << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << -1 << 2 << false << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << -1 << 2 << false << 14 << 18;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << 1 << 2 << true << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << 1 << 2 << true << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << 1 << 2 << true << 14 << 18;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << 1 << 2 << false << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << 1 << 2 << false << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << 1 << 2 << false << 14 << 18;
}

void CapacityTests::testStringMatrixCapacityWithIdenticalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("small size matrix") << 3 << 4 << std::string{"Value1"} << 3 << 5;
    QTest::newRow("small size matrix") << 4 << 3 << std::string{"Value1"} << 5 << 3;
    QTest::newRow("large size matrix") << 25 << 20 << std::string{"Value2"} << 31 << 25;
    QTest::newRow("large size matrix") << 20 << 25 << std::string{"Value2"} << 25 << 31;
}

void CapacityTests::testStringMatrixCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<std::string>("nonDiagonalValue");
    QTest::addColumn<std::string>("diagonalValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowColumnCapacity");

    QTest::newRow("small size matrix") << 3 << std::string{"Value1"} << std::string{"Value2"} << 3;
    QTest::newRow("small size matrix") << 4 << std::string{"Value1"} << std::string{"Value2"} << 5;
    QTest::newRow("medium size matrix") << 8 << std::string{"Value1"} << std::string{"Value2"} << 10;
    QTest::newRow("medium size matrix") << 10 << std::string{"Value1"} << std::string{"Value2"} << 12;
}

void CapacityTests::testStringMatrixCapacityWithCopyConstructor_data()
{
    _buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithMoveConstructor_data()
{
    _buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithCopyAssignmentOperator_data()
{
    _buildStringMatrixCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithMoveAssignmentOperator_data()
{
    _buildStringMatrixCapacityWithAssignmentOperatorsTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithTranspose_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("transposed matrix initially empty") << StringMatrix{3, 4, "Value"} << StringMatrix{} << 5 << 3 << false;
    QTest::newRow("transposed matrix initially empty") << StringMatrix{4, 3, "Value"} << StringMatrix{} << 3 << 5 << false;
    QTest::newRow("transposed matrix initially empty") << StringMatrix{7, 8, "Value"} << StringMatrix{} << 10 << 8 << false;
    QTest::newRow("transposed matrix initially empty") << StringMatrix{8, 7, "Value"} << StringMatrix{} << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 6, "Value"} << 8 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 6, "Value"} << 7 << 10 << false;
    QTest::newRow("transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 7, "Value"} << 8 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 7, "Value"} << 7 << 8 << false;
    QTest::newRow("transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{7, 8, "Value"} << 8 << 10 << false;
    QTest::newRow("matrix transposed to itself") << StringMatrix{3, 3, "Value"} << StringMatrix{3, 3, "Value"} << 3 << 3 << true;
    QTest::newRow("matrix transposed to itself") << StringMatrix{3, 4, "Value"} << StringMatrix{3, 4, "Value"} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << StringMatrix{4, 3, "Value"} << StringMatrix{4, 3, "Value"} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << StringMatrix{4, 4, "Value"} << StringMatrix{4, 4, "Value"} << 5 << 5 << true;
    QTest::newRow("matrix transposed to itself") << StringMatrix{7, 8, "Value"} << StringMatrix{7, 8, "Value"} << 8 << 10 << true;
    QTest::newRow("matrix transposed to itself") << StringMatrix{8, 7, "Value"} << StringMatrix{8, 7, "Value"} << 10 << 8 << true;
}

void CapacityTests::testStringMatrixCapacityWithResizeWithoutFillingInNewValues_data()
{
    _buildStringMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithResizeAndFillInNewValues_data()
{
    _buildStringMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithInsertRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("inserted row value NOT set") << StringMatrix{3, 4, "Value1"} << 1 << std::string{"Value2"} << 6 << 5 << false;
    QTest::newRow("inserted row value set") << StringMatrix{3, 4, "Value1"} << 1 << std::string{"Value2"} << 6 << 5 << true;
    QTest::newRow("inserted row value NOT set") << StringMatrix{6, 5, "Value1"} << 3 << std::string{"Value2"} << 7 << 6 << false;
    QTest::newRow("inserted row value set") << StringMatrix{6, 5, "Value1"} << 3 << std::string{"Value2"} << 7 << 6 << true;
    QTest::newRow("inserted row value NOT set") << StringMatrix{8, 2, "Value1"} << 5 << std::string{"Value2"} << 10 << 2 << false;
    QTest::newRow("inserted row value set") << StringMatrix{8, 2, "Value1"} << 5 << std::string{"Value2"} << 10 << 2 << true;
}

void CapacityTests::testStringMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("inserted column value NOT set") << StringMatrix{5, 3, "Value1"} << 1 << std::string{"Value2"} << 6 << 6 << false;
    QTest::newRow("inserted column value set") << StringMatrix{5, 3, "Value1"} << 1 << std::string{"Value2"} << 6 << 6 << true;
    QTest::newRow("inserted column value NOT set") << StringMatrix{5, 7, "Value1"} << 1 << std::string{"Value2"} << 6 << 8 << false;
    QTest::newRow("inserted column value set") << StringMatrix{5, 7, "Value1"} << 1 << std::string{"Value2"} << 6 << 8 << true;
    QTest::newRow("inserted column value NOT set") << StringMatrix{5, 14, "Value1"} << 1 << std::string{"Value2"} << 6 << 17 << false;
    QTest::newRow("inserted column value set") << StringMatrix{5, 14, "Value1"} << 1 << std::string{"Value2"} << 6 << 17 << true;
}

void CapacityTests::testStringMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedRowAndExpectedCapacity");

    QTest::newRow("less rows than columns") << StringMatrix{3, 4, "Value"} << TripleSizeTypeTupleArray{{1, 3, 5}, {1, 3, 5}, {0, 0, 0}};
    QTest::newRow("square matrix") << StringMatrix{4, 4, "Value"} << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 2, 5}, {0, 0, 0}};
    QTest::newRow("more rows than columns") << StringMatrix{7, 5, "Value"} << TripleSizeTypeTupleArray{{1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 8, 6}, {1, 4, 6}, {1, 2, 6}, {0, 0, 0}};
}

void CapacityTests::testStringMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<TripleSizeTypeTupleArray>("erasedColumnAndExpectedCapacity");

    QTest::newRow("less columns than rows") << StringMatrix{4, 3, "Value"} << TripleSizeTypeTupleArray{{1, 5, 3}, {1, 5, 3}, {0, 0, 0}};
    QTest::newRow("square matrix") << StringMatrix{4, 4, "Value"} << TripleSizeTypeTupleArray{{1, 5, 5}, {1, 5, 5}, {1, 5, 2}, {0, 0, 0}};
    QTest::newRow("more columns than rows") << StringMatrix{5, 7, "Value"} << TripleSizeTypeTupleArray{{1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 8}, {1, 6, 4}, {1, 6, 2}, {0, 0, 0}};
}

void CapacityTests::testStringMatrixCapacityWithCatByRow_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("firstSrcMatrix");
    QTest::addColumn<StringMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 7 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 8 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 9 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 11 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 10 << 8 << 10 << 8;
    QTest::newRow("scenario: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 11 << 8 << 10 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 12 << 8 << 11 << 8;

    // column capacity too
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 9 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 6 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 7 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 8 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 9 << 11 << 8;

    // additional tests
    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{7, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{10, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8;

    // empty matrix concatenation
    QTest::newRow("scenario: source both") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0;
}

void CapacityTests::testStringMatrixCapacityWithCatByColumn_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("firstSrcMatrix");
    QTest::addColumn<StringMatrix>("secondSrcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 7 << 8 << 10;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 8 << 8 << 10;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 9 << 8 << 10;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 11 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 10 << 8 << 10;
    QTest::newRow("scenario: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 11 << 8 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 12 << 8 << 11;

    // row capacity too
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 9 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 10 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 11 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 12 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 12 << 8 << 11;

    // additional tests
    QTest::newRow("scenario: all different") << StringMatrix{} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{5, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{5, 10, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;
    QTest::newRow("scenario: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11;

    // empty matrix concatenation
    QTest::newRow("scenario: source both") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0;
    QTest::newRow("scenario: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0;
}

void CapacityTests::testStringMatrixCapacityWithSplitByRow_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("firstDestMatrix");
    QTest::addColumn<StringMatrix>("secondDestMatrix");
    QTest::addColumn<StringMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 17 << false << 18 << 21 << 8 << 17;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 18 << false << 18 << 21 << 8 << 18;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 7 << 18;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 17 << true << 10 << 17 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 18 << true << 10 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << true << 10 << 17 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << true << 10 << 18 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 18 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << false << 10 << 21 << 8 << 17;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << false << 10 << 21 << 8 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 15, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 7 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 17 << false << 18 << 21 << 10 << 17;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 18 << false << 18 << 21 << 10 << 18;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 18;
    QTest::newRow("scenario: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 17 << true << 8 << 17 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 18 << true << 8 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 7 << 18 << 18 << 21;
    QTest::newRow("scenario: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << true << 8 << 17 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << true << 8 << 18 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 7 << 18 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << false << 8 << 21 << 10 << 17;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << false << 8 << 21 << 10 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 15, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 8 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
    QTest::newRow("scenario: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21;
}

void CapacityTests::testStringMatrixCapacityWithSplitByColumn_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("firstDestMatrix");
    QTest::addColumn<StringMatrix>("secondDestMatrix");
    QTest::addColumn<StringMatrixSizeType>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnCapacity");
    QTest::addColumn<bool>("isFirstDestResized");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacity");

    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 17 << 6 << false << 21 << 18 << 17 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 18 << 6 << false << 21 << 18 << 18 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 7;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << false << 21 << 10 << 17 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << false << 21 << 10 << 18 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 6, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 18 << 7;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 17 << 7 << false << 21 << 18 << 17 << 10;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 18 << 7 << false << 21 << 18 << 18 << 10;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 8;
    QTest::newRow("scenario: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 18;
    QTest::newRow("scenario: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << false << 21 << 8 << 17 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << false << 21 << 8 << 18 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 7, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 18 << 8;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
    QTest::newRow("scenario: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10;
}

void CapacityTests::testStringMatrixCapacityWithResizeAndEraseRowAndOrColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("resizeElementValue");
    QTest::addColumn<StringMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("erasedRowNr");
    QTest::addColumn<StringMatrixSizeType>("erasedColumnNr");
    QTest::addColumn<bool>("shouldEraseColumnBeforeRow");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 9 << 2 << -1 << false << 12 << 9;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 8 << 2 << -1 << false << 12 << 8;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 7 << 2 << -1 << false << 12 << 7;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 6 << 2 << -1 << false << 12 << 6;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 5 << 2 << -1 << false << 12 << 6;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 4 << 2 << -1 << false << 23 << 6;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 3 << 2 << -1 << false << 20 << 6;
    QTest::newRow("oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 2 << 2 << -1 << false << 18 << 6;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 9 << -1 << 1 << false << 45 << 9;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 8 << -1 << 1 << false << 29 << 8;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 7 << -1 << 1 << false << 28 << 7;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 6 << -1 << 1 << false << 27 << 6;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 5 << -1 << 1 << false << 24 << 6;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 4 << -1 << 1 << false << 23 << 6;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 3 << -1 << 1 << false << 20 << 6;
    QTest::newRow("oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 2 << -1 << 1 << false << 18 << 6;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << -1 << false << 12 << 41;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << -1 << false << 12 << 25;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << -1 << false << 12 << 24;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << -1 << false << 12 << 23;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << -1 << false << 12 << 20;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << -1 << false << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << -1 << false << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << -1 << false << 18 << 14;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << 1 << false << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << 1 << false << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << 1 << false << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << 1 << false << 18 << 14;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << 1 << true << 12 << 10;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << 1 << true << 23 << 19;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << 1 << true << 20 << 16;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << 1 << true << 18 << 14;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 9 << 45 << -1 << 2 << false << 9 << 12;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 8 << 29 << -1 << 2 << false << 8 << 12;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 7 << 28 << -1 << 2 << false << 7 << 12;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 6 << 27 << -1 << 2 << false << 6 << 12;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 5 << 24 << -1 << 2 << false << 6 << 12;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 4 << 23 << -1 << 2 << false << 6 << 23;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 3 << 20 << -1 << 2 << false << 6 << 20;
    QTest::newRow("oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 2 << 18 << -1 << 2 << false << 6 << 18;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 9 << 45 << 1 << -1 << false << 9 << 45;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 8 << 29 << 1 << -1 << false << 8 << 29;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 7 << 28 << 1 << -1 << false << 7 << 28;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 6 << 27 << 1 << -1 << false << 6 << 27;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 5 << 24 << 1 << -1 << false << 6 << 24;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 4 << 23 << 1 << -1 << false << 6 << 23;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 3 << 20 << 1 << -1 << false << 6 << 20;
    QTest::newRow("oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 2 << 18 << 1 << -1 << false << 6 << 18;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << -1 << 2 << false << 41 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << -1 << 2 << false << 25 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << -1 << 2 << false << 24 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << -1 << 2 << false << 23 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << -1 << 2 << false << 20 << 12;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << -1 << 2 << false << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << -1 << 2 << false << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << -1 << 2 << false << 14 << 18;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << 1 << 2 << true << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << 1 << 2 << true << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << 1 << 2 << true << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << 1 << 2 << true << 14 << 18;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << 1 << 2 << false << 10 << 12;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << 1 << 2 << false << 19 << 23;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << 1 << 2 << false << 16 << 20;
    QTest::newRow("oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << 1 << 2 << false << 14 << 18;
}

void CapacityTests::_buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable()
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

void CapacityTests::_buildIntMatrixCapacityWithAssignmentOperatorsTestingTable()
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

void CapacityTests::_buildIntMatrixCapacityWithResizeTestingTable()
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

    // empty matrix
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 0 << 1 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 1 << 1 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 2 << 1 << 2;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 3 << 1 << 3;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 0 << 1 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 1 << 1 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 2 << 1 << 2;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 3 << 1 << 3;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 0 << 2 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 1 << 2 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 2 << 2 << 2;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 3 << 2 << 3;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 0 << 3 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 1 << 3 << 1;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 2 << 3 << 2;
    QTest::newRow("more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 3 << 3 << 3;
}

void CapacityTests::_buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("small size matrix") << 3 << 4 << std::string{"Value"} << 3 << 5;
    QTest::newRow("small size matrix") << 4 << 3 << std::string{"Value"} << 5 << 3;
    QTest::newRow("medium size matrix") << 7 << 8 << std::string{"Value"} << 8 << 10;
    QTest::newRow("medium size matrix") << 8 << 7 << std::string{"Value"} << 10 << 8;
}

void CapacityTests::_buildStringMatrixCapacityWithAssignmentOperatorsTestingTable()
{
    QTest::addColumn<StringMatrixSizeType>("srcMatrixRowsCount");
    QTest::addColumn<StringMatrixSizeType>("srcMatrixColumnsCount");
    QTest::addColumn<std::string>("srcMatrixElementValue");
    QTest::addColumn<StringMatrixSizeType>("destMatrixRowsCount");
    QTest::addColumn<StringMatrixSizeType>("destMatrixColumnsCount");
    QTest::addColumn<std::string>("destMatrixElementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("destination matrix initially empty") << 3 << 4 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 3 << 5;
    QTest::newRow("destination matrix initially empty") << 4 << 3 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 5 << 3;
    QTest::newRow("destination matrix initially empty") << 7 << 8 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 8 << 10;
    QTest::newRow("destination matrix initially empty") << 8 << 7 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 10 << 8;
    QTest::newRow("destination matrix initially NOT empty") << 3 << 4 << std::string{"Value1"} << 2 << 3 << std::string{"Value3"} << 3 << 5;
    QTest::newRow("destination matrix initially NOT empty") << 4 << 3 << std::string{"Value1"} << 2 << 3 << std::string{"Value3"} << 5 << 3;
    QTest::newRow("destination matrix initially NOT empty") << 7 << 8 << std::string{"Value1"} << 3 << 4 << std::string{"Value3"} << 8 << 10;
    QTest::newRow("destination matrix initially NOT empty") << 8 << 7 << std::string{"Value1"} << 3 << 4 << std::string{"Value3"} << 10 << 8;
}

void CapacityTests::_buildStringMatrixCapacityWithResizeTestingTable()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("resizeElementValue");
    QTest::addColumn<StringMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");

    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 6 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 7 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 8 << 10 << 8;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 0 << 10 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7;
    QTest::newRow("equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 0 << 0 << 10 << 7;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 7 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 0 << 9 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 7 << 10 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 0 << 10 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8;
    QTest::newRow("less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 0 << 0 << 9 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 6 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 7 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 8 << 9 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 0 << 9 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 6 << 10 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 7 << 10 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 8 << 10 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 0 << 10 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7;
    QTest::newRow("less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 0 << 0 << 9 << 7;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 7 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 8 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 0 << 10 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8;
    QTest::newRow("same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 0 << 0 << 10 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8;
    QTest::newRow("more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 0 << 0 << 11 << 8;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 7 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 8 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 0 << 10 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9;
    QTest::newRow("same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 0 << 0 << 10 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9;
    QTest::newRow("more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 0 << 0 << 11 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7;
    QTest::newRow("more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 0 << 0 << 11 << 7;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 7 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 8 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 9 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 10 << 9 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 11 << 9 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 0 << 9 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 7 << 10 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 8 << 10 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 9 << 10 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 10 << 10 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 11 << 10 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 0 << 10 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9;
    QTest::newRow("less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 0 << 0 << 9 << 9;

    // empty matrix
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 0 << 1 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 1 << 1 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 2 << 1 << 2;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 3 << 1 << 3;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 0 << 1 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 1 << 1 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 2 << 1 << 2;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 3 << 1 << 3;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 0 << 2 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 1 << 2 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 2 << 2 << 2;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 3 << 2 << 3;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 0 << 3 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 1 << 3 << 1;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 2 << 3 << 2;
    QTest::newRow("more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 3 << 3 << 3;
}

QTEST_APPLESS_MAIN(CapacityTests)

#include "tst_capacitytests.moc"
