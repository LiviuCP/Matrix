#pragma once

// matrix concatenation
enum class ConcatMode : unsigned short
{
    SOURCE_TO_DESTINATION,
    TO_ITSELF
};

// matrix splitting
enum class SplitMode : unsigned short
{
    SOURCE_TO_DESTINATION,

    // for exceptions testing only
    TO_ITSELF
};
