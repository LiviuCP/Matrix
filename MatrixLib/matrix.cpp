#include "matrix.h"

template<typename DataType> int Matrix<DataType>::s_FilePosX=0;
template<typename DataType> int Matrix<DataType>::s_FilePosY=0;

template <typename DataType>
Matrix<DataType>::Matrix()
    : m_pMatrix{new DataType*[1]}
    , m_NrOfRows{1}
    , m_NrOfColumns{1}
    , m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    m_pMatrix[0] = new DataType;
    m_pMatrix[0][0] = 0;

    resetCurrentPos();
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3, "template <typename DataType> Matrix<DataType>::Matrix(int m, int n)");
    }
    else
    {
        _allocMemory(nrOfRows,nrOfColumns);
        setItemsToZero();
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(int nrOfRowsColumns)
    : Matrix{nrOfRowsColumns, nrOfRowsColumns}
{
}

template <typename DataType>
Matrix<DataType>::Matrix(DataType** matrixPtr, int nrOfRows, int nrOfColumns)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (matrixPtr==nullptr)
    {
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    }
    else if (nrOfRows <= 0 || nrOfColumns <= 0)
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    }
    else
    {
        _allocMemory(nrOfRows, nrOfColumns);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pMatrix[row][col]=matrixPtr[row][col];
            }
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(DataType* matrixPtr, int nrOfRows, int nrOfColumns)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if (matrixPtr==0)
    {
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }
    else if ((nrOfRows<=0) || (nrOfColumns<=0))
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }
    else
    {
        _allocMemory(nrOfRows, nrOfColumns);

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pMatrix[row][col]=*(matrixPtr++);
            }
        }
    }
}

