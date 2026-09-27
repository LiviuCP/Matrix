module;

#include <optional>
#include <vector>

#include "matrixdimensions.h"

#define ITERATOR_TRAITS(IterableType, DiffType, ReferenceType)                                                         \
    using iterator_category = std::random_access_iterator_tag;                                                         \
    using value_type = IterableType;                                                                                   \
    using difference_type = DiffType;                                                                                  \
    using pointer = IterableType**;                                                                                    \
    using reference = ReferenceType;

export module matrix:matrix_header;

export using matrix_size_t = Matr::size_t;
export using matrix_diff_t = Matr::diff_t;

template <typename MatrixIterator> MatrixIterator addOffsetToIterator(const MatrixIterator& it, matrix_diff_t offset)
{
    MatrixIterator temp{it};
    temp += offset;
    return temp;
}

export constexpr matrix_size_t maxAllowedDimension()
{
    // set all bits to 1 to get the maximum possible dimension (i.e. max. possible count of rows/columns)
    constexpr matrix_size_t c_MaxDimension{static_cast<matrix_size_t>(~matrix_size_t{0})};

    // set first bit to 0 in order to obtain a maximum dimension size that when squared doesn't exceed the maximum
    // matrix_diff_t value on the positive interval
    constexpr matrix_size_t c_MaxAllowedDimension{c_MaxDimension >> 1};

    return c_MaxAllowedDimension;
}

template <typename T>
concept MatrixElementType =
    std::default_initializable<T> && std::copy_constructible<T> && std::move_constructible<T> &&
    std::is_copy_assignable_v<T> && std::is_move_assignable_v<T> && std::swappable<T> && std::equality_comparable<T>;

