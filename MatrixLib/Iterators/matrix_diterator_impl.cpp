module;

#include <cassert>
#include <optional>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratordefinitions.h"

module matrix:matrix_diterator_impl;
import :matrix_header;

// 9) DIterator (diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T> typename Matrix<T>::DIterator& Matrix<T>::DIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::DIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(DIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::DIterator& Matrix<T>::DIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::DIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(DIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator& Matrix<T>::DIterator::operator+=(Matrix<T>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator& Matrix<T>::DIterator::operator-=(Matrix<T>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator::difference_type Matrix<T>::DIterator::operator-(const Matrix<T>::DIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> auto Matrix<T>::DIterator::operator<=>(const Matrix<T>::DIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::DIterator::operator==(const Matrix<T>::DIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex : *m_DiagonalIndex + m_DiagonalNr};
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::DIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::DIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> T& Matrix<T>::DIterator::operator*() const
{
    FORWARD_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> T* Matrix<T>::DIterator::operator->() const
{
    FORWARD_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> T& Matrix<T>::DIterator::operator[](Matrix<T>::DIterator::difference_type index) const
{
    FORWARD_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns,
                                const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr,
                                                       diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::DIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::DIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::DIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 10) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T> typename Matrix<T>::ConstDIterator& Matrix<T>::ConstDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstDIterator Matrix<T>::ConstDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstDIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstDIterator& Matrix<T>::ConstDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstDIterator Matrix<T>::ConstDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstDIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator& Matrix<T>::ConstDIterator::operator+=(
    Matrix<T>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator& Matrix<T>::ConstDIterator::operator-=(
    Matrix<T>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator::difference_type Matrix<T>::ConstDIterator::operator-(
    const Matrix<T>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> auto Matrix<T>::ConstDIterator::operator<=>(const Matrix<T>::ConstDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::ConstDIterator::operator==(const Matrix<T>::ConstDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex : *m_DiagonalIndex + m_DiagonalNr};
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ConstDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> const T& Matrix<T>::ConstDIterator::operator*() const
{
    FORWARD_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> const T* Matrix<T>::ConstDIterator::operator->() const
{
    FORWARD_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstDIterator::operator[](Matrix<T>::ConstDIterator::difference_type index) const
{
    FORWARD_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(const DIterator& dIterator)
    : m_pMatrixPtr{dIterator.m_pMatrixPtr}
    , m_DiagonalIndex{dIterator.m_DiagonalIndex}
    , m_DiagonalNr{dIterator.m_DiagonalNr}
    , m_DiagonalSize{dIterator.m_DiagonalSize}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr,
                                                       diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ConstDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 11) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template <MatrixElementType T> typename Matrix<T>::ReverseDIterator& Matrix<T>::ReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseDIterator Matrix<T>::ReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseDIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ReverseDIterator& Matrix<T>::ReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseDIterator Matrix<T>::ReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseDIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator& Matrix<T>::ReverseDIterator::operator+=(
    Matrix<T>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator& Matrix<T>::ReverseDIterator::operator-=(
    Matrix<T>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator::difference_type Matrix<T>::ReverseDIterator::operator-(
    const Matrix<T>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
auto Matrix<T>::ReverseDIterator::operator<=>(const Matrix<T>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T> bool Matrix<T>::ReverseDIterator::operator==(const Matrix<T>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(-m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr > 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> T& Matrix<T>::ReverseDIterator::operator*() const
{
    REVERSE_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> T* Matrix<T>::ReverseDIterator::operator->() const
{
    REVERSE_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T>
T& Matrix<T>::ReverseDIterator::operator[](Matrix<T>::ReverseDIterator::difference_type index) const
{
    REVERSE_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr,
                                                       diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ReverseDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ReverseDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ReverseDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 12) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the
// DIterator)

template <MatrixElementType T> typename Matrix<T>::ConstReverseDIterator& Matrix<T>::ConstReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::ConstReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseDIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseDIterator& Matrix<T>::ConstReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::ConstReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseDIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator& Matrix<T>::ConstReverseDIterator::operator+=(
    Matrix<T>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator& Matrix<T>::ConstReverseDIterator::operator-=(
    Matrix<T>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator::difference_type Matrix<T>::ConstReverseDIterator::operator-(
    const Matrix<T>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
auto Matrix<T>::ConstReverseDIterator::operator<=>(const Matrix<T>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
bool Matrix<T>::ConstReverseDIterator::operator==(const Matrix<T>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr < 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(-m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
           : m_DiagonalNr > 0
               ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + static_cast<size_type>(m_DiagonalNr)}
           : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                               : std::nullopt;
}

template <MatrixElementType T> typename Matrix<T>::diff_type Matrix<T>::ConstReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template <MatrixElementType T> const T& Matrix<T>::ConstReverseDIterator::operator*() const
{
    REVERSE_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> const T* Matrix<T>::ConstReverseDIterator::operator->() const
{
    REVERSE_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstReverseDIterator::operator[](Matrix<T>::ConstReverseDIterator::difference_type index) const
{
    REVERSE_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(const ReverseDIterator& reverseDIterator)
    : m_pMatrixPtr{reverseDIterator.m_pMatrixPtr}
    , m_DiagonalIndex{reverseDIterator.m_DiagonalIndex}
    , m_DiagonalNr{reverseDIterator.m_DiagonalNr}
    , m_DiagonalSize{reverseDIterator.m_DiagonalSize}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex,
                                                       pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr,
                                                       diagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

template <MatrixElementType T> bool Matrix<T>::ConstReverseDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}
