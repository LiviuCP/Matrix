#include <initializer_list>
#include <vector>
#include <utility>

#include "matrix_exceptions.h"

template <typename DataType>
class Matrix
{
public: 
    Matrix();
    Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeInitList);
    Matrix(int nrOfRows, int nrOfColumns, const DataType& dataType);
    Matrix(int nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues);
    Matrix(const Matrix<DataType>& matrix);
    Matrix(Matrix<DataType>&& matrix);
    ~Matrix();

    DataType& at(int i,int j);
    DataType& operator[] (int index);

    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    Matrix<DataType>& operator= (Matrix<DataType>&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    DataType** getBaseArrayPtr(int& nrOfRows, int& nrOfColumns, int& rowCapacity, int& columnCapacity);
	
    int getNrOfRows() const;
    int getNrOfColumns() const;
    int getRowCapacity() const;
    int getColumnCapacity() const;

    void getTransposedMatrix(Matrix<DataType>& result);

    void clear();

    // resize and don't init elements (user has the responsibility to init them)
    void resize(int nrOfRows, int nrOfColumns);
    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resize(int nrOfRows, int nrOfColumns, const DataType& dataType);

    void transformToDiagMatrix(int nrOfRowsColumns, const DataType& dataType, const DataType& diagDataType);
    void transformToEqualElementsMatrix(int nrOfRows, int nrOfColumns, const DataType& dataType);

    void insertRow(int rowNr);
    void insertRow(int rowNr, const DataType& dataType);
    void insertColumn(int columnNr);
    void insertColumn(int columnNr, const DataType& dataType);
    void eraseRow (int rowNr);
    void eraseColumn(int columnNr);

    void concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix, bool concatenateVertically = true);
    void split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr, bool splitVertically = true);

    void swapItems(int rowNr, int columnNr, Matrix<DataType>& matrix, int matrixRowNr, int matrixColumnNr);
    void swapRows(int rowNr, Matrix<DataType>& matrix, int matrixRowNr);
    void swapColumns(int columnNr, Matrix<DataType>& matrix, int matrixColumnNr);
    void swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr);

    void setAllItemsToValue(const DataType& value);
    void copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns, int srcX=0, int srcY=0, int destX=0, int destY=0);

    // logical operators (DataType should have them implemented)
    operator bool() const;
    bool operator== (const Matrix<DataType>& matrix) const;
    bool operator!= (const Matrix<DataType>& matrix) const;

