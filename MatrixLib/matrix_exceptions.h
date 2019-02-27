#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <map>

namespace Matr
{
    enum class Error
    {
        INSUFFICIENT_ELEMENTS_FOR_INIT,
        NULL_OR_NEG_DIMENSION,
        ROW_DOES_NOT_EXIST,
        COLUMN_DOES_NOT_EXIST,
        MATRIXES_ROWS_UNEQUAL_COLUMNS,
        MATRIXES_UNEQUAL_COLUMN_LENGTH,
        MATRIXES_UNEQUAL_ROW_LENGTH,
        NEGATIVE_ARG,
        INSERT_ROW_NONCONTIGUOUS,
        INSERT_COLUMN_NONCONTIGUOUS,
        INVALID_ELEMENT_INDEX,
        RESULT_NO_ROWS,
        RESULT_NO_COLUMNS,
        SAME_VARIABLE_TWO_ARGS,
        CURRENT_MATRIX_AS_ARG,
        EMPTY_MATRIX,
        DEREFERENCE_END_ITERATOR
    };

    using namespace std;

    static std::map<Error, string> exceptions
    {
        {    Error::INSUFFICIENT_ELEMENTS_FOR_INIT,                     string{"Not enough elements to initialize the matrix"}                                                                                  },
        {    Error::NULL_OR_NEG_DIMENSION,                              string{"At least one null or negative matrix dimension has been entered."}                                                              },
        {    Error::ROW_DOES_NOT_EXIST,                                 string{"For one or more matrixes at least one referenced row does not exist"}                                                           },
        {    Error::COLUMN_DOES_NOT_EXIST,                              string{"For one or more matrixes at least one referenced column does not exist"}                                                        },
        {    Error::MATRIXES_ROWS_UNEQUAL_COLUMNS,                      string{"The number of columns of the first matrix is different from the number of lines of the second one"}                             },
        {    Error::MATRIXES_UNEQUAL_COLUMN_LENGTH,                     string{"The columns of the two matrixes have different lengths. The number of rows is different."}                                      },
        {    Error::MATRIXES_UNEQUAL_ROW_LENGTH,                        string{"The rows of the two matrixes have different lengths. The number of columns is different."}                                      },
        {    Error::NEGATIVE_ARG,                                       string{"The function received a negative argument. A non-negative arg is expected."}                                                    },
        {    Error::INSERT_ROW_NONCONTIGUOUS,                           string{"Attempt to insert a row on a non-contiguous position"}                                                                          },
        {    Error::INSERT_COLUMN_NONCONTIGUOUS,                        string{"Attempt to insert a column on a non-contiguous position"}                                                                       },
        {    Error::INVALID_ELEMENT_INDEX,                              string{"Attempt to reference a matrix element with invalid index"}                                                                      },
        {    Error::RESULT_NO_ROWS,                                     string{"The resulting matrix has 0 rows"}                                                                                               },
        {    Error::RESULT_NO_COLUMNS,                                  string{"The resulting matrix has 0 columns"}                                                                                            },
        {    Error::SAME_VARIABLE_TWO_ARGS,                             string{"Same variable passed as two arguments to the function. This is not allowed for this method."}                                   },
        {    Error::CURRENT_MATRIX_AS_ARG,                              string{"Current matrix (*this) has been passed as argument into the function. This is not allowed for this method."}                    },
        {    Error::EMPTY_MATRIX,                                       string{"Illegal operation on empty matrix"}                                                                                             },
        {    Error::DEREFERENCE_END_ITERATOR,                           string{"Attempt to dereference an end iterator"}                                                                                        }
    };
}

#endif // MATRIX_EXCEPTIONS_H
