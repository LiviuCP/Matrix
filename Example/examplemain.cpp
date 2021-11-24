/* Small example project illustrating the usage of the Matrix library */

#include <iostream>
#include <algorithm>

#include "matrix.h"

using namespace std;
using IntMatrix = Matrix<int>;

extern void clearScreen();
extern void printMatrix(const IntMatrix& matrix);

int main()
{
    clearScreen();

    cout << "This is a small usage example of the Matrix library" << endl << endl;
    cout << "We will take a Matrix and perform following operations:" << endl;
    cout << "- calculate column subtotals" << endl;
    cout << "- perform a per-column sorting in decreasing order" << endl;
    cout << "- replace the origin diagonal values with a new value" << endl;
    cout << "- insert a row with the calculated subtotals within matrix" << endl << endl;

    IntMatrix matrix{4, 5, {
            -1,  6,  8, 2,  4,
             5,  7,  1, 1, -1,
             5, -5,  4, 1,  2,
             0,  1, -1, 0,  6
    }};

    IntMatrix matrixCopy{matrix}; // matrix copy not really needed, it's just for demonstrating the usage of the copy constructor
    IntMatrix columnSubtotalsMatrix{1, matrix.getNrOfColumns(), 0};

    for (int columnNumber{0}; columnNumber < matrix.getNrOfColumns(); ++columnNumber)
    {
        int currentSubtotal{0};

        for (IntMatrix::ConstNIterator it{matrix.constNColumnBegin(columnNumber)}; it != matrix.constNColumnEnd(columnNumber); ++it)
        {
            currentSubtotal += *it;
        }

        columnSubtotalsMatrix[columnNumber] = currentSubtotal;
        std::sort(matrixCopy.reverseNColumnBegin(columnNumber), matrixCopy.reverseNColumnEnd(columnNumber));
    }

    cout << "The original matrix is: " << endl;

    printMatrix(matrix);

    cout << "The column subtotals are: " << endl;

    printMatrix(columnSubtotalsMatrix);

    cout << "The per column decreasingly sorted matrix is: " << endl;

    printMatrix(matrixCopy);

    const int diagonalValue{-9};

    matrix = std::move(matrixCopy); // just for demonstrating the usage of the move assignment operator

    for (IntMatrix::DIterator it{matrix.dBegin(0)}; it != matrix.dEnd(0); ++it)
    {
        *it = diagonalValue;
    }

    cout << "After replacing the origin diagonal values of the sorted matrix with value " << diagonalValue << " the updated matrix is: " << endl;

    printMatrix(matrix);

    const int rowPositionToInsert{1};
    matrix.insertRow(rowPositionToInsert);

    for (IntMatrix::ZIterator it{matrix.zRowBegin(rowPositionToInsert)}; it != matrix.zRowEnd(rowPositionToInsert); ++it)
    {
        *it = columnSubtotalsMatrix.at(0, static_cast<size_t>(it.getColumnNr()));
    }

    cout << "After inserting the subtotals on row " << rowPositionToInsert + 1 << " the final matrix is: " << endl;

    printMatrix(matrix);

    cout << "Goodbye!" << endl << endl;

    return 0;
}