private:
    // ensure the currently allocated memory is first released (_deallocMemory()) prior to using this function
    void _allocMemory(int nrOfRows, int nrOfColumns, int rowCapacity = 0, int columnCapacity = 0);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    // to be used only when column capacity stays unchanged (otherwise use _allocMemory() and _deallocMemory()
    void _increaseRowCapacity(int rowCapacityIncrement);
    void _decreaseRowCapacity(int rowCapacityDecrement);

    void _increaseNrOfRows(int nrOfRowsIncrement);
    void _decreaseNrOfrows(int nrOfRowsDecrement);

    void _split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestmatrix, int splitRowColumnNr, bool splitVertically);
    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix, bool concatenateVertically);

    bool _isEqualTo(const Matrix<DataType> matrix) const;

    DataType** m_pBaseArrayPtr;
    int m_NrOfRows;
    int m_NrOfColumns;
    int m_RowCapacity;
    int m_ColumnCapacity;
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
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeInitList)
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    if (nrOfRows * nrOfColumns > static_cast<int>(dataTypeInitList.size()))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSUFFICIENT_ELEMENTS_FOR_INIT]};
    }

    const int c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const int c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::initializer_list<DataType>::iterator initListIterator{dataTypeInitList.begin()};
    for (int row{0}; row < nrOfRows; ++row)
    {
        for (int col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = *(initListIterator++);
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, const DataType& dataType)
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    const int c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const int c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (int row{0}; row < nrOfRows; ++row)
    {
        for (int col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = dataType;
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues)
    : Matrix<DataType>{nrOfRowsColumns, nrOfRowsColumns, diagMatrixValues.first}
{
    for (int diag{0}; diag<m_NrOfRows; ++diag)
    {
        m_pBaseArrayPtr[diag][diag] = diagMatrixValues.second;
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& matrix)
{
    const int c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
    const int c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
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
DataType& Matrix<DataType>::at(int i,int j)
{
    if (i<0 || j<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (i>=m_NrOfRows || j>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return m_pBaseArrayPtr[i][j];
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](int index)
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
        const int c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
        const int c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

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

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
DataType** Matrix<DataType>::getBaseArrayPtr(int& nrOfRows, int& nrOfColumns, int& rowCapacity, int& columnCapacity)
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
int Matrix<DataType>::getNrOfRows() const
{
    return m_NrOfRows;
}

template<typename DataType>
int Matrix<DataType>::getNrOfColumns() const
{
    return m_NrOfColumns;
}

template<typename DataType>
int Matrix<DataType>::getRowCapacity() const
{
    return m_RowCapacity;
}

template<typename DataType>
int Matrix<DataType>::getColumnCapacity() const
{
    return m_ColumnCapacity;
}

template <typename DataType>
void Matrix<DataType>::getTransposedMatrix(Matrix<DataType>& result)
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

        matrix = std::move(*this);

        const int c_RowCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};
        const int c_ColumnCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(matrix.m_NrOfColumns, matrix.m_NrOfRows, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[col][row];
            }
        }
    }
    else
    {
        const int c_RowCapacityToAlloc{m_NrOfColumns + m_NrOfColumns / 4};
        const int c_ColumnCapacityToAlloc{m_NrOfRows + m_NrOfRows / 4};

        result._deallocMemory();
        result._allocMemory(m_NrOfColumns, m_NrOfRows, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
void Matrix<DataType>::resize(int nrOfRows, int nrOfColumns)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }
    else if (nrOfRows != m_NrOfRows || nrOfColumns != m_NrOfColumns)
    {
        _deallocMemory();
        _allocMemory(nrOfRows, nrOfColumns);
    }
}

template <typename DataType>
void Matrix<DataType>::resize(int nrOfRows, int nrOfColumns, const DataType& value)
{
    auto copyMatrix = [](Matrix<DataType>& dest, Matrix<DataType>& src, int beginRowIndex, int endRowIndex, int beginColumnIndex, int endColumnIndex)
    {
        for (int row{beginRowIndex}; row<endRowIndex; ++row)
        {
            for (int col{beginColumnIndex}; col<endColumnIndex; ++col)
            {
                dest.m_pBaseArrayPtr[row][col]=src.m_pBaseArrayPtr[row][col];
            }
        }
    };

    // DataType should support the assign (=) operator
    auto fillNewItems = [](Matrix<DataType>& dest, int beginRowIndex, int endRowIndex, int beginColumnIndex, int endColumnIndex, const DataType& value)
    {
        for (int row{beginRowIndex}; row<endRowIndex; ++row)
        {
            for (int col{beginColumnIndex}; col<endColumnIndex; ++col)
            {
                dest.m_pBaseArrayPtr[row][col] = value;
            }
        }
    };

    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }
    else if (nrOfRows!=m_NrOfRows || nrOfColumns!=m_NrOfColumns)
    {
        Matrix<DataType> matrix{std::move(*this)};

        _allocMemory(nrOfRows, nrOfColumns);

        if (nrOfRows<matrix.m_NrOfRows && nrOfColumns<matrix.m_NrOfColumns)
        {
            copyMatrix(*this, matrix, 0, nrOfRows, 0, nrOfColumns);
        }
        else if (nrOfRows<=matrix.m_NrOfRows && nrOfColumns>=matrix.m_NrOfColumns)
        {
            copyMatrix(*this, matrix, 0, nrOfRows, 0, matrix.m_NrOfColumns);
            fillNewItems(*this, 0, nrOfRows, matrix.m_NrOfColumns, nrOfColumns, value);
        }
        else if ((nrOfRows>=matrix.m_NrOfRows) && (nrOfColumns<=matrix.m_NrOfColumns))
        {
            copyMatrix(*this, matrix, 0, matrix.m_NrOfRows, 0, nrOfColumns);
            fillNewItems(*this, matrix.m_NrOfRows, nrOfRows, 0, nrOfColumns, value);
        }
        else
        {
            copyMatrix(*this, matrix, 0, matrix.m_NrOfRows, 0, matrix.m_NrOfColumns);
            fillNewItems(*this, 0, nrOfRows, matrix.m_NrOfColumns, nrOfColumns, value);
            fillNewItems(*this, matrix.m_NrOfRows, nrOfRows, 0, nrOfColumns, value);
            fillNewItems(*this, matrix.m_NrOfRows, nrOfRows, matrix.m_NrOfColumns, nrOfColumns, value);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::transformToDiagMatrix(int nrOfRowsColumns, const DataType& dataType, const DataType& diagDataType)
{
    if (nrOfRowsColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }
    else
    {
        _deallocMemory();
        Matrix<DataType> matrix{nrOfRowsColumns, std::pair<DataType, DataType>(dataType, diagDataType)};
        std::swap(*this, matrix);
    }
}

template <typename DataType>
void Matrix<DataType>::transformToEqualElementsMatrix(int nrOfRows, int nrOfColumns, const DataType& dataType)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }
    else
    {
        _deallocMemory();
        Matrix matrix{nrOfRows, nrOfColumns, dataType};
        std::swap(*this, matrix);
    }
}



template <typename DataType>
void Matrix<DataType>::insertRow (int rowNr)
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

    for (int row{m_NrOfRows-1}; row > rowNr; --row)
    {
        std::swap(m_pBaseArrayPtr[row], m_pBaseArrayPtr[row-1]);
    }
}

template<typename DataType>
void Matrix<DataType>::insertRow(int rowNr, const DataType &dataType)
{
    insertRow(rowNr);

    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        m_pBaseArrayPtr[rowNr][col] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::insertColumn(int columnNr)
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

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(int col{columnNr+1}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col-1];
            }
        }
    }
    else
    {
        ++m_NrOfColumns;
        DataType* pColumnPtr{new DataType[m_NrOfRows]};

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for(int col{m_NrOfColumns-1}; col>columnNr; --col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col-1];
            }
        }

        // ensure the newly inserted column doesn't contain data from an old column
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            m_pBaseArrayPtr[row][columnNr] = pColumnPtr[row];
        }

        delete []pColumnPtr;
        pColumnPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::insertColumn(int columnNr, const DataType &dataType)
{
    insertColumn(columnNr);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        m_pBaseArrayPtr[row][columnNr] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::eraseRow (int rowNr)
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
        for (int row{rowNr}; row < m_NrOfRows-1; ++row)
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
void Matrix<DataType>::eraseColumn(int columnNr)
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
    else if (m_NrOfColumns <= m_ColumnCapacity/4)
    {
        Matrix matrix{};
        std::swap(*this, matrix);
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns-1, matrix.m_RowCapacity, (matrix.m_NrOfColumns - 1) * 2);

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for(int col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(int col{columnNr}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col+1];
            }
        }
    }
    else
    {
        DataType* pColumnPtr{new DataType[m_NrOfRows]};

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for(int col{columnNr}; col<m_NrOfColumns-1; ++col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col+1];
            }
        }

        // ensure the data of the last column is cleared prior to decrementing number of columns
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            m_pBaseArrayPtr[row][m_NrOfColumns-1] = pColumnPtr[row];
        }

        --m_NrOfColumns;
        delete []pColumnPtr;
        pColumnPtr = nullptr;
    }
}

