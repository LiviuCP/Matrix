#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QPointF>
#include <string>

#include "matrix.h"

using IntMatrix = Matrix<int>;

using IntMatrixZIterator = Matrix<int>::ZIterator;
using IntMatrixConstZIterator = Matrix<int>::ConstZIterator;
using IntMatrixReverseZIterator = Matrix<int>::ReverseZIterator;
using IntMatrixConstReverseZIterator = Matrix<int>::ConstReverseZIterator;
using IntMatrixNIterator = Matrix<int>::NIterator;
using IntMatrixConstNIterator = Matrix<int>::ConstNIterator;
using IntMatrixReverseNIterator = Matrix<int>::ReverseNIterator;
using IntMatrixConstReverseNIterator = Matrix<int>::ConstReverseNIterator;
using IntMatrixDIterator = Matrix<int>::DIterator;
using IntMatrixConstDIterator = Matrix<int>::ConstDIterator;
using IntMatrixReverseDIterator = Matrix<int>::ReverseDIterator;
using IntMatrixConstReverseDIterator = Matrix<int>::ConstReverseDIterator;
using IntMatrixMIterator = Matrix<int>::MIterator;
using IntMatrixConstMIterator = Matrix<int>::ConstMIterator;
using IntMatrixReverseMIterator = Matrix<int>::ReverseMIterator;
using IntMatrixConstReverseMIterator = Matrix<int>::ConstReverseMIterator;

using IntMatrixSizeType = IntMatrix::size_type;
using IntMatrixDiffType = IntMatrix::diff_type;
using FiveSizeTypesTuple = std::tuple<IntMatrixSizeType, IntMatrixSizeType, IntMatrixSizeType, IntMatrixSizeType, IntMatrixSizeType>; // can be any matrix size_type, does not depend on matrix data type
using FiveSizeTypesTupleArray = std::vector<FiveSizeTypesTuple>;

using StringMatrix = Matrix<std::string>;

using StringMatrixZIterator = Matrix<std::string>::ZIterator;
using StringMatrixConstZIterator = Matrix<std::string>::ConstZIterator;
using StringMatrixReverseZIterator = Matrix<std::string>::ReverseZIterator;
using StringMatrixConstReverseZIterator = Matrix<std::string>::ConstReverseZIterator;
using StringMatrixNIterator = Matrix<std::string>::NIterator;
using StringMatrixConstNIterator = Matrix<std::string>::ConstNIterator;
using StringMatrixReverseNIterator = Matrix<std::string>::ReverseNIterator;
using StringMatrixConstReverseNIterator = Matrix<std::string>::ConstReverseNIterator;
using StringMatrixDIterator = Matrix<std::string>::DIterator;
using StringMatrixConstDIterator = Matrix<std::string>::ConstDIterator;
using StringMatrixReverseDIterator = Matrix<std::string>::ReverseDIterator;
using StringMatrixConstReverseDIterator = Matrix<std::string>::ConstReverseDIterator;
using StringMatrixMIterator = Matrix<std::string>::MIterator;
using StringMatrixConstMIterator = Matrix<std::string>::ConstMIterator;
using StringMatrixReverseMIterator = Matrix<std::string>::ReverseMIterator;
using StringMatrixConstReverseMIterator = Matrix<std::string>::ConstReverseMIterator;

using StringMatrixSizeType = StringMatrix::size_type;
using StringMatrixDiffType = StringMatrix::diff_type;

using DecMatrix = Matrix<double>;
using QPointFMatrix = Matrix<QPointF>;

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

#define CHECK_MATRIX_IS_IDENTICAL_WITH_CORRECT_ELEMENT_VALUE(matrix, elementValue, errorMessage) \
    for (int rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr) \
    { \
        for (int columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr) \
        { \
            if (matrix.at(rowNr, columnNr) != elementValue) \
            { \
                QFAIL(errorMessage); \
                break; \
            } \
        } \
    }

#define CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(matrix, nonDiagElementValue, diagElementValue, errorMessage) \
    for (StringMatrix::size_type rowNr{0}; rowNr < matrix.getNrOfRows(); ++rowNr) \
    { \
        for (StringMatrix::size_type columnNr{0}; columnNr < matrix.getNrOfColumns(); ++columnNr) \
        { \
            if ((rowNr != columnNr && matrix.at(rowNr, columnNr) != nonDiagElementValue) || (rowNr == columnNr && matrix.at(rowNr, columnNr) != diagElementValue)) \
            { \
                QFAIL(errorMessage); \
            } \
        } \
    }

#endif // TESTUTILS_H
