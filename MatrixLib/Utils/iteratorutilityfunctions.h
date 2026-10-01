#pragma once

#include <optional>
#include <utility>

#include "../Matrix/matrixdimensions.h"

/* These functions should solely be used by iterator classes.

   They rely on correct data provided from Matrix class when iterators get constructed
   or from iterator classes when row/column numbers are being retrieved.
*/

using matrix_size_t = Matr::size_t;
using matrix_diff_t = Matr::diff_t;

/* For non-diagonal iterators the end iterator index can also be calculated using the compute functions. */

extern std::optional<matrix_diff_t> computeForwardNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate);

extern std::optional<matrix_diff_t> computeReverseNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate);

/* For diagonal iterators computing the end iterator diagonal number and index using the compute functions is not
   supported. These should be correctly provided by Matrix when calling the iterator constructors.
*/

extern std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeForwardDIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr);

extern std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeReverseDIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr);

extern std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeForwardMIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr);

extern std::pair<matrix_diff_t, std::optional<matrix_size_t>> computeReverseMIteratorDiagNrAndIndex(
    matrix_size_t nrOfMatrixRows, matrix_size_t nrOfMatrixColumns, std::optional<matrix_size_t> rowNr,
    std::optional<matrix_size_t> columnNr);

/* Helper functions for iterator row/column number getters:
   - end iterator row/column numbers supported
   - when diagonal index equals the diagonal size we are talking about an end iterator
*/

extern std::optional<matrix_size_t> computeForwardZIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeForwardZIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeReverseZIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows,
                                                                 matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeReverseZIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows,
                                                                    matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeForwardNIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows);

extern std::optional<matrix_size_t> computeForwardNIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows);

extern std::optional<matrix_size_t> computeReverseNIteratorRowNr(std::optional<matrix_diff_t> index,
                                                                 matrix_size_t nrOfMatrixRows,
                                                                 matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeReverseNIteratorColumnNr(std::optional<matrix_diff_t> index,
                                                                    matrix_size_t nrOfMatrixRows,
                                                                    matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeForwardDIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex);

extern std::optional<matrix_size_t> computeForwardDIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex);

extern std::optional<matrix_size_t> computeReverseDIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex,
                                                                 matrix_size_t diagonalSize);

extern std::optional<matrix_size_t> computeReverseDIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t diagonalSize);

extern std::optional<matrix_size_t> computeForwardMIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex);

extern std::optional<matrix_size_t> computeForwardMIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t nrOfMatrixColumns);

extern std::optional<matrix_size_t> computeReverseMIteratorRowNr(matrix_diff_t diagonalNr,
                                                                 std::optional<matrix_size_t> diagonalIndex,
                                                                 matrix_size_t diagonalSize);

extern std::optional<matrix_size_t> computeReverseMIteratorColumnNr(matrix_diff_t diagonalNr,
                                                                    std::optional<matrix_size_t> diagonalIndex,
                                                                    matrix_size_t diagonalSize,
                                                                    matrix_size_t nrOfMatrixColumns);
