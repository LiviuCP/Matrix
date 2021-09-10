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
    IteratorType operator++(); \
    IteratorType operator++(int unused); \
    IteratorType operator--(); \
    IteratorType operator--(int unused); \
\
    IteratorType operator+(DifferenceType offset); \
    IteratorType operator-(DifferenceType offset); \
\
    void operator+=(DifferenceType offset); \
    void operator-=(DifferenceType offset); \
\
    DifferenceType operator-(const IteratorType& it) const; \
\
    bool operator==(const IteratorType& it) const; \
    bool operator!=(const IteratorType& it) const; \
    bool operator<(const IteratorType& it) const; \
    bool operator<=(const IteratorType& it) const; \
    bool operator>(const IteratorType& it) const; \
    bool operator>=(const IteratorType& it) const; \
\
    /* This function was created mainly for testing purposes although it can be used in "production" as well. */ \
    /* However it's best to assume an iterator has become invalid if matrix has been changed structure-wise (resize, assignments, clear, row/column insertion, etc) */ \
    bool isValidWithMatrix(const Matrix<IterableType>& matrix) const; \
\
    SizeType getCurrentRowNr() const; \
    SizeType getCurrentColumnNr() const; \

#define COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = IterableType&; \
\
    IterableType& operator*(); \
    IterableType* operator->(); \
    IterableType& operator[](DifferenceType index);

#define COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = const IterableType&; \
\
    const IterableType& operator*() const; \
    const IterableType* operator->() const; \
    const IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType) \
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix */ \
    IteratorType();

#define COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(SizeType) \
    SizeType getDiagonalNr() const; \
    SizeType getDiagonalIndex() const;

#define COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(IterableType) \
    void _increment(); \
    void _decrement(); \
\
    IterableType** m_pMatrixPtr;

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(const Matrix<IterableType>& matrix, SizeType currentRowNr, SizeType currentColumnNr); \
\
    SizeType m_CurrentRowNr; \
    SizeType m_CurrentColumnNr; \
    SizeType m_NrOfMatrixRows; \
    SizeType m_NrOfMatrixColumns;

#define COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(const Matrix<IterableType>& matrix, SizeType first, SizeType second, bool isRelative = false); \
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

#define NON_DIAG_ITERATOR_CHECK_EQUAL(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentRowNr == secondIterator.mIteratorCurrentRowNr && mIteratorCurrentColumnNr == secondIterator.mIteratorCurrentColumnNr);

#define NON_DIAG_ITERATOR_CHECK_DIFFERENT(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentRowNr != secondIterator.mIteratorCurrentRowNr || mIteratorCurrentColumnNr != secondIterator.mIteratorCurrentColumnNr);

#define NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, pMatrixPtr, matrixRowsCount, matrixColumnsCount) \
    return (mpIteratorPtr == pMatrixPtr && mIteratorRowsCount == matrixRowsCount && mIteratorColumnsCount == matrixColumnsCount);

#define FORWARD_NON_DIAG_ITERATOR_BEGIN(IteratorType) \
    return IteratorType{*this, 0, 0};

#define REVERSE_NON_DIAG_ITERATOR_BEGIN(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{*this, mMatrixNrOfRows - 1, mMatrixNrOfColumns - 1};

// common DIterator/MIterator macros

#define DIAG_ITERATOR_ADD_SCALAR(IteratorType, mIteratorDiagonalSize, mIteratorDiagonalIndex, Sign, scalarValue) \
    IteratorType it{*this}; \
    const size_type c_ResultingIndex = it.mIteratorDiagonalIndex Sign scalarValue; \
    it.mIteratorDiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.mIteratorDiagonalSize ? it.mIteratorDiagonalSize : c_ResultingIndex; \
\
    return it;

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

#define DIAG_ITERATOR_DIAG_BEGIN(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
    return IteratorType{*this, matrixDiagonalNr, 0, true};

// specialized ZIterator macros

