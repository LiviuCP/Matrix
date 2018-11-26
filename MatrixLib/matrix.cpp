#include <vector>

#include "matrix.h"

template<typename DataType> int Matrix<DataType>::s_FilePosX=0;
template<typename DataType> int Matrix<DataType>::s_FilePosY=0;

template <typename DataType>
Matrix<DataType>::Matrix()
    : m_pBaseArrayPtr{nullptr}
    , m_NrOfRows{0}
    , m_NrOfColumns{0}
    , m_PosX{-1}
    , m_PosY{-1}
    , m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, const DataType& dataType)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3, "template <typename DataType> Matrix<DataType>::Matrix(int m, int n)");
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
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3, "template<typename DataType>Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeList)");
    }

    if (nrOfRows * nrOfColumns < dataTypeInitList.size())
    {
        _handleException(0, "template<typename DataType>Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, std::initializer_list<DataType> dataTypeList)");
    }

    _allocMemory(nrOfRows, nrOfColumns);

    int initListIndex{0};
    for (int row{0}; row < nrOfRows; ++row)
    {
        for (int col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = dataTypeInitList[initListIndex];
            ++initListIndex;
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRowsColumns, const DataType& dataType, const DataType& diagDataType)
    : Matrix<DataType>{nrOfRowsColumns, nrOfRowsColumns, dataType}
{
    for (int diag{0}; diag<m_NrOfRows; ++diag)
    {
        m_pBaseArrayPtr[diag][diag] = diagDataType;
    }
}

// for converting static matrixes from legacy code to object (dynamic) matrixes only (user is responsible to ensure the static matrix is not read "out-of-bounds")
template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, DataType** matrixPtr)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (!matrixPtr)
    {
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    }

    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    }

    _allocMemory(nrOfRows, nrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = matrixPtr[row][col];
        }
    }
}

// for converting one-dimensional arrays from legacy code to bidimensional dynamic matrixes only (user is responsible to ensure the static array is not read "out-of-bounds")
template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, DataType* matrixPtr)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (!matrixPtr)
    {
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }

    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }

    _allocMemory(nrOfRows, nrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = *(matrixPtr++);
        }
    }
}

template<typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, std::istream &in)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }

    _allocMemory(nrOfRows,nrOfColumns);
    _readDiscard(in);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        _readTextLine(in);
        ++m_PosX;
        ++s_FilePosX; // should this be reset to 0 after matrix is initialized?
    }

    // back to position 0 as when set by _allocMemory()
    m_PosX = 0;
}

template <typename DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& matrix)
    : m_MatrixPrintMode{matrix.m_MatrixPrintMode}
    , m_MatrixEntryMode{matrix.m_MatrixEntryMode}
    , m_WrapMatrixByRow{matrix.m_WrapMatrixByRow}
{
    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
        }
    }

    setPosX(matrix.m_PosX);
    setPosY(matrix.m_PosY);
}

template<typename DataType>
Matrix<DataType>::~Matrix()
{
    _deallocMemory();
}

