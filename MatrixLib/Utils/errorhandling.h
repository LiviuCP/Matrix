#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <map>
#include <cassert>
#include <string>

#ifndef ERROR_CHECKING_DISABLED
    #ifdef CONVERT_TO_EXCEPTIONS
    #define CHECK_ERROR_CONDITION(condition, errorMessage)                                      \
            {                                                                                   \
                /*printf("checking error condition, trigger exception\n");*/                    \
                if (condition)                                                                  \
                {                                                                               \
                    throw std::runtime_error(errorMessage);                                     \
                }                                                                               \
            }
    #else
    #define CHECK_ERROR_CONDITION(condition, errorMessage)                                      \
            {                                                                                   \
                /*printf("checking error condition, assertion\n");*/                            \
                if (condition)                                                                  \
                {                                                                               \
                    fprintf(stderr, "ASSERTION ERROR TRIGERRED! %s\n", errorMessage.c_str());   \
                    assert(false);                                                              \
                }                                                                               \
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
        NULL_OR_NEG_DIMENSION,
        ROW_DOES_NOT_EXIST,
        COLUMN_DOES_NOT_EXIST,
        DIAGONAL_DOES_NOT_EXIST,
        MATRIXES_UNEQUAL_COLUMN_LENGTH,
        MATRIXES_UNEQUAL_ROW_LENGTH,
        NEGATIVE_ARG,
        INSERT_ROW_NONCONTIGUOUS,
        INSERT_COLUMN_NONCONTIGUOUS,
        INVALID_ELEMENT_INDEX,
        RESULT_NO_ROWS,
        RESULT_NO_COLUMNS,
        SAME_VARIABLE_TWO_ARGS,
        EMPTY_MATRIX,
        DEREFERENCE_END_ITERATOR,
        INCOMPATIBLE_ITERATORS,
        DIAGONAL_INDEX_OUT_OF_BOUNDS,
        ITERATOR_INDEX_OUT_OF_BOUNDS
    };

    using namespace std;

    static std::map<Errors, string> errorMessages
    {
        {    Errors::INSUFFICIENT_ELEMENTS_FOR_INIT,                     string{"Not enough elements to initialize the matrix"}                                                                                  },
        {    Errors::NULL_OR_NEG_DIMENSION,                              string{"At least one null or negative matrix dimension has been entered."}                                                              },
        {    Errors::ROW_DOES_NOT_EXIST,                                 string{"For one or more matrixes at least one referenced row does not exist"}                                                           },
        {    Errors::COLUMN_DOES_NOT_EXIST,                              string{"For one or more matrixes at least one referenced column does not exist"}                                                        },
        {    Errors::DIAGONAL_DOES_NOT_EXIST,                            string{"The provided matrix diagonal does not exist"}                                                                                   },
        {    Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH,                     string{"The columns of the two matrixes have different lengths. The number of rows is different."}                                      },
        {    Errors::MATRIXES_UNEQUAL_ROW_LENGTH,                        string{"The rows of the two matrixes have different lengths. The number of columns is different."}                                      },
        {    Errors::NEGATIVE_ARG,                                       string{"The function received a negative argument. A non-negative arg is expected."}                                                    },
        {    Errors::INSERT_ROW_NONCONTIGUOUS,                           string{"Attempt to insert a row on a non-contiguous position"}                                                                          },
        {    Errors::INSERT_COLUMN_NONCONTIGUOUS,                        string{"Attempt to insert a column on a non-contiguous position"}                                                                       },
        {    Errors::INVALID_ELEMENT_INDEX,                              string{"Attempt to reference a matrix element with invalid index"}                                                                      },
        {    Errors::RESULT_NO_ROWS,                                     string{"The resulting matrix has 0 rows"}                                                                                               },
        {    Errors::RESULT_NO_COLUMNS,                                  string{"The resulting matrix has 0 columns"}                                                                                            },
        {    Errors::SAME_VARIABLE_TWO_ARGS,                             string{"Same variable passed as two arguments to the function. This is not allowed for this method."}                                   },
        {    Errors::EMPTY_MATRIX,                                       string{"Illegal operation on empty matrix"}                                                                                             },
        {    Errors::DEREFERENCE_END_ITERATOR,                           string{"Attempt to dereference an end iterator"}                                                                                        },
        {    Errors::INCOMPATIBLE_ITERATORS,                             string{"The two iterators are incompatible, their matrix parameters differ"}                                                            },
        {    Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS,                       string{"The diagonal index used for obtaining the iterator is out of bounds"}                                                           },
        {    Errors::ITERATOR_INDEX_OUT_OF_BOUNDS,                       string{"The index used for dereferencing the iterator is out of bounds"}                                                                }
    };
}
#endif

#endif // ERROR_HANDLING_H
