#include <iostream>
#include <fstream>
#include <sstream> 
#include <strstream>
#include <stdlib.h>
#include <math.h>
#include <string> 
#define mul true 
#define div false
using namespace std; 

template <typename mytype> class Matrix {

public: 
    Matrix();
    Matrix(int m, int n);
    Matrix(int n);
    Matrix(mytype** m, int ln, int cl);
    Matrix(mytype* m, int ln, int cl);
    Matrix(int m, int n, istream &is);
    Matrix(const Matrix &m);
    ~Matrix() {dealloc_matrix();}

	mytype& get(int i,int j); 
	mytype **getp() {return ptr; }
	mytype *getp(int i) {
		if (i<0) handle_exception(16, "template<typename mytype> mytype* Matrix<mytype>::getp(int i)"); 
		return ptr[i%line];
	} 
	
	int get_lines() {return line;}
	int get_columns() {return column; }
	int get_x() {return pos_x; }
	int get_y() {return pos_y; }
	int get_fx() {return f_x; }
	int get_fy() {return f_y; }
	void set_x(int m) {pos_x = abs(m)%line; }
	void set_y(int n) {pos_y = abs(n)%column; }
	void set_fx(int m) {f_x = abs(m); }
	void set_fy(int n) {f_y = abs(n); }
    void set_entdat(int m) {entdat=abs(m)%18; }
    void set_mprint(int m) {mprint=abs(m)%6; }
    void set_zero();

	void inc_x() {if (pos_x<line-1) pos_x++; else pos_x=0; }
	void dec_x() {if (pos_x>0) pos_x--; else pos_x=line-1; }
	void inc_y() {if (pos_y<column-1) pos_y++; else pos_y=0; }
	void dec_y() {if (pos_y>0) pos_y--; else pos_y=column-1; }

	void reset_xy() {pos_x=pos_y=0; }
	void reset_fxy() {f_x=0; f_y=0; }

    void resize(int m, int n) {
		if ((m<=0) || (n<=0)) 
			handle_exception(3,"template <typename mytype> void Matrix<mytype>::resize(int m, int n)"); 
		dealloc_matrix(); alloc_matrix(m, n);
	}
	void resize_m(int m, int n);

	void unit(int m);
	void null_matrix(int m, int n);

    void swap_i(int r1, int c1, Matrix &m2, int r2, int c2);
	void swap_r(int r1, Matrix &m2, int r2);
	void swap_c(int c1, Matrix &m2, int c2);
	void swap_rc(int r1, Matrix &m2, int c2);
	void swap_i(int r1, int c1, int r2, int c2);
	void swap_r(int r1, int r2);
	void swap_c(int c1, int c2);
	void swap_rc(int rc1);

    void rv_mat(Matrix &m);

    void sort_lc(int pos, int mode);
	void sort_matr(int mode);

    void insert_col(int n);
	void insert_row (int m);
	void delete_col(int n);
	void delete_row (int m);

    void add_rc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1);
	void add_cr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1);
	void add_rr(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1);
	void add_cc(int n1, mytype &m1, Matrix &src, int n2, mytype &m2, Matrix &dest, int p1);

    void cat(Matrix &m1, Matrix &m2);
	void split(Matrix &m1, Matrix &m2, int m);

    void copy(const Matrix &m, int step1, int step2);
	void copy(mytype **m, int ln, int cl);
	void copy(mytype *m, int ln, int cl);

    void coef_row (const Matrix &coeff, Matrix &src, bool multiply);
	void coef_col (const Matrix &coeff, Matrix &src, bool multiply);

    Matrix operator+ (const Matrix &m);
	Matrix operator- (const Matrix &m);
	Matrix operator* (const Matrix &m);
	friend Matrix operator*(const mytype &typ, Matrix &m) {return m.multiply(typ);}
	Matrix operator*(const mytype &typ) {return multiply(typ);}
	Matrix operator^ (int n);
	Matrix& operator= (const Matrix &m);
	bool operator== (const Matrix &m);
	bool operator != (Matrix &m) { if(ptr==m.ptr) return false; if (rank()!=m.rank()) return true; return false; }
	bool operator < (Matrix &m) { if (ptr==m.ptr) return false; if (rank()<m.rank()) return true; return false; }
	bool operator <= (Matrix &m) { if (ptr==m.ptr) return true; if (rank()<=m.rank()) return true; return false; }
	bool operator > (Matrix &m) { if (ptr==m.ptr) return false; if (rank()>m.rank()) return true; return false; }
	bool operator >= (Matrix &m) { if (ptr==m.ptr) return true; if (rank()>=m.rank()) return true; return false; }

    friend ostream &operator<<(ostream &os, Matrix &m) {
		if(((m.mprint==4) || (m.mprint==5))&&(m.line!=m.column))
			handle_exception(1, "friend ostream &operator<<(ostream &os, Matrix &m)"); 
		m.output(os, m.mprint); 
		return os; 
	} 
	friend istream &operator>> (istream &is, Matrix &m){
		if(((m.entdat==4) || (m.entdat==5) || (m.entdat==10) || (m.entdat==11) || (m.entdat==16) || (m.entdat==17))&&(m.line!=m.column))
			handle_exception(1, "friend istream &operator>> (istream &is, Matrix &m)");
		m.input(is, m.entdat); 
		return is;  
	}

	mytype& operator[] (int i) {
	 	if (i<0) handle_exception(16, "template <typename mytype> mytype& Matrix<mytype>::operator[] (int i)") ;
		if (i>=line*column) handle_exception(18, "template <typename mytype> mytype& Matrix<mytype>::operator[] (int i)");
		if (by_row) return item_l(i);
		return item_c(i);
	}

	int rank();
	void inversion(Matrix &coeff, Matrix &pseudo_inv);
	void transpose(Matrix &m);
	mytype det();

	void sums(Matrix &m, int sum_type);
	void products(Matrix &m, int prod);

	void neg_matrix(Matrix &m);
	void inv_matrix(Matrix &m);

