#ifndef ITERATORUTILS_H
#define ITERATORUTILS_H

/* These macros are meant solely meant for internal use within the Matrix class */

// macros used for declaring iterator class members

#define COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DifferenceType, SizeType) \
    /* Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege" */ \
    friend class Matrix<IterableType>; \
\
    /* all these are required for STL compatibility */ \
    using iterator_category = std::random_access_iterator_tag; \
    using value_type = IterableType; \
    using difference_type = DifferenceType; \
    using pointer = IterableType**; \
\
    IteratorType& operator++(); \
    IteratorType operator++(int unused); \
    IteratorType& operator--(); \
    IteratorType operator--(int unused); \
\
    IteratorType& operator+=(DifferenceType offset); \
    IteratorType& operator-=(DifferenceType offset); \
\
    DifferenceType operator-(const IteratorType& it) const; \
\
    auto operator<=>(const IteratorType& it) const; \
    bool operator==(const IteratorType& it) const; \
\
    std::optional<SizeType> getRowNr() const; \
    std::optional<SizeType> getColumnNr() const; \
\
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix */ \
    IteratorType(); \
\
    friend Matrix<IterableType>::IteratorType operator+(const Matrix<IterableType>::IteratorType& it, Matrix<IterableType>::IteratorType::difference_type offset) \
    { \
        typename Matrix<IterableType>::IteratorType temp{it}; \
        temp += offset; \
        return temp; \
    } \
\
    friend Matrix<IterableType>::IteratorType operator+(Matrix<IterableType>::IteratorType::difference_type offset, const Matrix<IterableType>::IteratorType& it) \
    { \
        return it + offset; \
    } \
\
    friend Matrix<IterableType>::IteratorType operator-(const Matrix<IterableType>::IteratorType& it, Matrix<IterableType>::IteratorType::difference_type offset) \
    { \
        typename Matrix<IterableType>::IteratorType temp{it}; \
        temp -= offset; \
        return temp; \
    }

#define COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = IterableType&; \
\
    IterableType& operator*() const; \
    IterableType* operator->() const; \
    IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = const IterableType&; \
\
    const IterableType& operator*() const; \
    const IterableType* operator->() const; \
    const IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(DiffType, SizeType) \
    DiffType getDiagonalNr() const; \
    std::optional<SizeType> getDiagonalIndex() const;

#define COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(IterableType) \
    void _increment(); \
    void _decrement(); \
    bool _isEmpty() const; \
\
    IterableType** m_pMatrixPtr;

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, std::optional<SizeType> rowNr, std::optional<SizeType> columnNr); \
\
    std::optional<SizeType> m_RowNr; \
    std::optional<SizeType> m_ColumnNr; \
    SizeType m_NrOfMatrixRows; \
    SizeType m_NrOfMatrixColumns;

#define COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DiffType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, std::optional<SizeType> rowNr, std::optional<SizeType> columnNr); \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, const std::pair<DiffType, std::optional<SizeType>>& diagonalNrAndIndex); \
\
    std::optional<SizeType> m_DiagonalIndex;    /* relative index within diagonal */ \
    DiffType m_DiagonalNr;   /* index of the diagonal within matrix */ \
    SizeType m_DiagonalSize;     /* number of elements contained within diagonal */

// generic iterator macros

#define ITERATOR_PRE_INCREMENT() \
    _increment(); \
    return *this;

#define ITERATOR_POST_INCREMENT(IteratorType, unusedVar) \
    (void) unusedVar; \
    IteratorType iterator{*this}; \
\
    _increment(); \
\
    return iterator;

#define ITERATOR_PRE_DECREMENT() \
    _decrement(); \
    return *this;

#define ITERATOR_POST_DECREMENT(IteratorType, unusedVar) \
    (void) unusedVar; \
    IteratorType iterator{*this}; \
\
    _decrement(); \
\
    return iterator;

// common ZIterator/NIterator macros

