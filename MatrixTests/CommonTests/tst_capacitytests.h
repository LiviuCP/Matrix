#ifndef TST_CAPACITYTESTS_H
#define TST_CAPACITYTESTS_H

#define TEST_COPIED_VECTOR_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity, expectedRowCapacityOffset, expectedColumnCapacityOffset) \
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Copied vector constructor initialized matrix with wrong capacity (offset)");

#define TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    Matrix<matrixType> matrix{elementValue, rowsCount, columnsCount}; \
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
    Matrix<matrixType> srcMatrix{elementValue, rowsCount, columnsCount}; \
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
    Matrix<matrixType> srcMatrix{elementValue, rowsCount, columnsCount}; \
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
    Matrix<matrixType> srcMatrix{srcMatrixElementValue, srcMatrixRowsCount, srcMatrixColumnsCount}; \
\
    if (destMatrixRowsCount > 0u && destMatrixColumnsCount > 0u) \
    { \
        Matrix<matrixType> destMatrix{destMatrixElementValue, destMatrixRowsCount, destMatrixColumnsCount}; \
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
    Matrix<matrixType> srcMatrix{srcMatrixElementValue, srcMatrixRowsCount, srcMatrixColumnsCount}; \
\
    if (destMatrixRowsCount > 0u && destMatrixColumnsCount > 0u) \
    { \
        Matrix<matrixType> destMatrix{destMatrixElementValue, destMatrixRowsCount, destMatrixColumnsCount}; \
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

#define TEST_CAPACITY_WITH_RESIZE_AND_FILL_IN_NEW_VALUES(matrixType, primaryMatrix, secondaryMatrix) \
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
    secondaryMatrix = primaryMatrix; \
\
    primaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
    secondaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue, requestedRowCapacity, requestedColumnCapacity); \
\
    if (secondaryMatrix.getRowCapacity() != expectedRowCapacity || \
        secondaryMatrix.getColumnCapacity() != expectedColumnCapacity || \
        secondaryMatrix.getRowCapacityOffset() != expectedRowCapacityOffset || \
        secondaryMatrix.getColumnCapacityOffset() != expectedColumnCapacityOffset) \
    { \
        QFAIL("Resizing failed, capacity (offset) of the matrix is not correct!"); \
    } \
\
    QVERIFY2(secondaryMatrix == primaryMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");

#define TEST_CAPACITY_WITH_INSERT_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedRowValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
    QFETCH(bool, isInsertedRowValueSet); \
\
    if (isInsertedRowValueSet) \
    { \
        matrix.insertRow(insertPosition, insertedRowValue); \
    } \
    else \
    { \
        matrix.insertRow(insertPosition); \
    } \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity && \
             matrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             matrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Insert row failed, capacity (offset) of the matrix is not correct!");

#define TEST_CAPACITY_WITH_INSERT_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedColumnValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
    QFETCH(bool, isInsertedColumnValueSet); \
\
    if (isInsertedColumnValueSet) \
    { \
        matrix.insertColumn(insertPosition, insertedColumnValue); \
    } \
    else \
    { \
        matrix.insertColumn(insertPosition); \
    } \
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
    QFETCH(Matrix<matrixType>, firstSrcMatrix); \
    QFETCH(Matrix<matrixType>, secondSrcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    if (resizeRowsCount > 0u && resizeColumnsCount > 0u) \
    { \
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
    } \
\
    switch(mode) \
    { \
    case ConcatMode::ALL_DIFFERENT: \
        destMatrix.catByRow(firstSrcMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_FIRST: \
        destMatrix.catByRow(destMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_SECOND: \
        destMatrix.catByRow(firstSrcMatrix, destMatrix); \
        break; \
    case ConcatMode::DESTINATION_ALL: \
        destMatrix.catByRow(destMatrix, destMatrix); \
        break; \
    case ConcatMode::SOURCE_BOTH: \
        destMatrix.catByRow(firstSrcMatrix, firstSrcMatrix); \
        break; \
    default: \
        break; \
    } \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Vertical concatenation failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_CAT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>, firstSrcMatrix); \
    QFETCH(Matrix<matrixType>, secondSrcMatrix); \
    QFETCH(ConcatMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedColumnCapacityOffset); \
\
    if (resizeRowsCount > 0u && resizeColumnsCount > 0u) \
    { \
        destMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
    } \
\
    switch(mode) \
    { \
    case ConcatMode::ALL_DIFFERENT: \
        destMatrix.catByColumn(firstSrcMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_FIRST: \
        destMatrix.catByColumn(destMatrix, secondSrcMatrix); \
        break; \
    case ConcatMode::DESTINATION_SECOND: \
        destMatrix.catByColumn(firstSrcMatrix, destMatrix); \
        break; \
    case ConcatMode::DESTINATION_ALL: \
        destMatrix.catByColumn(destMatrix, destMatrix); \
        break; \
    case ConcatMode::SOURCE_BOTH: \
        destMatrix.catByColumn(firstSrcMatrix, firstSrcMatrix); \
        break; \
    default: \
        break; \
    } \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity && \
             destMatrix.getRowCapacityOffset() == expectedRowCapacityOffset && \
             destMatrix.getColumnCapacityOffset() == expectedColumnCapacityOffset, "Horizontal concatenation failed, capacity (offset) of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_SPLIT_BY_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, firstDestMatrix); \
    QFETCH(Matrix<matrixType>, secondDestMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(SplitMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnCapacity); \
    QFETCH(bool, isFirstDestResized); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestColumnCapacityOffset); \
\
    if (resizeRowsCount > 0u && resizeColumnsCount > 0u) \
    { \
        if (isFirstDestResized) \
        { \
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
        } \
        else \
        { \
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
        } \
    } \
\
    switch(mode) \
    { \
    case SplitMode::ALL_DIFFERENT: \
        srcMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_FIRST: \
        firstDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_SECOND: \
        secondDestMatrix.splitByRow(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    default: \
        QFAIL("exception scenario"); \
        break; \
    } \
\
    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity && \
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity && \
             firstDestMatrix.getRowCapacityOffset() == expectedFirstDestRowCapacityOffset && \
             firstDestMatrix.getColumnCapacityOffset() == expectedFirstDestColumnCapacityOffset, "Vertical split failed, capacity (offset) of the first destination matrix is not correct!"); \
\
    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity && \
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity && \
             secondDestMatrix.getRowCapacityOffset() == expectedSecondDestRowCapacityOffset && \
             secondDestMatrix.getColumnCapacityOffset() == expectedSecondDestColumnCapacityOffset, "Vertical split failed, capacity (offset) of the second destination matrix is not correct!");

#define TEST_CAPACITY_WITH_SPLIT_BY_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, firstDestMatrix); \
    QFETCH(Matrix<matrixType>, secondDestMatrix); \
    QFETCH(Matrix<matrixType>::size_type, splitPosition); \
    QFETCH(SplitMode, mode); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnsCount); \
    QFETCH(Matrix<matrixType>::size_type, resizeRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, resizeColumnCapacity); \
    QFETCH(bool, isFirstDestResized); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedFirstDestColumnCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedSecondDestColumnCapacity); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedFirstDestColumnCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestRowCapacityOffset); \
    QFETCH(std::optional<Matrix<matrixType>::size_type>, expectedSecondDestColumnCapacityOffset); \
