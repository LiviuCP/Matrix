#ifndef TST_CAPACITYTESTS_H
#define TST_CAPACITYTESTS_H

#define TEST_COPIED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset) \
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Copied vector constructor initialized matrix with wrong capacity (offset)");

#define TEST_MOVED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset) \
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Moved vector constructor initialized matrix with wrong capacity (offset)");

#define TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> matrix{{rowsCount, columnsCount}, elementValue}; \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Identical matrix constructor initialized matrix with wrong capacity (offset)");

#define TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsColumnsCount); \
    QFETCH(matrixType, nonDiagonalValue); \
    QFETCH(matrixType, diagonalValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowColumnCapacityOffset); \
\
    Matrix<matrixType> matrix{rowsColumnsCount, std::pair<matrixType, matrixType>{nonDiagonalValue, diagonalValue}}; \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowColumnCapacity && \
             matrix.getColumnCapacity() == expectedRowColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowColumnCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedRowColumnCapacityOffset, "Diagonal matrix constructor initialized matrix with wrong capacity (offset)");

#define TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> srcMatrix{{rowsCount, columnsCount}, elementValue}; \
    Matrix<matrixType> destMatrix{srcMatrix}; \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Copy constructor failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> srcMatrix{{rowsCount, columnsCount}, elementValue}; \
    Matrix<matrixType> destMatrix{std::move(srcMatrix)}; \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Move constructor failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixColumnsCount); \
    QFETCH(matrixType, srcMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixColumnsCount); \
    QFETCH(matrixType, destMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> srcMatrix{{srcMatrixRowsCount, srcMatrixColumnsCount}, srcMatrixElementValue}; \
\
    if (destMatrixRowsCount > 0u && destMatrixColumnsCount > 0u) \
    { \
        Matrix<matrixType> destMatrix{{destMatrixRowsCount, destMatrixColumnsCount}, destMatrixElementValue}; \
        destMatrix = srcMatrix; \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Copy assignment failed, capacity (offset) of the destination matrix is not correct!"); \
    } \
    else \
    { \
        Matrix<matrixType> destMatrix; \
        destMatrix = srcMatrix; \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Copy assignment failed, capacity (offset) of the destination matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_MOVE_ASSIGNMENT_OPERATOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixColumnsCount); \
    QFETCH(matrixType, srcMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixColumnsCount); \
    QFETCH(matrixType, destMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> srcMatrix{{srcMatrixRowsCount, srcMatrixColumnsCount}, srcMatrixElementValue}; \
\
    if (destMatrixRowsCount > 0u && destMatrixColumnsCount > 0u) \
    { \
        Matrix<matrixType> destMatrix{{destMatrixRowsCount, destMatrixColumnsCount}, destMatrixElementValue}; \
        destMatrix = std::move(srcMatrix); \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Move assignment failed, capacity (offset) of the destination matrix is not correct!"); \
    } \
    else \
    { \
        Matrix<matrixType> destMatrix; \
        destMatrix = std::move(srcMatrix); \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Move assignment failed, capacity (offset) of the destination matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_TRANSPOSE(matrixType, primaryMatrix, secondaryMatrix) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
    QFETCH(bool, isTransposedToItself); \
\
    primaryMatrix = srcMatrix; \
\
    if (isTransposedToItself) \
    { \
        primaryMatrix.transpose(primaryMatrix); \
\
        QVERIFY2(primaryMatrix.getRowCapacity() == expectedRowCapacity && \
                 primaryMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 primaryMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 primaryMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Calculating transposed matrix failed, capacity (offset) of the destination (transposed) matrix is not correct!"); \
    } \
    else \
    { \
        secondaryMatrix = destMatrix; \
        primaryMatrix.transpose(secondaryMatrix); \
\
        QVERIFY2(secondaryMatrix.getRowCapacity() == expectedRowCapacity && \
                 secondaryMatrix.getColumnCapacity() == expectedColumnCapacity && \
                 secondaryMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
                 secondaryMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Calculating transposed matrix failed, capacity (offset) of the destination (transposed) matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_RESERVE(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
\
    if (primaryMatrix.getRowCapacity() != expectedRowCapacity || \
        primaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        primaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        primaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Reserving/resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \
\
    QVERIFY2(primaryMatrix == matrix, "Reserving/resizing failed, the matrix does not have the correct size and/or values!");

#define TEST_CAPACITY_WITH_RESIZE_AND_DEFAULT_NEW_VALUES(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.resize(resizeRowsCount, resizeColumnsCount); \
\
    if (primaryMatrix.getRowCapacity() != expectedRowCapacity || \
        primaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        primaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        primaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Reserving/resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \

#define TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(matrixType, resizeElementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
\
    if (primaryMatrix.getRowCapacity() != expectedRowCapacity || \
        primaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        primaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        primaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Reserving/resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \

#define TEST_CAPACITY_WITH_RESERVE_AND_RESIZE_AND_DEFAULT_NEW_VALUES(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
    primaryMatrix.resize(resizeRowsCount, resizeColumnsCount); \
\
    if (primaryMatrix.getRowCapacity() != expectedRowCapacity || \
        primaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        primaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        primaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Reserving/resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \

#define TEST_CAPACITY_WITH_RESERVE_AND_RESIZE_AND_FILL_IN_NEW_VALUES(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(matrixType, resizeElementValue); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
    primaryMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
\
    if (primaryMatrix.getRowCapacity() != expectedRowCapacity || \
        primaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        primaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        primaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Reserving/resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \

#define TEST_CAPACITY_WITH_INSERT_ROW_AND_DEFAULT_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.insertRow(insertPosition); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert row failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_INSERT_ROW_AND_FILL_IN_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedRowValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.insertRow(insertPosition, insertedRowValue); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert row failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.insertColumn(insertPosition); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert column failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedColumnValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.insertColumn(insertPosition, insertedColumnValue); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert column failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_RESERVE_AND_INSERT_ROW_AND_DEFAULT_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.reserve(requestedRowCapacity, matrix.getColumnCapacity()); \
    matrix.insertRow(insertPosition); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert row failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_RESERVE_AND_INSERT_ROW_AND_FILL_IN_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedRowValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.reserve(requestedRowCapacity, matrix.getColumnCapacity()); \
    matrix.insertRow(insertPosition, insertedRowValue); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert row failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_RESERVE_AND_INSERT_COLUMN_AND_DEFAULT_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.reserve(matrix.getRowCapacity(), requestedColumnCapacity); \
    matrix.insertColumn(insertPosition); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert column failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_RESERVE_AND_INSERT_COLUMN_AND_FILL_IN_NEW_VALUES(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedColumnValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    matrix.reserve(matrix.getRowCapacity(), requestedColumnCapacity); \
    matrix.insertColumn(insertPosition, insertedColumnValue); \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert column failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_ERASE_ROW(matrixType) \
    using FiveSizeTypesTuple = std::tuple<Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, std::optional<Matrix<matrixType>::size_type>, std::optional<Matrix<matrixType>::size_type>>; \
    using FiveSizeTypesTupleArray = std::vector<FiveSizeTypesTuple>; \
\
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(FiveSizeTypesTupleArray, erasedRowsAndExpectedCapacitiesWithOffsets); \
\
    for (const auto& data : erasedRowsAndExpectedCapacitiesWithOffsets) \
    { \
        matrix.eraseRow(std::get<0>(data)); \
\
        QVERIFY2(matrix.getRowCapacity() == std::get<1>(data) && \
                 matrix.getColumnCapacity() == std::get<2>(data) && \
                 matrix.getRowCapacityOffset() == std::get<3>(data) && \
                 matrix.getColumnCapacityOffset() == std::get<4>(data), "Erase row failed, capacity (offset) of the matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_ERASE_COLUMN(matrixType) \
    using FiveSizeTypesTuple = std::tuple<Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, std::optional<Matrix<matrixType>::size_type>, std::optional<Matrix<matrixType>::size_type>>; \
    using FiveSizeTypesTupleArray = std::vector<FiveSizeTypesTuple>; \
\
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(FiveSizeTypesTupleArray, erasedColumnsAndExpectedCapacitiesWithOffsets); \
\
    for (const auto& data : erasedColumnsAndExpectedCapacitiesWithOffsets) \
    { \
        matrix.eraseColumn(std::get<0>(data)); \
\
        QVERIFY2(matrix.getRowCapacity() == std::get<1>(data) && \
                 matrix.getColumnCapacity() == std::get<2>(data) && \
                 matrix.getRowCapacityOffset() == std::get<3>(data) && \
                 matrix.getColumnCapacityOffset() == std::get<4>(data), "Erase column failed, capacity (offset) of the matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_CAT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    if (requestedRowCapacity > 0u && requestedColumnCapacity > 0u) \
    { \
        destMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
    } \
\
    switch(mode) \
    { \
    case ConcatMode::SOURCE_TO_DESTINATION: \
        destMatrix.catByRow(srcMatrix); \
        QVERIFY(srcMatrix.getRowCapacity() == 0 && srcMatrix.getColumnCapacity() == 0); \
        break; \
    case ConcatMode::TO_ITSELF: \
        destMatrix.catByRow(destMatrix); \
        break; \
    default: \
        assert(false); \
        break; \
    } \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Vertical concatenation failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_CAT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    if (requestedRowCapacity > 0u && requestedColumnCapacity > 0u) \
    { \
        destMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
    } \
\
    switch(mode) \
    { \
    case ConcatMode::SOURCE_TO_DESTINATION: \
        destMatrix.catByColumn(srcMatrix); \
        QVERIFY(srcMatrix.getRowCapacity() == 0 && srcMatrix.getColumnCapacity() == 0); \
        break; \
    case ConcatMode::TO_ITSELF: \
        destMatrix.catByColumn(destMatrix); \
        break; \
    default: \
        assert(false); \
        break; \
    } \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Horizontal concatenation failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_SPLIT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(Matrix<matrixType>::size_type, requestedDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestColumnCapacityOffset); \
\
    if (requestedDestRowCapacity > 0u && requestedDestColumnCapacity > 0u) \
    { \
        destMatrix.reserve(requestedDestRowCapacity, requestedDestColumnCapacity); \
    } \
\
    srcMatrix.splitByRow(destMatrix, splitPosition); \
\
    QVERIFY2(srcMatrix.getRowCapacity() == expectedSrcRowCapacity && \
             srcMatrix.getColumnCapacity() == expectedSrcColumnCapacity && \
             srcMatrix.getRowCapacityOffset() == expectedSrcRowCapacityOffset && \
             srcMatrix.getColumnCapacityOffset() == expectedSrcColumnCapacityOffset, "Vertical split failed, capacity (offset) of the source matrix is not correct!"); \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedDestRowCapacity && \
             destMatrix.getColumnCapacity() == expectedDestColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedDestRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedDestColumnCapacityOffset, "Vertical split failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(Matrix<matrixType>::size_type, requestedDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSrcColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedDestColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSrcColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedDestColumnCapacityOffset); \
\
    if (requestedDestRowCapacity > 0u && requestedDestColumnCapacity > 0u) \
    { \
        destMatrix.reserve(requestedDestRowCapacity, requestedDestColumnCapacity); \
    } \
\
    srcMatrix.splitByColumn(destMatrix, splitPosition); \
\
    QVERIFY2(srcMatrix.getRowCapacity() == expectedSrcRowCapacity && \
             srcMatrix.getColumnCapacity() == expectedSrcColumnCapacity && \
             srcMatrix.getRowCapacityOffset() == expectedSrcRowCapacityOffset && \
             srcMatrix.getColumnCapacityOffset() == expectedSrcColumnCapacityOffset, "Horizontal split failed, capacity (offset) of the source matrix is not correct!"); \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedDestRowCapacity && \
             destMatrix.getColumnCapacity() == expectedDestColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedDestRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedDestColumnCapacityOffset, "Horizontal split failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_RESIZE_AND_ERASE_ROW_AND_OR_COLUMN(matrixType, primaryMatrix) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(matrixType, resizeElementValue); \
    QFETCH(Matrix<matrixType>::size_type, requestedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, requestedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, erasedRowNr); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, erasedColumnNr); \
    QFETCH(bool, shouldEraseColumnBeforeRow); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    primaryMatrix = matrix; \
\
    primaryMatrix.reserve(requestedRowCapacity, requestedColumnCapacity); \
    primaryMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
\
    const bool c_ShouldEraseRow{erasedRowNr.has_value() && erasedRowNr < matrix.getNrOfRows()}; \
    const bool c_ShouldEraseColumn{erasedColumnNr.has_value() && erasedColumnNr < matrix.getNrOfColumns()}; \
    const bool c_ShouldEraseBoth{c_ShouldEraseRow && c_ShouldEraseColumn}; \
    const bool c_ShouldEraseBothInReverse{c_ShouldEraseBoth && shouldEraseColumnBeforeRow}; \
\
    if (c_ShouldEraseBothInReverse) \
    { \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
        primaryMatrix.eraseRow(*erasedRowNr); \
    } \
    else if (c_ShouldEraseBoth) \
    { \
        primaryMatrix.eraseRow(*erasedRowNr); \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
    } \
    else if (c_ShouldEraseRow) \
    { \
        primaryMatrix.eraseRow(*erasedRowNr); \
    } \
    else if (c_ShouldEraseColumn) \
    { \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
    } \
\
    QVERIFY(expectedRowCapacity == primaryMatrix.getRowCapacity() && \
            expectedColumnCapacity == primaryMatrix.getColumnCapacity() && \
            expectedRowCapacityOffset == primaryMatrix.getRowCapacityOffset() && \
            expectedColumnCapacityOffset == primaryMatrix.getColumnCapacityOffset()); \

#endif // TST_CAPACITYTESTS_H
