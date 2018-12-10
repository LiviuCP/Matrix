#include <QtTest>

#include "../../MatrixLib/matrix.h"

using IntMatrix = Matrix<int>;

class CommonTests : public QObject
{
    Q_OBJECT

public:
    CommonTests();
    ~CommonTests();

private slots:
    void testDefaultConstructor();
    void testInitListConstructor();
    void testIdenticalMatrixConstructor();
    void testDiagMatrixConstructor();
    void testCopyConstructor();
    void testMoveConstructor();
    void testSwapNonEmptyMatrixes();
    void testSwapEmptyWithNonEmptyMatrix();
    void testSwapEmptyMatrixes();
    void testSwapItemSameMatrix();
    void testSwapItemTwoMatrixes();
    void testSwapRowSameMatrix();
    void testSwapRowTwoMatrixes();
    void testSwapColumnSameMatrix();
    void testSwapColumnTwoMatrixes();
    void testSwapRowColumnTwoMatrixes();
    void testConcatenateTwoMatrixesVertically();
    void testConcatenateTwoMatrixesHorizontally();
};

CommonTests::CommonTests()
{

}

CommonTests::~CommonTests()
{

}

void CommonTests::testDefaultConstructor()
{
    IntMatrix matrix{};

    QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Default constructor initialized matrix with wrong number of rows and columns");

    int nrOfRows, nrOfColumns;
    int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns)};

    QVERIFY2(!matrixPtr, "Default constructor allocated the wrong number of elements to the matrix");
}

void CommonTests::testInitListConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };

    QVERIFY2(matrix.getNrOfRows() == 2 && matrix.getNrOfColumns() == 3, "Init list constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrix.at(0, 0) == 1 &&
             matrix.at(0, 1) == 2 &&
             matrix.at(0, 2) == 3 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 5 &&
             matrix.at(1, 2) == 6,

             "Matrix elements have not been correctly initialized by the init list constructor");
}

void CommonTests::testIdenticalMatrixConstructor()
{
    IntMatrix matrix{3, 2, 4};

    QVERIFY2(matrix.getNrOfRows() == 3 && matrix.getNrOfColumns() == 2, "Identical matrix constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrix.at(0, 0) == 4 &&
             matrix.at(0, 1) == 4 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 4 &&
             matrix.at(2, 0) == 4 &&
             matrix.at(2, 1) == 4,

             "Matrix elements have not been correctly initialized by the identical matrix constructor");
}

void CommonTests::testDiagMatrixConstructor()
{
    IntMatrix matrix{3, std::pair<int, int>{2,1}};

    QVERIFY2(matrix.getNrOfRows() == 3 && matrix.getNrOfColumns() == 3, "Diagonal matrix constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrix.at(0, 0) == 1 &&
             matrix.at(0, 1) == 2 &&
             matrix.at(0, 2) == 2 &&
             matrix.at(1, 0) == 2 &&
             matrix.at(1, 1) == 1 &&
             matrix.at(1, 2) == 2 &&
             matrix.at(2, 0) == 2 &&
             matrix.at(2, 1) == 2 &&
             matrix.at(2, 2) == 1,

             "Matrix elements have not been correctly initialized by the diagonal matrix constructor");
}

void CommonTests::testCopyConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };
    IntMatrix matrixCopy{matrix};

    QVERIFY2(matrixCopy.getNrOfRows() == 2 && matrixCopy.getNrOfColumns() == 3, "Copy constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrixCopy.at(0, 0) == 1 &&
             matrixCopy.at(0, 1) == 2 &&
             matrixCopy.at(0, 2) == 3 &&
             matrixCopy.at(1, 0) == 4 &&
             matrixCopy.at(1, 1) == 5 &&
             matrixCopy.at(1, 2) == 6,

             "Matrix elements have not been correctly initialized by the copy constructor");
}

