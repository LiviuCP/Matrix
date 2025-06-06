#include <QtTest>

#include "testutils.h"
#include "tst_capacitytests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(size_tuple_t) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(size_tuple_array_t) // same here
Q_DECLARE_METATYPE(ConcatMode)
Q_DECLARE_METATYPE(SplitMode)

class IntMatrixCapacityTests : public QObject
{
    Q_OBJECT

private slots:
    // test functions
    void testCopiedVectorConstructor();
    void testMovedVectorConstructor();
    void testIdenticalElementsConstructor();
    void testDiagonalMatrixConstructor();
    void testCopyConstructor();
    void testMoveConstructor();
    void testCopyAssignmentOperator();
    void testMoveAssignmentOperator();
    void testTranspose();
    void testReserve();
    void testResizeAndDefaultNewValues();
    void testResizeAndSetNewValues();
    void testReserveAndResizeWithDefaultNewValues();
    void testReserveAndResizeAndSetNewValues();
    void testInsertRowAndDefaultNewValues();
    void testInsertRowAndSetNewValues();
    void testInsertColumnAndDefaultNewValues();
    void testInsertColumnAndSetNewValues();
    void testReserveAndInsertRowAndDefaultNewValues();
    void testReserveAndInsertRowAndSetNewValues();
    void testReserveAndInsertColumnAndDefaultNewValues();
    void testReserveAndInsertColumnAndSetNewValues();
    void testEraseRow();
    void testEraseColumn();
    void testCatByRow();
    void testCatByColumn();
    void testSplitByRow();
    void testSplitByColumn();
    void testReserveResizeAndEraseRowAndOrColumn(); // combined IntMatrix test (reserve/resize + erase row/column)

    // test data
    void testCopiedVectorConstructor_data();
    void testMovedVectorConstructor_data();
    void testIdenticalElementsConstructor_data();
    void testDiagonalMatrixConstructor_data();
    void testCopyConstructor_data();
    void testMoveConstructor_data();
    void testCopyAssignmentOperator_data();
    void testMoveAssignmentOperator_data();
    void testTranspose_data();
    void testReserve_data();
    void testResizeAndDefaultNewValues_data();
    void testResizeAndSetNewValues_data();
    void testReserveAndResizeWithDefaultNewValues_data();
    void testReserveAndResizeAndSetNewValues_data();
    void testInsertRowAndDefaultNewValues_data();
    void testInsertRowAndSetNewValues_data();
    void testInsertColumnAndDefaultNewValues_data();
    void testInsertColumnAndSetNewValues_data();
    void testReserveAndInsertRowAndDefaultNewValues_data();
    void testReserveAndInsertRowAndSetNewValues_data();
    void testReserveAndInsertColumnAndDefaultNewValues_data();
    void testReserveAndInsertColumnAndSetNewValues_data();
    void testEraseRow_data();
    void testEraseColumn_data();
    void testCatByRow_data();
    void testCatByColumn_data();
    void testSplitByRow_data();
    void testSplitByColumn_data();
    void testReserveResizeAndEraseRowAndOrColumn_data();

private:
    // test data helper methods
    void _buildMovedCopiedVectorConstructorsTestingTable();
    void _buildMoveCopyConstructorsTestingTable();
    void _buildAssignmentOperatorsTestingTable();
    void _buildReserveAndResizeTestingTable();
    void _buildResizeTestingTable();
    void _buildInsertRowTestingTable();
    void _buildInsertColumnTestingTable();
    void _buildReserveAndInsertRowTestingTable();
    void _buildReserveAndInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
    IntMatrix mSecondaryIntMatrix;
};

void IntMatrixCapacityTests::testCopiedVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    IntMatrix matrix{rowsCount, columnsCount, initList};

    TEST_COPIED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
}

void IntMatrixCapacityTests::testMovedVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<int>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    IntMatrix matrix{rowsCount, columnsCount, std::move(initList)};

    TEST_MOVED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
}

void IntMatrixCapacityTests::testIdenticalElementsConstructor()
{
    TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(int);
}

void IntMatrixCapacityTests::testDiagonalMatrixConstructor()
{
    TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(int);
}

void IntMatrixCapacityTests::testCopyConstructor()
{
    TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(int);
}

void IntMatrixCapacityTests::testMoveConstructor()
{
    TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(int);
}

void IntMatrixCapacityTests::testCopyAssignmentOperator()
{
    TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(int);
}

void IntMatrixCapacityTests::testMoveAssignmentOperator()
{
    TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(int);
}

void IntMatrixCapacityTests::testTranspose()
{
    TEST_CAPACITY_WITH_TRANSPOSE(int, mPrimaryIntMatrix, mSecondaryIntMatrix);
}

void IntMatrixCapacityTests::testReserve()
{
    TEST_CAPACITY_WITH_RESERVE(int, mPrimaryIntMatrix);
}

void IntMatrixCapacityTests::testResizeAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_DEFAULT_NEW_VALUES(int, mPrimaryIntMatrix);
}

void IntMatrixCapacityTests::testResizeAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(int, mPrimaryIntMatrix);
}

/* In addition to testing resulting capacity a consistency check (size and retained element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void IntMatrixCapacityTests::testReserveAndResizeWithDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_RESIZE_AND_DEFAULT_NEW_VALUES(int, mPrimaryIntMatrix);
}

/* In addition to testing resulting capacity a consistency check (size and element values comparison) is required in order to ensure
   the resizing with explicitly given capacity is consistent with the one where the capacity is not explicitly provided as argument
*/
void IntMatrixCapacityTests::testReserveAndResizeAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_RESIZE_AND_FILL_IN_NEW_VALUES(int, mPrimaryIntMatrix);
}

void IntMatrixCapacityTests::testInsertRowAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_DEFAULT_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testInsertRowAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_FILL_IN_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testInsertColumnAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testInsertColumnAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testReserveAndInsertRowAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_INSERT_ROW_AND_DEFAULT_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testReserveAndInsertRowAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_INSERT_ROW_AND_FILL_IN_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testReserveAndInsertColumnAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testReserveAndInsertColumnAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESERVE_AND_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(int);
}

void IntMatrixCapacityTests::testEraseRow()
{
    TEST_CAPACITY_WITH_ERASE_ROW(int);
}

void IntMatrixCapacityTests::testEraseColumn()
{
    TEST_CAPACITY_WITH_ERASE_COLUMN(int);
}

void IntMatrixCapacityTests::testCatByRow()
{
    TEST_CAPACITY_WITH_CAT_BY_ROW(int);
}

void IntMatrixCapacityTests::testCatByColumn()
{
    TEST_CAPACITY_WITH_CAT_BY_COLUMN(int);
}

void IntMatrixCapacityTests::testSplitByRow()
{
    TEST_CAPACITY_WITH_SPLIT_BY_ROW(int);
}

void IntMatrixCapacityTests::testSplitByColumn()
{
    TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(int);
}

void IntMatrixCapacityTests::testReserveResizeAndEraseRowAndOrColumn()
{
    TEST_CAPACITY_WITH_RESIZE_AND_ERASE_ROW_AND_OR_COLUMN(int, mPrimaryIntMatrix);
}

