#pragma once

#include <algorithm>
#include <optional>

#include "../Matrix/matrixdimensions.h"

#define ITERATOR_TRAITS(IterableType, DiffType, ReferenceType)                                                         \
    using iterator_category = std::random_access_iterator_tag;                                                         \
    using value_type = IterableType;                                                                                   \
    using difference_type = DiffType;                                                                                  \
    using pointer = IterableType**;                                                                                    \
    using reference = ReferenceType;

using matrix_size_t = Matr::size_t;
using matrix_diff_t = Matr::diff_t;

/* These functions should solely be used by iterator classes.

   They rely on correct data provided from Matrix class when iterators get constructed
   or from iterator classes when row/column numbers are being retrieved.
*/

template <typename MatrixIterator> MatrixIterator addOffsetToIterator(const MatrixIterator& it, matrix_diff_t offset)
{
    MatrixIterator temp{it};
    temp += offset;
    return temp;
}

/* For non-diagonal iterators the end iterator index can also be calculated using the compute functions. */

static std::optional<matrix_diff_t> computeForwardNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate)
{
    return matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value()
               ? matrixPrimaryCoordinate == matrixPrimaryDimension &&
                         matrixSecondaryCoordinate == matrixSecondaryDimension
                     ? static_cast<matrix_diff_t>(matrixPrimaryDimension) *
                           static_cast<matrix_diff_t>(matrixSecondaryDimension)
                     : static_cast<matrix_diff_t>(*matrixPrimaryCoordinate) *
                               static_cast<matrix_diff_t>(matrixSecondaryDimension) +
                           static_cast<matrix_diff_t>(*matrixSecondaryCoordinate)
               : std::optional<matrix_diff_t>{};
}

static std::optional<matrix_diff_t> computeReverseNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate)
{
    return matrixPrimaryCoordinate.has_value() && matrixSecondaryCoordinate.has_value()
               ? (static_cast<matrix_diff_t>(matrixPrimaryDimension) -
                  static_cast<matrix_diff_t>(*matrixPrimaryCoordinate)) *
                         static_cast<matrix_diff_t>(matrixSecondaryDimension) -
                     static_cast<matrix_diff_t>(*matrixSecondaryCoordinate) - matrix_diff_t{1}
           : !matrixPrimaryCoordinate.has_value() &&
                   matrixSecondaryCoordinate == matrixSecondaryDimension - matrix_diff_t{1}
               ? static_cast<matrix_diff_t>(matrixPrimaryDimension) *
                     static_cast<matrix_diff_t>(matrixSecondaryDimension)
               : std::optional<matrix_diff_t>{};
}

/* For diagonal iterators computing the end iterator diagonal number and index using the compute functions is not
   supported. These should be correctly provided by Matrix when calling the iterator constructors.
*/

static std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeForwardDIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr)
{
    matrix_diff_t diagonalNr{0};
    std::optional<matrix_size_t> diagonalIndex;

    if (nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} && rowNr.has_value() &&
        columnNr.has_value() && rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)
    {
        diagonalNr = static_cast<matrix_diff_t>(*columnNr) - static_cast<matrix_diff_t>(*rowNr);
        diagonalIndex = std::min(*rowNr, *columnNr);
    }

    return {diagonalNr, diagonalIndex};
}

static std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeReverseDIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr)
{
    matrix_diff_t diagonalNr{0};
    std::optional<matrix_size_t> diagonalIndex;

    if (nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} && rowNr.has_value() &&
        columnNr.has_value() && rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)
    {

        diagonalNr = static_cast<matrix_diff_t>(*columnNr) - static_cast<matrix_diff_t>(*rowNr);

        const matrix_size_t c_DiagonalSize =
            nrOfMatrixRows >= nrOfMatrixColumns
                ? (diagonalNr < matrix_diff_t{0} ? nrOfMatrixRows + diagonalNr : nrOfMatrixColumns - diagonalNr)
                : (diagonalNr <= matrix_diff_t{0} ? nrOfMatrixRows + diagonalNr : nrOfMatrixColumns - diagonalNr);

        diagonalIndex = diagonalNr < matrix_diff_t{0}
                            ? (columnNr.has_value() ? c_DiagonalSize - matrix_size_t{1} - *columnNr : c_DiagonalSize)
                            : (rowNr.has_value() ? c_DiagonalSize - matrix_size_t{1} - *rowNr : c_DiagonalSize);
    }

    return {diagonalNr, diagonalIndex};
}

static std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeForwardMIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr)
{
    matrix_diff_t diagonalNr{0};
    std::optional<matrix_size_t> diagonalIndex;

    if (nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} && rowNr.has_value() &&
        columnNr.has_value() && rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)
    {
        diagonalNr = static_cast<matrix_diff_t>(nrOfMatrixColumns) - static_cast<matrix_diff_t>(*columnNr) -
                     static_cast<matrix_diff_t>(*rowNr) - matrix_diff_t{1};
        diagonalIndex = std::min<matrix_size_t>(*rowNr, nrOfMatrixColumns - *columnNr - matrix_size_t{1});
    }

    return {diagonalNr, diagonalIndex};
}

static std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeReverseMIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr)
{
    matrix_diff_t diagonalNr{0};
    std::optional<matrix_size_t> diagonalIndex;

    if (nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} && rowNr.has_value() &&
        columnNr.has_value() && rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)
    {
        diagonalNr = static_cast<matrix_diff_t>(nrOfMatrixColumns) - static_cast<matrix_diff_t>(*columnNr) -
                     static_cast<matrix_diff_t>(*rowNr) - matrix_diff_t{1};

        /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of
         * rows (negative) / columns (positive) */
        const matrix_size_t c_DiagonalSize =
            nrOfMatrixRows >= nrOfMatrixColumns
                ? (diagonalNr < matrix_diff_t{0} ? nrOfMatrixRows - static_cast<matrix_size_t>(-diagonalNr)
                                                 : nrOfMatrixColumns + static_cast<matrix_size_t>(-diagonalNr))
                : (diagonalNr <= matrix_diff_t{0} ? nrOfMatrixRows + static_cast<matrix_size_t>(diagonalNr)
                                                  : nrOfMatrixColumns - static_cast<matrix_size_t>(diagonalNr));

        diagonalIndex = diagonalNr < matrix_diff_t{0} ? c_DiagonalSize - nrOfMatrixColumns + *columnNr
                        : rowNr.has_value()           ? c_DiagonalSize - matrix_size_t{1} - *rowNr
                                                      : c_DiagonalSize;
    }

    return {diagonalNr, diagonalIndex};
}

/* Helper functions for iterator row/column number getters:
   - end iterator row/column numbers supported
   - when diagonal index equals the diagonal size we are talking about an end iterator
*/

