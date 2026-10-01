module;

#include <cassert>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratorutilityfunctions.h"

// When building the project on Mac using Ninja and LLVM Clang, I noticed
// that a compilation error would be triggered unless adding export to the
// implementation partition.
// On Linux the export itself triggers a compilation error!
#if defined(__APPLE__) && defined(__MACH__)
export module matrix:matrix_full_traverse_iterators_impl;
#else
module matrix:matrix_full_traverse_iterators_impl;
#endif

import :matrix_header;

// Base FullTraverseIterator class to be used for implementing (Reverse)Z/NIterator classes

template <MatrixElementType T> template <typename IterType> class Matrix<T>::FullTraverseIterator
{
public:
    IterType& operator++();
    IterType operator++(int unused);
    IterType& operator--();
    IterType operator--(int unused);

    IterType& operator+=(diff_type offset);
    inline IterType& operator-=(diff_type offset);

    diff_type operator-(const IterType& it) const;

    std::strong_ordering operator<=>(const IterType& it) const;
    bool operator==(const IterType& it) const;

protected:
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any
     * empty matrix */
    FullTraverseIterator();

    FullTraverseIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                         std::optional<diff_type> index);

    T& _applyAsteriskOperator() const;
    T* _applyArrowOperator() const;
    T& _applySquareBracketsOperator(diff_type index) const;

    inline T** _getMatrixPtr() const;
    inline size_type _getNrOfMatrixRows() const;
    inline size_type _getNrOfMatrixColumns() const;
    inline std::optional<diff_type> _getIndex() const;

    bool _isEmpty() const;

