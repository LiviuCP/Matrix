module;

#include <cassert>
#include <optional>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratordefinitions.h"

module matrix:matrix_miterator_impl;
import :matrix_header;

// 13) MIterator (mirrored diagonal iterator, traverses a matrix diagonal from the other side (symetrically to
// DIterator); diagonal 0 passes through the upper right corner of the matrix)

template <MatrixElementType T> typename Matrix<T>::MIterator& Matrix<T>::MIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::MIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(MIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::MIterator& Matrix<T>::MIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::MIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(MIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator& Matrix<T>::MIterator::operator+=(Matrix<T>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator& Matrix<T>::MIterator::operator-=(Matrix<T>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator::difference_type Matrix<T>::MIterator::operator-(const Matrix<T>::MIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> auto Matrix<T>::MIterator::operator<=>(const Matrix<T>::MIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::MIterator::operator==(const Matrix<T>::MIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::getColumnNr() const
{
    // no overflow as for positive diagonals the diagonal number should be strictly smaller than the number of matrix
    // columns if the matrix is not empty
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? (*m_DiagonalIndex < m_NrOfMatrixColumns ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1}
                                                         : std::nullopt)
               : (*m_DiagonalIndex < m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr)
                      ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1 - static_cast<size_type>(m_DiagonalNr)}
                      : std::nullopt);
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::MIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::MIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> T& Matrix<T>::MIterator::operator*() const
{
    FORWARD_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                           m_NrOfMatrixColumns);
}

template <MatrixElementType T> T* Matrix<T>::MIterator::operator->() const
{
    FORWARD_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns);
}

template <MatrixElementType T> T& Matrix<T>::MIterator::operator[](Matrix<T>::MIterator::difference_type index) const
{
    FORWARD_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns, index);
}

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns,
                                const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::MIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::MIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::MIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 14) ConstMIterator

template <MatrixElementType T> typename Matrix<T>::ConstMIterator& Matrix<T>::ConstMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstMIterator Matrix<T>::ConstMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstMIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstMIterator& Matrix<T>::ConstMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstMIterator Matrix<T>::ConstMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstMIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator& Matrix<T>::ConstMIterator::operator+=(
    Matrix<T>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator& Matrix<T>::ConstMIterator::operator-=(
    Matrix<T>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator::difference_type Matrix<T>::ConstMIterator::operator-(
    const Matrix<T>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> auto Matrix<T>::ConstMIterator::operator<=>(const Matrix<T>::ConstMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::ConstMIterator::operator==(const Matrix<T>::ConstMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::getColumnNr() const
{
    // no overflow as for positive diagonals the diagonal number should be strictly smaller than the number of matrix
    // columns if the matrix is not empty
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? (*m_DiagonalIndex < m_NrOfMatrixColumns ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1}
                                                         : std::nullopt)
               : (*m_DiagonalIndex < m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr)
                      ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1 - static_cast<size_type>(m_DiagonalNr)}
                      : std::nullopt);
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ConstMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> const T& Matrix<T>::ConstMIterator::operator*() const
{
    FORWARD_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                           m_NrOfMatrixColumns);
}

template <MatrixElementType T> const T* Matrix<T>::ConstMIterator::operator->() const
{
    FORWARD_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstMIterator::operator[](Matrix<T>::ConstMIterator::difference_type index) const
{
    FORWARD_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns, index);
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(const MIterator& mIterator)
    : m_pMatrixPtr{mIterator.m_pMatrixPtr}
    , m_DiagonalIndex{mIterator.m_DiagonalIndex}
    , m_DiagonalNr{mIterator.m_DiagonalNr}
    , m_DiagonalSize{mIterator.m_DiagonalSize}
    , m_NrOfMatrixColumns{mIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ConstMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 15) ReverseMIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the MIterator)

template <MatrixElementType T> typename Matrix<T>::ReverseMIterator& Matrix<T>::ReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseMIterator Matrix<T>::ReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseMIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ReverseMIterator& Matrix<T>::ReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseMIterator Matrix<T>::ReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseMIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator& Matrix<T>::ReverseMIterator::operator+=(
    Matrix<T>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator& Matrix<T>::ReverseMIterator::operator-=(
    Matrix<T>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator::difference_type Matrix<T>::ReverseMIterator::operator-(
    const Matrix<T>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
auto Matrix<T>::ReverseMIterator::operator<=>(const Matrix<T>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::ReverseMIterator::operator==(const Matrix<T>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::getRowNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(-m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::getColumnNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size, the diagonal number is smaller than number of
    // columns (in the second case)
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0
                                          ? m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex
                                          : m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex - m_DiagonalNr};
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> T& Matrix<T>::ReverseMIterator::operator*() const
{
    REVERSE_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                           m_NrOfMatrixColumns);
}

template <MatrixElementType T> T* Matrix<T>::ReverseMIterator::operator->() const
{
    REVERSE_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns);
}

template <MatrixElementType T>
T& Matrix<T>::ReverseMIterator::operator[](Matrix<T>::ReverseMIterator::difference_type index) const
{
    REVERSE_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns, index);
}

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ReverseMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ReverseMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ReverseMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 16) ConstReverseMIterator

template <MatrixElementType T> typename Matrix<T>::ConstReverseMIterator& Matrix<T>::ConstReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::ConstReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseMIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseMIterator& Matrix<T>::ConstReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::ConstReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseMIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator& Matrix<T>::ConstReverseMIterator::operator+=(
    Matrix<T>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator& Matrix<T>::ConstReverseMIterator::operator-=(
    Matrix<T>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator::difference_type Matrix<T>::ConstReverseMIterator::operator-(
    const Matrix<T>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
auto Matrix<T>::ConstReverseMIterator::operator<=>(const Matrix<T>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
bool Matrix<T>::ConstReverseMIterator::operator==(const Matrix<T>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::getRowNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(-m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::getColumnNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size, the diagonal number is smaller than number of
    // columns (in the second case)
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0
                                          ? m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex
                                          : m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex - m_DiagonalNr};
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ConstReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> const T& Matrix<T>::ConstReverseMIterator::operator*() const
{
    REVERSE_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                           m_NrOfMatrixColumns);
}

template <MatrixElementType T> const T* Matrix<T>::ConstReverseMIterator::operator->() const
{
    REVERSE_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstReverseMIterator::operator[](Matrix<T>::ConstReverseMIterator::difference_type index) const
{
    REVERSE_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                        m_NrOfMatrixColumns, index);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(const ReverseMIterator& reverseMIterator)
    : m_pMatrixPtr{reverseMIterator.m_pMatrixPtr}
    , m_DiagonalIndex{reverseMIterator.m_DiagonalIndex}
    , m_DiagonalNr{reverseMIterator.m_DiagonalNr}
    , m_DiagonalSize{reverseMIterator.m_DiagonalSize}
    , m_NrOfMatrixColumns{reverseMIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows,
                                                       nrOfMatrixColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ConstReverseMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}
