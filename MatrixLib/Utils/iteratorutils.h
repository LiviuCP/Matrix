#ifndef ITERATORUTILS_H
#define ITERATORUTILS_H

#include <algorithm>
#include <cmath>

#include "../Matrix/matrixdimensions.h"

/* Retrieves the row and column number of the matrix based on given diagonal index:
   - the diagonal index is included in the result as it might be clamped in case it exceeds the given bounds (0 and
   maximum number of elements)
   - the mapping is matrix element type independent, instead of a matrix only its dimensions are required
   - null result for "empty matrix" (at least one provided matrix dimension is 0), no exceptions triggered

   Diagonal indexes are counted starting with the top left corner (element (0, 0)) and ending with bottom right corner
   (e.g. (4, 5) for a 5 x 6 matrix) as given in the example:

    0  2  5  9 14 19
    1  4  8 13 18 23
    3  7 12 17 22 26
    6 11 16 21 25 28
   10 15 20 24 27 29

   Diagonal numbers are counted starting with the top-left corner (diagonal 0) and ending with the bottom-right corner
   (diagonal nr_of_rows + nr_of_columns - 2). For the above example:
    - diagonal 0: index 0
    - diagonal 1: indexes 1, 2
    ...
    - diagonal 4: indexes 10-14 (max size diagonal)
    - diagonal 5: indexes 15-19 (max size diagonal)
    ...
    - diagonal 8: indexes 27-28
    - diagonal 9: index 29

   There are three scenarios/cases that would be taken into account:
    - case 1: the diagonal index is on a diagonal that precedes the first maximum size diagonal (top-left area)
      - a second order equation is being used for retrieving the diagonal number: diag_nr^2 + diag_nr - 2 * diag_index =
   0
      - the higher root is extracted as decimal value (the lower root would be negative and thus meaningless): diag_nr =
   (-1 + sqrt(1 + 8 * diag_index)) / 2
      - the equation result is (usually) decimal so it should be approximated with an integer that would either be the
   floor or the ceiling of the equation root (usually the floor)
        - if the int ceiling value solved the equation precisely and was different from the floor then this would be the
   required result
        - otherwise the floor yields the requested diagonal number
      - the equation has been elaborated based on the fact that the starting index of a diagonal from the top-left part
   equals the total number of elements located on the previous diagonals
        - the total number of elements preceding the diagonal number diag_nr is diag_nr * (diag_nr + 1) / 2, e.g. for
   diagonal number 3 (indexes 6, 7, 8, 9): 3 * 4 / 2 = 6 preceding elements
        - the index number of the first diagonal element equals the total number of elements from previous diagonals:
   first index on diagonal 3 is 6
        - this results in the above mentioned equation
        - the equation can be generalized and used for the other indexes of the diagonal too, but in that case a decimal
   number is obtained (which by using the above mentioned floor/ceiling approximations yields the required diagonal
   number)
    - case 2: the diagonal index is on a maximum size diagonal (center area)
        - use the fact that the maximum size diagonals have equal size
          - there can be one or more maximum diagonals
          - there can be only maximum diagonals for line, column or element matrixes
        - also use the total elements count of the preceding top-left diagonals
    - case 3: the diagonal index is on a diagonal following the maximum size diagonals (bottom-right area)
        - use symmetry to the top-left part, namely determine which is the symmetric top-left diagonal index
        - obtain the symmetric top-left coordinates and then by applying symmetry again (this time on coordinates) the
   required bottom-right row and column number would be obtained
*/
static std::pair<MatrixPoint, matrix_opt_diff_t> mapDiagonalIndexToRowAndColumnNr(matrix_size_t nrOfMatrixRows,
                                                                                  matrix_size_t nrOfMatrixColumns,
                                                                                  matrix_diff_t diagonalIndex)
{
    std::pair<MatrixPoint, matrix_opt_diff_t> result;

    if (nrOfMatrixRows > 0 && nrOfMatrixColumns > 0)
    {
        auto& [coordinates, diagonalIndexToConvert]{result};
        auto& [rowNr, columnNr]{coordinates};

        const matrix_size_t c_NrOfRows{nrOfMatrixRows};
        const matrix_size_t c_NrOfColumns{nrOfMatrixColumns};
        const matrix_diff_t c_TotalElementsCount{static_cast<matrix_diff_t>(static_cast<matrix_diff_t>(c_NrOfRows) * static_cast<matrix_diff_t>(c_NrOfColumns))};
        const matrix_size_t c_MaxDiagonalSize{std::min(c_NrOfRows, c_NrOfColumns)};

        const matrix_diff_t c_FirstMaxDiagonalNr{static_cast<matrix_diff_t>(c_MaxDiagonalSize - 1)};
        const matrix_diff_t c_ElementsCountBeforeFirstMaxDiagonal{static_cast<matrix_diff_t>(c_FirstMaxDiagonalNr * (c_FirstMaxDiagonalNr + 1) / 2)};

        // for this calculation symmetry is used: diagonals following max size diagonals are symmetric to diagonals
        // before max size diagonals
        const matrix_diff_t c_ElementsCountIncludingMaxDiagonals{static_cast<matrix_diff_t>(c_TotalElementsCount - c_ElementsCountBeforeFirstMaxDiagonal)};

        diagonalIndexToConvert = std::clamp<matrix_diff_t>(diagonalIndex, 0, c_TotalElementsCount - 1);

        if (diagonalIndexToConvert < c_ElementsCountBeforeFirstMaxDiagonal)
        {
            // case 1: index is in the top-left diagonals (before max diagonals)
            const double c_DecimalDiagonalNr{
                (std::sqrt(1.0 + 8.0 * static_cast<double>(*diagonalIndexToConvert)) - 1.0) / 2.0};
            const matrix_diff_t c_DiagonalNumberFloor{static_cast<matrix_diff_t>(std::floor(c_DecimalDiagonalNr))};
            const matrix_diff_t c_DiagonalNumberCeiling{static_cast<matrix_diff_t>(std::ceil(c_DecimalDiagonalNr))};

            /* Proving of the above mentioned equation for integer roots:
               - this verification is required in order to account for any rounding errors resulting in the calculation
               of c_DecimalDiagonalNr
               - more specifically a correction is required for the case when c_DecimalDiagonalNr should be precisely an
               integer according to the equation (e.g. 3), however due to a rounding error a decimal number slightly
               less then the required one (e.g. 2.999998) is obtained (which would yield 2 when using floor)
            */
            const matrix_diff_t c_DoubledCeilingIncremented{static_cast<matrix_diff_t>(2 * c_DiagonalNumberCeiling + 1)};
            const bool c_ShouldUseCeiling{c_DoubledCeilingIncremented * c_DoubledCeilingIncremented ==
                                          (8 * *diagonalIndexToConvert + 1)};

            const matrix_diff_t c_DiagonalNr{c_ShouldUseCeiling ? c_DiagonalNumberCeiling : c_DiagonalNumberFloor};
            const matrix_size_t c_DiagonalSize{static_cast<matrix_size_t>(c_DiagonalNr + 1)};
            const matrix_diff_t c_ElementsCountBeforeDiagonal{static_cast<matrix_diff_t>(c_DiagonalNr > 0 ? (c_DiagonalNr * (c_DiagonalNr + 1) / 2) : 0)};
            const matrix_size_t c_RelativeDiagonalIndex{
                static_cast<matrix_size_t>(*diagonalIndexToConvert - c_ElementsCountBeforeDiagonal)};
            rowNr = c_DiagonalSize - 1 - c_RelativeDiagonalIndex; // relative index should be between 0 and diagonal
                                                                  // size - 1, so no overflow risk
            columnNr = c_RelativeDiagonalIndex;
        }
        else if (diagonalIndexToConvert < c_ElementsCountIncludingMaxDiagonals)
        {
            // case 2: index is in the max size diagonals
            const matrix_diff_t c_DiagonalNr{static_cast<matrix_diff_t>(c_FirstMaxDiagonalNr + (*diagonalIndexToConvert - c_ElementsCountBeforeFirstMaxDiagonal) /
                                                 static_cast<matrix_diff_t>(c_MaxDiagonalSize))};
            const matrix_size_t c_RelativeDiagonalIndex{
                static_cast<matrix_size_t>(static_cast<matrix_size_t>(*diagonalIndexToConvert - c_ElementsCountBeforeFirstMaxDiagonal) % c_MaxDiagonalSize)}; // index relative to containing diagonal
            const matrix_size_t c_RelativeMaxDiagonalNr{static_cast<matrix_size_t>(
                c_DiagonalNr - c_FirstMaxDiagonalNr)}; // max diagonal number relative to the number of max diagonals
            rowNr = c_NrOfRows <= c_NrOfColumns ? c_NrOfRows - 1 - c_RelativeDiagonalIndex
                                                : c_NrOfColumns + c_RelativeMaxDiagonalNr - 1 - c_RelativeDiagonalIndex;
            columnNr = c_NrOfRows <= c_NrOfColumns ? c_RelativeMaxDiagonalNr + c_RelativeDiagonalIndex
                                                   : c_RelativeDiagonalIndex;
        }
        else
        {
            // case 3: index is in the bottom-right diagonals (after the max diagonals)
            const matrix_diff_t c_SymmetricalDiagonalIndex{static_cast<matrix_diff_t>(c_TotalElementsCount - 1 - *diagonalIndexToConvert)};
            const auto c_SymmetricalResult{mapDiagonalIndexToRowAndColumnNr(nrOfMatrixRows, nrOfMatrixColumns, c_SymmetricalDiagonalIndex)};
            const auto& [symmetricalCoordinates, _]{c_SymmetricalResult};
            const auto& [symmetricalRowNr, symmetricalColumnNr]{symmetricalCoordinates};
            rowNr = c_NrOfRows - 1 - *symmetricalRowNr;
            columnNr = c_NrOfColumns - 1 - *symmetricalColumnNr;
        }
    }

    return result;
}

