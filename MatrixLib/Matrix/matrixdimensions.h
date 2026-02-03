#ifndef MATRIXDIMENSIONS_H
#define MATRIXDIMENSIONS_H

#include <cstdint>
#include <optional>

#ifndef USE_SMALL_DIMENSIONS
using matrix_size_t = uint32_t;
using matrix_diff_t = int64_t;
#else
using matrix_size_t = uint8_t;
using matrix_diff_t = int16_t;
#endif

using matrix_opt_size_t = std::optional<matrix_size_t>;
using matrix_opt_diff_t = std::optional<matrix_diff_t>;
using MatrixPoint = std::pair<matrix_opt_size_t, matrix_opt_size_t>;

#endif // MATRIXDIMENSIONS_H
