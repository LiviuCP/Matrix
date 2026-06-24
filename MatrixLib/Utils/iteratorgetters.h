#pragma once

/* These macros are meant solely meant for internal use within the Matrix class */

// common ZIterator/NIterator macros

#define GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)          \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, size_type{0}};

#define GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)          \
    return IteratorType{                                                                                               \
        mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,                                                            \
        (mMatrixNrOfRows > size_type{0} ? std::optional{mMatrixNrOfRows - size_type{1}} : std::nullopt),               \
        (mMatrixNrOfColumns > size_type{0} ? std::optional{mMatrixNrOfColumns - size_type{1}} : std::nullopt)};

#define GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows,                   \
                                                       mMatrixNrOfColumns, matrixRowNr, matrixColumnNr)                \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns,                      \
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);                                   \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// common DIterator/MIterator macros

#define GET_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr)    \
    CHECK_ERROR_CONDITION(                                                                                             \
        matrixDiagonalNr<(diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || matrixDiagonalNr>(                \
            static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}),                                                \
        Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);                                                   \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, size_type{0}}};

#define GET_DIAG_RANDOM_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr,        \
                                 matrixColumnNr)                                                                       \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// specialized ZIterator macros

#define GET_FORWARD_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,                                            \
                        (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}),              \
                        mMatrixNrOfColumns};

#define GET_REVERSE_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, std::nullopt};

#define GET_FORWARD_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, size_type{0}};

#define GET_REVERSE_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
                                                                                                                       \
    /* number of columns should be > 0, see above error condition implying matrix should not be empty*/                \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr,                               \
                        (mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} : size_type{0})};

#define GET_FORWARD_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr)   \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
                                                                                                                       \
    /* no overflow, number of rows should be greater than 0, see above error condition implying matrix should not be   \
     * empty */                                                                                                        \
    return matrixRowNr < mMatrixNrOfRows - 1                                                                           \
               ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr + size_type{1},          \
                              size_type{0}}                                                                            \
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, mMatrixNrOfColumns};

#define GET_REVERSE_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr)   \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
                                                                                                                       \
    /* When matrixRowNr > 0 : number of columns should be > 0, see above error condition implying matrix should not be \
     * empty */                                                                                                        \
    return matrixRowNr > size_type{0}                                                                                  \
               ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr - size_type{1},          \
                              (mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} : size_type{0})}  \
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, std::nullopt};

// specialized NIterator macros

#define GET_FORWARD_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows,                           \
                        mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} : size_type{0}};

#define GET_REVERSE_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, size_type{0}};

#define GET_FORWARD_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,           \
                                           matrixColumnNr)                                                             \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, matrixColumnNr};

#define GET_REVERSE_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,           \
                                           matrixColumnNr)                                                             \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    /* number of rows should be > 0, see above error condition implying matrix should not be empty */                  \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,                                            \
                        (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}),              \
                        matrixColumnNr};

#define GET_FORWARD_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,             \
                                         matrixColumnNr)                                                               \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    /* no overflow, number of columns should be greater than 0, see above error condition implying matrix should not   \
     * be empty */                                                                                                     \
    return matrixColumnNr < mMatrixNrOfColumns - size_type{1}                                                          \
               ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0},                        \
                              matrixColumnNr + size_type{1}}                                                           \
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows, matrixColumnNr};

#define GET_REVERSE_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,             \
                                         matrixColumnNr)                                                               \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    /* When matrixColumnNr > 0 : number of rows should be > 0, see above error condition implying matrix should not be \
     * empty */                                                                                                        \
    return matrixColumnNr > size_type{0}                                                                               \
               ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,                                      \
                              (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}),        \
                              matrixColumnNr - size_type{1}}                                                           \
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, size_type{0}};

// specialized DIterator macros

#define GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, \
                                                     matrixRowNr, matrixColumnNr)                                      \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    const auto c_DiagonalNr{                                                                                           \
        static_cast<diff_type>(static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr))};         \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, size_type{0}}};

#define GET_END_DITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,             \
                                         matrixDiagonalNr)                                                             \
    CHECK_ERROR_CONDITION(                                                                                             \
        matrixDiagonalNr<(diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || matrixDiagonalNr>(                \
            static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}),                                                \
        Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);                                                   \
                                                                                                                       \
    const size_type c_BeginRowNr{matrixDiagonalNr < diff_type{0} ? static_cast<size_type>(-matrixDiagonalNr)           \
                                                                 : size_type{0}};                                      \
    const size_type c_BeginColumnNr{matrixDiagonalNr < diff_type{0} ? size_type{0}                                     \
                                                                    : static_cast<size_type>(matrixDiagonalNr)};       \
                                                                                                                       \
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not \
     * exceed total number of rows/columns (see above error condition) */                                              \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                \
                                                static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))};        \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}};

