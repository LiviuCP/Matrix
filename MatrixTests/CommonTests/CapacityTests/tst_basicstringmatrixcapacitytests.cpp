#include <QTest>

#include "testutils.h"
#include "tst_basiccapacitytests.h"

Q_DECLARE_METATYPE(StringMatrix)
Q_DECLARE_METATYPE(size_tuple_t) // used for any data type (contains integer size_type values) - it cannot be redeclared with Q_DECL...
Q_DECLARE_METATYPE(size_tuple_array_t) // same here
Q_DECLARE_METATYPE(ConcatMode)

class BasicStringMatrixCapacityTests : public QObject
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

    StringMatrix mPrimaryStringMatrix;
    StringMatrix mSecondaryStringMatrix;
};

void BasicStringMatrixCapacityTests::testCopiedVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<std::string>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    StringMatrix matrix{rowsCount, columnsCount, initList};

    TEST_COPIED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
}

void BasicStringMatrixCapacityTests::testMovedVectorConstructor()
{
    QFETCH(matrix_size_t, rowsCount);
    QFETCH(matrix_size_t, columnsCount);
    QFETCH(std::vector<std::string>, initList);
    QFETCH(matrix_size_t, expectedRowCapacity);
    QFETCH(matrix_size_t, expectedColumnCapacity);
    QFETCH(matrix_opt_size_t, expectedRowCapacityOffset);
    QFETCH(matrix_opt_size_t, expectedColumnCapacityOffset);

    StringMatrix matrix{rowsCount, columnsCount, std::move(initList)};

    TEST_MOVED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset);
}

void BasicStringMatrixCapacityTests::testIdenticalElementsConstructor()
{
    TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(std::string);
}

void BasicStringMatrixCapacityTests::testDiagonalMatrixConstructor()
{
    TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(std::string);
}

void BasicStringMatrixCapacityTests::testCopyConstructor()
{
    TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(std::string);
}

void BasicStringMatrixCapacityTests::testMoveConstructor()
{
    TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(std::string);
}

void BasicStringMatrixCapacityTests::testCopyAssignmentOperator()
{
    TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(std::string);
}

void BasicStringMatrixCapacityTests::testMoveAssignmentOperator()
{
    TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(std::string);
}

void BasicStringMatrixCapacityTests::testTranspose()
{
    TEST_CAPACITY_WITH_TRANSPOSE(std::string, mPrimaryStringMatrix, mSecondaryStringMatrix);
}

void BasicStringMatrixCapacityTests::testReserve()
{
    TEST_CAPACITY_WITH_RESERVE(std::string, mPrimaryStringMatrix);
}

void BasicStringMatrixCapacityTests::testResizeAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_DEFAULT_NEW_VALUES(std::string, mPrimaryStringMatrix);
}

void BasicStringMatrixCapacityTests::testResizeAndSetNewValues()
{
    TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(std::string, mPrimaryStringMatrix);
}

void BasicStringMatrixCapacityTests::testInsertRowAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_DEFAULT_NEW_VALUES(std::string);
}

void BasicStringMatrixCapacityTests::testInsertRowAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_ROW_AND_FILL_IN_NEW_VALUES(std::string);
}

void BasicStringMatrixCapacityTests::testInsertColumnAndDefaultNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(std::string);
}

void BasicStringMatrixCapacityTests::testInsertColumnAndSetNewValues()
{
    TEST_CAPACITY_WITH_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(std::string);
}

void BasicStringMatrixCapacityTests::testEraseRow()
{
    TEST_CAPACITY_WITH_ERASE_ROW(std::string);
}

void BasicStringMatrixCapacityTests::testEraseColumn()
{
    TEST_CAPACITY_WITH_ERASE_COLUMN(std::string);
}

void BasicStringMatrixCapacityTests::testCatByRow()
{
    TEST_CAPACITY_WITH_CAT_BY_ROW(std::string);
}

void BasicStringMatrixCapacityTests::testCatByColumn()
{
    TEST_CAPACITY_WITH_CAT_BY_COLUMN(std::string);
}

void BasicStringMatrixCapacityTests::testSplitByRow()
{
    TEST_CAPACITY_WITH_SPLIT_BY_ROW(std::string);
}

void BasicStringMatrixCapacityTests::testSplitByColumn()
{
    TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(std::string);
}

void BasicStringMatrixCapacityTests::testCopiedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void BasicStringMatrixCapacityTests::testMovedVectorConstructor_data()
{
    _buildMovedCopiedVectorConstructorsTestingTable();
}

