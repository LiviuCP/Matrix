#pragma once

#include <optional>

#include "../Matrix/matrixdimensions.h"

static std::optional<matrix_diff_t> computeForwardNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate)
{
    return matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value()
               ? matrixPrimaryCoordinate == matrixPrimaryDimension &&
                         matrixSecondaryCoordinate == matrixSecondaryDimension
                     ? static_cast<matrix_diff_t>(matrixPrimaryDimension) *
                           static_cast<matrix_diff_t>(matrixSecondaryDimension)
                     : static_cast<matrix_diff_t>(*matrixPrimaryCoordinate) *
                               static_cast<matrix_diff_t>(matrixSecondaryDimension) +
                           static_cast<matrix_diff_t>(*matrixSecondaryCoordinate)
               : std::optional<matrix_diff_t>{};
}

static std::optional<matrix_diff_t> computeReverseNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate)
{
    return matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value()
               ? (static_cast<matrix_diff_t>(matrixPrimaryDimension) -
                  static_cast<matrix_diff_t>(*matrixPrimaryCoordinate)) *
                         static_cast<matrix_diff_t>(matrixSecondaryDimension) -
                     static_cast<matrix_diff_t>(*matrixSecondaryCoordinate) - matrix_diff_t{1}
           : !matrixPrimaryCoordinate.has_value() &&
                   matrixSecondaryCoordinate == matrixSecondaryDimension - matrix_diff_t{1}
               ? static_cast<matrix_diff_t>(matrixPrimaryDimension) *
                     static_cast<matrix_diff_t>(matrixSecondaryDimension)
               : std::optional<matrix_diff_t>{};
}

/* These macros are meant solely meant for internal use within the Matrix class */

// macros used for declaring iterator class members

#define COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DifferenceType, SizeType)                 \
    /* Matrix should be allowed to use the private constructor of the iterator, but no other class should have this    \
     * "privilege" */                                                                                                  \
    friend class Matrix<IterableType>;                                                                                 \
                                                                                                                       \
    /* all these are required for STL compatibility */                                                                 \
    using iterator_category = std::random_access_iterator_tag;                                                         \
    using value_type = IterableType;                                                                                   \
    using difference_type = DifferenceType;                                                                            \
    using pointer = IterableType**;                                                                                    \
                                                                                                                       \
    IteratorType& operator++();                                                                                        \
    IteratorType operator++(int unused);                                                                               \
    IteratorType& operator--();                                                                                        \
    IteratorType operator--(int unused);                                                                               \
                                                                                                                       \
    IteratorType& operator+=(DifferenceType offset);                                                                   \
    IteratorType& operator-=(DifferenceType offset);                                                                   \
                                                                                                                       \
    DifferenceType operator-(const IteratorType& it) const;                                                            \
                                                                                                                       \
    auto operator<=>(const IteratorType& it) const;                                                                    \
    bool operator==(const IteratorType& it) const;                                                                     \
                                                                                                                       \
    std::optional<SizeType> getRowNr() const;                                                                          \
    std::optional<SizeType> getColumnNr() const;                                                                       \
                                                                                                                       \
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any      \
     * empty matrix */                                                                                                 \
    IteratorType();                                                                                                    \
                                                                                                                       \
    friend Matrix<IterableType>::IteratorType operator+(const Matrix<IterableType>::IteratorType& it,                  \
                                                        Matrix<IterableType>::IteratorType::difference_type offset)    \
    {                                                                                                                  \
        typename Matrix<IterableType>::IteratorType temp{it};                                                          \
        temp += offset;                                                                                                \
        return temp;                                                                                                   \
    }                                                                                                                  \
                                                                                                                       \
    friend Matrix<IterableType>::IteratorType operator+(Matrix<IterableType>::IteratorType::difference_type offset,    \
                                                        const Matrix<IterableType>::IteratorType& it)                  \
    {                                                                                                                  \
        return it + offset;                                                                                            \
    }                                                                                                                  \
                                                                                                                       \
    friend Matrix<IterableType>::IteratorType operator-(const Matrix<IterableType>::IteratorType& it,                  \
                                                        Matrix<IterableType>::IteratorType::difference_type offset)    \
    {                                                                                                                  \
        typename Matrix<IterableType>::IteratorType temp{it};                                                          \
        temp -= offset;                                                                                                \
        return temp;                                                                                                   \
    }

#define COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType)                               \
    using reference = IterableType&;                                                                                   \
                                                                                                                       \
    IterableType& operator*() const;                                                                                   \
    IterableType* operator->() const;                                                                                  \
    IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType)                                   \
    using reference = const IterableType&;                                                                             \
                                                                                                                       \
    const IterableType& operator*() const;                                                                             \
    const IterableType* operator->() const;                                                                            \
    const IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(DiffType, SizeType)                                              \
    DiffType getDiagonalNr() const;                                                                                    \
    std::optional<SizeType> getDiagonalIndex() const;

