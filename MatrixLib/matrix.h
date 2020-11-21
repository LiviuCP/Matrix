#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include <utility>
#include <cmath>

#include "errorhandling.h"


template <typename DataType>
class Matrix
{
public: 
    using size_type = int;
    using diff_type = int;

    class ZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ZIterator();

        ZIterator operator++();
        ZIterator operator++(int unused);
        ZIterator operator--();
        ZIterator operator--(int unused);

        ZIterator operator+(difference_type offset);
        ZIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ZIterator& it) const;

        bool operator==(const ZIterator& it) const;
        bool operator!=(const ZIterator& it) const;
        bool operator<(const ZIterator& it) const;
        bool operator<=(const ZIterator& it) const;
        bool operator>(const ZIterator& it) const;
        bool operator>=(const ZIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class ConstZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = const DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ConstZIterator();

        ConstZIterator operator++();
        ConstZIterator operator++(int unused);
        ConstZIterator operator--();
        ConstZIterator operator--(int unused);

        ConstZIterator operator+(difference_type offset);
        ConstZIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ConstZIterator& it) const;

        bool operator==(const ConstZIterator& it) const;
        bool operator!=(const ConstZIterator& it) const;
        bool operator<(const ConstZIterator& it) const;
        bool operator<=(const ConstZIterator& it) const;
        bool operator>(const ConstZIterator& it) const;
        bool operator>=(const ConstZIterator& it) const;

        reference operator*() const;
        const value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ConstZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class ReverseZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ReverseZIterator();

        ReverseZIterator operator++();
        ReverseZIterator operator++(int unused);
        ReverseZIterator operator--();
        ReverseZIterator operator--(int unused);

        ReverseZIterator operator+(difference_type offset);
        ReverseZIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ReverseZIterator& it) const;

        bool operator==(const ReverseZIterator& it) const;
        bool operator!=(const ReverseZIterator& it) const;
        bool operator<(const ReverseZIterator& it) const;
        bool operator<=(const ReverseZIterator& it) const;
        bool operator>(const ReverseZIterator& it) const;
        bool operator>=(const ReverseZIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ReverseZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class ConstReverseZIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = const DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ConstReverseZIterator();

        ConstReverseZIterator operator++();
        ConstReverseZIterator operator++(int unused);
        ConstReverseZIterator operator--();
        ConstReverseZIterator operator--(int unused);

        ConstReverseZIterator operator+(difference_type offset);
        ConstReverseZIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ConstReverseZIterator& it) const;

        bool operator==(const ConstReverseZIterator& it) const;
        bool operator!=(const ConstReverseZIterator& it) const;
        bool operator<(const ConstReverseZIterator& it) const;
        bool operator<=(const ConstReverseZIterator& it) const;
        bool operator>(const ConstReverseZIterator& it) const;
        bool operator>=(const ConstReverseZIterator& it) const;

        reference operator*() const;
        const value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ConstReverseZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class DIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;

    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        DIterator() = delete;

        DIterator operator++();
        DIterator operator++(int unused);
        DIterator operator--();
        DIterator operator--(int unused);

        DIterator operator+(difference_type offset);
        DIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const DIterator& it) const;

        bool operator==(const DIterator& it) const;
        bool operator!=(const DIterator& it) const;
        bool operator<(const DIterator& it) const;
        bool operator<=(const DIterator& it) const;
        bool operator>(const DIterator& it) const;
        bool operator>=(const DIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;
        size_type getDiagonalNr() const;
        size_type getDiagonalIndex() const;

    private:
        DIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative = false);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_DiagonalIndex;    // relative index within diagonal
        size_type m_DiagonalNumber;   // index of the diagonal within matrix
        size_type m_DiagonalSize;     // number of elements contained within diagonal
    };

    class ConstDIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;

    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = const DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ConstDIterator() = delete;

        ConstDIterator operator++();
        ConstDIterator operator++(int unused);
        ConstDIterator operator--();
        ConstDIterator operator--(int unused);

        ConstDIterator operator+(difference_type offset);
        ConstDIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ConstDIterator& it) const;

        bool operator==(const ConstDIterator& it) const;
        bool operator!=(const ConstDIterator& it) const;
        bool operator<(const ConstDIterator& it) const;
        bool operator<=(const ConstDIterator& it) const;
        bool operator>(const ConstDIterator& it) const;
        bool operator>=(const ConstDIterator& it) const;

        reference operator*() const;
        const value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;
        size_type getDiagonalNr() const;
        size_type getDiagonalIndex() const;

    private:
        ConstDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative = false);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_DiagonalIndex;    // relative index within diagonal
        size_type m_DiagonalNumber;   // index of the diagonal within matrix
        size_type m_DiagonalSize;     // number of elements contained within diagonal
    };

    class ReverseDIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;

    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ReverseDIterator() = delete;

        ReverseDIterator operator++();
        ReverseDIterator operator++(int unused);
        ReverseDIterator operator--();
        ReverseDIterator operator--(int unused);

        ReverseDIterator operator+(difference_type offset);
        ReverseDIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ReverseDIterator& it) const;

        bool operator==(const ReverseDIterator& it) const;
        bool operator!=(const ReverseDIterator& it) const;
        bool operator<(const ReverseDIterator& it) const;
        bool operator<=(const ReverseDIterator& it) const;
        bool operator>(const ReverseDIterator& it) const;
        bool operator>=(const ReverseDIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;
        size_type getDiagonalNr() const;
        size_type getDiagonalIndex() const;

    private:
        ReverseDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative = false);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_DiagonalIndex;    // relative index within diagonal
        size_type m_DiagonalNumber;   // index of the diagonal within matrix
        size_type m_DiagonalSize;     // number of elements contained within diagonal
    };

    class ConstReverseDIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;

    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = const DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ConstReverseDIterator() = delete;

        ConstReverseDIterator operator++();
        ConstReverseDIterator operator++(int unused);
        ConstReverseDIterator operator--();
        ConstReverseDIterator operator--(int unused);

        ConstReverseDIterator operator+(difference_type offset);
        ConstReverseDIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ConstReverseDIterator& it) const;

        bool operator==(const ConstReverseDIterator& it) const;
        bool operator!=(const ConstReverseDIterator& it) const;
        bool operator<(const ConstReverseDIterator& it) const;
        bool operator<=(const ConstReverseDIterator& it) const;
        bool operator>(const ConstReverseDIterator& it) const;
        bool operator>=(const ConstReverseDIterator& it) const;

        reference operator*() const;
        const value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;
        size_type getDiagonalNr() const;
        size_type getDiagonalIndex() const;

    private:
        ConstReverseDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative = false);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_DiagonalIndex;    // relative index within diagonal
        size_type m_DiagonalNumber;   // index of the diagonal within matrix
        size_type m_DiagonalSize;     // number of elements contained within diagonal
    };

    class NIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        NIterator();

        NIterator operator++();
        NIterator operator++(int unused);
        NIterator operator--();
        NIterator operator--(int unused);

        NIterator operator+(difference_type offset);
        NIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const NIterator& it) const;

        bool operator==(const NIterator& it) const;
        bool operator!=(const NIterator& it) const;
        bool operator<(const NIterator& it) const;
        bool operator<=(const NIterator& it) const;
        bool operator>(const NIterator& it) const;
        bool operator>=(const NIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        NIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class ConstNIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = const DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ConstNIterator();

        ConstNIterator operator++();
        ConstNIterator operator++(int unused);
        ConstNIterator operator--();
        ConstNIterator operator--(int unused);

        ConstNIterator operator+(difference_type offset);
        ConstNIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ConstNIterator& it) const;

        bool operator==(const ConstNIterator& it) const;
        bool operator!=(const ConstNIterator& it) const;
        bool operator<(const ConstNIterator& it) const;
        bool operator<=(const ConstNIterator& it) const;
        bool operator>(const ConstNIterator& it) const;
        bool operator>=(const ConstNIterator& it) const;

        reference operator*() const;
        const value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ConstNIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    class ReverseNIterator
    {
        // Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege"
        friend class Matrix;
    public:
        // all these are required for STL compatibility
        using iterator_category = std::random_access_iterator_tag;
        using value_type = DataType;
        using difference_type = diff_type;
        using pointer = DataType**;
        using reference = DataType&;

        // creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix
        ReverseNIterator();

        ReverseNIterator operator++();
        ReverseNIterator operator++(int unused);
        ReverseNIterator operator--();
        ReverseNIterator operator--(int unused);

        ReverseNIterator operator+(difference_type offset);
        ReverseNIterator operator-(difference_type offset);

        void operator+=(difference_type offset);
        void operator-=(difference_type offset);

        difference_type operator-(const ReverseNIterator& it) const;

        bool operator==(const ReverseNIterator& it) const;
        bool operator!=(const ReverseNIterator& it) const;
        bool operator<(const ReverseNIterator& it) const;
        bool operator<=(const ReverseNIterator& it) const;
        bool operator>(const ReverseNIterator& it) const;
        bool operator>=(const ReverseNIterator& it) const;

        reference operator*() const;
        value_type* operator->() const;
        reference operator[](difference_type index) const;

        bool isValidWithMatrix(const Matrix& matrix) const;

        size_type getCurrentRowNr() const;
        size_type getCurrentColumnNr() const;

    private:
        ReverseNIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr);

        void _increment();
        void _decrement();

        pointer m_pMatrixPtr;
        size_type m_CurrentRowNr;
        size_type m_CurrentColumnNr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
    };

    Matrix();
    Matrix(size_type nrOfRows, size_type nrOfColumns, std::initializer_list<DataType> dataTypeInitList);
    Matrix(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType);
    Matrix(size_type nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues);
    Matrix(const Matrix<DataType>& matrix);
    Matrix(Matrix<DataType>&& matrix);
    ~Matrix();

    DataType& at(size_type rowNr, size_type columnNr);
    const DataType& at(size_type rowNr, size_type columnNr) const;

    DataType& operator[] (size_type index);

    Matrix<DataType>& operator= (const Matrix<DataType>& matrix);
    Matrix<DataType>& operator= (Matrix<DataType>&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    DataType* getBaseArray(size_type& nrOfElements);
	
    size_type getNrOfRows() const;
    size_type getNrOfColumns() const;
    size_type getRowCapacity() const;
    size_type getColumnCapacity() const;

    void transpose(Matrix<DataType>& result);

    void clear();

    // resize and don't init new elements (user has the responsibility to init them), existing elements retain their old values
    void resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity=0, size_type columnCapacity=0);
    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType, size_type rowCapacity=0, size_type columnCapacity=0);

    void shrinkToFit();

    void insertRow(size_type rowNr);
    void insertRow(size_type rowNr, const DataType& dataType);
    void insertColumn(size_type columnNr);
    void insertColumn(size_type columnNr, const DataType& dataType);
    void eraseRow (size_type rowNr);
    void eraseColumn(size_type columnNr);

    void catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix);
    void splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitRowNr);
    void splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitColumnNr);

    void swapItems(size_type rowNr, size_type columnNr, Matrix<DataType>& matrix, size_type matrixRowNr, size_type matrixColumnNr);
    void swapRows(size_type rowNr, Matrix<DataType>& matrix, size_type matrixRowNr);
    void swapColumns(size_type columnNr, Matrix<DataType>& matrix, size_type matrixColumnNr);
    void swapRowColumn(size_type rowNr, Matrix<DataType>& matrix, size_type matrixColumnNr);

    void setAllItemsToValue(const DataType& value);
    void copy(const Matrix<DataType>& src, size_type nrOfRows, size_type nrOfColumns, size_type srcMatrixRowNr=0, size_type srcMatrixColumnNr=0, size_type rowNr=0, size_type columnNr=0);

    // logical operators (DataType should have them implemented, otherwise a template specialization is required)
    operator bool() const;
    bool operator== (const Matrix<DataType>& matrix) const;
    bool operator!= (const Matrix<DataType>& matrix) const;

    ZIterator zBegin();
    ZIterator zEnd();
    ZIterator zRowBegin(size_type rowNr);
    ZIterator zRowEnd(size_type rowNr);
    ZIterator getZIterator(size_type rowNr, size_type columnNr);
    ZIterator getZIterator(size_type index);

    ConstZIterator constZBegin() const;
    ConstZIterator constZEnd() const;
    ConstZIterator constZRowBegin(size_type rowNr) const;
    ConstZIterator constZRowEnd(size_type rowNr) const;
    ConstZIterator getConstZIterator(size_type rowNr, size_type columnNr) const;
    ConstZIterator getConstZIterator(size_type index) const;

    ReverseZIterator reverseZBegin();
    ReverseZIterator reverseZEnd();
    ReverseZIterator reverseZRowBegin(size_type rowNr);
    ReverseZIterator reverseZRowEnd(size_type rowNr);
    ReverseZIterator getReverseZIterator(size_type rowNr, size_type columnNr);
    ReverseZIterator getReverseZIterator(size_type index);

    ConstReverseZIterator constReverseZBegin() const;
    ConstReverseZIterator constReverseZEnd() const;
    ConstReverseZIterator constReverseZRowBegin(size_type rowNr) const;
    ConstReverseZIterator constReverseZRowEnd(size_type rowNr) const;
    ConstReverseZIterator getConstReverseZIterator(size_type rowNr, size_type columnNr) const;
    ConstReverseZIterator getConstReverseZIterator(size_type index) const;

    DIterator dBegin(size_type diagNr);
    DIterator dBegin(size_type rowNr, int columnNr);
    DIterator dEnd(size_type diagNr);
    DIterator dEnd(size_type rowNr, int columnNr);
    DIterator getDIterator(size_type first, size_type second, bool isRelative = false);

    ConstDIterator constDBegin(size_type diagNr) const;
    ConstDIterator constDBegin(size_type rowNr, size_type columnNr) const;
    ConstDIterator constDEnd(size_type diagNr) const;
    ConstDIterator constDEnd(size_type rowNr, size_type columnNr) const;
    ConstDIterator getConstDIterator(size_type first, size_type second, bool isRelative = false) const;

    ReverseDIterator reverseDBegin(size_type diagNr);
    ReverseDIterator reverseDBegin(size_type rowNr, size_type columnNr);
    ReverseDIterator reverseDEnd(size_type diagNr);
    ReverseDIterator reverseDEnd(size_type rowNr, size_type columnNr);
    ReverseDIterator getReverseDIterator(size_type first, size_type second, bool isRelative = false);

    ConstReverseDIterator constReverseDBegin(size_type diagNr) const;
    ConstReverseDIterator constReverseDBegin(size_type rowNr, size_type columnNr) const;
    ConstReverseDIterator constReverseDEnd(size_type diagNr) const;
    ConstReverseDIterator constReverseDEnd(size_type rowNr, size_type columnNr) const;
    ConstReverseDIterator getConstReverseDIterator(size_type first, size_type second, bool isRelative = false) const;

    NIterator nBegin();
    NIterator nEnd();
    NIterator nColumnBegin(size_type columnNr);
    NIterator nColumnEnd(size_type columnNr);
    NIterator getNIterator(size_type rowNr, size_type columnNr);
    NIterator getNIterator(size_type index);

    ConstNIterator constNBegin() const;
    ConstNIterator constNEnd() const;
    ConstNIterator constNColumnBegin(size_type columnNr) const;
    ConstNIterator constNColumnEnd(size_type columnNr) const;
    ConstNIterator getConstNIterator(size_type rowNr, size_type columnNr) const;
    ConstNIterator getConstNIterator(size_type index) const;

    ReverseNIterator reverseNBegin();
    ReverseNIterator reverseNEnd();
    ReverseNIterator reverseNColumnBegin(size_type columnNr);
    ReverseNIterator reverseNColumnEnd(size_type columnNr);
    ReverseNIterator getReverseNIterator(size_type rowNr, size_type columnNr);
    ReverseNIterator getReverseNIterator(size_type index);

    // required for being able to use the "auto" keyword for iterating through the matrix elements
    ZIterator begin();
    ZIterator end();
    ConstZIterator cbegin() const;
    ConstZIterator cend() const;

