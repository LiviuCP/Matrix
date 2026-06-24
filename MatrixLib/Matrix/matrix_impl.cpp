module;

#include <algorithm>
#include <cassert>
#include <optional>
#include <stdexcept>
#include <vector>

#include "../Utils/errorhandling.h"
#include "../Utils/iteratorgetters.h"

module matrix:matrix_impl;
import :matrix_header;

template <MatrixElementType T> Matrix<T>::Matrix()
{
    _allocMemory(0, 0);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, std::vector<T>&& vec)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(nrOfRows * nrOfColumns > vec.size(),
                          Matr::errorMessages[Matr::Errors::INSUFFICIENT_ELEMENTS_FOR_INIT]);

    const size_type c_RowCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRows + nrOfRows / 4), c_MaxAllowedDimension)};
    const size_type c_ColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfColumns + nrOfColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::vector<T>::iterator vecIterator{vec.begin()};

    /* absRowNr = absolute row number, i.e. number of the row within "physical" matrix (that includes free row/column
       capacity) When the "abs" keyword is missing (i.e. rowNr), then the row number within "logical" (actually used)
       matrix (excluding free capacity) is meant (see other methods too)
    */
    for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_move_n(vecIterator, m_NrOfColumns, m_pBaseArrayPtr[absRowNr]);
        vecIterator += m_NrOfColumns;
    }
}

template <MatrixElementType T> Matrix<T>::Matrix(Matrix<T>::dimensions_t dimensions, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};
    const auto& [nrOfRows, nrOfColumns] = dimensions;

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const size_type c_RowCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRows + nrOfRows / 4), c_MaxAllowedDimension)};
    const size_type c_ColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfColumns + nrOfColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
    _fillInitItems(0, 0, nrOfRows, nrOfColumns, value);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>::size_type nrOfRowsColumns, const std::pair<T, T>& diagMatrixValues)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRowsColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRowsColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const size_type c_RowColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRowsColumns + nrOfRowsColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRowsColumns, nrOfRowsColumns, c_RowColumnCapacityToAlloc, c_RowColumnCapacityToAlloc);

    const auto& [allButMainDiagValue, mainDiagValue]{diagMatrixValues};

    for (size_type absRowNr{*m_RowCapacityOffset}, columnNr{0}; columnNr < nrOfRowsColumns; ++columnNr, ++absRowNr)
    {
        T* const pRowBegin{m_pBaseArrayPtr[absRowNr]};
        T* const pMainDiagElement{m_pBaseArrayPtr[absRowNr] + columnNr};
        T* const pRowEnd{m_pBaseArrayPtr[absRowNr] + nrOfRowsColumns};

        std::uninitialized_fill(pRowBegin, pMainDiagElement, allButMainDiagValue);
        std::uninitialized_fill(pMainDiagElement, pMainDiagElement + 1, mainDiagValue);
        std::uninitialized_fill(pMainDiagElement + 1, pRowEnd, allButMainDiagValue);
    }
}

template <MatrixElementType T>
Matrix<T>::Matrix(const Matrix<T>& matrix)
    : Matrix{}
{
    _copyAssignMatrix(matrix);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>&& matrix)
    : Matrix{}
{
    _moveAssignMatrix(matrix);
}

template <MatrixElementType T> Matrix<T>::~Matrix()
{
    _deallocMemory();
}

template <MatrixElementType T> T& Matrix<T>::at(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);
    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template <MatrixElementType T> const T& Matrix<T>::at(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);
    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template <MatrixElementType T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
    _copyAssignMatrix(matrix);
    return *this;
}

template <MatrixElementType T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matrix)
{
    _moveAssignMatrix(matrix);
    return *this;
}

