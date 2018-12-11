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
    Matrix(int nrOfRows, int nrOfColumns, const DataType& dataType);
    Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeInitList);
    Matrix(int nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues);
    Matrix(const Matrix<DataType>& matrix);
    Matrix(Matrix<DataType>&& matrix);
    ~Matrix();

    DataType& at(int i,int j);
    DataType& operator[] (int index);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    DataType** getBaseArrayPtr(int& nrOfRows, int& nrOfColumns);
	
    int getNrOfRows() const;
    int getNrOfColumns() const;

    // resize and init elements with default constructor/value (DataType should be default constructible)
    void resize(int nrOfRows, int nrOfColumns);
    // resize and fill new elements with value of dataType (init still done with default constructor/value)
    void resize(int nrOfRows, int nrOfColumns, const DataType& dataType);

    void transformToDiagMatrix(int nrOfRowsColumns, const DataType& dataType, const DataType& diagDataType);
    void transformToEqualElementsMatrix(int nrOfRows, int nrOfColumns, const DataType& dataType);

    void insertRow (int rowNr);
    void insertColumn(int columnNr);
    void deleteRow (int rowNr);
    void deleteColumn(int columnNr);

    void concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix, bool concatenateVertically = true);
    void split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr, bool splitVertically = true);

    void swapItem(int rowNr, int columnNr, Matrix<DataType>& matrix, int matrixRowNr, int matrixColumnNr);
    void swapRow(int rowNr, Matrix<DataType>& matrix, int matrixRowNr);
    void swapColumn(int columnNr, Matrix<DataType>& matrix, int matrixColumnNr);
    void swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr);

    void setAllItemsToSameValue(const DataType& value);
    void copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns, int srcX=0, int srcY=0, int destX=0, int destY=0);

    // functions depending on operations supported by DataItem (addition, multiplication, etc)
    void addRowToColumn(int rowNr, const DataType& coeff, Matrix<DataType>& src, int srcColumnNr, const DataType& srcCoeff, Matrix<DataType>& dest, int destRowOrColumnNr, bool addToDestinationRow = true);
    void addColumnToRow(int columnNr, const DataType& coeff, Matrix<DataType>& src, int srcRowNr, const DataType& srcCoeff, Matrix<DataType>& dest, int destRowOrColumnNr, bool addToDestinationRow = true);
    void addRowToRow(int rowNr, const DataType& coeff, Matrix<DataType>& src, int srcRowNr, const DataType& srcCoeff, Matrix<DataType>& dest, int destRowOrColumnNr, bool addToDestinationRow = true);
    void addColumnToColumn(int columnNr, const DataType& coeff, Matrix<DataType>& src, int srcColumnNr, const DataType& srcCoeff, Matrix<DataType> &dest, int destRowOrColumnNr, bool addToDestinationRow = true);

    DataType determinant() const;
    int rank() const;

    void getInverseMatrix(Matrix<DataType> &coeff, Matrix<DataType>& pseudoInverse) const;
    void getTransposedMatrix(Matrix<DataType>& result);

    void sums(Matrix<DataType>& result, ArithmeticMode mode, int pos=-1) const;
    void products(Matrix<DataType>& result, ArithmeticMode mode, int pos=-1) const;

    Matrix<DataType> operator+ (const Matrix<DataType>& matrix);
    Matrix<DataType> operator- (const Matrix<DataType>& matrix);
    Matrix<DataType> operator* (const Matrix<DataType>& matrix);
    friend Matrix<DataType> operator*(const DataType& data, Matrix<DataType>& matrix);
    Matrix<DataType> operator*(const DataType& data);
    Matrix<DataType> operator^ (int exp);
    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    Matrix<DataType>& operator= (Matrix<DataType>&& matrix);

    bool operator== (const Matrix<DataType>& matrix) const;
    bool operator != (const Matrix<DataType>& matrix) const;
    bool operator < (const Matrix<DataType>& matrix) const;
    bool operator <= (const Matrix<DataType>& matrix) const;
    bool operator > (const Matrix<DataType>& matrix) const;
    bool operator >= (const Matrix<DataType>& matrix) const;

