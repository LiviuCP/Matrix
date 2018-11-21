#include "matrix.h"

template<typename mytype> int Matrix<mytype>::f_x=0;
template<typename mytype> int Matrix<mytype>::f_y=0;

template <typename mytype> Matrix<mytype>::Matrix() {
    bool by_row=true;
    line=1;
    column=1;
    mprint=0;
    entdat=0;
    ptr=new mytype*[1];
    ptr[0]=new mytype;
    ptr[0][0]=0;
    reset_xy();
}

template <typename mytype> Matrix<mytype>::Matrix(int m, int n) {
    if (m<=0 || n<=0) handle_exception(3, "template <typename mytype> Matrix<mytype>::Matrix(int m, int n)");
    by_row=true;
    line=m;
    column=n;
    entdat=0;
    mprint=0;
    reset_xy();
    alloc_matrix(m,n);
    set_zero();
}

template <typename mytype> Matrix<mytype>::Matrix(int n) {
    if (n<=0) handle_exception(3, "template <typename mytype> Matrix<mytype>::Matrix(int n)");
    bool by_row=true;
    line = n;
    column = n;
    mprint=0;
    entdat=0;
    reset_xy();
    alloc_matrix(line,column);
    set_zero();
    for (int i=0; i<n; i++)
        ptr[i][i]=1;
}

template <typename mytype> Matrix<mytype>::Matrix(mytype** m, int ln, int cl) {
    int i,j;
    if (m==0)
        handle_exception(22,"template <typename mytype> Matrix<mytype>::Matrix(mytype** m, int ln, int cl)");
    if ((ln<=0) || (cl<=0))
        handle_exception(3,"template <typename mytype> Matrix<mytype>::Matrix(mytype** m, int ln, int cl)");
    by_row=true;
    mprint=0;
    entdat=0;
    reset_xy();
    alloc_matrix(ln, cl);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=m[i][j];
}

template <typename mytype> Matrix<mytype>::Matrix(mytype* m, int ln, int cl) {
    int i,j;
    if (m==0)
        handle_exception(22,"template <typename mytype> Matrix<mytype>::Matrix(mytype* m, int ln, int cl)");
    if ((ln<=0) || (cl<=0))
        handle_exception(3,"template <typename mytype> Matrix<mytype>::Matrix(mytype* m, int ln, int cl)");
    by_row=true;
    line=ln;
    column=cl;
    mprint=0;
    entdat=0;
    reset_xy();
    alloc_matrix(ln, cl);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=*(m++);
}

template<typename mytype> Matrix<mytype>::Matrix(int m, int n, istream &is) {
    int i;
    by_row=true;
    mprint=0;
    entdat=0;
    line=m; column=n;
    alloc_matrix(m,n);
    read_discard(is);
    pos_x=0;
    for (i=0; i<line; i++) {
        read_text_line(is);
        pos_x++;
        f_x++;
    }
    pos_x=0;
    pos_y=0;
}

template <typename mytype> Matrix<mytype>::Matrix(const Matrix<mytype> &m) {
    alloc_matrix(m.line, m.column);
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=m.ptr[i][j];
    pos_x=m.pos_x;
    pos_y=m.pos_y;
    by_row=m.by_row;
    entdat=m.entdat;
    mprint=m.mprint;
}

template<typename mytype> mytype& Matrix<mytype>:: get(int i,int j) {
    if ((i<0) || (j<0)) handle_exception(16, "template<typename mytype> mytype& Matrix<mytype>::get(int i,int j)");
    if ((i>=line) || (j>=column)) handle_exception(18, "template<typename mytype> mytype& Matrix<mytype>::get(int i,int j)");
    return ptr[i][j];
}

template <typename mytype> void Matrix<mytype>::set_zero() {
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=0;
}

template <typename mytype> void Matrix<mytype>::unit(int m) {
    if (m<=0) handle_exception(3,"template <typename mytype> void Matrix<mytype>::unit(int m)");
    dealloc_matrix();
    alloc_matrix(m,m);
    set_zero();
    for (int i=0; i<m; i++)
        ptr[i][i]=1;
}

template <typename mytype> void Matrix<mytype>::null_matrix(int m, int n) {
    if (m<=0 || n<=0)
        handle_exception(3, "template <typename mytype> void Matrix<mytype>::null_matrix(int m, int n)");
    dealloc_matrix();
    alloc_matrix(m,n);
    set_zero();
}

