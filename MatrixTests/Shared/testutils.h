#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <QPointF>

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
using TripleSizeTypeTuple = std::tuple<IntMatrixSizeType, IntMatrixSizeType, IntMatrixSizeType>;
using TripleSizeTypeTupleArray = std::vector<TripleSizeTypeTuple>;

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
    SOURCE_SECOND
};

#endif // TESTUTILS_H