#define CONSTRUCT_FORWARD_ZITERATOR(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, matrixRowNr, matrixColumnNr) \
    if (matrixRowNr < 0 || matrixColumnNr < 0 || matrixRowNr >= mIteratorRowsCount || matrixColumnNr > mIteratorColumnsCount || \
        (matrixRowNr < mIteratorRowsCount - 1 && matrixColumnNr == mIteratorColumnsCount)) \
    { \
        mIteratorCurrentRowNr = -1; \
        mIteratorCurrentColumnNr = -1; \
    } \
    else \
    { \
        mIteratorCurrentRowNr = matrixRowNr; \
        mIteratorCurrentColumnNr = matrixColumnNr; \
    }

#define CONSTRUCT_REVERSE_ZITERATOR(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, matrixRowNr, matrixColumnNr) \
    if (matrixRowNr < 0 || matrixColumnNr < -1 || matrixRowNr >= mIteratorRowsCount || matrixColumnNr >= mIteratorColumnsCount || \
        (matrixRowNr < mIteratorRowsCount - 1 && matrixColumnNr == mIteratorColumnsCount)) \
    { \
        mIteratorCurrentRowNr = -1; \
        mIteratorCurrentColumnNr = -1; \
    } \
    else \
    { \
        mIteratorCurrentRowNr = matrixRowNr; \
        mIteratorCurrentColumnNr = matrixColumnNr; \
    }

#define FORWARD_ZITERATOR_ADD_SCALAR(IteratorType, mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, scalarValue) \
    IteratorType it{}; \
\
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorCurrentRowNr * mIteratorColumnsCount + mIteratorCurrentColumnNr}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
\
        it.mpIteratorPtr = mpIteratorPtr; \
        it.mIteratorRowsCount = mIteratorRowsCount; \
        it.mIteratorColumnsCount = mIteratorColumnsCount; \
        it.mIteratorCurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorRowsCount - 1 : c_ResultingIndex / mIteratorColumnsCount; \
        it.mIteratorCurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorColumnsCount : c_ResultingIndex % mIteratorColumnsCount; \
    } \
\
    return it;

#define REVERSE_ZITERATOR_ADD_SCALAR(IteratorType, mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, scalarValue) \
    IteratorType it{}; \
\
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorCurrentRowNr * mIteratorColumnsCount + mIteratorCurrentColumnNr}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
\
        it.mpIteratorPtr = mpIteratorPtr; \
        it.mIteratorRowsCount = mIteratorRowsCount; \
        it.mIteratorColumnsCount = mIteratorColumnsCount; \
        it.mIteratorCurrentRowNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorRowsCount - 1 : c_ResultingIndex / mIteratorColumnsCount; \
        it.mIteratorCurrentColumnNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? mIteratorColumnsCount-1 : c_ResultingIndex % mIteratorColumnsCount; \
    } \
\
    return it;

#define FORWARD_ZITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItCurrentIndex{mIteratorCurrentRowNr * mIteratorColumnsCount + mIteratorCurrentColumnNr}; \
    const size_type c_SecondItCurrentIndex{secondIterator.mIteratorCurrentRowNr * secondIterator.mIteratorColumnsCount + secondIterator.mIteratorCurrentColumnNr}; \
\
    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);

#define REVERSE_ZITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItCurrentIndex{mIteratorCurrentRowNr * mIteratorColumnsCount + mIteratorCurrentColumnNr}; \
    const size_type c_SecondItCurrentIndex{secondIterator.mIteratorCurrentRowNr * it.mIteratorColumnsCount + secondIterator.mIteratorCurrentColumnNr}; \
\
    return (c_SecondItCurrentIndex - c_FirstItCurrentIndex);

#define FORWARD_ZITERATOR_CHECK_STRICT_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentRowNr Operator secondIterator.mIteratorCurrentRowNr) || \
           (mIteratorCurrentRowNr == secondIterator.mIteratorCurrentRowNr && mIteratorCurrentColumnNr Operator secondIterator.mIteratorCurrentColumnNr);

#define REVERSE_ZITERATOR_CHECK_STRICT_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (secondIterator.mIteratorCurrentRowNr Operator mIteratorCurrentRowNr) || \
           (secondIterator.mIteratorCurrentRowNr == mIteratorCurrentRowNr && secondIterator.mIteratorCurrentColumnNr Operator mIteratorCurrentColumnNr);

