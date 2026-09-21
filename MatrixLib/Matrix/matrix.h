#pragma once

#include <algorithm>
#include <cassert>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

#include "matrixdimensions.h"

#include "../Utils/errorhandling.h"
#include "../Utils/iteratorgetters.h"
#include "../Utils/iteratorutilityfunctions.h"

using matrix_size_t = Matr::size_t;
using matrix_diff_t = Matr::diff_t;

constexpr matrix_size_t maxAllowedDimension()
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

template <MatrixElementType T> class Matrix
{
public:
    using size_type = matrix_size_t;
    using diff_type = matrix_diff_t;
    using dimensions_t = std::pair<size_type, size_type>;

    template <typename IterType> class FullTraverseIterator
    {
    public:
        IterType& operator++();
        IterType operator++(int unused);
        IterType& operator--();
        IterType operator--(int unused);

        IterType& operator+=(diff_type offset);

        inline IterType& operator-=(diff_type offset)
        {
            return *this += -offset;
        };

        diff_type operator-(const IterType& it) const;

        std::strong_ordering operator<=>(const IterType& it) const;
        bool operator==(const IterType& it) const;

    protected:
        /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any
         * empty matrix */
        FullTraverseIterator();

        FullTraverseIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                             std::optional<diff_type> index);

        T& _applyAsteriskOperator() const;
        T* _applyArrowOperator() const;
        T& _applySquareBracketsOperator(diff_type index) const;

        inline T** _getMatrixPtr() const
        {
            return m_pMatrixPtr;
        }

        inline size_type _getNrOfMatrixRows() const
        {
            return m_NrOfMatrixRows;
        }

        inline size_type _getNrOfMatrixColumns() const
        {
            return m_NrOfMatrixColumns;
        }

        inline std::optional<diff_type> _getIndex() const
        {
            return m_Index;
        }

        bool _isEmpty() const;

    private:
        void _increment();
        void _decrement();

        inline std::optional<size_type> _getRowNr() const
        {
            return static_cast<const IterType*>(this)->getRowNr();
        }

        inline std::optional<size_type> _getColumnNr() const
        {
            return static_cast<const IterType*>(this)->getColumnNr();
        }

        T** m_pMatrixPtr;
        size_type m_NrOfMatrixRows;
        size_type m_NrOfMatrixColumns;
        std::optional<diff_type> m_Index; /* relative index within begin - end iterators range */
    };

    template <typename IterType> class PartialDiagIterator
    {
    public:
        IterType& operator++();
        IterType operator++(int unused);
        IterType& operator--();
        IterType operator--(int unused);

        IterType& operator+=(diff_type offset);

        inline IterType& operator-=(diff_type offset)
        {
            return *this += -offset;
        };

        diff_type operator-(const IterType& it) const;

        std::strong_ordering operator<=>(const IterType& it) const;
        bool operator==(const IterType& it) const;

        inline diff_type getDiagonalNr() const
        {
            return m_DiagonalNr;
        }

        inline std::optional<size_type> getDiagonalIndex() const
        {
            return m_DiagonalIndex;
        }

    protected:
        /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any
         * empty matrix */
        PartialDiagIterator();
        PartialDiagIterator(T** pMatrixPtr, size_type nrOfMatrixRows, size_type nrOfMatrixColumns,
                            const std::pair<diff_type, std::optional<size_type>>& diagonalNrAndIndex);

        T& _applyAsteriskOperator() const;
        T* _applyArrowOperator() const;
        T& _applySquareBracketsOperator(diff_type index) const;

        inline T** _getMatrixPtr() const
        {
            return m_pMatrixPtr;
        }

        inline size_type _getDiagonalSize() const
        {
            return m_DiagonalSize;
        }

        inline size_type _getNrOfMatrixRows() const
        {
            return m_NrOfMatrixRows;
        }

        inline size_type _getNrOfMatrixColumns() const
        {
            return m_NrOfMatrixColumns;
        }

        bool _isEmpty() const;

    private:
        void _increment();
        void _decrement();

        inline std::optional<size_type> _getRowNr() const
        {
            return static_cast<const IterType*>(this)->getRowNr();
        }

        inline std::optional<size_type> _getColumnNr() const
        {
            return static_cast<const IterType*>(this)->getColumnNr();
        }

        T** m_pMatrixPtr;
        std::optional<size_type> m_DiagonalIndex; /* relative index within diagonal */
        diff_type m_DiagonalNr;                   /* index of the diagonal within matrix */
        size_type m_DiagonalSize;                 /* number of elements contained within diagonal */
        size_type m_NrOfMatrixRows;               /* only used for initialization of const iterators */
        size_type m_NrOfMatrixColumns;            /* only used by mirrored diagonal iterators */
    };

    class ZIterator final : public FullTraverseIterator<ZIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, T&);

        ZIterator() = default;

        using FullTraverseIterator<ZIterator>::operator<=>;
        using FullTraverseIterator<ZIterator>::operator==;

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardZIteratorRowNr(_getIndex(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardZIteratorColumnNr(_getIndex(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardZIteratorRowNr(index, _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardZIteratorColumnNr(index, _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ZIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ZIterator>::_applyArrowOperator;
        using FullTraverseIterator<ZIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ZIterator>::_getMatrixPtr;
        using FullTraverseIterator<ZIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ZIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ZIterator>::_getIndex;
        using FullTraverseIterator<ZIterator>::_isEmpty;
    };

    class ConstZIterator final : public FullTraverseIterator<ConstZIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, const T&);

        ConstZIterator() = default;
        ConstZIterator(const ZIterator& zIterator);

        using FullTraverseIterator<ConstZIterator>::operator<=>;
        using FullTraverseIterator<ConstZIterator>::operator==;

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardZIteratorRowNr(_getIndex(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardZIteratorColumnNr(_getIndex(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardZIteratorRowNr(index, _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardZIteratorColumnNr(index, _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ConstZIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ConstZIterator>::_applyArrowOperator;
        using FullTraverseIterator<ConstZIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ConstZIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ConstZIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ConstZIterator>::_getIndex;
        using FullTraverseIterator<ConstZIterator>::_isEmpty;
    };

    class ReverseZIterator final : public FullTraverseIterator<ReverseZIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, T&);

        ReverseZIterator() = default;

        using FullTraverseIterator<ReverseZIterator>::operator<=>;
        using FullTraverseIterator<ReverseZIterator>::operator==;

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseZIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseZIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseZIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseZIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ReverseZIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ReverseZIterator>::_applyArrowOperator;
        using FullTraverseIterator<ReverseZIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ReverseZIterator>::_getMatrixPtr;
        using FullTraverseIterator<ReverseZIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ReverseZIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ReverseZIterator>::_getIndex;
        using FullTraverseIterator<ReverseZIterator>::_isEmpty;
    };

    class ConstReverseZIterator final : public FullTraverseIterator<ConstReverseZIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, const T&);

        ConstReverseZIterator() = default;
        ConstReverseZIterator(const ReverseZIterator& zIterator);

        using FullTraverseIterator<ConstReverseZIterator>::operator<=>;
        using FullTraverseIterator<ConstReverseZIterator>::operator==;

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseZIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseZIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseZIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseZIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ConstReverseZIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ConstReverseZIterator>::_applyArrowOperator;
        using FullTraverseIterator<ConstReverseZIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ConstReverseZIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ConstReverseZIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ConstReverseZIterator>::_getIndex;
        using FullTraverseIterator<ConstReverseZIterator>::_isEmpty;
    };

    class NIterator final : public FullTraverseIterator<NIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, T&);

        NIterator() = default;

        using FullTraverseIterator<NIterator>::operator<=>;
        using FullTraverseIterator<NIterator>::operator==;

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardNIteratorRowNr(_getIndex(), _getNrOfMatrixRows());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardNIteratorRowNr(index, _getNrOfMatrixRows());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardNIteratorColumnNr(index, _getNrOfMatrixRows());
        }

        using FullTraverseIterator<NIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<NIterator>::_applyArrowOperator;
        using FullTraverseIterator<NIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<NIterator>::_getMatrixPtr;
        using FullTraverseIterator<NIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<NIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<NIterator>::_getIndex;
        using FullTraverseIterator<NIterator>::_isEmpty;
    };

    class ConstNIterator final : public FullTraverseIterator<ConstNIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, const T&);

        ConstNIterator() = default;
        ConstNIterator(const NIterator& zIterator);

        using FullTraverseIterator<ConstNIterator>::operator<=>;
        using FullTraverseIterator<ConstNIterator>::operator==;

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardNIteratorRowNr(_getIndex(), _getNrOfMatrixRows());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardNIteratorRowNr(index, _getNrOfMatrixRows());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardNIteratorColumnNr(index, _getNrOfMatrixRows());
        }

        using FullTraverseIterator<ConstNIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ConstNIterator>::_applyArrowOperator;
        using FullTraverseIterator<ConstNIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ConstNIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ConstNIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ConstNIterator>::_getIndex;
        using FullTraverseIterator<ConstNIterator>::_isEmpty;
    };

    class ReverseNIterator final : public FullTraverseIterator<ReverseNIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, T&);

        ReverseNIterator() = default;

        using FullTraverseIterator<ReverseNIterator>::operator<=>;
        using FullTraverseIterator<ReverseNIterator>::operator==;

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseNIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseNIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseNIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ReverseNIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ReverseNIterator>::_applyArrowOperator;
        using FullTraverseIterator<ReverseNIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ReverseNIterator>::_getMatrixPtr;
        using FullTraverseIterator<ReverseNIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ReverseNIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ReverseNIterator>::_getIndex;
        using FullTraverseIterator<ReverseNIterator>::_isEmpty;
    };

    class ConstReverseNIterator final : public FullTraverseIterator<ConstReverseNIterator>
    {
    public:
        /* Required for being able to return iterators by using the private constructor of the iterator class */
        friend class Matrix<T>;

        ITERATOR_TRAITS(T, diff_type, const T&);

        ConstReverseNIterator() = default;
        ConstReverseNIterator(const ReverseNIterator& zIterator);

        using FullTraverseIterator<ConstReverseNIterator>::operator<=>;
        using FullTraverseIterator<ConstReverseNIterator>::operator==;

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseNIteratorRowNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseNIteratorColumnNr(_getIndex(), _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseNIteratorRowNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseNIteratorColumnNr(index, _getNrOfMatrixRows(), _getNrOfMatrixColumns());
        }

        using FullTraverseIterator<ConstReverseNIterator>::_applyAsteriskOperator;
        using FullTraverseIterator<ConstReverseNIterator>::_applyArrowOperator;
        using FullTraverseIterator<ConstReverseNIterator>::_applySquareBracketsOperator;
        using FullTraverseIterator<ConstReverseNIterator>::_getNrOfMatrixRows;
        using FullTraverseIterator<ConstReverseNIterator>::_getNrOfMatrixColumns;
        using FullTraverseIterator<ConstReverseNIterator>::_getIndex;
        using FullTraverseIterator<ConstReverseNIterator>::_isEmpty;
    };

    class DIterator : public PartialDiagIterator<DIterator>
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

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardDIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardDIteratorRowNr(getDiagonalNr(), index);
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardDIteratorColumnNr(getDiagonalNr(), index);
        }

        using PartialDiagIterator<DIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<DIterator>::_applyArrowOperator;
        using PartialDiagIterator<DIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<DIterator>::_getMatrixPtr;
        using PartialDiagIterator<DIterator>::_getDiagonalSize;
        using PartialDiagIterator<DIterator>::_getNrOfMatrixRows;
        using PartialDiagIterator<DIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<DIterator>::_isEmpty;
    };

    class ConstDIterator : public PartialDiagIterator<ConstDIterator>
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

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardDIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardDIteratorRowNr(getDiagonalNr(), index);
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardDIteratorColumnNr(getDiagonalNr(), index);
        }

        using PartialDiagIterator<ConstDIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ConstDIterator>::_applyArrowOperator;
        using PartialDiagIterator<ConstDIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ConstDIterator>::_getDiagonalSize;
        using PartialDiagIterator<ConstDIterator>::_isEmpty;
    };

    class ReverseDIterator : public PartialDiagIterator<ReverseDIterator>
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

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseDIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseDIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseDIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        using PartialDiagIterator<ReverseDIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ReverseDIterator>::_applyArrowOperator;
        using PartialDiagIterator<ReverseDIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ReverseDIterator>::_getMatrixPtr;
        using PartialDiagIterator<ReverseDIterator>::_getDiagonalSize;
        using PartialDiagIterator<ReverseDIterator>::_getNrOfMatrixRows;
        using PartialDiagIterator<ReverseDIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<ReverseDIterator>::_isEmpty;
    };

    class ConstReverseDIterator : public PartialDiagIterator<ConstReverseDIterator>
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

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseDIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseDIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseDIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseDIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        using PartialDiagIterator<ConstReverseDIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ConstReverseDIterator>::_applyArrowOperator;
        using PartialDiagIterator<ConstReverseDIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ConstReverseDIterator>::_getDiagonalSize;
        using PartialDiagIterator<ConstReverseDIterator>::_isEmpty;
    };

    class MIterator : public PartialDiagIterator<MIterator>
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

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardMIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardMIteratorRowNr(getDiagonalNr(), index);
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardMIteratorColumnNr(getDiagonalNr(), index, _getNrOfMatrixColumns());
        }

        using PartialDiagIterator<MIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<MIterator>::_applyArrowOperator;
        using PartialDiagIterator<MIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<MIterator>::_getMatrixPtr;
        using PartialDiagIterator<MIterator>::_getDiagonalSize;
        using PartialDiagIterator<MIterator>::_getNrOfMatrixRows;
        using PartialDiagIterator<MIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<MIterator>::_isEmpty;
    };

    class ConstMIterator : public PartialDiagIterator<ConstMIterator>
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

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeForwardMIteratorRowNr(getDiagonalNr(), getDiagonalIndex());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeForwardMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardMIteratorRowNr(getDiagonalNr(), index);
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeForwardMIteratorColumnNr(getDiagonalNr(), index, _getNrOfMatrixColumns());
        }

        using PartialDiagIterator<ConstMIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ConstMIterator>::_applyArrowOperator;
        using PartialDiagIterator<ConstMIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ConstMIterator>::_getDiagonalSize;
        using PartialDiagIterator<ConstMIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<ConstMIterator>::_isEmpty;
    };

    class ReverseMIterator : public PartialDiagIterator<ReverseMIterator>
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

        inline T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseMIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize(),
                                                   _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseMIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseMIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize(), _getNrOfMatrixColumns());
        }

        using PartialDiagIterator<ReverseMIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ReverseMIterator>::_applyArrowOperator;
        using PartialDiagIterator<ReverseMIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ReverseMIterator>::_getMatrixPtr;
        using PartialDiagIterator<ReverseMIterator>::_getDiagonalSize;
        using PartialDiagIterator<ReverseMIterator>::_getNrOfMatrixRows;
        using PartialDiagIterator<ReverseMIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<ReverseMIterator>::_isEmpty;
    };

    class ConstReverseMIterator : public PartialDiagIterator<ConstReverseMIterator>
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

        inline const T& operator*() const
        {
            return _applyAsteriskOperator();
        }

        inline const T* operator->() const
        {
            return _applyArrowOperator();
        }

        inline const T& operator[](diff_type index) const
        {
            return _applySquareBracketsOperator(index);
        }

        inline std::optional<size_type> getRowNr() const
        {
            return computeReverseMIteratorRowNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize());
        }

        inline std::optional<size_type> getColumnNr() const
        {
            return computeReverseMIteratorColumnNr(getDiagonalNr(), getDiagonalIndex(), _getDiagonalSize(),
                                                   _getNrOfMatrixColumns());
        }

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

        inline std::optional<size_type> _rowNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseMIteratorRowNr(getDiagonalNr(), index, _getDiagonalSize());
        }

        inline std::optional<size_type> _columnNrFromIndex(std::optional<diff_type> index) const
        {
            return computeReverseMIteratorColumnNr(getDiagonalNr(), index, _getDiagonalSize(), _getNrOfMatrixColumns());
        }

        using PartialDiagIterator<ConstReverseMIterator>::_applyAsteriskOperator;
        using PartialDiagIterator<ConstReverseMIterator>::_applyArrowOperator;
        using PartialDiagIterator<ConstReverseMIterator>::_applySquareBracketsOperator;
        using PartialDiagIterator<ConstReverseMIterator>::_getDiagonalSize;
        using PartialDiagIterator<ConstReverseMIterator>::_getNrOfMatrixColumns;
        using PartialDiagIterator<ConstReverseMIterator>::_isEmpty;
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

