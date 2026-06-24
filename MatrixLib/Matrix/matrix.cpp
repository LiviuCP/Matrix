export module matrix;

export import :matrix_header;

import :matrix_impl;
import :matrix_ziterator_impl;
import :matrix_niterator_impl;
import :matrix_diterator_impl;
import :matrix_miterator_impl;

/* TODO: find a solution to replace the conditional compiling settings (defines)

   Some had to be disabled to make the code compile/run correctly with modules.

   Defines to take into consideration:
   - USE_SMALL_DIMENSIONS (only small dimensions possible at the moment)
   - USE_CAPACITY_OFFSET (had to enable the capacity offset getters in order to be able to run the tests)
   - CONVERT_TO_EXCEPTIONS (no assertions possible at the moment)
   - ERROR_CHECKING_DISABLED (how can we still make this work?)

   Proper solutions are required to make all versions work without using these defines.
*/
