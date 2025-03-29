#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <utility>
#include <memory>
#include <algorithm>
#include <optional>

#include "../Utils/iteratorutils.h"
#include "../Utils/errorhandling.h"

template <typename DataType>
class Matrix
{
public:
    using size_type = uint32_t;
    using diff_type = int32_t;

    class ZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ZIterator, DataType, size_type)
    };

    class ConstZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstZIterator(const ZIterator& zIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstZIterator, DataType, size_type)
    };

    class ReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, DataType, size_type)
    };

    class ConstReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstReverseZIterator(const ReverseZIterator& reverseZIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, DataType, size_type)
    };

    class NIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(NIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(NIterator, DataType, size_type)
    };

    class ConstNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstNIterator(const NIterator& nIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstNIterator, DataType, size_type)
    };

    class ReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, DataType, size_type)
    };

    class ConstReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstReverseNIterator(const ReverseNIterator& reverseNIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, DataType, size_type)
    };

    class DIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(DIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(DIterator, DataType, diff_type, size_type)

    };

    class ConstDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstDIterator(const DIterator& dIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstDIterator, DataType, diff_type, size_type)
    };

    class ReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, DataType, diff_type, size_type)
    };

    class ConstReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstReverseDIterator(const ReverseDIterator& reverseDIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, DataType, diff_type, size_type)
    };

    class MIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(MIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(MIterator, DataType, diff_type, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstMIterator(const MIterator& mIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstMIterator, DataType, diff_type, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, DataType, diff_type, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, DataType, diff_type, size_type)
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type)
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(DataType, diff_type)

        ConstReverseMIterator(const ReverseMIterator& reverseMIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(DataType)
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, DataType, diff_type, size_type)

        size_type m_NrOfMatrixColumns;      // number of matrix columns is required for mirrored iterators because the origin (diagonal 0) does no longer pass through element (0, 0)
    };

    Matrix();
    Matrix(size_type nrOfRows, size_type nrOfColumns, std::initializer_list<DataType> dataTypeInitList);
    Matrix(size_type nrOfRows, size_type nrOfColumns, const DataType& value);
    Matrix(size_type nrOfRowsColumns, const std::pair<DataType, DataType>& diagMatrixValues);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();

    DataType& at(size_type rowNr, size_type columnNr);
    const DataType& at(size_type rowNr, size_type columnNr) const;

    DataType& operator[] (size_type index);
    const DataType& operator[](size_type index) const;

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating the data properly)
    void* getBaseArray(size_type& nrOfElements);
	
    size_type getNrOfRows() const;
    size_type getNrOfColumns() const;
    size_type getRowCapacity() const;
    size_type getColumnCapacity() const;
#ifdef USE_CAPACITY_OFFSET
    std::optional<size_type> getRowCapacityOffset() const;
    std::optional<size_type> getColumnCapacityOffset() const;
#endif
    bool isEmpty() const;

    void transpose(Matrix& transposedMatrix);

    void clear();

    // resize and don't init new elements (user has the responsibility to init them), existing elements retain their old values
    void resize(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0, size_type columnCapacity = 0);

    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resizeWithValue(size_type nrOfRows, size_type nrOfColumns, const DataType& dataType, size_type rowCapacity = 0, size_type columnCapacity = 0);

    void shrinkToFit();

    void insertRow(size_type rowNr);
    void insertRow(size_type rowNr, const DataType& value);
    void insertColumn(size_type columnNr);
    void insertColumn(size_type columnNr, const DataType& value);
    void eraseRow(size_type rowNr);
    void eraseColumn(size_type columnNr);

    // vertical concatenation (cumulated rows)
    void catByRow(Matrix& firstMatrix, Matrix& secondMatrix);

    // horizontal concatenation (cumulated columns)
    void catByColumn(Matrix& firstMatrix, Matrix& secondMatrix);

    // vertical splitting
    void splitByRow(Matrix& firstMatrix, Matrix& secondMatrix, size_type splitRowNr);

    // horizontal splitting
    void splitByColumn(Matrix& firstMatrix, Matrix& secondMatrix, size_type splitColumnNr);

    void swapRows(size_type firstRowNr, size_type secondRowNr);
    void swapColumns(size_type firstColumnNr, size_type secondColumnNr);

    // the template type should have operator == implemented, otherwise a template specialization is required
    bool operator== (const Matrix& matrix) const;

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

    DIterator dBegin(diff_type diagonalNr);
    DIterator dBegin(size_type rowNr, size_type columnNr);
    DIterator dEnd(diff_type diagonalNr);
    DIterator dEnd(size_type rowNr, size_type columnNr);
    DIterator getDIterator(size_type rowNr, size_type columnNr);
    DIterator getDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);

    ConstDIterator constDBegin(diff_type diagonalNr) const;
    ConstDIterator constDBegin(size_type rowNr, size_type columnNr) const;
    ConstDIterator constDEnd(diff_type diagonalNr) const;
    ConstDIterator constDEnd(size_type rowNr, size_type columnNr) const;
    ConstDIterator getConstDIterator(size_type rowNr, size_type columnNr) const;
    ConstDIterator getConstDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    ReverseDIterator reverseDBegin(diff_type diagonalNr);
    ReverseDIterator reverseDBegin(size_type rowNr, size_type columnNr);
    ReverseDIterator reverseDEnd(diff_type diagonalNr);
    ReverseDIterator reverseDEnd(size_type rowNr, size_type columnNr);
    ReverseDIterator getReverseDIterator(size_type rowNr, size_type columnNr);
    ReverseDIterator getReverseDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);

    ConstReverseDIterator constReverseDBegin(diff_type diagonalNr) const;
    ConstReverseDIterator constReverseDBegin(size_type rowNr, size_type columnNr) const;
    ConstReverseDIterator constReverseDEnd(diff_type diagonalNr) const;
    ConstReverseDIterator constReverseDEnd(size_type rowNr, size_type columnNr) const;
    ConstReverseDIterator getConstReverseDIterator(size_type rowNr, size_type columnNr) const;
    ConstReverseDIterator getConstReverseDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    MIterator mBegin(diff_type diagonalNr);
    MIterator mBegin(size_type rowNr, size_type columnNr);
    MIterator mEnd(diff_type diagonalNr);
    MIterator mEnd(size_type rowNr, size_type columnNr);
    MIterator getMIterator(size_type rowNr, size_type columnNr);
    MIterator getMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);

    ConstMIterator constMBegin(diff_type diagonalNr) const;
    ConstMIterator constMBegin(size_type rowNr, size_type columnNr) const;
    ConstMIterator constMEnd(diff_type diagonalNr) const;
    ConstMIterator constMEnd(size_type rowNr, size_type columnNr) const;
    ConstMIterator getConstMIterator(size_type rowNr, size_type columnNr) const;
    ConstMIterator getConstMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    ReverseMIterator reverseMBegin(diff_type diagonalNr);
    ReverseMIterator reverseMBegin(size_type rowNr, size_type columnNr);
    ReverseMIterator reverseMEnd(diff_type diagonaNr);
    ReverseMIterator reverseMEnd(size_type rowNr, size_type columnNr);
    ReverseMIterator getReverseMIterator(size_type rowNr, size_type columnNr);
    ReverseMIterator getReverseMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);

    ConstReverseMIterator constReverseMBegin(diff_type diagonaNr) const;
    ConstReverseMIterator constReverseMBegin(size_type rowNr, size_type columnNr) const;
    ConstReverseMIterator constReverseMEnd(diff_type diagonalNr) const;
    ConstReverseMIterator constReverseMEnd(size_type rowNr, size_type columnNr) const;
    ConstReverseMIterator getConstReverseMIterator(size_type rowNr, size_type columnNr) const;
    ConstReverseMIterator getConstReverseMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    // required for being able to use the (const) auto (&) syntax for iterating through the matrix elements
    ZIterator begin();
    ZIterator end();
    ConstZIterator begin() const;
    ConstZIterator end() const;

private:
    // resize matrix, returns number of preserved elements (rows * columns), new elements should be initialized by caller
    std::pair<size_type, size_type> _resizeWithUninitializedNewElements(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity, size_type columnCapacity);

    // inserts the uninitialized row into the required position, initialialization is left to the caller
    void _insertUninitializedRow(size_type rowNr);

    // inserts the uninitialized column either into the required position or into the last position (depending on available column capacity)
    size_type _insertUninitializedColumn(size_type columnNr);

    // erases the row or column (depending on isRow) by reallocating memory and putting back all elements except the row/column (dimension element) to be removed
    void _reallocEraseDimensionElement(size_type dimensionElementNr, bool isRow);

    // erases the row without changing matrix capacity (shift bottom rows to top)
    void _shiftEraseRow(size_type rowNr);

    // erases the column without changing matrix capacity (shift right columns to left)
    void _shiftEraseColumn(size_type columnNr);

    // places the first column into the new position by performing a rotation
    void _rotateFirstColumn(size_type newColumnNr);

    // places the last column into the new position by performing a rotation
    void _rotateLastColumn(size_type newColumnNr);

    // normalize row capacity to have equal top/bottom unused capacity
    void _normalizeRowCapacity();

    // ensure the currently allocated memory is first released (_deallocMemory()) prior to using this function
    void _allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0, size_type columnCapacity = 0);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    // resize the matrix (no elements initialization) by ensuring the new row/column capacity is not lower than the new number of rows/columns
    void _adjustSizeAndCapacity(size_type nrOfRows, size_type nrOfColumns);

    // used for matrix-to-matrix copy construction and assignment
    void _copyAllItemsFromMatrix(const Matrix& matrix);

    // used for the matrix-to-matrix move construction and assignment
    void _moveAllItemsFromMatrix(Matrix& matrix);

    // initialize all or part of the elements by copying from source matrix
    void _copyInitItems(const Matrix& matrix, size_type matrixStartingRowNr, size_type matrixColumnOffset, size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // initialize all or part of the elements by moving from source matrix
    void _moveInitItems(Matrix& matrix, size_type matrixStartingRowNr, size_type matrixColumnOffset, size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // initialize all or part of the elements by filling in the same value
    void _fillInitItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns, const DataType& value);

    // initialize all or part of the elements with default constructor
    void _defaultConstructInitItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // destroy the elements contained within interval
    void _destroyItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // ensures the selected sub-matrix (elements to change) fits into matrix
    void _clampSubMatrixSelectionParameters(size_type& startingRowNr, size_type& columnOffset, size_type& nrOfRows, size_type& nrOfColumns);

    // similar to previous but this time clamping is done by also taking the parameters of a source matrix into account
    void _externalClampSubMatrixSelectionParameters(const Matrix& srcMatrix, size_type& srcStartingRowNr, size_type& srcColumnOffset, size_type& startingRowNr, size_type& columnOffset, size_type& nrOfRows, size_type& nrOfColumns);

    // converts the matrix to a single dimensional array of elements of m_RowCapacity * m_ColumnCapacity size (might include uninitialized elements)
    void* _convertToArray(size_type& nrOfElements);

    DataType* m_pAllocPtr; // use only this pointer in _allocMemory()/_deallocMemory() to allocate/de-allocate matrix elements
    DataType** m_pBaseArrayPtr; // this pointer manages the row pointers array

    size_type m_NrOfRows;
    size_type m_NrOfColumns;
    size_type m_RowCapacity;
    size_type m_ColumnCapacity;
    std::optional<size_type> m_RowCapacityOffset;
    std::optional<size_type> m_ColumnCapacityOffset;
};