#define COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(IterableType)                                                        \
    void _increment();                                                                                                 \
    void _decrement();                                                                                                 \
    bool _isEmpty() const;                                                                                             \
                                                                                                                       \
    IterableType** m_pMatrixPtr;

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DiffType, SizeType)             \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns,                       \
                 std::optional<SizeType> rowNr, std::optional<SizeType> columnNr);                                     \
                                                                                                                       \
    std::optional<DiffType> m_Index; /* relative index within begin - end iterators range */                           \
    SizeType m_NrOfMatrixRows;                                                                                         \
    SizeType m_NrOfMatrixColumns;

#define COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DiffType, SizeType)                 \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns,                       \
                 std::optional<SizeType> rowNr, std::optional<SizeType> columnNr);                                     \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns,                       \
                 const std::pair<DiffType, std::optional<SizeType>>& diagonalNrAndIndex);                              \
                                                                                                                       \
    std::optional<SizeType> m_DiagonalIndex; /* relative index within diagonal */                                      \
    DiffType m_DiagonalNr;                   /* index of the diagonal within matrix */                                 \
    SizeType m_DiagonalSize;                 /* number of elements contained within diagonal */

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

#define GET_FORWARD_NON_DIAG_ITERATOR_COORDINATE(mIteratorSecondaryDimension, mIteratorIndex, Operator)                \
    return mIteratorIndex                                                                                              \
               ? static_cast<size_type>(*mIteratorIndex Operator static_cast<diff_type>(mIteratorSecondaryDimension))  \
               : std::optional<size_type>{};

#define GET_REVERSE_NON_DIAG_ITERATOR_PRIMARY_COORDINATE(mIteratorPrimaryDimension, mIteratorSecondaryDimension,       \
                                                         mIteratorIndex)                                               \
    return mIteratorIndex.has_value() && mIteratorIndex < static_cast<diff_type>(mIteratorPrimaryDimension) *          \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension)      \
               ? static_cast<size_type>(mIteratorPrimaryDimension) -                                                   \
                     static_cast<size_type>(*mIteratorIndex / static_cast<diff_type>(mIteratorSecondaryDimension)) -   \
                     size_type{1}                                                                                      \
               : std::optional<size_type>{};

#define GET_REVERSE_NON_DIAG_ITERATOR_SECONDARY_COORDINATE(mIteratorPrimaryDimension, mIteratorSecondaryDimension,     \
                                                           mIteratorIndex)                                             \
    return mIteratorIndex.has_value()                                                                                  \
               ? m_Index < static_cast<diff_type>(mIteratorPrimaryDimension) *                                         \
                               static_cast<diff_type>(mIteratorSecondaryDimension)                                     \
                     ? static_cast<size_type>(mIteratorSecondaryDimension) -                                           \
                           static_cast<size_type>(*mIteratorIndex %                                                    \
                                                  static_cast<diff_type>(mIteratorSecondaryDimension)) -               \
                           size_type{1}                                                                                \
                     : static_cast<size_type>(mIteratorSecondaryDimension) - size_type{1}                              \
               : std::optional<size_type>{};

#define GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows,                   \
                                                       mMatrixNrOfColumns, matrixRowNr, matrixColumnNr)                \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns,                      \
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);                                   \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

#define GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)          \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, size_type{0}};

#define GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)          \
    return IteratorType{                                                                                               \
        mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,                                                            \
        (mMatrixNrOfRows > size_type{0} ? std::optional{mMatrixNrOfRows - size_type{1}} : std::nullopt),               \
        (mMatrixNrOfColumns > size_type{0} ? std::optional{mMatrixNrOfColumns - size_type{1}} : std::nullopt)};

#define GET_FORWARD_NON_DIAG_END_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)            \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows, mMatrixNrOfColumns};

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

/* mMatrixNrOfColumns - size_type{1} is ignored by constructor if pointer is null (empty matrix),
  otherwise it should not overflow */
#define GET_REVERSE_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt,                              \
                        mMatrixNrOfColumns - size_type{1}};

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
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt,                        \
                              mMatrixNrOfColumns - size_type{1}};

// specialized NIterator macros

/* mMatrixNrOfRows - size_type{1} is ignored by constructor if pointer is null (empty matrix),
  otherwise it should not overflow */
#define GET_REVERSE_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns)                    \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - size_type{1},            \
                        std::nullopt};

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
               : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - size_type{1},      \
                              std::nullopt};

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