export template <MatrixElementType T> class Matrix
{
public:
    using size_type = matrix_size_t;
    using diff_type = matrix_diff_t;
    using dimensions_t = std::pair<size_type, size_type>;

    template <typename IterType> class FullTraverseIterator;
    template <typename IterType> class PartialDiagIterator;

    class ZIterator;
    class ConstZIterator;
    class ReverseZIterator;
    class ConstReverseZIterator;
    class NIterator;
    class ConstNIterator;
    class ReverseNIterator;
    class ConstReverseNIterator;
    class DIterator;
    class ConstDIterator;
    class ReverseDIterator;
    class ConstReverseDIterator;
    class MIterator;
    class ConstMIterator;
    class ReverseMIterator;
    class ConstReverseMIterator;

    Matrix();
    Matrix(size_type nrOfRows, size_type nrOfColumns, std::vector<T>&& vec);
    Matrix(dimensions_t dimensions, const T& value);
    Matrix(size_type nrOfRowsColumns, const std::pair<T, T>& diagMatrixValues);
    Matrix(const Matrix& matrix);
    Matrix(Matrix&& matrix);
    ~Matrix();

    T& at(size_type rowNr, size_type columnNr);
    const T& at(size_type rowNr, size_type columnNr) const;

    Matrix& operator=(const Matrix& matrix);
    Matrix& operator=(Matrix&& matrix);

    // transfers ownership of the data to the user (object becomes empty and user becomes responsible for de-allocating
    // the data properly)
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

    void transpose();

    void clear();

    // resize and don't init new elements (user has the responsibility to init them), existing elements retain their old
    // values
    void resize(size_type nrOfRows, size_type nrOfColumns);

    // resize and fill new elements with value of dataType, existing elements retain their old values
    void resize(size_type nrOfRows, size_type nrOfColumns, const T& dataType);

    // reserve capacity without changing dimensions and element values
    void reserve(size_type rowCapacity, size_type columnCapacity);

    void shrinkToFit();

    void insertRow(size_type rowNr);
    void insertRow(size_type rowNr, const T& value);
    void insertColumn(size_type columnNr);
    void insertColumn(size_type columnNr, const T& value);
    void eraseRow(size_type rowNr);
    void eraseColumn(size_type columnNr);

    // vertical concatenation (cumulated rows)
    void catByRow(Matrix& matrix);

    // horizontal concatenation (cumulated columns)
    void catByColumn(Matrix& matrix);

    // vertical splitting
    void splitByRow(Matrix& matrix, Matrix<T>::size_type splitRowNr);

    // horizontal splitting
    void splitByColumn(Matrix& matrix, size_type splitColumnNr);

    void swapRows(size_type firstRowNr, size_type secondRowNr);
    void swapColumns(size_type firstColumnNr, size_type secondColumnNr);

    // the template type should have operator == implemented, otherwise a template specialization is required
    bool operator==(const Matrix& matrix) const;

    inline ZIterator zBegin();
    inline ZIterator zEnd();
    inline ZIterator zRowBegin(size_type rowNr);
    inline ZIterator zRowEnd(size_type rowNr);
    inline ZIterator getZIterator(size_type rowNr, size_type columnNr);
    inline ConstZIterator constZBegin() const;
    inline ConstZIterator constZEnd() const;
    inline ConstZIterator constZRowBegin(size_type rowNr) const;
    inline ConstZIterator constZRowEnd(size_type rowNr) const;
    inline ConstZIterator getConstZIterator(size_type rowNr, size_type columnNr) const;
    inline ReverseZIterator reverseZBegin();
    inline ReverseZIterator reverseZEnd();
    inline ReverseZIterator reverseZRowBegin(size_type rowNr);
    inline ReverseZIterator reverseZRowEnd(size_type rowNr);
    inline ReverseZIterator getReverseZIterator(size_type rowNr, size_type columnNr);
    inline ConstReverseZIterator constReverseZBegin() const;
    inline ConstReverseZIterator constReverseZEnd() const;
    inline ConstReverseZIterator constReverseZRowBegin(size_type rowNr) const;
    inline ConstReverseZIterator constReverseZRowEnd(size_type rowNr) const;
    inline ConstReverseZIterator getConstReverseZIterator(size_type rowNr, size_type columnNr) const;
    inline NIterator nBegin();
    inline NIterator nEnd();
    inline NIterator nColumnBegin(size_type columnNr);
    inline NIterator nColumnEnd(size_type columnNr);
    inline NIterator getNIterator(size_type rowNr, size_type columnNr);
    inline ConstNIterator constNBegin() const;
    inline ConstNIterator constNEnd() const;
    inline ConstNIterator constNColumnBegin(size_type columnNr) const;
    inline ConstNIterator constNColumnEnd(size_type columnNr) const;
    inline ConstNIterator getConstNIterator(size_type rowNr, size_type columnNr) const;
    inline ReverseNIterator reverseNBegin();
    inline ReverseNIterator reverseNEnd();
    inline ReverseNIterator reverseNColumnBegin(size_type columnNr);
    inline ReverseNIterator reverseNColumnEnd(size_type columnNr);
    inline ReverseNIterator getReverseNIterator(size_type rowNr, size_type columnNr);
    inline ConstReverseNIterator constReverseNBegin() const;
    inline ConstReverseNIterator constReverseNEnd() const;
    inline ConstReverseNIterator constReverseNColumnBegin(size_type columnNr) const;
    inline ConstReverseNIterator constReverseNColumnEnd(size_type columnNr) const;
    inline ConstReverseNIterator getConstReverseNIterator(size_type rowNr, size_type columnNr) const;
    inline DIterator dBegin(diff_type diagonalNr);
    inline DIterator dBegin(size_type rowNr, size_type columnNr);
    inline DIterator dEnd(diff_type diagonalNr);
    inline DIterator dEnd(size_type rowNr, size_type columnNr);
    inline DIterator getDIterator(size_type rowNr, size_type columnNr);
    inline DIterator getDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);
    inline ConstDIterator constDBegin(diff_type diagonalNr) const;
    inline ConstDIterator constDBegin(size_type rowNr, size_type columnNr) const;
    inline ConstDIterator constDEnd(diff_type diagonalNr) const;
    inline ConstDIterator constDEnd(size_type rowNr, size_type columnNr) const;
    inline ConstDIterator getConstDIterator(size_type rowNr, size_type columnNr) const;
    inline ConstDIterator getConstDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;
    inline ReverseDIterator reverseDBegin(diff_type diagonalNr);
    inline ReverseDIterator reverseDBegin(size_type rowNr, size_type columnNr);
    inline ReverseDIterator reverseDEnd(diff_type diagonalNr);
    inline ReverseDIterator reverseDEnd(size_type rowNr, size_type columnNr);
    inline ReverseDIterator getReverseDIterator(size_type rowNr, size_type columnNr);
    inline ReverseDIterator getReverseDIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);
    inline ConstReverseDIterator constReverseDBegin(diff_type diagonalNr) const;
    inline ConstReverseDIterator constReverseDBegin(size_type rowNr, size_type columnNr) const;
    inline ConstReverseDIterator constReverseDEnd(diff_type diagonalNr) const;
    inline ConstReverseDIterator constReverseDEnd(size_type rowNr, size_type columnNr) const;
    inline ConstReverseDIterator getConstReverseDIterator(size_type rowNr, size_type columnNr) const;
    inline ConstReverseDIterator getConstReverseDIterator(
        const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;
    inline MIterator mBegin(diff_type diagonalNr);
    inline MIterator mBegin(size_type rowNr, size_type columnNr);
    inline MIterator mEnd(diff_type diagonalNr);
    inline MIterator mEnd(size_type rowNr, size_type columnNr);
    inline MIterator getMIterator(size_type rowNr, size_type columnNr);
    inline MIterator getMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);
    inline ConstMIterator constMBegin(diff_type diagonalNr) const;
    inline ConstMIterator constMBegin(size_type rowNr, size_type columnNr) const;
    inline ConstMIterator constMEnd(diff_type diagonalNr) const;
    inline ConstMIterator constMEnd(size_type rowNr, size_type columnNr) const;
    inline ConstMIterator getConstMIterator(size_type rowNr, size_type columnNr) const;
    inline ConstMIterator getConstMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;
    inline ReverseMIterator reverseMBegin(diff_type diagonalNr);
    inline ReverseMIterator reverseMBegin(size_type rowNr, size_type columnNr);
    inline ReverseMIterator reverseMEnd(diff_type diagonalNr);
    inline ReverseMIterator reverseMEnd(size_type rowNr, size_type columnNr);
    inline ReverseMIterator getReverseMIterator(size_type rowNr, size_type columnNr);
    inline ReverseMIterator getReverseMIterator(const std::pair<diff_type, size_type>& diagonalNrAndIndex);
    inline ConstReverseMIterator constReverseMBegin(diff_type diagonalNr) const;
    inline ConstReverseMIterator constReverseMBegin(size_type rowNr, size_type columnNr) const;
    inline ConstReverseMIterator constReverseMEnd(diff_type diagonalNr) const;
    inline ConstReverseMIterator constReverseMEnd(size_type rowNr, size_type columnNr) const;
    inline ConstReverseMIterator getConstReverseMIterator(size_type rowNr, size_type columnNr) const;
    inline ConstReverseMIterator getConstReverseMIterator(
        const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    // required for being able to use the (const) auto (&) syntax for iterating through the matrix elements
    inline ZIterator begin();
    inline ZIterator end();
    inline ConstZIterator begin() const;
    inline ConstZIterator end() const;

private:
    // resize matrix, returns number of preserved elements (rows * columns), new elements should be initialized by
    // caller
    std::pair<size_type, size_type> _resizeWithUninitializedNewElements(size_type nrOfRows, size_type nrOfColumns);

    // inserts the uninitialized row into the required position, initialialization is left to the caller
    void _insertUninitializedRow(size_type rowNr);

    // inserts the uninitialized column either into the required position or into the last position (depending on
    // available column capacity)
    size_type _insertUninitializedColumn(size_type columnNr);

    // erases the row or column (depending on isRow) by reallocating memory and putting back all elements except the
    // row/column (dimension element) to be removed
    void _reallocEraseDimensionElement(size_type dimensionElementNr, bool isRow);

    // erases the row without changing matrix capacity (shift bottom rows to top)
    void _shiftEraseRow(size_type rowNr);

    // erases the column without changing matrix capacity (shift right columns to left)
    void _shiftEraseColumn(size_type columnNr);

    // places the first column into the new position by performing a rotation
    void _rotateFirstColumn(size_type newColumnNr);

    // places the last column into the new position by performing a rotation
    void _rotateLastColumn(size_type newColumnNr);

    // moves the matrix rows to top (row capacity offset set to 0) as preparation for performing specific operations
    // (capacity can the be re-distributed by calling _normalizeRowCapacity())
    void _alignToTop();

    // moves the matrix columns to left by the specified count of positions (which range between 0 and the current
    // column capacity offset)
    void _shiftColumnsLeft(size_type nrOfPositionsToShift);

    // normalize row capacity to have equal top/bottom unused capacity
    void _normalizeRowCapacity();

    // ensure the currently allocated memory is first released (_deallocMemory()) prior to using this function
    void _allocMemory(size_type nrOfRows, size_type nrOfColumns, size_type rowCapacity = 0,
                      size_type columnCapacity = 0);

    // ensure the current number of rows and columns is saved to local variables if still needed further
    void _deallocMemory();

    // clears the initialized memory (without de-allocation - capacity stays constant) and remaps it for the requested
    // number of rows and columns
    void _remapMemory(size_type nrOfRows, size_type nrOfColumns);

    // used for matrix-to-matrix copy construction and assignment
    void _copyAssignMatrix(const Matrix& matrix);

    // used for the matrix-to-matrix move construction and assignment
    void _moveAssignMatrix(Matrix& matrix);

    // initialize all or part of the elements by copying from source matrix
    void _copyInitItems(const Matrix& matrix, size_type matrixStartingRowNr, size_type matrixColumnOffset,
                        size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // initialize all or part of the elements by moving from source matrix
    void _moveInitItems(Matrix& matrix, size_type matrixStartingRowNr, size_type matrixColumnOffset,
                        size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // initialize all or part of the elements by filling in the same value
    void _fillInitItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns,
                        const T& value);

    // initialize all or part of the elements with default constructor
    void _defaultConstructInitItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows,
                                    size_type nrOfColumns);

    // destroy the elements contained within interval
    void _destroyItems(size_type startingRowNr, size_type columnOffset, size_type nrOfRows, size_type nrOfColumns);

    // ensures the selected sub-matrix (elements to change) fits into matrix
    void _clampSubMatrixSelectionParameters(size_type& startingRowNr, size_type& columnOffset, size_type& nrOfRows,
                                            size_type& nrOfColumns);

    // similar to previous but this time clamping is done by also taking the parameters of a source matrix into account
    void _externalClampSubMatrixSelectionParameters(const Matrix& srcMatrix, size_type& srcStartingRowNr,
                                                    size_type& srcColumnOffset, size_type& startingRowNr,
                                                    size_type& columnOffset, size_type& nrOfRows,
                                                    size_type& nrOfColumns);

    // converts the matrix to a single dimensional array of elements of m_RowCapacity * m_ColumnCapacity size (might
    // include uninitialized elements)
    void* _convertToArray(size_type& nrOfElements);

    // helper functions used for initializing iterators
    template <typename NonDiagIter> NonDiagIter _getForwardNonDiagBeginIterator() const;
    template <typename NonDiagIter> NonDiagIter _getForwardNonDiagEndIterator() const;
    template <typename NonDiagIter> NonDiagIter _getReverseNonDiagBeginIterator() const;

    template <typename NonDiagIter>
    NonDiagIter _getNonDiagIteratorByRowAndColumnNumber(size_type rowNr, size_type columnNr) const;

    template <typename ZIter> ZIter _getReverseEndZIterator() const;
    template <typename ZIter> ZIter _getForwardRowBeginZIterator(size_type rowNr) const;
    template <typename ZIter> ZIter _getReverseRowBeginZIterator(size_type rowNr) const;
    template <typename ZIter> ZIter _getForwardRowEndZIterator(size_type rowNr) const;
    template <typename ZIter> ZIter _getReverseRowEndZIterator(size_type rowNr) const;
    template <typename NIter> NIter _getReverseEndNIterator() const;
    template <typename NIter> NIter _getForwardColumnBeginNIterator(size_type columnNr) const;
    template <typename NIter> NIter _getReverseColumnBeginNIterator(size_type columnNr) const;
    template <typename NIter> NIter _getForwardColumnEndNIterator(size_type columnNr) const;
    template <typename NIter> NIter _getReverseColumnEndNIterator(size_type columnNr) const;
    template <typename DiagIter> DiagIter _getDiagBeginIterator(diff_type diagonalNr) const;
    template <typename DiagIter> DiagIter _getDiagRandomIterator(size_type rowNr, size_type columnNr) const;
    template <typename DIter> DIter _getBeginDIteratorByRowAndColumnNumber(size_type rowNr, size_type columnNr) const;
    template <typename DIter> DIter _getEndDIteratorByDiagNumber(diff_type diagonalNr) const;
    template <typename DIter> DIter _getEndDIteratorByRowAndColumnNumber(size_type rowNr, size_type columnNr) const;

    template <typename DIter>
    DIter _getRandomDIteratorByDiagNumberAndIndex(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    template <typename MIter> MIter _getBeginMIteratorByRowAndColumnNumber(size_type rowNr, size_type columnNr) const;
    template <typename MIter> MIter _getEndMIteratorByDiagNumber(diff_type diagonalNr) const;
    template <typename MIter> MIter _getEndMIteratorByRowAndColumnNumber(size_type rowNr, size_type columnNr) const;

    template <typename MIter>
    MIter _getRandomMIteratorByDiagNumberAndIndex(const std::pair<diff_type, size_type>& diagonalNrAndIndex) const;

    T* m_pAllocPtr; // use only this pointer in _allocMemory()/_deallocMemory() to allocate/de-allocate matrix elements
    T** m_pBaseArrayPtr; // this pointer manages the row pointers array

    size_type m_NrOfRows;
    size_type m_NrOfColumns;
    size_type m_RowCapacity;
    size_type m_ColumnCapacity;
    std::optional<size_type> m_RowCapacityOffset;
    std::optional<size_type> m_ColumnCapacityOffset;
};

export template <MatrixElementType T>
class Matrix<T>::ZIterator final : public Matrix<T>::FullTraverseIterator<ZIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    ZIterator() = default;

    using FullTraverseIterator<ZIterator>::operator<=>;
    using FullTraverseIterator<ZIterator>::operator==;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ZIterator operator+(const ZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ZIterator operator+(diff_type offset, const ZIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ZIterator operator-(const ZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ZIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns, std::optional<size_type> rowNr,
              std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ZIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ZIterator>::_applyArrowOperator;
    using FullTraverseIterator<ZIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ZIterator>::_getMatrixPtr;
    using FullTraverseIterator<ZIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ZIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ZIterator>::_getIndex;
    using FullTraverseIterator<ZIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstZIterator final : public Matrix<T>::FullTraverseIterator<ConstZIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstZIterator() = default;
    ConstZIterator(const ZIterator& zIterator);

    using FullTraverseIterator<ConstZIterator>::operator<=>;
    using FullTraverseIterator<ConstZIterator>::operator==;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstZIterator operator+(const ConstZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstZIterator operator+(diff_type offset, const ConstZIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstZIterator operator-(const ConstZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstZIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ConstZIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ConstZIterator>::_applyArrowOperator;
    using FullTraverseIterator<ConstZIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ConstZIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ConstZIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ConstZIterator>::_getIndex;
    using FullTraverseIterator<ConstZIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ReverseZIterator final : public Matrix<T>::FullTraverseIterator<ReverseZIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    ReverseZIterator() = default;

    using FullTraverseIterator<ReverseZIterator>::operator<=>;
    using FullTraverseIterator<ReverseZIterator>::operator==;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ReverseZIterator operator+(const ReverseZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseZIterator operator+(diff_type offset, const ReverseZIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseZIterator operator-(const ReverseZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ReverseZIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ReverseZIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ReverseZIterator>::_applyArrowOperator;
    using FullTraverseIterator<ReverseZIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ReverseZIterator>::_getMatrixPtr;
    using FullTraverseIterator<ReverseZIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ReverseZIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ReverseZIterator>::_getIndex;
    using FullTraverseIterator<ReverseZIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstReverseZIterator final : public Matrix<T>::FullTraverseIterator<ConstReverseZIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstReverseZIterator() = default;
    ConstReverseZIterator(const ReverseZIterator& zIterator);

    using FullTraverseIterator<ConstReverseZIterator>::operator<=>;
    using FullTraverseIterator<ConstReverseZIterator>::operator==;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstReverseZIterator operator+(const ConstReverseZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseZIterator operator+(diff_type offset, const ConstReverseZIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseZIterator operator-(const ConstReverseZIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstReverseZIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ConstReverseZIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ConstReverseZIterator>::_applyArrowOperator;
    using FullTraverseIterator<ConstReverseZIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ConstReverseZIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ConstReverseZIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ConstReverseZIterator>::_getIndex;
    using FullTraverseIterator<ConstReverseZIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::NIterator final : public Matrix<T>::FullTraverseIterator<NIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    NIterator() = default;

    using FullTraverseIterator<NIterator>::operator<=>;
    using FullTraverseIterator<NIterator>::operator==;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend NIterator operator+(const NIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend NIterator operator+(diff_type offset, const NIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend NIterator operator-(const NIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    NIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns, std::optional<size_type> rowNr,
              std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<NIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<NIterator>::_applyArrowOperator;
    using FullTraverseIterator<NIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<NIterator>::_getMatrixPtr;
    using FullTraverseIterator<NIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<NIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<NIterator>::_getIndex;
    using FullTraverseIterator<NIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstNIterator final : public Matrix<T>::FullTraverseIterator<ConstNIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstNIterator() = default;
    ConstNIterator(const NIterator& zIterator);

    using FullTraverseIterator<ConstNIterator>::operator<=>;
    using FullTraverseIterator<ConstNIterator>::operator==;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstNIterator operator+(const ConstNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstNIterator operator+(diff_type offset, const ConstNIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstNIterator operator-(const ConstNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstNIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ConstNIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ConstNIterator>::_applyArrowOperator;
    using FullTraverseIterator<ConstNIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ConstNIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ConstNIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ConstNIterator>::_getIndex;
    using FullTraverseIterator<ConstNIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ReverseNIterator final : public Matrix<T>::FullTraverseIterator<ReverseNIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    ReverseNIterator() = default;

    using FullTraverseIterator<ReverseNIterator>::operator<=>;
    using FullTraverseIterator<ReverseNIterator>::operator==;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ReverseNIterator operator+(const ReverseNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseNIterator operator+(diff_type offset, const ReverseNIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseNIterator operator-(const ReverseNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ReverseNIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ReverseNIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ReverseNIterator>::_applyArrowOperator;
    using FullTraverseIterator<ReverseNIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ReverseNIterator>::_getMatrixPtr;
    using FullTraverseIterator<ReverseNIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ReverseNIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ReverseNIterator>::_getIndex;
    using FullTraverseIterator<ReverseNIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstReverseNIterator final : public Matrix<T>::FullTraverseIterator<ConstReverseNIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstReverseNIterator() = default;
    ConstReverseNIterator(const ReverseNIterator& zIterator);

    using FullTraverseIterator<ConstReverseNIterator>::operator<=>;
    using FullTraverseIterator<ConstReverseNIterator>::operator==;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstReverseNIterator operator+(const ConstReverseNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseNIterator operator+(diff_type offset, const ConstReverseNIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseNIterator operator-(const ConstReverseNIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstReverseNIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          std::optional<size_type> rowNr, std::optional<size_type> columnNr);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using FullTraverseIterator<ConstReverseNIterator>::_applyAsteriskOperator;
    using FullTraverseIterator<ConstReverseNIterator>::_applyArrowOperator;
    using FullTraverseIterator<ConstReverseNIterator>::_applySquareBracketsOperator;
    using FullTraverseIterator<ConstReverseNIterator>::_getNrOfMatrixRows;
    using FullTraverseIterator<ConstReverseNIterator>::_getNrOfMatrixColumns;
    using FullTraverseIterator<ConstReverseNIterator>::_getIndex;
    using FullTraverseIterator<ConstReverseNIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::DIterator final : public Matrix<T>::PartialDiagIterator<DIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    DIterator() = default;

    using PartialDiagIterator<DIterator>::operator<=>;
    using PartialDiagIterator<DIterator>::operator==;
    using PartialDiagIterator<DIterator>::getDiagonalNr;
    using PartialDiagIterator<DIterator>::getDiagonalIndex;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend DIterator operator+(const DIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend DIterator operator+(diff_type offset, const DIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend DIterator operator-(const DIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    DIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns, std::optional<size_type> rowNr,
              std::optional<size_type> columnNr);
    DIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
              const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<DIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<DIterator>::_applyArrowOperator;
    using PartialDiagIterator<DIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<DIterator>::_getMatrixPtr;
    using PartialDiagIterator<DIterator>::_getDiagonalSize;
    using PartialDiagIterator<DIterator>::_getNrOfMatrixRows;
    using PartialDiagIterator<DIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<DIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstDIterator final : public Matrix<T>::PartialDiagIterator<ConstDIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstDIterator() = default;
    ConstDIterator(const DIterator& dIterator);

    using PartialDiagIterator<ConstDIterator>::operator<=>;
    using PartialDiagIterator<ConstDIterator>::operator==;
    using PartialDiagIterator<ConstDIterator>::getDiagonalNr;
    using PartialDiagIterator<ConstDIterator>::getDiagonalIndex;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstDIterator operator+(const ConstDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstDIterator operator+(diff_type offset, const ConstDIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstDIterator operator-(const ConstDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ConstDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ConstDIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ConstDIterator>::_applyArrowOperator;
    using PartialDiagIterator<ConstDIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ConstDIterator>::_getDiagonalSize;
    using PartialDiagIterator<ConstDIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ReverseDIterator final : public Matrix<T>::PartialDiagIterator<ReverseDIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    ReverseDIterator() = default;

    using PartialDiagIterator<ReverseDIterator>::operator<=>;
    using PartialDiagIterator<ReverseDIterator>::operator==;
    using PartialDiagIterator<ReverseDIterator>::getDiagonalNr;
    using PartialDiagIterator<ReverseDIterator>::getDiagonalIndex;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ReverseDIterator operator+(const ReverseDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseDIterator operator+(diff_type offset, const ReverseDIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseDIterator operator-(const ReverseDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ReverseDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ReverseDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ReverseDIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ReverseDIterator>::_applyArrowOperator;
    using PartialDiagIterator<ReverseDIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ReverseDIterator>::_getMatrixPtr;
    using PartialDiagIterator<ReverseDIterator>::_getDiagonalSize;
    using PartialDiagIterator<ReverseDIterator>::_getNrOfMatrixRows;
    using PartialDiagIterator<ReverseDIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<ReverseDIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstReverseDIterator final : public Matrix<T>::PartialDiagIterator<ConstReverseDIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstReverseDIterator() = default;
    ConstReverseDIterator(const ReverseDIterator& dIterator);

    using PartialDiagIterator<ConstReverseDIterator>::operator<=>;
    using PartialDiagIterator<ConstReverseDIterator>::operator==;
    using PartialDiagIterator<ConstReverseDIterator>::getDiagonalNr;
    using PartialDiagIterator<ConstReverseDIterator>::getDiagonalIndex;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstReverseDIterator operator+(const ConstReverseDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseDIterator operator+(diff_type offset, const ConstReverseDIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseDIterator operator-(const ConstReverseDIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstReverseDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ConstReverseDIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ConstReverseDIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ConstReverseDIterator>::_applyArrowOperator;
    using PartialDiagIterator<ConstReverseDIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ConstReverseDIterator>::_getDiagonalSize;
    using PartialDiagIterator<ConstReverseDIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::MIterator final : public Matrix<T>::PartialDiagIterator<MIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    MIterator() = default;

    using PartialDiagIterator<MIterator>::operator<=>;
    using PartialDiagIterator<MIterator>::operator==;
    using PartialDiagIterator<MIterator>::getDiagonalNr;
    using PartialDiagIterator<MIterator>::getDiagonalIndex;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend MIterator operator+(const MIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend MIterator operator+(diff_type offset, const MIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend MIterator operator-(const MIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    MIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns, std::optional<size_type> rowNr,
              std::optional<size_type> columnNr);
    MIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
              const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<MIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<MIterator>::_applyArrowOperator;
    using PartialDiagIterator<MIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<MIterator>::_getMatrixPtr;
    using PartialDiagIterator<MIterator>::_getDiagonalSize;
    using PartialDiagIterator<MIterator>::_getNrOfMatrixRows;
    using PartialDiagIterator<MIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<MIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstMIterator final : public Matrix<T>::PartialDiagIterator<ConstMIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstMIterator() = default;
    ConstMIterator(const MIterator& dIterator);

    using PartialDiagIterator<ConstMIterator>::operator<=>;
    using PartialDiagIterator<ConstMIterator>::operator==;
    using PartialDiagIterator<ConstMIterator>::getDiagonalNr;
    using PartialDiagIterator<ConstMIterator>::getDiagonalIndex;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstMIterator operator+(const ConstMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstMIterator operator+(diff_type offset, const ConstMIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstMIterator operator-(const ConstMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ConstMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                   const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ConstMIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ConstMIterator>::_applyArrowOperator;
    using PartialDiagIterator<ConstMIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ConstMIterator>::_getDiagonalSize;
    using PartialDiagIterator<ConstMIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<ConstMIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ReverseMIterator final : public Matrix<T>::PartialDiagIterator<ReverseMIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, T&);

    ReverseMIterator() = default;

    using PartialDiagIterator<ReverseMIterator>::operator<=>;
    using PartialDiagIterator<ReverseMIterator>::operator==;
    using PartialDiagIterator<ReverseMIterator>::getDiagonalNr;
    using PartialDiagIterator<ReverseMIterator>::getDiagonalIndex;

    inline T& operator*() const;
    inline T* operator->() const;
    inline T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ReverseMIterator operator+(const ReverseMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseMIterator operator+(diff_type offset, const ReverseMIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ReverseMIterator operator-(const ReverseMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ReverseMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ReverseMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                     const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ReverseMIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ReverseMIterator>::_applyArrowOperator;
    using PartialDiagIterator<ReverseMIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ReverseMIterator>::_getMatrixPtr;
    using PartialDiagIterator<ReverseMIterator>::_getDiagonalSize;
    using PartialDiagIterator<ReverseMIterator>::_getNrOfMatrixRows;
    using PartialDiagIterator<ReverseMIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<ReverseMIterator>::_isEmpty;
};

export template <MatrixElementType T>
class Matrix<T>::ConstReverseMIterator final : public Matrix<T>::PartialDiagIterator<ConstReverseMIterator>
{
public:
    /* Required for being able to return iterators by using the private constructor of the iterator class */
    friend class Matrix<T>;

    ITERATOR_TRAITS(T, diff_type, const T&);

    ConstReverseMIterator() = default;
    ConstReverseMIterator(const ReverseMIterator& dIterator);

    using PartialDiagIterator<ConstReverseMIterator>::operator<=>;
    using PartialDiagIterator<ConstReverseMIterator>::operator==;
    using PartialDiagIterator<ConstReverseMIterator>::getDiagonalNr;
    using PartialDiagIterator<ConstReverseMIterator>::getDiagonalIndex;

    inline const T& operator*() const;
    inline const T* operator->() const;
    inline const T& operator[](diff_type index) const;

    inline std::optional<size_type> getRowNr() const;
    inline std::optional<size_type> getColumnNr() const;

    inline friend ConstReverseMIterator operator+(const ConstReverseMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseMIterator operator+(diff_type offset, const ConstReverseMIterator& it)
    {
        return addOffsetToIterator(it, offset);
    }

    inline friend ConstReverseMIterator operator-(const ConstReverseMIterator& it, diff_type offset)
    {
        return addOffsetToIterator(it, -offset);
    }

private:
    ConstReverseMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          std::optional<size_type> rowNr, std::optional<size_type> columnNr);
    ConstReverseMIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                          const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

    inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const;
    inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const;

    using PartialDiagIterator<ConstReverseMIterator>::_applyAsteriskOperator;
    using PartialDiagIterator<ConstReverseMIterator>::_applyArrowOperator;
    using PartialDiagIterator<ConstReverseMIterator>::_applySquareBracketsOperator;
    using PartialDiagIterator<ConstReverseMIterator>::_getDiagonalSize;
    using PartialDiagIterator<ConstReverseMIterator>::_getNrOfMatrixColumns;
    using PartialDiagIterator<ConstReverseMIterator>::_isEmpty;
};
