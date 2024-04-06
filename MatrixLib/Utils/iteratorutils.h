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
    SizeType getRowNr() const; \
    SizeType getColumnNr() const; \
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

#define COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(SizeType) \
    SizeType getDiagonalNr() const; \
    SizeType getDiagonalIndex() const;

#define COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(IterableType) \
    void _increment(); \
    void _decrement(); \
\
    IterableType** m_pMatrixPtr;

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, SizeType rowNr, SizeType columnNr); \
\
    SizeType m_RowNr; \
    SizeType m_ColumnNr; \
    SizeType m_NrOfMatrixRows; \
    SizeType m_NrOfMatrixColumns;

#define COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, SizeType first, SizeType second, bool isRelative = false); \
\
    size_type m_DiagonalIndex;    /* relative index within diagonal */ \
    size_type m_DiagonalNr;   /* index of the diagonal within matrix */ \
    size_type m_DiagonalSize;     /* number of elements contained within diagonal */

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

#define CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(mPrimaryDimension, mSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    if (matrixPrimaryCoordinate < 0 || matrixSecondaryCoordinate < 0 || matrixPrimaryCoordinate >= mPrimaryDimension || matrixSecondaryCoordinate > mSecondaryDimension || \
        (matrixPrimaryCoordinate < mPrimaryDimension - 1 && matrixSecondaryCoordinate == mSecondaryDimension)) \
    { \
        mIteratorPrimaryCoordinate = -1; \
        mIteratorSecondaryCoordinate = -1; \
    } \
    else \
    { \
        mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
        mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
    }

#define CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    if (matrixPrimaryCoordinate < 0 || matrixSecondaryCoordinate < -1 || matrixPrimaryCoordinate >= mIteratorPrimaryDimension || matrixSecondaryCoordinate >= mIteratorSecondaryDimension || \
        (matrixPrimaryCoordinate < mIteratorPrimaryDimension - 1 && matrixSecondaryCoordinate == mIteratorSecondaryDimension)) \
    { \
        mIteratorPrimaryCoordinate = -1; \
        mIteratorSecondaryCoordinate = -1; \
    } \
    else \
    { \
        mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
        mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
    }

#define FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + mIteratorSecondaryCoordinate}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorPrimaryDimension * mIteratorSecondaryDimension}; \
\
        mIteratorPrimaryCoordinate = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorPrimaryDimension - 1 : c_ResultingIndex / mIteratorSecondaryDimension; \
        mIteratorSecondaryCoordinate = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorSecondaryDimension : c_ResultingIndex % mIteratorSecondaryDimension; \
    } \
\
    return *this;

#define REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + mIteratorSecondaryCoordinate}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorPrimaryDimension * mIteratorSecondaryDimension}; \
\
        mIteratorPrimaryCoordinate = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorPrimaryDimension - 1 : c_ResultingIndex / mIteratorSecondaryDimension; \
        mIteratorSecondaryCoordinate = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? mIteratorSecondaryDimension - 1 : c_ResultingIndex % mIteratorSecondaryDimension; \
    } \
\
    return *this;

#define FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItIndex{mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + mIteratorSecondaryCoordinate}; \
    const size_type c_SecondItIndex{secondIterator.mIteratorPrimaryCoordinate * secondIterator.mIteratorSecondaryDimension + secondIterator.mIteratorSecondaryCoordinate}; \
\
    return (c_FirstItIndex - c_SecondItIndex);

#define REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItIndex{mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + mIteratorSecondaryCoordinate}; \
    const size_type c_SecondItIndex{secondIterator.mIteratorPrimaryCoordinate * secondIterator.mIteratorSecondaryDimension + secondIterator.mIteratorSecondaryCoordinate}; \
\
    return (c_SecondItIndex - c_FirstItIndex);


