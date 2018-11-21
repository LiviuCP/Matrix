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
    DataType** getp() {return m_pMatrix; }
    DataType* getp(int i) {
        if (i<0) _handleException(16, "template<typename dataType> dataType* Matrix<dataType>::getp(int i)");
        return m_pMatrix[i%m_NrOfRows];
	} 
	
    int getNrOfRows() {return m_NrOfRows;}
    int getNrOfColumns() {return m_NrOfColumns; }
    int getPosX() {return m_PosX; }
    int getPosY() {return m_PosY; }
    int getFilePosX() {return s_FilePosX; }
    int getFilePosY() {return s_FilePosY; }
    void setPosX(int m) {m_PosX = abs(m)%m_NrOfRows; }
    void setPosY(int n) {m_PosY = abs(n)%m_NrOfColumns; }
    void setFilePosX(int m) {s_FilePosX = abs(m); }
    void setFilePosY(int n) {s_FilePosY = abs(n); }
    void setMatrixEntryMode(int matrixEntryMode) {m_MatrixEntryMode=abs(matrixEntryMode)%18; }
    void setMatrixPrintMode(int matrixPrintMode) {m_MatrixPrintMode=abs(matrixPrintMode)%6; }
    void setItemsToZero();

    void incrPosX() {if (m_PosX<m_NrOfRows-1) m_PosX++; else m_PosX=0; }
    void decrPosX() {if (m_PosX>0) m_PosX--; else m_PosX=m_NrOfRows-1; }
    void incrPosY() {if (m_PosY<m_NrOfColumns-1) m_PosY++; else m_PosY=0; }
    void decrPosY() {if (m_PosY>0) m_PosY--; else m_PosY=m_NrOfColumns-1; }

    void resetCurrentPos() {m_PosX=m_PosY=0; }
    void resetCurrentPosInFile() {s_FilePosX=0; s_FilePosY=0; }

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
    bool operator != (Matrix<DataType>& matrix) { if(m_pMatrix==matrix.m_pMatrix) return false; if (rank()!=matrix.rank()) return true; return false; }
    bool operator < (Matrix<DataType>& matrix) { if (m_pMatrix==matrix.m_pMatrix) return false; if (rank()<matrix.rank()) return true; return false; }
    bool operator <= (Matrix<DataType>& matrix) { if (m_pMatrix==matrix.m_pMatrix) return true; if (rank()<=matrix.rank()) return true; return false; }
    bool operator > (Matrix<DataType>& matrix) { if (m_pMatrix==matrix.m_pMatrix) return false; if (rank()>matrix.rank()) return true; return false; }
    bool operator >= (Matrix<DataType>& matrix) { if (m_pMatrix==matrix.m_pMatrix) return true; if (rank()>=matrix.rank()) return true; return false; }

    friend ostream &operator<<(ostream& out, Matrix<DataType>& matrix) {
        if(((matrix.m_MatrixPrintMode==4) || (matrix.m_MatrixPrintMode==5))&&(matrix.m_NrOfRows!=matrix.m_NrOfColumns))
            _handleException(1, "friend ostream &operator<<(ostream &os, Matrix &m)");
        matrix._writeMatrix(out, matrix.m_MatrixPrintMode);
        return out;
	} 
    friend istream &operator>> (istream& in, Matrix<DataType>& matrix){
        if(((matrix.m_MatrixEntryMode==4) || (matrix.m_MatrixEntryMode==5) || (matrix.m_MatrixEntryMode==10) || (matrix.m_MatrixEntryMode==11) || (matrix.m_MatrixEntryMode==16) || (matrix.m_MatrixEntryMode==17))&&(matrix.m_NrOfRows!=matrix.m_NrOfColumns))
            _handleException(1, "friend istream &operator>> (istream &is, Matrix &m)");
        matrix._readMatrix(in, matrix.m_MatrixEntryMode);
        return in;
	}

    DataType& operator[] (int index) {
        if (index<0) _handleException(16, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)") ;
        if (index>=m_NrOfRows*m_NrOfColumns) _handleException(18, "template <typename dataType> dataType& Matrix<dataType>::operator[] (int i)");
        if (m_WrapMatrixByRow) return _getItemForLineWrap(index);
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
        m_NrOfRows=abs(nrOfRows); m_NrOfColumns=abs(nrOfColumns);
        m_pMatrix=new DataType*[nrOfRows];
        for (i=0; i<nrOfRows; i++)
            m_pMatrix[i]=new DataType[nrOfColumns];
	}
	
    void _deallocMemory() {
        resetCurrentPos();
        for (int i=0; i<m_NrOfRows; i++)
            delete m_pMatrix[i];
        delete []m_pMatrix;
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

    void _readDiscard(istream &in) {
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
    DataType& _getItemForLineWrap(int oneDimensionalIndex) { return m_pMatrix[oneDimensionalIndex/m_NrOfColumns][oneDimensionalIndex%m_NrOfColumns]; }
    DataType& _getItemForColumnWrap(int oneDimensionalIndex) { return m_pMatrix[oneDimensionalIndex%m_NrOfRows][oneDimensionalIndex/m_NrOfRows]; }

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
        a.resizeNoInit(m_NrOfRows,m_NrOfColumns);
        for (int i=0; i<m_NrOfRows; i++)
            for (int j=0; j<m_NrOfColumns; j++)
                a.m_pMatrix[i][j]=scalar*m_pMatrix[i][j];
		return a; 
	} 
	
    void _split(Matrix<DataType>& m1, Matrix<DataType>& m2, int splitRowColumnNr) {
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

    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix) {
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

    static int s_FilePosX;
    static int s_FilePosY;

    DataType** m_pMatrix;
    int m_NrOfRows;
    int m_NrOfColumns;
    int m_PosX;
    int m_PosY;
    int m_MatrixPrintMode;
    int m_MatrixEntryMode;
    bool m_WrapMatrixByRow;
};
