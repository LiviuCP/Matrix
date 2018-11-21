#include "matrix.h"

template<typename DataType> int Matrix<DataType>::f_x=0;
template<typename DataType> int Matrix<DataType>::f_y=0;

template <typename DataType> Matrix<DataType>::Matrix() {
    bool by_row=true;
    line=1;
    column=1;
    mprint=0;
    entdat=0;
    ptr=new DataType*[1];
    ptr[0]=new DataType;
    ptr[0][0]=0;
    resetCurrentPos();
}

template <typename DataType> Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns) {
    if (nrOfRows<=0 || nrOfColumns<=0) _handleException(3, "template <typename DataType> Matrix<DataType>::Matrix(int m, int n)");
    by_row=true;
    line=nrOfRows;
    column=nrOfColumns;
    entdat=0;
    mprint=0;
    resetCurrentPos();
    _allocMemory(nrOfRows,nrOfColumns);
    setItemsToZero();
}

template <typename DataType> Matrix<DataType>::Matrix(int nrOfRowsColumns) {
    if (nrOfRowsColumns<=0) _handleException(3, "template <typename DataType> Matrix<DataType>::Matrix(int n)");
    bool by_row=true;
    line = nrOfRowsColumns;
    column = nrOfRowsColumns;
    mprint=0;
    entdat=0;
    resetCurrentPos();
    _allocMemory(line,column);
    setItemsToZero();
    for (int i=0; i<nrOfRowsColumns; i++)
        ptr[i][i]=1;
}

template <typename DataType> Matrix<DataType>::Matrix(DataType** matrixPtr, int nrOfRows, int nrOfColumns) {
    int i,j;
    if (matrixPtr==0)
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    if ((nrOfRows<=0) || (nrOfColumns<=0))
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType** m, int ln, int cl)");
    by_row=true;
    mprint=0;
    entdat=0;
    resetCurrentPos();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=matrixPtr[i][j];
}

