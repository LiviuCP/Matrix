#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include <utility>
#include <cmath>

#include "../Utils/iteratorutils.h"
#include "../Utils/errorhandling.h"

template <typename DataType>
class Matrix
{
public: 
    using size_type = int;
    using diff_type = int;

    class ZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ZIterator)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ZIterator, DataType, size_type)
    };

    class ConstZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstZIterator)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstZIterator, DataType, size_type)
    };

    class ReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseZIterator)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, DataType, size_type)
    };

    class ConstReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, DataType, size_type)
    };

    class NIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(NIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(NIterator)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(NIterator, DataType, size_type)
    };

    class ConstNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstNIterator)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstNIterator, DataType, size_type)
    };

    class ReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseNIterator)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, DataType, size_type)
    };

    class ConstReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, DataType, size_type)
    };

    class DIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(DIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(DIterator, DataType, size_type)

    };

    class ConstDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstDIterator, DataType, size_type)
    };

    class ReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, DataType, size_type)
    };

    class ConstReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, DataType, size_type)
    };

    class MIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(MIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(MIterator, DataType, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstMIterator, DataType, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, DataType, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, DataType, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
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
    const DataType& operator[](size_type index) const;

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
    void resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0, size_type columnCapacity = 0);

    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType, size_type rowCapacity = 0, size_type columnCapacity = 0);

    void shrinkToFit();

    void insertRow(size_type rowNr);
    void insertRow(size_type rowNr, const DataType& dataType);
    void insertColumn(size_type columnNr);
    void insertColumn(size_type columnNr, const DataType& dataType);
    void eraseRow(size_type rowNr);
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
    void copy(const Matrix<DataType>& src, size_type nrOfRows, size_type nrOfColumns, size_type srcMatrixRowNr = 0, size_type srcMatrixColumnNr = 0, size_type rowNr = 0, size_type columnNr = 0);

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

    ConstReverseNIterator constReverseNBegin() const;
    ConstReverseNIterator constReverseNEnd() const;
    ConstReverseNIterator constReverseNColumnBegin(size_type columnNr) const;
    ConstReverseNIterator constReverseNColumnEnd(size_type columnNr) const;
    ConstReverseNIterator getConstReverseNIterator(size_type rowNr, size_type columnNr) const;
    ConstReverseNIterator getConstReverseNIterator(size_type index) const;

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

    MIterator mBegin(size_type diagNr);
    MIterator mBegin(size_type rowNr, int columnNr);
    MIterator mEnd(size_type diagNr);
    MIterator mEnd(size_type rowNr, int columnNr);
    MIterator getMIterator(size_type first, size_type second, bool isRelative = false);

    ConstMIterator constMBegin(size_type diagNr);
    ConstMIterator constMBegin(size_type rowNr, int columnNr);
    ConstMIterator constMEnd(size_type diagNr);
    ConstMIterator constMEnd(size_type rowNr, int columnNr);
    ConstMIterator getConstMIterator(size_type first, size_type second, bool isRelative = false);

    ReverseMIterator reverseMBegin(size_type diagNr);
    ReverseMIterator reverseMBegin(size_type rowNr, size_type columnNr);
    ReverseMIterator reverseMEnd(size_type diagNr);
    ReverseMIterator reverseMEnd(size_type rowNr, size_type columnNr);
    ReverseMIterator getReverseMIterator(size_type first, size_type second, bool isRelative = false);

    ConstReverseMIterator constReverseMBegin(size_type diagNr);
    ConstReverseMIterator constReverseMBegin(size_type rowNr, size_type columnNr);
    ConstReverseMIterator constReverseMEnd(size_type diagNr);
    ConstReverseMIterator constReverseMEnd(size_type rowNr, size_type columnNr);
    ConstReverseMIterator getConstReverseMIterator(size_type first, size_type second, bool isRelative = false);

    // required for being able to use the "auto" keyword for iterating through the matrix elements
    ZIterator begin();
    ZIterator end();

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
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator+(Matrix<DataType>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator-(Matrix<DataType>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ZIterator::operator+=(Matrix<DataType>::ZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ZIterator::operator-=(Matrix<DataType>::ZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::difference_type Matrix<DataType>::ZIterator::operator-(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator==(const Matrix<DataType>::ZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator!=(const Matrix<DataType>::ZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator<=(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator>=(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ZIterator::operator*()
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ZIterator::operator->()
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ZIterator::operator[](Matrix<DataType>::ZIterator::difference_type index)
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator(const Matrix<DataType>& matrix,
                                       Matrix<DataType>::size_type rowNr,
                                       Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, rowNr, columnNr);
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr)
}

// 2) ConstZIterator

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator+(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ConstZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator-(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ConstZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::operator+=(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::operator-=(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator::difference_type Matrix<DataType>::ConstZIterator::operator-(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator==(const Matrix<DataType>::ConstZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator!=(const Matrix<DataType>::ConstZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator<(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator<=(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator>(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator>=(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstZIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstZIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstZIterator::operator[](Matrix<DataType>::ConstZIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator(const Matrix<DataType>& matrix,
                                                 Matrix<DataType>::size_type rowNr,
                                                 Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, rowNr, columnNr);
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
void Matrix<DataType>::ConstZIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 3) ReverseZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to ZIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator+(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ReverseZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator-(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ReverseZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::operator+=(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::operator-=(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::difference_type Matrix<DataType>::ReverseZIterator::operator-(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator==(const Matrix<DataType>::ReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator!=(const Matrix<DataType>::ReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator<(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator<=(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator>(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator>=(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseZIterator::operator*()
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseZIterator::operator->()
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseZIterator::operator[](Matrix<DataType>::ReverseZIterator::difference_type index)
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator(const Matrix<DataType>& matrix,
                                                     Matrix<DataType>::size_type rowNr,
                                                     Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, rowNr, columnNr);
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
void Matrix<DataType>::ReverseZIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 4) ConstReverseZIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator+(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ConstReverseZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator-(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ConstReverseZIterator, m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::operator+=(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::operator-=(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator::difference_type Matrix<DataType>::ConstReverseZIterator::operator-(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator==(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator!=(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator<(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator<=(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator>(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator>=(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseZIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstReverseZIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseZIterator::operator[](Matrix<DataType>::ConstReverseZIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator(const Matrix<DataType>& matrix,
                                                               Matrix<DataType>::size_type rowNr,
                                                               Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, rowNr, columnNr);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseZIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 5) NIterator - iterates within matrix from [0][0] to the end column by column
template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator++()
{
    ITERATOR_PRE_INCREMENT()
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(NIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(NIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator+(Matrix<DataType>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(NIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator-(Matrix<DataType>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(NIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
void Matrix<DataType>::NIterator::operator+=(Matrix<DataType>::NIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::NIterator::operator-=(Matrix<DataType>::NIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::NIterator::difference_type Matrix<DataType>::NIterator::operator-(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator==(const Matrix<DataType>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator!=(const Matrix<DataType>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator<(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator<=(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator>(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator>=(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::NIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::NIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::NIterator::operator*()
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType* Matrix<DataType>::NIterator::operator->()
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType& Matrix<DataType>::NIterator::operator[](Matrix<DataType>::NIterator::difference_type index)
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, %, /, index);
}

template<typename DataType>
Matrix<DataType>::NIterator::NIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::NIterator::NIterator(const Matrix<DataType>& matrix,
                                       Matrix<DataType>::size_type rowNr,
                                       Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, columnNr, rowNr);
}

template<typename DataType>
void Matrix<DataType>::NIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template<typename DataType>
void Matrix<DataType>::NIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 6) ConstNIterator
template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator+(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ConstNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator-(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR(ConstNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::operator+=(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::operator-=(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator::difference_type Matrix<DataType>::ConstNIterator::operator-(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator==(const Matrix<DataType>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator!=(const Matrix<DataType>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator<(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator<=(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator>(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator>=(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstNIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstNIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstNIterator::operator[](Matrix<DataType>::ConstNIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator(const Matrix<DataType>& matrix,
                                                 Matrix<DataType>::size_type rowNr,
                                                 Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, columnNr, rowNr);
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template<typename DataType>
void Matrix<DataType>::ConstNIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 7) ReverseNIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to NIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator+(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ReverseNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator-(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ReverseNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::operator+=(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::operator-=(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::difference_type Matrix<DataType>::ReverseNIterator::operator-(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator==(const Matrix<DataType>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator!=(const Matrix<DataType>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator<(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator<=(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator>(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator>=(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseNIterator::operator*()
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseNIterator::operator->()
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseNIterator::operator[](Matrix<DataType>::ReverseNIterator::difference_type index)
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator(const Matrix<DataType>& matrix,
                                                     Matrix<DataType>::size_type rowNr,
                                                     Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, columnNr, rowNr);
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template<typename DataType>
void Matrix<DataType>::ReverseNIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 8) ConstReverseNIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator+(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ConstReverseNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator-(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR(ConstReverseNIterator, m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseNIterator::operator+=(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseNIterator::operator-=(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator::difference_type Matrix<DataType>::ConstReverseNIterator::operator-(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator==(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUAL(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator!=(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_DIFFERENT(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator<(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator<=(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator>(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator>=(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseNIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstReverseNIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseNIterator::operator[](Matrix<DataType>::ConstReverseNIterator::difference_type index) const
{
    NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ConstReverseNIterator::ConstReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_RowNr{-1}
    , m_ColumnNr{-1}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseNIterator::ConstReverseNIterator(const Matrix<DataType>& matrix,
                                                               Matrix<DataType>::size_type rowNr,
                                                               Matrix<DataType>::size_type columnNr)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixRows{matrix.m_NrOfRows}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, columnNr, rowNr);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseNIterator::_increment()
{
    REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseNIterator::_decrement()
{
    REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 9) DIterator (diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(DIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(DIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator+(Matrix<DataType>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(DIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator-(Matrix<DataType>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(DIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::DIterator::operator+=(Matrix<DataType>::DIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::DIterator::operator-=(Matrix<DataType>::DIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::DIterator::difference_type Matrix<DataType>::DIterator::operator-(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator==(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator!=(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator<(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator<=(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator>(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator>=(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    DITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex - m_DiagonalNr : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex : m_DiagonalNr + m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::DIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::DIterator::operator*()
{
    FORWARD_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType* Matrix<DataType>::DIterator::operator->()
{
    FORWARD_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType& Matrix<DataType>::DIterator::operator[](Matrix<DataType>::DIterator::difference_type index)
{
    FORWARD_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template<typename DataType>
Matrix<DataType>::DIterator::DIterator(const Matrix<DataType>& matrix,
                                       Matrix<DataType>::size_type first,
                                       Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    CONSTRUCT_FORWARD_DITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, matrix.m_NrOfRows, matrix.m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::DIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::DIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 10) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator+(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstDIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator-(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstDIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::operator+=(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::operator-=(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator::difference_type Matrix<DataType>::ConstDIterator::operator-(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator==(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator!=(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator<(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator<=(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator>(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator>=(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    DITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex - m_DiagonalNr : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex : m_DiagonalNr + m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstDIterator::operator*() const
{
    FORWARD_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstDIterator::operator->() const
{
    FORWARD_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstDIterator::operator[](Matrix<DataType>::ConstDIterator::difference_type index) const
{
    FORWARD_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template<typename DataType>
Matrix<DataType>::ConstDIterator::ConstDIterator(const Matrix<DataType>& matrix,
                                                 Matrix<DataType>::size_type first,
                                                 Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    CONSTRUCT_FORWARD_DITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, matrix.m_NrOfRows, matrix.m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ConstDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 11) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator+(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ReverseDIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator-(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ReverseDIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::operator+=(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::operator-=(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::difference_type Matrix<DataType>::ReverseDIterator::operator-(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator==(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator!=(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator<(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator<=(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator>(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator>=(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    DITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNr : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseDIterator::operator*()
{
    REVERSE_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseDIterator::operator->()
{
    REVERSE_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseDIterator::operator[](Matrix<DataType>::ReverseDIterator::difference_type index)
{
    REVERSE_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ReverseDIterator::ReverseDIterator(const Matrix<DataType>& matrix,
                                                     Matrix<DataType>::size_type first,
                                                     Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    CONSTRUCT_REVERSE_DITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, matrix.m_NrOfRows, matrix.m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ReverseDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 12) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator+(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstReverseDIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator-(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstReverseDIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::operator+=(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::operator-=(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator::difference_type Matrix<DataType>::ConstReverseDIterator::operator-(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator==(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator!=(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator<(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator<=(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator>(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator>=(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    DITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNr : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - m_DiagonalIndex - 1 : m_DiagonalSize - 1 - m_DiagonalIndex + m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseDIterator::operator*() const
{
    REVERSE_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstReverseDIterator::operator->() const
{
    REVERSE_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseDIterator::operator[](Matrix<DataType>::ConstReverseDIterator::difference_type index) const
{
    REVERSE_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator(const Matrix<DataType>& matrix,
                                                               Matrix<DataType>::size_type first,
                                                               Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
{
    CONSTRUCT_REVERSE_DITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, matrix.m_NrOfRows, matrix.m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseDIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 13) MIterator (mirrored diagonal iterator, traverses a matrix diagonal from the other side (symetrically to DIterator); diagonal 0 passes through the upper right corner of the matrix)

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(MIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(MIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator+(Matrix<DataType>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(MIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator-(Matrix<DataType>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(MIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::MIterator::operator+=(Matrix<DataType>::MIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::MIterator::operator-=(Matrix<DataType>::MIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::MIterator::difference_type Matrix<DataType>::MIterator::operator-(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator==(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator!=(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator<(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator<=(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator>(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator>=(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    MITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::MIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex - m_DiagonalNr : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::MIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalIndex - 1 : m_NrOfMatrixColumns - m_DiagonalNr - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::MIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::MIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::MIterator::operator*()
{
    FORWARD_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType* Matrix<DataType>::MIterator::operator->()
{
    FORWARD_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType& Matrix<DataType>::MIterator::operator[](Matrix<DataType>::MIterator::difference_type index)
{
    FORWARD_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

template<typename DataType>
Matrix<DataType>::MIterator::MIterator(const Matrix<DataType>& matrix,
                                       Matrix<DataType>::size_type first,
                                       Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_MITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, matrix.m_NrOfRows, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::MIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::MIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 14) ConstMIterator

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator+(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstMIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator-(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstMIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstMIterator::operator+=(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstMIterator::operator-=(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator::difference_type Matrix<DataType>::ConstMIterator::operator-(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator==(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator!=(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator<(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator<=(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator>(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator>=(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    MITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstMIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalIndex - m_DiagonalNr : m_DiagonalIndex;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstMIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalIndex - 1 : m_NrOfMatrixColumns - m_DiagonalNr - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstMIterator::operator*() const
{
    FORWARD_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstMIterator::operator->() const
{
    FORWARD_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstMIterator::operator[](Matrix<DataType>::ConstMIterator::difference_type index) const
{
    FORWARD_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

template<typename DataType>
Matrix<DataType>::ConstMIterator::ConstMIterator(const Matrix<DataType>& matrix,
                                       Matrix<DataType>::size_type first,
                                       Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_FORWARD_MITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, matrix.m_NrOfRows, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ConstMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ConstMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 15) ReverseMIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the MIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator+(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ReverseMIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator-(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ReverseMIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ReverseMIterator::operator+=(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ReverseMIterator::operator-=(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator::difference_type Matrix<DataType>::ReverseMIterator::operator-(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator==(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator!=(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator<(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator<=(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator>(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator>=(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    MITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseMIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNr : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseMIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalSize + m_DiagonalIndex : m_NrOfMatrixColumns - m_DiagonalSize + m_DiagonalIndex - m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ReverseMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseMIterator::operator*()
{
    REVERSE_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseMIterator::operator->()
{
    REVERSE_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseMIterator::operator[](Matrix<DataType>::ReverseMIterator::difference_type index)
{
    REVERSE_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ReverseMIterator::ReverseMIterator(const Matrix<DataType>& matrix,
                                                     Matrix<DataType>::size_type first,
                                                     Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_MITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, matrix.m_NrOfRows, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ReverseMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ReverseMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
}

// 16) ConstReverseMIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator+(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstReverseMIterator, m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator-(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR(ConstReverseMIterator, m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseMIterator::operator+=(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    *this = *this + offset;
}

template<typename DataType>
void Matrix<DataType>::ConstReverseMIterator::operator-=(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    *this = *this - offset;
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator::difference_type Matrix<DataType>::ConstReverseMIterator::operator-(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator==(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, ==, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator!=(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, !=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator<(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator<=(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, <=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator>(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator>=(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPARE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, >=, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::isValidWithMatrix(const Matrix<DataType>& matrix) const
{
    MITERATOR_IS_VALID_WITH_MATRIX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_NrOfMatrixColumns, matrix.m_pBaseArrayPtr, matrix.m_NrOfRows, matrix.m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseMIterator::getRowNr() const
{
    return m_DiagonalNr < 0 ? m_DiagonalSize - 1 - m_DiagonalIndex - m_DiagonalNr : m_DiagonalSize - m_DiagonalIndex - 1;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseMIterator::getColumnNr() const
{
    return m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalSize + m_DiagonalIndex : m_NrOfMatrixColumns - m_DiagonalSize + m_DiagonalIndex - m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::ConstReverseMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseMIterator::operator*() const
{
    REVERSE_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
const DataType* Matrix<DataType>::ConstReverseMIterator::operator->() const
{
    REVERSE_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
const DataType& Matrix<DataType>::ConstReverseMIterator::operator[](Matrix<DataType>::ConstReverseMIterator::difference_type index) const
{
    REVERSE_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

// first and second can be interpreted either as diagonal number and (relative) diagonal index (isRelative is true) or as row/column number ((x, y) coordinates)
template<typename DataType>
Matrix<DataType>::ConstReverseMIterator::ConstReverseMIterator(const Matrix<DataType>& matrix,
                                                     Matrix<DataType>::size_type first,
                                                     Matrix<DataType>::size_type second, bool isRelative)
    : m_pMatrixPtr{matrix.m_pBaseArrayPtr}
    , m_NrOfMatrixColumns{matrix.m_NrOfColumns}
{
    CONSTRUCT_REVERSE_MITERATOR(m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, matrix.m_NrOfRows, first, second, isRelative);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseMIterator::_increment()
{
    DIAG_ITERATOR_DO_INCREMENT(m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
void Matrix<DataType>::ConstReverseMIterator::_decrement()
{
    DIAG_ITERATOR_DO_DECREMENT(m_DiagonalIndex);
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
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRows,
                         Matrix<DataType>::size_type nrOfColumns,
                         std::initializer_list<DataType> dataTypeInitList)
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
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRows,
                         Matrix<DataType>::size_type nrOfColumns, const DataType& dataType)
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
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRowsColumns,
                         const std::pair<DataType, DataType>& diagMatrixValues)
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
DataType& Matrix<DataType>::at(Matrix<DataType>::size_type rowNr,
                               Matrix<DataType>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[rowNr][columnNr];
}

template<typename DataType>
const DataType& Matrix<DataType>::at(Matrix<DataType>::size_type rowNr,
                                     Matrix<DataType>::size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr<0 || columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(rowNr>=m_NrOfRows || columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[rowNr][columnNr];
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](Matrix<DataType>::size_type index)
{
    CHECK_ERROR_CONDITION(index<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(index>=m_NrOfRows*m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[index / m_NrOfColumns][index % m_NrOfColumns];
}

template<typename DataType>
const DataType& Matrix<DataType>::operator[](Matrix<DataType>::size_type index) const
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
DataType* Matrix<DataType>::getBaseArray(Matrix<DataType>::size_type& nrOfElements)
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
void Matrix<DataType>::resize(Matrix<DataType>::size_type nrOfRows,
                              Matrix<DataType>::size_type nrOfColumns,
                              Matrix<DataType>::size_type rowCapacity,
                              Matrix<DataType>::size_type columnCapacity)
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
void Matrix<DataType>::resizeWithValue(Matrix<DataType>::size_type nrOfRows,
                                       Matrix<DataType>::size_type nrOfColumns,
                                       const DataType& value, Matrix<DataType>::size_type rowCapacity,
                                       Matrix<DataType>::size_type columnCapacity)
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
        Matrix<DataType> matrix{std::move(*this)};
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
void Matrix<DataType>::insertRow (Matrix<DataType>::size_type rowNr)
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
void Matrix<DataType>::insertRow(Matrix<DataType>::size_type rowNr,
                                 const DataType &dataType)
{
    insertRow(rowNr);

    for (size_type col{0}; col<m_NrOfColumns; ++col)
    {
        m_pBaseArrayPtr[rowNr][col] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::insertColumn(Matrix<DataType>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr>m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix<DataType> matrix{};
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
void Matrix<DataType>::insertColumn(Matrix<DataType>::size_type columnNr,
                                    const DataType &dataType)
{
    insertColumn(columnNr);

    for (size_type row{0}; row<m_NrOfRows; ++row)
    {
        m_pBaseArrayPtr[row][columnNr] = dataType;
    }
}

template <typename DataType>
void Matrix<DataType>::eraseRow(Matrix<DataType>::size_type rowNr)
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
void Matrix<DataType>::eraseColumn(Matrix<DataType>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr<0, Matr::errorMessages[Matr::Errors::NEGATIVE_ARG]);
    CHECK_ERROR_CONDITION(columnNr>=m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (m_NrOfColumns==1)
    {
        _deallocMemory();
    }
    else if (m_NrOfColumns-1 <= m_ColumnCapacity/4)
    {
        Matrix<DataType> matrix{};
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
void Matrix<DataType>::catByRow(Matrix<DataType>& firstSrcMatrix,
                                Matrix<DataType>& secondSrcMatrix)
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
void Matrix<DataType>::catByColumn(Matrix<DataType>& firstSrcMatrix,
                                   Matrix<DataType>& secondSrcMatrix)
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

    Matrix<DataType> matrix{};

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
void Matrix<DataType>::splitByRow(Matrix<DataType>& firstDestMatrix,
                                  Matrix<DataType>& secondDestMatrix,
                                  Matrix<DataType>::size_type splitRowNr)
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
void Matrix<DataType>::splitByColumn(Matrix<DataType>& firstDestMatrix,
                                     Matrix<DataType>& secondDestMatrix,
                                     Matrix<DataType>::size_type splitColumnNr)
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

        Matrix<DataType> matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for the good practice's sake!
        _allocMemory(c_EachDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns, matrix.m_RowCapacity, matrix.m_ColumnCapacity);

        copyElements(matrix, firstDestMatrix, 0, splitColumnNr, 0, 0);
    }
    else if (&firstDestMatrix != this && (&secondDestMatrix == this))
    {
        firstDestMatrix._adjustSizeAndCapacity(c_EachDestMatrixNrOfRows, c_FirstDestMatrixNrOfColumns);

        copyElements(*this, firstDestMatrix, 0, splitColumnNr, 0, 0);

        Matrix<DataType> matrix{std::move(*this)};
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
void Matrix<DataType>::swapItems(Matrix<DataType>::size_type rowNr,
                                 Matrix<DataType>::size_type columnNr,
                                 Matrix<DataType>& matrix,
                                 Matrix<DataType>::size_type matrixRowNr,
                                 Matrix<DataType>::size_type matrixColumnNr)
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
void Matrix<DataType>::swapRows(Matrix<DataType>::size_type rowNr,
                                Matrix<DataType>& matrix,
                                Matrix<DataType>::size_type matrixRowNr)
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
void Matrix<DataType>::swapColumns(Matrix<DataType>::size_type columnNr,
                                   Matrix<DataType>& matrix,
                                   Matrix<DataType>::size_type matrixColumnNr)
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
void Matrix<DataType>::swapRowColumn(Matrix<DataType>::size_type rowNr,
                                     Matrix<DataType>& matrix,
                                     Matrix<DataType>::size_type matrixColumnNr)
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

template <typename DataType>
void Matrix<DataType>::setAllItemsToValue(const DataType& value)
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
void Matrix<DataType>::copy(const Matrix<DataType>& srcMatrix,
                            Matrix<DataType>::size_type nrOfRows,
                            Matrix<DataType>::size_type nrOfColumns,
                            Matrix<DataType>::size_type srcMatrixRowNr,
                            Matrix<DataType>::size_type srcMatrixColumnNr,
                            Matrix<DataType>::size_type rowNr,
                            Matrix<DataType>::size_type columnNr)
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
bool Matrix<DataType>::operator!=(const Matrix<DataType>& matrix) const
{
    return !_isEqualTo(matrix);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ZIterator);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zEnd()
{
    GET_FORWARD_END_ZITERATOR(ZIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowBegin(Matrix<DataType>::size_type rowNr)
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ZIterator, m_NrOfRows, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowEnd(Matrix<DataType>::size_type rowNr)
{
    GET_FORWARD_ROW_END_ZITERATOR(ZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(Matrix<DataType>::size_type rowNr,
                                                                    Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ZIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ZIterator, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstZIterator);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZEnd() const
{
    GET_FORWARD_END_ZITERATOR(ConstZIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowBegin(Matrix<DataType>::size_type rowNr) const
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ConstZIterator, m_NrOfRows, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowEnd(Matrix<DataType>::size_type rowNr) const
{
    GET_FORWARD_ROW_END_ZITERATOR(ConstZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(Matrix<DataType>::size_type rowNr,
                                                                              Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ConstZIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstZIterator, m_NrOfRows, m_NrOfColumns, /, %, index);
}


template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseZIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZEnd()
{
    GET_REVERSE_END_ZITERATOR(ReverseZIterator);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowBegin(Matrix<DataType>::size_type rowNr)
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowEnd(Matrix<DataType>::size_type rowNr)
{
    GET_REVERSE_ROW_END_ZITERATOR(ReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(Matrix<DataType>::size_type rowNr,
                                                                                  Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ReverseZIterator, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseZIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZEnd() const
{
    GET_REVERSE_END_ZITERATOR(ConstReverseZIterator);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowBegin(Matrix<DataType>::size_type rowNr) const
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ConstReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowEnd(Matrix<DataType>::size_type rowNr) const
{
    GET_REVERSE_ROW_END_ZITERATOR(ConstReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(Matrix<DataType>::size_type rowNr,
                                                                                            Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseZIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstReverseZIterator, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(NIterator);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nEnd()
{
    GET_FORWARD_END_NITERATOR(NIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnBegin(Matrix<DataType>::size_type columnNr)
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(NIterator, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnEnd(Matrix<DataType>::size_type columnNr)
{
    GET_FORWARD_COLUMN_END_NITERATOR(NIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(Matrix<DataType>::size_type rowNr,
                                                                    Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(NIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(NIterator, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstNIterator);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNEnd() const
{
    GET_FORWARD_END_NITERATOR(ConstNIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnBegin(Matrix<DataType>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(ConstNIterator, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnEnd(Matrix<DataType>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_END_NITERATOR(ConstNIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(Matrix<DataType>::size_type rowNr,
                                                                              Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ConstNIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstNIterator, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseNIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNEnd()
{
    GET_REVERSE_END_NITERATOR(ReverseNIterator);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnBegin(Matrix<DataType>::size_type columnNr)
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ReverseNIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnEnd(Matrix<DataType>::size_type columnNr)
{
    GET_REVERSE_COLUMN_END_NITERATOR(ReverseNIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(Matrix<DataType>::size_type rowNr,
                                                                                  Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ReverseNIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ReverseNIterator, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseNIterator, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNEnd() const
{
    GET_REVERSE_END_NITERATOR(ConstReverseNIterator);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNColumnBegin(Matrix<DataType>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ConstReverseNIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNColumnEnd(Matrix<DataType>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_END_NITERATOR(ConstReverseNIterator, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::getConstReverseNIterator(Matrix<DataType>::size_type rowNr,
                                                                                            Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseNIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::getConstReverseNIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstReverseNIterator, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(DIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(Matrix<DataType>::size_type rowNr,
                                                              Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER(DIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(DIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(Matrix<DataType>::size_type rowNr,
                                                            Matrix<DataType>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER(DIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::getDIterator(Matrix<DataType>::size_type first,
                                                                    Matrix<DataType>::size_type second,
                                                                    bool isRelative)
{
    GET_RANDOM_DITERATOR(DIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(Matrix<DataType>::size_type diagNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(Matrix<DataType>::size_type rowNr,
                                                                        Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER(ConstDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(Matrix<DataType>::size_type diagNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(Matrix<DataType>::size_type rowNr,
                                                                      Matrix<DataType>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER(ConstDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::getConstDIterator(Matrix<DataType>::size_type first,
                                                                              Matrix<DataType>::size_type second,
                                                                              bool isRelative) const
{
    GET_RANDOM_DITERATOR(ConstDIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(Matrix<DataType>::size_type rowNr,
                                                                            Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER(ReverseDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ReverseDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(Matrix<DataType>::size_type rowNr,
                                                                          Matrix<DataType>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER(ReverseDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::getReverseDIterator(Matrix<DataType>::size_type first,
                                                                                  Matrix<DataType>::size_type second,
                                                                                  bool isRelative)
{
    GET_RANDOM_DITERATOR(ReverseDIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(Matrix<DataType>::size_type diagNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(Matrix<DataType>::size_type rowNr,
                                                                                      Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(Matrix<DataType>::size_type diagNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstReverseDIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(Matrix<DataType>::size_type rowNr,
                                                                                    Matrix<DataType>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseDIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::getConstReverseDIterator(Matrix<DataType>::size_type first,
                                                                                            Matrix<DataType>::size_type second,
                                                                                            bool isRelative) const
{
    GET_RANDOM_DITERATOR(ConstReverseDIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(MIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mBegin(Matrix<DataType>::size_type rowNr,
                                                              Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER(MIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(MIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mEnd(Matrix<DataType>::size_type rowNr,
                                                            Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER(MIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::getMIterator(Matrix<DataType>::size_type first,
                                                                    Matrix<DataType>::size_type second,
                                                                    bool isRelative)
{
    GET_RANDOM_MITERATOR(MIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(ConstMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMBegin(Matrix<DataType>::size_type rowNr,
                                                              Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER(ConstMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMEnd(Matrix<DataType>::size_type rowNr,
                                                            Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER(ConstMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::getConstMIterator(Matrix<DataType>::size_type first,
                                                                    Matrix<DataType>::size_type second,
                                                                    bool isRelative)
{
    GET_RANDOM_MITERATOR(ConstMIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMBegin(Matrix<DataType>::size_type rowNr,
                                                                            Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER(ReverseMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ReverseMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMEnd(Matrix<DataType>::size_type rowNr,
                                                                          Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER(ReverseMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::getReverseMIterator(Matrix<DataType>::size_type first,
                                                                                  Matrix<DataType>::size_type second,
                                                                                  bool isRelative)
{
    GET_RANDOM_MITERATOR(ReverseMIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMBegin(Matrix<DataType>::size_type diagNr)
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMBegin(Matrix<DataType>::size_type rowNr,
                                                                            Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMEnd(Matrix<DataType>::size_type diagNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstReverseMIterator, m_NrOfRows, m_NrOfColumns, diagNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMEnd(Matrix<DataType>::size_type rowNr,
                                                                          Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER(ConstReverseMIterator, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::getConstReverseMIterator(Matrix<DataType>::size_type first,
                                                                                  Matrix<DataType>::size_type second,
                                                                                  bool isRelative)
{
    GET_RANDOM_MITERATOR(ConstReverseMIterator, m_NrOfRows, m_NrOfColumns, first, second, isRelative);
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
void Matrix<DataType>::_allocMemory(Matrix<DataType>::size_type nrOfRows,
                                    Matrix<DataType>::size_type nrOfColumns,
                                    Matrix<DataType>::size_type rowCapacity,
                                    Matrix<DataType>::size_type columnCapacity)
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
void Matrix<DataType>::_adjustSizeAndCapacity(Matrix<DataType>::size_type nrOfRows,
                                              Matrix<DataType>::size_type nrOfColumns)
{
    const size_type c_NewRowCapacity{nrOfRows + nrOfRows/4};
    const size_type c_NewColumnCapacity{nrOfColumns + nrOfColumns/4};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};

    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns, c_OldRowCapacity < nrOfRows ? c_NewRowCapacity : c_OldRowCapacity, c_OldColumnCapacity < nrOfColumns ? c_NewColumnCapacity : c_OldColumnCapacity);
}

#undef CHECK_ERROR_CONDITION

#undef COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_NON_DIAG_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS

#undef ITERATOR_PRE_INCREMENT
#undef ITERATOR_POST_INCREMENT
#undef ITERATOR_PRE_DECREMENT
#undef ITERATOR_POST_DECREMENT
#undef CONSTRUCT_FORWARD_NON_DIAG_ITERATOR
#undef CONSTRUCT_REVERSE_NON_DIAG_ITERATOR
#undef FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR
#undef REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR
#undef FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY
#undef REVERSE_NON_DIAG_ITERATOR_CHECK_STRICT_INEQUALITY
#undef FORWARD_NON_DIAG_ITERATOR_CHECK_INEQUALITY
#undef REVERSE_NON_DIAG_ITERATOR_CHECK_INEQUALITY
#undef NON_DIAG_ITERATOR_CHECK_EQUAL
#undef NON_DIAG_ITERATOR_CHECK_DIFFERENT
#undef FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE
#undef NON_DIAG_ITERATOR_INDEX_DEREFERENCE
#undef NON_DIAG_ITERATOR_IS_VALID_WITH_MATRIX
#undef FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT
#undef REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT
#undef FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT
#undef REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT
#undef GET_FORWARD_NON_DIAG_BEGIN_ITERATOR
#undef GET_REVERSE_NON_DIAG_BEGIN_ITERATOR
#undef GET_NON_DIAG_ITERATOR_BY_ROW_COLUMN_NUMBER
#undef GET_NON_DIAG_ITERATOR_BY_INDEX
#undef DIAG_ITERATOR_ADD_SCALAR
#undef DIAG_ITERATOR_DO_INCREMENT
#undef DIAG_ITERATOR_DO_DECREMENT
#undef DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef DIAG_ITERATOR_COMPARE
#undef GET_DIAG_BEGIN_ITERATOR
#undef GET_FORWARD_END_ZITERATOR
#undef GET_REVERSE_END_ZITERATOR
#undef GET_FORWARD_ROW_BEGIN_ZITERATOR
#undef GET_REVERSE_ROW_BEGIN_ZITERATOR
#undef GET_FORWARD_ROW_END_ZITERATOR
#undef GET_REVERSE_ROW_END_ZITERATOR
#undef GET_FORWARD_END_NITERATOR
#undef GET_REVERSE_END_NITERATOR
#undef GET_FORWARD_COLUMN_BEGIN_NITERATOR
#undef GET_REVERSE_COLUMN_BEGIN_NITERATOR
#undef GET_FORWARD_COLUMN_END_NITERATOR
#undef GET_REVERSE_COLUMN_END_NITERATOR
#undef CONSTRUCT_FORWARD_DITERATOR
#undef CONSTRUCT_REVERSE_DITERATOR
#undef DITERATOR_IS_VALID_WITH_MATRIX
#undef FORWARD_DITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_DITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_DITERATOR_ARROW_DEREFERENCE
#undef REVERSE_DITERATOR_ARROW_DEREFERENCE
#undef FORWARD_DITERATOR_INDEX_DEREFERENCE
#undef REVERSE_DITERATOR_INDEX_DEREFERENCE
#undef GET_BEGIN_DITERATOR_BY_ROW_COLUMN_NUMBER
#undef GET_END_DITERATOR_BY_DIAG_NUMBER
#undef GET_END_DITERATOR_BY_ROW_COLUMN_NUMBER
#undef GET_RANDOM_DITERATOR
#undef CONSTRUCT_FORWARD_MITERATOR
#undef CONSTRUCT_REVERSE_MITERATOR
#undef MITERATOR_IS_VALID_WITH_MATRIX
#undef FORWARD_MITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_MITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_MITERATOR_ARROW_DEREFERENCE
#undef REVERSE_MITERATOR_ARROW_DEREFERENCE
#undef FORWARD_MITERATOR_INDEX_DEREFERENCE
#undef REVERSE_MITERATOR_INDEX_DEREFERENCE
#undef GET_BEGIN_MITERATOR_BY_ROW_COLUMN_NUMBER
#undef GET_END_MITERATOR_BY_DIAG_NUMBER
#undef GET_END_MITERATOR_BY_ROW_COLUMN_NUMBER
#undef GET_RANDOM_MITERATOR

#endif // MATRIX_H
