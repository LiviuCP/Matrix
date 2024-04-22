#include <QtTest>

#include "testutils.h"
#include "tst_capacitytests.h"
#include "tst_resizingtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(FiveSizeTypesTuple) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(FiveSizeTypesTupleArray) // same here
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
    void testIntMatrixCapacityWithResizeWithDefaultNewValues();
    void testIntMatrixCapacityWithResizeAndSetNewValues();
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
    void testStringMatrixCapacityWithResizeWithDefaultNewValues();
    void testStringMatrixCapacityWithResizeAndSetNewValues();
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
    void testIntMatrixCapacityWithResizeWithDefaultNewValues_data();
    void testIntMatrixCapacityWithResizeAndSetNewValues_data();
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
    void testStringMatrixCapacityWithResizeWithDefaultNewValues_data();
    void testStringMatrixCapacityWithResizeAndSetNewValues_data();
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
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 3, 5, 0, 0);
    }

    {
        IntMatrix matrix{4, 3, {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 5, 3, 0, 0);
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 10, 12, 1, 1);
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 12, 10, 1, 1);
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
void CapacityTests::testIntMatrixCapacityWithResizeWithDefaultNewValues()
{
    QFETCH(IntMatrix, matrix);
    QFETCH(IntMatrixSizeType, resizeRowsCount);
    QFETCH(IntMatrixSizeType, resizeColumnsCount);
    QFETCH(IntMatrixSizeType, requestedRowCapacity);
    QFETCH(IntMatrixSizeType, requestedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacity);
    QFETCH(IntMatrixSizeType, expectedColumnCapacity);
    QFETCH(IntMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixSizeType, expectedColumnCapacityOffset);

    mPrimaryIntMatrix = matrix;
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    const IntMatrixSizeType c_RetainedNrOfRows{std::min(resizeRowsCount, mSecondaryIntMatrix.getNrOfRows())};
    const IntMatrixSizeType c_RetainedNrOfColumns{std::min(resizeColumnsCount, mSecondaryIntMatrix.getNrOfColumns())};

    mPrimaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(mSecondaryIntMatrix, mPrimaryIntMatrix.getNrOfRows(), mPrimaryIntMatrix.getNrOfColumns(),
                                               expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

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
void CapacityTests::testIntMatrixCapacityWithResizeAndSetNewValues()
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
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 3, 5, 0, 0);
    }

    {
        StringMatrix matrix{4, 3, {"Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 5, 3, 0, 0);
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 10, 12, 1, 1);
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 12, 10, 1, 1);
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
void CapacityTests::testStringMatrixCapacityWithResizeWithDefaultNewValues()
{
    QFETCH(StringMatrix, matrix);
    QFETCH(StringMatrixSizeType, resizeRowsCount);
    QFETCH(StringMatrixSizeType, resizeColumnsCount);
    QFETCH(StringMatrixSizeType, requestedRowCapacity);
    QFETCH(StringMatrixSizeType, requestedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacity);
    QFETCH(StringMatrixSizeType, expectedColumnCapacity);
    QFETCH(StringMatrixSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixSizeType, expectedColumnCapacityOffset);

    mPrimaryStringMatrix = matrix;
    mSecondaryStringMatrix = mPrimaryStringMatrix;

    mPrimaryStringMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryStringMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(mSecondaryStringMatrix, mPrimaryStringMatrix.getNrOfRows(), mPrimaryStringMatrix.getNrOfColumns(),
                                               expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    QVERIFY2(mSecondaryStringMatrix == mPrimaryStringMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");
}

/* Same way to perform consistency check as for integer matrix scenario */
void CapacityTests::testStringMatrixCapacityWithResizeAndSetNewValues()
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << 4 << -5 << 3 << 5 << 0 << 0;
    QTest::newRow("2: small size matrix") << 4 << 3 << -5 << 5 << 3 << 0 << 0;
    QTest::newRow("3: large size matrix") << 25 << 20 << -2 << 31 << 25 << 3 << 2;
    QTest::newRow("4: large size matrix") << 20 << 25 << -2 << 25 << 31 << 2 << 3;
}

void CapacityTests::testIntMatrixCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << -2 << -3 << 3 << 0;
    QTest::newRow("2: small size matrix") << 4 << -2 << -3 << 5 << 0;
    QTest::newRow("3: medium size matrix") << 8 << -2 << -3 << 10 << 1;
    QTest::newRow("4: medium size matrix") << 10 << -2 << -3 << 12 << 1;
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << IntMatrix{3, 4, 2} << IntMatrix{} << 5 << 3 << 0 << 0 << false;
    QTest::newRow("2: transposed matrix initially empty") << IntMatrix{4, 3, 2} << IntMatrix{} << 3 << 5 << 0 << 0 << false;
    QTest::newRow("3: transposed matrix initially empty") << IntMatrix{7, 8, 2} << IntMatrix{} << 10 << 8 << 1 << 0 << false;
    QTest::newRow("4: transposed matrix initially empty") << IntMatrix{8, 7, 2} << IntMatrix{} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("5: transposed matrix initially empty") << IntMatrix{20, 25, 2} << IntMatrix{} << 31 << 25 << 3 << 2 << false;
    QTest::newRow("6: transposed matrix initially empty") << IntMatrix{25, 20, 2} << IntMatrix{} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 6, 2} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 6, 2} << 7 << 10 << 0 << 1 << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 7, 2} << 8 << 8 << 0 << 0 << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 7, 2} << 7 << 8 << 0 << 0 << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{7, 8, 2} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 19, 2} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 19, 2} << 20 << 31 << 0 << 3 << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 20, 2} << 25 << 25 << 2 << 0 << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 20, 2} << 20 << 25 << 0 << 0 << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 25, 2} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 25, 2} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 25, 2} << 20 << 31 << 0 << 3 << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 19, 2} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 20, 2} << 25 << 25 << 2 << 0 << false;
    QTest::newRow("21: matrix transposed to itself") << IntMatrix{3, 3, 2} << IntMatrix{3, 3, 2} << 3 << 3 << 0 << 0 << true;
    QTest::newRow("22: matrix transposed to itself") << IntMatrix{3, 4, 2} << IntMatrix{3, 4, 2} << 5 << 5 << 0 << 1 << true;
    QTest::newRow("23: matrix transposed to itself") << IntMatrix{4, 3, 2} << IntMatrix{4, 3, 2} << 5 << 5 << 1 << 0 << true;
    QTest::newRow("24: matrix transposed to itself") << IntMatrix{4, 4, 2} << IntMatrix{4, 4, 2} << 5 << 5 << 0 << 0 << true;
    QTest::newRow("25: matrix transposed to itself") << IntMatrix{7, 8, 2} << IntMatrix{7, 8, 2} << 8 << 10 << 0 << 1 << true;
    QTest::newRow("26: matrix transposed to itself") << IntMatrix{8, 7, 2} << IntMatrix{8, 7, 2} << 10 << 8 << 1 << 0 << true;
    QTest::newRow("27: matrix transposed to itself") << IntMatrix{20, 25, 2} << IntMatrix{20, 25, 2} << 25 << 31 << 0 << 5 << true;
    QTest::newRow("28: matrix transposed to itself") << IntMatrix{25, 20, 2} << IntMatrix{25, 20, 2} << 31 << 25 << 5 << 0 << true;
    QTest::newRow("29: matrix transposed to itself") << IntMatrix{25, 25, 2} << IntMatrix{25, 25, 2} << 31 << 31 << 3 << 3 << true;
    QTest::newRow("30: matrix transposed to itself") << IntMatrix{20, 26, 2} << IntMatrix{20, 26, 2} << 32 << 32 << 3 << 6 << true;
    QTest::newRow("31: matrix transposed to itself") << IntMatrix{26, 20, 2} << IntMatrix{26, 20, 2} << 32 << 32 << 6 << 3 << true;
}

void CapacityTests::testIntMatrixCapacityWithResizeWithDefaultNewValues_data()
{
    _buildIntMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testIntMatrixCapacityWithResizeAndSetNewValues_data()
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("1: inserted row value NOT set") << IntMatrix{3, 4, -2} << 1 << 5 << 6 << 5 << 1 << 0 << false;
    QTest::newRow("2: inserted row value set") << IntMatrix{3, 4, -2} << 1 << 5 << 6 << 5 << 1 << 0 << true;
    QTest::newRow("3: inserted row value NOT set") << IntMatrix{6, 5, -2} << 3 << 5 << 7 << 6 << 0 << 0 << false;
    QTest::newRow("4: inserted row value set") << IntMatrix{6, 5, -2} << 3 << 5 << 7 << 6 << 0 << 0 << true;
    QTest::newRow("5: inserted row value NOT set") << IntMatrix{8, 2, -2} << 5 << 5 << 10 << 2 << 1 << 0 << false;
    QTest::newRow("6: inserted row value set") << IntMatrix{8, 2, -2} << 5 << 5 << 10 << 2 << 1 << 0 << true;
    QTest::newRow("7: inserted row value NOT set") << IntMatrix{25, 20, -2} << 0 << 5 << 31 << 25 << 2 << 2 << false;
    QTest::newRow("8: inserted row value set") << IntMatrix{25, 20, -2} << 0 << 5 << 31 << 25 << 2 << 2 << true;
    QTest::newRow("9: inserted row value NOT set") << IntMatrix{25, 20, -2} << 11 << 5 << 31 << 25 << 2 << 2 << false;
    QTest::newRow("10: inserted row value set") << IntMatrix{25, 20, -2} << 11 << 5 << 31 << 25 << 2 << 2 << true;
    QTest::newRow("11: inserted row value NOT set") << IntMatrix{25, 20, -2} << 25 << 5 << 31 << 25 << 3 << 2 << false;
    QTest::newRow("12: inserted row value set") << IntMatrix{25, 20, -2} << 25 << 5 << 31 << 25 << 3 << 2 << true;
}

void CapacityTests::testIntMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("1: inserted column value NOT set") << IntMatrix{5, 3, 4} << 1 << 1 << 6 << 6 << 0 << 1 << false;
    QTest::newRow("2: inserted column value set") << IntMatrix{5, 3, 4} << 1 << 1 << 6 << 6 << 0 << 1 << true;
    QTest::newRow("3: inserted column value NOT set") << IntMatrix{5, 7, 4} << 1 << 1 << 6 << 8 << 0 << 0 << false;
    QTest::newRow("4: inserted column value set") << IntMatrix{5, 7, 4} << 1 << 1 << 6 << 8 << 0 << 0 << true;
    QTest::newRow("5: inserted column value NOT set") << IntMatrix{5, 14, 4} << 1 << 1 << 6 << 17 << 0 << 0 << false;
    QTest::newRow("6: inserted column value set") << IntMatrix{5, 14, 4} << 1 << 1 << 6 << 17 << 0 << 0 << true;
    QTest::newRow("7: inserted column value NOT set") << IntMatrix{20, 25, 4} << 0 << 1 << 25 << 31 << 2 << 2 << false;
    QTest::newRow("8: inserted column value set") << IntMatrix{20, 25, 4} << 0 << 1 << 25 << 31 << 2 << 2 << true;
    QTest::newRow("9: inserted column value NOT set") << IntMatrix{20, 25, 4} << 14 << 1 << 25 << 31 << 2 << 3 << false;
    QTest::newRow("10: inserted column value set") << IntMatrix{20, 25, 4} << 14 << 1 << 25 << 31 << 2 << 3 << true;
    QTest::newRow("11: inserted column value NOT set") << IntMatrix{20, 25, 4} << 25 << 1 << 25 << 31 << 2 << 3 << false;
    QTest::newRow("12: inserted column value set") << IntMatrix{20, 25, 4} << 25 << 1 << 25 << 31 << 2 << 3 << true;
}