#define NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, firstIterator, secondIterator) \
    CHECK_ERROR_CONDITION((firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr || (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension || (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result{(firstIterator).mIteratorPrimaryCoordinate <=> (secondIterator).mIteratorPrimaryCoordinate}; \
\
    if (0 == result) \
    { \
        result = (firstIterator).mIteratorSecondaryCoordinate <=> (secondIterator).mIteratorSecondaryCoordinate; \
    } \
\
    return result;

#define NON_DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorRowNr, mIteratorColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorRowNr == secondIterator.mIteratorRowNr && mIteratorColumnNr == secondIterator.mIteratorColumnNr);

#define FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(mIteratorSecondaryCoordinate == mIteratorSecondaryDimension || mIteratorSecondaryDimension == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorRowNr][mIteratorColumnNr];

#define REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(mIteratorSecondaryCoordinate == -1 || mIteratorSecondaryDimension == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorRowNr][mIteratorColumnNr];

#define FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(mIteratorSecondaryCoordinate == mIteratorSecondaryDimension || mIteratorSecondaryDimension == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorRowNr] + mIteratorColumnNr); \

#define REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(mIteratorSecondaryCoordinate == -1 || mIteratorSecondaryDimension == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorRowNr] + mIteratorColumnNr); \

#define NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, FirstOperator, SecondOperator, arrayIndex) \
    const size_type c_CurrentIndex{mIteratorPrimaryCoordinate * mIteratorSecondaryDimension + mIteratorSecondaryCoordinate}; \
    const size_type c_ResultingIndex{c_CurrentIndex Sign arrayIndex}; \
    const size_type c_UpperBound{mIteratorPrimaryDimension * mIteratorSecondaryDimension}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension][c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mIteratorSecondaryCoordinate != mIteratorSecondaryDimension || mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1)) \
    { \
        ++mIteratorSecondaryCoordinate; \
        if (mIteratorSecondaryCoordinate == mIteratorSecondaryDimension && (mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1))) \
        { \
            mIteratorSecondaryCoordinate = mIteratorSecondaryCoordinate - mIteratorSecondaryDimension; \
            ++mIteratorPrimaryCoordinate; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mIteratorSecondaryCoordinate != -1 || mIteratorPrimaryCoordinate != 0) \
    { \
        --mIteratorSecondaryCoordinate; \
        if (mIteratorSecondaryCoordinate < 0 && (mIteratorPrimaryCoordinate != 0)) \
        { \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - 1; \
            --mIteratorPrimaryCoordinate; \
        } \
    }

#define FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mIteratorPrimaryCoordinate > 0 || mIteratorSecondaryCoordinate > 0) \
    { \
        if(mIteratorSecondaryCoordinate == 0) \
        { \
            --mIteratorPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - 1; \
        } \
        else \
        { \
            --mIteratorSecondaryCoordinate; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mIteratorPrimaryCoordinate < mIteratorPrimaryDimension - 1 || mIteratorSecondaryCoordinate < mIteratorSecondaryDimension - 1) \
    { \
        if(mIteratorSecondaryCoordinate == mIteratorSecondaryDimension - 1) \
        { \
            ++mIteratorPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = 0; \
        } \
        else \
        { \
            ++mIteratorSecondaryCoordinate; \
        } \
    }

#define GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, 0};

#define GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - 1, mMatrixNrOfColumns - 1};

#define GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

#define GET_NON_DIAG_ITERATOR_BY_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixPrimaryDimension, mMatrixSecondaryDimension, FirstOperator, SecondOperator, arrayIndex) \
    CHECK_ERROR_CONDITION(arrayIndex < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(arrayIndex >= mMatrixPrimaryDimension * mMatrixSecondaryDimension, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, arrayIndex FirstOperator mMatrixSecondaryDimension, arrayIndex SecondOperator mMatrixSecondaryDimension};

// common DIterator/MIterator macros

#define DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mIteratorDiagonalSize, mIteratorDiagonalIndex, Sign, scalarValue) \
    const size_type c_ResultingIndex = mIteratorDiagonalIndex Sign scalarValue; \
    mIteratorDiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > mIteratorDiagonalSize ? mIteratorDiagonalSize : c_ResultingIndex; \
\
    return *this;

#define DIAG_ITERATOR_DO_INCREMENT(mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    if (mIteratorDiagonalIndex < mIteratorDiagonalSize) \
    { \
        ++mIteratorDiagonalIndex; \
    }

#define DIAG_ITERATOR_DO_DECREMENT(mIteratorDiagonalIndex) \
    if (mIteratorDiagonalIndex > 0) \
    { \
        --mIteratorDiagonalIndex; \
    }

#define DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorDiagonalIndex - secondIterator.mIteratorDiagonalIndex); \

#define DIAG_ITERATOR_COMPARE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return mIteratorDiagonalIndex Operator secondIterator.mIteratorDiagonalIndex;

#define GET_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr, 0, true};

// specialized ZIterator macros

#define GET_FORWARD_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - 1, mMatrixNrOfColumns};

#define GET_REVERSE_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, -1};

#define GET_FORWARD_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, 0};

#define GET_REVERSE_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, mMatrixNrOfColumns - 1};

#define GET_FORWARD_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
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
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixRowNr > 0) \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr - 1, mMatrixNrOfColumns - 1}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, -1}; \
    } \