template <typename DataType>
void Matrix<DataType>::concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix, bool concatenateVertically)
{
    if (concatenateVertically && (firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_ROW_LENGTH]};
    }

    if (!concatenateVertically && (firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_COLUMN_LENGTH]};
    }

    Matrix<DataType> thirdMatrix{};

    if (&firstSrcMatrix == this || &secondSrcMatrix == this)
    {
        thirdMatrix = std::move(*this);
    }

    if (&firstSrcMatrix == this && (&secondSrcMatrix != this))
    {
        _concatenate(thirdMatrix, secondSrcMatrix, concatenateVertically);
    }
    else if (&firstSrcMatrix != this && (&secondSrcMatrix == this))
    {
        _concatenate(firstSrcMatrix, thirdMatrix, concatenateVertically);
    }
    else if (&firstSrcMatrix == this && (&secondSrcMatrix == this))
    {
        _concatenate(thirdMatrix, thirdMatrix, concatenateVertically);
    }
    else
    {
        _concatenate(firstSrcMatrix, secondSrcMatrix, concatenateVertically);
    }
}

template <typename DataType>
void Matrix<DataType>::split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr, bool splitVertically)
{
    if (&firstDestMatrix == &secondDestMatrix)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SAME_VARIABLE_TWO_ARGS]};
    }

    if (splitRowColumnNr < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (splitVertically)
    {
        if (splitRowColumnNr >= m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
        }

        if (splitRowColumnNr == 0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_ROWS]};
        }
    }
    else
    {
        if (splitRowColumnNr >= m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
        }

        if (splitRowColumnNr == 0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_COLUMNS]};
        }
    }

    Matrix<DataType> thirdMatrix{};

    if (&firstDestMatrix == this || &secondDestMatrix == this)
    {
        thirdMatrix = std::move(*this);
    }

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        thirdMatrix._split(*this, secondDestMatrix, splitRowColumnNr, splitVertically);
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        thirdMatrix._split(firstDestMatrix, *this, splitRowColumnNr, splitVertically);
    }
    else
    {
        _split(firstDestMatrix, secondDestMatrix, splitRowColumnNr, splitVertically);
    }
}