template<typename DataType>
DataType& Matrix<DataType>:: get(int i,int j)
{
    if (i<0 || j<0)
    {
        _handleException(16, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
    }
    if (i>=m_NrOfRows || j>=m_NrOfColumns)
    {
        _handleException(18, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
    }
    return m_pBaseArrayPtr[i][j];
}

template<typename DataType>
DataType** Matrix<DataType>::getp()
{
    return m_pBaseArrayPtr;
}

template<typename DataType>
DataType* Matrix<DataType>::getp(int i)
{
    if (i<0)
    {
        _handleException(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
    }
    return m_pBaseArrayPtr[i%m_NrOfRows];
}

template<typename DataType>
int Matrix<DataType>::getNrOfRows()
{
    return m_NrOfRows;
}

template<typename DataType>
int Matrix<DataType>::getNrOfColumns()
{
    return m_NrOfColumns;
}

template<typename DataType>
int Matrix<DataType>::getPosX()
{
    return m_PosX;
}

template<typename DataType>
int Matrix<DataType>::getPosY()
{
    return m_PosY;
}

template<typename DataType>
int Matrix<DataType>::getFilePosX()
{
    return s_FilePosX;
}

template<typename DataType>
int Matrix<DataType>::getFilePosY()
{
    return s_FilePosY;
}

template<typename DataType>
void Matrix<DataType>::setPosX(int m)
{
    m_PosX = abs(m) % m_NrOfRows;
}

template<typename DataType>
void Matrix<DataType>::setPosY(int n)
{
    m_PosY = abs(n) % m_NrOfColumns;
}

template<typename DataType>
void Matrix<DataType>::setFilePosX(int filePosX)
{
    s_FilePosX = abs(filePosX);
}

template<typename DataType>
void Matrix<DataType>::setFilePosY(int filePosY)
{
    s_FilePosY = abs(filePosY);
}

template<typename DataType>
void Matrix<DataType>::setMatrixEntryMode(int matrixEntryMode)
{
    m_MatrixEntryMode = abs(matrixEntryMode) % 18;
}

template<typename DataType>
void Matrix<DataType>::setMatrixPrintMode(int matrixPrintMode)
{
    m_MatrixPrintMode=abs(matrixPrintMode) % 6;
}

template <typename DataType> void Matrix<DataType>::setItemsToZero()
{
    for (int row=0; row<m_NrOfRows; ++row)
    {
        for (int col=0; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col]=0;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::incrPosX()
{
    if (m_PosX<m_NrOfRows-1)
    {
        ++m_PosX;
    }
    else
    {
        m_PosX = 0;
    }
}

template<typename DataType>
void Matrix<DataType>::decrPosX()
{
    if (m_PosX>0) m_PosX--; else m_PosX=m_NrOfRows-1;
}

template<typename DataType>
void Matrix<DataType>::incrPosY()
{
    if (m_PosY<m_NrOfColumns-1)
    {
        ++m_PosY;
    }
    else
    {
        m_PosY = 0;
    }
}

template<typename DataType>
void Matrix<DataType>::decrPosY()
{
    if (m_PosY>0)
    {
        --m_PosY;
    }
    else
    {
        m_PosY = m_NrOfColumns-1;
    }
}

template<typename DataType>
void Matrix<DataType>::resetCurrentPos()
{
    m_PosX = 0;
    m_PosY = 0;
}

template<typename DataType>
void Matrix<DataType>::resetCurrentPosInFile()
{
    s_FilePosX = 0;
    s_FilePosY = 0;
}

template<typename DataType>
void Matrix<DataType>::resizeNoInit(int nrOfRows, int nrOfColumns)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        _handleException(3,"template <typename dataType> void Matrix<dataType>::resize(int m, int n)");
    }
    else
    {
        _deallocMemory();
        _allocMemory(nrOfRows, nrOfColumns);
    }
}

template <typename DataType>
void Matrix<DataType>::transformToUnitMatrix(int nrOfRowsColumns)
{
    if (nrOfRowsColumns<=0)
    {
        _handleException(3,"template <typename DataType> void Matrix<DataType>::unit(int m)");
    }
    else
    {
        _deallocMemory();
        _allocMemory(nrOfRowsColumns, nrOfRowsColumns);
        setItemsToZero();
        for (int diagIndex{0}; diagIndex<nrOfRowsColumns; diagIndex++)
        {
            m_pBaseArrayPtr[diagIndex][diagIndex] = 1;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::transformToZeroMatrix(int nrOfRows, int nrOfColumns)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        _handleException(3, "template <typename DataType> void Matrix<DataType>::null_matrix(int m, int n)");
    }
    else
    {
        _deallocMemory();
        _allocMemory(nrOfRows, nrOfColumns);
        setItemsToZero();
    }
}

template <typename DataType>
void Matrix<DataType>::resize(int nrOfRows, int nrOfColumns)
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

    auto setZeroes = [](Matrix<DataType>& dest, int beginRowIndex, int endRowIndex, int beginColumnIndex, int endColumnIndex)
    {
        for (int row{beginRowIndex}; row<endRowIndex; ++row)
        {
            for (int col{beginColumnIndex}; col<endColumnIndex; ++col)
            {
                dest.m_pBaseArrayPtr[row][col] = 0;
            }
        }
    };

    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        _handleException(3, "template <typename DataType> void Matrix<DataType>::resize_m(int m, int n)");
    }
    else if (nrOfRows!=m_NrOfRows || nrOfColumns!=m_NrOfColumns)
    {
        DataType** temp;
        Matrix<DataType> matrix{};

        temp=matrix.m_pBaseArrayPtr;
        matrix.m_pBaseArrayPtr=m_pBaseArrayPtr;
        m_pBaseArrayPtr=temp;

        matrix.m_NrOfRows=m_NrOfRows;
        matrix.m_NrOfColumns=m_NrOfColumns;

        _deallocMemory();
        _allocMemory(nrOfRows,nrOfColumns);
        matrix.resetCurrentPos();

        if (nrOfRows<matrix.m_NrOfRows && nrOfColumns<matrix.m_NrOfColumns)
        {
            copyMatrix(*this, matrix, 0, nrOfRows, 0, nrOfColumns);
        }
        else if (nrOfRows<=matrix.m_NrOfRows && nrOfColumns>=matrix.m_NrOfColumns)
        {
            copyMatrix(*this, matrix, 0, nrOfRows, 0, matrix.m_NrOfColumns);
            setZeroes(*this, 0, nrOfRows, matrix.m_NrOfColumns, nrOfColumns);
        }
        else if ((nrOfRows>=matrix.m_NrOfRows) && (nrOfColumns<=matrix.m_NrOfColumns))
        {
            copyMatrix(*this, matrix, 0, matrix.m_NrOfRows, 0, nrOfColumns);
            setZeroes(*this, matrix.m_NrOfRows, nrOfRows, 0, nrOfColumns);
        }
        else
        {
            copyMatrix(*this, matrix, 0, matrix.m_NrOfRows, 0, matrix.m_NrOfColumns);
            setZeroes(*this, 0, nrOfRows, matrix.m_NrOfColumns, nrOfColumns);
            setZeroes(*this, matrix.m_NrOfRows, nrOfRows, 0, nrOfColumns);
            setZeroes(*this, matrix.m_NrOfRows, nrOfRows, matrix.m_NrOfColumns, nrOfColumns);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapItem(int rowNr, int columnNr, Matrix& matrix, int matrixRowNr, int matrixColumnNr)
{
    if (matrix.m_pBaseArrayPtr == m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    }
    else if ((rowNr<0) || (columnNr<0) || (matrixRowNr<0) || (matrixColumnNr<0))
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    }
    else if ((rowNr>=m_NrOfRows) || (columnNr>=m_NrOfColumns) || (matrixRowNr>=matrix.m_NrOfRows) || (matrixColumnNr>=matrix.m_NrOfColumns))
    {
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    }
    else
    {
        std::swap(m_pBaseArrayPtr[rowNr][columnNr], m_pBaseArrayPtr[matrixRowNr][matrixColumnNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRow(int rowNr, Matrix& matrix, int matrixRowNr)
{
    if (matrix.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    }
    else if ((rowNr<0) || (matrixRowNr<0))
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    }
    else if (rowNr>=m_NrOfRows || matrixRowNr>=matrix.m_NrOfRows)
    {
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    }
    else if (m_NrOfColumns!=matrix.m_NrOfColumns)
    {
        _handleException(13, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    }
    else
    {
        std::swap(m_pBaseArrayPtr[rowNr], matrix.m_pBaseArrayPtr[matrixRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumn(int columnNr, Matrix& matrix, int matrixColumnNr)
{
    if (matrix.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    }
    else if ((columnNr<0) || (matrixColumnNr<0))
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    }
    else if ((columnNr>=m_NrOfColumns) || (matrixColumnNr>=matrix.m_NrOfColumns))
    {
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    }
    else if (m_NrOfRows!=matrix.m_NrOfRows)
    {
        _handleException(12, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    }
    else
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
    if (rowNr<0 || matrixColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else if (m_NrOfColumns!=matrix.m_NrOfRows)
    {
        _handleException(11, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else if (rowNr>=m_NrOfRows)
    {
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else if (matrixColumnNr>=matrix.m_NrOfColumns)
    {
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else if (m_pBaseArrayPtr==matrix.m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[rowNr][col]};
            m_pBaseArrayPtr[rowNr][col] = matrix.m_pBaseArrayPtr[col][matrixColumnNr];
            matrix.m_pBaseArrayPtr[col][matrixColumnNr] = swap;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapItem(int firstRowNr, int firstColumnNr, int secondRowNr, int secondColumnNr)
{
    if (firstRowNr<0 || firstColumnNr<0 || secondRowNr<0 || secondColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    }
    else if (firstRowNr>=m_NrOfRows || firstColumnNr>=m_NrOfColumns || secondRowNr>=m_NrOfRows || secondColumnNr>=m_NrOfColumns)
    {
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    }
    else
    {
        std::swap(m_pBaseArrayPtr[firstRowNr][firstColumnNr], m_pBaseArrayPtr[secondRowNr][secondColumnNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRow(int firstRowNr, int secondRowNr)
{
    if (firstRowNr<0 || secondRowNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    }
    else if ((firstRowNr>=m_NrOfRows) || (secondRowNr>=m_NrOfRows))
    {
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    }
    else
    {
        std::swap(m_pBaseArrayPtr[firstRowNr], m_pBaseArrayPtr[secondRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumn(int firstColumnNr, int secondColumnNr)
{
    if (firstColumnNr<0 || secondColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    }
    else if (firstColumnNr>=m_NrOfColumns || secondColumnNr>=m_NrOfColumns)
    {
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    }
    else
    {
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[row][firstColumnNr]};
            m_pBaseArrayPtr[row][firstColumnNr] = m_pBaseArrayPtr[row][secondColumnNr];
            m_pBaseArrayPtr[row][secondColumnNr] = swap;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::swapRowColumn(int rowColumnNr)
{
    if (m_NrOfRows!=m_NrOfColumns)
    {
        _handleException(1,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    }
    else if (rowColumnNr<0)
    {
        _handleException(16,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    }
    else if (rowColumnNr>=m_NrOfRows)
    {
        _handleException(18,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    }
    else
    {
        for (int col{0}; col<m_NrOfRows; col++)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[rowColumnNr][col]};
            m_pBaseArrayPtr[rowColumnNr][col] = m_pBaseArrayPtr[col][rowColumnNr];
            m_pBaseArrayPtr[col][rowColumnNr] = swap;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::swapWithMatrix(Matrix<DataType> &matrix)
{
    std::swap(m_NrOfRows,matrix.m_NrOfRows);
    std::swap(m_NrOfColumns,matrix.m_NrOfColumns);
    std::swap(m_MatrixEntryMode, matrix.m_MatrixEntryMode);
    std::swap(m_MatrixPrintMode, matrix.m_MatrixPrintMode);
    std::swap(m_PosX, matrix.m_PosX);
    std::swap(m_PosY, matrix.m_PosY);
    std::swap(m_WrapMatrixByRow, matrix.m_WrapMatrixByRow);
    std::swap(m_pBaseArrayPtr, matrix.m_pBaseArrayPtr);
}

template <typename DataType>
void Matrix<DataType>:: sortLineColumn(int lineColumnNr, int mode)
{
    switch (mode) {
    case 0:
        if (lineColumnNr<0 || lineColumnNr>m_NrOfRows-1)
        {
            _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
        }
        _quickSort(0, m_NrOfColumns-1, 0, lineColumnNr);
        break;
    case 1:
        if (lineColumnNr<0 || lineColumnNr>m_NrOfRows-1)
        {
            _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
        }
        _quickSort(0, m_NrOfColumns-1, 1, lineColumnNr);
        break;
    case 2:
        if (lineColumnNr<0 || lineColumnNr>m_NrOfColumns-1)
        {
            _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
        }
        _quickSort(0, m_NrOfRows-1, 2, lineColumnNr);
        break;
    case 3:
        if (lineColumnNr<0 || lineColumnNr>m_NrOfColumns-1)
        {
            _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
        }
        _quickSort(0, m_NrOfRows-1, 3, lineColumnNr);
        break;
    default:
        _handleException(21, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
    }
}

template <typename DataType>
void Matrix<DataType>::sortAllElements(int mode)
{
    switch (mode) {
    case 0:
        _quickSort(0, m_NrOfRows*m_NrOfColumns-1, 0);
        break;
    case 1:
        _quickSort(0, m_NrOfRows*m_NrOfColumns-1, 1);
        break;
    case 2:
        _quickSort(0, m_NrOfRows*m_NrOfColumns-1, 2);
        break;
    case 3:
        _quickSort(0, m_NrOfRows*m_NrOfColumns-1, 3);
    default:
        _handleException(21, "template <typename DataType> void Matrix<DataType>::sort_matr(int mode)");
    }
}

template <typename DataType>
void Matrix<DataType>::insertRow (int rowNr)
{
    if (rowNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
    }

    if (rowNr>m_NrOfRows)
    {
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
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
void Matrix<DataType>::deleteRow (int rowNr)
{
    if (m_NrOfRows==1)
    {
        _handleException(15, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    }

    if (rowNr>=m_NrOfRows)
    {
        _handleException(4, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    }

    if (rowNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
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
void Matrix<DataType>::insertColumn(int columnNr)
{
    if (columnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
    }

    if (columnNr>m_NrOfColumns)
    {
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
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
void Matrix<DataType>::deleteColumn(int columnNr)
{
    if (m_NrOfColumns==1)
    {
        _handleException(14, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    }

    if (columnNr<0)
    {
        _handleException (16, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    }

    if (columnNr>=m_NrOfColumns)
    {
        _handleException (7, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
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

template<typename DataType>
void Matrix<DataType>::addRowToColumn(int rowNr, const DataType& coeff, Matrix& src, int srcColumnNr, const DataType& srcCoeff, Matrix& dest,int destColumnNr)
{
    if (rowNr<0 || srcColumnNr<0 || destColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (rowNr>=m_NrOfRows)
    {
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (srcColumnNr>=src.m_NrOfColumns)
    {
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (dest.m_WrapMatrixByRow)
    {
        if (destColumnNr>=dest.m_NrOfRows)
        {
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destColumnNr][row] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
    else
    {
        if (destColumnNr>=dest.m_NrOfColumns)
        {
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destColumnNr] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToRow(int columnNr, const DataType& coeff, Matrix& src, int srcRowNr, const DataType& srcCoeff, Matrix& dest, int destRowNr)
{
    if (columnNr<0 || srcRowNr<0 || destRowNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (columnNr>=m_NrOfColumns)
    {
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (srcRowNr>=src.m_NrOfRows)
    {
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (dest.m_WrapMatrixByRow)
    {
        if (destRowNr>=dest.m_NrOfRows)
        {
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowNr][row] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
    else
    {
        if (destRowNr>=dest.m_NrOfColumns)
        {
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowNr] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addRowToRow(int rowNr, const DataType& coeff, Matrix &src, int srcRowNr, const DataType& srcCoeff, Matrix& dest, int destRowNr)
{
    if (rowNr<0 || srcRowNr<0 || destRowNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if ((rowNr>=m_NrOfRows) || (srcRowNr>=src.m_NrOfRows))
    {
        _handleException(6, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (dest.m_WrapMatrixByRow)
    {
        if (destRowNr>=dest.m_NrOfRows)
        {
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destRowNr][row] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
    else {
        if (destRowNr>=dest.m_NrOfColumns)
        {
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destRowNr] = coeff * m_pBaseArrayPtr[rowNr][row] + srcCoeff * src.m_pBaseArrayPtr[srcRowNr][row];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToColumn(int columnNr, const DataType& coeff, Matrix& src, int srcColumnNr, const DataType& srcCoeff, Matrix& dest, int destColumnNr)
{
    if (columnNr<0 || srcColumnNr<0 || destColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if ((columnNr>=m_NrOfColumns) || (srcColumnNr>=src.m_NrOfColumns))
    {
        _handleException(9, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    }

    if (dest.m_WrapMatrixByRow)
    {
        if (destColumnNr>=dest.m_NrOfRows)
        {
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[destColumnNr][row] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
    else
    {
        if (destColumnNr>=dest.m_NrOfColumns)
        {
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pBaseArrayPtr[row][destColumnNr] = coeff * m_pBaseArrayPtr[row][columnNr] + srcCoeff * src.m_pBaseArrayPtr[row][srcColumnNr];
        }
    }
}

template <typename DataType>
void Matrix<DataType>:: copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns)
{
    if (src.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    }

    if (nrOfRows<0 || nrOfColumns<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    }

    if ((src.m_PosX+nrOfRows>src.m_NrOfRows) || (src.m_PosY+nrOfColumns>src.m_NrOfColumns) || (m_PosX+nrOfRows>m_NrOfRows) || (m_PosY+nrOfColumns>m_NrOfColumns))
    {
        _handleException(18, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    }

    for (int row{0}; row<nrOfRows; ++row)
    {
        for (int col{0}; col<nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[m_PosX+row][m_PosY+col] = src.m_pBaseArrayPtr[src.m_PosX+row][src.m_PosY+col];
        }
    }
}

template <typename DataType>
void Matrix<DataType>::copy(DataType** src, int nrOfRows, int nrOfColumns)
{
    if (src==nullptr)
    {
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    }

    if ((nrOfRows<=0)||(nrOfColumns<=0))
    {
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    }

    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = src[row][col];
        }
    }
}

template <typename DataType>
void Matrix<DataType>::copy(DataType* src, int nrOfRows, int nrOfColumns)
{
    if (src==nullptr)
    {
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    }

    if ((nrOfRows<=0)||(nrOfColumns<=0))
    {
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    }

    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = *(src++);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    if (m_WrapMatrixByRow && (firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns))
    {
        _handleException(13,"template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
    }

    if ((!m_WrapMatrixByRow) && (firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows))
    {
        _handleException(12, "template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
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
        _concatenate(thirdMatrix, secondSrcMatrix);
    }
    else if ((firstSrcMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr) && (secondSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
    {
        _concatenate(firstSrcMatrix, thirdMatrix);
    }
    else if ((firstSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) && (secondSrcMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
    {
        _concatenate(thirdMatrix, thirdMatrix);
    }
    else
    {
        _concatenate(firstSrcMatrix, secondSrcMatrix);
    }
}

template <typename DataType>
void Matrix<DataType>::split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix,int splitRowColumnNr)
{
    if (firstDestMatrix.m_pBaseArrayPtr==secondDestMatrix.m_pBaseArrayPtr)
    {
        _handleException(24, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }

    if (splitRowColumnNr<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }

    if (m_WrapMatrixByRow)
    {
        if (splitRowColumnNr>m_NrOfRows)
        {
            _handleException(4, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        }
        if ((splitRowColumnNr == 0) || (splitRowColumnNr == m_NrOfRows))
        {
            _handleException(19, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        }
    }
    else {
        if (splitRowColumnNr>m_NrOfColumns)
        {
            _handleException(7, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        }
        if ((splitRowColumnNr == 0) || (splitRowColumnNr == m_NrOfColumns))
        {
            _handleException(20, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        }
    }

    Matrix<DataType> thirdMatrix{};

    if ((firstDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) || (secondDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr)) {
        thirdMatrix.m_pBaseArrayPtr = m_pBaseArrayPtr;
        thirdMatrix.m_NrOfRows = m_NrOfRows;
        thirdMatrix.m_NrOfColumns = m_NrOfColumns;
        thirdMatrix.m_WrapMatrixByRow = m_WrapMatrixByRow;

        _allocMemory(1,1);
    }

    if ((firstDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr) && (secondDestMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr))
    {
        thirdMatrix._split(*this, secondDestMatrix, splitRowColumnNr);
    }
    else if ((firstDestMatrix.m_pBaseArrayPtr != m_pBaseArrayPtr) && (secondDestMatrix.m_pBaseArrayPtr == m_pBaseArrayPtr))
    {
        thirdMatrix._split(firstDestMatrix, *this, splitRowColumnNr);
    }
    else
    {
        _split(firstDestMatrix, secondDestMatrix, splitRowColumnNr);
    }
}

template <typename DataType>
void Matrix<DataType>::applyCoefficientsToRow (const Matrix &coeff, Matrix &src, bool multiply)
{
    if (m_pBaseArrayPtr==coeff.m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    }

    if (coeff.m_NrOfRows!=src.m_NrOfRows)
    {
        _handleException(12,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    }

    if (m_NrOfRows != src.m_NrOfRows || m_NrOfColumns != src.m_NrOfColumns)
    {
        resizeNoInit(src.m_NrOfRows, src.m_NrOfColumns);
    }

    if (multiply)
    {
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = src.m_pBaseArrayPtr[row][col] * coeff.m_pBaseArrayPtr[row][0];
            }
        }
    }
    else
    {
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            if (coeff.m_pBaseArrayPtr[row][0]==0)
            {
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
            }
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = src.m_pBaseArrayPtr[row][col] / coeff.m_pBaseArrayPtr[row][0];
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::applyCoefficientsToColumn (const Matrix &coeff, Matrix &src, bool multiply)
{
    if (coeff.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    }

    if (coeff.m_NrOfColumns!=src.m_NrOfColumns)
    {
        _handleException(13,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    }

    if (m_NrOfRows != src.m_NrOfRows || m_NrOfColumns != src.m_NrOfColumns)
    {
        resizeNoInit(src.m_NrOfRows, src.m_NrOfColumns);
    }

    if (multiply)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                m_pBaseArrayPtr[row][col] = src.m_pBaseArrayPtr[row][col] * coeff.m_pBaseArrayPtr[0][col];
            }
        }
    }
    else {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            if (coeff.m_pBaseArrayPtr[0][col]==0)
            {
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
            }
        }

        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            for (int i{0}; i<m_NrOfRows; ++i)
            {
                m_pBaseArrayPtr[i][col] = src.m_pBaseArrayPtr[i][col] / coeff.m_pBaseArrayPtr[0][col];
            }
        }
    }
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator+ (const Matrix<DataType>& matrix)
{
    if (m_NrOfRows != matrix.m_NrOfRows || m_NrOfColumns != matrix.m_NrOfColumns)
    {
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator+ (const Matrix<DataType> &m)");
    }

    Matrix<DataType> result{};
    result.resizeNoInit(m_NrOfRows, m_NrOfColumns);

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
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator- (const Matrix<DataType> &m)");
    }

    Matrix<DataType> result{};
    result.resizeNoInit(m_NrOfRows, m_NrOfColumns);

    for (int i{0}; i<m_NrOfRows; ++i)
    {
        for (int j{0}; j<m_NrOfColumns; ++j)
        {
            result.m_pBaseArrayPtr[i][j] = m_pBaseArrayPtr[i][j] - matrix.m_pBaseArrayPtr[i][j];
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
Matrix<DataType> Matrix<DataType>::operator* (const Matrix<DataType>& matrix)
{
    if (m_NrOfColumns!=matrix.m_NrOfRows)
    {
        _handleException(11, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator* (const Matrix<DataType> &m)");
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

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator^ (int exp)
{
    if (m_NrOfRows!=m_NrOfColumns)
    {
        _handleException(1, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    }

    if (exp<0)
    {
        _handleException(16, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    }

    Matrix<DataType> result{};

    if (exp==0)
    {
        result.transformToUnitMatrix(m_NrOfRows);
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

    m_PosX = matrix.m_PosX;
    m_PosY = matrix.m_PosY;
    m_WrapMatrixByRow = matrix.m_WrapMatrixByRow;

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
bool Matrix<DataType>::operator !=(const Matrix<DataType>& matrix) const
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
bool Matrix<DataType>::operator <(const Matrix<DataType> &matrix) const
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
bool Matrix<DataType>::operator <=(const Matrix<DataType> &matrix) const
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
bool Matrix<DataType>::operator >(const Matrix<DataType> &matrix) const
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
bool Matrix<DataType>::operator >=(const Matrix<DataType> &matrix) const
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
std::ostream& operator<<(std::ostream &out, const Matrix<DataType> &matrix)
{
    if((matrix.m_MatrixPrintMode==4 || matrix.m_MatrixPrintMode==5) && (matrix.m_NrOfRows!=matrix.m_NrOfColumns))
    {
        Matrix<DataType>::_handleException(1, "friend ostream &operator<<(ostream &os, Matrix &m)");
    }

    matrix._writeMatrix(out, matrix.m_MatrixPrintMode);

    return out;
}

template<typename DataType>
std::istream& operator>>(std::istream &in, Matrix<DataType> &matrix)
{
    if((matrix.m_MatrixEntryMode==4   ||
        matrix.m_MatrixEntryMode==5   ||
        matrix.m_MatrixEntryMode==10  ||
        matrix.m_MatrixEntryMode==11  ||
        matrix.m_MatrixEntryMode==16  ||
        matrix.m_MatrixEntryMode==17) &&
       (matrix.m_NrOfRows!=matrix.m_NrOfColumns))
    {
        Matrix<DataType>::_handleException(1, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    matrix._readMatrix(in, matrix.m_MatrixEntryMode);

    return in;
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](int index)
{
    if (index<0)
    {
        _handleException(16, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
    }

    if (index>=m_NrOfRows*m_NrOfColumns)
    {
        _handleException(18, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
    }

    return m_WrapMatrixByRow ? _getItemForLineWrap(index) : _getItemForColumnWrap(index);
}

template <typename DataType>
DataType Matrix<DataType>::determinant()
{
    if (m_NrOfRows!=m_NrOfColumns)
    {
        _handleException(1, "template <typename DataType> DataType Matrix<DataType>::det()");
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
int Matrix<DataType>::rank()
{
    auto continueCalculation = [](Matrix& matrix)
    {
        for (int row{matrix.m_PosX+1}; row<matrix.m_NrOfRows; ++row)
        {
            for (int col{matrix.m_PosY+1}; col<matrix.m_NrOfColumns; ++col)
            {
                matrix.m_pBaseArrayPtr[row][col]=(matrix.m_pBaseArrayPtr[row][col]) * (matrix.m_pBaseArrayPtr[matrix.m_PosX][matrix.m_PosY]) -
                                           (matrix.m_pBaseArrayPtr[matrix.m_PosX][col]) * (matrix.m_pBaseArrayPtr[row][matrix.m_PosY]);
            }
        }

        ++matrix.m_PosX;
        ++matrix.m_PosY;
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

    matrix.m_PosX=0;
    matrix.m_PosY=0;

    int matrixRank{0};

    while (matrix.m_PosX < matrix.m_NrOfRows-1)
    {
        if (matrix.m_pBaseArrayPtr[matrix.m_PosX][matrix.m_PosY]==0)
        {
            for (int row{matrix.m_PosX+1}; row<matrix.m_NrOfRows; ++row)
            {
                if (matrix.m_pBaseArrayPtr[row][matrix.m_PosY]!=0)
                {
                    ++matrixRank;
                    matrix.swapRow(row,matrix.m_PosX);
                    continueCalculation(matrix);
                }
            }

            for (int col{matrix.m_PosY+1}; col<matrix.m_NrOfColumns; ++col)
            {
                if (matrix.m_pBaseArrayPtr[matrix.m_PosX][col]!=0)
                {
                    ++matrixRank;
                    matrix.swapColumn(col,matrix.m_PosY);
                    continueCalculation(matrix);
                }
            }
        }
        else
        {
            ++matrixRank;
        }
    }

    for (int col{matrix.m_PosY}; col<matrix.m_NrOfColumns; ++col)
    {
        if (matrix.m_pBaseArrayPtr[matrix.m_PosX][col]!=0)
        {
            ++matrixRank;
            break;
        }
    }

    return matrixRank;
}

template<typename DataType>
void Matrix<DataType>::getInverseMatrix(Matrix<DataType>& coeff, Matrix<DataType>& pseudoInverse)
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
        _handleException(25, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    }

    if (m_NrOfRows!=m_NrOfColumns)
    {
        _handleException(1, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    }

    matrix = *this;
    pseudoInverse.transformToUnitMatrix(m_NrOfRows);
    coeff.resizeNoInit(m_NrOfRows,1);

    for (int diag{0}; diag<m_NrOfRows-1; ++diag)
    {
        bool rowSwapped{false};

        if (matrix.m_pBaseArrayPtr[diag][diag]==0)
        {
            for (int col{diag+1}; col<m_NrOfRows; ++col)
            {
                if (matrix.m_pBaseArrayPtr[diag][col]!=0)
                {
                    matrix.swapRow(diag,col);
                    pseudoInverse.swapRow(diag,col);
                    continueCalculation(pseudoInverse, matrix, diag, m_NrOfRows);
                    rowSwapped = true;
                }
            }

            if (rowSwapped)
            {
                continue;
            }

            _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
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
        _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
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

        resizeNoInit(m_NrOfColumns, m_NrOfRows);

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
        result.resizeNoInit(m_NrOfColumns,m_NrOfRows);

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
void Matrix<DataType>::sums(Matrix& result, int mode)
{
    if (result.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    if (mode>4)
    {
        _handleException(21, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    if (mode<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    switch (mode)
    {
    case 0:
    {
        DataType allItemsSum{0};
        result.resizeNoInit(1,1);
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
    case 1:
    {
        DataType currentRowItemsSum{0};
        result.resizeNoInit(1,1);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            currentRowItemsSum *= m_pBaseArrayPtr[m_PosX][col];
        }
        result.m_pBaseArrayPtr[0][0] = currentRowItemsSum;
        break;
    }
    case 2:
    {
        result.resizeNoInit(m_NrOfRows,1);
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
    case 3:
    {
        DataType currentColumnItemsSum{0};
        result.resizeNoInit(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            currentColumnItemsSum *= m_pBaseArrayPtr[row][m_PosY];
        }
        result.m_pBaseArrayPtr[0][0] = currentColumnItemsSum;
        break;
    }
    case 4:
        result.resizeNoInit(1, m_NrOfColumns);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            DataType eachColumnItemsSum{0};
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                eachColumnItemsSum *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[0][col] = eachColumnItemsSum;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::products(Matrix& result, int mode)
{
    if (result.m_pBaseArrayPtr==m_pBaseArrayPtr)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    if (mode>4)
    {
        _handleException(21, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    if (mode<0)
    {
        _handleException(16, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    }

    switch (mode)
    {
    case 0:
    {
        DataType allItemsProduct{1};
        result.resizeNoInit(1,1);
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
    case 1:
    {
        DataType currentRowItemsProduct{1};
        result.resizeNoInit(1,1);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            currentRowItemsProduct *= m_pBaseArrayPtr[m_PosX][col];
        }
        result.m_pBaseArrayPtr[0][0] = currentRowItemsProduct;
        break;
    }
    case 2:
    {
        result.resizeNoInit(m_NrOfRows,1);
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
    case 3:
    {
        DataType currentColumnItemsProduct{1};
        result.resizeNoInit(1,1);
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            currentColumnItemsProduct *= m_pBaseArrayPtr[row][m_PosY];
        }
        result.m_pBaseArrayPtr[0][0] = currentColumnItemsProduct;
        break;
    }
    case 4:
        result.resizeNoInit(1, m_NrOfColumns);
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            DataType eachColumnItemsProduct{1};
            for (int row{0}; row<m_NrOfRows; ++row)
            {
                eachColumnItemsProduct *= m_pBaseArrayPtr[row][col];
            }
            result.m_pBaseArrayPtr[0][col] = eachColumnItemsProduct;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::getNegativeMatrix(Matrix<DataType>& result)
{
    if (this != &result)
    {
        result.resizeNoInit(m_NrOfRows,m_NrOfColumns);
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            result.m_pBaseArrayPtr[row][col] = (-1) * m_pBaseArrayPtr[row][col];
        }
    }
}

template <typename DataType>
void Matrix<DataType>::getInverseElementsMatrix(Matrix<DataType>& result)
{
    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            if (m_pBaseArrayPtr[row][col]==0)
            {
                _handleException(23,"template <typename DataType> void Matrix<DataType>::inv_matrix(Matrix<DataType> &m)");
            }
        }
    }

    if (this != &result)
    {
        result.resizeNoInit(m_NrOfRows,m_NrOfColumns);
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            result.m_pBaseArrayPtr[row][col]= 1 / m_pBaseArrayPtr[row][col];
        }
    }
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

    // this reset is required as the position indicators might get out of bound; no conditional reset as we need to have a consistent behavior
    resetCurrentPos();
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

    resetCurrentPos();
}

template <typename DataType>
void Matrix<DataType>::_writeMatrix(std::ostream& os, int mode)
{
    using namespace std;

    switch (mode)
    {
    case 0:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                os<<m_pBaseArrayPtr[row][col]<<" ";
            }
            os<<endl;
        }
        break;
    case 1:
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            os<<m_pBaseArrayPtr[m_PosX][col]<<" ";
        }
        break;
    case 2:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            os<<m_pBaseArrayPtr[row][m_PosY]<<endl;
        }
        break;
    case 3:
        os<<m_pBaseArrayPtr[m_PosX][m_PosY];
        break;
    case 4:
        for (int diag{0}; diag<m_NrOfRows; ++diag)
        {
            os<<m_pBaseArrayPtr[diag][diag]<<" ";
        }
        break;
    case 5:
        for (int diag{m_NrOfRows-1}; diag>=0; --diag)
        {
            os<<m_pBaseArrayPtr[diag][m_NrOfRows-1-diag]<<" ";
        }
    }
}

template <typename DataType>
void Matrix<DataType>::_readMatrix(std::istream &in, int mode)
{
    using namespace std;

    string str;
    stringstream stream(ios::in | ios::out);

    switch (mode)
    {
    case 0:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                if (in.eof())
                {
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                }
                cout<<"["<<row<<"]["<<col<<"]= ";
                in>>m_pBaseArrayPtr[row][col];
            }
        }
        break;
    case 1:
        cout<<"["<<m_PosX<<"]["<<m_PosY<<"]= ";
        in>>m_pBaseArrayPtr[m_PosX][m_PosY];
        break;
    case 2:
        for (int col{0}; col<m_NrOfColumns; ++col) {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            cout<<"["<<m_PosX<<"]["<<col<<"]= ";
            in>>m_pBaseArrayPtr[m_PosX][col];
        }
        break;
    case 3:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            cout<<"["<<row<<"]["<<m_PosY<<"]= ";
            in>>m_pBaseArrayPtr[row][m_PosY];
        }
        break;
    case 4:
        for(int diag{0}; diag<m_NrOfRows; ++diag){
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            cout<<"["<<diag<<"]["<<diag<<"]= ";
            in>>m_pBaseArrayPtr[diag][diag];
        }
        break;
    case 5:
        for(int diag{m_NrOfRows-1}; diag>=0; --diag) {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            cout<<"["<<diag<<"]["<<m_NrOfRows-1-diag<<"]= ";
            in>>m_pBaseArrayPtr[diag][m_NrOfRows-1-diag];
        }
        break;
    case 6:
        _readDiscard(in);
        m_PosX = 0;
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            _readTextLine(in);
            ++m_PosX;
            ++s_FilePosX;
        }
        break;
    case 7:
        _readDiscard(in);
        _readSingleItem(in);
        break;
    case 8:
        _readDiscard(in);
        _readTextLine(in);
        break;
    case 9:
        _readDiscard(in);
        m_PosX = 0;
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            _readSingleItem(in);
            ++m_PosX;
            ++s_FilePosX;
        }
        break;
    case 10:
        _readDiscard(in);
        resetCurrentPos();
        s_FilePosY=0;
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            _readSingleItem(in);
            s_FilePosX++;
            m_PosY = ++m_PosX;
            s_FilePosY++;
        }
        break;
    case 11:
        _readDiscard(in);
        s_FilePosY = m_NrOfRows-1;
        m_PosX = 0;
        m_PosY = m_NrOfRows-1;
        for(int row{0}; row<m_NrOfRows; ++row)
        {
            _readSingleItem(in);
            ++s_FilePosX;
            --s_FilePosY;
            ++m_PosX;
            --m_PosY;
        }
        break;
    case 12:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                if (in.eof())
                {
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                }
                in>>m_pBaseArrayPtr[row][col];
            }
        }
        break;
    case 13:
        if (in.eof())
        {
            _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
        }
        in>>m_pBaseArrayPtr[m_PosX][m_PosY];
        break;
    case 14:
        for (int col{0}; col<m_NrOfColumns; ++col) {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            in>>m_pBaseArrayPtr[m_PosX][col];
        }
        break;
    case 15:
        for (int row{0}; row<m_NrOfRows; ++row) {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            in>>m_pBaseArrayPtr[row][m_PosY];
        }
        break;
    case 16:
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            in>>m_pBaseArrayPtr[row][row];
        }
        break;
    case 17:
        for (int row{m_NrOfRows-1}; row>=0; --row)
        {
            if (in.eof())
            {
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            }
            in>>m_pBaseArrayPtr[row][m_NrOfRows-1-row];
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_readTextLine(std::istream &in)
{
    std::string str;
    std::stringstream stream;

    if (in.eof())
    {
        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    getline(in,str);

    int strSize=str.size();
    if (strSize==0)
    {
        _handleException (28, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    unsigned int strIndex{0};
    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        while(str[strIndex]==' ' && strIndex<strSize)
        {
            ++strIndex;
        }

        if (strIndex==strSize)
        {
            _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
        }

        do
        {
            stream.put(str[strIndex++]);
        }
        while(str[strIndex]!=' ' && strIndex<strSize);

        stream>>m_pBaseArrayPtr[m_PosX][col];
        stream.str("");
        stream.clear();
    }
}

template<typename DataType>
void Matrix<DataType>::_readSingleItem(std::istream &in)
{
    std::string str;
    std::stringstream stream;

    if (in.eof())
    {
        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    getline(in,str);

    int strSize = str.size();
    if (strSize==0)
    {
        _handleException (28, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    unsigned int strIndex{0};
    for (int col{0}; col<s_FilePosY; ++col)
    {
        while (str[strIndex]==' ' && strIndex<strSize)
        {
           ++strIndex;
        }

        if (strIndex==strSize)
        {
            _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
        }

        do
        {
            ++strIndex;
        }
        while(str[strIndex]!=' ' && strIndex<strSize);
    }

    if (strIndex==strSize)
    {
        _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    while(str[strIndex]==' ' && strIndex<strSize)
    {
        ++strIndex;
    }

    if (strIndex==strSize)
    {
        _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
    }

    do
    {
        stream.put(str[strIndex++]);
    }
    while(str[strIndex]!=' ' && strIndex<strSize);

    stream>>m_pBaseArrayPtr[m_PosX][m_PosY];
    stream.str("");
    stream.clear();
}

template<typename DataType>
void Matrix<DataType>::_readDiscard(std::istream &in)
{
    std::string str;

    in.clear();
    in.seekg(0);

    for (int row{0}; row<s_FilePosX; ++row)
    {
        if (in.eof())
        {
            _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
        }

        getline(in,str);
        str="";
        str.clear();
    }
}

template<typename DataType>
void Matrix<DataType>::_quickSort(int firstIndex, int lastIndex, int mode, int rowColumnNr)
{
    if (lastIndex>firstIndex)
    {
        int pivot{(firstIndex+lastIndex)/2};
        int splittingIndex{_createSortingPartition(firstIndex, lastIndex, pivot, mode, rowColumnNr)};

        _quickSort(firstIndex, splittingIndex-1, mode, rowColumnNr);
        _quickSort(splittingIndex+1, lastIndex, mode, rowColumnNr);
    }
}

template<typename DataType>
void Matrix<DataType>::_quickSort(int firstIndex, int lastIndex, int mode)
{
    if (lastIndex>firstIndex)
    {
        int pivot{(firstIndex+lastIndex)/2};
        int splittingIndex{_createSortingPartition(firstIndex, lastIndex, pivot, mode)};

        _quickSort(firstIndex, splittingIndex-1, mode);
        _quickSort(splittingIndex+1, lastIndex, mode);
    }
}

template<typename DataType>
int Matrix<DataType>:: _createSortingPartition(int firstIndex, int lastIndex, int pivot, int mode, int rowColumnNr)
{
    int leftIndex{firstIndex-1};
    int rightIndex{lastIndex};

    switch(mode)
    {
    case 0:
        if (pivot!=lastIndex)
        {
            swapItem(rowColumnNr, pivot, rowColumnNr, lastIndex);
        }

        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rowColumnNr][leftIndex] < m_pBaseArrayPtr[rowColumnNr][lastIndex]));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rowColumnNr][rightIndex] > m_pBaseArrayPtr[rowColumnNr][lastIndex]));

            if (leftIndex<rightIndex)
            {
                swapItem(rowColumnNr, leftIndex, rowColumnNr, rightIndex);
            }
        }

        if (leftIndex!=lastIndex)
        {
            swapItem(rowColumnNr, leftIndex, rowColumnNr, lastIndex);
        }
    case 1:
        if (pivot!=lastIndex)
        {
            swapItem(rowColumnNr, pivot, rowColumnNr, lastIndex);
        }

        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rowColumnNr][leftIndex] > m_pBaseArrayPtr[rowColumnNr][lastIndex]));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rowColumnNr][rightIndex] < m_pBaseArrayPtr[rowColumnNr][lastIndex]));

            if (leftIndex<rightIndex)
            {
                swapItem(rowColumnNr, leftIndex, rowColumnNr, rightIndex);
            }
        }

        if (leftIndex!=lastIndex)
        {
            swapItem(rowColumnNr, leftIndex, rowColumnNr, lastIndex);
        }
    case 2:
        if (pivot!=lastIndex)
        {
            swapItem(pivot, rowColumnNr, lastIndex, rowColumnNr);
        }

        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[leftIndex][rowColumnNr] < m_pBaseArrayPtr[lastIndex][rowColumnNr]));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rightIndex][rowColumnNr] > m_pBaseArrayPtr[lastIndex][rowColumnNr]));

            if (leftIndex<rightIndex)
            {
                swapItem(leftIndex, rowColumnNr, rightIndex, rowColumnNr);
            }
        }

        if (leftIndex!=lastIndex)
        {
            swapItem(leftIndex, rowColumnNr, lastIndex, rowColumnNr);
        }
    case 3:
        if (pivot!=lastIndex)
        {
            swapItem(pivot, rowColumnNr, lastIndex, rowColumnNr);
        }

        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[leftIndex][rowColumnNr] > m_pBaseArrayPtr[lastIndex][rowColumnNr]));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (m_pBaseArrayPtr[rightIndex][rowColumnNr] < m_pBaseArrayPtr[lastIndex][rowColumnNr]));

            if (leftIndex<rightIndex)
            {
                swapItem(leftIndex, rowColumnNr, rightIndex, rowColumnNr);
            }
        }

        if (leftIndex!=lastIndex)
        {
            swapItem(leftIndex, rowColumnNr, lastIndex, rowColumnNr);
        }
    }

    return leftIndex;
}

template<typename DataType>
int Matrix<DataType>:: _createSortingPartition(int firstIndex,int lastIndex,int pivot,int mode)
{
    int leftIndex{firstIndex-1};
    int rightIndex{lastIndex};

    switch(mode)
    {
    case 0:
        if (pivot!=lastIndex)
        {
            std::swap(_getItemForLineWrap(pivot), _getItemForLineWrap(lastIndex));
        }

        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForLineWrap(leftIndex) < _getItemForLineWrap(lastIndex)));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForLineWrap(rightIndex) > _getItemForLineWrap(lastIndex)));

            if (leftIndex<rightIndex)
            {
                std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(rightIndex));
            }
        }

        if (leftIndex!=(lastIndex))
        {
            std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(lastIndex));
        }
    case 1:
        if (pivot!=lastIndex)
        {
            std::swap(_getItemForLineWrap(pivot), _getItemForLineWrap(lastIndex));
        }
        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForLineWrap(leftIndex) > _getItemForLineWrap(lastIndex)));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForLineWrap(rightIndex) < _getItemForLineWrap(lastIndex)));

            if (leftIndex<rightIndex)
            {
                std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(rightIndex));
            }
        }
        if (leftIndex!=(lastIndex))
        {
            std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(lastIndex));
        }
    case 2:
        if (pivot!=lastIndex)
        {
            std::swap(_getItemForLineWrap(pivot), _getItemForLineWrap(lastIndex));
        }
        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForColumnWrap(leftIndex) < _getItemForColumnWrap(lastIndex)));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForColumnWrap(rightIndex) > _getItemForColumnWrap(lastIndex)));

            if (leftIndex<rightIndex)
            {
                std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(rightIndex));
            }
        }

        if (leftIndex!=lastIndex)
        {
            std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(lastIndex));
        }
    case 3:
        if (pivot!=lastIndex)
        {
            std::swap(_getItemForLineWrap(pivot), _getItemForLineWrap(lastIndex));
        }
        while (leftIndex<rightIndex)
        {
            do
            {
                ++leftIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForColumnWrap(leftIndex) > _getItemForColumnWrap(lastIndex)));

            do
            {
                --rightIndex;
            }
            while ((leftIndex!=rightIndex) && (_getItemForColumnWrap(rightIndex) < _getItemForColumnWrap(lastIndex)));

            if (leftIndex<rightIndex)
            {
                std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(rightIndex));
            }
        }

        if (leftIndex!=lastIndex)
        {
            std::swap(_getItemForLineWrap(leftIndex), _getItemForLineWrap(lastIndex));
        }
    }

    return leftIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::_getItemForLineWrap(int oneDimensionalIndex)
{
    return m_pBaseArrayPtr[oneDimensionalIndex/m_NrOfColumns][oneDimensionalIndex%m_NrOfColumns];
}

template<typename DataType>
DataType& Matrix<DataType>::_getItemForColumnWrap(int oneDimensionalIndex)
{
    return m_pBaseArrayPtr[oneDimensionalIndex%m_NrOfRows][oneDimensionalIndex/m_NrOfRows];
}

template<typename DataType>
void Matrix<DataType>::_handleException(int errorType, char* function)
{
    using namespace std;
    try {
        cerr<<"Exception in function: "<<function<<endl;
        throw errorType;
    }
    catch (int k) {
        switch (k) {
        case 0:
            cerr<<"Not enough elements to initialize the matrix"<<endl;
            break;
        case 1:
            cerr<<"The dimensions of the matrix are not equal."<<endl;
            break;
        case 2:
            cerr<<"The matrix determinant is null. The inverse cannot be calculated."<<endl;
            break;
        case 3:
            cerr<<"At least one null or negative matrix dimension has been entered."<<endl;
            break;
        case 4:
            cerr<<"A referenced source matrix row does not exist"<<endl;
            break;
        case 5:
            cerr<<"A referenced destination matrix row does not exist"<<endl;
            break;
        case 6:
            cerr<<"For one or more matrixes at least one referenced row does not exist"<<endl;
            break;
        case 7:
            cerr<<"A referenced column of the source matrix does not exist"<<endl;
            break;
        case 8:
            cerr<<"A referenced column of the destination matrix does not exist"<<endl;
            break;
        case 9:
            cerr<<"For one or more matrixes at least one referenced column does not exist"<<endl;
            break;
        case 10:
            cerr<<"The two matrixes have different dimensions"<<endl;
            break;
        case 11:
            cerr<<"The number of columns of the first matrix is different from the number of lines of the second one"<<endl;
            break;
        case 12:
            cerr<<"The columns of the two matrixes have different lengths. The number of lines is different."<<endl;
            break;
        case 13:
            cerr<<"The rows of the two matrixes have different lengths. The number of columns is different."<<endl;
            break;
        case 14:
            cerr<<"Attempt to erase the only column of the matrix. This is not allowed."<<endl;
            break;
        case 15:
            cerr<<"Attempt to erase the only row of the matrix. This is not allowed."<<endl;
            break;
        case 16:
            cerr<<"The function received a negative argument. A non-negative arg is expected."<<endl;
            break;
        case 17:
            cerr<<"Attempt to insert a line or a column on a non-contiguous position"<<endl;
            break;
        case 18:
            cerr<<"Attempt to reference a matrix element with invalid index"<<endl;
            break;
        case 19:
            cerr<<"The resulting matrix has 0 rows"<<endl;
            break;
        case 20:
            cerr<<"The resulting matrix has 0 columns"<<endl;
            break;
        case 21:
            cerr<<"Invalid numeric argument"<<endl;
            break;
        case 22:
            cerr<<"Null pointer"<<endl;
            break;
        case 23:
            cerr<<"Attempt to divide by 0"<<endl;
            break;
        case 24:
            cerr<<"Same variable passed into two function arguments. This is not allowed."<<endl;
            break;
        case 25:
            cerr<<"Current matrix (this) has been passed as argument into the function. This is not allowed for this method."<<endl;
            break;
        case 26:
            cerr<<"End of file. Operation aborted."<<endl;
            break;
        case 27:
            cerr<<"The row read from the file contains less items than the current matrix row"<<endl;
            break;
        case 28:
            cerr<<"The current row of the text file is empty"<<endl;
            break;
        default:
            cout<<"Unknown exception"<<endl;
        }
        exit(1);
    }
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
    matrix.resizeNoInit(m_NrOfRows, m_NrOfColumns);

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
void Matrix<DataType>::_split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr)
{
    firstDestMatrix._deallocMemory();
    secondDestMatrix._deallocMemory();

    if (m_WrapMatrixByRow) {
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
void Matrix<DataType>::_concatenate(Matrix<DataType> &firstSrcMatrix, Matrix<DataType> &secondSrcMatrix)
{
    if (m_WrapMatrixByRow) {
        resizeNoInit(firstSrcMatrix.m_NrOfRows+secondSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns);

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
        resizeNoInit(firstSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns+secondSrcMatrix.m_NrOfColumns);

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