\
    return it;

// specialized NIterator macros

#define GET_FORWARD_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,  mMatrixNrOfRows, mMatrixNrOfColumns - 1};

#define GET_REVERSE_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, -1, 0};

#define GET_FORWARD_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, 0, matrixColumnNr};

#define GET_REVERSE_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - 1, matrixColumnNr};

#define GET_FORWARD_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
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
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixColumnNr > 0) \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows - 1, matrixColumnNr - 1}; \
    } \
    else \
    { \
        it = IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, -1, 0}; \
    } \
\
    return it;

// specialized DIterator macros

#define CONSTRUCT_FORWARD_DITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, matrixRowsCount, matrixColumnsCount, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        /* firstParam and secondParam are interpreted as diagonal number and relative arrayIndex within diagonal */ \
        mIteratorDiagonalNr = firstParam; \
        mIteratorDiagonalIndex = secondParam; \
        const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
        const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - c_IteratorRowNr, matrixColumnsCount - c_IteratorColumnNr); \
    } \
    else \
    { \
        /* firstParam and secondParam are interpreted as (x, y) coordinates */ \
        mIteratorDiagonalNr = secondParam - firstParam; \
        mIteratorDiagonalIndex = std::min(firstParam, secondParam); \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - firstParam, matrixColumnsCount - secondParam); \
    }

#define CONSTRUCT_REVERSE_DITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, matrixRowsCount, matrixColumnsCount, firstParam, secondParam, relativeParamsUsed) \
    const size_type c_NrOfRows{matrixRowsCount}; \
    const size_type c_NrOfColumns{matrixColumnsCount}; \
    const size_type c_MaxSize{std::max(c_NrOfRows, c_NrOfColumns)}; \
    const difference_type c_Delta{c_NrOfRows - c_NrOfColumns}; \
\
    mIteratorDiagonalNr = relativeParamsUsed ? firstParam : secondParam - firstParam; \
    mIteratorDiagonalSize = (c_Delta >= 0) ? (mIteratorDiagonalNr < 0 ? c_MaxSize + mIteratorDiagonalNr : c_MaxSize - mIteratorDiagonalNr - c_Delta) \
                                    : (mIteratorDiagonalNr <= 0 ? c_MaxSize + mIteratorDiagonalNr + c_Delta : c_MaxSize - mIteratorDiagonalNr); \
    mIteratorDiagonalIndex = relativeParamsUsed ? secondParam : (mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - secondParam : mIteratorDiagonalSize - 1 - firstParam);

#define FORWARD_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - mIteratorDiagonalIndex - 1 : mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - mIteratorDiagonalIndex - 1 : mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    const size_type c_ResultingDiagonalIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex < 0 || c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? c_ResultingDiagonalIndex - mIteratorDiagonalNr : c_ResultingDiagonalIndex}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? c_ResultingDiagonalIndex : c_ResultingDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    const size_type c_ResultingDiagonalIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex < 0 || c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - c_ResultingDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1 : mIteratorDiagonalSize - 1 - c_ResultingDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagonalNr{matrixColumnNr - matrixRowNr}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, c_DiagonalNr, 0, true};

#define GET_END_DITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? -matrixDiagonalNr : 0}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr < 0 ? 0 : matrixDiagonalNr}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr, c_EndDiagonalIndex, true};

#define GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagonalNr{matrixColumnNr - matrixRowNr}; \
    const size_type c_BeginRowNr{c_DiagonalNr < 0 ? -c_DiagonalNr : 0}; \
    const size_type c_BeginColumnNr{c_DiagonalNr < 0 ? 0 : c_DiagonalNr}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, c_DiagonalNr, c_EndDiagonalIndex, true};