private:
    void _increment();
    void _decrement();

    inline std::optional<size_type> _getRowNr() const;
    inline std::optional<size_type> _getColumnNr() const;

    T** m_pMatrixPtr;
    size_type m_NrOfMatrixRows;
    size_type m_NrOfMatrixColumns;
    std::optional<diff_type> m_Index; /* relative index within begin - end iterators range */
};

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::FullTraverseIterator<IterType>::FullTraverseIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::FullTraverseIterator<IterType>::FullTraverseIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                                Matrix<T>::size_type nrOfMatrixColumns,
                                                                std::optional<Matrix<T>::diff_type> index)
{
    bool nonEmptyIteratorConstructed = false;

    if (pMatrixPtr)
    {
        if (nrOfMatrixRows > size_type{0} && nrOfMatrixColumns > size_type{0} && index.has_value() &&
            index <= static_cast<diff_type>(static_cast<diff_type>(nrOfMatrixRows) *
                                            static_cast<diff_type>(nrOfMatrixColumns)))
        {
            m_pMatrixPtr = pMatrixPtr;
            m_NrOfMatrixRows = nrOfMatrixRows;
            m_NrOfMatrixColumns = nrOfMatrixColumns;
            m_Index = index;
            nonEmptyIteratorConstructed = true;
        }
        else
        {
            assert(false);
        }
    }

    if (!nonEmptyIteratorConstructed)
    {
        m_pMatrixPtr = nullptr;
        m_NrOfMatrixRows = size_type{0};
        m_NrOfMatrixColumns = size_type{0};
    }
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator++()
{
    _increment();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::FullTraverseIterator<IterType>::operator++(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _increment();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator--()
{
    _decrement();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::FullTraverseIterator<IterType>::operator--(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _decrement();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator+=(Matrix<T>::diff_type offset)
{
    if (!_isEmpty())
    {
        const diff_type c_ResultingIndex{offset < diff_type{0} && std::abs(offset) > *m_Index
                                             ? diff_type{0}
                                             : static_cast<diff_type>(*m_Index + offset)};
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) *
                                                            static_cast<diff_type>(m_NrOfMatrixColumns))};

        m_Index = std::min<diff_type>(c_ResultingIndex, c_UpperBound);
    }

    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
inline IterType& Matrix<T>::FullTraverseIterator<IterType>::operator-=(Matrix<T>::diff_type offset)
{
    return *this += -offset;
}

template <MatrixElementType T>
template <typename IterType>
typename Matrix<T>::diff_type Matrix<T>::FullTraverseIterator<IterType>::operator-(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);
    return !_isEmpty() ? *m_Index - *it.m_Index : diff_type{0};
}

template <MatrixElementType T>
template <typename IterType>
std::strong_ordering Matrix<T>::FullTraverseIterator<IterType>::operator<=>(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    /* both iterators are either empty or not */
    return !_isEmpty() ? *m_Index <=> *it.m_Index : std::strong_ordering::equal;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::FullTraverseIterator<IterType>::operator==(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    /* both iterators are either empty or not */
    return _isEmpty() || *m_Index == *it.m_Index;
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::FullTraverseIterator<IterType>::_applyAsteriskOperator() const
{
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) * static_cast<diff_type>(m_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(_isEmpty() || m_Index == c_UpperBound,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[*_getRowNr()][*_getColumnNr()];
}

template <MatrixElementType T>
template <typename IterType>
T* Matrix<T>::FullTraverseIterator<IterType>::_applyArrowOperator() const
{
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) * static_cast<diff_type>(m_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(_isEmpty() || m_Index == c_UpperBound,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[*_getRowNr()] + *_getColumnNr());
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::FullTraverseIterator<IterType>::_applySquareBracketsOperator(diff_type index) const
{
    const std::optional<diff_type> c_Index{_getIndex()};

    /* The iterator index should not be std::nullopt if the matrix is not empty */
    CHECK_ERROR_CONDITION(_isEmpty() || (index < diff_type{0} && std::abs(index) > *c_Index),
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_NrOfMatrixRows{_getNrOfMatrixRows()};
    const size_type c_NrOfMatrixColumns{_getNrOfMatrixColumns()};
    const diff_type c_ResultingIndex{static_cast<diff_type>(*c_Index + index)};
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(c_NrOfMatrixRows) * static_cast<diff_type>(c_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound,
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const std::optional<size_type> c_RowNr{static_cast<const IterType*>(this)->_rowNrFromIndex(c_ResultingIndex)};
    const std::optional<size_type> c_ColumnNr{static_cast<const IterType*>(this)->_columnNrFromIndex(c_ResultingIndex)};

    assert(c_RowNr && c_ColumnNr);

    return m_pMatrixPtr[*c_RowNr][*c_ColumnNr];
}

template <MatrixElementType T>
template <typename IterType>
inline T** Matrix<T>::FullTraverseIterator<IterType>::_getMatrixPtr() const
{
    return m_pMatrixPtr;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::size_type Matrix<T>::FullTraverseIterator<IterType>::_getNrOfMatrixRows() const
{
    return m_NrOfMatrixRows;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::size_type Matrix<T>::FullTraverseIterator<IterType>::_getNrOfMatrixColumns() const
{
    return m_NrOfMatrixColumns;
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::diff_type> Matrix<T>::FullTraverseIterator<IterType>::_getIndex() const
{
    return m_Index;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::FullTraverseIterator<IterType>::_isEmpty() const
{
    if (m_pMatrixPtr)
    {
        assert(m_NrOfMatrixRows > size_type{0} && m_NrOfMatrixColumns > size_type{0} && m_Index.has_value());
    }
    else
    {
        assert(size_type{0} == m_NrOfMatrixRows && size_type{0} == m_NrOfMatrixColumns && !m_Index.has_value());
    }

    return !m_pMatrixPtr;
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::FullTraverseIterator<IterType>::_increment()
{
    if (!_isEmpty())
    {
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) *
                                                            static_cast<diff_type>(m_NrOfMatrixColumns))};
        if (m_Index < c_UpperBound)
        {
            m_Index = *m_Index + diff_type{1};
        }
    }
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::FullTraverseIterator<IterType>::_decrement()
{
    if (!_isEmpty() && m_Index > diff_type{0})
    {
        m_Index = *m_Index - diff_type{1};
    }
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::FullTraverseIterator<IterType>::_getRowNr() const
{
    return static_cast<const IterType*>(this)->getRowNr();
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::FullTraverseIterator<IterType>::_getColumnNr() const
{
    return static_cast<const IterType*>(this)->getColumnNr();
}

// 1) ZIterator - iterates within matrix from [0][0] to the end row by row

template <MatrixElementType T>
Matrix<T>::ZIterator::ZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T> inline T& Matrix<T>::ZIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::ZIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::ZIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::getRowNr() const
{
    return computeForwardZIteratorRowNr(_getIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::getColumnNr() const
{
    return computeForwardZIteratorColumnNr(_getIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardZIteratorRowNr(index, _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardZIteratorColumnNr(index, _getNrOfMatrixColumns());
}

// 2) ConstZIterator

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(const ZIterator& zIterator)
    : FullTraverseIterator<ConstZIterator>{zIterator._getMatrixPtr(), zIterator._getNrOfMatrixRows(),
                                           zIterator._getNrOfMatrixColumns(), zIterator._getIndex()}
{
}

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstZIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstZIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstZIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::getRowNr() const
{
    return computeForwardZIteratorRowNr(_getIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::getColumnNr() const
{
    return computeForwardZIteratorColumnNr(_getIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardZIteratorRowNr(index, _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardZIteratorColumnNr(index, _getNrOfMatrixColumns());
}

// 3) ReverseZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to
// ZIterator)

template <MatrixElementType T>
Matrix<T>::ReverseZIterator::ReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ReverseZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseZIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::ReverseZIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseZIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::getRowNr() const
{
    return computeReverseZIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::getColumnNr() const
{
    return computeReverseZIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseZIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseZIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

// 4) ConstReverseZIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(const ReverseZIterator& reverseZIterator)
    : FullTraverseIterator<ConstReverseZIterator>{
          reverseZIterator._getMatrixPtr(), reverseZIterator._getNrOfMatrixRows(),
          reverseZIterator._getNrOfMatrixColumns(), reverseZIterator._getIndex()}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstReverseZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstReverseZIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstReverseZIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T>
inline const T& Matrix<T>::ConstReverseZIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::getRowNr() const
{
    return computeReverseZIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::getColumnNr() const
{
    return computeReverseZIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseZIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseZIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

// 5) NIterator - iterates within matrix from [0][0] to the end column by column

template <MatrixElementType T>
Matrix<T>::NIterator::NIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<NIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

template <MatrixElementType T> inline T& Matrix<T>::NIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::NIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::NIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getRowNr() const
{
    return computeForwardNIteratorRowNr(_getIndex(), _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getColumnNr() const
{
    return computeForwardNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardNIteratorRowNr(index, _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardNIteratorColumnNr(index, _getNrOfMatrixRows());
}

// 6) ConstNIterator

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(const NIterator& nIterator)
    : FullTraverseIterator<ConstNIterator>{nIterator._getMatrixPtr(), nIterator._getNrOfMatrixRows(),
                                           nIterator._getNrOfMatrixColumns(), nIterator._getIndex()}
{
}

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstNIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstNIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstNIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getRowNr() const
{
    return computeForwardNIteratorRowNr(_getIndex(), _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getColumnNr() const
{
    return computeForwardNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardNIteratorRowNr(index, _getNrOfMatrixRows());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardNIteratorColumnNr(index, _getNrOfMatrixRows());
}

// 7) ReverseNIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to
// NIterator)

template <MatrixElementType T>
Matrix<T>::ReverseNIterator::ReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ReverseNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseNIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::ReverseNIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseNIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getRowNr() const
{
    return computeReverseNIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getColumnNr() const
{
    return computeReverseNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseNIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseNIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

// 8) ConstReverseNIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(const ReverseNIterator& reverseNIterator)
    : FullTraverseIterator<ConstReverseNIterator>{
          reverseNIterator._getMatrixPtr(), reverseNIterator._getNrOfMatrixRows(),
          reverseNIterator._getNrOfMatrixColumns(), reverseNIterator._getIndex()}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstReverseNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstReverseNIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstReverseNIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T>
inline const T& Matrix<T>::ConstReverseNIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getRowNr() const
{
    return computeReverseNIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getColumnNr() const
{
    return computeReverseNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseNIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseNIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
}