template <typename DataType> Matrix<DataType>::Matrix(DataType* matrixPtr, int nrOfRows, int nrOfColumns) {
    int i,j;
    if (matrixPtr==0)
        _handleException(22,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    if ((nrOfRows<=0) || (nrOfColumns<=0))
        _handleException(3,"template <typename DataType> Matrix<DataType>::Matrix(DataType* m, int ln, int cl)");
    by_row=true;
    line=nrOfRows;
    column=nrOfColumns;
    mprint=0;
    entdat=0;
    resetCurrentPos();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=*(matrixPtr++);
}

template<typename DataType> Matrix<DataType>::Matrix(int nrOfRows, int nrOfColumns, istream &in) {
    int i;
    by_row=true;
    mprint=0;
    entdat=0;
    line=nrOfRows; column=nrOfColumns;
    _allocMemory(nrOfRows,nrOfColumns);
    _readDiscard(in);
    pos_x=0;
    for (i=0; i<line; i++) {
        _readTextLine(in);
        pos_x++;
        f_x++;
    }
    pos_x=0;
    pos_y=0;
}

template <typename DataType> Matrix<DataType>::Matrix(const Matrix<DataType> &matrix) {
    _allocMemory(matrix.line, matrix.column);
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=matrix.ptr[i][j];
    pos_x=matrix.pos_x;
    pos_y=matrix.pos_y;
    by_row=matrix.by_row;
    entdat=matrix.entdat;
    mprint=matrix.mprint;
}

template<typename DataType> DataType& Matrix<DataType>:: get(int i,int j) {
    if ((i<0) || (j<0)) _handleException(16, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
    if ((i>=line) || (j>=column)) _handleException(18, "template<typename DataType> DataType& Matrix<DataType>::get(int i,int j)");
    return ptr[i][j];
}

template <typename DataType> void Matrix<DataType>::setItemsToZero() {
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=0;
}

template <typename DataType> void Matrix<DataType>::transformToUnitMatrix(int nrOfRowsColumns) {
    if (nrOfRowsColumns<=0) _handleException(3,"template <typename DataType> void Matrix<DataType>::unit(int m)");
    _deallocMemory();
    _allocMemory(nrOfRowsColumns,nrOfRowsColumns);
    setItemsToZero();
    for (int i=0; i<nrOfRowsColumns; i++)
        ptr[i][i]=1;
}

template <typename DataType> void Matrix<DataType>::transformToZeroMatrix(int nrOfRows, int nrOfColumns) {
    if (nrOfRows<=0 || nrOfColumns<=0)
        _handleException(3, "template <typename DataType> void Matrix<DataType>::null_matrix(int m, int n)");
    _deallocMemory();
    _allocMemory(nrOfRows,nrOfColumns);
    setItemsToZero();
}

template <typename DataType> void Matrix<DataType>::resize(int m, int n) {
    int i,j;
    DataType **temp;
    if ((m==line)&&(n==column)) return;
    if ((m<=0) || (n<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::resize_m(int m, int n)");
    Matrix a;
    temp=a.ptr;
    a.ptr=ptr;
    ptr=temp;
    a.line=line;
    a.column=column;
    delete ptr[0];
    delete ptr;
    _allocMemory(m,n);
    if ((m<a.line)&&(n<a.column)) {
        for (i=0; i<m; i++)
            for (j=0; j<n; j++)
                ptr[i][j]=a.ptr[i][j];
        return;
    }
    if ((m<=a.line)&&(n>=a.column)) {
        for (i=0; i<m; i++)
            for (j=0; j<a.column; j++)
                ptr[i][j]=a.ptr[i][j];
        for (i=0; i<m; i++)
            for (j=a.column; j<n; j++)
                ptr[i][j]=0;
        return;
    }
    if ((m>=a.line) && (n<=a.column)) {
        for (i=0; i<a.line; i++)
            for (j=0; j<n; j++)
                ptr[i][j]=a.ptr[i][j];
        for (i=a.line; i<m; i++)
            for (j=0; j<n; j++)
                ptr[i][j]=0;
        return;
    }

    for (i=0; i<a.line; i++)
        for (j=0; j<a.column; j++)
            ptr[i][j]=a.ptr[i][j];
    for (i=0; i<m; i++)
        for (j=a.column; j<n; j++)
            ptr[i][j]=0;
    for (i=a.line; i<m; i++)
        for (j=0; j<n; j++)
            ptr[i][j]=0;
    for (i=a.line; i<m; i++)
        for (j=a.column; j<n; j++)
            ptr[i][j]=0;
}
template <typename DataType> void Matrix<DataType>::swapItem(int rowNr, int columnNr, Matrix& matrix, int matrixRowNr, int matrixColumnNr) {
    DataType swap;
    if (matrix.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((rowNr<0) || (columnNr<0) || (matrixRowNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((rowNr>=line) || (columnNr>=column) || (matrixRowNr>=matrix.line) || (matrixColumnNr>=matrix.column))
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    swap=ptr[rowNr][columnNr];
    ptr[rowNr][columnNr]=matrix.ptr[matrixRowNr][matrixColumnNr];
    matrix.ptr[matrixRowNr][matrixColumnNr]=swap;
}

template <typename DataType> void Matrix<DataType>::swapRow(int rowNr, Matrix& matrix, int matrixRowNr) {
    DataType *swap;
    if (matrix.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if ((rowNr<0) || (matrixRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if ((rowNr>=line) || (matrixRowNr>=matrix.line))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    if (column!=matrix.column)
        _handleException(13, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, Matrix &m2, int r2)");
    swap=ptr[rowNr];
    ptr[rowNr]=matrix.ptr[matrixRowNr];
    matrix.ptr[matrixRowNr]=swap;
}

template <typename DataType> void Matrix<DataType>::swapColumn(int columnNr, Matrix& matrix, int matrixColumnNr) {
    DataType swap;
    int i;
    if (matrix.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if ((columnNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if ((columnNr>=column) || (matrixColumnNr>=matrix.column))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    if (line!=matrix.line)
        _handleException(12, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, Matrix &m2, int c2)");
    for(i=0; i<line; i++) {
        swap=ptr[i][columnNr];
        ptr[i][columnNr]=matrix.ptr[i][matrixColumnNr];
        matrix.ptr[i][matrixColumnNr]=swap;
    }
}

template <typename DataType> void Matrix<DataType>::swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr) {
    DataType swap;
    int k;
    if ((rowNr<0) || (matrixColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (column!=matrix.line)
        _handleException(11, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (rowNr>=line)
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (matrixColumnNr>=matrix.column)
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    if (ptr==matrix.ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::swap_rc(int r1, Matrix<DataType> &m2, int c2)");
    for (k=0; k<column; k++) {
        swap=ptr[rowNr][k];
        ptr[rowNr][k]=matrix.ptr[k][matrixColumnNr];
        matrix.ptr[k][matrixColumnNr]=swap;
    }
}

template <typename DataType> void Matrix<DataType>::swapItem(int firstRowNr, int firstColumnNr, int secondRowNr, int secondColumnNr) {
    if ((firstRowNr<0) || (firstColumnNr<0) || (secondRowNr<0) || (secondColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    if ((firstRowNr>=line) || (firstColumnNr>=column) || (secondRowNr>=line) || (secondColumnNr>=column))
        _handleException(18, "template <typename DataType> void Matrix<DataType>::swap_i(int r1, int c1, int r2, int c2)");
    DataType swap;
    swap=ptr[firstRowNr][firstColumnNr];
    ptr[firstRowNr][firstColumnNr]=ptr[secondRowNr][secondColumnNr];
    ptr[secondRowNr][secondColumnNr]=swap;
}

template <typename DataType> void Matrix<DataType>::swapRow(int firstRowNr, int secondRowNr) {
    DataType *swap;
    if ((firstRowNr<0) || (secondRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    if ((firstRowNr>=line) || (secondRowNr>=line))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::swap_r(int r1, int r2)");
    swap=ptr[firstRowNr];
    ptr[firstRowNr]=ptr[secondRowNr];
    ptr[secondRowNr]=swap;
}

template <typename DataType> void Matrix<DataType>::swapColumn(int firstColumnNr, int secondColumnNr) {
    DataType swap;
    int i;
    if ((firstColumnNr<0) || (secondColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    if ((firstColumnNr>=column) || (secondColumnNr>=column))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::swap_c(int c1, int c2)");
    for(i=0; i<line; i++) {
        swap=ptr[i][firstColumnNr];
        ptr[i][firstColumnNr]=ptr[i][secondColumnNr];
        ptr[i][secondColumnNr]=swap;
    }
}

template<typename DataType> void Matrix<DataType>::swapRowColumn(int rowColumnNr) {
    DataType swap;
    int k;
    if (line!=column)
        _handleException(1,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    if (rowColumnNr<0)
        _handleException(16,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    if (rowColumnNr>=line)
        _handleException(18,"template<typename DataType> void Matrix<DataType>::swap_rc(int rc1)");
    for (k=0; k<line; k++) {
        swap=ptr[rowColumnNr][k];
        ptr[rowColumnNr][k]=ptr[k][rowColumnNr];
        ptr[k][rowColumnNr]=swap;
    }
}

template<typename DataType> void Matrix<DataType>::swapWithMatrix(Matrix<DataType> &m) {
    DataType** temp;
    int mtemp;
    bool br;
    mtemp=line; line=m.line; m.line=mtemp;
    mtemp=column; column=m.column; m.column=mtemp;
    mtemp=entdat; entdat=m.entdat; m.entdat=mtemp;
    mtemp=mprint; mprint=m.mprint; m.mprint=mtemp;
    mtemp=pos_x; pos_x=m.pos_x; m.pos_x=mtemp;
    mtemp=pos_y; pos_y=m.pos_y; m.pos_y=mtemp;
    br=by_row; by_row=m.by_row; m.by_row=br;
    temp=ptr; ptr=m.ptr; m.ptr=temp;
}

template <typename DataType> void Matrix<DataType>:: sortLineColumn(int lineColumnNr, int mode) {
    if (mode<0 || mode>3)
        _handleException(21, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
    switch (mode) {
        case 0:
            if (lineColumnNr<0 || lineColumnNr>line-1)
                _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,column-1,0, lineColumnNr);
            return;
        case 1:
            if (lineColumnNr<0 || lineColumnNr>line-1)
                _handleException(4, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,column-1,1, lineColumnNr);
            return;
        case 2:
            if (lineColumnNr<0 || lineColumnNr>column-1)
                _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,line-1,2, lineColumnNr);
            return;
        case 3:
            if (lineColumnNr<0 || lineColumnNr>column-1)
                _handleException(7, "template <typename DataType> void Matrix<DataType>:: sort_lc(int pos, int mode)");
            _quickSort(0,line-1,3, lineColumnNr);
    }
}

template <typename DataType> void Matrix<DataType>::sortAllElements(int mode) {
    if (mode<0 || mode>3)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::sort_matr(int mode)");
    switch (mode) {
        case 0:
            _quickSort(0,line*column-1,0);
            return;
        case 1:
            _quickSort(0,line*column-1,1);
            return;
        case 2:
            _quickSort(0,line*column-1,2);
            return;
        case 3:
            _quickSort(0,line*column-1,3);
    }
}

template <typename DataType> void Matrix<DataType>::insertRow (int m) {
    int i;
    DataType **insert_ptr;
    if (m<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
    if (m>line)
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_row (int m)");
    insert_ptr=new DataType*[line+1];
    for (i=0; i<m; i++)
        insert_ptr[i]=ptr[i];
    insert_ptr[m]=new DataType[column];
    for (i=0; i<column; i++)
        insert_ptr[m][i]=0;
    for (i=m; i<line; i++)
        insert_ptr[i+1]=ptr[i];
    delete []ptr;
    ptr=insert_ptr;
    line++;
}

template <typename DataType> void Matrix<DataType>::deleteRow (int m) {
    int i;
    DataType **insert_ptr;
    if (line==1)
        _handleException(15, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    if (m>=line)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    if (m<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::delete_row (int m)");
    insert_ptr=new DataType*[line-1];
    for (i=0; i<m; i++)
        insert_ptr[i]=ptr[i];
    delete []ptr[m];
    for (i=m; i<line-1; i++)
        insert_ptr[i]=ptr[i+1];
    delete []ptr;
    ptr=insert_ptr;
    line--;
}

template <typename DataType> void Matrix<DataType>::insertColumn(int n) {
    int i,j;
    DataType **insert_ptr;
    if (n<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
    if (n>column)
        _handleException(17, "template <typename DataType> void Matrix<DataType>::insert_col(int n)");
    insert_ptr = new DataType*[line];
    for (i=0; i<line; i++)
        insert_ptr[i]=new DataType[column+1];
    for (i=0; i<line; i++)
        for (j=0; j<n; j++)
            insert_ptr[i][j]=ptr[i][j];
    for(i=0; i<line; i++)
        for(j=n+1; j<column+1; j++)
            insert_ptr[i][j]=ptr[i][j-1];
    for (i=0; i<line; i++)
        insert_ptr[i][n]=0;
    for (i=0; i<line; i++)
        delete []ptr[i];
    delete []ptr;
    ptr=insert_ptr;
    column++;
}

template <typename DataType> void Matrix<DataType>::deleteColumn(int n) {
    int i,j;
    if (column==1)
        _handleException(14, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    if (n<0)
        _handleException (16, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    if (n>=column)
        _handleException (7, "template <typename DataType> void Matrix<DataType>::delete_col(int n)");
    DataType **insert_ptr;
    insert_ptr = new DataType*[line];
    for (i=0; i<line; i++)
        insert_ptr[i]=new DataType[column-1];
    for (i=0; i<line; i++)
        for (j=0; j<n; j++)
            insert_ptr[i][j]=ptr[i][j];
    for(i=0; i<line; i++)
        for(j=n; j<column-1; j++)
            insert_ptr[i][j]=ptr[i][j+1];
    for (i=0; i<line; i++)
        delete []ptr[i];
    delete []ptr;
    ptr=insert_ptr;
    column--;
}

template<typename DataType> void Matrix<DataType>::addRowToColumn(int rowNr, DataType& coeff, Matrix& src, int srcColumnNr, DataType& srcCoeff, Matrix& dest,int destColumnNr) {
    int i;
    if ((rowNr<0) || (srcColumnNr<0) || (destColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (rowNr>=line)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (srcColumnNr>=src.column)
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (destColumnNr>=dest.line)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[destColumnNr][i]=coeff*ptr[rowNr][i]+srcCoeff*src.ptr[i][srcColumnNr];
    }
    else {
        if (destColumnNr>=dest.column)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][destColumnNr]=coeff*ptr[rowNr][i]+srcCoeff*src.ptr[i][srcColumnNr];
    }
}

template<typename DataType> void Matrix<DataType>::addColumnToRow(int columnNr, DataType& coeff, Matrix& src, int srcRowNr, DataType& srcCoeff, Matrix& dest, int destRowNr) {
    int i;
    if ((columnNr<0) || (srcRowNr<0) || (destRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (columnNr>=column)
        _handleException(7, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (srcRowNr>=src.line)
        _handleException(4, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (destRowNr>=dest.line)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[destRowNr][i]=coeff*ptr[i][columnNr]+srcCoeff*src.ptr[srcRowNr][i];
    }
    else {
        if (destRowNr>=dest.column)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][destRowNr]=coeff*ptr[i][columnNr]+srcCoeff*src.ptr[srcRowNr][i];
    }
}

template<typename DataType> void Matrix<DataType>::addRowToRow(int rowNr, DataType& coeff, Matrix &src, int srcRowNr, DataType& srcCoeff, Matrix& dest, int destRowNr) {
    int i;
    if ((rowNr<0) || (srcRowNr<0) || (destRowNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if ((rowNr>=line) || (srcRowNr>=src.line))
        _handleException(6, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (destRowNr>=dest.line)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[destRowNr][i]=coeff*ptr[rowNr][i]+srcCoeff*src.ptr[srcRowNr][i];
    }
    else {
        if (destRowNr>=dest.column)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_rr(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][destRowNr]=coeff*ptr[rowNr][i]+srcCoeff*src.ptr[srcRowNr][i];
    }
}

template<typename DataType> void Matrix<DataType>::addColumnToColumn(int columnNr, DataType& coeff, Matrix& src, int srcColumnNr, DataType& srcCoeff, Matrix& dest, int destColumnNr) {
    int i;
    if ((columnNr<0) || (srcColumnNr<0) || (destColumnNr<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if ((columnNr>=column) || (srcColumnNr>=src.column))
        _handleException(9, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (destColumnNr>=dest.line)
            _handleException(5, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[destColumnNr][i]=coeff*ptr[i][columnNr]+srcCoeff*src.ptr[i][srcColumnNr];
    }
    else {
        if (destColumnNr>=dest.column)
            _handleException(8, "template <typename DataType> void Matrix<DataType>::add_cc(int n1, DataType &m1, Matrix &src, int n2, DataType &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][destColumnNr]=coeff*ptr[i][columnNr]+srcCoeff*src.ptr[i][srcColumnNr];
    }
}

template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns) {



    if (src.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    if ((nrOfRows<0) || (nrOfColumns<0))
        _handleException(16, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    if ((src.pos_x+nrOfRows>src.line) || (src.pos_y+nrOfColumns>src.column) || (pos_x+nrOfRows>line) || (pos_y+nrOfColumns>column))
        _handleException(18, "template <typename DataType> void Matrix<DataType>:: copy(const Matrix<DataType> &m, int step1, int step2)");
    for (int i=0; i<nrOfRows; i++)
        for (int j=0; j<nrOfColumns; j++)
            ptr[pos_x+i][pos_y+j]=src.ptr[src.pos_x+i][src.pos_y+j];
}

template <typename DataType> void Matrix<DataType>::copy(DataType** src, int nrOfRows, int nrOfColumns) {
    int i,j;
    if (src==0)
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    if ((nrOfRows<=0)||(nrOfColumns<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType** m, int ln, int cl)");
    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=src[i][j];
}

template <typename DataType> void Matrix<DataType>::copy(DataType* src, int nrOfRows, int nrOfColumns) {
    int i,j;
    if (src==0)
        _handleException(22, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    if ((nrOfRows<=0)||(nrOfColumns<=0))
        _handleException(3, "template <typename DataType> void Matrix<DataType>::copy(DataType* m, int ln, int cl)");
    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=*(src++);
}

template <typename DataType> void Matrix<DataType>::concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix) {
    Matrix m3;
    if (by_row && (firstSrcMatrix.column!=secondSrcMatrix.column))
        _handleException(13,"template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
    if ((!by_row) && (firstSrcMatrix.line!=secondSrcMatrix.line))
        _handleException(12, "template <typename DataType> void Matrix<DataType>::cat(const Matrix<DataType> &m1, const Matrix<DataType> &m2)");
    if ((firstSrcMatrix.ptr==ptr) || (secondSrcMatrix.ptr==ptr)) {
        m3.ptr=ptr;
        m3.line=line;
        m3.column=column;
        _allocMemory(1,1);
    }
    if ((firstSrcMatrix.ptr==ptr) && (secondSrcMatrix.ptr!=ptr)) { _concatenate(m3, secondSrcMatrix); return; }
    if ((firstSrcMatrix.ptr!=ptr) && (secondSrcMatrix.ptr==ptr)) { _concatenate(firstSrcMatrix, m3); return; }
    if ((firstSrcMatrix.ptr==ptr) && (secondSrcMatrix.ptr==ptr)) { _concatenate(m3, m3); return; }
    _concatenate(firstSrcMatrix, secondSrcMatrix);
}

template <typename DataType> void Matrix<DataType>::split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix,int splitRowColumnNr) {
    Matrix m3;
    if (firstDestMatrix.ptr==secondDestMatrix.ptr)
        _handleException(24, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    if (splitRowColumnNr<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    if (by_row) {
        if (splitRowColumnNr>line)
            _handleException(4, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        if ((splitRowColumnNr==0)||(splitRowColumnNr==line))
            _handleException(19, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }
    else {
        if (splitRowColumnNr>column)
            _handleException(7, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
        if ((splitRowColumnNr==0)||(splitRowColumnNr==column))
            _handleException(20, "template <typename DataType> void Matrix<DataType>::split(Matrix<DataType> &m1, Matrix<DataType> &m2,int m)");
    }
    if ((firstDestMatrix.ptr==ptr) || (secondDestMatrix.ptr==ptr)) {
        m3.ptr=ptr;
        m3.line=line;
        m3.column=column;
        m3.by_row=by_row;
        _allocMemory(1,1);
    }
    if ((firstDestMatrix.ptr==ptr) && (secondDestMatrix.ptr!=ptr)) { m3._split(*this, secondDestMatrix, splitRowColumnNr); return; }
    if ((firstDestMatrix.ptr!=ptr) && (secondDestMatrix.ptr==ptr)) { m3._split(firstDestMatrix, *this, splitRowColumnNr); return; }
    _split(firstDestMatrix, secondDestMatrix, splitRowColumnNr);
}

template <typename DataType> void Matrix<DataType>::applyCoefficientsToRow (const Matrix &coeff, Matrix &src, bool multiply) {
    int i,j;
    if (ptr==coeff.ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.line!=src.line)
        _handleException(12,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((line!=src.line)||(column!=src.column))
        resizeNoInit(src.line, src.column);
    if (multiply==true)
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=src.ptr[i][j]*coeff.ptr[i][0];
    else {
        for (i=0; i<line; i++)
            if (coeff.ptr[i][0]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=src.ptr[i][j]/coeff.ptr[i][0];
    }
}

template <typename DataType> void Matrix<DataType>::applyCoefficientsToColumn (const Matrix &coeff, Matrix &src, bool multiply) {
    int i, j;
    if (coeff.ptr==ptr)
        _handleException(25,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.column!=src.column)
        _handleException(13,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((line!=src.line)||(column!=src.column))
        resizeNoInit(src.line, src.column);
    if (multiply==true)
        for (j=0; j<column; j++)
            for (i=0; i<line; i++)
                ptr[i][j]=src.ptr[i][j]*coeff.ptr[0][j];
    else {
        for (j=0; j<column; j++)
            if (coeff.ptr[0][j]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
        for (j=0; j<column; j++)
            for (i=0; i<line; i++)
                ptr[i][j]=src.ptr[i][j]/coeff.ptr[0][j];
    }
}

template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator+ (const Matrix<DataType>& matrix) {
    int i,j;
    if ((line!=matrix.line) || (column!=matrix.column))
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator+ (const Matrix<DataType> &m)");
    Matrix a(line,column);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            a.ptr[i][j]=ptr[i][j]+matrix.ptr[i][j];
    return a;
}

template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator- (const Matrix<DataType>& matrix) {
    int i,j;
    if ((line!=matrix.line) || (column!=matrix.column))
        _handleException(10, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator- (const Matrix<DataType> &m)");
    Matrix a(line,column);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            a.ptr[i][j]=ptr[i][j]-matrix.ptr[i][j];
    return a;
}

template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator* (const Matrix<DataType>& matrix) {
    int i,j,k;
    if (column!=matrix.line)
        _handleException(11, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator* (const Matrix<DataType> &m)");
    Matrix a(line,matrix.column);
    for (i=0; i<line; i++)
        for (j=0; j<matrix.column; j++)
            for (k=0; k<column; k++)
                a.ptr[i][j]=a.ptr[i][j]+ptr[i][k]*matrix.ptr[k][j];
    return a;
}

template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int exp) {
    Matrix a;
    if (line!=column)
        _handleException(1, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    if (exp<0)
        _handleException(16, "template <typename DataType> Matrix<DataType> Matrix<DataType> :: operator^ (int m)");
    if (exp==0) {
        a.transformToUnitMatrix(line);
        return a;
    }

    a=(*this);
    return a._power(exp);
}

template <typename DataType> Matrix<DataType>& Matrix<DataType>:: operator= (const Matrix<DataType>& matrix) {
    if (matrix.ptr==ptr) goto is_current_matrix;
    if ((line==matrix.line)&&(column==matrix.column)) goto is_equal;
    _deallocMemory();
    _allocMemory(matrix.line, matrix.column);
is_equal:
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=matrix.ptr[i][j];
    pos_x=matrix.pos_x;
    pos_y=matrix.pos_y;
    by_row=matrix.by_row;
is_current_matrix:
    return *this;
}

template <typename DataType> bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix) {
    int i,j;
    if (matrix.ptr==ptr)
        return true;
    if ((line!=matrix.line) || (column!=matrix.column))
        _handleException(10, "template <typename DataType> bool Matrix<DataType>::operator==(const Matrix<DataType> &m)");
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            if (ptr[i][j]!=matrix.ptr[i][j])
                return false;
    return true;
}

template <typename DataType> DataType Matrix<DataType>::determinant() {
    int i,j,k,l,temp=1;
    if (line!=column)
        _handleException(1, "template <typename DataType> DataType Matrix<DataType>::det()");
    Matrix m = *this;
    DataType det=1;
    int semn=1;
    for (k=0; k<line-1; k++) {
        if (m.ptr[k][k]==0) {
            for (l=k+1; l<line; l++)
                if (m.ptr[l][k]!=0) {
                    m.swapRow(k,l);
                    semn = semn*(-1);
                    goto Prelucrare;
                }
            return 0;
        }
Prelucrare:
        for (j=k+1; j<column; j++)
            for (i=k+1; i<line; i++) {
                m.ptr[i][j]=m.ptr[i][j]*(m.ptr[k][k])-m.ptr[k][j]*(m.ptr[i][k]);
                temp=temp*(m.ptr[k][k]*m.ptr[i][k]);
            }
    }
    for (k=0; k<line; k++)
        det=det*m.ptr[k][k];
    return (det/temp)*semn;
}

template<typename DataType> int Matrix<DataType>::rank() {
    int i,j;
    int rang=0;
    Matrix p;
    if (line>column)
        getTransposedMatrix(p);
    else p=*this;
    p.pos_x=0;
    p.pos_y=0;
    while (p.pos_x<p.line-1) {
        if (p.ptr[p.pos_x][p.pos_y]==0) {
            for (i=p.pos_x+1; i<p.line; i++)
                if (p.ptr[i][p.pos_y]!=0) {
                    rang++;
                    p.swapRow(i,p.pos_x);
                    goto Prelucrare;
                }
            for (j=p.pos_y+1; j<p.column; j++)
                if (p.ptr[p.pos_x][j]!=0) {
                    rang++;
                    p.swapColumn(j,p.pos_y);
                    goto Prelucrare;
                }
        }
        else
            rang++;
Prelucrare:
    for (i=p.pos_x+1; i<p.line; i++)
        for (j=p.pos_y+1; j<p.column; j++)
            p.ptr[i][j]=(p.ptr[i][j])*(p.ptr[p.pos_x][p.pos_y]) - (p.ptr[p.pos_x][j])*(p.ptr[i][p.pos_y]);
    (p.pos_x)++;
    (p.pos_y)++;
    }
    for (j=p.pos_y; j<p.column; j++)
        if (p.ptr[p.pos_x][j]!=0) {
            rang++;
            break;
        }
    return rang;
}

template<typename DataType> void Matrix<DataType>::getInverseMatrix(Matrix<DataType>& coeff, Matrix<DataType>& pseudoInverse) {
    int i,j,k,l;
    Matrix <DataType> temp;
    if ((ptr==coeff.ptr) || (ptr==pseudoInverse.ptr))
        _handleException(25, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    if (line!=column)
        _handleException(1, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    temp=*this;
    pseudoInverse.transformToUnitMatrix(line);
    coeff.resizeNoInit(line,1);

    for (k=0; k<line-1; k++) {
        if (temp.ptr[k][k]==0) {
            for (l=k+1; l<line; l++) {
                if (temp.ptr[k][l]!=0) {
                    temp.swapRow(k,l);
                    pseudoInverse.swapRow(k,l);
                    goto Prelucrare;
                }
            }
            _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
        }
Prelucrare:
        for (j=0; j<line; j++)
            for (i=k+1; i<line; i++) {
                if (j>k)
                    temp.ptr[i][j]=temp.ptr[i][j]*temp.ptr[k][k]- temp.ptr[k][j]*temp.ptr[i][k];
                pseudoInverse.ptr[i][j]=pseudoInverse.ptr[i][j]*temp.ptr[k][k] - pseudoInverse.ptr[k][j]*temp.ptr[i][k];
            }
    }
    for (k=0; k<line; k++)
        for (i=k+1; i<line; i++)
            temp.ptr[i][k]=0;
    if (temp.ptr[line-1][line-1]==0)
        _handleException(2, "template<typename DataType> void Matrix<DataType>::inversion(Matrix<DataType> &coeff, Matrix<DataType> &pseudo_inv)");
    for (k=line-1; k>0; k--)
        for (i=0; i<=k-1; i++)
            for (j=0; j<=line-1; j++) {
                if (j<k)
                    temp.ptr[i][j]=temp.ptr[i][j]*temp.ptr[k][k]-temp.ptr[k][j]*temp.ptr[i][k];
                pseudoInverse.ptr[i][j]=pseudoInverse.ptr[i][j]*temp.ptr[k][k]-pseudoInverse.ptr[k][j]*temp.ptr[i][k];
            }
    for (k=0; k<line; k++)
        coeff.ptr[k][0]=temp.ptr[k][k];
}

template <typename DataType> void Matrix<DataType>::getTransposedMatrix(Matrix<DataType>& result) {
    int i,j;
    Matrix temp;
    DataType **temp_ptr;
    if (ptr==result.ptr) {
        temp_ptr=temp.ptr;
        temp.ptr=ptr;
        ptr=temp_ptr;
        temp.line=line;
        temp.column=column;
        resizeNoInit(column, line);
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=temp.ptr[j][i];
        return;
    }
    result.resizeNoInit(column,line);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            result.ptr[j][i]=ptr[i][j];
}

template <typename DataType> void Matrix<DataType>::sums(Matrix& result, int mode) {
    int i,j;
    DataType sum=0;
    if (result.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    if (mode>4)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    if (mode<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::sums(Matrix &m, int sum_type)");
    switch (mode) {
        case 0:
            result.resizeNoInit(1,1);
            for (i=0; i<line; i++)
                for (j=0; j<column; j++)
                    sum=sum + ptr[i][j];
            result.ptr[0][0]=sum;
            return;
        case 1:
            result.resizeNoInit(1,1);
            for (j=0; j<column; j++)
                sum=sum+ptr[pos_x][j];
            result.ptr[0][0]=sum;
            return;
        case 2:
            result.resizeNoInit(line,1);
            for (i=0; i<line; i++) {
                result.ptr[i][0]=0;
                for (j=0; j<column; j++)
                    result.ptr[i][0]=result.ptr[i][0]+ptr[i][j];
            }
            return;
        case 3:
            result.resizeNoInit(1,1);
            for (i=0; i<line; i++)
                sum=sum+ptr[i][pos_y];
            result.ptr[0][0]=sum;
            return;
        case 4:
            result.resizeNoInit(1,column);
            for (j=0; j<column; j++) {
                result.ptr[0][j]=0;
                for (int i=0; i<line; i++)
                    result.ptr[0][j]=result.ptr[0][j]+ptr[i][j];
            }
            return;
    }
}

template <typename DataType> void Matrix<DataType>::products(Matrix& result, int mode) {
    int i,j;
    DataType product;
    if (result.ptr==ptr)
        _handleException(25, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    if (mode>4)
        _handleException(21, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    if (mode<0)
        _handleException(16, "template <typename DataType> void Matrix<DataType>::products(Matrix &m, int prod)");
    switch (mode) {
        case 0:
            product=1;
            result.resizeNoInit(1,1);
            for (i=0; i<line; i++)
                for (j=0; j<column; j++)
                    product = product * ptr[i][j];
            result.ptr[0][0]=product;
            return;
        case 1:
            product=1;
            result.resizeNoInit(1,1);
            for (j=0; j<column; j++)
                product=product*ptr[pos_x][j];
            result.ptr[0][0]=product;
            return;
        case 2:
            result.resizeNoInit(line,1);
            for (i=0; i<line; i++) {
                product=1;
                for (int j=0; j<column; j++)
                    product=product*ptr[i][j];
                result.ptr[i][0]=product;
            }
            return;
        case 3:
            result.resizeNoInit(1,1);
            product=1;
            for (i=0; i<line; i++)
                product=product*ptr[i][pos_y];
            result.ptr[0][0]=product;
            return;
        case 4:
            result.resizeNoInit(1,column);
            for (j=0; j<column; j++) {
                product=1;
                for (int i=0; i<line; i++)
                    product=product*ptr[i][j];
                result.ptr[0][j]=product;
            }
            return;
    }
}

template <typename DataType> void Matrix<DataType>::getNegativeMatrix(Matrix<DataType>& result) {
    int i,j;
    if (result.ptr==ptr) goto negativation;
    result.resizeNoInit(line,column);
negativation:
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            result.ptr[i][j]=(-1)*ptr[i][j];
}

template <typename DataType> void Matrix<DataType>::getInverseElementsMatrix(Matrix<DataType>& result) {
    int i,j;
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            if (ptr[i][j]==0)
                _handleException(23,"template <typename DataType> void Matrix<DataType>::inv_matrix(Matrix<DataType> &m)");
    if (result.ptr==ptr) goto inversion;
    result.resizeNoInit(line,column);
inversion:
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            result.ptr[i][j]=1/ptr[i][j];
}

template <typename DataType> void Matrix<DataType>::_writeMatrix(ostream& os, int mode) {
    int i,j;
    switch (mode) {
        case 0:
            for (i=0; i<line; i++) {
                for (j=0; j<column; j++)
                    os<<ptr[i][j]<<" ";
                os<<endl;
            }
            return;
        case 1:
            for (j=0; j<column; j++)
                os<<ptr[pos_x][j]<<" ";
            return;
        case 2:
            for (i=0; i<line; i++)
                os<<ptr[i][pos_y]<<endl;
            return;
        case 3:
            os<<ptr[pos_x][pos_y];
            return;
        case 4:
            for (i=0; i<line; i++)
                os<<ptr[i][i]<<" ";
            return;
        case 5:
            for (i=line-1; i>=0; i--)
                os<<ptr[i][line-1-i]<<" ";
            return;
    }
}

template <typename DataType> void Matrix<DataType>::_readMatrix(istream &is, int mode) {
    string s;
    int i,j;
    stringstream str_st(ios::in|ios::out);
    switch (mode) {
        case 0:
            for (i=0; i<line; i++)
                for (j=0; j<column; j++) {
                    if (is.eof())
                        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                    cout<<"["<<i<<"]["<<j<<"]= ";
                    is>>ptr[i][j];
                }
            return;
        case 1:
            cout<<"["<<pos_x<<"]["<<pos_y<<"]= ";
            is>>ptr[pos_x][pos_y];
            return;
        case 2:
            for (j=0; j<column; j++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<pos_x<<"]["<<j<<"]= ";
                is>>ptr[pos_x][j];
            }
            return;
        case 3:
            for (i=0; i<line; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<pos_y<<"]= ";
                is>>ptr[i][pos_y];
            }
            return;
        case 4:
            for(i=0; i<line; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<i<<"]= ";
                is>>ptr[i][i];
            }
            return;
        case 5:
            for(i=line-1; i>=0; i--) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<line-1-i<<"]= ";
                is>>ptr[i][line-1-i];
            }
            return;
        case 6:
            _readDiscard(is);
            pos_x=0;
            for (i=0; i<line; i++) {
                _readTextLine(is);
                pos_x++;
                f_x++;
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
            pos_x=0;
            for(i=0; i<line; i++) {
                _readSingleItem(is);
                pos_x++;
                f_x++;
            }
            return;
        case 10:
            _readDiscard(is);
            resetCurrentPos();
            f_y=0;
            for (i=0; i<line; i++) {
                _readSingleItem(is);
                f_x++;
                pos_y=++pos_x;
                f_y++;
            }
            return;
        case 11:
            _readDiscard(is);
            f_y=line-1;
            pos_x=0;
            pos_y=line-1;
            for(i=0; i<line; i++) {
                _readSingleItem(is);
                f_x++;
                f_y--;
                pos_x++;
                pos_y--;
            }
            return;
        case 12:
            for (i=0; i<line; i++)
                for (j=0; j<column; j++) {
                    if (is.eof())
                        _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                    is>>ptr[i][j];
                }
            return;
        case 13:
            if (is.eof())
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            is>>ptr[pos_x][pos_y];
            return;
        case 14:
            for (j=0; j<column; j++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[pos_x][j];
            }
            return;
        case 15:
            for (i=0; i<line; i++) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][pos_y];
            }
            return;
        case 16:
            for (i=0; i<line; i++)  {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][i];
            }
            return;
        case 17:
            for (i=line-1; i>=0; i--) {
                if (is.eof())
                    _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][line-1-i];
            }
    }
}

template<typename DataType> int Matrix<DataType>:: _createSortingPartition(int first,int last,int pivot,int mode,int pos) {
    int i,j;
    switch(mode) {
        case 0:
            if (pivot!=last)
                swapItem(pos,pivot,pos,last);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (ptr[pos][i]<ptr[pos][last]));
                do j--;
                    while ((i!=j) && (ptr[pos][j]>ptr[pos][last]));
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
                    while ((i!=j) && (ptr[pos][i]>ptr[pos][last]));
                do j--;
                    while ((i!=j) && (ptr[pos][j]<ptr[pos][last]));
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
                    while ((i!=j) && (ptr[i][pos]<ptr[last][pos]));
                do j--;
                    while ((i!=j) && (ptr[j][pos]>ptr[last][pos]));
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
                    while ((i!=j) && (ptr[i][pos]>ptr[last][pos]));
                do j--;
                    while ((i!=j) && (ptr[j][pos]<ptr[last][pos]));
                if (i<j)
                    swapItem(i,pos,j,pos);
            }
            if (i!=last)
                swapItem(i,pos,last,pos);
            return i;
    }
}

template<typename DataType> int Matrix<DataType>:: _createSortingPartition(int first,int last,int pivot,int mode) {
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

template<typename DataType> void Matrix<DataType>::_handleException(int errorType, char* function) {
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