// Base FullTraverseIterator class to be used for implementing (Reverse)Z/NIterator classes

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::FullTraverseIterator<IterType>::FullTraverseIterator()
    : m_pMatrixPtr{nullptr}
    , m_NrOfMatrixRows{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::FullTraverseIterator<IterType>::FullTraverseIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                                Matrix<T>::size_type nrOfMatrixColumns,
                                                                std::optional<Matrix<T>::diff_type> index)
{
    bool nonEmptyIteratorConstructed = false;

    if (pMatrixPtr)
    {
        if (nrOfMatrixRows > size_type{0} && nrOfMatrixColumns > size_type{0} && index.has_value() &&
            index <= static_cast<diff_type>(static_cast<diff_type>(nrOfMatrixRows) *
                                            static_cast<diff_type>(nrOfMatrixColumns)))
        {
            m_pMatrixPtr = pMatrixPtr;
            m_NrOfMatrixRows = nrOfMatrixRows;
            m_NrOfMatrixColumns = nrOfMatrixColumns;
            m_Index = index;
            nonEmptyIteratorConstructed = true;
        }
        else
        {
            assert(false);
        }
    }

    if (!nonEmptyIteratorConstructed)
    {
        m_pMatrixPtr = nullptr;
        m_NrOfMatrixRows = size_type{0};
        m_NrOfMatrixColumns = size_type{0};
    }
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator++()
{
    _increment();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::FullTraverseIterator<IterType>::operator++(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _increment();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator--()
{
    _decrement();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::FullTraverseIterator<IterType>::operator--(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _decrement();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::FullTraverseIterator<IterType>::operator+=(Matrix<T>::diff_type offset)
{
    if (!_isEmpty())
    {
        const diff_type c_ResultingIndex{offset < diff_type{0} && std::abs(offset) > *m_Index
                                             ? diff_type{0}
                                             : static_cast<diff_type>(*m_Index + offset)};
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) *
                                                            static_cast<diff_type>(m_NrOfMatrixColumns))};

        m_Index = std::min<diff_type>(c_ResultingIndex, c_UpperBound);
    }

    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
typename Matrix<T>::diff_type Matrix<T>::FullTraverseIterator<IterType>::operator-(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);
    return !_isEmpty() ? *m_Index - *it.m_Index : diff_type{0};
}

template <MatrixElementType T>
template <typename IterType>
std::strong_ordering Matrix<T>::FullTraverseIterator<IterType>::operator<=>(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    /* both iterators are either empty or not */
    return !_isEmpty() ? *m_Index <=> *it.m_Index : std::strong_ordering::equal;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::FullTraverseIterator<IterType>::operator==(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_NrOfMatrixRows != it.m_NrOfMatrixRows ||
                              m_NrOfMatrixColumns != it.m_NrOfMatrixColumns,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return m_Index == it.m_Index;
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::FullTraverseIterator<IterType>::_applyAsteriskOperator() const
{
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) * static_cast<diff_type>(m_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(_isEmpty() || m_Index == c_UpperBound,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return m_pMatrixPtr[*_getRowNr()][*_getColumnNr()];
}

template <MatrixElementType T>
template <typename IterType>
T* Matrix<T>::FullTraverseIterator<IterType>::_applyArrowOperator() const
{
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) * static_cast<diff_type>(m_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(_isEmpty() || m_Index == c_UpperBound,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);
    return (m_pMatrixPtr[*_getRowNr()] + *_getColumnNr());
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::FullTraverseIterator<IterType>::_applySquareBracketsOperator(diff_type index) const
{
    const std::optional<diff_type> c_Index{_getIndex()};

    /* The iterator index should not be std::nullopt if the matrix is not empty */
    CHECK_ERROR_CONDITION(_isEmpty() || (index < diff_type{0} && std::abs(index) > *c_Index),
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_NrOfMatrixRows{_getNrOfMatrixRows()};
    const size_type c_NrOfMatrixColumns{_getNrOfMatrixColumns()};
    const diff_type c_ResultingIndex{static_cast<diff_type>(*c_Index + index)};
    const diff_type c_UpperBound{
        static_cast<diff_type>(static_cast<diff_type>(c_NrOfMatrixRows) * static_cast<diff_type>(c_NrOfMatrixColumns))};

    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound,
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const std::optional<size_type> c_RowNr{static_cast<const IterType*>(this)->_rowNrFromIndex(c_ResultingIndex)};
    const std::optional<size_type> c_ColumnNr{static_cast<const IterType*>(this)->_columnNrFromIndex(c_ResultingIndex)};

    assert(c_RowNr && c_ColumnNr);

    return m_pMatrixPtr[*c_RowNr][*c_ColumnNr];
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::FullTraverseIterator<IterType>::_isEmpty() const
{
    if (m_pMatrixPtr)
    {
        assert(m_NrOfMatrixRows > size_type{0} && m_NrOfMatrixColumns > size_type{0} && m_Index.has_value());
    }
    else
    {
        assert(size_type{0} == m_NrOfMatrixRows && size_type{0} == m_NrOfMatrixColumns && !m_Index.has_value());
    }

    return !m_pMatrixPtr;
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::FullTraverseIterator<IterType>::_increment()
{
    if (!_isEmpty())
    {
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(m_NrOfMatrixRows) *
                                                            static_cast<diff_type>(m_NrOfMatrixColumns))};
        if (m_Index < c_UpperBound)
        {
            m_Index = *m_Index + diff_type{1};
        }
    }
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::FullTraverseIterator<IterType>::_decrement()
{
    if (!_isEmpty() && m_Index > diff_type{0})
    {
        m_Index = *m_Index - diff_type{1};
    }
}

// Base PartialDiagIterator class to be used for implementing (Reverse)D/MIterator classes

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::PartialDiagIterator<IterType>::PartialDiagIterator()
    : m_pMatrixPtr{nullptr}
    , m_DiagonalNr{0}
    , m_DiagonalSize{0}
    , m_NrOfMatrixColumns{0}
{
}

template <MatrixElementType T>
template <typename IterType>
Matrix<T>::PartialDiagIterator<IterType>::PartialDiagIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    bool nonEmptyIteratorConstructed = false;

    if (pMatrixPtr)
    {
        std::optional<size_type> resultingDiagonalIndex;
        size_type resultingDiagonalSize{0};

        if (nrOfMatrixRows > size_type{0} && nrOfMatrixColumns > size_type{0} && diagonalIndex.has_value())
        {
            const diff_type c_MinDiagonalNr{
                static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(nrOfMatrixRows))};
            const diff_type c_MaxDiagonalNr{
                static_cast<diff_type>(static_cast<diff_type>(nrOfMatrixColumns) - diff_type{1})};

            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr)
            {
                resultingDiagonalSize =
                    diagonalNr < diff_type{0}
                        ? std::min<size_type>(nrOfMatrixRows - static_cast<size_type>(-diagonalNr), nrOfMatrixColumns)
                        : std::min<size_type>(nrOfMatrixColumns - static_cast<size_type>(diagonalNr), nrOfMatrixRows);

                if (diagonalIndex <= resultingDiagonalSize)
                {
                    resultingDiagonalIndex = diagonalIndex;
                }
            }
        }

        if (resultingDiagonalIndex.has_value())
        {
            m_pMatrixPtr = pMatrixPtr;
            m_DiagonalNr = diagonalNr;
            m_DiagonalIndex = resultingDiagonalIndex;
            m_DiagonalSize = resultingDiagonalSize;
            m_NrOfMatrixRows = nrOfMatrixRows;
            m_NrOfMatrixColumns = nrOfMatrixColumns;
            nonEmptyIteratorConstructed = true;
        }
        else
        {
            assert(false);
        }
    }

    if (!nonEmptyIteratorConstructed)
    {
        m_pMatrixPtr = nullptr;
        m_DiagonalNr = diff_type{0};
        m_DiagonalSize = size_type{0};
        m_NrOfMatrixRows = size_type{0};
        m_NrOfMatrixColumns = size_type{0};
    }
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator++()
{
    _increment();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::PartialDiagIterator<IterType>::operator++(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _increment();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator--()
{
    _decrement();
    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
IterType Matrix<T>::PartialDiagIterator<IterType>::operator--(int unused)
{
    (void)unused;
    IterType iterator{*static_cast<IterType*>(this)};

    _decrement();

    return iterator;
}

template <MatrixElementType T>
template <typename IterType>
IterType& Matrix<T>::PartialDiagIterator<IterType>::operator+=(Matrix<T>::diff_type offset)
{
    const size_type c_ResultingIndex{
        static_cast<size_type>((offset < diff_type{0} && static_cast<size_type>(-offset) > m_DiagonalIndex)
                                   ? size_type{0}
                                   : static_cast<size_type>(static_cast<diff_type>(*m_DiagonalIndex) + offset))};
    m_DiagonalIndex = std::min(c_ResultingIndex, m_DiagonalSize);

    return *static_cast<IterType*>(this);
}

template <MatrixElementType T>
template <typename IterType>
typename Matrix<T>::diff_type Matrix<T>::PartialDiagIterator<IterType>::operator-(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return !_isEmpty() ? (static_cast<diff_type>(*m_DiagonalIndex) - static_cast<diff_type>(*it.m_DiagonalIndex))
                       : diff_type{0};
}

template <MatrixElementType T>
template <typename IterType>
std::strong_ordering Matrix<T>::PartialDiagIterator<IterType>::operator<=>(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return !_isEmpty() ? *m_DiagonalIndex <=> *it.m_DiagonalIndex : std::strong_ordering::equal;
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::PartialDiagIterator<IterType>::operator==(const IterType& it) const
{
    CHECK_ERROR_CONDITION(m_pMatrixPtr != it.m_pMatrixPtr || m_DiagonalSize != it.m_DiagonalSize ||
                              m_DiagonalNr != it.m_DiagonalNr,
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]);

    return _isEmpty() || m_DiagonalIndex == it.m_DiagonalIndex;
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::PartialDiagIterator<IterType>::_applyAsteriskOperator() const
{
    CHECK_ERROR_CONDITION(_isEmpty() || m_DiagonalIndex == m_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    return m_pMatrixPtr[*_getRowNr()][*_getColumnNr()];
}

template <MatrixElementType T>
template <typename IterType>
T* Matrix<T>::PartialDiagIterator<IterType>::_applyArrowOperator() const
{
    CHECK_ERROR_CONDITION(_isEmpty() || m_DiagonalIndex == m_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]);

    return m_pMatrixPtr[*_getRowNr()] + *_getColumnNr();
}

template <MatrixElementType T>
template <typename IterType>
T& Matrix<T>::PartialDiagIterator<IterType>::_applySquareBracketsOperator(Matrix<T>::diff_type index) const
{
    const std::optional<size_type> c_DiagonalIndex{getDiagonalIndex()};

    CHECK_ERROR_CONDITION(_isEmpty() ||
                              (index < diff_type{0} && static_cast<size_type>(std::abs(index)) > c_DiagonalIndex),
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*c_DiagonalIndex) + index)};
    const size_type c_DiagonalSize{_getDiagonalSize()};

    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= c_DiagonalSize,
                          Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]);

    const diff_type c_DiagonalNr{getDiagonalNr()};

    const std::optional<size_type> c_RowNr{
        static_cast<const IterType*>(this)->_rowNrFromIndex(c_ResultingDiagonalIndex)};
    const std::optional<size_type> c_ColumnNr{
        static_cast<const IterType*>(this)->_columnNrFromIndex(c_ResultingDiagonalIndex)};

    assert(c_RowNr && c_ColumnNr);

    return m_pMatrixPtr[*c_RowNr][*c_ColumnNr];
}

template <MatrixElementType T>
template <typename IterType>
bool Matrix<T>::PartialDiagIterator<IterType>::_isEmpty() const
{
    if (m_pMatrixPtr)
    {
        assert(m_DiagonalSize > size_type{0} && m_DiagonalIndex.has_value() && m_NrOfMatrixColumns > size_type{0});
    }
    else
    {
        assert(diff_type{0} == m_DiagonalNr && size_type{0} == m_DiagonalSize && !m_DiagonalIndex.has_value() &&
               size_type{0} == m_NrOfMatrixColumns);
    }

    return !m_pMatrixPtr;
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::PartialDiagIterator<IterType>::_increment()
{
    if (!_isEmpty() && m_DiagonalIndex < m_DiagonalSize)
    {
        m_DiagonalIndex = *m_DiagonalIndex + size_type{1};
    }
}

template <MatrixElementType T> template <typename IterType> void Matrix<T>::PartialDiagIterator<IterType>::_decrement()
{
    if (!_isEmpty() && m_DiagonalIndex > size_type{0})
    {
        m_DiagonalIndex = *m_DiagonalIndex - size_type{1};
    }
}

// 1) ZIterator - iterates within matrix from [0][0] to the end row by row

template <MatrixElementType T>
Matrix<T>::ZIterator::ZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

// 2) ConstZIterator

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(const ZIterator& zIterator)
    : FullTraverseIterator<ConstZIterator>{
          zIterator._getMatrixPtr(), zIterator._getNrOfMatrixRows(), zIterator._getNrOfMatrixColumns(),
          computeForwardNonDiagIteratorIndex(zIterator._getNrOfMatrixRows(), zIterator._getNrOfMatrixColumns(),
                                             zIterator.getRowNr(), zIterator.getColumnNr())}
{
}

template <MatrixElementType T>
Matrix<T>::ConstZIterator::ConstZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

// 3) ReverseZIterator - iterates within matrix from end to [0][0] row by row (in reverse direction comparing to
// ZIterator)

template <MatrixElementType T>
Matrix<T>::ReverseZIterator::ReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ReverseZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

// 4) ConstReverseZIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(const ReverseZIterator& reverseZIterator)
    : FullTraverseIterator<ConstReverseZIterator>{
          reverseZIterator._getMatrixPtr(), reverseZIterator._getNrOfMatrixRows(),
          reverseZIterator._getNrOfMatrixColumns(),
          computeReverseNonDiagIteratorIndex(reverseZIterator._getNrOfMatrixRows(),
                                             reverseZIterator._getNrOfMatrixColumns(), reverseZIterator.getRowNr(),
                                             reverseZIterator.getColumnNr())}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseZIterator::ConstReverseZIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstReverseZIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

// 5) NIterator - iterates within matrix from [0][0] to the end column by column

template <MatrixElementType T>
Matrix<T>::NIterator::NIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<NIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

// 6) ConstNIterator

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(const NIterator& nIterator)
    : FullTraverseIterator<ConstNIterator>{
          nIterator._getMatrixPtr(), nIterator._getNrOfMatrixRows(), nIterator._getNrOfMatrixColumns(),
          computeForwardNonDiagIteratorIndex(nIterator._getNrOfMatrixColumns(), nIterator._getNrOfMatrixRows(),
                                             nIterator.getColumnNr(), nIterator.getRowNr())}
{
}

template <MatrixElementType T>
Matrix<T>::ConstNIterator::ConstNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

// 7) ReverseNIterator - iterates within matrix from end to [0][0] column by column (in reverse direction comparing to
// NIterator)

template <MatrixElementType T>
Matrix<T>::ReverseNIterator::ReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ReverseNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

// 8) ConstReverseNIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(const ReverseNIterator& reverseNIterator)
    : FullTraverseIterator<ConstReverseNIterator>{
          reverseNIterator._getMatrixPtr(), reverseNIterator._getNrOfMatrixRows(),
          reverseNIterator._getNrOfMatrixColumns(),
          computeReverseNonDiagIteratorIndex(reverseNIterator._getNrOfMatrixColumns(),
                                             reverseNIterator._getNrOfMatrixRows(), reverseNIterator.getColumnNr(),
                                             reverseNIterator.getRowNr())}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseNIterator::ConstReverseNIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : FullTraverseIterator<ConstReverseNIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseNonDiagIteratorIndex(nrOfMatrixColumns, nrOfMatrixRows, columnNr, rowNr)}
{
}

// 9) DIterator (diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<DIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::DIterator::DIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<DIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 10) ConstDIterator (const diagonal iterator, traverses a matrix diagonal)

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(const DIterator& dIterator)
    : PartialDiagIterator<ConstDIterator>{dIterator._getMatrixPtr(),
                                          dIterator._getNrOfMatrixRows(),
                                          dIterator._getNrOfMatrixColumns(),
                                          {dIterator.getDiagonalNr(), dIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstDIterator::ConstDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 11) ReverseDIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the DIterator)

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ReverseDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseDIterator::ReverseDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ReverseDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 12) ConstReverseDIterator (const diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the
// DIterator)

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(const ReverseDIterator& reverseDIterator)
    : PartialDiagIterator<ConstReverseDIterator>{
          reverseDIterator._getMatrixPtr(),
          reverseDIterator._getNrOfMatrixRows(),
          reverseDIterator._getNrOfMatrixColumns(),
          {reverseDIterator.getDiagonalNr(), reverseDIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstReverseDIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseDIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseDIterator::ConstReverseDIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstReverseDIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 13) MIterator (mirrored diagonal iterator, traverses a matrix diagonal from the other side (symetrically to
// DIterator); diagonal 0 passes through the upper right corner of the matrix)

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                Matrix<T>::size_type nrOfMatrixColumns, std::optional<Matrix<T>::size_type> rowNr,
                                std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<MIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::MIterator::MIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<MIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 14) ConstMIterator

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(const MIterator& mIterator)
    : PartialDiagIterator<ConstMIterator>{mIterator._getMatrixPtr(),
                                          mIterator._getNrOfMatrixRows(),
                                          mIterator._getNrOfMatrixColumns(),
                                          {mIterator.getDiagonalNr(), mIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                          Matrix<T>::size_type nrOfMatrixColumns,
                                          std::optional<Matrix<T>::size_type> rowNr,
                                          std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeForwardMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstMIterator::ConstMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 15) ReverseMIterator (diagonal iterator, traverses a matrix diagonal in reverse direction comparing to the MIterator)

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                              Matrix<T>::size_type nrOfMatrixColumns,
                                              std::optional<Matrix<T>::size_type> rowNr,
                                              std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ReverseMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ReverseMIterator::ReverseMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ReverseMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// 16) ConstReverseMIterator

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(const ReverseMIterator& reverseMIterator)
    : PartialDiagIterator<ConstReverseMIterator>{
          reverseMIterator._getMatrixPtr(),
          reverseMIterator._getNrOfMatrixRows(),
          reverseMIterator._getNrOfMatrixColumns(),
          {reverseMIterator.getDiagonalNr(), reverseMIterator.getDiagonalIndex()}}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows,
                                                        Matrix<T>::size_type nrOfMatrixColumns,
                                                        std::optional<Matrix<T>::size_type> rowNr,
                                                        std::optional<Matrix<T>::size_type> columnNr)
    : PartialDiagIterator<ConstReverseMIterator>{
          pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns,
          computeReverseMIteratorDiagNrAndIndex(nrOfMatrixRows, nrOfMatrixColumns, rowNr, columnNr)}
{
}

template <MatrixElementType T>
Matrix<T>::ConstReverseMIterator::ConstReverseMIterator(
    T** pMatrixPtr, Matrix<T>::size_type nrOfMatrixRows, Matrix<T>::size_type nrOfMatrixColumns,
    const std::pair<Matrix<T>::diff_type, std::optional<Matrix<T>::size_type>>& diagonalNrAndIndex)
    : PartialDiagIterator<ConstReverseMIterator>{pMatrixPtr, nrOfMatrixRows, nrOfMatrixColumns, diagonalNrAndIndex}
{
}

// matrix methods

template <MatrixElementType T> Matrix<T>::Matrix()
{
    _allocMemory(0, 0);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, std::vector<T>&& vec)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(nrOfRows * nrOfColumns > vec.size(),
                          Matr::errorMessages[Matr::Errors::INSUFFICIENT_ELEMENTS_FOR_INIT]);

    const size_type c_RowCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRows + nrOfRows / 4), c_MaxAllowedDimension)};
    const size_type c_ColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfColumns + nrOfColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);

    typename std::vector<T>::iterator vecIterator{vec.begin()};

    /* absRowNr = absolute row number, i.e. number of the row within "physical" matrix (that includes free row/column
       capacity) When the "abs" keyword is missing (i.e. rowNr), then the row number within "logical" (actually used)
       matrix (excluding free capacity) is meant (see other methods too)
    */
    for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_move_n(vecIterator, m_NrOfColumns, m_pBaseArrayPtr[absRowNr]);
        vecIterator += m_NrOfColumns;
    }
}

template <MatrixElementType T> Matrix<T>::Matrix(Matrix<T>::dimensions_t dimensions, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};
    const auto& [nrOfRows, nrOfColumns] = dimensions;

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const size_type c_RowCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRows + nrOfRows / 4), c_MaxAllowedDimension)};
    const size_type c_ColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfColumns + nrOfColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRows, nrOfColumns, c_RowCapacityToAlloc, c_ColumnCapacityToAlloc);
    _fillInitItems(0, 0, nrOfRows, nrOfColumns, value);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>::size_type nrOfRowsColumns, const std::pair<T, T>& diagMatrixValues)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRowsColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRowsColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const size_type c_RowColumnCapacityToAlloc{
        std::min(static_cast<size_type>(nrOfRowsColumns + nrOfRowsColumns / 4), c_MaxAllowedDimension)};

    _allocMemory(nrOfRowsColumns, nrOfRowsColumns, c_RowColumnCapacityToAlloc, c_RowColumnCapacityToAlloc);

    const auto& [allButMainDiagValue, mainDiagValue]{diagMatrixValues};

    for (size_type absRowNr{*m_RowCapacityOffset}, columnNr{0}; columnNr < nrOfRowsColumns; ++columnNr, ++absRowNr)
    {
        T* const pRowBegin{m_pBaseArrayPtr[absRowNr]};
        T* const pMainDiagElement{m_pBaseArrayPtr[absRowNr] + columnNr};
        T* const pRowEnd{m_pBaseArrayPtr[absRowNr] + nrOfRowsColumns};

        std::uninitialized_fill(pRowBegin, pMainDiagElement, allButMainDiagValue);
        std::uninitialized_fill(pMainDiagElement, pMainDiagElement + 1, mainDiagValue);
        std::uninitialized_fill(pMainDiagElement + 1, pRowEnd, allButMainDiagValue);
    }
}