#define FORWARD_ZITERATOR_CHECK_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentRowNr Operator secondIterator.mIteratorCurrentRowNr) || \
           (mIteratorCurrentRowNr == secondIterator.mIteratorCurrentRowNr && (mIteratorCurrentColumnNr Operator secondIterator.mIteratorCurrentColumnNr || mIteratorCurrentColumnNr == secondIterator.mIteratorCurrentColumnNr));

#define REVERSE_ZITERATOR_CHECK_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (secondIterator.mIteratorCurrentRowNr Operator mIteratorCurrentRowNr) || \
           (secondIterator.mIteratorCurrentRowNr == mIteratorCurrentRowNr && (secondIterator.mIteratorCurrentColumnNr Operator mIteratorCurrentColumnNr || secondIterator.mIteratorCurrentColumnNr == mIteratorCurrentColumnNr));

#define FORWARD_ZITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentColumnNr == mIteratorColumnsCount || mIteratorColumnsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorCurrentRowNr][mIteratorCurrentColumnNr];

#define REVERSE_ZITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentColumnNr == -1 || mIteratorColumnsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorCurrentRowNr][mIteratorCurrentColumnNr];

#define FORWARD_ZITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentColumnNr == mIteratorColumnsCount || mIteratorColumnsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorCurrentRowNr] + mIteratorCurrentColumnNr); \

#define REVERSE_ZITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentColumnNr == -1 || mIteratorColumnsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorCurrentRowNr] + mIteratorCurrentColumnNr); \

#define ZITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, arrayIndex) \
    const size_type c_CurrentIndex{mIteratorCurrentRowNr * mIteratorColumnsCount + mIteratorCurrentColumnNr}; \
    const size_type c_ResultingIndex{c_CurrentIndex Sign arrayIndex}; \
    const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex / mIteratorColumnsCount][c_ResultingIndex % mIteratorColumnsCount];

#define FORWARD_ZITERATOR_DO_INCREMENT(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentColumnNr != mIteratorColumnsCount || mIteratorCurrentRowNr != (mIteratorRowsCount - 1)) \
    { \
        ++mIteratorCurrentColumnNr; \
        if (mIteratorCurrentColumnNr == mIteratorColumnsCount && (mIteratorCurrentRowNr != (mIteratorRowsCount - 1))) \
        { \
            mIteratorCurrentColumnNr = mIteratorCurrentColumnNr - mIteratorColumnsCount; \
            ++mIteratorCurrentRowNr; \
        } \
    }

#define REVERSE_ZITERATOR_DO_INCREMENT(mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentColumnNr != -1 || mIteratorCurrentRowNr != 0) \
    { \
        --mIteratorCurrentColumnNr; \
        if (mIteratorCurrentColumnNr < 0 && (mIteratorCurrentRowNr != 0)) \
        { \
            mIteratorCurrentColumnNr = mIteratorColumnsCount - 1; \
            --mIteratorCurrentRowNr; \
        } \
    }

#define FORWARD_ZITERATOR_DO_DECREMENT(mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentRowNr > 0 || mIteratorCurrentColumnNr > 0) \
    { \
        if(mIteratorCurrentColumnNr == 0) \
        { \
            --mIteratorCurrentRowNr; \
            mIteratorCurrentColumnNr = mIteratorColumnsCount - 1; \
        } \
        else \
        { \
            --mIteratorCurrentColumnNr; \
        } \
    }

#define REVERSE_ZITERATOR_DO_DECREMENT(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentRowNr < mIteratorRowsCount - 1 || mIteratorCurrentColumnNr < mIteratorColumnsCount - 1) \
    { \
        if(mIteratorCurrentColumnNr == mIteratorColumnsCount - 1) \
        { \
            ++mIteratorCurrentRowNr; \
            mIteratorCurrentColumnNr = 0; \
        } \
        else \
        { \
            ++mIteratorCurrentColumnNr; \
        } \
    }

#define FORWARD_ZITERATOR_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{*this, mMatrixNrOfRows - 1, mMatrixNrOfColumns};

#define REVERSE_ZITERATOR_END(IteratorType) \
    return IteratorType{*this, 0, -1};