#define CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, \
                                            pMatrixPtr, matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixPrimaryDimension > 0 && matrixSecondaryDimension > 0 && matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value() && \
            ((matrixPrimaryCoordinate < matrixPrimaryDimension && matrixSecondaryCoordinate < matrixSecondaryDimension) || \
             (matrixPrimaryCoordinate == matrixPrimaryDimension - 1 && matrixSecondaryCoordinate == matrixSecondaryDimension))) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorPrimaryDimension = matrixPrimaryDimension; \
            mIteratorSecondaryDimension = matrixSecondaryDimension; \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorPrimaryDimension = 0; \
        mIteratorSecondaryDimension = 0; \
    }

#define CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, \
                                            pMatrixPtr, matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixPrimaryDimension > 0 && matrixSecondaryDimension > 0 && matrixPrimaryCoordinate.has_value() && \
            ((0 == matrixPrimaryCoordinate && !matrixSecondaryCoordinate.has_value()) || \
             (matrixPrimaryCoordinate < matrixPrimaryDimension && matrixSecondaryCoordinate.has_value() && matrixSecondaryCoordinate < matrixSecondaryDimension))) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorPrimaryDimension = matrixPrimaryDimension; \
            mIteratorSecondaryDimension = matrixSecondaryDimension; \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorPrimaryDimension = 0; \
        mIteratorSecondaryDimension = 0; \
    }

#define FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                       mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (!_isEmpty()) \
    { \
        const diff_type normalizedScalarValue = Sign scalarValue; \
        const diff_type c_CurrentIndex{static_cast<diff_type>(*mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + *mIteratorSecondaryCoordinate)}; \
        const diff_type c_ResultingIndex{normalizedScalarValue < 0 && std::abs(normalizedScalarValue) > c_CurrentIndex ? diff_type{0} : static_cast<diff_type>(c_CurrentIndex + normalizedScalarValue)}; \
        const diff_type c_UpperBound{static_cast<diff_type>(mIteratorPrimaryDimension * mIteratorSecondaryDimension)}; \
\
        mIteratorPrimaryCoordinate = c_ResultingIndex < c_UpperBound ? c_ResultingIndex / mIteratorSecondaryDimension : mIteratorPrimaryDimension - 1; \
        mIteratorSecondaryCoordinate = c_ResultingIndex < c_UpperBound ? c_ResultingIndex % mIteratorSecondaryDimension : mIteratorSecondaryDimension; \
    } \
\
    return *this;

#define REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                       mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (!_isEmpty()) \
    { \
        const diff_type normalizedScalarValue = Sign scalarValue; \
        const std::optional<diff_type> c_CurrentIndex{mIteratorSecondaryCoordinate.has_value() ? std::optional{static_cast<diff_type>(*mIteratorPrimaryCoordinate * \
                                                                                                                                       mIteratorSecondaryDimension + \
                                                                                                                                      *mIteratorSecondaryCoordinate)} \
                                                                                               : std::nullopt}; \
        std::optional<diff_type> resultingIndex; \
\
        if (c_CurrentIndex.has_value()) \
        { \
            if (normalizedScalarValue >= 0 || std::abs(normalizedScalarValue) <= c_CurrentIndex) \
            { \
                resultingIndex = *c_CurrentIndex + normalizedScalarValue; \
            } \
        } \
        else \
        { \
            if (normalizedScalarValue > 0) \
            { \
                resultingIndex = normalizedScalarValue - 1; \
            } \
        } \
\
        const diff_type c_UpperBound{static_cast<diff_type>(mIteratorPrimaryDimension * mIteratorSecondaryDimension)}; \
\
        mIteratorPrimaryCoordinate = !resultingIndex.has_value() ? 0 \
                                                                 : resultingIndex >= c_UpperBound ? static_cast<size_type>(mIteratorPrimaryDimension - 1) \
                                                                                                  : static_cast<size_type>(*resultingIndex / mIteratorSecondaryDimension); \
        mIteratorSecondaryCoordinate = !resultingIndex.has_value() ? std::nullopt \
                                                                   : resultingIndex >= c_UpperBound ? std::optional{static_cast<size_type>(mIteratorSecondaryDimension - 1)} \
                                                                                                    : std::optional{static_cast<size_type>(*resultingIndex % mIteratorSecondaryDimension)}; \
    } \
