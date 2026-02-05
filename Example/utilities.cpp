#include <cstdlib>
#include <iostream>

#include "matrix.h"

void clearScreen()
{
#if defined(__unix__) || (defined(__APPLE__) && defined(__MACH__))
    system("clear");
#else
    system("cls");
#endif
}

void printMatrix(const Matrix<int>& matrix)
{
    std::cout << std::endl;

    for (int rowNumber{0}; rowNumber < matrix.getNrOfRows(); ++rowNumber)
    {
        for (Matrix<int>::ConstZIterator it{matrix.constZRowBegin(rowNumber)}; it != matrix.constZRowEnd(rowNumber);
             ++it)
        {
            std::cout << *it << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;
}