template <typename mytype> void Matrix<mytype>::resize_m(int m, int n) {
    int i,j;
    mytype **temp;
    if ((m==line)&&(n==column)) return;
    if ((m<=0) || (n<=0))
        handle_exception(3, "template <typename mytype> void Matrix<mytype>::resize_m(int m, int n)");
    Matrix a;
    temp=a.ptr;
    a.ptr=ptr;
    ptr=temp;
    a.line=line;
    a.column=column;
    delete ptr[0];
    delete ptr;
    alloc_matrix(m,n);
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

template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2) {
    mytype swap;
    if (m2.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((r1<0) || (c1<0) || (r2<0) || (c2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    if ((r1>=line) || (c1>=column) || (r2>=m2.line) || (c2>=m2.column))
        handle_exception(18, "template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, Matrix &m2, int r2, int c2)");
    swap=ptr[r1][c1];
    ptr[r1][c1]=m2.ptr[r2][c2];
    m2.ptr[r2][c2]=swap;
}

template <typename mytype> void Matrix<mytype>::swap_r(int r1, Matrix &m2, int r2) {
    mytype *swap;
    if (m2.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, Matrix &m2, int r2)");
    if ((r1<0) || (r2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, Matrix &m2, int r2)");
    if ((r1>=line) || (r2>=m2.line))
        handle_exception(6, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, Matrix &m2, int r2)");
    if (column!=m2.column)
        handle_exception(13, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, Matrix &m2, int r2)");
    swap=ptr[r1];
    ptr[r1]=m2.ptr[r2];
    m2.ptr[r2]=swap;
}

template <typename mytype> void Matrix<mytype>::swap_c(int c1, Matrix &m2, int c2) {
    mytype swap;
    int i;
    if (m2.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, Matrix &m2, int c2)");
    if ((c1<0) || (c2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, Matrix &m2, int c2)");
    if ((c1>=column) || (c2>=m2.column))
        handle_exception(9, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, Matrix &m2, int c2)");
    if (line!=m2.line)
        handle_exception(12, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, Matrix &m2, int c2)");
    for(i=0; i<line; i++) {
        swap=ptr[i][c1];
        ptr[i][c1]=m2.ptr[i][c2];
        m2.ptr[i][c2]=swap;
    }
}

template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2) {
    mytype swap;
    int k;
    if ((r1<0) || (c2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2)");
    if (column!=m2.line)
        handle_exception(11, "template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2)");
    if (r1>=line)
        handle_exception(6, "template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2)");
    if (c2>=m2.column)
        handle_exception(9, "template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2)");
    if (ptr==m2.ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::swap_rc(int r1, Matrix<mytype> &m2, int c2)");
    for (k=0; k<column; k++) {
        swap=ptr[r1][k];
        ptr[r1][k]=m2.ptr[k][c2];
        m2.ptr[k][c2]=swap;
    }
}

template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, int r2, int c2) {
    if ((r1<0) || (c1<0) || (r2<0) || (c2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, int r2, int c2)");
    if ((r1>=line) || (c1>=column) || (r2>=line) || (c2>=column))
        handle_exception(18, "template <typename mytype> void Matrix<mytype>::swap_i(int r1, int c1, int r2, int c2)");
    mytype swap;
    swap=ptr[r1][c1];
    ptr[r1][c1]=ptr[r2][c2];
    ptr[r2][c2]=swap;
}

template <typename mytype> void Matrix<mytype>::swap_r(int r1, int r2) {
    mytype *swap;
    if ((r1<0) || (r2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, int r2)");
    if ((r1>=line) || (r2>=line))
        handle_exception(6, "template <typename mytype> void Matrix<mytype>::swap_r(int r1, int r2)");
    swap=ptr[r1];
    ptr[r1]=ptr[r2];
    ptr[r2]=swap;
}

template <typename mytype> void Matrix<mytype>::swap_c(int c1, int c2) {
    mytype swap;
    int i;
    if ((c1<0) || (c2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, int c2)");
    if ((c1>=column) || (c2>=column))
        handle_exception(9, "template <typename mytype> void Matrix<mytype>::swap_c(int c1, int c2)");
    for(i=0; i<line; i++) {
        swap=ptr[i][c1];
        ptr[i][c1]=ptr[i][c2];
        ptr[i][c2]=swap;
    }
}

template<typename mytype> void Matrix<mytype>::swap_rc(int rc1) {
    mytype swap;
    int k;
    if (line!=column)
        handle_exception(1,"template<typename mytype> void Matrix<mytype>::swap_rc(int rc1)");
    if (rc1<0)
        handle_exception(16,"template<typename mytype> void Matrix<mytype>::swap_rc(int rc1)");
    if (rc1>=line)
        handle_exception(18,"template<typename mytype> void Matrix<mytype>::swap_rc(int rc1)");
    for (k=0; k<line; k++) {
        swap=ptr[rc1][k];
        ptr[rc1][k]=ptr[k][rc1];
        ptr[k][rc1]=swap;
    }
}

template<typename mytype> void Matrix<mytype>::rv_mat(Matrix<mytype> &m) {
    mytype** temp;
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

template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode) {
    if (mode<0 || mode>3)
        handle_exception(21, "template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode)");
    switch (mode) {
        case 0:
            if (pos<0 || pos>line-1)
                handle_exception(4, "template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode)");
            q_sort(0,column-1,0, pos);
            return;
        case 1:
            if (pos<0 || pos>line-1)
                handle_exception(4, "template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode)");
            q_sort(0,column-1,1, pos);
            return;
        case 2:
            if (pos<0 || pos>column-1)
                handle_exception(7, "template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode)");
            q_sort(0,line-1,2, pos);
            return;
        case 3:
            if (pos<0 || pos>column-1)
                handle_exception(7, "template <typename mytype> void Matrix<mytype>:: sort_lc(int pos, int mode)");
            q_sort(0,line-1,3, pos);
    }
}

template <typename mytype> void Matrix<mytype>::sort_matr(int mode) {
    if (mode<0 || mode>3)
        handle_exception(21, "template <typename mytype> void Matrix<mytype>::sort_matr(int mode)");
    switch (mode) {
        case 0:
            q_sort(0,line*column-1,0);
            return;
        case 1:
            q_sort(0,line*column-1,1);
            return;
        case 2:
            q_sort(0,line*column-1,2);
            return;
        case 3:
            q_sort(0,line*column-1,3);
    }
}

template <typename mytype> void Matrix<mytype>::insert_row (int m) {
    int i;
    mytype **insert_ptr;
    if (m<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::insert_row (int m)");
    if (m>line)
        handle_exception(17, "template <typename mytype> void Matrix<mytype>::insert_row (int m)");
    insert_ptr=new mytype*[line+1];
    for (i=0; i<m; i++)
        insert_ptr[i]=ptr[i];
    insert_ptr[m]=new mytype[column];
    for (i=0; i<column; i++)
        insert_ptr[m][i]=0;
    for (i=m; i<line; i++)
        insert_ptr[i+1]=ptr[i];
    delete []ptr;
    ptr=insert_ptr;
    line++;
}

template <typename mytype> void Matrix<mytype>::delete_row (int m) {
    int i;
    mytype **insert_ptr;
    if (line==1)
        handle_exception(15, "template <typename mytype> void Matrix<mytype>::delete_row (int m)");
    if (m>=line)
        handle_exception(4, "template <typename mytype> void Matrix<mytype>::delete_row (int m)");
    if (m<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::delete_row (int m)");
    insert_ptr=new mytype*[line-1];
    for (i=0; i<m; i++)
        insert_ptr[i]=ptr[i];
    delete []ptr[m];
    for (i=m; i<line-1; i++)
        insert_ptr[i]=ptr[i+1];
    delete []ptr;
    ptr=insert_ptr;
    line--;
}

template <typename mytype> void Matrix<mytype>::insert_col(int n) {
    int i,j;
    mytype **insert_ptr;
    if (n<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::insert_col(int n)");
    if (n>column)
        handle_exception(17, "template <typename mytype> void Matrix<mytype>::insert_col(int n)");
    insert_ptr = new mytype*[line];
    for (i=0; i<line; i++)
        insert_ptr[i]=new mytype[column+1];
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

template <typename mytype> void Matrix<mytype>::delete_col(int n) {
    int i,j;
    if (column==1)
        handle_exception(14, "template <typename mytype> void Matrix<mytype>::delete_col(int n)");
    if (n<0)
        handle_exception (16, "template <typename mytype> void Matrix<mytype>::delete_col(int n)");
    if (n>=column)
        handle_exception (7, "template <typename mytype> void Matrix<mytype>::delete_col(int n)");
    mytype **insert_ptr;
    insert_ptr = new mytype*[line];
    for (i=0; i<line; i++)
        insert_ptr[i]=new mytype[column-1];
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

template<typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest,int p1) {
    int i;
    if ((n1<0) || (n2<0) || (p1<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (n1>=line)
        handle_exception(4, "template <typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (n2>=src.column)
        handle_exception(7, "template <typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (p1>=dest.line)
            handle_exception(5, "template <typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[p1][i]=m1*ptr[n1][i]+m2*src.ptr[i][n2];
    }
    else {
        if (p1>=dest.column)
            handle_exception(8, "template <typename mytype> void Matrix<mytype>::add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][p1]=m1*ptr[n1][i]+m2*src.ptr[i][n2];
    }
}

template<typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1) {
    int i;
    if ((n1<0) || (n2<0) || (p1<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (n1>=column)
        handle_exception(7, "template <typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (n2>=src.line)
        handle_exception(4, "template <typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (p1>=dest.line)
            handle_exception(5, "template <typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[p1][i]=m1*ptr[i][n1]+m2*src.ptr[n2][i];
    }
    else {
        if (p1>=dest.column)
            handle_exception(8, "template <typename mytype> void Matrix<mytype>::add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][p1]=m1*ptr[i][n1]+m2*src.ptr[n2][i];
    }
}

template<typename mytype> void Matrix<mytype>::add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1) {
    int i;
    if ((n1<0) || (n2<0) || (p1<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if ((n1>=line) || (n2>=src.line))
        handle_exception(6, "template <typename mytype> void Matrix<mytype>::add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (p1>=dest.line)
            handle_exception(5, "template <typename mytype> void Matrix<mytype>::add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[p1][i]=m1*ptr[n1][i]+m2*src.ptr[n2][i];
    }
    else {
        if (p1>=dest.column)
            handle_exception(8, "template <typename mytype> void Matrix<mytype>::add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][p1]=m1*ptr[n1][i]+m2*src.ptr[n2][i];
    }
}

template<typename mytype> void Matrix<mytype>::add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1) {
    int i;
    if ((n1<0) || (n2<0) || (p1<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if ((n1>=column) || (n2>=src.column))
        handle_exception(9, "template <typename mytype> void Matrix<mytype>::add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
    if (dest.by_row) {
        if (p1>=dest.line)
            handle_exception(5, "template <typename mytype> void Matrix<mytype>::add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[p1][i]=m1*ptr[i][n1]+m2*src.ptr[i][n2];
    }
    else {
        if (p1>=dest.column)
            handle_exception(8, "template <typename mytype> void Matrix<mytype>::add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1)");
        for (i=0; i<line; i++)
            dest.ptr[i][p1]=m1*ptr[i][n1]+m2*src.ptr[i][n2];
    }
}

template <typename mytype> void Matrix<mytype>:: copy(const Matrix<mytype> &m, int step1, int step2) {



    if (m.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>:: copy(const Matrix<mytype> &m, int step1, int step2)");
    if ((step1<0) || (step2<0))
        handle_exception(16, "template <typename mytype> void Matrix<mytype>:: copy(const Matrix<mytype> &m, int step1, int step2)");
    if ((m.pos_x+step1>m.line) || (m.pos_y+step2>m.column) || (pos_x+step1>line) || (pos_y+step2>column))
        handle_exception(18, "template <typename mytype> void Matrix<mytype>:: copy(const Matrix<mytype> &m, int step1, int step2)");
    for (int i=0; i<step1; i++)
        for (int j=0; j<step2; j++)
            ptr[pos_x+i][pos_y+j]=m.ptr[m.pos_x+i][m.pos_y+j];
}

template <typename mytype> void Matrix<mytype>::copy(mytype** m, int ln, int cl) {
    int i,j;
    if (m==0)
        handle_exception(22, "template <typename mytype> void Matrix<mytype>::copy(mytype** m, int ln, int cl)");
    if ((ln<=0)||(cl<=0))
        handle_exception(3, "template <typename mytype> void Matrix<mytype>::copy(mytype** m, int ln, int cl)");
    dealloc_matrix();
    alloc_matrix(ln, cl);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=m[i][j];
}

template <typename mytype> void Matrix<mytype>::copy(mytype* m, int ln, int cl) {
    int i,j;
    if (m==0)
        handle_exception(22, "template <typename mytype> void Matrix<mytype>::copy(mytype* m, int ln, int cl)");
    if ((ln<=0)||(cl<=0))
        handle_exception(3, "template <typename mytype> void Matrix<mytype>::copy(mytype* m, int ln, int cl)");
    dealloc_matrix();
    alloc_matrix(ln, cl);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
                ptr[i][j]=*(m++);
}

template <typename mytype> void Matrix<mytype>::cat(Matrix<mytype> &m1, Matrix<mytype> &m2) {
    Matrix m3;
    if (by_row && (m1.column!=m2.column))
        handle_exception(13,"template <typename mytype> void Matrix<mytype>::cat(const Matrix<mytype> &m1, const Matrix<mytype> &m2)");
    if ((!by_row) && (m1.line!=m2.line))
        handle_exception(12, "template <typename mytype> void Matrix<mytype>::cat(const Matrix<mytype> &m1, const Matrix<mytype> &m2)");
    if ((m1.ptr==ptr) || (m2.ptr==ptr)) {
        m3.ptr=ptr;
        m3.line=line;
        m3.column=column;
        alloc_matrix(1,1);
    }
    if ((m1.ptr==ptr) && (m2.ptr!=ptr)) { cat_matr(m3, m2); return; }
    if ((m1.ptr!=ptr) && (m2.ptr==ptr)) { cat_matr(m1, m3); return; }
    if ((m1.ptr==ptr) && (m2.ptr==ptr)) { cat_matr(m3, m3); return; }
    cat_matr(m1, m2);
}

template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m) {
    Matrix m3;
    if (m1.ptr==m2.ptr)
        handle_exception(24, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
    if (m<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
    if (by_row) {
        if (m>line)
            handle_exception(4, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
        if ((m==0)||(m==line))
            handle_exception(19, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
    }
    else {
        if (m>column)
            handle_exception(7, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
        if ((m==0)||(m==column))
            handle_exception(20, "template <typename mytype> void Matrix<mytype>::split(Matrix<mytype> &m1, Matrix<mytype> &m2,int m)");
    }
    if ((m1.ptr==ptr) || (m2.ptr==ptr)) {
        m3.ptr=ptr;
        m3.line=line;
        m3.column=column;
        m3.by_row=by_row;
        alloc_matrix(1,1);
    }
    if ((m1.ptr==ptr) && (m2.ptr!=ptr)) { m3.split_matr(*this, m2, m); return; }
    if ((m1.ptr!=ptr) && (m2.ptr==ptr)) { m3.split_matr(m1, *this, m); return; }
    split_matr(m1, m2, m);
}

template <typename mytype> void Matrix<mytype>::coef_row (const Matrix &coeff, Matrix &src, bool multiply) {
    int i,j;
    if (ptr==coeff.ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.line!=src.line)
        handle_exception(12,"template <typename mytype> void Matrix<mytype>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((line!=src.line)||(column!=src.column))
        resize(src.line, src.column);
    if (multiply==true)
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=src.ptr[i][j]*coeff.ptr[i][0];
    else {
        for (i=0; i<line; i++)
            if (coeff.ptr[i][0]==0)
                handle_exception(23,"template <typename mytype> void Matrix<mytype>::coef_row (const Matrix &coeff, Matrix &src, bool multiply)");
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=src.ptr[i][j]/coeff.ptr[i][0];
    }
}

template <typename mytype> void Matrix<mytype>::coef_col (const Matrix &coeff, Matrix &src, bool multiply) {
    int i, j;
    if (coeff.ptr==ptr)
        handle_exception(25,"template <typename mytype> void Matrix<mytype>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if (coeff.column!=src.column)
        handle_exception(13,"template <typename mytype> void Matrix<mytype>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
    if ((line!=src.line)||(column!=src.column))
        resize(src.line, src.column);
    if (multiply==true)
        for (j=0; j<column; j++)
            for (i=0; i<line; i++)
                ptr[i][j]=src.ptr[i][j]*coeff.ptr[0][j];
    else {
        for (j=0; j<column; j++)
            if (coeff.ptr[0][j]==0)
                handle_exception(23,"template <typename mytype> void Matrix<mytype>::coef_col (const Matrix &coeff, Matrix &src, bool multiply)");
        for (j=0; j<column; j++)
            for (i=0; i<line; i++)
                ptr[i][j]=src.ptr[i][j]/coeff.ptr[0][j];
    }
}

template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator+ (const Matrix<mytype> &m) {
    int i,j;
    if ((line!=m.line) || (column!=m.column))
        handle_exception(10, "template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator+ (const Matrix<mytype> &m)");
    Matrix a(line,column);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            a.ptr[i][j]=ptr[i][j]+m.ptr[i][j];
    return a;
}

template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator- (const Matrix<mytype> &m) {
    int i,j;
    if ((line!=m.line) || (column!=m.column))
        handle_exception(10, "template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator- (const Matrix<mytype> &m)");
    Matrix a(line,column);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            a.ptr[i][j]=ptr[i][j]-m.ptr[i][j];
    return a;
}

template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator* (const Matrix<mytype> &m) {
    int i,j,k;
    if (column!=m.line)
        handle_exception(11, "template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator* (const Matrix<mytype> &m)");
    Matrix a(line,m.column);
    for (i=0; i<line; i++)
        for (j=0; j<m.column; j++)
            for (k=0; k<column; k++)
                a.ptr[i][j]=a.ptr[i][j]+ptr[i][k]*m.ptr[k][j];
    return a;
}

template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator^ (int m) {
    Matrix a;
    if (line!=column)
        handle_exception(1, "template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator^ (int m)");
    if (m<0)
        handle_exception(16, "template <typename mytype> Matrix<mytype> Matrix<mytype> :: operator^ (int m)");
    if (m==0) {
        a.unit(line);
        return a;
    }

    a=(*this);
    return a.power(m);
}

template <typename mytype> Matrix<mytype>& Matrix<mytype>:: operator= (const Matrix<mytype> &m) {
    if (m.ptr==ptr) goto is_current_matrix;
    if ((line==m.line)&&(column==m.column)) goto is_equal;
    dealloc_matrix();
    alloc_matrix(m.line, m.column);
is_equal:
    for (int i=0; i<line; i++)
        for (int j=0; j<column; j++)
            ptr[i][j]=m.ptr[i][j];
    pos_x=m.pos_x;
    pos_y=m.pos_y;
    by_row=m.by_row;
is_current_matrix:
    return *this;
}

template <typename mytype> bool Matrix<mytype>::operator==(const Matrix<mytype> &m) {
    int i,j;
    if (m.ptr==ptr)
        return true;
    if ((line!=m.line) || (column!=m.column))
        handle_exception(10, "template <typename mytype> bool Matrix<mytype>::operator==(const Matrix<mytype> &m)");
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            if (ptr[i][j]!=m.ptr[i][j])
                return false;
    return true;
}

template <typename mytype> mytype Matrix<mytype>::det() {
    int i,j,k,l,temp=1;
    if (line!=column)
        handle_exception(1, "template <typename mytype> mytype Matrix<mytype>::det()");
    Matrix m = *this;
    mytype det=1;
    int semn=1;
    for (k=0; k<line-1; k++) {
        if (m.ptr[k][k]==0) {
            for (l=k+1; l<line; l++)
                if (m.ptr[l][k]!=0) {
                    m.swap_r(k,l);
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

template<typename mytype> int Matrix<mytype>::rank() {
    int i,j;
    int rang=0;
    Matrix p;
    if (line>column)
        transpose(p);
    else p=*this;
    p.pos_x=0;
    p.pos_y=0;
    while (p.pos_x<p.line-1) {
        if (p.ptr[p.pos_x][p.pos_y]==0) {
            for (i=p.pos_x+1; i<p.line; i++)
                if (p.ptr[i][p.pos_y]!=0) {
                    rang++;
                    p.swap_r(i,p.pos_x);
                    goto Prelucrare;
                }
            for (j=p.pos_y+1; j<p.column; j++)
                if (p.ptr[p.pos_x][j]!=0) {
                    rang++;
                    p.swap_c(j,p.pos_y);
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

template<typename mytype> void Matrix<mytype>::inversion(Matrix<mytype> &coeff, Matrix<mytype> &pseudo_inv) {
    int i,j,k,l;
    Matrix <mytype> temp;
    if ((ptr==coeff.ptr) || (ptr==pseudo_inv.ptr))
        handle_exception(25, "template<typename mytype> void Matrix<mytype>::inversion(Matrix<mytype> &coeff, Matrix<mytype> &pseudo_inv)");
    if (line!=column)
        handle_exception(1, "template<typename mytype> void Matrix<mytype>::inversion(Matrix<mytype> &coeff, Matrix<mytype> &pseudo_inv)");
    temp=*this;
    pseudo_inv.unit(line);
    coeff.resize(line,1);

    for (k=0; k<line-1; k++) {
        if (temp.ptr[k][k]==0) {
            for (l=k+1; l<line; l++) {
                if (temp.ptr[k][l]!=0) {
                    temp.swap_r(k,l);
                    pseudo_inv.swap_r(k,l);
                    goto Prelucrare;
                }
            }
            handle_exception(2, "template<typename mytype> void Matrix<mytype>::inversion(Matrix<mytype> &coeff, Matrix<mytype> &pseudo_inv)");
        }
Prelucrare:
        for (j=0; j<line; j++)
            for (i=k+1; i<line; i++) {
                if (j>k)
                    temp.ptr[i][j]=temp.ptr[i][j]*temp.ptr[k][k]- temp.ptr[k][j]*temp.ptr[i][k];
                pseudo_inv.ptr[i][j]=pseudo_inv.ptr[i][j]*temp.ptr[k][k] - pseudo_inv.ptr[k][j]*temp.ptr[i][k];
            }
    }
    for (k=0; k<line; k++)
        for (i=k+1; i<line; i++)
            temp.ptr[i][k]=0;
    if (temp.ptr[line-1][line-1]==0)
        handle_exception(2, "template<typename mytype> void Matrix<mytype>::inversion(Matrix<mytype> &coeff, Matrix<mytype> &pseudo_inv)");
    for (k=line-1; k>0; k--)
        for (i=0; i<=k-1; i++)
            for (j=0; j<=line-1; j++) {
                if (j<k)
                    temp.ptr[i][j]=temp.ptr[i][j]*temp.ptr[k][k]-temp.ptr[k][j]*temp.ptr[i][k];
                pseudo_inv.ptr[i][j]=pseudo_inv.ptr[i][j]*temp.ptr[k][k]-pseudo_inv.ptr[k][j]*temp.ptr[i][k];
            }
    for (k=0; k<line; k++)
        coeff.ptr[k][0]=temp.ptr[k][k];
}

template <typename mytype> void Matrix<mytype>:: transpose(Matrix<mytype> &m) {
    int i,j;
    Matrix temp;
    mytype **temp_ptr;
    if (ptr==m.ptr) {
        temp_ptr=temp.ptr;
        temp.ptr=ptr;
        ptr=temp_ptr;
        temp.line=line;
        temp.column=column;
        resize(column, line);
        for (i=0; i<line; i++)
            for (j=0; j<column; j++)
                ptr[i][j]=temp.ptr[j][i];
        return;
    }
    m.resize(column,line);
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            m.ptr[j][i]=ptr[i][j];
}

template <typename mytype> void Matrix<mytype>::sums(Matrix &m, int sum_type) {
    int i,j;
    mytype sum=0;
    if (m.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::sums(Matrix &m, int sum_type)");
    if (sum_type>4)
        handle_exception(21, "template <typename mytype> void Matrix<mytype>::sums(Matrix &m, int sum_type)");
    if (sum_type<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::sums(Matrix &m, int sum_type)");
    switch (sum_type) {
        case 0:
            m.resize(1,1);
            for (i=0; i<line; i++)
                for (j=0; j<column; j++)
                    sum=sum + ptr[i][j];
            m.ptr[0][0]=sum;
            return;
        case 1:
            m.resize(1,1);
            for (j=0; j<column; j++)
                sum=sum+ptr[pos_x][j];
            m.ptr[0][0]=sum;
            return;
        case 2:
            m.resize(line,1);
            for (i=0; i<line; i++) {
                m.ptr[i][0]=0;
                for (j=0; j<column; j++)
                    m.ptr[i][0]=m.ptr[i][0]+ptr[i][j];
            }
            return;
        case 3:
            m.resize(1,1);
            for (i=0; i<line; i++)
                sum=sum+ptr[i][pos_y];
            m.ptr[0][0]=sum;
            return;
        case 4:
            m.resize(1,column);
            for (j=0; j<column; j++) {
                m.ptr[0][j]=0;
                for (int i=0; i<line; i++)
                    m.ptr[0][j]=m.ptr[0][j]+ptr[i][j];
            }
            return;
    }
}

template <typename mytype> void Matrix<mytype>::products(Matrix &m, int prod) {
    int i,j;
    mytype product;
    if (m.ptr==ptr)
        handle_exception(25, "template <typename mytype> void Matrix<mytype>::products(Matrix &m, int prod)");
    if (prod>4)
        handle_exception(21, "template <typename mytype> void Matrix<mytype>::products(Matrix &m, int prod)");
    if (prod<0)
        handle_exception(16, "template <typename mytype> void Matrix<mytype>::products(Matrix &m, int prod)");
    switch (prod) {
        case 0:
            product=1;
            m.resize(1,1);
            for (i=0; i<line; i++)
                for (j=0; j<column; j++)
                    product = product * ptr[i][j];
            m.ptr[0][0]=product;
            return;
        case 1:
            product=1;
            m.resize(1,1);
            for (j=0; j<column; j++)
                product=product*ptr[pos_x][j];
            m.ptr[0][0]=product;
            return;
        case 2:
            m.resize(line,1);
            for (i=0; i<line; i++) {
                product=1;
                for (int j=0; j<column; j++)
                    product=product*ptr[i][j];
                m.ptr[i][0]=product;
            }
            return;
        case 3:
            m.resize(1,1);
            product=1;
            for (i=0; i<line; i++)
                product=product*ptr[i][pos_y];
            m.ptr[0][0]=product;
            return;
        case 4:
            m.resize(1,column);
            for (j=0; j<column; j++) {
                product=1;
                for (int i=0; i<line; i++)
                    product=product*ptr[i][j];
                m.ptr[0][j]=product;
            }
            return;
    }
}

template <typename mytype> void Matrix<mytype>::neg_matrix(Matrix<mytype> &m) {
    int i,j;
    if (m.ptr==ptr) goto negativation;
    m.resize(line,column);
negativation:
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            m.ptr[i][j]=(-1)*ptr[i][j];
}

template <typename mytype> void Matrix<mytype>::inv_matrix(Matrix<mytype> &m) {
    int i,j;
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            if (ptr[i][j]==0)
                handle_exception(23,"template <typename mytype> void Matrix<mytype>::inv_matrix(Matrix<mytype> &m)");
    if (m.ptr==ptr) goto inversion;
    m.resize(line,column);
inversion:
    for (i=0; i<line; i++)
        for (j=0; j<column; j++)
            m.ptr[i][j]=1/ptr[i][j];
}

template <typename mytype> void Matrix<mytype>::output(ostream &os, int n) {
    int i,j;
    switch (n) {
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

template <typename mytype> void Matrix<mytype>::input(istream &is, int n) {
    string s;
    int i,j;
    stringstream str_st(ios::in|ios::out);
    switch (n) {
        case 0:
            for (i=0; i<line; i++)
                for (j=0; j<column; j++) {
                    if (is.eof())
                        handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
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
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<pos_x<<"]["<<j<<"]= ";
                is>>ptr[pos_x][j];
            }
            return;
        case 3:
            for (i=0; i<line; i++) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<pos_y<<"]= ";
                is>>ptr[i][pos_y];
            }
            return;
        case 4:
            for(i=0; i<line; i++) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<i<<"]= ";
                is>>ptr[i][i];
            }
            return;
        case 5:
            for(i=line-1; i>=0; i--) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                cout<<"["<<i<<"]["<<line-1-i<<"]= ";
                is>>ptr[i][line-1-i];
            }
            return;
        case 6:
            read_discard(is);
            pos_x=0;
            for (i=0; i<line; i++) {
                read_text_line(is);
                pos_x++;
                f_x++;
            }
            return;
        case 7:
            read_discard(is);
            read_single_item(is);
            return;
        case 8:
            read_discard(is);
            read_text_line(is);
            return;
        case 9:
            read_discard(is);
            pos_x=0;
            for(i=0; i<line; i++) {
                read_single_item(is);
                pos_x++;
                f_x++;
            }
            return;
        case 10:
            read_discard(is);
            reset_xy();
            f_y=0;
            for (i=0; i<line; i++) {
                read_single_item(is);
                f_x++;
                pos_y=++pos_x;
                f_y++;
            }
            return;
        case 11:
            read_discard(is);
            f_y=line-1;
            pos_x=0;
            pos_y=line-1;
            for(i=0; i<line; i++) {
                read_single_item(is);
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
                        handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                    is>>ptr[i][j];
                }
            return;
        case 13:
            if (is.eof())
                handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
            is>>ptr[pos_x][pos_y];
            return;
        case 14:
            for (j=0; j<column; j++) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[pos_x][j];
            }
            return;
        case 15:
            for (i=0; i<line; i++) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][pos_y];
            }
            return;
        case 16:
            for (i=0; i<line; i++)  {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][i];
            }
            return;
        case 17:
            for (i=line-1; i>=0; i--) {
                if (is.eof())
                    handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
                is>>ptr[i][line-1-i];
            }
    }
}

template<typename mytype> int Matrix<mytype>:: partition(int first,int last,int pivot,int mode,int pos) {
    int i,j;
    switch(mode) {
        case 0:
            if (pivot!=last)
                swap_i(pos,pivot,pos,last);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (ptr[pos][i]<ptr[pos][last]));
                do j--;
                    while ((i!=j) && (ptr[pos][j]>ptr[pos][last]));
                if (i<j)
                    swap_i(pos,i,pos,j);
            }
            if (i!=last)
                swap_i(pos,i,pos,last);
            return i;
        case 1:
            if (pivot!=last)
                swap_i(pos, pivot, pos,last);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (ptr[pos][i]>ptr[pos][last]));
                do j--;
                    while ((i!=j) && (ptr[pos][j]<ptr[pos][last]));
                if (i<j)
                    swap_i(pos,i,pos,j);
            }
            if (i!=last)
                swap_i(pos,i,pos,last);
            return i;
        case 2:
            if (pivot!=last)
                swap_i(pivot,pos,last,pos);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (ptr[i][pos]<ptr[last][pos]));
                do j--;
                    while ((i!=j) && (ptr[j][pos]>ptr[last][pos]));
                if (i<j)
                    swap_i(i,pos,j,pos);
            }
            if (i!=last)
                swap_i(i,pos,last,pos);
            return i;
        case 3:
            if (pivot!=last)
                swap_i(pivot,pos,last,pos);
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (ptr[i][pos]>ptr[last][pos]));
                do j--;
                    while ((i!=j) && (ptr[j][pos]<ptr[last][pos]));
                if (i<j)
                    swap_i(i,pos,j,pos);
            }
            if (i!=last)
                swap_i(i,pos,last,pos);
            return i;
    }
}

template<typename mytype> int Matrix<mytype>:: partition(int first,int last,int pivot,int mode) {
    int i,j;
    mytype swap;
    switch(mode) {
        case 0:
            if (pivot!=last) {
                swap=item_l(pivot);
                item_l(pivot)=item_l(last);
                item_l(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (item_l(i)<item_l(last)));
                do j--;
                    while ((i!=j) && (item_l(j)>item_l(last)));
                if (i<j) {
                    swap=item_l(i);
                    item_l(i)=item_l(j);
                    item_l(j)=swap;
                }
            }
            if (i!=(last)) {
                swap=item_l(i);
                item_l(i)=item_l(last);
                item_l(last)=swap;
            }
            return i;
        case 1:
            if (pivot!=last) {
                swap=item_l(pivot);
                item_l(pivot)=item_l(last);
                item_l(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (item_l(i)>item_l(last)));
                do j--;
                    while ((i!=j) && (item_l(j)<item_l(last)));
                if (i<j) {
                    swap=item_l(i);
                    item_l(i)=item_l(j);
                    item_l(j)=swap;
                }
            }
            if (i!=(last)) {
                swap=item_l(i);
                item_l(i)=item_l(last);
                item_l(last)=swap;
            }
            return i;
        case 2:
            if (pivot!=last) {
                swap=item_c(pivot);
                item_c(pivot)=item_c(last);
                item_c(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (item_c(i)<item_c(last)));
                do j--;
                    while ((i!=j) && (item_c(j)>item_c(last)));
                if (i<j) {
                    swap=item_c(i);
                    item_c(i)=item_c(j);
                    item_c(j)=swap;
                }
            }
            if (i!=last) {
                swap=item_c(i);
                item_c(i)=item_c(last);
                item_c(last)=swap;
            }
            return i;
        case 3:
            if (pivot!=last) {
                swap=item_c(pivot);
                item_c(pivot)=item_c(last);
                item_c(last)=swap;
            }
            i=first-1; j=last;
            while (i<j) {
                do i++;
                    while ((i!=j) && (item_c(i)>item_c(last)));
                do j--;
                    while ((i!=j) && (item_c(j)<item_c(last)));
                if (i<j) {
                    swap=item_c(i);
                    item_c(i)=item_c(j);
                    item_c(j)=swap;
                }
            }
            if (i!=last) {
                swap=item_c(i);
                item_c(i)=item_c(last);
                item_c(last)=swap;
            }
            return i;
    }
}

template<typename mytype> void Matrix<mytype>::handle_exception(int error_code, char *nume_functie) {
    try {
        cerr<<"Exceptie in functia: "<<nume_functie<<endl;
        throw error_code;
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




