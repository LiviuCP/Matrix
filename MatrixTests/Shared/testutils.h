#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QPointF>
#include <string>

#include "matrix.h"

using matrix_opt_size_t = std::optional<matrix_size_t>;
using size_tuple_t = std::tuple<matrix_size_t, matrix_size_t, matrix_size_t, matrix_opt_size_t, matrix_opt_size_t>;
using size_tuple_array_t = std::vector<size_tuple_t>;

using IntMatrix = Matrix<int>;
using StringMatrix = Matrix<std::string>;
using DecMatrix = Matrix<double>;
using QPointFMatrix = Matrix<QPointF>;

using IntZIter = Matrix<int>::ZIterator;
using IntConstZIter = Matrix<int>::ConstZIterator;
using IntReverseZIter = Matrix<int>::ReverseZIterator;
using IntConstReverseZIter = Matrix<int>::ConstReverseZIterator;
using IntNIter = Matrix<int>::NIterator;
using IntConstNIter = Matrix<int>::ConstNIterator;
using IntReverseNIter = Matrix<int>::ReverseNIterator;
using IntConstReverseNIter = Matrix<int>::ConstReverseNIterator;
using IntDIter = Matrix<int>::DIterator;
using IntConstDIter = Matrix<int>::ConstDIterator;
using IntReverseDIter = Matrix<int>::ReverseDIterator;
using IntConstReverseDIter = Matrix<int>::ConstReverseDIterator;
using IntMIter = Matrix<int>::MIterator;
using IntConstMIter = Matrix<int>::ConstMIterator;
using IntReverseMIter = Matrix<int>::ReverseMIterator;
using IntConstReverseMIter = Matrix<int>::ConstReverseMIterator;

using StringZIter = Matrix<std::string>::ZIterator;
using StringConstZIter = Matrix<std::string>::ConstZIterator;
using StringReverseZIter = Matrix<std::string>::ReverseZIterator;
using StringConstReverseZIter = Matrix<std::string>::ConstReverseZIterator;
using StringNIter = Matrix<std::string>::NIterator;
using StringConstNIter = Matrix<std::string>::ConstNIterator;
using StringReverseNIter = Matrix<std::string>::ReverseNIterator;
using StringConstReverseNIter = Matrix<std::string>::ConstReverseNIterator;
using StringDIter = Matrix<std::string>::DIterator;
using StringConstDIter = Matrix<std::string>::ConstDIterator;
using StringReverseDIter = Matrix<std::string>::ReverseDIterator;
using StringConstReverseDIter = Matrix<std::string>::ConstReverseDIterator;
using StringMIter = Matrix<std::string>::MIterator;
using StringConstMIter = Matrix<std::string>::ConstMIterator;
using StringReverseMIter = Matrix<std::string>::ReverseMIterator;
using StringConstReverseMIter = Matrix<std::string>::ConstReverseMIterator;

// matrix concatenation
enum class ConcatMode : unsigned short
{
    ALL_DIFFERENT,
    DESTINATION_FIRST,
    DESTINATION_SECOND,
    SOURCE_BOTH,
    DESTINATION_ALL
};

// matrix splitting
enum class SplitMode : unsigned short
{
    ALL_DIFFERENT,
    SOURCE_FIRST,
    SOURCE_SECOND,

    // for exceptions testing only
    DESTINATION_BOTH,
    DESTINATION_ALL
};

// useful macros shared between various test cases
#define CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, \
                                       requiredRowCapacity, requiredColumnCapacity, requiredRowCapacityOffset, requiredColumnCapacityOffset, \
                                       dimensionsFailMessage, capacityFailMessage, capacityOffsetFailMessage) \
    if (matrix.getNrOfRows() != requiredNrOfRows || matrix.getNrOfColumns() != requiredNrOfColumns) \
    { \
        QFAIL(dimensionsFailMessage); \
    } \
\
    if (matrix.getRowCapacity() != requiredRowCapacity || matrix.getColumnCapacity() != requiredColumnCapacity) \
    { \
        QFAIL(capacityFailMessage); \
    } \
\
    if (matrix.getRowCapacityOffset() != requiredRowCapacityOffset || matrix.getColumnCapacityOffset() != requiredColumnCapacityOffset) \
    { \
        QFAIL(capacityOffsetFailMessage); \
    }

#define CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(matrix, elementsList, errorMessage) \
    for (size_t elementNr{0}; elementNr < elementsList.size(); ++elementNr) \
    { \
        const matrix_size_t c_ColumnsCount{matrix.getNrOfColumns()}; \
\
        if (elementsList[elementNr] != matrix.at(elementNr / c_ColumnsCount, elementNr % c_ColumnsCount)) \
        { \
            QFAIL(errorMessage); \
        } \
    }

#define CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(matrix, elementValue, errorMessage) \
    for (int rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr) \
    { \
        for (int columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr) \
        { \
            if (matrix.at(rowNr, columnNr) != elementValue) \
            { \
                QFAIL(errorMessage); \
                break; \
            } \
        } \
    }

#define CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(matrix, nonDiagElementValue, diagElementValue, errorMessage) \
    for (StringMatrix::size_type rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr) \
    { \
        for (StringMatrix::size_type columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr) \
        { \
            if ((rowNr != columnNr && matrix.at(rowNr, columnNr) != nonDiagElementValue) || (rowNr == columnNr && matrix.at(rowNr, columnNr) != diagElementValue)) \
            { \
                QFAIL(errorMessage); \
            } \
        } \
    }

#endif // TESTUTILS_H