private:
    // ensure the currently allocated memory is first released (_deallocMemory()) prior to using this function
    void _allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0, size_type columnCapacity = 0);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    bool _isEqualTo(const Matrix<DataType>& matrix) const;
    void _adjustSizeAndCapacity(size_type nrOfRows, size_type nrOfColumns);

    DataType* m_pAllocPtr; // use only this pointer in _allocMemory()/_deallocMemory() to allocate/de-allocate matrix elements
    DataType** m_pBaseArrayPtr; // this pointer manages the row pointers array
    size_type m_NrOfRows;
    size_type m_NrOfColumns;
    size_type m_RowCapacity;
    size_type m_ColumnCapacity;
};

// 1) ZIterator - iterates within matrix from [0][0] to the end row by row
template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++(int unused)
{
    (void) unused;
    ZIterator zIterator{*this};

    _increment();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--(int unused)
{
    (void) unused;
    ZIterator zIterator{*this};

    _decrement();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator+(ZIterator::difference_type offset)
{
    ZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator-(ZIterator::difference_type offset)
{
    ZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
void Matrix<DataType>::ZIterator::operator+=(ZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ZIterator::operator-=(ZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::difference_type Matrix<DataType>::ZIterator::operator-(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator==(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator!=(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr < it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<=(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr <= it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr > it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>=(const ZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr >= it.m_CurrentColumnNr));
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::reference Matrix<DataType>::ZIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::value_type* Matrix<DataType>::ZIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::reference Matrix<DataType>::ZIterator::operator[](ZIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_ResultingIndex{c_CurrentIndex + index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void) c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex / m_NrOfMatrixColumns][c_ResultingIndex % m_NrOfMatrixColumns];
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < 0 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr > m_NrOfMatrixColumns ||
        (currentRowNr < m_NrOfMatrixRows-1 && currentColumnNr == m_NrOfMatrixColumns))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_increment()
{
    if (m_CurrentColumnNr != m_NrOfMatrixColumns || m_CurrentRowNr != (m_NrOfMatrixRows-1))
    {
        ++m_CurrentColumnNr;
        if (m_CurrentColumnNr == m_NrOfMatrixColumns && (m_CurrentRowNr != (m_NrOfMatrixRows-1)))
        {
            m_CurrentColumnNr = m_CurrentColumnNr - m_NrOfMatrixColumns;
            ++m_CurrentRowNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_decrement()
{
    if (m_CurrentRowNr > 0 || m_CurrentColumnNr > 0)
    {
        if(m_CurrentColumnNr == 0)
        {
            --m_CurrentRowNr;
            m_CurrentColumnNr = m_NrOfMatrixColumns - 1;
        }
        else
        {
            --m_CurrentColumnNr;
        }
    }
}

// 2) Const ZIterator

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator++(int unused)
{
    (void) unused;
    ConstZIterator zIterator{*this};

    _increment();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator--(int unused)
{
    (void) unused;
    ConstZIterator zIterator{*this};

    _decrement();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator+(ConstZIterator::difference_type offset)
{
    ConstZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator-(ConstZIterator::difference_type offset)
{
    ConstZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::operator+=(ConstZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::operator-=(ConstZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator::difference_type Matrix<DataType>::ConstZIterator::operator-(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator==(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator!=(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator<(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr < it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator<=(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr < it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr <= it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator>(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr > it.m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator>=(const ConstZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr > it.m_CurrentRowNr || (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr >= it.m_CurrentColumnNr));
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator::reference Matrix<DataType>::ConstZIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType> const
typename Matrix<DataType>::ConstZIterator::value_type* Matrix<DataType>::ConstZIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == m_NrOfMatrixColumns || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    const value_type* result{m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr};

    return result;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator::reference Matrix<DataType>::ConstZIterator::operator[](ConstZIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_ResultingIndex{c_CurrentIndex + index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void) c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex / m_NrOfMatrixColumns][c_ResultingIndex % m_NrOfMatrixColumns];
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstZIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstZIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < 0 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr > m_NrOfMatrixColumns ||
        (currentRowNr < m_NrOfMatrixRows-1 && currentColumnNr == m_NrOfMatrixColumns))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::_increment()
{
    if (m_CurrentColumnNr != m_NrOfMatrixColumns || m_CurrentRowNr != (m_NrOfMatrixRows-1))
    {
        ++m_CurrentColumnNr;
        if (m_CurrentColumnNr == m_NrOfMatrixColumns && (m_CurrentRowNr != (m_NrOfMatrixRows-1)))
        {
            m_CurrentColumnNr = m_CurrentColumnNr - m_NrOfMatrixColumns;
            ++m_CurrentRowNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::_decrement()
{
    if (m_CurrentRowNr > 0 || m_CurrentColumnNr > 0)
    {
        if(m_CurrentColumnNr == 0)
        {
            --m_CurrentRowNr;
            m_CurrentColumnNr = m_NrOfMatrixColumns - 1;
        }
        else
        {
            --m_CurrentColumnNr;
        }
    }
}

// 3) Reverse ZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to ZIterator)

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator++(int unused)
{
    (void) unused;
    ReverseZIterator zIterator{*this};

    _increment();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator--(int unused)
{
    (void) unused;
    ReverseZIterator zIterator{*this};

    _decrement();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator+(ReverseZIterator::difference_type offset)
{
    ReverseZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns-1 : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator-(ReverseZIterator::difference_type offset)
{
    ReverseZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns-1 : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::operator+=(ReverseZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::operator-=(ReverseZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::difference_type Matrix<DataType>::ReverseZIterator::operator-(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (c_SecondItCurrentIndex - c_FirstItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator==(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator!=(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator<(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr < m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr < m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator<=(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr < m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr <= m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator>(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr > m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr > m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator>=(const ReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr > m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr >= m_CurrentColumnNr));
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::reference Matrix<DataType>::ReverseZIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == -1 || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::value_type* Matrix<DataType>::ReverseZIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == -1 || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::reference Matrix<DataType>::ReverseZIterator::operator[](ReverseZIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_ResultingIndex{c_CurrentIndex - index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void)c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex / m_NrOfMatrixColumns][c_ResultingIndex % m_NrOfMatrixColumns];
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseZIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseZIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < -1 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr >= m_NrOfMatrixColumns ||
        (currentRowNr < m_NrOfMatrixRows-1 && currentColumnNr == m_NrOfMatrixColumns))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::_increment()
{
    if (m_CurrentColumnNr != -1 || m_CurrentRowNr != 0)
    {
        --m_CurrentColumnNr;
        if (m_CurrentColumnNr < 0 && (m_CurrentRowNr != 0))
        {
            m_CurrentColumnNr = m_NrOfMatrixColumns - 1;
            --m_CurrentRowNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::_decrement()
{
    if (m_CurrentRowNr < m_NrOfMatrixRows-1 || m_CurrentColumnNr < m_NrOfMatrixColumns-1)
    {
        if(m_CurrentColumnNr == m_NrOfMatrixColumns-1)
        {
            ++m_CurrentRowNr;
            m_CurrentColumnNr = 0;
        }
        else
        {
            ++m_CurrentColumnNr;
        }
    }
}

// 4) Const Reverse ZIterator

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator++(int unused)
{
    (void) unused;
    ConstReverseZIterator zIterator{*this};

    _increment();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator--(int unused)
{
    (void) unused;
    ConstReverseZIterator zIterator{*this};

    _decrement();

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator+(ConstReverseZIterator::difference_type offset)
{
    ConstReverseZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns-1 : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator-(ConstReverseZIterator::difference_type offset)
{
    ConstReverseZIterator zIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        zIterator.m_pMatrixPtr = m_pMatrixPtr;
        zIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        zIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        zIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows - 1 : c_ResultingIndex / m_NrOfMatrixColumns;
        zIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns-1 : c_ResultingIndex % m_NrOfMatrixColumns;
    }

    return zIterator;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::operator+=(ConstReverseZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::operator-=(ConstReverseZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator::difference_type Matrix<DataType>::ConstReverseZIterator::operator-(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentRowNr * it.m_NrOfMatrixColumns + it.m_CurrentColumnNr};

    return (c_SecondItCurrentIndex - c_FirstItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator==(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator!=(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator<(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr < m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr < m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator<=(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr < m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr <= m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator>(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr > m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr > m_CurrentColumnNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator>=(const ConstReverseZIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentRowNr > m_CurrentRowNr || (it.m_CurrentRowNr == m_CurrentRowNr && it.m_CurrentColumnNr >= m_CurrentColumnNr));
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator::reference Matrix<DataType>::ConstReverseZIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == -1 || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType> const
typename Matrix<DataType>::ConstReverseZIterator::value_type* Matrix<DataType>::ConstReverseZIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentColumnNr == -1 || m_NrOfMatrixColumns == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    const value_type* result{m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr};

    return result;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator::reference Matrix<DataType>::ConstReverseZIterator::operator[](ConstReverseZIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentRowNr * m_NrOfMatrixColumns + m_CurrentColumnNr};
    const size_type c_ResultingIndex{c_CurrentIndex - index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void)c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex / m_NrOfMatrixColumns][c_ResultingIndex % m_NrOfMatrixColumns];
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseZIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseZIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < -1 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr >= m_NrOfMatrixColumns ||
        (currentRowNr < m_NrOfMatrixRows-1 && currentColumnNr == m_NrOfMatrixColumns))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::_increment()
{
    if (m_CurrentColumnNr != -1 || m_CurrentRowNr != 0)
    {
        --m_CurrentColumnNr;
        if (m_CurrentColumnNr < 0 && (m_CurrentRowNr != 0))
        {
            m_CurrentColumnNr = m_NrOfMatrixColumns - 1;
            --m_CurrentRowNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::_decrement()
{
    if (m_CurrentRowNr < m_NrOfMatrixRows-1 || m_CurrentColumnNr < m_NrOfMatrixColumns-1)
    {
        if(m_CurrentColumnNr == m_NrOfMatrixColumns-1)
        {
            ++m_CurrentRowNr;
            m_CurrentColumnNr = 0;
        }
        else
        {
            ++m_CurrentColumnNr;
        }
    }
}

// 5) DIterator (diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator++(int unused)
{
    (void)unused;
    DIterator dIterator{*this};

    _increment();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator--(int unused)
{
    (void)unused;
    DIterator dIterator{*this};

    _decrement();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator+(DIterator::difference_type offset)
{
    DIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex + offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator-(DIterator::difference_type offset)
{
    DIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex - offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
void Matrix<DataType>::DIterator::operator+=(DIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::DIterator::operator-=(DIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::DIterator::difference_type Matrix<DataType>::DIterator::operator-(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_DiagonalIndex - it.m_DiagonalIndex);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator==(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex == it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator!=(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex != it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator<(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex < it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator<=(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex <= it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator>(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex > it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator>=(const DIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex >= it.m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::DIterator::reference Matrix<DataType>::DIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_CurrentRowNr][c_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::DIterator::value_type* Matrix<DataType>::DIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};

    return (m_pMatrixPtr[c_CurrentRowNr] + c_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator::reference Matrix<DataType>::DIterator::operator[](DIterator::difference_type index) const
{
    const size_type c_ResultingIndex{m_DiagonalIndex + index};

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= m_DiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingRowNr{m_DiagonalNumber < 0 ? c_ResultingIndex - m_DiagonalNumber : c_ResultingIndex};
    const size_type c_ResultingColumnNr{m_DiagonalNumber < 0 ? c_ResultingIndex : c_ResultingIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_ResultingRowNr][c_ResultingColumnNr];
}

template<typename DataType>
bool Matrix<DataType>::DIterator::isValidWithMatrix(const Matrix &matrix) const
{
    bool isValid{true};

    if (m_pMatrixPtr != matrix.m_pBaseArrayPtr)
    {
        isValid = false;
    }
    else if ((m_DiagonalNumber < 0 && std::abs(m_DiagonalNumber) >= matrix.getNrOfRows()) || (m_DiagonalNumber >= 0 && m_DiagonalNumber >= matrix.getNrOfColumns()))
    {
        isValid = false;
    }
    else
    {
        const size_type c_DiagonalSize{m_DiagonalNumber < 0 ? std::min(matrix.getNrOfRows() - std::abs(m_DiagonalNumber), matrix.getNrOfColumns())
                                              : std::min(matrix.getNrOfRows(), matrix.getNrOfColumns() - m_DiagonalNumber)};
        if (m_DiagonalSize != c_DiagonalSize)
        {
            isValid = false;
        }
    }

    return isValid;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getCurrentRowNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getCurrentColumnNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalNumber + m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getDiagonalNr() const
{
    return m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
Matrix<DataType>::DIterator::DIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    if (isRelative)
    {
        // first and second are interpreted as diagonal number and relative index within diagonal
        m_DiagonalNumber = first;
        m_DiagonalIndex = second;
        const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
        const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};
        m_DiagonalSize = m_DiagonalIndex + std::min(matrix.getNrOfRows() - c_CurrentRowNr, matrix.getNrOfColumns() - c_CurrentColumnNr);
    }
    else
    {
        // first and second are interpreted as (x, y) coordinates
        m_DiagonalNumber = second - first;
        m_DiagonalIndex = std::min(first, second);
        m_DiagonalSize = m_DiagonalIndex + std::min(matrix.getNrOfRows() - first, matrix.getNrOfColumns() - second);
    }
}

template<typename DataType>
void Matrix<DataType>::DIterator::_increment()
{
    if (m_DiagonalIndex < m_DiagonalSize)
    {
        ++m_DiagonalIndex;
    }
}

template<typename DataType>
void Matrix<DataType>::DIterator::_decrement()
{
    if (m_DiagonalIndex > 0)
    {
        --m_DiagonalIndex;
    }
}

// 6) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator++(int unused)
{
    (void)unused;
    ConstDIterator dIterator{*this};

    _increment();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator--(int unused)
{
    (void)unused;
    ConstDIterator dIterator{*this};

    _decrement();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator+(ConstDIterator::difference_type offset)
{
    ConstDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex + offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator-(ConstDIterator::difference_type offset)
{
    ConstDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex - offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::operator+=(ConstDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::operator-=(ConstDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator::difference_type Matrix<DataType>::ConstDIterator::operator-(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_DiagonalIndex - it.m_DiagonalIndex);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator==(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex == it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator!=(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex != it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator<(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex < it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator<=(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex <= it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator>(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex > it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator>=(const ConstDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex >= it.m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator::reference Matrix<DataType>::ConstDIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_CurrentRowNr][c_CurrentColumnNr];
}

template<typename DataType> const
typename Matrix<DataType>::ConstDIterator::value_type* Matrix<DataType>::ConstDIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};

    return (m_pMatrixPtr[c_CurrentRowNr] + c_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator::reference Matrix<DataType>::ConstDIterator::operator[](ConstDIterator::difference_type index) const
{
    const size_type c_ResultingIndex{m_DiagonalIndex + index};

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= m_DiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingRowNr{m_DiagonalNumber < 0 ? c_ResultingIndex - m_DiagonalNumber : c_ResultingIndex};
    const size_type c_ResultingColumnNr{m_DiagonalNumber < 0 ? c_ResultingIndex : c_ResultingIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_ResultingRowNr][c_ResultingColumnNr];
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::isValidWithMatrix(const Matrix &matrix) const
{
    bool isValid{true};

    if (m_pMatrixPtr != matrix.m_pBaseArrayPtr)
    {
        isValid = false;
    }
    else if ((m_DiagonalNumber < 0 && std::abs(m_DiagonalNumber) >= matrix.getNrOfRows()) || (m_DiagonalNumber >= 0 && m_DiagonalNumber >= matrix.getNrOfColumns()))
    {
        isValid = false;
    }
    else
    {
        const size_type c_DiagonalSize{m_DiagonalNumber < 0 ? std::min(matrix.getNrOfRows() - std::abs(m_DiagonalNumber), matrix.getNrOfColumns())
                                              : std::min(matrix.getNrOfRows(), matrix.getNrOfColumns() - m_DiagonalNumber)};
        if (m_DiagonalSize != c_DiagonalSize)
        {
            isValid = false;
        }
    }

    return isValid;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getCurrentRowNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getCurrentColumnNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalNumber + m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getDiagonalNr() const
{
    return m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
Matrix<DataType>::ConstDIterator::ConstDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    if (isRelative)
    {
        // first and second are interpreted as diagonal number and relative index within diagonal
        m_DiagonalNumber = first;
        m_DiagonalIndex = second;
        const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalIndex - m_DiagonalNumber : m_DiagonalIndex};
        const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalIndex : m_DiagonalIndex + m_DiagonalNumber};
        m_DiagonalSize = m_DiagonalIndex + std::min(matrix.getNrOfRows() - c_CurrentRowNr, matrix.getNrOfColumns() - c_CurrentColumnNr);
    }
    else
    {
        // first and second are interpreted as (x, y) coordinates
        m_DiagonalNumber = second - first;
        m_DiagonalIndex = std::min(first, second);
        m_DiagonalSize = m_DiagonalIndex + std::min(matrix.getNrOfRows() - first, matrix.getNrOfColumns() - second);
    }
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::_increment()
{
    if (m_DiagonalIndex < m_DiagonalSize)
    {
        ++m_DiagonalIndex;
    }
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::_decrement()
{
    if (m_DiagonalIndex > 0)
    {
        --m_DiagonalIndex;
    }
}

// 7) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator++(int unused)
{
    (void)unused;
    ReverseDIterator dIterator{*this};

    _increment();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator--(int unused)
{
    (void)unused;
    ReverseDIterator dIterator{*this};

    _decrement();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator+(ReverseDIterator::difference_type offset)
{
    ReverseDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex + offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator-(ReverseDIterator::difference_type offset)
{
    ReverseDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex - offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::operator+=(ReverseDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::operator-=(ReverseDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::difference_type Matrix<DataType>::ReverseDIterator::operator-(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_DiagonalIndex - it.m_DiagonalIndex);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator==(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex == it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator!=(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex != it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator<(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex < it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator<=(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex <= it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator>(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex > it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator>=(const ReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex >= it.m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::reference Matrix<DataType>::ReverseDIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_CurrentRowNr][c_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::value_type* Matrix<DataType>::ReverseDIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber};

    return (m_pMatrixPtr[c_CurrentRowNr] + c_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::reference Matrix<DataType>::ReverseDIterator::operator[](ReverseDIterator::difference_type index) const
{
    const size_type c_ResultingIndex{m_DiagonalIndex + index};

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= m_DiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - c_ResultingIndex - m_DiagonalNumber : m_DiagonalSize - c_ResultingIndex - 1};
    const size_type c_ResultingColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - c_ResultingIndex - 1 : m_DiagonalSize - 1 - c_ResultingIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_ResultingRowNr][c_ResultingColumnNr];
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::isValidWithMatrix(const Matrix &matrix) const
{
    bool isValid{true};

    if (m_pMatrixPtr != matrix.m_pBaseArrayPtr)
    {
        isValid = false;
    }
    else if ((m_DiagonalNumber < 0 && std::abs(m_DiagonalNumber) >= matrix.getNrOfRows()) || (m_DiagonalNumber >= 0 && m_DiagonalNumber >= matrix.getNrOfColumns()))
    {
        isValid = false;
    }
    else
    {
        const size_type c_DiagonalSize{m_DiagonalNumber < 0 ? std::min(matrix.getNrOfRows() - std::abs(m_DiagonalNumber), matrix.getNrOfColumns())
                                              : std::min(matrix.getNrOfRows(), matrix.getNrOfColumns() - m_DiagonalNumber)};
        if (m_DiagonalSize != c_DiagonalSize)
        {
            isValid = false;
        }
    }

    return isValid;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getCurrentRowNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getCurrentColumnNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ReverseDIterator::ReverseDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    const size_type c_NrOfRows{matrix.getNrOfRows()};
    const size_type c_NrOfColumns{matrix.getNrOfColumns()};
    const size_type c_MaxSize{std::max(c_NrOfRows, c_NrOfColumns)};
    const difference_type c_Delta{c_NrOfRows - c_NrOfColumns};

    m_DiagonalNumber = isRelative ? first : second - first;
    m_DiagonalSize = (c_Delta >= 0) ? (m_DiagonalNumber < 0 ? c_MaxSize + m_DiagonalNumber : c_MaxSize - m_DiagonalNumber - c_Delta)
                                    : (m_DiagonalNumber <= 0 ? c_MaxSize + m_DiagonalNumber + c_Delta : c_MaxSize - m_DiagonalNumber);
    m_DiagonalIndex = isRelative ? second : (m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - second : m_DiagonalSize - 1 - first);
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::_increment()
{
    if (m_DiagonalIndex < m_DiagonalSize)
    {
        ++m_DiagonalIndex;
    }
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::_decrement()
{
    if (m_DiagonalIndex > 0)
    {
        --m_DiagonalIndex;
    }
}

// 8) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator++(int unused)
{
    (void)unused;
    ConstReverseDIterator dIterator{*this};

    _increment();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator--(int unused)
{
    (void)unused;
    ConstReverseDIterator dIterator{*this};

    _decrement();

    return dIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator+(ConstReverseDIterator::difference_type offset)
{
    ConstReverseDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex + offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator-(ConstReverseDIterator::difference_type offset)
{
    ConstReverseDIterator it{*this};
    const size_type c_ResultingIndex = it.m_DiagonalIndex - offset;
    it.m_DiagonalIndex = c_ResultingIndex < 0 ? 0 : c_ResultingIndex > it.m_DiagonalSize ? it.m_DiagonalSize : c_ResultingIndex;

    return it;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::operator+=(ConstReverseDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::operator-=(ConstReverseDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator::difference_type Matrix<DataType>::ConstReverseDIterator::operator-(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_DiagonalIndex - it.m_DiagonalIndex);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator==(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex == it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator!=(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex != it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator<(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex < it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator<=(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex <= it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator>(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex > it.m_DiagonalIndex;
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator>=(const ConstReverseDIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize || m_DiagonalNumber != it.m_DiagonalNumber,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_DiagonalIndex >= it.m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator::reference Matrix<DataType>::ConstReverseDIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_CurrentRowNr][c_CurrentColumnNr];
}

template<typename DataType> const
typename Matrix<DataType>::ConstReverseDIterator::value_type* Matrix<DataType>::ConstReverseDIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_DiagonalIndex == m_DiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    const size_type c_CurrentRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1};
    const size_type c_CurrentColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber};

    return (m_pMatrixPtr[c_CurrentRowNr] + c_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator::reference Matrix<DataType>::ConstReverseDIterator::operator[](ConstReverseDIterator::difference_type index) const
{
    const size_type c_ResultingIndex{m_DiagonalIndex + index};

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= m_DiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingRowNr{m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - c_ResultingIndex - m_DiagonalNumber : m_DiagonalSize - c_ResultingIndex - 1};
    const size_type c_ResultingColumnNr{m_DiagonalNumber < 0 ? m_DiagonalSize - c_ResultingIndex - 1 : m_DiagonalSize - 1 - c_ResultingIndex + m_DiagonalNumber};

    return m_pMatrixPtr[c_ResultingRowNr][c_ResultingColumnNr];
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::isValidWithMatrix(const Matrix &matrix) const
{
    bool isValid{true};

    if (m_pMatrixPtr != matrix.m_pBaseArrayPtr)
    {
        isValid = false;
    }
    else if ((m_DiagonalNumber < 0 && std::abs(m_DiagonalNumber) >= matrix.getNrOfRows()) || (m_DiagonalNumber >= 0 && m_DiagonalNumber >= matrix.getNrOfColumns()))
    {
        isValid = false;
    }
    else
    {
        const size_type c_DiagonalSize{m_DiagonalNumber < 0 ? std::min(matrix.getNrOfRows() - std::abs(m_DiagonalNumber), matrix.getNrOfColumns())
                                              : std::min(matrix.getNrOfRows(), matrix.getNrOfColumns() - m_DiagonalNumber)};
        if (m_DiagonalSize != c_DiagonalSize)
        {
            isValid = false;
        }
    }

    return isValid;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getCurrentRowNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNumber : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getCurrentColumnNr() const
{
    return m_DiagonalNumber < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNumber;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator(const Matrix& matrix, size_type first, size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    const size_type c_NrOfRows{matrix.getNrOfRows()};
    const size_type c_NrOfColumns{matrix.getNrOfColumns()};
    const size_type c_MaxSize{std::max(c_NrOfRows, c_NrOfColumns)};
    const difference_type c_Delta{c_NrOfRows - c_NrOfColumns};

    m_DiagonalNumber = isRelative ? first : second - first;
    m_DiagonalSize = (c_Delta >= 0) ? (m_DiagonalNumber < 0 ? c_MaxSize + m_DiagonalNumber : c_MaxSize - m_DiagonalNumber - c_Delta)
                                    : (m_DiagonalNumber <= 0 ? c_MaxSize + m_DiagonalNumber + c_Delta : c_MaxSize - m_DiagonalNumber);
    m_DiagonalIndex = isRelative ? second : (m_DiagonalNumber < 0 ? m_DiagonalSize - 1 - second : m_DiagonalSize - 1 - first);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::_increment()
{
    if (m_DiagonalIndex < m_DiagonalSize)
    {
        ++m_DiagonalIndex;
    }
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::_decrement()
{
    if (m_DiagonalIndex > 0)
    {
        --m_DiagonalIndex;
    }
}

// 9) NIterator - iterates within matrix from [0][0] to the end column by column
template<typename DataType>
Matrix<DataType>::NIterator::NIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator++(int unused)
{
    (void) unused;
    NIterator nIterator{*this};

    _increment();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator--(int unused)
{
    (void) unused;
    NIterator nIterator{*this};

    _decrement();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator+(NIterator::difference_type offset)
{
    NIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator-(NIterator::difference_type offset)
{
    NIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
void Matrix<DataType>::NIterator::operator+=(NIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::NIterator::operator-=(NIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::NIterator::difference_type Matrix<DataType>::NIterator::operator-(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentColumnNr * it.m_NrOfMatrixRows + it.m_CurrentRowNr};

    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator==(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator!=(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator<(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr < it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr < it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator<=(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr < it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr <= it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator>(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr > it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr > it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator>=(const NIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr > it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr >= it.m_CurrentRowNr));
}

template<typename DataType>
typename Matrix<DataType>::NIterator::reference Matrix<DataType>::NIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == m_NrOfMatrixRows || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::NIterator::value_type* Matrix<DataType>::NIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == m_NrOfMatrixRows || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator::reference Matrix<DataType>::NIterator::operator[](NIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_ResultingIndex{c_CurrentIndex + index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void) c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex % m_NrOfMatrixRows][c_ResultingIndex / m_NrOfMatrixRows];
}

template<typename DataType>
bool Matrix<DataType>::NIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::NIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::NIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::NIterator::NIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < 0 || currentColumnNr >= m_NrOfMatrixColumns || currentRowNr > m_NrOfMatrixRows ||
        (currentColumnNr < m_NrOfMatrixColumns-1 && currentRowNr == m_NrOfMatrixRows))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::NIterator::_increment()
{
    if (m_CurrentRowNr != m_NrOfMatrixRows || m_CurrentColumnNr != (m_NrOfMatrixColumns-1))
    {
        ++m_CurrentRowNr;
        if (m_CurrentRowNr == m_NrOfMatrixRows && (m_CurrentColumnNr != (m_NrOfMatrixColumns-1)))
        {
            m_CurrentRowNr = m_CurrentRowNr - m_NrOfMatrixRows;
            ++m_CurrentColumnNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::NIterator::_decrement()
{
    if (m_CurrentRowNr > 0 || m_CurrentColumnNr > 0)
    {
        if(m_CurrentRowNr == 0)
        {
            --m_CurrentColumnNr;
            m_CurrentRowNr = m_NrOfMatrixRows - 1;
        }
        else
        {
            --m_CurrentRowNr;
        }
    }
}

// 10) Const NIterator
template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator++(int unused)
{
    (void) unused;
    ConstNIterator nIterator{*this};

    _increment();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator--(int unused)
{
    (void) unused;
    ConstNIterator nIterator{*this};

    _decrement();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator+(ConstNIterator::difference_type offset)
{
    ConstNIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator-(ConstNIterator::difference_type offset)
{
    ConstNIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= 0 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::operator+=(ConstNIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::operator-=(ConstNIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator::difference_type Matrix<DataType>::ConstNIterator::operator-(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentColumnNr * it.m_NrOfMatrixRows + it.m_CurrentRowNr};

    return (c_FirstItCurrentIndex - c_SecondItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator==(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator!=(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator<(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr < it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr < it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator<=(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr < it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr <= it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator>(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr > it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr > it.m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator>=(const ConstNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentColumnNr > it.m_CurrentColumnNr || (m_CurrentColumnNr == it.m_CurrentColumnNr && m_CurrentRowNr >= it.m_CurrentRowNr));
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator::reference Matrix<DataType>::ConstNIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == m_NrOfMatrixRows || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType> const
typename Matrix<DataType>::ConstNIterator::value_type* Matrix<DataType>::ConstNIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == m_NrOfMatrixRows || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator::reference Matrix<DataType>::ConstNIterator::operator[](ConstNIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_ResultingIndex{c_CurrentIndex + index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void) c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex % m_NrOfMatrixRows][c_ResultingIndex / m_NrOfMatrixRows];
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstNIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstNIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentRowNr < 0 || currentColumnNr < 0 || currentColumnNr >= m_NrOfMatrixColumns || currentRowNr > m_NrOfMatrixRows ||
        (currentColumnNr < m_NrOfMatrixColumns-1 && currentRowNr == m_NrOfMatrixRows))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::_increment()
{
    if (m_CurrentRowNr != m_NrOfMatrixRows || m_CurrentColumnNr != (m_NrOfMatrixColumns-1))
    {
        ++m_CurrentRowNr;
        if (m_CurrentRowNr == m_NrOfMatrixRows && (m_CurrentColumnNr != (m_NrOfMatrixColumns-1)))
        {
            m_CurrentRowNr = m_CurrentRowNr - m_NrOfMatrixRows;
            ++m_CurrentColumnNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::_decrement()
{
    if (m_CurrentRowNr > 0 || m_CurrentColumnNr > 0)
    {
        if(m_CurrentRowNr == 0)
        {
            --m_CurrentColumnNr;
            m_CurrentRowNr = m_NrOfMatrixRows - 1;
        }
        else
        {
            --m_CurrentRowNr;
        }
    }
}

// 11) Reverse NIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to NIterator)

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_CurrentRowNr{-1}
    , m_CurrentColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator++()
{
    _increment();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator++(int unused)
{
    (void) unused;
    ReverseNIterator nIterator{*this};

    _increment();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator--()
{
    _decrement();
    return *this;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator--(int unused)
{
    (void) unused;
    ReverseNIterator nIterator{*this};

    _decrement();

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator+(ReverseNIterator::difference_type offset)
{
    ReverseNIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex - offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows-1 : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator-(ReverseNIterator::difference_type offset)
{
    ReverseNIterator nIterator{};

    if (m_pMatrixPtr)
    {
        const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
        const size_type c_ResultingIndex{c_CurrentIndex + offset};
        const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};

        nIterator.m_pMatrixPtr = m_pMatrixPtr;
        nIterator.m_NrOfMatrixRows = m_NrOfMatrixRows;
        nIterator.m_NrOfMatrixColumns = m_NrOfMatrixColumns;
        nIterator.m_CurrentRowNr = c_ResultingIndex <= -1 ? -1 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixRows-1 : c_ResultingIndex % m_NrOfMatrixRows;
        nIterator.m_CurrentColumnNr = c_ResultingIndex <= -1 ? 0 : c_ResultingIndex >= c_UpperBound ? m_NrOfMatrixColumns - 1 : c_ResultingIndex / m_NrOfMatrixRows;
    }

    return nIterator;
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::operator+=(ReverseNIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::operator-=(ReverseNIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::difference_type Matrix<DataType>::ReverseNIterator::operator-(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    const size_type c_FirstItCurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_SecondItCurrentIndex{it.m_CurrentColumnNr * it.m_NrOfMatrixRows + it.m_CurrentRowNr};

    return (c_SecondItCurrentIndex - c_FirstItCurrentIndex);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator==(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr == it.m_CurrentRowNr && m_CurrentColumnNr == it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator!=(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (m_CurrentRowNr != it.m_CurrentRowNr || m_CurrentColumnNr != it.m_CurrentColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator<(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentColumnNr < m_CurrentColumnNr || (it.m_CurrentColumnNr == m_CurrentColumnNr && it.m_CurrentRowNr < m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator<=(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentColumnNr < m_CurrentColumnNr || (it.m_CurrentColumnNr == m_CurrentColumnNr && it.m_CurrentRowNr <= m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator>(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentColumnNr > m_CurrentColumnNr || (it.m_CurrentColumnNr == m_CurrentColumnNr && it.m_CurrentRowNr > m_CurrentRowNr));
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator>=(const ReverseNIterator& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows || m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return (it.m_CurrentColumnNr > m_CurrentColumnNr || (it.m_CurrentColumnNr == m_CurrentColumnNr && it.m_CurrentRowNr >= m_CurrentRowNr));
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::reference Matrix<DataType>::ReverseNIterator::operator*() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == -1 || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[m_CurrentRowNr][m_CurrentColumnNr];
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::value_type* Matrix<DataType>::ReverseNIterator::operator->() const
{
    CHECK_ERROR_CONDITION(m_CurrentRowNr == -1 || m_NrOfMatrixRows == 0, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[m_CurrentRowNr] + m_CurrentColumnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::reference Matrix<DataType>::ReverseNIterator::operator[](ReverseNIterator::difference_type index) const
{
    const size_type c_CurrentIndex{m_CurrentColumnNr * m_NrOfMatrixRows + m_CurrentRowNr};
    const size_type c_ResultingIndex{c_CurrentIndex - index};
    const size_type c_UpperBound{m_NrOfMatrixRows * m_NrOfMatrixColumns};
    (void)c_UpperBound;

    CHECK_ERROR_CONDITION(c_ResultingIndex < 0 || c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    return m_pMatrixPtr[c_ResultingIndex % m_NrOfMatrixRows][c_ResultingIndex / m_NrOfMatrixRows];
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::isValidWithMatrix(const Matrix &matrix) const
{
    return (m_pMatrixPtr == matrix.m_pBaseArrayPtr && m_NrOfMatrixRows == matrix.m_NrOfRows && m_NrOfMatrixColumns == matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseNIterator::getCurrentRowNr() const
{
    return m_CurrentRowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseNIterator::getCurrentColumnNr() const
{
    return m_CurrentColumnNr;
}

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator(const Matrix& matrix, size_type currentRowNr, size_type currentColumnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    if (currentColumnNr < 0 || currentRowNr < -1 || currentRowNr >= m_NrOfMatrixRows || currentColumnNr >= m_NrOfMatrixColumns ||
        (currentColumnNr < m_NrOfMatrixColumns-1 && currentRowNr == m_NrOfMatrixRows))
    {
        m_CurrentRowNr = -1;
        m_CurrentColumnNr = -1;
    }
    else
    {
        m_CurrentRowNr = currentRowNr;
        m_CurrentColumnNr = currentColumnNr;
    }
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::_increment()
{
    if (m_CurrentRowNr != -1 || m_CurrentColumnNr != 0)
    {
        --m_CurrentRowNr;
        if (m_CurrentRowNr < 0 && (m_CurrentColumnNr != 0))
        {
            m_CurrentRowNr = m_NrOfMatrixRows - 1;
            --m_CurrentColumnNr;
        }
    }
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::_decrement()
{
    if (m_CurrentColumnNr < m_NrOfMatrixColumns-1 || m_CurrentRowNr < m_NrOfMatrixRows-1)
    {
        if(m_CurrentRowNr == m_NrOfMatrixRows-1)
        {
            ++m_CurrentColumnNr;
            m_CurrentRowNr = 0;
        }
        else
        {
            ++m_CurrentRowNr;
        }
    }
}

// matrix methods

template <typename DataType>
Matrix<DataType>::Matrix()
    : m_pAllocPtr{nullptr}
    , m_pBaseArrayPtr{nullptr}
    , m_NrOfRows{0}
    , m_NrOfColumns{0}
    , m_RowCapacity{0}
    , m_ColumnCapacity{0}
{
}

template<typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRows, size_type nrOfColumns, std::initializer_list<DataType> dataTypeInitList)
{
    CHECK_ERROR_CONDITION(nrOfRows <= 0 || nrOfColumns <= 0, Matr::errorMessages[Matr::Errors::NULL_OR_NEG_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows * nrOfColumns > static_cast<size_type>(dataTypeInitList.size()), Matr::errorMessages[Matr::Errors::INSUFFICIENT_ELEMENTS_FOR_INIT]);

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::initializer_list<DataType>::iterator initListIterator{dataTypeInitList.begin()};
    for (size_type row{0}; row < nrOfRows; ++row)
    {
        for (size_type col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = *(initListIterator++);
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType)
{
    CHECK_ERROR_CONDITION(nrOfRows <= 0 || nrOfColumns <= 0, Matr::errorMessages[Matr::Errors::NULL_OR_NEG_DIMENSION]);

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (size_type row{0}; row < nrOfRows; ++row)
    {
        for (size_type col{0}; col < nrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = dataType;
        }
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(size_type nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues)
    : Matrix<DataType>{nrOfRowsColumns, nrOfRowsColumns, diagMatrixValues.first}
{
    for (size_type diag{0}; diag<m_NrOfRows; ++diag)
    {
        m_pBaseArrayPtr[diag][diag] = diagMatrixValues.second;
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& matrix)
{
    const size_type c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

    _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        for (size_type col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
        }
    }
}

template<typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>&& matrix)
    : m_pAllocPtr{matrix.m_pAllocPtr}
    , m_pBaseArrayPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfRows{matrix.m_NrOfRows}
    , m_NrOfColumns{matrix.m_NrOfColumns}
    , m_RowCapacity{matrix.m_RowCapacity}
    , m_ColumnCapacity{matrix.m_ColumnCapacity}
{
    matrix.m_pAllocPtr = nullptr;
    matrix.m_pBaseArrayPtr = nullptr;
    matrix.m_NrOfRows = 0;
    matrix.m_NrOfColumns = 0;
    matrix.m_RowCapacity = 0;
    matrix.m_ColumnCapacity = 0;
}

template<typename DataType>
Matrix<DataType>::~Matrix()
{
    _deallocMemory();
}

template<typename DataType>
DataType& Matrix<DataType>::at(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[rowNr][columnNr];
}

template<typename DataType>
const DataType& Matrix<DataType>::at(size_type rowNr, Matrix::size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[rowNr][columnNr];
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](size_type index)
{
    CHECK_ERROR_CONDITION(index<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index>=m_NrOfRows*m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[index / m_NrOfColumns][index % m_NrOfColumns];
}

template <typename DataType>
Matrix<DataType>& Matrix<DataType>::operator=(const Matrix<DataType>& matrix)
{
    if (&matrix != this && (m_pBaseArrayPtr || matrix.m_pBaseArrayPtr))
    {
        const size_type c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
        const size_type c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

        if (m_RowCapacity != c_RowCapacityToAlloc || m_ColumnCapacity != c_ColumnCapacityToAlloc)
        {
            _deallocMemory();
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
        }
        else
        {
            m_NrOfRows = matrix.m_NrOfRows;
            m_NrOfColumns = matrix.m_NrOfColumns;
        }

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }

    return *this;
}

template<typename DataType>
Matrix<DataType>& Matrix<DataType>::operator=(Matrix<DataType>&& matrix)
{
    if (&matrix != this)
    {
        if (m_pBaseArrayPtr)
        {
            _deallocMemory();
        }

        if (matrix.m_pBaseArrayPtr)
        {
            m_pAllocPtr = matrix.m_pAllocPtr;
            m_pBaseArrayPtr = matrix.m_pBaseArrayPtr;
            m_NrOfRows = matrix.m_NrOfRows;
            m_NrOfColumns = matrix.m_NrOfColumns;
            m_RowCapacity = matrix.m_RowCapacity;
            m_ColumnCapacity = matrix.m_ColumnCapacity;

            matrix.m_pAllocPtr = nullptr;
            matrix.m_pBaseArrayPtr = nullptr;
            matrix.m_NrOfRows = 0;
            matrix.m_NrOfColumns = 0;
            matrix.m_RowCapacity = 0;
            matrix.m_ColumnCapacity = 0;
        }
    }

    return *this;
}

// a contiguous unidimensional array with the matrix elements (in row order) is returned to user
template<typename DataType>
DataType* Matrix<DataType>::getBaseArray(size_type& nrOfElements)
{
    DataType* pAllocPtr{nullptr};

    if (m_pBaseArrayPtr)
    {
        // when transfering ownership user should get exactly the number of elements contained in the used lines and columns (no extra capacity to be included)
        shrinkToFit();

        // effective transfer of ownership
        nrOfElements = m_NrOfRows * m_NrOfColumns;
        pAllocPtr = m_pAllocPtr;

        // empty the matrix object
        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = nullptr;
        m_pAllocPtr = nullptr;
        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
    }
    else
    {
        nrOfElements = 0;
    }

    return pAllocPtr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getNrOfRows() const
{
    return m_NrOfRows;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getNrOfColumns() const
{
    return m_NrOfColumns;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getRowCapacity() const
{
    return m_RowCapacity;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::getColumnCapacity() const
{
    return m_ColumnCapacity;
}

template <typename DataType>
void Matrix<DataType>::transpose(Matrix<DataType>& result)
{
    if (!m_NrOfRows)
    {
        if (&result != this)
        {
            result._deallocMemory();
        }
    }
    else if (&result == this)
    {
        const size_type c_NewRowCapacity{m_RowCapacity < m_NrOfColumns ?  m_NrOfColumns +  m_NrOfColumns/4 : m_RowCapacity};
        const size_type c_NewColumnCapacity{m_ColumnCapacity < m_NrOfRows ? m_NrOfRows + m_NrOfRows/4 : m_ColumnCapacity};

        Matrix<DataType> matrix{std::move(*this)};

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(matrix.m_NrOfColumns, matrix.m_NrOfRows, c_NewRowCapacity, c_NewColumnCapacity);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[col][row];
            }
        }
    }
    else
    {
        result._adjustSizeAndCapacity(m_NrOfColumns, m_NrOfRows);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                result.m_pBaseArrayPtr[col][row] = m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::clear()
{
    _deallocMemory();
}

template<typename DataType>
void Matrix<DataType>::resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity, size_type columnCapacity)
{
    CHECK_ERROR_CONDITION(nrOfRows<=0 || nrOfColumns<=0, Matr::errorMessages[Matr::Errors::NULL_OR_NEG_DIMENSION]);

    const size_type c_NewRowCapacity{rowCapacity > nrOfRows ? rowCapacity : nrOfRows};
    const size_type c_NewColumnCapacity{columnCapacity > nrOfColumns ? columnCapacity : nrOfColumns};

    if (c_NewRowCapacity != m_RowCapacity || c_NewColumnCapacity != m_ColumnCapacity)
    {
        size_type rowsToKeep{nrOfRows > m_NrOfRows ? m_NrOfRows : nrOfRows};
        size_type columnsToKeep{nrOfColumns > m_NrOfColumns ? m_NrOfColumns : nrOfColumns};

        Matrix<DataType> matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(nrOfRows, nrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

        for (size_type row{0}; row<rowsToKeep; ++row)
        {
            for (size_type col{0}; col<columnsToKeep; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
    else
    {
        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;
    }
}

template <typename DataType>
void Matrix<DataType>::resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& value, size_type rowCapacity, size_type columnCapacity)
{
    // DataType should support the assign (=) operator
    auto fillNewItems = [this, &value](size_type beginRowIndex, size_type endRowIndex, size_type beginColumnIndex, size_type endColumnIndex)
    {
        for (size_type row{beginRowIndex}; row<endRowIndex; ++row)
        {
            for (size_type col{beginColumnIndex}; col<endColumnIndex; ++col)
            {
                m_pBaseArrayPtr[row][col] = value;
            }
        }
    };

    const diff_type c_RowDelta{nrOfRows <= m_NrOfRows ? 0 : nrOfRows - m_NrOfRows};
    const diff_type c_ColumnDelta{nrOfColumns <= m_NrOfColumns ? 0 : nrOfColumns - m_NrOfColumns};

    resize(nrOfRows, nrOfColumns, rowCapacity, columnCapacity);

    if (c_RowDelta)
    {
        if (c_ColumnDelta)
        {
            fillNewItems(0, m_NrOfRows - c_RowDelta, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns);
            fillNewItems(m_NrOfRows - c_RowDelta, m_NrOfRows, 0, m_NrOfColumns - c_ColumnDelta);
            fillNewItems(m_NrOfRows - c_RowDelta, m_NrOfRows, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns);
        }
        else
        {
            fillNewItems(m_NrOfRows - c_RowDelta, m_NrOfRows, 0, m_NrOfColumns);
        }
    }
    else if (c_ColumnDelta)
    {
        fillNewItems(0, m_NrOfRows, m_NrOfColumns - c_ColumnDelta, m_NrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::shrinkToFit()
{
    if (m_RowCapacity != m_NrOfRows || m_ColumnCapacity != m_NrOfColumns)
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory(); // just for safety purposes, not actually needed
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }
        }
    }
}

template <typename DataType>
void Matrix<DataType>::insertRow (size_type rowNr)
{
    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(rowNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    // double row capacity if no spare capacity left (to defer any re-size when inserting further rows)
    if (m_NrOfRows == m_RowCapacity)
    {
        resize(m_NrOfRows+1, m_NrOfColumns, 2 * m_RowCapacity, m_ColumnCapacity);
    }
    else
    {
        ++m_NrOfRows;
    }

    // move the (previously) first row from unused capacity area into the insert position (all rows after the insert position moved one position upwards)
    DataType* insertedRow{m_pBaseArrayPtr[m_NrOfRows-1]};

    for (size_type row{m_NrOfRows-1}; row > rowNr; --row)
    {
        m_pBaseArrayPtr[row] = m_pBaseArrayPtr[row-1];
    }

    m_pBaseArrayPtr[rowNr] = insertedRow;
    insertedRow = nullptr;
}

template<typename DataType>
void Matrix<DataType>::insertRow(size_type rowNr, const DataType &dataType)
{
    insertRow(rowNr);

    for (size_type col{0}; col<m_NrOfColumns; ++col)
    {
        m_pBaseArrayPtr[rowNr][col] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::insertColumn(size_type columnNr)
{
    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr>m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix matrix{};
        std::swap(*this, matrix);
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns + 1, matrix.m_RowCapacity, 2 * matrix.m_NrOfColumns);

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(size_type col{columnNr+1}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col-1];
            }
        }
    }
    else
    {
        ++m_NrOfColumns;

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{m_NrOfColumns-1}; col>columnNr; --col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col-1];
            }
        }
    }
}

template<typename DataType>
void Matrix<DataType>::insertColumn(size_type columnNr, const DataType &dataType)
{
    insertColumn(columnNr);

    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        m_pBaseArrayPtr[row][columnNr] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::eraseRow (size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(rowNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);

    // this corner case needs to be considered for avoiding situations when number of rows is 0 and number of columns is different from 0
    if (m_NrOfRows == 1)
    {
        _deallocMemory();
    }
    else
    {
        // move the rows downwards one position to fill in the gap
        DataType* removedRow{m_pBaseArrayPtr[rowNr]};
        for (size_type row{rowNr}; row < m_NrOfRows-1; ++row)
        {
            m_pBaseArrayPtr[row] = m_pBaseArrayPtr[row+1];
        }

        // removed row goes into the unused capacity area (first unused row)
        m_pBaseArrayPtr[m_NrOfRows-1] = removedRow;
        removedRow = nullptr;
        --m_NrOfRows;

        // prevent overcapacity
        if (m_NrOfRows <= m_RowCapacity/4)
        {
            resize(m_NrOfRows, m_NrOfColumns, 2 * m_NrOfRows, m_ColumnCapacity);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::eraseColumn(size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (m_NrOfColumns==1)
    {
        _deallocMemory();
    }
    else if (m_NrOfColumns-1 <= m_ColumnCapacity/4)
    {
        Matrix matrix{};
        std::swap(*this, matrix);
        _deallocMemory();
        _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns-1, matrix.m_RowCapacity, (matrix.m_NrOfColumns - 1) * 2);

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{0}; col<columnNr; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col];
            }

            for(size_type col{columnNr}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = matrix.m_pBaseArrayPtr[row][col+1];
            }
        }
    }
    else
    {
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for(size_type col{columnNr}; col<m_NrOfColumns-1; ++col)
            {
                m_pBaseArrayPtr[row][col] = m_pBaseArrayPtr[row][col+1];
            }
        }

        --m_NrOfColumns;
    }
}

template<typename DataType>
void Matrix<DataType>::catByRow(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    CHECK_ERROR_CONDITION(firstSrcMatrix.m_NrOfColumns != secondSrcMatrix.m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    const size_type c_OldNrOfRows{m_NrOfRows};
    const size_type c_NewNrOfRows{firstSrcMatrix.m_NrOfRows + secondSrcMatrix.m_NrOfRows};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};
    const size_type c_NewRowCapacity{c_OldRowCapacity < c_NewNrOfRows ? c_NewNrOfRows + c_NewNrOfRows / 4 : c_OldRowCapacity};
    const size_type c_NewColumnCapacity{firstSrcMatrix.m_NrOfColumns + firstSrcMatrix.m_NrOfColumns / 4};

    auto copyElements = [this](const Matrix& srcMatrix, size_type rangeStart, size_type rangeEnd)
    {
        for (size_type row{rangeStart}; row<rangeEnd; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = srcMatrix.m_pBaseArrayPtr[row-rangeStart][col];
            }
        }
    };

    if (&firstSrcMatrix == this && (&secondSrcMatrix != this))
    {
        if (c_OldRowCapacity < c_NewNrOfRows)
        {
            resize(c_NewNrOfRows, m_NrOfColumns, c_NewRowCapacity, m_ColumnCapacity);
        }
        else
        {
            m_NrOfRows = c_NewNrOfRows;
        }

        copyElements(secondSrcMatrix, c_OldNrOfRows, c_NewNrOfRows);
    }
    else if (&firstSrcMatrix != this && (&secondSrcMatrix == this))
    {
        Matrix<DataType> matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for the good practice's sake!
        _allocMemory(c_NewNrOfRows, matrix.m_NrOfColumns, c_NewRowCapacity, matrix.m_ColumnCapacity);

        copyElements(firstSrcMatrix, 0, firstSrcMatrix.m_NrOfRows);
        copyElements(matrix, firstSrcMatrix.m_NrOfRows, m_NrOfRows);
    }
    else if (&firstSrcMatrix == this && (&secondSrcMatrix == this))
    {
        if (c_OldRowCapacity < c_NewNrOfRows)
        {
            resize(c_NewNrOfRows, m_NrOfColumns, c_NewRowCapacity, m_ColumnCapacity);
        }
        else
        {
            m_NrOfRows = c_NewNrOfRows;
        }

        copyElements(*this, c_OldNrOfRows, c_NewNrOfRows);
    }
    else
    {
        if (c_OldRowCapacity < c_NewNrOfRows || c_OldColumnCapacity < firstSrcMatrix.m_NrOfColumns)
        {
            _deallocMemory();
            _allocMemory(c_NewNrOfRows, firstSrcMatrix.m_NrOfColumns, c_OldRowCapacity < c_NewNrOfRows ? c_NewRowCapacity : c_OldRowCapacity,
                         c_OldColumnCapacity < firstSrcMatrix.m_NrOfColumns ? c_NewColumnCapacity : c_OldColumnCapacity);
        }
        else
        {
            m_NrOfRows = c_NewNrOfRows;
            m_NrOfColumns = firstSrcMatrix.m_NrOfColumns;
        }

        copyElements(firstSrcMatrix, 0, firstSrcMatrix.m_NrOfRows);
        copyElements(secondSrcMatrix, firstSrcMatrix.m_NrOfRows, c_NewNrOfRows);
    }
}

template<typename DataType>
void Matrix<DataType>::catByColumn(Matrix<DataType>& firstSrcMatrix, Matrix<DataType>& secondSrcMatrix)
{
    CHECK_ERROR_CONDITION(firstSrcMatrix.m_NrOfRows != secondSrcMatrix.m_NrOfRows, Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH]);

    auto concatenate = [this](Matrix& firstSrcMatrix, Matrix& secondSrcMatrix)
    {
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<firstSrcMatrix.m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = firstSrcMatrix.m_pBaseArrayPtr[row][col];
            }
        }

        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{firstSrcMatrix.m_NrOfColumns}; col<m_NrOfColumns; ++col)
            {
                m_pBaseArrayPtr[row][col] = secondSrcMatrix.m_pBaseArrayPtr[row][col-firstSrcMatrix.m_NrOfColumns];
            }
        }
    };

    const size_type c_NewNrOfRows{firstSrcMatrix.m_NrOfRows};
    const size_type c_NewNrOfColumns{firstSrcMatrix.m_NrOfColumns + secondSrcMatrix.m_NrOfColumns};
    const size_type c_NewRowCapacity{c_NewNrOfRows + c_NewNrOfRows / 4};
    const size_type c_NewColumnCapacity{c_NewNrOfColumns + c_NewNrOfColumns / 4};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};

    Matrix matrix{};

    if (&firstSrcMatrix == this || (&secondSrcMatrix == this))
    {
        matrix = std::move(*this);
    }

    _deallocMemory(); // actually not required, just for the good practice's sake!
    _allocMemory(c_NewNrOfRows,
                 c_NewNrOfColumns,
                 c_OldRowCapacity < c_NewNrOfRows ? c_NewRowCapacity : c_OldRowCapacity,
                 c_OldColumnCapacity < c_NewNrOfColumns ? c_NewColumnCapacity : c_OldColumnCapacity);

    concatenate(&firstSrcMatrix == this ? matrix : firstSrcMatrix, &secondSrcMatrix == this ? matrix : secondSrcMatrix);
}

template<typename DataType>
void Matrix<DataType>::splitByRow(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitRowNr)
{
    CHECK_ERROR_CONDITION(&firstDestMatrix == &secondDestMatrix, Matr::errorMessages[Matr::Errors::SAME_VARIABLE_TWO_ARGS]);
    CHECK_ERROR_CONDITION(splitRowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(splitRowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(splitRowNr == 0, Matr::errorMessages[Matr::Errors::RESULT_NO_ROWS]);

    const size_type c_FirstDestMatrixNrOfRows{splitRowNr};
    const size_type c_SecondDestMatrixNrOfRows{m_NrOfRows - splitRowNr};
    const size_type c_EachDestMatrixNrOfColumns{m_NrOfColumns};

    auto copyElements = [this](Matrix& destMatrix, size_type rangeStart, size_type rangeEnd)
    {
        for (size_type row{rangeStart}; row<rangeEnd; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                destMatrix.m_pBaseArrayPtr[row-rangeStart][col] = m_pBaseArrayPtr[row][col];
            }
        }
    };

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_EachDestMatrixNrOfColumns);
        copyElements(secondDestMatrix, splitRowNr, m_NrOfRows);
        firstDestMatrix.m_NrOfRows = c_FirstDestMatrixNrOfRows;
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_EachDestMatrixNrOfColumns);
        copyElements(firstDestMatrix, 0, splitRowNr);

        for (size_type row{0}; row < c_SecondDestMatrixNrOfRows; ++row)
        {
            swapRows(row, *this, row+splitRowNr);
        }

        m_NrOfRows = c_SecondDestMatrixNrOfRows;
    }
    else
    {
        firstDestMatrix._adjustSizeAndCapacity(c_FirstDestMatrixNrOfRows, c_EachDestMatrixNrOfColumns);
        secondDestMatrix._adjustSizeAndCapacity(c_SecondDestMatrixNrOfRows, c_EachDestMatrixNrOfColumns);
        copyElements(firstDestMatrix, 0, splitRowNr);
        copyElements(secondDestMatrix, splitRowNr, m_NrOfRows);
    }
}

template<typename DataType>
void Matrix<DataType>::splitByColumn(Matrix<DataType>& firstDestMatrix, Matrix<DataType>& secondDestMatrix, size_type splitColumnNr)
{
    CHECK_ERROR_CONDITION(&firstDestMatrix == &secondDestMatrix, Matr::errorMessages[Matr::Errors::SAME_VARIABLE_TWO_ARGS]);
    CHECK_ERROR_CONDITION(splitColumnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(splitColumnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(splitColumnNr == 0, Matr::errorMessages[Matr::Errors::RESULT_NO_COLUMNS]);

    const size_type c_EachDestMatrixNrOfRows{m_NrOfRows};
    const size_type c_FirstDestMatrixNrOfColumns{splitColumnNr};
    const size_type c_SecondDestMatrixNrOfColumns{m_NrOfColumns - splitColumnNr};

    auto copyElements = [c_EachDestMatrixNrOfRows](const Matrix& srcMatrix, Matrix& destMatrix, size_type rangeStart, size_type rangeEnd, diff_type srcColumnIndexOffset, diff_type destColumnIndexOffset)
    {
        for (size_type row{0}; row<c_EachDestMatrixNrOfRows; ++row)
        {
            for (size_type col{rangeStart}; col<rangeEnd; ++col)
            {
                destMatrix.m_pBaseArrayPtr[row][col-destColumnIndexOffset] = srcMatrix.m_pBaseArrayPtr[row][col+srcColumnIndexOffset];
            }
        }
    };

    if (&firstDestMatrix == this && (&secondDestMatrix != this))
    {
        secondDestMatrix._adjustSizeAndCapacity(c_EachDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        copyElements(*this, secondDestMatrix, splitColumnNr, m_NrOfColumns, 0, splitColumnNr);

        Matrix matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for the good practice's sake!
        _allocMemory(c_EachDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        copyElements(matrix, firstDestMatrix, 0, splitColumnNr, 0, 0);
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_EachDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        copyElements(*this, firstDestMatrix, 0, splitColumnNr, 0, 0);

        Matrix matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for the good practice's sake!
        _allocMemory(c_EachDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        copyElements(matrix, *this, 0, c_SecondDestMatrixNrOfColumns, splitColumnNr, 0);
    }
    else
    {
        firstDestMatrix._adjustSizeAndCapacity(c_EachDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);
        secondDestMatrix._adjustSizeAndCapacity(c_EachDestMatrixNrOfRows, c_SecondDestMatrixNrOfColumns);

        copyElements(*this, firstDestMatrix, 0, splitColumnNr, 0, 0);
        copyElements(*this, secondDestMatrix, splitColumnNr, m_NrOfColumns, 0, splitColumnNr);
    }
}

template <typename DataType>
void Matrix<DataType>::swapItems(size_type rowNr, size_type columnNr, Matrix<DataType>& matrix, size_type matrixRowNr, size_type matrixColumnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0 || matrixRowNr<0 || matrixColumnNr<0,  Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns || matrixRowNr>=matrix.m_NrOfRows || matrixColumnNr>=matrix.m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    if (rowNr!=matrixRowNr || columnNr!=matrixColumnNr || &matrix != this)
    {
        std::swap(m_pBaseArrayPtr[rowNr][columnNr], matrix.m_pBaseArrayPtr[matrixRowNr][matrixColumnNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRows(size_type rowNr, Matrix& matrix, size_type matrixRowNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || matrixRowNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || matrixRowNr>=matrix.m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(m_NrOfColumns!=matrix.m_NrOfColumns, Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_ROW_LENGTH]);

    if (rowNr!=matrixRowNr || &matrix!=this)
    {
        std::swap(m_pBaseArrayPtr[rowNr], matrix.m_pBaseArrayPtr[matrixRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumns(size_type columnNr, Matrix& matrix, size_type matrixColumnNr)
{
    CHECK_ERROR_CONDITION(columnNr<0 || matrixColumnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr>=m_NrOfColumns || matrixColumnNr>=matrix.m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(m_NrOfRows!=matrix.m_NrOfRows, Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH]);

    if (columnNr!=matrixColumnNr || &matrix!=this)
    {
        for(size_type row{0}; row<m_NrOfRows; ++row)
        {
            // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
            DataType swap{m_pBaseArrayPtr[row][columnNr]};
            m_pBaseArrayPtr[row][columnNr] = matrix.m_pBaseArrayPtr[row][matrixColumnNr];
            matrix.m_pBaseArrayPtr[row][matrixColumnNr] = swap;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::swapRowColumn(size_type rowNr, Matrix<DataType>& matrix, size_type matrixColumnNr)
{
    CHECK_ERROR_CONDITION(&matrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARG]);
    CHECK_ERROR_CONDITION(rowNr<0 || matrixColumnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(m_NrOfColumns!=matrix.m_NrOfRows, Matr::errorMessages[Matr::Errors::MATRIXES_ROWS_UNEQUAL_COLUMNS]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(matrixColumnNr>=matrix.m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    for (size_type col{0}; col<m_NrOfColumns; ++col)
    {
        // for the moment we don't use the std::swap (might be too many function calls if it doesn't get inlined)
        DataType swap{m_pBaseArrayPtr[rowNr][col]};
        m_pBaseArrayPtr[rowNr][col] = matrix.m_pBaseArrayPtr[col][matrixColumnNr];
        matrix.m_pBaseArrayPtr[col][matrixColumnNr] = swap;
    }
}

template <typename DataType> void Matrix<DataType>::setAllItemsToValue(const DataType& value)
{
    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        for (size_type col{0}; col<m_NrOfColumns; ++col)
        {
            m_pBaseArrayPtr[row][col] = value;
        }
    }
}

template <typename DataType>
void Matrix<DataType>::copy(const Matrix<DataType>& srcMatrix, size_type nrOfRows, size_type nrOfColumns, size_type srcMatrixRowNr, size_type srcMatrixColumnNr, size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(&srcMatrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARG]);
    CHECK_ERROR_CONDITION(nrOfRows<0 || nrOfColumns<0 || srcMatrixRowNr<0 || srcMatrixColumnNr<0 || rowNr<0 || columnNr<0,
                          Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(srcMatrixRowNr + nrOfRows > srcMatrix.m_NrOfRows || srcMatrixColumnNr + nrOfColumns > srcMatrix.m_NrOfColumns || rowNr+nrOfRows > m_NrOfRows || columnNr+nrOfColumns > m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    if (nrOfRows && nrOfColumns)
    {
        for (size_type row{0}; row<nrOfRows; ++row)
        {
            for (size_type col{0}; col<nrOfColumns; ++col)
            {
                m_pBaseArrayPtr[rowNr+row][columnNr+col] = srcMatrix.m_pBaseArrayPtr[srcMatrixRowNr+row][srcMatrixColumnNr+col];
            }
        }
    }
}

template<typename DataType>
Matrix<DataType>::operator bool() const
{
    bool result{false};

    if (m_pBaseArrayPtr)
    {
        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col])
                {
                    result = true;
                    break;
                }
            }
        }
    }

    return result;
}

template <typename DataType>
bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix) const
{
    return _isEqualTo(matrix);
}

template<typename DataType>
bool Matrix<DataType>::operator!=(const Matrix<DataType> &matrix) const
{
    return !_isEqualTo(matrix);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zBegin()
{
    return ZIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zEnd()
{
    return ZIterator{*this, m_NrOfRows-1, m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowBegin(size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    return ZIterator{*this, rowNr, 0};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowEnd(size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    ZIterator it{};

    if (rowNr < m_NrOfRows-1)
    {
        it = ZIterator{*this, rowNr+1, 0};
    }
    else
    {
        it = ZIterator{*this, rowNr, m_NrOfColumns};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ZIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(size_type index)
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ZIterator{*this, index / m_NrOfColumns, index % m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZBegin() const
{
    return ConstZIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZEnd() const
{
    return ConstZIterator{*this, m_NrOfRows-1, m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowBegin(size_type rowNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    return ConstZIterator{*this, rowNr, 0};
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowEnd(size_type rowNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    ConstZIterator it{};

    if (rowNr < m_NrOfRows-1)
    {
        it = ConstZIterator{*this, rowNr+1, 0};
    }
    else
    {
        it = ConstZIterator{*this, rowNr, m_NrOfColumns};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstZIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(size_type index) const
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstZIterator{*this, index / m_NrOfColumns, index % m_NrOfColumns};
}


template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZBegin()
{
    return ReverseZIterator{*this, m_NrOfRows-1, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZEnd()
{
    return ReverseZIterator{*this, 0, -1};
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowBegin(size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    return ReverseZIterator{*this, rowNr, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowEnd(size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    ReverseZIterator it{};

    if (rowNr > 0)
    {
        it = ReverseZIterator{*this, rowNr-1, m_NrOfColumns-1};
    }
    else
    {
        it = ReverseZIterator{*this, 0, -1};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ReverseZIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(size_type index)
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ReverseZIterator{*this, index / m_NrOfColumns, index % m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZBegin() const
{
    return ConstReverseZIterator{*this, m_NrOfRows-1, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZEnd() const
{
    return ConstReverseZIterator{*this, 0, -1};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowBegin(size_type rowNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    return ConstReverseZIterator{*this, rowNr, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowEnd(size_type rowNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    ConstReverseZIterator it{};

    if (rowNr > 0)
    {
        it = ConstReverseZIterator{*this, rowNr-1, m_NrOfColumns-1};
    }
    else
    {
        it = ConstReverseZIterator{*this, 0, -1};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstReverseZIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(size_type index) const
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstReverseZIterator{*this, index / m_NrOfColumns, index % m_NrOfColumns};
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(size_type diagNr)
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
    return DIterator{*this, diagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    const size_type c_BeginRowNr{columnNr < rowNr ? rowNr - columnNr : 0};
    const size_type c_BeginColumnNr{columnNr < rowNr ? 0 : columnNr - rowNr};

    return DIterator{*this, c_BeginRowNr, c_BeginColumnNr};
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(size_type diagNr)
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);

    const size_type c_BeginRowNr{diagNr < 0 ? -diagNr : 0};
    const size_type c_BeginColumnNr{diagNr < 0 ? 0 : diagNr};
    const size_type c_EndDiagIndex{std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};

    return DIterator{*this, diagNr, c_EndDiagIndex, true};
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return dEnd(columnNr-rowNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::getDIterator(Matrix::size_type first, Matrix::size_type second, bool isRelative)
{
    if (isRelative)
    {
        CHECK_ERROR_CONDITION(first < (1-m_NrOfRows) || first > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);

        const size_type c_BeginRowNr{first < 0 ? -first : 0};
        const size_type c_BeginColumnNr{first < 0 ? 0 : first};
        const size_type c_DiagSize {std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};
        (void)c_DiagSize;

        CHECK_ERROR_CONDITION(second >= c_DiagSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);
    }
    else
    {
        CHECK_ERROR_CONDITION(first < 0 || second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
        CHECK_ERROR_CONDITION(first >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    }
    return DIterator{*this, first, second, isRelative};
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(size_type diagNr) const
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
    return ConstDIterator{*this, diagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    const size_type c_BeginRowNr{columnNr < rowNr ? rowNr - columnNr : 0};
    const size_type c_BeginColumnNr{columnNr < rowNr ? 0 : columnNr - rowNr};

    return ConstDIterator{*this, c_BeginRowNr, c_BeginColumnNr};
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(size_type diagNr) const
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);

    const size_type c_BeginRowNr{diagNr < 0 ? -diagNr : 0};
    const size_type c_BeginColumnNr{diagNr < 0 ? 0 : diagNr};
    const size_type c_EndDiagIndex{std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};

    return ConstDIterator{*this, diagNr, c_EndDiagIndex, true};
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return constDEnd(columnNr-rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::getConstDIterator(Matrix::size_type first, Matrix::size_type second, bool isRelative) const
{
    if (isRelative)
    {
        CHECK_ERROR_CONDITION(first < (1-m_NrOfRows) || first > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);

        const size_type c_BeginRowNr{first < 0 ? -first : 0};
        const size_type c_BeginColumnNr{first < 0 ? 0 : first};
        const size_type c_DiagSize {std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};
        (void)c_DiagSize;

        CHECK_ERROR_CONDITION(second >= c_DiagSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);
    }
    else
    {
        CHECK_ERROR_CONDITION(first < 0 || second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
        CHECK_ERROR_CONDITION(first >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    }
    return ConstDIterator{*this, first, second, isRelative};
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(size_type diagNr)
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
    return ReverseDIterator{*this, diagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= getNrOfRows(), Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= getNrOfColumns(), Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    const size_type c_DiagNr{columnNr - rowNr};

    return ReverseDIterator{*this, c_DiagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(size_type diagNr)
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);

    const size_type c_DiagBeginRowNr{diagNr < 0 ? -diagNr : 0};
    const size_type c_DiagBeginColumnNr{diagNr < 0 ? 0 : diagNr};
    const size_type c_EndDiagIndex{std::min(m_NrOfRows - c_DiagBeginRowNr, m_NrOfColumns - c_DiagBeginColumnNr)};

    return ReverseDIterator{*this, diagNr, c_EndDiagIndex, true};
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return reverseDEnd(columnNr-rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::getReverseDIterator(Matrix::size_type first, Matrix::size_type second, bool isRelative)
{
    if (isRelative)
    {
        CHECK_ERROR_CONDITION(first < (1-m_NrOfRows) || first > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);

        const size_type c_BeginRowNr{first < 0 ? -first : 0};
        const size_type c_BeginColumnNr{first < 0 ? 0 : first};
        const size_type c_DiagSize {std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};
        (void)c_DiagSize;

        CHECK_ERROR_CONDITION(second >= c_DiagSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);
    }
    else
    {
        CHECK_ERROR_CONDITION(first < 0 || second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
        CHECK_ERROR_CONDITION(first >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    }

    return ReverseDIterator{*this, first, second, isRelative};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(size_type diagNr) const
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
    return ConstReverseDIterator{*this, diagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= getNrOfRows(), Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= getNrOfColumns(), Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    const size_type c_DiagNr{columnNr - rowNr};

    return ConstReverseDIterator{*this, c_DiagNr, 0, true};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(size_type diagNr) const
{
    CHECK_ERROR_CONDITION(diagNr < (1-m_NrOfRows) || diagNr > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);

    const size_type c_DiagBeginRowNr{diagNr < 0 ? -diagNr : 0};
    const size_type c_DiagBeginColumnNr{diagNr < 0 ? 0 : diagNr};
    const size_type c_EndDiagIndex{std::min(m_NrOfRows - c_DiagBeginRowNr, m_NrOfColumns - c_DiagBeginColumnNr)};

    return ConstReverseDIterator{*this, diagNr, c_EndDiagIndex, true};
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr < 0 || columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return constReverseDEnd(columnNr-rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::getConstReverseDIterator(Matrix::size_type first, Matrix::size_type second, bool isRelative) const
{
    if (isRelative)
    {
        CHECK_ERROR_CONDITION(first < (1-m_NrOfRows) || first > (m_NrOfColumns-1), Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);

        const size_type c_BeginRowNr{first < 0 ? -first : 0};
        const size_type c_BeginColumnNr{first < 0 ? 0 : first};
        const size_type c_DiagSize {std::min(m_NrOfRows - c_BeginRowNr, m_NrOfColumns - c_BeginColumnNr)};
        (void)c_DiagSize;

        CHECK_ERROR_CONDITION(second >= c_DiagSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]);
    }
    else
    {
        CHECK_ERROR_CONDITION(first < 0 || second < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
        CHECK_ERROR_CONDITION(first >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
        CHECK_ERROR_CONDITION(second >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    }
    return ConstReverseDIterator{*this, first, second, isRelative};
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nBegin()
{
    return NIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nEnd()
{
    return NIterator{*this, m_NrOfRows, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnBegin(size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return NIterator{*this, 0, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnEnd(size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    NIterator it{};

    if (columnNr < m_NrOfColumns-1)
    {
        it = NIterator{*this, 0, columnNr+1};
    }
    else
    {
        it = NIterator{*this, m_NrOfRows, columnNr};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return NIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(size_type index)
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return NIterator{*this, index % m_NrOfRows, index / m_NrOfRows};
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNBegin() const
{
    return ConstNIterator{*this, 0, 0};
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNEnd() const
{
    return ConstNIterator{*this, m_NrOfRows, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnBegin(size_type columnNr) const
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return ConstNIterator{*this, 0, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnEnd(size_type columnNr) const
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    ConstNIterator it{};

    if (columnNr < m_NrOfColumns-1)
    {
        it = ConstNIterator{*this, 0, columnNr+1};
    }
    else
    {
        it = ConstNIterator{*this, m_NrOfRows, columnNr};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(size_type rowNr, size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstNIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(size_type index) const
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ConstNIterator{*this, index % m_NrOfRows, index / m_NrOfRows};
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNBegin()
{
    return ReverseNIterator{*this, m_NrOfRows-1, m_NrOfColumns-1};
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNEnd()
{
    return ReverseNIterator{*this, -1, 0};
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnBegin(size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    return ReverseNIterator{*this, m_NrOfRows-1, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnEnd(size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    ReverseNIterator it{};

    if (columnNr > 0)
    {
        it = ReverseNIterator{*this, m_NrOfRows-1, columnNr-1};
    }
    else
    {
        it = ReverseNIterator{*this, -1, 0};
    }

    return it;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(size_type rowNr, size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ReverseNIterator{*this, rowNr, columnNr};
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(size_type index)
{
    CHECK_ERROR_CONDITION(index < 0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return ReverseNIterator{*this, index % m_NrOfRows, index / m_NrOfRows};
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::begin()
{
    return zBegin();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::end()
{
    return zEnd();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::cbegin() const
{
    return constZBegin();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::cend() const
{
    return constZEnd();
}

template<typename DataType>
void Matrix<DataType>::_allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity, size_type columnCapacity)
{
    if (nrOfRows > 0 && nrOfColumns > 0)
    {
        m_RowCapacity = rowCapacity < nrOfRows ? nrOfRows : rowCapacity;
        m_ColumnCapacity = columnCapacity < nrOfColumns ? nrOfColumns : columnCapacity;

        m_pBaseArrayPtr = new DataType*[m_RowCapacity];
        m_pAllocPtr = new DataType[m_RowCapacity * m_ColumnCapacity]; // allocate all elements in a single array

        // map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed)
        for (size_type row{0}; row<m_RowCapacity; ++row)
        {
            m_pBaseArrayPtr[row] = m_pAllocPtr + (row * m_ColumnCapacity);
        }

        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;
    }
    else
    {
        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
        m_pBaseArrayPtr = nullptr;
        m_pAllocPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    if (m_pBaseArrayPtr)
    {
        // cut access of row pointers to allocated memory
        for (size_type row{0}; row<m_RowCapacity; ++row)
        {
            m_pBaseArrayPtr[row] = nullptr;
        }

        delete []m_pBaseArrayPtr;
        m_pBaseArrayPtr = nullptr;

        delete []m_pAllocPtr;
        m_pAllocPtr = nullptr;

        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
    }
}

template<typename DataType>
bool Matrix<DataType>::_isEqualTo(const Matrix<DataType>& matrix) const
{
    bool areEqual{false};

    if (&matrix == this)
    {
        areEqual = true;
    }
    else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
    {
        //change assumption of equality to true until proving the opposite
        areEqual = true;

        bool continueChecking{true};

        for (size_type row{0}; row<m_NrOfRows; ++row)
        {
            for (size_type col{0}; col<m_NrOfColumns; ++col)
            {
                if (m_pBaseArrayPtr[row][col] != matrix.m_pBaseArrayPtr[row][col])
                {
                    continueChecking = false;
                    areEqual = false;
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
void Matrix<DataType>::_adjustSizeAndCapacity(size_type nrOfRows, size_type nrOfColumns)
{
    const size_type c_NewRowCapacity{nrOfRows + nrOfRows/4};
    const size_type c_NewColumnCapacity{nrOfColumns + nrOfColumns/4};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};

    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns, c_OldRowCapacity < nrOfRows ? c_NewRowCapacity : c_OldRowCapacity, c_OldColumnCapacity < nrOfColumns ? c_NewColumnCapacity : c_OldColumnCapacity);
}

#endif // MATRIX_H