private:
    void _allocMemory(int nrOfRows, int nrOfColumns);
    void _deallocMemory();

    Matrix<DataType> _power(int exp);
    Matrix<DataType> _multiply(const DataType& scalar);

    void _split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestmatrix, int splitRowColumnNr, bool splitVertically);
    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix, bool concatenateVertically);

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

template<typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeInitList)
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    if (nrOfRows * nrOfColumns < static_cast<int>(dataTypeInitList.size()))
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
DataType& Matrix<DataType>:: at(int i,int j)
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

template<typename DataType>
DataType** Matrix<DataType>::getBaseArrayPtr(int& nrOfRows, int& nrOfColumns)
{
    DataType** pBaseArrayPtr{nullptr};

    if (!m_pBaseArrayPtr && (m_NrOfRows != 0) && (m_NrOfColumns != 0))
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

template<typename DataType>
void Matrix<DataType>::resize(int nrOfRows, int nrOfColumns)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }
    else
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
        Matrix<DataType> matrix{};

        std::swap(m_pBaseArrayPtr, matrix.m_pBaseArrayPtr);

        matrix.m_NrOfRows = m_NrOfRows;
        matrix.m_NrOfColumns = m_NrOfColumns;

        _deallocMemory(); // not actually required, it's just put for the sake of good practice (first free memory, then alloc new one)
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
        Matrix<DataType> matrix{nrOfRowsColumns, dataType, diagDataType};
        swapWithMatrix(matrix);
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
        swapWithMatrix(matrix);
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

    DataType** insert_ptr=new DataType*[m_NrOfRows+1];

    for (int row{0}; row<rowNr; ++row)
    {
        insert_ptr[row] = m_pBaseArrayPtr[row];
    }

    insert_ptr[rowNr]=new DataType[m_NrOfColumns];

    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        insert_ptr[rowNr][col]=0;
    }

    for (int row{rowNr}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row+1] = m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insert_ptr;
    ++m_NrOfRows;
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

    DataType** insert_ptr{new DataType*[m_NrOfRows]};

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row]=new DataType[m_NrOfColumns+1];
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col=0; col<columnNr; ++col)
        {
            insert_ptr[row][col]=m_pBaseArrayPtr[row][col];
        }
    }

    for(int row{0}; row<m_NrOfRows; ++row)
    {
        for(int col=columnNr+1; col<m_NrOfColumns+1; ++col)
        {
            insert_ptr[row][col]=m_pBaseArrayPtr[row][col-1];
        }
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row][columnNr]=0;
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete []m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insert_ptr;
    ++m_NrOfColumns;
}

template <typename DataType>
void Matrix<DataType>::deleteRow (int rowNr)
{
    if (m_NrOfRows==1)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ERASE_THE_ONLY_ROW]};
    }

    if (rowNr>=m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
    }

    if (rowNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    DataType** insert_ptr{new DataType*[m_NrOfRows-1]};

    for (int row{0}; row<rowNr; ++row)
    {
        insert_ptr[row] = m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr[rowNr];

    for (int row{rowNr}; row<m_NrOfRows-1; ++row)
    {
        insert_ptr[row] = m_pBaseArrayPtr[row+1];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insert_ptr;
    --m_NrOfRows;
}

template <typename DataType>
void Matrix<DataType>::deleteColumn(int columnNr)
{
    if (m_NrOfColumns==1)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ERASE_THE_ONLY_COLUMN]};
    }

    if (columnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
    }

    DataType** insert_ptr{new DataType*[m_NrOfRows]};

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row]=new DataType[m_NrOfColumns-1];
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<columnNr; ++col)
        {
            insert_ptr[row][col]=m_pBaseArrayPtr[row][col];
        }
    }

    for(int row{0}; row<m_NrOfRows; ++row)
    {
        for(int col{columnNr}; col<m_NrOfColumns-1; ++col)
        {
            insert_ptr[row][col]=m_pBaseArrayPtr[row][col+1];
        }
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete []m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = insert_ptr;
    --m_NrOfColumns;
}

