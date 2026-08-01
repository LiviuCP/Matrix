#pragma once

/* These macros are solely meant for internal use within the Matrix class */

// generic iterator macros

#define ITERATOR_PRE_INCREMENT()                                                                                       \
    _increment();                                                                                                      \
    return *this;

#define ITERATOR_POST_INCREMENT(IteratorType, unusedVar)                                                               \
    (void)unusedVar;                                                                                                   \
    IteratorType iterator{*this};                                                                                      \
                                                                                                                       \
    _increment();                                                                                                      \
                                                                                                                       \
    return iterator;

#define ITERATOR_PRE_DECREMENT()                                                                                       \
    _decrement();                                                                                                      \
    return *this;

#define ITERATOR_POST_DECREMENT(IteratorType, unusedVar)                                                               \
    (void)unusedVar;                                                                                                   \
    IteratorType iterator{*this};                                                                                      \
                                                                                                                       \
    _decrement();                                                                                                      \
                                                                                                                       \
    return iterator;

// common ZIterator/NIterator macros

#define CONSTRUCT_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,             \
                                    mIteratorIndex, pMatrixPtr, matrixPrimaryDimension, matrixSecondaryDimension,      \
                                    matrixIndex)                                                                       \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixPrimaryDimension > size_type{0} && matrixSecondaryDimension > size_type{0} &&                        \
            matrixIndex.has_value() &&                                                                                 \
            matrixIndex <= static_cast<diff_type>(static_cast<diff_type>(matrixPrimaryDimension) *                     \
                                                  static_cast<diff_type>(matrixSecondaryDimension)))                   \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorPrimaryDimension = matrixPrimaryDimension;                                                        \
            mIteratorSecondaryDimension = matrixSecondaryDimension;                                                    \
            mIteratorIndex = matrixIndex;                                                                              \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorPrimaryDimension = size_type{0};                                                                      \
        mIteratorSecondaryDimension = size_type{0};                                                                    \
    }

#define NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,  \
                                               mIteratorIndex, Sign, scalarValue)                                      \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const diff_type normalizedScalarValue = Sign scalarValue;                                                      \
        const diff_type c_ResultingIndex{normalizedScalarValue < diff_type{0} &&                                       \
                                                 std::abs(normalizedScalarValue) > *mIteratorIndex                     \
                                             ? diff_type{0}                                                            \
                                             : static_cast<diff_type>(*mIteratorIndex + normalizedScalarValue)};       \
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *        \
                                                            static_cast<diff_type>(mIteratorSecondaryDimension))};     \
                                                                                                                       \
        mIteratorIndex = std::min<diff_type>(c_ResultingIndex, c_UpperBound);                                          \
    }                                                                                                                  \
                                                                                                                       \
    return *this;

#define NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,    \
                                             mIteratorIndex, secondIterator)                                           \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension ||                 \
                              mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension,               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
    return !_isEmpty() ? *mIteratorIndex - *secondIterator.mIteratorIndex : diff_type{0};

#define NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                            mIteratorIndex, firstIterator, secondIterator)                             \
    CHECK_ERROR_CONDITION(                                                                                             \
        (firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr ||                                             \
            (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension ||                 \
            (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension,               \
        Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                                    \
                                                                                                                       \
    /* both iterators are either empty or not */                                                                       \
    return !(firstIterator)._isEmpty() ? *(firstIterator).mIteratorIndex <=> *(secondIterator).mIteratorIndex          \
                                       : std::strong_ordering::equal;

#define NON_DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorIndex,     \
                                         secondIterator)                                                               \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorRowsCount != secondIterator.mIteratorRowsCount ||                               \
                              mIteratorColumnsCount != secondIterator.mIteratorColumnsCount,                           \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    return mIteratorIndex == secondIterator.mIteratorIndex;

#define NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,  \
                                               mIteratorIndex)                                                         \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *            \
                                                        static_cast<diff_type>(mIteratorSecondaryDimension))};         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorIndex == c_UpperBound,                                                \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return mpIteratorPtr[*getRowNr()][*getColumnNr()];

#define NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                            mIteratorIndex)                                                            \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *            \
                                                        static_cast<diff_type>(mIteratorSecondaryDimension))};         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorIndex == c_UpperBound,                                                \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return (mpIteratorPtr[*getRowNr()] + *getColumnNr());