\
    return *this;

#define FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                     mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || \
                          mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = 0; \
\
    if (!_isEmpty()) \
    { \
        const diff_type c_FirstItIndex{static_cast<diff_type>(*mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + *mIteratorSecondaryCoordinate)}; \
        const diff_type c_SecondItIndex{static_cast<diff_type>(*secondIterator.mIteratorPrimaryCoordinate * secondIterator.mIteratorSecondaryDimension + *secondIterator.mIteratorSecondaryCoordinate)}; \
\
        result = c_FirstItIndex - c_SecondItIndex; \
    } \
\
    return result;

#define REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                     mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || \
                          mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = 0; \
\
    if (!_isEmpty()) \
    { \
        const std::optional<size_type> c_FirstItIndex{mIteratorSecondaryCoordinate.has_value() ? std::optional{*mIteratorPrimaryCoordinate * \
                                                                                                                mIteratorSecondaryDimension + \
                                                                                                               *mIteratorSecondaryCoordinate} \
                                                                                               : std::nullopt}; \
        const std::optional<size_type> c_SecondItIndex{secondIterator.mIteratorSecondaryCoordinate.has_value() ? std::optional{*secondIterator.mIteratorPrimaryCoordinate * \
                                                                                                                                secondIterator.mIteratorSecondaryDimension + \
                                                                                                                               *secondIterator.mIteratorSecondaryCoordinate} \
                                                                                                               : std::nullopt}; \
\
        if (c_FirstItIndex.has_value() && c_SecondItIndex.has_value()) \
        { \
            result = *c_SecondItIndex - *c_FirstItIndex; \
        } \
        else if (!c_FirstItIndex.has_value() && c_SecondItIndex.has_value()) \
        { \
            result = *c_SecondItIndex + 1; \
        } \
        else if (c_FirstItIndex.has_value() && !c_SecondItIndex.has_value()) \
        { \
            result = -1 - *c_FirstItIndex; \
        } \
    } \
\
    return result;