// a contiguous unidimensional array with the matrix elements (in row order) is returned to user
template <MatrixElementType T> void* Matrix<T>::getBaseArray(Matrix<T>::size_type& nrOfElements)
{
    void* pAllocPtr{nullptr};

    if (!isEmpty())
    {
        shrinkToFit(); // when transfering ownership user should get exactly the number of elements contained in the
                       // used lines and columns (no extra capacity to be included)
        pAllocPtr = _convertToArray(nrOfElements);
    }
    else
    {
        nrOfElements = 0;
    }

    return pAllocPtr;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getNrOfRows() const
{
    return m_NrOfRows;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getNrOfColumns() const
{
    return m_NrOfColumns;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getRowCapacity() const
{
    return m_RowCapacity;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getColumnCapacity() const
{
    return m_ColumnCapacity;
}
// #ifdef USE_CAPACITY_OFFSET
template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::getRowCapacityOffset() const
{
    return m_RowCapacityOffset;
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::getColumnCapacityOffset() const
{
    return m_ColumnCapacityOffset;
}
// #endif
template <MatrixElementType T> bool Matrix<T>::isEmpty() const
{
    if (m_pAllocPtr)
    {
        assert(m_pBaseArrayPtr && m_NrOfRows > 0 && m_NrOfColumns > 0 && m_RowCapacity >= m_NrOfRows &&
               m_ColumnCapacity >= m_NrOfColumns && m_RowCapacityOffset >= 0 && m_ColumnCapacityOffset >= 0);
    }
    else
    {
        assert(!m_pBaseArrayPtr && 0 == m_NrOfRows && 0 == m_NrOfColumns && 0 == m_RowCapacity &&
               0 == m_ColumnCapacity && !m_RowCapacityOffset.has_value() && !m_ColumnCapacityOffset.has_value());
    }

    return !m_pAllocPtr;
}

template <MatrixElementType T> void Matrix<T>::transpose()
{
    if (!isEmpty())
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_NewNrOfRows{m_NrOfColumns};
        const size_type c_NewNrOfColumns{m_NrOfRows};
        const size_type c_NewRowCapacity{
            m_RowCapacity < m_NrOfColumns
                ? std::min(static_cast<size_type>(m_NrOfColumns + m_NrOfColumns / 4), c_MaxAllowedDimension)
                : m_RowCapacity};
        const size_type c_NewColumnCapacity{
            m_ColumnCapacity < m_NrOfRows
                ? std::min(static_cast<size_type>(m_NrOfRows + m_NrOfRows / 4), c_MaxAllowedDimension)
                : m_ColumnCapacity};

        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(helperMatrix.m_NrOfColumns, helperMatrix.m_NrOfRows, c_NewRowCapacity, c_NewColumnCapacity);

        // no use of _moveInitItems(), too much overhead
        for (size_type absRowNr{*m_RowCapacityOffset}, rowNr{0}; rowNr < c_NewNrOfRows; ++rowNr, ++absRowNr)
        {
            for (size_type helperMatrixAbsRowNr{*helperMatrix.m_RowCapacityOffset}, columnNr{0};
                 columnNr < c_NewNrOfColumns; ++columnNr, ++helperMatrixAbsRowNr)
            {
                std::uninitialized_move_n(helperMatrix.m_pBaseArrayPtr[helperMatrixAbsRowNr] + rowNr, 1,
                                          m_pBaseArrayPtr[absRowNr] + columnNr);
            }
        }
    }
}

template <MatrixElementType T> void Matrix<T>::clear()
{
    _deallocMemory();
}

template <MatrixElementType T> void Matrix<T>::resize(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const auto [c_NrOfRemainingRows,
                c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns)};

    // initialize new elements to the right side of the retained ones
    if (m_NrOfColumns > c_NrOfRemainingColumns)
    {
        _defaultConstructInitItems(0, c_NrOfRemainingColumns, c_NrOfRemainingRows,
                                   m_NrOfColumns - c_NrOfRemainingColumns);
    }

    // same for the ones below
    if (m_NrOfRows > c_NrOfRemainingRows)
    {
        _defaultConstructInitItems(c_NrOfRemainingRows, 0, nrOfRows - c_NrOfRemainingRows, m_NrOfColumns);
    }

    _normalizeRowCapacity();
}

template <MatrixElementType T>
void Matrix<T>::resize(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const auto [c_NrOfRemainingRows,
                c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns)};

    // initialize new elements to the right side of the retained ones
    if (m_NrOfColumns > c_NrOfRemainingColumns)
    {
        _fillInitItems(0, c_NrOfRemainingColumns, c_NrOfRemainingRows, m_NrOfColumns - c_NrOfRemainingColumns, value);
    }

    // same for the ones below
    if (m_NrOfRows > c_NrOfRemainingRows)
    {
        _fillInitItems(c_NrOfRemainingRows, 0, nrOfRows - c_NrOfRemainingRows, m_NrOfColumns, value);
    }

    _normalizeRowCapacity();
}

template <MatrixElementType T>
void Matrix<T>::reserve(Matrix<T>::size_type rowCapacity, Matrix<T>::size_type columnCapacity)
{
    if (!isEmpty())
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_NewRowCapacity{std::clamp<size_type>(rowCapacity, m_NrOfRows, c_MaxAllowedDimension)};
        const size_type c_NewColumnCapacity{
            std::clamp<size_type>(columnCapacity, m_NrOfColumns, c_MaxAllowedDimension)};

        if (m_RowCapacity != c_NewRowCapacity || m_ColumnCapacity != c_NewColumnCapacity)
        {
            Matrix matrix{std::move(*this)};

            _deallocMemory(); // actually not required, just for safety purposes
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

            // move the retained items back
            _moveInitItems(matrix, 0, 0, 0, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::shrinkToFit()
{
    if (m_RowCapacity != m_NrOfRows || m_ColumnCapacity != m_NrOfColumns)
    {
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // just for safety purposes, not actually needed
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::insertRow(Matrix<T>::size_type rowNr)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_default_construct_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns);
}

template <MatrixElementType T> void Matrix<T>::insertRow(Matrix<T>::size_type rowNr, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_fill_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns, value);
}

template <MatrixElementType T> void Matrix<T>::insertColumn(Matrix<T>::size_type columnNr)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + c_UninitializedColumnNr, 1);
    }

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating
    // uninitialized elements
    if (c_UninitializedColumnNr != columnNr)
    {
        if (0 == c_UninitializedColumnNr)
        {
            _rotateFirstColumn(columnNr);
        }
        else if (m_NrOfColumns - 1 == c_UninitializedColumnNr)
        {
            _rotateLastColumn(columnNr);
        }
        else
        {
            assert(false);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::insertColumn(Matrix<T>::size_type columnNr, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    _fillInitItems(0, c_UninitializedColumnNr, m_NrOfRows, 1, value);

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating
    // uninitialized elements
    if (c_UninitializedColumnNr != columnNr)
    {
        if (0 == c_UninitializedColumnNr)
        {
            _rotateFirstColumn(columnNr);
        }
        else if (m_NrOfColumns - 1 == c_UninitializedColumnNr)
        {
            _rotateLastColumn(columnNr);
        }
        else
        {
            assert(false);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::eraseRow(Matrix<T>::size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    if (1 == m_NrOfRows)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfRows{static_cast<size_type>(m_NrOfRows - 1)};
             c_RemainingNrOfRows <= m_RowCapacity / 4)
    {
        _reallocEraseDimensionElement(rowNr, true);
    }
    else
    {
        _shiftEraseRow(rowNr);
    }
}

template <MatrixElementType T> void Matrix<T>::eraseColumn(Matrix<T>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (1 == m_NrOfColumns)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfColumns{static_cast<size_type>(m_NrOfColumns - 1)};
             c_RemainingNrOfColumns <= m_ColumnCapacity / 4)
    {
        _reallocEraseDimensionElement(columnNr, false);
    }
    else
    {
        _shiftEraseColumn(columnNr);
    }
}

template <MatrixElementType T> void Matrix<T>::catByRow(Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        CHECK_ERROR_CONDITION(m_NrOfColumns != matrix.m_NrOfColumns,
                              Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_ROW_LENGTH]);
    }

    const size_type c_OldNrOfRows{m_NrOfRows};
    const size_type c_NewNrOfRows{static_cast<size_type>(m_NrOfRows + matrix.m_NrOfRows)};

    CHECK_ERROR_CONDITION(c_NewNrOfRows > maxAllowedDimension(),
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    if (c_NewNrOfRows <= m_RowCapacity)
    {
        _alignToTop();
        m_NrOfRows = c_NewNrOfRows;

        if (&matrix != this)
        {
            _moveInitItems(matrix, 0, 0, c_OldNrOfRows, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
        else
        {
            _copyInitItems(*this, 0, 0, c_OldNrOfRows, 0, c_OldNrOfRows, m_NrOfColumns);
        }

        _normalizeRowCapacity();
    }
    else
    {
        const size_type c_OldColumnCapacity{m_ColumnCapacity};
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(c_NewNrOfRows, helperMatrix.m_NrOfColumns, c_NewNrOfRows, c_OldColumnCapacity);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);

        if (&matrix != this)
        {
            _moveInitItems(matrix, 0, 0, c_OldNrOfRows, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
        else
        {
            _copyInitItems(*this, 0, 0, c_OldNrOfRows, 0, c_OldNrOfRows, m_NrOfColumns);
        }
    }

    // clear the source matrix as its content is no longer usable
    if (&matrix != this)
    {
        matrix._deallocMemory();
    }
}

template <MatrixElementType T> void Matrix<T>::catByColumn(Matrix& matrix)
{
    if (&matrix != this)
    {
        CHECK_ERROR_CONDITION(m_NrOfRows != matrix.m_NrOfRows,
                              Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH]);
    }

    const size_type c_OldNrOfColumns{m_NrOfColumns};
    const size_type c_NewNrOfColumns{static_cast<size_type>(m_NrOfColumns + matrix.m_NrOfColumns)};

    CHECK_ERROR_CONDITION(c_NewNrOfColumns > maxAllowedDimension(),
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    if (!matrix.isEmpty())
    {
        if (c_NewNrOfColumns <= m_ColumnCapacity)
        {
            const size_type c_ColumnConcatenationSpace{
                static_cast<size_type>(m_ColumnCapacity - *m_ColumnCapacityOffset)};

            // if not enough available capacity on the right side, then the columns should be shifted left by the
            // minimal count of positions that ensure the concatenated content fits
            if (c_NewNrOfColumns > c_ColumnConcatenationSpace)
            {
                const size_type c_NrOfColumnsToShiftLeft{
                    static_cast<size_type>(c_NewNrOfColumns - c_ColumnConcatenationSpace)};
                _shiftColumnsLeft(c_NrOfColumnsToShiftLeft);
            }

            m_NrOfColumns = c_NewNrOfColumns;

            if (&matrix != this)
            {
                _moveInitItems(matrix, 0, 0, 0, c_OldNrOfColumns, matrix.m_NrOfRows, matrix.m_NrOfColumns);
            }
            else
            {
                _copyInitItems(*this, 0, 0, 0, c_OldNrOfColumns, m_NrOfRows, c_OldNrOfColumns);
            }
        }
        else
        {
            const size_type c_OldRowCapacity{m_RowCapacity};
            const size_type c_NewColumnCapacity{std::max(m_ColumnCapacity, c_NewNrOfColumns)};

            Matrix helperMatrix{std::move(*this)};

            _deallocMemory(); // actually not required, just for safety purposes
            _allocMemory(helperMatrix.m_NrOfRows, c_NewNrOfColumns, c_OldRowCapacity, c_NewColumnCapacity);

            _moveInitItems(helperMatrix, 0, 0, 0, 0, helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);

            if (&matrix != this)
            {
                _moveInitItems(matrix, 0, 0, 0, c_OldNrOfColumns, matrix.m_NrOfRows, matrix.m_NrOfColumns);
            }
            else
            {
                _copyInitItems(*this, 0, 0, 0, c_OldNrOfColumns, m_NrOfRows, c_OldNrOfColumns);
            }
        }

        // clear the source matrix as its content is no longer usable
        if (&matrix != this)
        {
            matrix._deallocMemory();
        }
    }
}

template <MatrixElementType T> void Matrix<T>::splitByRow(Matrix& matrix, size_type splitRowNr)
{
    CHECK_ERROR_CONDITION(&matrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARGUMENT]);
    CHECK_ERROR_CONDITION(splitRowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(0 == splitRowNr, Matr::errorMessages[Matr::Errors::RESULT_NO_ROWS]);

    const size_type c_NewDestNrOfRows{static_cast<size_type>(m_NrOfRows - splitRowNr)};
    const size_type c_NewDestRowCapacity{std::max<size_type>(matrix.m_RowCapacity, c_NewDestNrOfRows)};
    const size_type c_NewDestColumnCapacity{std::max<size_type>(matrix.m_ColumnCapacity, m_NrOfColumns)};

    if (matrix.isEmpty() || c_NewDestRowCapacity > matrix.m_RowCapacity ||
        c_NewDestColumnCapacity > matrix.m_ColumnCapacity)
    {
        matrix._deallocMemory();
        matrix._allocMemory(c_NewDestNrOfRows, m_NrOfColumns, c_NewDestRowCapacity, c_NewDestColumnCapacity);
    }
    else
    {
        matrix._remapMemory(c_NewDestNrOfRows, m_NrOfColumns);
    }

    matrix._moveInitItems(*this, splitRowNr, 0, 0, 0, c_NewDestNrOfRows, m_NrOfColumns);

    _destroyItems(splitRowNr, 0, c_NewDestNrOfRows, m_NrOfColumns);
    m_NrOfRows = splitRowNr;
    _normalizeRowCapacity();
}

template <MatrixElementType T> void Matrix<T>::splitByColumn(Matrix& matrix, size_type splitColumnNr)
{
    CHECK_ERROR_CONDITION(&matrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARGUMENT]);
    CHECK_ERROR_CONDITION(splitColumnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(0 == splitColumnNr, Matr::errorMessages[Matr::Errors::RESULT_NO_COLUMNS]);

    const size_type c_NewDestNrOfColumns{static_cast<size_type>(m_NrOfColumns - splitColumnNr)};
    const size_type c_NewDestRowCapacity{std::max<size_type>(matrix.m_RowCapacity, m_NrOfRows)};
    const size_type c_NewDestColumnCapacity{std::max<size_type>(matrix.m_ColumnCapacity, c_NewDestNrOfColumns)};

    if (matrix.isEmpty() || c_NewDestRowCapacity > matrix.m_RowCapacity ||
        c_NewDestColumnCapacity > matrix.m_ColumnCapacity)
    {
        matrix._deallocMemory();
        matrix._allocMemory(m_NrOfRows, c_NewDestNrOfColumns, c_NewDestRowCapacity, c_NewDestColumnCapacity);
    }
    else
    {
        matrix._remapMemory(m_NrOfRows, c_NewDestNrOfColumns);
    }

    matrix._moveInitItems(*this, 0, splitColumnNr, 0, 0, m_NrOfRows, c_NewDestNrOfColumns);

    _destroyItems(0, splitColumnNr, m_NrOfRows, c_NewDestNrOfColumns);
    m_NrOfColumns = splitColumnNr;
}

template <MatrixElementType T>
void Matrix<T>::swapRows(Matrix<T>::size_type firstRowNr, Matrix<T>::size_type secondRowNr)
{
    CHECK_ERROR_CONDITION(firstRowNr >= m_NrOfRows || secondRowNr >= m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    const size_type c_FirstAbsRowNr{static_cast<size_type>(*m_RowCapacityOffset + firstRowNr)};
    const size_type c_SecondAbsRowNr{static_cast<size_type>(*m_RowCapacityOffset + secondRowNr)};

    if (c_FirstAbsRowNr != c_SecondAbsRowNr)
    {
        // exchanging row pointers is enough and greatly optimizes the speed of execution
        std::swap(m_pBaseArrayPtr[c_FirstAbsRowNr], m_pBaseArrayPtr[c_SecondAbsRowNr]);
    }
}

template <MatrixElementType T>
void Matrix<T>::swapColumns(Matrix<T>::size_type firstColumnNr, Matrix<T>::size_type secondColumnNr)
{
    CHECK_ERROR_CONDITION(firstColumnNr >= m_NrOfColumns || secondColumnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (firstColumnNr != secondColumnNr)
    {
        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::swap(m_pBaseArrayPtr[absRowNr][firstColumnNr], m_pBaseArrayPtr[absRowNr][secondColumnNr]);
        }
    }
}

template <MatrixElementType T> bool Matrix<T>::operator==(const Matrix<T>& matrix) const
{
    bool areEqual{true};

    if (&matrix != this)
    {
        // matrix emptiness should be checked first in order to avoid accessing (std::optional) capacity offsets of
        // empty matrixes (see second case: "else if")
        if (const bool isCurrentMatrixEmpty{isEmpty()}, isOtherMatrixEmpty{matrix.isEmpty()};
            isCurrentMatrixEmpty || isOtherMatrixEmpty)
        {
            areEqual = isCurrentMatrixEmpty && isOtherMatrixEmpty;
        }
        else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}, matrixAbsRowNr{*matrix.m_RowCapacityOffset};
                 absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr, ++matrixAbsRowNr)
            {
                areEqual = areEqual && std::equal(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + m_NrOfColumns,
                                                  matrix.m_pBaseArrayPtr[matrixAbsRowNr]);

                if (!areEqual)
                {
                    break;
                }
            }
        }
        else
        {
            areEqual = false;
        }
    }

    return areEqual;
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zEnd()
{
    GET_FORWARD_END_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                              m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zRowBegin(Matrix<T>::size_type rowNr)
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zRowEnd(Matrix<T>::size_type rowNr)
{
    GET_FORWARD_ROW_END_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ZIterator Matrix<T>::getZIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::constZBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::constZEnd() const
{
    GET_FORWARD_END_ZITERATOR(ConstZIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::constZRowBegin(Matrix<T>::size_type rowNr) const
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ConstZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::constZRowEnd(Matrix<T>::size_type rowNr) const
{
    GET_FORWARD_ROW_END_ZITERATOR(ConstZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::getConstZIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZEnd()
{
    GET_REVERSE_END_ZITERATOR(ReverseZIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZRowBegin(Matrix<T>::size_type rowNr)
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ReverseZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZRowEnd(Matrix<T>::size_type rowNr)
{
    GET_REVERSE_ROW_END_ZITERATOR(ReverseZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::getReverseZIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZEnd() const
{
    GET_REVERSE_END_ZITERATOR(ConstReverseZIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZRowBegin(Matrix<T>::size_type rowNr) const
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ConstReverseZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZRowEnd(Matrix<T>::size_type rowNr) const
{
    GET_REVERSE_ROW_END_ZITERATOR(ConstReverseZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::getConstReverseZIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(NIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nEnd()
{
    GET_FORWARD_END_NITERATOR(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                              m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nColumnBegin(Matrix<T>::size_type columnNr)
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(NIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nColumnEnd(Matrix<T>::size_type columnNr)
{
    GET_FORWARD_COLUMN_END_NITERATOR(NIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator Matrix<T>::getNIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::constNBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::constNEnd() const
{
    GET_FORWARD_END_NITERATOR(ConstNIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::constNColumnBegin(Matrix<T>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(ConstNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::constNColumnEnd(Matrix<T>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_END_NITERATOR(ConstNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::getConstNIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNEnd()
{
    GET_REVERSE_END_NITERATOR(ReverseNIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNColumnBegin(Matrix<T>::size_type columnNr)
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ReverseNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNColumnEnd(Matrix<T>::size_type columnNr)
{
    GET_REVERSE_COLUMN_END_NITERATOR(ReverseNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::getReverseNIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNEnd() const
{
    GET_REVERSE_END_NITERATOR(ConstReverseNIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNColumnBegin(Matrix<T>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ConstReverseNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNColumnEnd(Matrix<T>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_END_NITERATOR(ConstReverseNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::getConstReverseNIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::dBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::dBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::dEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(DIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::dEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::getDIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::getDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDBegin(Matrix<T>::size_type rowNr,
                                                          Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::getConstDIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::getConstDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseDIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ReverseDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::getReverseDIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseDIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::getReverseDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseDIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDBegin(Matrix<T>::size_type rowNr,
                                                                        Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstReverseDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDEnd(Matrix<T>::size_type rowNr,
                                                                      Matrix<T>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::getConstReverseDIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseDIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::getConstReverseDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::mBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::mBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::mEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(MIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::mEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::getMIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::getMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMBegin(Matrix<T>::size_type rowNr,
                                                          Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::getConstMIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::getConstMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseMIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ReverseMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::getReverseMIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseMIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::getReverseMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseMIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMBegin(Matrix<T>::size_type rowNr,
                                                                        Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMEnd(Matrix<T>::diff_type diagonaNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstReverseMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonaNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMEnd(Matrix<T>::size_type rowNr,
                                                                      Matrix<T>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::getConstReverseMIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseMIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::getConstReverseMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::begin()
{
    return zBegin();
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::end()
{
    return zEnd();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::begin() const
{
    return constZBegin();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::end() const
{
    return constZEnd();
}

template <MatrixElementType T>
std::pair<typename Matrix<T>::size_type, typename Matrix<T>::size_type> Matrix<T>::_resizeWithUninitializedNewElements(
    Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    assert(nrOfRows <= maxAllowedDimension() && nrOfColumns <= maxAllowedDimension());

    const size_type c_NewNrOfRows{(nrOfRows > size_type{0} && nrOfColumns > size_type{0}) ? nrOfRows : size_type{0}};
    const size_type c_NewNrOfColumns{c_NewNrOfRows > size_type{0} ? nrOfColumns : size_type{0}};
    const size_type c_NewRowCapacity{std::max(m_RowCapacity, c_NewNrOfRows)};
    const size_type c_NewColumnCapacity{std::max(m_ColumnCapacity, c_NewNrOfColumns)};
    const size_type c_NrOfRowsToKeep{std::min(m_NrOfRows, c_NewNrOfRows)};
    const size_type c_NrOfColumnsToKeep{std::min(m_NrOfColumns, c_NewNrOfColumns)};
    const std::optional<size_type> c_NewRowCapacityOffset{
        c_NewNrOfRows > 0 ? std::optional((c_NewRowCapacity - c_NewNrOfRows) / 2) : std::nullopt};

    if (!m_RowCapacityOffset.has_value() /* empty matrix, column capacity offset std::nullopt as well */ ||
        !c_NewRowCapacityOffset.has_value() || c_NewRowCapacity != m_RowCapacity ||
        c_NewColumnCapacity != m_ColumnCapacity)
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(c_NewNrOfRows, c_NewNrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

        // move the retained items back
        _moveInitItems(matrix, 0, 0, 0, 0, c_NrOfRowsToKeep, c_NrOfColumnsToKeep);
    }
    else
    {
        const size_type c_ColumnsResizingSpace{static_cast<size_type>(m_ColumnCapacity - *m_ColumnCapacityOffset)};

        // if not enough available capacity on the right side, then the columns should be shifted left by the minimal
        // count of positions that ensure the resized content fits
        if (c_NewNrOfColumns > c_ColumnsResizingSpace)
        {
            const size_type c_NrOfColumnsToShiftLeft{static_cast<size_type>(c_NewNrOfColumns - c_ColumnsResizingSpace)};
            _shiftColumnsLeft(c_NrOfColumnsToShiftLeft);
        }

        // move unused top capacity to the bottom to avoid alignment issues (should be re-distributed once resize is
        // complete)
        _alignToTop();

        // ensure the items from the right side of the retained items get properly destroyed
        if (c_NewNrOfColumns < m_NrOfColumns)
        {
            _destroyItems(0, c_NrOfColumnsToKeep, c_NrOfRowsToKeep, m_NrOfColumns - c_NewNrOfColumns);
        }

        // same for the items below
        if (c_NewNrOfRows < m_NrOfRows)
        {
            _destroyItems(c_NrOfRowsToKeep, 0, m_NrOfRows - c_NewNrOfRows, m_NrOfColumns);
        }

        m_NrOfRows = c_NewNrOfRows;
        m_NrOfColumns = c_NewNrOfColumns;
    }

    return {c_NrOfRowsToKeep, c_NrOfColumnsToKeep};
}

template <MatrixElementType T> void Matrix<T>::_insertUninitializedRow(Matrix<T>::size_type rowNr)
{
    const size_type c_RowNr{std::clamp<size_type>(rowNr, 0u, m_NrOfRows)};

    // double the row capacity (without exceeding the maximum allowed capacity) if no spare capacity left (to defer any
    // resize when inserting further rows)
    if (m_NrOfRows == m_RowCapacity)
    {
        Matrix helperMatrix{std::move(*this)};
        const size_type c_NewRowCapacity{
            std::min(static_cast<size_type>(size_type{2} * helperMatrix.m_NrOfRows), maxAllowedDimension())};

        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows + 1, helperMatrix.m_NrOfColumns, c_NewRowCapacity,
                     helperMatrix.m_ColumnCapacity);

        // move everything back to the top/bottom of the inserted row (this one stays uninitialized - will be
        // initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_RowNr, m_NrOfColumns);
        _moveInitItems(helperMatrix, c_RowNr, 0, c_RowNr + 1, 0, m_NrOfRows - c_RowNr, m_NrOfColumns);
    }
    else
    {
        // row capacity offset cannot be std::nullopt as the matrix is not empty (rows count doesn't equal row capacity)
        const bool c_ShouldAppendRow{c_RowNr <= m_NrOfRows / 2 ? (0 == *m_RowCapacityOffset)
                                                               : (m_RowCapacity - *m_RowCapacityOffset > m_NrOfRows)};
        ++m_NrOfRows;

        T** pCurrentMatrixStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        // new row is initially first/last row (depending on the insert position), move it into the insert position (all
        // rows after the insert position moved one position downwards/upwards)
        if (c_ShouldAppendRow)
        {
            std::rotate(pCurrentMatrixStartingRow + c_RowNr, pCurrentMatrixStartingRow + m_NrOfRows - 1,
                        pCurrentMatrixStartingRow + m_NrOfRows);
        }
        else
        {
            m_RowCapacityOffset = *m_RowCapacityOffset - 1;
            --pCurrentMatrixStartingRow;
            std::rotate(pCurrentMatrixStartingRow, pCurrentMatrixStartingRow + 1,
                        pCurrentMatrixStartingRow + c_RowNr + 1);
        }
    }
}

template <MatrixElementType T>
typename Matrix<T>::size_type Matrix<T>::_insertUninitializedColumn(Matrix<T>::size_type columnNr)
{
    size_type resultingColumnNr{std::clamp<size_type>(columnNr, 0u, m_NrOfColumns)};

    // double the column capacity (without exceeding the maximum allowed capacity) if no spare capacity left (to defer
    // any resize when inserting further columns)
    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix helperMatrix{std::move(*this)};
        const size_type c_NewColumnCapacity{
            std::min(static_cast<size_type>(size_type{2} * helperMatrix.m_NrOfColumns), maxAllowedDimension())};

        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns + 1, helperMatrix.m_RowCapacity,
                     c_NewColumnCapacity);

        // move everything back to the left/right of the inserted column (this one stays uninitialized - will be
        // initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, resultingColumnNr);
        _moveInitItems(helperMatrix, 0, resultingColumnNr, 0, resultingColumnNr + 1, m_NrOfRows,
                       m_NrOfColumns - resultingColumnNr);
    }
    else
    {
        // row capacity offset cannot be std::nullopt as the matrix is not empty (columns count doesn't equal column
        // capacity)
        const bool c_ShouldAppendColumn{resultingColumnNr <= m_NrOfColumns / 2
                                            ? (0 == m_ColumnCapacityOffset)
                                            : (m_ColumnCapacity - *m_ColumnCapacityOffset > m_NrOfColumns)};

        if (c_ShouldAppendColumn)
        {
            resultingColumnNr = m_NrOfColumns;
        }
        else
        {
            resultingColumnNr = 0;
            m_ColumnCapacityOffset = *m_ColumnCapacityOffset - 1;

            // make the newly added column visible
            for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
            {
                --m_pBaseArrayPtr[rowNr];
            }
        }

        ++m_NrOfColumns;
    }

    return resultingColumnNr;
}

template <MatrixElementType T>
void Matrix<T>::_reallocEraseDimensionElement(Matrix<T>::size_type dimensionElementNr, bool isRow)
{
    if (!isEmpty())
    {
        const size_type c_RequiredNrOfRows{isRow ? static_cast<size_type>(m_NrOfRows - 1) : m_NrOfRows};
        const size_type c_RequiredNrOfColumns{isRow ? m_NrOfColumns : static_cast<size_type>(m_NrOfColumns - 1)};
        const size_type c_RequiredRowCapacity{isRow ? static_cast<size_type>(size_type{2} * c_RequiredNrOfRows)
                                                    : m_RowCapacity};
        const size_type c_RequiredColumnCapacity{isRow ? m_ColumnCapacity
                                                       : static_cast<size_type>(size_type{2} * c_RequiredNrOfColumns)};

        // row or column nr depending on scenario (variable isRow)
        const size_type c_DimensionElementNr{
            std::clamp<size_type>(dimensionElementNr, 0u, isRow ? c_RequiredNrOfRows : c_RequiredNrOfColumns)};

        // part one: top part (rows) / left part (columns) - relative to erased row/column
        const size_type c_PartOneNrOfRows{isRow ? c_DimensionElementNr : c_RequiredNrOfRows};
        const size_type c_PartOneNrOfColumns{isRow ? c_RequiredNrOfColumns : c_DimensionElementNr};

        // part two: bottom part (rows) / right part (columns) - relative to erased row/column
        const size_type c_PartTwoSrcStartingRowNr{isRow ? static_cast<size_type>(c_DimensionElementNr + 1)
                                                        : size_type{0}};
        const size_type c_PartTwoSrcColumnOffset{
            static_cast<size_type>(c_DimensionElementNr + 1 - c_PartTwoSrcStartingRowNr)};
        const size_type c_PartTwoStartingRowNr{isRow ? c_DimensionElementNr : size_type{0}};
        const size_type c_PartTwoColumnOffset{static_cast<size_type>(c_DimensionElementNr - c_PartTwoStartingRowNr)};
        const size_type c_PartTwoNrOfRows{static_cast<size_type>(c_RequiredNrOfRows - c_PartTwoStartingRowNr)};
        const size_type c_PartTwoNrOfColumns{static_cast<size_type>(c_RequiredNrOfColumns - c_PartTwoColumnOffset)};

        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not really necessary, just for safety purposes
        _allocMemory(c_RequiredNrOfRows, c_RequiredNrOfColumns, c_RequiredRowCapacity, c_RequiredColumnCapacity);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_PartOneNrOfRows, c_PartOneNrOfColumns);
        _moveInitItems(helperMatrix, c_PartTwoSrcStartingRowNr, c_PartTwoSrcColumnOffset, c_PartTwoStartingRowNr,
                       c_PartTwoColumnOffset, c_PartTwoNrOfRows, c_PartTwoNrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::_shiftEraseRow(Matrix<T>::size_type rowNr)
{
    if (!isEmpty())
    {
        const size_type c_RowNr{std::clamp<size_type>(rowNr, 0u, m_NrOfRows - 1)};
        T** pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        if (c_RowNr < m_NrOfRows / 2)
        {
            std::rotate(pStartingRow, pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset],
                           m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
            m_RowCapacityOffset = *m_RowCapacityOffset + 1;
        }
        else
        {
            std::rotate(pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1, pStartingRow + m_NrOfRows);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset + m_NrOfRows - 1],
                           m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
        }

        --m_NrOfRows;
    }
}

template <MatrixElementType T> void Matrix<T>::_shiftEraseColumn(Matrix<T>::size_type columnNr)
{
    if (!isEmpty())
    {
        const size_type c_ColumnNr{std::clamp<size_type>(columnNr, 0u, m_NrOfColumns - 1)};

        if (c_ColumnNr < m_NrOfColumns / 2)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + c_ColumnNr,
                            m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1);
                std::destroy_n(m_pBaseArrayPtr[absRowNr], 1);
            }

            for (size_type absRowNr{0}; absRowNr < m_RowCapacity; ++absRowNr)
            {
                ++m_pBaseArrayPtr[absRowNr];
            }

            m_ColumnCapacityOffset = *m_ColumnCapacityOffset + 1;
        }
        else
        {
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr] + c_ColumnNr, m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1,
                            m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
                std::destroy_n(m_pBaseArrayPtr[absRowNr] + m_NrOfColumns - 1,
                               1); // the memory outside matrix bounds should be uninitialized
            }
        }

        --m_NrOfColumns;
    }
}

template <MatrixElementType T> void Matrix<T>::_rotateFirstColumn(size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_NewColumnNr{std::clamp<size_type>(newColumnNr, 0u, m_NrOfColumns)};

        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + 1,
                        m_pBaseArrayPtr[absRowNr] + c_NewColumnNr + 1);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::_rotateLastColumn(Matrix<T>::size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_LastColumnNr{static_cast<size_type>(m_NrOfColumns - 1)};
        const size_type c_NewColumnNr{std::clamp<size_type>(newColumnNr, 0u, c_LastColumnNr)};

        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr] + c_NewColumnNr, m_pBaseArrayPtr[absRowNr] + c_LastColumnNr,
                        m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
        }
    }
}

// if shifting of columns is involved, then this method should be called after the columns shifting function (e.g.
// _shiftColumnsLeft(), see below)
template <MatrixElementType T> void Matrix<T>::_alignToTop()
{
    if (m_RowCapacityOffset.has_value() && m_RowCapacityOffset > 0)
    {
        std::rotate(m_pBaseArrayPtr, m_pBaseArrayPtr + *m_RowCapacityOffset,
                    m_pBaseArrayPtr + *m_RowCapacityOffset + m_NrOfRows);
        m_RowCapacityOffset = 0;
    }
}

// columns shifting should be performed before aligning to top (see above)
template <MatrixElementType T> void Matrix<T>::_shiftColumnsLeft(Matrix<T>::size_type nrOfPositionsToShift)
{
    if (m_ColumnCapacityOffset.has_value())
    {
        nrOfPositionsToShift = std::clamp<size_type>(nrOfPositionsToShift, 0, *m_ColumnCapacityOffset);
        m_ColumnCapacityOffset = *m_ColumnCapacityOffset - nrOfPositionsToShift;

        const size_type c_OldNrOfColumns{m_NrOfColumns};

        // Step 1: move row start to the left, get an additional count of uninitialized columns ("new" columns)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
        }

        m_NrOfColumns += nrOfPositionsToShift;

        const size_type c_FirstOldColumnNr = nrOfPositionsToShift;
        const size_type c_NrOfColumnsToInitialize{std::min(nrOfPositionsToShift, c_OldNrOfColumns)};

        // Step 2: initialize as many new columns as possible by moving the content of the existing ("old") ones
        _moveInitItems(*this, 0, c_FirstOldColumnNr, 0, 0, m_NrOfRows, c_NrOfColumnsToInitialize);

        // Step 3: any old columns that were not consumed for initializing the additional ones should be moved near the
        // new columns to complete shifting; consumed columns should be destroyed
        if (c_NrOfColumnsToInitialize < c_OldNrOfColumns)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr] + nrOfPositionsToShift,
                            m_pBaseArrayPtr[absRowNr] +
                                static_cast<size_type>(nrOfPositionsToShift + c_NrOfColumnsToInitialize),
                            m_pBaseArrayPtr[absRowNr] + nrOfPositionsToShift + c_OldNrOfColumns);
            }

            _destroyItems(0, c_OldNrOfColumns, m_NrOfRows, c_NrOfColumnsToInitialize);
        }
        else
        {
            _destroyItems(0, nrOfPositionsToShift, m_NrOfRows, c_OldNrOfColumns);
        }

        // at the end of the shifting operation the matrix should have the same number of columns as before
        m_NrOfColumns = c_OldNrOfColumns;
    }
}

template <MatrixElementType T> void Matrix<T>::_normalizeRowCapacity()
{
    const std::optional<size_type> c_NormalizedRowCapacityOffset{
        m_NrOfRows > 0 ? std::optional((m_RowCapacity - m_NrOfRows) / 2) : std::nullopt};

    if (m_RowCapacityOffset.has_value() &&
        (c_NormalizedRowCapacityOffset.has_value() && c_NormalizedRowCapacityOffset > 0) &&
        m_RowCapacityOffset < c_NormalizedRowCapacityOffset)
    {
        const size_type c_LastRowNr{static_cast<size_type>(m_NrOfRows - 1)};
        T** const pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};
        T** const pEndingRow{pStartingRow + c_LastRowNr};
        T** const pStartingRowToReplace{m_pBaseArrayPtr + *c_NormalizedRowCapacityOffset};
        T** const pEndingRowToReplace{pStartingRowToReplace + c_LastRowNr};

        T** pRowToReplace{pEndingRowToReplace};

        for (T** pCurrentRow{pEndingRow}; pCurrentRow >= pStartingRow; --pCurrentRow)
        {
            std::iter_swap(pCurrentRow, pRowToReplace);
            --pRowToReplace;
        }

        m_RowCapacityOffset = c_NormalizedRowCapacityOffset;
    }
}

template <MatrixElementType T>
void Matrix<T>::_allocMemory(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns,
                             Matrix<T>::size_type rowCapacity, Matrix<T>::size_type columnCapacity)
{
    if (nrOfRows > 0 && nrOfColumns > 0)
    {
        m_RowCapacity = rowCapacity < nrOfRows ? nrOfRows : rowCapacity;
        m_ColumnCapacity = columnCapacity < nrOfColumns ? nrOfColumns : columnCapacity;

        m_RowCapacityOffset = (m_RowCapacity - nrOfRows) / 2;
        m_ColumnCapacityOffset = (m_ColumnCapacity - nrOfColumns) / 2;

        m_pBaseArrayPtr = static_cast<T**>(std::malloc(m_RowCapacity * sizeof(T*)));
        m_pAllocPtr = static_cast<T*>(std::malloc(m_RowCapacity * m_ColumnCapacity * sizeof(T)));

        // map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed, left
        // free column capacity excluded)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
        }

        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;
    }
    else
    {
        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
        m_RowCapacityOffset.reset();
        m_ColumnCapacityOffset.reset();
        m_pBaseArrayPtr = nullptr;
        m_pAllocPtr = nullptr;
    }
}

template <MatrixElementType T> void Matrix<T>::_deallocMemory()
{
    if (!isEmpty())
    {
        // ensure the objects contained within matrix are properly disposed (no column capacity offset provided as
        // argument -> free left capacity excluded by m_pBaseArrayPtr pointer elements)
        _destroyItems(*m_RowCapacityOffset, 0, m_NrOfRows, m_NrOfColumns);

        // cut access of row pointers to allocated memory
        std::fill_n(m_pBaseArrayPtr, m_RowCapacity, nullptr);

        std::free(m_pBaseArrayPtr);
        m_pBaseArrayPtr = nullptr;

        std::free(m_pAllocPtr);
        m_pAllocPtr = nullptr;

        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
        m_RowCapacityOffset.reset();
        m_ColumnCapacityOffset.reset();
    }
}

// This method should be executed only for already initialized memory; the memory should be subsequently re-initialized
// by running another function
template <MatrixElementType T>
void Matrix<T>::_remapMemory(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (!isEmpty())
    {
        nrOfRows = std::clamp<size_type>(nrOfRows, 1, m_RowCapacity);
        nrOfColumns = std::clamp<size_type>(nrOfColumns, 1, m_ColumnCapacity);

        _destroyItems(0, 0, m_NrOfRows, m_NrOfColumns);

        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;

        // capacity gets distributed in an even manner as for new allocations (unused capacity equally distributed
        // between left/right and top/bottom)
        m_RowCapacityOffset = (m_RowCapacity - m_NrOfRows) / 2;
        m_ColumnCapacityOffset = (m_ColumnCapacity - m_NrOfColumns) / 2;

        // re-map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed,
        // left free column capacity excluded)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
        }
    }
}

template <MatrixElementType T> void Matrix<T>::_copyAssignMatrix(const Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_RowCapacityToAlloc{
            std::min(static_cast<size_type>(matrix.m_NrOfRows + matrix.m_NrOfRows / 4), c_MaxAllowedDimension)};
        const size_type c_ColumnCapacityToAlloc{
            std::min(static_cast<size_type>(matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4), c_MaxAllowedDimension)};

        if (matrix.isEmpty())
        {
            _deallocMemory();
        }
        else if (m_RowCapacity != c_RowCapacityToAlloc || m_ColumnCapacity != c_ColumnCapacityToAlloc)
        {
            _deallocMemory();
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
        }
        else
        {
            _remapMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }

        _copyInitItems(matrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::_moveAssignMatrix(Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        _deallocMemory();

        m_pAllocPtr = matrix.m_pAllocPtr;
        m_pBaseArrayPtr = matrix.m_pBaseArrayPtr;
        m_NrOfRows = matrix.m_NrOfRows;
        m_NrOfColumns = matrix.m_NrOfColumns;
        m_RowCapacity = matrix.m_RowCapacity;
        m_ColumnCapacity = matrix.m_ColumnCapacity;
        m_RowCapacityOffset = matrix.m_RowCapacityOffset;
        m_ColumnCapacityOffset = matrix.m_ColumnCapacityOffset;

        matrix._allocMemory(0, 0);
    }
}

template <MatrixElementType T>
void Matrix<T>::_copyInitItems(const Matrix<T>& matrix, Matrix<T>::size_type matrixStartingRowNr,
                               Matrix<T>::size_type matrixColumnOffset, Matrix<T>::size_type startingRowNr,
                               Matrix<T>::size_type columnOffset, Matrix<T>::size_type nrOfRows,
                               Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value() && matrix.m_RowCapacityOffset.has_value())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr,
                                                   columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)},
             srcAbsRowNr{static_cast<size_type>(*matrix.m_RowCapacityOffset + matrixStartingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_copy_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns,
                                      m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_moveInitItems(Matrix<T>& matrix, Matrix<T>::size_type matrixStartingRowNr,
                               Matrix<T>::size_type matrixColumnOffset, Matrix<T>::size_type startingRowNr,
                               Matrix<T>::size_type columnOffset, Matrix<T>::size_type nrOfRows,
                               Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value() && matrix.m_RowCapacityOffset.has_value())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr,
                                                   columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)},
             srcAbsRowNr{static_cast<size_type>(*matrix.m_RowCapacityOffset + matrixStartingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_move_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns,
                                      m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_fillInitItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                               Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, const T& value)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::uninitialized_fill_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns, value);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_defaultConstructInitItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                                           Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_destroyItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                              Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::destroy_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_clampSubMatrixSelectionParameters(Matrix<T>::size_type& startingRowNr,
                                                   Matrix<T>::size_type& columnOffset, Matrix<T>::size_type& nrOfRows,
                                                   Matrix<T>::size_type& nrOfColumns)
{
    startingRowNr = std::clamp<size_type>(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp<size_type>(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp<size_type>(nrOfRows, 0u, m_NrOfRows - startingRowNr);
    nrOfColumns = std::clamp<size_type>(nrOfColumns, 0u, m_NrOfColumns - columnOffset);
}

template <MatrixElementType T>
void Matrix<T>::_externalClampSubMatrixSelectionParameters(
    const Matrix<T>& srcMatrix, Matrix<T>::size_type& srcStartingRowNr, Matrix<T>::size_type& srcColumnOffset,
    Matrix<T>::size_type& startingRowNr, Matrix<T>::size_type& columnOffset, Matrix<T>::size_type& nrOfRows,
    Matrix<T>::size_type& nrOfColumns)
{
    srcStartingRowNr = std::clamp<size_type>(srcStartingRowNr, 0u, srcMatrix.m_NrOfRows);
    srcColumnOffset = std::clamp<size_type>(srcColumnOffset, 0u, srcMatrix.m_NrOfColumns);
    startingRowNr = std::clamp<size_type>(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp<size_type>(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp<size_type>(nrOfRows, 0u,
                                     std::min(srcMatrix.m_NrOfRows - srcStartingRowNr, m_NrOfRows - startingRowNr));
    nrOfColumns = std::clamp<size_type>(
        nrOfColumns, 0u, std::min(srcMatrix.m_NrOfColumns - srcColumnOffset, m_NrOfColumns - columnOffset));
}

template <MatrixElementType T> void* Matrix<T>::_convertToArray(Matrix<T>::size_type& nrOfElements)
{
    // effective transfer of ownership (items - including uninitalized ones)
    void* pAllocPtr{m_pAllocPtr};
    nrOfElements = m_RowCapacity * m_ColumnCapacity;

    // delete the matrix row pointers
    std::free(m_pBaseArrayPtr);

    // reset all internal variables to bring the matrix to empty state
    m_pBaseArrayPtr = nullptr;
    m_pAllocPtr = nullptr;
    m_NrOfRows = 0;
    m_NrOfColumns = 0;
    m_RowCapacity = 0;
    m_ColumnCapacity = 0;
    m_RowCapacityOffset.reset();
    m_ColumnCapacityOffset.reset();

    return pAllocPtr;
}