/* This function retrieves the diagonal index based on the provided coordinates (row and column number)
   - same considerations as for previous function regarding type-independent relationship between
   diagonal index and coordinates
   - similar to the previous function, for "empty matrixes" a null value is returned
*/
static std::pair<matrix_opt_diff_t, MatrixPoint> mapRowAndColumnNrToDiagonalIndex(matrix_size_t nrOfMatrixRows,
                                                                                      matrix_size_t nrOfMatrixColumns,
                                                                                      MatrixPoint rowAndColumnNr)
{
    std::pair<matrix_opt_diff_t, MatrixPoint> result;

    if (nrOfMatrixRows > 0 && nrOfMatrixColumns > 0 && rowAndColumnNr.first.has_value() && rowAndColumnNr.second.has_value())
    {
        auto& [diagonalIndex, rowAndColumnNrToConvert]{result};
        auto& [rowNr, columnNr]{rowAndColumnNrToConvert};

        const matrix_size_t c_NrOfRows{nrOfMatrixRows};
        const matrix_size_t c_NrOfColumns{nrOfMatrixColumns};
        const matrix_diff_t c_TotalElementsCount{static_cast<matrix_diff_t>(static_cast<matrix_diff_t>(c_NrOfRows) * static_cast<matrix_diff_t>(c_NrOfColumns))};
        const matrix_diff_t c_NrOfDiagonals{static_cast<matrix_diff_t>(static_cast<matrix_diff_t>(c_NrOfRows) + static_cast<matrix_diff_t>(c_NrOfColumns) - 1)};
        const matrix_size_t c_MaxDiagonalSize{std::min(c_NrOfRows, c_NrOfColumns)};

        rowNr = std::clamp<matrix_size_t>(*rowAndColumnNr.first, 0, c_NrOfRows - 1);
        columnNr = std::clamp<matrix_size_t>(*rowAndColumnNr.second, 0, c_NrOfColumns - 1);

        const matrix_diff_t c_DiagonalNr{static_cast<matrix_diff_t>(static_cast<matrix_diff_t>(*rowNr) + static_cast<matrix_diff_t>(*columnNr))};
        const matrix_size_t c_RelativeDiagonalIndex{std::min<matrix_size_t>(c_NrOfRows - 1 - *rowNr, *columnNr)};
        const matrix_diff_t c_FirstMaxDiagonalNr{static_cast<matrix_diff_t>(c_MaxDiagonalSize - 1)};
        const matrix_diff_t c_NrOfMaxSizeDiagonals{static_cast<matrix_diff_t>(c_NrOfDiagonals - 2 * c_FirstMaxDiagonalNr)};
        const matrix_diff_t c_LastMaxDiagonalNr{static_cast<matrix_diff_t>(c_FirstMaxDiagonalNr + c_NrOfMaxSizeDiagonals - 1)};

        if (c_DiagonalNr < c_FirstMaxDiagonalNr)
        {
            const matrix_diff_t c_ElementsCountBeforeDiagonal{static_cast<matrix_diff_t>(c_DiagonalNr * (c_DiagonalNr + 1) / 2)};
            diagonalIndex = c_ElementsCountBeforeDiagonal + static_cast<matrix_diff_t>(c_RelativeDiagonalIndex);
        }
        else if (c_DiagonalNr <= c_LastMaxDiagonalNr)
        {
            const matrix_diff_t c_ElementsCountBeforeFirstMaxDiagonal{static_cast<matrix_diff_t>(c_FirstMaxDiagonalNr * (c_FirstMaxDiagonalNr + 1) / 2)};
            const matrix_diff_t c_ElementsCountOnPrecedingMaxDiagonals{static_cast<matrix_diff_t>((c_DiagonalNr - c_FirstMaxDiagonalNr) * static_cast<matrix_diff_t>(c_MaxDiagonalSize))};
            diagonalIndex = c_ElementsCountBeforeFirstMaxDiagonal + c_ElementsCountOnPrecedingMaxDiagonals +
                            static_cast<matrix_diff_t>(c_RelativeDiagonalIndex);
        }
        else
        {
            const matrix_size_t c_SymmetricalRowNr{static_cast<matrix_size_t>(c_NrOfRows - 1 - *rowNr)};
            const matrix_size_t c_SymmetricalColumnNr{static_cast<matrix_size_t>(c_NrOfColumns - 1 - *columnNr)};
            const auto c_SymmetricalResult{
                mapRowAndColumnNrToDiagonalIndex(nrOfMatrixRows, nrOfMatrixColumns, {c_SymmetricalRowNr, c_SymmetricalColumnNr})};
            const auto& [symmetricalDiagonalIndex, _]{c_SymmetricalResult};
            diagonalIndex = c_TotalElementsCount - 1 - *symmetricalDiagonalIndex;
        }
    }

    return result;
}

/* These macros are meant solely meant for internal use within the Matrix class */

// macros used for declaring iterator class members

