module;

#include <cassert>
#include <optional>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratordefinitions.h"

module matrix:matrix_niterator_impl;
import :matrix_header;

// 5) NIterator - iterates within matrix from [0][0] to the end column by column
template <MatrixElementType T> typename Matrix<T>::NIterator& Matrix<T>::NIterator::operator++()
{
    ITERATOR_PRE_INCREMENT()
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::NIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(NIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::NIterator& Matrix<T>::NIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::NIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(NIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator& Matrix<T>::NIterator::operator+=(Matrix<T>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator& Matrix<T>::NIterator::operator-=(Matrix<T>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator::difference_type Matrix<T>::NIterator::operator-(const Matrix<T>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                 m_RowNr, it);
}

template <MatrixElementType T> auto Matrix<T>::NIterator::operator<=>(const Matrix<T>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::NIterator::operator==(const Matrix<T>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> T& Matrix<T>::NIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> T* Matrix<T>::NIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> T& Matrix<T>::NIterator::operator[](Matrix<T>::NIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, %, /, index);
}

template <MatrixElementType T>
Matrix<T>::NIterator::NIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::NIterator::NIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr,
                                        pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
}

template <MatrixElementType T> void Matrix<T>::NIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> void Matrix<T>::NIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> bool Matrix<T>::NIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 6) ConstNIterator
template <MatrixElementType T> typename Matrix<T>::ConstNIterator& Matrix<T>::ConstNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::ConstNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstNIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator& Matrix<T>::ConstNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::ConstNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstNIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator& Matrix<T>::ConstNIterator::operator+=(
    Matrix<T>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator& Matrix<T>::ConstNIterator::operator-=(
    Matrix<T>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator::difference_type Matrix<T>::ConstNIterator::operator-(
    const Matrix<T>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                 m_RowNr, it);
}

template <MatrixElementType T> auto Matrix<T>::ConstNIterator::operator<=>(const Matrix<T>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ConstNIterator::operator==(const Matrix<T>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> const T& Matrix<T>::ConstNIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> const T* Matrix<T>::ConstNIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstNIterator::operator[](Matrix<T>::ConstNIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, %, /, index);
}

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(const NIterator& nIterator)
    : m_pMatrixPtr{nIterator.m_pMatrixPtr}
    , m_RowNr{nIterator.m_RowNr}
    , m_ColumnNr{nIterator.m_ColumnNr}
    , m_NrOfMatrixRows{nIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{nIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr,
                                        pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
}

template <MatrixElementType T> void Matrix<T>::ConstNIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> void Matrix<T>::ConstNIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> bool Matrix<T>::ConstNIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 7) ReverseNIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to
// NIterator)

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator& Matrix<T>::ReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::ReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseNIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator& Matrix<T>::ReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::ReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseNIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator& Matrix<T>::ReverseNIterator::operator+=(
    Matrix<T>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator& Matrix<T>::ReverseNIterator::operator-=(
    Matrix<T>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator::difference_type Matrix<T>::ReverseNIterator::operator-(
    const Matrix<T>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                 m_RowNr, it);
}

template <MatrixElementType T>
auto Matrix<T>::ReverseNIterator::operator<=>(const Matrix<T>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ReverseNIterator::operator==(const Matrix<T>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> T& Matrix<T>::ReverseNIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> T* Matrix<T>::ReverseNIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T>
T& Matrix<T>::ReverseNIterator::operator[](Matrix<T>::ReverseNIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, %, /, index);
}

template <MatrixElementType T>
Matrix<T>::ReverseNIterator::ReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseNIterator::ReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr,
                                        pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
}

template <MatrixElementType T> void Matrix<T>::ReverseNIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> void Matrix<T>::ReverseNIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> bool Matrix<T>::ReverseNIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_ColumnNr, m_RowNr);
}

// 8) ConstReverseNIterator

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator& Matrix<T>::ConstReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::ConstReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseNIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator& Matrix<T>::ConstReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::ConstReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseNIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator& Matrix<T>::ConstReverseNIterator::operator+=(
    Matrix<T>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator& Matrix<T>::ConstReverseNIterator::operator-=(
    Matrix<T>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                   m_RowNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator::difference_type Matrix<T>::ConstReverseNIterator::operator-(
    const Matrix<T>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                 m_RowNr, it);
}

template <MatrixElementType T>
auto Matrix<T>::ConstReverseNIterator::operator<=>(const Matrix<T>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, *this, it);
}

template <MatrixElementType T>
bool Matrix<T>::ConstReverseNIterator::operator==(const Matrix<T>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> const T& Matrix<T>::ConstReverseNIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> const T* Matrix<T>::ConstReverseNIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstReverseNIterator::operator[](Matrix<T>::ConstReverseNIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr,
                                                m_RowNr, %, /, index);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(const ReverseNIterator& reverseNIterator)
    : m_pMatrixPtr{reverseNIterator.m_pMatrixPtr}
    , m_RowNr{reverseNIterator.m_RowNr}
    , m_ColumnNr{reverseNIterator.m_ColumnNr}
    , m_NrOfMatrixRows{reverseNIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{reverseNIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr,
                                        pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseNIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseNIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template <MatrixElementType T> bool Matrix<T>::ConstReverseNIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_ColumnNr, m_RowNr);
}