private:
	void alloc_matrix(int m, int n){
		int i;
		reset_xy();
		line=abs(m); column=abs(n); 
		ptr=new mytype*[m];
		for (i=0; i<m; i++)  
			ptr[i]=new mytype[n];
	}
	
	void dealloc_matrix() {
		reset_xy();
		for (int i=0; i<line; i++) 
			delete ptr[i]; 
		delete []ptr;
	}
	
	void output(ostream &os, int n);
	void input(istream &is, int n);

	void read_text_line(istream &is) { 
		string s;
		int j;
		int k=0;
		int l;
		stringstream str_st;
		if (is.eof())
			handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
		getline(is,s);
		l=s.size();
		if (l==0)
			handle_exception (28, "friend istream &operator>> (istream &is, Matrix &m)");
		for (j=0; j<column; j++) { 
			while(s[k]==' ' && k<l) 
				k++;
			if (k==l) 
				handle_exception(27, "friend istream &operator>> (istream &is, Matrix &m)");
			do 
				str_st.put(s[k++]);
			while(s[k]!=' ' && k<l);
			str_st>>ptr[pos_x][j];
			str_st.str("");
			str_st.clear();
		}
	}		

	void read_single_item(istream &is) { 
		string s; 
		int j;
		int k=0;
		int l;
		stringstream str_st;
		if (is.eof())
			handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
		getline(is,s);
		l=s.size();
		if (l==0)
			handle_exception (28, "friend istream &operator>> (istream &is, Matrix &m)");
		for (j=0; j<f_y; j++) {
			while (s[k]==' ' && k<l)
				k++;
			if (k==l) 
				handle_exception(27, "friend istream &operator>> (istream &is, Matrix &m)");
			do
				k++; 
			while(s[k]!=' ' && k<l);
		}
		if (k==l) 
			handle_exception(27, "friend istream &operator>> (istream &is, Matrix &m)");
		while(s[k]==' ' && k<l)
			k++;
		if (k==l) 
			handle_exception(27, "friend istream &operator>> (istream &is, Matrix &m)");
		do 
			str_st.put(s[k++]);
		while(s[k]!=' ' && k<l);
		str_st>>ptr[pos_x][pos_y];
		str_st.str("");
		str_st.clear();
	}

	void read_discard(istream &is) { 
		string s;
		int i;
		is.clear();
		is.seekg(0);
		for (i=0; i<f_x; i++) { 
			if (is.eof())
				handle_exception (26, "friend istream &operator>> (istream &is, Matrix &m)");
			getline(is,s);
			s="";
			s.clear();
		}
	}

	void q_sort(int first, int last, int mode, int pos){
		if (last>first) {
			int pivot=(first+last)/2;
			int k=partition(first,last,pivot,mode,pos);
			q_sort(first,k-1,mode,pos);
			q_sort(k+1,last,mode,pos);
		}
	} 
	void q_sort(int first, int last, int mode){
		if (last>first) {
			int pivot=(first+last)/2;
			int k=partition(first,last,pivot,mode);
			q_sort(first,k-1,mode);
			q_sort(k+1,last,mode);
		}
	}

	int partition(int first, int last, int pivot, int mode, int pos);
	int partition(int first, int last, int pivot, int mode);
	mytype &item_l(int i) { return ptr[i/column][i%column]; }
	mytype &item_c(int i) { return ptr[i%line][i/line]; }

	static void handle_exception(int error_code, char *nume_functie);
	
	Matrix power(int n){
		Matrix b; 
		if (n==1) 
			return *this; 
		else {
			b=power(n/2);
			if (n%2==0)
				return b*b;
			else 
				return b*b*(*this);
		}
	}   
	
	Matrix multiply(const mytype &typ){
		Matrix a;
		a.resize(line,column);
		for (int i=0; i<line; i++) 
			for (int j=0; j<column; j++) 
				a.ptr[i][j]=typ*ptr[i][j]; 
		return a; 
	} 
	
	void split_matr(Matrix &m1, Matrix &m2, int m) { 
		int i,j;
		m1.dealloc_matrix(); m2.dealloc_matrix(); 
		if (by_row) {
			m1.alloc_matrix(m,column); m2.alloc_matrix(line-m, column); 
			for (i=0; i<m; i++) 
				for (j=0; j<column; j++)
					m1.ptr[i][j]=ptr[i][j];
			for (i=m; i<line; i++) 
				for (j=0; j<column; j++) 
					m2.ptr[i-m][j]=ptr[i][j];
			return; 
		}

	m1.alloc_matrix(line,m); m2.alloc_matrix(line,column-m); 
	for (i=0; i<line; i++)
		for (j=0; j<m; j++)
			m1.ptr[i][j]=ptr[i][j];
	for (i=0; i<line; i++) 
		for (j=m; j<column; j++)
			m2.ptr[i][j-m]=ptr[i][j];
	}

	void cat_matr(Matrix<mytype> &m1,Matrix<mytype> &m2) {
		int i,j;
		if (by_row) {
			resize(m1.line+m2.line, m1.column);
			for (i=0; i<m1.line; i++) 
				for (j=0; j<column; j++)
					ptr[i][j]=m1.ptr[i][j];
			for (i=m1.line; i<line; i++)
				for (j=0; j<column; j++)
					ptr[i][j]=m2.ptr[i-m1.line][j];
			return; 
		} 
		resize(m1.line, m1.column+m2.column);
		for(i=0; i<line; i++) 
			for (j=0; j<m1.column; j++) 
				ptr[i][j]=m1.ptr[i][j];
		for(i=0; i<line; i++)
			for (j=m1.column; j<column; j++) 
				ptr[i][j]=m2.ptr[i][j-m1.column];
	}

    mytype **ptr;
    int line,column;
    int pos_x;
    int pos_y;
    int mprint;
    int entdat;
    static int f_x;
    static int f_y;
    bool by_row;
};
