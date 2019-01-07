#include <cstdlib>
#include <cmath>
#include <initializer_list>
#include <vector>
#include <utility>
#include <exception>

#include "matrix_exceptions.h"

template <typename DataType>
class Matrix
{
public: 
    enum class ArithmeticMode
    {
        ALL_ITEMS,
        ONE_ROW,
        EACH_ROW,
        ONE_COLUMN,
        EACH_COLUMN,
        ModesCount
    };

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
    DataType** getBaseArrayPtr(int& nrOfRows, int& nrOfColumns);
	
    int getNrOfRows() const;
    int getNrOfColumns() const;

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
    void _allocMemory(int nrOfRows, int nrOfColumns);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    void _split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestmatrix, int splitRowColumnNr, bool splitVertically);
    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix, bool concatenateVertically);

    bool _isEqualTo(const Matrix<DataType> matrix) const;

    DataType** m_pBaseArrayPtr;
    int m_NrOfRows;
    int m_NrOfColumns;
};

template <typename DataType>
Matrix<DataType>::Matrix()
    : m_pBaseArrayPtr{nullptr}
    , m_NrOfRows{0}
    , m_NrOfColumns{0}
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

    _allocMemory(nrOfRows, nrOfColumns);

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

    _allocMemory(nrOfRows,nrOfColumns);

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
    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);

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
{
    matrix.m_pBaseArrayPtr = nullptr;
    matrix.m_NrOfRows = 0;
    matrix.m_NrOfColumns = 0;
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
        if (m_NrOfRows != matrix.m_NrOfRows || m_NrOfColumns != matrix.m_NrOfColumns)
        {
            _deallocMemory();
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);
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

        matrix.m_pBaseArrayPtr = nullptr;
        matrix.m_NrOfRows = 0;
        matrix.m_NrOfColumns = 0;
    }

    return *this;
}

template<typename DataType>
DataType** Matrix<DataType>::getBaseArrayPtr(int& nrOfRows, int& nrOfColumns)
{
    DataType** pBaseArrayPtr{nullptr};

    if (m_pBaseArrayPtr && m_NrOfRows && m_NrOfColumns)
    {
        nrOfRows = m_NrOfRows;
        nrOfColumns = m_NrOfColumns;
        pBaseArrayPtr = m_pBaseArrayPtr;

        m_pBaseArrayPtr = nullptr;
        m_NrOfRows = 0;
        m_NrOfColumns = 0;
    }
    else
    {
        nrOfRows = 0;
        nrOfColumns = 0;
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

template <typename DataType>
void Matrix<DataType>::getTransposedMatrix(Matrix<DataType>& result)
{
    if (m_NrOfRows == 0)
    {
        if (this != &result)
        {
            result._deallocMemory();
        }
    }
    else if (this == &result)
    {
        Matrix<DataType> matrix{};

        matrix = std::move(*this);

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(matrix.m_NrOfColumns, matrix.m_NrOfRows);

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
        result._deallocMemory();
        result._allocMemory(m_NrOfColumns, m_NrOfRows);

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
    if (rowNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSERT_ROW_NONCONTIGUOUS]};
    }

    DataType** insertPtr=new DataType*[m_NrOfRows+1];

    for (int row{0}; row<rowNr; ++row)
    {
        insertPtr[row] = m_pBaseArrayPtr[row];
    }

    insertPtr[rowNr]=new DataType[m_NrOfColumns];

    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        insertPtr[rowNr][col]=0;
    }

    for (int row{rowNr}; row<m_NrOfRows; ++row)
    {
        insertPtr[row+1] = m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insertPtr;
    ++m_NrOfRows;
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
    if (columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INSERT_COLUMN_NONCONTIGUOUS]};
    }

    DataType** insertPtr{new DataType*[m_NrOfRows]};

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insertPtr[row]=new DataType[m_NrOfColumns+1];
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col=0; col<columnNr; ++col)
        {
            insertPtr[row][col]=m_pBaseArrayPtr[row][col];
        }
    }

    for(int row{0}; row<m_NrOfRows; ++row)
    {
        for(int col=columnNr+1; col<m_NrOfColumns+1; ++col)
        {
            insertPtr[row][col]=m_pBaseArrayPtr[row][col-1];
        }
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insertPtr[row][columnNr]=0;
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete []m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insertPtr;
    ++m_NrOfColumns;
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

    if (m_NrOfRows == 1)
    {
        _deallocMemory();
    }
    else
    {
        DataType** insertPtr{new DataType*[m_NrOfRows-1]};

        for (int row{0}; row<rowNr; ++row)
        {
            insertPtr[row] = m_pBaseArrayPtr[row];
        }

        delete []m_pBaseArrayPtr[rowNr];

        for (int row{rowNr}; row<m_NrOfRows-1; ++row)
        {
            insertPtr[row] = m_pBaseArrayPtr[row+1];
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = insertPtr;
        --m_NrOfRows;
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
    else
    {
        DataType** insertPtr{new DataType*[m_NrOfRows]};

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            insertPtr[row]=new DataType[m_NrOfColumns-1];
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<columnNr; ++col)
            {
                insertPtr[row][col]=m_pBaseArrayPtr[row][col];
            }
        }

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for(int col{columnNr}; col<m_NrOfColumns-1; ++col)
            {
                insertPtr[row][col]=m_pBaseArrayPtr[row][col+1];
            }
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            delete []m_pBaseArrayPtr[row];
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = insertPtr;
        --m_NrOfColumns;
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
void Matrix<DataType>::_allocMemory(int nrOfRows, int nrOfColumns)
{
    m_pBaseArrayPtr = new DataType*[nrOfRows];

    for (int row{0}; row<nrOfRows; ++row)
    {
        m_pBaseArrayPtr[row] = new DataType[nrOfColumns];
    }

    m_NrOfRows = nrOfRows;
    m_NrOfColumns = nrOfColumns;
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    if (m_pBaseArrayPtr)
    {
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            delete []m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = nullptr;

        m_NrOfRows = 0;
        m_NrOfColumns = 0;
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
