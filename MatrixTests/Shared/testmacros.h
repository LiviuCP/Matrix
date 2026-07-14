#pragma once

// useful macros shared between various test cases

#define CHECK_MATRIX_SIZE_AND_CAPACITY(matrix, requiredNrOfRows, requiredNrOfColumns, requiredRowCapacity,             \
                                       requiredColumnCapacity, requiredRowCapacityOffset,                              \
                                       requiredColumnCapacityOffset, dimensionsFailMessage, capacityFailMessage,       \
                                       capacityOffsetFailMessage)                                                      \
    if (matrix.getNrOfRows() != requiredNrOfRows || matrix.getNrOfColumns() != requiredNrOfColumns)                    \
    {                                                                                                                  \
        QFAIL(dimensionsFailMessage);                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    if (matrix.getRowCapacity() != requiredRowCapacity || matrix.getColumnCapacity() != requiredColumnCapacity)        \
    {                                                                                                                  \
        QFAIL(capacityFailMessage);                                                                                    \
    }                                                                                                                  \
                                                                                                                       \
    if (matrix.getRowCapacityOffset() != requiredRowCapacityOffset ||                                                  \
        matrix.getColumnCapacityOffset() != requiredColumnCapacityOffset)                                              \
    {                                                                                                                  \
        QFAIL(capacityOffsetFailMessage);                                                                              \
    }

#define CHECK_MATRIX_HAS_THE_RIGHT_ELEMENT_VALUES(matrix, elementsList, errorMessage)                                  \
    for (size_t elementNr{0}; elementNr < elementsList.size(); ++elementNr)                                            \
    {                                                                                                                  \
        const matrix_size_t c_ColumnsCount{matrix.getNrOfColumns()};                                                   \
                                                                                                                       \
        if (elementsList[elementNr] != matrix.at(elementNr / c_ColumnsCount, elementNr % c_ColumnsCount))              \
        {                                                                                                              \
            QFAIL(errorMessage);                                                                                       \
        }                                                                                                              \
    }

#define CHECK_ELEMENTS_ARE_IDENTICAL_AND_HAVE_CORRECT_VALUE(matrix, elementValue, errorMessage)                        \
    for (int rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr)                                                         \
    {                                                                                                                  \
        for (int columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr)                                         \
        {                                                                                                              \
            if (matrix.at(rowNr, columnNr) != elementValue)                                                            \
            {                                                                                                          \
                QFAIL(errorMessage);                                                                                   \
                break;                                                                                                 \
            }                                                                                                          \
        }                                                                                                              \
    }

#define CHECK_MATRIX_IS_DIAGONAL_WITH_CORRECT_ELEMENT_VALUES(matrix, nonDiagElementValue, diagElementValue,            \
                                                             errorMessage)                                             \
    for (StringMatrix::size_type rowNr{0u}; rowNr < matrix.getNrOfRows(); ++rowNr)                                     \
    {                                                                                                                  \
        for (StringMatrix::size_type columnNr{0u}; columnNr < matrix.getNrOfColumns(); ++columnNr)                     \
        {                                                                                                              \
            if ((rowNr != columnNr && matrix.at(rowNr, columnNr) != nonDiagElementValue) ||                            \
                (rowNr == columnNr && matrix.at(rowNr, columnNr) != diagElementValue))                                 \
            {                                                                                                          \
                QFAIL(errorMessage);                                                                                   \
            }                                                                                                          \
        }                                                                                                              \
    }
