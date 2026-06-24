#pragma once

/* These macros are meant solely meant for internal use within the Matrix class */

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

#define CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                            mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, pMatrixPtr,      \
                                            matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, \
                                            matrixSecondaryCoordinate)                                                 \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixPrimaryDimension > size_type{0} && matrixSecondaryDimension > size_type{0} &&                        \
            matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value() &&                            \
            ((matrixPrimaryCoordinate < matrixPrimaryDimension &&                                                      \
              matrixSecondaryCoordinate < matrixSecondaryDimension) ||                                                 \
             (matrixPrimaryCoordinate == matrixPrimaryDimension - size_type{1} &&                                      \
              matrixSecondaryCoordinate == matrixSecondaryDimension)))                                                 \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorPrimaryDimension = matrixPrimaryDimension;                                                        \
            mIteratorSecondaryDimension = matrixSecondaryDimension;                                                    \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate;                                                      \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate;                                                  \
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

#define CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                            mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, pMatrixPtr,      \
                                            matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, \
                                            matrixSecondaryCoordinate)                                                 \
    bool nonEmptyIteratorConstructed = false;                                                                          \
                                                                                                                       \
    if (pMatrixPtr)                                                                                                    \
    {                                                                                                                  \
        if (matrixPrimaryDimension > size_type{0} && matrixSecondaryDimension > size_type{0} &&                        \
            matrixPrimaryCoordinate.has_value() &&                                                                     \
            ((size_type{0} == matrixPrimaryCoordinate && !matrixSecondaryCoordinate.has_value()) ||                    \
             (matrixPrimaryCoordinate < matrixPrimaryDimension && matrixSecondaryCoordinate.has_value() &&             \
              matrixSecondaryCoordinate < matrixSecondaryDimension)))                                                  \
        {                                                                                                              \
            mpIteratorPtr = pMatrixPtr;                                                                                \
            mIteratorPrimaryDimension = matrixPrimaryDimension;                                                        \
            mIteratorSecondaryDimension = matrixSecondaryDimension;                                                    \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate;                                                      \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate;                                                  \
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

#define FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension,                       \
                                                       mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,        \
                                                       mIteratorSecondaryCoordinate, Sign, scalarValue)                \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const diff_type normalizedScalarValue = Sign scalarValue;                                                      \
        const diff_type c_CurrentIndex{                                                                                \
            static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *                               \
                                       static_cast<diff_type>(mIteratorSecondaryDimension) +                           \
                                   static_cast<diff_type>(*mIteratorSecondaryCoordinate))};                            \
        const diff_type c_ResultingIndex{normalizedScalarValue < diff_type{0} &&                                       \
                                                 std::abs(normalizedScalarValue) > c_CurrentIndex                      \
                                             ? diff_type{0}                                                            \
                                             : static_cast<diff_type>(c_CurrentIndex + normalizedScalarValue)};        \
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *        \
                                                            static_cast<diff_type>(mIteratorSecondaryDimension))};     \
                                                                                                                       \
        mIteratorPrimaryCoordinate =                                                                                   \
            c_ResultingIndex < c_UpperBound                                                                            \
                ? static_cast<size_type>(c_ResultingIndex / static_cast<diff_type>(mIteratorSecondaryDimension))       \
                : mIteratorPrimaryDimension - size_type{1};                                                            \
        mIteratorSecondaryCoordinate =                                                                                 \
            c_ResultingIndex < c_UpperBound                                                                            \
                ? static_cast<size_type>(c_ResultingIndex % static_cast<diff_type>(mIteratorSecondaryDimension))       \
                : mIteratorSecondaryDimension;                                                                         \
    }                                                                                                                  \
                                                                                                                       \
    return *this;