#define NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                            mIteratorIndex, FirstOperator, SecondOperator, arrayIndex, multiplier,     \
                                            Sign)                                                                      \
    /* The iterator index should not be std::nullopt if the matrix is not empty */                                     \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} && std::abs(arrayIndex) > *mIteratorIndex),         \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const diff_type c_ShiftedIndex{static_cast<diff_type>(*mIteratorIndex + arrayIndex)};                              \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *            \
                                                        static_cast<diff_type>(mIteratorSecondaryDimension))};         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ShiftedIndex >= c_UpperBound,                                                              \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const diff_type c_ResultingIndex{static_cast<diff_type>(static_cast<diff_type>(multiplier) *                       \
                                                            (c_UpperBound - diff_type{1}) Sign c_ShiftedIndex)};       \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingIndex FirstOperator static_cast<diff_type>(mIteratorSecondaryDimension)]           \
                        [c_ResultingIndex SecondOperator static_cast<diff_type>(mIteratorSecondaryDimension)];

#define NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorIndex)         \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *        \
                                                            static_cast<diff_type>(mIteratorSecondaryDimension))};     \
        if (mIteratorIndex < c_UpperBound)                                                                             \
        {                                                                                                              \
            mIteratorIndex = *mIteratorIndex + diff_type{1};                                                           \
        }                                                                                                              \
    }

#define NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorIndex)                                                                 \
    if (!_isEmpty() && mIteratorIndex > diff_type{0})                                                                  \
    {                                                                                                                  \
        mIteratorIndex = *mIteratorIndex - diff_type{1};                                                               \
    }

#define CHECK_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,        \
                                         mIteratorIndex)                                                               \
    if (mpIteratorPtr)                                                                                                 \
    {                                                                                                                  \
        assert(mIteratorPrimaryDimension > size_type{0} && mIteratorSecondaryDimension > size_type{0} &&               \
               mIteratorIndex.has_value());                                                                            \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        assert(size_type{0} == mIteratorPrimaryDimension && size_type{0} == mIteratorSecondaryDimension &&             \
               !mIteratorIndex.has_value());                                                                           \
    }                                                                                                                  \
                                                                                                                       \
    return !mpIteratorPtr;

#define RETRIEVE_FORWARD_NON_DIAG_ITERATOR_COORDINATE(mIteratorSecondaryDimension, mIteratorIndex, Operator)           \
    return mIteratorIndex.has_value()                                                                                  \
               ? static_cast<size_type>(*mIteratorIndex Operator static_cast<diff_type>(mIteratorSecondaryDimension))  \
               : std::optional<size_type>{};

#define RETRIEVE_REVERSE_NON_DIAG_ITERATOR_PRIMARY_COORDINATE(mIteratorPrimaryDimension, mIteratorSecondaryDimension,  \
                                                              mIteratorIndex)                                          \
    return mIteratorIndex.has_value() && mIteratorIndex < static_cast<diff_type>(mIteratorPrimaryDimension) *          \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension)      \
               ? static_cast<size_type>(mIteratorPrimaryDimension) -                                                   \
                     static_cast<size_type>(*mIteratorIndex / static_cast<diff_type>(mIteratorSecondaryDimension)) -   \
                     size_type{1}                                                                                      \
               : std::optional<size_type>{};

#define RETRIEVE_REVERSE_NON_DIAG_ITERATOR_SECONDARY_COORDINATE(mIteratorPrimaryDimension,                             \
                                                                mIteratorSecondaryDimension, mIteratorIndex)           \
    return mIteratorIndex.has_value()                                                                                  \
               ? m_Index < static_cast<diff_type>(mIteratorPrimaryDimension) *                                         \
                               static_cast<diff_type>(mIteratorSecondaryDimension)                                     \
                     ? static_cast<size_type>(mIteratorSecondaryDimension) -                                           \
                           static_cast<size_type>(*mIteratorIndex %                                                    \
                                                  static_cast<diff_type>(mIteratorSecondaryDimension)) -               \
                           size_type{1}                                                                                \
                     : static_cast<size_type>(mIteratorSecondaryDimension) - size_type{1}                              \
               : std::optional<size_type>{};

// common DIterator/MIterator macros

