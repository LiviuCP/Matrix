module;

#include <cassert>
#include <stdexcept>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratordefinitions.h"
#include "../Utils/iteratorutilityfunctions.h"

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
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator& Matrix<T>::NIterator::operator-=(Matrix<T>::NIterator::difference_type offset)
{
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator::difference_type Matrix<T>::NIterator::operator-(const Matrix<T>::NIterator& it) const
{
    NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, it);
}

template <MatrixElementType T> auto Matrix<T>::NIterator::operator<=>(const Matrix<T>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::NIterator::operator==(const Matrix<T>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getRowNr() const
{
    RETRIEVE_FORWARD_NON_DIAG_ITERATOR_COORDINATE(m_NrOfMatrixRows, m_Index, %);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::NIterator::getColumnNr() const
{
    RETRIEVE_FORWARD_NON_DIAG_ITERATOR_COORDINATE(m_NrOfMatrixRows, m_Index, /);
}

template <MatrixElementType T> T& Matrix<T>::NIterator::operator*() const
{
    NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> T* Matrix<T>::NIterator::operator->() const
{
    NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> T& Matrix<T>::NIterator::operator[](Matrix<T>::NIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, %, /, index, 0,
                                        +);
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
    CONSTRUCT_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, pMatrixPtr,
                                nrOfMatrixColumns, nrOfMatrixRows,
                                computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr));
}

template <MatrixElementType T> void Matrix<T>::NIterator::_increment()
{
    NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T> void Matrix<T>::NIterator::_decrement()
{
    NON_DIAG_ITERATOR_DO_DECREMENT(m_Index);
}

template <MatrixElementType T> bool Matrix<T>::NIterator::_isEmpty() const
{
    CHECK_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
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
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator& Matrix<T>::ConstNIterator::operator-=(
    Matrix<T>::ConstNIterator::difference_type offset)
{
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator::difference_type Matrix<T>::ConstNIterator::operator-(
    const Matrix<T>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, it);
}

template <MatrixElementType T> auto Matrix<T>::ConstNIterator::operator<=>(const Matrix<T>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ConstNIterator::operator==(const Matrix<T>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index, it);
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getRowNr() const
{
    RETRIEVE_FORWARD_NON_DIAG_ITERATOR_COORDINATE(m_NrOfMatrixRows, m_Index, %);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstNIterator::getColumnNr() const
{
    RETRIEVE_FORWARD_NON_DIAG_ITERATOR_COORDINATE(m_NrOfMatrixRows, m_Index, /);
}

template <MatrixElementType T> const T& Matrix<T>::ConstNIterator::operator*() const
{
    NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> const T* Matrix<T>::ConstNIterator::operator->() const
{
    NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstNIterator::operator[](Matrix<T>::ConstNIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, %, /, index, 0,
                                        +);
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
    , m_Index{nIterator.m_Index}
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
    CONSTRUCT_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, pMatrixPtr,
                                nrOfMatrixColumns, nrOfMatrixRows,
                                computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr));
}

template <MatrixElementType T> void Matrix<T>::ConstNIterator::_increment()
{
    NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T> void Matrix<T>::ConstNIterator::_decrement()
{
    NON_DIAG_ITERATOR_DO_DECREMENT(m_Index);
}

template <MatrixElementType T> bool Matrix<T>::ConstNIterator::_isEmpty() const
{
    CHECK_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
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
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator& Matrix<T>::ReverseNIterator::operator-=(
    Matrix<T>::ReverseNIterator::difference_type offset)
{
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator::difference_type Matrix<T>::ReverseNIterator::operator-(
    const Matrix<T>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, it);
}

template <MatrixElementType T>
auto Matrix<T>::ReverseNIterator::operator<=>(const Matrix<T>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, *this, it);
}

template <MatrixElementType T> bool Matrix<T>::ReverseNIterator::operator==(const Matrix<T>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getRowNr() const
{
    RETRIEVE_REVERSE_NON_DIAG_ITERATOR_SECONDARY_COORDINATE(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ReverseNIterator::getColumnNr() const
{
    RETRIEVE_REVERSE_NON_DIAG_ITERATOR_PRIMARY_COORDINATE(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T> T& Matrix<T>::ReverseNIterator::operator*() const
{
    NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> T* Matrix<T>::ReverseNIterator::operator->() const
{
    NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T>
T& Matrix<T>::ReverseNIterator::operator[](Matrix<T>::ReverseNIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, %, /, index, 1,
                                        -);
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
    CONSTRUCT_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, pMatrixPtr,
                                nrOfMatrixColumns, nrOfMatrixRows,
                                computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr));
}

template <MatrixElementType T> void Matrix<T>::ReverseNIterator::_increment()
{
    NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> void Matrix<T>::ReverseNIterator::_decrement()
{
    NON_DIAG_ITERATOR_DO_DECREMENT(m_Index);
}

template <MatrixElementType T> bool Matrix<T>::ReverseNIterator::_isEmpty() const
{
    CHECK_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
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
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, +, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator& Matrix<T>::ConstReverseNIterator::operator-=(
    Matrix<T>::ConstReverseNIterator::difference_type offset)
{
    NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, -, offset);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator::difference_type Matrix<T>::ConstReverseNIterator::operator-(
    const Matrix<T>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, it);
}

template <MatrixElementType T>
auto Matrix<T>::ConstReverseNIterator::operator<=>(const Matrix<T>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, *this, it);
}

template <MatrixElementType T>
bool Matrix<T>::ConstReverseNIterator::operator==(const Matrix<T>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index, it);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getRowNr() const
{
    RETRIEVE_REVERSE_NON_DIAG_ITERATOR_SECONDARY_COORDINATE(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T>
std::optional<typename Matrix<T>::size_type> Matrix<T>::ConstReverseNIterator::getColumnNr() const
{
    RETRIEVE_REVERSE_NON_DIAG_ITERATOR_PRIMARY_COORDINATE(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index);
}

template <MatrixElementType T> const T& Matrix<T>::ConstReverseNIterator::operator*() const
{
    NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> const T* Matrix<T>::ConstReverseNIterator::operator->() const
{
    NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T>
const T& Matrix<T>::ConstReverseNIterator::operator[](Matrix<T>::ConstReverseNIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, %, /, index, 1,
                                        -);
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
    , m_Index{reverseNIterator.m_Index}
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
    CONSTRUCT_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_Index, pMatrixPtr,
                                nrOfMatrixColumns, nrOfMatrixRows,
                                computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr));
}

template <MatrixElementType T> void Matrix<T>::ConstReverseNIterator::_increment()
{
    NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}

template <MatrixElementType T> void Matrix<T>::ConstReverseNIterator::_decrement()
{
    NON_DIAG_ITERATOR_DO_DECREMENT(m_Index);
}

template <MatrixElementType T> bool Matrix<T>::ConstReverseNIterator::_isEmpty() const
{
    CHECK_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_Index);
}