#define REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension,                       \
                                                       mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,        \
                                                       mIteratorSecondaryCoordinate, Sign, scalarValue)                \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const diff_type normalizedScalarValue = Sign scalarValue;                                                      \
        const std::optional<diff_type> c_CurrentIndex{                                                                 \
            mIteratorSecondaryCoordinate.has_value()                                                                   \
                ? std::optional{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *           \
                                                           static_cast<diff_type>(mIteratorSecondaryDimension) +       \
                                                       static_cast<diff_type>(*mIteratorSecondaryCoordinate))}         \
                : std::nullopt};                                                                                       \
        std::optional<diff_type> resultingIndex;                                                                       \
                                                                                                                       \
        if (c_CurrentIndex.has_value())                                                                                \
        {                                                                                                              \
            if (normalizedScalarValue >= diff_type{0} || std::abs(normalizedScalarValue) <= c_CurrentIndex)            \
            {                                                                                                          \
                resultingIndex = *c_CurrentIndex + normalizedScalarValue;                                              \
            }                                                                                                          \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            if (normalizedScalarValue > diff_type{0})                                                                  \
            {                                                                                                          \
                resultingIndex = normalizedScalarValue - diff_type{1};                                                 \
            }                                                                                                          \
        }                                                                                                              \
                                                                                                                       \
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *        \
                                                            static_cast<diff_type>(mIteratorSecondaryDimension))};     \
                                                                                                                       \
        mIteratorPrimaryCoordinate =                                                                                   \
            !resultingIndex.has_value() ? size_type{0}                                                                 \
            : resultingIndex >= c_UpperBound                                                                           \
                ? static_cast<size_type>(mIteratorPrimaryDimension - size_type{1})                                     \
                : static_cast<size_type>(*resultingIndex / static_cast<diff_type>(mIteratorSecondaryDimension));       \
        mIteratorSecondaryCoordinate =                                                                                 \
            !resultingIndex.has_value() ? std::nullopt                                                                 \
            : resultingIndex >= c_UpperBound                                                                           \
                ? std::optional{static_cast<size_type>(mIteratorSecondaryDimension - size_type{1})}                    \
                : std::optional{                                                                                       \
                      static_cast<size_type>(*resultingIndex % static_cast<diff_type>(mIteratorSecondaryDimension))};  \
    }                                                                                                                  \
                                                                                                                       \
    return *this;

#define FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension,                         \
                                                     mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,          \
                                                     mIteratorSecondaryCoordinate, secondIterator)                     \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension ||                 \
                              mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension,               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    diff_type result{0};                                                                                               \
                                                                                                                       \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const diff_type c_FirstItIndex{                                                                                \
            static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *                               \
                                       static_cast<diff_type>(mIteratorSecondaryDimension) +                           \
                                   static_cast<diff_type>(*mIteratorSecondaryCoordinate))};                            \
                                                                                                                       \
        const diff_type c_SecondItIndex{                                                                               \
            static_cast<diff_type>(static_cast<diff_type>(*secondIterator.mIteratorPrimaryCoordinate) *                \
                                       static_cast<diff_type>(secondIterator.mIteratorSecondaryDimension) +            \
                                   static_cast<diff_type>(*secondIterator.mIteratorSecondaryCoordinate))};             \
                                                                                                                       \
        result = c_FirstItIndex - c_SecondItIndex;                                                                     \
    }                                                                                                                  \
                                                                                                                       \
    return result;

