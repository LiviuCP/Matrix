#pragma once

#include <map>
#include <string>

#ifndef ERROR_CHECKING_DISABLED
// #ifdef CONVERT_TO_EXCEPTIONS
#define CHECK_ERROR_CONDITION(condition, errorMessage)                                                                 \
    {                                                                                                                  \
        /*printf("checking error condition, trigger exception\n");*/                                                   \
        if (condition)                                                                                                 \
        {                                                                                                              \
            throw std::runtime_error(errorMessage);                                                                    \
        }                                                                                                              \
    }
// #else
// #define CHECK_ERROR_CONDITION(condition, errorMessage) \
//     { \
//         /*printf("checking error condition, assertion\n");*/ \
//         if (condition) \
//         { \
//             fprintf(stderr, "ASSERTION ERROR TRIGERRED! %s\n", errorMessage.c_str()); \
//             assert(false); \
//         } \
//     }
// #endif
#else
#define CHECK_ERROR_CONDITION(condition, errorMessage)
#endif

#ifndef ERROR_CHECKING_DISABLED
namespace Matr
{
enum class Errors
{
    INSUFFICIENT_ELEMENTS_FOR_INIT,
    NULL_DIMENSION,
    ROW_DOES_NOT_EXIST,
    COLUMN_DOES_NOT_EXIST,
    DIAGONAL_DOES_NOT_EXIST,
    MATRIXES_UNEQUAL_COLUMN_LENGTH,
    MATRIXES_UNEQUAL_ROW_LENGTH,
    INSERT_ROW_NONCONTIGUOUS,
    INSERT_COLUMN_NONCONTIGUOUS,
    INVALID_ELEMENT_INDEX,
    RESULT_NO_ROWS,
    RESULT_NO_COLUMNS,
    CURRENT_MATRIX_AS_ARGUMENT,
    EMPTY_MATRIX,
    DEREFERENCE_END_ITERATOR,
    INCOMPATIBLE_ITERATORS,
    DIAGONAL_INDEX_OUT_OF_BOUNDS,
    ITERATOR_INDEX_OUT_OF_BOUNDS,
    MAX_ALLOWED_DIMENSIONS_EXCEEDED
};

extern std::map<Errors, std::string> errorMessages;

} // namespace Matr
#endif