void BasicStringMatrixCapacityTests::testIdenticalElementsConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value1"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: large size matrix") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("4: large size matrix") << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("5: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("6: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::string{"Value"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::string{"Value"} << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::string{"Value"} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::testDiagonalMatrixConstructor_data()
{
    QTest::addColumn<matrix_size_t>("rowsColumnsCount");
    QTest::addColumn<std::string>("nonDiagonalValue");
    QTest::addColumn<std::string>("diagonalValue");
    QTest::addColumn<matrix_size_t>("expectedRowColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << std::string{"Value1"} << std::string{"Value2"} << matrix_size_t{3u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << std::string{"Value1"} << std::string{"Value2"} << matrix_size_t{5u} << matrix_opt_size_t{0u};
    QTest::newRow("3: medium size matrix") << matrix_size_t{8u} << std::string{"Value1"} << std::string{"Value2"} << matrix_size_t{10u} << matrix_opt_size_t{1u};
    QTest::newRow("4: medium size matrix") << matrix_size_t{10u} << std::string{"Value1"} << std::string{"Value2"} << matrix_size_t{12u} << matrix_opt_size_t{1u};
    QTest::newRow("5: capped capacity") << c_LargeDimension1 << std::string{"Value1"} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_opt_size_t{1u};
    QTest::newRow("6: capped capacity") << c_LargeDimension2 << std::string{"Value1"} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_opt_size_t{0u};
    QTest::newRow("7: capped capacity") << c_MaxAllowedDimension << std::string{"Value1"} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::testCopyConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void BasicStringMatrixCapacityTests::testMoveConstructor_data()
{
    _buildMoveCopyConstructorsTestingTable();
}

void BasicStringMatrixCapacityTests::testCopyAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void BasicStringMatrixCapacityTests::testMoveAssignmentOperator_data()
{
    _buildAssignmentOperatorsTestingTable();
}

void BasicStringMatrixCapacityTests::testTranspose_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");
    QTest::addColumn<bool>("isTransposedToItself");

    QTest::newRow("1: transposed matrix initially empty") << StringMatrix{{3, 4}, "Value"} << StringMatrix{} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("2: transposed matrix initially empty") << StringMatrix{{4, 3}, "Value"} << StringMatrix{} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("3: transposed matrix initially empty") << StringMatrix{{7, 8}, "Value"} << StringMatrix{} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("4: transposed matrix initially empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("5: transposed matrix initially empty") << StringMatrix{{20, 25}, "Value"} << StringMatrix{} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u} << false;
    QTest::newRow("6: transposed matrix initially empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("7: transposed matrix initially NOT empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{5, 6}, "Value"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("8: transposed matrix initially NOT empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{6, 6}, "Value"} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("9: transposed matrix initially NOT empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{5, 7}, "Value"} << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("10: transposed matrix initially NOT empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{6, 7}, "Value"} << matrix_size_t{7u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("11: transposed matrix initially NOT empty") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{7, 8}, "Value"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << false;
    QTest::newRow("12: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{15, 19}, "Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("13: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{16, 19}, "Value"} << matrix_size_t{20u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("14: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{15, 20}, "Value"} << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("15: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{16, 20}, "Value"} << matrix_size_t{20u} << matrix_size_t{25u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("16: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{20, 25}, "Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("17: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{15, 25}, "Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("18: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{16, 25}, "Value"} << matrix_size_t{20u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("19: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{20, 19}, "Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u} << false;
    QTest::newRow("20: transposed matrix initially NOT empty") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{20, 20}, "Value"} << matrix_size_t{25u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << false;
    QTest::newRow("21: matrix transposed to itself") << StringMatrix{{3, 3}, "Value"} << StringMatrix{{3, 3}, "Value"} << matrix_size_t{3u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("22: matrix transposed to itself") << StringMatrix{{3, 4}, "Value"} << StringMatrix{{3, 4}, "Value"} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << true;
    QTest::newRow("23: matrix transposed to itself") << StringMatrix{{4, 3}, "Value"} << StringMatrix{{4, 3}, "Value"} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("24: matrix transposed to itself") << StringMatrix{{4, 4}, "Value"} << StringMatrix{{4, 4}, "Value"} << matrix_size_t{5u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("25: matrix transposed to itself") << StringMatrix{{7, 8}, "Value"} << StringMatrix{{7, 8}, "Value"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << true;
    QTest::newRow("26: matrix transposed to itself") << StringMatrix{{8, 7}, "Value"} << StringMatrix{{8, 7}, "Value"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("27: matrix transposed to itself") << StringMatrix{{20, 25}, "Value"} << StringMatrix{{20, 25}, "Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{0u} << matrix_opt_size_t{5u} << true;
    QTest::newRow("28: matrix transposed to itself") << StringMatrix{{25, 20}, "Value"} << StringMatrix{{25, 20}, "Value"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{5u} << matrix_opt_size_t{0u} << true;
    QTest::newRow("29: matrix transposed to itself") << StringMatrix{{25, 25}, "Value"} << StringMatrix{{25, 25}, "Value"} << matrix_size_t{31u} << matrix_size_t{31u} << matrix_opt_size_t{3u} << matrix_opt_size_t{3u} << true;
    QTest::newRow("30: matrix transposed to itself") << StringMatrix{{20, 26}, "Value"} << StringMatrix{{20, 26}, "Value"} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{3u} << matrix_opt_size_t{6u} << true;
    QTest::newRow("31: matrix transposed to itself") << StringMatrix{{26, 20}, "Value"} << StringMatrix{{26, 20}, "Value"} << matrix_size_t{32u} << matrix_size_t{32u} << matrix_opt_size_t{6u} << matrix_opt_size_t{3u} << true;
}

void BasicStringMatrixCapacityTests::testReserve_data()
{
    QTest::addColumn<StringMatrix>("matrix");
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

    QTest::newRow("1: row capacity < rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: row capacity < rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{0u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: row capacity < rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: row capacity < rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: row capacity < rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("7: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("9: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("10: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("11: row capacity < rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("12: row capacity == rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{0u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: row capacity == rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{7u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: row capacity == rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_size_t{10u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("19: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("20: row capacity == rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("21: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{0u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{7u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{0u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("24: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{7u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{0u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("26: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{7u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("27: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{0u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("28: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{7u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("29: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("30: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{7u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("31: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{0u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("32: row capacity > rows count, column capacity < columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{7u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("33: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_size_t{11u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("34: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_size_t{12u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("35: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_size_t{13u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("36: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimension2 << matrix_size_t{8u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("37: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("38: row capacity > rows count, column capacity == columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{8u} << c_MaxAllowedDimension << matrix_size_t{8u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("39: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_size_t{11u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_size_t{11u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("41: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("42: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimension2 << matrix_opt_size_t{0u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("43: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("44: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << c_ExceedingDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("45: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_size_t{12u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("46: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("47: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("48: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << c_LargeDimension2 << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("49: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("50: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << c_ExceedingDimension << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("51: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_size_t{13u} << matrix_size_t{9u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("52: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("54: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << c_LargeDimension2 << matrix_size_t{13u} << c_LargeDimension2 << matrix_opt_size_t{1u} << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("55: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("56: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << c_ExceedingDimension << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("57: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{9u} << c_LargeDimension2 << matrix_size_t{9u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("58: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimension2 << matrix_size_t{10u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("59: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimension2 << matrix_size_t{11u} << c_LargeDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("60: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("61: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("62: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << c_ExceedingDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("63: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("64: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("65: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("66: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("67: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("68: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("69: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{9u} << c_MaxAllowedDimension << matrix_size_t{9u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("70: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_size_t{10u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("71: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << matrix_size_t{11u} << c_MaxAllowedDimension << matrix_size_t{11u} << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("72: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxDimensionRowCapacityOffset << c_LargeDimensionColumnCapacityOffset;
    QTest::newRow("73: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("74: row capacity > rows count, column capacity > columns count") << StringMatrix{{10, 8}, "Value1"} << c_ExceedingDimension << c_ExceedingDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << c_MaxDimensionColumnCapacityOffset;
    QTest::newRow("75: row capacity < rows count, column capacity < columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension0 << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("76: row capacity < rows count, column capacity == columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("77: row capacity < rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension0 << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("78: row capacity < rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension0 << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("79: row capacity == rows count, column capacity < columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension0 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("80: row capacity == rows count, column capacity == columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("81: row capacity == rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("82: row capacity == rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("83: row capacity > rows count, column capacity < columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension0 << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("84: row capacity > rows count, column capacity < columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension0 << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("85: row capacity > rows count, column capacity == columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension1 << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("86: row capacity > rows count, column capacity == columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("87: row capacity > rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("88: row capacity > rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("89: row capacity > rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension2 << c_MaxAllowedDimension << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("90: row capacity > rows count, column capacity > columns count") << StringMatrix{{c_LargeDimension1, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    // empty matrix
    QTest::newRow("91: empty matrix") << StringMatrix{} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("92: empty matrix") << StringMatrix{} << matrix_size_t{0u} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("93: empty matrix") << StringMatrix{} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
    QTest::newRow("94: empty matrix") << StringMatrix{} << matrix_size_t{1u} << matrix_size_t{1u} << matrix_size_t{0u} << matrix_size_t{0u} << matrix_opt_size_t{} << matrix_opt_size_t{};
}

void BasicStringMatrixCapacityTests::testResizeAndDefaultNewValues_data()
{
    _buildResizeTestingTable();
}

void BasicStringMatrixCapacityTests::testResizeAndSetNewValues_data()
{
    _buildResizeTestingTable();
}

void BasicStringMatrixCapacityTests::testInsertRowAndDefaultNewValues_data()
{
    _buildInsertRowTestingTable();
}

void BasicStringMatrixCapacityTests::testInsertRowAndSetNewValues_data()
{
    _buildInsertRowTestingTable();
}

void BasicStringMatrixCapacityTests::testInsertColumnAndDefaultNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void BasicStringMatrixCapacityTests::testInsertColumnAndSetNewValues_data()
{
    _buildInsertColumnTestingTable();
}

void BasicStringMatrixCapacityTests::testEraseRow_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedRowsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less rows than columns") << StringMatrix{{3, 4}, "Value"} << size_tuple_array_t{{1u, 3u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {1u, 3u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("2: less rows than columns") << StringMatrix{{10, 15}, "Value"} << size_tuple_array_t{{1u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{5u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{6u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{7u}, matrix_opt_size_t{1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("3: less rows than columns") << StringMatrix{{10, 15}, "Value"} << size_tuple_array_t{{8u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 18u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("4: less rows than columns") << StringMatrix{{10, 15}, "Value"} << size_tuple_array_t{{0u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {8u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {6u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {4u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 18u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("5: less rows than columns") << StringMatrix{{10, 15}, "Value"} << size_tuple_array_t{{9u, 12u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {5u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {3u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 6u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("6: less rows than columns") << StringMatrix{{10, 15}, "Value"} << size_tuple_array_t{{3u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {6u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 18u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {2u, 12u, 18u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {2u, 12u, 18u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 18u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 18u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("7: square matrix") << StringMatrix{{4, 4}, "Value"} << size_tuple_array_t{{1u, 5u, 5u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {1u, 5u, 5u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {1u, 2u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("8: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{1, 12, 12, 2, 1}, {1u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {1u, 12u, 12u, matrix_opt_size_t{5u}, matrix_opt_size_t{1u}}, {1u, 12u, 12u, matrix_opt_size_t{6u}, matrix_opt_size_t{1u}}, {1u, 12u, 12u, matrix_opt_size_t{7u}, matrix_opt_size_t{1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("9: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{8u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 12u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("10: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{0u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {8u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {6u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {4u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 12u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("11: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{9u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {5u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {3u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 6u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("12: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{3u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {6u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 12u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {2u, 12u, 12u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {2u, 12u, 12u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 12u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("13: more rows than columns") << StringMatrix{{7, 5}, "Value"} << size_tuple_array_t{{1u, 8u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {1u, 8u, 6u, matrix_opt_size_t{2u}, matrix_opt_size_t{0u}}, {1u, 8u, 6u, matrix_opt_size_t{3u}, matrix_opt_size_t{0u}}, {1u, 8u, 6u, matrix_opt_size_t{4u}, matrix_opt_size_t{0u}}, {1u, 4u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {1u, 2u, 6u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("14: more rows than columns") << StringMatrix{{10, 9}, "Value"} << size_tuple_array_t{{1u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{5u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{6u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{7u}, matrix_opt_size_t{1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("15: more rows than columns") << StringMatrix{{10, 9}, "Value"} << size_tuple_array_t{{8u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 11u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("16: more rows than columns") << StringMatrix{{10, 9}, "Value"} << size_tuple_array_t{{0u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {8u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {6u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {4u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 2u, 11u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("17: more rows than columns") << StringMatrix{{10, 9}, "Value"} << size_tuple_array_t{{9u, 12u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {0u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {5u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {0u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {3u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 6u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("18: more rows than columns") << StringMatrix{{10, 9}, "Value"} << size_tuple_array_t{{3u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {6u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {7u, 12u, 11u, matrix_opt_size_t{2u}, matrix_opt_size_t{1u}}, {2u, 12u, 11u, matrix_opt_size_t{3u}, matrix_opt_size_t{1u}}, {1u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {2u, 12u, 11u, matrix_opt_size_t{4u}, matrix_opt_size_t{1u}}, {0u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 6u, 11u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 2u, 11u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
}

void BasicStringMatrixCapacityTests::testEraseColumn_data()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<size_tuple_array_t>("erasedColumnsAndExpectedCapacitiesWithOffsets");

    QTest::newRow("1: less columns than rows") << StringMatrix{{4, 3}, "Value"} << size_tuple_array_t{{1u, 5u, 3u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {1u, 5u, 3u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("2: less columns than rows") << StringMatrix{{15, 10}, "Value"} << size_tuple_array_t{{1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{5u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{6u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{7u}}, {1u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 18u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("3: less columns than rows") << StringMatrix{{15, 10}, "Value"} << size_tuple_array_t{{8u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 18u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("4: less columns than rows") << StringMatrix{{15, 10}, "Value"} << size_tuple_array_t{{0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {8u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {4u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 18u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("5: less columns than rows") << StringMatrix{{15, 10}, "Value"} << size_tuple_array_t{{9u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {5u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {3u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 18u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("6: less columns than rows") << StringMatrix{{15, 10}, "Value"} << size_tuple_array_t{{3u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {6u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {2u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {2u, 18u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 18u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 18u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("7: square matrix") << StringMatrix{{4, 4}, "Value"} << size_tuple_array_t{{1u, 5u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 5u, 5u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 5u, 2u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("8: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{5u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{6u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{7u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("9: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{8u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("10: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {8u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {4u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("11: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{9u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {5u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {3u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("12: square matrix") << StringMatrix{{10, 10}, "Value"} << size_tuple_array_t{{3u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {6u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {2u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {2u, 12u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 12u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 12u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("13: more columns than rows") << StringMatrix{{5, 7}, "Value"} << size_tuple_array_t{{1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{2u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{3u}}, {1u, 6u, 8u, matrix_opt_size_t{0u}, matrix_opt_size_t{4u}}, {1u, 6u, 4u, matrix_opt_size_t{0u}, matrix_opt_size_t{1u}}, {1u, 6u, 2u, matrix_opt_size_t{0u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("14: more columns than rows") << StringMatrix{{9, 10}, "Value"} << size_tuple_array_t{{1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{5u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{6u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{7u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("15: more columns than rows") << StringMatrix{{9, 10}, "Value"} << size_tuple_array_t{{8u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {5u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {4u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {3u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 11u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("16: more columns than rows") << StringMatrix{{9, 10}, "Value"} << size_tuple_array_t{{0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {8u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {4u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {2u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 11u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("17: more columns than rows") << StringMatrix{{9, 10}, "Value"} << size_tuple_array_t{{9u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {5u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {0u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {3u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
    QTest::newRow("18: more columns than rows") << StringMatrix{{9, 10}, "Value"} << size_tuple_array_t{{3u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {6u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {7u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{2u}}, {2u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{3u}}, {1u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {2u, 11u, 12u, matrix_opt_size_t{1u}, matrix_opt_size_t{4u}}, {0u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 11u, 6u, matrix_opt_size_t{1u}, matrix_opt_size_t{1u}}, {1u, 11u, 2u, matrix_opt_size_t{1u}, matrix_opt_size_t{0u}}, {0u, 0u, 0u, matrix_opt_size_t{}, matrix_opt_size_t{}}};
}

void BasicStringMatrixCapacityTests::testCatByRow_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << StringMatrix{{4, 7}, "Value1"} << StringMatrix{{5, 7}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << StringMatrix{{5, 7}, "Value2"} << StringMatrix{{4, 7}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{9u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{10, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("4: different matrixes") << StringMatrix{{10, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{26u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("5: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{1, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("6: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{2, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("7: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{3, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("8: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{4, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("9: different matrixes") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{{5, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("10: different matrixes") << StringMatrix{{1, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{17u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("11: different matrixes") << StringMatrix{{2, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{18u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("12: different matrixes") << StringMatrix{{3, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{19u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("13: different matrixes") << StringMatrix{{4, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{20u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("14: different matrixes") << StringMatrix{{5, 22}, "Value2"} << StringMatrix{{16, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{21u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("15: different matrixes") << StringMatrix{{c_LargeDimension2, 22}, "Value1"} << StringMatrix{{1, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("16: different matrixes") << StringMatrix{{c_LargeDimension1, 22}, "Value1"} << StringMatrix{{2, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("17: different matrixes") << StringMatrix{{1, 22}, "Value2"} << StringMatrix{{c_LargeDimension2, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    QTest::newRow("18: different matrixes") << StringMatrix{{2, 22}, "Value2"} << StringMatrix{{c_LargeDimension1, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("19_1a: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_2a: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_3a: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_4a: different matrixes") << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_5a: different matrixes") << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_6a: different matrixes") << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }
    else
    {
        QTest::newRow("19_1b: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension0 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_2b: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_3b: different matrixes") << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_4b: different matrixes") << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension1 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_5b: different matrixes") << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_6b: different matrixes") << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value1"} << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_7b: different matrixes") << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << StringMatrix{{c_DecrHalfMaxAllowedDimension, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_LargeDimension2 << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
        QTest::newRow("19_8b: different matrixes") << StringMatrix{{c_IncrHalfMaxAllowedDimension, 22}, "Value2"} << StringMatrix{{c_HalfMaxAllowedDimension, 22}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << c_MaxAllowedDimension << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
    }

    QTest::newRow("20: same matrix") << StringMatrix{{4, 7}, "Value1"} << StringMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: same matrix") << StringMatrix{{16, 22}, "Value1"} << StringMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{32u} << matrix_size_t{27u} << matrix_opt_size_t{0u} << matrix_opt_size_t{2u};
}

void BasicStringMatrixCapacityTests::testCatByColumn_data()
{
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<ConcatMode>("mode");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: different matrixes") << StringMatrix{{7, 4}, "Value1"} << StringMatrix{{7, 5}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: different matrixes") << StringMatrix{{7, 5}, "Value2"} << StringMatrix{{7, 4}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{8u} << matrix_size_t{9u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 10}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("4: different matrixes") << StringMatrix{{22, 10}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{26u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("5: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 1}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("6: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 2}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u}; // not fully equivalent to the similar catByRow() test: no offset balancing/change, second matrix fits into the right side available capacity
    QTest::newRow("7: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 3}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u};
    QTest::newRow("8: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 4}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("9: different matrixes") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{{22, 5}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("10: different matrixes") << StringMatrix{{22, 1}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{17u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("11: different matrixes") << StringMatrix{{22, 2}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{18u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("12: different matrixes") << StringMatrix{{22, 3}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{19u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("13: different matrixes") << StringMatrix{{22, 4}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{20u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("14: different matrixes") << StringMatrix{{22, 5}, "Value2"} << StringMatrix{{22, 16}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << matrix_size_t{21u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("15: different matrixes") << StringMatrix{{22, c_LargeDimension2}, "Value1"} << StringMatrix{{22, 1}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("16: different matrixes") << StringMatrix{{22, c_LargeDimension1}, "Value1"} << StringMatrix{{22, 2}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("17: different matrixes") << StringMatrix{{22, 1}, "Value2"} << StringMatrix{{22, c_LargeDimension2}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    QTest::newRow("18: different matrixes") << StringMatrix{{22, 2}, "Value2"} << StringMatrix{{22, c_LargeDimension1}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("19_1a: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_2a: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_3a: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_4a: different matrixes") << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_5a: different matrixes") << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_6a: different matrixes") << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("19_1b: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension0 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_2b: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_3b: different matrixes") << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_4b: different matrixes") << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension1 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_5b: different matrixes") << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_6b: different matrixes") << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value1"} << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_7b: different matrixes") << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << StringMatrix{{22, c_DecrHalfMaxAllowedDimension}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_LargeDimension2 << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
        QTest::newRow("19_8b: different matrixes") << StringMatrix{{22, c_IncrHalfMaxAllowedDimension}, "Value2"} << StringMatrix{{22, c_HalfMaxAllowedDimension}, "Value1"} << ConcatMode::SOURCE_TO_DESTINATION << matrix_size_t{27u} << c_MaxAllowedDimension << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
    }

    QTest::newRow("20: same matrix") << StringMatrix{{7, 4}, "Value1"} << StringMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{8u} << matrix_size_t{8u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: same matrix") << StringMatrix{{22, 16}, "Value1"} << StringMatrix{} << ConcatMode::TO_ITSELF << matrix_size_t{27u} << matrix_size_t{32u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::testSplitByRow_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<matrix_size_t>("expectedSrcRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSrcColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestColumnCapacityOffset");

    QTest::newRow("1: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{5, 8}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{5, 13}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{5, 14}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{5, 15}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{5, 16}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("7: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{6, 13}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{6, 14}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{6, 15}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{6, 16}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{7u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("11: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{7, 13}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{7, 14}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{7, 15}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{7, 16}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{8u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{8, 13}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{8, 14}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{17u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("17: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{8, 15}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{18u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("18: NO capacity reserve for destination matrix") << StringMatrix{{15, 17}, "Value1"} << StringMatrix{{8, 16}, "Value2"} << matrix_size_t{8u} << matrix_size_t{18u} << matrix_size_t{21u} << matrix_size_t{10u} << matrix_size_t{20u} << matrix_opt_size_t{5u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("19: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_HalfMaxAllowedDimension}, "Value2"} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{3, c_HalfMaxAllowedDimension}, "Value2"} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << c_LargeDimension1 << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("22: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_MaxAllowedDimension}, "Value2"} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("24: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{3, c_MaxAllowedDimension}, "Value2"} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("25a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_HalfMaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_LargeDimension1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("28a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_MaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("29a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("30a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_HalfMaxAllowedDimension}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("31a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("32a: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_MaxAllowedDimension}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("33a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension0, c_HalfMaxAllowedDimension}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{0u};
        QTest::newRow("35a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension0, c_LargeDimension1}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("36a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("37a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{c_DecrHalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("25b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_HalfMaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_LargeDimension1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("28b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{1, c_MaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("29b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension2 << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("30b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_HalfMaxAllowedDimension}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("31b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("32b: NO capacity reserve for destination matrix") << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension2, c_MaxAllowedDimension}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
        QTest::newRow("33b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension0, c_HalfMaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{0u};
        QTest::newRow("35b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension0, c_LargeDimension1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("36b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{{c_LargeDimension0, c_MaxAllowedDimension}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2} << matrix_opt_size_t{1u};
        QTest::newRow("37b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{c_HalfMaxAllowedDimension} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    }
}

void BasicStringMatrixCapacityTests::testSplitByColumn_data()
{
    QTest::addColumn<StringMatrix>("srcMatrix");
    QTest::addColumn<StringMatrix>("destMatrix");
    QTest::addColumn<matrix_size_t>("splitPosition");
    QTest::addColumn<matrix_size_t>("expectedSrcRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedSrcColumnCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedDestColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedSrcColumnCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedDestColumnCapacityOffset");

    QTest::newRow("1: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{8, 5}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{13, 5}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{14, 5}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("5: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{15, 5}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("6: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{16, 5}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{13, 6}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("8: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{14, 6}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{15, 6}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{16, 6}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{7u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("11: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{13, 7}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{14, 7}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{15, 7}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{16, 7}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{8u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{13, 8}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{14, 8}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{17u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{15, 8}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{18u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: NO capacity reserve for destination matrix") << StringMatrix{{17, 15}, "Value1"} << StringMatrix{{16, 8}, "Value2"} << matrix_size_t{8u} << matrix_size_t{21u} << matrix_size_t{18u} << matrix_size_t{20u} << matrix_size_t{10u} << matrix_opt_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("19: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 1}, "Value2"} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 3}, "Value2"} << c_LargeDimension2 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("22: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, 1}, "Value2"} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{1u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("24: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, 3}, "Value2"} << c_LargeDimension1 << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("25a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_LargeDimension1, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
        QTest::newRow("28a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    }
    else
    {
        QTest::newRow("25b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("26b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("27b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_LargeDimension1, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
        QTest::newRow("28b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, 1}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_IncrHalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    }

    QTest::newRow("29: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension2}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("31: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("32: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_MaxAllowedDimension}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension2}, "Value2"} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};

    if constexpr (c_IsEvenMaxAllowedDimension)
    {
        QTest::newRow("33a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension0}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
        QTest::newRow("35a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_LargeDimension1, c_LargeDimension0}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
        QTest::newRow("36a: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension1}, "Value2"} << c_DecrHalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_HalfMaxAllowedDimension / 2};
    }
    else
    {
        QTest::newRow("33b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_HalfMaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
        QTest::newRow("34b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_HalfMaxAllowedDimension, c_LargeDimension0}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
        QTest::newRow("35b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_LargeDimension1, c_LargeDimension0}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
        QTest::newRow("36b: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{{c_MaxAllowedDimension, c_LargeDimension0}, "Value2"} << c_HalfMaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u} << matrix_opt_size_t{c_IncrHalfMaxAllowedDimension / 2};
    }

    QTest::newRow("37: NO capacity reserve for destination matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << StringMatrix{} << matrix_size_t{1u} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_LargeDimension1 << c_LargeDimension1 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::_buildMovedCopiedVectorConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::vector<std::string>>("initList");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::vector<std::string>(12, "Value") << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::vector<std::string>(12, "Value") << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: large size matrix") << matrix_size_t{8u} << matrix_size_t{10u} << std::vector<std::string>(80, "Value") << matrix_size_t{10u} << matrix_size_t{12u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("4: large size matrix") << matrix_size_t{10u} << matrix_size_t{8u} << std::vector<std::string>(80, "Value") << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("5: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::vector<std::string>(c_LargeDimension1 * c_LargeDimension1, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("6: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::vector<std::string>(c_LargeDimension1 * c_MaxAllowedDimension, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::vector<std::string>(c_MaxAllowedDimension * c_LargeDimension1, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::vector<std::string>(c_LargeDimension2 * c_LargeDimension2, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::vector<std::string>(c_LargeDimension2 * c_MaxAllowedDimension, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("10: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::vector<std::string>(c_MaxAllowedDimension * c_LargeDimension2, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::vector<std::string>(c_MaxAllowedDimension * c_MaxAllowedDimension, "Value") << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::vector<std::string>(c_LargeDimension1 * 3, "Value") << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::vector<std::string>(c_LargeDimension2 * 3, "Value") << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::vector<std::string>(c_MaxAllowedDimension * 4, "Value") << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::vector<std::string>(c_LargeDimension1 * 8, "Value") << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::vector<std::string>(c_MaxAllowedDimension * 10, "Value") << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::vector<std::string>(c_LargeDimension2 * 10, "Value") << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::vector<std::string>(3 * c_LargeDimension1, "Value") << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::vector<std::string>(3 * c_LargeDimension2, "Value") << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::vector<std::string>(4 * c_MaxAllowedDimension, "Value") << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::vector<std::string>(8 * c_LargeDimension1, "Value") << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::vector<std::string>(10 * c_MaxAllowedDimension, "Value") << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::vector<std::string>(10 * c_LargeDimension2, "Value") << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::_buildMoveCopyConstructorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("rowsCount");
    QTest::addColumn<matrix_size_t>("columnsCount");
    QTest::addColumn<std::string>("elementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small size matrix") << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small size matrix") << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"Value"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: medium size matrix") << matrix_size_t{7u} << matrix_size_t{8u} << std::string{"Value"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("4: medium size matrix") << matrix_size_t{8u} << matrix_size_t{7u} << std::string{"Value"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: large size matrix") << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("6: large size matrix") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("7: capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("8: capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("9: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("10: capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("17: capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("18: capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::string{"Value"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::string{"Value"} << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::string{"Value"} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("24: capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::_buildAssignmentOperatorsTestingTable()
{
    QTest::addColumn<matrix_size_t>("srcMatrixRowsCount");
    QTest::addColumn<matrix_size_t>("srcMatrixColumnsCount");
    QTest::addColumn<std::string>("srcMatrixElementValue");
    QTest::addColumn<matrix_size_t>("destMatrixRowsCount");
    QTest::addColumn<matrix_size_t>("destMatrixColumnsCount");
    QTest::addColumn<std::string>("destMatrixElementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: destination matrix initially empty") << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("2: destination matrix initially empty") << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: destination matrix initially empty") << matrix_size_t{7u} << matrix_size_t{8u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("4: destination matrix initially empty") << matrix_size_t{8u} << matrix_size_t{7u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: destination matrix initially empty") << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("6: destination matrix initially empty") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("7: destination matrix initially empty, capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("8: destination matrix initially empty, capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("9: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("10: destination matrix initially empty, capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: destination matrix initially empty, capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: destination matrix initially empty, capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("14: destination matrix initially empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: destination matrix initially empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("16: destination matrix initially empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("17: destination matrix initially empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("18: destination matrix initially empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: destination matrix initially empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: destination matrix initially empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: destination matrix initially empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("22: destination matrix initially empty, capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("23: destination matrix initially empty, capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("24: destination matrix initially empty, capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("25: destination matrix initially empty, capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{0u} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("26: destination matrix initially NOT empty") << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value1"} << matrix_size_t{2u} << matrix_size_t{3u} << std::string{"Value3"} << matrix_size_t{3u} << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("27: destination matrix initially NOT empty") << matrix_size_t{4u} << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{2u} << matrix_size_t{3u} << std::string{"Value3"} << matrix_size_t{5u} << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("28: destination matrix initially NOT empty") << matrix_size_t{7u} << matrix_size_t{8u} << std::string{"Value1"} << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value3"} << matrix_size_t{8u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("29: destination matrix initially NOT empty") << matrix_size_t{8u} << matrix_size_t{7u} << std::string{"Value1"} << matrix_size_t{3u} << matrix_size_t{4u} << std::string{"Value3"} << matrix_size_t{10u} << matrix_size_t{8u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("30: destination matrix initially NOT empty") << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value1"} << matrix_size_t{15u} << matrix_size_t{20u} << std::string{"Value3"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("31: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value1"} << matrix_size_t{15u} << matrix_size_t{20u} << std::string{"Value3"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("32: destination matrix initially NOT empty") << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value1"} << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value3"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("33: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value1"} << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value3"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("34: destination matrix initially NOT empty") << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value1"} << matrix_size_t{25u} << matrix_size_t{20u} << std::string{"Value3"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("35: destination matrix initially NOT empty") << matrix_size_t{15u} << matrix_size_t{20u} << std::string{"Value1"} << matrix_size_t{20u} << matrix_size_t{25u} << std::string{"Value3"} << matrix_size_t{18u} << matrix_size_t{25u} << matrix_opt_size_t{1u} << matrix_opt_size_t{2u};
    QTest::newRow("36: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value1"} << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("37: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension1 << c_MaxAllowedDimension << std::string{"Value1"} << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("38: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{8u} << matrix_size_t{10u} << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("39: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value1"} << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: destination matrix initially NOT empty, capped row and column capacity") << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{8u} << c_MaxAllowedDimension << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("41: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value1"} << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("42: destination matrix initially NOT empty, capped row and column capacity") << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value1"} << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value3"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("43: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{3u} << std::string{"Value1"} << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("44: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value1"} << c_MaxAllowedDimension << matrix_size_t{3u} << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{3u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: destination matrix initially NOT empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{4u} << std::string{"Value1"} << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{5u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension1 << matrix_size_t{8u} << std::string{"Value1"} << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("47: destination matrix initially NOT empty, capped row capacity") << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value1"} << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("48: destination matrix initially NOT empty, capped row capacity") << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value1"} << c_LargeDimension1 << matrix_size_t{10u} << std::string{"Value3"} << c_MaxAllowedDimension << matrix_size_t{12u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("49: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension1 << std::string{"Value1"} << c_LargeDimension2 << matrix_size_t{3u} << std::string{"Value3"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("50: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{3u} << c_MaxAllowedDimension << std::string{"Value3"} << matrix_size_t{3u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("51: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{4u} << c_MaxAllowedDimension << std::string{"Value1"} << matrix_size_t{3u} << c_LargeDimension2 << std::string{"Value3"} << matrix_size_t{5u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("52: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{8u} << c_LargeDimension1 << std::string{"Value1"} << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value3"} << matrix_size_t{10u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value1"} << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value3"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("54: destination matrix initially NOT empty, capped column capacity") << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value1"} << matrix_size_t{10u} << c_LargeDimension1 << std::string{"Value3"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::_buildResizeTestingTable()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("resizeRowsCount");
    QTest::addColumn<matrix_size_t>("resizeColumnsCount");
    QTest::addColumn<std::string>("resizeElementValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: less rows, less columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{7u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("2: less rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{8u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("3: less rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{9u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("4: less rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{10u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: less rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("6: less rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << c_LargeDimension2 << std::string{"Value2"} << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("7: less rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{9u} << c_MaxAllowedDimension << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("8: equal rows, less columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{7u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("9: equal rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{8u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("10: equal rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{9u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("11: equal rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{10u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("12: equal rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("13: equal rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value2"} << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("14: equal rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: more rows, less columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{7u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: more rows, less columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{7u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: more rows, less columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{7u} << std::string{"Value2"} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("18: more rows, less columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{7u} << std::string{"Value2"} << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("19: more rows, less columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{7u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("20: more rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{8u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("21: more rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{8u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("22: more rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{8u} << std::string{"Value2"} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("23: more rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{8u} << std::string{"Value2"} << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("24: more rows, equal columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{8u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("25: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{9u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("26: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{10u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("27: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("28: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << c_LargeDimension2 << std::string{"Value2"} << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("29: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{11u} << c_MaxAllowedDimension << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("30: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{9u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("31: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{10u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("32: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{12u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("33: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << c_LargeDimension2 << std::string{"Value2"} << matrix_size_t{12u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("34: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{12u} << c_MaxAllowedDimension << std::string{"Value2"} << matrix_size_t{12u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("35: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{9u} << std::string{"Value2"} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("36: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{10u} << std::string{"Value2"} << matrix_size_t{13u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("37: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{13u} << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("38: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << c_LargeDimension2 << std::string{"Value2"} << matrix_size_t{13u} << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("39: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << matrix_size_t{13u} << c_MaxAllowedDimension << std::string{"Value2"} << matrix_size_t{13u} << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("40: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{9u} << std::string{"Value2"} << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("41: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{10u} << std::string{"Value2"} << c_LargeDimension2 << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("42: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << matrix_size_t{11u} << std::string{"Value2"} << c_LargeDimension2 << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("43: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value2"} << c_LargeDimension2 << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("44: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value2"} << c_LargeDimension2 << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("45: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{9u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("46: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{10u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("47: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{11u} << std::string{"Value2"} << c_MaxAllowedDimension << matrix_size_t{11u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("48: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value2"} << c_MaxAllowedDimension << c_LargeDimension2 << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("49: more rows, more columns") << StringMatrix{{10, 8}, "Value1"} << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};

    const matrix_size_t c_RowsCount{10};
    const matrix_opt_size_t c_MaxDimensionRowCapacityOffset{(c_MaxAllowedDimension - c_RowsCount) / 2};

    QTest::newRow("50: less rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{10u} << matrix_size_t{8u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("51: less rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{10u} << c_LargeDimension0 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("52: less rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << matrix_size_t{8u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("53: less rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension0 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("54: less rows, equal columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{10u} << c_LargeDimension1 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("55: less rows, equal columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension1 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("56: less rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{10u} << c_LargeDimension2 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{1u};
    QTest::newRow("57: less rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{10u} << c_MaxAllowedDimension << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << c_MaxDimensionRowCapacityOffset << matrix_opt_size_t{0u};
    QTest::newRow("58: less rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_LargeDimension2 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{1u};
    QTest::newRow("59: less rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension1 << c_MaxAllowedDimension << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("60: equal rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << matrix_size_t{8u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("61: equal rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension0 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("62: equal rows, equal columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension1 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("63: equal rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_LargeDimension2 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("64: equal rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_LargeDimension2 << c_MaxAllowedDimension << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("65: more rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << matrix_size_t{8u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("66: more rows, less columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension0 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("67: more rows, equal columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension1 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("68: more rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_LargeDimension2 << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("69: more rows, more columns") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << c_MaxAllowedDimension << c_MaxAllowedDimension << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
}

void BasicStringMatrixCapacityTests::_buildInsertRowTestingTable()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<std::string>("insertedRowValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << StringMatrix{{3, 4}, "Value1"} << matrix_size_t{1u} << std::string{"Value2"} << matrix_size_t{6u} << matrix_size_t{5u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("2: small matrix") << StringMatrix{{6, 5}, "Value1"} << matrix_size_t{3u} << std::string{"Value2"} << matrix_size_t{7u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: small matrix") << StringMatrix{{8, 2}, "Value1"} << matrix_size_t{1u} << std::string{"Value2"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << StringMatrix{{8, 2}, "Value1"} << matrix_size_t{5u} << std::string{"Value2"} << matrix_size_t{10u} << matrix_size_t{2u} << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("5: large matrix") << StringMatrix{{25, 20}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("6: large matrix") << StringMatrix{{25, 20}, "Value1"} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("7: large matrix") << StringMatrix{{25, 20}, "Value1"} << matrix_size_t{12u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("8: large matrix") << StringMatrix{{25, 20}, "Value1"} << matrix_size_t{13u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("9: large matrix") << StringMatrix{{25, 20}, "Value1"} << matrix_size_t{25u} << std::string{"Value2"} << matrix_size_t{31u} << matrix_size_t{25u} << matrix_opt_size_t{3u} << matrix_opt_size_t{2u};
    QTest::newRow("10: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2 - 1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2 + 1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("14: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("15: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("16: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension2 / 2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("17: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
}

void BasicStringMatrixCapacityTests::_buildInsertColumnTestingTable()
{
    QTest::addColumn<StringMatrix>("matrix");
    QTest::addColumn<matrix_size_t>("insertPosition");
    QTest::addColumn<std::string>("insertedColumnValue");
    QTest::addColumn<matrix_size_t>("expectedRowCapacity");
    QTest::addColumn<matrix_size_t>("expectedColumnCapacity");
    QTest::addColumn<matrix_opt_size_t>("expectedRowCapacityOffset");
    QTest::addColumn<matrix_opt_size_t>("expectedColumnCapacityOffset");

    QTest::newRow("1: small matrix") << StringMatrix{{4, 3}, "Value1"} << matrix_size_t{1u} << std::string{"Value2"} << matrix_size_t{5u} << matrix_size_t{6u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("2: small matrix") << StringMatrix{{5, 6}, "Value1"} << matrix_size_t{3u} << std::string{"Value2"} << matrix_size_t{6u} << matrix_size_t{7u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("3: small matrix") << StringMatrix{{2, 8}, "Value1"} << matrix_size_t{1u} << std::string{"Value2"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("4: small matrix") << StringMatrix{{2, 8}, "Value1"} << matrix_size_t{5u} << std::string{"Value2"} << matrix_size_t{2u} << matrix_size_t{10u} << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("5: large matrix") << StringMatrix{{20, 25}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("6: large matrix") << StringMatrix{{20, 25}, "Value1"} << matrix_size_t{11u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("7: large matrix") << StringMatrix{{20, 25}, "Value1"} << matrix_size_t{12u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{2u};
    QTest::newRow("8: large matrix") << StringMatrix{{20, 25}, "Value1"} << matrix_size_t{13u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("9: large matrix") << StringMatrix{{20, 25}, "Value1"} << matrix_size_t{25u} << std::string{"Value2"} << matrix_size_t{25u} << matrix_size_t{31u} << matrix_opt_size_t{2u} << matrix_opt_size_t{3u};
    QTest::newRow("10: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("11: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2 - 1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("12: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{0u};
    QTest::newRow("13: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension1 / 2 + 1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("14: extra large matrix") << StringMatrix{{c_LargeDimension2, c_LargeDimension1}, "Value1"} << matrix_size_t{c_LargeDimension1} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{0u} << matrix_opt_size_t{1u};
    QTest::newRow("15: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{0u} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("16: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension2 / 2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
    QTest::newRow("17: extra large matrix") << StringMatrix{{c_LargeDimension1, c_LargeDimension2}, "Value1"} << matrix_size_t{c_LargeDimension2} << std::string{"Value2"} << c_MaxAllowedDimension << c_MaxAllowedDimension << matrix_opt_size_t{1u} << matrix_opt_size_t{0u};
}

QTEST_APPLESS_MAIN(BasicStringMatrixCapacityTests)

#include "tst_basicstringmatrixcapacitytests.moc"
