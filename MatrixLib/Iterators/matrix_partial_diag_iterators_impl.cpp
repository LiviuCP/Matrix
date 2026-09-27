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
export module matrix:matrix_partial_diag_iterators_impl;
#else
module matrix:matrix_partial_diag_iterators_impl;
#endif

import :matrix_header;

// Base PartialDiagIterator class to be used for implementing (Reverse)D/MIterator classes

template <MatrixElementType T> template <typename IterType> class Matrix<T>::PartialDiagIterator
{
public:
    IterType& operator++();
    IterType operator++(int unused);
    IterType& operator--();
    IterType operator--(int unused);

    IterType& operator+=(diff_type offset);

    inline IterType& operator-=(diff_type offset)
    {
        return *this += -offset;
    };

    diff_type operator-(const IterType& it) const;

    std::strong_ordering operator<=>(const IterType& it) const;
    bool operator==(const IterType& it) const;

    inline diff_type getDiagonalNr() const;
    inline std::optional<size_type> getDiagonalIndex() const;

protected:
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any
     * empty matrix */
    PartialDiagIterator();
    PartialDiagIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                        const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    T& _applyAsteriskOperator() const;
    T* _applyArrowOperator() const;
    T& _applySquareBracketsOperator(diff_type index) const;

    inline T** _getMatrixPtr() const;
    inline size_type _getDiagonalSize() const;
    inline size_type _getNrOfMatrixRows() const;
    inline size_type _getNrOfMatrixColumns() const;

    bool _isEmpty() const;

private:
    void _increment();
    void _decrement();

    inline std::optional<size_type> _getRowNr() const;
    inline std::optional<size_type> _getColumnNr() const;

    T** m_pMatrixPtr;
    std::optional<size_type> m_DiagonalIndex; /* relative index within diagonal */
    diff_type m_DiagonalNr;                   /* index of the diagonal within matrix */
    size_type m_DiagonalSize;                 /* number of elements contained within diagonal */
    size_type m_NrOfMatrixRows;               /* only used for initialization of const iterators */
    size_type m_NrOfMatrixColumns;            /* only used by mirrored diagonal iterators */
};

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::PartialDiagIterator<IterType>::PartialDiagIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::PartialDiagIterator<IterType>::PartialDiagIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    bool nonEmptyIteratorConstructed = false;

    if (pMatrixPtr)
    {
        std::optional<size_type> resultingDiagonalIndex;
        size_type resultingDiagonalSize{0};

        if (nrOfMatrixRows > size_type{0} && nrOfMatrixColumns > size_type{0} && diagonalIndex.has_value())
        {
            const diff_type c_MinDiagonalNr{
                static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(nrOfMatrixRows))};
            const diff_type c_MaxDiagonalNr{
                static_cast<diff_type>(static_cast<diff_type>(nrOfMatrixColumns) - diff_type{1})};

            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)
            {
                resultingDiagonalSize =
                    diagonalNr < diff_type{0}
                        ? std::min<size_type>(nrOfMatrixRows - static_cast<size_type>(-diagonalNr), nrOfMatrixColumns)
                        : std::min<size_type>(nrOfMatrixColumns - static_cast<size_type>(diagonalNr), nrOfMatrixRows);

                if (diagonalIndex <= resultingDiagonalSize)
                {
                    resultingDiagonalIndex = diagonalIndex;
                }
            }
        }

        if (resultingDiagonalIndex.has_value())
        {
            m_pMatrixPtr = pMatrixPtr;
            m_DiagonalNr = diagonalNr;
            m_DiagonalIndex = resultingDiagonalIndex;
            m_DiagonalSize = resultingDiagonalSize;
            m_NrOfMatrixRows = nrOfMatrixRows;
            m_NrOfMatrixColumns = nrOfMatrixColumns;
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
        m_DiagonalNr = diff_type{0};
        m_DiagonalSize = size_type{0};
        m_NrOfMatrixRows = size_type{0};
        m_NrOfMatrixColumns = size_type{0};
    }
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator++()
{
    _increment();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::PartialDiagIterator<IterType>::operator++(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _increment();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator--()
{
    _decrement();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::PartialDiagIterator<IterType>::operator--(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _decrement();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator+=(Matrix<T>::diff_type offset)
{
    const size_type c_ResultingIndex{
        static_cast<size_type>((offset < diff_type{0} && static_cast<size_type>(-offset) > m_DiagonalIndex)
                                   ? size_type{0}
                                   : static_cast<size_type>(static_cast<diff_type>(*m_DiagonalIndex) + offset))};
    m_DiagonalIndex = std::min(c_ResultingIndex, m_DiagonalSize);

    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
typename Matrix<T>::diff_type Matrix<T>::PartialDiagIterator<IterType>::operator-(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return !_isEmpty() ? (static_cast<diff_type>(*m_DiagonalIndex) - static_cast<diff_type>(*it.m_DiagonalIndex))
                       : diff_type{0};
}

template <MatrixElementType T>
template <typename IterType>
std::strong_ordering Matrix<T>::PartialDiagIterator<IterType>::operator<=>(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    /* both iterators are either empty or not */
    return !_isEmpty() ? *m_DiagonalIndex <=> *it.m_DiagonalIndex : std::strong_ordering::equal;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::PartialDiagIterator<IterType>::operator==(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    /* both iterators are either empty or not */
    return _isEmpty() || *m_DiagonalIndex == *it.m_DiagonalIndex;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::diff_type Matrix<T>::PartialDiagIterator<IterType>::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::PartialDiagIterator<IterType>::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::PartialDiagIterator<IterType>::_applyAsteriskOperator() const
{
    CHECK_ERROR_CONDITION(_isEmpty() || m_DiagonalIndex == m_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    return m_pMatrixPtr[*_getRowNr()][*_getColumnNr()];
}

template <MatrixElementType T>
template <typename IterType>
T* Matrix<T>::PartialDiagIterator<IterType>::_applyArrowOperator() const
{
    CHECK_ERROR_CONDITION(_isEmpty() || m_DiagonalIndex == m_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    return m_pMatrixPtr[*_getRowNr()] + *_getColumnNr();
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::PartialDiagIterator<IterType>::_applySquareBracketsOperator(Matrix<T>::diff_type index) const
{
    const std::optional<size_type> c_DiagonalIndex{getDiagonalIndex()};

    CHECK_ERROR_CONDITION(_isEmpty() ||
                              (index < diff_type{0} && static_cast<size_type>(std::abs(index)) > c_DiagonalIndex),
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*c_DiagonalIndex) + index)};
    const size_type c_DiagonalSize{_getDiagonalSize()};

    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= c_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const std::optional<size_type> c_RowNr{
        static_cast<const IterType*>(this)->_rowNrFromIndex(c_ResultingDiagonalIndex)};
    const std::optional<size_type> c_ColumnNr{
        static_cast<const IterType*>(this)->_columnNrFromIndex(c_ResultingDiagonalIndex)};

    assert(c_RowNr && c_ColumnNr);

    return m_pMatrixPtr[*c_RowNr][*c_ColumnNr];
}

template <MatrixElementType T>
template <typename IterType>
inline T** Matrix<T>::PartialDiagIterator<IterType>::_getMatrixPtr() const
{
    return m_pMatrixPtr;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::size_type Matrix<T>::PartialDiagIterator<IterType>::_getDiagonalSize() const
{
    return m_DiagonalSize;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::size_type Matrix<T>::PartialDiagIterator<IterType>::_getNrOfMatrixRows() const
{
    return m_NrOfMatrixRows;
}

template <MatrixElementType T>
template <typename IterType>
inline typename Matrix<T>::size_type Matrix<T>::PartialDiagIterator<IterType>::_getNrOfMatrixColumns() const
{
    return m_NrOfMatrixColumns;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::PartialDiagIterator<IterType>::_isEmpty() const
{
    if (m_pMatrixPtr)
    {
        assert(m_DiagonalSize > size_type{0} && m_DiagonalIndex.has_value() && m_NrOfMatrixColumns > size_type{0});
    }
    else
    {
        assert(diff_type{0} == m_DiagonalNr && size_type{0} == m_DiagonalSize && !m_DiagonalIndex.has_value() &&
               size_type{0} == m_NrOfMatrixColumns);
    }

    return !m_pMatrixPtr;
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::PartialDiagIterator<IterType>::_increment()
{
    if (!_isEmpty() && m_DiagonalIndex < m_DiagonalSize)
    {
        m_DiagonalIndex = *m_DiagonalIndex + size_type{1};
    }
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::PartialDiagIterator<IterType>::_decrement()
{
    if (!_isEmpty() && m_DiagonalIndex > size_type{0})
    {
        m_DiagonalIndex = *m_DiagonalIndex - size_type{1};
    }
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::PartialDiagIterator<IterType>::_getRowNr() const
{
    return static_cast<const IterType*>(this)->getRowNr();
}

template <MatrixElementType T>
template <typename IterType>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::PartialDiagIterator<IterType>::_getColumnNr() const
{
    return static_cast<const IterType*>(this)->getColumnNr();
}

// 9) DIterator (diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<DIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<DIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline T& Matrix<T>::DIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::DIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::DIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::getRowNr() const
{
    return computeForwardDIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::getColumnNr() const
{
    return computeForwardDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardDIteratorRowNr(getDiagonalNr(), index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardDIteratorColumnNr(getDiagonalNr(), index);
}

// 10) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(const DIterator& dIterator)
    : PartialDiagIterator<ConstDIterator>{dIterator._getMatrixPtr(),
                                          dIterator._getNrOfMatrixRows(),
                                          dIterator._getNrOfMatrixColumns(),
                                          {dIterator.getDiagonalNr(), dIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstDIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstDIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstDIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::getRowNr() const
{
    return computeForwardDIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::getColumnNr() const
{
    return computeForwardDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardDIteratorRowNr(getDiagonalNr(), index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardDIteratorColumnNr(getDiagonalNr(), index);
}

// 11) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ReverseDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ReverseDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseDIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::ReverseDIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseDIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::getRowNr() const
{
    return computeReverseDIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::getColumnNr() const
{
    return computeReverseDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseDIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseDIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize());
}

// 12) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the
// DIterator)

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(const ReverseDIterator& reverseDIterator)
    : PartialDiagIterator<ConstReverseDIterator>{
          reverseDIterator._getMatrixPtr(),
          reverseDIterator._getNrOfMatrixRows(),
          reverseDIterator._getNrOfMatrixColumns(),
          {reverseDIterator.getDiagonalNr(), reverseDIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstReverseDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstReverseDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstReverseDIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstReverseDIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T>
inline const T& Matrix<T>::ConstReverseDIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::getRowNr() const
{
    return computeReverseDIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::getColumnNr() const
{
    return computeReverseDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseDIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseDIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize());
}

// 13) MIterator (mirrored diagonal iterator, traverses a matrix diagonal from the other side (symetrically to
// DIterator); diagonal 0 passes through the upper right corner of the matrix)

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<MIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<MIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline T& Matrix<T>::MIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::MIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::MIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::getRowNr() const
{
    return computeForwardMIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::getColumnNr() const
{
    return computeForwardMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardMIteratorRowNr(getDiagonalNr(), index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardMIteratorColumnNr(getDiagonalNr(), index, _getNrOfMatrixColumns());
}

// 14) ConstMIterator

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(const MIterator& mIterator)
    : PartialDiagIterator<ConstMIterator>{mIterator._getMatrixPtr(),
                                          mIterator._getNrOfMatrixRows(),
                                          mIterator._getNrOfMatrixColumns(),
                                          {mIterator.getDiagonalNr(), mIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstMIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstMIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstMIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::getRowNr() const
{
    return computeForwardMIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::getColumnNr() const
{
    return computeForwardMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardMIteratorRowNr(getDiagonalNr(), index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeForwardMIteratorColumnNr(getDiagonalNr(), index, _getNrOfMatrixColumns());
}

// 15) ReverseMIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the MIterator)

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ReverseMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ReverseMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseMIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline T* Matrix<T>::ReverseMIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T> inline T& Matrix<T>::ReverseMIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::getRowNr() const
{
    return computeReverseMIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::getColumnNr() const
{
    return computeReverseMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize(),
                                           _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseMIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseMIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize(), _getNrOfMatrixColumns());
}

// 16) ConstReverseMIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(const ReverseMIterator& reverseMIterator)
    : PartialDiagIterator<ConstReverseMIterator>{
          reverseMIterator._getMatrixPtr(),
          reverseMIterator._getNrOfMatrixRows(),
          reverseMIterator._getNrOfMatrixColumns(),
          {reverseMIterator.getDiagonalNr(), reverseMIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstReverseMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstReverseMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

template <MatrixElementType T> inline const T& Matrix<T>::ConstReverseMIterator::operator*() const
{
    return _applyAsteriskOperator();
}

template <MatrixElementType T> inline const T* Matrix<T>::ConstReverseMIterator::operator->() const
{
    return _applyArrowOperator();
}

template <MatrixElementType T>
inline const T& Matrix<T>::ConstReverseMIterator::operator[](Matrix<T>::diff_type index) const
{
    return _applySquareBracketsOperator(index);
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::getRowNr() const
{
    return computeReverseMIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::getColumnNr() const
{
    return computeReverseMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize(),
                                           _getNrOfMatrixColumns());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::_rowNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseMIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
}

template <MatrixElementType T>
inline std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::_columnNrFromIndex(
    std::optional<Matrix<T>::diff_type> index) const
{
    return computeReverseMIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize(), _getNrOfMatrixColumns());
}