#define GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,   \
                                                   matrixRowNr, matrixColumnNr)                                        \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    const auto c_DiagonalNr{                                                                                           \
        static_cast<diff_type>(static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr))};         \
                                                                                                                       \
    const size_type c_BeginRowNr{c_DiagonalNr < diff_type{0} ? static_cast<size_type>(-c_DiagonalNr) : size_type{0}};  \
    const size_type c_BeginColumnNr{c_DiagonalNr < diff_type{0} ? size_type{0}                                         \
                                                                : static_cast<size_type>(c_DiagonalNr)};               \
                                                                                                                       \
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not \
     * exceed total number of rows/columns (see above error conditions) */                                             \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                \
                                                static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))};        \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows,                    \
                                                      mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex)   \
    CHECK_ERROR_CONDITION(                                                                                             \
        iteratorDiagonalNr<(diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || iteratorDiagonalNr>(            \
            static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}),                                                \
        Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);                                                   \
                                                                                                                       \
    const size_type c_BeginRowNr{iteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(-iteratorDiagonalNr)       \
                                                                   : size_type{0}};                                    \
    const size_type c_BeginColumnNr{iteratorDiagonalNr < diff_type{0} ? size_type{0}                                   \
                                                                      : static_cast<size_type>(iteratorDiagonalNr)};   \
                                                                                                                       \
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not \
     * exceed total number of rows/columns (see above error condition) */                                              \
    const size_type c_DiagonalSize{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                    \
                                            static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))};            \
                                                                                                                       \
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize,                                                     \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    return IteratorType{                                                                                               \
        mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};

// specialized MIterator macros

#define GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, \
                                                     matrixRowNr, matrixColumnNr)                                      \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(mMatrixNrOfColumns) -                        \
                                                   static_cast<diff_type>(matrixColumnNr) - diff_type{1}) -            \
                            static_cast<diff_type>(matrixRowNr)};                                                      \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, size_type{0}}};

#define GET_END_MITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,             \
                                         matrixDiagonalNr)                                                             \
    CHECK_ERROR_CONDITION(                                                                                             \
        matrixDiagonalNr<(diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || matrixDiagonalNr>(                \
            static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}),                                                \
        Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);                                                   \
                                                                                                                       \
    const size_type c_BeginRowNr{matrixDiagonalNr < diff_type{0} ? static_cast<size_type>(-matrixDiagonalNr)           \
                                                                 : size_type{0}};                                      \
                                                                                                                       \
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */         \
    /* of matrix columns if the matrix is not empty (if empty above error condition triggers) */                       \
    const size_type c_BeginColumnNr{                                                                                   \
        matrixDiagonalNr <= diff_type{0}                                                                               \
            ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1})                                                \
            : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(matrixDiagonalNr))};   \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                \
                                                static_cast<size_type>(c_BeginColumnNr + size_type{1}))};              \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}};

#define GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,   \
                                                   matrixRowNr, matrixColumnNr)                                        \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);      \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns,                                                        \
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);                                   \
                                                                                                                       \
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(mMatrixNrOfColumns) -                        \
                                                   static_cast<diff_type>(matrixColumnNr) - diff_type{1}) -            \
                            static_cast<diff_type>(matrixRowNr)};                                                      \
                                                                                                                       \
    const size_type c_BeginRowNr{c_DiagonalNr < diff_type{0} ? static_cast<size_type>(-c_DiagonalNr) : size_type{0}};  \
                                                                                                                       \
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */         \
    /* of matrix columns if the matrix is not empty (if empty above error conditions trigger) */                       \
    const size_type c_BeginColumnNr{                                                                                   \
        c_DiagonalNr <= diff_type{0}                                                                                   \
            ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1})                                                \
            : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(c_DiagonalNr))};       \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                \
                                                static_cast<size_type>(c_BeginColumnNr + size_type{1}))};              \
                                                                                                                       \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows,                    \
                                                      mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex)   \
    CHECK_ERROR_CONDITION(                                                                                             \
        iteratorDiagonalNr<(diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || iteratorDiagonalNr>(            \
            static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}),                                                \
        Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);                                                   \
                                                                                                                       \
    const size_type c_BeginRowNr{iteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(-iteratorDiagonalNr)       \
                                                                   : size_type{0}};                                    \
                                                                                                                       \
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the */                \
    /* number of matrix columns if the matrix is not empty (if empty above error condition triggers) */                \
    const size_type c_BeginColumnNr{                                                                                   \
        iteratorDiagonalNr <= diff_type{0}                                                                             \
            ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1})                                                \
            : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(iteratorDiagonalNr))}; \
                                                                                                                       \
    /* no overflow as for negative diagonals the diagonal number (in absolute value) should be strictly smaller than   \
     * the */                                                                                                          \
    /* number of matrix rows if the matrix is not empty (if empty above error condition triggers */                    \
    const size_type c_DiagonalSize{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr),                    \
                                            static_cast<size_type>(c_BeginColumnNr + size_type{1}))};                  \
                                                                                                                       \
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize,                                                     \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    return IteratorType{                                                                                               \
        mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};
