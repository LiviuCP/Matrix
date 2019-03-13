#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include <utility>

#include "matrix_exceptions.h"

template <typename DataType>
class Matrix
{
public: 
    using size_type = int;
    using diff_type = int;

    Matrix();
    Matrix(size_type nrOfRows, size_type nrOfColumns, std::initializer_list<DataType> dataTypeInitList);
    Matrix(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType);
    Matrix(size_type nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues);
    Matrix(const Matrix<DataType>& matrix);
    Matrix(Matrix<DataType>&& matrix);
    ~Matrix();

    DataType& at(size_type rowNr, size_type columnNr);
    DataType& operator[] (size_type index);

    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    Matrix<DataType>& operator= (Matrix<DataType>&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    DataType** getBaseArrayPtr(size_type& nrOfRows, size_type& nrOfColumns, size_type& rowCapacity, size_type& columnCapacity);
	
    size_type getNrOfRows() const;
    size_type getNrOfColumns() const;
    size_type getRowCapacity() const;
    size_type getColumnCapacity() const;

    void transpose(Matrix<DataType>& result);

    void clear();

    // resize and don't init new elements (user has the responsibility to init them), existing elements retain their old values
    void resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity=0, size_type columnCapacity=0);
    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType, size_type rowCapacity=0, size_type columnCapacity=0);

    void shrinkToFit();

    void insertRow(size_type rowNr);
    void insertRow(size_type rowNr, const DataType& dataType);
    void insertColumn(size_type columnNr);
    void insertColumn(size_type columnNr, const DataType& dataType);
    void eraseRow (size_type rowNr);
    void eraseColumn(size_type columnNr);

    void catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitRowNr);
    void splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitColumnNr);

    void swapItems(size_type rowNr, size_type columnNr, Matrix<DataType>& matrix, size_type matrixRowNr, size_type matrixColumnNr);
    void swapRows(size_type rowNr, Matrix<DataType>& matrix, size_type matrixRowNr);
    void swapColumns(size_type columnNr, Matrix<DataType>& matrix, size_type matrixColumnNr);
    void swapRowColumn(size_type rowNr, Matrix<DataType>& matrix, size_type matrixColumnNr);

    void setAllItemsToValue(const DataType& value);
    void copy(const Matrix<DataType>& src, size_type nrOfRows, size_type nrOfColumns, size_type srcMatrixRowNr=0, size_type srcMatrixColumnNr=0, size_type rowNr=0, size_type columnNr=0);

    // logical operators (DataType should have them implemented)
    operator bool() const;
    bool operator== (const Matrix<DataType>& matrix) const;
    bool operator!= (const Matrix<DataType>& matrix) const;

    // iterators and iterator methods
    class ZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this priviledge
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // "empty" iterator, no position information
        ZIterator();

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        ZIterator operator++();
        ZIterator operator++(int unused);
        ZIterator operator--();
        ZIterator operator--(int unused);

        ZIterator operator+(difference_type offset);
        ZIterator operator-(difference_type offset);

        difference_type operator-(const ZIterator& it) const;

        bool operator==(const ZIterator& it) const;
        bool operator!=(const ZIterator& it) const;
        bool operator<(const ZIterator& it) const;
        bool operator<=(const ZIterator& it) const;
        bool operator>(const ZIterator& it) const;
        bool operator>=(const ZIterator& it) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    ZIterator zBegin() const;
    ZIterator zEnd() const;
    ZIterator zRowBegin(size_type rowNr) const;
    ZIterator zRowEnd(size_type rowNr) const;
    ZIterator getZIterator(size_type rowNr, size_type columnNr) const;
    ZIterator getZIterator(size_type index) const;

    // required for being able to use the "auto" keyword for iterating through the matrix elements
    ZIterator begin() const;
    ZIterator end() const;

private:
    // ensure the currently allocated memory is first released (_deallocMemory()) prior to using this function
    void _allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0, size_type columnCapacity = 0);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    // to be used only when column capacity stays unchanged (otherwise use _allocMemory() and _deallocMemory()
    void _increaseRowCapacity(diff_type rowCapacityIncrement);
    void _decreaseRowCapacity(diff_type rowCapacityDecrement);

    void _increaseNrOfRows(diff_type nrOfRowsIncrement);
    void _decreaseNrOfrows(diff_type nrOfRowsDecrement);

    bool _isEqualTo(const Matrix<DataType>& matrix) const;
    void _adjustSizeAndCapacity(size_type nrOfRows, size_type nrOfColumns);

    DataType** m_pBaseArrayPtr;
    size_type m_NrOfRows;
    size_type m_NrOfColumns;
    size_type m_RowCapacity;
    size_type m_ColumnCapacity;
};

template <typename DataType>
Matrix<DataType>::Matrix()
    : m_pBaseArrayPtr{nullptr}
    , m_NrOfRows{0}
    , m_NrOfColumns{0}
    , m_RowCapacity{0}
    , m_ColumnCapacity{0}
{
}

