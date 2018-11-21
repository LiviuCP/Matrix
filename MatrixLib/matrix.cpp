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
    if ((i<0) || (j<0)) _handleException(16, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
    if ((i>=m_NrOfRows) || (j>=m_NrOfColumns)) _handleException(18, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
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
    if (i<0) _handleException(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
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
    m_PosX = abs(m)%m_NrOfRows;
}

template<typename DataType>
void Matrix<DataType>::setPosY(int n)
{
    m_PosY = abs(n)%m_NrOfColumns;
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
    m_MatrixEntryMode=abs(matrixEntryMode)%18;
}

template<typename DataType>
void Matrix<DataType>::setMatrixPrintMode(int matrixPrintMode)
{
    m_MatrixPrintMode=abs(matrixPrintMode)%6;
}

template <typename DataType> void Matrix<DataType>::setItemsToZero()
{
    for (int i=0; i<m_NrOfRows; i++)
        for (int j=0; j<m_NrOfColumns; j++)
            m_pMatrix[i][j]=0;
}

template<typename DataType>
void Matrix<DataType>::incrPosX()
{
    if (m_PosX<m_NrOfRows-1) m_PosX++; else m_PosX=0;
}

template<typename DataType>
void Matrix<DataType>::decrPosX()
{
    if (m_PosX>0) m_PosX--; else m_PosX=m_NrOfRows-1;
}

template<typename DataType>
void Matrix<DataType>::incrPosY()
{
    if (m_PosY<m_NrOfColumns-1) m_PosY++; else m_PosY=0;
}

template<typename DataType>
void Matrix<DataType>::decrPosY()
{
    if (m_PosY>0) m_PosY--; else m_PosY=m_NrOfColumns-1;
}

template<typename DataType>
void Matrix<DataType>::resetCurrentPos()
{
    m_PosX=0;
    m_PosY=0;
}

template<typename DataType>
void Matrix<DataType>::resetCurrentPosInFile()
{
    s_FilePosX=0;
    s_FilePosY=0;
}

template<typename DataType>
void Matrix<DataType>::resizeNoInit(int m, int n)
{
    if ((m<=0) || (n<=0))
        _handleException(3,"template <typename dataType> void Matrix<dataType>::resize(int m, int n)");
    _deallocMemory(); _allocMemory(m, n);
}

template <typename DataType>
void Matrix<DataType>::transformToUnitMatrix(int nrOfRowsColumns)
{
    if (nrOfRowsColumns<=0) _handleException(3,"template <typename DataType> void Matrix<DataType>::unit(int m)");
    _deallocMemory();
    _allocMemory(nrOfRowsColumns,nrOfRowsColumns);
    setItemsToZero();
    for (int i=0; i<nrOfRowsColumns; i++)
        m_pMatrix[i][i]=1;
}

template <typename DataType>
void Matrix<DataType>::transformToZeroMatrix(int nrOfRows, int nrOfColumns)
{
    if (nrOfRows<=0 || nrOfColumns<=0)
        _handleException(3, "template <typename DataType> void Matrix<DataType>::null_matrix(int m, int n)");
    _deallocMemory();
    _allocMemory(nrOfRows,nrOfColumns);
    setItemsToZero();
}

template <typename DataType>
void Matrix<DataType>::resize(int m, int n)
{
    int i,j;
    DataType **temp;
    if ((m==m_NrOfRows)&&(n==m_NrOfColumns)) return;
    if ((m<=0) || (n<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::resize_m(int m, int n)");
    Matrix a;
    temp=a.m_pMatrix;
    a.m_pMatrix=m_pMatrix;
    m_pMatrix=temp;
    a.m_NrOfRows=m_NrOfRows;
    a.m_NrOfColumns=m_NrOfColumns;
    delete m_pMatrix[0];
    delete m_pMatrix;
    _allocMemory(m,n);
    if ((m<a.m_NrOfRows)&&(n<a.m_NrOfColumns)) {
        for (i=0; i<m; i++)
            for (j=0; j<n; j++)
                m_pMatrix[i][j]=a.m_pMatrix[i][j];
        return;
    }
    if ((m<=a.m_NrOfRows)&&(n>=a.m_NrOfColumns)) {
        for (i=0; i<m; i++)
            for (j=0; j<a.m_NrOfColumns; j++)
                m_pMatrix[i][j]=a.m_pMatrix[i][j];
        for (i=0; i<m; i++)
            for (j=a.m_NrOfColumns; j<n; j++)
                m_pMatrix[i][j]=0;
        return;
    }
    if ((m>=a.m_NrOfRows) && (n<=a.m_NrOfColumns)) {
        for (i=0; i<a.m_NrOfRows; i++)
            for (j=0; j<n; j++)
                m_pMatrix[i][j]=a.m_pMatrix[i][j];
        for (i=a.m_NrOfRows; i<m; i++)
            for (j=0; j<n; j++)
                m_pMatrix[i][j]=0;
        return;
    }

    for (i=0; i<a.m_NrOfRows; i++)
        for (j=0; j<a.m_NrOfColumns; j++)
            m_pMatrix[i][j]=a.m_pMatrix[i][j];
    for (i=0; i<m; i++)
        for (j=a.m_NrOfColumns; j<n; j++)
            m_pMatrix[i][j]=0;
    for (i=a.m_NrOfRows; i<m; i++)
        for (j=0; j<n; j++)
            m_pMatrix[i][j]=0;
    for (i=a.m_NrOfRows; i<m; i++)
        for (j=a.m_NrOfColumns; j<n; j++)
            m_pMatrix[i][j]=0;
}
template <typename DataType>
void Matrix<DataType>::swapItem(int rowNr, int columnNr, Matrix& matrix, int matrixRowNr, int matrixColumnNr)
{
    DataType swap;
    if (matrix.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((rowNr<0) || (columnNr<0) || (matrixRowNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((rowNr>=m_NrOfRows) || (columnNr>=m_NrOfColumns) || (matrixRowNr>=matrix.m_NrOfRows) || (matrixColumnNr>=matrix.m_NrOfColumns))
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    swap=m_pMatrix[rowNr][columnNr];
    m_pMatrix[rowNr][columnNr]=matrix.m_pMatrix[matrixRowNr][matrixColumnNr];
    matrix.m_pMatrix[matrixRowNr][matrixColumnNr]=swap;
}

template <typename DataType>
void Matrix<DataType>::swapRow(int rowNr, Matrix& matrix, int matrixRowNr)
{
    DataType *swap;
    if (matrix.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if ((rowNr<0) || (matrixRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if ((rowNr>=m_NrOfRows) || (matrixRowNr>=matrix.m_NrOfRows))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if (m_NrOfColumns!=matrix.m_NrOfColumns)
        _handleException(13, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    swap=m_pMatrix[rowNr];
    m_pMatrix[rowNr]=matrix.m_pMatrix[matrixRowNr];
    matrix.m_pMatrix[matrixRowNr]=swap;
}

template <typename DataType>
void Matrix<DataType>::swapColumn(int columnNr, Matrix& matrix, int matrixColumnNr)
{
    DataType swap;
    int i;
    if (matrix.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if ((columnNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if ((columnNr>=m_NrOfColumns) || (matrixColumnNr>=matrix.m_NrOfColumns))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if (m_NrOfRows!=matrix.m_NrOfRows)
        _handleException(12, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    for(i=0; i<m_NrOfRows; i++) {
        swap=m_pMatrix[i][columnNr];
        m_pMatrix[i][columnNr]=matrix.m_pMatrix[i][matrixColumnNr];
        matrix.m_pMatrix[i][matrixColumnNr]=swap;
    }
}

template <typename DataType>
void Matrix<DataType>::swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr)
{
    DataType swap;
    int k;
    if ((rowNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (m_NrOfColumns!=matrix.m_NrOfRows)
        _handleException(11, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (rowNr>=m_NrOfRows)
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (matrixColumnNr>=matrix.m_NrOfColumns)
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (m_pMatrix==matrix.m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    for (k=0; k<m_NrOfColumns; k++) {
        swap=m_pMatrix[rowNr][k];
        m_pMatrix[rowNr][k]=matrix.m_pMatrix[k][matrixColumnNr];
        matrix.m_pMatrix[k][matrixColumnNr]=swap;
    }
}

template <typename DataType>
void Matrix<DataType>::swapItem(int firstRowNr, int firstColumnNr, int secondRowNr, int secondColumnNr)
{
    if ((firstRowNr<0) || (firstColumnNr<0) || (secondRowNr<0) || (secondColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    if ((firstRowNr>=m_NrOfRows) || (firstColumnNr>=m_NrOfColumns) || (secondRowNr>=m_NrOfRows) || (secondColumnNr>=m_NrOfColumns))
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    DataType swap;
    swap=m_pMatrix[firstRowNr][firstColumnNr];
    m_pMatrix[firstRowNr][firstColumnNr]=m_pMatrix[secondRowNr][secondColumnNr];
    m_pMatrix[secondRowNr][secondColumnNr]=swap;
}

template <typename DataType>
void Matrix<DataType>::swapRow(int firstRowNr, int secondRowNr)
{
    DataType *swap;
    if ((firstRowNr<0) || (secondRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    if ((firstRowNr>=m_NrOfRows) || (secondRowNr>=m_NrOfRows))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    swap=m_pMatrix[firstRowNr];
    m_pMatrix[firstRowNr]=m_pMatrix[secondRowNr];
    m_pMatrix[secondRowNr]=swap;
}

template <typename DataType>
void Matrix<DataType>::swapColumn(int firstColumnNr, int secondColumnNr)
{
    DataType swap;
    int i;
    if ((firstColumnNr<0) || (secondColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    if ((firstColumnNr>=m_NrOfColumns) || (secondColumnNr>=m_NrOfColumns))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    for(i=0; i<m_NrOfRows; i++) {
        swap=m_pMatrix[i][firstColumnNr];
        m_pMatrix[i][firstColumnNr]=m_pMatrix[i][secondColumnNr];
        m_pMatrix[i][secondColumnNr]=swap;
    }
}

template<typename DataType>
void Matrix<DataType>::swapRowColumn(int rowColumnNr)
{
    DataType swap;
    int k;
    if (m_NrOfRows!=m_NrOfColumns)
        _handleException(1,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    if (rowColumnNr<0)
        _handleException(16,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    if (rowColumnNr>=m_NrOfRows)
        _handleException(18,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    for (k=0; k<m_NrOfRows; k++) {
        swap=m_pMatrix[rowColumnNr][k];
        m_pMatrix[rowColumnNr][k]=m_pMatrix[k][rowColumnNr];
        m_pMatrix[k][rowColumnNr]=swap;
    }
}

template<typename DataType>
void Matrix<DataType>::swapWithMatrix(Matrix<DataType> &m)
{
    DataType** temp;
    int mtemp;
    bool br;
    mtemp=m_NrOfRows; m_NrOfRows=m.m_NrOfRows; m.m_NrOfRows=mtemp;
    mtemp=m_NrOfColumns; m_NrOfColumns=m.m_NrOfColumns; m.m_NrOfColumns=mtemp;
    mtemp=m_MatrixEntryMode; m_MatrixEntryMode=m.m_MatrixEntryMode; m.m_MatrixEntryMode=mtemp;
    mtemp=m_MatrixPrintMode; m_MatrixPrintMode=m.m_MatrixPrintMode; m.m_MatrixPrintMode=mtemp;
    mtemp=m_PosX; m_PosX=m.m_PosX; m.m_PosX=mtemp;
    mtemp=m_PosY; m_PosY=m.m_PosY; m.m_PosY=mtemp;
    br=m_WrapMatrixByRow; m_WrapMatrixByRow=m.m_WrapMatrixByRow; m.m_WrapMatrixByRow=br;
    temp=m_pMatrix; m_pMatrix=m.m_pMatrix; m.m_pMatrix=temp;
}

template <typename DataType>
void Matrix<DataType>:: sortLineColumn(int lineColumnNr, int mode)
{
    if (mode<0 || mode>3)
        _handleException(21, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
    switch (mode) {
        case 0:
            if (lineColumnNr<0 || lineColumnNr>m_NrOfRows-1)
                _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,m_NrOfColumns-1,0, lineColumnNr);
            return;
        case 1:
            if (lineColumnNr<0 || lineColumnNr>m_NrOfRows-1)
                _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,m_NrOfColumns-1,1, lineColumnNr);
            return;
        case 2:
            if (lineColumnNr<0 || lineColumnNr>m_NrOfColumns-1)
                _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,m_NrOfRows-1,2, lineColumnNr);
            return;
        case 3:
            if (lineColumnNr<0 || lineColumnNr>m_NrOfColumns-1)
                _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,m_NrOfRows-1,3, lineColumnNr);
    }
}

template <typename DataType>
void Matrix<DataType>::sortAllElements(int mode)
{
    if (mode<0 || mode>3)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::sort_matr(int mode)");
    switch (mode) {
        case 0:
            _quickSort(0,m_NrOfRows*m_NrOfColumns-1,0);
            return;
        case 1:
            _quickSort(0,m_NrOfRows*m_NrOfColumns-1,1);
            return;
        case 2:
            _quickSort(0,m_NrOfRows*m_NrOfColumns-1,2);
            return;
        case 3:
            _quickSort(0,m_NrOfRows*m_NrOfColumns-1,3);
    }
}

template <typename DataType>
void Matrix<DataType>::insertRow (int m)
{
    int i;
    DataType **insert_ptr;
    if (m<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
    if (m>m_NrOfRows)
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
    insert_ptr=new DataType*[m_NrOfRows+1];
    for (i=0; i<m; i++)
        insert_ptr[i]=m_pMatrix[i];
    insert_ptr[m]=new DataType[m_NrOfColumns];
    for (i=0; i<m_NrOfColumns; i++)
        insert_ptr[m][i]=0;
    for (i=m; i<m_NrOfRows; i++)
        insert_ptr[i+1]=m_pMatrix[i];
    delete []m_pMatrix;
    m_pMatrix=insert_ptr;
    m_NrOfRows++;
}

template <typename DataType>
void Matrix<DataType>::deleteRow (int m)
{
    int i;
    DataType **insert_ptr;
    if (m_NrOfRows==1)
        _handleException(15, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    if (m>=m_NrOfRows)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    if (m<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    insert_ptr=new DataType*[m_NrOfRows-1];
    for (i=0; i<m; i++)
        insert_ptr[i]=m_pMatrix[i];
    delete []m_pMatrix[m];
    for (i=m; i<m_NrOfRows-1; i++)
        insert_ptr[i]=m_pMatrix[i+1];
    delete []m_pMatrix;
    m_pMatrix=insert_ptr;
    m_NrOfRows--;
}

template <typename DataType>
void Matrix<DataType>::insertColumn(int n)
{
    int i,j;
    DataType **insert_ptr;
    if (n<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
    if (n>m_NrOfColumns)
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
    insert_ptr = new DataType*[m_NrOfRows];
    for (i=0; i<m_NrOfRows; i++)
        insert_ptr[i]=new DataType[m_NrOfColumns+1];
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<n; j++)
            insert_ptr[i][j]=m_pMatrix[i][j];
    for(i=0; i<m_NrOfRows; i++)
        for(j=n+1; j<m_NrOfColumns+1; j++)
            insert_ptr[i][j]=m_pMatrix[i][j-1];
    for (i=0; i<m_NrOfRows; i++)
        insert_ptr[i][n]=0;
    for (i=0; i<m_NrOfRows; i++)
        delete []m_pMatrix[i];
    delete []m_pMatrix;
    m_pMatrix=insert_ptr;
    m_NrOfColumns++;
}

template <typename DataType>
void Matrix<DataType>::deleteColumn(int n)
{
    int i,j;
    if (m_NrOfColumns==1)
        _handleException(14, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    if (n<0)
        _handleException (16, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    if (n>=m_NrOfColumns)
        _handleException (7, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    DataType **insert_ptr;
    insert_ptr = new DataType*[m_NrOfRows];
    for (i=0; i<m_NrOfRows; i++)
        insert_ptr[i]=new DataType[m_NrOfColumns-1];
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<n; j++)
            insert_ptr[i][j]=m_pMatrix[i][j];
    for(i=0; i<m_NrOfRows; i++)
        for(j=n; j<m_NrOfColumns-1; j++)
            insert_ptr[i][j]=m_pMatrix[i][j+1];
    for (i=0; i<m_NrOfRows; i++)
        delete []m_pMatrix[i];
    delete []m_pMatrix;
    m_pMatrix=insert_ptr;
    m_NrOfColumns--;
}

template<typename DataType>
void Matrix<DataType>::addRowToColumn(int rowNr, DataType& coeff, Matrix& src, int srcColumnNr, DataType& srcCoeff, Matrix& dest,int destColumnNr)
{
    int i;
    if ((rowNr<0) || (srcColumnNr<0) || (destColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (rowNr>=m_NrOfRows)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (srcColumnNr>=src.m_NrOfColumns)
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.m_WrapMatrixByRow) {
        if (destColumnNr>=dest.m_NrOfRows)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[destColumnNr][i]=coeff*m_pMatrix[rowNr][i]+srcCoeff*src.m_pMatrix[i][srcColumnNr];
    }
    else {
        if (destColumnNr>=dest.m_NrOfColumns)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[i][destColumnNr]=coeff*m_pMatrix[rowNr][i]+srcCoeff*src.m_pMatrix[i][srcColumnNr];
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToRow(int columnNr, DataType& coeff, Matrix& src, int srcRowNr, DataType& srcCoeff, Matrix& dest, int destRowNr)
{
    int i;
    if ((columnNr<0) || (srcRowNr<0) || (destRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (columnNr>=m_NrOfColumns)
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (srcRowNr>=src.m_NrOfRows)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.m_WrapMatrixByRow) {
        if (destRowNr>=dest.m_NrOfRows)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[destRowNr][i]=coeff*m_pMatrix[i][columnNr]+srcCoeff*src.m_pMatrix[srcRowNr][i];
    }
    else {
        if (destRowNr>=dest.m_NrOfColumns)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[i][destRowNr]=coeff*m_pMatrix[i][columnNr]+srcCoeff*src.m_pMatrix[srcRowNr][i];
    }
}

template<typename DataType>
void Matrix<DataType>::addRowToRow(int rowNr, DataType& coeff, Matrix &src, int srcRowNr, DataType& srcCoeff, Matrix& dest, int destRowNr)
{
    int i;
    if ((rowNr<0) || (srcRowNr<0) || (destRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if ((rowNr>=m_NrOfRows) || (srcRowNr>=src.m_NrOfRows))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.m_WrapMatrixByRow) {
        if (destRowNr>=dest.m_NrOfRows)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[destRowNr][i]=coeff*m_pMatrix[rowNr][i]+srcCoeff*src.m_pMatrix[srcRowNr][i];
    }
    else {
        if (destRowNr>=dest.m_NrOfColumns)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[i][destRowNr]=coeff*m_pMatrix[rowNr][i]+srcCoeff*src.m_pMatrix[srcRowNr][i];
    }
}

template<typename DataType>
void Matrix<DataType>::addColumnToColumn(int columnNr, DataType& coeff, Matrix& src, int srcColumnNr, DataType& srcCoeff, Matrix& dest, int destColumnNr)
{
    int i;
    if ((columnNr<0) || (srcColumnNr<0) || (destColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if ((columnNr>=m_NrOfColumns) || (srcColumnNr>=src.m_NrOfColumns))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.m_WrapMatrixByRow) {
        if (destColumnNr>=dest.m_NrOfRows)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[destColumnNr][i]=coeff*m_pMatrix[i][columnNr]+srcCoeff*src.m_pMatrix[i][srcColumnNr];
    }
    else {
        if (destColumnNr>=dest.m_NrOfColumns)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<m_NrOfRows; i++)
            dest.m_pMatrix[i][destColumnNr]=coeff*m_pMatrix[i][columnNr]+srcCoeff*src.m_pMatrix[i][srcColumnNr];
    }
}

template <typename DataType>
void Matrix<DataType>:: copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns)
{



    if (src.m_pMatrix==m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    if ((nrOfRows<0) || (nrOfColumns<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    if ((src.m_PosX+nrOfRows>src.m_NrOfRows) || (src.m_PosY+nrOfColumns>src.m_NrOfColumns) || (m_PosX+nrOfRows>m_NrOfRows) || (m_PosY+nrOfColumns>m_NrOfColumns))
        _handleException(18, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    for (int i=0; i<nrOfRows; i++)
        for (int j=0; j<nrOfColumns; j++)
            m_pMatrix[m_PosX+i][m_PosY+j]=src.m_pMatrix[src.m_PosX+i][src.m_PosY+j];
}

template <typename DataType>
void Matrix<DataType>::copy(DataType** src, int nrOfRows, int nrOfColumns)
{
    int i,j;
    if (src==0)
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    if ((nrOfRows<=0)||(nrOfColumns<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=src[i][j];
}

template <typename DataType>
void Matrix<DataType>::copy(DataType* src, int nrOfRows, int nrOfColumns)
{
    int i,j;
    if (src==0)
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    if ((nrOfRows<=0)||(nrOfColumns<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=*(src++);
}

template <typename DataType>
void Matrix<DataType>::concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    Matrix m3;
    if (m_WrapMatrixByRow && (firstSrcMatrix.m_NrOfColumns!=secondSrcMatrix.m_NrOfColumns))
        _handleException(13,"template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
    if ((!m_WrapMatrixByRow) && (firstSrcMatrix.m_NrOfRows!=secondSrcMatrix.m_NrOfRows))
        _handleException(12, "template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
    if ((firstSrcMatrix.m_pMatrix==m_pMatrix) || (secondSrcMatrix.m_pMatrix==m_pMatrix)) {
        m3.m_pMatrix=m_pMatrix;
        m3.m_NrOfRows=m_NrOfRows;
        m3.m_NrOfColumns=m_NrOfColumns;
        _allocMemory(1,1);
    }
    if ((firstSrcMatrix.m_pMatrix==m_pMatrix) && (secondSrcMatrix.m_pMatrix!=m_pMatrix)) { _concatenate(m3, secondSrcMatrix); return; }
    if ((firstSrcMatrix.m_pMatrix!=m_pMatrix) && (secondSrcMatrix.m_pMatrix==m_pMatrix)) { _concatenate(firstSrcMatrix, m3); return; }
    if ((firstSrcMatrix.m_pMatrix==m_pMatrix) && (secondSrcMatrix.m_pMatrix==m_pMatrix)) { _concatenate(m3, m3); return; }
    _concatenate(firstSrcMatrix, secondSrcMatrix);
}

template <typename DataType>
void Matrix<DataType>::split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix,int splitRowColumnNr)
{
    Matrix m3;
    if (firstDestMatrix.m_pMatrix==secondDestMatrix.m_pMatrix)
        _handleException(24, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    if (splitRowColumnNr<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    if (m_WrapMatrixByRow) {
        if (splitRowColumnNr>m_NrOfRows)
            _handleException(4, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        if ((splitRowColumnNr==0)||(splitRowColumnNr==m_NrOfRows))
            _handleException(19, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }
    else {
        if (splitRowColumnNr>m_NrOfColumns)
            _handleException(7, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        if ((splitRowColumnNr==0)||(splitRowColumnNr==m_NrOfColumns))
            _handleException(20, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }
    if ((firstDestMatrix.m_pMatrix==m_pMatrix) || (secondDestMatrix.m_pMatrix==m_pMatrix)) {
        m3.m_pMatrix=m_pMatrix;
        m3.m_NrOfRows=m_NrOfRows;
        m3.m_NrOfColumns=m_NrOfColumns;
        m3.m_WrapMatrixByRow=m_WrapMatrixByRow;
        _allocMemory(1,1);
    }
    if ((firstDestMatrix.m_pMatrix==m_pMatrix) && (secondDestMatrix.m_pMatrix!=m_pMatrix)) { m3._split(*this, secondDestMatrix, splitRowColumnNr); return; }
    if ((firstDestMatrix.m_pMatrix!=m_pMatrix) && (secondDestMatrix.m_pMatrix==m_pMatrix)) { m3._split(firstDestMatrix, *this, splitRowColumnNr); return; }
    _split(firstDestMatrix, secondDestMatrix, splitRowColumnNr);
}

template <typename DataType>
void Matrix<DataType>::applyCoefficientsToRow (const Matrix &coeff, Matrix &src, bool multiply)
{
    int i,j;
    if (m_pMatrix==coeff.m_pMatrix)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.m_NrOfRows!=src.m_NrOfRows)
        _handleException(12,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((m_NrOfRows!=src.m_NrOfRows)||(m_NrOfColumns!=src.m_NrOfColumns))
        resizeNoInit(src.m_NrOfRows, src.m_NrOfColumns);
    if (multiply==true)
        for (i=0; i<m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=src.m_pMatrix[i][j]*coeff.m_pMatrix[i][0];
    else {
        for (i=0; i<m_NrOfRows; i++)
            if (coeff.m_pMatrix[i][0]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
        for (i=0; i<m_NrOfRows; i++)
            for (j=0; j<m_NrOfColumns; j++)
                m_pMatrix[i][j]=src.m_pMatrix[i][j]/coeff.m_pMatrix[i][0];
    }
}

template <typename DataType>
void Matrix<DataType>::applyCoefficientsToColumn (const Matrix &coeff, Matrix &src, bool multiply)
{
    int i, j;
    if (coeff.m_pMatrix==m_pMatrix)
        _handleException(25,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.m_NrOfColumns!=src.m_NrOfColumns)
        _handleException(13,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((m_NrOfRows!=src.m_NrOfRows)||(m_NrOfColumns!=src.m_NrOfColumns))
        resizeNoInit(src.m_NrOfRows, src.m_NrOfColumns);
    if (multiply==true)
        for (j=0; j<m_NrOfColumns; j++)
            for (i=0; i<m_NrOfRows; i++)
                m_pMatrix[i][j]=src.m_pMatrix[i][j]*coeff.m_pMatrix[0][j];
    else {
        for (j=0; j<m_NrOfColumns; j++)
            if (coeff.m_pMatrix[0][j]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
        for (j=0; j<m_NrOfColumns; j++)
            for (i=0; i<m_NrOfRows; i++)
                m_pMatrix[i][j]=src.m_pMatrix[i][j]/coeff.m_pMatrix[0][j];
    }
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator+ (const Matrix<DataType>& matrix)
{
    int i,j;
    if ((m_NrOfRows!=matrix.m_NrOfRows) || (m_NrOfColumns!=matrix.m_NrOfColumns))
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator+ (const Matrix<DataType> &m)");
    Matrix a(m_NrOfRows,m_NrOfColumns);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            a.m_pMatrix[i][j]=m_pMatrix[i][j]+matrix.m_pMatrix[i][j];
    return a;
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator- (const Matrix<DataType>& matrix)
{
    int i,j;
    if ((m_NrOfRows!=matrix.m_NrOfRows) || (m_NrOfColumns!=matrix.m_NrOfColumns))
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator- (const Matrix<DataType> &m)");
    Matrix a(m_NrOfRows,m_NrOfColumns);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            a.m_pMatrix[i][j]=m_pMatrix[i][j]-matrix.m_pMatrix[i][j];
    return a;
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
    int i,j,k;
    if (m_NrOfColumns!=matrix.m_NrOfRows)
        _handleException(11, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator* (const Matrix<DataType> &m)");
    Matrix a(m_NrOfRows,matrix.m_NrOfColumns);
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<matrix.m_NrOfColumns; j++)
            for (k=0; k<m_NrOfColumns; k++)
                a.m_pMatrix[i][j]=a.m_pMatrix[i][j]+m_pMatrix[i][k]*matrix.m_pMatrix[k][j];
    return a;
}

template <typename DataType>
Matrix<DataType> Matrix<DataType>::operator^ (int exp)
{
    Matrix a;
    if (m_NrOfRows!=m_NrOfColumns)
        _handleException(1, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    if (exp<0)
        _handleException(16, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    if (exp==0) {
        a.transformToUnitMatrix(m_NrOfRows);
        return a;
    }

    a=(*this);
    return a._power(exp);
}

template <typename DataType>
Matrix<DataType>& Matrix<DataType>:: operator= (const Matrix<DataType>& matrix)
{
    if (matrix.m_pMatrix==m_pMatrix) goto is_current_matrix;
    if ((m_NrOfRows==matrix.m_NrOfRows)&&(m_NrOfColumns==matrix.m_NrOfColumns)) goto is_equal;
    _deallocMemory();
    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);
is_equal:
    for (int i=0; i<m_NrOfRows; i++)
        for (int j=0; j<m_NrOfColumns; j++)
            m_pMatrix[i][j]=matrix.m_pMatrix[i][j];
    m_PosX=matrix.m_PosX;
    m_PosY=matrix.m_PosY;
    m_WrapMatrixByRow=matrix.m_WrapMatrixByRow;
is_current_matrix:
    return *this;
}

template <typename DataType>
bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix)
{
    int i,j;
    if (matrix.m_pMatrix==m_pMatrix)
        return true;
    if ((m_NrOfRows!=matrix.m_NrOfRows) || (m_NrOfColumns!=matrix.m_NrOfColumns))
        _handleException(10, "template <typename DataType> bool Matrix<DataType>::operator==(const Matrix<DataType> &m)");
    for (i=0; i<m_NrOfRows; i++)
        for (j=0; j<m_NrOfColumns; j++)
            if (m_pMatrix[i][j]!=matrix.m_pMatrix[i][j])
                return false;
    return true;
}

template<typename DataType>
bool Matrix<DataType>::operator !=(Matrix<DataType> &matrix)
{
    if(m_pMatrix==matrix.m_pMatrix) return false; if (rank()!=matrix.rank()) return true; return false;
}

template<typename DataType>
bool Matrix<DataType>::operator <(Matrix<DataType> &matrix)
{
    if (m_pMatrix==matrix.m_pMatrix) return false; if (rank()<matrix.rank()) return true; return false;
}

template<typename DataType>
bool Matrix<DataType>::operator <=(Matrix<DataType> &matrix)
{
    if (m_pMatrix==matrix.m_pMatrix) return true; if (rank()<=matrix.rank()) return true; return false;
}

template<typename DataType>
bool Matrix<DataType>::operator >(Matrix<DataType> &matrix)
{
    if (m_pMatrix==matrix.m_pMatrix) return false; if (rank()>matrix.rank()) return true; return false;
}

template<typename DataType>
bool Matrix<DataType>::operator >=(Matrix<DataType> &matrix)
{
    if (m_pMatrix==matrix.m_pMatrix) return true; if (rank()>=matrix.rank()) return true; return false;
}

template<typename DataType>
ostream& operator<<(ostream &out, Matrix<DataType> &matrix)
{
    if(((matrix.m_MatrixPrintMode==4) || (matrix.m_MatrixPrintMode==5))&&(matrix.m_NrOfRows!=matrix.m_NrOfColumns))
        Matrix<DataType>::_handleException(1, "friend ostream &operator<<(ostream &os, Matrix &m)");
    matrix._writeMatrix(out, matrix.m_MatrixPrintMode);
    return out;
}

template<typename DataType>
istream& operator>>(istream &in, Matrix<DataType> &matrix)
{
    if(((matrix.m_MatrixEntryMode==4) || (matrix.m_MatrixEntryMode==5) || (matrix.m_MatrixEntryMode==10) || (matrix.m_MatrixEntryMode==11) || (matrix.m_MatrixEntryMode==16) || (matrix.m_MatrixEntryMode==17))&&(matrix.m_NrOfRows!=matrix.m_NrOfColumns))
        Matrix<DataType>::_handleException(1, "friend istream &operator>> (istream &is, Matrix &m)");
    matrix._readMatrix(in, matrix.m_MatrixEntryMode);
    return in;
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](int index)
{
    if (index<0) _handleException(16, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)") ;
    if (index>=m_NrOfRows*m_NrOfColumns) _handleException(18, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
    if (m_WrapMatrixByRow) return _getItemForLineWrap(index);
    return _getItemForColumnWrap(index);
}

template <typename DataType>
DataType Matrix<DataType>::determinant()
{
    int i,j,k,l,temp=1;
    if (m_NrOfRows!=m_NrOfColumns)
        _handleException(1, "template <typename DataType> DataType Matrix<DataType>::det()");
    Matrix m = *this;
    DataType det=1;
    int semn=1;
    for (k=0; k<m_NrOfRows-1; k++) {
        if (m.m_pMatrix[k][k]==0) {
            for (l=k+1; l<m_NrOfRows; l++)
                if (m.m_pMatrix[l][k]!=0) {
                    m.swapRow(k,l);
                    semn = semn*(-1);
                    goto Prelucrare;
                }
            return 0;
        }
Prelucrare:
        for (j=k+1; j<m_NrOfColumns; j++)
            for (i=k+1; i<m_NrOfRows; i++) {
                m.m_pMatrix[i][j]=m.m_pMatrix[i][j]*(m.m_pMatrix[k][k])-m.m_pMatrix[k][j]*(m.m_pMatrix[i][k]);
                temp=temp*(m.m_pMatrix[k][k]*m.m_pMatrix[i][k]);
            }
    }
    for (k=0; k<m_NrOfRows; k++)
        det=det*m.m_pMatrix[k][k];
    return (det/temp)*semn;
}

template<typename DataType>
int Matrix<DataType>::rank()
{
    int i,j;
    int rang=0;
    Matrix p;
    if (m_NrOfRows>m_NrOfColumns)
        getTransposedMatrix(p);
    else p=*this;
    p.m_PosX=0;
    p.m_PosY=0;
    while (p.m_PosX<p.m_NrOfRows-1) {
        if (p.m_pMatrix[p.m_PosX][p.m_PosY]==0) {
            for (i=p.m_PosX+1; i<p.m_NrOfRows; i++)
                if (p.m_pMatrix[i][p.m_PosY]!=0) {
                    rang++;
                    p.swapRow(i,p.m_PosX);
                    goto Prelucrare;
                }
            for (j=p.m_PosY+1; j<p.m_NrOfColumns; j++)
                if (p.m_pMatrix[p.m_PosX][j]!=0) {
                    rang++;
                    p.swapColumn(j,p.m_PosY);
                    goto Prelucrare;
                }
        }
        else
            rang++;
Prelucrare:
    for (i=p.m_PosX+1; i<p.m_NrOfRows; i++)
        for (j=p.m_PosY+1; j<p.m_NrOfColumns; j++)
            p.m_pMatrix[i][j]=(p.m_pMatrix[i][j])*(p.m_pMatrix[p.m_PosX][p.m_PosY]) - (p.m_pMatrix[p.m_PosX][j])*(p.m_pMatrix[i][p.m_PosY]);
    (p.m_PosX)++;
    (p.m_PosY)++;
    }
    for (j=p.m_PosY; j<p.m_NrOfColumns; j++)
        if (p.m_pMatrix[p.m_PosX][j]!=0) {
            rang++;
            break;
        }
    return rang;
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