void IntMatrixCapacityTests::testCopiedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void IntMatrixCapacityTests::testMovedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void IntMatrixCapacityTests::testIdenticalElementsConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << -5 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << -5 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: large size matrix") << matrix_size_t{25u} << matrix_size_t{20u} << 2 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("4: large size matrix") << matrix_size_t{20u} << matrix_size_t{25u} << 2 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("5: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("6: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << 0 << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << 0 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << 0 << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << 0 << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::testDiagonalMatrixConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsColumnsCount");
    QTest::addColumn<int>("nonDiagonalValue");
    QTest::addColumn<int>("diagonalValue");
    QTest::addColumn<matrix_size_t>("expectedRowColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << -2 << -3 << matrix_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << -2 << -3 << matrix_size_t{5u} << matrix_opt_size_t{0u};
    QTest::newRow("3: medium size matrix") << matrix_size_t{8u} << -2 << -3 << matrix_size_t{10u} << matrix_opt_size_t{1u};
    QTest::newRow("4: medium size matrix") << matrix_size_t{10u} << -2 << -3 << matrix_size_t{12u} << matrix_opt_size_t{1u};
    QTest::newRow("5: capped capacity") << c_LargeDimension1 << -2 << -3 << c_MaxAllowedDimension << matrix_opt_size_t{1u};
    QTest::newRow("6: capped capacity") << c_LargeDimension2 << -2 << -3 << c_MaxAllowedDimension << matrix_opt_size_t{0u};
    QTest::newRow("7: capped capacity") << c_MaxAllowedDimension << -2 << -3 << c_MaxAllowedDimension << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::testCopyConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void IntMatrixCapacityTests::testMoveConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void IntMatrixCapacityTests::testCopyAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void IntMatrixCapacityTests::testMoveAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void IntMatrixCapacityTests::testTranspose_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << IntMatrix{{3, 4}, 2} << IntMatrix{} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("2: transposed matrix initially empty") << IntMatrix{{4, 3}, 2} << IntMatrix{} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("3: transposed matrix initially empty") << IntMatrix{{7, 8}, 2} << IntMatrix{} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("4: transposed matrix initially empty") << IntMatrix{{8, 7}, 2} << IntMatrix{} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("5: transposed matrix initially empty") << IntMatrix{{20, 25}, 2} << IntMatrix{} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << false;
    QTest::newRow("6: transposed matrix initially empty") << IntMatrix{{25, 20}, 2} << IntMatrix{} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << IntMatrix{{8, 7}, 2} << IntMatrix{{5, 6}, 2} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << IntMatrix{{8, 7}, 2} << IntMatrix{{6, 6}, 2} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << IntMatrix{{8, 7}, 2} << IntMatrix{{5, 7}, 2} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << IntMatrix{{8, 7}, 2} << IntMatrix{{6, 7}, 2} << matrix_size_t{7u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << IntMatrix{{8, 7}, 2} << IntMatrix{{7, 8}, 2} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{15, 19}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{16, 19}, 2} << matrix_size_t{20u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{15, 20}, 2} << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{16, 20}, 2} << matrix_size_t{20u} << matrix_size_t{25u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{20, 25}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{15, 25}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{16, 25}, 2} << matrix_size_t{20u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{20, 19}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << IntMatrix{{25, 20}, 2} << IntMatrix{{20, 20}, 2} << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("21: matrix transposed to itself") << IntMatrix{{3, 3}, 2} << IntMatrix{{3, 3}, 2} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("22: matrix transposed to itself") << IntMatrix{{3, 4}, 2} << IntMatrix{{3, 4}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << true;
    QTest::newRow("23: matrix transposed to itself") << IntMatrix{{4, 3}, 2} << IntMatrix{{4, 3}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("24: matrix transposed to itself") << IntMatrix{{4, 4}, 2} << IntMatrix{{4, 4}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("25: matrix transposed to itself") << IntMatrix{{7, 8}, 2} << IntMatrix{{7, 8}, 2} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << true;
    QTest::newRow("26: matrix transposed to itself") << IntMatrix{{8, 7}, 2} << IntMatrix{{8, 7}, 2} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("27: matrix transposed to itself") << IntMatrix{{20, 25}, 2} << IntMatrix{{20, 25}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{5u} << true;
    QTest::newRow("28: matrix transposed to itself") << IntMatrix{{25, 20}, 2} << IntMatrix{{25, 20}, 2} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{5u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("29: matrix transposed to itself") << IntMatrix{{25, 25}, 2} << IntMatrix{{25, 25}, 2} << matrix_size_t{31u} << matrix_size_t{31u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << true;
    QTest::newRow("30: matrix transposed to itself") << IntMatrix{{20, 26}, 2} << IntMatrix{{20, 26}, 2} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{3u} << matrix_opt_size_t{6u} << true;
    QTest::newRow("31: matrix transposed to itself") << IntMatrix{{26, 20}, 2} << IntMatrix{{26, 20}, 2} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{6u} << matrix_opt_size_t{3u} << true;
}

void IntMatrixCapacityTests::testReserve_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    const matrix_size_t c_RowsCount{10};
    const matrix_opt_size_t c_LargeDimensionRowCapacityOffset{(c_LargeDimension2 - c_RowsCount) / 2};
    const matrix_opt_size_t c_MaxDimensionRowCapacityOffset{(c_MaxAllowedDimension - c_RowsCount) / 2};

    const matrix_size_t c_ColumnsCount{8};
    const matrix_opt_size_t c_LargeDimensionColumnCapacityOffset{(c_LargeDimension2 - c_ColumnsCount) / 2};
    const matrix_opt_size_t c_MaxDimensionColumnCapacityOffset{(c_MaxAllowedDimension - c_ColumnsCount) / 2};

    QTest::newRow("1: row capacity < rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: row capacity < rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{0u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: row capacity < rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: row capacity < rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: row capacity < rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("7: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("10: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("11: row capacity < rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("12: row capacity == rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: row capacity == rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: row capacity == rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("19: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("20: row capacity == rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("21: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("24: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("26: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("27: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("28: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{7u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("29: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("30: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{7u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("31: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("32: row capacity > rows count, column capacity < columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{7u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("33: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("34: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("35: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("36: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("37: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("38: row capacity > rows count, column capacity == columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{8u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("39: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("41: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("42: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("43: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("44: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << c_ExceedingDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("45: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("46: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("47: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("48: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << c_LargeDimension2 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("49: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("50: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << c_ExceedingDimension << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("51: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("52: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("54: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << c_LargeDimension2 << matrix_size_t{13u} << c_LargeDimension2 << matrix_opt_size_t{1u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("55: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("56: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << c_ExceedingDimension << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("57: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{9u} << c_LargeDimension2 << matrix_size_t{9u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("58: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("59: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("60: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("61: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("62: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << c_ExceedingDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("63: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("64: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("65: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("66: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("67: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("68: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("69: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("70: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("71: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("72: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("73: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("74: row capacity > rows count, column capacity > columns count") << IntMatrix{{10, 8}, -2} << c_ExceedingDimension << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("75: row capacity < rows count, column capacity < columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension0 << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("76: row capacity < rows count, column capacity == columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("77: row capacity < rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension0 << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("78: row capacity < rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension0 << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("79: row capacity == rows count, column capacity < columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("80: row capacity == rows count, column capacity == columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("81: row capacity == rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("82: row capacity == rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension1 << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("83: row capacity > rows count, column capacity < columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension0 << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("84: row capacity > rows count, column capacity < columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension0 << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("85: row capacity > rows count, column capacity == columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("86: row capacity > rows count, column capacity == columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("87: row capacity > rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("88: row capacity > rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("89: row capacity > rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("90: row capacity > rows count, column capacity > columns count") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    // empty matrix
    QTest::newRow("91: empty matrix") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("92: empty matrix") << IntMatrix{} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("93: empty matrix") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("94: empty matrix") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void IntMatrixCapacityTests::testResizeAndDefaultNewValues_data()
{
    _buildResizeTestingTable();
}

void IntMatrixCapacityTests::testResizeAndSetNewValues_data()
{
    _buildResizeTestingTable();
}

void IntMatrixCapacityTests::testReserveAndResizeWithDefaultNewValues_data()
{
    _buildReserveAndResizeTestingTable();
}

void IntMatrixCapacityTests::testReserveAndResizeAndSetNewValues_data()
{
    _buildReserveAndResizeTestingTable();
}

void IntMatrixCapacityTests::testInsertRowAndDefaultNewValues_data()
{
    _buildInsertRowTestingTable();
}

void IntMatrixCapacityTests::testInsertRowAndSetNewValues_data()
{
    _buildInsertRowTestingTable();
}

void IntMatrixCapacityTests::testInsertColumnAndDefaultNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void IntMatrixCapacityTests::testInsertColumnAndSetNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void IntMatrixCapacityTests::testReserveAndInsertRowAndDefaultNewValues_data()
{
    _buildReserveAndInsertRowTestingTable();
}

void IntMatrixCapacityTests::testReserveAndInsertRowAndSetNewValues_data()
{
    _buildReserveAndInsertRowTestingTable();
}

void IntMatrixCapacityTests::testReserveAndInsertColumnAndDefaultNewValues_data()
{
    _buildReserveAndInsertColumnTestingTable();
}

void IntMatrixCapacityTests::testReserveAndInsertColumnAndSetNewValues_data()
{
    _buildReserveAndInsertColumnTestingTable();
}

void IntMatrixCapacityTests::testEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << IntMatrix{{3, 4}, -2} << size_tuple_array_t{{1u, 3u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {1u, 3u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("2: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{1u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {1u, 12u, 18u, matrix_opt_size_t{5u}, {1u}}, {1u, 12u, 18u, matrix_opt_size_t{6u}, {1u}}, {1u, 12u, 18u, matrix_opt_size_t{7u}, {1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("3: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{8u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {7u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {6u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {5u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {4u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {3u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 18u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("4: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{0u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {8u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {6u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {4u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 18u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("5: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{9u, 12u, 18u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {5u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {3u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {0u, 6u, 18u, matrix_opt_size_t{2u}, {1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("6: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{3u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {6u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 18u, matrix_opt_size_t{2u}, {1u}}, {2u, 12u, 18u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {2u, 12u, 18u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("7: square matrix") << IntMatrix{{4, 4}, -2} << size_tuple_array_t{{1u, 5u, 5u, matrix_opt_size_t{1u}, {0u}}, {1u, 5u, 5u, matrix_opt_size_t{1u}, {0u}}, {1u, 2u, 5u, matrix_opt_size_t{0u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("8: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{1u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{5u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{6u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{7u}, {1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("9: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{8u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {3u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 12u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("10: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{0u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {8u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {6u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {4u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 12u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("11: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{9u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {5u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {3u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 6u, 12u, matrix_opt_size_t{2u}, {1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("12: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{3u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {6u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 12u, matrix_opt_size_t{2u}, {1u}}, {2u, 12u, 12u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {2u, 12u, 12u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("13: more rows than columns") << IntMatrix{{7, 5}, -2} << size_tuple_array_t{{1u, 8u, 6u, matrix_opt_size_t{1u}, {0u}}, {1u, 8u, 6u, matrix_opt_size_t{2u}, {0u}}, {1u, 8u, 6u, matrix_opt_size_t{3u}, {0u}}, {1u, 8u, 6u, matrix_opt_size_t{4u}, {0u}}, {1u, 4u, 6u, matrix_opt_size_t{1u}, {0u}}, {1u, 2u, 6u, matrix_opt_size_t{0u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("14: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{1u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{5u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{6u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{7u}, {1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("15: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{8u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {7u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {6u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {5u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {4u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {3u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 11u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("16: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{0u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {8u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {6u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {4u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {2u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {0u, 2u, 11u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("17: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{9u, 12u, 11u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {0u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {5u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {0u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {3u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {0u, 6u, 11u, matrix_opt_size_t{2u}, {1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("18: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{3u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {6u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {7u, 12u, 11u, matrix_opt_size_t{2u}, {1u}}, {2u, 12u, 11u, matrix_opt_size_t{3u}, {1u}}, {1u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {2u, 12u, 11u, matrix_opt_size_t{4u}, {1u}}, {0u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, {1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, {1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
}

void IntMatrixCapacityTests::testEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << IntMatrix{{4, 3}, 4} << size_tuple_array_t{{1u, 5u, 3u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {1u, 5u, 3u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("2: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{1u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {5u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {6u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {7u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("3: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{8u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {5u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {4u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {3u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("4: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{0u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {8u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {4u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("5: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{9u, 18u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {5u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {3, 18, 6, {1u}, {1u}}, {0, 18, 6, {1u}, {2u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("6: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{3u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, {2u}}, {2u, 18u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {2u, 18u, 12u, matrix_opt_size_t{1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("7: square matrix") << IntMatrix{{4, 4}, 4} << size_tuple_array_t{{1u, 5u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 5u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 5u, 2u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("8: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{1u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {5u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {6u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {7u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("9: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{8u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {3u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {2u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("10: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{0u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {8u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {2u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("11: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{9u, 12u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {3u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, {2u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("12: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{3u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, {2u}}, {2u, 12u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {2u, 12u, 12u, matrix_opt_size_t{1u}, {4u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("13: more columns than rows") << IntMatrix{{5, 7}, 4} <<  size_tuple_array_t{{1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{2u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{3u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{4u}}, {1u, 6u, 4u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 6u, 2u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("14: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{1u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {5u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {6u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {7u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("15: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{8u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {5u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {4u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {3u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {2u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 11u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("16: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{0u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {8u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {4u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {2u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 11u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("17: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{9u, 11u, 12u, matrix_opt_size_t{1u}, {1u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {5u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {3u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, {2u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("18: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{3u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, {2u}}, {2u, 11u, 12u, matrix_opt_size_t{1u}, {3u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {2u, 11u, 12u, matrix_opt_size_t{1u}, {4u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, {1u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, {0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
}

void IntMatrixCapacityTests::testCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("6: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("12: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("14: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{22u} << matrix_size_t{26u} << matrix_size_t{22u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{31u} << matrix_size_t{26u} << matrix_size_t{31u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("16: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("17: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{33u} << matrix_size_t{28u} << matrix_size_t{33u} << matrix_size_t{28u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u};
    QTest::newRow("18: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("19: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{22u} << matrix_size_t{26u} << matrix_size_t{22u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{31u} << matrix_size_t{26u} << matrix_size_t{31u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("21: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("22: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{33u} << matrix_size_t{28u} << matrix_size_t{33u} << matrix_size_t{28u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u};
    QTest::newRow("23: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{1, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("24: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{2, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("25: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{3, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("26: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{4, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("27: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{5, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("28: different matrixes") << IntMatrix{{1, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{17u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("29: different matrixes") << IntMatrix{{2, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{18u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("30: different matrixes") << IntMatrix{{3, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{19u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("31: different matrixes") << IntMatrix{{4, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("32: different matrixes") << IntMatrix{{5, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("33: different matrixes") << IntMatrix{{c_LargeDimension2, 22}, 5} << IntMatrix{{1, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("34: different matrixes") << IntMatrix{{c_LargeDimension1, 22}, 5} << IntMatrix{{2, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("35: different matrixes") << IntMatrix{{1, 22}, -2} << IntMatrix{{c_LargeDimension2, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("36: different matrixes") << IntMatrix{{2, 22}, -2} << IntMatrix{{c_LargeDimension1, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("37: different matrixes") << IntMatrix{{c_LargeDimension0, 22}, 5} << IntMatrix{{1, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("38: different matrixes") << IntMatrix{{c_LargeDimension0, 22}, 5} << IntMatrix{{2, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("39: different matrixes") << IntMatrix{{c_LargeDimension0, 22}, 5} << IntMatrix{{3, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("40: different matrixes") << IntMatrix{{1, 22}, -2} << IntMatrix{{c_LargeDimension0, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("41: different matrixes") << IntMatrix{{2, 22}, -2} << IntMatrix{{c_LargeDimension0, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("42: different matrixes") << IntMatrix{{3, 22}, -2} << IntMatrix{{c_LargeDimension0, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("43_1a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_2a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_3a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_4a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_5a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_6a: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_7a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
        QTest::newRow("43_8a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_9a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_10a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_11a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_12a: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }
    else
    {
        QTest::newRow("43_1b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension0 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_2b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_3b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_4b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_5b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_6b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_7b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_8b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_9b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
        QTest::newRow("43_10b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
        QTest::newRow("43_11b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_12b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
        QTest::newRow("43_13b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_14b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_15b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("43_16b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }

    QTest::newRow("44: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{7u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("48: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("49: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("50: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("51: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{31u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("52: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("53: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{33u} << matrix_size_t{27u} << matrix_size_t{33u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("54: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{34u} << matrix_size_t{27u} << matrix_size_t{34u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("55: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{38u} << matrix_size_t{27u} << matrix_size_t{38u} << matrix_size_t{27u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};

    // additional tests for checking impact on column capacity when reserving and concatenating
    QTest::newRow("56: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("57: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("58: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("59: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("60: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{6u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("61: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("62: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("63: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("64: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("65: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("66: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("67: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("68: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("69: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("70: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("71: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("72: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{6u} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("73: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("74: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("75: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void IntMatrixCapacityTests::testCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("6: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("7: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("12: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};  // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("13: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("14: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{22u} << matrix_size_t{26u} << matrix_size_t{22u} << matrix_size_t{26u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{31u} << matrix_size_t{26u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("16: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("17: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{28u} << matrix_size_t{33u} << matrix_size_t{28u} << matrix_size_t{33u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u};
    QTest::newRow("18: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("19: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{22u} << matrix_size_t{26u} << matrix_size_t{22u} << matrix_size_t{26u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{31u} << matrix_size_t{26u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("21: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("22: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{28u} << matrix_size_t{33u} << matrix_size_t{28u} << matrix_size_t{33u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u};
    QTest::newRow("23: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 1}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("24: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 2}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("25: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 3}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("26: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 4}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("27: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("28: different matrixes") << IntMatrix{{22, 1}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{17u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("29: different matrixes") << IntMatrix{{22, 2}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("30: different matrixes") << IntMatrix{{22, 3}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("31: different matrixes") << IntMatrix{{22, 4}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("32: different matrixes") << IntMatrix{{22, 5}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("33: different matrixes") << IntMatrix{{22, c_LargeDimension2}, 5} << IntMatrix{{22, 1}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("34: different matrixes") << IntMatrix{{22, c_LargeDimension1}, 5} << IntMatrix{{22, 2}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("35: different matrixes") << IntMatrix{{22, 1}, -2} << IntMatrix{{22, c_LargeDimension2}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("36: different matrixes") << IntMatrix{{22, 2}, -2} << IntMatrix{{22, c_LargeDimension1}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("37: different matrixes") << IntMatrix{{22, c_LargeDimension0}, 5} << IntMatrix{{22, 1}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("38: different matrixes") << IntMatrix{{22, c_LargeDimension0}, 5} << IntMatrix{{22, 2}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};  // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("39: different matrixes") << IntMatrix{{22, c_LargeDimension0}, 5} << IntMatrix{{22, 3}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("40: different matrixes") << IntMatrix{{22, 1}, -2} << IntMatrix{{22, c_LargeDimension0}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("41: different matrixes") << IntMatrix{{22, 2}, -2} << IntMatrix{{22, c_LargeDimension0}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("42: different matrixes") << IntMatrix{{22, 3}, -2} << IntMatrix{{22, c_LargeDimension0}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("43_1a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_2a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_3a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_4a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_5a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_6a: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_7a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
        QTest::newRow("43_8a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_9a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_10a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_11a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_12a: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("43_1b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension0 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_2b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_3b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_4b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_5b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_6b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_7b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_8b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_9b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
        QTest::newRow("43_10b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
        QTest::newRow("43_11b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_12b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
        QTest::newRow("43_13b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_14b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_15b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("43_16b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }

    QTest::newRow("44: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("48: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("49: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u};  // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("50: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("51: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{31u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("52: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{32u} << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("53: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{33u} << matrix_size_t{27u} << matrix_size_t{33u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("54: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{34u} << matrix_size_t{27u} << matrix_size_t{34u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("55: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{38u} << matrix_size_t{27u} << matrix_size_t{38u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};

    // additional tests for checking impact on column capacity when reserving and concatenating
    QTest::newRow("56: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("57: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{7u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("58: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("59: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("60: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{6u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("61: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{7u} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("62: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("63: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("64: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("65: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("66: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("67: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("68: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("69: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("70: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("71: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("72: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{6u} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("73: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("74: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("75: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
}

void IntMatrixCapacityTests::testSplitByRow_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<matrix_size_t>("resizeRowCapacity");
    QTest::addColumn<matrix_size_t>("resizeColumnCapacity");
    QTest::addColumn<bool>("shouldResizeFirstDestMatrix");
    QTest::addColumn<matrix_size_t>("expectedFirstDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedFirstDestColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedSecondDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSecondDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("2: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("3: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 15}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 17}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("7: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("8: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("9: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{17u} << true << matrix_size_t{10u} << matrix_size_t{17u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("10: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{18u} << true << matrix_size_t{10u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("11: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 15}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("12: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 17}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};;
    QTest::newRow("13: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("14: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("15: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{17u} << true << matrix_size_t{10u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("16: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{18u} << true << matrix_size_t{10u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("17: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 15}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("18: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 17}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("19: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("20: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{6, 15}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{7, 17}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("24: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 17}, 2} << IntMatrix{{7, 17}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("25: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("26: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("27: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{17u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("28: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{18u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("29: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 15}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: source first") << IntMatrix{{15, 17}, -3} << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 17}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("31: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("32: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("33: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << true << matrix_size_t{8u} << matrix_size_t{17u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("34: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << true << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("35: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 15}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{7u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("36: source second") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 17}, 2} << IntMatrix{{15, 17}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("37: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("38: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("39: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << true << matrix_size_t{8u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("40: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{5u} << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << true << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("41: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 15}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{7u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("42: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 17}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("43: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("44: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{17u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("45: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{6, 8}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{6u} << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{18u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("46: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{7, 15}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{} << IntMatrix{{8, 17}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("48: all different") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 17}, 2} << IntMatrix{{8, 17}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{{25, 20}, -3} << IntMatrix{{9, 12}, 2} << IntMatrix{{18, 9}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{14u} << matrix_size_t{18u} << true << matrix_size_t{14u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u};
    QTest::newRow("50: all different") << IntMatrix{{25, 20}, -3} << IntMatrix{{9, 12}, 2} << IntMatrix{{18, 9}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{11u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_size_t{25u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u};
    QTest::newRow("51: all different") << IntMatrix{{25, 20}, -3} << IntMatrix{{9, 12}, 2} << IntMatrix{{18, 9}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{20u} << true << matrix_size_t{13u} << matrix_size_t{20u} << matrix_size_t{22u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u};
    QTest::newRow("52: all different") << IntMatrix{{25, 20}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{13u} << matrix_size_t{25u} << matrix_size_t{17u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("53: source first") << IntMatrix{{25, 20}, -3} << IntMatrix{{25, 20}, -3} << IntMatrix{{18, 9}, 2} << matrix_size_t{11u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{31u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u} << matrix_opt_size_t{2u};
    QTest::newRow("54: source first") << IntMatrix{{25, 20}, -3} << IntMatrix{{25, 20}, -3} << IntMatrix{} << matrix_size_t{11u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{31u} << matrix_size_t{25u} << matrix_size_t{17u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("55: source second") << IntMatrix{{25, 20}, -3} << IntMatrix{{9, 12}, 2} << IntMatrix{{25, 20}, -3} << matrix_size_t{11u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{11u} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("56: source second") << IntMatrix{{25, 20}, -3} << IntMatrix{} << IntMatrix{{25, 20}, -3} << matrix_size_t{11u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{13u} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
}

void IntMatrixCapacityTests::testSplitByColumn_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("firstDestMatrix");
    QTest::addColumn<IntMatrix>("secondDestMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<SplitMode>("mode");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<matrix_size_t>("resizeRowCapacity");
    QTest::addColumn<matrix_size_t>("resizeColumnCapacity");
    QTest::addColumn<bool>("shouldResizeFirstDestMatrix");
    QTest::addColumn<matrix_size_t>("expectedFirstDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedFirstDestColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedSecondDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSecondDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedFirstDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedFirstDestColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSecondDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSecondDestColumnCapacityOffset");

    QTest::newRow("1: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("2: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("3: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{17u} << matrix_size_t{6u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{18u} << matrix_size_t{6u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 6}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 7}, 2} << matrix_size_t{8u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("7: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("8: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("9: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << matrix_size_t{7u} << true << matrix_size_t{17u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("10: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << matrix_size_t{7u} << true << matrix_size_t{18u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("11: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 7}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("12: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 8}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{8u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("13: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("14: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("15: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << matrix_size_t{7u} << true << matrix_size_t{17u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("16: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << matrix_size_t{7u} << true << matrix_size_t{18u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("17: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 7}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("18: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 8}, 2} << IntMatrix{} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("19: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("20: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{17u} << matrix_size_t{6u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{18u} << matrix_size_t{6u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{15, 6}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{17, 7}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("24: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 8}, 2} << IntMatrix{{17, 7}, 2} << matrix_size_t{8u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("25: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("26: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("27: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << matrix_size_t{7u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("28: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << matrix_size_t{7u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("29: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 7}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: source first") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 8}, 2} << matrix_size_t{7u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("31: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("32: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("33: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{17u} << matrix_size_t{6u} << true << matrix_size_t{17u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("34: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{18u} << matrix_size_t{6u} << true << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("35: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 6}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{7u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("36: source second") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 7}, 2} << IntMatrix{{17, 15}, -3} << matrix_size_t{7u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("37: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("38: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("39: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{17u} << matrix_size_t{6u} << true << matrix_size_t{17u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("40: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{5u} << matrix_size_t{18u} << matrix_size_t{6u} << true << matrix_size_t{18u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("41: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 6}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{18u} << matrix_size_t{7u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("42: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 7}, 2} << IntMatrix{} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("43: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("44: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{17u} << matrix_size_t{7u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("45: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{8, 6}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{18u} << matrix_size_t{7u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("46: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{15, 7}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{} << IntMatrix{{17, 8}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("48: all different") << IntMatrix{{17, 15}, -3} << IntMatrix{{17, 7}, 2} << IntMatrix{{17, 8}, 2} << matrix_size_t{7u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};

    // additional tests
    QTest::newRow("49: all different") << IntMatrix{{20, 25}, -3} << IntMatrix{{12, 9}, 2} << IntMatrix{{9, 18}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{18u} << matrix_size_t{14u} << true << matrix_size_t{25u} << matrix_size_t{14u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u};
    QTest::newRow("50: all different") << IntMatrix{{20, 25}, -3} << IntMatrix{{12, 9}, 2} << IntMatrix{{9, 18}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{11u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u};
    QTest::newRow("51: all different") << IntMatrix{{20, 25}, -3} << IntMatrix{{12, 9}, 2} << IntMatrix{{9, 18}, 2} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{20u} << matrix_size_t{9u} << true << matrix_size_t{20u} << matrix_size_t{13u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u};
    QTest::newRow("52: all different") << IntMatrix{{20, 25}, -3} << IntMatrix{} << IntMatrix{} << matrix_size_t{11u} << SplitMode::ALL_DIFFERENT << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{13u} << matrix_size_t{25u} << matrix_size_t{17u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("53: source first") << IntMatrix{{20, 25}, -3} << IntMatrix{{20, 25}, -3} << IntMatrix{{9, 18}, 2} << matrix_size_t{11u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_size_t{22u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_opt_size_t{4u};
    QTest::newRow("54: source first") << IntMatrix{{20, 25}, -3} << IntMatrix{{20, 25}, -3} << IntMatrix{} << matrix_size_t{11u} << SplitMode::SOURCE_FIRST << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_size_t{17u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("55: source second") << IntMatrix{{20, 25}, -3} << IntMatrix{{12, 9}, 2} << IntMatrix{{20, 25}, -3} << matrix_size_t{11u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{11u} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("56: source second") << IntMatrix{{20, 25}, -3} << IntMatrix{} << IntMatrix{{20, 25}, -3} << matrix_size_t{11u} << SplitMode::SOURCE_SECOND << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << false << matrix_size_t{25u} << matrix_size_t{13u} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
}

void IntMatrixCapacityTests::testReserveResizeAndEraseRowAndOrColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("erasedRowNr");
    QTest::addColumn<matrix_opt_size_t>("erasedColumnNr");
    QTest::addColumn<bool>("shouldEraseColumnBeforeRow");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{45u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("2: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{29u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("3: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{28u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{7u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("4: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{27u} << matrix_size_t{6u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{6u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("5: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{24u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{6u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("6: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{23u} << matrix_size_t{4u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{23u} << matrix_size_t{6u} << matrix_opt_size_t{9u} << matrix_opt_size_t{0u};
    QTest::newRow("7: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{20u} << matrix_size_t{3u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{20u} << matrix_size_t{6u} << matrix_opt_size_t{7u} << matrix_opt_size_t{0u};
    QTest::newRow("8: oversized row capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{18u} << matrix_size_t{2u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{18u} << matrix_size_t{6u} << matrix_opt_size_t{6u} << matrix_opt_size_t{0u};
    QTest::newRow("9: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{45u} << matrix_size_t{9u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{45u} << matrix_size_t{9u} << matrix_opt_size_t{19u} << matrix_opt_size_t{3u};
    QTest::newRow("10: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{29u} << matrix_size_t{8u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{29u} << matrix_size_t{8u} << matrix_opt_size_t{11u} << matrix_opt_size_t{2u};
    QTest::newRow("11: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{28u} << matrix_size_t{7u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{28u} << matrix_size_t{7u} << matrix_opt_size_t{10u} << matrix_opt_size_t{2u};
    QTest::newRow("12: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{27u} << matrix_size_t{6u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{27u} << matrix_size_t{6u} << matrix_opt_size_t{10u} << matrix_opt_size_t{1u};
    QTest::newRow("13: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{24u} << matrix_size_t{5u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{24u} << matrix_size_t{6u} << matrix_opt_size_t{8u} << matrix_opt_size_t{1u};
    QTest::newRow("14: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{23u} << matrix_size_t{4u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{23u} << matrix_size_t{6u} << matrix_opt_size_t{8u} << matrix_opt_size_t{1u};
    QTest::newRow("15: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{20u} << matrix_size_t{3u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{20u} << matrix_size_t{6u} << matrix_opt_size_t{6u} << matrix_opt_size_t{1u};
    QTest::newRow("16: oversized row capacity, erase column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{18u} << matrix_size_t{2u} << matrix_opt_size_t{} << matrix_opt_size_t{1u} << false << matrix_size_t{18u} << matrix_size_t{6u} << matrix_opt_size_t{5u} << matrix_opt_size_t{1u};
    QTest::newRow("17: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{45u} << matrix_size_t{41u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{41u} << matrix_opt_size_t{3u} << matrix_opt_size_t{17u};
    QTest::newRow("18: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{29u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{9u};
    QTest::newRow("19: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{28u} << matrix_size_t{24u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{9u};
    QTest::newRow("20: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{27u} << matrix_size_t{23u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{8u};
    QTest::newRow("21: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{24u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{12u} << matrix_size_t{20u} << matrix_opt_size_t{3u} << matrix_opt_size_t{7u};
    QTest::newRow("22: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{9u} << matrix_opt_size_t{7u};
    QTest::newRow("23: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{7u} << matrix_opt_size_t{5u};
    QTest::newRow("24: oversized row and column capacity, erase row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{2u} << matrix_opt_size_t{} << false << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{6u} << matrix_opt_size_t{4u};
    QTest::newRow("25: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{45u} << matrix_size_t{41u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("26: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{29u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("27: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{28u} << matrix_size_t{24u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("28: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{27u} << matrix_size_t{23u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("29: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{24u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("30: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{9u} << matrix_opt_size_t{8u};
    QTest::newRow("31: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{7u} << matrix_opt_size_t{6u};
    QTest::newRow("32: oversized row and column capacity, erase row then column") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << false << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{6u} << matrix_opt_size_t{5u};
    QTest::newRow("33: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{45u} << matrix_size_t{41u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("34: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{29u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("35: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{28u} << matrix_size_t{24u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("36: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{27u} << matrix_size_t{23u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("37: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{24u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("38: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{23u} << matrix_size_t{19u} << matrix_opt_size_t{9u} << matrix_opt_size_t{8u};
    QTest::newRow("39: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{20u} << matrix_size_t{16u} << matrix_opt_size_t{7u} << matrix_opt_size_t{6u};
    QTest::newRow("40: oversized row and column capacity, erase column then row") << IntMatrix{{6, 5}, -3} << matrix_size_t{7u} << matrix_size_t{6u} << 5 << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << true << matrix_size_t{18u} << matrix_size_t{14u} << matrix_opt_size_t{6u} << matrix_opt_size_t{5u};
    QTest::newRow("41: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{9u} << matrix_size_t{45u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{9u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("42: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{8u} << matrix_size_t{29u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{8u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("43: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{7u} << matrix_size_t{28u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{7u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("44: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{6u} << matrix_size_t{27u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{6u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("45: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{5u} << matrix_size_t{24u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{6u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("46: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{4u} << matrix_size_t{23u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{6u} << matrix_size_t{23u} << matrix_opt_size_t{0u} << matrix_opt_size_t{9u};
    QTest::newRow("47: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{3u} << matrix_size_t{20u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{6u} << matrix_size_t{20u} << matrix_opt_size_t{0u} << matrix_opt_size_t{7u};
    QTest::newRow("48: oversized column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{2u} << matrix_size_t{18u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{6u} << matrix_size_t{18u} << matrix_opt_size_t{0u} << matrix_opt_size_t{6u};
    QTest::newRow("49: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{9u} << matrix_size_t{45u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{9u} << matrix_size_t{45u} << matrix_opt_size_t{2u} << matrix_opt_size_t{19u};
    QTest::newRow("50: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{8u} << matrix_size_t{29u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{8u} << matrix_size_t{29u} << matrix_opt_size_t{2u} << matrix_opt_size_t{11u};
    QTest::newRow("51: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{7u} << matrix_size_t{28u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{7u} << matrix_size_t{28u} << matrix_opt_size_t{1u} << matrix_opt_size_t{11u};
    QTest::newRow("52: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{6u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{6u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{10u};
    QTest::newRow("53: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{5u} << matrix_size_t{24u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{6u} << matrix_size_t{24u} << matrix_opt_size_t{1u} << matrix_opt_size_t{8u};
    QTest::newRow("54: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{4u} << matrix_size_t{23u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{6u} << matrix_size_t{23u} << matrix_opt_size_t{1u} << matrix_opt_size_t{8u};
    QTest::newRow("55: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{3u} << matrix_size_t{20u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{6u} << matrix_size_t{20u} << matrix_opt_size_t{1u} << matrix_opt_size_t{6u};
    QTest::newRow("56: oversized column capacity, erase row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{2u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{} << false << matrix_size_t{6u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{5u};
    QTest::newRow("57: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{41u} << matrix_size_t{45u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{41u} << matrix_size_t{12u} << matrix_opt_size_t{17u} << matrix_opt_size_t{3u};
    QTest::newRow("58: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{25u} << matrix_size_t{29u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{25u} << matrix_size_t{12u} << matrix_opt_size_t{9u} << matrix_opt_size_t{3u};
    QTest::newRow("59: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{24u} << matrix_size_t{28u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{24u} << matrix_size_t{12u} << matrix_opt_size_t{9u} << matrix_opt_size_t{3u};
    QTest::newRow("60: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{23u} << matrix_size_t{27u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{23u} << matrix_size_t{12u} << matrix_opt_size_t{8u} << matrix_opt_size_t{3u};
    QTest::newRow("61: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{20u} << matrix_size_t{24u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{20u} << matrix_size_t{12u} << matrix_opt_size_t{7u} << matrix_opt_size_t{3u};
    QTest::newRow("62: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{6u} << matrix_opt_size_t{9u};
    QTest::newRow("63: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{8u};
    QTest::newRow("64: oversized row and column capacity, erase column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{} << matrix_opt_size_t{2u} << false << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{4u} << matrix_opt_size_t{7u};
    QTest::newRow("65: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{41u} << matrix_size_t{45u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("66: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{25u} << matrix_size_t{29u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("67: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{24u} << matrix_size_t{28u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("68: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{23u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("69: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{20u} << matrix_size_t{24u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("70: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{7u} << matrix_opt_size_t{9u};
    QTest::newRow("71: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("72: oversized row and column capacity, erase column then row") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << true << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{7u};
    QTest::newRow("73: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{41u} << matrix_size_t{45u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("74: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{25u} << matrix_size_t{29u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("75: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{24u} << matrix_size_t{28u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("76: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{23u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("77: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{20u} << matrix_size_t{24u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("78: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{19u} << matrix_size_t{23u} << matrix_opt_size_t{7u} << matrix_opt_size_t{9u};
    QTest::newRow("79: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{16u} << matrix_size_t{20u} << matrix_opt_size_t{6u} << matrix_opt_size_t{8u};
    QTest::newRow("80: oversized row and column capacity, erase row then column") << IntMatrix{{5, 6}, -3} << matrix_size_t{6u} << matrix_size_t{7u} << 5 << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u} << false << matrix_size_t{14u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{7u};
}

void IntMatrixCapacityTests::_buildMovedCopiedVectorConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<int>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::vector<int>(12, 0) << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<int>(12, 0) << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << std::vector<int>(80, 0) << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("4: large size matrix") << matrix_size_t{10u} << matrix_size_t{8u} << std::vector<int>(80, 0) << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("5: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::vector<int>(c_LargeDimension1 * c_LargeDimension1, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("6: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::vector<int>(c_LargeDimension1 * c_MaxAllowedDimension, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::vector<int>(c_MaxAllowedDimension * c_LargeDimension1, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::vector<int>(c_LargeDimension2 * c_LargeDimension2, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::vector<int>(c_LargeDimension2 * c_MaxAllowedDimension, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::vector<int>(c_MaxAllowedDimension * c_LargeDimension2, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::vector<int>(c_MaxAllowedDimension * c_MaxAllowedDimension, 0) << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::vector<int>(c_LargeDimension1 * 3, 0) << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::vector<int>(c_LargeDimension2 * 3, 0) << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::vector<int>(c_MaxAllowedDimension * 4, 0) << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::vector<int>(c_LargeDimension1 * 8, 0) << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::vector<int>(c_MaxAllowedDimension * 10, 0) << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::vector<int>(c_LargeDimension2 * 10, 0) << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::vector<int>(3 * c_LargeDimension1, 0) << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::vector<int>(3 * c_LargeDimension2, 0) << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::vector<int>(4 * c_MaxAllowedDimension, 0) << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::vector<int>(8 * c_LargeDimension1, 0) << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::vector<int>(10 * c_MaxAllowedDimension, 0) << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::vector<int>(10 * c_LargeDimension2, 0) << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<int>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << 0 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << 0 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: medium size matrix") << matrix_size_t{7u} << matrix_size_t{8u} << 0 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("4: medium size matrix") << matrix_size_t{8u} << matrix_size_t{7u} << 0 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: large size matrix") << matrix_size_t{20u} << matrix_size_t{25u} << 0 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("6: large size matrix") << matrix_size_t{25u} << matrix_size_t{20u} << 0 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("7: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("10: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << 0 << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << 0 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << 0 << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << 0 << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("24: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildAssignmentOperatorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("srcMatrixRowsCount");
    QTest::addColumn<matrix_size_t>("srcMatrixColumnsCount");
    QTest::addColumn<int>("srcMatrixElementValue");
    QTest::addColumn<matrix_size_t>("destMatrixRowsCount");
    QTest::addColumn<matrix_size_t>("destMatrixColumnsCount");
    QTest::addColumn<int>("destMatrixElementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << matrix_size_t{3u} << matrix_size_t{4u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: destination matrix initially empty") << matrix_size_t{4u} << matrix_size_t{3u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: destination matrix initially empty") << matrix_size_t{7u} << matrix_size_t{8u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("4: destination matrix initially empty") << matrix_size_t{8u} << matrix_size_t{7u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: destination matrix initially empty") << matrix_size_t{20u} << matrix_size_t{25u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("6: destination matrix initially empty") << matrix_size_t{25u} << matrix_size_t{20u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("7: destination matrix initially empty, capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("8: destination matrix initially empty, capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("9: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("10: destination matrix initially empty, capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: destination matrix initially empty, capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: destination matrix initially empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: destination matrix initially empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: destination matrix initially empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("17: destination matrix initially empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("18: destination matrix initially empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: destination matrix initially empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: destination matrix initially empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: destination matrix initially empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: destination matrix initially empty, capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: destination matrix initially empty, capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("24: destination matrix initially empty, capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: destination matrix initially empty, capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << -1 << matrix_size_t{0u} << matrix_size_t{0u} << 0 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("26: destination matrix initially NOT empty") << matrix_size_t{3u} << matrix_size_t{4u} << -1 << matrix_size_t{2u} << matrix_size_t{3u} << -5 << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("27: destination matrix initially NOT empty") << matrix_size_t{4u} << matrix_size_t{3u} << -1 << matrix_size_t{2u} << matrix_size_t{3u} << -5 << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("28: destination matrix initially NOT empty") << matrix_size_t{7u} << matrix_size_t{8u} << -1 << matrix_size_t{3u} << matrix_size_t{4u} << -5 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("29: destination matrix initially NOT empty") << matrix_size_t{8u} << matrix_size_t{7u} << -1 << matrix_size_t{3u} << matrix_size_t{4u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("30: destination matrix initially NOT empty") << matrix_size_t{20u} << matrix_size_t{25u} << -1 << matrix_size_t{15u} << matrix_size_t{20u} << -5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("31: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << -1 << matrix_size_t{15u} << matrix_size_t{20u} << -5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("32: destination matrix initially NOT empty") << matrix_size_t{20u} << matrix_size_t{25u} << -1 << matrix_size_t{25u} << matrix_size_t{20u} << -5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("33: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << -1 << matrix_size_t{20u} << matrix_size_t{25u} << -5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("34: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << -1 << matrix_size_t{25u} << matrix_size_t{20u} << -5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("35: destination matrix initially NOT empty") << matrix_size_t{15u} << matrix_size_t{20u} << -1 << matrix_size_t{20u} << matrix_size_t{25u} << -5 << matrix_size_t{18u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("36: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << -1 << c_LargeDimension2 << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("37: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << -1 << c_MaxAllowedDimension << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("38: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << -1 << matrix_size_t{8u} << matrix_size_t{10u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("39: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << -1 << c_LargeDimension1 << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << -1 << matrix_size_t{8u} << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("41: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << -1 << c_MaxAllowedDimension << matrix_size_t{10u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("42: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << -1 << c_MaxAllowedDimension << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("43: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << -1 << matrix_size_t{3u} << c_LargeDimension2 << -5 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("44: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << -1 << c_MaxAllowedDimension << matrix_size_t{3u} << -5 << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: destination matrix initially NOT empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << -1 << c_LargeDimension2 << matrix_size_t{3u} << -5 << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << -1 << c_LargeDimension2 << matrix_size_t{10u} << -5 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("47: destination matrix initially NOT empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << -1 << matrix_size_t{10u} << c_LargeDimension2 << -5 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("48: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << -1 << c_LargeDimension1 << matrix_size_t{10u} << -5 << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("49: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << -1 << c_LargeDimension2 << matrix_size_t{3u} << -5 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("50: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << -1 << matrix_size_t{3u} << c_MaxAllowedDimension << -5 << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("51: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << -1 << matrix_size_t{3u} << c_LargeDimension2 << -5 << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("52: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << -1 << matrix_size_t{10u} << c_LargeDimension2 << -5 << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << -1 << c_LargeDimension2 << matrix_size_t{10u} << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("54: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << -1 << matrix_size_t{10u} << c_LargeDimension1 << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildReserveAndResizeTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("6: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("7: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("13: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("14: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("17: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("18: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("19: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{6u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("23: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("24: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("26: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("27: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("28: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("29: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{6u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("30: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("31: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("32: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("33: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("34: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("35: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("36: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("37: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("38: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("39: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("41: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("42: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{8u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("43: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("44: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("47: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("48: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("49: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("50: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("51: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("52: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("53: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("54: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("55: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("56: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("57: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("58: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("59: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("60: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("61: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("62: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("63: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("64: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("65: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("66: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("67: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("68: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("69: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("70: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("71: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("72: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("73: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("74: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("75: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("76: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("77: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("78: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("79: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("80: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{8u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("81: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("82: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("83: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("84: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("85: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("86: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("87: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("88: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{6u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("89: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("90: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("91: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("92: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("93: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("94: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("95: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("96: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("97: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("98: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("99: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("100: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("101: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("102: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{6u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("103: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("104: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("105: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("106: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("107: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("108: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("109: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{6u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("110: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("111: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("112: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("113: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("114: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("115: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("116: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("117: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("118: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("119: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("120: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("121: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("122: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("123: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("124: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("125: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("126: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("127: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("128: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("129: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("130: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("131: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("132: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("133: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("134: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("135: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("136: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("137: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("138: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("139: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("140: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("141: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("142: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("143: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("144: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("145: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("146: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("147: same rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("148: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("149: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("150: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("151: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("152: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("153: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("154: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("155: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("156: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("157: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("158: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("159: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("160: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("161: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("162: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("163: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("164: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("165: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("166: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("167: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("168: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("169: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("170: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("171: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("172: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("173: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("174: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("175: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("176: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("177: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("178: more rows, same columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("179: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("180: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("181: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("182: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("183: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("184: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("185: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("186: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("187: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("188: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("189: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("190: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("191: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("192: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("193: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("194: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("195: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("196: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("197: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("198: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("199: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("200: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("201: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("202: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("203: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("204: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("205: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("206: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("207: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("208: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("209: same rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("210: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("211: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("212: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("213: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("214: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("215: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("216: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("217: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("218: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("219: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("220: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("221: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("222: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("223: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("224: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("225: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("226: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("227: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("228: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("229: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("230: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("231: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("232: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("233: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("234: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("235: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("236: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("237: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("238: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("239: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("240: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("241: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("242: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("243: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("244: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("245: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("246: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("247: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("248: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("249: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("250: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("251: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("252: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("253: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("254: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("255: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{6u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("256: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("257: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("258: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("259: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("260: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("261: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("262: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{6u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("263: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("264: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("265: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("266: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("267: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("268: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("269: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{6u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("270: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("271: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("272: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("273: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("274: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("275: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("276: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("277: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("278: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("279: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("280: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("281: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("282: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{8u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("283: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("284: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("285: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("286: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("287: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("288: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("289: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("290: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("291: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("292: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("293: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("294: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("295: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("296: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("297: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("298: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("299: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("300: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("301: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("302: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("303: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("304: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("305: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("306: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("307: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("308: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("309: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("310: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("311: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("312: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("313: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    // empty matrix
    QTest::newRow("314: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("315: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("316: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{0u} << matrix_size_t{2u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("317: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{0u} << matrix_size_t{3u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("318: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("319: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("320: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{1u} << matrix_size_t{2u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("321: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{1u} << matrix_size_t{3u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("322: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{2u} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("323: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{2u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("324: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{2u} << matrix_size_t{2u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("325: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{2u} << matrix_size_t{3u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("326: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{3u} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("327: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{3u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("328: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{3u} << matrix_size_t{2u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("329: more rows, more columns") << IntMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << -5 << matrix_size_t{3u} << matrix_size_t{3u} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildResizeTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<int>("resizeElementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: less rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("2: less rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("3: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("4: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{10u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << matrix_size_t{11u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("6: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << c_LargeDimension2 << -5 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: less rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{9u} << c_MaxAllowedDimension << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("8: equal rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("9: equal rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("10: equal rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("11: equal rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{10u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("12: equal rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << matrix_size_t{11u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: equal rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << c_LargeDimension2 << -5 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("14: equal rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{10u} << c_MaxAllowedDimension << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{7u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: more rows, less columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{7u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: more rows, less columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{7u} << -5 << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: more rows, less columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{7u} << -5 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: more rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: more rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{8u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("22: more rows, equal columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{8u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("23: more rows, equal columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{8u} << -5 << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("24: more rows, equal columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{8u} << -5 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("25: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("26: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{10u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("27: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << matrix_size_t{11u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("28: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << c_LargeDimension2 << -5 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("29: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{11u} << c_MaxAllowedDimension << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{9u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("31: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{10u} << -5 << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("32: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << matrix_size_t{11u} << -5 << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("33: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << c_LargeDimension2 << -5 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("34: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{12u} << c_MaxAllowedDimension << -5 << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("35: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{9u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("36: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{10u} << -5 << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("37: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << matrix_size_t{11u} << -5 << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("38: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << c_LargeDimension2 << -5 << matrix_size_t{13u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("39: more rows, more columns") << IntMatrix{{10, 8}, -2} << matrix_size_t{13u} << c_MaxAllowedDimension << -5 << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{9u} << -5 << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("41: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{10u} << -5 << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("42: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << matrix_size_t{11u} << -5 << c_LargeDimension2 << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("43: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << c_LargeDimension2 << -5 << c_LargeDimension2 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("44: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_LargeDimension2 << c_MaxAllowedDimension << -5 << c_LargeDimension2 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{9u} << -5 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{10u} << -5 << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << matrix_size_t{11u} << -5 << c_MaxAllowedDimension << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("48: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("49: more rows, more columns") << IntMatrix{{10, 8}, -2} << c_MaxAllowedDimension << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const matrix_size_t c_RowsCount{10};
    const matrix_opt_size_t c_MaxDimensionRowCapacityOffset{(c_MaxAllowedDimension - c_RowsCount) / 2};

    QTest::newRow("50: less rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{10u} << matrix_size_t{8u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("51: less rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{10u} << c_LargeDimension0 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("52: less rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension1 << matrix_size_t{8u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: less rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension0 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("54: less rows, equal columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{10u} << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("55: less rows, equal columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("56: less rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{10u} << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("57: less rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{10u} << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("58: less rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("59: less rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension1 << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("60: equal rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension2 << matrix_size_t{8u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("61: equal rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension0 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("62: equal rows, equal columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("63: equal rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension2 << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("64: equal rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_LargeDimension2 << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("65: more rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_MaxAllowedDimension << matrix_size_t{8u} << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("66: more rows, less columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension0 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("67: more rows, equal columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension1 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("68: more rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_LargeDimension2 << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("69: more rows, more columns") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << c_MaxAllowedDimension << c_MaxAllowedDimension << -5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildInsertRowTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << IntMatrix{{3, 4}, -2} << matrix_size_t{1u} << 5 << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small matrix") << IntMatrix{{6, 5}, -2} << matrix_size_t{3u} << 5 << matrix_size_t{7u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: small matrix") << IntMatrix{{8, 2}, -2} << matrix_size_t{1u} << 5 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << IntMatrix{{8, 2}, -2} << matrix_size_t{5u} << 5 << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("6: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{11u} << 5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("7: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{12u} << 5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("8: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{13u} << 5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("9: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{25u} << 5 << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("10: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension1 / 2 - 1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension1 / 2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension1 / 2 + 1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("14: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension2 / 2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
}

void IntMatrixCapacityTests::_buildInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << IntMatrix{{4, 3}, -2} << matrix_size_t{1u} << 5 << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("2: small matrix") << IntMatrix{{5, 6}, -2} << matrix_size_t{3u} << 5 << matrix_size_t{6u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: small matrix") << IntMatrix{{2, 8}, -2} << matrix_size_t{1u} << 5 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << IntMatrix{{2, 8}, -2} << matrix_size_t{5u} << 5 << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{0u} << 5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("6: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{11u} << 5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("7: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{12u} << 5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("8: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{13u} << 5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("9: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{25u} << 5 << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("10: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension1 / 2 - 1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension1 / 2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension1 / 2 + 1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("14: extra large matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -2} << matrix_size_t{c_LargeDimension1} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension2 / 2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("17: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -2} << matrix_size_t{c_LargeDimension2} << 5 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void IntMatrixCapacityTests::_buildReserveAndInsertRowTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedRowCapacity");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << IntMatrix{{5, 4}, -2} << matrix_size_t{5u} << matrix_size_t{0u} << 5 << matrix_size_t{10u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small matrix") << IntMatrix{{5, 4}, -2} << matrix_size_t{5u} << matrix_size_t{2u} << 5 << matrix_size_t{10u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("3: small matrix") << IntMatrix{{5, 4}, -2} << matrix_size_t{5u} << matrix_size_t{5u} << 5 << matrix_size_t{10u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << IntMatrix{{6, 4}, -2} << matrix_size_t{6u} << matrix_size_t{0u} << 5 << matrix_size_t{12u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("5: small matrix") << IntMatrix{{6, 4}, -2} << matrix_size_t{6u} << matrix_size_t{3u} << 5 << matrix_size_t{12u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("6: small matrix") << IntMatrix{{6, 4}, -2} << matrix_size_t{6u} << matrix_size_t{6u} << 5 << matrix_size_t{12u} << matrix_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("7: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{20u} << matrix_size_t{0u} << 5 << matrix_size_t{40u} << matrix_size_t{31u} << matrix_opt_size_t{9u} << matrix_opt_size_t{3u};
    QTest::newRow("8: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{20u} << matrix_size_t{10u} << 5 << matrix_size_t{40u} << matrix_size_t{31u} << matrix_opt_size_t{9u} << matrix_opt_size_t{3u};
    QTest::newRow("9: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{20u} << matrix_size_t{20u} << 5 << matrix_size_t{40u} << matrix_size_t{31u} << matrix_opt_size_t{9u} << matrix_opt_size_t{3u};
    QTest::newRow("10: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{21u} << matrix_size_t{0u} << 5 << matrix_size_t{21u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("11: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{21u} << matrix_size_t{10u} << 5 << matrix_size_t{21u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("12: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{21u} << matrix_size_t{20u} << 5 << matrix_size_t{21u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("13: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{22u} << matrix_size_t{0u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("14: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{22u} << matrix_size_t{9u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("15: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{22u} << matrix_size_t{10u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("16: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{22u} << matrix_size_t{11u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("17: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{22u} << matrix_size_t{20u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("18: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{23u} << matrix_size_t{0u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("19: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{23u} << matrix_size_t{9u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("20: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{23u} << matrix_size_t{10u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("21: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{23u} << matrix_size_t{11u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("22: large matrix") << IntMatrix{{20, 25}, -2} << matrix_size_t{23u} << matrix_size_t{20u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("23: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{21u} << matrix_size_t{0u} << 5 << matrix_size_t{42u} << matrix_size_t{31u} << matrix_opt_size_t{10u} << matrix_opt_size_t{3u};
    QTest::newRow("24: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{21u} << matrix_size_t{10u} << 5 << matrix_size_t{42u} << matrix_size_t{31u} << matrix_opt_size_t{10u} << matrix_opt_size_t{3u};
    QTest::newRow("25: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{21u} << matrix_size_t{21u} << 5 << matrix_size_t{42u} << matrix_size_t{31u} << matrix_opt_size_t{10u} << matrix_opt_size_t{3u};
    QTest::newRow("26: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{22u} << matrix_size_t{0u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("27: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{22u} << matrix_size_t{10u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("28: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{22u} << matrix_size_t{21u} << 5 << matrix_size_t{22u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("29: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{23u} << matrix_size_t{0u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("30: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{23u} << matrix_size_t{9u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("31: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{23u} << matrix_size_t{10u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("32: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{23u} << matrix_size_t{11u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("33: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{23u} << matrix_size_t{21u} << 5 << matrix_size_t{23u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("34: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{24u} << matrix_size_t{0u} << 5 << matrix_size_t{24u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("35: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{24u} << matrix_size_t{9u} << 5 << matrix_size_t{24u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("36: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{24u} << matrix_size_t{10u} << 5 << matrix_size_t{24u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("37: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{24u} << matrix_size_t{11u} << 5 << matrix_size_t{24u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("38: large matrix") << IntMatrix{{21, 25}, -2} << matrix_size_t{24u} << matrix_size_t{21u} << 5 << matrix_size_t{24u} << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("39a: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_LargeDimension1 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("40a: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{c_DecrHalfMaxAllowedDimension / 2} << 5 << c_LargeDimension1 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("41a: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << c_DecrHalfMaxAllowedDimension << 5 << c_LargeDimension1 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("42a: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("43a: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{c_HalfMaxAllowedDimension / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("44a: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << c_HalfMaxAllowedDimension << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("45a: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1} << matrix_opt_size_t{3u};
        QTest::newRow("46a: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{c_IncrHalfMaxAllowedDimension / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1} << matrix_opt_size_t{3u};
        QTest::newRow("47a: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << c_IncrHalfMaxAllowedDimension << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1} << matrix_opt_size_t{3u};
    }
    else
    {
        QTest::newRow("39b: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_LargeDimension0 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("40b: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{c_DecrHalfMaxAllowedDimension / 2} << 5 << c_LargeDimension0 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("41b: extra large matrix") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 25}, -2} << c_DecrHalfMaxAllowedDimension << c_DecrHalfMaxAllowedDimension << 5 << c_LargeDimension0 << matrix_size_t{31u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2} << matrix_opt_size_t{3u};
        QTest::newRow("42b: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_LargeDimension2 << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("43b: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{c_HalfMaxAllowedDimension / 2} << 5 << c_LargeDimension2 << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("44b: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, 25}, -2} << c_HalfMaxAllowedDimension << c_HalfMaxAllowedDimension << 5 << c_LargeDimension2 << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("45b: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("46b: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{c_IncrHalfMaxAllowedDimension / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
        QTest::newRow("47b: extra large matrix") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 25}, -2} << c_IncrHalfMaxAllowedDimension << c_IncrHalfMaxAllowedDimension << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{3u};
    }

    constexpr matrix_opt_size_t c_ThreeQuartersCapacityOffset{(c_MaxAllowedDimension - c_ThreeQuartersMaxAllowedDimension - 1) / 2};

    QTest::newRow("48: extra large matrix") << IntMatrix{{c_ThreeQuartersMaxAllowedDimension, 25}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << c_ThreeQuartersCapacityOffset << matrix_opt_size_t{3u};
    QTest::newRow("49: extra large matrix") << IntMatrix{{c_ThreeQuartersMaxAllowedDimension, 25}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{c_ThreeQuartersMaxAllowedDimension / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << c_ThreeQuartersCapacityOffset << matrix_opt_size_t{3u};
    QTest::newRow("50: extra large matrix") << IntMatrix{{c_ThreeQuartersMaxAllowedDimension, 25}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{c_ThreeQuartersMaxAllowedDimension} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << c_ThreeQuartersCapacityOffset << matrix_opt_size_t{3u};
    QTest::newRow("51: extra large matrix") << IntMatrix{{c_LargeDimension0, 25}, -2} << c_LargeDimension0 << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("52: extra large matrix") << IntMatrix{{c_LargeDimension0, 25}, -2} << c_LargeDimension0 << matrix_size_t{c_LargeDimension0 / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("53: extra large matrix") << IntMatrix{{c_LargeDimension0, 25}, -2} << c_LargeDimension0 << c_LargeDimension0 << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{1u} << matrix_opt_size_t{3u};
    QTest::newRow("54: extra large matrix") << IntMatrix{{c_LargeDimension1, 25}, -2} << c_LargeDimension1 << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("55: extra large matrix") << IntMatrix{{c_LargeDimension1, 25}, -2} << c_LargeDimension1 << matrix_size_t{c_LargeDimension1 / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("56: extra large matrix") << IntMatrix{{c_LargeDimension1, 25}, -2} << c_LargeDimension1 << c_LargeDimension1 << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("57: extra large matrix") << IntMatrix{{c_LargeDimension2, 25}, -2} << c_LargeDimension2 << matrix_size_t{0u} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("58: extra large matrix") << IntMatrix{{c_LargeDimension2, 25}, -2} << c_LargeDimension2 << matrix_size_t{c_LargeDimension2 / 2} << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
    QTest::newRow("59: extra large matrix") << IntMatrix{{c_LargeDimension2, 25}, -2} << c_LargeDimension2 << c_LargeDimension2 << 5 << c_MaxAllowedDimension << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u};
}

void IntMatrixCapacityTests::_buildReserveAndInsertColumnTestingTable()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("requestedColumnCapacity");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<int>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << IntMatrix{{4, 5}, -2} << matrix_size_t{5u} << matrix_size_t{0u} << 5 << matrix_size_t{5u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("2: small matrix") << IntMatrix{{4, 5}, -2} << matrix_size_t{5u} << matrix_size_t{2u} << 5 << matrix_size_t{5u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("3: small matrix") << IntMatrix{{4, 5}, -2} << matrix_size_t{5u} << matrix_size_t{5u} << 5 << matrix_size_t{5u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("4: small matrix") << IntMatrix{{4, 6}, -2} << matrix_size_t{6u} << matrix_size_t{0u} << 5 << matrix_size_t{5u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("5: small matrix") << IntMatrix{{4, 6}, -2} << matrix_size_t{6u} << matrix_size_t{3u} << 5 << matrix_size_t{5u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("6: small matrix") << IntMatrix{{4, 6}, -2} << matrix_size_t{6u} << matrix_size_t{6u} << 5 << matrix_size_t{5u} << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("7: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{20u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{40u} << matrix_opt_size_t{3u} << matrix_opt_size_t{9u};
    QTest::newRow("8: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{20u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{40u} << matrix_opt_size_t{3u} << matrix_opt_size_t{9u};
    QTest::newRow("9: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{20u} << matrix_size_t{20u} << 5 << matrix_size_t{31u} << matrix_size_t{40u} << matrix_opt_size_t{3u} << matrix_opt_size_t{9u};
    QTest::newRow("10: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{21u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{21u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("11: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{21u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{21u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("12: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{21u} << matrix_size_t{20u} << 5 << matrix_size_t{31u} << matrix_size_t{21u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("13: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{22u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("14: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{22u} << matrix_size_t{9u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("15: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{22u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("16: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{22u} << matrix_size_t{11u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("17: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{22u} << matrix_size_t{20u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("18: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{23u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("19: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{23u} << matrix_size_t{9u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("20: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{23u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("21: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{23u} << matrix_size_t{11u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("22: large matrix") << IntMatrix{{25, 20}, -2} << matrix_size_t{23u} << matrix_size_t{20u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("23: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{21u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{42u} << matrix_opt_size_t{3u} << matrix_opt_size_t{10u};
    QTest::newRow("24: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{21u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{42u} << matrix_opt_size_t{3u} << matrix_opt_size_t{10u};
    QTest::newRow("25: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{21u} << matrix_size_t{21u} << 5 << matrix_size_t{31u} << matrix_size_t{42u} << matrix_opt_size_t{3u} << matrix_opt_size_t{10u};
    QTest::newRow("26: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{22u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("27: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{22u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("28: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{22u} << matrix_size_t{21u} << 5 << matrix_size_t{31u} << matrix_size_t{22u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("29: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{23u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("30: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{23u} << matrix_size_t{9u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("31: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{23u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("32: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{23u} << matrix_size_t{11u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("33: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{23u} << matrix_size_t{21u} << 5 << matrix_size_t{31u} << matrix_size_t{23u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("34: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{24u} << matrix_size_t{0u} << 5 << matrix_size_t{31u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("35: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{24u} << matrix_size_t{9u} << 5 << matrix_size_t{31u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("36: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{24u} << matrix_size_t{10u} << 5 << matrix_size_t{31u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("37: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{24u} << matrix_size_t{11u} << 5 << matrix_size_t{31u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("38: large matrix") << IntMatrix{{25, 21}, -2} << matrix_size_t{24u} << matrix_size_t{21u} << 5 << matrix_size_t{31u} << matrix_size_t{24u} << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("39a: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_LargeDimension1 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("40a: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{c_DecrHalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_LargeDimension1 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("41a: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << c_DecrHalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_LargeDimension1 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("42a: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("43a: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{c_HalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("44a: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << c_HalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("45a: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1};
        QTest::newRow("46a: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{c_IncrHalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1};
        QTest::newRow("47a: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << c_IncrHalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2 - 1};
    }
    else
    {
        QTest::newRow("39b: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_LargeDimension0 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("40b: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << matrix_size_t{c_DecrHalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_LargeDimension0 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("41b: extra large matrix") << IntMatrix{{25, c_DecrHalfMaxAllowedDimension}, -2} << c_DecrHalfMaxAllowedDimension << c_DecrHalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_LargeDimension0 << matrix_opt_size_t{3u} << matrix_opt_size_t{(c_DecrHalfMaxAllowedDimension - 1) / 2};
        QTest::newRow("42b: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_LargeDimension2 << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("43b: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << matrix_size_t{c_HalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_LargeDimension2 << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("44b: extra large matrix") << IntMatrix{{25, c_HalfMaxAllowedDimension}, -2} << c_HalfMaxAllowedDimension << c_HalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_LargeDimension2 << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("45b: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("46b: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << matrix_size_t{c_IncrHalfMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
        QTest::newRow("47b: extra large matrix") << IntMatrix{{25, c_IncrHalfMaxAllowedDimension}, -2} << c_IncrHalfMaxAllowedDimension << c_IncrHalfMaxAllowedDimension << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension / 2};
    }

    constexpr matrix_opt_size_t c_ThreeQuartersCapacityOffset{(c_MaxAllowedDimension - c_ThreeQuartersMaxAllowedDimension - 1) / 2};

    QTest::newRow("48: extra large matrix") << IntMatrix{{25, c_ThreeQuartersMaxAllowedDimension}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << c_ThreeQuartersCapacityOffset;
    QTest::newRow("49: extra large matrix") << IntMatrix{{25, c_ThreeQuartersMaxAllowedDimension}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{c_ThreeQuartersMaxAllowedDimension / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << c_ThreeQuartersCapacityOffset;
    QTest::newRow("50: extra large matrix") << IntMatrix{{25, c_ThreeQuartersMaxAllowedDimension}, -2} << c_ThreeQuartersMaxAllowedDimension << matrix_size_t{c_ThreeQuartersMaxAllowedDimension} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << c_ThreeQuartersCapacityOffset;
    QTest::newRow("51: extra large matrix") << IntMatrix{{25, c_LargeDimension0}, -2} << c_LargeDimension0 << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("52: extra large matrix") << IntMatrix{{25, c_LargeDimension0}, -2} << c_LargeDimension0 << matrix_size_t{c_LargeDimension0 / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("53: extra large matrix") << IntMatrix{{25, c_LargeDimension0}, -2} << c_LargeDimension0 << c_LargeDimension0 << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{1u};
    QTest::newRow("54: extra large matrix") << IntMatrix{{25, c_LargeDimension1}, -2} << c_LargeDimension1 << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("55: extra large matrix") << IntMatrix{{25, c_LargeDimension1}, -2} << c_LargeDimension1 << matrix_size_t{c_LargeDimension1 / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("56: extra large matrix") << IntMatrix{{25, c_LargeDimension1}, -2} << c_LargeDimension1 << c_LargeDimension1 << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("57: extra large matrix") << IntMatrix{{25, c_LargeDimension2}, -2} << c_LargeDimension2 << matrix_size_t{0u} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("58: extra large matrix") << IntMatrix{{25, c_LargeDimension2}, -2} << c_LargeDimension2 << matrix_size_t{c_LargeDimension2 / 2} << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("59: extra large matrix") << IntMatrix{{25, c_LargeDimension2}, -2} << c_LargeDimension2 << c_LargeDimension2 << 5 << matrix_size_t{31u} << c_MaxAllowedDimension << matrix_opt_size_t{3u} << matrix_opt_size_t{0u};
}

QTEST_APPLESS_MAIN(IntMatrixCapacityTests)

#include "tst_intmatrixcapacitytests.moc"