template<typename DataType>
Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, istream &in)
    : m_MatrixPrintMode{0}
    , m_MatrixEntryMode{0}
    , m_WrapMatrixByRow{true}
{
    if ((nrOfRows<=0) || (nrOfColumns<=0))
    {
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    }
    else
    {
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
            m_pMatrix[row][col]=matrix.m_pMatrix[row][col];
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
    return m_pMatrix[i][j];
}

template<typename DataType>
DataType** Matrix<DataType>::getp()
{
    return m_pMatrix;
}

template<typename DataType>
DataType* Matrix<DataType>::getp(int i)
{
    if (i<0)
    {
        _handleException(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
    }
    return m_pMatrix[i%m_NrOfRows];
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
            m_pMatrix[row][col]=0;
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
            m_pMatrix[diagIndex][diagIndex] = 1;
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
    if (nrOfRows<=0 || nrOfColumns<=0)
    {
        _handleException(3, "template <typename DataType> void Matrix<DataType>::resize_m(int m, int n)");
    }
    else if (nrOfRows!=m_NrOfRows || nrOfColumns!=m_NrOfColumns)
    {
        DataType** temp;
        Matrix matrix;

        temp=matrix.m_pMatrix;
        matrix.m_pMatrix=m_pMatrix;
        m_pMatrix=temp;

        matrix.m_NrOfRows=m_NrOfRows;
        matrix.m_NrOfColumns=m_NrOfColumns;

        _deallocMemory();
        _allocMemory(nrOfRows,nrOfColumns);
        matrix.resetCurrentPos();

        if (nrOfRows<matrix.m_NrOfRows && nrOfColumns<matrix.m_NrOfColumns) {
            for (int row{0}; row<nrOfRows; ++row)
            {
                for (int col{0}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=matrix.m_pMatrix[row][col];
                }
            }
        }
        else if (nrOfRows<=matrix.m_NrOfRows && nrOfColumns>=matrix.m_NrOfColumns) {
            for (int row{0}; row<nrOfRows; ++row)
            {
                for (int col{0}; col<matrix.m_NrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=matrix.m_pMatrix[row][col];
                }
            }
            for (int row{0}; row<nrOfRows; ++row)
            {
                for (int col{matrix.m_NrOfColumns}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=0;
                }
            }
        }
        else if ((nrOfRows>=matrix.m_NrOfRows) && (nrOfColumns<=matrix.m_NrOfColumns)) {
            for (int row{0}; row<matrix.m_NrOfRows; ++row)
            {
                for (int col{0}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=matrix.m_pMatrix[row][col];
                }
            }
            for (int row{matrix.m_NrOfRows}; row<nrOfRows; ++row)
            {
                for (int col{0}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=0;
                }
            }
        }
        else
        {
            for (int row{0}; row<matrix.m_NrOfRows; ++row)
            {
                for (int col{0}; col<matrix.m_NrOfColumns; ++col)
                {
                    m_pMatrix[row][col]=matrix.m_pMatrix[row][col];
                }
            }
            for (int row{0}; row<nrOfRows; row++)
            {
                for (int col{matrix.m_NrOfColumns}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col] = 0;
                }
            }
            for (int row{matrix.m_NrOfRows}; row<nrOfRows; ++row)
            {
                for (int col{0}; col<nrOfColumns; col++)
                {
                    m_pMatrix[row][col] = 0;
                }
            }
            for (int row{matrix.m_NrOfRows}; row<nrOfRows; ++row)
            {
                for (int col{matrix.m_NrOfColumns}; col<nrOfColumns; ++col)
                {
                    m_pMatrix[row][col] = 0;
                }
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapItem(int rowNr, int columnNr, Matrix& matrix, int matrixRowNr, int matrixColumnNr)
{
    if (matrix.m_pMatrix == m_pMatrix)
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
        std::swap(m_pMatrix[rowNr][columnNr], m_pMatrix[matrixRowNr][matrixColumnNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRow(int rowNr, Matrix& matrix, int matrixRowNr)
{
    if (matrix.m_pMatrix==m_pMatrix)
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
        std::swap(m_pMatrix[rowNr], matrix.m_pMatrix[matrixRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumn(int columnNr, Matrix& matrix, int matrixColumnNr)
{
    if (matrix.m_pMatrix==m_pMatrix)
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
            DataType swap{m_pMatrix[row][columnNr]};
            m_pMatrix[row][columnNr] = matrix.m_pMatrix[row][matrixColumnNr];
            matrix.m_pMatrix[row][matrixColumnNr] = swap;
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
    else if (m_pMatrix==matrix.m_pMatrix)
    {
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    }
    else
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pMatrix[rowNr][col]};
            m_pMatrix[rowNr][col] = matrix.m_pMatrix[col][matrixColumnNr];
            matrix.m_pMatrix[col][matrixColumnNr] = swap;
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
        std::swap(m_pMatrix[firstRowNr][firstColumnNr], m_pMatrix[secondRowNr][secondColumnNr]);
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
        std::swap(m_pMatrix[firstRowNr], m_pMatrix[secondRowNr]);
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
            DataType swap{m_pMatrix[row][firstColumnNr]};
            m_pMatrix[row][firstColumnNr] = m_pMatrix[row][secondColumnNr];
            m_pMatrix[row][secondColumnNr] = swap;
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
            DataType swap{m_pMatrix[rowColumnNr][col]};
            m_pMatrix[rowColumnNr][col] = m_pMatrix[col][rowColumnNr];
            m_pMatrix[col][rowColumnNr] = swap;
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
    std::swap(m_pMatrix, matrix.m_pMatrix);
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
        insert_ptr[row] = m_pMatrix[row];
    }

    insert_ptr[rowNr]=new DataType[m_NrOfColumns];

    for (int col{0}; col<m_NrOfColumns; ++col)
    {
        insert_ptr[rowNr][col]=0;
    }

    for (int row{rowNr}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row+1] = m_pMatrix[row];
    }

    delete []m_pMatrix;
    m_pMatrix = insert_ptr;
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
        insert_ptr[row] = m_pMatrix[row];
    }

    delete []m_pMatrix[rowNr];

    for (int row{rowNr}; row<m_NrOfRows-1; ++row)
    {
        insert_ptr[row] = m_pMatrix[row+1];
    }

    delete []m_pMatrix;
    m_pMatrix = insert_ptr;
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
            insert_ptr[row][col]=m_pMatrix[row][col];
        }
    }

    for(int row{0}; row<m_NrOfRows; ++row)
    {
        for(int col=columnNr+1; col<m_NrOfColumns+1; ++col)
        {
            insert_ptr[row][col]=m_pMatrix[row][col-1];
        }
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        insert_ptr[row][columnNr]=0;
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete []m_pMatrix[row];
    }

    delete []m_pMatrix;
    m_pMatrix = insert_ptr;
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
            insert_ptr[row][col]=m_pMatrix[row][col];
        }
    }

    for(int row{0}; row<m_NrOfRows; ++row)
    {
        for(int col{columnNr}; col<m_NrOfColumns-1; ++col)
        {
            insert_ptr[row][col]=m_pMatrix[row][col+1];
        }
    }

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        delete []m_pMatrix[row];
    }

    delete []m_pMatrix;
    m_pMatrix = insert_ptr;
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
            dest.m_pMatrix[destColumnNr][row] = coeff * m_pMatrix[rowNr][row] + srcCoeff * src.m_pMatrix[row][srcColumnNr];
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
            dest.m_pMatrix[row][destColumnNr] = coeff * m_pMatrix[rowNr][row] + srcCoeff * src.m_pMatrix[row][srcColumnNr];
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
            dest.m_pMatrix[destRowNr][row] = coeff * m_pMatrix[row][columnNr] + srcCoeff * src.m_pMatrix[srcRowNr][row];
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
            dest.m_pMatrix[row][destRowNr] = coeff * m_pMatrix[row][columnNr] + srcCoeff * src.m_pMatrix[srcRowNr][row];
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
            dest.m_pMatrix[destRowNr][row] = coeff * m_pMatrix[rowNr][row] + srcCoeff * src.m_pMatrix[srcRowNr][row];
        }
    }
    else {
        if (destRowNr>=dest.m_NrOfColumns)
        {
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            dest.m_pMatrix[row][destRowNr] = coeff * m_pMatrix[rowNr][row] + srcCoeff * src.m_pMatrix[srcRowNr][row];
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
            dest.m_pMatrix[destColumnNr][row] = coeff * m_pMatrix[row][columnNr] + srcCoeff * src.m_pMatrix[row][srcColumnNr];
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
            dest.m_pMatrix[row][destColumnNr] = coeff * m_pMatrix[row][columnNr] + srcCoeff * src.m_pMatrix[row][srcColumnNr];
        }
    }
}

