#pragma once

#include <optional>

#include "../Matrix/matrixdimensions.h"

using matrix_size_t = Matr::size_t;
using matrix_diff_t = Matr::diff_t;

extern std::optional<matrix_diff_t> computeForwardNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate);

extern std::optional<matrix_diff_t> computeReverseNonDiagIteratorIndex(
    matrix_size_t matrixPrimaryDimension, matrix_size_t matrixSecondaryDimension,
    std::optional<matrix_size_t> matrixPrimaryCoordinate, std::optional<matrix_size_t> matrixSecondaryCoordinate);