// 1) ZIterator - iterates within matrix from [0][0] to the end row by row
template<typename DataType>
typename Matrix<DataType>::ZIterator& Matrix<DataType>::ZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator& Matrix<DataType>::ZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::ZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator& Matrix<DataType>::ZIterator::operator+=(Matrix<DataType>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator& Matrix<DataType>::ZIterator::operator-=(Matrix<DataType>::ZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator::difference_type Matrix<DataType>::ZIterator::operator-(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ZIterator::operator<=>(const Matrix<DataType>::ZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::operator==(const Matrix<DataType>::ZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ZIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ZIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ZIterator::operator[](Matrix<DataType>::ZIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ZIterator::ZIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       std::optional<Matrix<DataType>::size_type> rowNr,
                                       std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_increment()
{
    FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
void Matrix<DataType>::ZIterator::_decrement()
{
    FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

template<typename DataType>
bool Matrix<DataType>::ZIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 2) ConstZIterator

template<typename DataType>
typename Matrix<DataType>::ConstZIterator& Matrix<DataType>::ConstZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator& Matrix<DataType>::ConstZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::ConstZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator& Matrix<DataType>::ConstZIterator::operator+=(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator& Matrix<DataType>::ConstZIterator::operator-=(Matrix<DataType>::ConstZIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator::difference_type Matrix<DataType>::ConstZIterator::operator-(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstZIterator::operator<=>(const Matrix<DataType>::ConstZIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::operator==(const Matrix<DataType>::ConstZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstZIterator::getColumnNr() const
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
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator(const ZIterator& zIterator)
    : m_pMatrixPtr{zIterator.m_pMatrixPtr}
    , m_RowNr{zIterator.m_RowNr}
    , m_ColumnNr{zIterator.m_ColumnNr}
    , m_NrOfMatrixRows{zIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{zIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstZIterator::ConstZIterator(DataType** pMatrixPtr,
                                                 Matrix<DataType>::size_type nrOfMatrixRows,
                                                 Matrix<DataType>::size_type nrOfMatrixColumns,
                                                 std::optional<Matrix<DataType>::size_type> rowNr,
                                                 std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
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

template<typename DataType>
bool Matrix<DataType>::ConstZIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 3) ReverseZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to ZIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator& Matrix<DataType>::ReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator& Matrix<DataType>::ReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::ReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator& Matrix<DataType>::ReverseZIterator::operator+=(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator& Matrix<DataType>::ReverseZIterator::operator-=(Matrix<DataType>::ReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator::difference_type Matrix<DataType>::ReverseZIterator::operator-(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ReverseZIterator::operator<=>(const Matrix<DataType>::ReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::operator==(const Matrix<DataType>::ReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseZIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseZIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseZIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, m_ColumnNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseZIterator::operator[](Matrix<DataType>::ReverseZIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseZIterator::ReverseZIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     std::optional<Matrix<DataType>::size_type> rowNr,
                                                     std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
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

template<typename DataType>
bool Matrix<DataType>::ReverseZIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 4) ConstReverseZIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator& Matrix<DataType>::ConstReverseZIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator& Matrix<DataType>::ConstReverseZIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::ConstReverseZIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseZIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator& Matrix<DataType>::ConstReverseZIterator::operator+=(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator& Matrix<DataType>::ConstReverseZIterator::operator-=(Matrix<DataType>::ConstReverseZIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator::difference_type Matrix<DataType>::ConstReverseZIterator::operator-(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstReverseZIterator::operator<=>(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::operator==(const Matrix<DataType>::ConstReverseZIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseZIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseZIterator::getColumnNr() const
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
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, /, %, index);
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator(const ReverseZIterator& reverseZIterator)
    : m_pMatrixPtr{reverseZIterator.m_pMatrixPtr}
    , m_RowNr{reverseZIterator.m_RowNr}
    , m_ColumnNr{reverseZIterator.m_ColumnNr}
    , m_NrOfMatrixRows{reverseZIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{reverseZIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseZIterator::ConstReverseZIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               std::optional<Matrix<DataType>::size_type> rowNr,
                                                               std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
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

template<typename DataType>
bool Matrix<DataType>::ConstReverseZIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr);
}

// 5) NIterator - iterates within matrix from [0][0] to the end column by column
template<typename DataType>
typename Matrix<DataType>::NIterator& Matrix<DataType>::NIterator::operator++()
{
    ITERATOR_PRE_INCREMENT()
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(NIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::NIterator& Matrix<DataType>::NIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::NIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(NIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::NIterator& Matrix<DataType>::NIterator::operator+=(Matrix<DataType>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::NIterator& Matrix<DataType>::NIterator::operator-=(Matrix<DataType>::NIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::NIterator::difference_type Matrix<DataType>::NIterator::operator-(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
auto Matrix<DataType>::NIterator::operator<=>(const Matrix<DataType>::NIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::NIterator::operator==(const Matrix<DataType>::NIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::NIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::NIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::NIterator::operator*() const
{
    FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType* Matrix<DataType>::NIterator::operator->() const
{
    FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType& Matrix<DataType>::NIterator::operator[](Matrix<DataType>::NIterator::difference_type index) const
{
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, %, /, index);
}

template<typename DataType>
Matrix<DataType>::NIterator::NIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::NIterator::NIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       std::optional<Matrix<DataType>::size_type> rowNr,
                                       std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
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

template<typename DataType>
bool Matrix<DataType>::NIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 6) ConstNIterator
template<typename DataType>
typename Matrix<DataType>::ConstNIterator& Matrix<DataType>::ConstNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator& Matrix<DataType>::ConstNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::ConstNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator& Matrix<DataType>::ConstNIterator::operator+=(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator& Matrix<DataType>::ConstNIterator::operator-=(Matrix<DataType>::ConstNIterator::difference_type offset)
{
    FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator::difference_type Matrix<DataType>::ConstNIterator::operator-(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstNIterator::operator<=>(const Matrix<DataType>::ConstNIterator& it) const
{
    FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::operator==(const Matrix<DataType>::ConstNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstNIterator::getColumnNr() const
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
    FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator(const NIterator& nIterator)
    : m_pMatrixPtr{nIterator.m_pMatrixPtr}
    , m_RowNr{nIterator.m_RowNr}
    , m_ColumnNr{nIterator.m_ColumnNr}
    , m_NrOfMatrixRows{nIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{nIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstNIterator::ConstNIterator(DataType** pMatrixPtr,
                                                 Matrix<DataType>::size_type nrOfMatrixRows,
                                                 Matrix<DataType>::size_type nrOfMatrixColumns,
                                                 std::optional<Matrix<DataType>::size_type> rowNr,
                                                 std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
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

template<typename DataType>
bool Matrix<DataType>::ConstNIterator::_isEmpty() const
{
    CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr);
}

// 7) ReverseNIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to NIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator& Matrix<DataType>::ReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator& Matrix<DataType>::ReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::ReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator& Matrix<DataType>::ReverseNIterator::operator+=(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator& Matrix<DataType>::ReverseNIterator::operator-=(Matrix<DataType>::ReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator::difference_type Matrix<DataType>::ReverseNIterator::operator-(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ReverseNIterator::operator<=>(const Matrix<DataType>::ReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::operator==(const Matrix<DataType>::ReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseNIterator::getColumnNr() const
{
    return m_ColumnNr;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseNIterator::operator*() const
{
    REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseNIterator::operator->() const
{
    REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixRows, m_RowNr, m_ColumnNr, m_RowNr);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseNIterator::operator[](Matrix<DataType>::ReverseNIterator::difference_type index) const
{
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseNIterator::ReverseNIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     std::optional<Matrix<DataType>::size_type> rowNr,
                                                     std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
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

template<typename DataType>
bool Matrix<DataType>::ReverseNIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_ColumnNr, m_RowNr);
}

// 8) ConstReverseNIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator& Matrix<DataType>::ConstReverseNIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator& Matrix<DataType>::ConstReverseNIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::ConstReverseNIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseNIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator& Matrix<DataType>::ConstReverseNIterator::operator+=(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator& Matrix<DataType>::ConstReverseNIterator::operator-=(Matrix<DataType>::ConstReverseNIterator::difference_type offset)
{
    REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator::difference_type Matrix<DataType>::ConstReverseNIterator::operator-(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstReverseNIterator::operator<=>(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, *this, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::operator==(const Matrix<DataType>::ConstReverseNIterator& it) const
{
    NON_DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_RowNr, m_ColumnNr, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseNIterator::getRowNr() const
{
    return m_RowNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseNIterator::getColumnNr() const
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
    REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, %, /, index);
}

template<typename DataType>
Matrix<DataType>::ConstReverseNIterator::ConstReverseNIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseNIterator::ConstReverseNIterator(const ReverseNIterator& reverseNIterator)
    : m_pMatrixPtr{reverseNIterator.m_pMatrixPtr}
    , m_RowNr{reverseNIterator.m_RowNr}
    , m_ColumnNr{reverseNIterator.m_ColumnNr}
    , m_NrOfMatrixRows{reverseNIterator.m_NrOfMatrixRows}
    , m_NrOfMatrixColumns{reverseNIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseNIterator::ConstReverseNIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               std::optional<Matrix<DataType>::size_type> rowNr,
                                                               std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(m_pMatrixPtr, m_NrOfMatrixColumns, m_NrOfMatrixRows, m_ColumnNr, m_RowNr, pMatrixPtr, nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr);
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

template<typename DataType>
bool Matrix<DataType>::ConstReverseNIterator::_isEmpty() const
{
    CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(m_pMatrixPtr, m_NrOfMatrixRows, m_NrOfMatrixColumns, m_ColumnNr, m_RowNr);
}

// 9) DIterator (diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::DIterator& Matrix<DataType>::DIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(DIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::DIterator& Matrix<DataType>::DIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::DIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(DIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::DIterator& Matrix<DataType>::DIterator::operator+=(Matrix<DataType>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::DIterator& Matrix<DataType>::DIterator::operator-=(Matrix<DataType>::DIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::DIterator::difference_type Matrix<DataType>::DIterator::operator-(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::DIterator::operator<=>(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::DIterator::operator==(const Matrix<DataType>::DIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::DIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::DIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex : *m_DiagonalIndex + m_DiagonalNr};
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::DIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::DIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::DIterator::operator*() const
{
    FORWARD_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType* Matrix<DataType>::DIterator::operator->() const
{
    FORWARD_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType& Matrix<DataType>::DIterator::operator[](Matrix<DataType>::DIterator::difference_type index) const
{
    FORWARD_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template<typename DataType>
Matrix<DataType>::DIterator::DIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template<typename DataType>
Matrix<DataType>::DIterator::DIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       std::optional<Matrix<DataType>::size_type> rowNr,
                                       std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::DIterator::DIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::DIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 10) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template<typename DataType>
typename Matrix<DataType>::ConstDIterator& Matrix<DataType>::ConstDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator& Matrix<DataType>::ConstDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::ConstDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator& Matrix<DataType>::ConstDIterator::operator+=(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator& Matrix<DataType>::ConstDIterator::operator-=(Matrix<DataType>::ConstDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator::difference_type Matrix<DataType>::ConstDIterator::operator-(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstDIterator::operator<=>(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::operator==(const Matrix<DataType>::ConstDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex : *m_DiagonalIndex + m_DiagonalNr};
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ConstDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstDIterator::getDiagonalIndex() const
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
Matrix<DataType>::ConstDIterator::ConstDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstDIterator::ConstDIterator(const DIterator& dIterator)
    : m_pMatrixPtr{dIterator.m_pMatrixPtr}
    , m_DiagonalIndex{dIterator.m_DiagonalIndex}
    , m_DiagonalNr{dIterator.m_DiagonalNr}
    , m_DiagonalSize{dIterator.m_DiagonalSize}
{
}

template<typename DataType>
Matrix<DataType>::ConstDIterator::ConstDIterator(DataType** pMatrixPtr,
                                                 Matrix<DataType>::size_type nrOfMatrixRows,
                                                 Matrix<DataType>::size_type nrOfMatrixColumns,
                                                 std::optional<Matrix<DataType>::size_type> rowNr,
                                                 std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ConstDIterator::ConstDIterator(DataType** pMatrixPtr,
                                                 Matrix<DataType>::size_type nrOfMatrixRows,
                                                 Matrix<DataType>::size_type nrOfMatrixColumns,
                                                 const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ConstDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 11) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator& Matrix<DataType>::ReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator& Matrix<DataType>::ReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::ReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator& Matrix<DataType>::ReverseDIterator::operator+=(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator& Matrix<DataType>::ReverseDIterator::operator-=(Matrix<DataType>::ReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator::difference_type Matrix<DataType>::ReverseDIterator::operator-(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ReverseDIterator::operator<=>(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::operator==(const Matrix<DataType>::ReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr < 0 ? std::optional{m_DiagonalSize + std::abs(m_DiagonalNr) - 1 - *m_DiagonalIndex}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr > 0 ? std::optional{m_DiagonalSize + m_DiagonalNr - 1 - *m_DiagonalIndex}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseDIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseDIterator::operator*() const
{
    REVERSE_DITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseDIterator::operator->() const
{
    REVERSE_DITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseDIterator::operator[](Matrix<DataType>::ReverseDIterator::difference_type index) const
{
    REVERSE_DITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, index);
}

template<typename DataType>
Matrix<DataType>::ReverseDIterator::ReverseDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseDIterator::ReverseDIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     std::optional<Matrix<DataType>::size_type> rowNr,
                                                     std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ReverseDIterator::ReverseDIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ReverseDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 12) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator& Matrix<DataType>::ConstReverseDIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator& Matrix<DataType>::ConstReverseDIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::ConstReverseDIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseDIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator& Matrix<DataType>::ConstReverseDIterator::operator+=(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator& Matrix<DataType>::ConstReverseDIterator::operator-=(Matrix<DataType>::ConstReverseDIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator::difference_type Matrix<DataType>::ConstReverseDIterator::operator-(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstReverseDIterator::operator<=>(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::operator==(const Matrix<DataType>::ConstReverseDIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseDIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr < 0 ? std::optional{m_DiagonalSize + std::abs(m_DiagonalNr) - 1 - *m_DiagonalIndex}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseDIterator::getColumnNr() const
{
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr > 0 ? std::optional{m_DiagonalSize + m_DiagonalNr - 1 - *m_DiagonalIndex}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ConstReverseDIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseDIterator::getDiagonalIndex() const
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

template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator(const ReverseDIterator& reverseDIterator)
    : m_pMatrixPtr{reverseDIterator.m_pMatrixPtr}
    , m_DiagonalIndex{reverseDIterator.m_DiagonalIndex}
    , m_DiagonalNr{reverseDIterator.m_DiagonalNr}
    , m_DiagonalSize{reverseDIterator.m_DiagonalSize}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               std::optional<Matrix<DataType>::size_type> rowNr,
                                                               std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ConstReverseDIterator::ConstReverseDIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ConstReverseDIterator::_isEmpty() const
{
    CHECK_DITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex);
}

// 13) MIterator (mirrored diagonal iterator, traverses a matrix diagonal from the other side (symetrically to DIterator); diagonal 0 passes through the upper right corner of the matrix)

template<typename DataType>
typename Matrix<DataType>::MIterator& Matrix<DataType>::MIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(MIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::MIterator& Matrix<DataType>::MIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::MIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(MIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::MIterator& Matrix<DataType>::MIterator::operator+=(Matrix<DataType>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::MIterator& Matrix<DataType>::MIterator::operator-=(Matrix<DataType>::MIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::MIterator::difference_type Matrix<DataType>::MIterator::operator-(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::MIterator::operator<=>(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::MIterator::operator==(const Matrix<DataType>::MIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::MIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::MIterator::getColumnNr() const
{
    // no overflow as for positive diagonals the diagonal number should be strictly smaller than the number of matrix columns if the matrix is not empty
    return _isEmpty() ? std::nullopt : m_DiagonalNr < 0 ? (*m_DiagonalIndex < m_NrOfMatrixColumns ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1} : std::nullopt)
                                                        : (*m_DiagonalIndex < m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr) ? std::optional{m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr) - *m_DiagonalIndex - 1} : std::nullopt);
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::MIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::MIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::MIterator::operator*() const
{
    FORWARD_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType* Matrix<DataType>::MIterator::operator->() const
{
    FORWARD_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType& Matrix<DataType>::MIterator::operator[](Matrix<DataType>::MIterator::difference_type index) const
{
    FORWARD_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

template<typename DataType>
Matrix<DataType>::MIterator::MIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::MIterator::MIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       std::optional<Matrix<DataType>::size_type> rowNr,
                                       std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::MIterator::MIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::MIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 14) ConstMIterator

template<typename DataType>
typename Matrix<DataType>::ConstMIterator& Matrix<DataType>::ConstMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator& Matrix<DataType>::ConstMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::ConstMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator& Matrix<DataType>::ConstMIterator::operator+=(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator& Matrix<DataType>::ConstMIterator::operator-=(Matrix<DataType>::ConstMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator::difference_type Matrix<DataType>::ConstMIterator::operator-(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstMIterator::operator<=>(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::operator==(const Matrix<DataType>::ConstMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstMIterator::getRowNr() const
{
    return _isEmpty() ? std::nullopt : std::optional{m_DiagonalNr < 0 ? *m_DiagonalIndex + std::abs(m_DiagonalNr) : *m_DiagonalIndex};
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstMIterator::getColumnNr() const
{
    // no overflow as for positive diagonals the diagonal number should be strictly smaller than the number of matrix columns if the matrix is not empty
    return _isEmpty() ? std::nullopt : m_DiagonalNr < 0 ? (*m_DiagonalIndex < m_NrOfMatrixColumns ? std::optional{m_NrOfMatrixColumns - *m_DiagonalIndex - 1} : std::nullopt)
                                                        : (*m_DiagonalIndex < m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr) ? std::optional{m_NrOfMatrixColumns - static_cast<size_type>(m_DiagonalNr) - *m_DiagonalIndex - 1} : std::nullopt);
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ConstMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstMIterator::getDiagonalIndex() const
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
Matrix<DataType>::ConstMIterator::ConstMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstMIterator::ConstMIterator(const MIterator& mIterator)
    : m_pMatrixPtr{mIterator.m_pMatrixPtr}
    , m_DiagonalIndex{mIterator.m_DiagonalIndex}
    , m_DiagonalNr{mIterator.m_DiagonalNr}
    , m_DiagonalSize{mIterator.m_DiagonalSize}
    , m_NrOfMatrixColumns{mIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstMIterator::ConstMIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       std::optional<Matrix<DataType>::size_type> rowNr,
                                       std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ConstMIterator::ConstMIterator(DataType** pMatrixPtr,
                                       Matrix<DataType>::size_type nrOfMatrixRows,
                                       Matrix<DataType>::size_type nrOfMatrixColumns,
                                       const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ConstMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 15) ReverseMIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the MIterator)

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator& Matrix<DataType>::ReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator& Matrix<DataType>::ReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::ReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator& Matrix<DataType>::ReverseMIterator::operator+=(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator& Matrix<DataType>::ReverseMIterator::operator-=(Matrix<DataType>::ReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator::difference_type Matrix<DataType>::ReverseMIterator::operator-(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ReverseMIterator::operator<=>(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::operator==(const Matrix<DataType>::ReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseMIterator::getRowNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr < 0 ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + std::abs(m_DiagonalNr)}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseMIterator::getColumnNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size, the diagonal number is smaller than number of columns (in the second case)
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex
                                                       : m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex - m_DiagonalNr};
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ReverseMIterator::getDiagonalIndex() const
{
    return m_DiagonalIndex;
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseMIterator::operator*() const
{
    REVERSE_MITERATOR_ASTERISK_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType* Matrix<DataType>::ReverseMIterator::operator->() const
{
    REVERSE_MITERATOR_ARROW_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

template<typename DataType>
DataType& Matrix<DataType>::ReverseMIterator::operator[](Matrix<DataType>::ReverseMIterator::difference_type index) const
{
    REVERSE_MITERATOR_INDEX_DEREFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, index);
}

template<typename DataType>
Matrix<DataType>::ReverseMIterator::ReverseMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ReverseMIterator::ReverseMIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     std::optional<Matrix<DataType>::size_type> rowNr,
                                                     std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ReverseMIterator::ReverseMIterator(DataType** pMatrixPtr,
                                                     Matrix<DataType>::size_type nrOfMatrixRows,
                                                     Matrix<DataType>::size_type nrOfMatrixColumns,
                                                     const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ReverseMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// 16) ConstReverseMIterator

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator& Matrix<DataType>::ConstReverseMIterator::operator++()
{
    ITERATOR_PRE_INCREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator++(int unused)
{
    ITERATOR_POST_INCREMENT(ConstReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator& Matrix<DataType>::ConstReverseMIterator::operator--()
{
    ITERATOR_PRE_DECREMENT();
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::ConstReverseMIterator::operator--(int unused)
{
    ITERATOR_POST_DECREMENT(ConstReverseMIterator, unused);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator& Matrix<DataType>::ConstReverseMIterator::operator+=(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, +, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator& Matrix<DataType>::ConstReverseMIterator::operator-=(Matrix<DataType>::ConstReverseMIterator::difference_type offset)
{
    DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(m_DiagonalSize, m_DiagonalIndex, -, offset);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator::difference_type Matrix<DataType>::ConstReverseMIterator::operator-(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_COMPUTE_DIFFERENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
auto Matrix<DataType>::ConstReverseMIterator::operator<=>(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUIVALENCE(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::operator==(const Matrix<DataType>::ConstReverseMIterator& it) const
{
    DIAG_ITERATOR_CHECK_EQUALITY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, it);
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseMIterator::getRowNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size
    return _isEmpty() ? std::nullopt
                      : m_DiagonalNr < 0 ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1 + std::abs(m_DiagonalNr)}
                                         : *m_DiagonalIndex < m_DiagonalSize ? std::optional{m_DiagonalSize - *m_DiagonalIndex - 1}
                                                                             : std::nullopt;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseMIterator::getColumnNr() const
{
    // no overflow risk, diagonal index should not exceed diagonal size, the diagonal number is smaller than number of columns (in the second case)
    return _isEmpty() ? std::nullopt
                      : std::optional{m_DiagonalNr < 0 ? m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex
                                                       : m_NrOfMatrixColumns - m_DiagonalSize + *m_DiagonalIndex - m_DiagonalNr};
}

template<typename DataType>
typename Matrix<DataType>::diff_type Matrix<DataType>::ConstReverseMIterator::getDiagonalNr() const
{
    return m_DiagonalNr;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::ConstReverseMIterator::getDiagonalIndex() const
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

template<typename DataType>
Matrix<DataType>::ConstReverseMIterator::ConstReverseMIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseMIterator::ConstReverseMIterator(const ReverseMIterator& reverseMIterator)
    : m_pMatrixPtr{reverseMIterator.m_pMatrixPtr}
    , m_DiagonalIndex{reverseMIterator.m_DiagonalIndex}
    , m_DiagonalNr{reverseMIterator.m_DiagonalNr}
    , m_DiagonalSize{reverseMIterator.m_DiagonalSize}
    , m_NrOfMatrixColumns{reverseMIterator.m_NrOfMatrixColumns}
{
}

template<typename DataType>
Matrix<DataType>::ConstReverseMIterator::ConstReverseMIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               std::optional<Matrix<DataType>::size_type> rowNr,
                                                               std::optional<Matrix<DataType>::size_type> columnNr)
{
    CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr);
}

template<typename DataType>
Matrix<DataType>::ConstReverseMIterator::ConstReverseMIterator(DataType** pMatrixPtr,
                                                               Matrix<DataType>::size_type nrOfMatrixRows,
                                                               Matrix<DataType>::size_type nrOfMatrixColumns,
                                                               const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns, pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNr, diagonalIndex);
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

template<typename DataType>
bool Matrix<DataType>::ConstReverseMIterator::_isEmpty() const
{
    CHECK_MITERATOR_IS_EMPTY(m_pMatrixPtr, m_DiagonalNr, m_DiagonalSize, m_DiagonalIndex, m_NrOfMatrixColumns);
}

// matrix methods

template <typename DataType>
Matrix<DataType>::Matrix()
{
    _allocMemory(0, 0);
}

template<typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRows,
                         Matrix<DataType>::size_type nrOfColumns,
                         std::initializer_list<DataType> dataTypeInitList)
{
    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows * nrOfColumns > dataTypeInitList.size(), Matr::errorMessages[Matr::Errors::INSUFFICIENT_ELEMENTS_FOR_INIT]);

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::initializer_list<DataType>::iterator initListIterator{dataTypeInitList.begin()};

    /*absRowNr = absolute row number, i.e. number of the row within "physical" matrix (that includes free row/column capacity)
      When the "abs" keyword is missing (i.e. rowNr), then the row number within "logical" (actually used) matrix (excluding free capacity) is meant (see other methods too)
    */
    for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_copy_n(initListIterator, m_NrOfColumns, m_pBaseArrayPtr[absRowNr]);
        initListIterator += m_NrOfColumns;
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRows,
                         Matrix<DataType>::size_type nrOfColumns,
                         const DataType& value)
{
    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);

    const size_type c_RowCapacityToAlloc{nrOfRows + nrOfRows / 4};
    const size_type c_ColumnCapacityToAlloc{nrOfColumns + nrOfColumns / 4};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
    _fillInitItems(0, 0, nrOfRows, nrOfColumns, value);
}

template <typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>::size_type nrOfRowsColumns,
                         const std::pair<DataType, DataType>& diagMatrixValues)
{
    CHECK_ERROR_CONDITION(0 == nrOfRowsColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);

    const size_type c_RowColumnCapacityToAlloc{nrOfRowsColumns + nrOfRowsColumns / 4};
    _allocMemory(nrOfRowsColumns, nrOfRowsColumns, c_RowColumnCapacityToAlloc, c_RowColumnCapacityToAlloc);

    const auto& [allButMainDiagValue, mainDiagValue]{diagMatrixValues};

    for (size_type absRowNr{*m_RowCapacityOffset}, columnNr{0}; columnNr < nrOfRowsColumns; ++columnNr, ++absRowNr)
    {
        DataType* const pRowBegin{m_pBaseArrayPtr[absRowNr]};
        DataType* const pMainDiagElement{m_pBaseArrayPtr[absRowNr] + columnNr};
        DataType* const pRowEnd{m_pBaseArrayPtr[absRowNr] + nrOfRowsColumns};

        std::uninitialized_fill(pRowBegin, pMainDiagElement, allButMainDiagValue);
        std::uninitialized_fill(pMainDiagElement, pMainDiagElement + 1, mainDiagValue);
        std::uninitialized_fill(pMainDiagElement + 1, pRowEnd, allButMainDiagValue);
    }
}

template <typename DataType>
Matrix<DataType>::Matrix(const Matrix<DataType>& matrix)
    : Matrix{}
{
    if (!matrix.isEmpty())
    {
        _copyAllItemsFromMatrix(matrix);
    }
}

template<typename DataType>
Matrix<DataType>::Matrix(Matrix<DataType>&& matrix)
{
    _moveAllItemsFromMatrix(matrix);
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
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template<typename DataType>
const DataType& Matrix<DataType>::at(Matrix<DataType>::size_type rowNr,
                                     Matrix<DataType>::size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template<typename DataType>
DataType& Matrix<DataType>::operator[](Matrix<DataType>::size_type index)
{
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[*m_RowCapacityOffset + index / m_NrOfColumns][index % m_NrOfColumns];
}

template<typename DataType>
const DataType& Matrix<DataType>::operator[](Matrix<DataType>::size_type index) const
{
    CHECK_ERROR_CONDITION(index >= m_NrOfRows * m_NrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);

    return m_pBaseArrayPtr[*m_RowCapacityOffset + index / m_NrOfColumns][index % m_NrOfColumns];
}

template <typename DataType>
Matrix<DataType>& Matrix<DataType>::operator=(const Matrix<DataType>& matrix)
{
    if (&matrix != this)
    {
        // this de-allocation is required for performance reasons (free memory before the copy operation that follows) - would be performed anyway at move assignment
        _deallocMemory();

        // _copyAllItemsFromMatrix(matrix) would have been a more elegant solution, however a crash occurred in some tests (the root cause hasn't been found yet)
        Matrix temp{matrix};
        *this = std::move(temp);
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

        _moveAllItemsFromMatrix(matrix);
    }

    return *this;
}

// a contiguous unidimensional array with the matrix elements (in row order) is returned to user
template<typename DataType>
void* Matrix<DataType>::getBaseArray(Matrix<DataType>::size_type& nrOfElements)
{
    void* pAllocPtr{nullptr};

    if (!isEmpty())
    {
        shrinkToFit(); // when transfering ownership user should get exactly the number of elements contained in the used lines and columns (no extra capacity to be included)
        pAllocPtr = _convertToArray(nrOfElements);
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
#ifdef USE_CAPACITY_OFFSET
template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::getRowCapacityOffset() const
{
    return m_RowCapacityOffset;
}

template<typename DataType>
std::optional<typename Matrix<DataType>::size_type> Matrix<DataType>::getColumnCapacityOffset() const
{
    return m_ColumnCapacityOffset;
}
#endif
template<typename DataType>
bool Matrix<DataType>::isEmpty() const
{
    if (m_pAllocPtr)
    {
        assert(m_pBaseArrayPtr && m_NrOfRows > 0 && m_NrOfColumns > 0 && m_RowCapacity >= m_NrOfRows && m_ColumnCapacity >= m_NrOfColumns && m_RowCapacityOffset >= 0 && m_ColumnCapacityOffset >= 0);
    }
    else
    {
        assert(!m_pBaseArrayPtr && 0 == m_NrOfRows && 0 == m_NrOfColumns && 0 == m_RowCapacity && 0 == m_ColumnCapacity && !m_RowCapacityOffset.has_value() && !m_ColumnCapacityOffset.has_value());
    }

    return !m_pAllocPtr;
}

template <typename DataType>
void Matrix<DataType>::transpose(Matrix<DataType>& transposedMatrix)
{
    if (!isEmpty())
    {
        const size_type c_ResultingNrOfRows{m_NrOfColumns};
        const size_type c_ResultingNrOfColumns{m_NrOfRows};

        Matrix helperMatrix;
        const Matrix& srcMatrix{&transposedMatrix != this ? *this : helperMatrix};

        if (&transposedMatrix == this)
        {
            const size_type c_NewRowCapacity{m_RowCapacity < m_NrOfColumns ?  m_NrOfColumns +  m_NrOfColumns / 4 : m_RowCapacity};
            const size_type c_NewColumnCapacity{m_ColumnCapacity < m_NrOfRows ? m_NrOfRows + m_NrOfRows / 4 : m_ColumnCapacity};

            helperMatrix = std::move(*this);

            _deallocMemory(); // not actually required, just for "safety" and consistency purposes
            _allocMemory(helperMatrix.m_NrOfColumns, helperMatrix.m_NrOfRows, c_NewRowCapacity, c_NewColumnCapacity);

            // no use of _moveInitItems(), too much overhead
            for (size_type transposedMatrixAbsRowNr{*transposedMatrix.m_RowCapacityOffset}, rowNr{0}; rowNr < c_ResultingNrOfRows; ++rowNr, ++transposedMatrixAbsRowNr)
            {
                for (size_type srcMatrixAbsRowNr{*srcMatrix.m_RowCapacityOffset}, columnNr{0}; columnNr < c_ResultingNrOfColumns; ++columnNr, ++srcMatrixAbsRowNr)
                {
                    std::uninitialized_move_n(srcMatrix.m_pBaseArrayPtr[srcMatrixAbsRowNr] + rowNr, 1, transposedMatrix.m_pBaseArrayPtr[transposedMatrixAbsRowNr] + columnNr);
                }
            }
        }
        else
        {
            transposedMatrix._adjustSizeAndCapacity(m_NrOfColumns, m_NrOfRows);

            // no use of _copyInitItems(), too much overhead
            for (size_type transposedMatrixAbsRowNr{*transposedMatrix.m_RowCapacityOffset}, rowNr{0}; rowNr < c_ResultingNrOfRows; ++rowNr, ++transposedMatrixAbsRowNr)
            {
                for (size_type srcMatrixAbsRowNr{*srcMatrix.m_RowCapacityOffset}, columnNr{0}; columnNr < c_ResultingNrOfColumns; ++columnNr, ++srcMatrixAbsRowNr)
                {
                    std::uninitialized_copy_n(srcMatrix.m_pBaseArrayPtr[srcMatrixAbsRowNr] + rowNr, 1, transposedMatrix.m_pBaseArrayPtr[transposedMatrixAbsRowNr] + columnNr);
                }
            }
        }
    }
    else if (&transposedMatrix != this)
    {
        transposedMatrix._deallocMemory();
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
    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);

    const auto[c_NrOfRemainingRows, c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns, rowCapacity, columnCapacity)};

    // initialize new elements to the right side of the retained ones
    if (m_NrOfColumns > c_NrOfRemainingColumns)
    {
        _defaultConstructInitItems(0, c_NrOfRemainingColumns, c_NrOfRemainingRows, m_NrOfColumns - c_NrOfRemainingColumns);
    }

    // same for the ones below
    if (m_NrOfRows > c_NrOfRemainingRows)
    {
        _defaultConstructInitItems(c_NrOfRemainingRows, 0, nrOfRows - c_NrOfRemainingRows, m_NrOfColumns);
    }

    _normalizeRowCapacity();
}

template <typename DataType>
void Matrix<DataType>::resizeWithValue(Matrix<DataType>::size_type nrOfRows,
                                       Matrix<DataType>::size_type nrOfColumns,
                                       const DataType& value,
                                       Matrix<DataType>::size_type rowCapacity,
                                       Matrix<DataType>::size_type columnCapacity)
{
    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);

    const auto[c_NrOfRemainingRows, c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns, rowCapacity, columnCapacity)};

    // initialize new elements to the right side of the retained ones
    if (m_NrOfColumns > c_NrOfRemainingColumns)
    {
        _fillInitItems(0, c_NrOfRemainingColumns, c_NrOfRemainingRows, m_NrOfColumns - c_NrOfRemainingColumns, value);
    }

    // same for the ones below
    if (m_NrOfRows > c_NrOfRemainingRows)
    {
        _fillInitItems(c_NrOfRemainingRows, 0, nrOfRows - c_NrOfRemainingRows, m_NrOfColumns, value);
    }

    _normalizeRowCapacity();
}

template<typename DataType>
void Matrix<DataType>::shrinkToFit()
{
    if (m_RowCapacity != m_NrOfRows || m_ColumnCapacity != m_NrOfColumns)
    {
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // just for safety purposes, not actually needed
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template <typename DataType>
void Matrix<DataType>::insertRow(Matrix<DataType>::size_type rowNr)
{
    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_default_construct_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns);
}

template<typename DataType>
void Matrix<DataType>::insertRow(Matrix<DataType>::size_type rowNr, const DataType& value)
{
    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_fill_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns, value);
}

template <typename DataType>
void Matrix<DataType>::insertColumn(Matrix<DataType>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + c_UninitializedColumnNr, 1);
    }

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating uninitialized elements
    if (c_UninitializedColumnNr != columnNr)
    {
        if (0 == c_UninitializedColumnNr)
        {
            _rotateFirstColumn(columnNr);
        }
        else if (m_NrOfColumns - 1 == c_UninitializedColumnNr)
        {
            _rotateLastColumn(columnNr);
        }
        else
        {
            assert(false);
        }
    }
}

template<typename DataType>
void Matrix<DataType>::insertColumn(Matrix<DataType>::size_type columnNr,
                                    const DataType& value)
{
    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    _fillInitItems(0, c_UninitializedColumnNr, m_NrOfRows, 1, value);

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating uninitialized elements
    if (c_UninitializedColumnNr != columnNr)
    {
        if (0 == c_UninitializedColumnNr)
        {
            _rotateFirstColumn(columnNr);
        }
        else if (m_NrOfColumns - 1 == c_UninitializedColumnNr)
        {
            _rotateLastColumn(columnNr);
        }
        else
        {
            assert(false);
        }
    }
}

template <typename DataType>
void Matrix<DataType>::eraseRow(Matrix<DataType>::size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    if (1 == m_NrOfRows)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfRows{m_NrOfRows - 1}; c_RemainingNrOfRows <= m_RowCapacity / 4)
    {
        _reallocEraseDimensionElement(rowNr, true);
    }
    else
    {
        _shiftEraseRow(rowNr);
    }
}

template <typename DataType>
void Matrix<DataType>::eraseColumn(Matrix<DataType>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (1 == m_NrOfColumns)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfColumns{m_NrOfColumns - 1}; c_RemainingNrOfColumns <= m_ColumnCapacity / 4)
    {
        _reallocEraseDimensionElement(columnNr, false);
    }
    else
    {
        _shiftEraseColumn(columnNr);
    }
}

template<typename DataType>
void Matrix<DataType>::catByRow(Matrix<DataType>& firstMatrix,
                                Matrix<DataType>& secondMatrix)
{
    CHECK_ERROR_CONDITION(firstMatrix.m_NrOfColumns != secondMatrix.m_NrOfColumns, Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_ROW_LENGTH]);

    const size_type c_NewNrOfRows{firstMatrix.m_NrOfRows + secondMatrix.m_NrOfRows};
    const size_type c_NewNrOfColumns{firstMatrix.m_NrOfColumns};
    const size_type c_NewRowCapacity{c_NewNrOfRows + c_NewNrOfRows / 4};
    const size_type c_NewColumnCapacity{c_NewNrOfColumns + c_NewNrOfColumns / 4};

    Matrix helperMatrix{};

    if (&firstMatrix == this || &secondMatrix == this)
    {
        helperMatrix = std::move(*this);
    }

    _deallocMemory();
    _allocMemory(c_NewNrOfRows, c_NewNrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

    Matrix& firstConcatenatedMatrix{&firstMatrix == this ? helperMatrix : firstMatrix};
    Matrix& secondConcatenatedMatrix{&secondMatrix == this ? helperMatrix : secondMatrix};

    if (&secondConcatenatedMatrix == &helperMatrix) // 2 cases, same behavior: a) both matrixes to concatenate are current matrix (this) b) only second matrix is current matrix
    {
        _copyInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
        _moveInitItems(secondConcatenatedMatrix, 0, 0, firstConcatenatedMatrix.m_NrOfRows, 0, m_NrOfRows - firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
    }
    else if (&firstConcatenatedMatrix == &helperMatrix) // only first matrix to concatenate is current matrix
    {
        _moveInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
        _copyInitItems(secondConcatenatedMatrix, 0, 0, firstConcatenatedMatrix.m_NrOfRows, 0, m_NrOfRows - firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
    }
    else // both matrixes to concatenate are different from current matrix
    {
        _copyInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
        _copyInitItems(secondConcatenatedMatrix, 0, 0, firstConcatenatedMatrix.m_NrOfRows, 0, m_NrOfRows - firstConcatenatedMatrix.m_NrOfRows, m_NrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::catByColumn(Matrix<DataType>& firstMatrix,
                                   Matrix<DataType>& secondMatrix)
{
    CHECK_ERROR_CONDITION(firstMatrix.m_NrOfRows != secondMatrix.m_NrOfRows, Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH]);

    const size_type c_NewNrOfRows{firstMatrix.m_NrOfRows};
    const size_type c_NewNrOfColumns{firstMatrix.m_NrOfColumns + secondMatrix.m_NrOfColumns};
    const size_type c_NewRowCapacity{c_NewNrOfRows + c_NewNrOfRows / 4};
    const size_type c_NewColumnCapacity{c_NewNrOfColumns + c_NewNrOfColumns / 4};

    Matrix helperMatrix{};

    if (&firstMatrix == this || &secondMatrix == this)
    {
        helperMatrix = std::move(*this);
    }

    _deallocMemory();
    _allocMemory(c_NewNrOfRows, c_NewNrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

    Matrix& firstConcatenatedMatrix{&firstMatrix == this ? helperMatrix : firstMatrix};
    Matrix& secondConcatenatedMatrix{&secondMatrix == this ? helperMatrix : secondMatrix};

    if (&secondConcatenatedMatrix == &helperMatrix) // 2 cases, same behavior: a) both matrixes to concatenate are current matrix (this) b) only second matrix is current matrix
    {
        _copyInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, m_NrOfRows, firstConcatenatedMatrix.m_NrOfColumns);
        _moveInitItems(secondConcatenatedMatrix, 0, 0, 0, firstConcatenatedMatrix.m_NrOfColumns, m_NrOfRows, secondConcatenatedMatrix.m_NrOfColumns);
    }
    else if (&firstConcatenatedMatrix == &helperMatrix) // only first matrix to concatenate is current matrix
    {
        _moveInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, m_NrOfRows, firstConcatenatedMatrix.m_NrOfColumns);
        _copyInitItems(secondConcatenatedMatrix, 0, 0, 0, firstConcatenatedMatrix.m_NrOfColumns, m_NrOfRows, secondConcatenatedMatrix.m_NrOfColumns);
    }
    else // both matrixes to concatenate are different from current matrix
    {
        _copyInitItems(firstConcatenatedMatrix, 0, 0, 0, 0, m_NrOfRows, firstConcatenatedMatrix.m_NrOfColumns);
        _copyInitItems(secondConcatenatedMatrix, 0, 0, 0, firstConcatenatedMatrix.m_NrOfColumns, m_NrOfRows, secondConcatenatedMatrix.m_NrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::splitByRow(Matrix<DataType>& firstMatrix,
                                  Matrix<DataType>& secondMatrix,
                                  Matrix<DataType>::size_type splitRowNr)
{
    CHECK_ERROR_CONDITION(&firstMatrix == &secondMatrix, Matr::errorMessages[Matr::Errors::SAME_VARIABLE_TWO_ARGS]);
    CHECK_ERROR_CONDITION(splitRowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(splitRowNr == 0, Matr::errorMessages[Matr::Errors::RESULT_NO_ROWS]);

    if (&firstMatrix == this || &secondMatrix == this)
    {
        Matrix& currentMatrix{&firstMatrix == this ? firstMatrix : secondMatrix};
        Matrix& otherMatrix{&firstMatrix == this ? secondMatrix : firstMatrix};

        const size_type c_CurrentMatrixNewNrOfRows{&firstMatrix == this ? splitRowNr : currentMatrix.m_NrOfRows - splitRowNr};
        const size_type c_CurrentMatrixRemainingItemsStartingRowNr{&firstMatrix == this ? 0 : splitRowNr};

        // step 1: move items that should be removed from current matrix ("this") to the other destination matrix
        otherMatrix._adjustSizeAndCapacity(currentMatrix.m_NrOfRows - c_CurrentMatrixNewNrOfRows, currentMatrix.m_NrOfColumns);
        otherMatrix._moveInitItems(currentMatrix, splitRowNr - c_CurrentMatrixRemainingItemsStartingRowNr, 0, 0, 0, otherMatrix.m_NrOfRows, otherMatrix.m_NrOfColumns);

        // step 2: update the current matrix: move kept elements into correct positions and remove/destroy elements that belong to the other destination matrix (their content already moved in previous step)
        DataType** const pCurrentMatrixStartingRow{currentMatrix.m_pBaseArrayPtr + *currentMatrix.m_RowCapacityOffset};
        std::rotate(pCurrentMatrixStartingRow, pCurrentMatrixStartingRow + c_CurrentMatrixRemainingItemsStartingRowNr, pCurrentMatrixStartingRow + currentMatrix.m_NrOfRows);
        currentMatrix._destroyItems(splitRowNr, 0, currentMatrix.m_NrOfRows, currentMatrix.m_NrOfColumns);
        currentMatrix.m_NrOfRows = c_CurrentMatrixNewNrOfRows;
    }
    else
    {
        firstMatrix._adjustSizeAndCapacity(splitRowNr, m_NrOfColumns);
        firstMatrix._copyInitItems(*this, 0, 0, 0, 0, firstMatrix.m_NrOfRows, m_NrOfColumns);
        secondMatrix._adjustSizeAndCapacity(m_NrOfRows - splitRowNr, m_NrOfColumns);
        secondMatrix._copyInitItems(*this, splitRowNr, 0, 0, 0, secondMatrix.m_NrOfRows, m_NrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::splitByColumn(Matrix<DataType>& firstMatrix,
                                     Matrix<DataType>& secondMatrix,
                                     Matrix<DataType>::size_type splitColumnNr)
{
    CHECK_ERROR_CONDITION(&firstMatrix == &secondMatrix, Matr::errorMessages[Matr::Errors::SAME_VARIABLE_TWO_ARGS]);
    CHECK_ERROR_CONDITION(splitColumnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(splitColumnNr == 0, Matr::errorMessages[Matr::Errors::RESULT_NO_COLUMNS]);

    if (&firstMatrix == this || &secondMatrix == this)
    {
        Matrix& currentMatrix{&firstMatrix == this ? firstMatrix : secondMatrix};
        Matrix& otherMatrix{&firstMatrix == this ? secondMatrix : firstMatrix};

        const size_type c_CurrentMatrixNewNrOfColumns{&firstMatrix == this ? splitColumnNr : currentMatrix.m_NrOfColumns - splitColumnNr};
        const size_type c_CurrentMatrixRemainingItemsColumnOffset{&firstMatrix == this ? 0 : splitColumnNr};

        // step 1: move items that should be removed from current matrix ("this") to the other destination matrix
        otherMatrix._adjustSizeAndCapacity(currentMatrix.m_NrOfRows, currentMatrix.m_NrOfColumns - c_CurrentMatrixNewNrOfColumns);
        otherMatrix._moveInitItems(currentMatrix, 0, splitColumnNr - c_CurrentMatrixRemainingItemsColumnOffset, 0, 0, otherMatrix.m_NrOfRows, otherMatrix.m_NrOfColumns);

        // step 2: update the current matrix: move kept elements into correct positions and remove/destroy elements that belong to the other destination matrix (their content already moved in previous step)
        for (size_type currentMatrixAbsRowNr{*currentMatrix.m_RowCapacityOffset}; currentMatrixAbsRowNr != currentMatrix.m_NrOfRows + *currentMatrix.m_RowCapacityOffset; ++currentMatrixAbsRowNr)
        {
            std::copy(currentMatrix.m_pBaseArrayPtr[currentMatrixAbsRowNr] + c_CurrentMatrixRemainingItemsColumnOffset,
                      currentMatrix.m_pBaseArrayPtr[currentMatrixAbsRowNr] + currentMatrix.m_NrOfColumns,
                      currentMatrix.m_pBaseArrayPtr[currentMatrixAbsRowNr]);
        }

        currentMatrix._destroyItems(0, c_CurrentMatrixNewNrOfColumns, currentMatrix.m_NrOfRows, currentMatrix.m_NrOfColumns - c_CurrentMatrixNewNrOfColumns);
        currentMatrix.m_NrOfColumns = c_CurrentMatrixNewNrOfColumns;
    }
    else
    {
        firstMatrix._adjustSizeAndCapacity(m_NrOfRows, splitColumnNr);
        firstMatrix._copyInitItems(*this, 0, 0, 0, 0, m_NrOfRows, splitColumnNr);
        secondMatrix._adjustSizeAndCapacity(m_NrOfRows, m_NrOfColumns - splitColumnNr);
        secondMatrix._copyInitItems(*this, 0, splitColumnNr, 0, 0, m_NrOfRows, secondMatrix.m_NrOfColumns);
    }
}

template <typename DataType>
void Matrix<DataType>::swapRows(Matrix<DataType>::size_type firstRowNr,
                                Matrix<DataType>::size_type secondRowNr)
{
    CHECK_ERROR_CONDITION(firstRowNr >= m_NrOfRows || secondRowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    const size_type c_FirstAbsRowNr{*m_RowCapacityOffset + firstRowNr};
    const size_type c_SecondAbsRowNr{*m_RowCapacityOffset + secondRowNr};

    if (c_FirstAbsRowNr != c_SecondAbsRowNr)
    {
        // exchanging row pointers is enough and greatly optimizes the speed of execution
        std::swap(m_pBaseArrayPtr[c_FirstAbsRowNr], m_pBaseArrayPtr[c_SecondAbsRowNr]);
    }
}

template <typename DataType>
void Matrix<DataType>::swapColumns(Matrix<DataType>::size_type firstColumnNr,
                                   Matrix<DataType>::size_type secondColumnNr)
{
    CHECK_ERROR_CONDITION(firstColumnNr >= m_NrOfColumns || secondColumnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (firstColumnNr != secondColumnNr)
    {
        for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::swap(m_pBaseArrayPtr[absRowNr][firstColumnNr], m_pBaseArrayPtr[absRowNr][secondColumnNr]);
        }
    }
}

template <typename DataType>
bool Matrix<DataType>::operator==(const Matrix<DataType>& matrix) const
{
    bool areEqual{true};

    if (&matrix != this)
    {
        // matrix emptiness should be checked first in order to avoid accessing (std::optional) capacity offsets of empty matrixes (see second case: "else if")
        if (const bool isCurrentMatrixEmpty{isEmpty()}, isOtherMatrixEmpty{matrix.isEmpty()};
            isCurrentMatrixEmpty || isOtherMatrixEmpty)
        {
            areEqual = isCurrentMatrixEmpty && isOtherMatrixEmpty;
        }
        else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}, matrixAbsRowNr{*matrix.m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr, ++matrixAbsRowNr)
            {
                areEqual = areEqual && std::equal(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + m_NrOfColumns, matrix.m_pBaseArrayPtr[matrixAbsRowNr]);

                if (!areEqual)
                {
                    break;
                }
            }
        }
        else
        {
            areEqual = false;
        }
    }

    return areEqual;
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zEnd()
{
    GET_FORWARD_END_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowBegin(Matrix<DataType>::size_type rowNr)
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::zRowEnd(Matrix<DataType>::size_type rowNr)
{
    GET_FORWARD_ROW_END_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ZIterator Matrix<DataType>::getZIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZEnd() const
{
    GET_FORWARD_END_ZITERATOR(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowBegin(Matrix<DataType>::size_type rowNr) const
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::constZRowEnd(Matrix<DataType>::size_type rowNr) const
{
    GET_FORWARD_ROW_END_ZITERATOR(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::getConstZIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfRows, m_NrOfColumns, /, %, index);
}


template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZEnd()
{
    GET_REVERSE_END_ZITERATOR(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowBegin(Matrix<DataType>::size_type rowNr)
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::reverseZRowEnd(Matrix<DataType>::size_type rowNr)
{
    GET_REVERSE_ROW_END_ZITERATOR(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseZIterator Matrix<DataType>::getReverseZIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZEnd() const
{
    GET_REVERSE_END_ZITERATOR(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowBegin(Matrix<DataType>::size_type rowNr) const
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::constReverseZRowEnd(Matrix<DataType>::size_type rowNr) const
{
    GET_REVERSE_ROW_END_ZITERATOR(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseZIterator Matrix<DataType>::getConstReverseZIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfRows, m_NrOfColumns, /, %, index);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nEnd()
{
    GET_FORWARD_END_NITERATOR(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnBegin(Matrix<DataType>::size_type columnNr)
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::nColumnEnd(Matrix<DataType>::size_type columnNr)
{
    GET_FORWARD_COLUMN_END_NITERATOR(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::NIterator Matrix<DataType>::getNIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNEnd() const
{
    GET_FORWARD_END_NITERATOR(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnBegin(Matrix<DataType>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::constNColumnEnd(Matrix<DataType>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_END_NITERATOR(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstNIterator Matrix<DataType>::getConstNIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNEnd()
{
    GET_REVERSE_END_NITERATOR(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnBegin(Matrix<DataType>::size_type columnNr)
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::reverseNColumnEnd(Matrix<DataType>::size_type columnNr)
{
    GET_REVERSE_COLUMN_END_NITERATOR(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseNIterator Matrix<DataType>::getReverseNIterator(Matrix<DataType>::size_type index)
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNEnd() const
{
    GET_REVERSE_END_NITERATOR(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNColumnBegin(Matrix<DataType>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::constReverseNColumnEnd(Matrix<DataType>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_END_NITERATOR(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::getConstReverseNIterator(Matrix<DataType>::size_type rowNr,
                                                                                            Matrix<DataType>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseNIterator Matrix<DataType>::getConstReverseNIterator(Matrix<DataType>::size_type index) const
{
    GET_NON_DIAG_ITERATOR_BY_INDEX(ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, m_NrOfColumns, m_NrOfRows, %, /, index);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(Matrix<DataType>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(Matrix<DataType>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::dEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::getDIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::DIterator Matrix<DataType>::getDIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::constDEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::getConstDIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstDIterator Matrix<DataType>::getConstDIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex) const
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(Matrix<DataType>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(Matrix<DataType>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::reverseDEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::getReverseDIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseDIterator Matrix<DataType>::getReverseDIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::constReverseDEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::getConstReverseDIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseDIterator Matrix<DataType>::getConstReverseDIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex) const
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mBegin(Matrix<DataType>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mEnd(Matrix<DataType>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::mEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::getMIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::MIterator Matrix<DataType>::getMIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMBegin(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMEnd(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::constMEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::getConstMIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstMIterator Matrix<DataType>::getConstMIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex) const
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMBegin(Matrix<DataType>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMEnd(Matrix<DataType>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::reverseMEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::getReverseMIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ReverseMIterator Matrix<DataType>::getReverseMIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex)
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMBegin(Matrix<DataType>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMBegin(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMEnd(Matrix<DataType>::diff_type diagonaNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonaNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::constReverseMEnd(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::getConstReverseMIterator(Matrix<DataType>::size_type rowNr, Matrix<DataType>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template<typename DataType>
typename Matrix<DataType>::ConstReverseMIterator Matrix<DataType>::getConstReverseMIterator(const std::pair<Matrix<DataType>::diff_type, Matrix<DataType>::size_type>& diagonalNrAndIndex) const
{
    const auto&[diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows, m_NrOfColumns, diagonalNr, diagonalIndex);
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
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::begin() const
{
   return constZBegin();
}

template<typename DataType>
typename Matrix<DataType>::ConstZIterator Matrix<DataType>::end() const
{
    return constZEnd();
}

template <typename DataType>
std::pair<typename Matrix<DataType>::size_type,
          typename Matrix<DataType>::size_type> Matrix<DataType>::_resizeWithUninitializedNewElements(Matrix<DataType>::size_type nrOfRows,
                                                                                                      Matrix<DataType>::size_type nrOfColumns,
                                                                                                      Matrix<DataType>::size_type rowCapacity,
                                                                                                      Matrix<DataType>::size_type columnCapacity)
{
    const size_type c_NewNrOfRows{(nrOfRows > 0 && nrOfColumns > 0) ? nrOfRows : 0};
    const size_type c_NewNrOfColumns{c_NewNrOfRows > 0 ? nrOfColumns : 0};
    const size_type c_NewRowCapacity{std::max(rowCapacity, c_NewNrOfRows)};
    const size_type c_NewColumnCapacity{std::max(columnCapacity, c_NewNrOfColumns)};
    const size_type c_NrOfRowsToKeep{std::min(m_NrOfRows, c_NewNrOfRows)};
    const size_type c_NrOfColumnsToKeep{std::min(m_NrOfColumns, c_NewNrOfColumns)};
    const std::optional<size_type> c_NewRowCapacityOffset{c_NewNrOfRows > 0 ? std::optional((c_NewRowCapacity - c_NewNrOfRows) / 2) : std::nullopt};
    const std::optional<size_type> c_NewColumnCapacityOffset{c_NewNrOfColumns > 0 ? std::optional((c_NewColumnCapacity - c_NewNrOfColumns) / 2) : std::nullopt};

    if (!m_RowCapacityOffset.has_value() || !c_NewRowCapacityOffset.has_value() || c_NewRowCapacity != m_RowCapacity || c_NewColumnCapacity != m_ColumnCapacity || c_NewColumnCapacityOffset != m_ColumnCapacityOffset)
    {

        Matrix matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(c_NewNrOfRows, c_NewNrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

        // move the retained items back
        _moveInitItems(matrix, 0, 0, 0, 0, c_NrOfRowsToKeep, c_NrOfColumnsToKeep);
    }
    else
    {
        // move unused top capacity to the bottom to avoid alignment issues (should be re-distributed once resize is complete)
        if (m_RowCapacityOffset.has_value() && m_RowCapacityOffset > 0)
        {
            std::rotate(m_pBaseArrayPtr, m_pBaseArrayPtr + *m_RowCapacityOffset, m_pBaseArrayPtr + *m_RowCapacityOffset + m_NrOfRows);
            m_RowCapacityOffset = 0;
        }

        // ensure the items from the right side of the retained items get properly destroyed
        if (c_NewNrOfColumns < m_NrOfColumns)
        {
            _destroyItems(0, c_NrOfColumnsToKeep, c_NrOfRowsToKeep, m_NrOfColumns - c_NewNrOfColumns);
        }

        // same for the items below
        if (c_NewNrOfRows < m_NrOfRows)
        {
            _destroyItems(c_NrOfRowsToKeep, 0, m_NrOfRows - c_NewNrOfRows, m_NrOfColumns);
        }

        m_NrOfRows = c_NewNrOfRows;
        m_NrOfColumns = c_NewNrOfColumns;
    }

    return {c_NrOfRowsToKeep, c_NrOfColumnsToKeep};
}

template<typename DataType>
void Matrix<DataType>::_insertUninitializedRow(Matrix<DataType>::size_type rowNr)
{
    const size_type c_RowNr{std::clamp(rowNr, 0u, m_NrOfRows)};

    // double row capacity if no spare capacity left (to defer any re-size when inserting further rows)
    if (m_NrOfRows == m_RowCapacity)
    {
        Matrix helperMatrix{std::move(*this)};
        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows + 1, helperMatrix.m_NrOfColumns, 2 * helperMatrix.m_NrOfRows, helperMatrix.m_ColumnCapacity);

        // move everything back to the top/bottom of the inserted row (this one stays uninitialized - will be initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_RowNr, m_NrOfColumns);
        _moveInitItems(helperMatrix, c_RowNr, 0, c_RowNr + 1, 0, m_NrOfRows - c_RowNr, m_NrOfColumns);
    }
    else
    {
        const bool c_ShouldAppendRow{c_RowNr <= m_NrOfRows / 2 ? (0 == *m_RowCapacityOffset) : (m_RowCapacity - *m_RowCapacityOffset > m_NrOfRows)};
        ++m_NrOfRows;

        DataType** pCurrentMatrixStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        // new row is initially first/last row (depending on the insert position), move it into the insert position (all rows after the insert position moved one position downwards/upwards)
        if (c_ShouldAppendRow)
        {
            std::rotate(pCurrentMatrixStartingRow + c_RowNr, pCurrentMatrixStartingRow + m_NrOfRows - 1, pCurrentMatrixStartingRow + m_NrOfRows);
        }
        else
        {
            m_RowCapacityOffset = *m_RowCapacityOffset - 1;
            --pCurrentMatrixStartingRow;
            std::rotate(pCurrentMatrixStartingRow, pCurrentMatrixStartingRow + 1, pCurrentMatrixStartingRow + c_RowNr + 1);
        }
    }
}

template<typename DataType>
typename Matrix<DataType>::size_type Matrix<DataType>::_insertUninitializedColumn(Matrix<DataType>::size_type columnNr)
{
    size_type resultingColumnNr{std::clamp(columnNr, 0u, m_NrOfColumns)};

    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns + 1, helperMatrix.m_RowCapacity, 2 * helperMatrix.m_NrOfColumns);

        // move everything back to the left/right of the inserted column (this one stays uninitialized - will be initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, resultingColumnNr);
        _moveInitItems(helperMatrix, 0, resultingColumnNr, 0, resultingColumnNr + 1, m_NrOfRows, m_NrOfColumns - resultingColumnNr);
    }
    else
    {
        const bool c_ShouldAppendColumn{resultingColumnNr <= m_NrOfColumns / 2 ? (0 == m_ColumnCapacityOffset) : (m_ColumnCapacity - *m_ColumnCapacityOffset > m_NrOfColumns)};

        if (c_ShouldAppendColumn)
        {
            resultingColumnNr = m_NrOfColumns;
        }
        else
        {
            resultingColumnNr = 0;
            --*m_ColumnCapacityOffset;

            // make the newly added column visible
            for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
            {
                --m_pBaseArrayPtr[rowNr];
            }
        }

        ++m_NrOfColumns;
    }

    return resultingColumnNr;
}

template<typename DataType>
void Matrix<DataType>::_reallocEraseDimensionElement(Matrix<DataType>::size_type dimensionElementNr, bool isRow)
{
    if (!isEmpty())
    {
        const size_type c_RequiredNrOfRows{isRow ? m_NrOfRows - 1 : m_NrOfRows};
        const size_type c_RequiredNrOfColumns{isRow ? m_NrOfColumns : m_NrOfColumns - 1};
        const size_type c_RequiredRowCapacity{isRow ? 2 * c_RequiredNrOfRows : m_RowCapacity};
        const size_type c_RequiredColumnCapacity{isRow ? m_ColumnCapacity : 2 * c_RequiredNrOfColumns};

        // row or column nr depending on scenario (variable isRow)
        const size_type c_DimensionElementNr{std::clamp(dimensionElementNr, 0u, isRow ? c_RequiredNrOfRows : c_RequiredNrOfColumns)};

        // part one: top part (rows) / left part (columns) - relative to erased row/column
        const size_type c_PartOneNrOfRows{isRow ? c_DimensionElementNr : c_RequiredNrOfRows};
        const size_type c_PartOneNrOfColumns{isRow ? c_RequiredNrOfColumns : c_DimensionElementNr};

        // part two: bottom part (rows) / right part (columns) - relative to erased row/column
        const size_type c_PartTwoSrcStartingRowNr{isRow ? c_DimensionElementNr + 1 : 0};
        const size_type c_PartTwoSrcColumnOffset{c_DimensionElementNr + 1 - c_PartTwoSrcStartingRowNr};
        const size_type c_PartTwoStartingRowNr{isRow ? c_DimensionElementNr : 0};
        const size_type c_PartTwoColumnOffset{c_DimensionElementNr - c_PartTwoStartingRowNr};
        const size_type c_PartTwoNrOfRows{c_RequiredNrOfRows - c_PartTwoStartingRowNr};
        const size_type c_PartTwoNrOfColumns{c_RequiredNrOfColumns - c_PartTwoColumnOffset};

        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not really necessary, just for safety purposes
        _allocMemory(c_RequiredNrOfRows, c_RequiredNrOfColumns, c_RequiredRowCapacity, c_RequiredColumnCapacity);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_PartOneNrOfRows, c_PartOneNrOfColumns);
        _moveInitItems(helperMatrix, c_PartTwoSrcStartingRowNr, c_PartTwoSrcColumnOffset, c_PartTwoStartingRowNr, c_PartTwoColumnOffset, c_PartTwoNrOfRows, c_PartTwoNrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::_shiftEraseRow(Matrix<DataType>::size_type rowNr)
{
    if (!isEmpty())
    {
        const size_type c_RowNr{std::clamp(rowNr, 0u, m_NrOfRows - 1)};
        DataType** pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        if (c_RowNr < m_NrOfRows / 2)
        {
            std::rotate(pStartingRow, pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset], m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
            m_RowCapacityOffset = *m_RowCapacityOffset + 1;
        }
        else
        {
            std::rotate(pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1, pStartingRow + m_NrOfRows);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset + m_NrOfRows - 1], m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
        }

        --m_NrOfRows;
    }
}

template<typename DataType>
void Matrix<DataType>::_shiftEraseColumn(Matrix<DataType>::size_type columnNr)
{
    if (!isEmpty())
    {
        const size_type c_ColumnNr{std::clamp(columnNr, 0u, m_NrOfColumns - 1)};

        if (c_ColumnNr < m_NrOfColumns / 2)
        {
            for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + c_ColumnNr, m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1);
                std::destroy_n(m_pBaseArrayPtr[absRowNr], 1);
            }

            for (size_type absRowNr{0}; absRowNr < m_RowCapacity; ++absRowNr)
            {
                ++m_pBaseArrayPtr[absRowNr];
            }

            m_ColumnCapacityOffset = *m_ColumnCapacityOffset + 1;
        }
        else
        {
            for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr] + c_ColumnNr, m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1, m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
                std::destroy_n(m_pBaseArrayPtr[absRowNr] + m_NrOfColumns - 1, 1); // the memory outside matrix bounds should be uninitialized
            }
        }

        --m_NrOfColumns;
    }
}

template<typename DataType>
void Matrix<DataType>::_rotateFirstColumn(size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_NewColumnNr{std::clamp(newColumnNr, 0u, m_NrOfColumns)};

        for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + 1, m_pBaseArrayPtr[absRowNr] + c_NewColumnNr + 1);
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_rotateLastColumn(Matrix<DataType>::size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_LastColumnNr{m_NrOfColumns - 1};
        const size_type c_NewColumnNr{std::clamp(newColumnNr, 0u, c_LastColumnNr)};

        for(size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr] + c_NewColumnNr, m_pBaseArrayPtr[absRowNr] + c_LastColumnNr, m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_normalizeRowCapacity()
{
    const std::optional<size_type> c_NormalizedRowCapacityOffset{m_NrOfRows > 0 ? std::optional((m_RowCapacity - m_NrOfRows) / 2) : std::nullopt};

    if (m_RowCapacityOffset.has_value() && (c_NormalizedRowCapacityOffset.has_value() && c_NormalizedRowCapacityOffset > 0) && m_RowCapacityOffset < c_NormalizedRowCapacityOffset)
    {
        const size_type c_LastRowNr{m_NrOfRows - 1};
        DataType** const pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};
        DataType** const pEndingRow{pStartingRow + c_LastRowNr};
        DataType** const pStartingRowToReplace{m_pBaseArrayPtr + *c_NormalizedRowCapacityOffset};
        DataType** const pEndingRowToReplace{pStartingRowToReplace + c_LastRowNr};

        DataType** pRowToReplace{pEndingRowToReplace};

        for (DataType** pCurrentRow{pEndingRow}; pCurrentRow >= pStartingRow; --pCurrentRow)
        {
            std::iter_swap(pCurrentRow, pRowToReplace);
            --pRowToReplace;
        }

        m_RowCapacityOffset = c_NormalizedRowCapacityOffset;
    }
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

        m_RowCapacityOffset = (m_RowCapacity - nrOfRows) / 2;
        m_ColumnCapacityOffset = (m_ColumnCapacity - nrOfColumns) / 2;

        m_pBaseArrayPtr = static_cast<DataType**>(std::malloc(m_RowCapacity * sizeof(DataType*)));
        m_pAllocPtr = static_cast<DataType*>(std::malloc(m_RowCapacity * m_ColumnCapacity * sizeof(DataType)));

        // map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed, left free column capacity excluded)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
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
        m_RowCapacityOffset.reset();
        m_ColumnCapacityOffset.reset();
        m_pBaseArrayPtr = nullptr;
        m_pAllocPtr = nullptr;
    }
}

template<typename DataType>
void Matrix<DataType>::_deallocMemory()
{
    if (!isEmpty())
    {
        // ensure the objects contained within matrix are properly disposed (no column capacity offset provided as argument -> free left capacity excluded by m_pBaseArrayPtr pointer elements)
        _destroyItems(*m_RowCapacityOffset, 0, m_NrOfRows, m_NrOfColumns);

        // cut access of row pointers to allocated memory
        std::fill_n(m_pBaseArrayPtr, m_RowCapacity, nullptr);

        std::free(m_pBaseArrayPtr);
        m_pBaseArrayPtr = nullptr;

        std::free(m_pAllocPtr);
        m_pAllocPtr = nullptr;

        m_NrOfRows = 0;
        m_NrOfColumns = 0;
        m_RowCapacity = 0;
        m_ColumnCapacity = 0;
        m_RowCapacityOffset.reset();
        m_ColumnCapacityOffset.reset();
    }
}

template<typename DataType>
void Matrix<DataType>::_adjustSizeAndCapacity(Matrix<DataType>::size_type nrOfRows,
                                              Matrix<DataType>::size_type nrOfColumns)
{
    const size_type c_NewRowCapacity{nrOfRows + nrOfRows / 4};
    const size_type c_NewColumnCapacity{nrOfColumns + nrOfColumns / 4};
    const size_type c_OldRowCapacity{m_RowCapacity};
    const size_type c_OldColumnCapacity{m_ColumnCapacity};

    _deallocMemory();
    _allocMemory(nrOfRows, nrOfColumns, c_OldRowCapacity < nrOfRows ? c_NewRowCapacity : c_OldRowCapacity, c_OldColumnCapacity < nrOfColumns ? c_NewColumnCapacity : c_OldColumnCapacity);
}

template<typename DataType>
void Matrix<DataType>::_copyAllItemsFromMatrix(const Matrix<DataType>& matrix)
{
    if (&matrix != this)
    {
        const size_type c_RowCapacityToAlloc{matrix.m_NrOfRows + matrix.m_NrOfRows / 4};
        const size_type c_ColumnCapacityToAlloc{matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4};

        if (matrix.isEmpty())
        {
            _deallocMemory();
        }
        else if (m_RowCapacity != c_RowCapacityToAlloc || m_ColumnCapacity != c_ColumnCapacityToAlloc)
        {
            _deallocMemory();
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
        }
        else
        {
            /* ensure existing elements are destroyed correctly
              (the number of rows/columns between the two matrixes might not coincide meaning some elements might be left "hanging" - outside bounds elements should be uninitialized)
            */
            _destroyItems(0, 0, m_NrOfRows, m_NrOfColumns);

            m_NrOfRows = matrix.m_NrOfRows;
            m_NrOfColumns = matrix.m_NrOfColumns;
            m_RowCapacityOffset = (m_RowCapacity - m_NrOfRows) / 2;
            m_ColumnCapacityOffset = (m_ColumnCapacity - m_NrOfColumns) / 2;
        }

        _copyInitItems(matrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::_moveAllItemsFromMatrix(Matrix<DataType>& matrix)
{
    m_pAllocPtr = matrix.m_pAllocPtr;
    m_pBaseArrayPtr = matrix.m_pBaseArrayPtr;
    m_NrOfRows = matrix.m_NrOfRows;
    m_NrOfColumns = matrix.m_NrOfColumns;
    m_RowCapacity = matrix.m_RowCapacity;
    m_ColumnCapacity = matrix.m_ColumnCapacity;
    m_RowCapacityOffset = matrix.m_RowCapacityOffset;
    m_ColumnCapacityOffset = matrix.m_ColumnCapacityOffset;

    matrix._allocMemory(0, 0);
}

template<typename DataType>
void Matrix<DataType>::_copyInitItems(const Matrix<DataType>& matrix,
                                      Matrix<DataType>::size_type matrixStartingRowNr,
                                      Matrix<DataType>::size_type matrixColumnOffset,
                                      Matrix<DataType>::size_type startingRowNr,
                                      Matrix<DataType>::size_type columnOffset,
                                      Matrix<DataType>::size_type nrOfRows,
                                      Matrix<DataType>::size_type nrOfColumns)
{
    // emptiness check required due to capacity offset optionals (see below)
    if (!isEmpty() && !matrix.isEmpty())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{*m_RowCapacityOffset + startingRowNr}, srcAbsRowNr{*matrix.m_RowCapacityOffset + matrixStartingRowNr};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows;
             ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_copy_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns, m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_moveInitItems(Matrix<DataType>& matrix,
                                      Matrix<DataType>::size_type matrixStartingRowNr,
                                      Matrix<DataType>::size_type matrixColumnOffset,
                                      Matrix<DataType>::size_type startingRowNr,
                                      Matrix<DataType>::size_type columnOffset,
                                      Matrix<DataType>::size_type nrOfRows,
                                      Matrix<DataType>::size_type nrOfColumns)
{
    // emptiness check required due to capacity offset optionals (see below)
    if (!isEmpty() && !matrix.isEmpty())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{*m_RowCapacityOffset + startingRowNr}, srcAbsRowNr{*matrix.m_RowCapacityOffset + matrixStartingRowNr};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows;
             ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_move_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns, m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template<typename DataType>
void Matrix<DataType>::_fillInitItems(Matrix<DataType>::size_type startingRowNr,
                                      Matrix<DataType>::size_type columnOffset,
                                      Matrix<DataType>::size_type nrOfRows,
                                      Matrix<DataType>::size_type nrOfColumns,
                                      const DataType& value)
{
    _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

    for (size_type absRowNr{*m_RowCapacityOffset + startingRowNr}; absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
    {
        std::uninitialized_fill_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns, value);
    }
}

template<typename DataType>
void Matrix<DataType>::_defaultConstructInitItems(Matrix<DataType>::size_type startingRowNr,
                                                  Matrix<DataType>::size_type columnOffset,
                                                  Matrix<DataType>::size_type nrOfRows,
                                                  Matrix<DataType>::size_type nrOfColumns)
{
    _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

    for (size_type absRowNr{*m_RowCapacityOffset + startingRowNr}; absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
    {
        std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::_destroyItems(Matrix<DataType>::size_type startingRowNr,
                                     Matrix<DataType>::size_type columnOffset,
                                     Matrix<DataType>::size_type nrOfRows,
                                     Matrix<DataType>::size_type nrOfColumns)
{
    _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

    for (size_type absRowNr{*m_RowCapacityOffset + startingRowNr}; absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
    {
        std::destroy_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
    }
}

template<typename DataType>
void Matrix<DataType>::_clampSubMatrixSelectionParameters(Matrix<DataType>::size_type& startingRowNr,
                                                          Matrix<DataType>::size_type& columnOffset,
                                                          Matrix<DataType>::size_type& nrOfRows,
                                                          Matrix<DataType>::size_type& nrOfColumns)
{
    startingRowNr = std::clamp(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp(nrOfRows, 0u, m_NrOfRows - startingRowNr);
    nrOfColumns = std::clamp(nrOfColumns, 0u, m_NrOfColumns - columnOffset);
}


template<typename DataType>
void Matrix<DataType>::_externalClampSubMatrixSelectionParameters(const Matrix<DataType>& srcMatrix,
                                                                  Matrix<DataType>::size_type& srcStartingRowNr,
                                                                  Matrix<DataType>::size_type& srcColumnOffset,
                                                                  Matrix<DataType>::size_type& startingRowNr,
                                                                  Matrix<DataType>::size_type& columnOffset,
                                                                  Matrix<DataType>::size_type& nrOfRows,
                                                                  Matrix<DataType>::size_type& nrOfColumns)
{
    srcStartingRowNr = std::clamp(srcStartingRowNr, 0u, srcMatrix.m_NrOfRows);
    srcColumnOffset = std::clamp(srcColumnOffset, 0u, srcMatrix.m_NrOfColumns);
    startingRowNr = std::clamp(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp(nrOfRows, 0u, std::min(srcMatrix.m_NrOfRows - srcStartingRowNr, m_NrOfRows - startingRowNr));
    nrOfColumns = std::clamp(nrOfColumns, 0u, std::min(srcMatrix.m_NrOfColumns - srcColumnOffset, m_NrOfColumns - columnOffset));
}

template<typename DataType>
void* Matrix<DataType>::_convertToArray(Matrix<DataType>::size_type& nrOfElements)
{
    // effective transfer of ownership (items - including uninitalized ones)
    void* pAllocPtr{m_pAllocPtr};
    nrOfElements = m_RowCapacity * m_ColumnCapacity;

    // delete the matrix row pointers
    std::free(m_pBaseArrayPtr);

    // reset all internal variables to bring the matrix to empty state
    m_pBaseArrayPtr = nullptr;
    m_pAllocPtr = nullptr;
    m_NrOfRows = 0;
    m_NrOfColumns = 0;
    m_RowCapacity = 0;
    m_ColumnCapacity = 0;
    m_RowCapacityOffset.reset();
    m_ColumnCapacityOffset.reset();

    return pAllocPtr;
}

#undef CHECK_ERROR_CONDITION

#undef COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS
#undef COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS
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
#undef FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF
#undef REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF
#undef FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE
#undef REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE
#undef NON_DIAG_ITERATOR_CHECK_EQUALITY
#undef FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE
#undef REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE
#undef FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT
#undef REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT
#undef FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT
#undef REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT
#undef CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY
#undef CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY
#undef GET_FORWARD_NON_DIAG_BEGIN_ITERATOR
#undef GET_REVERSE_NON_DIAG_BEGIN_ITERATOR
#undef GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_NON_DIAG_ITERATOR_BY_INDEX
#undef DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF
#undef DIAG_ITERATOR_DO_INCREMENT
#undef DIAG_ITERATOR_DO_DECREMENT
#undef DIAG_ITERATOR_COMPUTE_DIFFERENCE
#undef DIAG_ITERATOR_CHECK_EQUIVALENCE
#undef DIAG_ITERATOR_CHECK_EQUALITY
#undef GET_DIAG_BEGIN_ITERATOR
#undef GET_DIAG_RANDOM_ITERATOR
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
#undef CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR
#undef CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX
#undef CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR
#undef CONSTRUCT_REVERSE_DITERATOR_WITH_DIAG_NR_AND_INDEX
#undef FORWARD_DITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_DITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_DITERATOR_ARROW_DEREFERENCE
#undef REVERSE_DITERATOR_ARROW_DEREFERENCE
#undef FORWARD_DITERATOR_INDEX_DEREFERENCE
#undef REVERSE_DITERATOR_INDEX_DEREFERENCE
#undef GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_END_DITERATOR_BY_DIAG_NUMBER
#undef GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX
#undef CHECK_DITERATOR_IS_EMPTY
#undef CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR
#undef CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX
#undef CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR
#undef CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX
#undef FORWARD_MITERATOR_ASTERISK_DEREFERENCE
#undef REVERSE_MITERATOR_ASTERISK_DEREFERENCE
#undef FORWARD_MITERATOR_ARROW_DEREFERENCE
#undef REVERSE_MITERATOR_ARROW_DEREFERENCE
#undef FORWARD_MITERATOR_INDEX_DEREFERENCE
#undef REVERSE_MITERATOR_INDEX_DEREFERENCE
#undef GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_END_MITERATOR_BY_DIAG_NUMBER
#undef GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX
#undef CHECK_MITERATOR_IS_EMPTY

#endif // MATRIX_H
