module;

#include <cstdint>
#include <optional>
#include <vector>

#include "../Utils/iteratordeclarations.h"

export module matrix:matrix_header;

#ifndef USE_SMALL_DIMENSIONS
export using matrix_size_t = uint32_t;
export using matrix_diff_t = int64_t;
#else
export using matrix_size_t = uint8_t;
export using matrix_diff_t = int16_t;
#endif

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

    class ZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ZIterator, T, diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ZIterator, T, size_type);
    };

    class ConstZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstZIterator, T, diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstZIterator(const ZIterator& zIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstZIterator, T, size_type);
    };

    class ReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, T, diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseZIterator, T, size_type);
    };

    class ConstReverseZIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, T, diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstReverseZIterator(const ReverseZIterator& reverseZIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseZIterator, T, size_type);
    };

    class NIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(NIterator, T, diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(NIterator, T, size_type);
    };

    class ConstNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstNIterator, T, diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstNIterator(const NIterator& nIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstNIterator, T, size_type);
    };

    class ReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, T, diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseNIterator, T, size_type);
    };

    class ConstReverseNIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, T, diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstReverseNIterator(const ReverseNIterator& reverseNIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseNIterator, T, size_type);
    };

    class DIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(DIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(DIterator, T, diff_type, size_type);
    };

    class ConstDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstDIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstDIterator(const DIterator& dIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstDIterator, T, diff_type, size_type);
    };

    class ReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseDIterator, T, diff_type, size_type);
    };

    class ConstReverseDIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstReverseDIterator(const ReverseDIterator& reverseDIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseDIterator, T, diff_type, size_type);
    };

    class MIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(MIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(MIterator, T, diff_type, size_type);

        size_type m_NrOfMatrixColumns; // number of matrix columns is required for mirrored iterators because the origin
                                       // (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstMIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstMIterator(const MIterator& mIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstMIterator, T, diff_type, size_type);

        size_type m_NrOfMatrixColumns; // number of matrix columns is required for mirrored iterators because the origin
                                       // (diagonal 0) does no longer pass through element (0, 0)
    };

    class ReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ReverseMIterator, T, diff_type, size_type);

        size_type m_NrOfMatrixColumns; // number of matrix columns is required for mirrored iterators because the origin
                                       // (diagonal 0) does no longer pass through element (0, 0)
    };

    class ConstReverseMIterator
    {
    public:
        COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, T, diff_type, size_type);
        COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(diff_type, size_type);
        COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(T, diff_type);

        ConstReverseMIterator(const ReverseMIterator& reverseMIterator);

    private:
        COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(T);
        COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(ConstReverseMIterator, T, diff_type, size_type);

        size_type m_NrOfMatrixColumns; // number of matrix columns is required for mirrored iterators because the origin
                                       // (diagonal 0) does no longer pass through element (0, 0)
    };

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

    ZIterator zBegin();
    ZIterator zEnd();
    ZIterator zRowBegin(size_type rowNr);
    ZIterator zRowEnd(size_type rowNr);
    ZIterator getZIterator(size_type rowNr, size_type columnNr);

    ConstZIterator constZBegin() const;
    ConstZIterator constZEnd() const;
    ConstZIterator constZRowBegin(size_type rowNr) const;
    ConstZIterator constZRowEnd(size_type rowNr) const;
    ConstZIterator getConstZIterator(size_type rowNr, size_type columnNr) const;

    ReverseZIterator reverseZBegin();
    ReverseZIterator reverseZEnd();
    ReverseZIterator reverseZRowBegin(size_type rowNr);
    ReverseZIterator reverseZRowEnd(size_type rowNr);
    ReverseZIterator getReverseZIterator(size_type rowNr, size_type columnNr);

    ConstReverseZIterator constReverseZBegin() const;
    ConstReverseZIterator constReverseZEnd() const;
    ConstReverseZIterator constReverseZRowBegin(size_type rowNr) const;
    ConstReverseZIterator constReverseZRowEnd(size_type rowNr) const;
    ConstReverseZIterator getConstReverseZIterator(size_type rowNr, size_type columnNr) const;

    NIterator nBegin();
    NIterator nEnd();
    NIterator nColumnBegin(size_type columnNr);
    NIterator nColumnEnd(size_type columnNr);
    NIterator getNIterator(size_type rowNr, size_type columnNr);

    ConstNIterator constNBegin() const;
    ConstNIterator constNEnd() const;
    ConstNIterator constNColumnBegin(size_type columnNr) const;
    ConstNIterator constNColumnEnd(size_type columnNr) const;
    ConstNIterator getConstNIterator(size_type rowNr, size_type columnNr) const;

    ReverseNIterator reverseNBegin();
    ReverseNIterator reverseNEnd();
    ReverseNIterator reverseNColumnBegin(size_type columnNr);
    ReverseNIterator reverseNColumnEnd(size_type columnNr);
    ReverseNIterator getReverseNIterator(size_type rowNr, size_type columnNr);

    ConstReverseNIterator constReverseNBegin() const;
    ConstReverseNIterator constReverseNEnd() const;
    ConstReverseNIterator constReverseNColumnBegin(size_type columnNr) const;
    ConstReverseNIterator constReverseNColumnEnd(size_type columnNr) const;
    ConstReverseNIterator getConstReverseNIterator(size_type rowNr, size_type columnNr) const;

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

    T* m_pAllocPtr; // use only this pointer in _allocMemory()/_deallocMemory() to allocate/de-allocate matrix elements
    T** m_pBaseArrayPtr; // this pointer manages the row pointers array

    size_type m_NrOfRows;
    size_type m_NrOfColumns;
    size_type m_RowCapacity;
    size_type m_ColumnCapacity;
    std::optional<size_type> m_RowCapacityOffset;
    std::optional<size_type> m_ColumnCapacityOffset;
};