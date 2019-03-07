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

    DataType& at(int rowNr, int columnNr);
    DataType& operator[] (int index);

    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    Matrix<DataType>& operator= (Matrix<DataType>&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    DataType** getBaseArrayPtr(int& nrOfRows, int& nrOfColumns, int& rowCapacity, int& columnCapacity);
	
    int getNrOfRows() const;
    int getNrOfColumns() const;
    int getRowCapacity() const;
    int getColumnCapacity() const;

    void transpose(Matrix<DataType>& result);

    void clear();

    // resize and don't init new elements (user has the responsibility to init them), existing elements retain their old values
    void resize(int nrOfRows, int nrOfColumns, int rowCapacity=0, int columnCapacity=0);
    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resizeWithValue(int nrOfRows, int nrOfColumns, const DataType& dataType, int rowCapacity=0, int columnCapacity=0);

    void shrinkToFit();

    void insertRow(int rowNr);
    void insertRow(int rowNr, const DataType& dataType);
    void insertColumn(int columnNr);
    void insertColumn(int columnNr, const DataType& dataType);
    void eraseRow (int rowNr);
    void eraseColumn(int columnNr);

    void catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowNr);
    void splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitColumnNr);

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

    // iterators and iterator methods
    class ZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this priviledge
        friend class Matrix;
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = DataType;
        using difference_type = int;
        using pointer = DataType**;
        using reference = DataType&;

        // "empty" iterator, no position information
        ZIterator();

        DataType& operator*() const;
        DataType* operator->() const;

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

    private:
        ZIterator(const Matrix& matrix, int currentRowNr, int currentColumnNr);

        void _increment();
        void _decrement();

        DataType** m_pMatrixPtr;
        int m_CurrentRowNr;
        int m_CurrentColumnNr;
        int m_NrOfMatrixRows;
        int m_NrOfMatrixColumns;
    };

    ZIterator zBegin();
    ZIterator zEnd();
    ZIterator zRowBegin(int rowNr);
    ZIterator zRowEnd(int rowNr);
    ZIterator getZIterator(int rowNr, int columnNr);
    ZIterator getZIterator(int index);

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

    bool _isEqualTo(const Matrix<DataType>& matrix) const;
    void _adjustSizeAndCapacity(int nrOfRows, int nrOfColumns);

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
DataType& Matrix<DataType>::at(int rowNr, int columnNr)
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

        const int c_InitialRowCapacity{m_RowCapacity};
        const int c_InitialColumnCapacity{m_ColumnCapacity};

        matrix = std::move(*this);

        const int c_RowCapacityToAlloc{c_InitialRowCapacity < matrix.m_NrOfColumns ?  matrix.m_NrOfColumns +  matrix.m_NrOfColumns/4 : c_InitialRowCapacity};
        const int c_ColumnCapacityToAlloc{c_InitialColumnCapacity < matrix.m_NrOfRows ? matrix.m_NrOfRows + matrix.m_NrOfRows/4 : c_InitialColumnCapacity};

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
        result._adjustSizeAndCapacity(m_NrOfColumns, m_NrOfRows);

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
void Matrix<DataType>::resize(int nrOfRows, int nrOfColumns, int rowCapacity, int columnCapacity)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NULL_OR_NEG_DIMENSION]};
    }

    int rowCapacityToSet{rowCapacity > nrOfRows ? rowCapacity : nrOfRows};
    int columnCapacityToSet{columnCapacity > nrOfColumns ? columnCapacity : nrOfColumns};

    if (columnCapacityToSet != m_ColumnCapacity)
    {
        int rowsToKeep{nrOfRows > m_NrOfRows ? m_NrOfRows : nrOfRows};
        int columnsToKeep{nrOfColumns > m_NrOfColumns ? m_NrOfColumns : nrOfColumns};

        Matrix<DataType> matrix{std::move(*this)};
        _allocMemory(nrOfRows, nrOfColumns, rowCapacityToSet, columnCapacityToSet);

        for (int row{0}; row<rowsToKeep; ++row)
        {
            for (int col{0}; col<columnsToKeep; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else if (rowCapacityToSet != m_RowCapacity)
    {
        if (m_RowCapacity < rowCapacityToSet)
        {
            _increaseRowCapacity(rowCapacityToSet-m_RowCapacity);
        }
        else
        {
            _decreaseRowCapacity(m_RowCapacity - rowCapacityToSet);
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
void Matrix<DataType>::resizeWithValue(int nrOfRows, int nrOfColumns, const DataType& value, int rowCapacity, int columnCapacity)
{
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

    int rowDelta{nrOfRows <= m_NrOfRows ? 0 : nrOfRows - m_NrOfRows};
    int columnDelta{nrOfColumns <= m_NrOfColumns ? 0 : nrOfColumns - m_NrOfColumns};

    resize(nrOfRows, nrOfColumns, rowCapacity, columnCapacity);

    if (rowDelta)
    {
        if (columnDelta)
        {
            fillNewItems(*this, 0, m_NrOfRows - rowDelta, m_NrOfColumns - columnDelta, m_NrOfColumns, value);
            fillNewItems(*this, m_NrOfRows - rowDelta, m_NrOfRows, 0, m_NrOfColumns - columnDelta, value);
            fillNewItems(*this, m_NrOfRows - rowDelta, m_NrOfRows, m_NrOfColumns - columnDelta, m_NrOfColumns, value);
        }
        else
        {
            fillNewItems(*this, m_NrOfRows - rowDelta, m_NrOfRows, 0, m_NrOfColumns, value);
        }
    }
    else if (columnDelta)
    {
        fillNewItems(*this, 0, m_NrOfRows, m_NrOfColumns - columnDelta, m_NrOfColumns, value);
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

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
    else if (m_NrOfColumns-1 <= m_ColumnCapacity/4)
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

template<typename DataType>
void Matrix<DataType>::catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    if (firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_ROW_LENGTH]};
    }

    const int c_NrOfRows{firstSrcMatrix.m_NrOfRows + secondSrcMatrix.m_NrOfRows};
    const int c_NrOfColumns{firstSrcMatrix.m_NrOfColumns};
    const int c_RowCapacity{c_NrOfRows + c_NrOfRows / 4};
    const int c_ColumnCapacity{c_NrOfColumns + c_NrOfColumns / 4};

    if (&firstSrcMatrix == this && (&secondSrcMatrix != this))
    {
        const int c_StartingRowNr{m_NrOfRows};
        if (m_RowCapacity < c_NrOfRows)
        {
            _increaseRowCapacity(c_RowCapacity - m_RowCapacity);
        }
        _increaseNrOfRows(c_NrOfRows - m_NrOfRows);

        for (int row{c_StartingRowNr}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row-c_StartingRowNr][col];
            }
        }
    }
    else if (&firstSrcMatrix != this && (&secondSrcMatrix == this))
    {
        const int c_NewRowCapacity{m_RowCapacity < c_NrOfRows ? c_RowCapacity : m_RowCapacity};
        DataType** pBaseArrayPtr{new DataType*[c_NewRowCapacity]};

        for (int row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = new DataType[m_ColumnCapacity];
        }

        for (int row{firstSrcMatrix.m_NrOfRows}; row<c_NrOfRows; ++row)
        {
            pBaseArrayPtr[row] = m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows];
            m_pBaseArrayPtr[row-firstSrcMatrix.m_NrOfRows] = nullptr;
        }

        for (int row{c_NrOfRows}; row<c_NewRowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        for (int row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
        const int c_StartingRowNr{m_NrOfRows};
        if (m_RowCapacity < c_NrOfRows)
        {
            _increaseRowCapacity(c_RowCapacity - m_RowCapacity);
        }
        _increaseNrOfRows(m_NrOfRows);

        for (int row{c_StartingRowNr}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
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
                const int c_SameRowCapacity{m_RowCapacity};
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
}

template<typename DataType>
void Matrix<DataType>::catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    if (firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::MATRIXES_UNEQUAL_COLUMN_LENGTH]};
    }

    const int c_NrOfRows{firstSrcMatrix.m_NrOfRows};
    const int c_NrOfColumns{firstSrcMatrix.m_NrOfColumns + secondSrcMatrix.m_NrOfColumns};
    const int c_RowCapacity{c_NrOfRows + c_NrOfRows / 4};
    const int c_ColumnCapacity{c_NrOfColumns + c_NrOfColumns / 4};

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

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<matrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{matrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
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

        for (int row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (int col{0}; col<firstSrcMatrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{0}; row<firstSrcMatrix.m_NrOfRows; ++row)
        {
            for (int col{firstSrcMatrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
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

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<matrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{matrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
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
                int sameRowCapacity{m_RowCapacity};
                _deallocMemory();
                _allocMemory(c_NrOfRows, c_NrOfColumns, sameRowCapacity, c_ColumnCapacity);
            }
        }
        else if (m_RowCapacity < c_NrOfRows)
        {
            int sameColumnCapacity{m_ColumnCapacity};
            _deallocMemory();
            _allocMemory(c_NrOfRows, c_NrOfColumns, c_RowCapacity, sameColumnCapacity);
        }
        else
        {
            int sameRowCapacity{m_RowCapacity};
            int sameColumnCapacity{m_ColumnCapacity};
            _deallocMemory();
            _allocMemory(c_NrOfRows, c_NrOfColumns, sameRowCapacity, sameColumnCapacity);
        }

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
void Matrix<DataType>::splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowNr)
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

    const int c_FirstDestMatrixNrOfRows{splitRowNr};
    const int c_FirstDestMatrixNrOfColumns{m_NrOfColumns};

    const int c_SecondDestMatrixNrOfRows{m_NrOfRows - splitRowNr};
    const int c_SecondDestMatrixNrOfColumns{m_NrOfColumns};

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (int row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row-splitRowNr][col] = m_pBaseArrayPtr[row][col];
            }
        }

        firstDestMatrix._decreaseNrOfrows(m_NrOfRows - c_FirstDestMatrixNrOfRows);
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        for (int row{0}; row<splitRowNr; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        DataType** pBaseArrayPtr{new DataType*[secondDestMatrix.m_RowCapacity]};

        for (int row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            pBaseArrayPtr[row-splitRowNr] = m_pBaseArrayPtr[row];
            m_pBaseArrayPtr[row] = nullptr;
        }

        for (int row{splitRowNr}; row < secondDestMatrix.m_RowCapacity; ++row)
        {
            pBaseArrayPtr[row] = nullptr;
        }

        int sameRowCapacity{secondDestMatrix.m_RowCapacity};
        int sameColumnCapacity{secondDestMatrix.m_ColumnCapacity};
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

        for (int row{0}; row<splitRowNr; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{splitRowNr}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row-splitRowNr][col] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitColumnNr)
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

    const int c_FirstDestMatrixNrOfRows{m_NrOfRows};
    const int c_FirstDestMatrixNrOfColumns{splitColumnNr};

    const int c_SecondDestMatrixNrOfRows{m_NrOfRows};
    const int c_SecondDestMatrixNrOfColumns{m_NrOfColumns - splitColumnNr};

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{splitColumnNr}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row][col-splitColumnNr] = m_pBaseArrayPtr[row][col];
            }
        }

        Matrix matrix{std::move(*this)};
        _deallocMemory();
        _allocMemory(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        Matrix matrix{std::move(*this)};
        _deallocMemory();
        _allocMemory(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        for (int row{0}; row<c_SecondDestMatrixNrOfRows; ++row)
        {
            for (int col{0}; col<c_SecondDestMatrixNrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col+splitColumnNr];
            }
        }
    }
    else
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<splitColumnNr; ++col)
            {
                firstDestMatrix.m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col];
            }
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{splitColumnNr}; col<m_NrOfColumns; ++col)
            {
                secondDestMatrix.m_pBaseArrayPtr[row][col-splitColumnNr] = m_pBaseArrayPtr[row][col];
            }
        }
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
typename Matrix<DataType>::ZIterator Matrix<DataType>::zBegin()
{
    return ZIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zEnd()
{
    return ZIterator{*this, m_NrOfRows-1, m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowBegin(int rowNr)
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
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowEnd(int rowNr)
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
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(int rowNr, int columnNr)
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
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(int index)
{
    if (index < 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::NEGATIVE_ARG]};
    }

    if (index >= m_NrOfRows*m_NrOfColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::INVALID_ELEMENT_INDEX]};
    }

    return ZIterator{*this, index/m_NrOfColumns, index%m_NrOfColumns};
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
        for (int row{0}; row<m_NrOfRows; ++row)
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

        delete []m_pBaseArrayPtr;
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

        delete []m_pBaseArrayPtr;
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