#define FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, firstIterator, secondIterator) \
    CHECK_ERROR_CONDITION((firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr || \
                          (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension || \
                          (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = std::strong_ordering::equal; \
\
    /* both iterators are either empty or not */ \
    if (!(firstIterator)._isEmpty()) \
    { \
        result = *(firstIterator).mIteratorPrimaryCoordinate <=> *(secondIterator).mIteratorPrimaryCoordinate; \
\
        if (std::strong_ordering::equal == result) \
        { \
            result = *(firstIterator).mIteratorSecondaryCoordinate <=> *(secondIterator).mIteratorSecondaryCoordinate; \
        } \
    } \
\
    return result;

#define REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, firstIterator, secondIterator) \
    CHECK_ERROR_CONDITION((firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr || \
                          (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension || \
                          (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = std::strong_ordering::equal; \
\
    /* both iterators are either empty or not */ \
    if (!(firstIterator)._isEmpty()) \
    { \
        result = *(secondIterator).mIteratorPrimaryCoordinate <=> *(firstIterator).mIteratorPrimaryCoordinate; \
\
        if (std::strong_ordering::equal == result) \
        { \
            if ((firstIterator).mIteratorSecondaryCoordinate.has_value() && (secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                /* for reverse iterators greater coordinates mean smaller iterator */ \
                result = *(secondIterator).mIteratorSecondaryCoordinate <=> *(firstIterator).mIteratorSecondaryCoordinate; \
            } \
            else if ((firstIterator).mIteratorSecondaryCoordinate.has_value() && !(secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                result = std::strong_ordering::less; \
            } \
            else if (!(firstIterator).mIteratorSecondaryCoordinate.has_value() && (secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                result = std::strong_ordering::greater; \
            } \
        } \
    } \
\
    return result;

#define NON_DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorRowNr, mIteratorColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorRowsCount != secondIterator.mIteratorRowsCount || \
                          mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorRowNr == secondIterator.mIteratorRowNr && mIteratorColumnNr == secondIterator.mIteratorColumnNr);

#define FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr); \

#define REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr); \

#define FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty(), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_CurrentIndex{static_cast<diff_type>(*mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + *mIteratorSecondaryCoordinate)}; \
\
    CHECK_ERROR_CONDITION(arrayIndex < 0 && std::abs(arrayIndex) > c_CurrentIndex, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + arrayIndex)}; \
    const diff_type c_UpperBound{static_cast<diff_type>(mIteratorPrimaryDimension * mIteratorSecondaryDimension)}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension][c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_CurrentIndex{static_cast<diff_type>(*mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + *mIteratorSecondaryCoordinate)}; \
    const diff_type c_NormalizedIndex = -arrayIndex; \
\
    CHECK_ERROR_CONDITION(c_NormalizedIndex < 0 && std::abs(c_NormalizedIndex) > c_CurrentIndex, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + c_NormalizedIndex)}; \
    const diff_type c_UpperBound{static_cast<diff_type>(mIteratorPrimaryDimension * mIteratorSecondaryDimension)}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension][c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate != mIteratorSecondaryDimension || mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1))) \
    { \
        mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + 1; \
\
        if (mIteratorSecondaryCoordinate == mIteratorSecondaryDimension && mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1)) \
        { \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - mIteratorSecondaryDimension; \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + 1; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate.has_value() || mIteratorPrimaryCoordinate > 0)) \
    { \
        if (mIteratorSecondaryCoordinate > 0) \
        { \
           mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - 1; \
        } \
        else \
        { \
            mIteratorSecondaryCoordinate.reset(); \
        } \
 \
        if (!mIteratorSecondaryCoordinate.has_value() && mIteratorPrimaryCoordinate > 0) \
        { \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - 1; \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - 1; \
        } \
    }

#define FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorPrimaryCoordinate > 0 || mIteratorSecondaryCoordinate > 0)) \
    { \
        if(0 == mIteratorSecondaryCoordinate) \
        { \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - 1; \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - 1; \
        } \
        else \
        { \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - 1; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty()) \
    { \
        if (!mIteratorSecondaryCoordinate.has_value()) \
        { \
            mIteratorSecondaryCoordinate = 0; /* decrement from end iterator */ \
        } \
        else if (mIteratorPrimaryCoordinate < mIteratorPrimaryDimension - 1 || mIteratorSecondaryCoordinate < mIteratorSecondaryDimension - 1) \
        { \
            if(mIteratorSecondaryCoordinate == mIteratorSecondaryDimension - 1) \
            { \
                mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + 1; \
                mIteratorSecondaryCoordinate = 0; \
            } \
            else \
            { \
                mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + 1; \
            } \
        } \
    }


#define CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorPrimaryDimension > 0 && mIteratorSecondaryDimension > 0 && mIteratorPrimaryCoordinate.has_value() && mIteratorSecondaryCoordinate.has_value()); \
    } \
    else \
    { \
        assert(0 == mIteratorPrimaryDimension && 0 == mIteratorSecondaryDimension && !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value()); \
    } \
\
    return !mpIteratorPtr;

#define CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorPrimaryDimension > 0 && mIteratorSecondaryDimension > 0 && mIteratorPrimaryCoordinate.has_value()); \
    } \
    else \
    { \
        assert(0 == mIteratorPrimaryDimension && 0 == mIteratorSecondaryDimension && !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value()); \
    } \
\
    return !mpIteratorPtr;

#define GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, 0};

#define GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, \
                        (mMatrixNrOfRows > 0 ? std::optional{mMatrixNrOfRows - 1} : std::nullopt), (mMatrixNrOfColumns > 0 ? std::optional{mMatrixNrOfColumns - 1} : std::nullopt)};

#define GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// common DIterator/MIterator macros

#define DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mIteratorDiagonalSize, mIteratorDiagonalIndex, Sign, scalarValue) \
    const diff_type c_NormalizedScalarValue = Sign scalarValue; \
    const size_type c_ResultingIndex = (c_NormalizedScalarValue < 0 && std::abs(c_NormalizedScalarValue) > mIteratorDiagonalIndex) ? 0 \
                                                                                                                                   : *mIteratorDiagonalIndex + c_NormalizedScalarValue; \
    mIteratorDiagonalIndex = std::min(c_ResultingIndex, mIteratorDiagonalSize); \
\
    return *this;

#define DIAG_ITERATOR_DO_INCREMENT(mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    if (!_isEmpty() && mIteratorDiagonalIndex < mIteratorDiagonalSize) \
    { \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex + 1; \
    }

#define DIAG_ITERATOR_DO_DECREMENT(mIteratorDiagonalIndex) \
    if (!_isEmpty() && mIteratorDiagonalIndex > 0) \
    { \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex - 1; \
    }

#define DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    /* No overflow occurs as the two operands are automatically converted to diff_type prior to applying difference operation */ \
    return !_isEmpty() ? (static_cast<diff_type>(*mIteratorDiagonalIndex) - static_cast<diff_type>(*secondIterator.mIteratorDiagonalIndex)) : 0; \

#define DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return !_isEmpty() ? *mIteratorDiagonalIndex <=> *secondIterator.mIteratorDiagonalIndex : std::strong_ordering::equal;

#define DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return _isEmpty() || mIteratorDiagonalIndex == secondIterator.mIteratorDiagonalIndex;

#define GET_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - static_cast<diff_type>(mMatrixNrOfRows)) || matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - 1), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, 0}};

#define GET_DIAG_RANDOM_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// specialized ZIterator macros

#define GET_FORWARD_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > 0 ? mMatrixNrOfRows - 1 : 0), mMatrixNrOfColumns};

#define GET_REVERSE_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, std::nullopt};

#define GET_FORWARD_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, 0};

#define GET_REVERSE_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    /* number of columns should be > 0, see above error condition implying matrix should not be empty*/ \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, (mMatrixNrOfColumns > 0 ? mMatrixNrOfColumns - 1 : 0)};

#define GET_FORWARD_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    /* no overflow, number of rows should be greater than 0, see above error condition implying matrix should not be empty*/ \
    if (matrixRowNr < mMatrixNrOfRows - 1) \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr + 1, 0}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, mMatrixNrOfColumns}; \
    } \