template <MatrixElementType T>
Matrix<T>::Matrix(const Matrix<T>& matrix)
    : Matrix{}
{
    _copyAssignMatrix(matrix);
}

template <MatrixElementType T>
Matrix<T>::Matrix(Matrix<T>&& matrix)
    : Matrix{}
{
    _moveAssignMatrix(matrix);
}

template <MatrixElementType T> Matrix<T>::~Matrix()
{
    _deallocMemory();
}

template <MatrixElementType T> T& Matrix<T>::at(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);
    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template <MatrixElementType T> const T& Matrix<T>::at(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows || columnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]);
    return m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr][columnNr];
}

template <MatrixElementType T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& matrix)
{
    _copyAssignMatrix(matrix);
    return *this;
}

template <MatrixElementType T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& matrix)
{
    _moveAssignMatrix(matrix);
    return *this;
}

// a contiguous unidimensional array with the matrix elements (in row order) is returned to user
template <MatrixElementType T> void* Matrix<T>::getBaseArray(Matrix<T>::size_type& nrOfElements)
{
    void* pAllocPtr{nullptr};

    if (!isEmpty())
    {
        shrinkToFit(); // when transfering ownership user should get exactly the number of elements contained in the
                       // used lines and columns (no extra capacity to be included)
        pAllocPtr = _convertToArray(nrOfElements);
    }
    else
    {
        nrOfElements = 0;
    }

    return pAllocPtr;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getNrOfRows() const
{
    return m_NrOfRows;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getNrOfColumns() const
{
    return m_NrOfColumns;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getRowCapacity() const
{
    return m_RowCapacity;
}

template <MatrixElementType T> typename Matrix<T>::size_type Matrix<T>::getColumnCapacity() const
{
    return m_ColumnCapacity;
}
#ifdef USE_CAPACITY_OFFSET
template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::getRowCapacityOffset() const
{
    return m_RowCapacityOffset;
}

template <MatrixElementType T> std::optional<typename Matrix<T>::size_type> Matrix<T>::getColumnCapacityOffset() const
{
    return m_ColumnCapacityOffset;
}
#endif
template <MatrixElementType T> bool Matrix<T>::isEmpty() const
{
    if (m_pAllocPtr)
    {
        assert(m_pBaseArrayPtr && m_NrOfRows > 0 && m_NrOfColumns > 0 && m_RowCapacity >= m_NrOfRows &&
               m_ColumnCapacity >= m_NrOfColumns && m_RowCapacityOffset >= 0 && m_ColumnCapacityOffset >= 0);
    }
    else
    {
        assert(!m_pBaseArrayPtr && 0 == m_NrOfRows && 0 == m_NrOfColumns && 0 == m_RowCapacity &&
               0 == m_ColumnCapacity && !m_RowCapacityOffset.has_value() && !m_ColumnCapacityOffset.has_value());
    }

    return !m_pAllocPtr;
}

template <MatrixElementType T> void Matrix<T>::transpose()
{
    if (!isEmpty())
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_NewNrOfRows{m_NrOfColumns};
        const size_type c_NewNrOfColumns{m_NrOfRows};
        const size_type c_NewRowCapacity{
            m_RowCapacity < m_NrOfColumns
                ? std::min(static_cast<size_type>(m_NrOfColumns + m_NrOfColumns / 4), c_MaxAllowedDimension)
                : m_RowCapacity};
        const size_type c_NewColumnCapacity{
            m_ColumnCapacity < m_NrOfRows
                ? std::min(static_cast<size_type>(m_NrOfRows + m_NrOfRows / 4), c_MaxAllowedDimension)
                : m_ColumnCapacity};

        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not actually required, just for "safety" and consistency purposes
        _allocMemory(helperMatrix.m_NrOfColumns, helperMatrix.m_NrOfRows, c_NewRowCapacity, c_NewColumnCapacity);

        // no use of _moveInitItems(), too much overhead
        for (size_type absRowNr{*m_RowCapacityOffset}, rowNr{0}; rowNr < c_NewNrOfRows; ++rowNr, ++absRowNr)
        {
            for (size_type helperMatrixAbsRowNr{*helperMatrix.m_RowCapacityOffset}, columnNr{0};
                 columnNr < c_NewNrOfColumns; ++columnNr, ++helperMatrixAbsRowNr)
            {
                std::uninitialized_move_n(helperMatrix.m_pBaseArrayPtr[helperMatrixAbsRowNr] + rowNr, 1,
                                          m_pBaseArrayPtr[absRowNr] + columnNr);
            }
        }
    }
}

template <MatrixElementType T> void Matrix<T>::clear()
{
    _deallocMemory();
}

template <MatrixElementType T> void Matrix<T>::resize(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const auto [c_NrOfRemainingRows,
                c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns)};

    // initialize new elements to the right side of the retained ones
    if (m_NrOfColumns > c_NrOfRemainingColumns)
    {
        _defaultConstructInitItems(0, c_NrOfRemainingColumns, c_NrOfRemainingRows,
                                   m_NrOfColumns - c_NrOfRemainingColumns);
    }

    // same for the ones below
    if (m_NrOfRows > c_NrOfRemainingRows)
    {
        _defaultConstructInitItems(c_NrOfRemainingRows, 0, nrOfRows - c_NrOfRemainingRows, m_NrOfColumns);
    }

    _normalizeRowCapacity();
}

template <MatrixElementType T>
void Matrix<T>::resize(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == nrOfRows || 0 == nrOfColumns, Matr::errorMessages[Matr::Errors::NULL_DIMENSION]);
    CHECK_ERROR_CONDITION(nrOfRows > c_MaxAllowedDimension || nrOfColumns > c_MaxAllowedDimension,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    const auto [c_NrOfRemainingRows,
                c_NrOfRemainingColumns]{_resizeWithUninitializedNewElements(nrOfRows, nrOfColumns)};

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

template <MatrixElementType T>
void Matrix<T>::reserve(Matrix<T>::size_type rowCapacity, Matrix<T>::size_type columnCapacity)
{
    if (!isEmpty())
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_NewRowCapacity{std::clamp<size_type>(rowCapacity, m_NrOfRows, c_MaxAllowedDimension)};
        const size_type c_NewColumnCapacity{
            std::clamp<size_type>(columnCapacity, m_NrOfColumns, c_MaxAllowedDimension)};

        if (m_RowCapacity != c_NewRowCapacity || m_ColumnCapacity != c_NewColumnCapacity)
        {
            Matrix matrix{std::move(*this)};

            _deallocMemory(); // actually not required, just for safety purposes
            _allocMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

            // move the retained items back
            _moveInitItems(matrix, 0, 0, 0, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::shrinkToFit()
{
    if (m_RowCapacity != m_NrOfRows || m_ColumnCapacity != m_NrOfColumns)
    {
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // just for safety purposes, not actually needed
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::insertRow(Matrix<T>::size_type rowNr)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_default_construct_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns);
}

template <MatrixElementType T> void Matrix<T>::insertRow(Matrix<T>::size_type rowNr, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(0 == m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(rowNr > m_NrOfRows, Matr::errorMessages[Matr::Errors::INSERT_ROW_NONCONTIGUOUS]);

    _insertUninitializedRow(rowNr);

    std::uninitialized_fill_n(m_pBaseArrayPtr[*m_RowCapacityOffset + rowNr], m_NrOfColumns, value);
}

template <MatrixElementType T> void Matrix<T>::insertColumn(Matrix<T>::size_type columnNr)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
    {
        std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + c_UninitializedColumnNr, 1);
    }

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating
    // uninitialized elements
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

template <MatrixElementType T> void Matrix<T>::insertColumn(Matrix<T>::size_type columnNr, const T& value)
{
    constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

    CHECK_ERROR_CONDITION(!m_NrOfRows, Matr::errorMessages[Matr::Errors::EMPTY_MATRIX]);
    CHECK_ERROR_CONDITION(c_MaxAllowedDimension == m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);
    CHECK_ERROR_CONDITION(columnNr > m_NrOfColumns, Matr::errorMessages[Matr::Errors::INSERT_COLUMN_NONCONTIGUOUS]);

    const size_type c_UninitializedColumnNr{_insertUninitializedColumn(columnNr)};

    _fillInitItems(0, c_UninitializedColumnNr, m_NrOfRows, 1, value);

    // the rotation of the column should be done after initialization, otherwise an error occurs when rotating
    // uninitialized elements
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

template <MatrixElementType T> void Matrix<T>::eraseRow(Matrix<T>::size_type rowNr)
{
    CHECK_ERROR_CONDITION(rowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    if (1 == m_NrOfRows)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfRows{static_cast<size_type>(m_NrOfRows - 1)};
             c_RemainingNrOfRows <= m_RowCapacity / 4)
    {
        _reallocEraseDimensionElement(rowNr, true);
    }
    else
    {
        _shiftEraseRow(rowNr);
    }
}

template <MatrixElementType T> void Matrix<T>::eraseColumn(Matrix<T>::size_type columnNr)
{
    CHECK_ERROR_CONDITION(columnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (1 == m_NrOfColumns)
    {
        _deallocMemory();
    }
    else if (const size_type c_RemainingNrOfColumns{static_cast<size_type>(m_NrOfColumns - 1)};
             c_RemainingNrOfColumns <= m_ColumnCapacity / 4)
    {
        _reallocEraseDimensionElement(columnNr, false);
    }
    else
    {
        _shiftEraseColumn(columnNr);
    }
}

template <MatrixElementType T> void Matrix<T>::catByRow(Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        CHECK_ERROR_CONDITION(m_NrOfColumns != matrix.m_NrOfColumns,
                              Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_ROW_LENGTH]);
    }

    const size_type c_OldNrOfRows{m_NrOfRows};
    const size_type c_NewNrOfRows{static_cast<size_type>(m_NrOfRows + matrix.m_NrOfRows)};

    CHECK_ERROR_CONDITION(c_NewNrOfRows > maxAllowedDimension(),
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    if (c_NewNrOfRows <= m_RowCapacity)
    {
        _alignToTop();
        m_NrOfRows = c_NewNrOfRows;

        if (&matrix != this)
        {
            _moveInitItems(matrix, 0, 0, c_OldNrOfRows, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
        else
        {
            _copyInitItems(*this, 0, 0, c_OldNrOfRows, 0, c_OldNrOfRows, m_NrOfColumns);
        }

        _normalizeRowCapacity();
    }
    else
    {
        const size_type c_OldColumnCapacity{m_ColumnCapacity};
        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(c_NewNrOfRows, helperMatrix.m_NrOfColumns, c_NewNrOfRows, c_OldColumnCapacity);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);

        if (&matrix != this)
        {
            _moveInitItems(matrix, 0, 0, c_OldNrOfRows, 0, matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }
        else
        {
            _copyInitItems(*this, 0, 0, c_OldNrOfRows, 0, c_OldNrOfRows, m_NrOfColumns);
        }
    }

    // clear the source matrix as its content is no longer usable
    if (&matrix != this)
    {
        matrix._deallocMemory();
    }
}

template <MatrixElementType T> void Matrix<T>::catByColumn(Matrix& matrix)
{
    if (&matrix != this)
    {
        CHECK_ERROR_CONDITION(m_NrOfRows != matrix.m_NrOfRows,
                              Matr::errorMessages[Matr::Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH]);
    }

    const size_type c_OldNrOfColumns{m_NrOfColumns};
    const size_type c_NewNrOfColumns{static_cast<size_type>(m_NrOfColumns + matrix.m_NrOfColumns)};

    CHECK_ERROR_CONDITION(c_NewNrOfColumns > maxAllowedDimension(),
                          Matr::errorMessages[Matr::Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED]);

    if (!matrix.isEmpty())
    {
        if (c_NewNrOfColumns <= m_ColumnCapacity)
        {
            const size_type c_ColumnConcatenationSpace{
                static_cast<size_type>(m_ColumnCapacity - *m_ColumnCapacityOffset)};

            // if not enough available capacity on the right side, then the columns should be shifted left by the
            // minimal count of positions that ensure the concatenated content fits
            if (c_NewNrOfColumns > c_ColumnConcatenationSpace)
            {
                const size_type c_NrOfColumnsToShiftLeft{
                    static_cast<size_type>(c_NewNrOfColumns - c_ColumnConcatenationSpace)};
                _shiftColumnsLeft(c_NrOfColumnsToShiftLeft);
            }

            m_NrOfColumns = c_NewNrOfColumns;

            if (&matrix != this)
            {
                _moveInitItems(matrix, 0, 0, 0, c_OldNrOfColumns, matrix.m_NrOfRows, matrix.m_NrOfColumns);
            }
            else
            {
                _copyInitItems(*this, 0, 0, 0, c_OldNrOfColumns, m_NrOfRows, c_OldNrOfColumns);
            }
        }
        else
        {
            const size_type c_OldRowCapacity{m_RowCapacity};
            const size_type c_NewColumnCapacity{std::max(m_ColumnCapacity, c_NewNrOfColumns)};

            Matrix helperMatrix{std::move(*this)};

            _deallocMemory(); // actually not required, just for safety purposes
            _allocMemory(helperMatrix.m_NrOfRows, c_NewNrOfColumns, c_OldRowCapacity, c_NewColumnCapacity);

            _moveInitItems(helperMatrix, 0, 0, 0, 0, helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns);

            if (&matrix != this)
            {
                _moveInitItems(matrix, 0, 0, 0, c_OldNrOfColumns, matrix.m_NrOfRows, matrix.m_NrOfColumns);
            }
            else
            {
                _copyInitItems(*this, 0, 0, 0, c_OldNrOfColumns, m_NrOfRows, c_OldNrOfColumns);
            }
        }

        // clear the source matrix as its content is no longer usable
        if (&matrix != this)
        {
            matrix._deallocMemory();
        }
    }
}

template <MatrixElementType T> void Matrix<T>::splitByRow(Matrix& matrix, Matrix<T>::size_type splitRowNr)
{
    CHECK_ERROR_CONDITION(&matrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARGUMENT]);
    CHECK_ERROR_CONDITION(splitRowNr >= m_NrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(0 == splitRowNr, Matr::errorMessages[Matr::Errors::RESULT_NO_ROWS]);

    const size_type c_NewDestNrOfRows{static_cast<size_type>(m_NrOfRows - splitRowNr)};
    const size_type c_NewDestRowCapacity{std::max<size_type>(matrix.m_RowCapacity, c_NewDestNrOfRows)};
    const size_type c_NewDestColumnCapacity{std::max<size_type>(matrix.m_ColumnCapacity, m_NrOfColumns)};

    if (matrix.isEmpty() || c_NewDestRowCapacity > matrix.m_RowCapacity ||
        c_NewDestColumnCapacity > matrix.m_ColumnCapacity)
    {
        matrix._deallocMemory();
        matrix._allocMemory(c_NewDestNrOfRows, m_NrOfColumns, c_NewDestRowCapacity, c_NewDestColumnCapacity);
    }
    else
    {
        matrix._remapMemory(c_NewDestNrOfRows, m_NrOfColumns);
    }

    matrix._moveInitItems(*this, splitRowNr, 0, 0, 0, c_NewDestNrOfRows, m_NrOfColumns);

    _destroyItems(splitRowNr, 0, c_NewDestNrOfRows, m_NrOfColumns);
    m_NrOfRows = splitRowNr;
    _normalizeRowCapacity();
}

template <MatrixElementType T> void Matrix<T>::splitByColumn(Matrix& matrix, Matrix<T>::size_type splitColumnNr)
{
    CHECK_ERROR_CONDITION(&matrix == this, Matr::errorMessages[Matr::Errors::CURRENT_MATRIX_AS_ARGUMENT]);
    CHECK_ERROR_CONDITION(splitColumnNr >= m_NrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);
    CHECK_ERROR_CONDITION(0 == splitColumnNr, Matr::errorMessages[Matr::Errors::RESULT_NO_COLUMNS]);

    const size_type c_NewDestNrOfColumns{static_cast<size_type>(m_NrOfColumns - splitColumnNr)};
    const size_type c_NewDestRowCapacity{std::max<size_type>(matrix.m_RowCapacity, m_NrOfRows)};
    const size_type c_NewDestColumnCapacity{std::max<size_type>(matrix.m_ColumnCapacity, c_NewDestNrOfColumns)};

    if (matrix.isEmpty() || c_NewDestRowCapacity > matrix.m_RowCapacity ||
        c_NewDestColumnCapacity > matrix.m_ColumnCapacity)
    {
        matrix._deallocMemory();
        matrix._allocMemory(m_NrOfRows, c_NewDestNrOfColumns, c_NewDestRowCapacity, c_NewDestColumnCapacity);
    }
    else
    {
        matrix._remapMemory(m_NrOfRows, c_NewDestNrOfColumns);
    }

    matrix._moveInitItems(*this, 0, splitColumnNr, 0, 0, m_NrOfRows, c_NewDestNrOfColumns);

    _destroyItems(0, splitColumnNr, m_NrOfRows, c_NewDestNrOfColumns);
    m_NrOfColumns = splitColumnNr;
}

template <MatrixElementType T>
void Matrix<T>::swapRows(Matrix<T>::size_type firstRowNr, Matrix<T>::size_type secondRowNr)
{
    CHECK_ERROR_CONDITION(firstRowNr >= m_NrOfRows || secondRowNr >= m_NrOfRows,
                          Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]);

    const size_type c_FirstAbsRowNr{static_cast<size_type>(*m_RowCapacityOffset + firstRowNr)};
    const size_type c_SecondAbsRowNr{static_cast<size_type>(*m_RowCapacityOffset + secondRowNr)};

    if (c_FirstAbsRowNr != c_SecondAbsRowNr)
    {
        // exchanging row pointers is enough and greatly optimizes the speed of execution
        std::swap(m_pBaseArrayPtr[c_FirstAbsRowNr], m_pBaseArrayPtr[c_SecondAbsRowNr]);
    }
}

template <MatrixElementType T>
void Matrix<T>::swapColumns(Matrix<T>::size_type firstColumnNr, Matrix<T>::size_type secondColumnNr)
{
    CHECK_ERROR_CONDITION(firstColumnNr >= m_NrOfColumns || secondColumnNr >= m_NrOfColumns,
                          Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]);

    if (firstColumnNr != secondColumnNr)
    {
        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::swap(m_pBaseArrayPtr[absRowNr][firstColumnNr], m_pBaseArrayPtr[absRowNr][secondColumnNr]);
        }
    }
}

template <MatrixElementType T> bool Matrix<T>::operator==(const Matrix<T>& matrix) const
{
    bool areEqual{true};

    if (&matrix != this)
    {
        // matrix emptiness should be checked first in order to avoid accessing (std::optional) capacity offsets of
        // empty matrixes (see second case: "else if")
        if (const bool isCurrentMatrixEmpty{isEmpty()}, isOtherMatrixEmpty{matrix.isEmpty()};
            isCurrentMatrixEmpty || isOtherMatrixEmpty)
        {
            areEqual = isCurrentMatrixEmpty && isOtherMatrixEmpty;
        }
        else if (m_NrOfRows == matrix.m_NrOfRows && m_NrOfColumns == matrix.m_NrOfColumns)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}, matrixAbsRowNr{*matrix.m_RowCapacityOffset};
                 absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr, ++matrixAbsRowNr)
            {
                areEqual = areEqual && std::equal(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + m_NrOfColumns,
                                                  matrix.m_pBaseArrayPtr[matrixAbsRowNr]);

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

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zEnd()
{
    GET_FORWARD_NON_DIAG_END_ITERATOR(ZIterator,
                                      m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                      m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zRowBegin(Matrix<T>::size_type rowNr)
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::zRowEnd(Matrix<T>::size_type rowNr)
{
    GET_FORWARD_ROW_END_ZITERATOR(ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ZIterator Matrix<T>::getZIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::constZBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::constZEnd() const
{
    GET_FORWARD_NON_DIAG_END_ITERATOR(ConstZIterator,
                                      m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                      m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::constZRowBegin(Matrix<T>::size_type rowNr) const
{
    GET_FORWARD_ROW_BEGIN_ZITERATOR(ConstZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::constZRowEnd(Matrix<T>::size_type rowNr) const
{
    GET_FORWARD_ROW_END_ZITERATOR(ConstZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstZIterator Matrix<T>::getConstZIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZEnd()
{
    GET_REVERSE_END_ZITERATOR(ReverseZIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZRowBegin(Matrix<T>::size_type rowNr)
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ReverseZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::reverseZRowEnd(Matrix<T>::size_type rowNr)
{
    GET_REVERSE_ROW_END_ZITERATOR(ReverseZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseZIterator Matrix<T>::getReverseZIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseZIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZEnd() const
{
    GET_REVERSE_END_ZITERATOR(ConstReverseZIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZRowBegin(Matrix<T>::size_type rowNr) const
{
    GET_REVERSE_ROW_BEGIN_ZITERATOR(ConstReverseZIterator,
                                    m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                    m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::constReverseZRowEnd(Matrix<T>::size_type rowNr) const
{
    GET_REVERSE_ROW_END_ZITERATOR(ConstReverseZIterator,
                                  m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                  m_NrOfRows, m_NrOfColumns, rowNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseZIterator Matrix<T>::getConstReverseZIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseZIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nBegin()
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(NIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nEnd()
{
    GET_FORWARD_NON_DIAG_END_ITERATOR(NIterator,
                                      m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                      m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nColumnBegin(Matrix<T>::size_type columnNr)
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(NIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::NIterator Matrix<T>::nColumnEnd(Matrix<T>::size_type columnNr)
{
    GET_FORWARD_COLUMN_END_NITERATOR(NIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::NIterator Matrix<T>::getNIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        NIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::constNBegin() const
{
    GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(ConstNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstNIterator Matrix<T>::constNEnd() const
{
    GET_FORWARD_NON_DIAG_END_ITERATOR(ConstNIterator,
                                      m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                      m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::constNColumnBegin(Matrix<T>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_BEGIN_NITERATOR(ConstNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::constNColumnEnd(Matrix<T>::size_type columnNr) const
{
    GET_FORWARD_COLUMN_END_NITERATOR(ConstNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstNIterator Matrix<T>::getConstNIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNBegin()
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ReverseNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNEnd()
{
    GET_REVERSE_END_NITERATOR(ReverseNIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNColumnBegin(Matrix<T>::size_type columnNr)
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ReverseNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::reverseNColumnEnd(Matrix<T>::size_type columnNr)
{
    GET_REVERSE_COLUMN_END_NITERATOR(ReverseNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseNIterator Matrix<T>::getReverseNIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNBegin() const
{
    GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(ConstReverseNIterator,
                                        m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                        m_NrOfRows, m_NrOfColumns);
}

template <MatrixElementType T> typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNEnd() const
{
    GET_REVERSE_END_NITERATOR(ConstReverseNIterator,
                              m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                              m_NrOfColumns);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNColumnBegin(Matrix<T>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_BEGIN_NITERATOR(ConstReverseNIterator,
                                       m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                       m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::constReverseNColumnEnd(Matrix<T>::size_type columnNr) const
{
    GET_REVERSE_COLUMN_END_NITERATOR(ConstReverseNIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseNIterator Matrix<T>::getConstReverseNIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseNIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::dBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::dBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::DIterator Matrix<T>::dEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(DIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::dEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::getDIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::DIterator Matrix<T>::getDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        DIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDBegin(Matrix<T>::size_type rowNr,
                                                          Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::constDEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::getConstDIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstDIterator Matrix<T>::getConstDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseDIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ReverseDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::reverseDEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::getReverseDIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseDIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseDIterator Matrix<T>::getReverseDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseDIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDBegin(Matrix<T>::size_type rowNr,
                                                                        Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_DITERATOR_BY_DIAG_NUMBER(ConstReverseDIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::constReverseDEnd(Matrix<T>::size_type rowNr,
                                                                      Matrix<T>::size_type columnNr) const
{
    GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::getConstReverseDIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseDIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseDIterator Matrix<T>::getConstReverseDIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstReverseDIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::mBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::mBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T> typename Matrix<T>::MIterator Matrix<T>::mEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(MIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::mEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::getMIterator(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::MIterator Matrix<T>::getMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                            m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMBegin(Matrix<T>::size_type rowNr,
                                                          Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMEnd(Matrix<T>::diff_type diagonalNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::constMEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::getConstMIterator(Matrix<T>::size_type rowNr,
                                                                Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                             m_NrOfRows, m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstMIterator Matrix<T>::getConstMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        MIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMBegin(Matrix<T>::diff_type diagonalNr)
{
    GET_DIAG_BEGIN_ITERATOR(ReverseMIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMBegin(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMEnd(Matrix<T>::diff_type diagonalNr)
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ReverseMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::reverseMEnd(Matrix<T>::size_type rowNr, Matrix<T>::size_type columnNr)
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::getReverseMIterator(Matrix<T>::size_type rowNr,
                                                                    Matrix<T>::size_type columnNr)
{
    GET_DIAG_RANDOM_ITERATOR(ReverseMIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ReverseMIterator Matrix<T>::getReverseMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex)
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMBegin(Matrix<T>::diff_type diagonalNr) const
{
    GET_DIAG_BEGIN_ITERATOR(ConstReverseMIterator,
                            m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                            m_NrOfColumns, diagonalNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMBegin(Matrix<T>::size_type rowNr,
                                                                        Matrix<T>::size_type columnNr) const
{
    GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMEnd(Matrix<T>::diff_type diagonaNr) const
{
    GET_END_MITERATOR_BY_DIAG_NUMBER(ConstReverseMIterator,
                                     m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr,
                                     m_NrOfRows, m_NrOfColumns, diagonaNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::constReverseMEnd(Matrix<T>::size_type rowNr,
                                                                      Matrix<T>::size_type columnNr) const
{
    GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::getConstReverseMIterator(Matrix<T>::size_type rowNr,
                                                                              Matrix<T>::size_type columnNr) const
{
    GET_DIAG_RANDOM_ITERATOR(ConstReverseMIterator,
                             m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
                             m_NrOfColumns, rowNr, columnNr);
}

template <MatrixElementType T>
typename Matrix<T>::ConstReverseMIterator Matrix<T>::getConstReverseMIterator(
    const std::pair<Matrix<T>::diff_type, Matrix<T>::size_type>& diagonalNrAndIndex) const
{
    const auto& [diagonalNr, diagonalIndex] = diagonalNrAndIndex;
    GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(
        ConstReverseMIterator, m_pBaseArrayPtr ? m_pBaseArrayPtr + *m_RowCapacityOffset : m_pBaseArrayPtr, m_NrOfRows,
        m_NrOfColumns, diagonalNr, diagonalIndex);
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::begin()
{
    return zBegin();
}

template <MatrixElementType T> typename Matrix<T>::ZIterator Matrix<T>::end()
{
    return zEnd();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::begin() const
{
    return constZBegin();
}

template <MatrixElementType T> typename Matrix<T>::ConstZIterator Matrix<T>::end() const
{
    return constZEnd();
}

template <MatrixElementType T>
std::pair<typename Matrix<T>::size_type, typename Matrix<T>::size_type> Matrix<T>::_resizeWithUninitializedNewElements(
    Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    assert(nrOfRows <= maxAllowedDimension() && nrOfColumns <= maxAllowedDimension());

    const size_type c_NewNrOfRows{(nrOfRows > size_type{0} && nrOfColumns > size_type{0}) ? nrOfRows : size_type{0}};
    const size_type c_NewNrOfColumns{c_NewNrOfRows > size_type{0} ? nrOfColumns : size_type{0}};
    const size_type c_NewRowCapacity{std::max(m_RowCapacity, c_NewNrOfRows)};
    const size_type c_NewColumnCapacity{std::max(m_ColumnCapacity, c_NewNrOfColumns)};
    const size_type c_NrOfRowsToKeep{std::min(m_NrOfRows, c_NewNrOfRows)};
    const size_type c_NrOfColumnsToKeep{std::min(m_NrOfColumns, c_NewNrOfColumns)};
    const std::optional<size_type> c_NewRowCapacityOffset{
        c_NewNrOfRows > 0 ? std::optional((c_NewRowCapacity - c_NewNrOfRows) / 2) : std::nullopt};

    if (!m_RowCapacityOffset.has_value() /* empty matrix, column capacity offset std::nullopt as well */ ||
        !c_NewRowCapacityOffset.has_value() || c_NewRowCapacity != m_RowCapacity ||
        c_NewColumnCapacity != m_ColumnCapacity)
    {
        Matrix matrix{std::move(*this)};
        _deallocMemory(); // actually not required, just for safety purposes
        _allocMemory(c_NewNrOfRows, c_NewNrOfColumns, c_NewRowCapacity, c_NewColumnCapacity);

        // move the retained items back
        _moveInitItems(matrix, 0, 0, 0, 0, c_NrOfRowsToKeep, c_NrOfColumnsToKeep);
    }
    else
    {
        const size_type c_ColumnsResizingSpace{static_cast<size_type>(m_ColumnCapacity - *m_ColumnCapacityOffset)};

        // if not enough available capacity on the right side, then the columns should be shifted left by the minimal
        // count of positions that ensure the resized content fits
        if (c_NewNrOfColumns > c_ColumnsResizingSpace)
        {
            const size_type c_NrOfColumnsToShiftLeft{static_cast<size_type>(c_NewNrOfColumns - c_ColumnsResizingSpace)};
            _shiftColumnsLeft(c_NrOfColumnsToShiftLeft);
        }

        // move unused top capacity to the bottom to avoid alignment issues (should be re-distributed once resize is
        // complete)
        _alignToTop();

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

template <MatrixElementType T> void Matrix<T>::_insertUninitializedRow(Matrix<T>::size_type rowNr)
{
    const size_type c_RowNr{std::clamp<size_type>(rowNr, 0u, m_NrOfRows)};

    // double the row capacity (without exceeding the maximum allowed capacity) if no spare capacity left (to defer any
    // resize when inserting further rows)
    if (m_NrOfRows == m_RowCapacity)
    {
        Matrix helperMatrix{std::move(*this)};
        const size_type c_NewRowCapacity{
            std::min(static_cast<size_type>(size_type{2} * helperMatrix.m_NrOfRows), maxAllowedDimension())};

        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows + 1, helperMatrix.m_NrOfColumns, c_NewRowCapacity,
                     helperMatrix.m_ColumnCapacity);

        // move everything back to the top/bottom of the inserted row (this one stays uninitialized - will be
        // initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_RowNr, m_NrOfColumns);
        _moveInitItems(helperMatrix, c_RowNr, 0, c_RowNr + 1, 0, m_NrOfRows - c_RowNr, m_NrOfColumns);
    }
    else
    {
        // row capacity offset cannot be std::nullopt as the matrix is not empty (rows count doesn't equal row capacity)
        const bool c_ShouldAppendRow{c_RowNr <= m_NrOfRows / 2 ? (0 == *m_RowCapacityOffset)
                                                               : (m_RowCapacity - *m_RowCapacityOffset > m_NrOfRows)};
        ++m_NrOfRows;

        T** pCurrentMatrixStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        // new row is initially first/last row (depending on the insert position), move it into the insert position (all
        // rows after the insert position moved one position downwards/upwards)
        if (c_ShouldAppendRow)
        {
            std::rotate(pCurrentMatrixStartingRow + c_RowNr, pCurrentMatrixStartingRow + m_NrOfRows - 1,
                        pCurrentMatrixStartingRow + m_NrOfRows);
        }
        else
        {
            m_RowCapacityOffset = *m_RowCapacityOffset - 1;
            --pCurrentMatrixStartingRow;
            std::rotate(pCurrentMatrixStartingRow, pCurrentMatrixStartingRow + 1,
                        pCurrentMatrixStartingRow + c_RowNr + 1);
        }
    }
}

template <MatrixElementType T>
typename Matrix<T>::size_type Matrix<T>::_insertUninitializedColumn(Matrix<T>::size_type columnNr)
{
    size_type resultingColumnNr{std::clamp<size_type>(columnNr, 0u, m_NrOfColumns)};

    // double the column capacity (without exceeding the maximum allowed capacity) if no spare capacity left (to defer
    // any resize when inserting further columns)
    if (m_NrOfColumns == m_ColumnCapacity)
    {
        Matrix helperMatrix{std::move(*this)};
        const size_type c_NewColumnCapacity{
            std::min(static_cast<size_type>(size_type{2} * helperMatrix.m_NrOfColumns), maxAllowedDimension())};

        _deallocMemory(); // not quite necessary, just for safety/consistency purposes
        _allocMemory(helperMatrix.m_NrOfRows, helperMatrix.m_NrOfColumns + 1, helperMatrix.m_RowCapacity,
                     c_NewColumnCapacity);

        // move everything back to the left/right of the inserted column (this one stays uninitialized - will be
        // initialized in a separate step)
        _moveInitItems(helperMatrix, 0, 0, 0, 0, m_NrOfRows, resultingColumnNr);
        _moveInitItems(helperMatrix, 0, resultingColumnNr, 0, resultingColumnNr + 1, m_NrOfRows,
                       m_NrOfColumns - resultingColumnNr);
    }
    else
    {
        // row capacity offset cannot be std::nullopt as the matrix is not empty (columns count doesn't equal column
        // capacity)
        const bool c_ShouldAppendColumn{resultingColumnNr <= m_NrOfColumns / 2
                                            ? (0 == m_ColumnCapacityOffset)
                                            : (m_ColumnCapacity - *m_ColumnCapacityOffset > m_NrOfColumns)};

        if (c_ShouldAppendColumn)
        {
            resultingColumnNr = m_NrOfColumns;
        }
        else
        {
            resultingColumnNr = 0;
            m_ColumnCapacityOffset = *m_ColumnCapacityOffset - 1;

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

template <MatrixElementType T>
void Matrix<T>::_reallocEraseDimensionElement(Matrix<T>::size_type dimensionElementNr, bool isRow)
{
    if (!isEmpty())
    {
        const size_type c_RequiredNrOfRows{isRow ? static_cast<size_type>(m_NrOfRows - 1) : m_NrOfRows};
        const size_type c_RequiredNrOfColumns{isRow ? m_NrOfColumns : static_cast<size_type>(m_NrOfColumns - 1)};
        const size_type c_RequiredRowCapacity{isRow ? static_cast<size_type>(size_type{2} * c_RequiredNrOfRows)
                                                    : m_RowCapacity};
        const size_type c_RequiredColumnCapacity{isRow ? m_ColumnCapacity
                                                       : static_cast<size_type>(size_type{2} * c_RequiredNrOfColumns)};

        // row or column nr depending on scenario (variable isRow)
        const size_type c_DimensionElementNr{
            std::clamp<size_type>(dimensionElementNr, 0u, isRow ? c_RequiredNrOfRows : c_RequiredNrOfColumns)};

        // part one: top part (rows) / left part (columns) - relative to erased row/column
        const size_type c_PartOneNrOfRows{isRow ? c_DimensionElementNr : c_RequiredNrOfRows};
        const size_type c_PartOneNrOfColumns{isRow ? c_RequiredNrOfColumns : c_DimensionElementNr};

        // part two: bottom part (rows) / right part (columns) - relative to erased row/column
        const size_type c_PartTwoSrcStartingRowNr{isRow ? static_cast<size_type>(c_DimensionElementNr + 1)
                                                        : size_type{0}};
        const size_type c_PartTwoSrcColumnOffset{
            static_cast<size_type>(c_DimensionElementNr + 1 - c_PartTwoSrcStartingRowNr)};
        const size_type c_PartTwoStartingRowNr{isRow ? c_DimensionElementNr : size_type{0}};
        const size_type c_PartTwoColumnOffset{static_cast<size_type>(c_DimensionElementNr - c_PartTwoStartingRowNr)};
        const size_type c_PartTwoNrOfRows{static_cast<size_type>(c_RequiredNrOfRows - c_PartTwoStartingRowNr)};
        const size_type c_PartTwoNrOfColumns{static_cast<size_type>(c_RequiredNrOfColumns - c_PartTwoColumnOffset)};

        Matrix helperMatrix{std::move(*this)};

        _deallocMemory(); // not really necessary, just for safety purposes
        _allocMemory(c_RequiredNrOfRows, c_RequiredNrOfColumns, c_RequiredRowCapacity, c_RequiredColumnCapacity);
        _moveInitItems(helperMatrix, 0, 0, 0, 0, c_PartOneNrOfRows, c_PartOneNrOfColumns);
        _moveInitItems(helperMatrix, c_PartTwoSrcStartingRowNr, c_PartTwoSrcColumnOffset, c_PartTwoStartingRowNr,
                       c_PartTwoColumnOffset, c_PartTwoNrOfRows, c_PartTwoNrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::_shiftEraseRow(Matrix<T>::size_type rowNr)
{
    if (!isEmpty())
    {
        const size_type c_RowNr{std::clamp<size_type>(rowNr, 0u, m_NrOfRows - 1)};
        T** pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};

        if (c_RowNr < m_NrOfRows / 2)
        {
            std::rotate(pStartingRow, pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset],
                           m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
            m_RowCapacityOffset = *m_RowCapacityOffset + 1;
        }
        else
        {
            std::rotate(pStartingRow + c_RowNr, pStartingRow + c_RowNr + 1, pStartingRow + m_NrOfRows);
            std::destroy_n(m_pBaseArrayPtr[*m_RowCapacityOffset + m_NrOfRows - 1],
                           m_NrOfColumns); // the memory outside matrix bounds should be uninitialized
        }

        --m_NrOfRows;
    }
}

template <MatrixElementType T> void Matrix<T>::_shiftEraseColumn(Matrix<T>::size_type columnNr)
{
    if (!isEmpty())
    {
        const size_type c_ColumnNr{std::clamp<size_type>(columnNr, 0u, m_NrOfColumns - 1)};

        if (c_ColumnNr < m_NrOfColumns / 2)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + c_ColumnNr,
                            m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1);
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
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr] + c_ColumnNr, m_pBaseArrayPtr[absRowNr] + c_ColumnNr + 1,
                            m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
                std::destroy_n(m_pBaseArrayPtr[absRowNr] + m_NrOfColumns - 1,
                               1); // the memory outside matrix bounds should be uninitialized
            }
        }

        --m_NrOfColumns;
    }
}

template <MatrixElementType T> void Matrix<T>::_rotateFirstColumn(Matrix<T>::size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_NewColumnNr{std::clamp<size_type>(newColumnNr, 0u, m_NrOfColumns)};

        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr], m_pBaseArrayPtr[absRowNr] + 1,
                        m_pBaseArrayPtr[absRowNr] + c_NewColumnNr + 1);
        }
    }
}

template <MatrixElementType T> void Matrix<T>::_rotateLastColumn(Matrix<T>::size_type newColumnNr)
{
    if (!isEmpty())
    {
        const size_type c_LastColumnNr{static_cast<size_type>(m_NrOfColumns - 1)};
        const size_type c_NewColumnNr{std::clamp<size_type>(newColumnNr, 0u, c_LastColumnNr)};

        for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
        {
            std::rotate(m_pBaseArrayPtr[absRowNr] + c_NewColumnNr, m_pBaseArrayPtr[absRowNr] + c_LastColumnNr,
                        m_pBaseArrayPtr[absRowNr] + m_NrOfColumns);
        }
    }
}

// if shifting of columns is involved, then this method should be called after the columns shifting function (e.g.
// _shiftColumnsLeft(), see below)
template <MatrixElementType T> void Matrix<T>::_alignToTop()
{
    if (m_RowCapacityOffset.has_value() && m_RowCapacityOffset > 0)
    {
        std::rotate(m_pBaseArrayPtr, m_pBaseArrayPtr + *m_RowCapacityOffset,
                    m_pBaseArrayPtr + *m_RowCapacityOffset + m_NrOfRows);
        m_RowCapacityOffset = 0;
    }
}

// columns shifting should be performed before aligning to top (see above)
template <MatrixElementType T> void Matrix<T>::_shiftColumnsLeft(Matrix<T>::size_type nrOfPositionsToShift)
{
    if (m_ColumnCapacityOffset.has_value())
    {
        nrOfPositionsToShift = std::clamp<size_type>(nrOfPositionsToShift, 0, *m_ColumnCapacityOffset);
        m_ColumnCapacityOffset = *m_ColumnCapacityOffset - nrOfPositionsToShift;

        const size_type c_OldNrOfColumns{m_NrOfColumns};

        // Step 1: move row start to the left, get an additional count of uninitialized columns ("new" columns)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
        }

        m_NrOfColumns += nrOfPositionsToShift;

        const size_type c_FirstOldColumnNr = nrOfPositionsToShift;
        const size_type c_NrOfColumnsToInitialize{std::min(nrOfPositionsToShift, c_OldNrOfColumns)};

        // Step 2: initialize as many new columns as possible by moving the content of the existing ("old") ones
        _moveInitItems(*this, 0, c_FirstOldColumnNr, 0, 0, m_NrOfRows, c_NrOfColumnsToInitialize);

        // Step 3: any old columns that were not consumed for initializing the additional ones should be moved near the
        // new columns to complete shifting; consumed columns should be destroyed
        if (c_NrOfColumnsToInitialize < c_OldNrOfColumns)
        {
            for (size_type absRowNr{*m_RowCapacityOffset}; absRowNr != *m_RowCapacityOffset + m_NrOfRows; ++absRowNr)
            {
                std::rotate(m_pBaseArrayPtr[absRowNr] + nrOfPositionsToShift,
                            m_pBaseArrayPtr[absRowNr] +
                                static_cast<size_type>(nrOfPositionsToShift + c_NrOfColumnsToInitialize),
                            m_pBaseArrayPtr[absRowNr] + nrOfPositionsToShift + c_OldNrOfColumns);
            }

            _destroyItems(0, c_OldNrOfColumns, m_NrOfRows, c_NrOfColumnsToInitialize);
        }
        else
        {
            _destroyItems(0, nrOfPositionsToShift, m_NrOfRows, c_OldNrOfColumns);
        }

        // at the end of the shifting operation the matrix should have the same number of columns as before
        m_NrOfColumns = c_OldNrOfColumns;
    }
}

template <MatrixElementType T> void Matrix<T>::_normalizeRowCapacity()
{
    const std::optional<size_type> c_NormalizedRowCapacityOffset{
        m_NrOfRows > 0 ? std::optional((m_RowCapacity - m_NrOfRows) / 2) : std::nullopt};

    if (m_RowCapacityOffset.has_value() &&
        (c_NormalizedRowCapacityOffset.has_value() && c_NormalizedRowCapacityOffset > 0) &&
        m_RowCapacityOffset < c_NormalizedRowCapacityOffset)
    {
        const size_type c_LastRowNr{static_cast<size_type>(m_NrOfRows - 1)};
        T** const pStartingRow{m_pBaseArrayPtr + *m_RowCapacityOffset};
        T** const pEndingRow{pStartingRow + c_LastRowNr};
        T** const pStartingRowToReplace{m_pBaseArrayPtr + *c_NormalizedRowCapacityOffset};
        T** const pEndingRowToReplace{pStartingRowToReplace + c_LastRowNr};

        T** pRowToReplace{pEndingRowToReplace};

        for (T** pCurrentRow{pEndingRow}; pCurrentRow >= pStartingRow; --pCurrentRow)
        {
            std::iter_swap(pCurrentRow, pRowToReplace);
            --pRowToReplace;
        }

        m_RowCapacityOffset = c_NormalizedRowCapacityOffset;
    }
}

template <MatrixElementType T>
void Matrix<T>::_allocMemory(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns,
                             Matrix<T>::size_type rowCapacity, Matrix<T>::size_type columnCapacity)
{
    if (nrOfRows > 0 && nrOfColumns > 0)
    {
        m_RowCapacity = rowCapacity < nrOfRows ? nrOfRows : rowCapacity;
        m_ColumnCapacity = columnCapacity < nrOfColumns ? nrOfColumns : columnCapacity;

        m_RowCapacityOffset = (m_RowCapacity - nrOfRows) / 2;
        m_ColumnCapacityOffset = (m_ColumnCapacity - nrOfColumns) / 2;

        m_pBaseArrayPtr = static_cast<T**>(std::malloc(m_RowCapacity * sizeof(T*)));
        m_pAllocPtr = static_cast<T*>(std::malloc(m_RowCapacity * m_ColumnCapacity * sizeof(T)));

        // map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed, left
        // free column capacity excluded)
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

template <MatrixElementType T> void Matrix<T>::_deallocMemory()
{
    if (!isEmpty())
    {
        // ensure the objects contained within matrix are properly disposed (no column capacity offset provided as
        // argument -> free left capacity excluded by m_pBaseArrayPtr pointer elements)
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

// This method should be executed only for already initialized memory; the memory should be subsequently re-initialized
// by running another function
template <MatrixElementType T>
void Matrix<T>::_remapMemory(Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (!isEmpty())
    {
        nrOfRows = std::clamp<size_type>(nrOfRows, 1, m_RowCapacity);
        nrOfColumns = std::clamp<size_type>(nrOfColumns, 1, m_ColumnCapacity);

        _destroyItems(0, 0, m_NrOfRows, m_NrOfColumns);

        m_NrOfRows = nrOfRows;
        m_NrOfColumns = nrOfColumns;

        // capacity gets distributed in an even manner as for new allocations (unused capacity equally distributed
        // between left/right and top/bottom)
        m_RowCapacityOffset = (m_RowCapacity - m_NrOfRows) / 2;
        m_ColumnCapacityOffset = (m_ColumnCapacity - m_NrOfColumns) / 2;

        // re-map row pointers to allocated space, each pointer manages part of the memory array (no overlap allowed,
        // left free column capacity excluded)
        for (size_type rowNr{0}; rowNr < m_RowCapacity; ++rowNr)
        {
            m_pBaseArrayPtr[rowNr] = m_pAllocPtr + (rowNr * m_ColumnCapacity) + *m_ColumnCapacityOffset;
        }
    }
}

template <MatrixElementType T> void Matrix<T>::_copyAssignMatrix(const Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        constexpr size_type c_MaxAllowedDimension{maxAllowedDimension()};

        const size_type c_RowCapacityToAlloc{
            std::min(static_cast<size_type>(matrix.m_NrOfRows + matrix.m_NrOfRows / 4), c_MaxAllowedDimension)};
        const size_type c_ColumnCapacityToAlloc{
            std::min(static_cast<size_type>(matrix.m_NrOfColumns + matrix.m_NrOfColumns / 4), c_MaxAllowedDimension)};

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
            _remapMemory(matrix.m_NrOfRows, matrix.m_NrOfColumns);
        }

        _copyInitItems(matrix, 0, 0, 0, 0, m_NrOfRows, m_NrOfColumns);
    }
}

template <MatrixElementType T> void Matrix<T>::_moveAssignMatrix(Matrix<T>& matrix)
{
    if (&matrix != this)
    {
        _deallocMemory();

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
}

template <MatrixElementType T>
void Matrix<T>::_copyInitItems(const Matrix<T>& matrix, Matrix<T>::size_type matrixStartingRowNr,
                               Matrix<T>::size_type matrixColumnOffset, Matrix<T>::size_type startingRowNr,
                               Matrix<T>::size_type columnOffset, Matrix<T>::size_type nrOfRows,
                               Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value() && matrix.m_RowCapacityOffset.has_value())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr,
                                                   columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)},
             srcAbsRowNr{static_cast<size_type>(*matrix.m_RowCapacityOffset + matrixStartingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_copy_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns,
                                      m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_moveInitItems(Matrix<T>& matrix, Matrix<T>::size_type matrixStartingRowNr,
                               Matrix<T>::size_type matrixColumnOffset, Matrix<T>::size_type startingRowNr,
                               Matrix<T>::size_type columnOffset, Matrix<T>::size_type nrOfRows,
                               Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value() && matrix.m_RowCapacityOffset.has_value())
    {
        _externalClampSubMatrixSelectionParameters(matrix, matrixStartingRowNr, matrixColumnOffset, startingRowNr,
                                                   columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)},
             srcAbsRowNr{static_cast<size_type>(*matrix.m_RowCapacityOffset + matrixStartingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++srcAbsRowNr, ++absRowNr)
        {
            std::uninitialized_move_n(matrix.m_pBaseArrayPtr[srcAbsRowNr] + matrixColumnOffset, nrOfColumns,
                                      m_pBaseArrayPtr[absRowNr] + columnOffset);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_fillInitItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                               Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns, const T& value)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::uninitialized_fill_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns, value);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_defaultConstructInitItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                                           Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::uninitialized_default_construct_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_destroyItems(Matrix<T>::size_type startingRowNr, Matrix<T>::size_type columnOffset,
                              Matrix<T>::size_type nrOfRows, Matrix<T>::size_type nrOfColumns)
{
    if (m_RowCapacityOffset.has_value())
    {
        _clampSubMatrixSelectionParameters(startingRowNr, columnOffset, nrOfRows, nrOfColumns);

        for (size_type absRowNr{static_cast<size_type>(*m_RowCapacityOffset + startingRowNr)};
             absRowNr != *m_RowCapacityOffset + startingRowNr + nrOfRows; ++absRowNr)
        {
            std::destroy_n(m_pBaseArrayPtr[absRowNr] + columnOffset, nrOfColumns);
        }
    }
}

template <MatrixElementType T>
void Matrix<T>::_clampSubMatrixSelectionParameters(Matrix<T>::size_type& startingRowNr,
                                                   Matrix<T>::size_type& columnOffset, Matrix<T>::size_type& nrOfRows,
                                                   Matrix<T>::size_type& nrOfColumns)
{
    startingRowNr = std::clamp<size_type>(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp<size_type>(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp<size_type>(nrOfRows, 0u, m_NrOfRows - startingRowNr);
    nrOfColumns = std::clamp<size_type>(nrOfColumns, 0u, m_NrOfColumns - columnOffset);
}

template <MatrixElementType T>
void Matrix<T>::_externalClampSubMatrixSelectionParameters(
    const Matrix<T>& srcMatrix, Matrix<T>::size_type& srcStartingRowNr, Matrix<T>::size_type& srcColumnOffset,
    Matrix<T>::size_type& startingRowNr, Matrix<T>::size_type& columnOffset, Matrix<T>::size_type& nrOfRows,
    Matrix<T>::size_type& nrOfColumns)
{
    srcStartingRowNr = std::clamp<size_type>(srcStartingRowNr, 0u, srcMatrix.m_NrOfRows);
    srcColumnOffset = std::clamp<size_type>(srcColumnOffset, 0u, srcMatrix.m_NrOfColumns);
    startingRowNr = std::clamp<size_type>(startingRowNr, 0u, m_NrOfRows);
    columnOffset = std::clamp<size_type>(columnOffset, 0u, m_NrOfColumns);
    nrOfRows = std::clamp<size_type>(nrOfRows, 0u,
                                     std::min(srcMatrix.m_NrOfRows - srcStartingRowNr, m_NrOfRows - startingRowNr));
    nrOfColumns = std::clamp<size_type>(
        nrOfColumns, 0u, std::min(srcMatrix.m_NrOfColumns - srcColumnOffset, m_NrOfColumns - columnOffset));
}

template <MatrixElementType T> void* Matrix<T>::_convertToArray(Matrix<T>::size_type& nrOfElements)
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
#undef USE_SMALL_DIMENSIONS

#undef ITERATOR_TRAITS

#undef GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_FORWARD_NON_DIAG_BEGIN_ITERATOR
#undef GET_REVERSE_NON_DIAG_BEGIN_ITERATOR
#undef GET_FORWARD_NON_DIAG_END_ITERATOR
#undef GET_DIAG_BEGIN_ITERATOR
#undef GET_DIAG_RANDOM_ITERATOR
#undef GET_REVERSE_END_ZITERATOR
#undef GET_FORWARD_ROW_BEGIN_ZITERATOR
#undef GET_REVERSE_ROW_BEGIN_ZITERATOR
#undef GET_FORWARD_ROW_END_ZITERATOR
#undef GET_REVERSE_ROW_END_ZITERATOR
#undef GET_REVERSE_END_NITERATOR
#undef GET_FORWARD_COLUMN_BEGIN_NITERATOR
#undef GET_REVERSE_COLUMN_BEGIN_NITERATOR
#undef GET_FORWARD_COLUMN_END_NITERATOR
#undef GET_REVERSE_COLUMN_END_NITERATOR
#undef GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_END_DITERATOR_BY_DIAG_NUMBER
#undef GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX
#undef GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_END_MITERATOR_BY_DIAG_NUMBER
#undef GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER
#undef GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX
