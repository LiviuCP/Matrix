export module testconstants;
export import matrix;

// various constants related to the maximum allowed matrix dimensions
export constexpr matrix_size_t c_MaxAllowedDimension{maxAllowedDimension()};
export constexpr matrix_size_t c_DecrMaxAllowedDimension{c_MaxAllowedDimension - 1};
export constexpr matrix_size_t c_TwiceDecrMaxAllowedDimension{c_MaxAllowedDimension - 2};
export constexpr matrix_size_t c_ThreeTimesDecrMaxAllowedDimension{c_MaxAllowedDimension - 3};
export constexpr matrix_size_t c_IncrMaxAllowedDimension{c_MaxAllowedDimension + 1};
export constexpr matrix_size_t c_HalfMaxAllowedDimension{c_MaxAllowedDimension / 2};
export constexpr matrix_size_t c_DecrHalfMaxAllowedDimension{c_MaxAllowedDimension / 2 - 1};
export constexpr matrix_size_t c_IncrHalfMaxAllowedDimension{c_MaxAllowedDimension / 2 + 1};
export constexpr matrix_size_t c_ThreeQuartersMaxAllowedDimension{c_HalfMaxAllowedDimension +
                                                                  c_HalfMaxAllowedDimension / 2};
export constexpr matrix_size_t c_QuarterMaxAllowedDimension{c_MaxAllowedDimension / 4};
export constexpr matrix_size_t c_FiveEighthsMaxAllowedDimension{c_HalfMaxAllowedDimension +
                                                                c_HalfMaxAllowedDimension / 4};
export constexpr matrix_size_t c_SevenEighthsMaxAllowedDimension{(c_MaxAllowedDimension / 8) * 7};
export constexpr matrix_size_t c_DecrQuarterMaxAllowedDimension{c_QuarterMaxAllowedDimension - 1};
export constexpr matrix_size_t c_IncrQuarterMaxAllowedDimension{c_QuarterMaxAllowedDimension + 1};
export constexpr matrix_size_t c_TwiceIncrQuarterMaxAllowedDimension{c_IncrQuarterMaxAllowedDimension + 1};
export constexpr matrix_size_t c_DoubleQuarterMaxAllowedDimension{c_QuarterMaxAllowedDimension * 2};
export constexpr matrix_size_t c_DoubleDecrQuarterMaxAllowedDimension{c_DecrQuarterMaxAllowedDimension * 2};
export constexpr matrix_size_t c_HalfQuarterMaxAllowedDimension{c_QuarterMaxAllowedDimension / 2};
export constexpr matrix_size_t c_HalfDecrQuarterMaxAllowedDimension{c_DecrQuarterMaxAllowedDimension / 2};
export constexpr matrix_size_t c_HalfThreeQuartersMaxAllowedDimension{
    (c_MaxAllowedDimension - c_QuarterMaxAllowedDimension) / 2};

export constexpr matrix_size_t c_HalfToFiveEighthsCapacityOffset{
    (c_FiveEighthsMaxAllowedDimension - c_HalfMaxAllowedDimension) / 2};
export constexpr matrix_size_t c_HalfToMaxCapacityOffset{(c_MaxAllowedDimension - c_HalfMaxAllowedDimension) / 2};
export constexpr matrix_size_t c_SevenEighthsToMaxCapacityOffset{
    (c_MaxAllowedDimension - c_SevenEighthsMaxAllowedDimension) / 2};

export constexpr bool c_IsEvenMaxAllowedDimension{0 == c_MaxAllowedDimension % 2};