\
    return it;

#define GET_REVERSE_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixRowNr > 0) \
    { \
        /* number of columns should be > 0, see above error condition implying matrix should not be empty*/ \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr - 1, (mMatrixNrOfColumns > 0 ? mMatrixNrOfColumns - 1 : 0)}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, std::nullopt}; \
    } \
\
    return it;

// specialized NIterator macros

#define GET_FORWARD_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,  mMatrixNrOfRows, mMatrixNrOfColumns > 0 ? mMatrixNrOfColumns - 1 : 0};

#define GET_REVERSE_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, 0};

#define GET_FORWARD_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, matrixColumnNr};

#define GET_REVERSE_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    /* number of rows should be > 0, see above error condition implying matrix should not be empty */ \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > 0 ? mMatrixNrOfRows - 1 : 0), matrixColumnNr};

#define GET_FORWARD_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    /* no overflow, number of columns should be greater than 0, see above error condition implying matrix should not be empty*/ \
    if (matrixColumnNr < mMatrixNrOfColumns - 1) \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, matrixColumnNr + 1}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows, matrixColumnNr}; \
    } \
\
    return it;

#define GET_REVERSE_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixColumnNr > 0) \
    { \
        /* number of rows should be > 0, see above error condition implying matrix should not be empty */ \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > 0 ? mMatrixNrOfRows - 1 : 0), matrixColumnNr - 1}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, 0}; \
    } \
