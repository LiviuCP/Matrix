#ifndef TST_COMBINEDCAPACITYTESTS_H
#define TST_COMBINEDCAPACITYTESTS_H

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

#define TEST_CAPACITY_WITH_RESERVE_AND_CAT_BY_ROW(matrixType) \
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
    else \
    { \
        assert(false); \
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

#define TEST_CAPACITY_WITH_RESERVE_AND_CAT_BY_COLUMN(matrixType) \
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
    else \
    { \
        assert(false); \
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

#define TEST_CAPACITY_WITH_RESERVE_AND_SPLIT_BY_ROW(matrixType) \
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
    else \
    { \
        assert(false); \
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

#define TEST_CAPACITY_WITH_RESERVE_AND_SPLIT_BY_COLUMN(matrixType) \
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
    else \
    { \
        assert(false); \
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

#endif // TST_COMBINEDCAPACITYTESTS_H