#define DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mIteratorDiagonalSize, mIteratorDiagonalIndex, Sign, scalarValue)           \
    const diff_type c_NormalizedScalarValue{static_cast<diff_type>(Sign scalarValue)};                                 \
    const size_type c_ResultingIndex{static_cast<size_type>(                                                           \
        (c_NormalizedScalarValue < diff_type{0} &&                                                                     \
         static_cast<size_type>(std::abs(c_NormalizedScalarValue)) > mIteratorDiagonalIndex)                           \
            ? size_type{0}                                                                                             \
            : static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + c_NormalizedScalarValue))};     \
    mIteratorDiagonalIndex = std::min(c_ResultingIndex, mIteratorDiagonalSize);                                        \
                                                                                                                       \
    return *this;

#define DIAG_ITERATOR_DO_INCREMENT(mIteratorDiagonalSize, mIteratorDiagonalIndex)                                      \
    if (!_isEmpty() && mIteratorDiagonalIndex < mIteratorDiagonalSize)                                                 \
    {                                                                                                                  \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex + size_type{1};                                               \
    }

#define DIAG_ITERATOR_DO_DECREMENT(mIteratorDiagonalIndex)                                                             \
    if (!_isEmpty() && mIteratorDiagonalIndex > size_type{0})                                                          \
    {                                                                                                                  \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex - size_type{1};                                               \
    }

#define DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                    \
                                         mIteratorDiagonalIndex, secondIterator)                                       \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize ||                         \
                              mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr,                               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    return !_isEmpty() ? (static_cast<diff_type>(*mIteratorDiagonalIndex) -                                            \
                          static_cast<diff_type>(*secondIterator.mIteratorDiagonalIndex))                              \
                       : diff_type{0};

#define DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                     \
                                        mIteratorDiagonalIndex, secondIterator)                                        \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize ||                         \
                              mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr,                               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    return !_isEmpty() ? *mIteratorDiagonalIndex <=> *secondIterator.mIteratorDiagonalIndex                            \
                       : std::strong_ordering::equal;

#define DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                        \
                                     mIteratorDiagonalIndex, secondIterator)                                           \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize ||                         \
                              mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr,                               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    return _isEmpty() || mIteratorDiagonalIndex == secondIterator.mIteratorDiagonalIndex;

#define RETRIEVE_FORWARD_DIAG_ITERATOR_ROW_NR(mIteratorDiagonalNr, mIteratorDiagonalIndex)                             \
    return !_isEmpty()                                                                                                 \
               ? std::optional{mIteratorDiagonalNr < size_type{0} ? *m_DiagonalIndex + std::abs(mIteratorDiagonalNr)   \
                                                                  : *mIteratorDiagonalIndex}                           \
               : std::nullopt;

// specialized DIterator macros

#define CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,  \
                                                           mIteratorDiagonalIndex, pMatrixPtr, matrixRowsCount,        \
                                                           matrixColumnsCount, matrixRowNr, matrixColumnNr)            \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixRowNr.has_value() &&          \
            matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)        \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorDiagonalNr = static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr);      \
            mIteratorDiagonalIndex = std::min(*matrixRowNr, *matrixColumnNr);                                          \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex +                                                          \
                                    std::min(matrixRowsCount - *matrixRowNr, matrixColumnsCount - *matrixColumnNr);    \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
    }

