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
    ~Matrix() {_deallocMemory();}

    DataType& get(int i,int j);
    DataType** getp() {return ptr; }
    DataType* getp(int i) {
        if (i<0) _handleException(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
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
            _handleException(3,"template <typename dataType> void Matrix<dataType>::resize(int m, int n)");
        _deallocMemory(); _allocMemory(m, n);
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

    void applyCoefficientsToRow (const Matrix<DataType>& coeff, Matrix<DataType>& src, bool _multiply);
    void applyCoefficientsToColumn (const Matrix<DataType>& coeff, Matrix<DataType>& src, bool _multiply);

    Matrix<DataType> operator+ (const Matrix<DataType>& matrix);
    Matrix<DataType> operator- (const Matrix<DataType>& matrix);
    Matrix<DataType> operator* (const Matrix<DataType>& matrix);
    friend Matrix<DataType> operator*(const DataType& data, Matrix<DataType>& matrix) {return matrix._multiply(data);}
    Matrix<DataType> operator*(const DataType& data) {return _multiply(data);}
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
            _handleException(1, "friend ostream &operator<<(ostream &os, Matrix &m)");
        matrix._writeMatrix(out, matrix.mprint);
        return out;
	} 
    friend istream &operator>> (istream& in, Matrix<DataType>& matrix){
        if(((matrix.entdat==4) || (matrix.entdat==5) || (matrix.entdat==10) || (matrix.entdat==11) || (matrix.entdat==16) || (matrix.entdat==17))&&(matrix.line!=matrix.column))
            _handleException(1, "friend istream &operator>> (istream &is, Matrix &m)");
        matrix._readMatrix(in, matrix.entdat);
        return in;
	}

    DataType& operator[] (int index) {
        if (index<0) _handleException(16, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)") ;
        if (index>=line*column) _handleException(18, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
        if (by_row) return _getItemForLineWrap(index);
        return _getItemForColumnWrap(index);
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
    void _allocMemory(int nrOfRows, int nrOfColumns){
		int i;
        resetCurrentPos();
        line=abs(nrOfRows); column=abs(nrOfColumns);
        ptr=new DataType*[nrOfRows];
        for (i=0; i<nrOfRows; i++)
            ptr[i]=new DataType[nrOfColumns];
	}
	
    void _deallocMemory() {
        resetCurrentPos();
		for (int i=0; i<line; i++) 
			delete ptr[i]; 
		delete []ptr;
	}
	
    void _writeMatrix(ostream& os, int mode);
    void _readMatrix(istream& is, int mode);

    void _readTextLine(istream &in) {
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
		for (j=0; j<column; j++) { 
			while(s[k]==' ' && k<l) 
				k++;
			if (k==l) 
                _handleException(27, "friend istream &operator>> (istream &is, Matrix &m)");
			do 
				str_st.put(s[k++]);
			while(s[k]!=' ' && k<l);
			str_st>>ptr[pos_x][j];
			str_st.str("");
			str_st.clear();
		}
	}		

    void _readSingleItem(istream &in) {
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
		for (j=0; j<f_y; j++) {
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
		str_st>>ptr[pos_x][pos_y];
		str_st.str("");
		str_st.clear();
	}

    void _readDiscard(istream &in) {
		string s;
		int i;
        in.clear();
        in.seekg(0);
		for (i=0; i<f_x; i++) { 
            if (in.eof())
                _handleException (26, "friend istream &operator>> (istream &is, Matrix &m)");
            getline(in,s);
			s="";
			s.clear();
		}
	}

    void _quickSort(int first, int last, int mode, int pos){
		if (last>first) {
			int pivot=(first+last)/2;
            int k=_createSortingPartition(first,last,pivot,mode,pos);
            _quickSort(first,k-1,mode,pos);
            _quickSort(k+1,last,mode,pos);
		}
	} 
    void _quickSort(int first, int last, int mode){
		if (last>first) {
			int pivot=(first+last)/2;
            int k=_createSortingPartition(first,last,pivot,mode);
            _quickSort(first,k-1,mode);
            _quickSort(k+1,last,mode);
		}
	}

    int _createSortingPartition(int first, int last, int pivot, int mode, int pos);
    int _createSortingPartition(int first, int last, int pivot, int mode);
    DataType& _getItemForLineWrap(int oneDimensionalIndex) { return ptr[oneDimensionalIndex/column][oneDimensionalIndex%column]; }
    DataType& _getItemForColumnWrap(int oneDimensionalIndex) { return ptr[oneDimensionalIndex%line][oneDimensionalIndex/line]; }

    static void _handleException(int errorType, char* function);
	
    Matrix<DataType> _power(int exp){
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
	
    Matrix _multiply(const DataType& scalar){
		Matrix a;
        a.resizeNoInit(line,column);
		for (int i=0; i<line; i++) 
			for (int j=0; j<column; j++) 
                a.ptr[i][j]=scalar*ptr[i][j];
		return a; 
	} 
	
    void _split(Matrix<DataType>& m1, Matrix<DataType>& m2, int splitRowColumnNr) {
		int i,j;
        m1._deallocMemory(); m2._deallocMemory();
		if (by_row) {
            m1._allocMemory(splitRowColumnNr,column); m2._allocMemory(line-splitRowColumnNr, column);
            for (i=0; i<splitRowColumnNr; i++)
				for (j=0; j<column; j++)
					m1.ptr[i][j]=ptr[i][j];
            for (i=splitRowColumnNr; i<line; i++)
				for (j=0; j<column; j++) 
                    m2.ptr[i-splitRowColumnNr][j]=ptr[i][j];
			return; 
		}

    m1._allocMemory(line,splitRowColumnNr); m2._allocMemory(line,column-splitRowColumnNr);
	for (i=0; i<line; i++)
        for (j=0; j<splitRowColumnNr; j++)
			m1.ptr[i][j]=ptr[i][j];
	for (i=0; i<line; i++) 
        for (j=splitRowColumnNr; j<column; j++)
            m2.ptr[i][j-splitRowColumnNr]=ptr[i][j];
	}

    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix) {
		int i,j;
		if (by_row) {
            resizeNoInit(firstSrcMatrix.line+secondSrcMatrix.line, firstSrcMatrix.column);
            for (i=0; i<firstSrcMatrix.line; i++)
				for (j=0; j<column; j++)
                    ptr[i][j]=firstSrcMatrix.ptr[i][j];
            for (i=firstSrcMatrix.line; i<line; i++)
				for (j=0; j<column; j++)
                    ptr[i][j]=secondSrcMatrix.ptr[i-firstSrcMatrix.line][j];
			return; 
		} 
        resizeNoInit(firstSrcMatrix.line, firstSrcMatrix.column+secondSrcMatrix.column);
		for(i=0; i<line; i++) 
            for (j=0; j<firstSrcMatrix.column; j++)
                ptr[i][j]=firstSrcMatrix.ptr[i][j];
		for(i=0; i<line; i++)
            for (j=firstSrcMatrix.column; j<column; j++)
                ptr[i][j]=secondSrcMatrix.ptr[i][j-firstSrcMatrix.column];
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
