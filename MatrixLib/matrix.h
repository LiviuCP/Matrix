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

template <typename DataType> class Matrix {

public: 
    Matrix();
    Matrix(int nrOfRows, int nrOfColumns);
    Matrix(int nrOfRowsColumns);
    Matrix(DataType** matrixPtr, int nrOfRows, int nrOfColumns);
    Matrix(DataType* matrixPtr, int nrOfRows, int nrOfColumns);
    Matrix(int nrOfRows, int nrOfColumns, istream &in);
    Matrix(const Matrix<DataType>& matrix);
    ~Matrix() {dealloc_matrix();}

    DataType& get(int i,int j);
    DataType** getp() {return ptr; }
    DataType* getp(int i) {
        if (i<0) handle_exception(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
		return ptr[i%line];
	} 
	
    int getNrOfRows() {return line;}
    int getNrOfColumns() {return column; }
    int getPosX() {return pos_x; }
    int getPosY() {return pos_y; }
    int getFilePosX() {return f_x; }
    int getFilePosY() {return f_y; }
    void setPosX(int m) {pos_x = abs(m)%line; }
    void setPosY(int n) {pos_y = abs(n)%column; }
    void setFilePosX(int m) {f_x = abs(m); }
    void setFilePosY(int n) {f_y = abs(n); }
    void setMatrixEntryMode(int matrixEntryMode) {entdat=abs(matrixEntryMode)%18; }
    void setMatrixPrintMode(int matrixPrintMode) {mprint=abs(matrixPrintMode)%6; }
    void setItemsToZero();

    void incrPosX() {if (pos_x<line-1) pos_x++; else pos_x=0; }
    void decrPosX() {if (pos_x>0) pos_x--; else pos_x=line-1; }
    void incrPosY() {if (pos_y<column-1) pos_y++; else pos_y=0; }
    void decrPosY() {if (pos_y>0) pos_y--; else pos_y=column-1; }

    void resetCurrentPos() {pos_x=pos_y=0; }
    void resetCurrentPosInFile() {f_x=0; f_y=0; }

    void resizeNoInit(int m, int n) {
		if ((m<=0) || (n<=0)) 
            handle_exception(3,"template <typename dataType> void Matrix<dataType>::resize(int m, int n)");
		dealloc_matrix(); alloc_matrix(m, n);
	}
    void resize(int m, int n);

    void transformToUnitMatrix(int nrOfRowsColumns);
    void transformToZeroMatrix(int nrOfRows, int nrOfColumns);

    void swapItem(int rowNr, int columnNr, Matrix<DataType>& matrix, int matrixRowNr, int matrixColumnNr);
    void swapRow(int rowNr, Matrix<DataType>& matrix, int matrixRowNr);
    void swapColumn(int columnNr, Matrix<DataType>& matrix, int matrixColumnNr);
    void swapRowColumn(int rowNr, Matrix<DataType>& matrix, int matrixColumnNr);
    void swapItem(int firstRowNr, int firstColumnNr, int secondRowNr, int secondColumnNr);
    void swapRow(int firstRowNr, int secondRowNr);
    void swapColumn(int firstColumnNr, int secondColumnNr);
    void swapRowColumn(int rowColumnNr);

    void swapWithMatrix(Matrix<DataType> &m);

    void sortLineColumn(int lineColumnNr, int mode);
    void sortAllElements(int mode);

    void insertColumn(int columnNr);
    void insertRow (int rowNr);
    void deleteColumn(int columnNr);
    void deleteRow (int rowNr);

    void addRowToColumn(int rowNr, DataType& coeff, Matrix<DataType>& src, int srcColumnNr, DataType& srcCoeff, Matrix<DataType>& dest, int destColumnNr);
    void addColumnToRow(int columnNr, DataType& coeff, Matrix<DataType>& src, int srcRowNr, DataType& srcCoeff, Matrix<DataType>& dest, int destRowNr);
    void addRowToRow(int rowNr, DataType& coeff, Matrix<DataType>& src, int srcRowNr, DataType& srcCoeff, Matrix<DataType>& dest, int destRowNr);
    void addColumnToColumn(int columnNr, DataType& coeff, Matrix<DataType>& src, int srcColumnNr, DataType& srcCoeff, Matrix<DataType> &dest, int destColumnNr);

    void concatenate(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void split(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, int splitRowColumnNr);

    void copy(const Matrix<DataType>& src, int nrOfRows, int nrOfColumns);
    void copy(DataType** src, int nrOfRows, int nrOfColumns);
    void copy(DataType* src, int nrOfRows, int nrOfColumns);

    void applyCoefficientsToRow (const Matrix<DataType>& coeff, Matrix<DataType>& src, bool multiply);
    void applyCoefficientsToColumn (const Matrix<DataType>& coeff, Matrix<DataType>& src, bool multiply);

    Matrix<DataType> operator+ (const Matrix<DataType>& matrix);
    Matrix<DataType> operator- (const Matrix<DataType>& matrix);
    Matrix<DataType> operator* (const Matrix<DataType>& matrix);
    friend Matrix<DataType> operator*(const DataType& data, Matrix<DataType>& matrix) {return matrix.multiply(data);}
    Matrix<DataType> operator*(const DataType& data) {return multiply(data);}
    Matrix<DataType> operator^ (int exp);
    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    bool operator== (const Matrix<DataType>& matrix);
    bool operator != (Matrix<DataType>& matrix) { if(ptr==matrix.ptr) return false; if (rank()!=matrix.rank()) return true; return false; }
    bool operator < (Matrix<DataType>& matrix) { if (ptr==matrix.ptr) return false; if (rank()<matrix.rank()) return true; return false; }
    bool operator <= (Matrix<DataType>& matrix) { if (ptr==matrix.ptr) return true; if (rank()<=matrix.rank()) return true; return false; }
    bool operator > (Matrix<DataType>& matrix) { if (ptr==matrix.ptr) return false; if (rank()>matrix.rank()) return true; return false; }
    bool operator >= (Matrix<DataType>& matrix) { if (ptr==matrix.ptr) return true; if (rank()>=matrix.rank()) return true; return false; }

    friend ostream &operator<<(ostream& out, Matrix<DataType>& matrix) {
        if(((matrix.mprint==4) || (matrix.mprint==5))&&(matrix.line!=matrix.column))
			handle_exception(1, "friend ostream &operator<<(ostream &os, Matrix &m)"); 
        matrix.output(out, matrix.mprint);
        return out;
	} 
    friend istream &operator>> (istream& in, Matrix<DataType>& matrix){
        if(((matrix.entdat==4) || (matrix.entdat==5) || (matrix.entdat==10) || (matrix.entdat==11) || (matrix.entdat==16) || (matrix.entdat==17))&&(matrix.line!=matrix.column))
			handle_exception(1, "friend istream &operator>> (istream &is, Matrix &m)");
        matrix.input(in, matrix.entdat);
        return in;
	}

    DataType& operator[] (int index) {
        if (index<0) handle_exception(16, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)") ;
        if (index>=line*column) handle_exception(18, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
        if (by_row) return item_l(index);
        return item_c(index);
	}

	int rank();
    void getInverseMatrix(Matrix<DataType> &coeff, Matrix<DataType>& pseudoInverse);
    void getTransposedMatrix(Matrix<DataType>& result);
    DataType determinant();

    void sums(Matrix<DataType>& result, int mode);
    void products(Matrix<DataType>& result, int mode);

    void getNegativeMatrix(Matrix<DataType>& result);
    void getInverseElementsMatrix(Matrix<DataType>& result);

private:
	void alloc_matrix(int m, int n){
		int i;
        resetCurrentPos();
		line=abs(m); column=abs(n); 
        ptr=new DataType*[m];
		for (i=0; i<m; i++)  
            ptr[i]=new DataType[n];
	}
	
	void dealloc_matrix() {
        resetCurrentPos();
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
    DataType &item_l(int i) { return ptr[i/column][i%column]; }
    DataType &item_c(int i) { return ptr[i%line][i/line]; }

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
	
    Matrix multiply(const DataType &typ){
		Matrix a;
        a.resizeNoInit(line,column);
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

    void cat_matr(Matrix<DataType> &m1,Matrix<DataType> &m2) {
		int i,j;
		if (by_row) {
            resizeNoInit(m1.line+m2.line, m1.column);
			for (i=0; i<m1.line; i++) 
				for (j=0; j<column; j++)
					ptr[i][j]=m1.ptr[i][j];
			for (i=m1.line; i<line; i++)
				for (j=0; j<column; j++)
					ptr[i][j]=m2.ptr[i-m1.line][j];
			return; 
		} 
        resizeNoInit(m1.line, m1.column+m2.column);
		for(i=0; i<line; i++) 
			for (j=0; j<m1.column; j++) 
				ptr[i][j]=m1.ptr[i][j];
		for(i=0; i<line; i++)
			for (j=m1.column; j<column; j++) 
				ptr[i][j]=m2.ptr[i][j-m1.column];
	}

    DataType **ptr;
    int line,column;
    int pos_x;
    int pos_y;
    int mprint;
    int entdat;
    static int f_x;
    static int f_y;
    bool by_row;
};