#define CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,  \
                                                           mIteratorDiagonalIndex, pMatrixPtr, matrixRowsCount,        \
                                                           matrixColumnsCount, diagonalNr, diagonalIndex)              \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        std::optional<size_type> resultingDiagonalIndex;                                                               \
        size_type resultingDiagonalSize{0};                                                                            \
                                                                                                                       \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value())          \
        {                                                                                                              \
            const diff_type c_MinDiagonalNr{                                                                           \
                static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))};                       \
            const diff_type c_MaxDiagonalNr{                                                                           \
                static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1})};                    \
                                                                                                                       \
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)                                        \
            {                                                                                                          \
                resultingDiagonalSize =                                                                                \
                    diagonalNr < diff_type{0}                                                                          \
                        ? std::min<size_type>(matrixRowsCount - static_cast<size_type>(-diagonalNr),                   \
                                              matrixColumnsCount)                                                      \
                        : std::min<size_type>(matrixColumnsCount - static_cast<size_type>(diagonalNr),                 \
                                              matrixRowsCount);                                                        \
                                                                                                                       \
                if (diagonalIndex <= resultingDiagonalSize)                                                            \
                {                                                                                                      \
                    resultingDiagonalIndex = diagonalIndex;                                                            \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        if (resultingDiagonalIndex.has_value())                                                                        \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorDiagonalNr = diagonalNr;                                                                          \
            mIteratorDiagonalIndex = resultingDiagonalIndex;                                                           \
            mIteratorDiagonalSize = resultingDiagonalSize;                                                             \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,  \
                                                           mIteratorDiagonalIndex, pMatrixPtr, matrixRowsCount,        \
                                                           matrixColumnsCount, matrixRowNr, matrixColumnNr)            \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        const bool c_AreValidDimensions{matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0}};          \
        assert(c_AreValidDimensions);                                                                                  \
                                                                                                                       \
        if (c_AreValidDimensions)                                                                                      \
        {                                                                                                              \
            const bool c_AreRowAndColumnNrValid{                                                                       \
                (!matrixRowNr.has_value() && !matrixColumnNr.has_value()) ||                                           \
                (!matrixRowNr.has_value() && matrixColumnNr < matrixColumnsCount - size_type{1}) ||                    \
                (!matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount - size_type{1}) ||                       \
                (matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount &&             \
                 matrixColumnNr < matrixColumnsCount)};                                                                \
            assert(c_AreRowAndColumnNrValid);                                                                          \
                                                                                                                       \
            if (c_AreRowAndColumnNrValid)                                                                              \
            {                                                                                                          \
                mpIteratorPtr = pMatrixPtr;                                                                            \
                mIteratorDiagonalNr =                                                                                  \
                    matrixRowNr.has_value() && matrixColumnNr.has_value()                                              \
                        ? static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr)               \
                    : matrixRowNr.has_value()    ? diff_type{-1} - static_cast<diff_type>(*matrixRowNr)                \
                    : matrixColumnNr.has_value() ? static_cast<diff_type>(*matrixColumnNr) + diff_type{1}              \
                                                 : diff_type{0};                                                       \
                                                                                                                       \
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of \
                 * rows (negative) / columns (positive) */                                                             \
                mIteratorDiagonalSize =                                                                                \
                    matrixRowsCount >= matrixColumnsCount                                                              \
                        ? (mIteratorDiagonalNr < diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr                  \
                                                              : matrixColumnsCount - mIteratorDiagonalNr)              \
                        : (mIteratorDiagonalNr <= diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr                 \
                                                               : matrixColumnsCount - mIteratorDiagonalNr);            \
                mIteratorDiagonalIndex =                                                                               \
                    mIteratorDiagonalNr < diff_type{0}                                                                 \
                        ? (matrixColumnNr.has_value() ? mIteratorDiagonalSize - size_type{1} - *matrixColumnNr         \
                                                      : mIteratorDiagonalSize)                                         \
                        : (matrixRowNr.has_value() ? mIteratorDiagonalSize - size_type{1} - *matrixRowNr               \
                                                   : mIteratorDiagonalSize);                                           \
                nonEmptyIteratorConstructed = true;                                                                    \
            }                                                                                                          \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,  \
                                                           mIteratorDiagonalIndex, pMatrixPtr, matrixRowsCount,        \
                                                           matrixColumnsCount, diagonalNr, diagonalIndex)              \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        std::optional<size_type> resultingDiagonalIndex;                                                               \
        size_type resultingDiagonalSize{0};                                                                            \
                                                                                                                       \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value())          \
        {                                                                                                              \
            const diff_type c_MinDiagonalNr{                                                                           \
                static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))};                       \
            const diff_type c_MaxDiagonalNr                                                                            \
            {                                                                                                          \
                static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1});                     \
                                                                                                                       \
                if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)                                    \
                {                                                                                                      \
                    const size_type c_MaxSize{std::max(matrixRowsCount, matrixColumnsCount)};                          \
                                                                                                                       \
                    /* There should be no overflow risk (the absolute value of the diagonal number is lower than       \
                     * number of rows (negative) / columns (positive) */                                               \
                    resultingDiagonalSize =                                                                            \
                        matrixRowsCount >= matrixColumnsCount                                                          \
                            ? (mIteratorDiagonalNr < diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr              \
                                                                  : matrixColumnsCount - mIteratorDiagonalNr)          \
                            : (mIteratorDiagonalNr <= diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr             \
                                                                   : matrixColumnsCount - mIteratorDiagonalNr);        \
                                                                                                                       \
                    if (diagonalIndex <= resultingDiagonalSize)                                                        \
                    {                                                                                                  \
                        resultingDiagonalIndex = diagonalIndex;                                                        \
                    }                                                                                                  \
                }                                                                                                      \
            }                                                                                                          \
                                                                                                                       \
            if (resultingDiagonalIndex.has_value())                                                                    \
            {                                                                                                          \
                mpIteratorPtr = pMatrixPtr;                                                                            \
                mIteratorDiagonalNr = diagonalNr;                                                                      \
                mIteratorDiagonalSize = resultingDiagonalSize;                                                         \
                mIteratorDiagonalIndex = resultingDiagonalIndex;                                                       \
                nonEmptyIteratorConstructed = true;                                                                    \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                assert(false);                                                                                         \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        if (!nonEmptyIteratorConstructed)                                                                              \
        {                                                                                                              \
            mpIteratorPtr = nullptr;                                                                                   \
            mIteratorDiagonalNr = diff_type{0};                                                                        \
            mIteratorDiagonalSize = size_type{0};                                                                      \
        }

#define FORWARD_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,              \
                                               mIteratorDiagonalIndex)                                                 \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))           \
            : *mIteratorDiagonalIndex};                                                                                \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? *mIteratorDiagonalIndex                                                                                  \
            : static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))};          \
                                                                                                                       \
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,              \
                                               mIteratorDiagonalIndex)                                                 \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    /* no overflow risk, diagonal index is less than diagonal size */                                                  \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})};                 \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})                   \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex)                                                    \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))           \
            : *mIteratorDiagonalIndex};                                                                                \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? *mIteratorDiagonalIndex                                                                                  \
            : static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))};          \
                                                                                                                       \
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex)                                                    \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    /* no overflow risk, diagonal index is less than diagonal size */                                                  \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})};                 \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})                   \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, arrayIndex)                                        \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} &&                                                  \
                                         static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex),       \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingDiagonalIndex{                                                                          \
        static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)};                         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize,                                           \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingRowNr{                                                                                  \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))          \
            : c_ResultingDiagonalIndex};                                                                               \
    const size_type c_ResultingColumnNr{                                                                               \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? c_ResultingDiagonalIndex                                                                                 \
            : static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))};         \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, arrayIndex)                                        \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} &&                                                  \
                                         static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex),       \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingDiagonalIndex{                                                                          \
        static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)};                         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize,                                           \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    /* no overflow risk, diagonal index is less than diagonal size */                                                  \
    const size_type c_ResultingRowNr{                                                                                  \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} +                 \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1})};                \
    const size_type c_ResultingColumnNr{                                                                               \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1})                  \
            : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} +                 \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define CHECK_DITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex)    \
    if (mpIteratorPtr)                                                                                                 \
    {                                                                                                                  \
        assert(mIteratorDiagonalSize > size_type{0} && mIteratorDiagonalIndex.has_value());                            \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        assert(diff_type{0} == mIteratorDiagonalNr && size_type{0} == mIteratorDiagonalSize &&                         \
               !mIteratorDiagonalIndex.has_value());                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    return !mpIteratorPtr;

#define RETRIEVE_FORWARD_DITERATOR_COLUMN_NR(mIteratorDiagonalNr, mIteratorDiagonalIndex)                              \
    return !_isEmpty()                                                                                                 \
               ? std::optional{mIteratorDiagonalNr < size_type{0} ? *m_DiagonalIndex                                   \
                                                                  : *mIteratorDiagonalIndex + mIteratorDiagonalNr}     \
               : std::nullopt;

#define RETRIEVE_REVERSE_DITERATOR_ROW_NR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex)          \
    return !_isEmpty() ? mIteratorDiagonalNr < size_type{0}                                                            \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +          \
                                             static_cast<size_type>(-mIteratorDiagonalNr)}                             \
                         : *mIteratorDiagonalIndex < mIteratorDiagonalSize                                             \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}}           \
                             : std::nullopt                                                                            \
                       : std::nullopt;