#define COMMON_PUBLIC_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DifferenceType, SizeType) \
    /* Matrix should be allowed to use the private constructor of the iterator, but no other class should have this "privilege" */ \
    friend class Matrix<IterableType>; \
\
    /* all these are required for STL compatibility */ \
    using iterator_category = std::random_access_iterator_tag; \
    using value_type = IterableType; \
    using difference_type = DifferenceType; \
    using pointer = IterableType**; \
\
    IteratorType& operator++(); \
    IteratorType operator++(int unused); \
    IteratorType& operator--(); \
    IteratorType operator--(int unused); \
\
    IteratorType& operator+=(DifferenceType offset); \
    IteratorType& operator-=(DifferenceType offset); \
\
    DifferenceType operator-(const IteratorType& it) const; \
\
    auto operator<=>(const IteratorType& it) const; \
    bool operator==(const IteratorType& it) const; \
\
    std::optional<SizeType> getRowNr() const; \
    std::optional<SizeType> getColumnNr() const; \
\
    /* creates "empty" iterator (no position information, no linkage to a non-empty matrix); can be linked to any empty matrix */ \
    IteratorType(); \
\
    friend Matrix<IterableType>::IteratorType operator+(const Matrix<IterableType>::IteratorType& it, Matrix<IterableType>::IteratorType::difference_type offset) \
    { \
        typename Matrix<IterableType>::IteratorType temp{it}; \
        temp += offset; \
        return temp; \
    } \
\
    friend Matrix<IterableType>::IteratorType operator+(Matrix<IterableType>::IteratorType::difference_type offset, const Matrix<IterableType>::IteratorType& it) \
    { \
        return it + offset; \
    } \
\
    friend Matrix<IterableType>::IteratorType operator-(const Matrix<IterableType>::IteratorType& it, Matrix<IterableType>::IteratorType::difference_type offset) \
    { \
        typename Matrix<IterableType>::IteratorType temp{it}; \
        temp -= offset; \
        return temp; \
    }

#define COMMON_PUBLIC_NON_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = IterableType&; \
\
    IterableType& operator*() const; \
    IterableType* operator->() const; \
    IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_CONST_ITERATOR_CODE_DECLARATIONS(IterableType, DifferenceType) \
    using reference = const IterableType&; \
\
    const IterableType& operator*() const; \
    const IterableType* operator->() const; \
    const IterableType& operator[](DifferenceType index) const;

#define COMMON_PUBLIC_DIAG_ITERATOR_CODE_DECLARATIONS(DiffType, SizeType) \
    DiffType getDiagonalNr() const; \
    std::optional<SizeType> getDiagonalIndex() const;

#define COMMON_PRIVATE_ITERATOR_CODE_DECLARATIONS(IterableType) \
    void _increment(); \
    void _decrement(); \
    bool _isEmpty() const; \
\
    IterableType** m_pMatrixPtr;

#define COMMON_PRIVATE_NON_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, std::optional<SizeType> rowNr, std::optional<SizeType> columnNr); \
\
    std::optional<SizeType> m_RowNr; \
    std::optional<SizeType> m_ColumnNr; \
    SizeType m_NrOfMatrixRows; \
    SizeType m_NrOfMatrixColumns;

#define COMMON_PRIVATE_DIAG_ITERATOR_CODE_DECLARATIONS(IteratorType, IterableType, DiffType, SizeType) \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, std::optional<SizeType> rowNr, std::optional<SizeType> columnNr); \
    IteratorType(IterableType** pMatrixPtr, SizeType nrOfMatrixRows, SizeType nrOfMatrixColumns, const std::pair<DiffType, std::optional<SizeType>>& diagonalNrAndIndex); \
\
    std::optional<SizeType> m_DiagonalIndex;    /* relative index within diagonal */ \
    DiffType m_DiagonalNr;   /* index of the diagonal within matrix */ \
    SizeType m_DiagonalSize;     /* number of elements contained within diagonal */

// generic iterator macros

#define ITERATOR_PRE_INCREMENT() \
    _increment(); \
    return *this;

#define ITERATOR_POST_INCREMENT(IteratorType, unusedVar) \
    (void) unusedVar; \
    IteratorType iterator{*this}; \
\
    _increment(); \
\
    return iterator;

#define ITERATOR_PRE_DECREMENT() \
    _decrement(); \
    return *this;

#define ITERATOR_POST_DECREMENT(IteratorType, unusedVar) \
    (void) unusedVar; \
    IteratorType iterator{*this}; \
\
    _decrement(); \
\
    return iterator;

// common ZIterator/NIterator macros

#define CONSTRUCT_FORWARD_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, \
                                            pMatrixPtr, matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixPrimaryDimension > size_type{0} && matrixSecondaryDimension > size_type{0} && matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value() && \
            ((matrixPrimaryCoordinate < matrixPrimaryDimension && matrixSecondaryCoordinate < matrixSecondaryDimension) || \
             (matrixPrimaryCoordinate == matrixPrimaryDimension - size_type{1} && matrixSecondaryCoordinate == matrixSecondaryDimension))) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorPrimaryDimension = matrixPrimaryDimension; \
            mIteratorSecondaryDimension = matrixSecondaryDimension; \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorPrimaryDimension = size_type{0}; \
        mIteratorSecondaryDimension = size_type{0}; \
    }

#define CONSTRUCT_REVERSE_NON_DIAG_ITERATOR(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, \
                                            pMatrixPtr, matrixPrimaryDimension, matrixSecondaryDimension, matrixPrimaryCoordinate, matrixSecondaryCoordinate) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixPrimaryDimension > size_type{0} && matrixSecondaryDimension > size_type{0} && matrixPrimaryCoordinate.has_value() && \
            ((size_type{0} == matrixPrimaryCoordinate && !matrixSecondaryCoordinate.has_value()) || \
             (matrixPrimaryCoordinate < matrixPrimaryDimension && matrixSecondaryCoordinate.has_value() && matrixSecondaryCoordinate < matrixSecondaryDimension))) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorPrimaryDimension = matrixPrimaryDimension; \
            mIteratorSecondaryDimension = matrixSecondaryDimension; \
            mIteratorPrimaryCoordinate = matrixPrimaryCoordinate; \
            mIteratorSecondaryCoordinate = matrixSecondaryCoordinate; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorPrimaryDimension = size_type{0}; \
        mIteratorSecondaryDimension = size_type{0}; \
    }

#define FORWARD_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                       mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (!_isEmpty()) \
    { \
        const diff_type normalizedScalarValue = Sign scalarValue; \
        const diff_type c_CurrentIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                              static_cast<diff_type>(*mIteratorSecondaryCoordinate))}; \
        const diff_type c_ResultingIndex{normalizedScalarValue < diff_type{0} && std::abs(normalizedScalarValue) > c_CurrentIndex ? diff_type{0} : static_cast<diff_type>(c_CurrentIndex + normalizedScalarValue)}; \
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) * static_cast<diff_type>(mIteratorSecondaryDimension))}; \
\
        mIteratorPrimaryCoordinate = c_ResultingIndex < c_UpperBound ? static_cast<size_type>(c_ResultingIndex / static_cast<diff_type>(mIteratorSecondaryDimension)) : mIteratorPrimaryDimension - size_type{1}; \
        mIteratorSecondaryCoordinate = c_ResultingIndex < c_UpperBound ? static_cast<size_type>(c_ResultingIndex % static_cast<diff_type>(mIteratorSecondaryDimension)) : mIteratorSecondaryDimension; \
    } \
