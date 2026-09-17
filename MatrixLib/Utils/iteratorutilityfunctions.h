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

template <typename MatrixIterator> MatrixIterator addOffsetToIterator(const MatrixIterator& it, matrix_diff_t offset)
{
    MatrixIterator temp{it};
    temp += offset;
    return temp;
}

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
        const bool c_AreRowAndColumnNrValid{
            (!rowNr.has_value() && !columnNr.has_value()) ||
            (!rowNr.has_value() && columnNr < nrOfMatrixColumns - matrix_size_t{1}) ||
            (!columnNr.has_value() && rowNr < nrOfMatrixRows - matrix_size_t{1}) ||
            (rowNr.has_value() && columnNr.has_value() && rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)};

        if (c_AreRowAndColumnNrValid)
        {
            diagonalNr = rowNr.has_value() && columnNr.has_value()
                             ? static_cast<matrix_diff_t>(*columnNr) - static_cast<matrix_diff_t>(*rowNr)
                         : rowNr.has_value()    ? matrix_diff_t{-1} - static_cast<matrix_diff_t>(*rowNr)
                         : columnNr.has_value() ? static_cast<matrix_diff_t>(*columnNr) + matrix_diff_t{1}
                                                : matrix_diff_t{0};

            const matrix_size_t c_DiagonalSize =
                nrOfMatrixRows >= nrOfMatrixColumns
                    ? (diagonalNr < matrix_diff_t{0} ? nrOfMatrixRows + diagonalNr : nrOfMatrixColumns - diagonalNr)
                    : (diagonalNr <= matrix_diff_t{0} ? nrOfMatrixRows + diagonalNr : nrOfMatrixColumns - diagonalNr);

            diagonalIndex =
                diagonalNr < matrix_diff_t{0}
                    ? (columnNr.has_value() ? c_DiagonalSize - matrix_size_t{1} - *columnNr : c_DiagonalSize)
                    : (rowNr.has_value() ? c_DiagonalSize - matrix_size_t{1} - *rowNr : c_DiagonalSize);
        }
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

    if (nrOfMatrixRows > matrix_size_t{0} && nrOfMatrixColumns > matrix_size_t{0} && columnNr.has_value() &&
        columnNr <= nrOfMatrixColumns)
    {
        const bool c_IsValidRowNr{
            (!rowNr.has_value() && columnNr > matrix_size_t{0}) ||
            (rowNr.has_value() && ((rowNr < nrOfMatrixRows - matrix_size_t{1} && columnNr == nrOfMatrixColumns) ||
                                   (rowNr < nrOfMatrixRows && columnNr < nrOfMatrixColumns)))};

        if (c_IsValidRowNr)
        {
            diagonalNr = rowNr.has_value()
                             ? static_cast<matrix_diff_t>(nrOfMatrixColumns) - static_cast<matrix_diff_t>(*columnNr) -
                                   static_cast<matrix_diff_t>(*rowNr) - matrix_diff_t{1}
                             : static_cast<matrix_diff_t>(nrOfMatrixColumns) - static_cast<matrix_diff_t>(*columnNr);

            /* There should be no overflow risk (the absolute value of the diagonal number is lower than number of
             * rows (negative) / columns (positive) */
            const matrix_diff_t c_DiagonalSize =
                nrOfMatrixRows >= nrOfMatrixColumns
                    ? (diagonalNr < matrix_diff_t{0} ? nrOfMatrixRows - static_cast<matrix_size_t>(-diagonalNr)
                                                     : nrOfMatrixColumns + static_cast<matrix_size_t>(-diagonalNr))
                    : (diagonalNr <= matrix_diff_t{0} ? nrOfMatrixRows + static_cast<matrix_size_t>(diagonalNr)
                                                      : nrOfMatrixColumns - static_cast<matrix_size_t>(diagonalNr));

            diagonalIndex = diagonalNr < matrix_diff_t{0} ? c_DiagonalSize - nrOfMatrixColumns + *columnNr
                            : rowNr.has_value()           ? c_DiagonalSize - matrix_size_t{1} - *rowNr
                                                          : c_DiagonalSize;
        }
    }

    return {diagonalNr, diagonalIndex};
}
