#ifndef TST_CAPACITYTESTS_H
#define TST_CAPACITYTESTS_H

#define TEST_INIT_LIST_CONSTRUCTOR_CHECK_MATRIX_CAPACITY(matrix, expectedRowCapacity, expectedColumnCapacity) \
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity, "Init list constructor initialized matrix with wrong capacity");

#define TEST_CAPACITY_WITH_IDENTICAL_MATRIX_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
\
    Matrix<matrixType> matrix{rowsCount, columnsCount, elementValue}; \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowCapacity && \
             matrix.getColumnCapacity() == expectedColumnCapacity, "Identical matrix constructor initialized matrix with wrong capacity");

#define TEST_CAPACITY_WITH_DIAGONAL_MATRIX_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsColumnsCount); \
    QFETCH(matrixType, nonDiagonalValue); \
    QFETCH(matrixType, diagonalValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowColumnCapacity); \
\
    Matrix<matrixType> matrix{rowsColumnsCount, std::pair<matrixType, matrixType>{nonDiagonalValue, diagonalValue}}; \
\
    QVERIFY2(matrix.getRowCapacity() == expectedRowColumnCapacity && \
             matrix.getColumnCapacity() == expectedRowColumnCapacity, "Diag matrix constructor initialized matrix with wrong capacity");

#define TEST_CAPACITY_WITH_COPY_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
\
    Matrix<matrixType> srcMatrix{rowsCount, columnsCount, elementValue}; \
    Matrix<matrixType> destMatrix{srcMatrix}; \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy constructor failed, capacity of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_MOVE_CONSTRUCTOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, rowsCount); \
    QFETCH(Matrix<matrixType>::size_type, columnsCount); \
    QFETCH(matrixType, elementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
\
    Matrix<matrixType> srcMatrix{rowsCount, columnsCount, elementValue}; \
    Matrix<matrixType> destMatrix{std::move(srcMatrix)}; \
\
    QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Move constructor failed, capacity of the destination matrix is not correct!");

#define TEST_CAPACITY_WITH_COPY_ASSIGNMENT_OPERATOR(matrixType) \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, srcMatrixColumnsCount); \
    QFETCH(matrixType, srcMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixRowsCount); \
    QFETCH(Matrix<matrixType>::size_type, destMatrixColumnsCount); \
    QFETCH(matrixType, destMatrixElementValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
\
    Matrix<matrixType> srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue}; \
\
    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0) \
    { \
        Matrix<matrixType> destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue}; \
        destMatrix = srcMatrix; \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!"); \
    } \
    else \
    { \
        Matrix<matrixType> destMatrix; \
        destMatrix = srcMatrix; \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!"); \
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
\
    Matrix<matrixType> srcMatrix{srcMatrixRowsCount, srcMatrixColumnsCount, srcMatrixElementValue}; \
