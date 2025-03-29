#include <QtTest>

#include "testutils.h"
#include "tst_capacitytests.h"
#include "tst_resizingtests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(SizeTypeTuple) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(SizeTypeTupleArray) // same here
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
    QFETCH(IntMatrixOptSizeType, expectedRowCapacityOffset);
    QFETCH(IntMatrixOptSizeType, expectedColumnCapacityOffset);

    mPrimaryIntMatrix = matrix;
    mSecondaryIntMatrix = mPrimaryIntMatrix;

    const IntMatrixSizeType c_RetainedNrOfRows{std::min(resizeRowsCount, mSecondaryIntMatrix.getNrOfRows())};
    const IntMatrixSizeType c_RetainedNrOfColumns{std::min(resizeColumnsCount, mSecondaryIntMatrix.getNrOfColumns())};

    mPrimaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount);
    mSecondaryIntMatrix.resize(resizeRowsCount, resizeColumnsCount, requestedRowCapacity, requestedColumnCapacity);

    TEST_RESIZE_CHECK_MATRIX_SIZE_AND_CAPACITY(mSecondaryIntMatrix, mPrimaryIntMatrix.getNrOfRows(), mPrimaryIntMatrix.getNrOfColumns(),
                                               expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);

    bool areRetainedValuesCorrect{true};

    for (IntMatrixSizeType rowNr{0u}; rowNr < c_RetainedNrOfRows; ++rowNr)
    {
        for (IntMatrixSizeType columnNr{0u}; columnNr < c_RetainedNrOfColumns; ++columnNr)
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
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 3u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u});
    }

    {
        StringMatrix matrix{4, 3, {"Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value", "Value"}};
        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 5u, 3u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u});
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 10u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u});
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

        TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, 12u, 10u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u});
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
    QFETCH(StringMatrixOptSizeType, expectedRowCapacityOffset);
    QFETCH(StringMatrixOptSizeType, expectedColumnCapacityOffset);

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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << 4u << -5 << 3u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << 3u << -5 << 5u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: large size matrix") << 25u << 20u << -2 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("4: large size matrix") << 20u << 25u << -2 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
}

void CapacityTests::testIntMatrixCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<IntMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowColumnCapacity");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << -2 << -3 << 3u << IntMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << -2 << -3 << 5u << IntMatrixOptSizeType{0u};
    QTest::newRow("3: medium size matrix") << 8u << -2 << -3 << 10u << IntMatrixOptSizeType{1u};
    QTest::newRow("4: medium size matrix") << 10u << -2 << -3 << 12u << IntMatrixOptSizeType{1u};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << IntMatrix{3, 4, 2} << IntMatrix{} << 5u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("2: transposed matrix initially empty") << IntMatrix{4, 3, 2} << IntMatrix{} << 3u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("3: transposed matrix initially empty") << IntMatrix{7, 8, 2} << IntMatrix{} << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("4: transposed matrix initially empty") << IntMatrix{8, 7, 2} << IntMatrix{} << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << false;
    QTest::newRow("5: transposed matrix initially empty") << IntMatrix{20, 25, 2} << IntMatrix{} << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << false;
    QTest::newRow("6: transposed matrix initially empty") << IntMatrix{25, 20, 2} << IntMatrix{} << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 6, 2} << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 6, 2} << 7u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{5, 7, 2} << 8u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{6, 7, 2} << 7u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << IntMatrix{8, 7, 2} << IntMatrix{7, 8, 2} << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 19, 2} << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 19, 2} << 20u << 31u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 20, 2} << 25u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 20, 2} << 20u << 25u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 25, 2} << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{15, 25, 2} << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{16, 25, 2} << 20u << 31u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 19, 2} << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << IntMatrix{25, 20, 2} << IntMatrix{20, 20, 2} << 25u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("21: matrix transposed to itself") << IntMatrix{3, 3, 2} << IntMatrix{3, 3, 2} << 3u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("22: matrix transposed to itself") << IntMatrix{3, 4, 2} << IntMatrix{3, 4, 2} << 5u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << true;
    QTest::newRow("23: matrix transposed to itself") << IntMatrix{4, 3, 2} << IntMatrix{4, 3, 2} << 5u << 5u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("24: matrix transposed to itself") << IntMatrix{4, 4, 2} << IntMatrix{4, 4, 2} << 5u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("25: matrix transposed to itself") << IntMatrix{7, 8, 2} << IntMatrix{7, 8, 2} << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << true;
    QTest::newRow("26: matrix transposed to itself") << IntMatrix{8, 7, 2} << IntMatrix{8, 7, 2} << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("27: matrix transposed to itself") << IntMatrix{20, 25, 2} << IntMatrix{20, 25, 2} << 25u << 31u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{5u} << true;
    QTest::newRow("28: matrix transposed to itself") << IntMatrix{25, 20, 2} << IntMatrix{25, 20, 2} << 31u << 25u << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("29: matrix transposed to itself") << IntMatrix{25, 25, 2} << IntMatrix{25, 25, 2} << 31u << 31u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{3u} << true;
    QTest::newRow("30: matrix transposed to itself") << IntMatrix{20, 26, 2} << IntMatrix{20, 26, 2} << 32u << 32u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{6u} << true;
    QTest::newRow("31: matrix transposed to itself") << IntMatrix{26, 20, 2} << IntMatrix{26, 20, 2} << 32u << 32u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{3u} << true;
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("1: inserted row value NOT set") << IntMatrix{3, 4, -2} << 1u << 5 << 6u << 5u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("2: inserted row value set") << IntMatrix{3, 4, -2} << 1u << 5 << 6u << 5u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("3: inserted row value NOT set") << IntMatrix{6, 5, -2} << 3u << 5 << 7u << 6u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("4: inserted row value set") << IntMatrix{6, 5, -2} << 3u << 5 << 7u << 6u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("5: inserted row value NOT set") << IntMatrix{8, 2, -2} << 5u << 5 << 10u << 2u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("6: inserted row value set") << IntMatrix{8, 2, -2} << 5u << 5 << 10u << 2u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("7: inserted row value NOT set") << IntMatrix{25, 20, -2} << 0u << 5 << 31u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << false;
    QTest::newRow("8: inserted row value set") << IntMatrix{25, 20, -2} << 0u << 5 << 31u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << true;
    QTest::newRow("9: inserted row value NOT set") << IntMatrix{25, 20, -2} << 11u << 5 << 31u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << false;
    QTest::newRow("10: inserted row value set") << IntMatrix{25, 20, -2} << 11u << 5 << 31u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << true;
    QTest::newRow("11: inserted row value NOT set") << IntMatrix{25, 20, -2} << 25u << 5 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << false;
    QTest::newRow("12: inserted row value set") << IntMatrix{25, 20, -2} << 25u << 5 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << true;
}

void CapacityTests::testIntMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("1: inserted column value NOT set") << IntMatrix{5, 3, 4} << 1u << 1 << 6u << 6u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << false;
    QTest::newRow("2: inserted column value set") << IntMatrix{5, 3, 4} << 1u << 1 << 6u << 6u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << true;
    QTest::newRow("3: inserted column value NOT set") << IntMatrix{5, 7, 4} << 1u << 1 << 6u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("4: inserted column value set") << IntMatrix{5, 7, 4} << 1u << 1 << 6u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("5: inserted column value NOT set") << IntMatrix{5, 14, 4} << 1u << 1 << 6u << 17u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << false;
    QTest::newRow("6: inserted column value set") << IntMatrix{5, 14, 4} << 1u << 1 << 6u << 17u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << true;
    QTest::newRow("7: inserted column value NOT set") << IntMatrix{20, 25, 4} << 0u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << false;
    QTest::newRow("8: inserted column value set") << IntMatrix{20, 25, 4} << 0u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u} << true;
    QTest::newRow("9: inserted column value NOT set") << IntMatrix{20, 25, 4} << 14u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("10: inserted column value set") << IntMatrix{20, 25, 4} << 14u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << true;
    QTest::newRow("11: inserted column value NOT set") << IntMatrix{20, 25, 4} << 25u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << false;
    QTest::newRow("12: inserted column value set") << IntMatrix{20, 25, 4} << 25u << 1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << true;
}

