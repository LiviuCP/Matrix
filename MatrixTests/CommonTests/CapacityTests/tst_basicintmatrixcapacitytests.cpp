#include <QTest>

#include "testutils.h"
#include "tst_basiccapacitytests.h"

Q_DECLARE_METATYPE(IntMatrix)
Q_DECLARE_METATYPE(size_tuple_t) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(size_tuple_array_t) // same here
Q_DECLARE_METATYPE(ConcatMode)

class BasicIntMatrixCapacityTests : public QObject
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
    void testInsertRowAndDefaultNewValues();
    void testInsertRowAndSetNewValues();
    void testInsertColumnAndDefaultNewValues();
    void testInsertColumnAndSetNewValues();
    void testEraseRow();
    void testEraseColumn();
    void testCatByRow();
    void testCatByColumn();
    void testSplitByRow();
    void testSplitByColumn();

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
    void testInsertRowAndDefaultNewValues_data();
    void testInsertRowAndSetNewValues_data();
    void testInsertColumnAndDefaultNewValues_data();
    void testInsertColumnAndSetNewValues_data();
    void testEraseRow_data();
    void testEraseColumn_data();
    void testCatByRow_data();
    void testCatByColumn_data();
    void testSplitByRow_data();
    void testSplitByColumn_data();

private:
    // test data helper methods
    void _buildMovedCopiedVectorConstructorsTestingTable();
    void _buildMoveCopyConstructorsTestingTable();
    void _buildAssignmentOperatorsTestingTable();
    void _buildResizeTestingTable();
    void _buildInsertRowTestingTable();
    void _buildInsertColumnTestingTable();

    IntMatrix mPrimaryIntMatrix;
};

void BasicIntMatrixCapacityTests::testCopiedVectorConstructor()
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

void BasicIntMatrixCapacityTests::testMovedVectorConstructor()
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

void BasicIntMatrixCapacityTests::testIdenticalElementsConstructor()
{
    TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(int);
}

void BasicIntMatrixCapacityTests::testDiagonalMatrixConstructor()
{
    TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(int);
}

void BasicIntMatrixCapacityTests::testCopyConstructor()
{
    TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(int);
}

void BasicIntMatrixCapacityTests::testMoveConstructor()
{
    TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(int);
}

void BasicIntMatrixCapacityTests::testCopyAssignmentOperator()
{
    TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(int);
}

void BasicIntMatrixCapacityTests::testMoveAssignmentOperator()
{
    TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(int);
}

void BasicIntMatrixCapacityTests::testTranspose()
{
    TEST_CAPACITY_WITH_TRANSPOSE(int);
}

void BasicIntMatrixCapacityTests::testReserve()
{
    TEST_CAPACITY_WITH_RESERVE(int, mPrimaryIntMatrix);
}

void BasicIntMatrixCapacityTests::testResizeAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_DEFAULT_NEW_VALUES(int, mPrimaryIntMatrix);
}

void BasicIntMatrixCapacityTests::testResizeAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(int, mPrimaryIntMatrix);
}

void BasicIntMatrixCapacityTests::testInsertRowAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_DEFAULT_NEW_VALUES(int);
}

void BasicIntMatrixCapacityTests::testInsertRowAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_FILL_IN_NEW_VALUES(int);
}

void BasicIntMatrixCapacityTests::testInsertColumnAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(int);
}

void BasicIntMatrixCapacityTests::testInsertColumnAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(int);
}

void BasicIntMatrixCapacityTests::testEraseRow()
{
    TEST_CAPACITY_WITH_ERASE_ROW(int);
}

void BasicIntMatrixCapacityTests::testEraseColumn()
{
    TEST_CAPACITY_WITH_ERASE_COLUMN(int);
}

void BasicIntMatrixCapacityTests::testCatByRow()
{
    TEST_CAPACITY_WITH_CAT_BY_ROW(int);
}

void BasicIntMatrixCapacityTests::testCatByColumn()
{
    TEST_CAPACITY_WITH_CAT_BY_COLUMN(int);
}

void BasicIntMatrixCapacityTests::testSplitByRow()
{
    TEST_CAPACITY_WITH_SPLIT_BY_ROW(int);
}

void BasicIntMatrixCapacityTests::testSplitByColumn()
{
    TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(int);
}

void BasicIntMatrixCapacityTests::testCopiedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void BasicIntMatrixCapacityTests::testMovedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void BasicIntMatrixCapacityTests::testIdenticalElementsConstructor_data()
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

void BasicIntMatrixCapacityTests::testDiagonalMatrixConstructor_data()
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