#define RETRIEVE_REVERSE_DITERATOR_COLUMN_NR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex)       \
    return !_isEmpty() ? mIteratorDiagonalNr > size_type{0}                                                            \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +          \
                                             static_cast<size_type>(mIteratorDiagonalNr)}                              \
                         : *mIteratorDiagonalIndex < mIteratorDiagonalSize                                             \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}}           \
                             : std::nullopt                                                                            \
                       : std::nullopt;

// specialized MIterator macros

#define CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(                                                            \
    mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount,          \
    pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr)                                      \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixRowNr.has_value() &&          \
            matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)        \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorDiagonalNr = static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) -                  \
                                                         static_cast<diff_type>(*matrixColumnNr)) -                    \
                                  static_cast<diff_type>(*matrixRowNr) - diff_type{1};                                 \
            mIteratorDiagonalIndex =                                                                                   \
                std::min<size_type>(*matrixRowNr, matrixColumnsCount - *matrixColumnNr - size_type{1});                \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex + std::min<size_type>(matrixRowsCount - *matrixRowNr,      \
                                                                                  *matrixColumnNr + size_type{1});     \
            mIteratorColumnsCount = matrixColumnsCount;                                                                \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
        mIteratorColumnsCount = size_type{0};                                                                          \
    }