void CommonTests::testMoveConstructor()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6} };
    IntMatrix matrixMove{std::move(matrix)};

    QVERIFY2(matrixMove.getNrOfRows() == 2 && matrixMove.getNrOfColumns() == 3, "Move constructor initialized matrix with wrong number of rows and columns");
    QVERIFY2(matrixMove.at(0, 0) == 1 &&
             matrixMove.at(0, 1) == 2 &&
             matrixMove.at(0, 2) == 3 &&
             matrixMove.at(1, 0) == 4 &&
             matrixMove.at(1, 1) == 5 &&
             matrixMove.at(1, 2) == 6,

             "Matrix elements have not been correctly initialized by the move constructor");

    QVERIFY2(matrix.getNrOfRows() == 0 && matrix.getNrOfColumns() == 0, "Move constructor set the wrong number of rows and columns to the source matrix");

    int nrOfRows, nrOfColumns;
    int** matrixPtr{matrix.getBaseArrayPtr(nrOfRows, nrOfColumns)};

    QVERIFY2(!matrixPtr, "The ressources haven't been correctly moved to the destination matrix by move constructor");
}

void CommonTests::testSwapNonEmptyMatrixes()
{
    IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

    std::swap(firstMatrix, secondMatrix);

    QVERIFY2(firstMatrix.getNrOfRows() == 3 &&
             firstMatrix.getNrOfColumns() == 2,

             "Incorrect number of rows and/or columns in the first matrix after swap");

    QVERIFY2(secondMatrix.getNrOfRows() == 2 &&
             secondMatrix.getNrOfColumns() == 3,

             "Incorrect number of rows and/or columns in the second matrix after swap");

    QVERIFY2(firstMatrix.at(0, 0) == 7 &&
             firstMatrix.at(0, 1) == 8 &&
             firstMatrix.at(1, 0) == 9 &&
             firstMatrix.at(1, 1) == 10 &&
             firstMatrix.at(2, 0) == 11 &&
             firstMatrix.at(2, 1) == 12,

             "First matrix has incorrect element values after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 1 &&
             secondMatrix.at(0, 1) == 2 &&
             secondMatrix.at(0, 2) == 3 &&
             secondMatrix.at(1, 0) == 4 &&
             secondMatrix.at(1, 1) == 5 &&
             secondMatrix.at(1, 2) == 6,

             "Second matrix has incorrect element values after swap");
}

void CommonTests::testSwapEmptyWithNonEmptyMatrix()
{
    IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    IntMatrix secondMatrix{};

    std::swap(firstMatrix, secondMatrix);

    QVERIFY2(firstMatrix.getNrOfRows() == 0 &&
             firstMatrix.getNrOfColumns() == 0,

             "Incorrect number of rows and/or columns in the first matrix after swap");

    QVERIFY2(secondMatrix.getNrOfRows() == 2 &&
             secondMatrix.getNrOfColumns() == 3,

             "Incorrect number of rows and/or columns in the second matrix after swap");

    int nrOfRows, nrOfColumns;
    int** matrixPtr{firstMatrix.getBaseArrayPtr(nrOfRows, nrOfColumns)};

    QVERIFY2(!matrixPtr, "First matrix has incorrect number of elements after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 1 &&
             secondMatrix.at(0, 1) == 2 &&
             secondMatrix.at(0, 2) == 3 &&
             secondMatrix.at(1, 0) == 4 &&
             secondMatrix.at(1, 1) == 5 &&
             secondMatrix.at(1, 2) == 6,

             "Second matrix has incorrect element values after swap");
}

void CommonTests::testSwapEmptyMatrixes()
{
    IntMatrix firstMatrix{};
    IntMatrix secondMatrix{};

    std::swap(firstMatrix, secondMatrix);

    QVERIFY2(firstMatrix.getNrOfRows() == 0 &&
             firstMatrix.getNrOfColumns() == 0,

             "Incorrect number of rows and/or columns in the first matrix after swap");

    QVERIFY2(secondMatrix.getNrOfRows() == 0 &&
             secondMatrix.getNrOfColumns() == 0,

             "Incorrect number of rows and/or columns in the second matrix after swap");

    int nrOfRows, nrOfColumns;
    int** matrixPtr{firstMatrix.getBaseArrayPtr(nrOfRows, nrOfColumns)};

    QVERIFY2(!matrixPtr, "First matrix has incorrect number of elements after swap");

    matrixPtr = secondMatrix.getBaseArrayPtr(nrOfRows, nrOfColumns);

    QVERIFY2(!matrixPtr, "Second matrix has incorrect number of elements after swap");
}

void CommonTests::testSwapItemSameMatrix()
{
    IntMatrix matrix{2, 3, {1, 2, 3, 4, 5, 6}};

    matrix.swapItem(1, 2, matrix, 0, 1);

    QVERIFY2(matrix.at(0, 0) == 1 &&
             matrix.at(0, 1) == 6 &&
             matrix.at(0, 2) == 3 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 5 &&
             matrix.at(1, 2) == 2,

             "Items are incorrectly swapped within same matrix");
}