#define FORWARD_ZITERATOR_ROW_BEGIN(IteratorType, mMatrixNrOfRows, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    return IteratorType{*this, matrixRowNr, 0};

#define REVERSE_ZITERATOR_ROW_BEGIN(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    return IteratorType{*this, matrixRowNr, mMatrixNrOfColumns - 1};

#define FORWARD_ZITERATOR_ROW_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixRowNr < mMatrixNrOfRows - 1) \
    { \
        it = IteratorType{*this, matrixRowNr + 1, 0}; \
    } \
    else \
    { \
        it = IteratorType{*this, matrixRowNr, mMatrixNrOfColumns}; \
    } \
\
    return it;

#define REVERSE_ZITERATOR_ROW_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixRowNr > 0) \
    { \
        it = IteratorType{*this, matrixRowNr - 1, mMatrixNrOfColumns - 1}; \
    } \
    else \
    { \
        it = IteratorType{*this, 0, -1}; \
    } \
\
    return it;

#define ZITERATOR_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr<0 || matrixColumnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{*this, matrixRowNr, matrixColumnNr};

#define ZITERATOR_INDEX(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, arrayIndex) \
    CHECK_ERROR_CONDITION(arrayIndex < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(arrayIndex >= mMatrixNrOfRows * mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{*this, arrayIndex / mMatrixNrOfColumns, arrayIndex % mMatrixNrOfColumns};

// specialized NIterator macros

#define CONSTRUCT_FORWARD_NITERATOR(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, matrixRowNr, matrixColumnNr) \
    if (matrixRowNr < 0 || matrixColumnNr < 0 || matrixColumnNr >= mIteratorColumnsCount || matrixRowNr > mIteratorRowsCount || \
        (matrixColumnNr < mIteratorColumnsCount-1 && matrixRowNr == mIteratorRowsCount)) \
    { \
        mIteratorCurrentRowNr = -1; \
        mIteratorCurrentColumnNr = -1; \
    } \
    else \
    { \
        mIteratorCurrentRowNr = matrixRowNr; \
        mIteratorCurrentColumnNr = matrixColumnNr; \
    }

#define CONSTRUCT_REVERSE_NITERATOR(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, matrixRowNr, matrixColumnNr) \
    if (matrixColumnNr < 0 || matrixRowNr < -1 || matrixRowNr >= mIteratorRowsCount || matrixColumnNr >= mIteratorColumnsCount || \
        (matrixColumnNr < mIteratorColumnsCount-1 && matrixRowNr == mIteratorRowsCount)) \
    { \
        mIteratorCurrentRowNr = -1; \
        mIteratorCurrentColumnNr = -1; \
    } \
    else \
    { \
        mIteratorCurrentRowNr = matrixRowNr; \
        mIteratorCurrentColumnNr = matrixColumnNr; \
    }

#define FORWARD_NITERATOR_ADD_SCALAR(IteratorType, mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, scalarValue) \
    IteratorType it{}; \
\
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorCurrentColumnNr * mIteratorRowsCount + mIteratorCurrentRowNr}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
\
        it.mpIteratorPtr = mpIteratorPtr; \
        it.mIteratorRowsCount = mIteratorRowsCount; \
        it.mIteratorColumnsCount = mIteratorColumnsCount; \
        it.mIteratorCurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorRowsCount : c_ResultingIndex % mIteratorRowsCount; \
        it.mIteratorCurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorColumnsCount - 1 : c_ResultingIndex / mIteratorRowsCount; \
    } \
\
    return it;

#define REVERSE_NITERATOR_ADD_SCALAR(IteratorType, mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, scalarValue) \
    IteratorType it{}; \
\
    if (mpIteratorPtr) \
    { \
        const size_type c_CurrentIndex{mIteratorCurrentColumnNr * mIteratorRowsCount + mIteratorCurrentRowNr}; \
        const size_type c_ResultingIndex{c_CurrentIndex Sign scalarValue}; \
        const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
\
        it.mpIteratorPtr = mpIteratorPtr; \
        it.mIteratorRowsCount = mIteratorRowsCount; \
        it.mIteratorColumnsCount = mIteratorColumnsCount; \
        it.mIteratorCurrentRowNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? mIteratorRowsCount-1 : c_ResultingIndex % mIteratorRowsCount; \
        it.mIteratorCurrentColumnNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? mIteratorColumnsCount - 1 : c_ResultingIndex / mIteratorRowsCount; \
    } \