template<typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRows, size_type nrOfColumns, std::initializer_list<DataType> dataTypeInitList)
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    if (nrOfRows * nrOfColumns > static_cast<size_type>(dataTypeInitList.size()))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSUFFICIENT_ELEMENTS_FOR_INIT]};
    }

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::initializer_list<DataType>::iterator initListIterator{dataTypeInitList.begin()};
    for (size_type row{0}; row < nrOfRows; ++row)
    {
        for (size_type col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = *(initListIterator++);
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType)
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (size_type row{0}; row < nrOfRows; ++row)
    {
        for (size_type col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = dataType;
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues)
    : Matrix<DataType>{nrOfRowsColumns, nrOfRowsColumns, diagMatrixValues.first}
{
    for (size_type diag{0}; diag<m_NrOfRows; ++diag)
    {
        m_pBaseArrayPtr[diag][diag] = diagMatrixValues.second;
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& matrix)
{
    const size_type c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        for (size_type col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
        }
    }
}

template<typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType> &&matrix)
    : m_pBaseArrayPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfRows{matrix.m_NrOfRows}
    , m_NrOfColumns{matrix.m_NrOfColumns}
    , m_RowCapacity{matrix.m_RowCapacity}
    , m_ColumnCapacity{matrix.m_ColumnCapacity}
{
    matrix.m_pBaseArrayPtr = nullptr;
    matrix.m_NrOfRows = 0;
    matrix.m_NrOfColumns = 0;
    matrix.m_RowCapacity = 0;
    matrix.m_ColumnCapacity = 0;
}

template<typename DataType>
Matrix<DataType>::~Matrix()
{
    _deallocMemory();
}

template<typename DataType>
DataType& Matrix<DataType>::at(size_type rowNr, size_type columnNr)
{
    if (rowNr<0 || columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return m_pBaseArrayPtr[rowNr][columnNr];
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](size_type index)
{
    if (index<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (index>=m_NrOfRows*m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return m_pBaseArrayPtr[index/m_NrOfColumns][index%m_NrOfColumns];
}

template <typename DataType>
Matrix<DataType>& Matrix<DataType>::operator=(const Matrix<DataType>& matrix)
{
    if (&matrix != this && (m_pBaseArrayPtr || matrix.m_pBaseArrayPtr))
    {
        const size_type c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
        const size_type c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

        if (m_RowCapacity != c_RowCapacityToAlloc || m_ColumnCapacity != c_ColumnCapacityToAlloc)
        {
            _deallocMemory();
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
        }
        else
        {
            if (m_NrOfRows < matrix.m_NrOfRows)
            {
                _increaseNrOfRows(matrix.m_NrOfRows-m_NrOfRows);
            }
            else if (m_NrOfRows > matrix.m_NrOfRows)
            {
                _decreaseNrOfrows(m_NrOfRows-matrix.m_NrOfRows);
            }

            m_NrOfColumns = matrix.m_NrOfColumns;
        }

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }

    return *this;
}

template<typename DataType>
Matrix<DataType>& Matrix<DataType>::operator=(Matrix<DataType> &&matrix)
{
    if (&matrix != this && (m_pBaseArrayPtr || matrix.m_pBaseArrayPtr))
    {
        m_pBaseArrayPtr = matrix.m_pBaseArrayPtr;
        m_NrOfRows = matrix.m_NrOfRows;
        m_NrOfColumns = matrix.m_NrOfColumns;
        m_RowCapacity = matrix.m_RowCapacity;
        m_ColumnCapacity = matrix.m_ColumnCapacity;

        matrix.m_pBaseArrayPtr = nullptr;
        matrix.m_NrOfRows = 0;
        matrix.m_NrOfColumns = 0;
        matrix.m_RowCapacity = 0;
        matrix.m_ColumnCapacity = 0;
    }

    return *this;
}

template<typename DataType>
DataType** Matrix<DataType>::getBaseArrayPtr(size_type& nrOfRows, size_type& nrOfColumns, size_type& rowCapacity, size_type& columnCapacity)
{
    DataType** pBaseArrayPtr{nullptr};

    if (m_pBaseArrayPtr)
    {
        nrOfRows = m_NrOfRows;
        nrOfColumns = m_NrOfColumns;
        rowCapacity = m_RowCapacity;
        columnCapacity = m_ColumnCapacity;
        pBaseArrayPtr = m_pBaseArrayPtr;

        m_pBaseArrayPtr = nullptr;
        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
    }
    else
    {
        nrOfRows = 0;
        nrOfColumns = 0;
        rowCapacity = 0;
        columnCapacity = 0;
    }

    return pBaseArrayPtr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getNrOfRows() const
{
    return m_NrOfRows;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getNrOfColumns() const
{
    return m_NrOfColumns;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getRowCapacity() const
{
    return m_RowCapacity;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getColumnCapacity() const
{
    return m_ColumnCapacity;
}

template <typename DataType>
void Matrix<DataType>::transpose(Matrix<DataType>& result)
{
    if (!m_NrOfRows)
    {
        if (&result != this)
        {
            result._deallocMemory();
        }
    }
    else if (&result == this)
    {
        Matrix<DataType> matrix{};

        const size_type c_InitialRowCapacity{m_RowCapacity};
        const size_type c_InitialColumnCapacity{m_ColumnCapacity};

        matrix = std::move(*this);

        const size_type c_RowCapacityToAlloc{c_InitialRowCapacity < matrix.m_NrOfColumns ?  matrix.m_NrOfColumns +  matrix.m_NrOfColumns/4 : c_InitialRowCapacity};
        const size_type c_ColumnCapacityToAlloc{c_InitialColumnCapacity < matrix.m_NrOfRows ? matrix.m_NrOfRows + matrix.m_NrOfRows/4 : c_InitialColumnCapacity};

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(matrix.m_NrOfColumns, matrix.m_NrOfRows, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[col][row];
            }
        }
    }
    else
    {
        result._adjustSizeAndCapacity(m_NrOfColumns, m_NrOfRows);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                result.m_pBaseArrayPtr[col][row] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::clear()
{
    _deallocMemory();
}

template<typename DataType>
void Matrix<DataType>::resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity, size_type columnCapacity)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    const size_type c_RowCapacityToSet{rowCapacity > nrOfRows ? rowCapacity : nrOfRows};
    const size_type c_ColumnCapacityToSet{columnCapacity > nrOfColumns ? columnCapacity : nrOfColumns};

    if (c_ColumnCapacityToSet != m_ColumnCapacity)
    {
        size_type rowsToKeep{nrOfRows > m_NrOfRows ? m_NrOfRows : nrOfRows};
        size_type columnsToKeep{nrOfColumns > m_NrOfColumns ? m_NrOfColumns : nrOfColumns};

        Matrix<DataType> matrix{std::move(*this)};
        _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToSet, c_ColumnCapacityToSet);

        for (size_type row{0}; row<rowsToKeep; ++row)
        {
            for (size_type col{0}; col<columnsToKeep; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else if (c_RowCapacityToSet != m_RowCapacity)
    {
        if (m_RowCapacity < c_RowCapacityToSet)
        {
            _increaseRowCapacity(c_RowCapacityToSet-m_RowCapacity);
        }
        else
        {
            _decreaseRowCapacity(m_RowCapacity - c_RowCapacityToSet);
        }

        if (nrOfRows > m_NrOfRows)
        {
            _increaseNrOfRows(nrOfRows - m_NrOfRows);
        }
        else if (nrOfRows < m_NrOfRows)
        {
            _decreaseNrOfrows(m_NrOfRows - nrOfRows);
        }

        m_NrOfColumns = nrOfColumns;
    }
    else
    {
        if (nrOfRows > m_NrOfRows)
        {
            _increaseNrOfRows(nrOfRows - m_NrOfRows);
        }
        else if (nrOfRows < m_NrOfRows)
        {
            _decreaseNrOfrows(m_NrOfRows - nrOfRows);
        }

        m_NrOfColumns = nrOfColumns;
    }
}

template <typename DataType>
void Matrix<DataType>::resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& value, size_type rowCapacity, size_type columnCapacity)
{
    // DataType should support the assign (=) operator
    auto fillNewItems = [](Matrix<DataType>& dest, size_type beginRowIndex, size_type endRowIndex, size_type beginColumnIndex, size_type endColumnIndex, const DataType& value)
    {
        for (size_type row{beginRowIndex}; row<endRowIndex; ++row)
        {
            for (size_type col{beginColumnIndex}; col<endColumnIndex; ++col)
            {
                dest.m_pBaseArrayPtr[row][col] = value;
            }
        }
    };

    const diff_type c_RowDelta{nrOfRows <= m_NrOfRows ? 0 : nrOfRows - m_NrOfRows};
    const diff_type c_ColumnDelta{nrOfColumns <= m_NrOfColumns ? 0 : nrOfColumns - m_NrOfColumns};

    resize(nrOfRows, nrOfColumns, rowCapacity, columnCapacity);

    if (c_RowDelta)
    {
        if (c_ColumnDelta)
        {
            fillNewItems(*this, 0, m_NrOfRows - c_RowDelta, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns, value);
            fillNewItems(*this, m_NrOfRows - c_RowDelta, m_NrOfRows, 0, m_NrOfColumns - c_ColumnDelta, value);
            fillNewItems(*this, m_NrOfRows - c_RowDelta, m_NrOfRows, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns, value);
        }
        else
        {
            fillNewItems(*this, m_NrOfRows - c_RowDelta, m_NrOfRows, 0, m_NrOfColumns, value);
        }
    }
    else if (c_ColumnDelta)
    {
        fillNewItems(*this, 0, m_NrOfRows, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns, value);
    }
}

template<typename DataType>
void Matrix<DataType>::shrinkToFit()
{
    if (m_ColumnCapacity != m_NrOfColumns)
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else if (m_RowCapacity != m_NrOfRows)
    {
        _decreaseRowCapacity(m_RowCapacity - m_NrOfRows);
    }
}

template <typename DataType>
void Matrix<DataType>::insertRow (size_type rowNr)
{
    if (!m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::EMPTY_MATRIX]};
    }

    if (rowNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSERT_ROW_NONCONTIGUOUS]};
    }

    // double row capacity if no spare capacity left (to defer any re-size when inserting further rows)
    if (m_NrOfRows == m_RowCapacity)
    {
        _increaseRowCapacity(m_RowCapacity);
    }

    // append empty row and move it upwards until reaching the correct position
    _increaseNrOfRows(1);

    for (size_type row{m_NrOfRows-1}; row > rowNr; --row)
    {
        std::swap(m_pBaseArrayPtr[row], m_pBaseArrayPtr[row-1]);
    }
}

template<typename DataType>
void Matrix<DataType>::insertRow(size_type rowNr, const DataType &dataType)
{
    insertRow(rowNr);

    for (size_type col{0}; col<m_NrOfColumns; ++col)
    {
        m_pBaseArrayPtr[rowNr][col] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::insertColumn(size_type columnNr)
{
    if (!m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::EMPTY_MATRIX]};
    }

    if (columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSERT_COLUMN_NONCONTIGUOUS]};
    }

    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix matrix{};
        std::swap(*this, matrix);
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns + 1, matrix.m_RowCapacity, 2 * matrix.m_NrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(size_type col{columnNr+1}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col-1];
            }
        }
    }
    else
    {
        ++m_NrOfColumns;
        DataType* pColumnPtr{new DataType[m_NrOfRows]};

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{m_NrOfColumns-1}; col>columnNr; --col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col-1];
            }
        }

        // ensure the newly inserted column doesn't contain data from an old column
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            m_pBaseArrayPtr[row][columnNr] = pColumnPtr[row];
        }

        delete []pColumnPtr;
        pColumnPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::insertColumn(size_type columnNr, const DataType &dataType)
{
    insertColumn(columnNr);

    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        m_pBaseArrayPtr[row][columnNr] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::eraseRow (size_type rowNr)
{
    if (rowNr>=m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    if (rowNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    // this corner case needs to be considered for avoiding situations when number of rows is 0 and number of columns is different from 0
    if (m_NrOfRows == 1)
    {
        _deallocMemory();
    }
    else
    {
        // delete the row elements
        delete []m_pBaseArrayPtr[rowNr];
        m_pBaseArrayPtr[rowNr] = nullptr;

        // move the rows upwards one position to fill in the gap
        for (size_type row{rowNr}; row < m_NrOfRows-1; ++row)
        {
            m_pBaseArrayPtr[row] = m_pBaseArrayPtr[row+1];
        }

        m_pBaseArrayPtr[m_NrOfRows-1] = nullptr;
        --m_NrOfRows;

        // prevent overcapacity

        if (m_NrOfRows <= m_RowCapacity/4)
        {
            _decreaseRowCapacity(m_RowCapacity - 2 * m_NrOfRows);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::eraseColumn(size_type columnNr)
{
    if (columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
    }

    if (m_NrOfColumns==1)
    {
        _deallocMemory();
    }
    else if (m_NrOfColumns-1 <= m_ColumnCapacity/4)
    {
        Matrix matrix{};
        std::swap(*this, matrix);
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns-1, matrix.m_RowCapacity, (matrix.m_NrOfColumns - 1) * 2);

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(size_type col{columnNr}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col+1];
            }
        }
    }
    else
    {
        DataType* pColumnPtr{new DataType[m_NrOfRows]};

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{columnNr}; col<m_NrOfColumns-1; ++col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col+1];
            }
        }

        // ensure the data of the last column is cleared prior to decrementing number of columns
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            m_pBaseArrayPtr[row][m_NrOfColumns-1] = pColumnPtr[row];
        }

        --m_NrOfColumns;
        delete []pColumnPtr;
        pColumnPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    if (firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_ROW_LENGTH]};
    }

    const size_type c_NrOfRows{firstSrcMatrix.m_NrOfRows + secondSrcMatrix.m_NrOfRows};
    const size_type c_NrOfColumns{firstSrcMatrix.m_NrOfColumns};
    const size_type c_RowCapacity{c_NrOfRows + c_NrOfRows / 4};
    const size_type c_ColumnCapacity{c_NrOfColumns + c_NrOfColumns / 4};

    if (&firstSrcMatrix == this && (&secondSrcMatrix != this))
    {
        const size_type c_StartingRowNr{m_NrOfRows};
        if (m_RowCapacity < c_NrOfRows)
        {
            _increaseRowCapacity(c_RowCapacity - m_RowCapacity);
        }
        _increaseNrOfRows(c_NrOfRows - m_NrOfRows);

        for (size_type row{c_StartingRowNr}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row-c_StartingRowNr][col];
            }
        }
    }
    else if (&firstSrcMatrix != this && (&secondSrcMatrix == this))
    {
        const size_type c_NewRowCapacity{m_RowCapacity < c_NrOfRows ? c_RowCapacity : m_RowCapacity};
        DataType** pBaseArrayPtr{new DataType*[c_NewRowCapacity]};

        for (size_type row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
        }

        for (size_type row{firstSrcMatrix.m_NrOfRows}; row<c_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows];
            m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows] = nullptr;
        }

        for (size_type row{c_NrOfRows}; row<c_NewRowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        for (size_type row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;
        m_NrOfRows = c_NrOfRows;
        m_RowCapacity = c_NewRowCapacity;
    }
    else if (&firstSrcMatrix == this && (&secondSrcMatrix == this))
    {
        const size_type c_StartingRowNr{m_NrOfRows};
        if (m_RowCapacity < c_NrOfRows)
        {
            _increaseRowCapacity(c_RowCapacity - m_RowCapacity);
        }
        _increaseNrOfRows(m_NrOfRows);

        for (size_type row{c_StartingRowNr}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row-c_StartingRowNr][col];
            }
        }
    }
    else
    {
        if (m_ColumnCapacity < c_NrOfColumns)
        {
            if (m_RowCapacity < c_NrOfRows)
            {
                _deallocMemory();
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, c_ColumnCapacity);
            }
            else
            {
                const size_type c_SameRowCapacity{m_RowCapacity};
                _deallocMemory();
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_SameRowCapacity, c_ColumnCapacity);
            }
        }
        else if (m_RowCapacity < c_NrOfRows)
        {
            _increaseRowCapacity(c_RowCapacity - m_RowCapacity);
            _increaseNrOfRows(c_NrOfRows - m_NrOfRows);
            m_NrOfColumns = c_NrOfColumns;
        }
        else
        {
            _increaseNrOfRows(c_NrOfRows - m_NrOfRows);
            m_NrOfColumns = c_NrOfColumns;
        }

        for (size_type row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for (size_type row{firstSrcMatrix.m_NrOfRows}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    if (firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_COLUMN_LENGTH]};
    }

    const size_type c_NrOfRows{firstSrcMatrix.m_NrOfRows};
    const size_type c_NrOfColumns{firstSrcMatrix.m_NrOfColumns + secondSrcMatrix.m_NrOfColumns};
    const size_type c_RowCapacity{c_NrOfRows + c_NrOfRows / 4};
    const size_type c_ColumnCapacity{c_NrOfColumns + c_NrOfColumns / 4};

    if (&firstSrcMatrix == this && (&secondSrcMatrix != this))
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory();
        if (matrix.m_ColumnCapacity < c_NrOfColumns)
        {
            if (matrix.m_RowCapacity < c_NrOfRows)
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, c_ColumnCapacity);
            }
            else
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, c_ColumnCapacity);
            }
        }
        else
        {
            _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<matrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{matrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row][col-matrix.m_NrOfColumns];
            }
        }
    }
    else if (&firstSrcMatrix != this && (&secondSrcMatrix == this))
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory();
        if (matrix.m_ColumnCapacity < c_NrOfColumns || matrix.m_RowCapacity < c_NrOfRows)
        {
            if (matrix.m_RowCapacity < c_NrOfRows)
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, c_ColumnCapacity);
            }
            else
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, c_ColumnCapacity);
            }
        }
        else
        {
            _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);
        }

        for (size_type row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<firstSrcMatrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for (size_type row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (size_type col{firstSrcMatrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col-firstSrcMatrix.m_NrOfColumns];
            }
        }
    }
    else if (&firstSrcMatrix == this && (&secondSrcMatrix == this))
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory();
        if (matrix.m_ColumnCapacity < c_NrOfColumns || matrix.m_RowCapacity < c_NrOfRows)
        {
            if (matrix.m_RowCapacity < c_NrOfRows)
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, c_ColumnCapacity);
            }
            else
            {
                _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, c_ColumnCapacity);
            }
        }
        else
        {
            _allocMemory(c_NrOfRows, c_NrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<matrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{matrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col-matrix.m_NrOfColumns];
            }
        }
    }
    else
    {
        if (m_ColumnCapacity < c_NrOfColumns)
        {
            if (m_RowCapacity < c_NrOfRows)
            {
                _deallocMemory();
                _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, c_ColumnCapacity);
            }
            else
            {
                size_type sameRowCapacity{m_RowCapacity};
                _deallocMemory();
                _allocMemory(c_NrOfRows, c_NrOfColumns, sameRowCapacity, c_ColumnCapacity);
            }
        }
        else if (m_RowCapacity < c_NrOfRows)
        {
            size_type sameColumnCapacity{m_ColumnCapacity};
            _deallocMemory();
            _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, sameColumnCapacity);
        }
        else
        {
            size_type sameRowCapacity{m_RowCapacity};
            size_type sameColumnCapacity{m_ColumnCapacity};
            _deallocMemory();
            _allocMemory(c_NrOfRows, c_NrOfColumns, sameRowCapacity, sameColumnCapacity);
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<firstSrcMatrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{firstSrcMatrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row][col-firstSrcMatrix.m_NrOfColumns];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitRowNr)
{
    if (&firstDestMatrix == &secondDestMatrix)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SAME_VARIABLE_TWO_ARGS]};
    }

    if (splitRowNr < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (splitRowNr >= m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    if (splitRowNr == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_ROWS]};
    }

    const size_type c_FirstDestMatrixNrOfRows{splitRowNr};
    const size_type c_FirstDestMatrixNrOfColumns{m_NrOfColumns};

    const size_type c_SecondDestMatrixNrOfRows{m_NrOfRows - splitRowNr};
    const size_type c_SecondDestMatrixNrOfColumns{m_NrOfColumns};

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (size_type row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row-splitRowNr][col] = m_pBaseArrayPtr[row][col];
            }
        }

        firstDestMatrix._decreaseNrOfrows(m_NrOfRows - c_FirstDestMatrixNrOfRows);
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        for (size_type row{0}; row<splitRowNr; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        DataType** pBaseArrayPtr{new DataType*[secondDestMatrix.m_RowCapacity]};

        for (size_type row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row-splitRowNr] = m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        for (size_type row{splitRowNr}; row < secondDestMatrix.m_RowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        size_type sameRowCapacity{secondDestMatrix.m_RowCapacity};
        size_type sameColumnCapacity{secondDestMatrix.m_ColumnCapacity};
        _deallocMemory();

        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;

        m_NrOfRows = c_SecondDestMatrixNrOfRows;
        m_NrOfColumns = c_SecondDestMatrixNrOfColumns;
        m_RowCapacity = sameRowCapacity;
        m_ColumnCapacity = sameColumnCapacity;
    }
    else
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (size_type row{0}; row<splitRowNr; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (size_type row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row-splitRowNr][col] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitColumnNr)
{
    if (&firstDestMatrix == &secondDestMatrix)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SAME_VARIABLE_TWO_ARGS]};
    }

    if (splitColumnNr < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (splitColumnNr >= m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
    }

    if (splitColumnNr == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_COLUMNS]};
    }

    const size_type c_FirstDestMatrixNrOfRows{m_NrOfRows};
    const size_type c_FirstDestMatrixNrOfColumns{splitColumnNr};

    const size_type c_SecondDestMatrixNrOfRows{m_NrOfRows};
    const size_type c_SecondDestMatrixNrOfColumns{m_NrOfColumns - splitColumnNr};

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{splitColumnNr}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row][col-splitColumnNr] = m_pBaseArrayPtr[row][col];
            }
        }

        Matrix matrix{std::move(*this)};
        _deallocMemory();
        _allocMemory(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        Matrix matrix{std::move(*this)};
        _deallocMemory();
        _allocMemory(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        for (size_type row{0}; row<c_SecondDestMatrixNrOfRows; ++row)
        {
            for (size_type col{0}; col<c_SecondDestMatrixNrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col+splitColumnNr];
            }
        }
    }
    else
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{splitColumnNr}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row][col-splitColumnNr] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapItems(size_type rowNr, size_type columnNr, Matrix<DataType>& matrix, size_type matrixRowNr, size_type matrixColumnNr)
{
    if (rowNr<0 || columnNr<0 || matrixRowNr<0 || matrixColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns || matrixRowNr>=matrix.m_NrOfRows || matrixColumnNr>=matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    if (rowNr!=matrixRowNr || columnNr!=matrixColumnNr || &matrix != this)
    {
        std::swap(m_pBaseArrayPtr[rowNr][columnNr], matrix.m_pBaseArrayPtr[matrixRowNr][matrixColumnNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRows(size_type rowNr, Matrix& matrix, size_type matrixRowNr)
{
    if (rowNr<0 || matrixRowNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>=m_NrOfRows || matrixRowNr>=matrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    if (m_NrOfColumns!=matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_ROW_LENGTH]};
    }

    if (rowNr!=matrixRowNr || &matrix!=this)
    {
        std::swap(m_pBaseArrayPtr[rowNr], matrix.m_pBaseArrayPtr[matrixRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumns(size_type columnNr, Matrix& matrix, size_type matrixColumnNr)
{
    if (columnNr<0 || matrixColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>=m_NrOfColumns || matrixColumnNr>=matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
    }

    if (m_NrOfRows!=matrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_COLUMN_LENGTH]};
    }

    if (columnNr!=matrixColumnNr || &matrix!=this)
    {
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[row][columnNr]};
            m_pBaseArrayPtr[row][columnNr] = matrix.m_pBaseArrayPtr[row][matrixColumnNr];
            matrix.m_pBaseArrayPtr[row][matrixColumnNr] = swap;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapRowColumn(size_type rowNr, Matrix<DataType>& matrix, size_type matrixColumnNr)
{
    if (&matrix == this)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    if (rowNr<0 || matrixColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (m_NrOfColumns!=matrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_ROWS_UNEQUAL_COLUMNS]};
    }

    if (rowNr>=m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    if (matrixColumnNr>=matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
    }

    for (size_type col{0}; col<m_NrOfColumns; ++col)
    {
        // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
        DataType swap{m_pBaseArrayPtr[rowNr][col]};
        m_pBaseArrayPtr[rowNr][col] = matrix.m_pBaseArrayPtr[col][matrixColumnNr];
        matrix.m_pBaseArrayPtr[col][matrixColumnNr] = swap;
    }
}

template <typename DataType> void Matrix<DataType>::setAllItemsToValue(const DataType& value)
{
    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        for (size_type col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = value;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::copy(const Matrix<DataType>& srcMatrix, size_type nrOfRows, size_type nrOfColumns, size_type srcMatrixRowNr, size_type srcMatrixColumnNr, size_type rowNr, size_type columnNr)
{
    if (&srcMatrix == this)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    if (nrOfRows<0 || nrOfColumns<0 || srcMatrixRowNr<0 || srcMatrixColumnNr<0 || rowNr<0 || columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (srcMatrixRowNr + nrOfRows > srcMatrix.m_NrOfRows || srcMatrixColumnNr + nrOfColumns > srcMatrix.m_NrOfColumns || rowNr+nrOfRows > m_NrOfRows || columnNr+nrOfColumns > m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    if (nrOfRows && nrOfColumns)
    {
        for (size_type row{0}; row<nrOfRows; ++row)
        {
            for (size_type col{0}; col<nrOfColumns; ++col)
            {
                m_pBaseArrayPtr[rowNr+row][columnNr+col] = srcMatrix.m_pBaseArrayPtr[srcMatrixRowNr+row][srcMatrixColumnNr+col];
            }
        }
    }
}

template<typename DataType>
Matrix<DataType>::operator bool() const
{
    bool result{false};

    if (m_pBaseArrayPtr)
    {
        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col])
                {
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

template <typename DataType>
bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix) const
{
    return _isEqualTo(matrix);
}

template<typename DataType>
bool Matrix<DataType>::operator!=(const Matrix<DataType> &matrix) const
{
    return !_isEqualTo(matrix);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zBegin() const
{
    return ZIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zEnd() const
{
    return ZIterator{*this, m_NrOfRows-1, m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowBegin(size_type rowNr) const
{
    if (rowNr < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr >= m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    return ZIterator{*this, rowNr, 0};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowEnd(size_type rowNr) const
{
    if (rowNr < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr >= m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    ZIterator it{};

    if (rowNr < m_NrOfRows-1)
    {
        it = ZIterator{*this, rowNr+1, 0};
    }
    else
    {
        it = ZIterator{*this, rowNr, m_NrOfColumns};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(size_type rowNr, size_type columnNr) const
{
    if (rowNr<0 || columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return ZIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(size_type index) const
{
    if (index < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (index >= m_NrOfRows * m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return ZIterator{*this, index / m_NrOfColumns, index % m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::begin() const
{
    return zBegin();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::end() const
{
    return zEnd();
}

template<typename DataType>
void Matrix<DataType>::_allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity, size_type columnCapacity)
{
    if (nrOfRows > 0 && nrOfColumns > 0)
    {
        m_RowCapacity = rowCapacity < nrOfRows ? nrOfRows : rowCapacity;
        m_ColumnCapacity = columnCapacity < nrOfColumns ? nrOfColumns : columnCapacity;

        m_pBaseArrayPtr = new DataType*[m_RowCapacity];

        for (size_type row{0}; row<nrOfRows; ++row)
        {
            m_pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
        }

        // no elements to be allocated to the extra rows (elements to be allocated on demand)
        if (m_RowCapacity > nrOfRows)
        {
            for (size_type row{nrOfRows}; row<m_RowCapacity; ++row)
            {
                m_pBaseArrayPtr[row] = nullptr;
            }
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
        m_pBaseArrayPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    if (m_pBaseArrayPtr)
    {
        // if row capacity exceeds number of rows the surplus contains null pointers so no need to de-allocate them
        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            if (m_pBaseArrayPtr[row])
            {
                delete []m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = nullptr;

        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
    }
}

template<typename DataType>
void Matrix<DataType>::_increaseRowCapacity(diff_type rowCapacityIncrement)
{
    if (rowCapacityIncrement > 0)
    {
        size_type rowCapacity{m_RowCapacity + rowCapacityIncrement};
        DataType** pBaseArrayPtr{new DataType*[rowCapacity]};

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        for (size_type row{m_NrOfRows}; row<rowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;
        m_RowCapacity = rowCapacity;
    }
}

template<typename DataType>
void Matrix<DataType>::_decreaseRowCapacity(diff_type rowCapacityDecrement)
{
    if (rowCapacityDecrement > 0 && rowCapacityDecrement < m_RowCapacity)
    {
        size_type rowCapacity{m_RowCapacity - rowCapacityDecrement};
        DataType** pBaseArrayPtr{new DataType*[rowCapacity]};

        if (rowCapacity < m_NrOfRows)
        {
            for (size_type row{0}; row<rowCapacity; ++row)
            {
                pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            for (size_type row{rowCapacity}; row<m_NrOfRows; ++row)
            {
                delete []m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            m_NrOfRows = rowCapacity;
        }
        else
        {
            for (size_type row{0}; row<m_NrOfRows; ++row)
            {
                pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            for (size_type row{m_NrOfRows}; row<rowCapacity; ++row)
            {
                pBaseArrayPtr[row] = nullptr;
            }
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;
        m_RowCapacity = rowCapacity;
    }
}

template<typename DataType>
void Matrix<DataType>::_increaseNrOfRows(diff_type nrOfRowsIncrement)
{
    if (nrOfRowsIncrement > 0)
    {
        size_type nrOfRows{m_NrOfRows + nrOfRowsIncrement};

        if (nrOfRows <= m_RowCapacity)
        {
            for(size_type row{m_NrOfRows}; row<nrOfRows; ++row)
            {
                m_pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
            }

            m_NrOfRows = nrOfRows;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_decreaseNrOfrows(diff_type nrOfRowsDecrement)
{
    if (nrOfRowsDecrement > 0 && nrOfRowsDecrement < m_NrOfRows)
    {
        size_type nrOfRows{m_NrOfRows - nrOfRowsDecrement};

        for (size_type row{nrOfRows}; row<m_NrOfRows; ++row)
        {
            delete []m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        m_NrOfRows = nrOfRows;
    }
}

template<typename DataType>
bool Matrix<DataType>::_isEqualTo(const Matrix<DataType>& matrix) const
{
    bool areEqual{false};

    if (&matrix == this)
    {
        areEqual = true;
    }
    else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
    {
        //change assumption of equality to true until proving the opposite
        areEqual = true;

        bool continueChecking{true};

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col] != matrix.m_pBaseArrayPtr[row][col])
                {
                    continueChecking = false;
                    areEqual = false;
                    break;
                }
            }

            if (!continueChecking)
            {
                break;
            }
        }
    }

    return areEqual;
}

template<typename DataType>
void Matrix<DataType>::_adjustSizeAndCapacity(size_type nrOfRows, size_type nrOfColumns)
{
    const size_type c_NewRowCapacity{nrOfRows + nrOfRows/4};
    const size_type c_NewColumnCapacity{nrOfColumns + nrOfColumns/4};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};

    if (m_RowCapacity < nrOfRows)
    {
        if (m_ColumnCapacity < nrOfColumns)
        {
            _deallocMemory();
            _allocMemory(nrOfRows, nrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);
        }
        else
        {
            _deallocMemory();
            _allocMemory(nrOfRows, nrOfColumns, c_NewRowCapacity, c_OldColumnCapacity);
        }
    }
    else if (m_ColumnCapacity < nrOfColumns)
    {
        _deallocMemory();
        _allocMemory(nrOfRows, nrOfColumns, c_OldRowCapacity, c_NewColumnCapacity);
    }
    else
    {
        _deallocMemory();
        _allocMemory(nrOfRows, nrOfColumns, c_OldRowCapacity, c_OldColumnCapacity);
    }
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::reference Matrix<DataType>::ZIterator::operator*() const
{
    if (m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::DEREFERENCE_END_ITERATOR]};
    }

    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::value_type* Matrix<DataType>::ZIterator::operator->() const
{
    if (m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::DEREFERENCE_END_ITERATOR]};
    }

    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::reference Matrix<DataType>::ZIterator::operator[](ZIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_ResultingIndex{c_CurrentIndex + index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

    if (c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATOR_INDEX_OUT_OF_BOUNDS]};
    }

    return m_pMatrixPtr[c_ResultingIndex / m_NrOfMatrixColumns][c_ResultingIndex % m_NrOfMatrixColumns];
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++(int unused)
{
    (void) unused;
    ZIterator zIterator{*this};

    _increment();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--(int unused)
{
    (void) unused;
    ZIterator zIterator{*this};

    _decrement();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator+(ZIterator::difference_type offset)
{
    ZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator-(ZIterator::difference_type offset)
{
    ZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::difference_type Matrix<DataType>::ZIterator::operator-(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    const size_type c_FirstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator==(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator!=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr < it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr <= it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr > it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INCOMPATIBLE_ITERATORS]};
    }

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr >= it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < 0 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr > m_NrOfMatrixColumns ||
        (currentRowNr < m_NrOfMatrixRows-1 && currentColumnNr == m_NrOfMatrixColumns))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_increment()
{
    if (!(m_CurrentColumnNr == m_NrOfMatrixColumns && m_CurrentRowNr == (m_NrOfMatrixRows-1)))
    {
        ++m_CurrentColumnNr;
        if (m_CurrentColumnNr == m_NrOfMatrixColumns && (m_CurrentRowNr != (m_NrOfMatrixRows-1)))
        {
            m_CurrentColumnNr = m_CurrentColumnNr - m_NrOfMatrixColumns;
            ++m_CurrentRowNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_decrement()
{
    if (m_CurrentRowNr > 0 || m_CurrentColumnNr > 0)
    {
        if(m_CurrentColumnNr == 0)
        {
            --m_CurrentRowNr;
            m_CurrentColumnNr = m_NrOfMatrixColumns - 1;
        }
        else
        {
            --m_CurrentColumnNr;
        }
    }
}

#endif // MATRIX_H