template <typename DataType>
void Matrix<DataType>::concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix, bool concatenateVertically)
{
    if (concatenateVertically && (firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_ROW_LENGTH]};
    }

    if ((!concatenateVertically) && (firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_COLUMN_LENGTH]};
    }

    Matrix<DataType> thirdMatrix{};

    if ((firstSrcMatrix.m_pBaseArrayPtr==m_pBaseArrayPtr) || (secondSrcMatrix.m_pBaseArrayPtr==m_pBaseArrayPtr))
    {
        thirdMatrix.m_pBaseArrayPtr = m_pBaseArrayPtr;
        thirdMatrix.m_NrOfRows = m_NrOfRows;
        thirdMatrix.m_NrOfColumns = m_NrOfColumns;

        _allocMemory(1,1);
    }

    if ((firstSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) && (secondSrcMatrix.m_pBaseArrayPtr!=m_pBaseArrayPtr))
    {
        _concatenate(thirdMatrix, secondSrcMatrix, concatenateVertically);
    }
    else if ((firstSrcMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr) && (secondSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
    {
        _concatenate(firstSrcMatrix, thirdMatrix, concatenateVertically);
    }
    else if ((firstSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) && (secondSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
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
    if (&firstDestMatrix==&secondDestMatrix)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SAME_VARIABLE_TWO_ARGS]};
    }

    if (splitRowColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (splitVertically)
    {
        if (splitRowColumnNr>m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
        }
        if ((splitRowColumnNr == 0) || (splitRowColumnNr == m_NrOfRows))
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_ROWS]};
        }
    }
    else {
        if (splitRowColumnNr>m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
        }
        if ((splitRowColumnNr == 0) || (splitRowColumnNr == m_NrOfColumns))
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::RESULT_NO_COLUMNS]};
        }
    }

    Matrix<DataType> thirdMatrix{};

    if ((firstDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) || (secondDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr)) {
        thirdMatrix.m_pBaseArrayPtr = m_pBaseArrayPtr;
        thirdMatrix.m_NrOfRows = m_NrOfRows;
        thirdMatrix.m_NrOfColumns = m_NrOfColumns;

        _allocMemory(1,1);
    }

    if ((firstDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) && (secondDestMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr))
    {
        thirdMatrix._split(*this, secondDestMatrix, splitRowColumnNr, splitVertically);
    }
    else if ((firstDestMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr) && (secondDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
    {
        thirdMatrix._split(firstDestMatrix, *this, splitRowColumnNr, splitVertically);
    }
    else
    {
        _split(firstDestMatrix, secondDestMatrix, splitRowColumnNr, splitVertically);
    }
}

template <typename DataType>
void Matrix<DataType>::swapItem(int rowNr, int columnNr, Matrix<DataType>& matrix, int matrixRowNr, int matrixColumnNr)
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
void Matrix<DataType>::swapRow(int rowNr, Matrix& matrix, int matrixRowNr)
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
void Matrix<DataType>::swapColumn(int columnNr, Matrix& matrix, int matrixColumnNr)
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

template <typename DataType> void Matrix<DataType>::setAllItemsToSameValue(const DataType& value)
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
    if(m_pBaseArrayPtr || !src.m_pBaseArrayPtr)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_PTR]};
    }

    if (src.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    if (nrOfRows<0 || nrOfColumns<0 || srcX<0 || srcY<0 || destX<0 || destY<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (srcX+nrOfRows>src.m_NrOfRows || srcY+nrOfColumns>src.m_NrOfColumns || destX+nrOfRows>m_NrOfRows || destY+nrOfColumns>m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    for (int row{0}; row<nrOfRows; ++row)
    {
        for (int col{0}; col<nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[destX+row][destY+col] = src.m_pBaseArrayPtr[srcX+row][srcY+col];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addRowToColumn(int rowNr, const DataType& coeff, Matrix& src, int srcColumnNr, const DataType& srcCoeff, Matrix& dest, int destRowOrColumnNr, bool addToDestinationRow)
{
    if (rowNr<0 || srcColumnNr<0 || destRowOrColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (rowNr>=m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
    }

    if (srcColumnNr>=src.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
    }

    if (addToDestinationRow)
    {
        if (destRowOrColumnNr>=dest.m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_ROW_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowOrColumnNr][row] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
    else
    {
        if (destRowOrColumnNr>=dest.m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_COLUMN_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowOrColumnNr] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToRow(int columnNr, const DataType& coeff, Matrix& src, int srcRowNr, const DataType& srcCoeff, Matrix& dest, int destRowOrColumnNr, bool addToDestinationRow)
{
    if (columnNr<0 || srcRowNr<0 || destRowOrColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (columnNr>=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
    }

    if (srcRowNr>=src.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
    }

    if (addToDestinationRow)
    {
        if (destRowOrColumnNr>=dest.m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_ROW_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowOrColumnNr][row] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
    else
    {
        if (destRowOrColumnNr>=dest.m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_COLUMN_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowOrColumnNr] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addRowToRow(int rowNr, const DataType& coeff, Matrix &src, int srcRowNr, const DataType& srcCoeff, Matrix& dest, int destRowOrColumnNr, bool addToDestinationRow)
{
    if (rowNr<0 || srcRowNr<0 || destRowOrColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if ((rowNr>=m_NrOfRows) || (srcRowNr>=src.m_NrOfRows))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ROW_DOES_NOT_EXIST]};
    }

    if (addToDestinationRow)
    {
        if (destRowOrColumnNr>=dest.m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_ROW_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowOrColumnNr][row] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
    else {
        if (destRowOrColumnNr>=dest.m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_COLUMN_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowOrColumnNr] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToColumn(int columnNr, const DataType& coeff, Matrix& src, int srcColumnNr, const DataType& srcCoeff, Matrix& dest, int destRowOrColumnNr, bool addToDestinationRow)
{
    if (columnNr<0 || srcColumnNr<0 || destRowOrColumnNr<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if ((columnNr>=m_NrOfColumns) || (srcColumnNr>=src.m_NrOfColumns))
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::COLUMN_DOES_NOT_EXIST]};
    }

    if (addToDestinationRow)
    {
        if (destRowOrColumnNr>=dest.m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_ROW_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowOrColumnNr][row] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
    else
    {
        if (destRowOrColumnNr>=dest.m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::DEST_COLUMN_DOES_NOT_EXIST]};
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowOrColumnNr] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
}

template <typename DataType>
DataType Matrix<DataType>::determinant() const
{
    if (m_NrOfRows!=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_DIMENSIONS]};
    }

    Matrix<DataType> matrix{*this};
    int sign{1};
    int temp{1};
    bool isZeroDet{false};

    // convert to triangle matrix using Gauss-Jordan algorithm
    for (int diagIndex{0}; diagIndex<m_NrOfRows-1; ++diagIndex)
    {
        if (matrix.m_pBaseArrayPtr[diagIndex][diagIndex]==0)
        {
            isZeroDet = true;
            for (int firstRowIndex{diagIndex+1}; firstRowIndex<m_NrOfRows; ++firstRowIndex)
            {
                if (matrix.m_pBaseArrayPtr[firstRowIndex][diagIndex]!=0)
                {
                    matrix.swapRow(diagIndex,firstRowIndex);
                    sign = sign * (-1);

                    for (int colIndex{diagIndex+1}; colIndex<m_NrOfColumns; ++colIndex)
                    {
                        for (int secondRowIndex{diagIndex+1}; secondRowIndex<m_NrOfRows; ++secondRowIndex)
                        {
                            matrix.m_pBaseArrayPtr[secondRowIndex][colIndex] = matrix.m_pBaseArrayPtr[secondRowIndex][colIndex] * (matrix.m_pBaseArrayPtr[diagIndex][diagIndex]) -
                                                                         matrix.m_pBaseArrayPtr[diagIndex][colIndex] * (matrix.m_pBaseArrayPtr[secondRowIndex][diagIndex]);
                            temp = temp * (matrix.m_pBaseArrayPtr[diagIndex][diagIndex] * matrix.m_pBaseArrayPtr[secondRowIndex][diagIndex]);
                        }
                    }

                    isZeroDet = false;
                    break;
                }
            }
        }
    }

    DataType det{1};

    // multiply elements from main diagonal to get the determinant
    if (isZeroDet)
    {
        det = 0;
    }
    else
    {
        for (int diag{0}; diag<m_NrOfRows; ++diag)
        {
            det  =det * matrix.m_pBaseArrayPtr[diag][diag];
        }
        det = (det/temp) * sign;
    }

    return det;
}

template<typename DataType>
int Matrix<DataType>::rank() const
{
    auto continueCalculation = [](Matrix& matrix, int& posX, int& posY)
    {
        for (int row{posX+1}; row<matrix.m_NrOfRows; ++row)
        {
            for (int col{posY+1}; col<matrix.m_NrOfColumns; ++col)
            {
                matrix.m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col] * matrix.m_pBaseArrayPtr[posX][posY] -
                                                   matrix.m_pBaseArrayPtr[posX][col] * matrix.m_pBaseArrayPtr[row][posY];
            }
        }

        ++posX;
        ++posY;
    };

    Matrix<DataType> matrix{};

    if (m_NrOfRows>m_NrOfColumns)
    {
        getTransposedMatrix(matrix);
    }
    else
    {
        matrix = *this;
    }

    int posX{0};
    int posY{0};
    int matrixRank{0};

    while (posX < matrix.m_NrOfRows-1)
    {
        if (matrix.m_pBaseArrayPtr[posX][posY]==0)
        {
            for (int row{posX+1}; row<matrix.m_NrOfRows; ++row)
            {
                if (matrix.m_pBaseArrayPtr[row][posY]!=0)
                {
                    ++matrixRank;
                    matrix.swapRow(row, posX);
                    continueCalculation(matrix, posX, posY);
                }
            }

            for (int col{posY+1}; col<matrix.m_NrOfColumns; ++col)
            {
                if (matrix.m_pBaseArrayPtr[posX][col]!=0)
                {
                    ++matrixRank;
                    matrix.swapColumn(col,posY);
                    continueCalculation(matrix, posX, posY);
                }
            }
        }
        else
        {
            ++matrixRank;
        }
    }

    for (int col{posY}; col<matrix.m_NrOfColumns; ++col)
    {
        if (matrix.m_pBaseArrayPtr[posX][col]!=0)
        {
            ++matrixRank;
            break;
        }
    }

    return matrixRank;
}

template<typename DataType>
void Matrix<DataType>::getInverseMatrix(Matrix<DataType>& coeff, Matrix<DataType>& pseudoInverse) const
{
    auto continueCalculation = [](Matrix<DataType>& pseudoInverse, Matrix<DataType>& helperMatrix, int diagIndex, int nrOfRows)
    {
        for (int col{0}; col<nrOfRows; ++col)
        {
            for (int row{diagIndex+1}; row<nrOfRows; ++row)
            {
                if (col>diagIndex)
                {
                    helperMatrix.m_pBaseArrayPtr[row][col] = helperMatrix.m_pBaseArrayPtr[row][col] * helperMatrix.m_pBaseArrayPtr[diagIndex][diagIndex] -
                                                             helperMatrix.m_pBaseArrayPtr[diagIndex][col] * helperMatrix.m_pBaseArrayPtr[row][diagIndex];
                }

                pseudoInverse.m_pBaseArrayPtr[row][col] = pseudoInverse.m_pBaseArrayPtr[row][col] * helperMatrix.m_pBaseArrayPtr[diagIndex][diagIndex] -
                                                          pseudoInverse.m_pBaseArrayPtr[diagIndex][col] * helperMatrix.m_pBaseArrayPtr[row][diagIndex];
            }
        }
    };

    Matrix <DataType> matrix{};

    if (m_pBaseArrayPtr == coeff.m_pBaseArrayPtr || m_pBaseArrayPtr == pseudoInverse.m_pBaseArrayPtr)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    if (m_NrOfRows!=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_DIMENSIONS]};
    }

    matrix = *this;
    pseudoInverse.transformToDiagMatrix(m_NrOfRows, 0, 1);
    coeff.resize(m_NrOfRows,1);

    for (int diag{0}; diag<m_NrOfRows-1; ++diag)
    {
        bool rowSwapped{false};

        if (matrix.m_pBaseArrayPtr[diag][diag]==0)
        {
            for (int col{diag+1}; col<m_NrOfRows; ++col)
            {
                if (matrix.m_pBaseArrayPtr[diag][col]!=0)
                {
                    matrix.swapRow(diag, matrix, col);
                    pseudoInverse.swapRow(diag, pseudoInverse, col);
                    continueCalculation(pseudoInverse, matrix, diag, m_NrOfRows);
                    rowSwapped = true;
                }
            }

            if (rowSwapped)
            {
                continue;
            }

            throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_DETERMINANT]};
        }
    }

    for (int diag{0}; diag<m_NrOfRows; ++diag)
    {
        for (int row{diag+1}; row<m_NrOfRows; ++row)
        {
            matrix.m_pBaseArrayPtr[row][diag] = 0;
        }
    }

    if (matrix.m_pBaseArrayPtr[m_NrOfRows-1][m_NrOfRows-1]==0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_DETERMINANT]};
    }

    for (int diag{m_NrOfRows-1}; diag>0; --diag)
    {
        for (int row{0}; row<=diag-1; ++row)
        {
            for (int col{0}; col<=m_NrOfRows-1; ++col)
            {
                if (col<diag)
                {
                    matrix.m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col] * matrix.m_pBaseArrayPtr[diag][diag] -
                                                       matrix.m_pBaseArrayPtr[diag][col] * matrix.m_pBaseArrayPtr[row][diag];
                }

                pseudoInverse.m_pBaseArrayPtr[row][col] = pseudoInverse.m_pBaseArrayPtr[row][col] * matrix.m_pBaseArrayPtr[diag][diag] -
                                                          pseudoInverse.m_pBaseArrayPtr[diag][col] * matrix.m_pBaseArrayPtr[row][diag];
            }
        }
    }

    for (int diag{0}; diag<m_NrOfRows; ++diag)
    {
        coeff.m_pBaseArrayPtr[diag][0] = matrix.m_pBaseArrayPtr[diag][diag];
    }
}

template <typename DataType>
void Matrix<DataType>::getTransposedMatrix(Matrix<DataType>& result)
{
    Matrix<DataType> matrix{};

    if (m_pBaseArrayPtr==result.m_pBaseArrayPtr)
    {
        std::swap(m_pBaseArrayPtr, matrix.m_pBaseArrayPtr);

        matrix.m_NrOfRows = m_NrOfRows;
        matrix.m_NrOfColumns = m_NrOfColumns;

        resize(m_NrOfColumns, m_NrOfRows);

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
        result.resize(m_NrOfColumns,m_NrOfRows);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                result.m_pBaseArrayPtr[col][row]=m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::sums(Matrix& result, ArithmeticMode mode, int pos) const
{
    if (result.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    switch (mode)
    {
    case ArithmeticMode::ALL_ITEMS:
    {
        DataType allItemsSum{0};
        result.resize(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                allItemsSum *= m_pBaseArrayPtr[row][col];
            }
        }
        result.m_pBaseArrayPtr[0][0] = allItemsSum;
        break;
    }
    case ArithmeticMode::ONE_ROW:
    {
        if (pos<0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
        }

        if (pos>=m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
        }

        DataType currentRowItemsSum{0};
        result.resize(1,1);

        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            currentRowItemsSum *= m_pBaseArrayPtr[pos][col];
        }
        result.m_pBaseArrayPtr[0][0] = currentRowItemsSum;
        break;
    }
    case ArithmeticMode::EACH_ROW:
    {
        result.resize(m_NrOfRows,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            DataType eachRowItemsSum{0};
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                eachRowItemsSum *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[row][0] = eachRowItemsSum;
        }
        break;
    }
    case ArithmeticMode::ONE_COLUMN:
    {
        if (pos<0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
        }

        if (pos>=m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
        }

        DataType currentColumnItemsSum{0};
        result.resize(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            currentColumnItemsSum *= m_pBaseArrayPtr[row][pos];
        }
        result.m_pBaseArrayPtr[0][0] = currentColumnItemsSum;
        break;
    }
    case ArithmeticMode::EACH_COLUMN:
        result.resize(1, m_NrOfColumns);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            DataType eachColumnItemsSum{0};
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                eachColumnItemsSum *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[0][col] = eachColumnItemsSum;
        }
    default:
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_MODE]};
    }
}