\
    return *this;

#define REVERSE_NON_DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                       mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, Sign, scalarValue) \
    if (!_isEmpty()) \
    { \
        const diff_type normalizedScalarValue = Sign scalarValue; \
        const std::optional<diff_type> c_CurrentIndex{mIteratorSecondaryCoordinate.has_value() ? std::optional{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                                                                                                      static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                                                                                                      static_cast<diff_type>(*mIteratorSecondaryCoordinate))} \
                                                                                               : std::nullopt}; \
        std::optional<diff_type> resultingIndex; \
\
        if (c_CurrentIndex.has_value()) \
        { \
            if (normalizedScalarValue >= diff_type{0} || std::abs(normalizedScalarValue) <= c_CurrentIndex) \
            { \
                resultingIndex = *c_CurrentIndex + normalizedScalarValue; \
            } \
        } \
        else \
        { \
            if (normalizedScalarValue > diff_type{0}) \
            { \
                resultingIndex = normalizedScalarValue - diff_type{1}; \
            } \
        } \
\
        const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) * static_cast<diff_type>(mIteratorSecondaryDimension))}; \
\
        mIteratorPrimaryCoordinate = !resultingIndex.has_value() ? size_type{0} \
                                                                 : resultingIndex >= c_UpperBound ? static_cast<size_type>(mIteratorPrimaryDimension - size_type{1}) \
                                                                                                  : static_cast<size_type>(*resultingIndex / static_cast<diff_type>(mIteratorSecondaryDimension)); \
        mIteratorSecondaryCoordinate = !resultingIndex.has_value() ? std::nullopt \
                                                                   : resultingIndex >= c_UpperBound ? std::optional{static_cast<size_type>(mIteratorSecondaryDimension - size_type{1})} \
                                                                                                    : std::optional{static_cast<size_type>(*resultingIndex % static_cast<diff_type>(mIteratorSecondaryDimension))}; \
    } \
\
    return *this;

#define FORWARD_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                     mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || \
                          mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    diff_type result{0}; \
\
    if (!_isEmpty()) \
    { \
        const diff_type c_FirstItIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                              static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                              static_cast<diff_type>(*mIteratorSecondaryCoordinate))}; \
\
        const diff_type c_SecondItIndex{static_cast<diff_type>(static_cast<diff_type>(*secondIterator.mIteratorPrimaryCoordinate) * \
                                                               static_cast<diff_type>(secondIterator.mIteratorSecondaryDimension) + \
                                                               static_cast<diff_type>(*secondIterator.mIteratorSecondaryCoordinate))}; \
\
        result = c_FirstItIndex - c_SecondItIndex; \
    } \
\
    return result;

#define REVERSE_NON_DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                     mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorPrimaryDimension != secondIterator.mIteratorPrimaryDimension || \
                          mIteratorSecondaryDimension != secondIterator.mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    diff_type result{0}; \
\
    if (!_isEmpty()) \
    { \
        const std::optional<diff_type> c_FirstItIndex{mIteratorSecondaryCoordinate.has_value() ? std::optional{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                                                                                                      static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                                                                                                      static_cast<diff_type>(*mIteratorSecondaryCoordinate))} \
                                                                                               : std::nullopt}; \
        const std::optional<diff_type> c_SecondItIndex{secondIterator.mIteratorSecondaryCoordinate.has_value() ? std::optional{static_cast<diff_type>(static_cast<diff_type>(*secondIterator.mIteratorPrimaryCoordinate) * \
                                                                                                                                                      static_cast<diff_type>(secondIterator.mIteratorSecondaryDimension) + \
                                                                                                                                                      static_cast<diff_type>(*secondIterator.mIteratorSecondaryCoordinate))} \
                                                                                                               : std::nullopt}; \
\
        if (c_FirstItIndex.has_value() && c_SecondItIndex.has_value()) \
        { \
            result = *c_SecondItIndex - *c_FirstItIndex; \
        } \
        else if (!c_FirstItIndex.has_value() && c_SecondItIndex.has_value()) \
        { \
            result = *c_SecondItIndex + diff_type{1}; \
        } \
        else if (c_FirstItIndex.has_value() && !c_SecondItIndex.has_value()) \
        { \
            result = diff_type{-1} - *c_FirstItIndex; \
        } \
    } \
\
    return result;