#define CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(                                                            \
    mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount,          \
    pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex)                                        \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        std::optional<size_type> resultingDiagonalIndex;                                                               \
        size_type resultingDiagonalSize{0};                                                                            \
                                                                                                                       \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value())          \
        {                                                                                                              \
            const diff_type c_MinDiagonalNr{                                                                           \
                static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))};                       \
            const diff_type c_MaxDiagonalNr{                                                                           \
                static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1})};                    \
                                                                                                                       \
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)                                        \
            {                                                                                                          \
                resultingDiagonalSize =                                                                                \
                    diagonalNr < diff_type{0}                                                                          \
                        ? std::min<size_type>(matrixRowsCount - static_cast<size_type>(-diagonalNr),                   \
                                              matrixColumnsCount)                                                      \
                        : std::min<size_type>(matrixColumnsCount - static_cast<size_type>(diagonalNr),                 \
                                              matrixRowsCount);                                                        \
                                                                                                                       \
                if (diagonalIndex <= resultingDiagonalSize)                                                            \
                {                                                                                                      \
                    resultingDiagonalIndex = diagonalIndex;                                                            \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        if (resultingDiagonalIndex.has_value())                                                                        \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorDiagonalNr = diagonalNr;                                                                          \
            mIteratorDiagonalIndex = resultingDiagonalIndex;                                                           \
            mIteratorDiagonalSize = resultingDiagonalSize;                                                             \
            mIteratorColumnsCount = matrixColumnsCount;                                                                \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
        mIteratorColumnsCount = size_type{0};                                                                          \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(                                                            \
    mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount,          \
    pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr)                                      \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixColumnNr.has_value() &&       \
            matrixColumnNr <= matrixColumnsCount)                                                                      \
        {                                                                                                              \
            const bool c_IsValidRowNr{                                                                                 \
                (!matrixRowNr.has_value() && matrixColumnNr > size_type{0}) ||                                         \
                (matrixRowNr.has_value() &&                                                                            \
                 ((matrixRowNr < matrixRowsCount - size_type{1} && matrixColumnNr == matrixColumnsCount) ||            \
                  (matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)))};                           \
            assert(c_IsValidRowNr);                                                                                    \
                                                                                                                       \
            if (c_IsValidRowNr)                                                                                        \
            {                                                                                                          \
                mpIteratorPtr = pMatrixPtr;                                                                            \
                mIteratorDiagonalNr = matrixRowNr.has_value()                                                          \
                                          ? static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) -        \
                                                                   static_cast<diff_type>(*matrixColumnNr)) -          \
                                                static_cast<diff_type>(*matrixRowNr) - diff_type{1}                    \
                                          : static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) -        \
                                                                   static_cast<diff_type>(*matrixColumnNr));           \
                                                                                                                       \
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of \
                 * rows (negative) / columns (positive) */                                                             \
                mIteratorDiagonalSize =                                                                                \
                    matrixRowsCount >= matrixColumnsCount                                                              \
                        ? (mIteratorDiagonalNr < diff_type{0}                                                          \
                               ? matrixRowsCount - static_cast<size_type>(-mIteratorDiagonalNr)                        \
                               : matrixColumnsCount + static_cast<size_type>(-mIteratorDiagonalNr))                    \
                        : (mIteratorDiagonalNr <= diff_type{0}                                                         \
                               ? matrixRowsCount + static_cast<size_type>(mIteratorDiagonalNr)                         \
                               : matrixColumnsCount - static_cast<size_type>(mIteratorDiagonalNr));                    \
                mIteratorDiagonalIndex =                                                                               \
                    mIteratorDiagonalNr < diff_type{0} ? mIteratorDiagonalSize - matrixColumnsCount + *matrixColumnNr  \
                    : matrixRowNr.has_value()          ? mIteratorDiagonalSize - size_type{1} - *matrixRowNr           \
                                                       : mIteratorDiagonalSize;                                                 \
                mIteratorColumnsCount = matrixColumnsCount;                                                            \
                nonEmptyIteratorConstructed = true;                                                                    \
            }                                                                                                          \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
        mIteratorColumnsCount = size_type{0};                                                                          \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(                                                            \
    mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount,          \
    pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex)                                        \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        std::optional<size_type> resultingDiagonalIndex;                                                               \
        size_type resultingDiagonalSize{0};                                                                            \
                                                                                                                       \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value())          \
        {                                                                                                              \
            const diff_type c_MinDiagonalNr = diff_type{1} - static_cast<diff_type>(matrixRowsCount);                  \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - diff_type{1};               \
                                                                                                                       \
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)                                        \
            {                                                                                                          \
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of \
                 * rows (negative) / columns (positive) */                                                             \
                resultingDiagonalSize =                                                                                \
                    matrixRowsCount >= matrixColumnsCount                                                              \
                        ? (diagonalNr < diff_type{0} ? matrixRowsCount - static_cast<size_type>(-diagonalNr)           \
                                                     : matrixColumnsCount + static_cast<size_type>(-diagonalNr))       \
                        : (diagonalNr <= diff_type{0} ? matrixRowsCount + static_cast<size_type>(diagonalNr)           \
                                                      : matrixColumnsCount - static_cast<size_type>(diagonalNr));      \
                                                                                                                       \
                if (diagonalIndex <= resultingDiagonalSize)                                                            \
                {                                                                                                      \
                    resultingDiagonalIndex = diagonalIndex;                                                            \
                }                                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        if (resultingDiagonalIndex.has_value())                                                                        \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorDiagonalNr = diagonalNr;                                                                          \
            mIteratorDiagonalSize = resultingDiagonalSize;                                                             \
            mIteratorDiagonalIndex = resultingDiagonalIndex;                                                           \
            mIteratorColumnsCount = matrixColumnsCount;                                                                \
            nonEmptyIteratorConstructed = true;                                                                        \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            assert(false);                                                                                             \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    if (!nonEmptyIteratorConstructed)                                                                                  \
    {                                                                                                                  \
        mpIteratorPtr = nullptr;                                                                                       \
        mIteratorDiagonalNr = diff_type{0};                                                                            \
        mIteratorDiagonalSize = size_type{0};                                                                          \
        mIteratorColumnsCount = size_type{0};                                                                          \
    }

#define FORWARD_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,              \
                                               mIteratorDiagonalIndex, mIteratorColumnsCount)                          \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))           \
            : *mIteratorDiagonalIndex};                                                                                \
                                                                                                                       \
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the        \
     * difference between the */                                                                                       \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for    \
     * negative diagonals) */                                                                                          \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1})                   \
            : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1} -                  \
                                     mIteratorDiagonalNr)};                                                            \
                                                                                                                       \
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,              \
                                               mIteratorDiagonalIndex, mIteratorColumnsCount)                          \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of      \
     * columns; diagonal number if smaller than number of columns */                                                   \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})};                 \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex)          \
            : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex -         \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, mIteratorColumnsCount)                             \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))           \
            : *mIteratorDiagonalIndex};                                                                                \
                                                                                                                       \
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the        \
     * difference between the */                                                                                       \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for    \
     * negative diagonals) */                                                                                          \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1})                   \
            : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1} -                  \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, mIteratorColumnsCount)                             \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize,                               \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
                                                                                                                       \
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of      \
     * columns; diagonal number if smaller than number of columns */                                                   \
    const size_type c_IteratorRowNr{                                                                                   \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +                  \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})};                 \
    const size_type c_IteratorColumnNr{                                                                                \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex)          \
            : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex -         \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex)                 \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} &&                                                  \
                                         static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex),       \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingDiagonalIndex{                                                                          \
        static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)};                         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize,                                           \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingRowNr{                                                                                  \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr))          \
            : c_ResultingDiagonalIndex};                                                                               \
                                                                                                                       \
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the        \
     * difference between the */                                                                                       \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for    \
     * negative diagonals) */                                                                                          \
    const size_type c_ResultingColumnNr{                                                                               \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - size_type{1})                  \
            : static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - size_type{1} -                 \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize,                 \
                                            mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex)                 \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} &&                                                  \
                                         static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex),       \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const size_type c_ResultingDiagonalIndex{                                                                          \
        static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)};                         \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize,                                           \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of      \
     * columns; diagonal number if smaller than number of columns */                                                   \
    const size_type c_ResultingRowNr{                                                                                  \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} +                 \
                                     static_cast<size_type>(-mIteratorDiagonalNr))                                     \
            : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1})};                \
    const size_type c_ResultingColumnNr{                                                                               \
        mIteratorDiagonalNr < diff_type{0}                                                                             \
            ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex)         \
            : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex -        \
                                     static_cast<size_type>(mIteratorDiagonalNr))};                                    \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define CHECK_MITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex,    \
                                 mIteratorNrOfColumns)                                                                 \
    if (mpIteratorPtr)                                                                                                 \
    {                                                                                                                  \
        assert(mIteratorDiagonalSize > size_type{0} && mIteratorDiagonalIndex.has_value() &&                           \
               mIteratorNrOfColumns > size_type{0});                                                                   \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        assert(diff_type{0} == mIteratorDiagonalNr && size_type{0} == mIteratorDiagonalSize &&                         \
               !mIteratorDiagonalIndex.has_value() && size_type{0} == mIteratorNrOfColumns);                           \
    }                                                                                                                  \
                                                                                                                       \
    return !mpIteratorPtr;

