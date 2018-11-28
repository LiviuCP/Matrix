#ifndef MATRIX_EXCEPTIONS_H
#define MATRIX_EXCEPTIONS_H

#include <map>

namespace Matr
{
    enum class Error
    {
        INSUFFICIENT_ELEMENTS_FOR_INIT,
        UNEQUAL_MATRIX_DIMENSIONS,
        NULL_DETERMINANT,
        NULL_OR_NEG_DIMENSION,
        SRC_ROW_DOES_NOT_EXIST,
        DEST_ROW_DOES_NOT_EXIST,
        ROW_DOES_NOT_EXIST,
        SRC_COLUMN_DOES_NOT_EXIST,
        DEST_COLUMN_DOES_NOT_EXIST,
        COLUMN_DOES_NOT_EXIST,
        MATRIXES_UNEQUAL_DIMENSIONS,
        MATRIXES_ROWS_UNEQUAL_COLUMNS,
        MATRIXES_UNEQUAL_COLUMN_LENGTH,
        MATRIXES_UNEQUAL_ROW_LENGTH,
        ERASE_THE_ONLY_COLUMN,
        ERASE_THE_ONLY_ROW,
        NEGATIVE_ARG,
        INSERT_ROW_NONCONTIGUOUS,
        INSERT_COLUMN_NONCONTIGUOUS,
        INVALID_ELEMENT_INDEX,
        RESULT_NO_ROWS,
        RESULT_NO_COLUMNS,
        INVALID_NUMERIC_ARG,
        NULL_PTR,
        DIVISION_BY_ZERO,
        SAME_VARIABLE_TWO_ARGS,
        CURRENT_MATRIX_AS_ARG,
        END_OF_FILE,
        INSUFFICIENT_ELEMENTS_FILE_ROW,
        EMPTY_FILE_ROW,
        UNKNOWN_ERROR
    };

    using namespace std;

    static std::map<Error, string> exceptions
    {
        {    Error::INSUFFICIENT_ELEMENTS_FOR_INIT,                     string{"Not enough elements to initialize the matrix"}                                                                                  },
        {    Error::UNEQUAL_MATRIX_DIMENSIONS,                          string{"The dimensions of the matrix are not equal."}                                                                                   },
        {    Error::NULL_DETERMINANT,                                   string{"The matrix determinant is null. The inverse cannot be calculated."}                                                             },
        {    Error::NULL_OR_NEG_DIMENSION,                              string{"At least one null or negative matrix dimension has been entered."}                                                              },
        {    Error::SRC_ROW_DOES_NOT_EXIST,                             string{"A referenced source matrix row does not exist"}                                                                                 },
        {    Error::DEST_ROW_DOES_NOT_EXIST,                            string{"A referenced destination matrix row does not exist"}                                                                            },
        {    Error::ROW_DOES_NOT_EXIST,                                 string{"For one or more matrixes at least one referenced row does not exist"}                                                           },
        {    Error::SRC_COLUMN_DOES_NOT_EXIST,                          string{"A referenced column of the source matrix does not exist"}                                                                       },
        {    Error::DEST_COLUMN_DOES_NOT_EXIST,                         string{"A referenced column of the destination matrix does not exist"}                                                                  },
        {    Error::COLUMN_DOES_NOT_EXIST,                              string{"For one or more matrixes at least one referenced column does not exist"}                                                        },
        {    Error::MATRIXES_UNEQUAL_DIMENSIONS,                        string{"The two matrixes have different dimensions"}                                                                                    },
        {    Error::MATRIXES_ROWS_UNEQUAL_COLUMNS,                      string{"The number of columns of the first matrix is different from the number of lines of the second one"}                             },
        {    Error::MATRIXES_UNEQUAL_COLUMN_LENGTH,                     string{"The columns of the two matrixes have different lengths. The number of rows is different."}                                      },
        {    Error::MATRIXES_UNEQUAL_ROW_LENGTH,                        string{"The rows of the two matrixes have different lengths. The number of columns is different."}                                      },
        {    Error::ERASE_THE_ONLY_COLUMN,                              string{"Attempt to erase the only column of the matrix. This is not allowed."}                                                          },
        {    Error::ERASE_THE_ONLY_ROW,                                 string{"Attempt to erase the only row of the matrix. This is not allowed."}                                                             },
        {    Error::NEGATIVE_ARG,                                       string{"The function received a negative argument. A non-negative arg is expected."}                                                    },
        {    Error::INSERT_ROW_NONCONTIGUOUS,                           string{"Attempt to insert a row on a non-contiguous position"}                                                                          },
        {    Error::INSERT_COLUMN_NONCONTIGUOUS,                        string{"Attempt to insert a column on a non-contiguous position"}                                                                       },
        {    Error::INVALID_ELEMENT_INDEX,                              string{"Attempt to reference a matrix element with invalid index"}                                                                      },
        {    Error::RESULT_NO_ROWS,                                     string{"The resulting matrix has 0 rows"}                                                                                               },
        {    Error::RESULT_NO_COLUMNS,                                  string{"The resulting matrix has 0 columns"}                                                                                            },
        {    Error::INVALID_NUMERIC_ARG,                                string{"Invalid numeric argument"}                                                                                                      },
        {    Error::NULL_PTR,                                           string{"Null pointer"}                                                                                                                  },
        {    Error::DIVISION_BY_ZERO,                                   string{"Attempt to divide by 0"}                                                                                                        },
        {    Error::SAME_VARIABLE_TWO_ARGS,                             string{"Same variable passed as two arguments to the function. This is not allowed for this method."}                                   },
        {    Error::CURRENT_MATRIX_AS_ARG,                              string{"Current matrix (*this) has been passed as argument into the function. This is not allowed for this method."}                    },
        {    Error::END_OF_FILE,                                        string{"End of file. Operation aborted."}                                                                                               },
        {    Error::INSUFFICIENT_ELEMENTS_FILE_ROW,                     string{"The row read from the file contains less items than required for the current matrix row"}                                       },
        {    Error::EMPTY_FILE_ROW,                                     string{"The current row of the text file is empty"}                                                                                     },
        {    Error::UNKNOWN_ERROR,                                      string{"Unknown error"}                                                                                                                 },
    };
}

#endif // MATRIX_EXCEPTIONS_H
