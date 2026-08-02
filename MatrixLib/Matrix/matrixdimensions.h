#pragma once

#include <cstdint>

namespace Matr
{
#ifndef USE_SMALL_DIMENSIONS
using size_t = uint32_t;
using diff_t = int64_t;
#else
using size_t = uint8_t;
using diff_t = int16_t;
#endif
} // namespace Matr