#define RETRIEVE_FORWARD_MITERATOR_COLUMN_NR(mIteratorDiagonalNr, mIteratorDiagonalIndex, mIteratorNrOfColumns)        \
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller */                         \
    /* than the number of matrix columns if the matrix is not empty */                                                 \
    return !_isEmpty()                                                                                                 \
               ? mIteratorDiagonalNr < size_type{0}                                                                    \
                     ? (*mIteratorDiagonalIndex < mIteratorNrOfColumns                                                 \
                            ? std::optional{mIteratorNrOfColumns - *mIteratorDiagonalIndex - size_type{1}}             \
                            : std::nullopt)                                                                            \
                     : (*mIteratorDiagonalIndex < mIteratorNrOfColumns - static_cast<size_type>(mIteratorDiagonalNr)   \
                            ? std::optional{mIteratorNrOfColumns - *mIteratorDiagonalIndex - size_type{1} -            \
                                            static_cast<size_type>(mIteratorDiagonalNr)}                               \
                            : std::nullopt)                                                                            \
               : std::nullopt;

#define RETRIEVE_REVERSE_MITERATOR_ROW_NR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex,          \
                                          mIteratorNrOfColumns)                                                        \
    /* no overflow risk, diagonal index should not exceed diagonal size */                                             \
    return !_isEmpty() ? mIteratorDiagonalNr < size_type{0}                                                            \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} +          \
                                             static_cast<size_type>(-mIteratorDiagonalNr)}                             \
                         : *mIteratorDiagonalIndex < mIteratorDiagonalSize                                             \
                             ? std::optional{mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}}           \
                             : std::nullopt                                                                            \
                       : std::nullopt;

#define RETRIEVE_REVERSE_MITERATOR_COLUMN_NR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex,       \
                                             mIteratorNrOfColumns)                                                     \
    /* no overflow risk, diagonal index should not exceed diagonal size, the diagonal number */                        \
    /* is smaller than number of columns (in the second case) */                                                       \
    return !_isEmpty() ? std::optional{mIteratorDiagonalNr < size_type{0}                                              \
                                           ? mIteratorNrOfColumns - mIteratorDiagonalSize + *mIteratorDiagonalIndex    \
                                           : mIteratorNrOfColumns - mIteratorDiagonalSize + *mIteratorDiagonalIndex -  \
                                                 mIteratorDiagonalNr}                                                  \
                       : std::nullopt;