#define FORWARD_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, firstIterator, secondIterator) \
    CHECK_ERROR_CONDITION((firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr || \
                          (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension || \
                          (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = std::strong_ordering::equal; \
\
    /* both iterators are either empty or not */ \
    if (!(firstIterator)._isEmpty()) \
    { \
        result = *(firstIterator).mIteratorPrimaryCoordinate <=> *(secondIterator).mIteratorPrimaryCoordinate; \
\
        if (std::strong_ordering::equal == result) \
        { \
            result = *(firstIterator).mIteratorSecondaryCoordinate <=> *(secondIterator).mIteratorSecondaryCoordinate; \
        } \
    } \
\
    return result;

#define REVERSE_NON_DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, firstIterator, secondIterator) \
    CHECK_ERROR_CONDITION((firstIterator).mpIteratorPtr != (secondIterator).mpIteratorPtr || \
                          (firstIterator).mIteratorPrimaryDimension != (secondIterator).mIteratorPrimaryDimension || \
                          (firstIterator).mIteratorSecondaryDimension != (secondIterator).mIteratorSecondaryDimension, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    auto result = std::strong_ordering::equal; \
\
    /* both iterators are either empty or not */ \
    if (!(firstIterator)._isEmpty()) \
    { \
        result = *(secondIterator).mIteratorPrimaryCoordinate <=> *(firstIterator).mIteratorPrimaryCoordinate; \
\
        if (std::strong_ordering::equal == result) \
        { \
            if ((firstIterator).mIteratorSecondaryCoordinate.has_value() && (secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                /* for reverse iterators greater coordinates mean smaller iterator */ \
                result = *(secondIterator).mIteratorSecondaryCoordinate <=> *(firstIterator).mIteratorSecondaryCoordinate; \
            } \
            else if ((firstIterator).mIteratorSecondaryCoordinate.has_value() && !(secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                result = std::strong_ordering::less; \
            } \
            else if (!(firstIterator).mIteratorSecondaryCoordinate.has_value() && (secondIterator).mIteratorSecondaryCoordinate.has_value()) \
            { \
                result = std::strong_ordering::greater; \
            } \
        } \
    } \
\
    return result;

#define NON_DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorRowsCount, mIteratorColumnsCount, mIteratorRowNr, mIteratorColumnNr, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorRowsCount != secondIterator.mIteratorRowsCount || \
                          mIteratorColumnsCount != secondIterator.mIteratorColumnsCount, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return (mIteratorRowNr == secondIterator.mIteratorRowNr && mIteratorColumnNr == secondIterator.mIteratorColumnNr);

#define FORWARD_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define REVERSE_NON_DIAG_ITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return mpIteratorPtr[*mIteratorRowNr][*mIteratorColumnNr];

#define FORWARD_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorSecondaryCoordinate == mIteratorSecondaryDimension, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr); \

#define REVERSE_NON_DIAG_ITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorSecondaryDimension, mIteratorRowNr, mIteratorColumnNr, mIteratorSecondaryCoordinate) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
    return (mpIteratorPtr[*mIteratorRowNr] + *mIteratorColumnNr); \

#define FORWARD_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty(), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_CurrentIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                          static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                          static_cast<diff_type>(*mIteratorSecondaryCoordinate))}; \
\
    CHECK_ERROR_CONDITION(arrayIndex < diff_type{0} && std::abs(arrayIndex) > c_CurrentIndex, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + arrayIndex)}; \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) * static_cast<diff_type>(mIteratorSecondaryDimension))}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension][c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define REVERSE_NON_DIAG_ITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, \
                                                    mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate, FirstOperator, SecondOperator, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || !mIteratorSecondaryCoordinate.has_value(), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_CurrentIndex{static_cast<diff_type>(static_cast<diff_type>(*mIteratorPrimaryCoordinate) * \
                                                          static_cast<diff_type>(mIteratorSecondaryDimension) + \
                                                          static_cast<diff_type>(*mIteratorSecondaryCoordinate))}; \
    const diff_type c_NormalizedIndex{static_cast<diff_type>(-arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_NormalizedIndex < diff_type{0} && std::abs(c_NormalizedIndex) > c_CurrentIndex, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const diff_type c_ResultingIndex{static_cast<diff_type>(c_CurrentIndex + c_NormalizedIndex)}; \
    const diff_type c_UpperBound{static_cast<diff_type>(static_cast<diff_type>(mIteratorPrimaryDimension) * static_cast<diff_type>(mIteratorSecondaryDimension))}; \
    (void) c_UpperBound; \
\
    CHECK_ERROR_CONDITION(c_ResultingIndex >= c_UpperBound, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    return mpIteratorPtr[c_ResultingIndex FirstOperator mIteratorSecondaryDimension][c_ResultingIndex SecondOperator mIteratorSecondaryDimension];

#define FORWARD_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate != mIteratorSecondaryDimension || mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - 1))) \
    { \
        mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + size_type{1}; \
\
        if (mIteratorSecondaryCoordinate == mIteratorSecondaryDimension && mIteratorPrimaryCoordinate != (mIteratorPrimaryDimension - size_type{1})) \
        { \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - mIteratorSecondaryDimension; \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + size_type{1}; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_INCREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorSecondaryCoordinate.has_value() || mIteratorPrimaryCoordinate > size_type{0})) \
    { \
        if (mIteratorSecondaryCoordinate > size_type{0}) \
        { \
           mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - size_type{1}; \
        } \
        else \
        { \
            mIteratorSecondaryCoordinate.reset(); \
        } \
 \
        if (!mIteratorSecondaryCoordinate.has_value() && mIteratorPrimaryCoordinate > size_type{0}) \
        { \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - size_type{1}; \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - size_type{1}; \
        } \
    }

#define FORWARD_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty() && (mIteratorPrimaryCoordinate > size_type{0} || mIteratorSecondaryCoordinate > size_type{0})) \
    { \
        if(0 == mIteratorSecondaryCoordinate) \
        { \
            mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate - size_type{1}; \
            mIteratorSecondaryCoordinate = mIteratorSecondaryDimension - size_type{1}; \
        } \
        else \
        { \
            mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate - size_type{1}; \
        } \
    }

#define REVERSE_NON_DIAG_ITERATOR_DO_DECREMENT(mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (!_isEmpty()) \
    { \
        if (!mIteratorSecondaryCoordinate.has_value()) \
        { \
            mIteratorSecondaryCoordinate = size_type{0}; /* decrement from end iterator */ \
        } \
        else if (mIteratorPrimaryCoordinate < mIteratorPrimaryDimension - size_type{1} || mIteratorSecondaryCoordinate < mIteratorSecondaryDimension - size_type{1}) \
        { \
            if(mIteratorSecondaryCoordinate == mIteratorSecondaryDimension - size_type{1}) \
            { \
                mIteratorPrimaryCoordinate = *mIteratorPrimaryCoordinate + size_type{1}; \
                mIteratorSecondaryCoordinate = size_type{0}; \
            } \
            else \
            { \
                mIteratorSecondaryCoordinate = *mIteratorSecondaryCoordinate + size_type{1}; \
            } \
        } \
    }


#define CHECK_FORWARD_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorPrimaryDimension > size_type{0} && mIteratorSecondaryDimension > size_type{0} && mIteratorPrimaryCoordinate.has_value() && mIteratorSecondaryCoordinate.has_value()); \
    } \
    else \
    { \
        assert(size_type{0} == mIteratorPrimaryDimension && size_type{0} == mIteratorSecondaryDimension && !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value()); \
    } \
\
    return !mpIteratorPtr;

#define CHECK_REVERSE_NON_DIAG_ITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorPrimaryDimension, mIteratorSecondaryDimension, mIteratorPrimaryCoordinate, mIteratorSecondaryCoordinate) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorPrimaryDimension > size_type{0} && mIteratorSecondaryDimension > size_type{0} && mIteratorPrimaryCoordinate.has_value()); \
    } \
    else \
    { \
        assert(size_type{0} == mIteratorPrimaryDimension && size_type{0} == mIteratorSecondaryDimension && !mIteratorPrimaryCoordinate.has_value() && !mIteratorSecondaryCoordinate.has_value()); \
    } \
\
    return !mpIteratorPtr;

#define GET_FORWARD_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, size_type{0}};

#define GET_REVERSE_NON_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, \
                        (mMatrixNrOfRows > size_type{0} ? std::optional{mMatrixNrOfRows - size_type{1}} : std::nullopt), \
                        (mMatrixNrOfColumns > size_type{0} ? std::optional{mMatrixNrOfColumns - size_type{1}} : std::nullopt)};

#define GET_NON_DIAG_ITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows || matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::INVALID_ELEMENT_INDEX]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// common DIterator/MIterator macros

#define DIAG_ITERATOR_ADD_SCALAR_TO_ITSELF(mIteratorDiagonalSize, mIteratorDiagonalIndex, Sign, scalarValue) \
    const diff_type c_NormalizedScalarValue{static_cast<diff_type>(Sign scalarValue)}; \
    const size_type c_ResultingIndex{static_cast<size_type>((c_NormalizedScalarValue < diff_type{0} && static_cast<size_type>(std::abs(c_NormalizedScalarValue)) > mIteratorDiagonalIndex) ? size_type{0} \
                                                                                                        : static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + c_NormalizedScalarValue))}; \
    mIteratorDiagonalIndex = std::min(c_ResultingIndex, mIteratorDiagonalSize); \
\
    return *this;

#define DIAG_ITERATOR_DO_INCREMENT(mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    if (!_isEmpty() && mIteratorDiagonalIndex < mIteratorDiagonalSize) \
    { \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex + size_type{1}; \
    }

#define DIAG_ITERATOR_DO_DECREMENT(mIteratorDiagonalIndex) \
    if (!_isEmpty() && mIteratorDiagonalIndex > size_type{0}) \
    { \
        mIteratorDiagonalIndex = *mIteratorDiagonalIndex - size_type{1}; \
    }

#define DIAG_ITERATOR_COMPUTE_DIFFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return !_isEmpty() ? (static_cast<diff_type>(*mIteratorDiagonalIndex) - static_cast<diff_type>(*secondIterator.mIteratorDiagonalIndex)) : diff_type{0}; \

#define DIAG_ITERATOR_CHECK_EQUIVALENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return !_isEmpty() ? *mIteratorDiagonalIndex <=> *secondIterator.mIteratorDiagonalIndex : std::strong_ordering::equal;

#define DIAG_ITERATOR_CHECK_EQUALITY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, secondIterator) \
    CHECK_ERROR_CONDITION(mpIteratorPtr != secondIterator.mpIteratorPtr || \
                          mIteratorDiagonalSize != secondIterator.mIteratorDiagonalSize || \
                          mIteratorDiagonalNr != secondIterator.mIteratorDiagonalNr, \
                          Matr::errorMessages[Matr::Errors::INCOMPATIBLE_ITERATORS]); \
\
    return _isEmpty() || mIteratorDiagonalIndex == secondIterator.mIteratorDiagonalIndex;

#define GET_DIAG_BEGIN_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, size_type{0}}};

#define GET_DIAG_RANDOM_ITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr};

// specialized ZIterator macros

#define GET_FORWARD_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}), mMatrixNrOfColumns};

#define GET_REVERSE_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, std::nullopt};

#define GET_FORWARD_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, size_type{0}};

#define GET_REVERSE_ROW_BEGIN_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    /* number of columns should be > 0, see above error condition implying matrix should not be empty*/ \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, (mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} : size_type{0})};

#define GET_FORWARD_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    /* no overflow, number of rows should be greater than 0, see above error condition implying matrix should not be empty */ \
    return matrixRowNr < mMatrixNrOfRows - 1 ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr + size_type{1}, size_type{0}} \
                                             : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, mMatrixNrOfColumns};

