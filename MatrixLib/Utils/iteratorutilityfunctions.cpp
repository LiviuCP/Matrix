#include "iteratorutilityfunctions.h"

std::optional<matrix_diff_t> computeForwardNonDiagIteratorIndex(matrix_size_t matrixPrimaryDimension,
                                                                matrix_size_t matrixSecondaryDimension,
                                                                std::optional<matrix_size_t> matrixPrimaryCoordinate,
                                                                std::optional<matrix_size_t> matrixSecondaryCoordinate)
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

std::optional<matrix_diff_t> computeReverseNonDiagIteratorIndex(matrix_size_t matrixPrimaryDimension,
                                                                matrix_size_t matrixSecondaryDimension,
                                                                std::optional<matrix_size_t> matrixPrimaryCoordinate,
                                                                std::optional<matrix_size_t> matrixSecondaryCoordinate)
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