template<typename DataType>
void Matrix<DataType>::_adjustSizeAndCapacity(int nrOfRows, int nrOfColumns)
{
    const int c_NewRowCapacity{nrOfRows + nrOfRows/4};
    const int c_NewColumnCapacity{nrOfColumns + nrOfColumns/4};
    const int c_OldRowCapacity{m_RowCapacity};
    const int c_OldColumnCapacity{m_ColumnCapacity};

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
DataType& Matrix<DataType>::ZIterator::operator*() const
{
    if (m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::DEREFERENCE_END_ITERATOR]};
    }

    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
DataType* Matrix<DataType>::ZIterator::operator->() const
{
    if (m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::DEREFERENCE_END_ITERATOR]};
    }

    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
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
        const int currentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const int resultingIndex{currentIndex + offset};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = resultingIndex <= 0 ? 0 : resultingIndex >= m_NrOfMatrixRows * m_NrOfMatrixColumns ? m_NrOfMatrixRows - 1 : resultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = resultingIndex <= 0 ? 0 : resultingIndex >= m_NrOfMatrixRows * m_NrOfMatrixColumns ? m_NrOfMatrixColumns : resultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator-(ZIterator::difference_type offset)
{
    ZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const int currentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const int resultingIndex{currentIndex - offset};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = resultingIndex <= 0 ? 0 : resultingIndex >= m_NrOfMatrixRows * m_NrOfMatrixColumns ? m_NrOfMatrixRows - 1 : resultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = resultingIndex <= 0 ? 0 : resultingIndex >= m_NrOfMatrixRows * m_NrOfMatrixColumns ? m_NrOfMatrixColumns : resultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::difference_type Matrix<DataType>::ZIterator::operator-(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    const int firstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const int secondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (firstItCurrentIndex - secondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator==(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator!=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr < it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr <= it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr > it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>=(const ZIterator& it) const
{
    if (m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns)
    {
        throw std::runtime_error{Matr::exceptions[Matr::Error::ITERATORS_DIFFERENT_MATRIXES]};
    }

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr >= it.m_CurrentColumnNr));
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator(const Matrix& matrix, int currentRowNr, int currentColumnNr)
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