\
    return it;

// specialized DIterator macros

#define CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr); \
            mIteratorDiagonalIndex = std::min(*matrixRowNr, *matrixColumnNr); \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex + std::min(matrixRowsCount - *matrixRowNr, matrixColumnsCount - *matrixColumnNr); \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
    }

#define CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize = 0; \
        \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr = 1 - static_cast<diff_type>(matrixRowsCount); \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - 1; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                resultingDiagonalSize = diagonalNr < 0 ? std::min<size_type>(matrixRowsCount + diagonalNr, matrixColumnsCount) \
                                                       : std::min<size_type>(matrixColumnsCount - diagonalNr, matrixRowsCount); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        const bool c_AreValidDimensions = matrixRowsCount > 0 && matrixColumnsCount > 0; \
        assert(c_AreValidDimensions); \
\
        if (c_AreValidDimensions) \
        { \
            const bool c_AreRowAndColumnNrValid{(!matrixRowNr.has_value() && !matrixColumnNr.has_value()) || \
                                                (!matrixRowNr.has_value() && matrixColumnNr < matrixColumnsCount - 1) || \
                                                (!matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount - 1) || \
                                                (matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)}; \
            assert(c_AreRowAndColumnNrValid); \
\
            if (c_AreRowAndColumnNrValid) \
            { \
                mpIteratorPtr = pMatrixPtr; \
                mIteratorDiagonalNr = matrixRowNr.has_value() && matrixColumnNr.has_value() ? static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr) \
                                                                                            : matrixRowNr.has_value() ? -1 - static_cast<diff_type>(*matrixRowNr) \
                                                                                                                      : matrixColumnNr.has_value() ? static_cast<diff_type>(*matrixColumnNr) + 1 \
                                                                                                                                                   : 0; \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                mIteratorDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr) \
                                                                              : (mIteratorDiagonalNr <= 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr); \
                mIteratorDiagonalIndex = mIteratorDiagonalNr < 0 ? (matrixColumnNr.has_value() ? mIteratorDiagonalSize - 1 - *matrixColumnNr : mIteratorDiagonalSize) \
                                                                 : (matrixRowNr.has_value() ? mIteratorDiagonalSize - 1 - *matrixRowNr : mIteratorDiagonalSize); \
                nonEmptyIteratorConstructed = true; \
            } \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize = 0; \
        \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr = 1 - static_cast<diff_type>(matrixRowsCount); \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - 1; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                const size_type c_MaxSize{std::max(matrixRowsCount, matrixColumnsCount)}; \
                const diff_type c_Delta{static_cast<diff_type>(matrixRowsCount) - static_cast<diff_type>(matrixColumnsCount)}; \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                resultingDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr) \
                                                                              : (mIteratorDiagonalNr <= 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
    }

#define FORWARD_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(*mIteratorDiagonalIndex + std::abs(mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? *mIteratorDiagonalIndex : static_cast<size_type>(*mIteratorDiagonalIndex + mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1 + std::abs(mIteratorDiagonalNr)) \
                                                            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1)}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1) \
                                                               : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1 + mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(*mIteratorDiagonalIndex + std::abs(mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? *mIteratorDiagonalIndex : static_cast<size_type>(*mIteratorDiagonalIndex + mIteratorDiagonalNr)}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1 + std::abs(mIteratorDiagonalNr)) \
                                                            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1)}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1) \
                                                               : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1 + mIteratorDiagonalNr)}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < 0 && std::abs(arrayIndex) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(*mIteratorDiagonalIndex + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(c_ResultingDiagonalIndex + std::abs(mIteratorDiagonalNr)) : c_ResultingDiagonalIndex}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? c_ResultingDiagonalIndex : static_cast<size_type>(c_ResultingDiagonalIndex + mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < 0 && std::abs(arrayIndex) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(*mIteratorDiagonalIndex + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1 + std::abs(mIteratorDiagonalNr)) \
                                                             : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1)}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1) \
                                                                : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1 + mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, 0}};