#define GET_RANDOM_DITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        CHECK_ERROR_CONDITION(firstParam < (1 - mMatrixNrOfRows) || firstParam > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
\
        const size_type c_BeginRowNr{firstParam < 0 ? -firstParam : 0}; \
        const size_type c_BeginColumnNr{firstParam < 0 ? 0 : firstParam}; \
        const size_type c_DiagonalSize {std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
        CHECK_ERROR_CONDITION(secondParam >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
    } \
    else \
    { \
        CHECK_ERROR_CONDITION(firstParam < 0 || secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
        CHECK_ERROR_CONDITION(firstParam >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
    } \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed};

// specialized MIterator macros

#define CONSTRUCT_FORWARD_MITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, matrixRowsCount, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        /* firstParam and secondParam are interpreted as diagonal number and relative arrayIndex within diagonal */ \
        mIteratorDiagonalNr = firstParam; \
        mIteratorDiagonalIndex = secondParam; \
        const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
        const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - c_IteratorRowNr, c_IteratorColumnNr + 1); \
    } \
    else \
    { \
        /* firstParam and secondParam are interpreted as (x, y) coordinates */ \
        mIteratorDiagonalNr = mIteratorColumnsCount - firstParam - secondParam - 1; \
        mIteratorDiagonalIndex = std::min(firstParam, mIteratorColumnsCount - secondParam - 1); \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - firstParam, secondParam + 1); \
    }

#define CONSTRUCT_REVERSE_MITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, matrixRowsCount, firstParam, secondParam, relativeParamsUsed) \
    const size_type c_MaxSize{std::max(matrixRowsCount, mIteratorColumnsCount)}; \
    const difference_type c_Delta{matrixRowsCount - mIteratorColumnsCount}; \
\
    mIteratorDiagonalNr = relativeParamsUsed ? firstParam : mIteratorColumnsCount - firstParam - secondParam - 1; \
    mIteratorDiagonalSize = (c_Delta >= 0) ? (mIteratorDiagonalNr < 0 ? c_MaxSize + mIteratorDiagonalNr : c_MaxSize - mIteratorDiagonalNr - c_Delta) \
                                    : (mIteratorDiagonalNr <= 0 ? c_MaxSize + mIteratorDiagonalNr + c_Delta : c_MaxSize - mIteratorDiagonalNr); \
    mIteratorDiagonalIndex = relativeParamsUsed ? secondParam : (mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - mIteratorColumnsCount + secondParam : mIteratorDiagonalSize - 1 - firstParam);

#define FORWARD_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex : mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex - mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex : mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex - mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    const size_type c_ResultingDiagonalIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex < 0 || c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? c_ResultingDiagonalIndex - mIteratorDiagonalNr : c_ResultingDiagonalIndex}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - c_ResultingDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - c_ResultingDiagonalIndex - 1}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    const size_type c_ResultingDiagonalIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex < 0 || c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - c_ResultingDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - c_ResultingDiagonalIndex - 1}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex : mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex - mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagonalNr{mMatrixNrOfColumns - matrixRowNr - matrixColumnNr - 1}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, c_DiagonalNr, 0, true};

#define GET_END_MITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? -matrixDiagonalNr : 0}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr <= 0 ? mMatrixNrOfColumns - 1 : mMatrixNrOfColumns - matrixDiagonalNr - 1}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, c_BeginColumnNr + 1)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr, c_EndDiagonalIndex, true};

#define GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagonalNr{mMatrixNrOfColumns - matrixRowNr - matrixColumnNr - 1}; \
    const size_type c_BeginRowNr{c_DiagonalNr < 0 ? -c_DiagonalNr : 0}; \
    const size_type c_BeginColumnNr{c_DiagonalNr <= 0 ? mMatrixNrOfColumns - 1 : mMatrixNrOfColumns - c_DiagonalNr - 1}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, c_BeginColumnNr + 1)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, c_DiagonalNr, c_EndDiagonalIndex, true};

#define GET_RANDOM_MITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        CHECK_ERROR_CONDITION(firstParam < (1 - mMatrixNrOfRows) || firstParam > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
\
        const size_type c_BeginRowNr{firstParam < 0 ? -firstParam : 0}; \
        const size_type c_BeginColumnNr{firstParam <= 0 ? mMatrixNrOfColumns - 1 : mMatrixNrOfColumns - firstParam - 1}; \
        const size_type c_DiagonalSize {std::min(mMatrixNrOfRows - c_BeginRowNr, c_BeginColumnNr + 1)}; \
\
        CHECK_ERROR_CONDITION(secondParam >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
    } \
    else \
    { \
        CHECK_ERROR_CONDITION(firstParam < 0 || secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
        CHECK_ERROR_CONDITION(firstParam >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
    } \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed};

#endif // ITERATORUTILS_H