template <typename DataType>
void Matrix<DataType>::products(Matrix& result, ArithmeticMode mode, int pos) const
{
    if (result.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::CURRENT_MATRIX_AS_ARG]};
    }

    switch (mode)
    {
    case ArithmeticMode::ALL_ITEMS:
    {
        DataType allItemsProduct{1};
        result.resize(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                allItemsProduct *= m_pBaseArrayPtr[row][col];
            }
        }
        result.m_pBaseArrayPtr[0][0] = allItemsProduct;
        break;
    }
    case ArithmeticMode::ONE_ROW:
    {
        if (pos<0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
        }

        if (pos>=m_NrOfRows)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_ROW_DOES_NOT_EXIST]};
        }

        DataType currentRowItemsProduct{1};
        result.resize(1,1);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            currentRowItemsProduct *= m_pBaseArrayPtr[pos][col];
        }
        result.m_pBaseArrayPtr[0][0] = currentRowItemsProduct;
        break;
    }
    case ArithmeticMode::EACH_ROW:
    {
        result.resize(m_NrOfRows,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            DataType eachRowItemsProduct{1};
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                eachRowItemsProduct *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[row][0] = eachRowItemsProduct;
        }
        break;
    }
    case ArithmeticMode::ONE_COLUMN:
    {
        if (pos<0)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
        }

        if (pos>=m_NrOfColumns)
        {
            throw std::runtime_error{Matr::exceptions[Matr::Error::SRC_COLUMN_DOES_NOT_EXIST]};
        }

        DataType currentColumnItemsProduct{1};
        result.resize(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            currentColumnItemsProduct *= m_pBaseArrayPtr[row][pos];
        }
        result.m_pBaseArrayPtr[0][0] = currentColumnItemsProduct;
        break;
    }
    case ArithmeticMode::EACH_COLUMN:
        result.resize(1, m_NrOfColumns);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            DataType eachColumnItemsProduct{1};
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                eachColumnItemsProduct *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[0][col] = eachColumnItemsProduct;
        }
    default:
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_MODE]};
    }
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator+ (const Matrix<DataType>& matrix)
{
    if (m_NrOfRows != matrix.m_NrOfRows || m_NrOfColumns != matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_DIMENSIONS]};
    }

    Matrix<DataType> result{};
    result.resize(m_NrOfRows, m_NrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            result.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col] + matrix.m_pBaseArrayPtr[row][col];
        }
    }

    return result;
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator- (const Matrix<DataType>& matrix)
{
    if (m_NrOfRows != matrix.m_NrOfRows || m_NrOfColumns != matrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_DIMENSIONS]};
    }

    Matrix<DataType> result{};
    result.resize(m_NrOfRows, m_NrOfColumns);

    for (int i{0}; i<m_NrOfRows; ++i)
    {
        for (int j{0}; j<m_NrOfColumns; ++j)
        {
            result.m_pBaseArrayPtr[i][j] = m_pBaseArrayPtr[i][j] - matrix.m_pBaseArrayPtr[i][j];
        }
    }

    return result;
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator* (const Matrix<DataType>& matrix)
{
    if (m_NrOfColumns!=matrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_ROWS_UNEQUAL_COLUMNS]};
    }

    Matrix<DataType> result{};
    result.resize(m_NrOfRows,matrix.m_NrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<matrix.m_NrOfColumns; ++col)
        {
            for (int pivot{0}; pivot<m_NrOfColumns; ++pivot)
            {
                result.m_pBaseArrayPtr[row][col] = result.m_pBaseArrayPtr[row][col]+m_pBaseArrayPtr[row][pivot] * matrix.m_pBaseArrayPtr[pivot][col];
            }
        }
    }

    return result;
}