void CommonTests::testSwapItemTwoMatrixes()
{
    IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    IntMatrix secondMatrix{3, 2, {7, 8, 9, 10, 11, 12}};

    firstMatrix.swapItem(1, 2, secondMatrix, 2, 0);

    QVERIFY2(firstMatrix.at(0, 0) == 1 &&
             firstMatrix.at(0, 1) == 2 &&
             firstMatrix.at(0, 2) == 3 &&
             firstMatrix.at(1, 0) == 4 &&
             firstMatrix.at(1, 1) == 5 &&
             firstMatrix.at(1, 2) == 11,

             "Items are incorrectly swapped between matrixes, first matrix does not have the desired value after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 7 &&
             secondMatrix.at(0, 1) == 8 &&
             secondMatrix.at(1, 0) == 9 &&
             secondMatrix.at(1, 1) == 10 &&
             secondMatrix.at(2, 0) == 6 &&
             secondMatrix.at(2, 1) == 12,

             "Items are incorrectly swapped between matrixes, second matrix does not have the desired value after swap");
}

void CommonTests::testSwapRowSameMatrix()
{
    IntMatrix matrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    matrix.swapRow(0, matrix, 2);

    QVERIFY2(matrix.at(0, 0) == 7 &&
             matrix.at(0, 1) == 8 &&
             matrix.at(0, 2) == 9 &&
             matrix.at(1, 0) == 4 &&
             matrix.at(1, 1) == 5 &&
             matrix.at(1, 2) == 6 &&
             matrix.at(2, 0) == 1 &&
             matrix.at(2, 1) == 2 &&
             matrix.at(2, 2) == 3 &&
             matrix.at(3, 0) == 10 &&
             matrix.at(3, 1) == 11 &&
             matrix.at(3, 2) == 12,

             "Rows are incorrectly swapped within same matrix");
}

void CommonTests::testSwapRowTwoMatrixes()
{
    IntMatrix firstMatrix{2, 3, {1, 2, 3, 4, 5, 6}};
    IntMatrix secondMatrix{4, 3, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};

    firstMatrix.swapRow(0, secondMatrix, 3);

    QVERIFY2(firstMatrix.at(0, 0) == 16 &&
             firstMatrix.at(0, 1) == 17 &&
             firstMatrix.at(0, 2) == 18 &&
             firstMatrix.at(1, 0) == 4 &&
             firstMatrix.at(1, 1) == 5 &&
             firstMatrix.at(1, 2) == 6,

             "Rows are incorrectly swapped between matrixes, first matrix does not have the desired value after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 7 &&
             secondMatrix.at(0, 1) == 8 &&
             secondMatrix.at(0, 2) == 9 &&
             secondMatrix.at(1, 0) == 10 &&
             secondMatrix.at(1, 1) == 11 &&
             secondMatrix.at(1, 2) == 12 &&
             secondMatrix.at(2, 0) == 13 &&
             secondMatrix.at(2, 1) == 14 &&
             secondMatrix.at(2, 2) == 15 &&
             secondMatrix.at(3, 0) == 1 &&
             secondMatrix.at(3, 1) == 2 &&
             secondMatrix.at(3, 2) == 3,

             "Rows are incorrectly swapped between matrixes, second matrix does not have the desired value after swap");
}

void CommonTests::testSwapColumnSameMatrix()
{
    IntMatrix matrix{3, 4, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};

    matrix.swapColumn(0, matrix, 2);

    QVERIFY2(matrix.at(0, 0) == 3 &&
             matrix.at(0, 1) == 2 &&
             matrix.at(0, 2) == 1 &&
             matrix.at(0, 3) == 4 &&
             matrix.at(1, 0) == 7 &&
             matrix.at(1, 1) == 6 &&
             matrix.at(1, 2) == 5 &&
             matrix.at(1, 3) == 8 &&
             matrix.at(2, 0) == 11 &&
             matrix.at(2, 1) == 10 &&
             matrix.at(2, 2) == 9 &&
             matrix.at(2, 3) == 12,

             "Columns are incorrectly swapped within same matrix");
}