void CapacityTests::testIntMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<FiveSizeTypesTupleArray>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << IntMatrix{3, 4, -2} << FiveSizeTypesTupleArray{{1, 3, 5, 0, 0}, {1, 3, 5, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("2: less rows than columns") << IntMatrix{10, 15, -2} << FiveSizeTypesTupleArray{{1, 12, 18, 2, 1}, {1, 12, 18, 3, 1}, {1, 12, 18, 4, 1}, {1, 12, 18, 5, 1}, {1, 12, 18, 6, 1}, {1, 12, 18, 7, 1}, {1, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("3: less rows than columns") << IntMatrix{10, 15, -2} << FiveSizeTypesTupleArray{{8, 12, 18, 1, 1}, {7, 12, 18, 1, 1}, {6, 12, 18, 1, 1}, {5, 12, 18, 1, 1}, {4, 12, 18, 1, 1}, {3, 12, 18, 1, 1}, {2, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {0, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("4: less rows than columns") << IntMatrix{10, 15, -2} << FiveSizeTypesTupleArray{{0, 12, 18, 2, 1}, {8, 12, 18, 2, 1}, {0, 12, 18, 3, 1}, {6, 12, 18, 3, 1}, {0, 12, 18, 4, 1}, {4, 12, 18, 4, 1}, {0, 6, 18, 1, 1}, {2, 6, 18, 1, 1}, {0, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("5: less rows than columns") << IntMatrix{10, 15, -2} << FiveSizeTypesTupleArray{{9, 12, 18, 1, 1}, {0, 12, 18, 2, 1}, {7, 12, 18, 2, 1}, {0, 12, 18, 3, 1}, {5, 12, 18, 3, 1}, {0, 12, 18, 4, 1}, {3, 6, 18, 1, 1}, {0, 6, 18, 2, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("6: less rows than columns") << IntMatrix{10, 15, -2} << FiveSizeTypesTupleArray{{3, 12, 18, 2, 1}, {6, 12, 18, 2, 1}, {7, 12, 18, 2, 1}, {2, 12, 18, 3, 1}, {1, 12, 18, 4, 1}, {2, 12, 18, 4, 1}, {0, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("7: square matrix") << IntMatrix{4, 4, -2} << FiveSizeTypesTupleArray{{1, 5, 5, 1, 0}, {1, 5, 5, 1, 0}, {1, 2, 5, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("8: square matrix") << IntMatrix{10, 10, -2} << FiveSizeTypesTupleArray{{1, 12, 12, 2, 1}, {1, 12, 12, 3, 1}, {1, 12, 12, 4, 1}, {1, 12, 12, 5, 1}, {1, 12, 12, 6, 1}, {1, 12, 12, 7, 1}, {1, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("9: square matrix") << IntMatrix{10, 10, -2} << FiveSizeTypesTupleArray{{8, 12, 12, 1, 1}, {7, 12, 12, 1, 1}, {6, 12, 12, 1, 1}, {5, 12, 12, 1, 1}, {4, 12, 12, 1, 1}, {3, 12, 12, 1, 1}, {2, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {0, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("10: square matrix") << IntMatrix{10, 10, -2} << FiveSizeTypesTupleArray{{0, 12, 12, 2, 1}, {8, 12, 12, 2, 1}, {0, 12, 12, 3, 1}, {6, 12, 12, 3, 1}, {0, 12, 12, 4, 1}, {4, 12, 12, 4, 1}, {0, 6, 12, 1, 1}, {2, 6, 12, 1, 1}, {0, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("11: square matrix") << IntMatrix{10, 10, -2} << FiveSizeTypesTupleArray{{9, 12, 12, 1, 1}, {0, 12, 12, 2, 1}, {7, 12, 12, 2, 1}, {0, 12, 12, 3, 1}, {5, 12, 12, 3, 1}, {0, 12, 12, 4, 1}, {3, 6, 12, 1, 1}, {0, 6, 12, 2, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("12: square matrix") << IntMatrix{10, 10, -2} << FiveSizeTypesTupleArray{{3, 12, 12, 2, 1}, {6, 12, 12, 2, 1}, {7, 12, 12, 2, 1}, {2, 12, 12, 3, 1}, {1, 12, 12, 4, 1}, {2, 12, 12, 4, 1}, {0, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("13: more rows than columns") << IntMatrix{7, 5, -2} << FiveSizeTypesTupleArray{{1, 8, 6, 1, 0}, {1, 8, 6, 2, 0}, {1, 8, 6, 3, 0}, {1, 8, 6, 4, 0}, {1, 4, 6, 1, 0}, {1, 2, 6, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("14: more rows than columns") << IntMatrix{10, 9, -2} << FiveSizeTypesTupleArray{{1, 12, 11, 2, 1}, {1, 12, 11, 3, 1}, {1, 12, 11, 4, 1}, {1, 12, 11, 5, 1}, {1, 12, 11, 6, 1}, {1, 12, 11, 7, 1}, {1, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("15: more rows than columns") << IntMatrix{10, 9, -2} << FiveSizeTypesTupleArray{{8, 12, 11, 1, 1}, {7, 12, 11, 1, 1}, {6, 12, 11, 1, 1}, {5, 12, 11, 1, 1}, {4, 12, 11, 1, 1}, {3, 12, 11, 1, 1}, {2, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {0, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("16: more rows than columns") << IntMatrix{10, 9, -2} << FiveSizeTypesTupleArray{{0, 12, 11, 2, 1}, {8, 12, 11, 2, 1}, {0, 12, 11, 3, 1}, {6, 12, 11, 3, 1}, {0, 12, 11, 4, 1}, {4, 12, 11, 4, 1}, {0, 6, 11, 1, 1}, {2, 6, 11, 1, 1}, {0, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("17: more rows than columns") << IntMatrix{10, 9, -2} << FiveSizeTypesTupleArray{{9, 12, 11, 1, 1}, {0, 12, 11, 2, 1}, {7, 12, 11, 2, 1}, {0, 12, 11, 3, 1}, {5, 12, 11, 3, 1}, {0, 12, 11, 4, 1}, {3, 6, 11, 1, 1}, {0, 6, 11, 2, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("18: more rows than columns") << IntMatrix{10, 9, -2} << FiveSizeTypesTupleArray{{3, 12, 11, 2, 1}, {6, 12, 11, 2, 1}, {7, 12, 11, 2, 1}, {2, 12, 11, 3, 1}, {1, 12, 11, 4, 1}, {2, 12, 11, 4, 1}, {0, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
}

void CapacityTests::testIntMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<FiveSizeTypesTupleArray>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << IntMatrix{4, 3, 4} << FiveSizeTypesTupleArray{{1, 5, 3, 0, 0}, {1, 5, 3, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("2: less columns than rows") << IntMatrix{15, 10, 4} << FiveSizeTypesTupleArray{{1, 18, 12, 1, 2}, {1, 18, 12, 1, 3}, {1, 18, 12, 1, 4}, {1, 18, 12, 1, 5}, {1, 18, 12, 1, 6}, {1, 18, 12, 1, 7}, {1, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("3: less columns than rows") << IntMatrix{15, 10, 4} << FiveSizeTypesTupleArray{{8, 18, 12, 1, 1}, {7, 18, 12, 1, 1}, {6, 18, 12, 1, 1}, {5, 18, 12, 1, 1}, {4, 18, 12, 1, 1}, {3, 18, 12, 1, 1}, {2, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {0, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("4: less columns than rows") << IntMatrix{15, 10, 4} << FiveSizeTypesTupleArray{{0, 18, 12, 1, 2}, {8, 18, 12, 1, 2}, {0, 18, 12, 1, 3}, {6, 18, 12, 1, 3}, {0, 18, 12, 1, 4}, {4, 18, 12, 1, 4}, {0, 18, 6, 1, 1}, {2, 18, 6, 1, 1}, {0, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("5: less columns than rows") << IntMatrix{15, 10, 4} << FiveSizeTypesTupleArray{{9, 18, 12, 1, 1}, {0, 18, 12, 1, 2}, {7, 18, 12, 1, 2}, {0, 18, 12, 1, 3}, {5, 18, 12, 1, 3}, {0, 18, 12, 1, 4}, {3, 18, 6, 1, 1}, {0, 18, 6, 1, 2}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("6: less columns than rows") << IntMatrix{15, 10, 4} << FiveSizeTypesTupleArray{{3, 18, 12, 1, 2}, {6, 18, 12, 1, 2}, {7, 18, 12, 1, 2}, {2, 18, 12, 1, 3}, {1, 18, 12, 1, 4}, {2, 18, 12, 1, 4}, {0, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("7: square matrix") << IntMatrix{4, 4, 4} << FiveSizeTypesTupleArray{{1, 5, 5, 0, 1}, {1, 5, 5, 0, 1}, {1, 5, 2, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("8: square matrix") << IntMatrix{10, 10, 4} << FiveSizeTypesTupleArray{{1, 12, 12, 1, 2}, {1, 12, 12, 1, 3}, {1, 12, 12, 1, 4}, {1, 12, 12, 1, 5}, {1, 12, 12, 1, 6}, {1, 12, 12, 1, 7}, {1, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("9: square matrix") << IntMatrix{10, 10, 4} << FiveSizeTypesTupleArray{{8, 12, 12, 1, 1}, {7, 12, 12, 1, 1}, {6, 12, 12, 1, 1}, {5, 12, 12, 1, 1}, {4, 12, 12, 1, 1}, {3, 12, 12, 1, 1}, {2, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {0, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("10: square matrix") << IntMatrix{10, 10, 4} << FiveSizeTypesTupleArray{{0, 12, 12, 1, 2}, {8, 12, 12, 1, 2}, {0, 12, 12, 1, 3}, {6, 12, 12, 1, 3}, {0, 12, 12, 1, 4}, {4, 12, 12, 1, 4}, {0, 12, 6, 1, 1}, {2, 12, 6, 1, 1}, {0, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("11: square matrix") << IntMatrix{10, 10, 4} << FiveSizeTypesTupleArray{{9, 12, 12, 1, 1}, {0, 12, 12, 1, 2}, {7, 12, 12, 1, 2}, {0, 12, 12, 1, 3}, {5, 12, 12, 1, 3}, {0, 12, 12, 1, 4}, {3, 12, 6, 1, 1}, {0, 12, 6, 1, 2}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("12: square matrix") << IntMatrix{10, 10, 4} << FiveSizeTypesTupleArray{{3, 12, 12, 1, 2}, {6, 12, 12, 1, 2}, {7, 12, 12, 1, 2}, {2, 12, 12, 1, 3}, {1, 12, 12, 1, 4}, {2, 12, 12, 1, 4}, {0, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("13: more columns than rows") << IntMatrix{5, 7, 4} << FiveSizeTypesTupleArray{{1, 6, 8, 0, 1}, {1, 6, 8, 0, 2}, {1, 6, 8, 0, 3}, {1, 6, 8, 0, 4}, {1, 6, 4, 0, 1}, {1, 6, 2, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("14: more columns than rows") << IntMatrix{9, 10, 4} << FiveSizeTypesTupleArray{{1, 11, 12, 1, 2}, {1, 11, 12, 1, 3}, {1, 11, 12, 1, 4}, {1, 11, 12, 1, 5}, {1, 11, 12, 1, 6}, {1, 11, 12, 1, 7}, {1, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("15: more columns than rows") << IntMatrix{9, 10, 4} << FiveSizeTypesTupleArray{{8, 11, 12, 1, 1}, {7, 11, 12, 1, 1}, {6, 11, 12, 1, 1}, {5, 11, 12, 1, 1}, {4, 11, 12, 1, 1}, {3, 11, 12, 1, 1}, {2, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {0, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("16: more columns than rows") << IntMatrix{9, 10, 4} << FiveSizeTypesTupleArray{{0, 11, 12, 1, 2}, {8, 11, 12, 1, 2}, {0, 11, 12, 1, 3}, {6, 11, 12, 1, 3}, {0, 11, 12, 1, 4}, {4, 11, 12, 1, 4}, {0, 11, 6, 1, 1}, {2, 11, 6, 1, 1}, {0, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("17: more columns than rows") << IntMatrix{9, 10, 4} << FiveSizeTypesTupleArray{{9, 11, 12, 1, 1}, {0, 11, 12, 1, 2}, {7, 11, 12, 1, 2}, {0, 11, 12, 1, 3}, {5, 11, 12, 1, 3}, {0, 11, 12, 1, 4}, {3, 11, 6, 1, 1}, {0, 11, 6, 1, 2}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("18: more columns than rows") << IntMatrix{9, 10, 4} << FiveSizeTypesTupleArray{{3, 11, 12, 1, 2}, {6, 11, 12, 1, 2}, {7, 11, 12, 1, 2}, {2, 11, 12, 1, 3}, {1, 11, 12, 1, 4}, {2, 11, 12, 1, 4}, {0, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("2: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("3: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("4: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("5: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("6: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("7: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("8: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("9: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("10: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("11: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("12: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("13: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 10 << 8 << 1 << 0;
    QTest::newRow("14: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 7 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("15: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 8 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("16: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 9 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("17: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 10 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("18: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5 << 7 << 11 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("19: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 10 << 8 << 1 << 0;
    QTest::newRow("20: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("21: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("22: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("23: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 10 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("24: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4 << 7 << 11 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("25: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("26: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("27: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("28: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("29: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("30: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 12 << 8 << 11 << 8 << 1 << 0;

    // column capacity too
    QTest::newRow("31: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("32: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("33: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("34: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("35: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("36: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("37: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("38: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("39: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("40: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("41: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("42: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("43: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("44: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("45: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("46: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("47: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("48: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("49: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("50: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 9 << 11 << 8 << 1 << 0;

    // additional tests
    QTest::newRow("51: all different") << IntMatrix{} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("52: all different") << IntMatrix{7, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("53: all different") << IntMatrix{10, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("54: all different") << IntMatrix{6, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("55: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("56: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 26 << 22 << 32 << 27 << 3 << 2;
    QTest::newRow("57: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 31 << 26 << 32 << 27 << 3 << 2;
    QTest::newRow("58: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 32 << 27 << 32 << 27 << 3 << 2;
    QTest::newRow("59: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("60: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 26 << 22 << 32 << 27 << 3 << 2;
    QTest::newRow("61: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 31 << 26 << 32 << 27 << 3 << 2;
    QTest::newRow("62: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 32 << 27 << 32 << 27 << 3 << 2;
    QTest::newRow("63: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("64: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 27 << 23 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("65: destination first") << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("66: destination second") << IntMatrix{10, 22, -2} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("67: destination all") << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 40 << 27 << 4 << 2;
    QTest::newRow("68: source both") << IntMatrix{10, 22, -2} << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 40 << 27 << 4 << 2;

    // empty matrix concatenation
    QTest::newRow("69: source both") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
    QTest::newRow("70: all different") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("2: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("3: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("4: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("5: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("6: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("7: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("8: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("9: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("10: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("11: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("12: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("13: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 8 << 10 << 0 << 1;
    QTest::newRow("14: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 7 << 8 << 10 << 0 << 1;
    QTest::newRow("15: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 8 << 8 << 10 << 0 << 1;
    QTest::newRow("16: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 9 << 8 << 10 << 0 << 1;
    QTest::newRow("17: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 10 << 8 << 10 << 0 << 1;
    QTest::newRow("18: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 11 << 8 << 10 << 0 << 1;
    QTest::newRow("19: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 8 << 10 << 0 << 1;
    QTest::newRow("20: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7 << 8 << 10 << 0 << 1;
    QTest::newRow("21: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8 << 8 << 10 << 0 << 1;
    QTest::newRow("22: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9 << 8 << 10 << 0 << 1;
    QTest::newRow("23: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 10 << 8 << 10 << 0 << 1;
    QTest::newRow("24: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 11 << 8 << 10 << 0 << 1;
    QTest::newRow("25: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("26: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("27: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("28: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("29: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("30: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 12 << 8 << 11 << 0 << 1;

    // row capacity too
    QTest::newRow("31: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("32: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("33: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("34: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("35: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("36: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("37: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("38: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("39: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("40: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("41: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("42: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("43: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("44: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("45: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("46: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("47: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("48: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("49: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("50: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 12 << 8 << 11 << 0 << 1;

    // additional tests
    QTest::newRow("51: all different") << IntMatrix{} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("52: all different") << IntMatrix{5, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("53: all different") << IntMatrix{5, 10, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("54: all different") << IntMatrix{6, 6, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("55: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("56: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 22 << 26 << 27 << 32 << 2 << 3;
    QTest::newRow("57: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 26 << 31 << 27 << 32 << 2 << 3;
    QTest::newRow("58: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 27 << 32 << 27 << 32 << 2 << 3;
    QTest::newRow("59: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("60: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 22 << 26 << 27 << 32 << 2 << 3;
    QTest::newRow("61: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 26 << 31 << 27 << 32 << 2 << 3;
    QTest::newRow("62: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 27 << 32 << 27 << 32 << 2 << 3;
    QTest::newRow("63: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("64: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 23 << 27 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("65: destination first") << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("66: destination second") << IntMatrix{22, 10, -2} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("67: destination all") << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 27 << 40 << 2 << 4;
    QTest::newRow("68: source both") << IntMatrix{22, 10, -2} << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 27 << 40 << 2 << 4;

    // empty matrix concatenation
    QTest::newRow("69: source both") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
    QTest::newRow("70: all different") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
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
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("2: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("3: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 17 << false << 18 << 21 << 8 << 17 << 1 << 2 << 0 << 0;
    QTest::newRow("4: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 18 << false << 18 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("5: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 7 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("6: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("7: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("8: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("9: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 17 << true << 10 << 17 << 18 << 21 << 1 << 0 << 1 << 2;
    QTest::newRow("10: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 18 << true << 10 << 18 << 18 << 21 << 1 << 0 << 1 << 2;
    QTest::newRow("11: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("12: source second") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{15, 17, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;;
    QTest::newRow("13: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("14: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("15: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << true << 10 << 17 << 8 << 21 << 1 << 0 << 0 << 2;
    QTest::newRow("16: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << true << 10 << 18 << 8 << 21 << 1 << 0 << 0 << 2;
    QTest::newRow("17: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 18 << 8 << 21 << 0 << 0 << 0 << 2;
    QTest::newRow("18: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("19: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("20: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << false << 10 << 21 << 8 << 17 << 1 << 2 << 0 << 0;
    QTest::newRow("21: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << false << 10 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("22: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 15, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 7 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("23: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("24: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{7, 17, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("25: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("26: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("27: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 17 << false << 18 << 21 << 10 << 17 << 1 << 2 << 1 << 0;
    QTest::newRow("28: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 18 << false << 18 << 21 << 10 << 18 << 1 << 2 << 1 << 0;
    QTest::newRow("29: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("30: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("31: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("32: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("33: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 17 << true << 8 << 17 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("34: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 18 << true << 8 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("35: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 7 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("36: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{15, 17, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("37: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("38: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("39: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << true << 8 << 17 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("40: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << true << 8 << 18 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("41: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 7 << 18 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("42: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("43: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("44: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << false << 8 << 21 << 10 << 17 << 0 << 2 << 1 << 0;
    QTest::newRow("45: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << false << 8 << 21 << 10 << 18 << 0 << 2 << 1 << 0;
    QTest::newRow("46: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 15, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 8 << 18 << 0 << 2 << 0 << 0;
    QTest::newRow("47: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("48: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{8, 17, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11 << SplitMode::ALL_DIFFERENT << 9 << 12 << 14 << 18 << true << 14 << 25 << 22 << 25 << 1 << 2 << 4 << 2;
    QTest::newRow("50: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 11 << 25 << 22 << 25 << 0 << 2 << 4 << 2;
    QTest::newRow("51: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11 << SplitMode::ALL_DIFFERENT << 9 << 12 << 9 << 20 << true << 13 << 20 << 22 << 25 << 1 << 0 << 4 << 2;
    QTest::newRow("52: all different") << IntMatrix{25, 20, -3} << IntMatrix{} << IntMatrix{} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 13 << 25 << 17 << 25 << 1 << 2 << 1 << 2;
    QTest::newRow("53: source first") << IntMatrix{25, 20, -3} << IntMatrix{25, 20, -3} << IntMatrix{18, 9, 2} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 31 << 25 << 22 << 25 << 3 << 2 << 4 << 2;
    QTest::newRow("54: source first") << IntMatrix{25, 20, -3} << IntMatrix{25, 20, -3} << IntMatrix{} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 31 << 25 << 17 << 25 << 3 << 2 << 1 << 2;
    QTest::newRow("55: source second") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{25, 20, -3} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 11 << 25 << 31 << 25 << 0 << 2 << 3 << 2;
    QTest::newRow("56: source second") << IntMatrix{25, 20, -3} << IntMatrix{} << IntMatrix{25, 20, -3} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 13 << 25 << 31 << 25 << 1 << 2 << 3 << 2;
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
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("2: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("3: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 17 << 6 << false << 21 << 18 << 17 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("4: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 18 << 6 << false << 21 << 18 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("5: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 7 << 2 << 1 << 0 << 0;
    QTest::newRow("6: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("7: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("8: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("9: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 18 << 0 << 1 << 2 << 1;
    QTest::newRow("10: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 18 << 0 << 1 << 2 << 1;
    QTest::newRow("11: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("12: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 15, -3} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("13: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("14: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("15: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 8 << 0 << 1 << 2 << 0;
    QTest::newRow("16: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 8 << 0 << 1 << 2 << 0;
    QTest::newRow("17: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 8 << 0 << 0 << 2 << 0;
    QTest::newRow("18: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("19: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("20: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << false << 21 << 10 << 17 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("21: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << false << 21 << 10 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("22: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 6, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 18 << 7 << 2 << 1 << 0 << 0;
    QTest::newRow("23: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("24: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 7, 2} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("25: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("26: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("27: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 17 << 7 << false << 21 << 18 << 17 << 10 << 2 << 1 << 0 << 1;
    QTest::newRow("28: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 18 << 7 << false << 21 << 18 << 18 << 10 << 2 << 1 << 0 << 1;
    QTest::newRow("29: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("30: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("31: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("32: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("33: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("34: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("35: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("36: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 15, -3} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("37: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("38: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("39: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("40: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("41: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("42: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("43: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("44: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << false << 21 << 8 << 17 << 10 << 2 << 0 << 0 << 1;
    QTest::newRow("45: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << false << 21 << 8 << 18 << 10 << 2 << 0 << 0 << 1;
    QTest::newRow("46: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 7, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 18 << 8 << 2 << 0 << 0 << 0;
    QTest::newRow("47: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("48: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 8, 2} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11 << SplitMode::ALL_DIFFERENT << 12 << 9 << 18 << 14 << true << 25 << 14 << 25 << 22 << 2 << 1 << 2 << 4;
    QTest::newRow("50: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 25 << 11 << 25 << 22 << 2 << 0 << 2 << 4;
    QTest::newRow("51: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11 << SplitMode::ALL_DIFFERENT << 12 << 9 << 20 << 9 << true << 20 << 13 << 25 << 22 << 0 << 1 << 2 << 4;
    QTest::newRow("52: all different") << IntMatrix{20, 25, -3} << IntMatrix{} << IntMatrix{} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 25 << 13 << 25 << 17 << 2 << 1 << 2 << 1;
    QTest::newRow("53: source first") << IntMatrix{20, 25, -3} << IntMatrix{20, 25, -3} << IntMatrix{9, 18, 2} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 25 << 31 << 25 << 22 << 2 << 3 << 2 << 4;
    QTest::newRow("54: source first") << IntMatrix{20, 25, -3} << IntMatrix{20, 25, -3} << IntMatrix{} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 25 << 31 << 25 << 17 << 2 << 3 << 2 << 1;
    QTest::newRow("55: source second") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{20, 25, -3} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 25 << 11 << 25 << 31 << 2 << 0 << 2 << 3;
    QTest::newRow("56: source second") << IntMatrix{20, 25, -3} << IntMatrix{} << IntMatrix{20, 25, -3} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 25 << 13 << 25 << 31 << 2 << 1 << 2 << 3;
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 9 << 2 << -1 << false << 12 << 9 << 3 << 1;
    QTest::newRow("2: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 8 << 2 << -1 << false << 12 << 8 << 3 << 1;
    QTest::newRow("3: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 7 << 2 << -1 << false << 12 << 7 << 3 << 0;
    QTest::newRow("4: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 6 << 2 << -1 << false << 12 << 6 << 3 << 0;
    QTest::newRow("5: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 5 << 2 << -1 << false << 12 << 6 << 3 << 0;
    QTest::newRow("6: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 4 << 2 << -1 << false << 23 << 6 << 9 << 0;
    QTest::newRow("7: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 3 << 2 << -1 << false << 20 << 6 << 7 << 0;
    QTest::newRow("8: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 2 << 2 << -1 << false << 18 << 6 << 6 << 0;
    QTest::newRow("9: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 9 << -1 << 1 << false << 45 << 9 << 19 << 2;
    QTest::newRow("10: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 8 << -1 << 1 << false << 29 << 8 << 11 << 2;
    QTest::newRow("11: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 7 << -1 << 1 << false << 28 << 7 << 10 << 1;
    QTest::newRow("12: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 6 << -1 << 1 << false << 27 << 6 << 10 << 1;
    QTest::newRow("13: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 5 << -1 << 1 << false << 24 << 6 << 8 << 1;
    QTest::newRow("14: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 4 << -1 << 1 << false << 23 << 6 << 8 << 1;
    QTest::newRow("15: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 3 << -1 << 1 << false << 20 << 6 << 6 << 1;
    QTest::newRow("16: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 2 << -1 << 1 << false << 18 << 6 << 5 << 1;
    QTest::newRow("17: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << -1 << false << 12 << 41 << 3 << 17;
    QTest::newRow("18: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << -1 << false << 12 << 25 << 3 << 9;
    QTest::newRow("19: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << -1 << false << 12 << 24 << 3 << 9;
    QTest::newRow("20: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << -1 << false << 12 << 23 << 3 << 8;
    QTest::newRow("21: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << -1 << false << 12 << 20 << 3 << 7;
    QTest::newRow("22: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << -1 << false << 23 << 19 << 9 << 6;
    QTest::newRow("23: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << -1 << false << 20 << 16 << 7 << 5;
    QTest::newRow("24: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << -1 << false << 18 << 14 << 6 << 4;
    QTest::newRow("25: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("26: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("27: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("28: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("29: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("30: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << 1 << false << 23 << 19 << 9 << 7;
    QTest::newRow("31: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << 1 << false << 20 << 16 << 7 << 6;
    QTest::newRow("32: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << 1 << false << 18 << 14 << 6 << 5;
    QTest::newRow("33: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 45 << 41 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("34: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 29 << 25 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("35: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 28 << 24 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("36: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 27 << 23 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("37: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 24 << 20 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("38: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 23 << 19 << 2 << 1 << true << 23 << 19 << 9 << 7;
    QTest::newRow("39: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 20 << 16 << 2 << 1 << true << 20 << 16 << 7 << 6;
    QTest::newRow("40: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7 << 6 << 5 << 18 << 14 << 2 << 1 << true << 18 << 14 << 6 << 5;
    QTest::newRow("41: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 9 << 45 << -1 << 2 << false << 9 << 12 << 1 << 3;
    QTest::newRow("42: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 8 << 29 << -1 << 2 << false << 8 << 12 << 1 << 3;
    QTest::newRow("43: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 7 << 28 << -1 << 2 << false << 7 << 12 << 0 << 3;
    QTest::newRow("44: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 6 << 27 << -1 << 2 << false << 6 << 12 << 0 << 3;
    QTest::newRow("45: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 5 << 24 << -1 << 2 << false << 6 << 12 << 0 << 3;
    QTest::newRow("46: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 4 << 23 << -1 << 2 << false << 6 << 23 << 0 << 9;
    QTest::newRow("47: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 3 << 20 << -1 << 2 << false << 6 << 20 << 0 << 7;
    QTest::newRow("48: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 2 << 18 << -1 << 2 << false << 6 << 18 << 0 << 6;
    QTest::newRow("49: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 9 << 45 << 1 << -1 << false << 9 << 45 << 2 << 19;
    QTest::newRow("50: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 8 << 29 << 1 << -1 << false << 8 << 29 << 2 << 11;
    QTest::newRow("51: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 7 << 28 << 1 << -1 << false << 7 << 28 << 1 << 10;
    QTest::newRow("52: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 6 << 27 << 1 << -1 << false << 6 << 27 << 1 << 10;
    QTest::newRow("53: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 5 << 24 << 1 << -1 << false << 6 << 24 << 1 << 8;
    QTest::newRow("54: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 4 << 23 << 1 << -1 << false << 6 << 23 << 1 << 8;
    QTest::newRow("55: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 3 << 20 << 1 << -1 << false << 6 << 20 << 1 << 6;
    QTest::newRow("56: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 2 << 18 << 1 << -1 << false << 6 << 18 << 1 << 5;
    QTest::newRow("57: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << -1 << 2 << false << 41 << 12 << 17 << 3;
    QTest::newRow("58: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << -1 << 2 << false << 25 << 12 << 9 << 3;
    QTest::newRow("59: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << -1 << 2 << false << 24 << 12 << 9 << 3;
    QTest::newRow("60: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << -1 << 2 << false << 23 << 12 << 8 << 3;
    QTest::newRow("61: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << -1 << 2 << false << 20 << 12 << 7 << 3;
    QTest::newRow("62: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << -1 << 2 << false << 19 << 23 << 6 << 9;
    QTest::newRow("63: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << -1 << 2 << false << 16 << 20 << 5 << 7;
    QTest::newRow("64: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << -1 << 2 << false << 14 << 18 << 4 << 6;
    QTest::newRow("65: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("66: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("67: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("68: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("69: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("70: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << 1 << 2 << true << 19 << 23 << 7 << 9;
    QTest::newRow("71: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << 1 << 2 << true << 16 << 20 << 6 << 7;
    QTest::newRow("72: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << 1 << 2 << true << 14 << 18 << 5 << 6;
    QTest::newRow("73: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 41 << 45 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("74: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 25 << 29 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("75: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 24 << 28 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("76: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 23 << 27 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("77: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 20 << 24 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("78: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 19 << 23 << 1 << 2 << false << 19 << 23 << 7 << 9;
    QTest::newRow("79: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 16 << 20 << 1 << 2 << false << 16 << 20 << 6 << 7;
    QTest::newRow("80: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6 << 7 << 5 << 14 << 18 << 1 << 2 << false << 14 << 18 << 5 << 6;
}

void CapacityTests::testStringMatrixCapacityWithIdenticalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << 4 << std::string{"Value1"} << 3 << 5 << 0 << 0;
    QTest::newRow("2: small size matrix") << 4 << 3 << std::string{"Value1"} << 5 << 3 << 0 << 0;
    QTest::newRow("3: large size matrix") << 25 << 20 << std::string{"Value2"} << 31 << 25 << 3 << 2;
    QTest::newRow("4: large size matrix") << 20 << 25 << std::string{"Value2"} << 25 << 31 << 2 << 3;
}

void CapacityTests::testStringMatrixCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<std::string>("nonDiagonalValue");
    QTest::addColumn<std::string>("diagonalValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << std::string{"Value1"} << std::string{"Value2"} << 3 << 0;
    QTest::newRow("2: small size matrix") << 4 << std::string{"Value1"} << std::string{"Value2"} << 5 << 0;
    QTest::newRow("3: medium size matrix") << 8 << std::string{"Value1"} << std::string{"Value2"} << 10 << 1;
    QTest::newRow("4: medium size matrix") << 10 << std::string{"Value1"} << std::string{"Value2"} << 12 << 1;
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << StringMatrix{3, 4, "Value"} << StringMatrix{} << 5 << 3 << 0 << 0 << false;
    QTest::newRow("2: transposed matrix initially empty") << StringMatrix{4, 3, "Value"} << StringMatrix{} << 3 << 5 << 0 << 0 << false;
    QTest::newRow("3: transposed matrix initially empty") << StringMatrix{7, 8, "Value"} << StringMatrix{} << 10 << 8 << 1 << 0 << false;
    QTest::newRow("4: transposed matrix initially empty") << StringMatrix{8, 7, "Value"} << StringMatrix{} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("5: transposed matrix initially empty") << StringMatrix{20, 25, "Value"} << StringMatrix{} << 31 << 25 << 3 << 2 << false;
    QTest::newRow("6: transposed matrix initially empty") << StringMatrix{25, 20, "Value"} << StringMatrix{} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 6, "Value"} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 6, "Value"} << 7 << 10 << 0 << 1 << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 7, "Value"} << 8 << 8 << 0 << 0 << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 7, "Value"} << 7 << 8 << 0 << 0 << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{7, 8, "Value"} << 8 << 10 << 0 << 1 << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 19, "Value"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 19, "Value"} << 20 << 31 << 0 << 3 << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 20, "Value"} << 25 << 25 << 2 << 0 << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 20, "Value"} << 20 << 25 << 0 << 0 << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 25, "Value"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 25, "Value"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 25, "Value"} << 20 << 31 << 0 << 3 << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 19, "Value"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 20, "Value"} << 25 << 25 << 2 << 0 << false;
    QTest::newRow("21: matrix transposed to itself") << StringMatrix{3, 3, "Value"} << StringMatrix{3, 3, "Value"} << 3 << 3 << 0 << 0 << true;
    QTest::newRow("22: matrix transposed to itself") << StringMatrix{3, 4, "Value"} << StringMatrix{3, 4, "Value"} << 5 << 5 << 0 << 1 << true;
    QTest::newRow("23: matrix transposed to itself") << StringMatrix{4, 3, "Value"} << StringMatrix{4, 3, "Value"} << 5 << 5 << 1 << 0 << true;
    QTest::newRow("24: matrix transposed to itself") << StringMatrix{4, 4, "Value"} << StringMatrix{4, 4, "Value"} << 5 << 5 << 0 << 0 << true;
    QTest::newRow("25: matrix transposed to itself") << StringMatrix{7, 8, "Value"} << StringMatrix{7, 8, "Value"} << 8 << 10 << 0 << 1 << true;
    QTest::newRow("26: matrix transposed to itself") << StringMatrix{8, 7, "Value"} << StringMatrix{8, 7, "Value"} << 10 << 8 << 1 << 0 << true;
    QTest::newRow("27: matrix transposed to itself") << StringMatrix{20, 25, "Value"} << StringMatrix{20, 25, "Value"} << 25 << 31 << 0 << 5 << true;
    QTest::newRow("28: matrix transposed to itself") << StringMatrix{25, 20, "Value"} << StringMatrix{25, 20, "Value"} << 31 << 25 << 5 << 0 << true;
    QTest::newRow("29: matrix transposed to itself") << StringMatrix{25, 25, "Value"} << StringMatrix{25, 25, "Value"} << 31 << 31 << 3 << 3 << true;
    QTest::newRow("30: matrix transposed to itself") << StringMatrix{20, 26, "Value"} << StringMatrix{20, 26, "Value"} << 32 << 32 << 3 << 6 << true;
    QTest::newRow("31: matrix transposed to itself") << StringMatrix{26, 20, "Value"} << StringMatrix{26, 20, "Value"} << 32 << 32 << 6 << 3 << true;
}

void CapacityTests::testStringMatrixCapacityWithResizeWithDefaultNewValues_data()
{
    _buildStringMatrixCapacityWithResizeTestingTable();
}

void CapacityTests::testStringMatrixCapacityWithResizeAndSetNewValues_data()
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("1: inserted row value NOT set") << StringMatrix{3, 4, "Value1"} << 1 << std::string{"Value2"} << 6 << 5 << 1 << 0 << false;
    QTest::newRow("2: inserted row value set") << StringMatrix{3, 4, "Value1"} << 1 << std::string{"Value2"} << 6 << 5 << 1 << 0 << true;
    QTest::newRow("3: inserted row value NOT set") << StringMatrix{6, 5, "Value1"} << 3 << std::string{"Value2"} << 7 << 6 << 0 << 0 << false;
    QTest::newRow("4: inserted row value set") << StringMatrix{6, 5, "Value1"} << 3 << std::string{"Value2"} << 7 << 6 << 0 << 0 << true;
    QTest::newRow("5: inserted row value NOT set") << StringMatrix{8, 2, "Value1"} << 5 << std::string{"Value2"} << 10 << 2 << 1 << 0 << false;
    QTest::newRow("6: inserted row value set") << StringMatrix{8, 2, "Value1"} << 5 << std::string{"Value2"} << 10 << 2 << 1 << 0 << true;
    QTest::newRow("7: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 0 << std::string{"Value2"} << 31 << 25 << 2 << 2 << false;
    QTest::newRow("8: inserted row value set") << StringMatrix{25, 20, "Value1"} << 0 << std::string{"Value2"} << 31 << 25 << 2 << 2 << true;
    QTest::newRow("9: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 11 << std::string{"Value2"} << 31 << 25 << 2 << 2 << false;
    QTest::newRow("10: inserted row value set") << StringMatrix{25, 20, "Value1"} << 11 << std::string{"Value2"} << 31 << 25 << 2 << 2 << true;
    QTest::newRow("11: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 25 << std::string{"Value2"} << 31 << 25 << 3 << 2 << false;
    QTest::newRow("12: inserted row value set") << StringMatrix{25, 20, "Value1"} << 25 << std::string{"Value2"} << 31 << 25 << 3 << 2 << true;
}

void CapacityTests::testStringMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("1: inserted column value NOT set") << StringMatrix{5, 3, "Value1"} << 1 << std::string{"Value2"} << 6 << 6 << 0 << 1 << false;
    QTest::newRow("2: inserted column value set") << StringMatrix{5, 3, "Value1"} << 1 << std::string{"Value2"} << 6 << 6 << 0 << 1 << true;
    QTest::newRow("3: inserted column value NOT set") << StringMatrix{5, 7, "Value1"} << 1 << std::string{"Value2"} << 6 << 8 << 0 << 0 << false;
    QTest::newRow("4: inserted column value set") << StringMatrix{5, 7, "Value1"} << 1 << std::string{"Value2"} << 6 << 8 << 0 << 0 << true;
    QTest::newRow("5: inserted column value NOT set") << StringMatrix{5, 14, "Value1"} << 1 << std::string{"Value2"} << 6 << 17 << 0 << 0 << false;
    QTest::newRow("6: inserted column value set") << StringMatrix{5, 14, "Value1"} << 1 << std::string{"Value2"} << 6 << 17 << 0 << 0 << true;
    QTest::newRow("7: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 0 << std::string{"Value2"} << 25 << 31 << 2 << 2 << false;
    QTest::newRow("8: inserted column value set") << StringMatrix{20, 25, "Value1"} << 0 << std::string{"Value2"} << 25 << 31 << 2 << 2 << true;
    QTest::newRow("9: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 14 << std::string{"Value2"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("10: inserted column value set") << StringMatrix{20, 25, "Value1"} << 14 << std::string{"Value2"} << 25 << 31 << 2 << 3 << true;
    QTest::newRow("11: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 25 << std::string{"Value2"} << 25 << 31 << 2 << 3 << false;
    QTest::newRow("12: inserted column value set") << StringMatrix{20, 25, "Value1"} << 25 << std::string{"Value2"} << 25 << 31 << 2 << 3 << true;
}

void CapacityTests::testStringMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<FiveSizeTypesTupleArray>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << StringMatrix{3, 4, "Value"} << FiveSizeTypesTupleArray{{1, 3, 5, 0, 0}, {1, 3, 5, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("2: less rows than columns") << StringMatrix{10, 15, "Value"} << FiveSizeTypesTupleArray{{1, 12, 18, 2, 1}, {1, 12, 18, 3, 1}, {1, 12, 18, 4, 1}, {1, 12, 18, 5, 1}, {1, 12, 18, 6, 1}, {1, 12, 18, 7, 1}, {1, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("3: less rows than columns") << StringMatrix{10, 15, "Value"} << FiveSizeTypesTupleArray{{8, 12, 18, 1, 1}, {7, 12, 18, 1, 1}, {6, 12, 18, 1, 1}, {5, 12, 18, 1, 1}, {4, 12, 18, 1, 1}, {3, 12, 18, 1, 1}, {2, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {0, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("4: less rows than columns") << StringMatrix{10, 15, "Value"} << FiveSizeTypesTupleArray{{0, 12, 18, 2, 1}, {8, 12, 18, 2, 1}, {0, 12, 18, 3, 1}, {6, 12, 18, 3, 1}, {0, 12, 18, 4, 1}, {4, 12, 18, 4, 1}, {0, 6, 18, 1, 1}, {2, 6, 18, 1, 1}, {0, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("5: less rows than columns") << StringMatrix{10, 15, "Value"} << FiveSizeTypesTupleArray{{9, 12, 18, 1, 1}, {0, 12, 18, 2, 1}, {7, 12, 18, 2, 1}, {0, 12, 18, 3, 1}, {5, 12, 18, 3, 1}, {0, 12, 18, 4, 1}, {3, 6, 18, 1, 1}, {0, 6, 18, 2, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("6: less rows than columns") << StringMatrix{10, 15, "Value"} << FiveSizeTypesTupleArray{{3, 12, 18, 2, 1}, {6, 12, 18, 2, 1}, {7, 12, 18, 2, 1}, {2, 12, 18, 3, 1}, {1, 12, 18, 4, 1}, {2, 12, 18, 4, 1}, {0, 6, 18, 1, 1}, {1, 6, 18, 1, 1}, {1, 2, 18, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("7: square matrix") << StringMatrix{4, 4, "Value"} << FiveSizeTypesTupleArray{{1, 5, 5, 1, 0}, {1, 5, 5, 1, 0}, {1, 2, 5, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("8: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{1, 12, 12, 2, 1}, {1, 12, 12, 3, 1}, {1, 12, 12, 4, 1}, {1, 12, 12, 5, 1}, {1, 12, 12, 6, 1}, {1, 12, 12, 7, 1}, {1, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("9: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{8, 12, 12, 1, 1}, {7, 12, 12, 1, 1}, {6, 12, 12, 1, 1}, {5, 12, 12, 1, 1}, {4, 12, 12, 1, 1}, {3, 12, 12, 1, 1}, {2, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {0, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("10: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{0, 12, 12, 2, 1}, {8, 12, 12, 2, 1}, {0, 12, 12, 3, 1}, {6, 12, 12, 3, 1}, {0, 12, 12, 4, 1}, {4, 12, 12, 4, 1}, {0, 6, 12, 1, 1}, {2, 6, 12, 1, 1}, {0, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("11: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{9, 12, 12, 1, 1}, {0, 12, 12, 2, 1}, {7, 12, 12, 2, 1}, {0, 12, 12, 3, 1}, {5, 12, 12, 3, 1}, {0, 12, 12, 4, 1}, {3, 6, 12, 1, 1}, {0, 6, 12, 2, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("12: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{3, 12, 12, 2, 1}, {6, 12, 12, 2, 1}, {7, 12, 12, 2, 1}, {2, 12, 12, 3, 1}, {1, 12, 12, 4, 1}, {2, 12, 12, 4, 1}, {0, 6, 12, 1, 1}, {1, 6, 12, 1, 1}, {1, 2, 12, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("13: more rows than columns") << StringMatrix{7, 5, "Value"} << FiveSizeTypesTupleArray{{1, 8, 6, 1, 0}, {1, 8, 6, 2, 0}, {1, 8, 6, 3, 0}, {1, 8, 6, 4, 0}, {1, 4, 6, 1, 0}, {1, 2, 6, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("14: more rows than columns") << StringMatrix{10, 9, "Value"} << FiveSizeTypesTupleArray{{1, 12, 11, 2, 1}, {1, 12, 11, 3, 1}, {1, 12, 11, 4, 1}, {1, 12, 11, 5, 1}, {1, 12, 11, 6, 1}, {1, 12, 11, 7, 1}, {1, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("15: more rows than columns") << StringMatrix{10, 9, "Value"} << FiveSizeTypesTupleArray{{8, 12, 11, 1, 1}, {7, 12, 11, 1, 1}, {6, 12, 11, 1, 1}, {5, 12, 11, 1, 1}, {4, 12, 11, 1, 1}, {3, 12, 11, 1, 1}, {2, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {0, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("16: more rows than columns") << StringMatrix{10, 9, "Value"} << FiveSizeTypesTupleArray{{0, 12, 11, 2, 1}, {8, 12, 11, 2, 1}, {0, 12, 11, 3, 1}, {6, 12, 11, 3, 1}, {0, 12, 11, 4, 1}, {4, 12, 11, 4, 1}, {0, 6, 11, 1, 1}, {2, 6, 11, 1, 1}, {0, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("17: more rows than columns") << StringMatrix{10, 9, "Value"} << FiveSizeTypesTupleArray{{9, 12, 11, 1, 1}, {0, 12, 11, 2, 1}, {7, 12, 11, 2, 1}, {0, 12, 11, 3, 1}, {5, 12, 11, 3, 1}, {0, 12, 11, 4, 1}, {3, 6, 11, 1, 1}, {0, 6, 11, 2, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
    QTest::newRow("18: more rows than columns") << StringMatrix{10, 9, "Value"} << FiveSizeTypesTupleArray{{3, 12, 11, 2, 1}, {6, 12, 11, 2, 1}, {7, 12, 11, 2, 1}, {2, 12, 11, 3, 1}, {1, 12, 11, 4, 1}, {2, 12, 11, 4, 1}, {0, 6, 11, 1, 1}, {1, 6, 11, 1, 1}, {1, 2, 11, 0, 1}, {0, 0, 0, -1, -1}};
}

void CapacityTests::testStringMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<FiveSizeTypesTupleArray>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << StringMatrix{4, 3, "Value"} << FiveSizeTypesTupleArray{{1, 5, 3, 0, 0}, {1, 5, 3, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("2: less columns than rows") << StringMatrix{15, 10, "Value"} << FiveSizeTypesTupleArray{{1, 18, 12, 1, 2}, {1, 18, 12, 1, 3}, {1, 18, 12, 1, 4}, {1, 18, 12, 1, 5}, {1, 18, 12, 1, 6}, {1, 18, 12, 1, 7}, {1, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("3: less columns than rows") << StringMatrix{15, 10, "Value"} << FiveSizeTypesTupleArray{{8, 18, 12, 1, 1}, {7, 18, 12, 1, 1}, {6, 18, 12, 1, 1}, {5, 18, 12, 1, 1}, {4, 18, 12, 1, 1}, {3, 18, 12, 1, 1}, {2, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {0, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("4: less columns than rows") << StringMatrix{15, 10, "Value"} << FiveSizeTypesTupleArray{{0, 18, 12, 1, 2}, {8, 18, 12, 1, 2}, {0, 18, 12, 1, 3}, {6, 18, 12, 1, 3}, {0, 18, 12, 1, 4}, {4, 18, 12, 1, 4}, {0, 18, 6, 1, 1}, {2, 18, 6, 1, 1}, {0, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("5: less columns than rows") << StringMatrix{15, 10, "Value"} << FiveSizeTypesTupleArray{{9, 18, 12, 1, 1}, {0, 18, 12, 1, 2}, {7, 18, 12, 1, 2}, {0, 18, 12, 1, 3}, {5, 18, 12, 1, 3}, {0, 18, 12, 1, 4}, {3, 18, 6, 1, 1}, {0, 18, 6, 1, 2}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("6: less columns than rows") << StringMatrix{15, 10, "Value"} << FiveSizeTypesTupleArray{{3, 18, 12, 1, 2}, {6, 18, 12, 1, 2}, {7, 18, 12, 1, 2}, {2, 18, 12, 1, 3}, {1, 18, 12, 1, 4}, {2, 18, 12, 1, 4}, {0, 18, 6, 1, 1}, {1, 18, 6, 1, 1}, {1, 18, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("7: square matrix") << StringMatrix{4, 4, "Value"} << FiveSizeTypesTupleArray{{1, 5, 5, 0, 1}, {1, 5, 5, 0, 1}, {1, 5, 2, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("8: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{1, 12, 12, 1, 2}, {1, 12, 12, 1, 3}, {1, 12, 12, 1, 4}, {1, 12, 12, 1, 5}, {1, 12, 12, 1, 6}, {1, 12, 12, 1, 7}, {1, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("9: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{8, 12, 12, 1, 1}, {7, 12, 12, 1, 1}, {6, 12, 12, 1, 1}, {5, 12, 12, 1, 1}, {4, 12, 12, 1, 1}, {3, 12, 12, 1, 1}, {2, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {0, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("10: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{0, 12, 12, 1, 2}, {8, 12, 12, 1, 2}, {0, 12, 12, 1, 3}, {6, 12, 12, 1, 3}, {0, 12, 12, 1, 4}, {4, 12, 12, 1, 4}, {0, 12, 6, 1, 1}, {2, 12, 6, 1, 1}, {0, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("11: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{9, 12, 12, 1, 1}, {0, 12, 12, 1, 2}, {7, 12, 12, 1, 2}, {0, 12, 12, 1, 3}, {5, 12, 12, 1, 3}, {0, 12, 12, 1, 4}, {3, 12, 6, 1, 1}, {0, 12, 6, 1, 2}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("12: square matrix") << StringMatrix{10, 10, "Value"} << FiveSizeTypesTupleArray{{3, 12, 12, 1, 2}, {6, 12, 12, 1, 2}, {7, 12, 12, 1, 2}, {2, 12, 12, 1, 3}, {1, 12, 12, 1, 4}, {2, 12, 12, 1, 4}, {0, 12, 6, 1, 1}, {1, 12, 6, 1, 1}, {1, 12, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("13: more columns than rows") << StringMatrix{5, 7, "Value"} << FiveSizeTypesTupleArray{{1, 6, 8, 0, 1}, {1, 6, 8, 0, 2}, {1, 6, 8, 0, 3}, {1, 6, 8, 0, 4}, {1, 6, 4, 0, 1}, {1, 6, 2, 0, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("14: more columns than rows") << StringMatrix{9, 10, "Value"} << FiveSizeTypesTupleArray{{1, 11, 12, 1, 2}, {1, 11, 12, 1, 3}, {1, 11, 12, 1, 4}, {1, 11, 12, 1, 5}, {1, 11, 12, 1, 6}, {1, 11, 12, 1, 7}, {1, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("15: more columns than rows") << StringMatrix{9, 10, "Value"} << FiveSizeTypesTupleArray{{8, 11, 12, 1, 1}, {7, 11, 12, 1, 1}, {6, 11, 12, 1, 1}, {5, 11, 12, 1, 1}, {4, 11, 12, 1, 1}, {3, 11, 12, 1, 1}, {2, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {0, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("16: more columns than rows") << StringMatrix{9, 10, "Value"} << FiveSizeTypesTupleArray{{0, 11, 12, 1, 2}, {8, 11, 12, 1, 2}, {0, 11, 12, 1, 3}, {6, 11, 12, 1, 3}, {0, 11, 12, 1, 4}, {4, 11, 12, 1, 4}, {0, 11, 6, 1, 1}, {2, 11, 6, 1, 1}, {0, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("17: more columns than rows") << StringMatrix{9, 10, "Value"} << FiveSizeTypesTupleArray{{9, 11, 12, 1, 1}, {0, 11, 12, 1, 2}, {7, 11, 12, 1, 2}, {0, 11, 12, 1, 3}, {5, 11, 12, 1, 3}, {0, 11, 12, 1, 4}, {3, 11, 6, 1, 1}, {0, 11, 6, 1, 2}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
    QTest::newRow("18: more columns than rows") << StringMatrix{9, 10, "Value"} << FiveSizeTypesTupleArray{{3, 11, 12, 1, 2}, {6, 11, 12, 1, 2}, {7, 11, 12, 1, 2}, {2, 11, 12, 1, 3}, {1, 11, 12, 1, 4}, {2, 11, 12, 1, 4}, {0, 11, 6, 1, 1}, {1, 11, 6, 1, 1}, {1, 11, 2, 1, 0}, {0, 0, 0, -1, -1}};
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("2: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("3: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("4: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("5: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("6: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4 << 7 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("7: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("8: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("9: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("10: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("11: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("12: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5 << 7 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("13: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 10 << 8 << 1 << 0;
    QTest::newRow("14: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 7 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("15: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 8 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("16: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 9 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("17: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 10 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("18: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5 << 7 << 11 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("19: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 10 << 8 << 1 << 0;
    QTest::newRow("20: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 7 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("21: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 8 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("22: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 9 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("23: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 10 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("24: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4 << 7 << 11 << 8 << 10 << 8 << 1 << 0;
    QTest::newRow("25: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("26: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("27: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("28: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("29: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("30: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 12 << 8 << 11 << 8 << 1 << 0;

    // column capacity too
    QTest::newRow("31: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("32: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("33: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("34: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("35: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("36: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("37: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("38: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 9 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("39: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("40: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("41: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("42: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 10 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("43: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("44: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("45: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("46: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 11 << 9 << 11 << 8 << 1 << 0;
    QTest::newRow("47: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 6 << 11 << 8 << 1 << 0;
    QTest::newRow("48: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("49: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("50: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 12 << 9 << 11 << 8 << 1 << 0;

    // additional tests
    QTest::newRow("51: all different") << StringMatrix{} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("52: all different") << StringMatrix{7, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("53: all different") << StringMatrix{10, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("54: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("55: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("56: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 26 << 22 << 32 << 27 << 3 << 2;
    QTest::newRow("57: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 31 << 26 << 32 << 27 << 3 << 2;
    QTest::newRow("58: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 32 << 27 << 32 << 27 << 3 << 2;
    QTest::newRow("59: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12 << 15 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("60: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 26 << 22 << 32 << 27 << 3 << 2;
    QTest::newRow("61: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 31 << 26 << 32 << 27 << 3 << 2;
    QTest::newRow("62: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 32 << 27 << 32 << 27 << 3 << 2;
    QTest::newRow("63: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26 << 22 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("64: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 27 << 23 << 33 << 28 << 32 << 27 << 3 << 2;
    QTest::newRow("65: destination first") << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("66: destination second") << StringMatrix{10, 22, "Value2"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 32 << 27 << 3 << 2;
    QTest::newRow("67: destination all") << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 40 << 27 << 4 << 2;
    QTest::newRow("68: source both") << StringMatrix{10, 22, "Value2"} << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 40 << 27 << 4 << 2;

    // empty matrix concatenation
    QTest::newRow("69: source both") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
    QTest::newRow("70: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("2: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("3: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("4: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("5: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("6: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7 << 4 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("7: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("8: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("9: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("10: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("11: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("12: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7 << 5 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("13: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 8 << 10 << 0 << 1;
    QTest::newRow("14: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 7 << 8 << 10 << 0 << 1;
    QTest::newRow("15: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 8 << 8 << 10 << 0 << 1;
    QTest::newRow("16: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 9 << 8 << 10 << 0 << 1;
    QTest::newRow("17: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 10 << 8 << 10 << 0 << 1;
    QTest::newRow("18: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7 << 5 << 8 << 11 << 8 << 10 << 0 << 1;
    QTest::newRow("19: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 8 << 10 << 0 << 1;
    QTest::newRow("20: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 7 << 8 << 10 << 0 << 1;
    QTest::newRow("21: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 8 << 8 << 10 << 0 << 1;
    QTest::newRow("22: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 9 << 8 << 10 << 0 << 1;
    QTest::newRow("23: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 10 << 8 << 10 << 0 << 1;
    QTest::newRow("24: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7 << 4 << 8 << 11 << 8 << 10 << 0 << 1;
    QTest::newRow("25: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("26: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("27: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("28: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("29: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("30: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7 << 6 << 8 << 12 << 8 << 11 << 0 << 1;

    // row capacity too
    QTest::newRow("31: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("32: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("33: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("34: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 8 << 8 << 11 << 0 << 1;
    QTest::newRow("35: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("36: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("37: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("38: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 9 << 8 << 11 << 0 << 1;
    QTest::newRow("39: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("40: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("41: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("42: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 10 << 8 << 11 << 0 << 1;
    QTest::newRow("43: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("44: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("45: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("46: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 11 << 8 << 11 << 0 << 1;
    QTest::newRow("47: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 6 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("48: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 7 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("49: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 8 << 12 << 8 << 11 << 0 << 1;
    QTest::newRow("50: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6 << 7 << 9 << 12 << 8 << 11 << 0 << 1;

    // additional tests
    QTest::newRow("51: all different") << StringMatrix{} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("52: all different") << StringMatrix{5, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("53: all different") << StringMatrix{5, 10, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("54: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 8 << 11 << 0 << 1;
    QTest::newRow("55: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("56: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 22 << 26 << 27 << 32 << 2 << 3;
    QTest::newRow("57: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 26 << 31 << 27 << 32 << 2 << 3;
    QTest::newRow("58: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 27 << 32 << 27 << 32 << 2 << 3;
    QTest::newRow("59: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15 << 12 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("60: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 22 << 26 << 27 << 32 << 2 << 3;
    QTest::newRow("61: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 26 << 31 << 27 << 32 << 2 << 3;
    QTest::newRow("62: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 27 << 32 << 27 << 32 << 2 << 3;
    QTest::newRow("63: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22 << 26 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("64: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 23 << 27 << 28 << 33 << 27 << 32 << 2 << 3;
    QTest::newRow("65: destination first") << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::DESTINATION_FIRST << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("66: destination second") << StringMatrix{22, 10, "Value2"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::DESTINATION_SECOND << 0 << 0 << 0 << 0 << 27 << 32 << 2 << 3;
    QTest::newRow("67: destination all") << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << ConcatMode::DESTINATION_ALL << 0 << 0 << 0 << 0 << 27 << 40 << 2 << 4;
    QTest::newRow("68: source both") << StringMatrix{22, 10, "Value2"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 27 << 40 << 2 << 4;

    // empty matrix concatenation
    QTest::newRow("69: source both") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
    QTest::newRow("70: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << 0 << 0 << -1 << -1;
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
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("2: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("3: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 17 << false << 18 << 21 << 8 << 17 << 1 << 2 << 0 << 0;
    QTest::newRow("4: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 5 << 8 << 6 << 18 << false << 18 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("5: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 7 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("6: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("7: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("8: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("9: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 17 << true << 10 << 17 << 18 << 21 << 1 << 0 << 1 << 2;
    QTest::newRow("10: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 6 << 8 << 7 << 18 << true << 10 << 18 << 18 << 21 << 1 << 0 << 1 << 2;
    QTest::newRow("11: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("12: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 10 << 21 << 18 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("13: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("14: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("15: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << true << 10 << 17 << 8 << 21 << 1 << 0 << 0 << 2;
    QTest::newRow("16: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << true << 10 << 18 << 8 << 21 << 1 << 0 << 0 << 2;
    QTest::newRow("17: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 18 << 8 << 21 << 0 << 0 << 0 << 2;
    QTest::newRow("18: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("19: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("20: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << false << 10 << 21 << 8 << 17 << 1 << 2 << 0 << 0;
    QTest::newRow("21: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << false << 10 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("22: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 15, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 7 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("23: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("24: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{7, 17, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 10 << 21 << 8 << 21 << 1 << 2 << 0 << 2;
    QTest::newRow("25: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("26: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("27: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 17 << false << 18 << 21 << 10 << 17 << 1 << 2 << 1 << 0;
    QTest::newRow("28: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 6 << 8 << 7 << 18 << false << 18 << 21 << 10 << 18 << 1 << 2 << 1 << 0;
    QTest::newRow("29: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 8 << 18 << 1 << 2 << 0 << 0;
    QTest::newRow("30: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 18 << 21 << 10 << 21 << 1 << 2 << 1 << 2;
    QTest::newRow("31: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("32: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("33: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 17 << true << 8 << 17 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("34: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 5 << 8 << 6 << 18 << true << 8 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("35: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 7 << 18 << 18 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("36: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 8 << 21 << 18 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("37: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("38: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("39: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 17 << true << 8 << 17 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("40: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 5 << 8 << 6 << 18 << true << 8 << 18 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("41: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 7 << 18 << 10 << 21 << 0 << 0 << 1 << 2;
    QTest::newRow("42: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("43: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("44: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 17 << false << 8 << 21 << 10 << 17 << 0 << 2 << 1 << 0;
    QTest::newRow("45: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 6 << 8 << 7 << 18 << false << 8 << 21 << 10 << 18 << 0 << 2 << 1 << 0;
    QTest::newRow("46: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 15, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 8 << 18 << 0 << 2 << 0 << 0;
    QTest::newRow("47: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;
    QTest::newRow("48: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{8, 17, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 8 << 21 << 10 << 21 << 0 << 2 << 1 << 2;

    // additional tests
    QTest::newRow("49: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 9 << 12 << 14 << 18 << true << 14 << 25 << 22 << 25 << 1 << 2 << 4 << 2;
    QTest::newRow("50: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 11 << 25 << 22 << 25 << 0 << 2 << 4 << 2;
    QTest::newRow("51: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 9 << 12 << 9 << 20 << true << 13 << 20 << 22 << 25 << 1 << 0 << 4 << 2;
    QTest::newRow("52: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{} << StringMatrix{} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 13 << 25 << 17 << 25 << 1 << 2 << 1 << 2;
    QTest::newRow("53: source first") << StringMatrix{25, 20, "Value1"} << StringMatrix{25, 20, "Value1"} << StringMatrix{18, 9, "Value2"} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 31 << 25 << 22 << 25 << 3 << 2 << 4 << 2;
    QTest::newRow("54: source first") << StringMatrix{25, 20, "Value1"} << StringMatrix{25, 20, "Value1"} << StringMatrix{} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 31 << 25 << 17 << 25 << 3 << 2 << 1 << 2;
    QTest::newRow("55: source second") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{25, 20, "Value1"} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 11 << 25 << 31 << 25 << 0 << 2 << 3 << 2;
    QTest::newRow("56: source second") << StringMatrix{25, 20, "Value1"} << StringMatrix{} << StringMatrix{25, 20, "Value1"} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 13 << 25 << 31 << 25 << 1 << 2 << 3 << 2;
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
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("2: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("3: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 17 << 6 << false << 21 << 18 << 17 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("4: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 8 << 5 << 18 << 6 << false << 21 << 18 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("5: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 7 << 2 << 1 << 0 << 0;
    QTest::newRow("6: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("7: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("8: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("9: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 18 << 0 << 1 << 2 << 1;
    QTest::newRow("10: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 18 << 0 << 1 << 2 << 1;
    QTest::newRow("11: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("12: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 15, "Value1"} << 8 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 18 << 2 << 1 << 2 << 1;
    QTest::newRow("13: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("14: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("15: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << true << 17 << 10 << 21 << 8 << 0 << 1 << 2 << 0;
    QTest::newRow("16: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << true << 18 << 10 << 21 << 8 << 0 << 1 << 2 << 0;
    QTest::newRow("17: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 8 << 21 << 8 << 0 << 0 << 2 << 0;
    QTest::newRow("18: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("19: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("20: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << false << 21 << 10 << 17 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("21: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << false << 21 << 10 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("22: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 6, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 18 << 7 << 2 << 1 << 0 << 0;
    QTest::newRow("23: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("24: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 7, "Value2"} << 8 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 10 << 21 << 8 << 2 << 1 << 2 << 0;
    QTest::newRow("25: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("26: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("27: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 17 << 7 << false << 21 << 18 << 17 << 10 << 2 << 1 << 0 << 1;
    QTest::newRow("28: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 8 << 6 << 18 << 7 << false << 21 << 18 << 18 << 10 << 2 << 1 << 0 << 1;
    QTest::newRow("29: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 18 << 8 << 2 << 1 << 0 << 0;
    QTest::newRow("30: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 21 << 18 << 21 << 10 << 2 << 1 << 2 << 1;
    QTest::newRow("31: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("32: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("33: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("34: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("35: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 18 << 0 << 0 << 2 << 1;
    QTest::newRow("36: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 7 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 18 << 2 << 0 << 2 << 1;
    QTest::newRow("37: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("38: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("39: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 17 << 6 << true << 17 << 8 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("40: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 8 << 5 << 18 << 6 << true << 18 << 8 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("41: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 18 << 7 << 21 << 10 << 0 << 0 << 2 << 1;
    QTest::newRow("42: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("43: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("44: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 17 << 7 << false << 21 << 8 << 17 << 10 << 2 << 0 << 0 << 1;
    QTest::newRow("45: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 8 << 6 << 18 << 7 << false << 21 << 8 << 18 << 10 << 2 << 0 << 0 << 1;
    QTest::newRow("46: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 7, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 18 << 8 << 2 << 0 << 0 << 0;
    QTest::newRow("47: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;
    QTest::newRow("48: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 8, "Value2"} << 7 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 21 << 8 << 21 << 10 << 2 << 0 << 2 << 1;

    // additional tests
    QTest::newRow("49: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 12 << 9 << 18 << 14 << true << 25 << 14 << 25 << 22 << 2 << 1 << 2 << 4;
    QTest::newRow("50: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 25 << 11 << 25 << 22 << 2 << 0 << 2 << 4;
    QTest::newRow("51: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11 << SplitMode::ALL_DIFFERENT << 12 << 9 << 20 << 9 << true << 20 << 13 << 25 << 22 << 0 << 1 << 2 << 4;
    QTest::newRow("52: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{} << StringMatrix{} << 11 << SplitMode::ALL_DIFFERENT << 0 << 0 << 0 << 0 << false << 25 << 13 << 25 << 17 << 2 << 1 << 2 << 1;
    QTest::newRow("53: source first") << StringMatrix{20, 25, "Value1"} << StringMatrix{20, 25, "Value1"} << StringMatrix{9, 18, "Value2"} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 25 << 31 << 25 << 22 << 2 << 3 << 2 << 4;
    QTest::newRow("54: source first") << StringMatrix{20, 25, "Value1"} << StringMatrix{20, 25, "Value1"} << StringMatrix{} << 11 << SplitMode::SOURCE_FIRST << 0 << 0 << 0 << 0 << false << 25 << 31 << 25 << 17 << 2 << 3 << 2 << 1;
    QTest::newRow("55: source second") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{20, 25, "Value1"} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 25 << 11 << 25 << 31 << 2 << 0 << 2 << 3;
    QTest::newRow("56: source second") << StringMatrix{20, 25, "Value1"} << StringMatrix{} << StringMatrix{20, 25, "Value1"} << 11 << SplitMode::SOURCE_SECOND << 0 << 0 << 0 << 0 << false << 25 << 13 << 25 << 31 << 2 << 1 << 2 << 3;
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 9 << 2 << -1 << false << 12 << 9 << 3 << 1;
    QTest::newRow("2: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 8 << 2 << -1 << false << 12 << 8 << 3 << 1;
    QTest::newRow("3: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 7 << 2 << -1 << false << 12 << 7 << 3 << 0;
    QTest::newRow("4: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 6 << 2 << -1 << false << 12 << 6 << 3 << 0;
    QTest::newRow("5: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 5 << 2 << -1 << false << 12 << 6 << 3 << 0;
    QTest::newRow("6: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 4 << 2 << -1 << false << 23 << 6 << 9 << 0;
    QTest::newRow("7: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 3 << 2 << -1 << false << 20 << 6 << 7 << 0;
    QTest::newRow("8: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 2 << 2 << -1 << false << 18 << 6 << 6 << 0;
    QTest::newRow("9: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 9 << -1 << 1 << false << 45 << 9 << 19 << 2;
    QTest::newRow("10: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 8 << -1 << 1 << false << 29 << 8 << 11 << 2;
    QTest::newRow("11: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 7 << -1 << 1 << false << 28 << 7 << 10 << 1;
    QTest::newRow("12: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 6 << -1 << 1 << false << 27 << 6 << 10 << 1;
    QTest::newRow("13: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 5 << -1 << 1 << false << 24 << 6 << 8 << 1;
    QTest::newRow("14: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 4 << -1 << 1 << false << 23 << 6 << 8 << 1;
    QTest::newRow("15: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 3 << -1 << 1 << false << 20 << 6 << 6 << 1;
    QTest::newRow("16: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 2 << -1 << 1 << false << 18 << 6 << 5 << 1;
    QTest::newRow("17: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << -1 << false << 12 << 41 << 3 << 17;
    QTest::newRow("18: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << -1 << false << 12 << 25 << 3 << 9;
    QTest::newRow("19: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << -1 << false << 12 << 24 << 3 << 9;
    QTest::newRow("20: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << -1 << false << 12 << 23 << 3 << 8;
    QTest::newRow("21: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << -1 << false << 12 << 20 << 3 << 7;
    QTest::newRow("22: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << -1 << false << 23 << 19 << 9 << 6;
    QTest::newRow("23: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << -1 << false << 20 << 16 << 7 << 5;
    QTest::newRow("24: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << -1 << false << 18 << 14 << 6 << 4;
    QTest::newRow("25: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("26: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("27: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("28: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("29: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << 1 << false << 12 << 10 << 3 << 2;
    QTest::newRow("30: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << 1 << false << 23 << 19 << 9 << 7;
    QTest::newRow("31: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << 1 << false << 20 << 16 << 7 << 6;
    QTest::newRow("32: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << 1 << false << 18 << 14 << 6 << 5;
    QTest::newRow("33: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 45 << 41 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("34: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 29 << 25 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("35: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 28 << 24 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("36: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 27 << 23 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("37: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 24 << 20 << 2 << 1 << true << 12 << 10 << 3 << 2;
    QTest::newRow("38: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 23 << 19 << 2 << 1 << true << 23 << 19 << 9 << 7;
    QTest::newRow("39: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 20 << 16 << 2 << 1 << true << 20 << 16 << 7 << 6;
    QTest::newRow("40: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7 << 6 << std::string{"Value2"} << 18 << 14 << 2 << 1 << true << 18 << 14 << 6 << 5;
    QTest::newRow("41: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 9 << 45 << -1 << 2 << false << 9 << 12 << 1 << 3;
    QTest::newRow("42: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 8 << 29 << -1 << 2 << false << 8 << 12 << 1 << 3;
    QTest::newRow("43: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 7 << 28 << -1 << 2 << false << 7 << 12 << 0 << 3;
    QTest::newRow("44: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 6 << 27 << -1 << 2 << false << 6 << 12 << 0 << 3;
    QTest::newRow("45: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 5 << 24 << -1 << 2 << false << 6 << 12 << 0 << 3;
    QTest::newRow("46: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 4 << 23 << -1 << 2 << false << 6 << 23 << 0 << 9;
    QTest::newRow("47: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 3 << 20 << -1 << 2 << false << 6 << 20 << 0 << 7;
    QTest::newRow("48: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 2 << 18 << -1 << 2 << false << 6 << 18 << 0 << 6;
    QTest::newRow("49: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 9 << 45 << 1 << -1 << false << 9 << 45 << 2 << 19;
    QTest::newRow("50: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 8 << 29 << 1 << -1 << false << 8 << 29 << 2 << 11;
    QTest::newRow("51: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 7 << 28 << 1 << -1 << false << 7 << 28 << 1 << 10;
    QTest::newRow("52: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 6 << 27 << 1 << -1 << false << 6 << 27 << 1 << 10;
    QTest::newRow("53: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 5 << 24 << 1 << -1 << false << 6 << 24 << 1 << 8;
    QTest::newRow("54: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 4 << 23 << 1 << -1 << false << 6 << 23 << 1 << 8;
    QTest::newRow("55: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 3 << 20 << 1 << -1 << false << 6 << 20 << 1 << 6;
    QTest::newRow("56: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 2 << 18 << 1 << -1 << false << 6 << 18 << 1 << 5;
    QTest::newRow("57: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << -1 << 2 << false << 41 << 12 << 17 << 3;
    QTest::newRow("58: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << -1 << 2 << false << 25 << 12 << 9 << 3;
    QTest::newRow("59: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << -1 << 2 << false << 24 << 12 << 9 << 3;
    QTest::newRow("60: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << -1 << 2 << false << 23 << 12 << 8 << 3;
    QTest::newRow("61: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << -1 << 2 << false << 20 << 12 << 7 << 3;
    QTest::newRow("62: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << -1 << 2 << false << 19 << 23 << 6 << 9;
    QTest::newRow("63: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << -1 << 2 << false << 16 << 20 << 5 << 7;
    QTest::newRow("64: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << -1 << 2 << false << 14 << 18 << 4 << 6;
    QTest::newRow("65: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("66: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("67: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("68: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("69: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << 1 << 2 << true << 10 << 12 << 2 << 3;
    QTest::newRow("70: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << 1 << 2 << true << 19 << 23 << 7 << 9;
    QTest::newRow("71: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << 1 << 2 << true << 16 << 20 << 6 << 7;
    QTest::newRow("72: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << 1 << 2 << true << 14 << 18 << 5 << 6;
    QTest::newRow("73: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 41 << 45 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("74: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 25 << 29 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("75: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 24 << 28 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("76: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 23 << 27 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("77: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 20 << 24 << 1 << 2 << false << 10 << 12 << 2 << 3;
    QTest::newRow("78: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 19 << 23 << 1 << 2 << false << 19 << 23 << 7 << 9;
    QTest::newRow("79: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 16 << 20 << 1 << 2 << false << 16 << 20 << 6 << 7;
    QTest::newRow("80: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6 << 7 << std::string{"Value2"} << 14 << 18 << 1 << 2 << false << 14 << 18 << 5 << 6;
}

void CapacityTests::_buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << 4 << -1 << 3 << 5 << 0 << 0;
    QTest::newRow("2: small size matrix") << 4 << 3 << -1 << 5 << 3 << 0 << 0;
    QTest::newRow("3: medium size matrix") << 7 << 8 << -1 << 8 << 10 << 0 << 1;
    QTest::newRow("4: medium size matrix") << 8 << 7 << -1 << 10 << 8 << 1 << 0;
    QTest::newRow("5: large size matrix") << 20 << 25 << -1 << 25 << 31 << 2 << 3;
    QTest::newRow("6: large size matrix") << 25 << 20 << -1 << 31 << 25 << 3 << 2;
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << 3 << 4 << -1 << 0 << 0 << 0 << 3 << 5 << 0 << 0;
    QTest::newRow("2: destination matrix initially empty") << 4 << 3 << -1 << 0 << 0 << 0 << 5 << 3 << 0 << 0;
    QTest::newRow("3: destination matrix initially empty") << 7 << 8 << -1 << 0 << 0 << 0 << 8 << 10 << 0 << 1;
    QTest::newRow("4: destination matrix initially empty") << 8 << 7 << -1 << 0 << 0 << 0 << 10 << 8 << 1 << 0;
    QTest::newRow("5: destination matrix initially empty") << 20 << 25 << -1 << 0 << 0 << 0 << 25 << 31 << 2 << 3;
    QTest::newRow("6: destination matrix initially empty") << 25 << 20 << -1 << 0 << 0 << 0 << 31 << 25 << 3 << 2;
    QTest::newRow("7: destination matrix initially NOT empty") << 3 << 4 << -1 << 2 << 3 << -5 << 3 << 5 << 0 << 0;
    QTest::newRow("8: destination matrix initially NOT empty") << 4 << 3 << -1 << 2 << 3 << -5 << 5 << 3 << 0 << 0;
    QTest::newRow("9: destination matrix initially NOT empty") << 7 << 8 << -1 << 3 << 4 << -5 << 8 << 10 << 0 << 1;
    QTest::newRow("10: destination matrix initially NOT empty") << 8 << 7 << -1 << 3 << 4 << -5 << 10 << 8 << 1 << 0;
    QTest::newRow("11: destination matrix initially NOT empty") << 20 << 25 << -1 << 15 << 20 << -5 << 25 << 31 << 2 << 3;
    QTest::newRow("12: destination matrix initially NOT empty") << 25 << 20 << -1 << 15 << 20 << -5 << 31 << 25 << 3 << 2;
    QTest::newRow("13: destination matrix initially NOT empty") << 20 << 25 << -1 << 25 << 20 << -5 << 25 << 31 << 2 << 3;
    QTest::newRow("14: destination matrix initially NOT empty") << 25 << 20 << -1 << 20 << 25 << -5 << 31 << 25 << 3 << 2;
    QTest::newRow("15: destination matrix initially NOT empty") << 25 << 20 << -1 << 25 << 20 << -5 << 31 << 25 << 3 << 2;
    QTest::newRow("16: destination matrix initially NOT empty") << 15 << 20 << -1 << 20 << 25 << -5 << 18 << 25 << 1 << 2;
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
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("2: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("3: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("4: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("5: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("6: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("7: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 9 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("8: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("9: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("10: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("11: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("12: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("13: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("14: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 10 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("15: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("16: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("17: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("18: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("19: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("20: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("21: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 11 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("22: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 6 << 12 << 7 << 1 << 0;
    QTest::newRow("23: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 7 << 12 << 7 << 1 << 0;
    QTest::newRow("24: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("25: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 9 << 12 << 9 << 1 << 1;
    QTest::newRow("26: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("27: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 11 << 12 << 11 << 1 << 2;
    QTest::newRow("28: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 12 << 0 << 12 << 7 << 1 << 0;
    QTest::newRow("29: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 6 << 13 << 7 << 1 << 0;
    QTest::newRow("30: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 7 << 13 << 7 << 1 << 0;
    QTest::newRow("31: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("32: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 9 << 13 << 9 << 1 << 1;
    QTest::newRow("33: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("34: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 11 << 13 << 11 << 1 << 2;
    QTest::newRow("35: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 13 << 0 << 13 << 7 << 1 << 0;
    QTest::newRow("36: equal rows, less columns") << IntMatrix{10, 8, -2} << 10 << 7 << -5 << 0 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("37: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 7 << 9 << 8 << 0 << 0;
    QTest::newRow("38: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("39: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("40: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("41: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("42: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 8 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("43: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 7 << 9 << 8 << 0 << 0;
    QTest::newRow("44: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("45: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("46: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("47: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("48: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 9 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("49: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("50: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("51: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("52: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("53: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("54: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 10 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("55: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("56: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("57: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 9 << 11 << 9 << 1 << 0;
    QTest::newRow("58: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 10 << 11 << 10 << 1 << 1;
    QTest::newRow("59: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 11 << 11 << 11 << 1 << 1;
    QTest::newRow("60: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 11 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("61: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 7 << 12 << 8 << 1 << 0;
    QTest::newRow("62: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("63: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("64: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("65: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("66: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 12 << 0 << 12 << 8 << 1 << 0;
    QTest::newRow("67: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 7 << 13 << 8 << 2 << 0;
    QTest::newRow("68: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 8 << 13 << 8 << 2 << 0;
    QTest::newRow("69: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 9 << 13 << 9 << 2 << 0;
    QTest::newRow("70: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 10 << 13 << 10 << 2 << 1;
    QTest::newRow("71: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 11 << 13 << 11 << 2 << 1;
    QTest::newRow("72: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 13 << 0 << 13 << 8 << 2 << 0;
    QTest::newRow("73: less rows, equal columns") << IntMatrix{10, 8, -2} << 9 << 8 << -5 << 0 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("74: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 6 << 9 << 7 << 0 << 0;
    QTest::newRow("75: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 7 << 9 << 7 << 0 << 0;
    QTest::newRow("76: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("77: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 9 << 9 << 9 << 0 << 1;
    QTest::newRow("78: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("79: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 11 << 9 << 11 << 0 << 2;
    QTest::newRow("80: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 8 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("81: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 6 << 9 << 7 << 0 << 0;
    QTest::newRow("82: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 7 << 9 << 7 << 0 << 0;
    QTest::newRow("83: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("84: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 9 << 9 << 9 << 0 << 1;
    QTest::newRow("85: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("86: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 11 << 9 << 11 << 0 << 2;
    QTest::newRow("87: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 9 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("88: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("89: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("90: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("91: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("92: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("93: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("94: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 10 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("95: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 6 << 11 << 7 << 1 << 0;
    QTest::newRow("96: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 7 << 11 << 7 << 1 << 0;
    QTest::newRow("97: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("98: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 9 << 11 << 9 << 1 << 1;
    QTest::newRow("99: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 10 << 11 << 10 << 1 << 1;
    QTest::newRow("100: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 11 << 11 << 11 << 1 << 2;
    QTest::newRow("101: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 11 << 0 << 11 << 7 << 1 << 0;
    QTest::newRow("102: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 6 << 12 << 7 << 1 << 0;
    QTest::newRow("103: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 7 << 12 << 7 << 1 << 0;
    QTest::newRow("104: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("105: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 9 << 12 << 9 << 1 << 1;
    QTest::newRow("106: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("107: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 11 << 12 << 11 << 1 << 2;
    QTest::newRow("108: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 12 << 0 << 12 << 7 << 1 << 0;
    QTest::newRow("109: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 6 << 13 << 7 << 2 << 0;
    QTest::newRow("110: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 7 << 13 << 7 << 2 << 0;
    QTest::newRow("111: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 8 << 13 << 8 << 2 << 0;
    QTest::newRow("112: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 9 << 13 << 9 << 2 << 1;
    QTest::newRow("113: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 10 << 13 << 10 << 2 << 1;
    QTest::newRow("114: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 11 << 13 << 11 << 2 << 2;
    QTest::newRow("115: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 13 << 0 << 13 << 7 << 2 << 0;
    QTest::newRow("116: less rows, less columns") << IntMatrix{10, 8, -2} << 9 << 7 << -5 << 0 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("117: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("118: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("119: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("120: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("121: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("122: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 9 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("123: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("124: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("125: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("126: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("127: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("128: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 10 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("129: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("130: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("131: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("132: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("133: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("134: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 11 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("135: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 7 << 12 << 8 << 1 << 0;
    QTest::newRow("136: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("137: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("138: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("139: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("140: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 12 << 0 << 12 << 8 << 1 << 0;
    QTest::newRow("141: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 7 << 13 << 8 << 1 << 0;
    QTest::newRow("142: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("143: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("144: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("145: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("146: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 13 << 0 << 13 << 8 << 1 << 0;
    QTest::newRow("147: same rows, same columns") << IntMatrix{10, 8, -2} << 10 << 8 << -5 << 0 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("148: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("149: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("150: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("151: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("152: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("153: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 9 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("154: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("155: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("156: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("157: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("158: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("159: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 10 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("160: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("161: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("162: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("163: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("164: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("165: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 11 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("166: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 7 << 12 << 8 << 0 << 0;
    QTest::newRow("167: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 8 << 12 << 8 << 0 << 0;
    QTest::newRow("168: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 9 << 12 << 9 << 0 << 0;
    QTest::newRow("169: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 10 << 12 << 10 << 0 << 1;
    QTest::newRow("170: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 11 << 12 << 11 << 0 << 1;
    QTest::newRow("171: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 12 << 0 << 12 << 8 << 0 << 0;
    QTest::newRow("172: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 7 << 13 << 8 << 1 << 0;
    QTest::newRow("173: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("174: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("175: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("176: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("177: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 13 << 0 << 13 << 8 << 1 << 0;
    QTest::newRow("178: more rows, same columns") << IntMatrix{10, 8, -2} << 11 << 8 << -5 << 0 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("179: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("180: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("181: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("182: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("183: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("184: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 9 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("185: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("186: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("187: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("188: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("189: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("190: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 10 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("191: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("192: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("193: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("194: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("195: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("196: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 11 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("197: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 7 << 12 << 9 << 1 << 0;
    QTest::newRow("198: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 8 << 12 << 9 << 1 << 0;
    QTest::newRow("199: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("200: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 10 << 12 << 10 << 1 << 0;
    QTest::newRow("201: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("202: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 12 << 0 << 12 << 9 << 1 << 0;
    QTest::newRow("203: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 7 << 13 << 9 << 1 << 0;
    QTest::newRow("204: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 8 << 13 << 9 << 1 << 0;
    QTest::newRow("205: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("206: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 10 << 13 << 10 << 1 << 0;
    QTest::newRow("207: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("208: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 13 << 0 << 13 << 9 << 1 << 0;
    QTest::newRow("209: same rows, more columns") << IntMatrix{10, 8, -2} << 10 << 9 << -5 << 0 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("210: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("211: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("212: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("213: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("214: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("215: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 9 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("216: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("217: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("218: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("219: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("220: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("221: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 10 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("222: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("223: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("224: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("225: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("226: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("227: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 11 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("228: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 7 << 12 << 9 << 0 << 0;
    QTest::newRow("229: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 8 << 12 << 9 << 0 << 0;
    QTest::newRow("230: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 9 << 12 << 9 << 0 << 0;
    QTest::newRow("231: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 10 << 12 << 10 << 0 << 0;
    QTest::newRow("232: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 11 << 12 << 11 << 0 << 1;
    QTest::newRow("233: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 12 << 0 << 12 << 9 << 0 << 0;
    QTest::newRow("234: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 7 << 13 << 9 << 1 << 0;
    QTest::newRow("235: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 8 << 13 << 9 << 1 << 0;
    QTest::newRow("236: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("237: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 10 << 13 << 10 << 1 << 0;
    QTest::newRow("238: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("239: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 13 << 0 << 13 << 9 << 1 << 0;
    QTest::newRow("240: more rows, more columns") << IntMatrix{10, 8, -2} << 11 << 9 << -5 << 0 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("241: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("242: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("243: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("244: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("245: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("246: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("247: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 9 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("248: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("249: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("250: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("251: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("252: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("253: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("254: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 10 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("255: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("256: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("257: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("258: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("259: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("260: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("261: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 11 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("262: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 6 << 12 << 7 << 0 << 0;
    QTest::newRow("263: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 7 << 12 << 7 << 0 << 0;
    QTest::newRow("264: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 8 << 12 << 8 << 0 << 0;
    QTest::newRow("265: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 9 << 12 << 9 << 0 << 1;
    QTest::newRow("266: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 10 << 12 << 10 << 0 << 1;
    QTest::newRow("267: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 11 << 12 << 11 << 0 << 2;
    QTest::newRow("268: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 12 << 0 << 12 << 7 << 0 << 0;
    QTest::newRow("269: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 6 << 13 << 7 << 1 << 0;
    QTest::newRow("270: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 7 << 13 << 7 << 1 << 0;
    QTest::newRow("271: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("272: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 9 << 13 << 9 << 1 << 1;
    QTest::newRow("273: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("274: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 11 << 13 << 11 << 1 << 2;
    QTest::newRow("275: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 13 << 0 << 13 << 7 << 1 << 0;
    QTest::newRow("276: more rows, less columns") << IntMatrix{10, 8, -2} << 11 << 7 << -5 << 0 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("277: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 7 << 9 << 9 << 0 << 0;
    QTest::newRow("278: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 8 << 9 << 9 << 0 << 0;
    QTest::newRow("279: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("280: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 10 << 9 << 10 << 0 << 0;
    QTest::newRow("281: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("282: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 8 << 0 << 9 << 9 << 0 << 0;
    QTest::newRow("283: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 7 << 9 << 9 << 0 << 0;
    QTest::newRow("284: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 8 << 9 << 9 << 0 << 0;
    QTest::newRow("285: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("286: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 10 << 9 << 10 << 0 << 0;
    QTest::newRow("287: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("288: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 9 << 0 << 9 << 9 << 0 << 0;
    QTest::newRow("289: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("290: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("291: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("292: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("293: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("294: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 10 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("295: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 7 << 11 << 9 << 1 << 0;
    QTest::newRow("296: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 8 << 11 << 9 << 1 << 0;
    QTest::newRow("297: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 9 << 11 << 9 << 1 << 0;
    QTest::newRow("298: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 10 << 11 << 10 << 1 << 0;
    QTest::newRow("299: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 11 << 11 << 11 << 1 << 1;
    QTest::newRow("300: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 11 << 0 << 11 << 9 << 1 << 0;
    QTest::newRow("301: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 7 << 12 << 9 << 1 << 0;
    QTest::newRow("302: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 8 << 12 << 9 << 1 << 0;
    QTest::newRow("303: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("304: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 10 << 12 << 10 << 1 << 0;
    QTest::newRow("305: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("306: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 12 << 0 << 12 << 9 << 1 << 0;
    QTest::newRow("307: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 7 << 13 << 9 << 2 << 0;
    QTest::newRow("308: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 8 << 13 << 9 << 2 << 0;
    QTest::newRow("309: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 9 << 13 << 9 << 2 << 0;
    QTest::newRow("310: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 10 << 13 << 10 << 2 << 0;
    QTest::newRow("311: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 11 << 13 << 11 << 2 << 1;
    QTest::newRow("312: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 13 << 0 << 13 << 9 << 2 << 0;
    QTest::newRow("313: less rows, more columns") << IntMatrix{10, 8, -2} << 9 << 9 << -5 << 0 << 0 << 9 << 9 << 0 << 0;

    // empty matrix
    QTest::newRow("314: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 0 << 1 << 1 << 0 << 0;
    QTest::newRow("315: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 1 << 1 << 1 << 0 << 0;
    QTest::newRow("316: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 2 << 1 << 2 << 0 << 0;
    QTest::newRow("317: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 0 << 3 << 1 << 3 << 0 << 1;
    QTest::newRow("318: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 0 << 1 << 1 << 0 << 0;
    QTest::newRow("319: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 1 << 1 << 1 << 0 << 0;
    QTest::newRow("320: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 2 << 1 << 2 << 0 << 0;
    QTest::newRow("321: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 1 << 3 << 1 << 3 << 0 << 1;
    QTest::newRow("322: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 0 << 2 << 1 << 0 << 0;
    QTest::newRow("323: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 1 << 2 << 1 << 0 << 0;
    QTest::newRow("324: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 2 << 2 << 2 << 0 << 0;
    QTest::newRow("325: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 2 << 3 << 2 << 3 << 0 << 1;
    QTest::newRow("326: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 0 << 3 << 1 << 1 << 0;
    QTest::newRow("327: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 1 << 3 << 1 << 1 << 0;
    QTest::newRow("328: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 2 << 3 << 2 << 1 << 0;
    QTest::newRow("329: more rows, more columns") << IntMatrix{} << 1 << 1 << -5 << 3 << 3 << 3 << 3 << 1 << 1;
}

void CapacityTests::_buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3 << 4 << std::string{"Value"} << 3 << 5 << 0 << 0;
    QTest::newRow("2: small size matrix") << 4 << 3 << std::string{"Value"} << 5 << 3 << 0 << 0;
    QTest::newRow("3: medium size matrix") << 7 << 8 << std::string{"Value"} << 8 << 10 << 0 << 1;
    QTest::newRow("4: medium size matrix") << 8 << 7 << std::string{"Value"} << 10 << 8 << 1 << 0;
    QTest::newRow("5: large size matrix") << 20 << 25 << std::string{"Value"} << 25 << 31 << 2 << 3;
    QTest::newRow("6: large size matrix") << 25 << 20 << std::string{"Value"} << 31 << 25 << 3 << 2;
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << 3 << 4 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 3 << 5 << 0 << 0;
    QTest::newRow("2: destination matrix initially empty") << 4 << 3 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 5 << 3 << 0 << 0;
    QTest::newRow("3: destination matrix initially empty") << 7 << 8 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 8 << 10 << 0 << 1;
    QTest::newRow("4: destination matrix initially empty") << 8 << 7 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 10 << 8 << 1 << 0;
    QTest::newRow("5: destination matrix initially empty") << 20 << 25 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 25 << 31 << 2 << 3;
    QTest::newRow("6: destination matrix initially empty") << 25 << 20 << std::string{"Value1"} << 0 << 0 << std::string{"Value2"} << 31 << 25 << 3 << 2;
    QTest::newRow("7: destination matrix initially NOT empty") << 3 << 4 << std::string{"Value1"} << 2 << 3 << std::string{"Value3"} << 3 << 5 << 0 << 0;
    QTest::newRow("8: destination matrix initially NOT empty") << 4 << 3 << std::string{"Value1"} << 2 << 3 << std::string{"Value3"} << 5 << 3 << 0 << 0;
    QTest::newRow("9: destination matrix initially NOT empty") << 7 << 8 << std::string{"Value1"} << 3 << 4 << std::string{"Value3"} << 8 << 10 << 0 << 1;
    QTest::newRow("10: destination matrix initially NOT empty") << 8 << 7 << std::string{"Value1"} << 3 << 4 << std::string{"Value3"} << 10 << 8 << 1 << 0;
    QTest::newRow("11: destination matrix initially NOT empty") << 20 << 25 << std::string{"Value1"} << 15 << 20 << std::string{"Value3"} << 25 << 31 << 2 << 3;
    QTest::newRow("12: destination matrix initially NOT empty") << 25 << 20 << std::string{"Value1"} << 15 << 20 << std::string{"Value3"} << 31 << 25 << 3 << 2;
    QTest::newRow("13: destination matrix initially NOT empty") << 20 << 25 << std::string{"Value1"} << 25 << 20 << std::string{"Value3"} << 25 << 31 << 2 << 3;
    QTest::newRow("14: destination matrix initially NOT empty") << 25 << 20 << std::string{"Value1"} << 20 << 25 << std::string{"Value3"} << 31 << 25 << 3 << 2;
    QTest::newRow("15: destination matrix initially NOT empty") << 25 << 20 << std::string{"Value1"} << 25 << 20 << std::string{"Value3"} << 31 << 25 << 3 << 2;
    QTest::newRow("16: destination matrix initially NOT empty") << 15 << 20 << std::string{"Value1"} << 20 << 25 << std::string{"Value3"} << 18 << 25 << 1 << 2;
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
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("2: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("3: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("4: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("5: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("6: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("7: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 9 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("8: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("9: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("10: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("11: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("12: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("13: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("14: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 10 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("15: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("16: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("17: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("18: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("19: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("20: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("21: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("22: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7 << 1 << 0;
    QTest::newRow("23: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7 << 1 << 0;
    QTest::newRow("24: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("25: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 1;
    QTest::newRow("26: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("27: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 2;
    QTest::newRow("28: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7 << 1 << 0;
    QTest::newRow("29: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7 << 1 << 0;
    QTest::newRow("30: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7 << 1 << 0;
    QTest::newRow("31: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("32: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 1;
    QTest::newRow("33: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("34: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 2;
    QTest::newRow("35: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7 << 1 << 0;
    QTest::newRow("36: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10 << 7 << std::string{"Value2"} << 0 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("37: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 7 << 9 << 8 << 0 << 0;
    QTest::newRow("38: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("39: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("40: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("41: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("42: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 8 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("43: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 7 << 9 << 8 << 0 << 0;
    QTest::newRow("44: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("45: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("46: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("47: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("48: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 9 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("49: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("50: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("51: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("52: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("53: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("54: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 10 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("55: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8 << 1 << 0;
    QTest::newRow("56: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("57: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 1 << 0;
    QTest::newRow("58: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 1 << 1;
    QTest::newRow("59: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 1 << 1;
    QTest::newRow("60: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8 << 1 << 0;
    QTest::newRow("61: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8 << 1 << 0;
    QTest::newRow("62: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("63: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("64: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("65: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("66: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8 << 1 << 0;
    QTest::newRow("67: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8 << 2 << 0;
    QTest::newRow("68: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 2 << 0;
    QTest::newRow("69: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 2 << 0;
    QTest::newRow("70: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 2 << 1;
    QTest::newRow("71: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 2 << 1;
    QTest::newRow("72: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8 << 2 << 0;
    QTest::newRow("73: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9 << 8 << std::string{"Value2"} << 0 << 0 << 9 << 8 << 0 << 0;
    QTest::newRow("74: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 6 << 9 << 7 << 0 << 0;
    QTest::newRow("75: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 7 << 9 << 7 << 0 << 0;
    QTest::newRow("76: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("77: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 9 << 9 << 9 << 0 << 1;
    QTest::newRow("78: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("79: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 11 << 9 << 11 << 0 << 2;
    QTest::newRow("80: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 8 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("81: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 6 << 9 << 7 << 0 << 0;
    QTest::newRow("82: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 7 << 9 << 7 << 0 << 0;
    QTest::newRow("83: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 8 << 9 << 8 << 0 << 0;
    QTest::newRow("84: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 9 << 9 << 9 << 0 << 1;
    QTest::newRow("85: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 10 << 9 << 10 << 0 << 1;
    QTest::newRow("86: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 11 << 9 << 11 << 0 << 2;
    QTest::newRow("87: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 9 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("88: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 6 << 10 << 7 << 0 << 0;
    QTest::newRow("89: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 7 << 10 << 7 << 0 << 0;
    QTest::newRow("90: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("91: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 1;
    QTest::newRow("92: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("93: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 2;
    QTest::newRow("94: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 10 << 0 << 10 << 7 << 0 << 0;
    QTest::newRow("95: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7 << 1 << 0;
    QTest::newRow("96: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7 << 1 << 0;
    QTest::newRow("97: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 1 << 0;
    QTest::newRow("98: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 1 << 1;
    QTest::newRow("99: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 1 << 1;
    QTest::newRow("100: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 1 << 2;
    QTest::newRow("101: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7 << 1 << 0;
    QTest::newRow("102: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7 << 1 << 0;
    QTest::newRow("103: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7 << 1 << 0;
    QTest::newRow("104: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("105: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 1;
    QTest::newRow("106: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("107: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 2;
    QTest::newRow("108: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7 << 1 << 0;
    QTest::newRow("109: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7 << 2 << 0;
    QTest::newRow("110: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7 << 2 << 0;
    QTest::newRow("111: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 2 << 0;
    QTest::newRow("112: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 2 << 1;
    QTest::newRow("113: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 2 << 1;
    QTest::newRow("114: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 2 << 2;
    QTest::newRow("115: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7 << 2 << 0;
    QTest::newRow("116: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9 << 7 << std::string{"Value2"} << 0 << 0 << 9 << 7 << 0 << 0;
    QTest::newRow("117: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("118: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("119: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("120: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("121: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("122: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 9 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("123: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 7 << 10 << 8 << 0 << 0;
    QTest::newRow("124: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 8 << 10 << 8 << 0 << 0;
    QTest::newRow("125: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("126: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 1;
    QTest::newRow("127: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("128: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 10 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("129: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("130: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("131: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("132: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("133: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("134: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("135: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8 << 1 << 0;
    QTest::newRow("136: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 1 << 0;
    QTest::newRow("137: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("138: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 1;
    QTest::newRow("139: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("140: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8 << 1 << 0;
    QTest::newRow("141: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8 << 1 << 0;
    QTest::newRow("142: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("143: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("144: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("145: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("146: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8 << 1 << 0;
    QTest::newRow("147: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10 << 8 << std::string{"Value2"} << 0 << 0 << 10 << 8 << 0 << 0;
    QTest::newRow("148: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("149: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("150: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("151: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("152: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("153: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 9 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("154: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("155: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("156: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("157: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("158: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("159: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 10 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("160: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 7 << 11 << 8 << 0 << 0;
    QTest::newRow("161: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("162: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("163: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("164: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("165: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 11 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("166: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 7 << 12 << 8 << 0 << 0;
    QTest::newRow("167: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 0 << 0;
    QTest::newRow("168: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 0 << 0;
    QTest::newRow("169: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 0 << 1;
    QTest::newRow("170: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 0 << 1;
    QTest::newRow("171: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 12 << 0 << 12 << 8 << 0 << 0;
    QTest::newRow("172: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 7 << 13 << 8 << 1 << 0;
    QTest::newRow("173: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("174: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("175: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("176: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("177: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 13 << 0 << 13 << 8 << 1 << 0;
    QTest::newRow("178: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11 << 8 << std::string{"Value2"} << 0 << 0 << 11 << 8 << 0 << 0;
    QTest::newRow("179: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("180: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("181: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("182: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("183: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("184: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 9 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("185: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("186: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("187: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("188: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("189: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("190: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 10 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("191: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("192: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("193: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("194: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("195: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("196: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("197: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9 << 1 << 0;
    QTest::newRow("198: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9 << 1 << 0;
    QTest::newRow("199: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("200: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 0;
    QTest::newRow("201: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("202: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9 << 1 << 0;
    QTest::newRow("203: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9 << 1 << 0;
    QTest::newRow("204: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9 << 1 << 0;
    QTest::newRow("205: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("206: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 0;
    QTest::newRow("207: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("208: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9 << 1 << 0;
    QTest::newRow("209: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10 << 9 << std::string{"Value2"} << 0 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("210: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("211: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("212: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("213: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("214: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("215: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 9 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("216: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("217: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("218: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("219: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("220: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("221: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 10 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("222: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9 << 0 << 0;
    QTest::newRow("223: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9 << 0 << 0;
    QTest::newRow("224: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 0;
    QTest::newRow("225: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 0;
    QTest::newRow("226: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 1;
    QTest::newRow("227: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("228: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9 << 0 << 0;
    QTest::newRow("229: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9 << 0 << 0;
    QTest::newRow("230: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 0 << 0;
    QTest::newRow("231: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 0 << 0;
    QTest::newRow("232: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 0 << 1;
    QTest::newRow("233: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9 << 0 << 0;
    QTest::newRow("234: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9 << 1 << 0;
    QTest::newRow("235: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9 << 1 << 0;
    QTest::newRow("236: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 0;
    QTest::newRow("237: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 0;
    QTest::newRow("238: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 1;
    QTest::newRow("239: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9 << 1 << 0;
    QTest::newRow("240: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11 << 9 << std::string{"Value2"} << 0 << 0 << 11 << 9 << 0 << 0;
    QTest::newRow("241: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("242: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("243: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("244: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("245: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("246: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("247: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 9 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("248: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("249: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("250: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("251: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("252: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("253: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("254: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 10 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("255: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 6 << 11 << 7 << 0 << 0;
    QTest::newRow("256: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 7 << 11 << 7 << 0 << 0;
    QTest::newRow("257: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 8 << 11 << 8 << 0 << 0;
    QTest::newRow("258: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 0 << 1;
    QTest::newRow("259: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 0 << 1;
    QTest::newRow("260: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 0 << 2;
    QTest::newRow("261: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 11 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("262: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 6 << 12 << 7 << 0 << 0;
    QTest::newRow("263: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 7 << 12 << 7 << 0 << 0;
    QTest::newRow("264: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 8 << 12 << 8 << 0 << 0;
    QTest::newRow("265: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 0 << 1;
    QTest::newRow("266: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 0 << 1;
    QTest::newRow("267: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 0 << 2;
    QTest::newRow("268: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 12 << 0 << 12 << 7 << 0 << 0;
    QTest::newRow("269: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 6 << 13 << 7 << 1 << 0;
    QTest::newRow("270: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 7 << 13 << 7 << 1 << 0;
    QTest::newRow("271: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 8 << 13 << 8 << 1 << 0;
    QTest::newRow("272: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 1 << 1;
    QTest::newRow("273: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 1 << 1;
    QTest::newRow("274: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 1 << 2;
    QTest::newRow("275: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 13 << 0 << 13 << 7 << 1 << 0;
    QTest::newRow("276: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11 << 7 << std::string{"Value2"} << 0 << 0 << 11 << 7 << 0 << 0;
    QTest::newRow("277: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 7 << 9 << 9 << 0 << 0;
    QTest::newRow("278: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 8 << 9 << 9 << 0 << 0;
    QTest::newRow("279: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("280: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 10 << 9 << 10 << 0 << 0;
    QTest::newRow("281: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("282: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 8 << 0 << 9 << 9 << 0 << 0;
    QTest::newRow("283: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 7 << 9 << 9 << 0 << 0;
    QTest::newRow("284: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 8 << 9 << 9 << 0 << 0;
    QTest::newRow("285: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 9 << 9 << 9 << 0 << 0;
    QTest::newRow("286: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 10 << 9 << 10 << 0 << 0;
    QTest::newRow("287: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 11 << 9 << 11 << 0 << 1;
    QTest::newRow("288: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 9 << 0 << 9 << 9 << 0 << 0;
    QTest::newRow("289: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 7 << 10 << 9 << 0 << 0;
    QTest::newRow("290: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 8 << 10 << 9 << 0 << 0;
    QTest::newRow("291: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 9 << 10 << 9 << 0 << 0;
    QTest::newRow("292: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 10 << 10 << 10 << 0 << 0;
    QTest::newRow("293: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 11 << 10 << 11 << 0 << 1;
    QTest::newRow("294: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 10 << 0 << 10 << 9 << 0 << 0;
    QTest::newRow("295: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 7 << 11 << 9 << 1 << 0;
    QTest::newRow("296: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 8 << 11 << 9 << 1 << 0;
    QTest::newRow("297: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 9 << 11 << 9 << 1 << 0;
    QTest::newRow("298: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 10 << 11 << 10 << 1 << 0;
    QTest::newRow("299: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 11 << 11 << 11 << 1 << 1;
    QTest::newRow("300: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 11 << 0 << 11 << 9 << 1 << 0;
    QTest::newRow("301: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 7 << 12 << 9 << 1 << 0;
    QTest::newRow("302: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 8 << 12 << 9 << 1 << 0;
    QTest::newRow("303: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 9 << 12 << 9 << 1 << 0;
    QTest::newRow("304: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 10 << 12 << 10 << 1 << 0;
    QTest::newRow("305: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 11 << 12 << 11 << 1 << 1;
    QTest::newRow("306: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 12 << 0 << 12 << 9 << 1 << 0;
    QTest::newRow("307: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 7 << 13 << 9 << 2 << 0;
    QTest::newRow("308: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 8 << 13 << 9 << 2 << 0;
    QTest::newRow("309: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 9 << 13 << 9 << 2 << 0;
    QTest::newRow("310: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 10 << 13 << 10 << 2 << 0;
    QTest::newRow("311: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 11 << 13 << 11 << 2 << 1;
    QTest::newRow("312: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 13 << 0 << 13 << 9 << 2 << 0;
    QTest::newRow("313: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9 << 9 << std::string{"Value2"} << 0 << 0 << 9 << 9 << 0 << 0;

    // empty matrix
    QTest::newRow("314: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 0 << 1 << 1 << 0 << 0;
    QTest::newRow("315: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 1 << 1 << 1 << 0 << 0;
    QTest::newRow("316: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 2 << 1 << 2 << 0 << 0;
    QTest::newRow("317: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 0 << 3 << 1 << 3 << 0 << 1;
    QTest::newRow("318: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 0 << 1 << 1 << 0 << 0;
    QTest::newRow("319: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 1 << 1 << 1 << 0 << 0;
    QTest::newRow("320: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 2 << 1 << 2 << 0 << 0;
    QTest::newRow("321: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 1 << 3 << 1 << 3 << 0 << 1;
    QTest::newRow("322: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 0 << 2 << 1 << 0 << 0;
    QTest::newRow("323: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 1 << 2 << 1 << 0 << 0;
    QTest::newRow("324: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 2 << 2 << 2 << 0 << 0;
    QTest::newRow("325: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 2 << 3 << 2 << 3 << 0 << 1;
    QTest::newRow("326: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 0 << 3 << 1 << 1 << 0;
    QTest::newRow("327: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 1 << 3 << 1 << 1 << 0;
    QTest::newRow("328: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 2 << 3 << 2 << 1 << 0;
    QTest::newRow("329: more rows, more columns") << StringMatrix{} << 1 << 1 << std::string{"Value2"} << 3 << 3 << 3 << 3 << 1 << 1;
}

QTEST_APPLESS_MAIN(CapacityTests)

#include "tst_capacitytests.moc"
