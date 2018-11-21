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

template <typename DataType>
class Matrix
{
public: 
    Matrix();
    Matrix(int nrOfRows, int nrOfColumns);
    Matrix(int nrOfRowsColumns);
    Matrix(DataType** matrixPtr, int nrOfRows, int nrOfColumns);
    Matrix(DataType* matrixPtr, int nrOfRows, int nrOfColumns);
    Matrix(int nrOfRows, int nrOfColumns, istream &in);
    Matrix(const Matrix<DataType>& matrix);
    ~Matrix();

    DataType& get(int i,int j);
    DataType** getp();
    DataType* getp(int i);
	
    int getNrOfRows();
    int getNrOfColumns();
    int getPosX();
    int getPosY();
    int getFilePosX();
    int getFilePosY();
    void setPosX(int m);
    void setPosY(int n);
    void setFilePosX(int filePosX);
    void setFilePosY(int filePosY);
    void setMatrixEntryMode(int matrixEntryMode);
    void setMatrixPrintMode(int matrixPrintMode);
    void setItemsToZero();

    void incrPosX();
    void decrPosX();
    void incrPosY();
    void decrPosY();

    void resetCurrentPos();
    void resetCurrentPosInFile();

    void resizeNoInit(int nrOfRows, int nrOfColumns);
    void resize(int nrOfRows, int nrOfColumns);

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
    friend Matrix<DataType> operator*(const DataType& data, Matrix<DataType>& matrix);
    Matrix<DataType> operator*(const DataType& data);
    Matrix<DataType> operator^ (int exp);
    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    bool operator== (const Matrix<DataType>& matrix);
    bool operator != (Matrix<DataType>& matrix);
    bool operator < (Matrix<DataType>& matrix);
    bool operator <= (Matrix<DataType>& matrix);
    bool operator > (Matrix<DataType>& matrix);
    bool operator >= (Matrix<DataType>& matrix);

    friend ostream &operator<<(ostream& out, Matrix<DataType>& matrix);
    friend istream &operator>> (istream& in, Matrix<DataType>& matrix);

    DataType& operator[] (int index);

	int rank();
    void getInverseMatrix(Matrix<DataType> &coeff, Matrix<DataType>& pseudoInverse);
    void getTransposedMatrix(Matrix<DataType>& result);
    DataType determinant();

    void sums(Matrix<DataType>& result, int mode);
    void products(Matrix<DataType>& result, int mode);

    void getNegativeMatrix(Matrix<DataType>& result);
    void getInverseElementsMatrix(Matrix<DataType>& result);

private:
    void _allocMemory(int nrOfRows, int nrOfColumns);
	
    void _deallocMemory();
	
    void _writeMatrix(ostream& os, int mode);
    void _readMatrix(istream& is, int mode);

    void _readTextLine(istream &in);

    void _readSingleItem(istream &in);

    void _readDiscard(istream &in);

    void _quickSort(int first, int last, int mode, int pos);
    void _quickSort(int first, int last, int mode);

    int _createSortingPartition(int first, int last, int pivot, int mode, int pos);
    int _createSortingPartition(int first, int last, int pivot, int mode);
    DataType& _getItemForLineWrap(int oneDimensionalIndex);
    DataType& _getItemForColumnWrap(int oneDimensionalIndex);

    static void _handleException(int errorType, char* function);
	
    Matrix<DataType> _power(int exp);
	
    Matrix<DataType> _multiply(const DataType& scalar);
	
    void _split(Matrix<DataType>& m1, Matrix<DataType>& m2, int splitRowColumnNr);

    void _concatenate(Matrix<DataType>& firstSrcMatrix,Matrix<DataType>& secondSrcMatrix);

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