void BasicIntMatrixCapacityTests::testCopyConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void BasicIntMatrixCapacityTests::testMoveConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void BasicIntMatrixCapacityTests::testCopyAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void BasicIntMatrixCapacityTests::testMoveAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void BasicIntMatrixCapacityTests::testTranspose_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << IntMatrix{{3, 3}, 2} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small matrix") << IntMatrix{{3, 4}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("3: small matrix") << IntMatrix{{4, 3}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << IntMatrix{{4, 4}, 2} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: medium matrix") << IntMatrix{{7, 8}, 2} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("6: medium matrix") << IntMatrix{{8, 7}, 2} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: large matrix") << IntMatrix{{20, 25}, 2} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{5u};
    QTest::newRow("8: large matrix") << IntMatrix{{25, 20}, 2} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{5u} << matrix_opt_size_t{0u};
    QTest::newRow("9: large matrix") << IntMatrix{{25, 25}, 2} << matrix_size_t{31u} << matrix_size_t{31u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u};
    QTest::newRow("10: large matrix") << IntMatrix{{20, 26}, 2} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{3u} << matrix_opt_size_t{6u};
    QTest::newRow("11: large matrix") << IntMatrix{{26, 20}, 2} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{6u} << matrix_opt_size_t{3u};
    QTest::newRow("12: extra large matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension1}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("13: extra large matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("14: extra large matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: extra large matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const matrix_size_t c_CustomCapacityOffset1{static_cast<matrix_size_t>((c_MaxAllowedDimension - c_SevenEighthsMaxAllowedDimension) / 2)};
    const matrix_size_t c_CustomCapacityOffset2{static_cast<matrix_size_t>((c_FiveEighthsMaxAllowedDimension - c_HalfMaxAllowedDimension) / 2)};
    const matrix_size_t c_CustomCapacityOffset3{static_cast<matrix_size_t>((c_MaxAllowedDimension - c_HalfMaxAllowedDimension) / 2)};

    QTest::newRow("16: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, c_HalfMaxAllowedDimension}, 2} << c_FiveEighthsMaxAllowedDimension << c_FiveEighthsMaxAllowedDimension << matrix_opt_size_t{c_CustomCapacityOffset2} << matrix_opt_size_t{c_CustomCapacityOffset2};
    QTest::newRow("17: extra large matrix") << IntMatrix{{c_HalfMaxAllowedDimension, c_SevenEighthsMaxAllowedDimension}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_CustomCapacityOffset1} << matrix_opt_size_t{c_CustomCapacityOffset3};
    QTest::newRow("18: extra large matrix") << IntMatrix{{c_SevenEighthsMaxAllowedDimension, c_HalfMaxAllowedDimension}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_CustomCapacityOffset3} << matrix_opt_size_t{c_CustomCapacityOffset1};
    QTest::newRow("19: extra large matrix") << IntMatrix{{c_SevenEighthsMaxAllowedDimension, c_SevenEighthsMaxAllowedDimension}, 2} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_CustomCapacityOffset1} << matrix_opt_size_t{c_CustomCapacityOffset1};
}

void BasicIntMatrixCapacityTests::testReserve_data()
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

void BasicIntMatrixCapacityTests::testResizeAndDefaultNewValues_data()
{
    _buildResizeTestingTable();
}

void BasicIntMatrixCapacityTests::testResizeAndSetNewValues_data()
{
    _buildResizeTestingTable();
}

void BasicIntMatrixCapacityTests::testInsertRowAndDefaultNewValues_data()
{
    _buildInsertRowTestingTable();
}

void BasicIntMatrixCapacityTests::testInsertRowAndSetNewValues_data()
{
    _buildInsertRowTestingTable();
}

void BasicIntMatrixCapacityTests::testInsertColumnAndDefaultNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void BasicIntMatrixCapacityTests::testInsertColumnAndSetNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void BasicIntMatrixCapacityTests::testEraseRow_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << IntMatrix{{3, 4}, -2} << size_tuple_array_t{{1u, 3u, 5u, {0u}, {0u}}, {1u, 3u, 5u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("2: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{1u, 12u, 18u, {2u}, {1u}}, {1u, 12u, 18u, {3u}, {1u}}, {1u, 12u, 18u, {4u}, {1u}}, {1u, 12u, 18u, {5u}, {1u}}, {1u, 12u, 18u, {6u}, {1u}}, {1u, 12u, 18u, {7u}, {1u}}, {1u, 6u, 18u, {1u}, {1u}}, {1u, 6u, 18u, {1u}, {1u}}, {1u, 2u, 18u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("3: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{8u, 12u, 18u, {1u}, {1u}}, {7u, 12u, 18u, {1u}, {1u}}, {6u, 12u, 18u, {1u}, {1u}}, {5u, 12u, 18u, {1u}, {1u}}, {4u, 12u, 18u, {1u}, {1u}}, {3u, 12u, 18u, {1u}, {1u}}, {2u, 6u, 18u, {1u}, {1u}}, {1u, 6u, 18u, {1u}, {1u}}, {0u, 2u, 18u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("4: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{0u, 12u, 18u, {2u}, {1u}}, {8u, 12u, 18u, {2u}, {1u}}, {0u, 12u, 18u, {3u}, {1u}}, {6u, 12u, 18u, {3u}, {1u}}, {0u, 12u, 18u, {4u}, {1u}}, {4u, 12u, 18u, {4u}, {1u}}, {0u, 6u, 18u, {1u}, {1u}}, {2u, 6u, 18u, {1u}, {1u}}, {0u, 2u, 18u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("5: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{9u, 12u, 18u, {1u}, {1u}}, {0u, 12u, 18u, {2u}, {1u}}, {7u, 12u, 18u, {2u}, {1u}}, {0u, 12u, 18u, {3u}, {1u}}, {5u, 12u, 18u, {3u}, {1u}}, {0u, 12u, 18u, {4u}, {1u}}, {3u, 6u, 18u, {1u}, {1u}}, {0u, 6u, 18u, {2u}, {1u}}, {1u, 2u, 18u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("6: less rows than columns") << IntMatrix{{10, 15}, -2} << size_tuple_array_t{{3u, 12u, 18u, {2u}, {1u}}, {6u, 12u, 18u, {2u}, {1u}}, {7u, 12u, 18u, {2u}, {1u}}, {2u, 12u, 18u, {3u}, {1u}}, {1u, 12u, 18u, {4u}, {1u}}, {2u, 12u, 18u, {4u}, {1u}}, {0u, 6u, 18u, {1u}, {1u}}, {1u, 6u, 18u, {1u}, {1u}}, {1u, 2u, 18u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("7: square matrix") << IntMatrix{{4, 4}, -2} << size_tuple_array_t{{1u, 5u, 5u, {1u}, {0u}}, {1u, 5u, 5u, {1u}, {0u}}, {1u, 2u, 5u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("8: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{1u, 12u, 12u, {2u}, {1u}}, {1u, 12u, 12u, {3u}, {1u}}, {1u, 12u, 12u, {4u}, {1u}}, {1u, 12u, 12u, {5u}, {1u}}, {1u, 12u, 12u, {6u}, {1u}}, {1u, 12u, 12u, {7u}, {1u}}, {1u, 6u, 12u, {1u}, {1u}}, {1u, 6u, 12u, {1u}, {1u}}, {1u, 2u, 12u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("9: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{8u, 12u, 12u, {1u}, {1u}}, {7u, 12u, 12u, {1u}, {1u}}, {6u, 12u, 12u, {1u}, {1u}}, {5u, 12u, 12u, {1u}, {1u}}, {4u, 12u, 12u, {1u}, {1u}}, {3u, 12u, 12u, {1u}, {1u}}, {2u, 6u, 12u, {1u}, {1u}}, {1u, 6u, 12u, {1u}, {1u}}, {0u, 2u, 12u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("10: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{0u, 12u, 12u, {2u}, {1u}}, {8u, 12u, 12u, {2u}, {1u}}, {0u, 12u, 12u, {3u}, {1u}}, {6u, 12u, 12u, {3u}, {1u}}, {0u, 12u, 12u, {4u}, {1u}}, {4u, 12u, 12u, {4u}, {1u}}, {0u, 6u, 12u, {1u}, {1u}}, {2u, 6u, 12u, {1u}, {1u}}, {0u, 2u, 12u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("11: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{9u, 12u, 12u, {1u}, {1u}}, {0u, 12u, 12u, {2u}, {1u}}, {7u, 12u, 12u, {2u}, {1u}}, {0u, 12u, 12u, {3u}, {1u}}, {5u, 12u, 12u, {3u}, {1u}}, {0u, 12u, 12u, {4u}, {1u}}, {3u, 6u, 12u, {1u}, {1u}}, {0u, 6u, 12u, {2u}, {1u}}, {1u, 2u, 12u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("12: square matrix") << IntMatrix{{10, 10}, -2} << size_tuple_array_t{{3u, 12u, 12u, {2u}, {1u}}, {6u, 12u, 12u, {2u}, {1u}}, {7u, 12u, 12u, {2u}, {1u}}, {2u, 12u, 12u, {3u}, {1u}}, {1u, 12u, 12u, {4u}, {1u}}, {2u, 12u, 12u, {4u}, {1u}}, {0u, 6u, 12u, {1u}, {1u}}, {1u, 6u, 12u, {1u}, {1u}}, {1u, 2u, 12u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("13: more rows than columns") << IntMatrix{{7, 5}, -2} << size_tuple_array_t{{1u, 8u, 6u, {1u}, {0u}}, {1u, 8u, 6u, {2u}, {0u}}, {1u, 8u, 6u, {3u}, {0u}}, {1u, 8u, 6u, {4u}, {0u}}, {1u, 4u, 6u, {1u}, {0u}}, {1u, 2u, 6u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("14: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{1u, 12u, 11u, {2u}, {1u}}, {1u, 12u, 11u, {3u}, {1u}}, {1u, 12u, 11u, {4u}, {1u}}, {1u, 12u, 11u, {5u}, {1u}}, {1u, 12u, 11u, {6u}, {1u}}, {1u, 12u, 11u, {7u}, {1u}}, {1u, 6u, 11u, {1u}, {1u}}, {1u, 6u, 11u, {1u}, {1u}}, {1u, 2u, 11u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("15: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{8u, 12u, 11u, {1u}, {1u}}, {7u, 12u, 11u, {1u}, {1u}}, {6u, 12u, 11u, {1u}, {1u}}, {5u, 12u, 11u, {1u}, {1u}}, {4u, 12u, 11u, {1u}, {1u}}, {3u, 12u, 11u, {1u}, {1u}}, {2u, 6u, 11u, {1u}, {1u}}, {1u, 6u, 11u, {1u}, {1u}}, {0u, 2u, 11u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("16: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{0u, 12u, 11u, {2u}, {1u}}, {8u, 12u, 11u, {2u}, {1u}}, {0u, 12u, 11u, {3u}, {1u}}, {6u, 12u, 11u, {3u}, {1u}}, {0u, 12u, 11u, {4u}, {1u}}, {4u, 12u, 11u, {4u}, {1u}}, {0u, 6u, 11u, {1u}, {1u}}, {2u, 6u, 11u, {1u}, {1u}}, {0u, 2u, 11u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("17: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{9u, 12u, 11u, {1u}, {1u}}, {0u, 12u, 11u, {2u}, {1u}}, {7u, 12u, 11u, {2u}, {1u}}, {0u, 12u, 11u, {3u}, {1u}}, {5u, 12u, 11u, {3u}, {1u}}, {0u, 12u, 11u, {4u}, {1u}}, {3u, 6u, 11u, {1u}, {1u}}, {0u, 6u, 11u, {2u}, {1u}}, {1u, 2u, 11u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("18: more rows than columns") << IntMatrix{{10, 9}, -2} << size_tuple_array_t{{3u, 12u, 11u, {2u}, {1u}}, {6u, 12u, 11u, {2u}, {1u}}, {7u, 12u, 11u, {2u}, {1u}}, {2u, 12u, 11u, {3u}, {1u}}, {1u, 12u, 11u, {4u}, {1u}}, {2u, 12u, 11u, {4u}, {1u}}, {0u, 6u, 11u, {1u}, {1u}}, {1u, 6u, 11u, {1u}, {1u}}, {1u, 2u, 11u, {0u}, {1u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("19: max allowed dimension, less rows than columns") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
    QTest::newRow("20: max allowed dimension, less rows than columns") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{static_cast<matrix_size_t>(c_DecrHalfMaxAllowedDimension - 1), c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
    QTest::newRow("21: max allowed dimension, less rows than columns") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("22: max allowed dimension, less rows than columns") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("23: max allowed dimension, less rows than columns") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("24: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
    QTest::newRow("25: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
    QTest::newRow("26: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("27: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("28: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
    QTest::newRow("29: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}};
    QTest::newRow("30: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("31: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("32: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("33: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("34: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("35a: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
        QTest::newRow("36a: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}};
        QTest::newRow("37a: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
        QTest::newRow("38a: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
        QTest::newRow("39a: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    }
    else
    {
        QTest::newRow("35b: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {0u}}};
        QTest::newRow("36b: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
        QTest::newRow("37b: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {1u}}};
        QTest::newRow("38b: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
        QTest::newRow("39b: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
    }

    QTest::newRow("40: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
    QTest::newRow("41: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("42: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("43: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("44: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {2u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {3u}, {1u}}};
    QTest::newRow("45: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("46: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("47: max allowed dimension, more rows than columns") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
}

void BasicIntMatrixCapacityTests::testEraseColumn_data()
{
    QTest::addColumn<IntMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << IntMatrix{{4, 3}, 4} << size_tuple_array_t{{1u, 5u, 3u, {0u}, {0u}}, {1u, 5u, 3u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("2: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{1u, 18u, 12u, {1u}, {2u}}, {1u, 18u, 12u, {1u}, {3u}}, {1u, 18u, 12u, {1u}, {4u}}, {1u, 18u, 12u, {1u}, {5u}}, {1u, 18u, 12u, {1u}, {6u}}, {1u, 18u, 12u, {1u}, {7u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("3: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{8u, 18u, 12u, {1u}, {1u}}, {7u, 18u, 12u, {1u}, {1u}}, {6u, 18u, 12u, {1u}, {1u}}, {5u, 18u, 12u, {1u}, {1u}}, {4u, 18u, 12u, {1u}, {1u}}, {3u, 18u, 12u, {1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("4: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{0u, 18u, 12u, {1u}, {2u}}, {8u, 18u, 12u, {1u}, {2u}}, {0u, 18u, 12u, {1u}, {3u}}, {6u, 18u, 12u, {1u}, {3u}}, {0u, 18u, 12u, {1u}, {4u}}, {4u, 18u, 12u, {1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {2, 18, 6, {1u}, {1u}}, {0, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("5: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{9u, 18u, 12u, {1u}, {1u}}, {0u, 18u, 12u, {1u}, {2u}}, {7u, 18u, 12u, {1u}, {2u}}, {0u, 18u, 12u, {1u}, {3u}}, {5u, 18u, 12u, {1u}, {3u}}, {0u, 18u, 12u, {1u}, {4u}}, {3, 18, 6, {1u}, {1u}}, {0, 18, 6, {1u}, {2u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("6: less columns than rows") << IntMatrix{{15, 10}, 4} << size_tuple_array_t{{3u, 18u, 12u, {1u}, {2u}}, {6u, 18u, 12u, {1u}, {2u}}, {7u, 18u, 12u, {1u}, {2u}}, {2u, 18u, 12u, {1u}, {3u}}, {1u, 18u, 12u, {1u}, {4u}}, {2u, 18u, 12u, {1u}, {4u}}, {0, 18, 6, {1u}, {1u}}, {1, 18, 6, {1u}, {1u}}, {1, 18, 2, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("7: square matrix") << IntMatrix{{4, 4}, 4} << size_tuple_array_t{{1u, 5u, 5u, {0u}, {1u}}, {1u, 5u, 5u, {0u}, {1u}}, {1u, 5u, 2u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("8: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{1u, 12u, 12u, {1u}, {2u}}, {1u, 12u, 12u, {1u}, {3u}}, {1u, 12u, 12u, {1u}, {4u}}, {1u, 12u, 12u, {1u}, {5u}}, {1u, 12u, 12u, {1u}, {6u}}, {1u, 12u, 12u, {1u}, {7u}}, {1u, 12u, 6u, {1u}, {1u}}, {1u, 12u, 6u, {1u}, {1u}}, {1u, 12u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("9: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{8u, 12u, 12u, {1u}, {1u}}, {7u, 12u, 12u, {1u}, {1u}}, {6u, 12u, 12u, {1u}, {1u}}, {5u, 12u, 12u, {1u}, {1u}}, {4u, 12u, 12u, {1u}, {1u}}, {3u, 12u, 12u, {1u}, {1u}}, {2u, 12u, 6u, {1u}, {1u}}, {1u, 12u, 6u, {1u}, {1u}}, {0u, 12u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("10: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{0u, 12u, 12u, {1u}, {2u}}, {8u, 12u, 12u, {1u}, {2u}}, {0u, 12u, 12u, {1u}, {3u}}, {6u, 12u, 12u, {1u}, {3u}}, {0u, 12u, 12u, {1u}, {4u}}, {4u, 12u, 12u, {1u}, {4u}}, {0u, 12u, 6u, {1u}, {1u}}, {2u, 12u, 6u, {1u}, {1u}}, {0u, 12u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("11: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{9u, 12u, 12u, {1u}, {1u}}, {0u, 12u, 12u, {1u}, {2u}}, {7u, 12u, 12u, {1u}, {2u}}, {0u, 12u, 12u, {1u}, {3u}}, {5u, 12u, 12u, {1u}, {3u}}, {0u, 12u, 12u, {1u}, {4u}}, {3u, 12u, 6u, {1u}, {1u}}, {0u, 12u, 6u, {1u}, {2u}}, {1u, 12u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("12: square matrix") << IntMatrix{{10, 10}, 4} << size_tuple_array_t{{3u, 12u, 12u, {1u}, {2u}}, {6u, 12u, 12u, {1u}, {2u}}, {7u, 12u, 12u, {1u}, {2u}}, {2u, 12u, 12u, {1u}, {3u}}, {1u, 12u, 12u, {1u}, {4u}}, {2u, 12u, 12u, {1u}, {4u}}, {0u, 12u, 6u, {1u}, {1u}}, {1u, 12u, 6u, {1u}, {1u}}, {1u, 12u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("13: more columns than rows") << IntMatrix{{5, 7}, 4} <<  size_tuple_array_t{{1u, 6u, 8u, {0u}, {1u}}, {1u, 6u, 8u, {0u}, {2u}}, {1u, 6u, 8u, {0u}, {3u}}, {1u, 6u, 8u, {0u}, {4u}}, {1u, 6u, 4u, {0u}, {1u}}, {1u, 6u, 2u, {0u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("14: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{1u, 11u, 12u, {1u}, {2u}}, {1u, 11u, 12u, {1u}, {3u}}, {1u, 11u, 12u, {1u}, {4u}}, {1u, 11u, 12u, {1u}, {5u}}, {1u, 11u, 12u, {1u}, {6u}}, {1u, 11u, 12u, {1u}, {7u}}, {1u, 11u, 6u, {1u}, {1u}}, {1u, 11u, 6u, {1u}, {1u}}, {1u, 11u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("15: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{8u, 11u, 12u, {1u}, {1u}}, {7u, 11u, 12u, {1u}, {1u}}, {6u, 11u, 12u, {1u}, {1u}}, {5u, 11u, 12u, {1u}, {1u}}, {4u, 11u, 12u, {1u}, {1u}}, {3u, 11u, 12u, {1u}, {1u}}, {2u, 11u, 6u, {1u}, {1u}}, {1u, 11u, 6u, {1u}, {1u}}, {0u, 11u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("16: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{0u, 11u, 12u, {1u}, {2u}}, {8u, 11u, 12u, {1u}, {2u}}, {0u, 11u, 12u, {1u}, {3u}}, {6u, 11u, 12u, {1u}, {3u}}, {0u, 11u, 12u, {1u}, {4u}}, {4u, 11u, 12u, {1u}, {4u}}, {0u, 11u, 6u, {1u}, {1u}}, {2u, 11u, 6u, {1u}, {1u}}, {0u, 11u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("17: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{9u, 11u, 12u, {1u}, {1u}}, {0u, 11u, 12u, {1u}, {2u}}, {7u, 11u, 12u, {1u}, {2u}}, {0u, 11u, 12u, {1u}, {3u}}, {5u, 11u, 12u, {1u}, {3u}}, {0u, 11u, 12u, {1u}, {4u}}, {3u, 11u, 6u, {1u}, {1u}}, {0u, 11u, 6u, {1u}, {2u}}, {1u, 11u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("18: more columns than rows") << IntMatrix{{9, 10}, 4} << size_tuple_array_t{{3u, 11u, 12u, {1u}, {2u}}, {6u, 11u, 12u, {1u}, {2u}}, {7u, 11u, 12u, {1u}, {2u}}, {2u, 11u, 12u, {1u}, {3u}}, {1u, 11u, 12u, {1u}, {4u}}, {2u, 11u, 12u, {1u}, {4u}}, {0u, 11u, 6u, {1u}, {1u}}, {1u, 11u, 6u, {1u}, {1u}}, {1u, 11u, 2u, {1u}, {0u}}, {0u, 0u, 0u, {}, {}}};
    QTest::newRow("19: max allowed dimension, less columns than rows") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
    QTest::newRow("20: max allowed dimension, less columns than rows") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{static_cast<matrix_size_t>(c_DecrHalfMaxAllowedDimension - 1), c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
    QTest::newRow("21: max allowed dimension, less columns than rows") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("22: max allowed dimension, less columns than rows") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("23: max allowed dimension, less columns than rows") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -2} << size_tuple_array_t{{c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("24: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
    QTest::newRow("25: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
    QTest::newRow("26: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("27: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("28: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
    QTest::newRow("29: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}};
    QTest::newRow("30: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("31: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("32: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("33: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
    QTest::newRow("34: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("35a: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
        QTest::newRow("36a: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}};
        QTest::newRow("37a: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
        QTest::newRow("38a: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
        QTest::newRow("39a: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    }
    else
    {
        QTest::newRow("35b: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {2u}}};
        QTest::newRow("36b: max allowed dimension, square matrix") << IntMatrix{{c_MaxAllowedDimension, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {0u}, {1u}}};
        QTest::newRow("37b: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {2u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {2u}}};
        QTest::newRow("38b: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
        QTest::newRow("39b: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
    }

    QTest::newRow("40: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}};
    QTest::newRow("41: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("42: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("43: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_DecrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("44: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {1u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {2u}}, {0u, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {3u}}};
    QTest::newRow("45: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_HalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("46: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_IncrHalfMaxAllowedDimension, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
    QTest::newRow("47: max allowed dimension, more columns than rows") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -2} << size_tuple_array_t{{c_LargeDimension2, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension1, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}, {c_LargeDimension0, c_MaxAllowedDimension, c_MaxAllowedDimension, {1u}, {0u}}};
}

void BasicIntMatrixCapacityTests::testCatByRow_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << IntMatrix{{4, 7}, 5} << IntMatrix{{5, 7}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << IntMatrix{{5, 7}, -2} << IntMatrix{{4, 7}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{10, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("4: different matrixes") << IntMatrix{{10, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("5: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{1, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("6: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{2, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("7: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{3, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("8: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{4, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("9: different matrixes") << IntMatrix{{16, 22}, 5} << IntMatrix{{5, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("10: different matrixes") << IntMatrix{{1, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{17u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("11: different matrixes") << IntMatrix{{2, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{18u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("12: different matrixes") << IntMatrix{{3, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{19u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("13: different matrixes") << IntMatrix{{4, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("14: different matrixes") << IntMatrix{{5, 22}, -2} << IntMatrix{{16, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("15: different matrixes") << IntMatrix{{c_LargeDimension2, 22}, 5} << IntMatrix{{1, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("16: different matrixes") << IntMatrix{{c_LargeDimension1, 22}, 5} << IntMatrix{{2, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("17: different matrixes") << IntMatrix{{1, 22}, -2} << IntMatrix{{c_LargeDimension2, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("18: different matrixes") << IntMatrix{{2, 22}, -2} << IntMatrix{{c_LargeDimension1, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("19_1a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_2a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_3a: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_4a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_5a: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_6a: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }
    else
    {
        QTest::newRow("19_1b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension0 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_2b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_3b: different matrixes") << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_4b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_5b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_6b: different matrixes") << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_7b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_DecrHalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_8b: different matrixes") << IntMatrix{{c_IncrHalfMaxAllowedDimension, 22}, -2} << IntMatrix{{c_HalfMaxAllowedDimension, 22}, 5} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }

    QTest::newRow("20: same matrix") << IntMatrix{{4, 7}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: same matrix") << IntMatrix{{16, 22}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
}

void BasicIntMatrixCapacityTests::testCatByColumn_data()
{
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << IntMatrix{{7, 4}, 5} << IntMatrix{{7, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << IntMatrix{{7, 5}, -2} << IntMatrix{{7, 4}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 10}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("4: different matrixes") << IntMatrix{{22, 10}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("5: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 1}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("6: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 2}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("7: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 3}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("8: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 4}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("9: different matrixes") << IntMatrix{{22, 16}, 5} << IntMatrix{{22, 5}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("10: different matrixes") << IntMatrix{{22, 1}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{17u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("11: different matrixes") << IntMatrix{{22, 2}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("12: different matrixes") << IntMatrix{{22, 3}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("13: different matrixes") << IntMatrix{{22, 4}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("14: different matrixes") << IntMatrix{{22, 5}, -2} << IntMatrix{{22, 16}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("15: different matrixes") << IntMatrix{{22, c_LargeDimension2}, 5} << IntMatrix{{22, 1}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("16: different matrixes") << IntMatrix{{22, c_LargeDimension1}, 5} << IntMatrix{{22, 2}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("17: different matrixes") << IntMatrix{{22, 1}, -2} << IntMatrix{{22, c_LargeDimension2}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("18: different matrixes") << IntMatrix{{22, 2}, -2} << IntMatrix{{22, c_LargeDimension1}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("19_1a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_2a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_3a: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_4a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_5a: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_6a: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("19_1b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension0 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_2b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_3b: different matrixes") << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_4b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_5b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_HalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_6b: different matrixes") << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_7b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_DecrHalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_8b: different matrixes") << IntMatrix{{22, c_IncrHalfMaxAllowedDimension}, -2} << IntMatrix{{22, c_HalfMaxAllowedDimension}, 5} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }

    QTest::newRow("20: same matrix") << IntMatrix{{7, 4}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: same matrix") << IntMatrix{{22, 16}, 5} << IntMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
}

void BasicIntMatrixCapacityTests::testSplitByRow_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<matrix_size_t>("expectedSrcRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSrcColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestColumnCapacityOffset");

    QTest::newRow("1: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 8}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 13}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 14}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 15}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{5, 16}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("7: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 13}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 14}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 15}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{6, 16}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("11: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 13}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 14}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 15}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{7, 16}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 13}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 14}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("17: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 15}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("18: NO capacity reserve for destination matrix") << IntMatrix{{15, 17}, -3} << IntMatrix{{8, 16}, 2} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("19: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_HalfMaxAllowedDimension}, 2} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{3, c_HalfMaxAllowedDimension}, 2} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("22: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{1, c_MaxAllowedDimension}, 2} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("24: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{3, c_MaxAllowedDimension}, 2} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("25a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_HalfMaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_LargeDimension1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("28a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_MaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("29a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("30a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_HalfMaxAllowedDimension}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("31a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("32a: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_MaxAllowedDimension}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("33a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension0, c_HalfMaxAllowedDimension}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{0u};
        QTest::newRow("35a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension0, c_LargeDimension1}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("36a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("37a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("25b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_HalfMaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_LargeDimension1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("28b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{1, c_MaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("29b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("30b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_HalfMaxAllowedDimension}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("31b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("32b: NO capacity reserve for destination matrix") << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension2, c_MaxAllowedDimension}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("33b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension0, c_HalfMaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{0u};
        QTest::newRow("35b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension0, c_LargeDimension1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("36b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{{c_LargeDimension0, c_MaxAllowedDimension}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("37b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension2, c_LargeDimension1}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    }
}

void BasicIntMatrixCapacityTests::testSplitByColumn_data()
{
    QTest::addColumn<IntMatrix>("srcMatrix");
    QTest::addColumn<IntMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<matrix_size_t>("expectedSrcRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSrcColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestColumnCapacityOffset");

    QTest::newRow("1: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{8, 5}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{13, 5}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{14, 5}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 5}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{16, 5}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{13, 6}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{14, 6}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 6}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{16, 6}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("11: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{13, 7}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{14, 7}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 7}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{16, 7}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{13, 8}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{14, 8}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{15, 8}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: NO capacity reserve for destination matrix") << IntMatrix{{17, 15}, -3} << IntMatrix{{16, 8}, 2} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("19: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 1}, 2} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 3}, 2} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("22: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_MaxAllowedDimension, 1}, 2} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("24: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_MaxAllowedDimension, 3}, 2} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("25a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_LargeDimension1, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
        QTest::newRow("28a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_MaxAllowedDimension, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("25b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_LargeDimension1, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
        QTest::newRow("28b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_MaxAllowedDimension, 1}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    }

    QTest::newRow("29: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension2}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("31: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("32: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, -3} << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension2}, 2} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("33a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension0}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
        QTest::newRow("35a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_LargeDimension1, c_LargeDimension0}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
        QTest::newRow("36a: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, 2} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
    }
    else
    {
        QTest::newRow("33b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension0}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
        QTest::newRow("35b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_LargeDimension1, c_LargeDimension0}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
        QTest::newRow("36b: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{{c_MaxAllowedDimension, c_LargeDimension0}, 2} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
    }

    QTest::newRow("37: NO capacity reserve for destination matrix") << IntMatrix{{c_LargeDimension1, c_LargeDimension2}, -3} << IntMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
}

void BasicIntMatrixCapacityTests::_buildMovedCopiedVectorConstructorsTestingTable()
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

void BasicIntMatrixCapacityTests::_buildMoveCopyConstructorsTestingTable()
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

void BasicIntMatrixCapacityTests::_buildAssignmentOperatorsTestingTable()
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

void BasicIntMatrixCapacityTests::_buildResizeTestingTable()
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

void BasicIntMatrixCapacityTests::_buildInsertRowTestingTable()
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

void BasicIntMatrixCapacityTests::_buildInsertColumnTestingTable()
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

QTEST_APPLESS_MAIN(BasicIntMatrixCapacityTests)

#include "tst_basicintmatrixcapacitytests.moc"