template <typename DataType>
void Matrix<DataType>::swapItems(int rowNr, int columnNr, Matrix<DataType>& matrix, int matrixRowNr, int matrixColumnNr)
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
void Matrix<DataType>::swapRows(int rowNr, Matrix& matrix, int matrixRowNr)
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
void Matrix<DataType>::swapColumns(int columnNr, Matrix& matrix, int matrixColumnNr)
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
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[row][columnNr]};
            m_pBaseArrayPtr[row][columnNr] = matrix.m_pBaseArrayPtr[row][matrixColumnNr];
            matrix.m_pBaseArrayPtr[row][matrixColumnNr] = swap;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr)
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

    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
        DataType swap{m_pBaseArrayPtr[rowNr][col]};
        m_pBaseArrayPtr[rowNr][col] = matrix.m_pBaseArrayPtr[col][matrixColumnNr];
        matrix.m_pBaseArrayPtr[col][matrixColumnNr] = swap;
    }
}

template <typename DataType> void Matrix<DataType>::setAllItemsToValue(const DataType& value)
{
    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = value;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns, int srcX, int srcY, int destX, int destY)
{
    if (&src == this)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    if (nrOfRows<0 || nrOfColumns<0 || srcX<0 || srcY<0 || destX<0 || destY<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (srcX + nrOfRows > src.m_NrOfRows || srcY + nrOfColumns > src.m_NrOfColumns || destX+nrOfRows > m_NrOfRows || destY+nrOfColumns > m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    if (nrOfRows && nrOfColumns)
    {
        for (int row{0}; row<nrOfRows; ++row)
        {
            for (int col{0}; col<nrOfColumns; ++col)
            {
                m_pBaseArrayPtr[destX+row][destY+col] = src.m_pBaseArrayPtr[srcX+row][srcY+col];
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
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
void Matrix<DataType>::_allocMemory(int nrOfRows, int nrOfColumns, int rowCapacity, int columnCapacity)
{
    if (nrOfRows > 0 && nrOfColumns > 0)
    {
        if (rowCapacity < nrOfRows)
        {
            m_RowCapacity = nrOfRows;
        }
        else
        {
            m_RowCapacity = rowCapacity;
        }

        if (columnCapacity < nrOfColumns)
        {
            m_ColumnCapacity = nrOfColumns;
        }
        else
        {
            m_ColumnCapacity = columnCapacity;
        }

        m_pBaseArrayPtr = new DataType*[m_RowCapacity];

        for (int row{0}; row<nrOfRows; ++row)
        {
            m_pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
        }

        // no elements to be allocated to the extra rows (elements to be allocated on demand)
        if (m_RowCapacity > nrOfRows)
        {
            for (int row{nrOfRows}; row<m_RowCapacity; ++row)
            {
                m_pBaseArrayPtr[row] = nullptr;
            }
        }

        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;
    }
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    if (m_pBaseArrayPtr)
    {
        // if row capacity exceeds number of rows the surplus contains null pointers so no need to de-allocate them
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            delete []m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
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
void Matrix<DataType>::_increaseRowCapacity(int rowCapacityIncrement)
{
    if (rowCapacityIncrement > 0)
    {
        int rowCapacity{m_RowCapacity + rowCapacityIncrement};
        DataType** pBaseArrayPtr{new DataType*[rowCapacity]};

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        for (int row{m_NrOfRows}; row<rowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        delete m_pBaseArrayPtr;
        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;
        m_RowCapacity = rowCapacity;
    }
}

template<typename DataType>
void Matrix<DataType>::_decreaseRowCapacity(int rowCapacityDecrement)
{
    if (rowCapacityDecrement > 0 && rowCapacityDecrement < m_RowCapacity)
    {
        int rowCapacity{m_RowCapacity - rowCapacityDecrement};
        DataType** pBaseArrayPtr{new DataType*[rowCapacity]};

        if (rowCapacity < m_NrOfRows)
        {
            for (int row{0}; row<rowCapacity; ++row)
            {
                pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            for (int row{rowCapacity}; row<m_NrOfRows; ++row)
            {
                delete []m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            m_NrOfRows = rowCapacity;
        }
        else
        {
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                pBaseArrayPtr[row] = m_pBaseArrayPtr[row];
                m_pBaseArrayPtr[row] = nullptr;
            }

            for (int row{m_NrOfRows}; row<rowCapacity; ++row)
            {
                pBaseArrayPtr[row] = nullptr;
            }
        }

        delete m_pBaseArrayPtr;
        m_pBaseArrayPtr = pBaseArrayPtr;
        pBaseArrayPtr = nullptr;
        m_RowCapacity = rowCapacity;
    }
}

template<typename DataType>
void Matrix<DataType>::_increaseNrOfRows(int nrOfRowsIncrement)
{
    if (nrOfRowsIncrement > 0)
    {
        int nrOfRows{m_NrOfRows + nrOfRowsIncrement};

        if (nrOfRows <= m_RowCapacity)
        {
            for(int row{m_NrOfRows}; row<nrOfRows; ++row)
            {
                m_pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
            }

            m_NrOfRows = nrOfRows;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_decreaseNrOfrows(int nrOfRowsDecrement)
{
    if (nrOfRowsDecrement > 0 && nrOfRowsDecrement < m_NrOfRows)
    {
        int nrOfRows{m_NrOfRows - nrOfRowsDecrement};

        for (int row{nrOfRows}; row<m_NrOfRows; ++row)
        {
            delete []m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        m_NrOfRows = nrOfRows;
    }
}

template<typename DataType>
void Matrix<DataType>::_split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr, bool splitVertically)
{
    firstDestMatrix._deallocMemory();
    secondDestMatrix._deallocMemory();

    if (splitVertically) {
        firstDestMatrix._allocMemory(splitRowColumnNr, m_NrOfColumns);
        secondDestMatrix._allocMemory(m_NrOfRows - splitRowColumnNr, m_NrOfColumns);

        for (int row{0}; row<splitRowColumnNr; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{splitRowColumnNr}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row-splitRowColumnNr][col] = m_pBaseArrayPtr[row][col];
            }
        }
    }
    else
    {
        firstDestMatrix._allocMemory(m_NrOfRows, splitRowColumnNr);
        secondDestMatrix._allocMemory(m_NrOfRows, m_NrOfColumns - splitRowColumnNr);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<splitRowColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{splitRowColumnNr}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row][col-splitRowColumnNr] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_concatenate(Matrix<DataType> &firstSrcMatrix, Matrix<DataType> &secondSrcMatrix, bool concatenateVertically)
{
    if (concatenateVertically) {
        resize(firstSrcMatrix.m_NrOfRows + secondSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns);

        for (int row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{firstSrcMatrix.m_NrOfRows}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows][col];
            }
        }
    }
    else
    {
        resize(firstSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns + secondSrcMatrix.m_NrOfColumns);

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<firstSrcMatrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{firstSrcMatrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row][col-firstSrcMatrix.m_NrOfColumns];
            }
        }
    }
}

template<typename DataType>
bool Matrix<DataType>::_isEqualTo(const Matrix<DataType> matrix) const
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

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
