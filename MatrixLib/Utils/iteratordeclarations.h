#pragma once

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

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType)                       \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns,                       \
                 std::optional<SizeType> rowNr, std::optional<SizeType> columnNr);                                     \
                                                                                                                       \
    std::optional<SizeType> m_RowNr;                                                                                   \
    std::optional<SizeType> m_ColumnNr;                                                                                \
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