template <typename DataType>
void Matrix<DataType>:: copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns)
{
    if (src.m_pMatrix==m_pMatrix)
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
            m_pMatrix[m_PosX+row][m_PosY+col] = src.m_pMatrix[src.m_PosX+row][src.m_PosY+col];
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
            m_pMatrix[row][col] = src[row][col];
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
            m_pMatrix[row][col] = *(src++);
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

    Matrix thirdMatrix;

    if ((firstSrcMatrix.m_pMatrix==m_pMatrix) || (secondSrcMatrix.m_pMatrix==m_pMatrix))
    {
        thirdMatrix.m_pMatrix = m_pMatrix;
        thirdMatrix.m_NrOfRows = m_NrOfRows;
        thirdMatrix.m_NrOfColumns = m_NrOfColumns;

        _allocMemory(1,1);
    }

    if ((firstSrcMatrix.m_pMatrix == m_pMatrix) && (secondSrcMatrix.m_pMatrix!=m_pMatrix))
    {
        _concatenate(thirdMatrix, secondSrcMatrix);
    }
    else if ((firstSrcMatrix.m_pMatrix != m_pMatrix) && (secondSrcMatrix.m_pMatrix == m_pMatrix))
    {
        _concatenate(firstSrcMatrix, thirdMatrix);
    }
    else if ((firstSrcMatrix.m_pMatrix == m_pMatrix) && (secondSrcMatrix.m_pMatrix == m_pMatrix))
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
    if (firstDestMatrix.m_pMatrix==secondDestMatrix.m_pMatrix)
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

    Matrix thirdMatrix;

    if ((firstDestMatrix.m_pMatrix == m_pMatrix) || (secondDestMatrix.m_pMatrix == m_pMatrix)) {
        thirdMatrix.m_pMatrix = m_pMatrix;
        thirdMatrix.m_NrOfRows = m_NrOfRows;
        thirdMatrix.m_NrOfColumns = m_NrOfColumns;
        thirdMatrix.m_WrapMatrixByRow = m_WrapMatrixByRow;

        _allocMemory(1,1);
    }

    if ((firstDestMatrix.m_pMatrix == m_pMatrix) && (secondDestMatrix.m_pMatrix != m_pMatrix))
    {
        thirdMatrix._split(*this, secondDestMatrix, splitRowColumnNr);
    }
    else if ((firstDestMatrix.m_pMatrix != m_pMatrix) && (secondDestMatrix.m_pMatrix == m_pMatrix))
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
    if (m_pMatrix==coeff.m_pMatrix)
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
                m_pMatrix[row][col] = src.m_pMatrix[row][col] * coeff.m_pMatrix[row][0];
            }
        }
    }
    else
    {
        for (int row{0}; row<m_NrOfRows; ++row)
        {
            if (coeff.m_pMatrix[row][0]==0)
            {
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
            }
        }

        for (int row{0}; row<m_NrOfRows; ++row)
        {
            for (int col{0}; col<m_NrOfColumns; ++col)
            {
                m_pMatrix[row][col] = src.m_pMatrix[row][col] / coeff.m_pMatrix[row][0];
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::applyCoefficientsToColumn (const Matrix &coeff, Matrix &src, bool multiply)
{
    if (coeff.m_pMatrix==m_pMatrix)
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
                m_pMatrix[row][col] = src.m_pMatrix[row][col] * coeff.m_pMatrix[0][col];
            }
        }
    }
    else {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            if (coeff.m_pMatrix[0][col]==0)
            {
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
            }
        }

        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            for (int i{0}; i<m_NrOfRows; ++i)
            {
                m_pMatrix[i][col] = src.m_pMatrix[i][col] / coeff.m_pMatrix[0][col];
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

    Matrix result{m_NrOfRows,m_NrOfColumns};

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<m_NrOfColumns; ++col)
        {
            result.m_pMatrix[row][col] = m_pMatrix[row][col] + matrix.m_pMatrix[row][col];
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

    Matrix result{m_NrOfRows,m_NrOfColumns};

    for (int i{0}; i<m_NrOfRows; ++i)
    {
        for (int j{0}; j<m_NrOfColumns; ++j)
        {
            result.m_pMatrix[i][j]=m_pMatrix[i][j]-matrix.m_pMatrix[i][j];
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

    Matrix result{m_NrOfRows,matrix.m_NrOfColumns};

    for (int row{0}; row<m_NrOfRows; ++row)
    {
        for (int col{0}; col<matrix.m_NrOfColumns; ++col)
        {
            for (int pivot{0}; pivot<m_NrOfColumns; ++pivot)
            {
                result.m_pMatrix[row][col] = result.m_pMatrix[row][col]+m_pMatrix[row][pivot] * matrix.m_pMatrix[pivot][col];
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

    Matrix result;

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
    if (!(matrix.m_pMatrix == m_pMatrix))
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
                m_pMatrix[row][col] = matrix.m_pMatrix[row][col];
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

    if (matrix.m_pMatrix==m_pMatrix)
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
                if (m_pMatrix[row][col]!=matrix.m_pMatrix[row][col])
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
ostream& operator<<(ostream &out, const Matrix<DataType> &matrix)
{
    if((matrix.m_MatrixPrintMode==4 || matrix.m_MatrixPrintMode==5) && (matrix.m_NrOfRows!=matrix.m_NrOfColumns))
    {
        Matrix<DataType>::_handleException(1, "friend ostream &operator<<(ostream &os, Matrix &m)");
    }

    matrix._writeMatrix(out, matrix.m_MatrixPrintMode);

    return out;
}

template<typename DataType>
istream& operator>>(istream &in, Matrix<DataType> &matrix)
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

    Matrix matrix{*this};
    int sign{1};
    int temp{1};
    bool isZeroDet{false};

    // convert to triangle matrix using Gauss-Jordan algorithm
    for (int diagIndex{0}; diagIndex<m_NrOfRows-1; ++diagIndex)
    {
        if (matrix.m_pMatrix[diagIndex][diagIndex]==0)
        {
            isZeroDet = true;
            for (int firstRowIndex{diagIndex+1}; firstRowIndex<m_NrOfRows; ++firstRowIndex)
            {
                if (matrix.m_pMatrix[firstRowIndex][diagIndex]!=0)
                {
                    matrix.swapRow(diagIndex,firstRowIndex);
                    sign = sign * (-1);

                    for (int colIndex{diagIndex+1}; colIndex<m_NrOfColumns; ++colIndex)
                    {
                        for (int secondRowIndex{diagIndex+1}; secondRowIndex<m_NrOfRows; ++secondRowIndex)
                        {
                            matrix.m_pMatrix[secondRowIndex][colIndex] = matrix.m_pMatrix[secondRowIndex][colIndex] * (matrix.m_pMatrix[diagIndex][diagIndex]) -
                                                                         matrix.m_pMatrix[diagIndex][colIndex] * (matrix.m_pMatrix[secondRowIndex][diagIndex]);
                            temp = temp * (matrix.m_pMatrix[diagIndex][diagIndex] * matrix.m_pMatrix[secondRowIndex][diagIndex]);
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
            det  =det * matrix.m_pMatrix[diag][diag];
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
                matrix.m_pMatrix[row][col]=(matrix.m_pMatrix[row][col]) * (matrix.m_pMatrix[matrix.m_PosX][matrix.m_PosY]) -
                                           (matrix.m_pMatrix[matrix.m_PosX][col]) * (matrix.m_pMatrix[row][matrix.m_PosY]);
            }
        }

        ++matrix.m_PosX;
        ++matrix.m_PosY;
    };

    Matrix matrix;

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
        if (matrix.m_pMatrix[matrix.m_PosX][matrix.m_PosY]==0)
        {
            for (int row{matrix.m_PosX+1}; row<matrix.m_NrOfRows; ++row)
            {
                if (matrix.m_pMatrix[row][matrix.m_PosY]!=0)
                {
                    ++matrixRank;
                    matrix.swapRow(row,matrix.m_PosX);
                    continueCalculation(matrix);
                }
            }

            for (int col{matrix.m_PosY+1}; col<matrix.m_NrOfColumns; ++col)
            {
                if (matrix.m_pMatrix[matrix.m_PosX][col]!=0)
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
        if (matrix.m_pMatrix[matrix.m_PosX][col]!=0)
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
    int i,j,k,l;
    Matrix <DataType> temp;
    if ((m_pMatrix==coeff.m_pMatrix) || (m_pMatrix==pseudoInverse.m_pMatrix))
        _handleException(25, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    if (m_NrOfRows!=m_NrOfColumns)
        _handleException(1, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    temp=*this;
    pseudoInverse.transformToUnitMatrix(m_NrOfRows);
    coeff.resizeNoInit(m_NrOfRows,1);

    for (k=0; k<m_NrOfRows-1; k++) {
        if (temp.m_pMatrix[k][k]==0) {
            for (l=k+1; l<m_NrOfRows; l++) {
                if (temp.m_pMatrix[k][l]!=0) {
                    temp.swapRow(k,l);
                    pseudoInverse.swapRow(k,l);
                    goto Prelucrare;
                }
            }
            _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
        }
Prelucrare:
        for (j=0; j<m_NrOfRows; j++)
            for (i=k+1; i<m_NrOfRows; i++) {
                if (j>k)
                    temp.m_pMatrix[i][j]=temp.m_pMatrix[i][j]*temp.m_pMatrix[k][k]- temp.m_pMatrix[k][j]*temp.m_pMatrix[i][k];
                pseudoInverse.m_pMatrix[i][j]=pseudoInverse.m_pMatrix[i][j]*temp.m_pMatrix[k][k] - pseudoInverse.m_pMatrix[k][j]*temp.m_pMatrix[i][k];
            }
    }
    for (k=0; k<m_NrOfRows; k++)
        for (i=k+1; i<m_NrOfRows; i++)
            temp.m_pMatrix[i][k]=0;
    if (temp.m_pMatrix[m_NrOfRows-1][m_NrOfRows-1]==0)
        _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    for (k=m_NrOfRows-1; k>0; k--)
        for (i=0; i<=k-1; i++)
            for (j=0; j<=m_NrOfRows-1; j++) {
                if (j<k)
                    temp.m_pMatrix[i][j]=temp.m_pMatrix[i][j]*temp.m_pMatrix[k][k]-temp.m_pMatrix[k][j]*temp.m_pMatrix[i][k];
                pseudoInverse.m_pMatrix[i][j]=pseudoInverse.m_pMatrix[i][j]*temp.m_pMatrix[k][k]-pseudoInverse.m_pMatrix[k][j]*temp.m_pMatrix[i][k];
            }
    for (k=0; k<m_NrOfRows; k++)
        coeff.m_pMatrix[k][0]=temp.m_pMatrix[k][k];
}

template <typename DataType>
void Matrix<DataType>::getTransposedMatrix(Matrix<DataType>& result)
{
    int i,j;
    Matrix temp;
    DataType **temp_ptr;
    if (m_pMatrix==result.m_pMatrix) {
        temp_ptr=temp.m_pMatrix;
        temp.m_pMatrix=m_pMatrix;
        m_pMatrix=temp_ptr;
        temp.m_NrOfRows=m_NrOfRows;
        temp.m_NrOfColumns=m_NrOfColumns;
        resizeNoInit(m_NrOfColumns, m_NrOfRows);
        for (i=0; i<m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=temp.m_pMatrix[j][i];
        return;
    }
    result.resizeNoInit(m_NrOfColumns,m_NrOfRows);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            result.m_pMatrix[j][i]=m_pMatrix[i][j];
}

template <typename DataType>
void Matrix<DataType>::sums(Matrix& result, int mode)
{
    int i,j;
    DataType sum=0;
    if (result.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    if (mode>4)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    if (mode<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    switch (mode) {
        case 0:
            result.resizeNoInit(1,1);
            for (i=0; i<m_NrOfRows; i++)
                for (j=0; j<m_NrOfColumns; j++)
                    sum=sum + m_pMatrix[i][j];
            result.m_pMatrix[0][0]=sum;
            return;
        case 1:
            result.resizeNoInit(1,1);
            for (j=0; j<m_NrOfColumns; j++)
                sum=sum+m_pMatrix[m_PosX][j];
            result.m_pMatrix[0][0]=sum;
            return;
        case 2:
            result.resizeNoInit(m_NrOfRows,1);
            for (i=0; i<m_NrOfRows; i++) {
                result.m_pMatrix[i][0]=0;
                for (j=0; j<m_NrOfColumns; j++)
                    result.m_pMatrix[i][0]=result.m_pMatrix[i][0]+m_pMatrix[i][j];
            }
            return;
        case 3:
            result.resizeNoInit(1,1);
            for (i=0; i<m_NrOfRows; i++)
                sum=sum+m_pMatrix[i][m_PosY];
            result.m_pMatrix[0][0]=sum;
            return;
        case 4:
            result.resizeNoInit(1,m_NrOfColumns);
            for (j=0; j<m_NrOfColumns; j++) {
                result.m_pMatrix[0][j]=0;
                for (int i=0; i<m_NrOfRows; i++)
                    result.m_pMatrix[0][j]=result.m_pMatrix[0][j]+m_pMatrix[i][j];
            }
            return;
    }
}

template <typename DataType>
void Matrix<DataType>::products(Matrix& result, int mode)
{
    int i,j;
    DataType product;
    if (result.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    if (mode>4)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    if (mode<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    switch (mode) {
        case 0:
            product=1;
            result.resizeNoInit(1,1);
            for (i=0; i<m_NrOfRows; i++)
                for (j=0; j<m_NrOfColumns; j++)
                    product = product * m_pMatrix[i][j];
            result.m_pMatrix[0][0]=product;
            return;
        case 1:
            product=1;
            result.resizeNoInit(1,1);
            for (j=0; j<m_NrOfColumns; j++)
                product=product*m_pMatrix[m_PosX][j];
            result.m_pMatrix[0][0]=product;
            return;
        case 2:
            result.resizeNoInit(m_NrOfRows,1);
            for (i=0; i<m_NrOfRows; i++) {
                product=1;
                for (int j=0; j<m_NrOfColumns; j++)
                    product=product*m_pMatrix[i][j];
                result.m_pMatrix[i][0]=product;
            }
            return;
        case 3:
            result.resizeNoInit(1,1);
            product=1;
            for (i=0; i<m_NrOfRows; i++)
                product=product*m_pMatrix[i][m_PosY];
            result.m_pMatrix[0][0]=product;
            return;
        case 4:
            result.resizeNoInit(1,m_NrOfColumns);
            for (j=0; j<m_NrOfColumns; j++) {
                product=1;
                for (int i=0; i<m_NrOfRows; i++)
                    product=product*m_pMatrix[i][j];
                result.m_pMatrix[0][j]=product;
            }
            return;
    }
}

template <typename DataType>
void Matrix<DataType>::getNegativeMatrix(Matrix<DataType>& result)
{
    int i,j;
    if (result.m_pMatrix==m_pMatrix) goto negativation;
    result.resizeNoInit(m_NrOfRows,m_NrOfColumns);
negativation:
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            result.m_pMatrix[i][j]=(-1)*m_pMatrix[i][j];
}

template <typename DataType>
void Matrix<DataType>::getInverseElementsMatrix(Matrix<DataType>& result)
{
    int i,j;
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            if (m_pMatrix[i][j]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::inv_matrix(Matrix<DataType> &m)");
    if (result.m_pMatrix==m_pMatrix) goto inversion;
    result.resizeNoInit(m_NrOfRows,m_NrOfColumns);
inversion:
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            result.m_pMatrix[i][j]=1/m_pMatrix[i][j];
}

template<typename DataType>
void Matrix<DataType>::_allocMemory(int nrOfRows, int nrOfColumns)
{
    m_NrOfRows=nrOfRows;
    m_NrOfColumns=nrOfColumns;
    m_pMatrix=new DataType*[nrOfRows];

    for (int row{0}; row<nrOfRows; ++row)
    {
        m_pMatrix[row]=new DataType[nrOfColumns];
    }

    // to be clarified if this function call should be kept or better put separately after calling the _allocMemory() method
    resetCurrentPos();
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    resetCurrentPos();
    for (int i=0; i<m_NrOfRows; i++)
        delete m_pMatrix[i];
    delete []m_pMatrix;
}

template <typename DataType>
void Matrix<DataType>::_writeMatrix(ostream& os, int mode)
{
    int i,j;
    switch (mode) {
    case 0:
        for (i=0; i<m_NrOfRows; i++) {
            for (j=0; j<m_NrOfColumns; j++)
                    os<<m_pMatrix[i][j]<<" ";
                os<<endl;
            }
            return;
        case 1:
            for (j=0; j<m_NrOfColumns; j++)
                os<<m_pMatrix[m_PosX][j]<<" ";
            return;
        case 2:
            for (i=0; i<m_NrOfRows; i++)
                os<<m_pMatrix[i][m_PosY]<<endl;
            return;
        case 3:
            os<<m_pMatrix[m_PosX][m_PosY];
            return;
        case 4:
            for (i=0; i<m_NrOfRows; i++)
                os<<m_pMatrix[i][i]<<" ";
            return;
        case 5:
            for (i=m_NrOfRows-1; i>=0; i--)
                os<<m_pMatrix[i][m_NrOfRows-1-i]<<" ";
            return;
    }
}

template <typename DataType>
void Matrix<DataType>::_readMatrix(istream &is, int mode)
{
    string s;
    int i,j;
    stringstream str_st(ios::in|ios::out);
    switch (mode) {
        case 0:
            for (i=0; i<m_NrOfRows; i++)
                for (j=0; j<m_NrOfColumns; j++) {
                    if (is.eof())
                        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                    cout<<"["<<i<<"]["<<j<<"]= ";
                    is>>m_pMatrix[i][j];
                }
            return;
        case 1:
            cout<<"["<<m_PosX<<"]["<<m_PosY<<"]= ";
            is>>m_pMatrix[m_PosX][m_PosY];
            return;
        case 2:
            for (j=0; j<m_NrOfColumns; j++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<m_PosX<<"]["<<j<<"]= ";
                is>>m_pMatrix[m_PosX][j];
            }
            return;
        case 3:
            for (i=0; i<m_NrOfRows; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<m_PosY<<"]= ";
                is>>m_pMatrix[i][m_PosY];
            }
            return;
        case 4:
            for(i=0; i<m_NrOfRows; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<i<<"]= ";
                is>>m_pMatrix[i][i];
            }
            return;
        case 5:
            for(i=m_NrOfRows-1; i>=0; i--) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<m_NrOfRows-1-i<<"]= ";
                is>>m_pMatrix[i][m_NrOfRows-1-i];
            }
            return;
        case 6:
            _readDiscard(is);
            m_PosX=0;
            for (i=0; i<m_NrOfRows; i++) {
                _readTextLine(is);
                m_PosX++;
                s_FilePosX++;
            }
            return;
        case 7:
            _readDiscard(is);
            _readSingleItem(is);
            return;
        case 8:
            _readDiscard(is);
            _readTextLine(is);
            return;
        case 9:
            _readDiscard(is);
            m_PosX=0;
            for(i=0; i<m_NrOfRows; i++) {
                _readSingleItem(is);
                m_PosX++;
                s_FilePosX++;
            }
            return;
        case 10:
            _readDiscard(is);
            resetCurrentPos();
            s_FilePosY=0;
            for (i=0; i<m_NrOfRows; i++) {
                _readSingleItem(is);
                s_FilePosX++;
                m_PosY=++m_PosX;
                s_FilePosY++;
            }
            return;
        case 11:
            _readDiscard(is);
            s_FilePosY=m_NrOfRows-1;
            m_PosX=0;
            m_PosY=m_NrOfRows-1;
            for(i=0; i<m_NrOfRows; i++) {
                _readSingleItem(is);
                s_FilePosX++;
                s_FilePosY--;
                m_PosX++;
                m_PosY--;
            }
            return;
        case 12:
            for (i=0; i<m_NrOfRows; i++)
                for (j=0; j<m_NrOfColumns; j++) {
                    if (is.eof())
                        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                    is>>m_pMatrix[i][j];
                }
            return;
        case 13:
            if (is.eof())
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            is>>m_pMatrix[m_PosX][m_PosY];
            return;
        case 14:
            for (j=0; j<m_NrOfColumns; j++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>m_pMatrix[m_PosX][j];
            }
            return;
        case 15:
            for (i=0; i<m_NrOfRows; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>m_pMatrix[i][m_PosY];
            }
            return;
        case 16:
            for (i=0; i<m_NrOfRows; i++)  {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>m_pMatrix[i][i];
            }
            return;
        case 17:
            for (i=m_NrOfRows-1; i>=0; i--) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>m_pMatrix[i][m_NrOfRows-1-i];
            }
    }
}

template<typename DataType>
void Matrix<DataType>::_readTextLine(istream &in)
{
    string s;
    int j;
    int k=0;
    int l;
    stringstream str_st;
    if (in.eof())
        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
    getline(in,s);
    l=s.size();
    if (l==0)
        _handleException (28, "friend istream &operator>> (istream &is, Matrix &m)");
    for (j=0; j<m_NrOfColumns; j++) {
        while(s[k]==' ' && k<l)
            k++;
        if (k==l)
            _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
        do
            str_st.put(s[k++]);
        while(s[k]!=' ' && k<l);
        str_st>>m_pMatrix[m_PosX][j];
        str_st.str("");
        str_st.clear();
    }
}

template<typename DataType>
void Matrix<DataType>::_readSingleItem(istream &in)
{
    string s;
    int j;
    int k=0;
    int l;
    stringstream str_st;
    if (in.eof())
        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
    getline(in,s);
    l=s.size();
    if (l==0)
        _handleException (28, "friend istream &operator>> (istream &is, Matrix &m)");
    for (j=0; j<s_FilePosY; j++) {
        while (s[k]==' ' && k<l)
            k++;
        if (k==l)
            _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
        do
            k++;
        while(s[k]!=' ' && k<l);
    }
    if (k==l)
        _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
    while(s[k]==' ' && k<l)
        k++;
    if (k==l)
        _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
    do
        str_st.put(s[k++]);
    while(s[k]!=' ' && k<l);
    str_st>>m_pMatrix[m_PosX][m_PosY];
    str_st.str("");
    str_st.clear();
}

template<typename DataType>
void Matrix<DataType>::_readDiscard(istream &in)
{
    string s;
    int i;
    in.clear();
    in.seekg(0);
    for (i=0; i<s_FilePosX; i++) {
        if (in.eof())
            _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
        getline(in,s);
        s="";
        s.clear();
    }
}

template<typename DataType>
void Matrix<DataType>::_quickSort(int first, int last, int mode, int pos)
{
    if (last>first) {
        int pivot=(first+last)/2;
        int k=_createSortingPartition(first,last,pivot,mode,pos);
        _quickSort(first,k-1,mode,pos);
        _quickSort(k+1,last,mode,pos);
    }
}

template<typename DataType>
void Matrix<DataType>::_quickSort(int first, int last, int mode)
{
    if (last>first) {
        int pivot=(first+last)/2;
        int k=_createSortingPartition(first,last,pivot,mode);
        _quickSort(first,k-1,mode);
        _quickSort(k+1,last,mode);
    }
}

template<typename DataType>
int Matrix<DataType>:: _createSortingPartition(int first,int last,int pivot,int mode,int pos)
{
    int i,j;
    switch(mode) {
    case 0:
        if (pivot!=last)
            swapItem(pos,pivot,pos,last);
        i=first-1; j=last;
        while (i<j) {
            do i++;
                    while ((i!=j) && (m_pMatrix[pos][i]<m_pMatrix[pos][last]));
                do j--;
                    while ((i!=j) && (m_pMatrix[pos][j]>m_pMatrix[pos][last]));
                if (i<j)
                    swapItem(pos,i,pos,j);
            }
            if (i!=last)
                swapItem(pos,i,pos,last);
            return i;
        case 1:
            if (pivot!=last)
                swapItem(pos, pivot, pos,last);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (m_pMatrix[pos][i]>m_pMatrix[pos][last]));
                do j--;
                    while ((i!=j) && (m_pMatrix[pos][j]<m_pMatrix[pos][last]));
                if (i<j)
                    swapItem(pos,i,pos,j);
            }
            if (i!=last)
                swapItem(pos,i,pos,last);
            return i;
        case 2:
            if (pivot!=last)
                swapItem(pivot,pos,last,pos);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (m_pMatrix[i][pos]<m_pMatrix[last][pos]));
                do j--;
                    while ((i!=j) && (m_pMatrix[j][pos]>m_pMatrix[last][pos]));
                if (i<j)
                    swapItem(i,pos,j,pos);
            }
            if (i!=last)
                swapItem(i,pos,last,pos);
            return i;
        case 3:
            if (pivot!=last)
                swapItem(pivot,pos,last,pos);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (m_pMatrix[i][pos]>m_pMatrix[last][pos]));
                do j--;
                    while ((i!=j) && (m_pMatrix[j][pos]<m_pMatrix[last][pos]));
                if (i<j)
                    swapItem(i,pos,j,pos);
            }
            if (i!=last)
                swapItem(i,pos,last,pos);
            return i;
    }
}

template<typename DataType>
int Matrix<DataType>:: _createSortingPartition(int first,int last,int pivot,int mode)
{
    int i,j;
    DataType swap;
    switch(mode) {
        case 0:
            if (pivot!=last) {
                swap=_getItemForLineWrap(pivot);
                _getItemForLineWrap(pivot)=_getItemForLineWrap(last);
                _getItemForLineWrap(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (_getItemForLineWrap(i)<_getItemForLineWrap(last)));
                do j--;
                    while ((i!=j) && (_getItemForLineWrap(j)>_getItemForLineWrap(last)));
                if (i<j) {
                    swap=_getItemForLineWrap(i);
                    _getItemForLineWrap(i)=_getItemForLineWrap(j);
                    _getItemForLineWrap(j)=swap;
                }
            }
            if (i!=(last)) {
                swap=_getItemForLineWrap(i);
                _getItemForLineWrap(i)=_getItemForLineWrap(last);
                _getItemForLineWrap(last)=swap;
            }
            return i;
        case 1:
            if (pivot!=last) {
                swap=_getItemForLineWrap(pivot);
                _getItemForLineWrap(pivot)=_getItemForLineWrap(last);
                _getItemForLineWrap(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (_getItemForLineWrap(i)>_getItemForLineWrap(last)));
                do j--;
                    while ((i!=j) && (_getItemForLineWrap(j)<_getItemForLineWrap(last)));
                if (i<j) {
                    swap=_getItemForLineWrap(i);
                    _getItemForLineWrap(i)=_getItemForLineWrap(j);
                    _getItemForLineWrap(j)=swap;
                }
            }
            if (i!=(last)) {
                swap=_getItemForLineWrap(i);
                _getItemForLineWrap(i)=_getItemForLineWrap(last);
                _getItemForLineWrap(last)=swap;
            }
            return i;
        case 2:
            if (pivot!=last) {
                swap=_getItemForColumnWrap(pivot);
                _getItemForColumnWrap(pivot)=_getItemForColumnWrap(last);
                _getItemForColumnWrap(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (_getItemForColumnWrap(i)<_getItemForColumnWrap(last)));
                do j--;
                    while ((i!=j) && (_getItemForColumnWrap(j)>_getItemForColumnWrap(last)));
                if (i<j) {
                    swap=_getItemForColumnWrap(i);
                    _getItemForColumnWrap(i)=_getItemForColumnWrap(j);
                    _getItemForColumnWrap(j)=swap;
                }
            }
            if (i!=last) {
                swap=_getItemForColumnWrap(i);
                _getItemForColumnWrap(i)=_getItemForColumnWrap(last);
                _getItemForColumnWrap(last)=swap;
            }
            return i;
        case 3:
            if (pivot!=last) {
                swap=_getItemForColumnWrap(pivot);
                _getItemForColumnWrap(pivot)=_getItemForColumnWrap(last);
                _getItemForColumnWrap(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (_getItemForColumnWrap(i)>_getItemForColumnWrap(last)));
                do j--;
                    while ((i!=j) && (_getItemForColumnWrap(j)<_getItemForColumnWrap(last)));
                if (i<j) {
                    swap=_getItemForColumnWrap(i);
                    _getItemForColumnWrap(i)=_getItemForColumnWrap(j);
                    _getItemForColumnWrap(j)=swap;
                }
            }
            if (i!=last) {
                swap=_getItemForColumnWrap(i);
                _getItemForColumnWrap(i)=_getItemForColumnWrap(last);
                _getItemForColumnWrap(last)=swap;
            }
            return i;
    }
}

template<typename DataType>
DataType& Matrix<DataType>::_getItemForLineWrap(int oneDimensionalIndex)
{
    return m_pMatrix[oneDimensionalIndex/m_NrOfColumns][oneDimensionalIndex%m_NrOfColumns];
}

template<typename DataType>
DataType& Matrix<DataType>::_getItemForColumnWrap(int oneDimensionalIndex)
{
    return m_pMatrix[oneDimensionalIndex%m_NrOfRows][oneDimensionalIndex/m_NrOfRows];
}

template<typename DataType>
void Matrix<DataType>::_handleException(int errorType, char* function)
{
    try {
        cerr<<"Exceptie in functia: "<<function<<endl;
        throw errorType;
    }
    catch (int k) {
        switch (k) {


            case 1:
                cerr<<"Eroarea 1: Dimensiunile matricei nu sunt egale."<<endl;
                exit(1);
            case 2:
                cerr<<"Eroarea 2: Determinantul matricei este nul, matricea este neinversabila."<<endl;
                exit(1);
            case 3:
                cerr<<"Eroarea 3: S-a introdus cel putin o dimensiune nula sau negativa a unei matrici."<<endl;
                exit(1);
            case 4:
                cerr<<"Eroarea 4: Rand inexistent al matricei sursa."<<endl;
                exit(1);
            case 5:
                cerr<<"Eroarea 5: Rand inexistent al matricei destinatie."<<endl;
                exit(1);
            case 6:
                cerr<<"Eroarea 6: Cel putzin un rand inexistent al cel putzin unei matrici."<<endl;
                exit(1);
            case 7:
                cerr<<"Eroarea 7: Coloana inexistenta a matricei sursa"<<endl;
                exit(1);
            case 8:
                cerr<<"Eroarea 8: Coloana inexistenta a matricei destinatie"<<endl;
                exit(1);
            case 9:
                cerr<<"Eroarea 9: Cel putzin o coloana inexistenta a cel putzin unei matrici"<<endl;
                exit(1);
            case 10:
                cerr<<"Eroarea 10: Cele 2 matrici nu au aceleasi dimensiuni"<<endl;
                exit(1);
            case 11:
                cerr<<"Eroarea 11: Numarul de coloane ale primei matrici este diferit de numarul de linii ale celei de-a doua matrici"<<endl;
                exit(1);
            case 12:
                cerr<<"Eroarea 12: Coloanele celor 2 matrici nu au aceeasi lungime. Numarul de linii difera."<<endl;
                exit(1);
            case 13:
                cerr<<"Eroarea 13: Liniile celor 2 matrici nu au aceeasi lungime. Numarul de coloane difera."<<endl;
                exit(1);
            case 14:
                cerr<<"Eroarea 14: S-a incercat stergerea singurei coloane a matricei. Acest lucru nu este permis."<<endl;
                exit(1);
            case 15:
                cerr<<"Eroarea 15: S-a incercat stergerea singurei linii a matricei. Acest lucru nu este permis."<<endl;
                exit(1);
            case 16:
                cerr<<"Eroarea 16: Argument negativ al functiei. Se astepta un argument nenegativ."<<endl;
                exit(1);
            case 17:
                cerr<<"Eroarea 17: linia sau coloana inserate in matrice nu sunt inserate pe o pozitie contigua"<<endl;



                exit(1);
            case 18:
                cerr<<"Eroarea 18: S-a incercat accesarea unui element inexistent intr-una dintre matrici"<<endl;
                exit(1);
            case 19:
                cerr<<"Eroarea 19: Din calcule rezulta o matrice cu un numar nul de linii"<<endl;
                exit(1);
            case 20:
                cerr<<"Eroarea 20: Din calcule rezulta o matrice cu un numar nul de coloane"<<endl;
                exit(1);
            case 21:
                cerr<<"Eroarea 21: Argument incorect. Instructiunea switch a functiei nu include aceasta valoare."<<endl;
                exit(1);
            case 22:
                cerr<<"Eroarea 22: Pointer nul. Se cere un pointer nenul."<<endl;
                exit(1);
            case 23:
                cerr<<"Eroarea 23: S-a incercat o impartire la 0. Acest lucru nu este permis."<<endl;
                exit(1);
            case 24:
                cerr<<"Eroarea 24: Aceeasi variabila este folosita in 2 argumente ale functiei. Acest lucru nu este permis."<<endl;
                exit(1);
            case 25:
                cerr<<"Eroarea 25: Matricea curenta a fost folosita in acelasi timp ca argument al functiei. Acest lucru nu este permis pentru aceasta functie."<<endl;
                exit(1);
            case 26:
                cerr<<"Eroarea 26: sfarsit de fisier, operatie intrerupta"<<endl;
                exit(1);
            case 27:
                cerr<<"Eroarea 27: linia citita din fisierul text contine mai putine elemente decat linia matricei curente"<<endl;
                exit(1);
            case 28:
                cerr<<"Eroarea 28: nu s-a gasit nici un caracter pe randul curent al fisierului text."<<endl;
                exit(1);
            default:
                cout<<"Eroare necunoscuta. Programul s-a incheiat"<<endl;
                exit(1);
        }
    }
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::_power(int exp)
{
    Matrix<DataType> b;
    if (exp==1)
        return *this;
    else {
        b=_power(exp/2);
        if (exp%2==0)
            return b*b;
        else
            return b*b*(*this);
    }
}

template<typename DataType>
Matrix<DataType> Matrix<DataType>::_multiply(const DataType &scalar)
{
    Matrix a;
    a.resizeNoInit(m_NrOfRows,m_NrOfColumns);
    for (int i=0; i<m_NrOfRows; i++)
        for (int j=0; j<m_NrOfColumns; j++)
            a.m_pMatrix[i][j]=scalar*m_pMatrix[i][j];
    return a;
}

template<typename DataType>
void Matrix<DataType>::_split(Matrix<DataType> &m1, Matrix<DataType> &m2, int splitRowColumnNr)
{
    int i,j;
    m1._deallocMemory(); m2._deallocMemory();
    if (m_WrapMatrixByRow) {
        m1._allocMemory(splitRowColumnNr,m_NrOfColumns); m2._allocMemory(m_NrOfRows-splitRowColumnNr, m_NrOfColumns);
        for (i=0; i<splitRowColumnNr; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m1.m_pMatrix[i][j]=m_pMatrix[i][j];
        for (i=splitRowColumnNr; i<m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m2.m_pMatrix[i-splitRowColumnNr][j]=m_pMatrix[i][j];
        return;
    }

    m1._allocMemory(m_NrOfRows,splitRowColumnNr); m2._allocMemory(m_NrOfRows,m_NrOfColumns-splitRowColumnNr);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<splitRowColumnNr; j++)
            m1.m_pMatrix[i][j]=m_pMatrix[i][j];
    for (i=0; i<m_NrOfRows; i++)
        for (j=splitRowColumnNr; j<m_NrOfColumns; j++)
            m2.m_pMatrix[i][j-splitRowColumnNr]=m_pMatrix[i][j];
}

template<typename DataType>
void Matrix<DataType>::_concatenate(Matrix<DataType> &firstSrcMatrix, Matrix<DataType> &secondSrcMatrix)
{
    int i,j;
    if (m_WrapMatrixByRow) {
        resizeNoInit(firstSrcMatrix.m_NrOfRows+secondSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns);
        for (i=0; i<firstSrcMatrix.m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=firstSrcMatrix.m_pMatrix[i][j];
        for (i=firstSrcMatrix.m_NrOfRows; i<m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=secondSrcMatrix.m_pMatrix[i-firstSrcMatrix.m_NrOfRows][j];
        return;
    }
    resizeNoInit(firstSrcMatrix.m_NrOfRows, firstSrcMatrix.m_NrOfColumns+secondSrcMatrix.m_NrOfColumns);
    for(i=0; i<m_NrOfRows; i++)
        for (j=0; j<firstSrcMatrix.m_NrOfColumns; j++)
            m_pMatrix[i][j]=firstSrcMatrix.m_pMatrix[i][j];
    for(i=0; i<m_NrOfRows; i++)
        for (j=firstSrcMatrix.m_NrOfColumns; j<m_NrOfColumns; j++)
            m_pMatrix[i][j]=secondSrcMatrix.m_pMatrix[i][j-firstSrcMatrix.m_NrOfColumns];
}