\
    if (resizeRowsCount > 0u && resizeColumnsCount > 0u) \
    { \
        if (isFirstDestResized) \
        { \
            firstDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
        } \
        else \
        { \
            secondDestMatrix.resize(resizeRowsCount, resizeColumnsCount, resizeRowCapacity, resizeColumnCapacity); \
        } \
    } \
\
    switch(mode) \
    { \
    case SplitMode::ALL_DIFFERENT: \
        srcMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_FIRST: \
        firstDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    case SplitMode::SOURCE_SECOND: \
        secondDestMatrix.splitByColumn(firstDestMatrix, secondDestMatrix, splitPosition); \
        break; \
    default: \
        QFAIL("exception scenario"); \
        break; \
    } \
\
    QVERIFY2(firstDestMatrix.getRowCapacity() == expectedFirstDestRowCapacity && \
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity && \
             firstDestMatrix.getRowCapacityOffset() == expectedFirstDestRowCapacityOffset && \
             firstDestMatrix.getColumnCapacityOffset() == expectedFirstDestColumnCapacityOffset, "Horizontal split failed, capacity (offset) of the first destination matrix is not correct!"); \
\
    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity && \
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity && \
             secondDestMatrix.getRowCapacityOffset() == expectedSecondDestRowCapacityOffset && \
             secondDestMatrix.getColumnCapacityOffset() == expectedSecondDestColumnCapacityOffset, "Horizontal split failed, capacity (offset) of the second destination matrix is not correct!");

#define TEST_CAPACITY_WITH_REZIZE_AND_ERASE_ROW_AND_OR_COLUMN(matrixType, primaryMatrix, secondaryMatrix) \
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
    primaryMatrix = matrix; /* used for consistency check (similarly to resizing tests) */ \
    secondaryMatrix = primaryMatrix; /* tested matrix */ \
\
    primaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
    secondaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue, requestedRowCapacity, requestedColumnCapacity); \
\
    const bool c_ShouldEraseRow{erasedRowNr.has_value() && erasedRowNr < matrix.getNrOfRows()}; \
    const bool c_ShouldEraseColumn{erasedColumnNr.has_value() && erasedColumnNr < matrix.getNrOfColumns()}; \
    const bool c_ShouldEraseBoth{c_ShouldEraseRow && c_ShouldEraseColumn}; \
    const bool c_ShouldEraseBothInReverse{c_ShouldEraseBoth && shouldEraseColumnBeforeRow}; \
\
    if (c_ShouldEraseBothInReverse) \
    { \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
        secondaryMatrix.eraseColumn(*erasedColumnNr); \
        primaryMatrix.eraseRow(*erasedRowNr); \
        secondaryMatrix.eraseRow(*erasedRowNr); \
    } \
    else if (c_ShouldEraseBoth) \
    { \
        primaryMatrix.eraseRow(*erasedRowNr); \
        secondaryMatrix.eraseRow(*erasedRowNr); \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
        secondaryMatrix.eraseColumn(*erasedColumnNr); \
    } \
    else if (c_ShouldEraseRow) \
    { \
        primaryMatrix.eraseRow(*erasedRowNr); \
        secondaryMatrix.eraseRow(*erasedRowNr); \
    } \
    else if (c_ShouldEraseColumn) \
    { \
        primaryMatrix.eraseColumn(*erasedColumnNr); \
        secondaryMatrix.eraseColumn(*erasedColumnNr); \
    } \
\
    QVERIFY(expectedRowCapacity == secondaryMatrix.getRowCapacity() && \
            expectedColumnCapacity == secondaryMatrix.getColumnCapacity() && \
            expectedRowCapacityOffset == secondaryMatrix.getRowCapacityOffset() && \
            expectedColumnCapacityOffset == secondaryMatrix.getColumnCapacityOffset()); \
\
    QVERIFY(secondaryMatrix == primaryMatrix);

#endif // TST_CAPACITYTESTS_H