\
    return it;

#define FORWARD_NITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != it.mpIteratorPtr || mIteratorRowsCount != it.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItCurrentIndex{mIteratorCurrentColumnNr * mIteratorRowsCount + mIteratorCurrentRowNr}; \
    const size_type c_SecondItCurrentIndex{it.mIteratorCurrentColumnNr * it.mIteratorRowsCount + it.mIteratorCurrentRowNr}; \
\
    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);

#define REVERSE_NITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != it.mpIteratorPtr || mIteratorRowsCount != it.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    const size_type c_FirstItCurrentIndex{mIteratorCurrentColumnNr * mIteratorRowsCount + mIteratorCurrentRowNr}; \
    const size_type c_SecondItCurrentIndex{it.mIteratorCurrentColumnNr * it.mIteratorRowsCount + it.mIteratorCurrentRowNr}; \
\
    return (c_SecondItCurrentIndex - c_FirstItCurrentIndex);

#define FORWARD_NITERATOR_CHECK_STRICT_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentColumnNr Operator secondIterator.mIteratorCurrentColumnNr) || \
           (mIteratorCurrentColumnNr == secondIterator.mIteratorCurrentColumnNr && mIteratorCurrentRowNr Operator secondIterator.mIteratorCurrentRowNr);

#define REVERSE_NITERATOR_CHECK_STRICT_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (secondIterator.mIteratorCurrentColumnNr Operator mIteratorCurrentColumnNr) || \
           (secondIterator.mIteratorCurrentColumnNr == mIteratorCurrentColumnNr && secondIterator.mIteratorCurrentRowNr Operator mIteratorCurrentRowNr);

#define FORWARD_NITERATOR_CHECK_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorCurrentColumnNr Operator secondIterator.mIteratorCurrentColumnNr) || \
           (mIteratorCurrentColumnNr == secondIterator.mIteratorCurrentColumnNr && (mIteratorCurrentRowNr Operator secondIterator.mIteratorCurrentRowNr || mIteratorCurrentRowNr == secondIterator.mIteratorCurrentRowNr));

#define REVERSE_NITERATOR_CHECK_INEQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Operator, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || mIteratorRowsCount != secondIterator.mIteratorRowsCount || mIteratorColumnsCount != it.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (secondIterator.mIteratorCurrentColumnNr Operator mIteratorCurrentColumnNr) || \
           (secondIterator.mIteratorCurrentColumnNr == mIteratorCurrentColumnNr && (secondIterator.mIteratorCurrentRowNr Operator mIteratorCurrentRowNr || secondIterator.mIteratorCurrentRowNr == mIteratorCurrentRowNr));

#define FORWARD_NITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentRowNr == mIteratorRowsCount || mIteratorRowsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorCurrentRowNr][mIteratorCurrentColumnNr];

#define REVERSE_NITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentRowNr == -1 || mIteratorRowsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[mIteratorCurrentRowNr][mIteratorCurrentColumnNr];

#define FORWARD_NITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentRowNr == mIteratorRowsCount || mIteratorRowsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorCurrentRowNr] + mIteratorCurrentColumnNr);

#define REVERSE_NITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    CHECK_ERROR_CONDITION(mIteratorCurrentRowNr == -1 || mIteratorRowsCount == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[mIteratorCurrentRowNr] + mIteratorCurrentColumnNr);

#define NITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr, Sign, arrayIndex) \
    const size_type c_CurrentIndex{mIteratorCurrentColumnNr * mIteratorRowsCount + mIteratorCurrentRowNr}; \
    const size_type c_ResultingIndex{c_CurrentIndex Sign arrayIndex}; \
    const size_type c_UpperBound{mIteratorRowsCount * mIteratorColumnsCount}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex % mIteratorRowsCount][c_ResultingIndex / mIteratorRowsCount];