#define GET_REVERSE_ROW_END_ZITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
\
    /* When matrixRowNr > 0 : number of columns should be > 0, see above error condition implying matrix should not be empty */ \
    return matrixRowNr > size_type{0} ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr - size_type{1}, (mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} \
                                                                                                                                                                        : size_type{0})} \
                                      : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, std::nullopt};

// specialized NIterator macros

#define GET_FORWARD_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns,  mMatrixNrOfRows, mMatrixNrOfColumns > size_type{0} ? mMatrixNrOfColumns - size_type{1} : size_type{0}};

#define GET_REVERSE_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns) \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, size_type{0}};

#define GET_FORWARD_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, matrixColumnNr};

#define GET_REVERSE_COLUMN_BEGIN_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    /* number of rows should be > 0, see above error condition implying matrix should not be empty */ \
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}), matrixColumnNr};

#define GET_FORWARD_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    /* no overflow, number of columns should be greater than 0, see above error condition implying matrix should not be empty */ \
    return matrixColumnNr < mMatrixNrOfColumns - size_type{1} ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, size_type{0}, matrixColumnNr + size_type{1}} \
                                                              : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, mMatrixNrOfRows, matrixColumnNr};

#define GET_REVERSE_COLUMN_END_NITERATOR(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    /* When matrixColumnNr > 0 : number of rows should be > 0, see above error condition implying matrix should not be empty */ \
    return matrixColumnNr > size_type{0} ? IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, (mMatrixNrOfRows > size_type{0} ? mMatrixNrOfRows - size_type{1} : size_type{0}), matrixColumnNr - size_type{1}} \
                                         : IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, std::nullopt, size_type{0}};

// specialized DIterator macros

#define CONSTRUCT_FORWARD_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr); \
            mIteratorDiagonalIndex = std::min(*matrixRowNr, *matrixColumnNr); \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex + std::min(matrixRowsCount - *matrixRowNr, matrixColumnsCount - *matrixColumnNr); \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
    }

#define CONSTRUCT_FORWARD_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize{0}; \
        \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr{static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))}; \
            const diff_type c_MaxDiagonalNr{static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1})}; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                resultingDiagonalSize = diagonalNr < diff_type{0} ? std::min<size_type>(matrixRowsCount - static_cast<size_type>(-diagonalNr), matrixColumnsCount) \
                                                                  : std::min<size_type>(matrixColumnsCount - static_cast<size_type>(diagonalNr), matrixRowsCount); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        const bool c_AreValidDimensions{matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0}}; \
        assert(c_AreValidDimensions); \
\
        if (c_AreValidDimensions) \
        { \
            const bool c_AreRowAndColumnNrValid{(!matrixRowNr.has_value() && !matrixColumnNr.has_value()) || \
                                                (!matrixRowNr.has_value() && matrixColumnNr < matrixColumnsCount - size_type{1}) || \
                                                (!matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount - size_type{1}) || \
                                                (matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)}; \
            assert(c_AreRowAndColumnNrValid); \
\
            if (c_AreRowAndColumnNrValid) \
            { \
                mpIteratorPtr = pMatrixPtr; \
                mIteratorDiagonalNr = matrixRowNr.has_value() && matrixColumnNr.has_value() ? static_cast<diff_type>(*matrixColumnNr) - static_cast<diff_type>(*matrixRowNr) \
                                                                                            : matrixRowNr.has_value() ? diff_type{-1} - static_cast<diff_type>(*matrixRowNr) \
                                                                                                                      : matrixColumnNr.has_value() ? static_cast<diff_type>(*matrixColumnNr) + diff_type{1} \
                                                                                                                                                   : diff_type{0}; \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                mIteratorDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr) \
                                                                              : (mIteratorDiagonalNr <= diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr); \
                mIteratorDiagonalIndex = mIteratorDiagonalNr < diff_type{0} ? (matrixColumnNr.has_value() ? mIteratorDiagonalSize - size_type{1} - *matrixColumnNr : mIteratorDiagonalSize) \
                                                                            : (matrixRowNr.has_value() ? mIteratorDiagonalSize - size_type{1} - *matrixRowNr : mIteratorDiagonalSize); \
                nonEmptyIteratorConstructed = true; \
            } \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
    }

#define CONSTRUCT_REVERSE_DITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize{0}; \
        \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr{static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))}; \
            const diff_type c_MaxDiagonalNr{static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1}); \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                const size_type c_MaxSize{std::max(matrixRowsCount, matrixColumnsCount)}; \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                resultingDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr) \
                                                                              : (mIteratorDiagonalNr <= diff_type{0} ? matrixRowsCount + mIteratorDiagonalNr : matrixColumnsCount - mIteratorDiagonalNr); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
    }

#define FORWARD_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? *mIteratorDiagonalIndex : static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_DITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                            : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}) \
                                                               : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? *mIteratorDiagonalIndex : static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_DITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                       : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}) \
                                                                          : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} && static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : c_ResultingDiagonalIndex}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < diff_type{0} ? c_ResultingDiagonalIndex : static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_DITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} && static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    /* no overflow risk, diagonal index is less than diagonal size */ \
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                        : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1})}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1}) \
                                                                           : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} + static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, size_type{0}}};

#define GET_END_DITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < diff_type{0} ? static_cast<size_type>(-matrixDiagonalNr) : size_type{0}}; \
    const size_type c_BeginColumnNr{matrixDiagonalNr < diff_type{0} ? size_type{0} : static_cast<size_type>(matrixDiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error condition) */ \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}}; \

