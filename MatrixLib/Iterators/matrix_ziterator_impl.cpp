module;

#include <cassert>
#include <optional>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratordefinitions.h"

module matrix:matrix_ziterator_impl;
import :matrix_header;

// 1) ZIterator - iterates within matrix from [0][0] to the end row by row
template <MatrixElementType T> typename Matrix<T>::ZIterator& Matrix<T>::ZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::ZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ZIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator& Matrix<T>::ZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::ZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ZIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ZIterator& Matrix<T>::ZIterator::operator+=(Matrix<T>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ZIterator& Matrix<T>::ZIterator::operator-=(Matrix<T>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ZIterator::difference_type Matrix<T>::ZIterator::operator-(const Matrix<T>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                 m_ColumnNr, it);
}

template <MatrixElementType T> auto Matrix<T>::ZIterator::operator<=>(const Matrix<T>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ZIterator::operator==(const Matrix<T>::ZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> T& Matrix<T>::ZIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T> T* Matrix<T>::ZIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T> T& Matrix<T>::ZIterator::operator[](Matrix<T>::ZIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, /, %, index);
}

template <MatrixElementType T>
Matrix<T>::ZIterator::ZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ZIterator::ZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr,
                                        pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T> void Matrix<T>::ZIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> void Matrix<T>::ZIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> bool Matrix<T>::ZIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 2) ConstZIterator

template <MatrixElementType T> typename Matrix<T>::ConstZIterator& Matrix<T>::ConstZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::ConstZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstZIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator& Matrix<T>::ConstZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::ConstZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstZIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator& Matrix<T>::ConstZIterator::operator+=(
    Matrix<T>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator& Matrix<T>::ConstZIterator::operator-=(
    Matrix<T>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator::difference_type Matrix<T>::ConstZIterator::operator-(
    const Matrix<T>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                 m_ColumnNr, it);
}

template <MatrixElementType T> auto Matrix<T>::ConstZIterator::operator<=>(const Matrix<T>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ConstZIterator::operator==(const Matrix<T>::ConstZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> const T& Matrix<T>::ConstZIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T> const T* Matrix<T>::ConstZIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstZIterator::operator[](Matrix<T>::ConstZIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, /, %, index);
}

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(const ZIterator& zIterator)
    : m_pMatrixPtr{zIterator.m_pMatrixPtr}
    , m_RowNr{zIterator.m_RowNr}
    , m_ColumnNr{zIterator.m_ColumnNr}
    , m_NrOfMatrixRows{zIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{zIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr,
                                        pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T> void Matrix<T>::ConstZIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> void Matrix<T>::ConstZIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> bool Matrix<T>::ConstZIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 3) ReverseZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to
// ZIterator)

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator& Matrix<T>::ReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::ReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseZIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator& Matrix<T>::ReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::ReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseZIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator& Matrix<T>::ReverseZIterator::operator+=(
    Matrix<T>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator& Matrix<T>::ReverseZIterator::operator-=(
    Matrix<T>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator::difference_type Matrix<T>::ReverseZIterator::operator-(
    const Matrix<T>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                 m_ColumnNr, it);
}

template <MatrixElementType T>
auto Matrix<T>::ReverseZIterator::operator<=>(const Matrix<T>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ReverseZIterator::operator==(const Matrix<T>::ReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> T& Matrix<T>::ReverseZIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T> T* Matrix<T>::ReverseZIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T>
T& Matrix<T>::ReverseZIterator::operator[](Matrix<T>::ReverseZIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, /, %, index);
}

template <MatrixElementType T>
Matrix<T>::ReverseZIterator::ReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseZIterator::ReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr,
                                        pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T> void Matrix<T>::ReverseZIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> void Matrix<T>::ReverseZIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> bool Matrix<T>::ReverseZIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 4) ConstReverseZIterator

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator& Matrix<T>::ConstReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::ConstReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseZIterator, unused);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator& Matrix<T>::ConstReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::ConstReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseZIterator, unused);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator& Matrix<T>::ConstReverseZIterator::operator+=(
    Matrix<T>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator& Matrix<T>::ConstReverseZIterator::operator-=(
    Matrix<T>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                   m_ColumnNr, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator::difference_type Matrix<T>::ConstReverseZIterator::operator-(
    const Matrix<T>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                 m_ColumnNr, it);
}

template <MatrixElementType T>
auto Matrix<T>::ConstReverseZIterator::operator<=>(const Matrix<T>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, *this, it);
}

template <MatrixElementType T>
bool Matrix<T>::ConstReverseZIterator::operator==(const Matrix<T>::ConstReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template <MatrixElementType T> const T& Matrix<T>::ConstReverseZIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T> const T* Matrix<T>::ConstReverseZIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstReverseZIterator::operator[](Matrix<T>::ConstReverseZIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr,
                                                m_ColumnNr, /, %, index);
}

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(const ReverseZIterator& reverseZIterator)
    : m_pMatrixPtr{reverseZIterator.m_pMatrixPtr}
    , m_RowNr{reverseZIterator.m_RowNr}
    , m_ColumnNr{reverseZIterator.m_ColumnNr}
    , m_NrOfMatrixRows{reverseZIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{reverseZIterator.m_NrOfMatrixColumns}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr,
                                        pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseZIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseZIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template <MatrixElementType T> bool Matrix<T>::ConstReverseZIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}