#define GET_END_DITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - 1), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? static_cast<size_type>(std::abs(matrixDiagonalNr)) : size_type{0}}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr < 0 ? size_type{0} : static_cast<size_type>(matrixDiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error condition) */ \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}}; \

#define GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr)}; \
\
    const size_type c_BeginRowNr{c_DiagonalNr < 0 ? static_cast<size_type>(std::abs(c_DiagonalNr)) : size_type{0}}; \
    const size_type c_BeginColumnNr{c_DiagonalNr < 0 ? size_type{0} : static_cast<size_type>(c_DiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error conditions) */ \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(iteratorDiagonalNr < (1 - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          iteratorDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - 1), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{iteratorDiagonalNr < 0 ? static_cast<size_type>(std::abs(iteratorDiagonalNr)) : size_type{0}}; \
    const size_type c_BeginColumnNr{iteratorDiagonalNr < 0 ? size_type{0} : static_cast<size_type>(iteratorDiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error condition) */ \
    const size_type c_DiagonalSize{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};

#define CHECK_DITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorDiagonalSize > 0 && mIteratorDiagonalIndex.has_value()); \
    } \
    else \
    { \
        assert(0 == mIteratorDiagonalNr && 0 == mIteratorDiagonalSize && !mIteratorDiagonalIndex.has_value()); \
    } \
\
    return !mpIteratorPtr;

// specialized MIterator macros

#define CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = static_cast<diff_type>(matrixColumnsCount - *matrixColumnNr) - static_cast<diff_type>(*matrixRowNr) - 1; \
            mIteratorDiagonalIndex = std::min<size_type>(*matrixRowNr, matrixColumnsCount - *matrixColumnNr - 1); \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex + std::min<size_type>(matrixRowsCount - *matrixRowNr, *matrixColumnNr + 1); \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
        mIteratorColumnsCount = 0; \
    }

#define CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize = 0; \
        \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr = 1 - static_cast<diff_type>(matrixRowsCount); \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - 1; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                resultingDiagonalSize = diagonalNr < 0 ? std::min<size_type>(matrixRowsCount + diagonalNr, matrixColumnsCount) \
                                                       : std::min<size_type>(matrixColumnsCount - diagonalNr, matrixRowsCount); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
        mIteratorColumnsCount = 0; \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && matrixColumnNr.has_value() && matrixColumnNr <= matrixColumnsCount) \
        { \
            const bool c_IsValidRowNr = (!matrixRowNr.has_value() && matrixColumnNr > 0) || \
                                         (matrixRowNr.has_value() && ((matrixRowNr < matrixRowsCount - 1 && matrixColumnNr == matrixColumnsCount) || \
                                                                      (matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount))); \
            assert(c_IsValidRowNr); \
\
            if (c_IsValidRowNr) \
            { \
                mpIteratorPtr = pMatrixPtr; \
                mIteratorDiagonalNr = matrixRowNr.has_value() ? static_cast<diff_type>(matrixColumnsCount - *matrixColumnNr) - static_cast<diff_type>(*matrixRowNr) - 1 \
                                                              : static_cast<diff_type>(matrixColumnsCount - *matrixColumnNr); \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                mIteratorDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr) \
                                                                              : (mIteratorDiagonalNr <= 0 ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr); \
                mIteratorDiagonalIndex = mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - matrixColumnsCount + *matrixColumnNr \
                                                                 : matrixRowNr.has_value() ? mIteratorDiagonalSize - 1 - *matrixRowNr \
                                                                                           : mIteratorDiagonalSize; \
                mIteratorColumnsCount = matrixColumnsCount; \
                nonEmptyIteratorConstructed = true; \
            } \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
        mIteratorColumnsCount = 0; \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize = 0; \
        \
        if (matrixRowsCount > 0 && matrixColumnsCount > 0 && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr = 1 - static_cast<diff_type>(matrixRowsCount); \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - 1; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                resultingDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (diagonalNr < 0 ? matrixRowsCount + diagonalNr : matrixColumnsCount - diagonalNr) \
                                                                              : (diagonalNr <= 0 ? matrixRowsCount + diagonalNr : matrixColumnsCount - diagonalNr); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = 0; \
        mIteratorDiagonalSize = 0; \
        mIteratorColumnsCount = 0; \
    }