#define GET_END_DITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(matrixColumnNr) - static_cast<diff_type>(matrixRowNr))}; \
\
    const size_type c_BeginRowNr{c_DiagonalNr < diff_type{0} ? static_cast<size_type>(-c_DiagonalNr) : size_type{0}}; \
    const size_type c_BeginColumnNr{c_DiagonalNr < diff_type{0} ? size_type{0} : static_cast<size_type>(c_DiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error conditions) */ \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_DITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(iteratorDiagonalNr < (diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          iteratorDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{iteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(-iteratorDiagonalNr) : size_type{0}}; \
    const size_type c_BeginColumnNr{iteratorDiagonalNr < diff_type{0} ? size_type{0} : static_cast<size_type>(iteratorDiagonalNr)}; \
\
    /* no overflow risk, begin row number and begin column number determined based on diagonal number which should not exceed total number of rows/columns (see above error condition) */ \
    const size_type c_DiagonalSize{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(mMatrixNrOfColumns - c_BeginColumnNr))}; \
\
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};

#define CHECK_DITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorDiagonalSize > size_type{0} && mIteratorDiagonalIndex.has_value()); \
    } \
    else \
    { \
        assert(diff_type{0} == mIteratorDiagonalNr && size_type{0} == mIteratorDiagonalSize && !mIteratorDiagonalIndex.has_value()); \
    } \
\
    return !mpIteratorPtr;

// specialized MIterator macros

#define CONSTRUCT_FORWARD_MITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixRowNr.has_value() && matrixColumnNr.has_value() && matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - static_cast<diff_type>(*matrixColumnNr)) - static_cast<diff_type>(*matrixRowNr) - diff_type{1}; \
            mIteratorDiagonalIndex = std::min<size_type>(*matrixRowNr, matrixColumnsCount - *matrixColumnNr - size_type{1}); \
            mIteratorDiagonalSize = *mIteratorDiagonalIndex + std::min<size_type>(matrixRowsCount - *matrixRowNr, *matrixColumnNr + size_type{1}); \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
        mIteratorColumnsCount = size_type{0}; \
    }

#define CONSTRUCT_FORWARD_MITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize{0}; \
        \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr{static_cast<diff_type>(diff_type{1} - static_cast<diff_type>(matrixRowsCount))}; \
            const diff_type c_MaxDiagonalNr{static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - diff_type{1})}; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                resultingDiagonalSize = diagonalNr < diff_type{0} ? std::min<size_type>(matrixRowsCount - static_cast<size_type>(-diagonalNr), matrixColumnsCount) \
                                                                  : std::min<size_type>(matrixColumnsCount - static_cast<size_type>(diagonalNr), matrixRowsCount); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
        mIteratorColumnsCount = size_type{0}; \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_ROW_AND_COLUMN_NR(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, matrixRowNr, matrixColumnNr) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && matrixColumnNr.has_value() && matrixColumnNr <= matrixColumnsCount) \
        { \
            const bool c_IsValidRowNr{(!matrixRowNr.has_value() && matrixColumnNr > size_type{0}) || \
                                       (matrixRowNr.has_value() && ((matrixRowNr < matrixRowsCount - size_type{1} && matrixColumnNr == matrixColumnsCount) || \
                                                                    (matrixRowNr < matrixRowsCount && matrixColumnNr < matrixColumnsCount)))}; \
            assert(c_IsValidRowNr); \
\
            if (c_IsValidRowNr) \
            { \
                mpIteratorPtr = pMatrixPtr; \
                mIteratorDiagonalNr = matrixRowNr.has_value() ? static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - static_cast<diff_type>(*matrixColumnNr)) - static_cast<diff_type>(*matrixRowNr) - diff_type{1} \
                                                              : static_cast<diff_type>(static_cast<diff_type>(matrixColumnsCount) - static_cast<diff_type>(*matrixColumnNr)); \
\
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                mIteratorDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (mIteratorDiagonalNr < diff_type{0} ? matrixRowsCount - static_cast<size_type>(-mIteratorDiagonalNr) : matrixColumnsCount + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                              : (mIteratorDiagonalNr <= diff_type{0} ? matrixRowsCount + static_cast<size_type>(mIteratorDiagonalNr) : matrixColumnsCount - static_cast<size_type>(mIteratorDiagonalNr)); \
                mIteratorDiagonalIndex = mIteratorDiagonalNr < diff_type{0} ? mIteratorDiagonalSize - matrixColumnsCount + *matrixColumnNr \
                                                                            : matrixRowNr.has_value() ? mIteratorDiagonalSize - size_type{1} - *matrixRowNr \
                                                                                                      : mIteratorDiagonalSize; \
                mIteratorColumnsCount = matrixColumnsCount; \
                nonEmptyIteratorConstructed = true; \
            } \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
        mIteratorColumnsCount = size_type{0}; \
    }

#define CONSTRUCT_REVERSE_MITERATOR_WITH_DIAG_NR_AND_INDEX(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, \
                                                           pMatrixPtr, matrixRowsCount, matrixColumnsCount, diagonalNr, diagonalIndex) \
    bool nonEmptyIteratorConstructed = false; \
\
    if (pMatrixPtr) \
    { \
        std::optional<size_type> resultingDiagonalIndex; \
        size_type resultingDiagonalSize{0}; \
        \
        if (matrixRowsCount > size_type{0} && matrixColumnsCount > size_type{0} && diagonalIndex.has_value()) \
        { \
            const diff_type c_MinDiagonalNr = diff_type{1} - static_cast<diff_type>(matrixRowsCount); \
            const diff_type c_MaxDiagonalNr = static_cast<diff_type>(matrixColumnsCount) - diff_type{1}; \
\
            if (diagonalNr >= c_MinDiagonalNr && diagonalNr <= c_MaxDiagonalNr) \
            { \
                /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of rows (negative) / columns (positive) */ \
                resultingDiagonalSize = matrixRowsCount >= matrixColumnsCount ? (diagonalNr < diff_type{0} ? matrixRowsCount - static_cast<size_type>(-diagonalNr) : matrixColumnsCount + static_cast<size_type>(-diagonalNr)) \
                                                                              : (diagonalNr <= diff_type{0} ? matrixRowsCount + static_cast<size_type>(diagonalNr) : matrixColumnsCount - static_cast<size_type>(diagonalNr)); \
\
                if (diagonalIndex <= resultingDiagonalSize) \
                { \
                    resultingDiagonalIndex = diagonalIndex; \
                } \
            } \
        } \
\
        if (resultingDiagonalIndex.has_value()) \
        { \
            mpIteratorPtr = pMatrixPtr; \
            mIteratorDiagonalNr = diagonalNr; \
            mIteratorDiagonalSize = resultingDiagonalSize; \
            mIteratorDiagonalIndex = resultingDiagonalIndex; \
            mIteratorColumnsCount = matrixColumnsCount; \
            nonEmptyIteratorConstructed = true; \
        } \
        else \
        { \
            assert(false); \
        } \
    } \
\
    if (!nonEmptyIteratorConstructed) \
    { \
        mpIteratorPtr = nullptr; \
        mIteratorDiagonalNr = diff_type{0}; \
        mIteratorDiagonalSize = size_type{0}; \
        mIteratorColumnsCount = size_type{0}; \
    }

#define FORWARD_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1}) \
                                                                          : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1} - mIteratorDiagonalNr)}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define REVERSE_MITERATOR_ASTERISK_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1}  + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                       : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex) \
                                                                          : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex - static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_IteratorRowNr][c_IteratorColumnNr];

