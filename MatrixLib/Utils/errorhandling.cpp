#include "errorhandling.h"

#ifndef ERROR_CHECKING_DISABLED
namespace Matr
{

using namespace std;

std::map<Errors, string> errorMessages{
    {Errors::INSUFFICIENT_ELEMENTS_FOR_INIT, string{"Not enough elements to initialize the matrix"}},
    {Errors::NULL_DIMENSION, string{"At least one null matrix dimension has been entered."}},
    {Errors::ROW_DOES_NOT_EXIST, string{"For one or more matrixes at least one referenced row does not exist"}},
    {Errors::COLUMN_DOES_NOT_EXIST, string{"For one or more matrixes at least one referenced column does not exist"}},
    {Errors::DIAGONAL_DOES_NOT_EXIST, string{"The provided matrix diagonal does not exist"}},
    {Errors::MATRIXES_UNEQUAL_COLUMN_LENGTH,
     string{"The columns of the two matrixes have different lengths. The number of rows is different."}},
    {Errors::MATRIXES_UNEQUAL_ROW_LENGTH,
     string{"The rows of the two matrixes have different lengths. The number of columns is different."}},
    {Errors::INSERT_ROW_NONCONTIGUOUS, string{"Attempt to insert a row on a non-contiguous position"}},
    {Errors::INSERT_COLUMN_NONCONTIGUOUS, string{"Attempt to insert a column on a non-contiguous position"}},
    {Errors::INVALID_ELEMENT_INDEX, string{"Attempt to reference a matrix element with invalid index"}},
    {Errors::RESULT_NO_ROWS, string{"The resulting matrix has 0 rows"}},
    {Errors::RESULT_NO_COLUMNS, string{"The resulting matrix has 0 columns"}},
    {Errors::CURRENT_MATRIX_AS_ARGUMENT,
     string{"The current matrix has been provided as argument. This is not allowed for this method."}},
    {Errors::EMPTY_MATRIX, string{"Illegal operation on empty matrix"}},
    {Errors::DEREFERENCE_END_ITERATOR, string{"Attempt to dereference an end iterator"}},
    {Errors::INCOMPATIBLE_ITERATORS, string{"The two iterators are incompatible, their matrix parameters differ"}},
    {Errors::DIAGONAL_INDEX_OUT_OF_BOUNDS,
     string{"The diagonal index used for obtaining the iterator is out of bounds"}},
    {Errors::ITERATOR_INDEX_OUT_OF_BOUNDS, string{"The index used for dereferencing the iterator is out of bounds"}},
    {Errors::MAX_ALLOWED_DIMENSIONS_EXCEEDED, string{"The maximum allowed dimensions have been exceeded."}}};
} // namespace Matr
#endif
