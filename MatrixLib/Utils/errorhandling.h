#pragma once

#include <map>
#include <string>

#ifndef ERROR_CHECKING_DISABLED
#ifdef CONVERT_TO_EXCEPTIONS
#define CHECK_ERROR_CONDITION(condition, errorMessage)                                                                 \
    {                                                                                                                  \
        /*printf("checking error condition, trigger exception\n");*/                                                   \
        if (condition)                                                                                                 \
        {                                                                                                              \
            throw std::runtime_error(errorMessage);                                                                    \
        }                                                                                                              \
    }
#else
#define CHECK_ERROR_CONDITION(condition, errorMessage)                                                                 \
    {                                                                                                                  \
        /*printf("checking error condition, assertion\n");*/                                                           \
        if (condition)                                                                                                 \
        {                                                                                                              \
            fprintf(stderr, "ASSERTION ERROR TRIGERRED! %s\n", errorMessage.c_str());                                  \
            assert(false);                                                                                             \
        }                                                                                                              \
    }
#endif
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

static std::map<Errors, std::string> errorMessages{
    {Errors::INSUFFICIENT_ELEMENTS_FOR_INIT, std::string{"Not enough elements to initialize the matrix"}},
    {Errors::NULL_DIMENSION, std::string{"At least one null matrix dimension has been entered."}},
    {Errors::ROW_DOES_NOT_EXIST, std::string{"For one or more matrixes at least one referenced row does not exist"}},
    {Errors::COLUMN_DOES_NOT_EXIST,
     std::string{"For one or more matrixes at least one referenced column does not exist"}},
    {Errors::DIAGONAL_DOES_NOT_EXIST, std::string{"The provided matrix diagonal does not exist"}},
    {Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH,
     std::string{"The columns of the two matrixes have different lengths. The number of rows is different."}},
    {Errors::MATRIXES_UNEQUAL_ROW_LENGTH,
     std::string{"The rows of the two matrixes have different lengths. The number of columns is different."}},
    {Errors::INSERT_ROW_NONCONTIGUOUS, std::string{"Attempt to insert a row on a non-contiguous position"}},
    {Errors::INSERT_COLUMN_NONCONTIGUOUS, std::string{"Attempt to insert a column on a non-contiguous position"}},
    {Errors::INVALID_ELEMENT_INDEX, std::string{"Attempt to reference a matrix element with invalid index"}},
    {Errors::RESULT_NO_ROWS, std::string{"The resulting matrix has 0 rows"}},
    {Errors::RESULT_NO_COLUMNS, std::string{"The resulting matrix has 0 columns"}},
    {Errors::CURRENT_MATRIX_AS_ARGUMENT,
     std::string{"The current matrix has been provided as argument. This is not allowed for this method."}},
    {Errors::EMPTY_MATRIX, std::string{"Illegal operation on empty matrix"}},
    {Errors::DEREFERENCE_END_ITERATOR, std::string{"Attempt to dereference an end iterator"}},
    {Errors::INCOMPATIBLE_ITERATORS, std::string{"The two iterators are incompatible, their matrix parameters differ"}},
    {Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS,
     std::string{"The diagonal index used for obtaining the iterator is out of bounds"}},
    {Errors::ITERATOR_INDEX_OUT_OF_BOUNDS,
     std::string{"The index used for dereferencing the iterator is out of bounds"}},
    {Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED, std::string{"The maximum allowed dimensions have been exceeded."}}};
} // namespace Matr
#endif