void CommonTests::testSwapColumnTwoMatrixes()
{
    IntMatrix firstMatrix{3, 2, {1, 2, 3, 4, 5, 6}};
    IntMatrix secondMatrix{3, 4, {7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18}};

    firstMatrix.swapColumn(0, secondMatrix, 3);

    QVERIFY2(firstMatrix.at(0, 0) == 10 &&
             firstMatrix.at(0, 1) == 2 &&
             firstMatrix.at(1, 0) == 14 &&
             firstMatrix.at(1, 1) == 4 &&
             firstMatrix.at(2, 0) == 18 &&
             firstMatrix.at(2, 1) == 6,

             "Columns are incorrectly swapped between matrixes, first matrix does not have the desired value after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 7 &&
             secondMatrix.at(0, 1) == 8 &&
             secondMatrix.at(0, 2) == 9 &&
             secondMatrix.at(0, 3) == 1 &&
             secondMatrix.at(1, 0) == 11 &&
             secondMatrix.at(1, 1) == 12 &&
             secondMatrix.at(1, 2) == 13 &&
             secondMatrix.at(1, 3) == 3 &&
             secondMatrix.at(2, 0) == 15 &&
             secondMatrix.at(2, 1) == 16 &&
             secondMatrix.at(2, 2) == 17 &&
             secondMatrix.at(2, 3) == 5,

             "Columns are incorrectly swapped between matrixes, second matrix does not have the desired value after swap");
}

void CommonTests::testSwapRowColumnTwoMatrixes()
{
    IntMatrix firstMatrix{4, 3, {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}};
    IntMatrix secondMatrix{3, 4, {13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24}};

    firstMatrix.swapRowColumn(0, secondMatrix, 3);

    QVERIFY2(firstMatrix.at(0, 0) == 16 &&
             firstMatrix.at(0, 1) == 20 &&
             firstMatrix.at(0, 2) == 24 &&
             firstMatrix.at(1, 0) == 4 &&
             firstMatrix.at(1, 1) == 5 &&
             firstMatrix.at(1, 2) == 6 &&
             firstMatrix.at(2, 0) == 7 &&
             firstMatrix.at(2, 1) == 8 &&
             firstMatrix.at(2, 2) == 9 &&
             firstMatrix.at(3, 0) == 10 &&
             firstMatrix.at(3, 1) == 11 &&
             firstMatrix.at(3, 2) == 12,

             "Row from first matrix is incorrectly swapped with column from the second, first matrix does not have the desired value after swap");

    QVERIFY2(secondMatrix.at(0, 0) == 13 &&
             secondMatrix.at(0, 1) == 14 &&
             secondMatrix.at(0, 2) == 15 &&
             secondMatrix.at(0, 3) == 1 &&
             secondMatrix.at(1, 0) == 17 &&
             secondMatrix.at(1, 1) == 18 &&
             secondMatrix.at(1, 2) == 19 &&
             secondMatrix.at(1, 3) == 2 &&
             secondMatrix.at(2, 0) == 21 &&
             secondMatrix.at(2, 1) == 22 &&
             secondMatrix.at(2, 2) == 23 &&
             secondMatrix.at(2, 3) == 3,

             "Row from first matrix is incorrectly swapped with column from the second, second matrix does not have the desired value after swap");
}

