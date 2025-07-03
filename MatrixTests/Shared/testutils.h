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

// various constants related to the maximum allowed matrix dimensions
static constexpr matrix_size_t c_MaxAllowedDimension{maxAllowedDimension()};
static constexpr matrix_size_t c_LargeDimension0{c_MaxAllowedDimension - 3};
static constexpr matrix_size_t c_LargeDimension1{c_MaxAllowedDimension - 2};
static constexpr matrix_size_t c_LargeDimension2{c_MaxAllowedDimension - 1};
static constexpr matrix_size_t c_ExceedingDimension{c_MaxAllowedDimension + 1};
static constexpr matrix_size_t c_HalfMaxAllowedDimension{c_MaxAllowedDimension / 2};
static constexpr matrix_size_t c_DecrHalfMaxAllowedDimension{c_MaxAllowedDimension / 2 - 1};
static constexpr matrix_size_t c_IncrHalfMaxAllowedDimension{c_MaxAllowedDimension / 2 + 1};
static constexpr matrix_size_t c_ThreeQuartersMaxAllowedDimension{c_HalfMaxAllowedDimension + c_HalfMaxAllowedDimension / 2};
static constexpr matrix_size_t c_QuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_MaxAllowedDimension / 4)};
static constexpr matrix_size_t c_FiveEighthsMaxAllowedDimension{static_cast<matrix_size_t>(c_HalfMaxAllowedDimension + c_HalfMaxAllowedDimension / 4)};
static constexpr matrix_size_t c_SevenEighthsMaxAllowedDimension{static_cast<matrix_size_t>(7 * (c_MaxAllowedDimension / 8))};
static constexpr matrix_size_t c_DecrQuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_QuarterMaxAllowedDimension - 1)};
static constexpr matrix_size_t c_IncrQuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_QuarterMaxAllowedDimension + 1)};
static constexpr matrix_size_t c_TwiceIncrQuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_IncrQuarterMaxAllowedDimension + 1)};
static constexpr matrix_size_t c_DoubleQuarterMaxAllowedDimension{static_cast<matrix_size_t>(2 * c_QuarterMaxAllowedDimension)};
static constexpr matrix_size_t c_DoubleDecrQuarterMaxAllowedDimension{static_cast<matrix_size_t>(2 * c_DecrQuarterMaxAllowedDimension)};
static constexpr matrix_size_t c_HalfQuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_QuarterMaxAllowedDimension / 2)};
static constexpr matrix_size_t c_HalfDecrQuarterMaxAllowedDimension{static_cast<matrix_size_t>(c_DecrQuarterMaxAllowedDimension / 2)};
static constexpr matrix_size_t c_HalfThreeQuartersMaxAllowedDimension{static_cast<matrix_size_t>((c_MaxAllowedDimension - c_QuarterMaxAllowedDimension) / 2)};

static constexpr matrix_size_t c_HalfToFiveEighthsCapacityOffset{static_cast<matrix_size_t>((c_FiveEighthsMaxAllowedDimension - c_HalfMaxAllowedDimension) / 2)};
static constexpr matrix_size_t c_HalfToMaxCapacityOffset{static_cast<matrix_size_t>((c_MaxAllowedDimension - c_HalfMaxAllowedDimension) / 2)};
static constexpr matrix_size_t c_SevenEighthsToMaxCapacityOffset{static_cast<matrix_size_t>((c_MaxAllowedDimension - c_SevenEighthsMaxAllowedDimension) / 2)};


static constexpr bool c_IsEvenMaxAllowedDimension{0 == c_MaxAllowedDimension % 2};

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

#define CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(matrix, elementValue, errorMessage) \
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