#define FORWARD_NITERATOR_DO_INCREMENT(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentRowNr != mIteratorRowsCount || mIteratorCurrentColumnNr != (mIteratorColumnsCount - 1)) \
    { \
        ++mIteratorCurrentRowNr; \
        if (mIteratorCurrentRowNr == mIteratorRowsCount && (mIteratorCurrentColumnNr != (mIteratorColumnsCount - 1))) \
        { \
            mIteratorCurrentRowNr = mIteratorCurrentRowNr - mIteratorRowsCount; \
            ++mIteratorCurrentColumnNr; \
        } \
    }

#define REVERSE_NITERATOR_DO_INCREMENT(mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentRowNr != -1 || mIteratorCurrentColumnNr != 0) \
    { \
        --mIteratorCurrentRowNr; \
        if (mIteratorCurrentRowNr < 0 && (mIteratorCurrentColumnNr != 0)) \
        { \
            mIteratorCurrentRowNr = mIteratorRowsCount - 1; \
            --mIteratorCurrentColumnNr; \
        } \
    }

#define FORWARD_NITERATOR_DO_DECREMENT(mIteratorRowsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentRowNr > 0 || mIteratorCurrentColumnNr > 0) \
    { \
        if(mIteratorCurrentRowNr == 0) \
        { \
            --mIteratorCurrentColumnNr; \
            mIteratorCurrentRowNr = mIteratorRowsCount - 1; \
        } \
        else \
        { \
            --mIteratorCurrentRowNr; \
        } \
    }

#define REVERSE_NITERATOR_DO_DECREMENT(mIteratorRowsCount, mIteratorColumnsCount, mIteratorCurrentRowNr, mIteratorCurrentColumnNr) \
    if (mIteratorCurrentColumnNr < mIteratorColumnsCount - 1 || mIteratorCurrentRowNr < mIteratorRowsCount - 1) \
    { \
        if(mIteratorCurrentRowNr == mIteratorRowsCount - 1) \
        { \
            ++mIteratorCurrentColumnNr; \
            mIteratorCurrentRowNr = 0; \
        } \
        else \
        { \
            ++mIteratorCurrentRowNr; \
        } \
    }

#define FORWARD_NITERATOR_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{*this, mMatrixNrOfRows, mMatrixNrOfColumns - 1};

#define REVERSE_NITERATOR_END(IteratorType) \
    return IteratorType{*this, -1, 0};

#define FORWARD_NITERATOR_COLUMN_BEGIN(IteratorType, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{*this, 0, matrixColumnNr};

#define REVERSE_NITERATOR_COLUMN_BEGIN(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{*this, mMatrixNrOfRows - 1, matrixColumnNr};

#define FORWARD_NITERATOR_COLUMN_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixColumnNr < mMatrixNrOfColumns - 1) \
    { \
        it = IteratorType{*this, 0, matrixColumnNr + 1}; \
    } \
    else \
    { \
        it = IteratorType{*this, mMatrixNrOfRows, matrixColumnNr}; \
    } \
\
    return it;

#define REVERSE_NITERATOR_COLUMN_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    IteratorType it{}; \
\
    if (matrixColumnNr > 0) \
    { \
        it = IteratorType{*this, mMatrixNrOfRows - 1, matrixColumnNr - 1}; \
    } \
    else \
    { \
        it = IteratorType{*this, -1, 0}; \
    } \
\
    return it;

#define NITERATOR_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{*this, matrixRowNr, matrixColumnNr};