\
    if (destMatrixRowsCount != 0 && destMatrixColumnsCount != 0) \
    { \
        Matrix<matrixType> destMatrix{destMatrixRowsCount, destMatrixColumnsCount, destMatrixElementValue}; \
        destMatrix = std::move(srcMatrix); \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!"); \
    } \
    else \
    { \
        Matrix<matrixType> destMatrix; \
        destMatrix = std::move(srcMatrix); \
\
        QVERIFY2(destMatrix.getRowCapacity() == expectedRowCapacity && \
                 destMatrix.getColumnCapacity() == expectedColumnCapacity, "Copy assignment failed, capacity of the destination matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_TRANSPOSE(matrixType, primaryMatrix, secondaryMatrix) \
    QFETCH(Matrix<matrixType>, srcMatrix); \
    QFETCH(Matrix<matrixType>, destMatrix); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
    QFETCH(bool, isTransposedToItself); \
\
    primaryMatrix = srcMatrix; \
\
    if (isTransposedToItself) \
    { \
        primaryMatrix.transpose(primaryMatrix); \
\
        QVERIFY2(primaryMatrix.getRowCapacity() == expectedRowCapacity && \
                 primaryMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!"); \
    } \
    else \
    { \
        secondaryMatrix = destMatrix; \
        primaryMatrix.transpose(secondaryMatrix); \
\
        QVERIFY2(secondaryMatrix.getRowCapacity() == expectedRowCapacity && \
                 secondaryMatrix.getColumnCapacity() == expectedColumnCapacity, "Calculating transposed matrix failed, capacity of the destination (transposed) matrix is not correct!"); \
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
\
    primaryMatrix = matrix; \
    secondaryMatrix = primaryMatrix; \
\
    primaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue); \
    secondaryMatrix.resizeWithValue(resizeRowsCount, resizeColumnsCount, resizeElementValue, requestedRowCapacity, requestedColumnCapacity); \
\
    if (secondaryMatrix.getRowCapacity() != expectedRowCapacity || secondaryMatrix.getColumnCapacity() != expectedColumnCapacity) \
    { \
        QFAIL("Resizing failed, capacity of the matrix is not correct!"); \
    } \
\
    QVERIFY2(secondaryMatrix == primaryMatrix, "Resizing failed, the matrix does not have the correct size and/or values!");

#define TEST_CAPACITY_WITH_INSERT_ROW(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedRowValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
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
             matrix.getColumnCapacity() == expectedColumnCapacity, "Insert row failed, capacity of the matrix is not correct!");

#define TEST_CAPACITY_WITH_INSERT_COLUMN(matrixType) \
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(Matrix<matrixType>::size_type, insertPosition); \
    QFETCH(matrixType, insertedColumnValue); \
    QFETCH(Matrix<matrixType>::size_type, expectedRowCapacity); \
    QFETCH(Matrix<matrixType>::size_type, expectedColumnCapacity); \
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
             matrix.getColumnCapacity() == expectedColumnCapacity, "Insert column failed, capacity of the matrix is not correct!");

#define TEST_CAPACITY_WITH_ERASE_ROW(matrixType) \
    using ThreeSizeTypeTuple = std::tuple<Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, Matrix<matrixType>::size_type>; \
    using TripleSizeTypeTupleArray = std::vector<ThreeSizeTypeTuple>; \
\
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(TripleSizeTypeTupleArray, erasedRowAndExpectedCapacity); \
\
    for (const auto& data : erasedRowAndExpectedCapacity) \
    { \
        matrix.eraseRow(std::get<0>(data)); \
\
        QVERIFY2(matrix.getRowCapacity() == std::get<1>(data) && \
                 matrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!"); \
    }

#define TEST_CAPACITY_WITH_ERASE_COLUMN(matrixType) \
    using TripleSizeTypeTuple = std::tuple<Matrix<matrixType>::size_type, Matrix<matrixType>::size_type, Matrix<matrixType>::size_type>; \
    using TripleSizeTypeTupleArray = std::vector<TripleSizeTypeTuple>; \
\
    QFETCH(Matrix<matrixType>, matrix); \
    QFETCH(TripleSizeTypeTupleArray, erasedColumnAndExpectedCapacity); \
\
    for (const auto& data : erasedColumnAndExpectedCapacity) \
    { \
        matrix.eraseColumn(std::get<0>(data)); \
\
        QVERIFY2(matrix.getRowCapacity() == std::get<1>(data) && \
                 matrix.getColumnCapacity() == std::get<2>(data), "Erase row failed, capacity of the matrix is not correct!"); \
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
\
    if (resizeRowsCount > 0 && resizeColumnsCount > 0) \
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
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Vertical concatenation failed, capacity of the destination matrix is not correct!");

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
\
    if (resizeRowsCount > 0 && resizeColumnsCount > 0) \
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
             destMatrix.getColumnCapacity() == expectedColumnCapacity, "Horizontal concatenation failed, capacity of the destination matrix is not correct!");

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
\
    if (resizeRowsCount > 0 && resizeColumnsCount > 0) \
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
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Vertical split failed, capacity of the first destination matrix is not correct!"); \
\
    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity && \
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Vertical split failed, capacity of the second destination matrix is not correct!");

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
\
    if (resizeRowsCount > 0 && resizeColumnsCount > 0) \
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
             firstDestMatrix.getColumnCapacity() == expectedFirstDestColumnCapacity, "Horizontal split failed, capacity of the first destination matrix is not correct!"); \
\
    QVERIFY2(secondDestMatrix.getRowCapacity() == expectedSecondDestRowCapacity && \
             secondDestMatrix.getColumnCapacity() == expectedSecondDestColumnCapacity, "Horizontal split failed, capacity of the second destination matrix is not correct!");

#endif // TST_CAPACITYTESTS_H