#define REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension,                         \
                                                     mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,          \
                                                     mIteratorSecondaryCoordinate, secondIterator)                     \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension ||                 \
                              mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension,               \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    diff_type result{0};                                                                                               \
                                                                                                                       \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        const std::optional<diff_type> c_FirstItIndex{                                                                 \
            mIteratorSecondaryCoordinate.has_value()                                                                   \
                ? std::optional{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *           \
                                                           static_cast<diff_type>(mIteratorSecondaryDimension) +       \
                                                       static_cast<diff_type>(*mIteratorSecondaryCoordinate))}         \
                : std::nullopt};                                                                                       \
        const std::optional<diff_type> c_SecondItIndex{                                                                \
            secondIterator.mIteratorSecondaryCoordinate.has_value()                                                    \
                ? std::optional{static_cast<diff_type>(                                                                \
                      static_cast<diff_type>(*secondIterator.mIteratorPrimaryCoordinate) *                             \
                          static_cast<diff_type>(secondIterator.mIteratorSecondaryDimension) +                         \
                      static_cast<diff_type>(*secondIterator.mIteratorSecondaryCoordinate))}                           \
                : std::nullopt};                                                                                       \
                                                                                                                       \
        if (c_FirstItIndex.has_value() && c_SecondItIndex.has_value())                                                 \
        {                                                                                                              \
            result = *c_SecondItIndex - *c_FirstItIndex;                                                               \
        }                                                                                                              \
        else if (!c_FirstItIndex.has_value() && c_SecondItIndex.has_value())                                           \
        {                                                                                                              \
            result = *c_SecondItIndex + diff_type{1};                                                                  \
        }                                                                                                              \
        else if (c_FirstItIndex.has_value() && !c_SecondItIndex.has_value())                                           \
        {                                                                                                              \
            result = diff_type{-1} - *c_FirstItIndex;                                                                  \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    return result;

#define FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension,                          \
                                                    mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,           \
                                                    mIteratorSecondaryCoordinate, firstIterator, secondIterator)       \
    CHECK_ERROR_CONDITION(                                                                                             \
        (firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr ||                                             \
            (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension ||                 \
            (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension,               \
        Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                                    \
                                                                                                                       \
    auto result = std::strong_ordering::equal;                                                                         \
                                                                                                                       \
    /* both iterators are either empty or not */                                                                       \
    if (!(firstIterator)._isEmpty())                                                                                   \
    {                                                                                                                  \
        result = *(firstIterator).mIteratorPrimaryCoordinate <=> *(secondIterator).mIteratorPrimaryCoordinate;         \
                                                                                                                       \
        if (std::strong_ordering::equal == result)                                                                     \
        {                                                                                                              \
            result = *(firstIterator).mIteratorSecondaryCoordinate <=> *(secondIterator).mIteratorSecondaryCoordinate; \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    return result;

#define REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension,                          \
                                                    mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,           \
                                                    mIteratorSecondaryCoordinate, firstIterator, secondIterator)       \
    CHECK_ERROR_CONDITION(                                                                                             \
        (firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr ||                                             \
            (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension ||                 \
            (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension,               \
        Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                                    \
                                                                                                                       \
    auto result = std::strong_ordering::equal;                                                                         \
                                                                                                                       \
    /* both iterators are either empty or not */                                                                       \
    if (!(firstIterator)._isEmpty())                                                                                   \
    {                                                                                                                  \
        result = *(secondIterator).mIteratorPrimaryCoordinate <=> *(firstIterator).mIteratorPrimaryCoordinate;         \
                                                                                                                       \
        if (std::strong_ordering::equal == result)                                                                     \
        {                                                                                                              \
            if ((firstIterator).mIteratorSecondaryCoordinate.has_value() &&                                            \
                (secondIterator).mIteratorSecondaryCoordinate.has_value())                                             \
            {                                                                                                          \
                /* for reverse iterators greater coordinates mean smaller iterator */                                  \
                result =                                                                                               \
                    *(secondIterator).mIteratorSecondaryCoordinate <=> *(firstIterator).mIteratorSecondaryCoordinate;  \
            }                                                                                                          \
            else if ((firstIterator).mIteratorSecondaryCoordinate.has_value() &&                                       \
                     !(secondIterator).mIteratorSecondaryCoordinate.has_value())                                       \
            {                                                                                                          \
                result = std::strong_ordering::less;                                                                   \
            }                                                                                                          \
            else if (!(firstIterator).mIteratorSecondaryCoordinate.has_value() &&                                      \
                     (secondIterator).mIteratorSecondaryCoordinate.has_value())                                        \
            {                                                                                                          \
                result = std::strong_ordering::greater;                                                                \
            }                                                                                                          \
        }                                                                                                              \
    }                                                                                                                  \
                                                                                                                       \
    return result;

#define NON_DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorRowNr,     \
                                         mIteratorColumnNr, secondIterator)                                            \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr ||                                             \
                              mIteratorRowsCount != secondIterator.mIteratorRowsCount ||                               \
                              mIteratorColumnsCount != secondIterator.mIteratorColumnsCount,                           \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);                                  \
                                                                                                                       \
    return (mIteratorRowNr == secondIterator.mIteratorRowNr && mIteratorColumnNr == secondIterator.mIteratorColumnNr);

#define FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr,     \
                                                       mIteratorColumnNr, mIteratorSecondaryCoordinate)                \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension,                   \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr,     \
                                                       mIteratorColumnNr, mIteratorSecondaryCoordinate)                \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(),                                     \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr,        \
                                                    mIteratorColumnNr, mIteratorSecondaryCoordinate)                   \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension,                   \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr);

#define REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr,        \
                                                    mIteratorColumnNr, mIteratorSecondaryCoordinate)                   \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(),                                     \
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);                                \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr);