#define FORWARD_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(*mIteratorDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : *mIteratorDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1}) \
                                                                          : static_cast<size_type>(mIteratorColumnsCount - *mIteratorDiagonalIndex - size_type{1} - static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define REVERSE_MITERATOR_ARROW_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount) \
    CHECK_ERROR_CONDITION(_isEmpty() || mIteratorDiagonalIndex == mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::DEREFERENCE_END_ITERATOR]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_IteratorRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1} + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                       : static_cast<size_type>(mIteratorDiagonalSize - *mIteratorDiagonalIndex - size_type{1})}; \
    const size_type c_IteratorColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex) \
                                                                          : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + *mIteratorDiagonalIndex - static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return (mpIteratorPtr[c_IteratorRowNr] + c_IteratorColumnNr);

#define FORWARD_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} && static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(c_ResultingDiagonalIndex + static_cast<size_type>(-mIteratorDiagonalNr)) : c_ResultingDiagonalIndex}; \
\
    /* No overflow as the maximum diagonal index (for non-end iterators in non-empty matrixes) is less than the difference between the */ \
    /* columns count and diagonal number (for positive diagonals) respectively less than the number of columns (for negative diagonals) */ \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - size_type{1}) \
                                                                           : static_cast<size_type>(mIteratorColumnsCount - c_ResultingDiagonalIndex - size_type{1} - static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define REVERSE_MITERATOR_INDEX_DEREFERENCE(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorColumnsCount, arrayIndex) \
    CHECK_ERROR_CONDITION(_isEmpty() || (arrayIndex < diff_type{0} && static_cast<size_type>(std::abs(arrayIndex)) > mIteratorDiagonalIndex), Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    const size_type c_ResultingDiagonalIndex{static_cast<size_type>(static_cast<diff_type>(*mIteratorDiagonalIndex) + arrayIndex)}; \
\
    CHECK_ERROR_CONDITION(c_ResultingDiagonalIndex >= mIteratorDiagonalSize, Matr::errorMessages[Matr::Errors::ITERATOR_INDEX_OUT_OF_BOUNDS]); \
\
    /* No overflow risk: diagonal index is smaller than diagonal size; diagonal size is not higher than number of columns; diagonal number if smaller than number of columns */ \
    const size_type c_ResultingRowNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1} + static_cast<size_type>(-mIteratorDiagonalNr)) \
                                                                        : static_cast<size_type>(mIteratorDiagonalSize - c_ResultingDiagonalIndex - size_type{1})}; \
    const size_type c_ResultingColumnNr{mIteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex) \
                                                                           : static_cast<size_type>(mIteratorColumnsCount - mIteratorDiagonalSize + c_ResultingDiagonalIndex - static_cast<size_type>(mIteratorDiagonalNr))}; \
\
    return mpIteratorPtr[c_ResultingRowNr][c_ResultingColumnNr];

#define GET_BEGIN_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(mMatrixNrOfColumns) - static_cast<diff_type>(matrixColumnNr) - diff_type{1}) - static_cast<diff_type>(matrixRowNr)}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, size_type{0}}};

#define GET_END_MITERATOR_BY_DIAG_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixDiagonalNr) \
    CHECK_ERROR_CONDITION(matrixDiagonalNr < (diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          matrixDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{matrixDiagonalNr < diff_type{0} ? static_cast<size_type>(-matrixDiagonalNr) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */ \
    /* of matrix columns if the matrix is not empty (if empty above error condition triggers) */ \
    const size_type c_BeginColumnNr{matrixDiagonalNr <= diff_type{0} ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1}) : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(matrixDiagonalNr))}; \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + size_type{1}))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {matrixDiagonalNr, c_EndDiagonalIndex}};

#define GET_END_MITERATOR_BY_ROW_AND_COLUMN_NUMBER(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, matrixRowNr, matrixColumnNr) \
    CHECK_ERROR_CONDITION(matrixRowNr >= mMatrixNrOfRows, Matr::errorMessages[Matr::Errors::ROW_DOES_NOT_EXIST]); \
    CHECK_ERROR_CONDITION(matrixColumnNr >= mMatrixNrOfColumns, Matr::errorMessages[Matr::Errors::COLUMN_DOES_NOT_EXIST]); \
\
    const auto c_DiagonalNr{static_cast<diff_type>(static_cast<diff_type>(mMatrixNrOfColumns) - static_cast<diff_type>(matrixColumnNr) - diff_type{1}) - static_cast<diff_type>(matrixRowNr)}; \
\
    const size_type c_BeginRowNr{c_DiagonalNr < diff_type{0} ? static_cast<size_type>(-c_DiagonalNr) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the number */ \
    /* of matrix columns if the matrix is not empty (if empty above error conditions trigger) */ \
    const size_type c_BeginColumnNr{c_DiagonalNr <= diff_type{0} ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1}) : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(c_DiagonalNr))}; \
    const size_type c_EndDiagonalIndex{std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + size_type{1}))}; \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {c_DiagonalNr, c_EndDiagonalIndex}};

#define GET_RANDOM_MITERATOR_BY_DIAG_NUMBER_AND_INDEX(IteratorType, mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, iteratorDiagonalNr, iteratorDiagonalIndex) \
    CHECK_ERROR_CONDITION(iteratorDiagonalNr < (diff_type{1} - static_cast<diff_type>(mMatrixNrOfRows)) || \
                          iteratorDiagonalNr > (static_cast<diff_type>(mMatrixNrOfColumns) - diff_type{1}), \
                          Matr::errorMessages[Matr::Errors::DIAGONAL_DOES_NOT_EXIST]); \
\
    const size_type c_BeginRowNr{iteratorDiagonalNr < diff_type{0} ? static_cast<size_type>(-iteratorDiagonalNr) : size_type{0}}; \
\
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller than the */ \
    /* number of matrix columns if the matrix is not empty (if empty above error condition triggers) */ \
    const size_type c_BeginColumnNr{iteratorDiagonalNr <= diff_type{0} ? static_cast<size_type>(mMatrixNrOfColumns - size_type{1}) : static_cast<size_type>(mMatrixNrOfColumns - size_type{1} - static_cast<size_type>(iteratorDiagonalNr))}; \
\
    /* no overflow as for negative diagonals the diagonal number (in absolute value) should be strictly smaller than the */ \
    /* number of matrix rows if the matrix is not empty (if empty above error condition triggers */ \
    const size_type c_DiagonalSize {std::min(static_cast<size_type>(mMatrixNrOfRows - c_BeginRowNr), static_cast<size_type>(c_BeginColumnNr + size_type{1}))}; \
\
    CHECK_ERROR_CONDITION(iteratorDiagonalIndex >= c_DiagonalSize, Matr::errorMessages[Matr::Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS]); \
\
    return IteratorType{mpIteratorPtr, mMatrixNrOfRows, mMatrixNrOfColumns, {iteratorDiagonalNr, iteratorDiagonalIndex}};

#define CHECK_MITERATOR_IS_EMPTY(mpIteratorPtr, mIteratorDiagonalNr, mIteratorDiagonalSize, mIteratorDiagonalIndex, mIteratorNrOfColumns) \
    if (mpIteratorPtr) \
    { \
        assert(mIteratorDiagonalSize > size_type{0} && mIteratorDiagonalIndex.has_value() && mIteratorNrOfColumns > size_type{0}); \
    } \
    else \
    { \
        assert(diff_type{0} == mIteratorDiagonalNr && size_type{0} == mIteratorDiagonalSize && !mIteratorDiagonalIndex.has_value() && size_type{0} == mIteratorNrOfColumns); \
    } \
\
    return !mpIteratorPtr;

#endif // ITERATORUTILS_H