#define FORWARD_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(*mIteratorDiagonalIndex + std::abs(mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - 1) \
                                                               : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - 1 - mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1  + std::abs(mIteratorDiagonalNr)) \
                                                            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1)}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex) \
                                                               : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex - mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(*mIteratorDiagonalIndex + std::abs(mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - 1) \
                                                               : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - 1 - mIteratorDiagonalNr)}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1 + std::abs(mIteratorDiagonalNr)) \
                                                            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - 1)}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex) \
                                                               : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex - mIteratorDiagonalNr)}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < 0 && std::abs(arrayIndex) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(*mIteratorDiagonalIndex + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(c_ResultingDiagonalIndex + std::abs(mIteratorDiagonalNr)) : c_ResultingDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - 1) \
                                                                : static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - 1 - mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < 0 && std::abs(arrayIndex) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(*mIteratorDiagonalIndex + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1 + std::abs(mIteratorDiagonalNr)) \
                                                             : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1)}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex) \
                                                                : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex - mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(mMatrixNrOfColumns - matrixColumnNr - 1) - static_cast<diff_type>(matrixRowNr)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, 0}};

#define GET_END_MITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - 1), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? static_cast<size_type>(std::abs(matrixDiagonalNr)) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */ \
    /* of matrix columns if the matrix is not empty (if empty above error condition triggers) */ \
    const size_type c_BeginColumnNr{matrixDiagonalNr <= 0 ? static_cast<size_type>(mMatrixNrOfColumns - 1) : static_cast<size_type>(mMatrixNrOfColumns - 1 - matrixDiagonalNr)}; \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + 1))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}};

#define GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(mMatrixNrOfColumns - matrixColumnNr - 1) - static_cast<diff_type>(matrixRowNr)}; \
\
    const size_type c_BeginRowNr{c_DiagonalNr < 0 ? static_cast<size_type>(std::abs(c_DiagonalNr)) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */ \
    /* of matrix columns if the matrix is not empty (if empty above error conditions trigger) */ \
    const size_type c_BeginColumnNr{c_DiagonalNr <= 0 ? static_cast<size_type>(mMatrixNrOfColumns - 1) : static_cast<size_type>(mMatrixNrOfColumns - 1 - c_DiagonalNr)}; \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + 1))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(iteratorDiagonalNr < (1 - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          iteratorDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - 1), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{iteratorDiagonalNr < 0 ? static_cast<size_type>(std::abs(iteratorDiagonalNr)) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the */ \
    /* number of matrix columns if the matrix is not empty (if empty above error condition triggers) */ \
    const size_type c_BeginColumnNr{iteratorDiagonalNr <= 0 ? static_cast<size_type>(mMatrixNrOfColumns - 1) : static_cast<size_type>(mMatrixNrOfColumns - 1 - iteratorDiagonalNr)}; \
\
    /* no overflow as for negative diagonals the diagonal number (in absolute value) should be strictly smaller than the */ \
    /* number of matrix rows if the matrix is not empty (if empty above error condition triggers */ \
    const size_type c_DiagonalSize {std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + 1))}; \
\
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};

#define CHECK_MITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorNrOfColumns) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorDiagonalSize > 0 && mIteratorDiagonalIndex.has_value() && mIteratorNrOfColumns > 0); \
    } \
    else \
    { \
        assert(0 == mIteratorDiagonalNr && 0 == mIteratorDiagonalSize && !mIteratorDiagonalIndex.has_value() && 0 == mIteratorNrOfColumns); \
    } \
\
    return !mpIteratorPtr;

#endif // ITERATORUTILS_H