template<typename DataType>
Matrix<DataType> operator*(const DataType &data, Matrix<DataType> &matrix)
{
    return matrix._multiply(data);
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::operator*(const DataType &data)
{
    return _multiply(data);
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator^ (int exp)
{
    if (m_NrOfRows!=m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_DIMENSIONS]};
    }

    if (exp<0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    Matrix<DataType> result{};

    if (exp==0)
    {
        result.transformToDiagMatrix(m_NrOfRows, 0, 1);
        return result;
    }

    result=(*this);

    return result._power(exp);
}

template <typename DataType>
Matrix<DataType>& Matrix<DataType>:: operator= (const Matrix<DataType>& matrix)
{
    if (!(matrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
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
    m_pBaseArrayPtr = matrix.m_pBaseArrayPtr;
    m_NrOfRows = matrix.m_NrOfRows;
    m_NrOfColumns = matrix.m_NrOfColumns;

    matrix.m_pBaseArrayPtr = nullptr;
    matrix.m_NrOfRows = 0;
    matrix.m_NrOfColumns = 0;

    return *this;
}

template <typename DataType>
bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix) const
{
    bool areEqual{false};

    if (matrix.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        areEqual = true;
    }
    else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
    {
        bool continueChecking{true};

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col]!=matrix.m_pBaseArrayPtr[row][col])
                {
                    continueChecking = false;
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
bool Matrix<DataType>::operator!=(const Matrix<DataType>& matrix) const
{
    bool areRanksDifferent{true};

    if (&matrix != this)
    {
        // avoid calling the rank() method if same matrix (too costly)
        if (rank() == matrix.rank())
        {
            areRanksDifferent = false;
        }
    }
    else
    {
        areRanksDifferent = false;
    }

    return areRanksDifferent;
}

template<typename DataType>
bool Matrix<DataType>::operator<(const Matrix<DataType> &matrix) const
{
    bool isRankSmaller{true};

    if (&matrix !=this)
    {
        // avoid calling the rank() method if same matrix (too costly)
        if (rank()>=matrix.rank())
        {
            isRankSmaller = false;
        }
    }
    else
    {
        isRankSmaller = false;
    }

    return isRankSmaller;
}

template<typename DataType>
bool Matrix<DataType>::operator<=(const Matrix<DataType> &matrix) const
{
    bool isRankSmallerOrEqual{true};

    if (&matrix !=this)
    {
        // avoid calling the rank() method if same matrix (too costly)
        if (rank()>matrix.rank())
        {
            isRankSmallerOrEqual = false;
        }
    }
    else
    {
        isRankSmallerOrEqual = false;
    }

    return isRankSmallerOrEqual;
}

template<typename DataType>
bool Matrix<DataType>::operator>(const Matrix<DataType> &matrix) const
{
    bool isRankHigher{true};

    if (&matrix !=this)
    {
        // avoid calling the rank() method if same matrix (too costly)
        if (rank()<=matrix.rank())
        {
            isRankHigher = false;
        }
    }
    else
    {
        isRankHigher = false;
    }

    return isRankHigher;
}

template<typename DataType>
bool Matrix<DataType>::operator>=(const Matrix<DataType> &matrix) const
{
    bool isRankHigherOrEqual{true};

    if (&matrix !=this)
    {
        // avoid calling the rank() method if same matrix (too costly)
        if (rank()<matrix.rank())
        {
            isRankHigherOrEqual = false;
        }
    }
    else
    {
        isRankHigherOrEqual = false;
    }

    return isRankHigherOrEqual;
}

template<typename DataType>
void Matrix<DataType>::_allocMemory(int nrOfRows, int nrOfColumns)
{
    m_NrOfRows = nrOfRows;
    m_NrOfColumns = nrOfColumns;
    m_pBaseArrayPtr = new DataType*[nrOfRows];

    for (int row{0}; row<nrOfRows; ++row)
    {
        m_pBaseArrayPtr[row] = new DataType[nrOfColumns];
    }
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete m_pBaseArrayPtr[row];
    }

    delete []m_pBaseArrayPtr;
    m_pBaseArrayPtr = nullptr;
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::_power(int exponent)
{
    Matrix<DataType> result{*this};
    std::vector<bool> remainders;

    int quotient{exponent};

    while (quotient > 1)
    {
        remainders.push_back(static_cast<bool>(quotient%2));
        quotient /= 2;
    }

    for (std::vector<bool>::const_iterator it = remainders.cend(); it != remainders.cbegin(); --it)
    {
        result *= result;

        if (*it)
        {
            result *= this;
        }
    }

    return result;
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::_multiply(const DataType &scalar)
{
    Matrix<DataType> matrix{};
    matrix.resize(m_NrOfRows, m_NrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            matrix.m_pBaseArrayPtr[row][col] = scalar * m_pBaseArrayPtr[row][col];
        }
    }

    return matrix;
}

template<typename DataType>
void Matrix<DataType>::_split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr, bool splitVertically)
{
    firstDestMatrix._deallocMemory();
    secondDestMatrix._deallocMemory();

    if (splitVertically) {
        firstDestMatrix._allocMemory(splitRowColumnNr, m_NrOfColumns);
        secondDestMatrix._allocMemory(m_NrOfRows-splitRowColumnNr, m_NrOfColumns);

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
        secondDestMatrix._allocMemory(m_NrOfRows, m_NrOfColumns-splitRowColumnNr);

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
        resize(firstSrcMatrix.m_NrOfRows+secondSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns);

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
        resize(firstSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns+secondSrcMatrix.m_NrOfColumns);

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