#define FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(                                                                   \
    mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,                 \
    mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex)                                           \
    CHECK_ERROR_CONDITION(_isEmpty(), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                \
                                                                                                                       \
    const diff_type c_CurrentIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *        \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension) +    \
                                                          static_cast<diff_type>(*mIteratorSecondaryCoordinate))};     \
                                                                                                                       \
    CHECK_ERROR_CONDITION(arrayIndex<diff_type{0} && std::abs(arrayIndex)> c_CurrentIndex,                             \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + arrayIndex)};                             \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *            \
                                                        static_cast<diff_type>(mIteratorSecondaryDimension))};         \
    (void)c_UpperBound;                                                                                                \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound,                                                            \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension]                                   \
                        [c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(                                                                   \
    mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,                 \
    mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex)                                           \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(),                                     \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const diff_type c_CurrentIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) *        \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension) +    \
                                                          static_cast<diff_type>(*mIteratorSecondaryCoordinate))};     \
    const diff_type c_NormalizedIndex{static_cast<diff_type>(-arrayIndex)};                                            \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_NormalizedIndex<diff_type{0} && std::abs(c_NormalizedIndex)> c_CurrentIndex,               \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + c_NormalizedIndex)};                      \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) *            \
                                                        static_cast<diff_type>(mIteratorSecondaryDimension))};         \
    (void)c_UpperBound;                                                                                                \
                                                                                                                       \
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound,                                                            \
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);                            \
                                                                                                                       \
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension]                                   \
                        [c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension,                 \
                                               mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate)               \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate != mIteratorSecondaryDimension ||                                 \
                        mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1)))                                \
    {                                                                                                                  \
        mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + size_type{1};                                   \
                                                                                                                       \
        if (mIteratorSecondaryCoordinate == mIteratorSecondaryDimension &&                                             \
            mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - size_type{1}))                                  \
        {                                                                                                              \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - mIteratorSecondaryDimension;                \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + size_type{1};                                   \
        }                                                                                                              \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,                \
                                               mIteratorSecondaryCoordinate)                                           \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate.has_value() || mIteratorPrimaryCoordinate > size_type{0}))        \
    {                                                                                                                  \
        if (mIteratorSecondaryCoordinate > size_type{0})                                                               \
        {                                                                                                              \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - size_type{1};                               \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            mIteratorSecondaryCoordinate.reset();                                                                      \
        }                                                                                                              \
                                                                                                                       \
        if (!mIteratorSecondaryCoordinate.has_value() && mIteratorPrimaryCoordinate > size_type{0})                    \
        {                                                                                                              \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - size_type{1};                                 \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - size_type{1};                                   \
        }                                                                                                              \
    }

#define FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,                \
                                               mIteratorSecondaryCoordinate)                                           \
    if (!_isEmpty() && (mIteratorPrimaryCoordinate > size_type{0} || mIteratorSecondaryCoordinate > size_type{0}))     \
    {                                                                                                                  \
        if (0 == mIteratorSecondaryCoordinate)                                                                         \
        {                                                                                                              \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - size_type{1};                                   \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - size_type{1};                                 \
        }                                                                                                              \
        else                                                                                                           \
        {                                                                                                              \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - size_type{1};                               \
        }                                                                                                              \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension,                 \
                                               mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate)               \
    if (!_isEmpty())                                                                                                   \
    {                                                                                                                  \
        if (!mIteratorSecondaryCoordinate.has_value())                                                                 \
        {                                                                                                              \
            mIteratorSecondaryCoordinate = size_type{0}; /* decrement from end iterator */                             \
        }                                                                                                              \
        else if (mIteratorPrimaryCoordinate < mIteratorPrimaryDimension - size_type{1} ||                              \
                 mIteratorSecondaryCoordinate < mIteratorSecondaryDimension - size_type{1})                            \
        {                                                                                                              \
            if (mIteratorSecondaryCoordinate == mIteratorSecondaryDimension - size_type{1})                            \
            {                                                                                                          \
                mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + size_type{1};                               \
                mIteratorSecondaryCoordinate = size_type{0};                                                           \
            }                                                                                                          \
            else                                                                                                       \
            {                                                                                                          \
                mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + size_type{1};                           \
            }                                                                                                          \
        }                                                                                                              \
    }

#define CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension,                             \
                                                 mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,              \
                                                 mIteratorSecondaryCoordinate)                                         \
    if (mpIteratorPtr)                                                                                                 \
    {                                                                                                                  \
        assert(mIteratorPrimaryDimension > size_type{0} && mIteratorSecondaryDimension > size_type{0} &&               \
               mIteratorPrimaryCoordinate.has_value() && mIteratorSecondaryCoordinate.has_value());                    \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        assert(size_type{0} == mIteratorPrimaryDimension && size_type{0} == mIteratorSecondaryDimension &&             \
               !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value());                  \
    }                                                                                                                  \
                                                                                                                       \
    return !mpIteratorPtr;

#define CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension,                             \
                                                 mIteratorSecondaryDimension, mIteratorPrimaryCoordinate,              \
                                                 mIteratorSecondaryCoordinate)                                         \
    if (mpIteratorPtr)                                                                                                 \
    {                                                                                                                  \
        assert(mIteratorPrimaryDimension > size_type{0} && mIteratorSecondaryDimension > size_type{0} &&               \
               mIteratorPrimaryCoordinate.has_value());                                                                \
    }                                                                                                                  \
    else                                                                                                               \
    {                                                                                                                  \
        assert(size_type{0} == mIteratorPrimaryDimension && size_type{0} == mIteratorSecondaryDimension &&             \
               !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value());                  \
    }                                                                                                                  \
                                                                                                                       \
    return !mpIteratorPtr;

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