void CapacityTests::testIntMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<SizeTypeTupleArray>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << IntMatrix{3, 4, -2} << SizeTypeTupleArray{{1u, 3u, 5u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {1u, 3u, 5u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("2: less rows than columns") << IntMatrix{10, 15, -2} << SizeTypeTupleArray{{1u, 12u, 18u, IntMatrixOptSizeType{2u}, IntMatrixOptSizeType{1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{5u}, {1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{6u}, {1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{7u}, {1u}}, {1u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 18u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("3: less rows than columns") << IntMatrix{10, 15, -2} << SizeTypeTupleArray{{8u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 18u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("4: less rows than columns") << IntMatrix{10, 15, -2} << SizeTypeTupleArray{{0u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {8u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {6u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {4u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 18u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("5: less rows than columns") << IntMatrix{10, 15, -2} << SizeTypeTupleArray{{9u, 12u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {5u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {3u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 6u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {1u, 2u, 18u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("6: less rows than columns") << IntMatrix{10, 15, -2} << SizeTypeTupleArray{{3u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {6u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 18u, IntMatrixOptSizeType{2u}, {1u}}, {2u, 12u, 18u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {2u, 12u, 18u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 18u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 18u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("7: square matrix") << IntMatrix{4, 4, -2} << SizeTypeTupleArray{{1u, 5u, 5u, IntMatrixOptSizeType{1u}, {0u}}, {1u, 5u, 5u, IntMatrixOptSizeType{1u}, {0u}}, {1u, 2u, 5u, IntMatrixOptSizeType{0u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("8: square matrix") << IntMatrix{10, 10, -2} << SizeTypeTupleArray{{1u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{5u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{6u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{7u}, {1u}}, {1u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 12u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("9: square matrix") << IntMatrix{10, 10, -2} << SizeTypeTupleArray{{8u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 12u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("10: square matrix") << IntMatrix{10, 10, -2} << SizeTypeTupleArray{{0u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {8u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {6u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {4u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 12u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("11: square matrix") << IntMatrix{10, 10, -2} << SizeTypeTupleArray{{9u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {5u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {3u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 6u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {1u, 2u, 12u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("12: square matrix") << IntMatrix{10, 10, -2} << SizeTypeTupleArray{{3u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {6u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 12u, IntMatrixOptSizeType{2u}, {1u}}, {2u, 12u, 12u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {2u, 12u, 12u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 12u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("13: more rows than columns") << IntMatrix{7, 5, -2} << SizeTypeTupleArray{{1u, 8u, 6u, IntMatrixOptSizeType{1u}, {0u}}, {1u, 8u, 6u, IntMatrixOptSizeType{2u}, {0u}}, {1u, 8u, 6u, IntMatrixOptSizeType{3u}, {0u}}, {1u, 8u, 6u, IntMatrixOptSizeType{4u}, {0u}}, {1u, 4u, 6u, IntMatrixOptSizeType{1u}, {0u}}, {1u, 2u, 6u, IntMatrixOptSizeType{0u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("14: more rows than columns") << IntMatrix{10, 9, -2} << SizeTypeTupleArray{{1u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{5u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{6u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{7u}, {1u}}, {1u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 11u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("15: more rows than columns") << IntMatrix{10, 9, -2} << SizeTypeTupleArray{{8u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 11u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("16: more rows than columns") << IntMatrix{10, 9, -2} << SizeTypeTupleArray{{0u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {8u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {6u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {4u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 2u, 11u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("17: more rows than columns") << IntMatrix{10, 9, -2} << SizeTypeTupleArray{{9u, 12u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {0u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {5u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {0u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {3u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 6u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {1u, 2u, 11u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("18: more rows than columns") << IntMatrix{10, 9, -2} << SizeTypeTupleArray{{3u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {6u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {7u, 12u, 11u, IntMatrixOptSizeType{2u}, {1u}}, {2u, 12u, 11u, IntMatrixOptSizeType{3u}, {1u}}, {1u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {2u, 12u, 11u, IntMatrixOptSizeType{4u}, {1u}}, {0u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 6u, 11u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 2u, 11u, IntMatrixOptSizeType{0u}, {1u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
}

void CapacityTests::testIntMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<SizeTypeTupleArray>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << IntMatrix{4, 3, 4} << SizeTypeTupleArray{{1u, 5u, 3u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {1u, 5u, 3u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("2: less columns than rows") << IntMatrix{15, 10, 4} << SizeTypeTupleArray{{1u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {5u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {6u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {7u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("3: less columns than rows") << IntMatrix{15, 10, 4} << SizeTypeTupleArray{{8u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("4: less columns than rows") << IntMatrix{15, 10, 4} << SizeTypeTupleArray{{0u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {8u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {6u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {4u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("5: less columns than rows") << IntMatrix{15, 10, 4} << SizeTypeTupleArray{{9u, 18u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {5u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {3, 18, 6, {1u}, {1u}}, {0, 18, 6, {1u}, {2u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("6: less columns than rows") << IntMatrix{15, 10, 4} << SizeTypeTupleArray{{3u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {6u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 18u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {2u, 18u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {2u, 18u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("7: square matrix") << IntMatrix{4, 4, 4} << SizeTypeTupleArray{{1u, 5u, 5u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{1u}}, {1u, 5u, 5u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{1u}}, {1u, 5u, 2u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("8: square matrix") << IntMatrix{10, 10, 4} << SizeTypeTupleArray{{1u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {5u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {6u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {7u}}, {1u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 12u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("9: square matrix") << IntMatrix{10, 10, 4} << SizeTypeTupleArray{{8u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("10: square matrix") << IntMatrix{10, 10, 4} << SizeTypeTupleArray{{0u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {8u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {6u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {4u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("11: square matrix") << IntMatrix{10, 10, 4} << SizeTypeTupleArray{{9u, 12u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {5u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {3u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 12u, 6u, IntMatrixOptSizeType{1u}, {2u}}, {1u, 12u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("12: square matrix") << IntMatrix{10, 10, 4} << SizeTypeTupleArray{{3u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {6u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 12u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {2u, 12u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {2u, 12u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 12u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 12u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("13: more columns than rows") << IntMatrix{5, 7, 4} <<  SizeTypeTupleArray{{1u, 6u, 8u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{1u}}, {1u, 6u, 8u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{2u}}, {1u, 6u, 8u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{3u}}, {1u, 6u, 8u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{4u}}, {1u, 6u, 4u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{1u}}, {1u, 6u, 2u, IntMatrixOptSizeType{0u}, IntMatrixOptSizeType{0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("14: more columns than rows") << IntMatrix{9, 10, 4} << SizeTypeTupleArray{{1u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {5u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {6u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {7u}}, {1u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 11u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("15: more columns than rows") << IntMatrix{9, 10, 4} << SizeTypeTupleArray{{8u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {7u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {6u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {5u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {4u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {3u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 11u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("16: more columns than rows") << IntMatrix{9, 10, 4} << SizeTypeTupleArray{{0u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {8u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {6u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {4u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {2u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 11u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("17: more columns than rows") << IntMatrix{9, 10, 4} << SizeTypeTupleArray{{9u, 11u, 12u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {0u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {5u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {0u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {3u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {0u, 11u, 6u, IntMatrixOptSizeType{1u}, {2u}}, {1u, 11u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
    QTest::newRow("18: more columns than rows") << IntMatrix{9, 10, 4} << SizeTypeTupleArray{{3u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {6u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {7u, 11u, 12u, IntMatrixOptSizeType{1u}, {2u}}, {2u, 11u, 12u, IntMatrixOptSizeType{1u}, {3u}}, {1u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {2u, 11u, 12u, IntMatrixOptSizeType{1u}, {4u}}, {0u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 11u, 6u, IntMatrixOptSizeType{1u}, {1u}}, {1u, 11u, 2u, IntMatrixOptSizeType{1u}, {0u}}, {0u, 0u, 0u, IntMatrixOptSizeType{}, IntMatrixOptSizeType{}}};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 8u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: destination first") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 12u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 8u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("10: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("12: destination second") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 12u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("13: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("14: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5u << 7u << 7u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("15: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5u << 7u << 8u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("16: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5u << 7u << 9u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("17: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5u << 7u << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("18: source both") << IntMatrix{5, 7, -2} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::SOURCE_BOTH << 5u << 7u << 11u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("19: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("20: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4u << 7u << 7u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("21: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4u << 7u << 8u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("22: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4u << 7u << 9u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("23: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4u << 7u << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("24: destination all") << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << IntMatrix{4, 7, 5} << ConcatMode::DESTINATION_ALL << 4u << 7u << 11u << 8u << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("25: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("26: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("27: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("28: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("29: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("30: all different") << IntMatrix{6, 7, 3} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 12u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};

    // column capacity too
    QTest::newRow("31: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 6u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("32: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("33: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("34: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 9u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("35: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 6u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("36: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("37: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("38: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 9u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("39: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 6u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("40: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("41: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("42: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 9u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("43: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 6u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("44: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("45: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("46: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 9u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 6u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("48: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("49: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("50: all different") << IntMatrix{7, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 9u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};

    // additional tests
    QTest::newRow("51: all different") << IntMatrix{} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("52: all different") << IntMatrix{7, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("53: all different") << IntMatrix{10, 5, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("54: all different") << IntMatrix{6, 6, -1} << IntMatrix{4, 7, 5} << IntMatrix{5, 7, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("55: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("56: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 26u << 22u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("57: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 31u << 26u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("58: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 32u << 27u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("59: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 33u << 28u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("60: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 26u << 22u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("61: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 31u << 26u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("62: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 32u << 27u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("63: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 33u << 28u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("64: all different") << IntMatrix{12, 15, -1} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::ALL_DIFFERENT << 27u << 23u << 33u << 28u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("65: destination first") << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("66: destination second") << IntMatrix{10, 22, -2} << IntMatrix{16, 22, 5} << IntMatrix{10, 22, -2} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 32u << 27u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("67: destination all") << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 40u << 27u << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};
    QTest::newRow("68: source both") << IntMatrix{10, 22, -2} << IntMatrix{16, 22, 5} << IntMatrix{16, 22, 5} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 40u << 27u << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};

    // empty matrix concatenation
    QTest::newRow("69: source both") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 0u << 0u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
    QTest::newRow("70: all different") << IntMatrix{7, 6, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 0u << 0u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("2: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("3: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("4: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("5: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("6: destination first") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("7: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("8: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("9: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("10: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("11: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("12: destination second") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("13: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("14: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 7u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("15: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 8u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("16: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 9u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("17: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 10u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("18: source both") << IntMatrix{7, 5, -2} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 11u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("19: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("20: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 7u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("21: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 8u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("22: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 9u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("23: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 10u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("24: destination all") << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << IntMatrix{7, 4, 5} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 11u << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("25: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("26: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("27: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("28: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("29: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("30: all different") << IntMatrix{7, 6, 3} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};

    // row capacity too
    QTest::newRow("31: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("32: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("33: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("34: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 8u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("35: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("36: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("37: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("38: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 9u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("39: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("40: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("41: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("42: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 10u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("43: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("44: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("45: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("46: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 11u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("47: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("48: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("49: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("50: all different") << IntMatrix{6, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 12u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};

    // additional tests
    QTest::newRow("51: all different") << IntMatrix{} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("52: all different") << IntMatrix{5, 7, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("53: all different") << IntMatrix{5, 10, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("54: all different") << IntMatrix{6, 6, -1} << IntMatrix{7, 4, 5} << IntMatrix{7, 5, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("55: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("56: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 22u << 26u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("57: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 26u << 31u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("58: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 27u << 32u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("59: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 28u << 33u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("60: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 22u << 26u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("61: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 26u << 31u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("62: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 27u << 32u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("63: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 28u << 33u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("64: all different") << IntMatrix{15, 12, -1} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::ALL_DIFFERENT << 23u << 27u << 28u << 33u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("65: destination first") << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("66: destination second") << IntMatrix{22, 10, -2} << IntMatrix{22, 16, 5} << IntMatrix{22, 10, -2} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 27u << 32u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("67: destination all") << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 27u << 40u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};
    QTest::newRow("68: source both") << IntMatrix{22, 10, -2} << IntMatrix{22, 16, 5} << IntMatrix{22, 16, 5} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 27u << 40u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};

    // empty matrix concatenation
    QTest::newRow("69: source both") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 0u << 0u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
    QTest::newRow("70: all different") << IntMatrix{6, 7, -1} << IntMatrix{} << IntMatrix{} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 0u << 0u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("2: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("3: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8u << SplitMode::SOURCE_FIRST << 5u << 8u << 6u << 17u << false << 18u << 21u << 8u << 17u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << 8u << SplitMode::SOURCE_FIRST << 5u << 8u << 6u << 18u << false << 18u << 21u << 8u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 7u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("7: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("8: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("9: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 6u << 8u << 7u << 17u << true << 10u << 17u << 18u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("10: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 6u << 8u << 7u << 18u << true << 10u << 18u << 18u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("11: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 18u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("12: source second") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{15, 17, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};;
    QTest::newRow("13: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("14: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("15: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 17u << true << 10u << 17u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("16: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 18u << true << 10u << 18u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("17: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 18u << 8u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("18: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("19: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("20: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 17u << false << 10u << 21u << 8u << 17u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("21: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{5, 8, 2} << 8u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 18u << false << 10u << 21u << 8u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("22: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 15, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 7u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("23: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 17, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("24: all different") << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << IntMatrix{7, 17, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("25: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("26: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("27: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7u << SplitMode::SOURCE_FIRST << 6u << 8u << 7u << 17u << false << 18u << 21u << 10u << 17u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("28: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{6, 8, 2} << 7u << SplitMode::SOURCE_FIRST << 6u << 8u << 7u << 18u << false << 18u << 21u << 10u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("29: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{7, 15, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("30: source first") << IntMatrix{15, 17, -3} << IntMatrix{15, 17, -3} << IntMatrix{8, 17, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("31: source second") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("32: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("33: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 5u << 8u << 6u << 17u << true << 8u << 17u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("34: source second") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 5u << 8u << 6u << 18u << true << 8u << 18u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("35: source second") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 7u << 18u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("36: source second") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{15, 17, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("37: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("38: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("39: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 17u << true << 8u << 17u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("40: all different") << IntMatrix{15, 17, -3} << IntMatrix{5, 8, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 18u << true << 8u << 18u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("41: all different") << IntMatrix{15, 17, -3} << IntMatrix{6, 15, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 7u << 18u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("42: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("43: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("44: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 17u << false << 8u << 21u << 10u << 17u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("45: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{6, 8, 2} << 7u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 18u << false << 8u << 21u << 10u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("46: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{7, 15, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 8u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << IntMatrix{15, 17, -3} << IntMatrix{} << IntMatrix{8, 17, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("48: all different") << IntMatrix{15, 17, -3} << IntMatrix{7, 17, 2} << IntMatrix{8, 17, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11u << SplitMode::ALL_DIFFERENT << 9u << 12u << 14u << 18u << true << 14u << 25u << 22u << 25u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};
    QTest::newRow("50: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 11u << 25u << 22u << 25u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};
    QTest::newRow("51: all different") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{18, 9, 2} << 11u << SplitMode::ALL_DIFFERENT << 9u << 12u << 9u << 20u << true << 13u << 20u << 22u << 25u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};
    QTest::newRow("52: all different") << IntMatrix{25, 20, -3} << IntMatrix{} << IntMatrix{} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 13u << 25u << 17u << 25u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("53: source first") << IntMatrix{25, 20, -3} << IntMatrix{25, 20, -3} << IntMatrix{18, 9, 2} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 31u << 25u << 22u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{2u};
    QTest::newRow("54: source first") << IntMatrix{25, 20, -3} << IntMatrix{25, 20, -3} << IntMatrix{} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 31u << 25u << 17u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("55: source second") << IntMatrix{25, 20, -3} << IntMatrix{9, 12, 2} << IntMatrix{25, 20, -3} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 11u << 25u << 31u << 25u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("56: source second") << IntMatrix{25, 20, -3} << IntMatrix{} << IntMatrix{25, 20, -3} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 13u << 25u << 31u << 25u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8u << SplitMode::SOURCE_FIRST << 8u << 5u << 17u << 6u << false << 21u << 18u << 17u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << 8u << SplitMode::SOURCE_FIRST << 8u << 5u << 18u << 6u << false << 21u << 18u << 18u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 18u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("8: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("9: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 8u << 6u << 17u << 7u << true << 17u << 10u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("10: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 8u << 6u << 18u << 7u << true << 18u << 10u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("11: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 18u << 8u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("12: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 15, -3} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("13: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("14: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("15: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 8u << 6u << 17u << 7u << true << 17u << 10u << 21u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("16: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 8u << 6u << 18u << 7u << true << 18u << 10u << 21u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("17: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 18u << 8u << 21u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("18: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("19: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("20: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8u << SplitMode::ALL_DIFFERENT << 8u << 5u << 17u << 6u << false << 21u << 10u << 17u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("21: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 5, 2} << 8u << SplitMode::ALL_DIFFERENT << 8u << 5u << 18u << 6u << false << 21u << 10u << 18u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("22: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 6, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 18u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("23: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 7, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("24: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << IntMatrix{17, 7, 2} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("25: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("26: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("27: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7u << SplitMode::SOURCE_FIRST << 8u << 6u << 17u << 7u << false << 21u << 18u << 17u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("28: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{8, 6, 2} << 7u << SplitMode::SOURCE_FIRST << 8u << 6u << 18u << 7u << false << 21u << 18u << 18u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("29: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{15, 7, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 18u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("30: source first") << IntMatrix{17, 15, -3} << IntMatrix{17, 15, -3} << IntMatrix{17, 8, 2} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("31: source second") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("32: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("33: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 8u << 5u << 17u << 6u << true << 17u << 8u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("34: source second") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 8u << 5u << 18u << 6u << true << 18u << 8u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("35: source second") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 18u << 7u << 21u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("36: source second") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 15, -3} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("37: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("38: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("39: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 8u << 5u << 17u << 6u << true << 17u << 8u << 21u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("40: all different") << IntMatrix{17, 15, -3} << IntMatrix{8, 5, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 8u << 5u << 18u << 6u << true << 18u << 8u << 21u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("41: all different") << IntMatrix{17, 15, -3} << IntMatrix{15, 6, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 18u << 7u << 21u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("42: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("43: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("44: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7u << SplitMode::ALL_DIFFERENT << 8u << 6u << 17u << 7u << false << 21u << 8u << 17u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("45: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{8, 6, 2} << 7u << SplitMode::ALL_DIFFERENT << 8u << 6u << 18u << 7u << false << 21u << 8u << 18u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("46: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{15, 7, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 18u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << IntMatrix{17, 15, -3} << IntMatrix{} << IntMatrix{17, 8, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("48: all different") << IntMatrix{17, 15, -3} << IntMatrix{17, 7, 2} << IntMatrix{17, 8, 2} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11u << SplitMode::ALL_DIFFERENT << 12u << 9u << 18u << 14u << true << 25u << 14u << 25u << 22u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};
    QTest::newRow("50: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 25u << 11u << 25u << 22u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};
    QTest::newRow("51: all different") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{9, 18, 2} << 11u << SplitMode::ALL_DIFFERENT << 12u << 9u << 20u << 9u << true << 20u << 13u << 25u << 22u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};
    QTest::newRow("52: all different") << IntMatrix{20, 25, -3} << IntMatrix{} << IntMatrix{} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 25u << 13u << 25u << 17u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("53: source first") << IntMatrix{20, 25, -3} << IntMatrix{20, 25, -3} << IntMatrix{9, 18, 2} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 25u << 31u << 25u << 22u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{4u};
    QTest::newRow("54: source first") << IntMatrix{20, 25, -3} << IntMatrix{20, 25, -3} << IntMatrix{} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 25u << 31u << 25u << 17u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("55: source second") << IntMatrix{20, 25, -3} << IntMatrix{12, 9, 2} << IntMatrix{20, 25, -3} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 25u << 11u << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("56: source second") << IntMatrix{20, 25, -3} << IntMatrix{} << IntMatrix{20, 25, -3} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 25u << 13u << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
}

void CapacityTests::testIntMatrixCapacityWithResizeAndEraseRowAndOrColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<IntMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<IntMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<IntMatrixOptSizeType>("erasedRowNr");
    QTest::addColumn<IntMatrixOptSizeType>("erasedColumnNr");
    QTest::addColumn<bool>("shouldEraseColumnBeforeRow");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 45u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 9u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{1u};
    QTest::newRow("2: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 29u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 8u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{1u};
    QTest::newRow("3: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 28u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 7u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 27u << 6u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 6u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 24u << 5u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 6u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{0u};
    QTest::newRow("6: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 23u << 4u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 23u << 6u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{0u};
    QTest::newRow("7: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 20u << 3u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 20u << 6u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: oversized row capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 18u << 2u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 18u << 6u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 45u << 9u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 45u << 9u << IntMatrixOptSizeType{19u} << IntMatrixOptSizeType{2u};
    QTest::newRow("10: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 29u << 8u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 29u << 8u << IntMatrixOptSizeType{11u} << IntMatrixOptSizeType{2u};
    QTest::newRow("11: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 28u << 7u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 28u << 7u << IntMatrixOptSizeType{10u} << IntMatrixOptSizeType{1u};
    QTest::newRow("12: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 27u << 6u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 27u << 6u << IntMatrixOptSizeType{10u} << IntMatrixOptSizeType{1u};
    QTest::newRow("13: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 24u << 5u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 24u << 6u << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{1u};
    QTest::newRow("14: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 23u << 4u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 23u << 6u << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{1u};
    QTest::newRow("15: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 20u << 3u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 20u << 6u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{1u};
    QTest::newRow("16: oversized row capacity, erase column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 18u << 2u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{1u} << false << 18u << 6u << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{1u};
    QTest::newRow("17: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 45u << 41u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 41u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{17u};
    QTest::newRow("18: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 29u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{9u};
    QTest::newRow("19: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 28u << 24u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 24u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{9u};
    QTest::newRow("20: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 27u << 23u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 23u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{8u};
    QTest::newRow("21: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 24u << 20u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 12u << 20u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{7u};
    QTest::newRow("22: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 23u << 19u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 23u << 19u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{6u};
    QTest::newRow("23: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 20u << 16u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 20u << 16u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{5u};
    QTest::newRow("24: oversized row and column capacity, erase row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 18u << 14u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{} << false << 18u << 14u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{4u};
    QTest::newRow("25: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 45u << 41u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("26: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 29u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("27: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 28u << 24u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("28: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 27u << 23u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("29: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 24u << 20u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("30: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 23u << 19u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 23u << 19u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{7u};
    QTest::newRow("31: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 20u << 16u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 20u << 16u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{6u};
    QTest::newRow("32: oversized row and column capacity, erase row then column") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 18u << 14u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << false << 18u << 14u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{5u};
    QTest::newRow("33: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 45u << 41u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("34: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 29u << 25u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("35: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 28u << 24u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("36: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 27u << 23u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("37: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 24u << 20u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 12u << 10u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("38: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 23u << 19u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 23u << 19u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{7u};
    QTest::newRow("39: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 20u << 16u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 20u << 16u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{6u};
    QTest::newRow("40: oversized row and column capacity, erase column then row") << IntMatrix{6, 5, -3} << 7u << 6u << 5 << 18u << 14u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u} << true << 18u << 14u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{5u};
    QTest::newRow("41: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 9u << 45u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 9u << 12u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{3u};
    QTest::newRow("42: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 8u << 29u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 8u << 12u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{3u};
    QTest::newRow("43: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 7u << 28u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 7u << 12u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{3u};
    QTest::newRow("44: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 6u << 27u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 6u << 12u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{3u};
    QTest::newRow("45: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 5u << 24u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 6u << 12u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{3u};
    QTest::newRow("46: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 4u << 23u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 6u << 23u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{9u};
    QTest::newRow("47: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 3u << 20u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 6u << 20u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{7u};
    QTest::newRow("48: oversized column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 2u << 18u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 6u << 18u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{6u};
    QTest::newRow("49: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 9u << 45u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 9u << 45u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{19u};
    QTest::newRow("50: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 8u << 29u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 8u << 29u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{11u};
    QTest::newRow("51: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 7u << 28u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 7u << 28u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{10u};
    QTest::newRow("52: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 6u << 27u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 6u << 27u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{10u};
    QTest::newRow("53: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 5u << 24u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 6u << 24u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{8u};
    QTest::newRow("54: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 4u << 23u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 6u << 23u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{8u};
    QTest::newRow("55: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 3u << 20u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 6u << 20u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{6u};
    QTest::newRow("56: oversized column capacity, erase row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 2u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{} << false << 6u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{5u};
    QTest::newRow("57: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 41u << 45u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 41u << 12u << IntMatrixOptSizeType{17u} << IntMatrixOptSizeType{3u};
    QTest::newRow("58: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 25u << 29u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 25u << 12u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{3u};
    QTest::newRow("59: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 24u << 28u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 24u << 12u << IntMatrixOptSizeType{9u} << IntMatrixOptSizeType{3u};
    QTest::newRow("60: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 23u << 27u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 23u << 12u << IntMatrixOptSizeType{8u} << IntMatrixOptSizeType{3u};
    QTest::newRow("61: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 20u << 24u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 20u << 12u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{3u};
    QTest::newRow("62: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 19u << 23u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 19u << 23u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{9u};
    QTest::newRow("63: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 16u << 20u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 16u << 20u << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{7u};
    QTest::newRow("64: oversized row and column capacity, erase column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 14u << 18u << IntMatrixOptSizeType{} << IntMatrixOptSizeType{2u} << false << 14u << 18u << IntMatrixOptSizeType{4u} << IntMatrixOptSizeType{6u};
    QTest::newRow("65: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 41u << 45u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("66: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 25u << 29u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("67: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 24u << 28u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("68: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 23u << 27u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("69: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 20u << 24u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("70: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 19u << 23u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 19u << 23u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{9u};
    QTest::newRow("71: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 16u << 20u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 16u << 20u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{7u};
    QTest::newRow("72: oversized row and column capacity, erase column then row") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 14u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << true << 14u << 18u << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{6u};
    QTest::newRow("73: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 41u << 45u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("74: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 25u << 29u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("75: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 24u << 28u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("76: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 23u << 27u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("77: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 20u << 24u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 10u << 12u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("78: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 19u << 23u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 19u << 23u << IntMatrixOptSizeType{7u} << IntMatrixOptSizeType{9u};
    QTest::newRow("79: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 16u << 20u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 16u << 20u << IntMatrixOptSizeType{6u} << IntMatrixOptSizeType{7u};
    QTest::newRow("80: oversized row and column capacity, erase row then column") << IntMatrix{5, 6, -3} << 6u << 7u << 5 << 14u << 18u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u} << false << 14u << 18u << IntMatrixOptSizeType{5u} << IntMatrixOptSizeType{6u};
}

void CapacityTests::testStringMatrixCapacityWithIdenticalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << 4u << std::string{"Value1"} << 3u << 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << 3u << std::string{"Value1"} << 5u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: large size matrix") << 25u << 20u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("4: large size matrix") << 20u << 25u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
}

void CapacityTests::testStringMatrixCapacityWithDiagonalMatrixConstructor_data()
{
    QTest::addColumn<StringMatrixSizeType>("rowsColumnsCount");
    QTest::addColumn<std::string>("nonDiagonalValue");
    QTest::addColumn<std::string>("diagonalValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << std::string{"Value1"} << std::string{"Value2"} << 3u << StringMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << std::string{"Value1"} << std::string{"Value2"} << 5u << StringMatrixOptSizeType{0u};
    QTest::newRow("3: medium size matrix") << 8u << std::string{"Value1"} << std::string{"Value2"} << 10u << StringMatrixOptSizeType{1u};
    QTest::newRow("4: medium size matrix") << 10u << std::string{"Value1"} << std::string{"Value2"} << 12u << StringMatrixOptSizeType{1u};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << StringMatrix{3, 4, "Value"} << StringMatrix{} << 5u<< 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("2: transposed matrix initially empty") << StringMatrix{4, 3, "Value"} << StringMatrix{} << 3u<< 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("3: transposed matrix initially empty") << StringMatrix{7, 8, "Value"} << StringMatrix{} << 10u<< 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("4: transposed matrix initially empty") << StringMatrix{8, 7, "Value"} << StringMatrix{} << 8u<< 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << false;
    QTest::newRow("5: transposed matrix initially empty") << StringMatrix{20, 25, "Value"} << StringMatrix{} << 31u<< 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << false;
    QTest::newRow("6: transposed matrix initially empty") << StringMatrix{25, 20, "Value"} << StringMatrix{} << 25u<< 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 6, "Value"} << 8u<< 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 6, "Value"} << 7u<< 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{5, 7, "Value"} << 8u<< 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{6, 7, "Value"} << 7u<< 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << StringMatrix{8, 7, "Value"} << StringMatrix{7, 8, "Value"} << 8u<< 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 19, "Value"} << 25u<< 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 19, "Value"} << 20u<< 31u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 20, "Value"} << 25u<< 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 20, "Value"} << 20u<< 25u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 25, "Value"} << 25u<< 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{15, 25, "Value"} << 25u<< 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{16, 25, "Value"} << 20u<< 31u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 19, "Value"} << 25u<< 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << StringMatrix{25, 20, "Value"} << StringMatrix{20, 20, "Value"} << 25u<< 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("21: matrix transposed to itself") << StringMatrix{3, 3, "Value"} << StringMatrix{3, 3, "Value"} << 3u<< 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("22: matrix transposed to itself") << StringMatrix{3, 4, "Value"} << StringMatrix{3, 4, "Value"} << 5u<< 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << true;
    QTest::newRow("23: matrix transposed to itself") << StringMatrix{4, 3, "Value"} << StringMatrix{4, 3, "Value"} << 5u<< 5u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("24: matrix transposed to itself") << StringMatrix{4, 4, "Value"} << StringMatrix{4, 4, "Value"} << 5u<< 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("25: matrix transposed to itself") << StringMatrix{7, 8, "Value"} << StringMatrix{7, 8, "Value"} << 8u<< 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << true;
    QTest::newRow("26: matrix transposed to itself") << StringMatrix{8, 7, "Value"} << StringMatrix{8, 7, "Value"} << 10u<< 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("27: matrix transposed to itself") << StringMatrix{20, 25, "Value"} << StringMatrix{20, 25, "Value"} << 25u<< 31u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{5u} << true;
    QTest::newRow("28: matrix transposed to itself") << StringMatrix{25, 20, "Value"} << StringMatrix{25, 20, "Value"} << 31u<< 25u << StringMatrixOptSizeType{5u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("29: matrix transposed to itself") << StringMatrix{25, 25, "Value"} << StringMatrix{25, 25, "Value"} << 31u<< 31u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{3u} << true;
    QTest::newRow("30: matrix transposed to itself") << StringMatrix{20, 26, "Value"} << StringMatrix{20, 26, "Value"} << 32u<< 32u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{6u} << true;
    QTest::newRow("31: matrix transposed to itself") << StringMatrix{26, 20, "Value"} << StringMatrix{26, 20, "Value"} << 32u<< 32u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{3u} << true;
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedRowValueSet");

    QTest::newRow("1: inserted row value NOT set") << StringMatrix{3, 4, "Value1"} << 1u << std::string{"Value2"} << 6u << 5u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("2: inserted row value set") << StringMatrix{3, 4, "Value1"} << 1u << std::string{"Value2"} << 6u << 5u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("3: inserted row value NOT set") << StringMatrix{6, 5, "Value1"} << 3u << std::string{"Value2"} << 7u << 6u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("4: inserted row value set") << StringMatrix{6, 5, "Value1"} << 3u << std::string{"Value2"} << 7u << 6u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("5: inserted row value NOT set") << StringMatrix{8, 2, "Value1"} << 5u << std::string{"Value2"} << 10u << 2u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("6: inserted row value set") << StringMatrix{8, 2, "Value1"} << 5u << std::string{"Value2"} << 10u << 2u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("7: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 0u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << false;
    QTest::newRow("8: inserted row value set") << StringMatrix{25, 20, "Value1"} << 0u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << true;
    QTest::newRow("9: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 11u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << false;
    QTest::newRow("10: inserted row value set") << StringMatrix{25, 20, "Value1"} << 11u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << true;
    QTest::newRow("11: inserted row value NOT set") << StringMatrix{25, 20, "Value1"} << 25u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << false;
    QTest::newRow("12: inserted row value set") << StringMatrix{25, 20, "Value1"} << 25u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << true;
}

void CapacityTests::testStringMatrixCapacityWithInsertColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<IntMatrixSizeType>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isInsertedColumnValueSet");

    QTest::newRow("1: inserted column value NOT set") << StringMatrix{5, 3, "Value1"} << 1u << std::string{"Value2"} << 6u << 6u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << false;
    QTest::newRow("2: inserted column value set") << StringMatrix{5, 3, "Value1"} << 1u << std::string{"Value2"} << 6u << 6u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << true;
    QTest::newRow("3: inserted column value NOT set") << StringMatrix{5, 7, "Value1"} << 1u << std::string{"Value2"} << 6u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("4: inserted column value set") << StringMatrix{5, 7, "Value1"} << 1u << std::string{"Value2"} << 6u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("5: inserted column value NOT set") << StringMatrix{5, 14, "Value1"} << 1u << std::string{"Value2"} << 6u << 17u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << false;
    QTest::newRow("6: inserted column value set") << StringMatrix{5, 14, "Value1"} << 1u << std::string{"Value2"} << 6u << 17u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << true;
    QTest::newRow("7: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 0u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << false;
    QTest::newRow("8: inserted column value set") << StringMatrix{20, 25, "Value1"} << 0u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u} << true;
    QTest::newRow("9: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 14u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("10: inserted column value set") << StringMatrix{20, 25, "Value1"} << 14u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << true;
    QTest::newRow("11: inserted column value NOT set") << StringMatrix{20, 25, "Value1"} << 25u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << false;
    QTest::newRow("12: inserted column value set") << StringMatrix{20, 25, "Value1"} << 25u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << true;
}

void CapacityTests::testStringMatrixCapacityWithEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<SizeTypeTupleArray>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << StringMatrix{3, 4, "Value"} << SizeTypeTupleArray{{1u, 3u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {1u, 3u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("2: less rows than columns") << StringMatrix{10, 15, "Value"} << SizeTypeTupleArray{{1u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{5u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{6u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{7u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 18u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("3: less rows than columns") << StringMatrix{10, 15, "Value"} << SizeTypeTupleArray{{8u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 18u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("4: less rows than columns") << StringMatrix{10, 15, "Value"} << SizeTypeTupleArray{{0u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {8u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 18u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("5: less rows than columns") << StringMatrix{10, 15, "Value"} << SizeTypeTupleArray{{9u, 12u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {3u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 18u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("6: less rows than columns") << StringMatrix{10, 15, "Value"} << SizeTypeTupleArray{{3u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 18u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 18u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 18u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 18u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 18u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("7: square matrix") << StringMatrix{4, 4, "Value"} << SizeTypeTupleArray{{1u, 5u, 5u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {1u, 5u, 5u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {1u, 2u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("8: square matrix") << StringMatrix{10u, 10, "Value"} << SizeTypeTupleArray{{1, 12, 12, 2, 1}, {1u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 12u, StringMatrixOptSizeType{5u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 12u, StringMatrixOptSizeType{6u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 12u, StringMatrixOptSizeType{7u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 12u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("9: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{8u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 12u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("10: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{0u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {8u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 12u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("11: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{9u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {3u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 12u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("12: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{3u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 12u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 12u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 12u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 12u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("13: more rows than columns") << StringMatrix{7, 5, "Value"} << SizeTypeTupleArray{{1u, 8u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {1u, 8u, 6u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{0u}}, {1u, 8u, 6u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{0u}}, {1u, 8u, 6u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{0u}}, {1u, 4u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {1u, 2u, 6u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("14: more rows than columns") << StringMatrix{10, 9, "Value"} << SizeTypeTupleArray{{1u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{5u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{6u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{7u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 11u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("15: more rows than columns") << StringMatrix{10, 9, "Value"} << SizeTypeTupleArray{{8u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 11u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("16: more rows than columns") << StringMatrix{10, 9, "Value"} << SizeTypeTupleArray{{0u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {8u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 2u, 11u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("17: more rows than columns") << StringMatrix{10, 9, "Value"} << SizeTypeTupleArray{{9u, 12u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {3u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 11u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("18: more rows than columns") << StringMatrix{10, 9, "Value"} << SizeTypeTupleArray{{3u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 11u, StringMatrixOptSizeType{2u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 11u, StringMatrixOptSizeType{3u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 11u, StringMatrixOptSizeType{4u}, StringMatrixOptSizeType{1u}}, {0u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 11u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 2u, 11u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
}

void CapacityTests::testStringMatrixCapacityWithEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<SizeTypeTupleArray>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << StringMatrix{4, 3, "Value"} << SizeTypeTupleArray{{1u, 5u, 3u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {1u, 5u, 3u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("2: less columns than rows") << StringMatrix{15, 10, "Value"} << SizeTypeTupleArray{{1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{5u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{6u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{7u}}, {1u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 18u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("3: less columns than rows") << StringMatrix{15, 10, "Value"} << SizeTypeTupleArray{{8u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 18u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("4: less columns than rows") << StringMatrix{15, 10, "Value"} << SizeTypeTupleArray{{0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {8u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {6u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {4u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 18u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("5: less columns than rows") << StringMatrix{15, 10, "Value"} << SizeTypeTupleArray{{9u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {5u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {3u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 18u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("6: less columns than rows") << StringMatrix{15, 10, "Value"} << SizeTypeTupleArray{{3u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {6u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {2u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {2u, 18u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 18u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 18u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("7: square matrix") << StringMatrix{4, 4, "Value"} << SizeTypeTupleArray{{1u, 5u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {1u, 5u, 5u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {1u, 5u, 2u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("8: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{5u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{6u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{7u}}, {1u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("9: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{8u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("10: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {8u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {6u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {4u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("11: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{9u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {5u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {3u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 12u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("12: square matrix") << StringMatrix{10, 10, "Value"} << SizeTypeTupleArray{{3u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {6u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {2u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {2u, 12u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 12u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("13: more columns than rows") << StringMatrix{5, 7, "Value"} << SizeTypeTupleArray{{1u, 6u, 8u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 8u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{2u}}, {1u, 6u, 8u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{3u}}, {1u, 6u, 8u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{4u}}, {1u, 6u, 4u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{1u}}, {1u, 6u, 2u, StringMatrixOptSizeType{0u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("14: more columns than rows") << StringMatrix{9, 10, "Value"} << SizeTypeTupleArray{{1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{5u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{6u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{7u}}, {1u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 11u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("15: more columns than rows") << StringMatrix{9, 10, "Value"} << SizeTypeTupleArray{{8u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {7u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {6u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {5u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {4u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {3u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 11u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("16: more columns than rows") << StringMatrix{9, 10, "Value"} << SizeTypeTupleArray{{0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {8u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {6u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {4u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {2u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 11u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("17: more columns than rows") << StringMatrix{9, 10, "Value"} << SizeTypeTupleArray{{9u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {5u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {0u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {3u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {0u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {1u, 11u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
    QTest::newRow("18: more columns than rows") << StringMatrix{9, 10, "Value"} << SizeTypeTupleArray{{3u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {6u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {7u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{2u}}, {2u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{3u}}, {1u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {2u, 11u, 12u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{4u}}, {0u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 11u, 6u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{1u}}, {1u, 11u, 2u, StringMatrixOptSizeType{1u}, StringMatrixOptSizeType{0u}}, {0u, 0u, 0u, StringMatrixOptSizeType{}, StringMatrixOptSizeType{}}};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 8u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("4: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("6: destination first") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_FIRST << 4u << 7u << 12u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("7: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("8: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 8u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("9: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("10: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("11: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("12: destination second") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::DESTINATION_SECOND << 5u << 7u << 12u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("13: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("14: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5u << 7u << 7u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("15: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5u << 7u << 8u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("16: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5u << 7u << 9u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("17: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5u << 7u << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("18: source both") << StringMatrix{5, 7, "Value2"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::SOURCE_BOTH << 5u << 7u << 11u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("19: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("20: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4u << 7u << 7u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("21: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4u << 7u << 8u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("22: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4u << 7u << 9u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("23: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4u << 7u << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("24: destination all") << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << StringMatrix{4, 7, "Value1"} << ConcatMode::DESTINATION_ALL << 4u << 7u << 11u << 8u << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("25: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("26: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("27: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("28: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("29: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("30: all different") << StringMatrix{6, 7, "Value3"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 12u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};

    // column capacity too
    QTest::newRow("31: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 6u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("32: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("33: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("34: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 9u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("35: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 6u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("36: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("37: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("38: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 9u << 9u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("39: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 6u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("40: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("41: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("42: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 10u << 9u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("43: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 6u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("44: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("45: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("46: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 11u << 9u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 6u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("48: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("49: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("50: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 12u << 9u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};

    // additional tests
    QTest::newRow("51: all different") << StringMatrix{} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("52: all different") << StringMatrix{7, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("53: all different") << StringMatrix{10, 5, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("54: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{4, 7, "Value1"} << StringMatrix{5, 7, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("55: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("56: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 26u << 22u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("57: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 31u << 26u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("58: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 32u << 27u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("59: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 12u << 15u << 33u << 28u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("60: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 26u << 22u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("61: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 31u << 26u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("62: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 32u << 27u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("63: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 26u << 22u << 33u << 28u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("64: all different") << StringMatrix{12, 15, "Value4"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::ALL_DIFFERENT << 27u << 23u << 33u << 28u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("65: destination first") << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("66: destination second") << StringMatrix{10, 22, "Value2"} << StringMatrix{16, 22, "Value1"} << StringMatrix{10, 22, "Value2"} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 32u << 27u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("67: destination all") << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 40u << 27u << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};
    QTest::newRow("68: source both") << StringMatrix{10, 22, "Value2"} << StringMatrix{16, 22, "Value1"} << StringMatrix{16, 22, "Value1"} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 40u << 27u << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};

    // empty matrix concatenation
    QTest::newRow("69: source both") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 0u << 0u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{};
    QTest::newRow("70: all different") << StringMatrix{7, 6, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 0u << 0u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("2: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("3: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("4: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("5: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("6: destination first") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_FIRST << 7u << 4u << 8u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("7: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("8: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("9: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("10: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("11: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("12: destination second") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::DESTINATION_SECOND << 7u << 5u << 8u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("13: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("14: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 7u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("15: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 8u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("16: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 9u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("17: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 10u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("18: source both") << StringMatrix{7, 5, "Value2"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::SOURCE_BOTH << 7u << 5u << 8u << 11u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("19: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("20: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 7u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("21: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 8u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("22: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 9u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("23: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 10u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("24: destination all") << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 4, "Value1"} << ConcatMode::DESTINATION_ALL << 7u << 4u << 8u << 11u << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("25: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("26: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("27: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("28: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("29: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("30: all different") << StringMatrix{7, 6, "Value3"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 7u << 6u << 8u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};

    // row capacity too
    QTest::newRow("31: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("32: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("33: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("34: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 8u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("35: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("36: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("37: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("38: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 9u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("39: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("40: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("41: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("42: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 10u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("43: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("44: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("45: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("46: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 11u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("47: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 6u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("48: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 7u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("49: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 8u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("50: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 6u << 7u << 9u << 12u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};

    // additional tests
    QTest::newRow("51: all different") << StringMatrix{} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("52: all different") << StringMatrix{5, 7, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("53: all different") << StringMatrix{5, 10, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("54: all different") << StringMatrix{6, 6, "Value4"} << StringMatrix{7, 4, "Value1"} << StringMatrix{7, 5, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 8u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("55: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("56: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 22u << 26u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("57: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 26u << 31u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("58: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 27u << 32u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("59: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 15u << 12u << 28u << 33u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("60: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 22u << 26u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("61: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 26u << 31u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("62: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 27u << 32u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("63: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 22u << 26u << 28u << 33u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("64: all different") << StringMatrix{15, 12, "Value4"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::ALL_DIFFERENT << 23u << 27u << 28u << 33u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("65: destination first") << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::DESTINATION_FIRST << 0u << 0u << 0u << 0u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("66: destination second") << StringMatrix{22, 10, "Value2"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 10, "Value2"} << ConcatMode::DESTINATION_SECOND << 0u << 0u << 0u << 0u << 27u << 32u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("67: destination all") << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << ConcatMode::DESTINATION_ALL << 0u << 0u << 0u << 0u << 27u << 40u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};
    QTest::newRow("68: source both") << StringMatrix{22, 10, "Value2"} << StringMatrix{22, 16, "Value1"} << StringMatrix{22, 16, "Value1"} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 27u << 40u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};

    // empty matrix concatenation
    QTest::newRow("69: source both") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::SOURCE_BOTH << 0u << 0u << 0u << 0u << 0u << 0u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{};
    QTest::newRow("70: all different") << StringMatrix{6, 7, "Value4"} << StringMatrix{} << StringMatrix{} << ConcatMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << 0u << 0u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("2: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("3: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 5u << 8u << 6u << 17u << false << 18u << 21u << 8u << 17u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("4: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 5u << 8u << 6u << 18u << false << 18u << 21u << 8u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 7u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("6: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("7: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("8: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("9: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 6u << 8u << 7u << 17u << true << 10u << 17u << 18u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("10: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 6u << 8u << 7u << 18u << true << 10u << 18u << 18u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("11: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 18u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("12: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 10u << 21u << 18u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("13: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("14: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("15: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 17u << true << 10u << 17u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("16: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 18u << true << 10u << 18u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("17: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 18u << 8u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("18: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("19: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("20: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 17u << false << 10u << 21u << 8u << 17u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("21: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{5, 8, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 18u << false << 10u << 21u << 8u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("22: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 15, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 7u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("23: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 17, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("24: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << StringMatrix{7, 17, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 10u << 21u << 8u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("25: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("26: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("27: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 6u << 8u << 7u << 17u << false << 18u << 21u << 10u << 17u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("28: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 6u << 8u << 7u << 18u << false << 18u << 21u << 10u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("29: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 15, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 8u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("30: source first") << StringMatrix{15, 17, "Value1"} << StringMatrix{15, 17, "Value1"} << StringMatrix{8, 17, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 18u << 21u << 10u << 21u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("31: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("32: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("33: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 5u << 8u << 6u << 17u << true << 8u << 17u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("34: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 5u << 8u << 6u << 18u << true << 8u << 18u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("35: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 7u << 18u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("36: source second") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{15, 17, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 8u << 21u << 18u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("37: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("38: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("39: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 17u << true << 8u << 17u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("40: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{5, 8, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 5u << 8u << 6u << 18u << true << 8u << 18u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("41: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{6, 15, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 7u << 18u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("42: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("43: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("44: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 17u << false << 8u << 21u << 10u << 17u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("45: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{6, 8, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 6u << 8u << 7u << 18u << false << 8u << 21u << 10u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("46: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{7, 15, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 8u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{} << StringMatrix{8, 17, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("48: all different") << StringMatrix{15, 17, "Value1"} << StringMatrix{7, 17, "Value2"} << StringMatrix{8, 17, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 8u << 21u << 10u << 21u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};

    // additional tests
    QTest::newRow("49: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 9u << 12u << 14u << 18u << true << 14u << 25u << 22u << 25u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};
    QTest::newRow("50: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 11u << 25u << 22u << 25u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};
    QTest::newRow("51: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{18, 9, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 9u << 12u << 9u << 20u << true << 13u << 20u << 22u << 25u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};
    QTest::newRow("52: all different") << StringMatrix{25, 20, "Value1"} << StringMatrix{} << StringMatrix{} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 13u << 25u << 17u << 25u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("53: source first") << StringMatrix{25, 20, "Value1"} << StringMatrix{25, 20, "Value1"} << StringMatrix{18, 9, "Value2"} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 31u << 25u << 22u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{2u};
    QTest::newRow("54: source first") << StringMatrix{25, 20, "Value1"} << StringMatrix{25, 20, "Value1"} << StringMatrix{} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 31u << 25u << 17u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("55: source second") << StringMatrix{25, 20, "Value1"} << StringMatrix{9, 12, "Value2"} << StringMatrix{25, 20, "Value1"} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 11u << 25u << 31u << 25u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("56: source second") << StringMatrix{25, 20, "Value1"} << StringMatrix{} << StringMatrix{25, 20, "Value1"} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 13u << 25u << 31u << 25u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 8u << 5u << 17u << 6u << false << 21u << 18u << 17u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("4: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 8u << 5u << 18u << 6u << false << 21u << 18u << 18u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 18u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("6: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << 8u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("7: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("8: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("9: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 8u << 6u << 17u << 7u << true << 17u << 10u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("10: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 8u << 6u << 18u << 7u << true << 18u << 10u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("11: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 18u << 8u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("12: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 15, "Value1"} << 8u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("13: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("14: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("15: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 8u << 6u << 17u << 7u << true << 17u << 10u << 21u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("16: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 8u << 6u << 18u << 7u << true << 18u << 10u << 21u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("17: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 18u << 8u << 21u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("18: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("19: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("20: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 8u << 5u << 17u << 6u << false << 21u << 10u << 17u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("21: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 5, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 8u << 5u << 18u << 6u << false << 21u << 10u << 18u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("22: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 6, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 18u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("23: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 7, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("24: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << StringMatrix{17, 7, "Value2"} << 8u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 10u << 21u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("25: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("26: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("27: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 8u << 6u << 17u << 7u << false << 21u << 18u << 17u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("28: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 8u << 6u << 18u << 7u << false << 21u << 18u << 18u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("29: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 7, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 18u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("30: source first") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 8, "Value2"} << 7u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 21u << 18u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("31: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("32: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("33: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 8u << 5u << 17u << 6u << true << 17u << 8u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("34: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 8u << 5u << 18u << 6u << true << 18u << 8u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("35: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 18u << 7u << 21u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("36: source second") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 15, "Value1"} << 7u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 18u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("37: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("38: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("39: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 8u << 5u << 17u << 6u << true << 17u << 8u << 21u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("40: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{8, 5, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 8u << 5u << 18u << 6u << true << 18u << 8u << 21u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("41: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{15, 6, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 18u << 7u << 21u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("42: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("43: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("44: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 8u << 6u << 17u << 7u << false << 21u << 8u << 17u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("45: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{8, 6, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 8u << 6u << 18u << 7u << false << 21u << 8u << 18u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("46: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{15, 7, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 18u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("47: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{} << StringMatrix{17, 8, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("48: all different") << StringMatrix{17, 15, "Value1"} << StringMatrix{17, 7, "Value2"} << StringMatrix{17, 8, "Value2"} << 7u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 21u << 8u << 21u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};

    // additional tests
    QTest::newRow("49: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 12u << 9u << 18u << 14u << true << 25u << 14u << 25u << 22u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};
    QTest::newRow("50: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 25u << 11u << 25u << 22u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};
    QTest::newRow("51: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{9, 18, "Value2"} << 11u << SplitMode::ALL_DIFFERENT << 12u << 9u << 20u << 9u << true << 20u << 13u << 25u << 22u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};
    QTest::newRow("52: all different") << StringMatrix{20, 25, "Value1"} << StringMatrix{} << StringMatrix{} << 11u << SplitMode::ALL_DIFFERENT << 0u << 0u << 0u << 0u << false << 25u << 13u << 25u << 17u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("53: source first") << StringMatrix{20, 25, "Value1"} << StringMatrix{20, 25, "Value1"} << StringMatrix{9, 18, "Value2"} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 25u << 31u << 25u << 22u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{4u};
    QTest::newRow("54: source first") << StringMatrix{20, 25, "Value1"} << StringMatrix{20, 25, "Value1"} << StringMatrix{} << 11u << SplitMode::SOURCE_FIRST << 0u << 0u << 0u << 0u << false << 25u << 31u << 25u << 17u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("55: source second") << StringMatrix{20, 25, "Value1"} << StringMatrix{12, 9, "Value2"} << StringMatrix{20, 25, "Value1"} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 25u << 11u << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("56: source second") << StringMatrix{20, 25, "Value1"} << StringMatrix{} << StringMatrix{20, 25, "Value1"} << 11u << SplitMode::SOURCE_SECOND << 0u << 0u << 0u << 0u << false << 25u << 13u << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
}

void CapacityTests::testStringMatrixCapacityWithResizeAndEraseRowAndOrColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<StringMatrixSizeType>("resizeRowsCount");
    QTest::addColumn<StringMatrixSizeType>("resizeColumnsCount");
    QTest::addColumn<std::string>("resizeElementValue");
    QTest::addColumn<StringMatrixSizeType>("requestedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("requestedColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("erasedRowNr");
    QTest::addColumn<StringMatrixOptSizeType>("erasedColumnNr");
    QTest::addColumn<bool>("shouldEraseColumnBeforeRow");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 45u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 9u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{1u};
    QTest::newRow("2: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 29u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 8u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{1u};
    QTest::newRow("3: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 28u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 7u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{0u};
    QTest::newRow("4: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 27u << 6u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 6u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 24u << 5u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 6u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{0u};
    QTest::newRow("6: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 23u << 4u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 23u << 6u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{0u};
    QTest::newRow("7: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 20u << 3u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 20u << 6u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{0u};
    QTest::newRow("8: oversized row capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 18u << 2u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 18u << 6u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{0u};
    QTest::newRow("9: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 45u << 9u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 45u << 9u << StringMatrixOptSizeType{19u} << StringMatrixOptSizeType{2u};
    QTest::newRow("10: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 29u << 8u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 29u << 8u << StringMatrixOptSizeType{11u} << StringMatrixOptSizeType{2u};
    QTest::newRow("11: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 28u << 7u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 28u << 7u << StringMatrixOptSizeType{10u} << StringMatrixOptSizeType{1u};
    QTest::newRow("12: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 27u << 6u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 27u << 6u << StringMatrixOptSizeType{10u} << StringMatrixOptSizeType{1u};
    QTest::newRow("13: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 24u << 5u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 24u << 6u << StringMatrixOptSizeType{8u} << StringMatrixOptSizeType{1u};
    QTest::newRow("14: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 23u << 4u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 23u << 6u << StringMatrixOptSizeType{8u} << StringMatrixOptSizeType{1u};
    QTest::newRow("15: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 20u << 3u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 20u << 6u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{1u};
    QTest::newRow("16: oversized row capacity, erase column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 18u << 2u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{1u} << false << 18u << 6u << StringMatrixOptSizeType{5u} << StringMatrixOptSizeType{1u};
    QTest::newRow("17: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 45u << 41u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 41u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{17u};
    QTest::newRow("18: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 29u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{9u};
    QTest::newRow("19: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 28u << 24u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 24u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{9u};
    QTest::newRow("20: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 27u << 23u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 23u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{8u};
    QTest::newRow("21: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 24u << 20u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 12u << 20u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{7u};
    QTest::newRow("22: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 23u << 19u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 23u << 19u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{6u};
    QTest::newRow("23: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 20u << 16u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 20u << 16u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{5u};
    QTest::newRow("24: oversized row and column capacity, erase row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 18u << 14u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{} << false << 18u << 14u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{4u};
    QTest::newRow("25: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 45u << 41u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("26: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 29u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("27: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 28u << 24u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("28: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 27u << 23u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("29: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 24u << 20u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("30: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 23u << 19u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 23u << 19u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{7u};
    QTest::newRow("31: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 20u << 16u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 20u << 16u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{6u};
    QTest::newRow("32: oversized row and column capacity, erase row then column") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 18u << 14u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << false << 18u << 14u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{5u};
    QTest::newRow("33: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 45u << 41u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("34: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 29u << 25u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("35: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 28u << 24u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("36: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 27u << 23u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("37: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 24u << 20u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 12u << 10u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("38: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 23u << 19u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 23u << 19u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{7u};
    QTest::newRow("39: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 20u << 16u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 20u << 16u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{6u};
    QTest::newRow("40: oversized row and column capacity, erase column then row") << StringMatrix{6, 5, "Value1"} << 7u << 6u << std::string{"Value2"} << 18u << 14u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u} << true << 18u << 14u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{5u};
    QTest::newRow("41: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 9u << 45u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 9u << 12u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{3u};
    QTest::newRow("42: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 8u << 29u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 8u << 12u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{3u};
    QTest::newRow("43: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 7u << 28u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 7u << 12u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{3u};
    QTest::newRow("44: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 6u << 27u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 6u << 12u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{3u};
    QTest::newRow("45: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 5u << 24u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 6u << 12u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{3u};
    QTest::newRow("46: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 4u << 23u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 6u << 23u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{9u};
    QTest::newRow("47: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 3u << 20u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 6u << 20u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{7u};
    QTest::newRow("48: oversized column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 2u << 18u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 6u << 18u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{6u};
    QTest::newRow("49: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 9u << 45u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 9u << 45u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{19u};
    QTest::newRow("50: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 8u << 29u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 8u << 29u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{11u};
    QTest::newRow("51: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 7u << 28u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 7u << 28u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{10u};
    QTest::newRow("52: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 6u << 27u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 6u << 27u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{10u};
    QTest::newRow("53: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 5u << 24u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 6u << 24u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{8u};
    QTest::newRow("54: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 4u << 23u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 6u << 23u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{8u};
    QTest::newRow("55: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 3u << 20u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 6u << 20u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{6u};
    QTest::newRow("56: oversized column capacity, erase row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 2u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{} << false << 6u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{5u};
    QTest::newRow("57: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 41u << 45u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 41u << 12u << StringMatrixOptSizeType{17u} << StringMatrixOptSizeType{3u};
    QTest::newRow("58: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 25u << 29u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 25u << 12u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{3u};
    QTest::newRow("59: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 24u << 28u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 24u << 12u << StringMatrixOptSizeType{9u} << StringMatrixOptSizeType{3u};
    QTest::newRow("60: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 23u << 27u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 23u << 12u << StringMatrixOptSizeType{8u} << StringMatrixOptSizeType{3u};
    QTest::newRow("61: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 20u << 24u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 20u << 12u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{3u};
    QTest::newRow("62: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 19u << 23u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 19u << 23u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{9u};
    QTest::newRow("63: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 16u << 20u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 16u << 20u << StringMatrixOptSizeType{5u} << StringMatrixOptSizeType{7u};
    QTest::newRow("64: oversized row and column capacity, erase column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 14u << 18u << StringMatrixOptSizeType{} << StringMatrixOptSizeType{2u} << false << 14u << 18u << StringMatrixOptSizeType{4u} << StringMatrixOptSizeType{6u};
    QTest::newRow("65: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 41u << 45u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("66: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 25u << 29u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("67: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 24u << 28u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("68: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 23u << 27u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("69: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 20u << 24u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("70: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 19u << 23u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 19u << 23u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{9u};
    QTest::newRow("71: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 16u << 20u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 16u << 20u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{7u};
    QTest::newRow("72: oversized row and column capacity, erase column then row") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 14u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << true << 14u << 18u << StringMatrixOptSizeType{5u} << StringMatrixOptSizeType{6u};
    QTest::newRow("73: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 41u << 45u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("74: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 25u << 29u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("75: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 24u << 28u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("76: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 23u << 27u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("77: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 20u << 24u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 10u << 12u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("78: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 19u << 23u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 19u << 23u << StringMatrixOptSizeType{7u} << StringMatrixOptSizeType{9u};
    QTest::newRow("79: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 16u << 20u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 16u << 20u << StringMatrixOptSizeType{6u} << StringMatrixOptSizeType{7u};
    QTest::newRow("80: oversized row and column capacity, erase row then column") << StringMatrix{5, 6, "Value1"} << 6u << 7u << std::string{"Value2"} << 14u << 18u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u} << false << 14u << 18u << StringMatrixOptSizeType{5u} << StringMatrixOptSizeType{6u};
}

void CapacityTests::_buildIntMatrixCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<IntMatrixSizeType>("rowsCount");
    QTest::addColumn<IntMatrixSizeType>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<IntMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<IntMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << 4u << -1 << 3u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << 3u << -1 << 5u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: medium size matrix") << 7u << 8u << -1 << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("4: medium size matrix") << 8u << 7u << -1 << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: large size matrix") << 20u << 25u << -1 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("6: large size matrix") << 25u << 20u << -1 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << 3u << 4u << -1 << 0u << 0u << 0 << 3u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: destination matrix initially empty") << 4u << 3u << -1 << 0u << 0u << 0 << 5u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: destination matrix initially empty") << 7u << 8u << -1 << 0u << 0u << 0 << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("4: destination matrix initially empty") << 8u << 7u << -1 << 0u << 0u << 0 << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("5: destination matrix initially empty") << 20u << 25u << -1 << 0u << 0u << 0 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("6: destination matrix initially empty") << 25u << 20u << -1 << 0u << 0u << 0 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("7: destination matrix initially NOT empty") << 3u << 4u << -1 << 2u << 3u << -5 << 3u << 5u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: destination matrix initially NOT empty") << 4u << 3u << -1 << 2u << 3u << -5 << 5u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: destination matrix initially NOT empty") << 7u << 8u << -1 << 3u << 4u << -5 << 8u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("10: destination matrix initially NOT empty") << 8u << 7u << -1 << 3u << 4u << -5 << 10u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: destination matrix initially NOT empty") << 20u << 25u << -1 << 15u << 20u << -5 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("12: destination matrix initially NOT empty") << 25u << 20u << -1 << 15u << 20u << -5 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("13: destination matrix initially NOT empty") << 20u << 25u << -1 << 25u << 20u << -5 << 25u << 31u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{3u};
    QTest::newRow("14: destination matrix initially NOT empty") << 25u << 20u << -1 << 20u << 25u << -5 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("15: destination matrix initially NOT empty") << 25u << 20u << -1 << 25u << 20u << -5 << 31u << 25u << IntMatrixOptSizeType{3u} << IntMatrixOptSizeType{2u};
    QTest::newRow("16: destination matrix initially NOT empty") << 15u << 20u << -1 << 20u << 25u << -5 << 18u << 25u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
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
    QTest::addColumn<IntMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<IntMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 6u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("2: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 7u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("3: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("4: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("5: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("6: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("7: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 9u << 0u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("8: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 6u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("9: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 7u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("10: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("11: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("12: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("13: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("14: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 10u << 0u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("15: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 6u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("16: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 7u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("17: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("18: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("19: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("20: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("21: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 11u << 0u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("22: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 6u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("23: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 7u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("24: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("25: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("26: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("27: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("28: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 12u << 0u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("29: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 6u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("30: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 7u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("31: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("32: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("33: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("34: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("35: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 13u << 0u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("36: equal rows, less columns") << IntMatrix{10, 8, -2} << 10u << 7u << -5 << 0u << 0u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("37: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 7u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("38: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 8u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("39: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("40: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("41: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("42: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 8u << 0u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("43: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 7u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("44: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 8u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("45: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("46: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("47: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("48: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 9u << 0u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("49: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 7u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("50: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("51: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("52: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("53: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("54: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 10u << 0u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("55: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 7u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("56: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("57: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("58: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("59: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("60: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 11u << 0u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("61: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 7u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("62: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("63: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("64: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("65: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("66: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 12u << 0u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("67: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 7u << 13u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("68: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("69: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("70: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("71: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("72: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 13u << 0u << 13u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("73: less rows, equal columns") << IntMatrix{10, 8, -2} << 9u << 8u << -5 << 0u << 0u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("74: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 6u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("75: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 7u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("76: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 8u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("77: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("78: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("79: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("80: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 8u << 0u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("81: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 6u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("82: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 7u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("83: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 8u << 9u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("84: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("85: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("86: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("87: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 9u << 0u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("88: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 6u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("89: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 7u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("90: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("91: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("92: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("93: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("94: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 10u << 0u << 10u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("95: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 6u << 11u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("96: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 7u << 11u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("97: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("98: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("99: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("100: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("101: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 11u << 0u << 11u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("102: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 6u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("103: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 7u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("104: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("105: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("106: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("107: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("108: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 12u << 0u << 12u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("109: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 6u << 13u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("110: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 7u << 13u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("111: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("112: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("113: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("114: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{2u};
    QTest::newRow("115: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 13u << 0u << 13u << 7u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("116: less rows, less columns") << IntMatrix{10, 8, -2} << 9u << 7u << -5 << 0u << 0u << 9u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("117: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 7u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("118: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("119: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("120: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("121: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("122: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 9u << 0u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("123: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 7u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("124: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 8u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("125: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("126: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("127: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("128: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 10u << 0u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("129: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 7u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("130: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("131: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("132: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("133: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("134: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 11u << 0u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("135: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 7u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("136: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("137: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("138: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("139: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("140: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 12u << 0u << 12u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("141: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 7u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("142: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("143: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("144: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("145: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("146: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 13u << 0u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("147: same rows, same columns") << IntMatrix{10, 8, -2} << 10u << 8u << -5 << 0u << 0u << 10u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("148: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 7u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("149: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("150: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("151: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("152: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("153: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 9u << 0u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("154: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 7u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("155: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("156: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("157: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("158: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("159: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 10u << 0u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("160: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 7u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("161: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("162: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("163: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("164: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("165: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 11u << 0u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("166: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 7u << 12u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("167: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("168: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("169: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("170: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("171: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 12u << 0u << 12u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("172: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 7u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("173: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("174: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("175: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("176: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("177: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 13u << 0u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("178: more rows, same columns") << IntMatrix{10, 8, -2} << 11u << 8u << -5 << 0u << 0u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("179: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 7u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("180: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 8u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("181: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("182: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("183: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("184: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 9u << 0u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("185: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 7u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("186: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 8u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("187: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("188: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("189: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("190: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 10u << 0u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("191: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 7u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("192: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 8u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("193: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("194: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("195: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("196: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 11u << 0u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("197: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 7u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("198: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 8u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("199: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("200: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("201: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("202: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 12u << 0u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("203: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 7u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("204: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 8u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("205: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("206: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("207: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("208: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 13u << 0u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("209: same rows, more columns") << IntMatrix{10, 8, -2} << 10u << 9u << -5 << 0u << 0u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("210: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 7u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("211: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 8u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("212: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("213: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("214: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("215: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 9u << 0u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("216: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 7u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("217: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 8u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("218: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("219: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("220: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("221: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 10u << 0u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("222: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 7u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("223: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 8u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("224: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("225: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("226: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("227: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 11u << 0u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("228: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 7u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("229: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 8u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("230: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("231: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("232: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("233: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 12u << 0u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("234: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 7u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("235: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 8u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("236: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("237: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("238: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("239: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 13u << 0u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("240: more rows, more columns") << IntMatrix{10, 8, -2} << 11u << 9u << -5 << 0u << 0u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("241: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 6u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("242: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 7u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("243: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("244: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("245: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("246: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("247: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 9u << 0u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("248: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 6u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("249: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 7u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("250: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("251: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("252: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("253: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("254: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 10u << 0u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("255: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 6u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("256: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 7u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("257: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 8u << 11u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("258: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("259: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("260: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("261: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 11u << 0u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("262: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 6u << 12u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("263: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 7u << 12u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("264: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 8u << 12u << 8u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("265: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("266: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("267: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{2u};
    QTest::newRow("268: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 12u << 0u << 12u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("269: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 6u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("270: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 7u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("271: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 8u << 13u << 8u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("272: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("273: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("274: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{2u};
    QTest::newRow("275: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 13u << 0u << 13u << 7u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("276: more rows, less columns") << IntMatrix{10, 8, -2} << 11u << 7u << -5 << 0u << 0u << 11u << 7u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("277: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 7u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("278: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 8u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("279: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("280: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("281: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("282: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 8u << 0u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("283: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 7u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("284: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 8u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("285: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 9u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("286: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 10u << 9u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("287: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 11u << 9u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("288: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 9u << 0u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("289: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 7u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("290: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 8u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("291: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 9u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("292: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 10u << 10u << 10u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("293: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 11u << 10u << 11u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("294: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 10u << 0u << 10u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("295: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 7u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("296: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 8u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("297: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 9u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("298: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 10u << 11u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("299: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 11u << 11u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("300: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 11u << 0u << 11u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("301: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 7u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("302: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 8u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("303: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 9u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("304: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 10u << 12u << 10u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("305: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 11u << 12u << 11u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
    QTest::newRow("306: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 12u << 0u << 12u << 9u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("307: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 7u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("308: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 8u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("309: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 9u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("310: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 10u << 13u << 10u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("311: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 11u << 13u << 11u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{1u};
    QTest::newRow("312: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 13u << 0u << 13u << 9u << IntMatrixOptSizeType{2u} << IntMatrixOptSizeType{0u};
    QTest::newRow("313: less rows, more columns") << IntMatrix{10, 8, -2} << 9u << 9u << -5 << 0u << 0u << 9u << 9u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};

    // empty matrix
    QTest::newRow("314: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 0u << 0u << 1u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("315: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 0u << 1u << 1u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("316: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 0u << 2u << 1u << 2u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("317: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 0u << 3u << 1u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("318: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 1u << 0u << 1u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("319: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 1u << 1u << 1u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("320: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 1u << 2u << 1u << 2u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("321: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 1u << 3u << 1u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("322: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 2u << 0u << 2u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("323: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 2u << 1u << 2u << 1u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("324: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 2u << 2u << 2u << 2u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{0u};
    QTest::newRow("325: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 2u << 3u << 2u << 3u << IntMatrixOptSizeType{0u} << IntMatrixOptSizeType{1u};
    QTest::newRow("326: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 3u << 0u << 3u << 1u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("327: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 3u << 1u << 3u << 1u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("328: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 3u << 2u << 3u << 2u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{0u};
    QTest::newRow("329: more rows, more columns") << IntMatrix{} << 1u << 1u << -5 << 3u << 3u << 3u << 3u << IntMatrixOptSizeType{1u} << IntMatrixOptSizeType{1u};
}

void CapacityTests::_buildStringMatrixCapacityWithMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<StringMatrixSizeType>("rowsCount");
    QTest::addColumn<StringMatrixSizeType>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<StringMatrixSizeType>("expectedRowCapacity");
    QTest::addColumn<StringMatrixSizeType>("expectedColumnCapacity");
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << 3u << 4u << std::string{"Value"} << 3u << 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: small size matrix") << 4u << 3u << std::string{"Value"} << 5u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: medium size matrix") << 7u << 8u << std::string{"Value"} << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("4: medium size matrix") << 8u << 7u << std::string{"Value"} << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: large size matrix") << 20u << 25u << std::string{"Value"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("6: large size matrix") << 25u << 20u << std::string{"Value"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << 3u << 4u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 3u << 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: destination matrix initially empty") << 4u << 3u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 5u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: destination matrix initially empty") << 7u << 8u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("4: destination matrix initially empty") << 8u << 7u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("5: destination matrix initially empty") << 20u << 25u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("6: destination matrix initially empty") << 25u << 20u << std::string{"Value1"} << 0u << 0u << std::string{"Value2"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("7: destination matrix initially NOT empty") << 3u << 4u << std::string{"Value1"} << 2u << 3u << std::string{"Value3"} << 3u << 5u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("8: destination matrix initially NOT empty") << 4u << 3u << std::string{"Value1"} << 2u << 3u << std::string{"Value3"} << 5u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("9: destination matrix initially NOT empty") << 7u << 8u << std::string{"Value1"} << 3u << 4u << std::string{"Value3"} << 8u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("10: destination matrix initially NOT empty") << 8u << 7u << std::string{"Value1"} << 3u << 4u << std::string{"Value3"} << 10u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("11: destination matrix initially NOT empty") << 20u << 25u << std::string{"Value1"} << 15u << 20u << std::string{"Value3"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("12: destination matrix initially NOT empty") << 25u << 20u << std::string{"Value1"} << 15u << 20u << std::string{"Value3"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("13: destination matrix initially NOT empty") << 20u << 25u << std::string{"Value1"} << 25u << 20u << std::string{"Value3"} << 25u << 31u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{3u};
    QTest::newRow("14: destination matrix initially NOT empty") << 25u << 20u << std::string{"Value1"} << 20u << 25u << std::string{"Value3"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("15: destination matrix initially NOT empty") << 25u << 20u << std::string{"Value1"} << 25u << 20u << std::string{"Value3"} << 31u << 25u << StringMatrixOptSizeType{3u} << StringMatrixOptSizeType{2u};
    QTest::newRow("16: destination matrix initially NOT empty") << 15u << 20u << std::string{"Value1"} << 20u << 25u << std::string{"Value3"} << 18u << 25u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
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
    QTest::addColumn<StringMatrixOptSizeType>("expectedRowCapacityOffset");
    QTest::addColumn<StringMatrixOptSizeType>("expectedColumnCapacityOffset");

    QTest::newRow("1: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 6u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("2: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 7u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("3: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("4: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("5: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("6: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("7: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 9u << 0u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("8: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 6u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("9: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 7u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("10: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("11: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("12: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("13: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("14: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 10u << 0u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("15: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 6u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("16: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 7u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("17: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("18: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("19: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("20: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("21: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 11u << 0u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("22: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 6u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("23: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 7u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("24: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("25: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("26: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("27: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("28: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 12u << 0u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("29: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 6u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("30: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 7u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("31: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("32: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("33: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("34: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("35: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 13u << 0u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("36: equal rows, less columns") << StringMatrix{10, 8, "Value1"} << 10u << 7u << std::string{"Value2"} << 0u << 0u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("37: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 7u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("38: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 8u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("39: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("40: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("41: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("42: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 8u << 0u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("43: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 7u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("44: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 8u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("45: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("46: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("47: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("48: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 9u << 0u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("49: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 7u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("50: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("51: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("52: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("53: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("54: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 10u << 0u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("55: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 7u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("56: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("57: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("58: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("59: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("60: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 11u << 0u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("61: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 7u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("62: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("63: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("64: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("65: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("66: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 12u << 0u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("67: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 7u << 13u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("68: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("69: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("70: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("71: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("72: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 13u << 0u << 13u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("73: less rows, equal columns") << StringMatrix{10, 8, "Value1"} << 9u << 8u << std::string{"Value2"} << 0u << 0u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("74: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 6u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("75: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 7u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("76: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 8u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("77: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("78: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("79: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("80: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 8u << 0u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("81: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 6u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("82: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 7u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("83: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 8u << 9u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("84: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("85: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("86: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("87: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 9u << 0u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("88: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 6u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("89: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 7u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("90: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("91: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("92: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("93: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("94: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 10u << 0u << 10u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("95: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 6u << 11u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("96: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 7u << 11u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("97: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("98: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("99: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("100: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("101: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 11u << 0u << 11u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("102: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 6u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("103: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 7u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("104: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("105: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("106: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("107: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("108: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 12u << 0u << 12u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("109: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 6u << 13u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("110: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 7u << 13u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("111: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("112: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("113: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("114: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{2u};
    QTest::newRow("115: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 13u << 0u << 13u << 7u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("116: less rows, less columns") << StringMatrix{10, 8, "Value1"} << 9u << 7u << std::string{"Value2"} << 0u << 0u << 9u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("117: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 7u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("118: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("119: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("120: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("121: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("122: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 9u << 0u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("123: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 7u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("124: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 8u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("125: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("126: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("127: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("128: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 10u << 0u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("129: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 7u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("130: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("131: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("132: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("133: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("134: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 11u << 0u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("135: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 7u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("136: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("137: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("138: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("139: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("140: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 12u << 0u << 12u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("141: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 7u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("142: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("143: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("144: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("145: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("146: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 13u << 0u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("147: same rows, same columns") << StringMatrix{10, 8, "Value1"} << 10u << 8u << std::string{"Value2"} << 0u << 0u << 10u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("148: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 7u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("149: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("150: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("151: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("152: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("153: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 9u << 0u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("154: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 7u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("155: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("156: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("157: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("158: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("159: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 10u << 0u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("160: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 7u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("161: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("162: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("163: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("164: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("165: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 11u << 0u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("166: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 7u << 12u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("167: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("168: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("169: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("170: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("171: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 12u << 0u << 12u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("172: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 7u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("173: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("174: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("175: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("176: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("177: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 13u << 0u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("178: more rows, same columns") << StringMatrix{10, 8, "Value1"} << 11u << 8u << std::string{"Value2"} << 0u << 0u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("179: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 7u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("180: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 8u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("181: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("182: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("183: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("184: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 9u << 0u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("185: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 7u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("186: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 8u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("187: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("188: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("189: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("190: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 10u << 0u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("191: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 7u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("192: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 8u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("193: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("194: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("195: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("196: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 11u << 0u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("197: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 7u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("198: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 8u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("199: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("200: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("201: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("202: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 12u << 0u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("203: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 7u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("204: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 8u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("205: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("206: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("207: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("208: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 13u << 0u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("209: same rows, more columns") << StringMatrix{10, 8, "Value1"} << 10u << 9u << std::string{"Value2"} << 0u << 0u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("210: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 7u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("211: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 8u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("212: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("213: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("214: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("215: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 9u << 0u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("216: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 7u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("217: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 8u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("218: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("219: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("220: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("221: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 10u << 0u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("222: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 7u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("223: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 8u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("224: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("225: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("226: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("227: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 11u << 0u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("228: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 7u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("229: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 8u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("230: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("231: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("232: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("233: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 12u << 0u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("234: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 7u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("235: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 8u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("236: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("237: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("238: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("239: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 13u << 0u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("240: more rows, more columns") << StringMatrix{10, 8, "Value1"} << 11u << 9u << std::string{"Value2"} << 0u << 0u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("241: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 6u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("242: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 7u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("243: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("244: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("245: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("246: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("247: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 9u << 0u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("248: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 6u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("249: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 7u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("250: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("251: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("252: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("253: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("254: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 10u << 0u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("255: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 6u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("256: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 7u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("257: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 8u << 11u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("258: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("259: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("260: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("261: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 11u << 0u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("262: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 6u << 12u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("263: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 7u << 12u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("264: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 8u << 12u << 8u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("265: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("266: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("267: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{2u};
    QTest::newRow("268: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 12u << 0u << 12u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("269: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 6u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("270: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 7u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("271: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 8u << 13u << 8u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("272: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("273: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("274: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{2u};
    QTest::newRow("275: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 13u << 0u << 13u << 7u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("276: more rows, less columns") << StringMatrix{10, 8, "Value1"} << 11u << 7u << std::string{"Value2"} << 0u << 0u << 11u << 7u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("277: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 7u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("278: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 8u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("279: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("280: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("281: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("282: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 8u << 0u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("283: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 7u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("284: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 8u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("285: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 9u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("286: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 10u << 9u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("287: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 11u << 9u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("288: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 9u << 0u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("289: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 7u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("290: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 8u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("291: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 9u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("292: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 10u << 10u << 10u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("293: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 11u << 10u << 11u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("294: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 10u << 0u << 10u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("295: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 7u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("296: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 8u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("297: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 9u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("298: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 10u << 11u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("299: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 11u << 11u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("300: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 11u << 0u << 11u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("301: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 7u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("302: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 8u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("303: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 9u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("304: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 10u << 12u << 10u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("305: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 11u << 12u << 11u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
    QTest::newRow("306: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 12u << 0u << 12u << 9u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("307: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 7u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("308: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 8u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("309: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 9u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("310: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 10u << 13u << 10u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("311: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 11u << 13u << 11u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{1u};
    QTest::newRow("312: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 13u << 0u << 13u << 9u << StringMatrixOptSizeType{2u} << StringMatrixOptSizeType{0u};
    QTest::newRow("313: less rows, more columns") << StringMatrix{10, 8, "Value1"} << 9u << 9u << std::string{"Value2"} << 0u << 0u << 9u << 9u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};

    // empty matrix
    QTest::newRow("314: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 0u << 0u << 1u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("315: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 0u << 1u << 1u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("316: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 0u << 2u << 1u << 2u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("317: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 0u << 3u << 1u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("318: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 1u << 0u << 1u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("319: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 1u << 1u << 1u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("320: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 1u << 2u << 1u << 2u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("321: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 1u << 3u << 1u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("322: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 2u << 0u << 2u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("323: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 2u << 1u << 2u << 1u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("324: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 2u << 2u << 2u << 2u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{0u};
    QTest::newRow("325: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 2u << 3u << 2u << 3u << StringMatrixOptSizeType{0u} << StringMatrixOptSizeType{1u};
    QTest::newRow("326: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 3u << 0u << 3u << 1u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("327: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 3u << 1u << 3u << 1u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("328: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 3u << 2u << 3u << 2u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{0u};
    QTest::newRow("329: more rows, more columns") << StringMatrix{} << 1u << 1u << std::string{"Value2"} << 3u << 3u << 3u << 3u << StringMatrixOptSizeType{1u} << StringMatrixOptSizeType{1u};
}

QTEST_APPLESS_MAIN(CapacityTests)

#include "tst_capacitytests.moc"