static std::optional<matrix_size_t> computeForwardZIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixColumns > matrix_size_t{0}
               ? static_cast<matrix_size_t>(*index / static_cast<matrix_diff_t>(nrOfMatrixColumns))
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardZIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixColumns > matrix_size_t{0}
               ? static_cast<matrix_size_t>(*index % static_cast<matrix_diff_t>(nrOfMatrixColumns))
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseZIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows,
                                                                 matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} &&
                   index < static_cast<matrix_diff_t>(nrOfMatrixRows) * static_cast<matrix_diff_t>(nrOfMatrixColumns)
               ? static_cast<matrix_size_t>(nrOfMatrixRows) -
                     static_cast<matrix_size_t>(*index / static_cast<matrix_diff_t>(nrOfMatrixColumns)) -
                     matrix_size_t{1}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseZIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows,
                                                                    matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0}
               ? index < static_cast<matrix_diff_t>(nrOfMatrixRows) * static_cast<matrix_diff_t>(nrOfMatrixColumns)
                     ? static_cast<matrix_size_t>(nrOfMatrixColumns) -
                           static_cast<matrix_size_t>(*index % static_cast<matrix_diff_t>(nrOfMatrixColumns)) -
                           matrix_size_t{1}
                     : static_cast<matrix_size_t>(nrOfMatrixColumns) - matrix_size_t{1}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardNIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0}
               ? static_cast<matrix_size_t>(*index % static_cast<matrix_diff_t>(nrOfMatrixRows))
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardNIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0}
               ? static_cast<matrix_size_t>(*index / static_cast<matrix_diff_t>(nrOfMatrixRows))
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseNIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows,
                                                                 matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0}
               ? index < static_cast<matrix_diff_t>(nrOfMatrixColumns) * static_cast<matrix_diff_t>(nrOfMatrixRows)
                     ? static_cast<matrix_size_t>(nrOfMatrixRows) -
                           static_cast<matrix_size_t>(*index % static_cast<matrix_diff_t>(nrOfMatrixRows)) -
                           matrix_size_t{1}
                     : static_cast<matrix_size_t>(nrOfMatrixRows) - matrix_size_t{1}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseNIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows,
                                                                    matrix_size_t nrOfMatrixColumns)
{
    return index.has_value() && nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} &&
                   index < static_cast<matrix_diff_t>(nrOfMatrixColumns) * static_cast<matrix_diff_t>(nrOfMatrixRows)
               ? static_cast<matrix_size_t>(nrOfMatrixColumns) -
                     static_cast<matrix_size_t>(*index / static_cast<matrix_diff_t>(nrOfMatrixRows)) - matrix_size_t{1}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardDIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex)
{
    return diagonalIndex.has_value() ? diagonalNr < matrix_diff_t{0}
                                           ? *diagonalIndex + static_cast<matrix_size_t>(-diagonalNr)
                                           : *diagonalIndex
                                     : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardDIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex)
{
    return diagonalIndex.has_value() ? diagonalNr < matrix_diff_t{0}
                                           ? *diagonalIndex
                                           : *diagonalIndex + static_cast<matrix_size_t>(diagonalNr)
                                     : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseDIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex,
                                                                 matrix_size_t diagonalSize)
{
    return diagonalIndex.has_value() && diagonalSize > matrix_size_t{0} && *diagonalIndex <= diagonalSize
               ? diagonalNr < matrix_diff_t{0}
                     ? diagonalSize - *diagonalIndex + static_cast<matrix_size_t>(-diagonalNr) - matrix_size_t{1}
                 : *diagonalIndex < diagonalSize ? diagonalSize - *diagonalIndex - matrix_size_t{1}
                                                 : std::optional<matrix_size_t>{}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseDIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t diagonalSize)
{
    return diagonalIndex.has_value() && diagonalSize > matrix_size_t{0} && *diagonalIndex <= diagonalSize
               ? diagonalNr > matrix_diff_t{0}
                     ? diagonalSize - *diagonalIndex + static_cast<matrix_size_t>(diagonalNr) - matrix_size_t{1}
                 : *diagonalIndex < diagonalSize ? diagonalSize - *diagonalIndex - matrix_size_t{1}
                                                 : std::optional<matrix_size_t>{}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardMIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex)
{
    return diagonalIndex.has_value() ? diagonalNr < matrix_diff_t{0}
                                           ? *diagonalIndex + static_cast<matrix_size_t>(-diagonalNr)
                                           : *diagonalIndex
                                     : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeForwardMIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t nrOfMatrixColumns)
{
    /* no overflow as for positive diagonals the diagonal number should be strictly smaller */
    /* than the number of matrix columns if the matrix is not empty */
    return diagonalIndex.has_value() && nrOfMatrixColumns > matrix_size_t{0} && *diagonalIndex < nrOfMatrixColumns
               ? diagonalNr < matrix_diff_t{0} ? nrOfMatrixColumns - *diagonalIndex - matrix_size_t{1}
                 : *diagonalIndex < nrOfMatrixColumns - static_cast<matrix_size_t>(diagonalNr)
                     ? nrOfMatrixColumns - static_cast<matrix_size_t>(diagonalNr) - *diagonalIndex - matrix_size_t{1}
                     : std::optional<matrix_size_t>{}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseMIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex,
                                                                 matrix_size_t diagonalSize)
{
    return diagonalIndex.has_value() && diagonalSize > matrix_size_t{0} && *diagonalIndex <= diagonalSize
               ? diagonalNr < matrix_diff_t{0}
                     ? diagonalSize - *diagonalIndex + static_cast<matrix_size_t>(-diagonalNr) - matrix_size_t{1}
                 : *diagonalIndex < diagonalSize ? diagonalSize - *diagonalIndex - matrix_size_t{1}
                                                 : std::optional<matrix_size_t>{}
               : std::optional<matrix_size_t>{};
}

static std::optional<matrix_size_t> computeReverseMIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t diagonalSize,
                                                                    matrix_size_t nrOfMatrixColumns)
{
    /* no overflow risk for positive diagonals: diagonal size added to diagonal number equals the number of columns */
    return diagonalIndex.has_value() && diagonalSize > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} &&
                   *diagonalIndex <= diagonalSize && diagonalSize <= nrOfMatrixColumns
               ? diagonalNr < matrix_diff_t{0}
                     ? nrOfMatrixColumns - diagonalSize + *diagonalIndex
                     : nrOfMatrixColumns - diagonalSize + *diagonalIndex - static_cast<matrix_size_t>(diagonalNr)
               : std::optional<matrix_size_t>{};
}
