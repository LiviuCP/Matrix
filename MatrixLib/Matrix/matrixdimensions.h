#pragma once

#include <cstdint>

#ifndef USE_SMALL_DIMENSIONS
using matrix_size_t = uint32_t;
using matrix_diff_t = int64_t;
#else
using matrix_size_t = uint8_t;
using matrix_diff_t = int16_t;
#endif