void CommonTests::testConcatenateTwoMatrixesVertically()
{
    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{1, 2, {5, 6}};
        IntMatrix thirdMatrix{};

        thirdMatrix.concatenate(firstMatrix, secondMatrix);

        if (thirdMatrix.getNrOfRows() != 3 || thirdMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(thirdMatrix.at(0, 0) == 1 &&
                 thirdMatrix.at(0, 1) == 2 &&
                 thirdMatrix.at(1, 0) == 3 &&
                 thirdMatrix.at(1, 1) == 4 &&
                 thirdMatrix.at(2, 0) == 5 &&
                 thirdMatrix.at(2, 1) == 6,

                 "Vertical concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{1, 2, {5, 6}};

        firstMatrix.concatenate(firstMatrix, secondMatrix);

        if (firstMatrix.getNrOfRows() != 3 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(1, 0) == 3 &&
                 firstMatrix.at(1, 1) == 4 &&
                 firstMatrix.at(2, 0) == 5 &&
                 firstMatrix.at(2, 1) == 6,

                 "Vertical concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{1, 2, {5, 6}};

        secondMatrix.concatenate(firstMatrix, secondMatrix);

        if (secondMatrix.getNrOfRows() != 3 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4 &&
                 secondMatrix.at(2, 0) == 5 &&
                 secondMatrix.at(2, 1) == 6,

                 "Vertical concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};

        firstMatrix.concatenate(firstMatrix, firstMatrix);

        if (firstMatrix.getNrOfRows() != 4 || firstMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(1, 0) == 3 &&
                 firstMatrix.at(1, 1) == 4 &&
                 firstMatrix.at(2, 0) == 1 &&
                 firstMatrix.at(2, 1) == 2 &&
                 firstMatrix.at(3, 0) == 3 &&
                 firstMatrix.at(3, 1) == 4,

                 "Vertical concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{};

        secondMatrix.concatenate(firstMatrix, firstMatrix);

        if (secondMatrix.getNrOfRows() != 4 || secondMatrix.getNrOfColumns() != 2)
        {
            QFAIL("Vertical concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4 &&
                 secondMatrix.at(2, 0) == 1 &&
                 secondMatrix.at(2, 1) == 2 &&
                 secondMatrix.at(3, 0) == 3 &&
                 secondMatrix.at(3, 1) == 4,

                 "Vertical concatenation failed, destination matrix has incorrect values!");
    }
}

void CommonTests::testConcatenateTwoMatrixesHorizontally()
{
    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{2, 1, {5, 6}};
        IntMatrix thirdMatrix{};

        thirdMatrix.concatenate(firstMatrix, secondMatrix, false);

        if (thirdMatrix.getNrOfRows() != 2 || thirdMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Horizontal concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(thirdMatrix.at(0, 0) == 1 &&
                 thirdMatrix.at(0, 1) == 2 &&
                 thirdMatrix.at(0, 2) == 5 &&
                 thirdMatrix.at(1, 0) == 3 &&
                 thirdMatrix.at(1, 1) == 4 &&
                 thirdMatrix.at(1, 2) == 6,

                 "Horizontal concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{2, 1, {5, 6}};

        firstMatrix.concatenate(firstMatrix, secondMatrix, false);

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Horizontal concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(0, 2) == 5 &&
                 firstMatrix.at(1, 0) == 3 &&
                 firstMatrix.at(1, 1) == 4 &&
                 firstMatrix.at(1, 2) == 6,

                 "Horizontal concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{2, 1, {5, 6}};

        secondMatrix.concatenate(firstMatrix, secondMatrix, false);

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 3)
        {
            QFAIL("Horizontal concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(0, 2) == 5 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4 &&
                 secondMatrix.at(1, 2) == 6,

                 "Horizontal concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};

        firstMatrix.concatenate(firstMatrix, firstMatrix, false);

        if (firstMatrix.getNrOfRows() != 2 || firstMatrix.getNrOfColumns() != 4)
        {
            QFAIL("Horizontal concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(firstMatrix.at(0, 0) == 1 &&
                 firstMatrix.at(0, 1) == 2 &&
                 firstMatrix.at(0, 2) == 1 &&
                 firstMatrix.at(0, 3) == 2 &&
                 firstMatrix.at(1, 0) == 3 &&
                 firstMatrix.at(1, 1) == 4 &&
                 firstMatrix.at(1, 2) == 3 &&
                 firstMatrix.at(1, 3) == 4,

                 "Horizontal concatenation failed, destination matrix has incorrect values!");
    }

    {
        IntMatrix firstMatrix{2, 2, {1, 2, 3, 4}};
        IntMatrix secondMatrix{};

        secondMatrix.concatenate(firstMatrix, firstMatrix, false);

        if (secondMatrix.getNrOfRows() != 2 || secondMatrix.getNrOfColumns() != 4)
        {
            QFAIL("Horizontal concatenation failed, number of rows or columns of the destination matrix is not correct!");
        }

        QVERIFY2(secondMatrix.at(0, 0) == 1 &&
                 secondMatrix.at(0, 1) == 2 &&
                 secondMatrix.at(0, 2) == 1 &&
                 secondMatrix.at(0, 3) == 2 &&
                 secondMatrix.at(1, 0) == 3 &&
                 secondMatrix.at(1, 1) == 4 &&
                 secondMatrix.at(1, 2) == 3 &&
                 secondMatrix.at(1, 3) == 4,

                 "Horizontal concatenation failed, destination matrix has incorrect values!");
    }
}

QTEST_APPLESS_MAIN(CommonTests)

#include "tst_commontests.moc"