#define NITERATOR_INDEX(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, arrayIndex) \
    CHECK_ERROR_CONDITION(arrayIndex < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(arrayIndex >= mMatrixNrOfRows * mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
\
    return IteratorType{*this, arrayIndex % mMatrixNrOfRows, arrayIndex / mMatrixNrOfRows};

// specialized DIterator macros
#define CONSTRUCT_FORWARD_DITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, matrixRowsCount, matrixColumnsCount, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        /* firstParam and secondParam are interpreted as diagonal number and relative arrayIndex within diagonal */ \
        mIteratorDiagonalNr = firstParam; \
        mIteratorDiagonalIndex = secondParam; \
        const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
        const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - c_CurrentRowNr, matrixColumnsCount - c_CurrentColumnNr); \
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

#define DITERATOR_IS_VALID_WITH_MATRIX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, pMatrixPtr, matrixRowsCount, matrixColumnsCount) \
    bool isValid{true}; \
\
    if (mpIteratorPtr != pMatrixPtr) \
    { \
        isValid = false; \
    } \
    else if ((mIteratorDiagonalNr < 0 && -mIteratorDiagonalNr >= matrixRowsCount) || (mIteratorDiagonalNr >= 0 && mIteratorDiagonalNr >= matrixColumnsCount)) \
    { \
        isValid = false; \
    } \
    else \
    { \
        const size_type c_DiagonalSize{mIteratorDiagonalNr < 0 ? std::min(matrixRowsCount + mIteratorDiagonalNr, matrixColumnsCount) \
                                                            : std::min(matrixRowsCount, matrixColumnsCount - mIteratorDiagonalNr)}; \
        if (mIteratorDiagonalSize != c_DiagonalSize) \
        { \
            isValid = false; \
        } \
    } \
\
    return isValid;

#define FORWARD_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_CurrentRowNr][c_CurrentColumnNr];

#define REVERSE_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - mIteratorDiagonalIndex - 1 : mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_CurrentRowNr][c_CurrentColumnNr];

#define FORWARD_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex : mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_CurrentRowNr] + c_CurrentColumnNr);

#define REVERSE_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - mIteratorDiagonalIndex - 1 : mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex + mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_CurrentRowNr] + c_CurrentColumnNr);

#define FORWARD_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    const size_type c_ResultingIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? c_ResultingIndex - mIteratorDiagonalNr : c_ResultingIndex}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? c_ResultingIndex : c_ResultingIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    const size_type c_ResultingIndex{mIteratorDiagonalIndex + arrayIndex}; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - c_ResultingIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - c_ResultingIndex - 1}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - c_ResultingIndex - 1 : mIteratorDiagonalSize - 1 - c_ResultingIndex + mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define DITERATOR_BEGIN_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagNr{matrixColumnNr - matrixRowNr}; \
\
    return IteratorType{*this, c_DiagNr, 0, true};

#define DITERATOR_DIAG_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1-mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? -matrixDiagonalNr : 0}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr < 0 ? 0 : matrixDiagonalNr}; \
    const size_type c_EndDiagIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
    return IteratorType{*this, matrixDiagonalNr, c_EndDiagIndex, true};

#define DITERATOR_END_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagNr{matrixColumnNr - matrixRowNr}; \
    const size_type c_BeginRowNr{c_DiagNr < 0 ? -c_DiagNr : 0}; \
    const size_type c_BeginColumnNr{c_DiagNr < 0 ? 0 : c_DiagNr}; \
    const size_type c_EndDiagIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
    return IteratorType{*this, c_DiagNr, c_EndDiagIndex, true};

#define DITERATOR_RANDOM(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        CHECK_ERROR_CONDITION(firstParam < (1 - mMatrixNrOfRows) || firstParam > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
\
        const size_type c_BeginRowNr{firstParam < 0 ? -firstParam : 0}; \
        const size_type c_BeginColumnNr{firstParam < 0 ? 0 : firstParam}; \
        const size_type c_DiagSize {std::min(mMatrixNrOfRows - c_BeginRowNr, mMatrixNrOfColumns - c_BeginColumnNr)}; \
\
        CHECK_ERROR_CONDITION(secondParam >= c_DiagSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
    } \
    else \
    { \
        CHECK_ERROR_CONDITION(firstParam < 0 || secondParam < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
        CHECK_ERROR_CONDITION(firstParam >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
        CHECK_ERROR_CONDITION(secondParam >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
    } \
\
    return IteratorType{*this, firstParam, secondParam, relativeParamsUsed};

// specialized MIterator macros

#define CONSTRUCT_FORWARD_MITERATOR(mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, matrixRowsCount, firstParam, secondParam, relativeParamsUsed) \
    if (relativeParamsUsed) \
    { \
        /* firstParam and secondParam are interpreted as diagonal number and relative arrayIndex within diagonal */ \
        mIteratorDiagonalNr = firstParam; \
        mIteratorDiagonalIndex = secondParam; \
        const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
        const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
        mIteratorDiagonalSize = mIteratorDiagonalIndex + std::min(matrixRowsCount - c_CurrentRowNr, c_CurrentColumnNr + 1); \
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

#define MITERATOR_IS_VALID_WITH_MATRIX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorColumnsCount, pMatrixPtr, matrixRowsCount, matrixColumnsCount) \
    bool isValid{true}; \
\
    if (mpIteratorPtr != pMatrixPtr || mIteratorColumnsCount != matrixColumnsCount) \
    { \
        isValid = false; \
    } \
    else if ((mIteratorDiagonalNr < 0 && -mIteratorDiagonalNr >= matrixRowsCount) || (mIteratorDiagonalNr >= 0 && mIteratorDiagonalNr >= matrixColumnsCount)) \
    { \
        isValid = false; \
    } \
    else \
    { \
        const size_type c_DiagonalSize{mIteratorDiagonalNr < 0 ? std::min(matrixRowsCount + mIteratorDiagonalNr, matrixColumnsCount) \
                                                            : std::min(matrixRowsCount, matrixColumnsCount - mIteratorDiagonalNr)}; \
        if (mIteratorDiagonalSize != c_DiagonalSize) \
        { \
            isValid = false; \
        } \
    } \
\
    return isValid;

#define FORWARD_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
\
    return mpIteratorPtr[c_CurrentRowNr][c_CurrentColumnNr];

#define REVERSE_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex : mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex - mIteratorDiagonalNr}; \
\
    return mpIteratorPtr[c_CurrentRowNr][c_CurrentColumnNr];

#define FORWARD_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalIndex}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalIndex - 1 : mIteratorColumnsCount - mIteratorDiagonalNr - mIteratorDiagonalIndex - 1}; \
\
    return (mpIteratorPtr[c_CurrentRowNr] + c_CurrentColumnNr);

#define REVERSE_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_CurrentRowNr{mIteratorDiagonalNr < 0 ? mIteratorDiagonalSize - 1 - mIteratorDiagonalIndex - mIteratorDiagonalNr : mIteratorDiagonalSize - mIteratorDiagonalIndex - 1}; \
    const size_type c_CurrentColumnNr{mIteratorDiagonalNr < 0 ? mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex : mIteratorColumnsCount - mIteratorDiagonalSize + mIteratorDiagonalIndex - mIteratorDiagonalNr}; \
\
    return (mpIteratorPtr[c_CurrentRowNr] + c_CurrentColumnNr);

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

#define MITERATOR_BEGIN_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagNr{mMatrixNrOfColumns - matrixRowNr - matrixColumnNr - 1}; \
\
    return IteratorType{*this, c_DiagNr, 0, true};

#define MITERATOR_DIAG_END(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (1 - mMatrixNrOfRows) || matrixDiagonalNr > (mMatrixNrOfColumns - 1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < 0 ? -matrixDiagonalNr : 0}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr <= 0 ? mMatrixNrOfColumns - 1 : mMatrixNrOfColumns - matrixDiagonalNr - 1}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, c_BeginColumnNr + 1)}; \
\
    return IteratorType{*this, matrixDiagonalNr, c_EndDiagonalIndex, true};

#define MITERATOR_END_ROW_COLUMN_NUMBER(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr < 0 || matrixColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]); \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const size_type c_DiagNr{mMatrixNrOfColumns - matrixRowNr - matrixColumnNr - 1}; \
    const size_type c_BeginRowNr{c_DiagNr < 0 ? -c_DiagNr : 0}; \
    const size_type c_BeginColumnNr{c_DiagNr <= 0 ? mMatrixNrOfColumns - 1 : mMatrixNrOfColumns - c_DiagNr - 1}; \
    const size_type c_EndDiagonalIndex{std::min(mMatrixNrOfRows - c_BeginRowNr, c_BeginColumnNr + 1)}; \
\
    return IteratorType{*this, c_DiagNr, c_EndDiagonalIndex, true};

#define MITERATOR_RANDOM(IteratorType, mMatrixNrOfRows, mMatrixNrOfColumns, firstParam, secondParam, relativeParamsUsed) \
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
    return IteratorType{*this, firstParam, secondParam, relativeParamsUsed};

#endif // ITERATORUTILS_H
